
(* Zaimplementuj ewaluator formuł QBF, w którym wyrazeniami sa wartosci
typu qbf, a wartosciami wartosci typu bool. 
  Niech ewaluator działa przez podstawienie stałych Top i Bot za zmienne *)

type ident = string

type qbf =
| Top (* ⊤ *)
| Bot (* ⊥ *)
| Var of ident (* x *)
| Disj of qbf * qbf (* ∨ *)
| Conj of qbf * qbf (* ∧ *)
| Not of qbf (* ¬ *)
| Forall of ident * qbf (* ∀ *)
| Exists of ident * qbf (* ∃ *)

(*                       let x = s in f                    *)
let rec subst ( x : ident ) ( s : qbf ) ( f : qbf ) : qbf = 
  match f with 
  | Top -> Top
  | Bot -> Bot
  | Var y -> if x = y then s else Var y
  | Disj (f1, f2) -> Disj (subst x s f1, subst x s f2)
  | Conj (f1, f2) -> Conj (subst x s f1, subst x s f2)
  | Not f1 -> Not (subst x s f1)
  | Forall (y, f1) -> 
    if y = x then Forall (y, subst x s f1)
    else Forall (y, subst x s f1)
  | Exists (y, f1) -> 
    if y = x then Exists (y, subst x s f1)
    else Exists (y, subst x s f1)

let rec eval ( f : qbf ) : bool = 
  match f with 
  | Top -> true
  | Bot -> false
  | Disj (f1, f2) -> eval f1 || eval f2
  | Conj (f1, f2) -> eval f1 && eval f2
  | Not f1 -> if eval f1 then false else true
  | Forall (y, f1) -> eval (subst y Top f1) && eval (subst y Bot f1)
  | Exists (y, f1) -> eval (subst y Top f1) || eval (subst y Bot f1)
  | Var _ -> failwith "unbound value";;
    


subst "x" (Var "z") (Conj(Var "y", Var "x"));;
subst "y" (Not (Var "z")) (Disj(Not (Var "y"), Var "x"));;
eval (Forall("x", Forall("y", Forall("z", Conj(Disj(Var "x", Var "y"), Var "z")))));;
eval (Not(Bot));;
eval (Forall("x", Conj(Var "x", Var "x")));;
eval (Forall("x", Disj(Var "x", Not(Var "x"))));;
eval (Exists("x", Disj(Var "x", Not(Var "x"))));;

