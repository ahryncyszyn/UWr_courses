[@@@ocaml.warning "-8"]

module I = Interp

(* Składnia RPN *)

type cmd =
  | PushInt  of int
  | PushBool of bool
  | PushPair
  | PushUnit
  | Fst
  | Snd
  | IsPair
  | Binop    of Ast.bop
  | Binop1 of Ast.bop * int
  | Binop0 of Ast.bop
  | CndJmp   of prog * prog

and prog = cmd list

(* Kompilacja do RPN *)

let rec of_ast (expr : Ast.expr) : prog =
  match expr with
  | Ast.Int n ->
      [PushInt n]
  | Ast.Bool b ->
      [PushBool b]
  | Ast.Binop (op, e1, e2) ->
      [Binop op] @ of_ast e1 @ of_ast e2                        (* zad 1 *)
  | Ast.If (b, t, e) ->
      [CndJmp (of_ast t, of_ast e)] @ of_ast b
  | Ast.Pair (e1, e2) ->
      [PushPair] @ of_ast e2 @ of_ast e1
  | Ast.Fst e ->
      [Fst] @ of_ast e
  | Ast.Snd e ->
      [Snd] @ of_ast e
  | Ast.Unit ->
      [PushUnit]
  | Ast.IsPair e ->
      [IsPair] @ of_ast e
  | _ -> failwith "not implemented"

(* testy do zad 1 *)
(* 
open Fun.Ast;; 
open Fun.Rpn;;
let 1 =
  Binop (
    Add,
    Binop (Add, Int 3, Int 8),
    Binop (
      Mult,
      Int 4,
      Binop (Sub, Int 2, Int 1)
    )
  );;

let test2 = If (Bool true, Int 1, Int 2);;
of_ast test;;
*)

(* Ewaluator dla RPN *)

(* Nowy typ dla elementów stosu, który pozwala na przechowywanie
   zarówno wartości jak i oczekujących operacji *)
type stack_item =
   | Value of I.value  (* Wartość na stosie *)
   | BinopWaiting of Ast.bop * int  (* Oczekujący operator binarny i liczba brakujących operandów *)
   | PairWaiting of int 
   | FstWaiting 
   | SndWaiting 
   | IsPairWaiting 
   | IfWaiting of prog * prog 

(* Zmodyfikowany ewaluator, który obsługuje notację polską (PN) *)
let rec eval (s : stack_item list) (p : prog) : I.value =
  match p, s with
  | [], [Value v] -> v
  | [], _ -> failwith "błąd: na stosie powinna pozostać dokładnie jedna wartość"
  | (PushInt n :: p'), s -> process_value (I.VInt n) s p'
  | (PushBool b :: p'), s -> process_value (I.VBool b) s p'
  | (PushUnit :: p'), s -> process_value (I.VUnit) s p'
  | (Binop op :: p'), s -> eval (BinopWaiting (op, 2) :: s) p'  (* Operator binarny potrzebuje 2 operandów *)
  | (PushPair :: p'), s -> eval (PairWaiting 2 :: s) p'  (* Para potrzebuje 2 elementów *)
  | (Fst :: p'), s -> eval (FstWaiting :: s) p'  (* Fst oczekuje na jedną wartość *)
  | (Snd :: p'), s -> eval (SndWaiting :: s) p' 
  | (IsPair :: p'), s -> eval (IsPairWaiting :: s) p'  
  | (CndJmp (t, e) :: p'), s -> eval (IfWaiting (t, e) :: s) p' 


(* Pomocnicza funkcja do przetwarzania wartości i wykonywania oczekujących operacji *)
and process_value (v : I.value) (s : stack_item list) (p : prog) : I.value =
  match s with
  | [] -> eval [Value v] p  (* Jeśli stos jest pusty, dodajemy wartość *)
  
  (* Pierwszy operand dla operatora binarnego, czekamy na drugi, dodajemy pierwszy na stos *)
  | BinopWaiting (op, 2) :: rest -> eval (BinopWaiting (op, 1) :: Value v :: rest) p
  | BinopWaiting (op, 1) :: Value v1 :: rest ->
      let result = I.eval_op op v1 v in process_value result rest p
  
  | PairWaiting 2 :: rest -> eval (PairWaiting 1 :: Value v :: rest) p
  | PairWaiting 1 :: Value v1 :: rest ->
      let pair = I.VPair (v1, v) in
      process_value pair rest p
  | FstWaiting :: rest ->
      (match v with
       | I.VPair (v1, _) -> process_value v1 rest p
       | _ -> failwith "fst wymaga pary")
  | SndWaiting :: rest ->
      (match v with
       | I.VPair (_, v2) -> process_value v2 rest p
       | _ -> failwith "snd wymaga pary")
  | IsPairWaiting :: rest ->
      let is_pair = match v with
        | I.VPair _ -> I.VBool true
        | _ -> I.VBool false in
        process_value is_pair rest p
  | IfWaiting (t, e) :: rest ->
      (match v with
       | I.VBool true -> eval rest (t @ p)  
       | I.VBool false -> eval rest (e @ p)  
       | _ -> failwith "warunek musi być typu bool")
  
  | Value _ :: _ -> failwith "błąd: nieoczekiwany stan programu lub stosu"

(*
open Fun.Interp;;
open Fun.Rpn;;
of_ast (parse "(3+8)+4*(2 - 1)");;
*)
 

(* ewaluator nie jest elementem procesu kompilacji, ale
 * przydaje się do testowania i debugowania
 *)
let rec eval (s : I.value list) (p : prog) : I.value =
  match p, s with
  | [], [n] -> n
  | [], _   -> failwith "error!"
  | (PushInt n :: p'), _ ->
      eval (I.VInt n :: s) p'
  | (PushBool b :: p'), _ ->
      eval (I.VBool b :: s) p'
  | (Binop op :: p'), (v2 :: v1 :: s') ->
      eval (I.eval_op op v1 v2 :: s') p'
  | (CndJmp (t,_) :: p'), (I.VBool true :: s') ->
      eval s' (t @ p')
  | (CndJmp (_,e) :: p'), (I.VBool false :: s') ->
      eval s' (e @ p')
  | (PushPair :: p'), (v2 :: v1 :: s') ->
      eval (I.VPair (v1, v2) :: s') p'
  | (Fst :: p'), (I.VPair (v1,_) :: s') ->
      eval (v1 :: s') p'
  | (Snd :: p'), (I.VPair (_,v2) :: s') ->
      eval (v2 :: s') p'
  | (PushUnit :: p'), (s') ->
      eval (I.VUnit :: s') p'

  | _ -> failwith "error!!"

(* Kompilacja RPN do podzbioru C *)

let lbl_cntr = ref 0 (* bleee!! *)

let fresh_lbl () =
  incr lbl_cntr;
  "lbl" ^ string_of_int !lbl_cntr

let emit_bop (op : Ast.bop) : string =
  Ast.(match op with
  | Add  -> "+"
  | Sub  -> "-"
  | Mult -> "*"
  | Div  -> "/"
  | And  -> "&&"
  | Or   -> "||"
  | Eq   -> "=="
  | Neq  -> "!="
  | Gt   -> ">"
  | Lt   -> "<"
  | Geq  -> ">="
  | Leq  -> "<=")

let emit_bop_res_tag (op : Ast.bop) : string =
  Ast.(match op with
  | Add | Sub | Mult | Div -> "INT"
  | _ -> "BOOL")

let emit_line (s : string) : string =
  "  " ^ s ^ ";\n"

let emit_lbl (s : string) : string =
  " " ^ s ^ ":\n"

(** allocate list of values, pop n elems from the stack*)
let alloc_pop (ss : string list) (to_pop : int) : string =
  (ss
   |> List.mapi (fun i s ->
        emit_line ("heap[heap_ptr+" ^ string_of_int i ^ "] = " ^ s))
   |> String.concat "") ^
  emit_line ("heap_ptr += " ^ string_of_int (List.length ss)) ^
  emit_line ("stack_ptr += " ^ string_of_int (1 - to_pop)) ^
  emit_line ("stack[stack_ptr] = heap_ptr - " ^ string_of_int (List.length ss - 1))

let show_cmd (c : cmd) : string =
  match c with
  | PushInt n -> emit_line ("// PushInt " ^ string_of_int n)
  | PushBool b -> emit_line ("// PushBool " ^ (if b then "true" else "false"))
  | Binop _op -> emit_line "// Binop"
  | PushPair -> emit_line "// PushPair"
  | CndJmp _ -> emit_line "// CndJmp"
  | Fst -> emit_line "// Fst"
  | Snd -> emit_line "// Snd"
  | PushUnit -> emit_line "// PushUnit"
  | IsPair -> emit_line "// IsPair"

let rec emit_cmd (c : cmd) : string =
  show_cmd c ^
  match c with
  | PushInt n ->
      alloc_pop ["INT"; string_of_int n] 0
  | PushBool n ->
      alloc_pop ["BOOL"; if n then "1" else "0"] 0
  | PushPair ->
      alloc_pop ["PAIR"; "stack[stack_ptr-1]"; "stack[stack_ptr]"] 2
  | PushUnit ->
      alloc_pop ["UNIT"] 0
  | Fst ->
      emit_line "stack[stack_ptr] = heap[stack[stack_ptr]]"
  | Snd ->
      emit_line "stack[stack_ptr] = heap[stack[stack_ptr]+1]"
  | IsPair ->
      alloc_pop ["BOOL"; "heap[stack[stack_ptr] - 1] == PAIR"] 1
  | Binop op ->
      alloc_pop
        [emit_bop_res_tag op;
         ("heap[stack[stack_ptr-1]] " ^ emit_bop op ^ " heap[stack[stack_ptr]]")] 2
  | CndJmp (t, e) ->
      let lbl_t = fresh_lbl () in
      let lbl_end = fresh_lbl () in
      emit_line ("if (heap[stack[stack_ptr]]) goto " ^ lbl_t) ^
      emit_line "stack_ptr--" ^
      emit e ^
      emit_line ("goto " ^ lbl_end) ^
      emit_lbl lbl_t ^
      emit_line "stack_ptr--" ^
      emit t ^
      emit_lbl lbl_end

and emit (p : prog) : string =
  List.fold_left (fun res cmd -> res ^ emit_cmd cmd) "" p

let compile (s : string) : string =
  s
  |> Interp.parse
  |> of_ast
  |> emit
  |> Runtime.with_runtime
