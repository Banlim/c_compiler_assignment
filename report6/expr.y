%{
#include "y.tab.h"
%}
%start S
%token number PLUS STAR LP RP

%%
S : E		{ printf("answer : %d\n",$1); }
  ;
E : E PLUS T	{ $$ = $1 + $3; }
  | T		{ $$ = $1; }
  ;
T : T STAR F	{ $$ = $1 * $3; }
  | F		{ $$ = $1; }
  ;
F : LP E RP	{ $$ = $2; }
  | number	{ $$ = $1; }
  ;
%%
extern char *yytext;
//yylex() {
	// '+' : return(PLUS);
	// '*' : return(STAR);
	// '(' : return(LP);
	// ')' : return(RP);
	// 정수 : yylval=정수값; return(number);
//}
yyerror(char *s)
{
	printf("Error\n");
	exit(1);
}
void main(){
	yyparse();
}

