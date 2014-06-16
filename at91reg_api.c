#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "at91reg.h"

static void *at91reg_base_addr;

/**********************************************************************************
**	@brief	:	map at91 system controller register to userspace 
**	@reg	:	userspace at91 system controller register data structure
**	@return	:	sucess return 0, failed return -1
**********************************************************************************/
int at91reg_mmap(P_AT91_SCR reg)
{
	int fd;	

	/* Open at91reg device */
	if ((fd = open(AT91_REG_DEVICE, O_RDWR)) == -1){

		perror("Open at91reg device error:");
		return -1;
	}

	/* Mmap at91reg to userspace */	
	if ((at91reg_base_addr = (mmap(NULL, AT91_MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0))) == MAP_FAILED){

		perror("Mmap at91reg device error:");
		close(fd);
		return -1;
	}

	/* Set at91reg offset for user space */	
	reg->pio_a = (P_AT91_PIO)(at91reg_base_addr + AT91_PIOA_OFFSET);
	reg->pio_b = (P_AT91_PIO)(at91reg_base_addr + AT91_PIOB_OFFSET);
	reg->pio_c = (P_AT91_PIO)(at91reg_base_addr + AT91_PIOC_OFFSET);	
	reg->pmc   = (P_AT91_PMC)(at91reg_base_addr + AT91_PMC_OFFSET);

	/* After mmap close device */
	close(fd);

	return 0;
}

/**********************************************************************************
**	@brief	:	unmap at91 system controller register form userspace
**********************************************************************************/
int at91reg_unmap(void)
{
	/* Unmap at91 system controller register */
	if (munmap(at91reg_base_addr, AT91_MMAP_SIZE) == -1){

		perror("Unmap at91reg device error:");
		return -1;
	}	

	return 0;
}

