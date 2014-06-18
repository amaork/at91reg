#ifndef	_AT91REG_H_
#define _AT91REG_H_

#include <pthread.h>

/* Macro */
#define AT91_PIO_NB			3
#define AT91_PIO_A			0
#define AT91_PIO_B			1
#define AT91_PIO_C			2

#define AT91_PIO_PERA		'A'
#define	AT91_PIO_PERB		'B'
#define AT91_PIO_IN			'I'
#define AT91_PIO_OUT		'O'

/* PIO index start and end */
#define AT91_PIO_START		0
#define AT91_PIO_END		3
#define IS_VALID_PIN(x)		((x) >= 0 && (x) < 32)
#define IS_VALID_PORT(x)	((x) >= (AT91_PIO_START) && (x) < (AT91_PIO_END))


/* Peripheral id */
#define PIOA_PER_ID			2
#define PIOB_PER_ID			3
#define PIOC_PER_ID			4

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

	/* Init flags */
	volatile unsigned int init;
}AT91_SCR, *P_AT91_SCR;

/*
**	Functions declaration
*/


/* Init and exit */
int at91reg_init(void);
int at91reg_exit(void);


/* GPIO operating */
int gpio_set_pin(unsigned int port, unsigned int pin);
int gpio_clr_pin(unsigned int port, unsigned int pin);
int gpio_get_pin(unsigned int port, unsigned int pin);

int gpio_get_pin_desc(unsigned int port, unsigned int pin);

int gpio_pin_oper(unsigned int port, unsigned int pin, unsigned int oper);

int gpio_set_as_per_a(unsigned int port, unsigned int pin, int pull_up);
int gpio_set_as_per_b(unsigned int port, unsigned int pin, int pull_up);
int gpio_set_as_input(unsigned int port, unsigned int pin, int pull_up, int filter);
int gpio_set_as_output(unsigned int port, unsigned int pin, int pull_up, int open_drain);


/* Power management controller */
int pmc_peripheral_status(unsigned int per_id);
int pmc_peripheral_endis(unsigned int per_id, unsigned int endis);


#endif
