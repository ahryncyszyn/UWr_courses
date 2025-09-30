(*------------------------------- MODUŁY -------------------------------*)
(* zbior definicji, moze zawierac nowe typy itp *)
(* przydatne do definiowania struktur danych *)
(* nazwa modułu musi się zaczynac duzą literą *)
module MyModule = struct
  let inc x = x + 1
  type primary_color = Red | Green | Blue
  exception Oops
end

(* KOLEJKA PRIORYTETOWA *)
(* sygnatura (typ modułu) to jak kontrakt: *)
(* kazdy moduł ktory chce byc tego typu musi zaimplementowac te funkcje *)
(* sig - sygnatura *)
module type QUEUE = sig
  type 'a queue
  val empty : 'a queue
  val push : 'a -> 'a queue -> 'a queue
  val peek : 'a queue -> 'a
  val pop : 'a queue -> 'a queue
end

(* implementacja modułu *)
(* ": QUEUE" to adnotacja typu *)
module Queue : QUEUE = struct
  type 'a queue = Queue of 'a list * 'a list;;

  let empty = Queue ([], [])

  let mk_queue xs ys =
    match xs with
    | [] -> Queue (List.rev ys, [])
    | _ -> Queue (xs, ys)

  (* uzywa jednej listy na front a drugiej na rear *)
  let push x (Queue (xs, ys)) = mk_queue xs (x :: ys)

  let peek (Queue (xs, ys)) =
    match xs with
    | [] -> failwith "peek on empty queue"
    | x :: _ -> x

  let pop (Queue (xs, ys)) =
    match xs with
    | [] -> failwith "pop on empty queue"
    | _ :: xs' -> mk_queue xs' ys
end

(* STOS *)
module Stack : QUEUE = struct
  type 'a queue = 'a list

  let empty = []

  let push x st = x :: st

  let peek st =
    match st with
    | [] -> failwith "peek on empty stack"
    | x :: _ -> x

  let pop st =
    match st with
    | [] -> failwith "peek on empty stack"
    | _ :: st' -> st'
end

(*------------------------------- FUNKTORY -------------------------------*)
(* funkcje z modułu w moduł *)
module type X = sig
  val x : int
end

(* IncX to funktor, tworzy nowy moduł na podstawie modułu X *)
(* module IncX : functor (M : X) -> sig val x : int end *)
module IncX (M : X) = struct
  let x = M.x + 1
end

(* skoro funktory to funkcje to mozemy je aplikowac *)
module A = struct let x = 0 end;; (* A.x = 0 *)
module B = IncX (A);;             (* B.x = 1 *)

module AddX (M : X) = struct
  let add y = M.x + y
end

(* mozemy zaaplikowac "anonimowy" moduł *)
module Add42 = AddX (struct let x = 42 end) (* Add42.add 1 = 43 *)

(*------------------------------- BFS I DFS NA DRZEWACH -------------------------------*)
type 'a tree = 
  | Leaf 
  | Node of 'a tree * 'a * 'a tree;;

let bfs t =
  let rec f q xs =
    if q = Queue.empty
    then List.rev xs
    else match Queue.peek q with
    | Leaf -> f (Queue.pop q) xs
    | Node (l, v, r) -> f (q |> Queue.pop |> Queue.push l |> Queue.push r) (v :: xs)
  in f (Queue.push t Queue.empty) []

let dfs t =
  let rec f q xs =
    if q = Stack.empty
    then List.rev xs
    else match Stack.peek q with
    | Leaf -> f (Stack.pop q) xs
    | Node (l, v, r) -> f (q |> Stack.pop |> Stack.push l |> Stack.push r) (v :: xs)
  in f (Stack.push t Stack.empty) []

let ex_tree = Node (Node (Node (Leaf, 4, Leaf), 2, Leaf), 1, 
  Node (Node (Leaf, 5, Leaf), 3, Node (Node (Leaf, 7, Leaf), 6, Leaf)))


module Search (M : QUEUE) = struct
  let search t =
  let rec f q xs =
    if q = M.empty
    then List.rev xs
    else match M.peek q with
    | Leaf -> f (M.pop q) xs
    | Node (l, v, r) -> f (q |> M.pop |> M.push l |> M.push r) (v :: xs)
  in f (M.push t M.empty) []
end
  
module Bfs = Search (Queue)
module Dfs = Search (Stack)
  
let search (module M : QUEUE) t =
  let rec f q xs =
    if q = M.empty
    then List.rev xs
    else match M.peek q with
    | Leaf -> f (M.pop q) xs
    | Node (l, v, r) -> f (q |> M.pop |> M.push l |> M.push r) (v :: xs)
  in f (M.push t M.empty) []
  
let bfs t = search (module Queue) t
let dfs t = search (module Stack) t

(*------------------------------- DEKODOWANIE HUFFMANNA -------------------------------*)
module type PRIO_QUEUE = sig
  type ('a, 'b) pq
  val empty : ('a, 'b) pq
  val insert : 'a -> 'b -> ('a, 'b) pq -> ('a, 'b) pq
  val pop : ('a, 'b) pq -> ('a, 'b) pq
  val min : ('a, 'b) pq -> 'b
  val min_prio : ('a, 'b) pq -> 'a
end

module ListPrioQueue : PRIO_QUEUE = struct
  type ('a, 'b) pq = ('a * 'b) list
  let empty = []
  let pop q = List.tl q
  let rec insert a x q =
    match q with
    | [] -> [(a, x)]
    | (b, y) :: q' -> if a < b then (a, x) :: q else (b, y) :: insert a x q'
  let min q = List.hd q |> snd
  let min_prio q = List.hd q |> fst
end

type 'a code_tree = 
  | CTNode of 'a code_tree * 'a code_tree 
  | CTLeaf of 'a

let make_code_tree xs =
  let rec it q = (
    let t1 = ListPrioQueue.min q
    and p1 = ListPrioQueue.min_prio q
    and q' = ListPrioQueue.pop q
    in if q' = ListPrioQueue.empty
    then t1
    else 
      let t2 = ListPrioQueue.min q'
      and p2 = ListPrioQueue.min_prio q'
      and q'' = ListPrioQueue.pop q'
      in it (ListPrioQueue.insert (p1 + p2) (CTNode (t1, t2)) q''))
  in let initial_pq =
    List.fold_left (fun q (p, v) -> ListPrioQueue.insert p (CTLeaf v) q) ListPrioQueue.empty xs
  in it initial_pq

  let decode bs t =
    let rec walk bs cur_t =
      match cur_t, bs with
      | CTLeaf v, _ -> v :: start bs
      | CTNode (l, r), 0 :: bs' -> walk bs' l
      | CTNode (l, r), 1 :: bs' -> walk bs' r
      | _, _ :: _ -> failwith "invalid bit"
      | _, [] -> failwith "incomplete code"
    and start bs =
      if bs = []
      then []
      else walk bs t
    in start bs