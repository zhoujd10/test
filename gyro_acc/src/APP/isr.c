#include "isr.h"





int stime = 0;  //ϵͳʱ��
//��ʱ��0�жϺ���
void PIT0_ISR(void)
{
    PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;//����жϱ�־λ
    stime++;

}





//��ʱ��1�жϺ���
void PIT1_ISR(void)
{
    PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK;//����жϱ�־λ
  

}






//KBI0�жϺ���
void KBI0_Isr(void)	
{
  
     KBI0->SC |= KBI_SC_KBACK_MASK;       /* clear interrupt flag */
     KBI0->SC |= KBI_SC_RSTKBSP_MASK ;    //����жϱ�־λ

  

}






//KBI1�жϺ���
void KBI1_Isr(void)	
{
   
     KBI1->SC |= KBI_SC_KBACK_MASK;                /* clear interrupt flag */
     KBI1->SC |= KBI_SC_RSTKBSP_MASK ;             //����жϱ�־λ
}