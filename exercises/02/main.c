/*What does Example above output? Try running it on your machine. 
Why did it output what it did? Try checking the output of the preprocessor.

O que o Exemplo acima produz? Tente executá-lo em sua máquina. 
Por que produziu o que fez? Tente verificar a saída do pré-processador.
*/

//===============EXAMPLE======================

#include <stdio.h>

#define SQR(x) (x * x)

int main(){
    int counter; /* counter for loop */

    for (counter = 0; counter < 5; ++counter) {
        printf("x %d, x squared %d\n",counter+1, SQR(counter+1));
    }

    return (0);

}
//=============================================

/*
Ao executar, era esperado que retornasse o quadrado do contador no loop. Mas há
um problema com a expressão sqr(counter+1), onde a mesma expandida, temos:
sqr(counter+1)
(counter+1 * counter+1)
Logo, a macro implementada nao funciona para retornar o quadrado. No entanto,
colocando parenteses em volta dos paramentros podemos resolver o problema.
#define sqr(x) ((X) * (X))
*/