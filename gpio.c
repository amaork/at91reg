#include "at91reg_api.h"
#include "lock.h"

/**********************************************************************************
**	@brief	:	Set gpio as input port		
**	#port	:	which port AT91_PIO_A, AT91_PIO_B, AT91_PIC_C etc
**	#pin	:	which pin in port will set as input pin 0 - 31 
**	#pull_up:	enable or disable pull up resistor
**	#filter	:	enable or disable glitch filters
**	@return	:	success return 0, fialed return -1
**********************************************************************************/
int gpio_set_as_input(unsigned int port, unsigned int pin, int pull_up, int filter)
{
	/* Check port and pin */
	CHECK_GPIO_PORT(port);
	CHECK_GPIO_PIN(pin);

	/* Get lock */
	LOCK_GPIO(port);

	/* Pull up resistor */	
	if (pull_up){

		__at91reg->pio[port]->PIO_PUER |= (1 << pin);
	}
	else{
		__at91reg->pio[port]->PIO_PUDR |= (1 << pin);
	}
	
	/* Glitch filter */
	if (filter){

		__at91reg->pio[port]->PIO_IFER |= (1 << pin);
	}
	else{

		__at91reg->pio[port]->PIO_IFDR |= (1 << pin);
	}	

	/* Disable output */
	__at91reg->pio[port]->PIO_ODR 	|= (1 << pin);

	/* Disable interrupt */
	__at91reg->pio[port]->PIO_IDR 	|= (1 << pin);

	/* Disable multi-driver */
	__at91reg->pio[port]->PIO_MDDR 	|= (1 << pin);

	/* Enable pio controller */
	__at91reg->pio[port]->PIO_PER  	|= (1 << pin);

	/* Unlock */
	UNLOCK_GPIO(port);	

	/* Check if pio pmc is enabled */
	if (!pmc_peripheral_status(port)){

		switch (port){

			case	AT91_PIO_A	:	return(pmc_peripheral_endis(PIOA_PER_ID, 1));break;
			case	AT91_PIO_B	:	return(pmc_peripheral_endis(PIOB_PER_ID, 1));break;
			case	AT91_PIO_C	:	return(pmc_peripheral_endis(PIOC_PER_ID, 1));break;
		}
	}

	return 0;
}


/**********************************************************************************
**	@brief		:	set gpio as output port	
**	#port		:	which port AT91_PIO_A, AT91_PIO_B, AT91_PIO_C etc
**	#pin		:	which pin in port will set as output 0 - 31
**	#pull_up	:	enable or disable pull up resistor
**	#open_drain	:	enable or disbale open drain
**	#reg		:	
**	@return		:	success return 0, fialed return -1
**********************************************************************************/
int gpio_set_as_output(unsigned int port, unsigned int pin, int pull_up, int open_drain)
{
	/* Check port and pin */
	CHECK_GPIO_PORT(port);
	CHECK_GPIO_PIN(pin);

	/* Get lock */
	LOCK_GPIO(port);

	/* Pull up resistor */	
	if (pull_up){

		__at91reg->pio[port]->PIO_PUER |= (1 << pin);
	}
	else{
		__at91reg->pio[port]->PIO_PUDR |= (1 << pin);
	}

	/* Open drain */
	if (open_drain){
	
		__at91reg->pio[port]->PIO_MDER |= (1 << pin);
	}
	else{
	
		__at91reg->pio[port]->PIO_MDDR |= (1 << pin);	
	}

	/* Disable interrupt */
	__at91reg->pio[port]->PIO_IDR	|= (1 << pin);
	
	/* Enbale output */
	__at91reg->pio[port]->PIO_OER	|= (1 << pin);	

	/* Enable pio controller */
	__at91reg->pio[port]->PIO_PER  	|= (1 << pin);

	/* Unlock */
	UNLOCK_GPIO(port);

 	return 0;
}


/**********************************************************************************
**	@brief	:	set gpio as peripheral function	
**	#port	:	which port AT91_PIO_A, AT91_PIO_B, AT91_PIO_C
**	#pin	:	which pin in port will set as peripheral a function
**	#pull_up:	enable or disable pull up resistor
**	#ab		:	AT91_PIO_PERA, AT91_PIO_PERB	
**	@return	:	success return 0, fialed return -1
**********************************************************************************/
static int gpio_set_as_per(unsigned int port, unsigned int pin, int pull_up, int ab)
{
	/* Check port and pin */
	CHECK_GPIO_PORT(port);
	CHECK_GPIO_PIN(pin);

	/* Get lock */
	LOCK_GPIO(port);

	/* Pull up resistor */	
	if (pull_up){

		__at91reg->pio[port]->PIO_PUER |= (1 << pin);
	}
	else{
		__at91reg->pio[port]->PIO_PUDR |= (1 << pin);
	}

	/* Disable interrupt */
	__at91reg->pio[port]->PIO_IDR	|=	(1 << pin);

	/* Disable output */
	__at91reg->pio[port]->PIO_ODR	|=	(1 << pin);

	/* Disable multi-driver */
	__at91reg->pio[port]->PIO_MDDR	|=	(1 << pin);

	/* Disable glitch filter */ 
	__at91reg->pio[port]->PIO_IFDR	|=	(1 << pin);

	/* Disable pio controller */
	__at91reg->pio[port]->PIO_PDR	|=	(1 << pin);

	/* Enable peripheralfunction */
	switch (ab){

		case AT91_PIO_PERA:	__at91reg->pio[port]->PIO_ASR	|=	(1 << pin);break;
		case AT91_PIO_PERB: __at91reg->pio[port]->PIO_BSR	|=	(1 << pin);break;
	}
	
	/* Unlock */
	UNLOCK_GPIO(port);


	return 0;
}


/**********************************************************************************
**	@brief	:	set gpio as peripheral a(b) function	
**	#port	:	which port AT91_PIO_A, AT91_PIO_B, AT91_PIO_C
**	#pin	:	which pin in port will set as peripheral b function
**	#pull_up:	enable or disable pull up resistor
**	@return	:	success return 0, fialed return -1
**********************************************************************************/
int gpio_set_as_per_a(unsigned int port, unsigned int pin, int pull_up)
{
	return gpio_set_as_per(port, pin, pull_up, AT91_PIO_PERA);
}

int gpio_set_as_per_b(unsigned int port, unsigned int pin, int pull_up)
{
	return gpio_set_as_per(port, pin, pull_up, AT91_PIO_PERB);
}



/**********************************************************************************
**	@brief	:	get specified gpio status such as in out or peripheral function
**	#port	:	which port AT91_PIO_[A B C]
**	#pin	:	which pin [0 - 31]
**	@return	:	success return AT91_PIO_[IN OUT PERA PERB] failed return -1
**********************************************************************************/
int gpio_get_pin_desc(unsigned int port, unsigned int pin)
{
	int st;

	/* Check port and pin */
	CHECK_GPIO_PORT(port);
	CHECK_GPIO_PIN(pin);

	/* Lock */
	LOCK_GPIO(port);

	/* First check if peripheral is active or not */
	if (!(__at91reg->pio[port]->PIO_PSR & (1 << pin))){

		/* check which function is enabled */	
		if (__at91reg->pio[port]->PIO_ABSR & (1 << pin)){

			st = AT91_PIO_PERA;
		}
		else{

			st = AT91_PIO_PERB;
		}
	}
	/* Pin is a gpio */	
	else{
		
		/* Check pin is in or out */
		if (__at91reg->pio[port]->PIO_OSR & (1 << pin)){

			st = AT91_PIO_OUT;
		}
		else{

			st = AT91_PIO_IN;
		}
	}

	/* Unlock */
	UNLOCK_GPIO(port);

	return st;	
}

/**********************************************************************************
**	@brief	:	operating gpio pins
**	#port	:	gpio port AT91_PIO_[A B C]
**	#pin	:	gpio pin [0 - 31]
**	#oper	:	oper zero do clear operating, no zero do set operating
**	@return	:	success return 0, failed return -1
**********************************************************************************/
int gpio_pin_oper(unsigned int port, unsigned int pin, unsigned int oper)
{
	int desc;

	/* Get pin desc, and check if it's a output pin */
	if ((desc = gpio_get_pin_desc(port, pin)) != AT91_PIO_OUT){

		return -1;
	}

	/* Lock */
	LOCK_GPIO(port);

	/* Set pin */
	if (oper){

		__at91reg->pio[port]->PIO_SODR |=	(1 << pin);
	}
	/* Clear pin */
	else{

		__at91reg->pio[port]->PIO_CODR |=	(1 << pin);
	}

	/* Unlock */
	UNLOCK_GPIO(port);

	return 0;
}


/**********************************************************************************
**	@brief	:	set or clear output gpio pin  
**	#port	:	gpio port AT91_PIO_[A B C]
**	#pin	:	gpio pin [0 - 31]
**	@return	:	success return 0, failed return -1
**********************************************************************************/
int gpio_set_pin(unsigned int port, unsigned int pin)
{
	return gpio_pin_oper(port, pin, 1);
}

int gpio_clr_pin(unsigned int port, unsigned int pin)
{
	return gpio_pin_oper(port, pin, 0);
}


/**********************************************************************************KE
**	@brief	:	get gpio pin value  
**	#port	:	gpio port AT91_PIO_[A B C]
**	#pin	:	gpio pin [0 - 31]
**	@return	:	success return gpio pin value, failed return -1
**********************************************************************************/
int gpio_get_pin(unsigned int port, unsigned int pin)
{
	int desc;
	unsigned int st;

	/* First get pin desc */
	if ((desc = gpio_get_pin_desc(port, pin)) == -1){

		return -1;
	}

	/* Lock */
	LOCK_GPIO(port);

	/* Check port type */		
	switch (desc){


		case AT91_PIO_OUT	:	
		case AT91_PIO_PERA	:
		case AT91_PIO_PERB	:	st = (__at91reg->pio[port]->PIO_ODSR & (1 << pin)) >> pin;break;
		case AT91_PIO_IN	:	st = (__at91reg->pio[port]->PIO_PDSR & (1 << pin)) >> pin;break;
	}

	/* Unlock */
	UNLOCK_GPIO(port);

	return st;
}

