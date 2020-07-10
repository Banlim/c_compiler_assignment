digit	[0-9]
%{
#include "y.tab.h"
//enum {PLUS, STAR, LP, RP, number}
extern int yylval;
%}

%%
"\n" 		{ return(0); }
"+"		{ return(PLUS); }
"*"		{ return(STAR); }
"("		{ return(LP); }
")"		{ return(RP); }
{digit}+	{ yylval=atoi(yytext); return(number);}
%%

yywrap()
{
	return(0);
}
