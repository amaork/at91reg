#ifndef	_AT91REG_API_H_
#define _AT91REG_API_H_

/* GPIO */
enum AT91_PIO{AT91_PIO_A, AT91_PIO_B, AT91_PIO_C, AT91_PIO_NUM};

/* Pullup */
enum AT91_PIO_OPER{CLR_OPER, SET_OPER};
enum AT91_PIO_PULLUP{DIS_PULLUP, EN_PULLUP};
enum AT91_PIO_FILTER{DIS_FILTER, EN_FILTER};
enum AT91_PIO_MULTID{DIS_MULTID, EN_MULTID};

/* Init and exit */
int at91reg_init(const char* device_name);
int at91reg_exit(void);


/* GPIO operating */
int gpio_set_pin(unsigned int port, unsigned int pin);
int gpio_clr_pin(unsigned int port, unsigned int pin);
int gpio_get_pin(unsigned int port, unsigned int pin, unsigned int *data);
int gpio_get_pin_desc(unsigned int port, unsigned int pin);

int gpio_pin_oper(unsigned int port, unsigned int pin, unsigned int oper);

int gpio_set_as_per_a(unsigned int port, unsigned int pin,  int pull_up);
int gpio_set_as_per_b(unsigned int port, unsigned int pin,  int pull_up);
int gpio_set_as_input(unsigned int port, unsigned int pin,  int pull_up, int filter);
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
