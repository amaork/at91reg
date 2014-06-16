#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include "at91reg_api.h"

static void *at91reg_base_addr = NULL;

extern int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int kind);
/**********************************************************************************
**	@brief	:	map at91 system controller register to userspace 
**	@reg	:	userspace at91 system controller register data structure
**	@return	:	sucess return 0, failed return -1
**********************************************************************************/
int at91reg_mmap(P_AT91_SCR reg)
{
	int fd, ret;	
	unsigned int idx, pio_offset;
	pthread_mutexattr_t mutex_attr;

	/* Check if it's already mmaped */
	if (at91reg_base_addr != NULL){

		fprintf(stderr, "AT91REG already mmap, userspace can only mmap one instance!!!\n");
		return -1;
	}

	/* Clear data structure */
	bzero(reg, sizeof(AT91_SCR));

	/* Set pthread mutex have error checking make sure didnot occur deadlock */
	if ((ret = pthread_mutexattr_settype(&mutex_attr,  PTHREAD_MUTEX_ERRORCHECK_NP))){
		fprintf(stderr, "Set thread mutex attribute as error checking error:%s\n", strerror(ret));
		return -1;	
	}	
	
	/* Init mutex lock */
	if ((ret = pthread_mutex_init(&reg->lock.pmc, &mutex_attr))){
		fprintf(stderr, "Init PMC resources mutex error:%s\n", strerror(ret));
		return -1;
	}

	for (idx = AT91_PIO_START; idx < AT91_PIO_END; idx++){

		if ((ret = pthread_mutex_init(&reg->lock.pio[idx], &mutex_attr))){

			fprintf(stderr, "Init PIO[%c] resources mutex error:%s\n", (char)('A' + idx), strerror(ret));
			return -1;
		}
	}

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

	/* GPIO resources init */
	for (idx = AT91_PIO_START, pio_offset = AT91_PIO_BASE; idx < AT91_PIO_END;  idx++, pio_offset += AT91_PIO_SIZE){

		reg->pio[idx]	=	(P_AT91_PIO)(at91reg_base_addr + pio_offset);
	}

	/* PMC resources init */
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

	/* Clear at91reg_base_addr */
	at91reg_base_addr = NULL;

	return 0;
}

