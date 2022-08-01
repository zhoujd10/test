#include "common.h"
#include "pit.h"

/*************************************************************************
*  �������ƣ�PIT_Init
*  ����˵������ʼ���ж϶�ʱ��
*  �������أ���
*  ����˵����u8Channel_No��PITͨ���˿ں�
*           cn  ����ʱ��ʱ��
*  for example     PIT_Init(PIT_CHANNEL0,5*BUS_CLK_KHZ);
*************************************************************************/
void PIT_Init(uint8_t u8Channel_No, uint32_t cn)
{  
    SIM->SCGC |= SIM_SCGC_PIT_MASK;     /*!< enable clock to PIT */
    
    PIT->MCR &= ~PIT_MCR_MDIS_MASK;    
    PIT->CHANNEL[u8Channel_No].LDVAL = cn ;//u32loadvalue;   //��ʼ��ʱ��                                  
    PIT->CHANNEL[u8Channel_No].TCTRL |= PIT_TCTRL_TIE_MASK;  
    PIT->CHANNEL[u8Channel_No].TCTRL |= PIT_TCTRL_TEN_MASK;
    PIT->CHANNEL[u8Channel_No].TFLG  |= PIT_TFLG_TIF_MASK;
    if (u8Channel_No)
    {  
      NVIC_EnableIRQ(PIT_CH1_IRQn);             
    }
    else
    {  
      NVIC_EnableIRQ(PIT_CH0_IRQn);
    }
    
}





   


