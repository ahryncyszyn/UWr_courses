{
open Parser
}

let white = [' ' '\t']+
let digit = ['0'-'9']
int number = '-'? digit+
let number = '-'? digit+ ( '.' digit+ )?

rule read =
    parse
    | white { read lexbuf }
    |  "log" { LOG }
    | "**" { POW }
    | "*" { TIMES }
    | "+" { PLUS }
    | "-" { MINUS }
    | "/" { DIV }
    | "(" { LPAREN }
    | ")" { RPAREN }
    | number { INT ( int_of_string (Lexing.lexeme lexbuf)) }
    | float { FLOAT ( float_of_string (Lexing.lexeme lexbuf)) }
    | eof { EOF }
