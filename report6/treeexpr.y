%{
#define YYSTYPE_IS_DECLARED 1
	typedef long YYSTYPE;
	typedef enum e {N_NULL, N_INT, N_PLUS, N_STAR} NODE_NAME;
	typedef struct s {NODE_NAME name; struct s *link, *rlink; int value; } A_NODE;
	A_NODE *makeNode(), *root;
#include "y.tab.h"
%}
%start S
%token number PLUS STAR LP RP

%%
S : E		{ root=$1; }
  ;
E : E PLUS T	{ $$ = makeNode(N_PLUS, $1, 0, $3); }
  | T		{ $$ = $1; }
  ;
T : T STAR F	{ $$ = makeNode(N_STAR, $1, 0, $3); }
  | F		{ $$ = $1; }
  ;
F : LP E RP	{ $$ = $2; }
  | number	{ $$ = makeNode(N_INT, 0, $1, 0); }
  ;
%%
extern char *yytext;

yyerror(char *s)
{
	printf("Syntax Error\n");
	exit(1);
}
void printTree(A_NODE *p){
	//tree print
	switch(p->name){
		case N_NULL:
			printf("NULL\n");
			break;
		case N_INT:
			printf("%d", p->value);
			break;
		case N_PLUS:
			printf("+ ");
			break;
		case N_STAR:
			printf("* ");
			break;
	}
	printf("\n");
	if(p->link != 0){
		printf("    ");
		printf("left : ");
		printTree(p->link);
	}
	else{
		printf("	No Node    ");
	}
	if(p->rlink != 0){
		printf("    ");
		printf("right : ");
		printTree(p->rlink);
	}
	else{
		printf("No Node\n");
		return;
	}
}

A_NODE *makeNode(NODE_NAME n, A_NODE *a, int b, A_NODE *c)
{
	A_NODE *p;
	p = malloc(sizeof(A_NODE));
	p->name = n;
	p->link=a;
	p->value=b;
	p->rlink=c;
	return(p);
}
void main(){
	yyparse();
	printTree(root);
}


