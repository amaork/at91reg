at91_reg
========

Atmel AT91SAM serial SOC System Controller Register operating API for userspace (Include a simple linux device driver and a userspace lib)

## Description

This repository include a linux device driver module(`at91reg.c`) and a userspace lib (`at91reg_api.c`) , using to operate ATMEL AT91SAM serial Soc System controller register in userspace. So that you can operating GPIO、PMC and othen SCRs in userspace, without a specific device driver in kernel to support it. The `at91reg.c` device driver module just simple mmap the AT91SAM Soc SFRs to userspace, other operating all doing in the userspace.

## Feature

- You can control SFRs in userspace it's very flexible

- One device driver in kernel, can visit all SFRs in userspace

- Currently only support PIO and PMC, in the future will support more 


## How to use

1. Configure & make
	
		Edit makefile CROSS as you Cross compiler and make
		
		CROSS	:=	arm-linux-
		
		make

		after make get at91reg.ko libat91reg.a libat91reg.so 

2. Install device driver module in target board (AT91SAM9x arm linux)

		insmod at91reg.ko

3. Using userspace lib operating SFRs in your apps or embedded source code to your apps

		#include "at91reg_api.h"

		/* Mmap at91reg */
		if (at91reg_mmap("/dev/at91reg") == -1){

			fprintf(stderr, "Mmap at91reg failed!\n");
			return -1;
		}    

		/* Do something with sfrs */

		/* Set PIOA 8 as output and set pull up and open drain */
		gpio_set_as_output(AT91_PIO_A, 8, 1, 1);

		/* Set PIOB 9 as output and set pull up */
		gpio_set_as_output(AT91_PIO_B, 9, 1, 0);

		/* Set PIOC 10 as input with pull up and glitch filter */
		gpio_set_as_input(AT91_PIO_C, 10, 1, 1);

		/* Set PIOC 11, 12 as peripheral A function and with pull up*/
		gpio_set_as_per_a(AT91_PIOC, 11, 1);
		gpio_set_as_per_a(AT91_PIOC, 12, 1);


		/* Set PIOC 13, 14 as peripheral B function without pull up */
		gpio_set_as_per_b(AT91_PIOC, 13, 0);
		gpio_set_as_per_b(AT91_PIOC, 14, 0);

		/* Using PIOA 8 output a square wave */
		for (i  = 0; i < 100; i++){

			gpio_set_pin(AT91_PIO_B, 8);
			usleep(10);
			gpio_clr_pin(AT91_PIO_B, 8);
			usleep(10);
		}		
		
		/* Get PIOC 10 value */
		value = gpio_get_pin(AT91_PIO_C, 10);
		.....
		
		.......

		.........


		/* After use, at the end unmap at91reg */
		if (at91reg_unmap() == -1){

			fprintf(stderr, "Unmap at91reg failed!\n");
			return -1;
		}
