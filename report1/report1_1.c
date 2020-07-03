#include <stdio.h>
#include <stdlib.h>
#define MAX 64

int num;
int arrNum = 0;
char ch = ' ';
char arr[MAX];
typedef enum TOKEN {null, NUMBER, PLUS, STAR, LP, RP, END} T;
T token;

void get_token();
int expression();
int term();
int factor();
void error(int i);

void get_token(){
	ch = arr[arrNum];
//	printf("get token ch : %c\n", ch);
	if(ch == '+'){
		token = PLUS;
	}
	else if(ch == '*'){
		token = STAR;
	}
	else if(ch == '('){
		token = LP;
	}
	else if(ch == ')'){
		token = RP;
	}
	else if(ch == '\n'){
//		printf("token end!\n");
		token = END;
	}
	else if((ch >= '0') && (ch <= '9')){
		token = NUMBER;
		num = ch - '0';
		while((arr[arrNum+1] >= '0') && (arr[arrNum+1] <= '9'))
		{
			arrNum++;
			ch = arr[arrNum];
			num = num*10 + (ch - '0');
		}
	}
	else{
		token = null;
	}
	arrNum++;
}

int expression(){
	int result;
//	printf("expression ch : %c\n", ch);
//	printf("token is %d\n", token);
	result = term();
//	printf("plus result? %d\n", result);
	while(token==PLUS)
	{
//		printf("expression while token plus!\n");
		get_token();
		result=result+term();
	}
	return (result);
}

int term(){
	int result;
//	printf("term ch %c\n", ch);
	result=factor();
	while(token==STAR)
	{
//		printf("term while token star!\n");
		get_token();
		result=result*factor();
	}
//	printf("term result : %d\n", result);
	return (result);
}

int factor(){
	int result;
//	printf("factor ch %c\n", ch);
//	printf("factor token : %d\n", token);
	if(token == NUMBER)
	{
		result=num;
		get_token();
	}
	else if(token==LP){
		get_token();
		result=expression();
		if(token == RP)
			get_token();
		else
			error(2);
	}
	else
		error(1);

//	printf("factor result is %d\n", result);
	return (result);
}
void main(){
	int result;
	int i = 0;
	while(i<MAX){
		arr[i] = getchar();
		if(arr[i] == '\n')
			break;
		i++;
	}
	get_token();
	result=expression();
//	printf("main token is %d\n", token);
	if(token!=END){
//		printf("main EOF!!\n");
		error(3);
	}
	else
		printf("result %d \n",result);
}
void error(int i){
	switch(i)
	{
		case 1:
			printf("error : number or '(' expected\n");
			break;
		case 2:
			printf("error : ')' expected\n");
			break;
		case 3:
			printf("error : EOF expected\n");
			break;
	}
	exit(1);
}
