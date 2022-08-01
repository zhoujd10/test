#include "headfile.h"

//陀螺仪接口   PTB0
//加速度计接口 PTB1


uint16 gyro = 0, acc = 0;

void main(void)
{
    DisableInterrupts ;                  //禁止中断
    ADC_Init(ADC_CHANNEL_AD4,ADC_12BIT);
    ADC_Init(ADC_CHANNEL_AD5,ADC_12BIT);
    EnableInterrupts;
    
    while(1)
    {
        gyro = adc_once(ADC_CHANNEL_AD4,ADC_12BIT);
        acc = adc_once(ADC_CHANNEL_AD5,ADC_12BIT);
    }
}


  
