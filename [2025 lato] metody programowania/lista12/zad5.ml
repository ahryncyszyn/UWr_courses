
type 'v nnf =
  | NNFLit of bool * 'v           (* literal (czy zanegowany?, zmienna) *)
  | NNFConj of 'v nnf * 'v nnf    (* koniunkcja *)
  | NNFDisj of 'v nnf * 'v nnf    (* alternatywa *)

type 'v formula =
  | Var of 'v
  | Not of 'v formula
  | And of 'v formula * 'v formula
  | Or of 'v formula * 'v formula
  | Imp of 'v formula * 'v formula
  | Wtw of 'v formula * 'v formula


(* sprowadza do formuly uzywajacejtylko alternatywy koniunkcji i literalow *)
let rec elim_imp_wtw f =
  match f with
  | Var x -> Var x
  | Not p -> Not (elim_imp_wtw p)
  | And (p, q) -> And (elim_imp_wtw p, elim_imp_wtw q)
  | Or (p, q) -> Or (elim_imp_wtw p, elim_imp_wtw q)
  | Imp (p, q) -> Or (Not (elim_imp_wtw p), elim_imp_wtw q)  (* p => q  ≡  ~p v q *)
  | Wtw (p, q) ->
      let p' = elim_imp_wtw p in
      let q' = elim_imp_wtw q in
      And (Or (Not p', q'), Or (Not q', p'))                 (* p <=> q  ≡  (p => q) ^ (q => p)  ≡  (~p v q) ^ (p v ~q) *)
;;

let rec to_nnf f =
  match f with
  | Var x -> NNFLit (false, x)
  | And (p, q) -> NNFConj (to_nnf p, to_nnf q)
  | Or (p, q) -> NNFDisj (to_nnf p, to_nnf q)
  | Not f' ->
      (match f' with
       | Var x -> NNFLit (true, x)
       | Not f'' -> to_nnf f''
       | And (p, q) -> NNFDisj (to_nnf (Not p), to_nnf (Not q))     (* ~(p ^ q)  ≡  (~p v ~q) *)
       | Or (p, q) -> NNFConj (to_nnf (Not p), to_nnf (Not q))      (* nie mozna dodac Not, mozemy sie tylko wywolywac na nziszych poziomach *)
       | _ -> to_nnf (Not (elim_imp_wtw f')))
  | _ -> to_nnf (elim_imp_wtw f)
;;


let nnf_of_formula f =
  to_nnf (elim_imp_wtw f)
;;


let f0 = Not(And (Var "p", Var "q"));;
let nnf0 = nnf_of_formula f0;;

let f1 = Imp (And (Var "p", Var "q"), Var "r")
let nnf1 = nnf_of_formula f1;;

let f6 = Not (Or (Wtw (Var "p", Imp (Var "q", Var "r")), Not (And (Var "s", Var "t"))))
let nnf6 = nnf_of_formula f6;;