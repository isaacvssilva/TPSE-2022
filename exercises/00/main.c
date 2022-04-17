/*The Example below generates the answer 47 instead of the expected answer 144. Why?
O Exemplo abaixo gera a resposta 47 em vez da resposta esperada 144. Por quê?
*/

//==============EXEMPLO=============

#include <stdio.h>

#define FIRST_PART 7
#define LAST_PART 5
#define ALL_PARTS FIRST_PART + LAST_PART

int main() {
    printf("The square of all the parts is %d\n", ALL_PARTS * ALL_PARTS); 
   return (0);
}
//================================

/*
por causa do nivel de precedencia da 
multiplicacao. Ou seja, ira ficar 7 + 5 * 7 + 5 
resultando em 47. Seria 144 se na macro fosse colocado parenteses, como:
#define ALL_PARTS (FIRST_PART + LAST_PART)
*/