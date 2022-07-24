/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/05/2018 14:32:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include "bbb_regs.h"
#include "hw_types.h"


bool flag_gpio;

typedef enum _pinNum{
	PIN1=1,
	PIN2
}pinNum;


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  disableWdt
 *  Description:  
 * =====================================================================================
 */
void disableWdt(void){
	HWREG(WDT_WSPR) = 0xAAAA;
	while((HWREG(WDT_WWPS) & (1<<4)));
	
	HWREG(WDT_WSPR) = 0x5555;
	while((HWREG(WDT_WWPS) & (1<<4)));
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  delay
 *  Description:  
 * =====================================================================================
 */
void delay(unsigned int mSec){
    volatile unsigned int count;
    
	for(count=0; count<mSec; count++);

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  putCh
 *  Description:  
 * =====================================================================================
 */
void putCh(char c){
	while(!(HWREG(UART0_LSR) & (1<<5)));

	HWREG(UART0_THR) = c;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getCh
 *  Description:  
 * =====================================================================================
 */
char getCh(){
	while(!(HWREG(UART0_LSR) & (1<<0)));

	return(HWREG(UART0_RHR));
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  putString
 *  Description:  
 * =====================================================================================
 */
int putString(char *str, unsigned int length){
	for(int i = 0; i < length; i++){
    	putCh(str[i]);
	}
	return(length);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getString
 *  Description:  
 * =====================================================================================
 */
int getString(char *buf, unsigned int length){
	for(int i = 0; i < length; i ++){
    	buf[i] = getCh();
   	}
	return(length);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  gpioSetup
 *  Description:  
 * =====================================================================================
 */
void gpioSetup(){
	/* set clock for GPIO1, TRM 8.1.12.1.31 */
	HWREG(CM_PER_GPIO1_CLKCTRL) = 0x40002;

    /* Interrupt mask */
    HWREG(INTC_MIR_CLEAR3) |= (1<<2);//(98 --> Bit 2 do 4º registrador (MIR CLEAR3))

	//mascara de interrupcao para o mir_clear do grupo: GPIOINT1B = 99 -> (0, 1, 2 ou 3) -> (99 >> 5)
	HWREG(INTC_MIR_CLEAR3) |= (1<<3);//Bit 3 do 4º registrador (MIR CLEAR3) 0x63 & 0x1F = 3
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  butConfig
 *  Description:  
 * =====================================================================================
 */
void butConfig ( ){
    /*  configure pin mux for input GPIO */
	HWREG(CM_PER_GPMCAD12_REGS) |= 0x2F;

	//configuracao do modulo do pino referente ao botao como entrada gpio1_17(P9, 23)
	HWREG(CM_PER_GPMC_A1_REGS) |= 0x2F;

    /* clear pin 23 for input, led USR0, TRM 25.3.4.3 */
	HWREG(GPIO1_OE) |= 1<<12 | 1<<PIN_BUTTON_GPIO1_17;//habilitando recursos de saida(PADs)
	
	flag_gpio = false;

    /* Setting interrupt GPIO pin. */
	HWREG(GPIO1_IRQSTATUS_SET_0) |= 1<<12; 	
	HWREG(GPIO1_IRQSTATUS_SET_1) |= 1<<PIN_BUTTON_GPIO1_17;

  	/* Enable interrupt generation on detection of a rising edge.*/
	HWREG(GPIO1_RISINGDETECT) |= 1<<12;// | 1<<PIN_BUTTON_GPIO1_17;
	HWREG(GPIO1_FALLINGDETECT) |= 1<<PIN_BUTTON_GPIO1_17;

}/* -----  end of function butConfig  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledConfig
 *  Description:  
 * =====================================================================================
 */
void ledConfig ( ){
    /*  configure pin mux for output GPIO */
    HWREG(CM_PER_GPMCA7_REGS) |= 0x7;
    HWREG(CM_PER_GPMCA8_REGS) |= 0x7;

    /* clear pin 23 and 24 for output, leds USR3 and USR4, TRM 25.3.4.3 */
    HWREG(GPIO1_OE) &= ~(1<<23);
    HWREG(GPIO1_OE) &= ~(1<<24);

}/* -----  end of function ledConfig  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  readBut
 *  Description:  
 * =====================================================================================
 */
unsigned int readBut ( ){
	unsigned int temp;
	temp = HWREG(GPIO1_DATAIN)&0x1000;

	return(temp);
}/* -----  end of function readBut  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledOff
 *  Description:  
 * =====================================================================================
 */
void ledOff(pinNum pin){
	switch (pin) {
		case PIN1:
			HWREG(GPIO1_CLEARDATAOUT) |= (1<<23);
		break;
		case PIN2:	
			HWREG(GPIO1_CLEARDATAOUT) |= (1<<24);
		break;
		default:
		break;
	}/* -----  end switch  ----- */
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledOn
 *  Description:  
 * =====================================================================================
 */
void ledOn(pinNum pin){
	
	switch (pin) {
		case PIN1:
			HWREG(GPIO1_SETDATAOUT) |= (1<<23);
		break;
		case PIN2:
			HWREG(GPIO1_SETDATAOUT) |= (1<<24);
		break;
		default:
		break;
	}/* -----  end switch  ----- */
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  gpioIsrHandler
 *  Description:  
 * =====================================================================================
 */
void gpioIsrHandler(void){

    /* Clear the status of the interrupt flags */
	HWREG(GPIO1_IRQSTATUS_0) = 0x1000;

	HWREG(GPIO1_IRQSTATUS_1) = (1<<PIN_BUTTON_GPIO1_17); 

	flag_gpio = true;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ISR_Handler
 *  Description:  
 * =====================================================================================
 */
void ISR_Handler(void){
	/* Verify active IRQ number */
	unsigned int irq_number = HWREG(INTC_SIR_IRQ) & 0x7f;

	switch(irq_number){
		case 98:
			gpioIsrHandler();
		break;
		case 99:
			gpioIsrHandler();
		break;
		default:
		break;
	}
	/* acknowledge IRQ */
	HWREG(INTC_CONTROL) = 0x1;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main(void){
	
	/* Hardware setup */
	gpioSetup();
	ledConfig();
	butConfig();
	disableWdt();

	putString("gpio Interrupt...\n\r",19);
	ledOff(PIN1);
	ledOff(PIN2);
	delay(0x3FFFF);

	while(true){
		if(flag_gpio){
			putString("button press!\n\r",15);
			ledOn(PIN1);
			delay(0x3FFFFFF);
			ledOn(PIN2);
			delay(0x3FFFF);
			// ledOff(PIN1);
			// delay(0x3FFFFFF);
			// ledOff(PIN2);
			// delay(0x3FFFF);
			flag_gpio = false;
		}else{
			// ledOn(PIN1);
			// ledOn(PIN2);
			// delay(0x3FFFF);
			ledOff(PIN1);
			ledOff(PIN2);
			//delay(0x3FFFF);		
		}
	}

	return(0);
}




