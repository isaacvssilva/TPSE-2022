/*
 * =====================================================================================
 *
 *       Filename:  blink-sysfs.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25/09/2022 17:07:50
 *       Revision:  none
 *       Compiler:  arm-linux-gnueabihf-gcc (CROSS_COMPILE)
 *
 *         Author:  Isaac Vinicius, isaacvinicius2121@alu.ufc.br
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define PATH "/sys/class/leds/"

int main(int argc, char *argv[]){
    unsigned int iUsr; //variavel que ira definir qual led USR
    char str_mode[25]; //variavel que ira definir como o USR deve se comportar

    FILE *diretorio = NULL; //ponteiro para acessar diretorio dos leds no linux da bbb
    FILE *set_IO = NULL; //ponteiro para setar o tipo de saida da funcao do led
    
    /*-----------modos USR--------*/
    char func_timer[] = "timer";
    char func_none[] = "none";
    char delay_on[200];
    char delay_off[200];
    char func_heartbeat[] = "heartbeat";
    char func_in[1];
   
    printf("Informe o USR(0-3):\n"); 
    scanf("%d", &iUsr);
    
    switch (iUsr){
        case 0:
            printf("escolha um modo: heartbeat, timer, brightness, none\n");
            scanf("%s", str_mode);

            if(strcmp(str_mode, "heartbeat")==0){
                //abrindo diretorio do USR0 e setando com timer
                diretorio = fopen(PATH"beaglebone:green:usr0/trigger", "w");
                fwrite(func_heartbeat, 1, sizeof(func_heartbeat), diretorio);
                fclose(diretorio);
                printf("modo heartbeat ativo...\n");
            
            }else if(strcmp(str_mode, "timer")==0){
                
                printf("defina o delay_On\n");
                scanf("%s", &delay_on);
                printf("defina o delay_Off\n");
                scanf("%s", &delay_off);

                //abrindo diretorio do USR0 e setando com timer
                diretorio = fopen(PATH"beaglebone:green:usr0/trigger", "w");
                fwrite(func_timer, 1, sizeof(func_timer), diretorio);
                fclose(diretorio);

                //setando delay_on e delay_off do USR0
                set_IO = fopen(PATH"beaglebone:green:usr0/delay_on", "w");
                fwrite(delay_on, 1, sizeof(delay_on), set_IO);
                fclose(set_IO);

                set_IO = fopen(PATH"beaglebone:green:usr0/delay_off", "w");
                fwrite(delay_off, 1, sizeof(delay_off), set_IO);
                fclose(set_IO);
                printf("modo timer ativo...\n");

            }else if(strcmp(str_mode, "brightness")==0){
                printf("defina a saida (0-1)\n");
                scanf("%s", &func_in);

                if(strcmp(func_in, "1")==0){
                    diretorio = fopen(PATH"beaglebone:green:usr0/brightness", "w");
                    fwrite(func_in, 1, sizeof(func_in), diretorio);
                    printf("LED on\n");
                    fclose(diretorio);
                }else if(strcmp(func_in, "0")==0){
                    diretorio = fopen(PATH"beaglebone:green:usr0/brightness", "w");
                    fwrite(func_in, 1, sizeof(func_in), diretorio);
                    printf("LED off\n");
                    fclose(diretorio);
                }
            }else if(strcmp(str_mode, "none")==0){
                diretorio = fopen(PATH"beaglebone:green:usr0/trigger", "w");
                fwrite(func_none, 1, sizeof(func_none), diretorio);
                fclose(diretorio);
            }else{
                printf("modo invalido!!\n");
            }
        break;
        case 1:
            printf("escolha um modo: heartbeat, timer, brightness, none\n");
            scanf("%s", str_mode);

            if(strcmp(str_mode, "heartbeat")==0){
                //abrindo diretorio do USR1 e setando com timer
                diretorio = fopen(PATH"beaglebone:green:usr1/trigger", "w");
                fwrite(func_heartbeat, 1, sizeof(func_heartbeat), diretorio);
                fclose(diretorio);
                printf("modo heartbeat ativo...\n");
            
            }else if(strcmp(str_mode, "timer")==0){
                
                printf("defina o delay_On\n");
                scanf("%s", &delay_on);
                printf("defina o delay_Off\n");
                scanf("%s", &delay_off);

                //abrindo diretorio do USR1 e setando com timer
                diretorio = fopen(PATH"beaglebone:green:usr1/trigger", "w");
                fwrite(func_timer, 1, sizeof(func_timer), diretorio);
                fclose(diretorio);

                //setando delay_on e delay_off do USR1
                set_IO = fopen(PATH"beaglebone:green:usr1/delay_on", "w");
                fwrite(delay_on, 1, sizeof(delay_on), set_IO);
                fclose(set_IO);

                set_IO = fopen(PATH"beaglebone:green:usr1/delay_off", "w");
                fwrite(delay_off, 1, sizeof(delay_off), set_IO);
                fclose(set_IO);
                printf("modo timer ativo...\n");

            }else if(strcmp(str_mode, "brightness")==0){
                printf("defina a saida (0-1)\n");
                scanf("%s", &func_in);

                if(strcmp(func_in, "1")==0){
                    diretorio = fopen(PATH"beaglebone:green:usr1/brightness", "w");
                    fwrite(func_in, 1, sizeof(func_in), diretorio);
                    printf("LED on\n");
                    fclose(diretorio);
                    
                }else if(strcmp(func_in, "0")==0){
                    diretorio = fopen(PATH"beaglebone:green:usr1/brightness", "w");
                    fwrite(func_in, 1, sizeof(func_in), diretorio);
                    printf("LED off\n");
                    fclose(diretorio);
                }
            }else if(strcmp(str_mode, "none")==0){
                diretorio = fopen(PATH"beaglebone:green:usr1/trigger", "w");
                fwrite(func_none, 1, sizeof(func_none), diretorio);
                fclose(diretorio);
            }else{
                printf("modo invalido!!\n");
            }
        break;
        case 2:
            printf("escolha um modo: heartbeat, timer, brightness, none\n");
            scanf("%s", str_mode);

            if(strcmp(str_mode, "heartbeat")==0){
                //abrindo diretorio do USR2 e setando com timer
                diretorio = fopen(PATH"beaglebone:green:usr2/trigger", "w");
                fwrite(func_heartbeat, 1, sizeof(func_heartbeat), diretorio);
                fclose(diretorio);
                printf("modo heartbeat ativo...\n");
            
            }else if(strcmp(str_mode, "timer")==0){
                
                printf("defina o delay_On\n");
                scanf("%s", &delay_on);
                printf("defina o delay_Off\n");
                scanf("%s", &delay_off);

                //abrindo diretorio do USR2 e setando com timer
                diretorio = fopen(PATH"beaglebone:green:usr2/trigger", "w");
                fwrite(func_timer, 1, sizeof(func_timer), diretorio);
                fclose(diretorio);

                //setando delay_on e delay_off do USR2
                set_IO = fopen(PATH"beaglebone:green:usr2/delay_on", "w");
                fwrite(delay_on, 1, sizeof(delay_on), set_IO);
                fclose(set_IO);

                set_IO = fopen(PATH"beaglebone:green:usr2/delay_off", "w");
                fwrite(delay_off, 1, sizeof(delay_off), set_IO);
                fclose(set_IO);
                printf("modo timer ativo...\n");

            }else if(strcmp(str_mode, "brightness")==0){
                printf("defina a saida (0-1)\n");
                scanf("%s", &func_in);

                if(strcmp(func_in, "1")==0){
                    diretorio = fopen(PATH"beaglebone:green:usr2/brightness", "w");
                    fwrite(func_in, 1, sizeof(func_in), diretorio);
                    printf("LED on\n");
                    fclose(diretorio);

                }else if(strcmp(func_in, "0")==0){
                    diretorio = fopen(PATH"beaglebone:green:usr2/brightness", "w");
                    fwrite(func_in, 1, sizeof(func_in), diretorio);
                    printf("LED off\n");
                    fclose(diretorio);
                }
            }else if(strcmp(str_mode, "none")==0){
                diretorio = fopen(PATH"beaglebone:green:usr2/trigger", "w");
                fwrite(func_none, 1, sizeof(func_none), diretorio);
                fclose(diretorio);
            }else{
                printf("modo invalido!!\n");
            }
        break;
        case 3:
            printf("escolha um modo: heartbeat, timer, brightness, none\n");
            scanf("%s", str_mode);

            if(strcmp(str_mode, "heartbeat")==0){
                //abrindo diretorio do USR3 e setando com timer
                diretorio = fopen(PATH"beaglebone:green:usr3/trigger", "w");
                fwrite(func_heartbeat, 1, sizeof(func_heartbeat), diretorio);
                fclose(diretorio);
                printf("modo heartbeat ativo...\n");
            
            }else if(strcmp(str_mode, "timer")==0){
                
                printf("defina o delay_On\n");
                scanf("%s", &delay_on);
                printf("defina o delay_Off\n");
                scanf("%s", &delay_off);

                //abrindo diretorio do USR3 e setando com timer
                diretorio = fopen(PATH"beaglebone:green:usr3/trigger", "w");
                fwrite(func_timer, 1, sizeof(func_timer), diretorio);
                fclose(diretorio);

                //setando delay_on e delay_off do USR3
                set_IO = fopen(PATH"beaglebone:green:usr3/delay_on", "w");
                fwrite(delay_on, 1, sizeof(delay_on), set_IO);
                fclose(set_IO);

                set_IO = fopen(PATH"beaglebone:green:usr3/delay_off", "w");
                fwrite(delay_off, 1, sizeof(delay_off), set_IO);
                fclose(set_IO);
                printf("modo timer ativo...\n");

            }else if(strcmp(str_mode, "brightness")==0){
                printf("defina a saida (0-1)\n");
                scanf("%s", &func_in);

                if(strcmp(func_in, "1")==0){
                    diretorio = fopen(PATH"beaglebone:green:usr3/brightness", "w");
                    fwrite(func_in, 1, sizeof(func_in), diretorio);
                    printf("LED on\n");
                    fclose(diretorio);

                }else if(strcmp(func_in, "0")==0){
                    diretorio = fopen(PATH"beaglebone:green:usr3/brightness", "w");
                    fwrite(func_in, 1, sizeof(func_in), diretorio);
                    printf("LED off\n");
                    fclose(diretorio);
                }
            }else if(strcmp(str_mode, "none")==0){
                diretorio = fopen(PATH"beaglebone:green:usr3/trigger", "w");
                fwrite(func_none, 1, sizeof(func_none), diretorio);
                fclose(diretorio);
            }else{
                printf("modo invalido!!\n");
            }
        break;
        default:
        printf("Nenhum LED USR selecionado...\n");
    }
    
    return(0);
}
