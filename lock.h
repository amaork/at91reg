#ifndef	_LOCK_H_
#define _LOCK_H_

#include <errno.h>
#include <stdio.h>
#include <string.h>

/* Normal user please do not refercrence this var */
extern AT91_SCR __at91reg;

#define LOCK_PMC()		do{ \
							if (__at91reg.init == 0){\
								fprintf(stderr, "%s[%s] --> [%d] --> AT91reg module uninit!!!\n", __FILE__,__func__, __LINE__);\
								return -1;\
							}\
							if (pthread_mutex_lock(&__at91reg.lock.pmc)){ \
								fprintf(stderr, "%s[%s] --> [%d] --> Lock pmc error:%s\n", __FILE__,__func__, __LINE__, strerror(errno));\
								return -1;\
							}\
						}while(0)


#define UNLOCK_PMC()	do{ \
							if (pthread_mutex_unlock(&__at91reg.lock.pmc)){ \
								fprintf(stderr, "%s[%s] --> [%d] --> Unlock pmc error:%s\n", __FILE__, __func__, __LINE__, strerror(errno));\
								return -1;\
							}\
						}while(0)


#define LOCK_GPIO(x)	do{ \
							if (__at91reg.init == 0){\
								fprintf(stderr, "%s[%s] --> [%d] --> AT91reg module uninit!!!\n", __FILE__,__func__, __LINE__);\
								return -1;\
							}\
							if (pthread_mutex_lock(&__at91reg.lock.pio[(x)])){ \
								fprintf(stderr, "%s[%s] --> [%d] --> Lock pio error:%s\n", __FILE__,__func__, __LINE__, strerror(errno));\
								return -1;\
							}\
						}while(0)


#define UNLOCK_GPIO(x)	do{ \
							if (pthread_mutex_unlock(&__at91reg.lock.pio[(x)])){\
								fprintf(stderr, "%s[%s] --> [%d] --> Unlock pio error:%s\n", __FILE__, __func__, __LINE__, strerror(errno));\
								return -1;\
							}\
						}while(0)


#define CHECK_GPIO_PORT(x)	do{ \
								if (!IS_VALID_PORT(x)){\
									fprintf(stderr, "GPIO Port[%u] is invalid!\n", x);\
									return -1;\
								}\
							}while(0)

#define CHECK_GPIO_PIN(x)	do{ \
								if (!IS_VALID_PIN(x)){\
									fprintf(stderr, "GPIO Pin[%u] is invalid!\n", x);\
									return -1;\
								}\
							}while(0)

#define CHECK_GPIO_REG(x)	do{ \
								if (!IS_VALID_GPIOREG(x)){\
									fprintf(stderr, "GPIO Reg[%u] is invalid!\n", x);\
									return -1;\
								}\
							}while(0)

#define CHECK_PER_ID(x)		do{ \
								if (!IS_VALID_PID(x)){\
									fprintf(stderr, "Peripheral id[%d] is invalid!\n", x);\
									return -1;\
								}\
							}while(0)

#define CHECK_PMC_REG(x)	do{ \
								if (!IS_VALID_PMCREG(x)){\
									fprintf(stderr, "PMC register id[%d] is invalid!\n", x);\
									return -1;\
								}\
							}while(0)

#endif
