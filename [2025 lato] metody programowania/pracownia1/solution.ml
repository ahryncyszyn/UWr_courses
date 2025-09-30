
let alpha_num = 3;;
let alpha_denom = 4;;
let alpha = float_of_int alpha_num /. float_of_int alpha_denom;;

type 'a tree = Leaf | Node of 'a tree * 'a * 'a tree
type 'a sgtree = { tree : 'a tree; size : int; max_size: int }

let alpha_height (n : int) : int =
  let alpha_inv = float_of_int alpha_denom/. float_of_int alpha_num 
  in int_of_float (floor (log (float_of_int n) /. log (alpha_inv)))

let rec to_list (t : 'a tree) (acc : 'a list) : 'a list =
  match t with
  | Leaf -> acc
  | Node (l, v, r) -> to_list l (v :: to_list r acc)

let rebuild_balanced (t : 'a tree) : 'a tree =
  let elements = to_list t []
  in let elements = Array.of_list elements
  in let rec build min max =
    if min > max then Leaf
    else let mid = (min + max + 1) / 2
    in let v = elements.(mid) in
      Node (build min (mid - 1), v, build (mid + 1) max)
  in build 0 (Array.length elements - 1)

let empty : 'a sgtree = 
  {tree = Leaf; size = 0; max_size = 0}

let find (x : 'a) (sgt : 'a sgtree) : bool =
  let rec find_bst x tree =
    match tree with
    | Leaf -> false
    | Node(l, v, r) ->
      if x = v then true
      else if x < v then find_bst x l
      else find_bst x r
    in find_bst x sgt.tree

(* zwraca licze wierzcholkow w calym drzewie *)
let rec size (tree : 'a tree) : int = 
  match tree with 
  | Leaf -> 0
  | Node(l, _, r) -> 1 + size l + size r

(* zwraca wartosc w korzeniu *)
let get_root_value (t : 'a tree) : 'a = 
  match t with
  | Leaf -> failwith "no root"
  | Node(_, v, _) -> v

(* zwraca potencjalnie niezbalansowane drzewo z wstawionym elementem x,
 odleglosc x do korzenia i liste poddrzew ktore zostaly odwiedzone po drodze *)
let rec insert_hlp (x : 'a) (sgt : 'a sgtree) (depth : int) (path : 'a tree list)
                  : 'a sgtree * int option * 'a tree list =
  match sgt.tree with
  | Leaf -> 
    { tree = Node(Leaf, x, Leaf); 
      size = sgt.size + 1; 
      max_size = max sgt.max_size (sgt.size + 1)}, 
      Some depth, (Node(Leaf, x, Leaf) :: path)

  | Node(l, v, r) -> 
      if x = v then failwith "element juz istnieje w drzewie"
      else if (x < v) then 
        let left_subtree = {tree = l; size = 0; max_size = 0}
        in let (new_left_subtree, new_dist, new_path) 
                = insert_hlp x left_subtree (depth + 1) path
        in { tree = Node(new_left_subtree.tree, v, r);
            size = sgt.size + 1; 
            max_size = max sgt.max_size (sgt.size + 1)}, 
            new_dist, (Node(new_left_subtree.tree, v, r) :: new_path)
      else 
        let right_subtree = {tree = r; size = 0; max_size = 0}
        in let (new_right_subtree, new_dist, new_path) 
              = insert_hlp x right_subtree (depth + 1) path
        in { tree = Node(l, v, new_right_subtree.tree);
            size = sgt.size + 1;
            max_size = max sgt.max_size (sgt.size + 1)}, 
            new_dist, (Node(l, v, new_right_subtree.tree) :: new_path)

(* zwraca kozła ofiarnego i jego cale poddrzewo *)
let rec find_scapegoat (path : 'a tree list) : 'a tree option =
  match path with
  | [] -> None
  | Leaf :: rest -> None
  | Node(l, v, r) :: rest ->
      let left_size = size l
      in let right_size = size r
      in let subtree_size = left_size + right_size + 1
      in if float_of_int left_size > alpha *. float_of_int subtree_size
            || float_of_int right_size > alpha *. float_of_int subtree_size 
        then Some (Node(l, v, r))
        else find_scapegoat rest

(* zwraca drzewo z poddrzewem zaczynajacym sie od wierzcholka target_val zamienionym na replacement poddrzewo*)
let rec replace_subtree (target_val : 'a) (replacement : 'a tree) (original_tree : 'a tree) : 'a tree =
  match original_tree with
    | Leaf -> Leaf
    | Node(l, v, r) ->
        if v = target_val then replacement
        else if (v > target_val) then Node(replace_subtree target_val replacement l, v, r)
        else Node(l, v, replace_subtree target_val replacement r)

let insert (x : 'a) (sgt : 'a sgtree) : 'a sgtree =
    let (new_sgt, depth, path) = insert_hlp x sgt 0 []
    in let h_alfa = alpha_height new_sgt.size
    in match depth with
    | None -> sgt
    | Some depth -> 
      if (depth <= h_alfa) then new_sgt
      else 
        let scapegoat = find_scapegoat (List.rev path)
        in match scapegoat with
        | None | Some Leaf -> failwith "nie znaleziono kozla ofiarnegoo"
        | Some scapegoat -> 
          let rebuilt = rebuild_balanced scapegoat
              in let new_tree = replace_subtree (get_root_value scapegoat) rebuilt new_sgt.tree 
              in { tree = new_tree; size = new_sgt.size; max_size = new_sgt.max_size }
              
(* znajduje najmniejszy element w drzewie *)
let rec min_value (t : 'a tree) : 'a =
  match t with
  | Leaf -> failwith "drzewo jest puste"
  | Node (Leaf, v, _) -> v
  | Node (left, _, _) -> min_value left

(* zwraca drzewo bst bez wierzcholka o wartosci key *)
let rec bst_remove (key : 'a) (t : 'a tree) : 'a tree =
  match t with
  | Leaf -> Leaf
  | Node (left, value, right) ->
      if key < value then Node (bst_remove key left, value, right)
      else if key > value then Node (left, value, bst_remove key right)
      else match left, right with
        | Leaf, _ -> right
        | _, Leaf -> left
        | _ ->
            let successor = min_value right in
            Node (left, successor, bst_remove successor right)

let remove (x : 'a) (sgt : 'a sgtree) : 'a sgtree =
  let new_tree = bst_remove x sgt.tree 
  in let new_size = sgt.size - 1
  in if (float_of_int new_size < alpha *. float_of_int sgt.max_size)
    then let balanced = rebuild_balanced new_tree
      in {tree = balanced; size = new_size; max_size = new_size}
  else {tree = new_tree; size = new_size; max_size = sgt.max_size}