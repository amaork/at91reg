#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <strings.h>
#include "at91reg_api.h"
#include "lock.h"

P_AT91_SCR __at91reg = NULL;
static void *at91reg_base_addr = NULL;
extern int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int kind);


/**********************************************************************************
**	@brief	:	map at91 system controller register to userspace 
**	@return	:	sucess return 0, failed return -1
**********************************************************************************/
int at91reg_init(void)
{
	int fd, ret;	
	unsigned int idx, pio_offset;
	pthread_mutexattr_t mutex_attr;

	/* Check if it's already mmaped */
	if (at91reg_base_addr != NULL){

		fprintf(stderr, "AT91REG already mmap, userspace can only mmap one instance!!!\n");
		goto out;
	}

	/* Malloc space for AT91_SRC data structure */
	if ((__at91reg = (P_AT91_SCR)calloc(sizeof(AT91_SCR), 1)) == NULL){

		fprintf(stderr, "Malloc space for AT91REG error:%s\n", strerror(errno));
		goto out;
	}

	/* Set pthread mutex have error checking make sure didnot occur deadlock */
	if ((ret = pthread_mutexattr_settype(&mutex_attr,  PTHREAD_MUTEX_ERRORCHECK_NP))){
		fprintf(stderr, "Set thread mutex attribute as error checking error:%s\n", strerror(ret));
		goto out1;
	}	
	
	/* Init mutex lock */
	if ((ret = pthread_mutex_init(&__at91reg->lock.pmc, &mutex_attr))){
		fprintf(stderr, "Init PMC resources mutex error:%s\n", strerror(ret));
		goto out1;
	}

	for (idx = AT91_PIO_START; idx < AT91_PIO_END; idx++){

		if ((ret = pthread_mutex_init(&__at91reg->lock.pio[idx], &mutex_attr))){

			fprintf(stderr, "Init PIO[%c] resources mutex error:%s\n", (char)('A' + idx), strerror(ret));
			goto out1;
		}
	}

	/* Open at91reg device */
	if ((fd = open(AT91_REG_DEVICE, O_RDWR)) == -1){

		perror("Open at91reg device error:");
		goto out1;
	}

	/* Mmap at91reg to userspace */	
	if ((at91reg_base_addr = (mmap(NULL, AT91_MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0))) == MAP_FAILED){

		perror("Mmap at91reg device error:");
		goto out2;
	}

	/* GPIO resources init */
	for (idx = AT91_PIO_START, pio_offset = AT91_PIO_BASE; idx < AT91_PIO_END;  idx++, pio_offset += AT91_PIO_SIZE){

		__at91reg->pio[idx]	=	(P_AT91_PIO)(at91reg_base_addr + pio_offset);
	}

	/* PMC resources init */
	__at91reg->pmc   = (P_AT91_PMC)(at91reg_base_addr + AT91_PMC_OFFSET);

	/* Set init flags */
	__at91reg->init = 1;

	/* After mmap close device */
	close(fd);

	return 0;

	/* Error process */
	out2:
		
		close(fd);		

	out1:

		if (__at91reg){

			free(__at91reg);
			__at91reg = NULL;
		}

	out:

		return -1;
}

/**********************************************************************************
**	@brief	:	unmap at91 system controller register form userspace
**********************************************************************************/
int at91reg_exit(void)
{
	/* Unmap at91 system controller register */
	if (munmap(at91reg_base_addr, AT91_MMAP_SIZE) == -1){

		perror("Unmap at91reg device error:");
		return -1;
	}	

	/* Clear at91reg_base_addr */
	at91reg_base_addr = NULL;

	/* Free space */
	if (__at91reg){

		free(__at91reg);
		__at91reg = NULL;
	}

	return 0;
}



