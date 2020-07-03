#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 64

int num;
int arrNum = 0;
int isFloat = 0;
int floatPoint = 0;
int triggerMix = 0;
float floatNum = 0.0;
char ch = ' ';
char arr[MAX];
typedef enum TOKEN {null, NUMBER, PLUS, STAR, LP, RP, END} To;
typedef enum TYPE {INTTYPE, FLOATTYPE} Ty;
typedef union UNITYPE { int i; float f;} Uni;
typedef struct {
	Ty type;
	Uni value;
}st;
To token;
void get_token();
st* expression();
st* term();
st* factor();
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
		isFloat = 0;
		floatNum = 0.0;
		floatPoint = 0;
		token = NUMBER;
		num = ch - '0';
		while(((arr[arrNum+1] >= '0') && (arr[arrNum+1] <= '9')) || arr[arrNum+1] == '.')
		{
//			printf("arrNum is %d\n", arrNum);
			if(arr[arrNum+1] == '.'){
				isFloat = 1;
				floatNum = num;
				arrNum++;
				continue;
			}
			if(isFloat == 1){
				arrNum++;
				ch = arr[arrNum];
				floatPoint++;
				//printf("ch is %c\n", ch);
				//printf("ch - o %d\n", ch - '0');
//				printf("floatNum prev is %f\n", floatNum);
				//printf("ch - 0 is %f\n", 0.1*(ch-'0'));
				floatNum = floatNum + (ch-'0')*pow(0.1,floatPoint);
//				printf("floatNum is %f\n", floatNum);
			}
			else{
				arrNum++;
				ch = arr[arrNum];
				num = num*10 + (ch - '0');
			}
		}
	}
	else{
		token = null;
	}
	arrNum++;
}

st* expression(){
	st* result;
//	printf("expression ch : %c\n", ch);
//	printf("token is %d\n", token);
	result = term();
//	printf("plus result? %d\n", result->type);
	while(token==PLUS)
	{
	//	printf("triggerMix %d\n", triggerMix);
	//	printf("expression while token plus!\n");
		if((result->type == FLOATTYPE) && (triggerMix == 0)){
			triggerMix = 1;
		}
		get_token();
		st* temp = term();
		if(temp->type == INTTYPE){
	//		printf("expr int value is %d\n", temp->value.i);
			if(triggerMix>0){
	//			printf("expr prev float type\n");
				triggerMix = 2;
				temp->type = FLOATTYPE;
				temp->value.f = temp->value.i;
			}
			else{
				result->value.i = result->value.i + temp->value.i;
			}
		}
		if(temp->type == FLOATTYPE){
	//		printf("expr float value is %f\n", temp->value.f);
			if((triggerMix==0) || (result->type == INTTYPE)){
	//			printf("expr floattype!\n");
				triggerMix = 2;
				result->value.f = result->value.i;
			}
	//		result->value.f = result->value.i;
			result->value.f = result->value.f + temp->value.f;
	//		printf("expression result value : %f\n", result->value.f);
		}
		free(temp);
	}
	return (result);
}

st* term(){
	st* result;
//	printf("term ch %c\n", ch);
	result=factor();
	while(token==STAR)
	{
//		printf("term while token star!\n");
		if((result->type == FLOATTYPE) && (triggerMix == 0))
			triggerMix = 1;

		get_token();
		st* temp = factor();
		if(temp->type == INTTYPE){
			if(triggerMix > 0){
//				printf("term inttype prev floattype\n");
				triggerMix = 2;
				temp->type = FLOATTYPE;
//				printf("term result int value %f\n", result->value.f);
				temp->value.f = temp->value.i;
			}
			else{
				result->value.i = result->value.i * temp->value.i;
			}
		}
		if(temp->type == FLOATTYPE){
			if((triggerMix == 0) || (result->type == INTTYPE)){
				result->value.f = result->value.i;
				triggerMix = 2;
			}
//			printf("term resultvalue %f\n", result->value.f);
			result->type = FLOATTYPE;
			result->value.f = result->value.f * temp->value.f;
//			printf("term value is %f\n", result->value.f);
		}

		free(temp);
	}
	return (result);
}

st* factor(){
	st* result = (st*)malloc(sizeof(st));
//	printf("factor ch %c\n", ch);
//	printf("factor token : %d\n", token);
	if(token == NUMBER)
	{
		if(isFloat == 1){
			result->value.f = floatNum;
			result->type = FLOATTYPE;
		//	printf("factor result float %f\n", result->value.f);
		}
		else{
			result->value.i = num;
			result->type = INTTYPE;
		//	printf("factor result int %d\n", result->value.i);
		}
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

	return (result);
}
void main(){
	st* result;
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
	else{
		switch(triggerMix){
			case 0:
				printf("result %d\n", result->value.i);
				break;
			case 1:
				printf("result %.4f\n", result->value.f);
				break;
			case 2:
				error(4);
				printf("result %.4f\n", result->value.f);
				break;
		}
	}
}
void error(int i){
	switch(i)
	{
		case 1:
			printf("error : number or '(' expected\n");
			printf("%d번째칸 문법적 에러\n", arrNum);
			exit(1);
			break;
		case 2:
			printf("error : ')' expected\n");
			printf("%d번째칸 문법적 에러\n", arrNum);
			exit(1);
			break;
		case 3:
			printf("error : EOF expected\n");
			exit(1);
			break;
		case 4:
			printf("warning : Mixed type.\n");
			break;
	}
}
