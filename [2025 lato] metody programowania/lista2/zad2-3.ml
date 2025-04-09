
(* zad2 - reprezentacja macierzy 2x2 poprzez czteroelementowe krotki *)
(* (a, b, c, d) = | a | b |
                  | c | d |  *)

(* iloczyn dwoch macierzy *)
let matrix_mult (a1, b1, c1, d1) (a2, b2, c2, d2) = 
  (a1 * a2 + b1 * c2, a1 * b2 + b1 * d2, 
   c1 * a2 + d1 * c2, c1 * b2 + d1 * d2);;

(* macierz identycznosciowa *)
let matrix_id = (1, 0, 0, 1);;

(* podnoszenie macierzy m do k-tej potegi *)
let rec matrix_expt m k =
  if k < 0 then failwith "tylko liczby naturalne dozwolone" else
  match k with
  | 0 -> matrix_id
  | 1 -> m
  | _ -> matrix_mult (m) (matrix_expt m (k-1));;

(* obliczanie k-tej liczby fibonacciego *)
let rec fib_matrix k = 
  let m = (1, 1, 1, 0) in
  let _, fk, _, _ = matrix_expt m k in
  fk;;


(* zad 3 - uzyc algorytm szybkiego potegowania *)
let rec matrix_expt_fast m k =
  if k < 0 then failwith "tylko liczby naturalne dozwolone"
  else if k = 0 then matrix_id 
  else if k mod 2 = 0 then
    let half = matrix_expt_fast m (k / 2) in
    matrix_mult half half
  else matrix_mult m (matrix_expt_fast m (k - 1))

let rec matrix_expt_fast m k =
  if k < 0 then failwith "tylko liczby naturalne dozwolone" else
  match k with
  | 0 -> matrix_id
  | 1 -> m
  | _ -> 
        let half = matrix_expt m (k/2) in
        let half_sqrd = matrix_mult half half in
        match (k mod 2) with
        | 0 -> half_sqrd
        | _ -> matrix_mult m half_sqrd;;

let rec fib_fast k = 
  let m = (1, 1, 1, 0) in
  let _, fk, _, _ = matrix_expt_fast m k in
  fk;;
      
