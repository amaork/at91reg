at91_reg
========

Atmel AT91SAM serial SOC System Controller Register operating API for userspace (Include a simple linux device driver and a userspace lib)

## Description

This repository include a linux device driver module(`at91reg.c`) and a userspace lib (`at91reg_api.c`) , using to operate ATMEL AT91SAM serial Soc System controller register in userspace. So that you can operating GPIO、PMC and othen SCRs in userspace, without a specific device driver in kernel to support it. The `at91reg.c` device driver module just simple mmap the AT91SAM Soc SFRs to userspace, other operating all doing in the userspace.

## Feature

- You can control SFRs in userspace it's very flexible

- One device driver in kernel, can visit all SFRs in userspace


## How to use

1. Configure & make
	
		Edit makefile CROSS as you Cross compiler and make
		
		CROSS	:=	arm-linux-
		
		make

		after make get at91reg.ko libat91reg.a libat91reg.so 

2. Install device driver module in target board (AT91SAM9x arm linux)

		insmod at91reg.ko

3. Using userspace lib operating SFRs in your apps or embedded source code to your apps

		AT91_SFR at91_sfr;
		bzero(&at91_sfr, sizeof(AT91_SFR));

		/* Mmap at91reg */
		if (at91reg_mmap(&at91_sfr) == -1){

			fprintf(stderr, "Mmap at91reg failed!\n");
			return -1;
		}    

		/* Do something with sfrs */
		.....
		
		.......

		.........


		/* After use, at the end unmap at91reg */
		if (at91reg_unmap() == -1){

			fprintf(stderr, "Unmap at91reg failed!\n");
			return -1;
		}