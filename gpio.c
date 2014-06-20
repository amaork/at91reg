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

	/* Disable output write */
	__at91reg->pio[port]->PIO_OWDR	|= (1 << pin);

	/* Enable pio controller */
	__at91reg->pio[port]->PIO_PER  	|= (1 << pin);

	/* Unlock */
	UNLOCK_GPIO(port);

 	return 0;
}

/**********************************************************************************
**	@brief		:	set gpio pin as sync output port
**	#port		:	which port AT91_PIO_X
**	#pin_mask	:	which pins will set as sync output, set bit as 1
**	#pull_up	:	enable or disable pull up resistor
**	#open_drain	:	enable or disable open drain
**	@return		:	success return 0, fialed return -1
**********************************************************************************/
int gpio_set_as_sync_output(unsigned int port, unsigned int pin_mask, int pull_up, int open_drain)
{
	/* Check port and pin */
	CHECK_GPIO_PORT(port);

	/* Get lock */
	LOCK_GPIO(port);

	/* Pull up resistor */	
	if (pull_up){

		__at91reg->pio[port]->PIO_PUER |= pin_mask;
	}
	else{
		__at91reg->pio[port]->PIO_PUDR |= pin_mask;
	}

	/* Open drain */
	if (open_drain){
	
		__at91reg->pio[port]->PIO_MDER |= pin_mask;
	}
	else{
	
		__at91reg->pio[port]->PIO_MDDR |= pin_mask;	
	}

	/* Disable interrupt */
	__at91reg->pio[port]->PIO_IDR	|= pin_mask;
	
	/* Enbale output */
	__at91reg->pio[port]->PIO_OER	|= pin_mask;	

	/* Enable sync output */
	__at91reg->pio[port]->PIO_OWER	|= pin_mask;

	/* Enable pio controller */
	__at91reg->pio[port]->PIO_PER  	|= pin_mask;

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

int gpio_sync_write(unsigned int port, unsigned int pin_mask, unsigned int data)
{
	unsigned int osr = 0;
	unsigned int psr = 0;
	unsigned int owsr = 0;

	/* Get PIN_PSR */
	if (gpio_raw_r_psr(port, &psr)){

		fprintf(stderr, "Read PIN_PSR raw data failed!\n");
		return -1;
	}

	/* Check if pin is controled by Pio cotroller */
	if ((psr & pin_mask) != pin_mask){

		fprintf(stderr, "These pins[%X] do not control by pio controller!\n", (psr & pin_mask) ^ pin_mask);
		return -1;
	}

	/* Read PIN_OSR */
	if (gpio_raw_r_osr(port, &osr)){

		fprintf(stderr, "Read PIN_OSR raw data failed!\n");
		return -1;
	}

	/* Check if pin is a output pin */	
	if ((osr & pin_mask) != pin_mask){

		fprintf(stderr, "These pins[%X] do not output pins!\n", (osr & pin_mask) ^ pin_mask);
		return -1;
	}

	/* Read PIN_OWSR */
	if (gpio_raw_r_owsr(port, &owsr)){

		fprintf(stderr, "These pins[%X] do not support sync write!\n", (owsr & pin_mask) ^ pin_mask);
		return -1;
	}		

	/* Sync write */
	return gpio_raw_w_odsr(port, data);
}

int gpio_clr_pin(unsigned int port, unsigned int pin)
{
	return gpio_pin_oper(port, pin, 0);
}



/**********************************************************************************KE
**	@brief	:	get gpio pin value  
**	#port	:	gpio port AT91_PIO_[A B C]
**	#pin	:	gpio pin [0 - 31]
**	#data	:	get gpio pin value save to pin
**	@return	:	success return 0, failed return -1
**********************************************************************************/
int gpio_get_pin(unsigned int port, unsigned int pin, unsigned int *data)
{
	int desc;

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
		case AT91_PIO_PERB	:	*data = (__at91reg->pio[port]->PIO_ODSR & (1 << pin)) >> pin;break;
		case AT91_PIO_IN	:	*data = (__at91reg->pio[port]->PIO_PDSR & (1 << pin)) >> pin;break;
	}

	/* Unlock */
	UNLOCK_GPIO(port);

	return 0;
}

/************************************************************************************
**	@brief	:	read or write gpio register
**	#prot	:	which port AT91_REG_[A B C]
**	#reg	:	which register will read or write GPIO_XXXX
**	#rw		:	zero read not zero write
**	#data	:	if is read(rw == 0) value will save at data, if is write(rw == 1) will
				write data save at data
**	@return	:	success return 0, failed return -1
*************************************************************************************/
int gpio_raw_rw(unsigned int port, unsigned int reg, unsigned int rw, unsigned int *data)
{
	int ret = 0;

	/* Check port */		
	CHECK_GPIO_PORT(port);
	
	/* Check reg */
	CHECK_GPIO_REG(reg);

	/* Lock */
	LOCK_GPIO(port);

	/* Read */
	if (rw == 0){

		switch (reg){

			/* Pio status */
			case 	GPIO_PSR	:	*data	=	__at91reg->pio[port]->PIO_PSR;break;

			/* Output status */
			case 	GPIO_OSR	:	*data	=	__at91reg->pio[port]->PIO_OSR;break;

			/* Input filter */
			case 	GPIO_IFSR	:	*data	=	__at91reg->pio[port]->PIO_IFSR;break;
	
			/* Output and input status */
			case 	GPIO_ODSR	:	*data	=	__at91reg->pio[port]->PIO_ODSR;break;
			case 	GPIO_PDSR	:	*data	=	__at91reg->pio[port]->PIO_PDSR;break;
	
			/* Interrupt */
			case 	GPIO_IMR	:	*data	=	__at91reg->pio[port]->PIO_IMR;break;
			case 	GPIO_ISR	:	*data	=	__at91reg->pio[port]->PIO_ISR;break;
	
			/* Multi-driver */
			case 	GPIO_MDSR	:	*data	=	__at91reg->pio[port]->PIO_MDSR;break;
			
			/* Pull-up */
			case 	GPIO_PUSR	:	*data	=	__at91reg->pio[port]->PIO_PUSR;break;
		
			/* Peripheral a, b */
			case 	GPIO_ABSR	:	*data	=	__at91reg->pio[port]->PIO_ABSR;break;
			
			/* Ouput write */
			case 	GPIO_OWSR	:	*data	=	__at91reg->pio[port]->PIO_OWSR;break;

			default	:	fprintf(stderr, "This register[%u] is write-only!\n", reg); ret = -1;break;
		}	
	}
	/* Write */
	else{

		switch (reg){

			/* Pio enable, disable, status */
			case 	GPIO_PER	:	__at91reg->pio[port]->PIO_PER	|=	*data;break;
			case 	GPIO_PDR	:	__at91reg->pio[port]->PIO_PDR	|=	*data;break;

			/* Output enable, disable, status */
			case 	GPIO_OER	:	__at91reg->pio[port]->PIO_OER	|=	*data;break;
			case 	GPIO_ODR	:	__at91reg->pio[port]->PIO_ODR	|=	*data;break;

			/* Input filter */
			case 	GPIO_IFER	:	__at91reg->pio[port]->PIO_IFER	|=	*data;break;
			case 	GPIO_IFDR	:	__at91reg->pio[port]->PIO_IFDR	|=	*data;break;
	
			/* Set and clear output */
			case 	GPIO_SODR	:	__at91reg->pio[port]->PIO_SODR	|=	*data;break;
			case 	GPIO_CODR	:	__at91reg->pio[port]->PIO_CODR	|=	*data;break;
			case 	GPIO_ODSR	:	__at91reg->pio[port]->PIO_ODSR	=	*data;break;
	
			/* Interrupt */
			case 	GPIO_IER	:	__at91reg->pio[port]->PIO_IER	|=	*data;break;
			case 	GPIO_IDR	:	__at91reg->pio[port]->PIO_IDR	|=	*data;break;
	
			/* Multi-driver */
			case 	GPIO_MDER	:	__at91reg->pio[port]->PIO_MDER	|=	*data;break;
			case 	GPIO_MDDR	:	__at91reg->pio[port]->PIO_MDDR	|=	*data;break;
			
			/* Pull-up */
			case 	GPIO_PUDR	:	__at91reg->pio[port]->PIO_PUDR	|=	*data;break;
			case 	GPIO_PUER	:	__at91reg->pio[port]->PIO_PUER	|=	*data;break;
		
			/* Peripheral a, b */
			case 	GPIO_ASR	:	__at91reg->pio[port]->PIO_ASR	|=	*data;break;
			case 	GPIO_BSR	:	__at91reg->pio[port]->PIO_BSR	|=	*data;break;
			
			/* Ouput write */
			case 	GPIO_OWER	:	__at91reg->pio[port]->PIO_OWER	|=	*data;break;
			case 	GPIO_OWDR	:	__at91reg->pio[port]->PIO_OWDR	|=	*data;break;

			default	:	fprintf(stderr, "This register[%u] is read-only!\n", reg); ret = -1;break;
		}	

	}

	/* Unlock */
	UNLOCK_GPIO(port);
	
	return ret;
}



/************************************************************************************
**	@brief	:	read gpio register
**	#port	:	which port will write AT91_PIO_X
**	#data	:	read data
**	@return	:	success return 0, failed return -1
*************************************************************************************/
int gpio_raw_r_psr(unsigned int port, unsigned int *data)
{
	return gpio_raw_rw(port, GPIO_PSR, READ_OPER, data);
}

int gpio_raw_r_osr(unsigned int port, unsigned int *data)
{
	return gpio_raw_rw(port, GPIO_OSR, READ_OPER, data);
}

int gpio_raw_r_ifsr(unsigned int port, unsigned int *data)
{
	return gpio_raw_rw(port, GPIO_IFSR, READ_OPER, data);
}

int gpio_raw_r_odsr(unsigned int port, unsigned int *data)
{
	return gpio_raw_rw(port, GPIO_ODSR, READ_OPER, data);
}

int gpio_raw_r_prsr(unsigned int port, unsigned int *data)
{
	return gpio_raw_rw(port, GPIO_PDSR, READ_OPER, data);
}

int gpio_raw_r_imr(unsigned int port, unsigned int *data)
{
	return gpio_raw_rw(port, GPIO_IMR, READ_OPER, data);
}

int gpio_raw_r_isr(unsigned int port, unsigned int *data)
{
	return gpio_raw_rw(port, GPIO_ISR, READ_OPER, data);
}

int gpio_raw_r_mdsr(unsigned int port, unsigned int *data)
{
	return gpio_raw_rw(port, GPIO_MDSR, READ_OPER, data);
}

int gpio_raw_r_pusr(unsigned int port, unsigned int *data)
{
	return gpio_raw_rw(port, GPIO_PUSR, READ_OPER, data);
}

int gpio_raw_r_absr(unsigned int port, unsigned int *data)
{
	return gpio_raw_rw(port, GPIO_ABSR, READ_OPER, data);
}

int gpio_raw_r_owsr(unsigned int port, unsigned int *data)
{
	return gpio_raw_rw(port, GPIO_OWSR, READ_OPER, data);
}

/************************************************************************************
**	@brief	:	write gpio register
**	#port	:	which port will write AT91_PIO_X
**	#data	:	write data
**	@return	:	success return 0, failed return -1
*************************************************************************************/
int gpio_raw_w_per(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_PER, WRITE_OPER, &data);
}

int gpio_raw_w_pdr(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_PDR, WRITE_OPER, &data);
}

int gpio_raw_w_oer(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_OER, WRITE_OPER, &data);
}

int gpio_raw_w_odr(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_ODR, WRITE_OPER, &data);
}

int gpio_raw_w_ifer(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_IFER, WRITE_OPER, &data);
}

int gpio_raw_w_ifdr(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_IFDR, WRITE_OPER, &data);
}

int gpio_raw_w_sodr(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_SODR, WRITE_OPER, &data);
}

int gpio_raw_w_codr(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_CODR, WRITE_OPER, &data);
}

int gpio_raw_w_odsr(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_ODSR, WRITE_OPER, &data);
}

int gpio_raw_w_ier(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_IER, WRITE_OPER, &data);
}

int gpio_raw_w_idr(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_IDR, WRITE_OPER, &data);
}

int gpio_raw_w_mder(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_MDER, WRITE_OPER, &data);
}

int gpio_raw_w_mddr(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_MDDR, WRITE_OPER, &data);
}

int gpio_raw_w_pudr(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_PUDR, WRITE_OPER, &data);
}

int gpio_raw_w_puer(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_PUER, WRITE_OPER, &data);
}

int gpio_raw_w_asr(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_ASR, WRITE_OPER, &data);
}

int gpio_raw_w_bsr(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_BSR, WRITE_OPER, &data);
}

int gpio_raw_w_ower(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_OWER, WRITE_OPER, &data);
}

int gpio_raw_w_owdr(unsigned int port, unsigned int data)
{
	return gpio_raw_rw(port, GPIO_OWDR, WRITE_OPER, &data);
}
