/*
 * =====================================================================================
 *
 *       Filename:  mpu_i2c.h
 *
 *    Description:  -
 *
 *        Version:  1.0
 *        Created:  12/10/2022 15:29:58
 *       Revision:  none
 *       Compiler:  arm-linux-gnueabihf-gcc
 *
 *         Author:  Isaac Vinicius, isaacvinicius2121@alu.ufc.br
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#ifndef MPUI2C_H
#define MPUI2C_H

/****************************************************************************
**                MACRO REGISTER ADDRESS CONFIG MPU-6050
*****************************************************************************/

#define ADDRESS_AD0_LOW 0x68 // I2C ADDRESS (GND) -> b1101000
#define PWR_MGMT_1 0x6B      // power ADDRESS
#define ACCEL_CONFIG 0x1C    // Accelerometer ADDRESS
#define GYRO_CONFIG 0x1B     // Gyroscope ADDRESS

/*Gyroscope Measurements*/
#define REG_GYRO_XOUT_H 0x43 // axis X+
#define REG_GYRO_XOUT_L 0x44 // axis X-
#define REG_GYRO_YOUT_H 0x45 // axis Y+
#define REG_GYRO_YOUT_L 0x46 // axis Y-
#define REG_GYRO_ZOUT_H 0x47 // axis Z+
#define REG_GYRO_ZOUT_L 0x48 // axis Z-

/*Accelerometer Measurements*/
#define REG_ACCEL_XOUT_H 0x3B // axis X+
#define REG_ACCEL_XOUT_L 0x3C // axis X-
#define REG_ACCEL_YOUT_H 0x3D // axis Y+
#define REG_ACCEL_YOUT_L 0x3E // axis Y+
#define REG_ACCEL_ZOUT_H 0x3F // axis Z+
#define REG_ACCEL_ZOUT_L 0x40 // axis Z-

/*GYROSCOPE SENSITIVITY*/
#define GYRO_FS_SEL_0 131  // esacala ± 250
#define GYRO_FS_SEL_1 65.5 // esacala ± 500
#define GYRO_FS_SEL_2 32.8 // esacala ± 1000
#define GYRO_FS_SEL_3 16.4 // esacala ± 2000

/*ACCELEROMETER SENSITIVITY*/
#define ACCEL_FS_SEL_0 16384 // esacala ± 2
#define ACCEL_FS_SEL_1 8192  // esacala ± 4
#define ACCEL_FS_SEL_2 4096  // esacala ± 8
#define ACCEL_FS_SEL_3 2048  // esacala ± 16
#define I2C_DEVICE_FILE "/dev/i2c-2" //use the I2C ports(P9_19 | P9_20)
#include <stdint.h>
#include <stdio.h>

/*-----------------------------------------------------------------------------
 *  Function prototype
 *-----------------------------------------------------------------------------*/
int file; //Device file
// inicializando modulo
void mod_MPU6050();

/*I2C data bytes are defined to be 8-bits long.*/
/*mestre transmite a condição de partida e escreve os dados no registrador do sensor*/
int writeMPU(uint8_t addr_start, uint8_t dados);

/*
Para ler os registradores internos do MPU-60X0, o mestre envia uma condição de partida,
seguida do endereço I2C e um bit de escrita e, em seguida, o endereço do registrador que será lido.
Ao receber o sinal ACK do MPU-60X0, o mestre transmite um sinal de início seguido do endereço do
escravo e do bit de leitura. Como resultado, O MPU-60X0 envia um sinal ACK e os dados.
*/
int readMPU(uint8_t addr_start, char *buffer, uint32_t tamByte);

/*leitura dos valores bruto do acelerometro */
void read_acc(short int *value);

/*leitura dos valores bruto do giroscopio */
void read_gyro(short *value);
#endif
/*****************************END OF FILE**************************************/
