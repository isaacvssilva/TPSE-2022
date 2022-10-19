/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  -
 *
 *        Version:  1.0
 *        Created:  12/10/2022 15:33:47
 *       Revision:  none
 *       Compiler:  arm-linux-gnueabihf-gcc
 *
 *         Author:  Isaac Vinicius, isaacvinicius2121@alu.ufc.br
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include "../inc/mpu_i2c.h"
#define PATH "/sys/class/gpio/"
#define GPIO_60 "60"
#define OUT "out"

int writeMPU(uint8_t addr_start, uint8_t dados){
    /*mestre coloca endereço do registrador e os dados do registrador no barramento.*/
    char buffer_write[2];
    buffer_write[0] = addr_start;
    buffer_write[1] = dados;
    
    if(write(file, buffer_write, 2) <= 0){
        printf("Falha ao adquirir acesso ao barramento e/ou falar com o escravo.\n");
        return -1;
    }
    return 0;
}

int readMPU(uint8_t addr_start, char *buffer, uint32_t tamByte){
    char buffer_write[2];
    buffer_write[0] = addr_start;
    if(write(file, buffer_write, 1) <= 0){
        printf("falha na escrita do endereco\n");
        exit(1);
    }

    if (read(file, buffer, tamByte) <= 0) {
        perror("falha na leitura\n");
    }
    return 0;
}

void mod_MPU6050(){
    //sleep mode: Quando definido como 1, este bit coloca o MPU-60X0 no modo de suspensão.
    writeMPU(PWR_MGMT_1, 0x00); // Tirando o MPU6050 do modo sleep
    writeMPU(GYRO_CONFIG, 0x00); // habilitando giroscopio
    writeMPU(ACCEL_CONFIG, 0x00); // habilitando acelerometro
}

void read_acc(short int *value){
    
    /*inicia a leitura do endereço base dos valores do acelerômetro
    cada valor de eixo é armazenado em 2 registros
    */
    char acc_buffer[6];
    readMPU(REG_ACCEL_XOUT_H, acc_buffer, 6);
    
    /*value[0] = valor do eixo acc x, value[1] = valor do eixo acc y, value[2] = valor do eixo acc z*/
    value[0] = (int) ((acc_buffer[0] << 8) | acc_buffer[1]); // lendo os registradores X
    value[1] = (int) ((acc_buffer[2] << 8) | acc_buffer[3]); // lendo os registradores Y
    value[2] = (int) ((acc_buffer[4] << 8) | acc_buffer[5]); // lendo os registradores Z
}

void read_gyro(short *value){
    
    /*inicia a leitura do endereço base dos valores do giroscopio
    cada valor de eixo é armazenado em 2 registros
    */
    char gyro_buffer[6];
    readMPU(REG_GYRO_XOUT_H, gyro_buffer, 6);
    
    /*value[0] = valor do eixo gyro x, value[1] = valor do eixo gyro y, value[2] = valor do eixo gyro z*/
    value[0] = ((gyro_buffer[0] << 8) + gyro_buffer[1]); // lendo os registradores X
    value[1] = ((gyro_buffer[2] << 8) + gyro_buffer[3]); // lendo os registradores Y
    value[2] = ((gyro_buffer[4] << 8) + gyro_buffer[5]); // lendo os registradores Z
}

int main(){

    FILE *diretorio = NULL; //ponteiro para acessar diretorio do gpio
    FILE *set_IO = NULL; //ponteiro para setar o tipo de saida da funcao do gpio

    //variaveis para pegar os valores do sensor
    double acc_X, acc_Y, acc_Z;
    double gyro_X, gyro_Y, gyro_Z;

    //variaveis para armazenar os valores bruto do sensor
    short acc_value[3], gyro_value[3];

    /*Abrindo barramento para leitura e escrita I2C*/
    if((file = open(I2C_DEVICE_FILE, O_RDWR)) < 0 ){
        perror("Falha ao abrir o barramento i2c!\n");
        return -1;
    }
    /*define o endereço do escravo I2C usando o comando ioctl I2C_SLAVE*/
    if(ioctl(file, I2C_SLAVE, ADDRESS_AD0_LOW) < 0 ){
        perror("Falha ao definir o endereço do escravo I2C!\n");
        close(file);
        return -1;
    }
    mod_MPU6050();
    
    /*exportando diretorio do gpio60(P9_12), e setando como output para conectar o buzzer*/
    diretorio = fopen(PATH"export", "w");
    fwrite(GPIO_60, 1, sizeof(GPIO_60), diretorio);
    fclose(diretorio);
    set_IO = fopen(PATH"gpio60/direction", "w");
    fwrite(OUT, 1, sizeof(OUT), diretorio);
    fclose(set_IO);

    while(1){
        read_acc(acc_value);
        read_gyro(gyro_value);

        /*ACELEROMETRO:
            convertendo valor bruto de ACC em valor G:
                - verificar faixa de valores em operacao, exemplo:
                    faixa sel=2 : 1g -> 4096
                    valor bruto / (valor faixa)
        */
       /*Obtendo valores de saida de -2g a +2g*/
       acc_X = (double) acc_value[0] / ACCEL_FS_SEL_0;
       acc_Y = (double) acc_value[1] / ACCEL_FS_SEL_0;
       acc_Z = (double) acc_value[2] / ACCEL_FS_SEL_0;

        /*
        GIROSCOPIO:
            convertendo valor bruto de gyro em graus:
            faixa sel=0 1graus/seg -> 131
            valor bruto / (valor faixa) = graus/seg : 131/131 = 1graus/seg
        */
       /*Obtendo valores de saida (esacala) ± 250°/seg*/
        gyro_X = (double) gyro_value[0] / GYRO_FS_SEL_0;
        gyro_Y = (double) gyro_value[1] / GYRO_FS_SEL_0;
        gyro_Z = (double) gyro_value[2] / GYRO_FS_SEL_0;

        // printf("Printando valores brutos:\nAcelerometro:\n");
        // printf("angulo X: %d\n", acc_value[0]);
        // printf("angulo Y: %d\n", acc_value[1]);
        // printf("angulo Z: %d\n\n", acc_value[2]);

        // printf("Printando valores convertidos:\nAcelerometro:\n");
        // printf("angulo X: %0.2f\n", acc_X);
        // printf("angulo Y: %0.2f\n", acc_Y);
        // printf("angulo Z: %0.2f\n\n", acc_Z);

        // printf("Printando valores brutos:\nGiroscopio:\n");
        // printf("angulo X: %d\n", gyro_value[0]);
        // printf("angulo Y: %d\n", gyro_value[1]);
        // printf("angulo Z: %d\n\n", gyro_value[2]);

        /*verfica se os eixos utrapassam o range de -40 a 40+, caso verdadeiro, aciona o buzzer*/
        if(gyro_X < -40 || gyro_X > 40 || gyro_Y < -40 || gyro_Y > 40 || gyro_Z < -40 || gyro_Z > 40){
            
            set_IO = fopen(PATH"gpio60/value", "w");
            fwrite("1", 1, 1, diretorio);
            fclose(set_IO);
        }else{
            set_IO = fopen(PATH"gpio60/value", "w");
            fwrite("0", 1, 1, diretorio);
            fclose(set_IO);
        }

        printf("Printando valores convertidos:\nGiroscopio:\n");
        printf("angulo X: %0.2f\n", gyro_X);
        printf("angulo Y: %0.2f\n", gyro_Y);
        printf("angulo Z: %0.2f\n\n", gyro_Z);
        /*suspende a execucao do thread de chamada por 1 segundo*/
        // usleep(1000000);
        /*suspende a execucao do thread de chamada por 0,2 segundo*/
        usleep(200000);
    } 
    return (0);
}