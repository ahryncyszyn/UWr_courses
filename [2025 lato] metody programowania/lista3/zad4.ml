
(* zad 4 - reprezentowanie zbiorow uzywajac predykatow charakterystycznych *)
(* funkcje 'a -> bool zwracajacy true tylko gdy x nalezy do zbioru *)

(* empty_set – reprezentacja zbioru pustego *)
let empty_set x = false;;

(* singleton a – zwraca zbiór zawierający wyłącznie element a *)
let singleton a x = (a = x);;
let singleton a = (fun x -> a = x);;

(* in_set a s – zwraca true gdy a należy do zbioru s, w przeciwnym wypadku wynikiem jest false *)
let in_set a s = s a;;

(* union s t – zwraca sumę zbiorów s i t *) 
let union s t = fun x -> (s x) || (t x)§;;

(* intersect s t – zwraca przecięcie zbiorów s i t *)
let intersect s t = fun x -> (s x) && (t x);;