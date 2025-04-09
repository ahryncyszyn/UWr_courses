(* zad 9 - funkcja delete zwracajaca drzewo z usunietym danym kluczem *)

type 'a tree = Leaf | Node of 'a tree * 'a * 'a tree;;
let ex_tree = Node (Node (Leaf, 1, Leaf), 2, Node (Leaf, 3, Leaf));;

(* znajduje najmniejszy element w drzewie *)
let rec min_value t =
  match t with
  | Leaf -> failwith "Drzewo jest puste"
  | Node (Leaf, v, _) -> v
  | Node (left, _, _) -> min_value left;;

(* usuwa dany klucz z drzewa BST *)
let rec delete key t =
  match t with
  | Leaf -> Leaf  (* klucz nie istnieje *)
  | Node (left, value, right) ->
      if key < value then Node (delete key left, value, right)
      else if key > value then Node (left, value, delete key right)
      else match left, right with
        | Leaf, _ -> right
        | _, Leaf -> left
        | _ ->
            let successor = min_value right in
            Node (left, successor, delete successor right)
