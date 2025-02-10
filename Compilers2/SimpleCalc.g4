grammar SimpleCalc;

/* Grammar Rules */
compileUnit : (expr ';')+ ;

expr : NUMBER                #NUMBER
     | IDENTIFIER            #IDENTIFIER
     | expr op=(MULT|'/') expr  #MultDiv
     | expr op=(ADD|'-') expr   #AddSub
     | LP expr ')'           #Parenthesis
     | IDENTIFIER '=' expr   #Assignment
     ;
     
/* Lexer Rules */
LP : '(';
RP : ')';
ADD : '+';
SUB : '-';
MULT : '*';
DIV : '/';
ASSIGN : '=';
SEMI : ';' ;
NUMBER : '0'|[1-9][0-9]*;
IDENTIFIER : [a-zA-Z][a-zA-Z0-9_]*;

WS : [ \n\r\t]+ ->skip; // whitespaces 