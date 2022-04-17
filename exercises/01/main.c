/*
The Example above is supposed to print the message "Fatal Error: Abort" and exit 
when it receives bad data. But when it gets good data, it exits. Why?

O exemplo acima deve imprimir a mensagem "Fatal Error: Abort" e sair 
quando receber dados incorretos. Mas quando obtém bons dados, ele sai. Por quê?
*/

//===============EXAMPLE============

#include <stdio.h>
#include <stdlib.h>

#define DIE \
fprintf(stderr, "Fatal Error:Abort\n");exit(8);

int main() {
    /* a random value for testing */
    int value;

    value = 1;
    if (value < 0)
        DIE;

    printf("We did not die\n");
    return (0);
}
//===================================

/*
O programa sai quando colocamos valores > 0 por causa da identação
do pre-processador, onde há duas instruções depois do if pra um macro. 
o if vai executar so a primeira intrução, que seria o DIE, até do ponto e virgula.
A instrucao exit(8) esta fora do bloco do if. Para funcionar, basta colocar chaves
após o DIE e depois do ponto e virgula do exit(8). Dessa forma executa as duas
instruções.
*/