(*------------------------------- GRAMATYKA BEZKONTEKSTOWA -------------------------------
  - czworka G(N, T, P, S) 
    - N - zbior nieterminali 
    - T - zbior terminali
    - P - zbior produkcji (regul)
    - S - symbol poczatkowy gramatyki *)
(* GRAMATYKA NIEJEDNOZNACZNA - moze byc wiecej niz jedno wyprowadzenie jakiegos slowa *)
(* GRAMATYKA LINIOWA - po prawej stronie produkcji występuje co najwyżej jeden symbol nieterminalny *)
(* GRAMATYKA JEDNOSTRONNIE LINIOWA - symbol nieterminalny wystepuje zawsze jako ostatni w produkcjach 
    - np A → wB lub A → e *)

(* JEZYK L(G) - jezyk generowany przez gramatyke G nad alfabetem T *)
(* JEZYK REGULARNY - generowany przez gramatyke jedostronnie liniowa *)

(*------------------------------- INTERPRETERY -------------------------------*)
(* KOMPILATOR - tlumaczy program z wyzszego języka na nizszy *)
(* INTERPRETER - wykonuje instrukcje zapisane w wyzszym jezyku bez tłumaczenia go *)

(* ETAPY KOMPILACJI: 
  - analiza leksykalna - przetwarza kod w sekwencje tokenow 
  - analiza składniowa (parsing) - przetwarza tokeny w abstract syntax tree (AST) 
                                 - reprezentuje strukture programu 
  - analiza semantyczna - weryfikuje czy program ma sens 
                        - np czy typy sie zgadzaja 
                        - np czy sa wszystkie przypadki uwzglednione po match 
  - generowanie kodu *)

(* ETAPY INTERPRETACJI: wszystkie powyzsze tylko zamiast generowania kodu, od razu go wykonuje *)

(* SKŁADANIA KONKRETNA - rzeczywisty zapis kodu - np if (x > 0) { y = x + 1; }
   SKLADANIE ABSTRAKCYJNA - logiczna struktura programu - np drzewo ast z wezlami if, >, +, =, x, y *)

(*------------------------------- AST.ML -------------------------------*)
(* definiuje typy w AST (abstract syntax tree) *)
type bop = Add | Sub | Mult | Div

type expr = 
  | Int of int 
  | Binop of bop * expr * expr

(*------------------------------- PARSER.MLy -------------------------------*)
(* tworzy drzewo AST z sekwencji tokenow *)
(* parser generator - menhir *)
(* %token <type>identifier - deklaracje tokenow *)
%token EOF
%token PLUS
%token LPAREN
%token RPAREN
%token <int> INT 

(* deklaruje asocjacyjnosc i priorytet operatorow *)
%left PLUS MINUS
%left TIMES DIV (* deklaracja nizej = wyzszy priorytet *)

%start <ast.expr> prog (* deklaracja symbolu startowego prog oraz zwracanego typu *)
%% (* koniec sekcji deklaracji *)

prog: (* zasady / produkcje *)
  | e = expr; EOF { e } 
  | e1 = expr; PLUS; e2 = expr { Binop(Add, e1, e2) }
  | LPAREN; e = expr; RPAREN { e }
  ;

expr:
  | i = INT { Int i }
  ;

(*------------------------------- LEXER.MLL --------------------------------*)
{ open Parser } (* preluda *)
 
(* wyrazenia regularne definiujace identyfikatory *)
let white = [' ' '\t']+
let digit = ['0'-'9'] 
let int = '-'? digit+ 

(* zasady leksykalne (dopasowywania) *)
rule read = 
  parse 
  | white { read lexbuf } (* pozwala na whitespace *)
                       (* zwraca argument jako string *)
  | int { INT int_of_string(Lexing.lexeme lexbuf) }
  | eof { EOF }
  | "*" { TIMES }
  | "+" { PLUS }
  | "(" { LPAREN }
  | ")" { RPAREN }
  (* (...) *)
  | id { ID (Lexing.lexeme lexbuf) } (* wczytuje stringi wiec powinna byc na koncu! *)
  | int { INT (int_of_string (Lexing.lexeme lexbuf)) }
  | eof { EOF }

(*------------------------------- MAIN.ML -------------------------------*)
open Ast

(* parsuje stringa w AST *)
let parse (s : string) : expr = 
    Parser.prog Lexer.read (Lexing.from_string s)

(* funkcja pomocnicza do ewaluowania operatorow *)
let eval_op (op : bop) (v1 : float) (v2 : float) : float =
    match op with
    | Add -> v1 +. v2
    | Sub -> v1 -. v2
    | Mult -> v1 *. v2
    | Div -> v1 /. v2
    | Pow -> v1 ** v2

(* rekursywnie ewaluuje ast az dotrze do koncowej wartosci *)
let rec eval (e : expr) : float =
    match e with
    | Float f -> f
    | Binop (op, e1, e2) -> eval_op op (eval e1) (eval e2)
    | Log e -> log (eval e)

(* interpretuje s poprzez wywolanie powyzszych funkcji *)
let interp (s : string) : float = 
    eval (parse s)

