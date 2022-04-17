/*
Write a macro that returns TRUE 
if its parameter is divisible by 10 and FALSE 
otherwise.

Escreva uma macro que retorne TRUE
se seu parâmetro for divisível por 10 e FALSE
caso contrário.
*/
#include <stdio.h>

#define is_div(n) ((n)%10 == 0)

int main(){

    int iNum;
    scanf("%d", &iNum);

    if(is_div(iNum)){
        printf("ok, divide\n");
    }else{
        printf("erro\n");
    }
    return(0);
}