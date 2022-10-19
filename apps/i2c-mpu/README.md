# Aplicação com dispositivo I2C, utilizando a Beaglebone Black e seu sistema de arquivos

## Descrição

O objetivo dessa aplicação é utilizar algum dispositvo que tenha comunicação I2C, e usar o barramento da Beaglebone, para por em funcionamento. Foi utilizado:

* Placa de desenvolvimento Beaglebone Black

* Sistema de arquivo personalizado (criação via Buildroot)

* Módulo MPU6050

* Linaro GCC (cross-toolchain)

Para compilar:

```sh
arm-linux-gnueabihf-gcc main.c -static -o ./app
```

Para executar (no linux da placa):

```sh
./app
```

Funcionamento:

Ao movimentar o módulo MPU-6050, é feita a verficação se os eixos excedem o range determinado. Caso sejam ultrapassados, aciona-se um buzzer para sinalizar que o o limite foi execedido.
