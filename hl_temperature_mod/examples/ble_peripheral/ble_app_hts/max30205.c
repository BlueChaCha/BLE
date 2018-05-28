
#include "max30205.h"
#include "app_util_platform.h"
#include "nrf_drv_twi.h"
#include "nrf_gpio.h"
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

uint8_t max30205_dev_addr = MAX30205_DEV_ADDR;
static volatile bool m_xfer_done = false;
uint8_t max30205_dev_conf[2]={MAX30205_REG_CONF,0};
#define TWI_INSTANCE_ID     0
static bool max30205_wirte_data(uint8_t  address, uint8_t *data,uint8_t lenght) ;
static uint8_t max30205_read_byte(uint8_t address, uint8_t *p_read_byte,uint8_t length);
static uint32_t temper_data[16];
static const nrf_drv_twi_t max30205_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);
void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context);
///////////////////////////////////////////////////
///////////////////////////////////////////////////
void dev_max30205_uninit(void)
{
	nrf_drv_twi_uninit(&max30205_twi);
}

void dev_max30205_powerCfg(void)
{
    nrf_gpio_cfg(
        MAX30205_PWR_PIN,
        NRF_GPIO_PIN_DIR_OUTPUT,
        NRF_GPIO_PIN_INPUT_DISCONNECT,
        NRF_GPIO_PIN_NOPULL,
        NRF_GPIO_PIN_S0H1,
        NRF_GPIO_PIN_NOSENSE);
	
	 // nrf_gpio_pin_set(MAX30205_PWR_PIN);
	nrf_gpio_pin_clear(MAX30205_PWR_PIN);
}

void dev_max30205_init(void)
{

	
	ret_code_t err_code;
	
	 const nrf_drv_twi_config_t max30205_twi_config = {
       .scl                = MAX30205_SCL_PIN,
       .sda                = MAX30205_SDA_PIN,
       .frequency          = NRF_TWI_FREQ_400K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };
	 
	err_code = nrf_drv_twi_init(&max30205_twi, &max30205_twi_config, twi_handler, NULL);
  APP_ERROR_CHECK(err_code);

  nrf_drv_twi_enable(&max30205_twi);
//	
	temper_data[0]  = MAX30205_D00_VL;
	temper_data[1]  = MAX30205_D01_VL;
	temper_data[2]  = MAX30205_D02_VL;
	temper_data[3]  = MAX30205_D03_VL;
	temper_data[4]  = MAX30205_D04_VL;
	temper_data[5]  = MAX30205_D05_VL;
	temper_data[6]  = MAX30205_D06_VL;
	temper_data[7]  = MAX30205_D07_VL;
	temper_data[8]  = MAX30205_D08_VL;
	temper_data[9]  = MAX30205_D09_VL;
	temper_data[10] = MAX30205_D10_VL;
	temper_data[11] = MAX30205_D11_VL;
	temper_data[12] = MAX30205_D12_VL;
	temper_data[13] = MAX30205_D13_VL;
	temper_data[14] = MAX30205_D14_VL;
	//max30205_wirte_data(max30205_dev_conf[0],max30205_dev_conf,sizeof(max30205_dev_conf));
}
void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX)
            {
               
            }
            m_xfer_done = true;
            break;
        default:
            break;
    }
}
void dev_max30205_mode_set(MAX30205_CONFIG_INDEX index  ,uint8_t en)
{
	
	max30205_dev_conf[1] &= ~(1<<  index);
	max30205_dev_conf[1] |= (en << index);
	max30205_wirte_data(max30205_dev_conf[0],max30205_dev_conf,sizeof(max30205_dev_conf));
}
uint16_t data = 0;
unsigned int dev_max30205_read_temperature(void)
{

	uint8_t i =0;
	uint16_t temp =0;
	unsigned int temperature = 0;
	max30205_read_byte(MAX30205_REG_TEMP,(uint8_t*)&data,2);
		max30205_read_byte(MAX30205_REG_TEMP,(uint8_t*)&data,2);
	temp = (data & 0xFF)*256 +((data>>8) & 0xFF);
	for(i =0;i < 14;i ++)
	{
		if((temp >>i)&0x01)
			temperature += temper_data[i];
	}

	return temperature;
}

static bool max30205_wirte_data(uint8_t  address, uint8_t *data,uint8_t lenght) 
{
	return nrf_drv_twi_tx(&max30205_twi, MAX30205_DEV_ADDR, data, lenght,false);
}
uint8_t max30205_read_byte(uint8_t address, uint8_t *p_read_byte,uint8_t length)
{
	ret_code_t err_code;
	m_xfer_done = false;
  nrf_drv_twi_tx(&max30205_twi,MAX30205_DEV_ADDR,&address,1,0);
	while(m_xfer_done== false);
  err_code = nrf_drv_twi_rx(&max30205_twi, MAX30205_DEV_ADDR, p_read_byte, length);
  APP_ERROR_CHECK(err_code);
	while(m_xfer_done== false);
	
	
	return err_code;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////


