#include "headfile.h"

//�����ǽӿ�   PTB0
//���ٶȼƽӿ� PTB1


uint16 gyro = 0, acc = 0;

void main(void)
{
    DisableInterrupts ;                  //��ֹ�ж�
    ADC_Init(ADC_CHANNEL_AD4,ADC_12BIT);
    ADC_Init(ADC_CHANNEL_AD5,ADC_12BIT);
    EnableInterrupts;
    
    while(1)
    {
        gyro = adc_once(ADC_CHANNEL_AD4,ADC_12BIT);
        acc = adc_once(ADC_CHANNEL_AD5,ADC_12BIT);
    }
}


  
