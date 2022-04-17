/*
Why will Example above not produce the expected output? By how much will the counter go up each time?

Por que o Exemplo acima não produzirá a saída esperada? De quanto o contador subirá a cada vez?
*/

//=============EXAMPLE===================

#include <stdio.h>

#define SQR(x) ((x) * (x))

int main(){
    int counter; /* counter for loop */
    counter = 0;

    while (counter < 5)
        printf("x %d square %d\n", counter, SQR(++counter));

    return (0);
}
//=======================================

/*
O contador esta incrementado em 2 a cada vez que passa no laço de repeticao,
devido a macro SQR, que expandida, temos: ((++counter) * (++counter))
*/