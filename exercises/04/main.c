/*
Example 10-10 tells us that we have an undefined variable number, 
but our only variable name is counter.

O Exemplo 10-10 nos diz que temos um número de variável indefinido, 
mas nosso único nome de variável é contador.
*/

//===============EXAMPLE=================

#include <stdio.h>
#define RECIPROCAL (number) (1.0 / (number))

int main(){
    float counter; /* Counter for our table */

    for (counter = 1.0; counter < 10.0;counter += 1.0)
        printf("1/%f = %f\n", counter, RECIPROCAL(counter));

    return (0);
}
//=======================================

/*Existe a diferença entre uma macro sem paramentro e uma parametrizada,
onde a parametrizado é quando colocamos parenteses seguido do nome da macro,
e a que não contem parametro é seguida por um espaco apos a definicao da macro.
Neste exemplo pode ser corrigido removendo o espaço entre o nome da macro e o 
parenteses.
*/
