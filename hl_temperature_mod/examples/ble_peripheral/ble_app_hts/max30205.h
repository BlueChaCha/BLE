#include "nrf_drv_twi.h"

#define MAX30205_DEV_ADDR          					(0x90>>1)

#define MAX30205_PWR_PIN 										6

#define MAX30205_REG_TEMP      							0x00
#define MAX30205_REG_CONF      							0x01
#define MAX30205_REG_THYST     							0x02
#define MAX30205_REG_TOS       							0x03

#define MAX30205_BUFFER_SIZE                2
#define MAX_PENDING_TRANSACTIONS    				5

#define MAX30205_INIT_TRANSFER_COUNT 				1


		
		

#define MAX30205_SCL_PIN                    8
#define MAX30205_SDA_PIN                    9







typedef enum
{
	MAX30205_SHUTDOWN   = 0,
	MAX30205_COMPARATOR = 1,
	MAX30205_POLARITY   = 2,
	MAX30205_FAULT_0    = 3,
	MAX30205_FAULT_1    = 4,
	MAX30205_FORMAT     = 5,
	MAX30205_TIMEOUT    = 6,
	MAX30205_ONE_SHOT   = 7,
}MAX30205_CONFIG_INDEX;

#define MAX30205_D00_VL     0
#define MAX30205_D01_VL     0
#define MAX30205_D02_VL     0
#define MAX30205_D03_VL     3
#define MAX30205_D04_VL     6
#define MAX30205_D05_VL     12
#define MAX30205_D06_VL     25
#define MAX30205_D07_VL     50
#define MAX30205_D08_VL     100
#define MAX30205_D09_VL     200
#define MAX30205_D10_VL     400
#define MAX30205_D11_VL     800
#define MAX30205_D12_VL     1600
#define MAX30205_D13_VL     3200
#define MAX30205_D14_VL     6400



#define MAX30258_MODE_OPEN      0
#define MAX30258_MODE_SHOUTDOWN 1


void dev_max30205_powerCfg(void);
void  dev_max30205_init(void);
void  dev_max30205_mode_set(MAX30205_CONFIG_INDEX index  ,uint8_t en);
unsigned int dev_max30205_read_temperature(void);
void dev_max30205_uninit(void);
