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

#define DELAY_USE_INTERRUPT		1

unsigned int contDelay = 50;

/**
 * \brief   This macro will check for write POSTED status
 *
 * \param   reg          Register whose status has to be checked
 *
 *    'reg' can take the following values \n
 *    DMTIMER_WRITE_POST_TCLR - Timer Control register \n
 *    DMTIMER_WRITE_POST_TCRR - Timer Counter register \n
 *    DMTIMER_WRITE_POST_TLDR - Timer Load register \n
 *    DMTIMER_WRITE_POST_TTGR - Timer Trigger register \n
 *    DMTIMER_WRITE_POST_TMAR - Timer Match register \n
 *
 **/
#define DMTimerWaitForWrite(reg)   \
            if(HWREG(DMTIMER_TSICR) & 0x4)\
            while((reg & HWREG(DMTIMER_TWPS)));


int flag_timer = false;


bool flag_gpio;

typedef enum _pinNum{
	PIN1=3,
	PIN2=4,
	PIN3=1
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
	HWREG(CM_PER_GPIO2_CLKCTRL) = 0x40002;
	

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
	
	HWREG(CM_PER_GPMC_A0_REGS) |= 0x2F;
	HWREG(CM_PER_GPMC_BEn1_REGS) |= 0x2F;

    /* clear pin 23 for input, led USR0, TRM 25.3.4.3 */
	HWREG(GPIO1_OE) |= 1<<PULLDOWN | 1<<PULLUP;//habilitando recursos de saida(PADs)
	
	flag_gpio = false;

    /* Setting interrupt GPIO pin. */
	HWREG(GPIO1_IRQSTATUS_SET_0) |= 1<<PULLUP; 	
	HWREG(GPIO1_IRQSTATUS_SET_1) |= 1<<PULLDOWN;


  	/* Enable interrupt generation on detection of a rising our falling edge.*/
	HWREG(GPIO1_RISINGDETECT) |= 1<<PULLDOWN;
	HWREG(GPIO1_RISINGDETECT) |= 1<<PULLUP;
	HWREG(GPIO1_DEBOUNCENABLE) |= 1<<PULLUP;

}/* -----  end of function butConfig  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledConfig
 *  Description:  
 * =====================================================================================
 */
void ledConfig ( ){
   
	//leds externos
	HWREG(CM_PER_GPMC_OEN_REN_REGS) |= 0x7;
	HWREG(CM_PER_GPMC_WEn_REGS) |= 0x7;
	HWREG(CM_PER_GPMC_CLK_REGS) |= 0x7;


	/* clear pin leds externos*/
	HWREG(GPIO2_OE) &= ~(1<<LED1);
	HWREG(GPIO2_OE) &= ~(1<<LED2);
	HWREG(GPIO2_OE) &= ~(1<<LED3);


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
			HWREG(GPIO2_CLEARDATAOUT) |= (1<<LED1);
		break;
		case PIN2:	
			HWREG(GPIO2_CLEARDATAOUT) |= (1<<LED2);
		break;
		case PIN3:	
			HWREG(GPIO2_CLEARDATAOUT) |= (1<<LED3);
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
			HWREG(GPIO2_SETDATAOUT) |= (1<<LED1);
		break;
		case PIN2:	
			HWREG(GPIO2_SETDATAOUT) |= (1<<LED2);
		break;
		case PIN3:	
			HWREG(GPIO2_SETDATAOUT) |= (1<<LED3);
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  timerEnable
 *  Description:  
 * =====================================================================================
 */
void timerEnable(){
    /* Wait for previous write to complete in TCLR */
	DMTimerWaitForWrite(0x1);

    /* Start the timer */
    HWREG(DMTIMER_TCLR) |= 0x1;
}/* -----  end of function timerEnable  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  timerDisable
 *  Description:  
 * =====================================================================================
 */
void timerDisable(){
    /* Wait for previous write to complete in TCLR */
	DMTimerWaitForWrite(0x1);

    /* Start the timer */
    HWREG(DMTIMER_TCLR) &= ~(0x1);
}/* -----  end of function timerEnable  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  delay
 *  Description:  
 * =====================================================================================
 */
void delay(unsigned int mSec){
#ifdef DELAY_USE_INTERRUPT
    unsigned int countVal = TIMER_OVERFLOW - (mSec * TIMER_1MS_COUNT);

   	/* Wait for previous write to complete */
	DMTimerWaitForWrite(0x2);

    /* Load the register with the re-load value */
	HWREG(DMTIMER_TCRR) = countVal;
	
	flag_timer = false;

    /* Enable the DMTimer interrupts */
	HWREG(DMTIMER_IRQENABLE_SET) = 0x2; 

    /* Start the DMTimer */
	timerEnable();

    while(flag_timer == false);

    /* Disable the DMTimer interrupts */
	HWREG(DMTIMER_IRQENABLE_CLR) = 0x2; 
#else
    while(mSec != 0){
        /* Wait for previous write to complete */
        DMTimerWaitForWrite(0x2);

        /* Set the counter value. */
        HWREG(DMTIMER_TCRR) = 0x0;

        timerEnable();

        while(HWREG(DMTIMER_TCRR) < TIMER_1MS_COUNT);

        /* Stop the timer */
        HWREG(DMTIMER_TCLR) &= ~(0x00000001u);

        mSec--;
    }
#endif
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  timerSetup
 *  Description:  
 * =====================================================================================
 */
void timerSetup(void){
     /*  Clock enable for DMTIMER7 TRM 8.1.12.1.25 */
    HWREG(CM_PER_TIMER7_CLKCTRL) |= 0x2;

	/*  Check clock enable for DMTIMER7 TRM 8.1.12.1.25 */    
    while((HWREG(CM_PER_TIMER7_CLKCTRL) & 0x3) != 0x2);

#ifdef DELAY_USE_INTERRUPT
    /* Interrupt mask */
    HWREG(INTC_MIR_CLEAR2) |= (1<<31);//(95 --> Bit 31 do 3º registrador (MIR CLEAR2))
#endif
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  timerIrqHandler
 *  Description:  
 * =====================================================================================
 */
void timerIrqHandler(void){

    /* Clear the status of the interrupt flags */
	HWREG(DMTIMER_IRQSTATUS) = 0x2; 

	flag_timer = true;

    /* Stop the DMTimer */
	timerDisable();
}

void gpioIsrHandlerA(){
	/* Clear the status of the interrupt flags */
	HWREG(GPIO1_IRQSTATUS_0) = (1<<PULLUP);
	contDelay+=50;
	if(contDelay==1000){
		contDelay = 50;
	}
	
}

void gpioIsrHandlerB(){
	/* Clear the status of the interrupt flags */
	HWREG(GPIO1_IRQSTATUS_1) = (1<<PULLDOWN);
	flag_gpio ^= true;

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

	if(irq_number == 95){
		timerIrqHandler();

	}else if(irq_number == 98){
		gpioIsrHandlerA();

	}else if(irq_number == 99){
		gpioIsrHandlerB();
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
	timerSetup();


	// putString("\n\n*------------------------------------------*\n\r",48);
	// putString("                  *MENU*                     \n\r",48);
	// putString("*------------------------------------------*\n\r",47);

	// putString("Selecione uma opcao:\n\r",22);

	// putString("\n1- 250ms\n\r",11);
	// putString("\n2- 500ms\n\r",11);
	// putString("\n3- 750ms\n\r",11);
	// putString("\n4- 1000ms\n\r",12);
	
	/* Hardware setup */
	gpioSetup();
	timerSetup();
	disableWdt();

	while(true){
		if(flag_gpio){
	
			ledOn(PIN1);
			delay(contDelay);
			ledOn(PIN2);
			delay(contDelay);
			ledOn(PIN3);
			delay(contDelay);

			ledOff(LED2);
			delay(contDelay);
			ledOff(LED1);
			delay(contDelay);
			ledOff(LED3);
			delay(contDelay);

						
		}else{
			ledOn(LED1);
			ledOn(LED2);
			ledOn(LED3);
			delay(contDelay);
			ledOff(LED1);
			ledOff(LED2);
			ledOff(LED3);
			delay(contDelay);
				
		}
	}

	return(0);
}




