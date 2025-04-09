
(* zaimplementuj kopce lewicowe *)
(* kopiec - drzewo binarne które implementuje kolejkę priorytetową
   ze znajdowaniem min elementu w O(1) i pozostałymi operacjami w O(log(N)) *)
(* każdy kopiec ma rangę, czyli długość prawego poddrzewa + 1 *)
(* lewicowy - kopiec którego ranga lewego poddrzewa jest nie mniejsza niż ranga prawego *)

module LeftistHeap = struct type ('a, 'b) heap =
  | HLeaf
  | HNode of int * ('a, 'b) heap * 'a * 'b * ('a, 'b) heap

  let rank = function HLeaf -> 0 | HNode (n, _, _, _, _) -> n

  let heap_ordered p = function
  | HLeaf -> true
  | HNode (_, _, p', _, _) -> p <= p'

  let rec is_valid = function | HLeaf -> true
  | HNode (n, l, p, v, r) ->
    rank r <= rank l
    && rank r + 1 = n 
    && heap_ordered p l 
    && heap_ordered p r 
    && is_valid l
    && is_valid r

  let make_node p v l r =
    let r1 = rank l in
    let r2 = rank r in
    if r1 < r2 then Hnode(r1 + 1, r, p, v, l)
    else Hnode(r2 + 1, l, p, v, l)

  let heap_merge h1 h2 =
    match (h1, h2) with
    | Hleaf, h -> h
    | h, Hleaf -> h
    | Hnode(rank1, l1, p1, v1, r1), Hnode(rank2, l2, p2, v2, r2) ->
      let e, p, hl, hr, h_weak =
        if p1 < p2 then (v1, p1, l1, r1, h2)
        else (v2, p2, l2, r2, h1)
        in let merged = heap merge hr h_weak in 
        make_node p e hl merged

end