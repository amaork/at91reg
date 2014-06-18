#include "at91reg_api.h"
#include "lock.h"


/**********************************************************************************
**	@brief	:	enable or disable soc embedded peripheral clock
**	#per_id	:	operate which embedded peripheral, id refer to at91reg_api.h
**	#endis	:	zero disable #per_id specified peripheral, not zero enable 
**	@return	:	success return 0, fialed return -1
**********************************************************************************/
int pmc_peripheral_endis(unsigned int per_id, unsigned int endis)
{
	/* Check peripheral id */
	CHECK_PER_ID(per_id);

	/* Get pmc lock */
	LOCK_PMC();

	/* Enable peripheral */	
	if (endis){

		__at91reg->pmc->PMC_PCER |=	(1 << per_id);
	}
	/* Disable peripheral */
	else{

		__at91reg->pmc->PMC_PCDR |=	(1 << per_id);
	}

	/* Unlock pmc */
	UNLOCK_PMC();

	return 0;
}

/**********************************************************************************
**	@brief	:	check peripheral status
**	#per_id	:	which peripheral will check 
**	@return	:	enable return 1, disable return 0, faild return -1
**********************************************************************************/
int pmc_peripheral_status(unsigned int per_id)
{
	unsigned int st;

	/* Check peripheral id */
	CHECK_PER_ID(per_id);

	/* Get pmc lock */
	LOCK_PMC();

	/* Get status */
	st = (__at91reg->pmc->PMC_PCSR & (1 << per_id)) >> per_id;
	
	/* Unlock pmc */	
	UNLOCK_PMC();

	return st;		
}

