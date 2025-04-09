
type 'a tree = Leaf | Node of 'a tree * 'a * 'a tree;;
let ex_tree = Node (Node (Leaf, 1, Leaf), 2, Node (Leaf, 3, Leaf));;

let rec fold_tree f a t =
  match t with
  | Leaf -> a
  | Node (l, v, r) -> f (fold_tree f a l) v (fold_tree f a r);;

(* tree_product t – iloczyn wszystkich wartości występujących w drzewie *)
let tree_product t = fold_tree (fun vl v vr -> vl * v * vr) 1 t;;

(* tree_flip t – odwrócenie kolejności: zamiana lewego i prawego poddrzewa wszystkich węzłów w drzewie *)
let tree_flip t = fold_tree (fun vl v vr -> Node(vr, v, vl)) Leaf t;;

(* tree_height t – wysokosć drzewa *)
let tree_height t = fold_tree (fun vl v vr -> 1 + max vl vr) 0 t;;

(* tree_span t – para złożona z wartości skrajnie prawego i skrajnie lewego węzła w drzewie *)
let tree_span t = 
  fold_tree (fun vl v vr -> 
    let min_val = match vl with
    | None -> v
    | Some (min, _) -> min
  in
    let max_val = match vr with
    | None -> v
    | Some (_, max) -> max
  in Some(min_val, max_val)
  ) None t;;

(* flatten t – lista wszystkich elementów występujących w drzewie, w kolejności infiksowej *)
let flatten t = fold_tree (fun vl v vr -> vl @ [v] @ vr) [] t;;