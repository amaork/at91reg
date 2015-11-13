#include "at91reg.h"
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

		__at91reg.pmc->PMC_PCER |=	(1 << per_id);
	}
	/* Disable peripheral */
	else{

		__at91reg.pmc->PMC_PCDR |=	(1 << per_id);
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
	st = (__at91reg.pmc->PMC_PCSR & (1 << per_id)) >> per_id;
	
	/* Unlock pmc */	
	UNLOCK_PMC();

	return st;		
}

/**********************************************************************************
**	@brief	:	read/write power managerment controller register
**	#reg	:	which register will r/w PMCR_XXXX
**	#rw		:	READ_OPER or WRITE_OPER
**	#data	:	r/w data
**	@return	:	success return 0, failed return -1
**********************************************************************************/
int pmc_raw_rw(unsigned int reg, unsigned int rw, unsigned int *data)
{
	int ret = 0;

	/* Check register */
	CHECK_PMC_REG(reg);

	/* Lock pmc */
	LOCK_PMC();

	/* Read */
	if (rw == READ_OPER){

		switch (reg){
	
			case	PMCR_SCSR		:	*data = __at91reg.pmc->PMC_SCSR;break;	

			case	PMCR_PCSR		:	*data = __at91reg.pmc->PMC_PCSR;break;	

			case	PMCR_CKGR_MOR	:	*data = __at91reg.pmc->PMC_MOR;break;	
			case	PMCR_CKGR_MCFR	:	*data = __at91reg.pmc->PMC_MCFR;break;	
			case	PMCR_CKGR_PLLAR	:	*data = __at91reg.pmc->PMC_PLLAR;break;	
			case	PMCR_CKGR_PLLBR	:	*data = __at91reg.pmc->PMC_PLLBR;break;	

			case	PMCR_MCKR		:	*data = __at91reg.pmc->PMC_MCKR;break;	
			case	PMCR_PCK0		:	*data = __at91reg.pmc->PMC_PCK0;break;	
			case	PMCR_PCK1		:	*data = __at91reg.pmc->PMC_PCK1;break;	

			case	PMCR_SR			:	*data = __at91reg.pmc->PMC_SR;break;	
			case	PMCR_IMR		:	*data = __at91reg.pmc->PMC_IMR;break;	
			
			default	:	fprintf(stderr, "This register[%u] is write-only!\n", reg); ret = -1;break;
		}

	}
	/* Write */
	else{
		
		switch (reg){
	
			case	PMCR_SCER		:	__at91reg.pmc->PMC_SCER	|=	*data;break;	
			case	PMCR_SCDR		:	__at91reg.pmc->PMC_SCDR	|=	*data;break;	

			case	PMCR_PCER		:	__at91reg.pmc->PMC_PCER	|=	*data;break;	
			case	PMCR_PCDR		:	__at91reg.pmc->PMC_PCDR	|=	*data;break;	

			case	PMCR_CKGR_MOR	:	__at91reg.pmc->PMC_MOR		|=	*data;break;	
			case	PMCR_CKGR_PLLAR	:	__at91reg.pmc->PMC_PLLAR	|=	*data;break;	
			case	PMCR_CKGR_PLLBR	:	__at91reg.pmc->PMC_PLLBR	|=	*data;break;	

			case	PMCR_MCKR		:	__at91reg.pmc->PMC_MCKR	|=	*data;break;	
			case	PMCR_PCK0		:	__at91reg.pmc->PMC_PCK0	|=	*data;break;	
			case	PMCR_PCK1		:	__at91reg.pmc->PMC_PCK1	|=	*data;break;	

			case	PMCR_IER		:	__at91reg.pmc->PMC_IER		|=	*data;break;	
			case	PMCR_IDR		:	__at91reg.pmc->PMC_IDR		|=	*data;break;	

			case	PMCR_PLLICPR	:	__at91reg.pmc->PMC_PLLICPR	|=	*data;break;	

			default	:	fprintf(stderr, "This register[%u] is read-only!\n", reg); ret = -1;break;
		}
	}


	/* Unlock pmc */
	UNLOCK_PMC();

	return ret;	
}

/**********************************************************************************
**	@brief	:	read pmc register
**	#data	:	register read  result will save to #data
**	@return	:	success return 0, failed return -1
**********************************************************************************/
int pmc_raw_r_scsr(unsigned int *data)
{
	return pmc_raw_rw(PMCR_SCSR, READ_OPER, data);
}

int pmc_raw_r_pcsr(unsigned int *data)
{
	return pmc_raw_rw(PMCR_PCSR, READ_OPER, data);
}

int pmc_raw_r_ckgr_mor(unsigned int *data)
{
	return pmc_raw_rw(PMCR_CKGR_MOR, READ_OPER, data);
}

int pmc_raw_r_ckgr_mcfr(unsigned int *data)
{
	return pmc_raw_rw(PMCR_CKGR_MCFR, READ_OPER, data);
}

int pmc_raw_r_ckgr_pllar(unsigned int *data)
{
	return pmc_raw_rw(PMCR_CKGR_PLLAR, READ_OPER, data);
}

int pmc_raw_r_ckgr_pllbr(unsigned int *data)
{
	return pmc_raw_rw(PMCR_CKGR_PLLBR, READ_OPER, data);
}

int pmc_raw_r_mckr(unsigned int *data)
{
	return pmc_raw_rw(PMCR_MCKR, READ_OPER, data);
}

int pmc_raw_r_pck0(unsigned int *data)
{
	return pmc_raw_rw(PMCR_PCK0, READ_OPER, data);
}

int pmc_raw_r_pck1(unsigned int *data)
{
	return pmc_raw_rw(PMCR_PCK1, READ_OPER, data);
}

int pmc_raw_r_sr(unsigned int *data)
{
	return pmc_raw_rw(PMCR_SR, READ_OPER, data);
}

int pmc_raw_r_imr(unsigned int *data)
{
	return pmc_raw_rw(PMCR_IMR, READ_OPER, data);
}
/**********************************************************************************
**	@brief	:	write pmc register
**	#data	:	will write to register data
**	@return	:	success return 0, failed return -1
**********************************************************************************/
int pmc_raw_w_scer(unsigned int data)
{
	return pmc_raw_rw(PMCR_SCER, WRITE_OPER, &data);
}

int pmc_raw_w_scdr(unsigned int data)
{
	return pmc_raw_rw(PMCR_SCDR, WRITE_OPER, &data);
}

int pmc_raw_w_pcer(unsigned int data)
{
	return pmc_raw_rw(PMCR_PCER, WRITE_OPER, &data);
}

int pmc_raw_w_pcdr(unsigned int data)
{
	return pmc_raw_rw(PMCR_PCDR, WRITE_OPER, &data);
}

int pmc_raw_w_ckgr_mor(unsigned int data)
{
	return pmc_raw_rw(PMCR_CKGR_MOR, WRITE_OPER, &data);
}

int pmc_raw_w_ckgr_pllar(unsigned int data)
{
	return pmc_raw_rw(PMCR_CKGR_PLLAR, WRITE_OPER, &data);
}

int pmc_raw_w_ckgr_pllbr(unsigned int data)
{
	return pmc_raw_rw(PMCR_CKGR_PLLBR, WRITE_OPER, &data);
}

int pmc_raw_w_mckr(unsigned int data)
{
	return pmc_raw_rw(PMCR_MCKR, WRITE_OPER, &data);
}

int pmc_raw_w_pck0(unsigned int data)
{
	return pmc_raw_rw(PMCR_PCK0, WRITE_OPER, &data);
}

int pmc_raw_w_pck1(unsigned int data)
{
	return pmc_raw_rw(PMCR_PCK1, WRITE_OPER, &data);
}

int pmc_raw_w_ier(unsigned int data)
{
	return pmc_raw_rw(PMCR_IER, WRITE_OPER, &data);
}

int pmc_raw_w_idr(unsigned int data)
{
	return pmc_raw_rw(PMCR_IDR, WRITE_OPER, &data);
}

int pmc_raw_w_pllicpr(unsigned int data)
{
	return pmc_raw_rw(PMCR_PLLICPR, WRITE_OPER, &data);
}
