/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/02/2017 20:05:55
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include	"gpio.h"
#include	"uart.h"
#define		PIN_BUTTON_GPIO1_28 28
#define		PIN_BUTTON_GPIO2_1	1
#define 	PIN_LED_EXTERN		15
#define 	TOGGLE			   	(0x01u)


/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define TIME						1000000

// state machine
typedef enum _state{
			SEQ1=1,
			SEQ2,
			SEQ3,
			SEQ4,
			SEQ5
}state;

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void delay(int);
void ledON(gpioMod  ,ucPinNumber );
void ledOFF(gpioMod ,ucPinNumber );
	
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */

unsigned int flagButton;
int main(void){
	//unsigned int op=SEQ2;
	unsigned int count=0; 
	ucPinNumber pin=22;
	
	/*-----------------------------------------------------------------------------
	 *  initialize GPIO and UART modules
	 *-----------------------------------------------------------------------------*/
	gpioInitModule(GPIO1);
	//delay(1000);
	//gpioInitModule(GPIO2);
   	uartInitModule(UART0, 115200, STOP1, PARITY_NONE, FLOW_OFF);
	
	//inicializando gpio2 para o segundo botao
	gpioInitModule(GPIO2);

	/*-----------------------------------------------------------------------------
	 *  initialize pin of mudule
	 *-----------------------------------------------------------------------------*/
	for(count=pin; count<25; count++){
		//default: inicializando apenas o modulo do pino 22 como saida
		//gpioPinMuxSetup(GPIO1, pin, OUTPUT);

		//alterando para inicilizar o modulo dos pinos: 22, 23, 24 como saida
		gpioPinMuxSetup(GPIO1, count, OUTPUT);
		delay(1000);
	}
	//default:
	gpioPinMuxSetup(GPIO1, 12, INPUT);

	//multiplexacao do modulo do pino referente ao botao como entrada - gpio1_28 (P9, 12)
	gpioPinMuxSetup(GPIO1, PIN_BUTTON_GPIO1_28, INPUT);

	//multiplexacao do modulo do pino referente ao led externo como saida - gpio1_15 (P8, 15)
	gpioPinMuxSetup(GPIO1, PIN_LED_EXTERN, OUTPUT);

	//multiplexacao do modulo do pino referente ao segundo botao como entrada = gpio2_1 (P8, 18)
	gpioPinMuxSetup(GPIO2, PIN_BUTTON_GPIO2_1, INPUT);
	
	/*-----------------------------------------------------------------------------
	 *  set pin direction 
	 *-----------------------------------------------------------------------------*/
	for(count=pin; count<25; count++){
		//default: seta apenas o modulo do pino 22 como saida
		//gpioSetDirection(GPIO1, pin, OUTPUT);

		//alterando para setar o modulo dos pinos: 22, 23, 24 como saida
		gpioSetDirection(GPIO1, count, OUTPUT);
		delay(1000);
	}
	//default:
	gpioSetDirection(GPIO1, 12, INPUT);

	//setando o pino referente ao botao como entrada - gpio1_28 (P9, 12)
	gpioSetDirection(GPIO1, PIN_BUTTON_GPIO1_28, INPUT);

	//setando o pino referente ao led externo como saida - gpio1_15 (P8, 15)
	gpioSetDirection(GPIO1, PIN_LED_EXTERN, OUTPUT);

	//setando o pino referente ao segundo botao como entrada - gpio2_1 (P8, 18)
	gpioSetDirection(GPIO2, PIN_BUTTON_GPIO2_1, INPUT);

    /*-----------------------------------------------------------------------------
     *  set pin in LOW level
     *-----------------------------------------------------------------------------*/
    for(count=pin; count<25; count++){
        ledOFF(GPIO1, count);
		delay(1000);
	}
	//default
	uartPutString(UART0,"GPIO INPUT Initialized\n",22);

	while(true){
		//flagButton ^= TOGGLE;
		//se o botao for pressionado (nivel logico 1) - 
		//ponteiro com a base do endereco do modulo gpio1 + offset 
		//do registro de entrada & bit do pino
		if(HWREG(SOC_GPIO_1_REGS + GPIO_DATAIN) & (1<<PIN_BUTTON_GPIO1_28)){

			
			for(unsigned int i = pin; i<25; i++){
				ledON(GPIO1, pin);
				delay(TIME);
				ledON(GPIO1, pin+1);
				delay(TIME);
				ledON(GPIO1, pin+2);
				delay(TIME);
			}
			ledON(GPIO1, PIN_LED_EXTERN);
			delay(TIME);

			
		//se pressionar o segundo botao, liga todos leds enquanto esta pressionado
		}else if(HWREG(SOC_GPIO_2_REGS + GPIO_DATAIN) & (1<<PIN_BUTTON_GPIO2_1)){
	
			for(unsigned int i = pin; i<25; i++){
				ledON(GPIO1, pin);
				ledON(GPIO1, pin+1);
				ledON(GPIO1, pin+2);	
			}
			ledON(GPIO1, PIN_LED_EXTERN);
		}else{
			for(unsigned int i = pin; i<25; i++){
				ledOFF(GPIO1, pin);
				ledOFF(GPIO1, pin+1);
				ledOFF(GPIO1, pin+2);	
			}
			ledOFF(GPIO1, PIN_LED_EXTERN);
		}
	}

	/*--------------codigo original----------------- */
	// while(true){
	// 				switch (op) {
	// 					case SEQ1:
	// 						ledON(GPIO1, pin);
	// 						delay(1000000);
	// 						ledOFF(GPIO1, pin);
	// 						delay(1000000);
	// 						if(gpioGetPinValue(GPIO1, 12))
	// 							op=SEQ2;
	// 					break;
	// 					case SEQ2:	
	// 						ledON(GPIO1, pin);
	// 						delay(1000000);
	// 						ledOFF(GPIO1, pin);
	// 						delay(1000000);	
	// 						if(gpioGetPinValue(GPIO1, 12))
	// 							op=SEQ3;
	// 					break;
	// 					case SEQ3:	
	// 						ledON(GPIO1, pin+1);
	// 						delay(1000000);
	// 						ledOFF(GPIO1, pin+1);
	// 						delay(1000000);	
	// 						if(gpioGetPinValue(GPIO1, 12))
	// 							op=SEQ4;
	// 					break;
	// 					case SEQ4:	
	// 						ledON(GPIO1, pin+2);
	// 						delay(1000000);
	// 						ledOFF(GPIO1, pin+2);
	// 						delay(1000000);
	// 						if(gpioGetPinValue(GPIO1, 12))
	// 							op=SEQ5;//
	// 					break;
	// 					case SEQ5:
	// 						for(count=pin; count<25; count++)
	// 							ledON(GPIO1, count);
	// 						delay(1000000);
	// 						//delay();
	// 						for(count=pin; count<25; count++)
	// 							ledOFF(GPIO1, count);
	// 						delay(1000000);
	// 						//delay();
	// 						if(gpioGetPinValue(GPIO1, 12))
	// 							op=SEQ2;
	// 					break;
	// 					default:	
	// 					break;
	// 				}				/* -----  end switch  ----- */
	// }

	return(0);
} /* ----------  end of function main  ---------- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledON
 *  Description:  
 * =====================================================================================
 */
void ledON(gpioMod mod, ucPinNumber pin){
				gpioSetPinValue(mod, pin, HIGH);	
}/* -----  end of function ledON  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledOFF
 *  Description:  
 * =====================================================================================
 */
void ledOFF(gpioMod mod,  ucPinNumber pin ){
				gpioSetPinValue(mod, pin, LOW);
}/* -----  end of function ledOFF  ----- */

/*FUNCTION*-------------------------------------------------------
*
* Function Name : Delay
* Comments      :
*END*-----------------------------------------------------------*/
static void delay(int iTime){
	volatile unsigned int ra;
	for(ra = 0; ra < iTime; ra ++);
}

