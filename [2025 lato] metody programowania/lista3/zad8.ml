

let rec insert_bst x t =
  match t with
  | Leaf -> Node (Leaf, x, Leaf)
  | Node (l, v, r) ->
      if v < x then Node (l, v, insert_bst x r)
      else Node (insert_bst x l, v, r);; 