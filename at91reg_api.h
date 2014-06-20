#ifndef	_AT91REG_H_
#define _AT91REG_H_

#include <pthread.h>

#define READ_OPER			0
#define WRITE_OPER			1

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
int gpio_get_pin(unsigned int port, unsigned int pin, unsigned int *data);
int gpio_get_pin_desc(unsigned int port, unsigned int pin);

int gpio_pin_oper(unsigned int port, unsigned int pin, unsigned int oper);

int gpio_set_as_per_a(unsigned int port, unsigned int pin, int pull_up);
int gpio_set_as_per_b(unsigned int port, unsigned int pin, int pull_up);
int gpio_set_as_input(unsigned int port, unsigned int pin, int pull_up, int filter);
int gpio_set_as_output(unsigned int port, unsigned int pin, int pull_up, int open_drain);


int gpio_sync_write(unsigned int port, unsigned int pin_mask, unsigned int data);
int gpio_set_as_sync_output(unsigned int port, unsigned int pin_mask, int pull_up, int open_drain);


/* Raw read/write */
int gpio_raw_rw(unsigned int port, unsigned int reg, unsigned int rw, unsigned int *data);

int gpio_raw_r_psr(unsigned int port, unsigned int *data);
int gpio_raw_r_osr(unsigned int port, unsigned int *data);
int gpio_raw_r_ifsr(unsigned int port, unsigned int *data);
int gpio_raw_r_odsr(unsigned int port, unsigned int *data);
int gpio_raw_r_prsr(unsigned int port, unsigned int *data);
int gpio_raw_r_imr(unsigned int port, unsigned int *data);
int gpio_raw_r_isr(unsigned int port, unsigned int *data);
int gpio_raw_r_mdsr(unsigned int port, unsigned int *data);
int gpio_raw_r_pusr(unsigned int port, unsigned int *data);
int gpio_raw_r_absr(unsigned int port, unsigned int *data);
int gpio_raw_r_owsr(unsigned int port, unsigned int *data);


int gpio_raw_w_per(unsigned int port, unsigned int data);
int gpio_raw_w_pdr(unsigned int port, unsigned int data);

int gpio_raw_w_oer(unsigned int port, unsigned int data);
int gpio_raw_w_odr(unsigned int port, unsigned int data);

int gpio_raw_w_ifer(unsigned int port, unsigned int data);
int gpio_raw_w_ifdr(unsigned int port, unsigned int data);

int gpio_raw_w_sodr(unsigned int port, unsigned int data);
int gpio_raw_w_codr(unsigned int port, unsigned int data);
int gpio_raw_w_odsr(unsigned int port, unsigned int data);

int gpio_raw_w_ier(unsigned int port, unsigned int data);
int gpio_raw_w_idr(unsigned int port, unsigned int data);

int gpio_raw_w_mder(unsigned int port, unsigned int data);
int gpio_raw_w_mddr(unsigned int port, unsigned int data);

int gpio_raw_w_pudr(unsigned int port, unsigned int data);
int gpio_raw_w_puer(unsigned int port, unsigned int data);

int gpio_raw_w_asr(unsigned int port, unsigned int data);
int gpio_raw_w_bsr(unsigned int port, unsigned int data);

int gpio_raw_w_ower(unsigned int port, unsigned int data);
int gpio_raw_w_owdr(unsigned int port, unsigned int data);

/* Power management controller */
int pmc_peripheral_status(unsigned int per_id);
int pmc_peripheral_endis(unsigned int per_id, unsigned int endis);

/* Raw read/write */
int pmc_raw_rw(unsigned int reg, unsigned int rw, unsigned int *data);

int pmc_raw_r_pcsr(unsigned int *data);
int pmc_raw_r_scsr(unsigned int *data);
int pmc_raw_r_ckgr_mor(unsigned int *data);
int pmc_raw_r_ckgr_mcfr(unsigned int *data);
int pmc_raw_r_ckgr_pllar(unsigned int *data);
int pmc_raw_r_ckgr_pllbr(unsigned int *data);
int pmc_raw_r_mckr(unsigned int *data);
int pmc_raw_r_pck0(unsigned int *data);
int pmc_raw_r_pck1(unsigned int *data);
int pmc_raw_r_sr(unsigned int *data);
int pmc_raw_r_imr(unsigned int *data);

int pmc_raw_w_scer(unsigned int data);
int pmc_raw_w_scdr(unsigned int data);
int pmc_raw_w_pcer(unsigned int data);
int pmc_raw_w_pcdr(unsigned int data);
int pmc_raw_w_ckgr_mor(unsigned int data);
int pmc_raw_w_ckgr_pllar(unsigned int data);
int pmc_raw_w_ckgr_pllbr(unsigned int data);
int pmc_raw_w_mckr(unsigned int data);
int pmc_raw_w_pck0(unsigned int data);
int pmc_raw_w_pck1(unsigned int data);
int pmc_raw_w_ier(unsigned int data);
int pmc_raw_w_idr(unsigned int data);
int pmc_raw_w_pllicpr(unsigned int data);

#endif
