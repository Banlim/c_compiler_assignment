#include <stdio.h>
#include <stdlib.h>
extern FILE *yyin;

void main(int argc, char *argv[])
{
	if(argc<2)
	{
		printf("source file not given\n");
		exit(1);
	}
	if((yyin=fopen(argv[argc-1], "r"))==NULL)
	{
		printf("can not open input file: %s\n", argv[argc-1]);
		exit(1);
	}
	printf("\nstart syntax analysis\n");
	yyparse();
	exit(0);
}
