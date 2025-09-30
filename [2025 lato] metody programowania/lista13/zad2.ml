(* Zdefiniuj predykat (relację unarną) mówiący, że lista jest posortowana niemalejąco. *)

let rec niemalejaco lst =
  match lst with
  | [] -> true
  | [_] -> true
  | x :: y :: rest -> x <= y && niemalejaco (y :: rest);;

niemalejaco [1; 2; 2; 4];;
niemalejaco [3; 2; 5];;
