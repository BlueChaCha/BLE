
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf_drv_saadc.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "battery.h"

static uint32_t battery_tbl[11] = {4800,4700,4600,4500,4400,4300,4200,4100,4000,3900,3800};

#define BATTERY_IN_BUFFER 4
#define BATTERY_OUT_PIN   3
static nrf_saadc_value_t       m_buffer_pool[BATTERY_IN_BUFFER];
static uint32_t battery_lev = 0,battery_val;
uint8_t battery_get(void)
{
//	if(battery_val>=battery_tbl[0])
//		battery_lev = 100;
//	else if(battery_val>=battery_tbl[1])
//		battery_lev = 95;
//	else if(battery_val>=battery_tbl[2])
//		battery_lev = 90;
//	else if(battery_val>=battery_tbl[3])
//		battery_lev = 80;
//	else if(battery_val>=battery_tbl[4])
//		battery_lev = 70;
//	else if(battery_val>=battery_tbl[5])
//		battery_lev = 60;
//	else if(battery_val>=battery_tbl[6])
//		battery_lev = 50;
//	else if(battery_val>=battery_tbl[7])
//		battery_lev = 40;
//	else if(battery_val>=battery_tbl[8])
//		battery_lev = 30;
//	else if(battery_val>=battery_tbl[9])
//		battery_lev = 20;
//	else if(battery_val>=battery_tbl[10])
//		battery_lev = 10;
//	else
//		battery_lev = 5;
if(battery_val<=330)
{
	battery_val=10;
}
else if(battery_val<=350)
{
	battery_val=20;
}
else if(battery_val<=370)
{
	battery_val=30;
}
else if(battery_val<=375)
{
	battery_val=40;
}
else if(battery_val<=380)
{
	battery_val=50;
}
else if(battery_val<=385)
{
	battery_val=60;
}
else if(battery_val<=390)
{
	battery_val=70;
}
else if(battery_val<=395)
{
	battery_val=80;
}
else if(battery_val<=400)
{
	battery_val=90;
}
else if(battery_val>405)
{
	battery_val=100;
}
	return (battery_val & 0xff);
}
static void battery_callback(nrf_drv_saadc_evt_t const * p_event)
{
		ret_code_t err_code;
//	  nrf_saadc_value_t adc_result;
	  uint32_t temp=0,i =0;
    if (p_event->type == NRF_DRV_SAADC_EVT_DONE)
    {
			err_code = nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, BATTERY_IN_BUFFER);
			err_code = err_code;
			for( i =0;i < BATTERY_IN_BUFFER;i ++)
			{
				temp += (p_event->data.done.p_buffer[i]);
			}
			temp /= BATTERY_IN_BUFFER;
//			
//			temp *= 36;
			battery_val = 36*temp*20/1024;
			 nrf_gpio_pin_write(BATTERY_OUT_PIN,1);
			nrf_drv_saadc_uninit();
			NVIC_ClearPendingIRQ(SAADC_IRQn);
		//	nrf_saadc_task_trigger(NRF_SAADC_TASK_STOP);
    }
}

void battery_uninit()
{
	nrf_drv_saadc_uninit();
}
void battery_init()
{
	 ret_code_t err_code;
	
   err_code = nrf_drv_saadc_init(NULL, battery_callback);
//    APP_ERROR_CHECK(err_code);
	
		nrf_saadc_channel_config_t channel_config = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN0);
	//参考电压0.9，增益电压1.1，最大测量电压4.4，原来的电压3.3
	//  channel_config.reference =SAADC_CH_CONFIG_REFSEL_VDD1_4;
	//  channel_config.gain = SAADC_CH_CONFIG_GAIN_Gain1_3;
    err_code = nrf_drv_saadc_channel_init(0, &channel_config);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool,BATTERY_IN_BUFFER);
    APP_ERROR_CHECK(err_code);
    
		nrf_saadc_task_trigger(NRF_SAADC_TASK_START);
	
	  nrf_gpio_cfg_output(BATTERY_OUT_PIN);
	  nrf_gpio_pin_write(BATTERY_OUT_PIN,0);
}

void battery_close(){
	
		NRF_GPIOTE->CONFIG[2] = (GPIOTE_CONFIG_MODE_Disabled << GPIOTE_CONFIG_MODE_Pos);

		nrf_saadc_task_trigger(NRF_SAADC_TASK_STOP);

}

void battery_read(){
	  int i=0;
    battery_init();
 //   nrf_gpio_pin_write(BATTERY_OUT_PIN,0);
	  //nrf_drv_saadc_init(NULL, battery_callback);
	 
  //	nrf_saadc_task_trigger(NRF_SAADC_TASK_START);
	  nrf_delay_ms(50);
		for(i=0;i<BATTERY_IN_BUFFER;i++){
			
			nrf_delay_us(50);
			nrf_saadc_task_trigger(NRF_SAADC_TASK_SAMPLE );
		}
		
   // nrf_gpio_pin_write(BATTERY_OUT_PIN,1);
}

