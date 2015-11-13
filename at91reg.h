#ifndef	_AT91REG_H_
#define _AT91REG_H_

#include <pthread.h>
#include "at91reg_api.h"

/* Register oper */
enum AT91_REG_OPER{READ_OPER, WRITE_OPER};

/* GPIO Inout */
enum AT91_PIO_IO{AT91_PIO_IN = 'I', AT91_PIO_OUT = 'O'};

/* Peripheral id */
enum AT91_PIO_ID{PIOA_PER_ID = 2, PIOB_PER_ID, PIOC_PER_ID};

/* Peripheral function */
enum AT91_PIO_PER{AT91_PIO_PERA = 'A', AT91_PIO_PERB = 'B'};


/* PIO index start and end */
#define AT91_PIO_START		0
#define AT91_PIO_END		3
#define IS_VALID_PIN(x)		((x) >= 0 && (x) < 32)
#define IS_VALID_PORT(x)	((x) >= (AT91_PIO_START) && (x) < (AT91_PIO_END))



#define PER_ID_START		0
#define PER_ID_END			31
#define IS_VALID_PID(x)		((x) >= (PER_ID_START) && (x) < (PER_ID_END))

/* PIO mmap base and size */
#define	AT91_PIO_BASE		0x400
#define AT91_PIO_SIZE		0x200

/* Power manager offset */
#define AT91_PMC_OFFSET		0xc00

/* Mmap size */
#define AT91_MMAP_SIZE		0x1000

typedef volatile unsigned int AT91_REG;


/* AT91 System Controller Register  */
/*
**	AT91 Parallel Input Output Controller 
*/

#define	GPIO_PER	1
#define GPIO_PDR	2
#define	GPIO_PSR	3

#define GPIO_OER	4
#define GPIO_ODR	5
#define GPIO_OSR	6

#define GPIO_IFER	7
#define GPIO_IFDR	8
#define GPIO_IFSR	9

#define GPIO_SODR	10
#define GPIO_CODR	11

#define GPIO_ODSR	12
#define GPIO_PDSR	13

#define	GPIO_IER	14
#define GPIO_IDR	15
#define GPIO_IMR	16
#define GPIO_ISR	17

#define GPIO_MDER	18
#define GPIO_MDDR	19
#define GPIO_MDSR	20

#define GPIO_PUDR	21
#define GPIO_PUER	22
#define GPIO_PUSR	23

#define GPIO_ASR	24
#define GPIO_BSR	25
#define GPIO_ABSR	26

#define GPIO_OWER	27
#define GPIO_OWDR	28
#define GPIO_OWSR	29

#define AT91_GPIOREG_START	1
#define AT91_GPIOREG_END		30
#define IS_VALID_GPIOREG(x)	((x) >= (AT91_GPIOREG_START) && (x) < (AT91_GPIOREG_END))

typedef struct PIO {
	AT91_REG	 PIO_PER;	// PIO Enable Register
	AT91_REG	 PIO_PDR;	// PIO Disable Register
	AT91_REG	 PIO_PSR;	// PIO Status Register
	AT91_REG	 Reserved0[1];	// 
	AT91_REG	 PIO_OER;	// Output Enable Register
	AT91_REG	 PIO_ODR;	// Output Disable Registerr
	AT91_REG	 PIO_OSR;	// Output Status Register
	AT91_REG	 Reserved1[1];	// 
	AT91_REG	 PIO_IFER;	// Input Filter Enable Register
	AT91_REG	 PIO_IFDR;	// Input Filter Disable Register
	AT91_REG	 PIO_IFSR;	// Input Filter Status Register
	AT91_REG	 Reserved2[1];	// 
	AT91_REG	 PIO_SODR;	// Set Output Data Register
	AT91_REG	 PIO_CODR;	// Clear Output Data Register
	AT91_REG	 PIO_ODSR;	// Output Data Status Register
	AT91_REG	 PIO_PDSR;	// Pin Data Status Register
	AT91_REG	 PIO_IER;	// Interrupt Enable Register
	AT91_REG	 PIO_IDR;	// Interrupt Disable Register
	AT91_REG	 PIO_IMR;	// Interrupt Mask Register
	AT91_REG	 PIO_ISR;	// Interrupt Status Register
	AT91_REG	 PIO_MDER;	// Multi-driver Enable Register
	AT91_REG	 PIO_MDDR;	// Multi-driver Disable Register
	AT91_REG	 PIO_MDSR;	// Multi-driver Status Register
	AT91_REG	 Reserved3[1];	// 
	AT91_REG	 PIO_PUDR;	// Pull-up Disable Register
	AT91_REG	 PIO_PUER;	// Pull-up Enable Register
	AT91_REG	 PIO_PUSR;	// Pull-up Status Register
	AT91_REG	 Reserved4[1];	// 
	AT91_REG	 PIO_ASR;	// Select A Register
	AT91_REG	 PIO_BSR;	// Select B Register
	AT91_REG	 PIO_ABSR;	// AB Select Status Register
	AT91_REG	 Reserved5[9];	// 
	AT91_REG	 PIO_OWER;	// Output Write Enable Register
	AT91_REG	 PIO_OWDR;	// Output Write Disable Register
	AT91_REG	 PIO_OWSR;	// Output Write Status Register
}AT91_PIO, *P_AT91_PIO;


/*
**	AT91 Power Management Controller
**	Block size: 512
*/

#define PMCR_SCER	1
#define PMCR_SCDR	2
#define PMCR_SCSR	3

#define PMCR_PCER	4
#define PMCR_PCDR	5
#define PMCR_PCSR	6

#define PMCR_CKGR_MOR	7
#define PMCR_CKGR_MCFR	8
#define PMCR_CKGR_PLLAR	9
#define PMCR_CKGR_PLLBR	10

#define PMCR_MCKR		11
#define PMCR_PCK0		12
#define PMCR_PCK1		13

#define PMCR_IER		14
#define PMCR_IDR		15
#define PMCR_SR			16
#define PMCR_IMR		17

#define PMCR_PLLICPR	18

#define AT91_PMCREG_START	1
#define AT91_PMCREG_END		19
#define IS_VALID_PMCREG(x)	((x) >= (AT91_PMCREG_START) && (x) < (AT91_PMCREG_END))

typedef struct PMC {
	AT91_REG	 PMC_SCER; 	// System Clock Enable Register
	AT91_REG	 PMC_SCDR; 	// System Clock Disable Register
	AT91_REG	 PMC_SCSR; 	// System Clock Status Register
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 PMC_PCER; 	// Peripheral Clock Enable Register
	AT91_REG	 PMC_PCDR; 	// Peripheral Clock Disable Register
	AT91_REG	 PMC_PCSR; 	// Peripheral Clock Status Register
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 PMC_MOR; 	// Main Oscillator Register
	AT91_REG	 PMC_MCFR; 	// Main Clock  Frequency Register
	AT91_REG	 PMC_PLLAR; 	// PLL A Register
	AT91_REG	 PMC_PLLBR; 	// PLL B Register
	AT91_REG	 PMC_MCKR; 	// Master Clock Register
	AT91_REG	 Reserved2[2]; 	// 
	AT91_REG	 PMC_PCK0; 	// Programmable Clock Register
	AT91_REG	 PMC_PCK1;	
	AT91_REG	 Reserved3[6];
	AT91_REG	 PMC_IER; 	// Interrupt Enable Register
	AT91_REG	 PMC_IDR; 	// Interrupt Disable Register
	AT91_REG	 PMC_SR; 	// Status Register
	AT91_REG	 PMC_IMR; 	// Interrupt Mask Register
	AT91_REG	 Reserved4[4];
	AT91_REG	 PMC_PLLICPR;// PLL Charge pump Current register
}AT91_PMC, *P_AT91_PMC;


/*
**	AT91 System controller register group
**
*/
typedef struct{

	/* Resources */
	P_AT91_PMC	pmc;
	P_AT91_PIO	pio[AT91_PIO_NUM];
	
	/* Mutex lock */
	struct{
	
		pthread_mutex_t pmc;
		pthread_mutex_t pio[AT91_PIO_NUM];

	}lock;

	/* Init flags */
	volatile unsigned int init;
}AT91_SCR, *P_AT91_SCR;

/*
**	Functions declaration
*/

#endif
