#ifndef	_AT91REG_H_
#define _AT91REG_H_

#include <pthread.h>

/* Macro */
#define AT91_PIO_NB			3
#define AT91_PIO_A			0
#define AT91_PIO_B			1
#define AT91_PIO_C			2

/* PIO index start and end */
#define AT91_PIO_START		0
#define AT91_PIO_END		3

/* PIO mmap base and size */
#define	AT91_PIO_BASE		0x400
#define AT91_PIO_SIZE		0x200

/* Power manager offset */
#define AT91_PMC_OFFSET		0xc00

/* Mmap size */
#define AT91_MMAP_SIZE		0x1000


#define AT91_REG_DEVICE		"/dev/at91reg"

typedef volatile unsigned int AT91_REG;


/* AT91 System Controller Register  */

/*
**	AT91 Parallel Input Output Controller 
**	Block size : 512 bytes
*/
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
	AT91_REG	 PIO_PPUDR;	// Pull-up Disable Register
	AT91_REG	 PIO_PPUER;	// Pull-up Enable Register
	AT91_REG	 PIO_PPUSR;	// Pull-up Status Register
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
	AT91_REG	 Reserved2[3]; 	// 
	AT91_REG	 PMC_PCKR[8]; 	// Programmable Clock Register
	AT91_REG	 PMC_IER; 	// Interrupt Enable Register
	AT91_REG	 PMC_IDR; 	// Interrupt Disable Register
	AT91_REG	 PMC_SR; 	// Status Register
	AT91_REG	 PMC_IMR; 	// Interrupt Mask Register
}AT91_PMC, *P_AT91_PMC;


/*
**	AT91 System controller register group
**
*/
typedef struct{

	/* Resources */
	P_AT91_PMC	pmc;
	P_AT91_PIO	pio[AT91_PIO_NB];
	
	/* Mutex lock */
	struct{
	
		pthread_mutex_t pmc;
		pthread_mutex_t pio[AT91_PIO_NB];

	}lock;
}AT91_SCR, *P_AT91_SCR;


/*
**	Functions declaration
*/

int at91reg_mmap(P_AT91_SCR reg);
int at91reg_unmap(void);


#endif
