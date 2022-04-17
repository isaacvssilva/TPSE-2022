/*
Write a preprocessor macro that swaps two integers. 
(For the real hacker, write one that does not use a temporary 
variable declared outside the macro.)

Escreva uma macro de pré-processador que troque dois inteiros. 
(Para o hacker real, escreva um que não use uma variável temporária 
declarada fora da macro.)
*/

#include <stdio.h>

#define swap(a,b) a = a + b; b = a - b; a = a - b

int main(){

    int iNum1;
    int iNum2;

    scanf("%d", &iNum1);
    scanf("%d", &iNum2);

    printf("Num1 = %d | Num2 = %d\n", iNum1, iNum2);

    swap(iNum1, iNum2);

    printf("Num1 = %d | Num2 = %d\n", iNum1, iNum2);
    return(0);
}