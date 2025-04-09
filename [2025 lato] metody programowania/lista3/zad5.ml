
type 'a tree = Leaf | Node of 'a tree * 'a * 'a tree;;

let t = Node ( Node ( Leaf, 2, Leaf ), 
  5 ,
  ( Node ( Node ( Leaf, 6, Leaf ) ) ,
  8 ,
  ( Node ( Leaf, 9, Leaf ) ) ) );;

(* jak jest reprezentowane t w pamieci? *)
- wskazniki na typy Node
- zakonczone typami Leaf

(* insert_bst wstawiającą element do drzewa BST *)
let rec insert_bst x t =
  match t with
  | Leaf -> Node (Leaf, x, Leaf)
  | Node (l, v, r) ->
      if x = v then t
      else if v < x then Node (l, v, insert_bst x r)
      else Node (insert_bst x l, v, r);; 

(* jak będzie wyglądał stan pamięci po wykonaniu wstawienia BST wartości 7? *)
    5
  /   \
2      8
      / \
     6   9
      \
       7

(* które fragmenty drzewa t są współdzielone między drzewem t i insert_bst 7 t? *)
- wszystko poza 7 