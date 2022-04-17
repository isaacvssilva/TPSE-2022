/*
Write a macro is_digit that returns TRUE if its argument is a decimal digit.

Escreva uma macro is_digit que retorne TRUE se seu argumento for um dígito decimal.
*/

#include <stdio.h>

#define is_digit(n) ((((n) >= '0') && (n) <= '9'))

int main(){

    char N;
    scanf("%c", &N);
    
    if(is_digit(N)){
		printf("ok\n");
	}else{
		printf("erro\n");
	}
    return(0);
}