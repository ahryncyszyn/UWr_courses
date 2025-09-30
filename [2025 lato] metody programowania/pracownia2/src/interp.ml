(* ********************* *)
(* UWAGA! *)
(* Sam interpreter i resztę pliku (z wyjątkiem typu value) można dowolnie modyfikować. *)
(* Liczy się to, zeby funkcja eval_spreadsheet zwracała poprawną wartość! *)
(* ********************* *)

open Ast

let parse (s : string) : expr =
  Parser.main Lexer.read (Lexing.from_string s)

module M = Map.Make(String)

type env = value M.t

and value =
  | VInt of int
  | VBool of bool
  | VUnit
  | VPair of value * value
  | VClosure of ident * expr * env
  | VRecClosure of ident * ident * expr * env

let rec show_value v =
  match v with
  | VInt n -> string_of_int n
  | VBool v -> string_of_bool v
  | VUnit -> "()"
  | VPair (v1,v2) -> "(" ^ show_value v1 ^ ", " ^ show_value v2 ^ ")"
  | VClosure _ | VRecClosure _ -> "<fun>"

let eval_op (op : bop) (val1 : value) (val2 : value) : value =
  match op, val1, val2 with
  | Add,  VInt  v1, VInt  v2 -> VInt  (v1 + v2)
  | Sub,  VInt  v1, VInt  v2 -> VInt  (v1 - v2)
  | Mult, VInt  v1, VInt  v2 -> VInt  (v1 * v2)
  | Div,  VInt  v1, VInt  v2 -> VInt  (v1 / v2)
  | And,  VBool v1, VBool v2 -> VBool (v1 && v2)
  | Or,   VBool v1, VBool v2 -> VBool (v1 || v2)
  | Leq,  VInt  v1, VInt  v2 -> VBool (v1 <= v2)
  | Lt,   VInt  v1, VInt  v2 -> VBool (v1 < v2)
  | Gt,   VInt  v1, VInt  v2 -> VBool (v1 > v2)
  | Geq,  VInt  v1, VInt  v2 -> VBool (v1 >= v2)
  | Neq,  _,        _        -> VBool (val1 <> val2)
  | Eq,   _,        _        -> VBool (val1 = val2)
  | _,    _,        _        -> failwith "type error"

(* wyjatki *)
exception CircularDependency
exception OutOfBounds

(* inicjalizuje globalne tablice z informacjami o arkuszu kalkulacyjnym *)
let visited : bool array array ref = ref [||]
let sheet_expr : expr array array ref = ref [||]
let sheet_val : value option array array ref = ref [||]

(* sprawdza czy dana komorka arkusza istnieje *)
let within_bounds i j =
  let rows = Array.length (!sheet_expr) in
  let cols = Array.length (!sheet_expr).(0) in
  i >= 0 && j >= 0 && i < rows && j < cols

let rec eval_env (env : env) (e : expr) : value =
  match e with
  | Int i -> VInt i
  | Bool b -> VBool b
  | Binop (op, e1, e2) ->
      eval_op op (eval_env env e1) (eval_env env e2)
  | If (b, t, e) ->
      (match eval_env env b with
        | VBool true -> eval_env env t
        | VBool false -> eval_env env e
        | _ -> failwith "type error")
  | Var x ->
     (match M.find_opt x env with
       | Some v -> v
       | None -> failwith "unknown var")
  | Let (x, e1, e2) ->
      eval_env (M.add x (eval_env env e1) env) e2
  | Pair (e1, e2) -> VPair (eval_env env e1, eval_env env e2)
  | Unit -> VUnit
  | Fst e ->
      (match eval_env env e with
        | VPair (v1, _) -> v1
        | _ -> failwith "Type error")
  | Snd e ->
      (match eval_env env e with
        | VPair (_, v2) -> v2
        | _ -> failwith "Type error")
  | Match (_e1, _x, _y, _e2) ->
      failwith "Not implemented"
  | IsPair e ->
      (match eval_env env e with
        | VPair _ -> VBool true
        | _ -> VBool false)
  | Fun (x, e) -> VClosure (x, e, env)
  | Funrec (f, x, e) -> VRecClosure (f, x, e, env)
  | App (e1, e2) ->
      let v1 = eval_env env e1 in
      let v2 = eval_env env e2 in
      (match v1 with
        | VClosure (x, body, clo_env) ->
            eval_env (M.add x v2 clo_env) body
        | VRecClosure (f, x, body, clo_env) as c ->
            eval_env (clo_env |> M.add x v2 |> M.add f c) body
        | _ -> failwith "not a function")
  | Cell (_row, _col) ->
      if not (within_bounds _row _col) then raise OutOfBounds;
      if (!visited).(_row).(_col) then raise CircularDependency;
      (!visited).(_row).(_col) <- true;
      (match (!sheet_val).(_row).(_col) with
      | Some v -> 
          (!visited).(_row).(_col) <- false;
          v
      | None ->
          let expr = (!sheet_expr).(_row).(_col) in
          let v = eval_env env expr in
          (!sheet_val).(_row).(_col) <- Some v;
          (!visited).(_row).(_col) <- false;
          v)

(* przetwarza komorke po komorce w rzecie arkusza *)
let rec eval_cells (cells : expr list) (env : env) : value list option =
  match cells with
  | [] -> Some []
  | expr :: rest ->
      match eval_env env expr, eval_cells rest env with
      | v, Some vs -> Some (v :: vs)
      | _, _ -> None

(* przetwarza rzad po rzedzie w arkuszu *)
let rec eval_rows (rows : expr list list) (env : env) : value list list option =
  match rows with
  | [] -> Some []
  | row :: rest ->
      match eval_cells row env, eval_rows rest env with
      | Some row_vals, Some rest_vals -> Some (row_vals :: rest_vals)
      | _ -> None

(* inicjalizuje tablice pomocnicze wartosciami i wywoluje przetwarzanie arkusza *)
let eval_spreadsheet (s : expr list list) : value list list option =
  let rows = List.length s in
  let cols = List.length (List.nth s 0) in 
  let sheet_expr_init = Array.of_list (List.map Array.of_list s) in 
  let sheet_val_init = Array.make_matrix rows cols None in
  let visited_init = Array.make_matrix rows cols false in
    sheet_expr := sheet_expr_init;
    sheet_val := sheet_val_init;
    visited := visited_init;
  try eval_rows s M.empty
  with CircularDependency | OutOfBounds -> None


let parse_and_eval_spreadsheet (s : string list list) : string list list option =
  let es = List.map (List.map parse) s in
  let vs = eval_spreadsheet es in
  Option.map (List.map (List.map show_value)) vs