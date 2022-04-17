/*
Write a second macro is_hex that returns true if its argument is a hex digit (0-9, A-F, a-f). 
The second macro should reference the first.

Escreva uma segunda macro is_hex que retorne true se seu argumento for um dígito hexadecimal (0-9, AF, af). 
A segunda macro deve referenciar a primeira.
*/
#include <stdio.h>

#define is_digit(n) ((((n) >= '0') && (n) <= '9'))

#define is_hex(n) ((((n) >= 'A') && (n) <= 'F')) \
    || ((((n) >= 'a') && (n) <= 'f')) || is_digit(n)

int main(){

    char N;
    scanf("%c", &N);

    if(is_hex(N)){
        printf("ok\n");
    }else{
        printf("erro\n");
    }
    return(0);
}