#include "common.h"
#include "kbi.h"

volatile KBI_Type * KBIx[2] = { KBI0,KBI1} ;

/*************************************************************************
*  �������ƣ�  KBI_Init
*  ����˵����  ��ʼ���ж�
*  �������أ�
*  ����˵����
*  for example KBI_Init(KBIX0, 29, KBI_FALLING_LOW);//PTD5
*************************************************************************/
void KBI_Init(KBIn_e kbix,uint8_t kbich,KBI_Edge RiFal)
{
  
  if(kbix == KBIX0 )
    {
        SIM->SCGC   |= SIM_SCGC_KBI0_MASK;             /* enable clock to KBI0 */\
        KBIx[kbix]->SC  &= ~KBI_SC_KBIE_MASK ;
        /****
        ��ʼ��IO
        *****/
        FGPIOA->PIDR  &= ~(1<<kbich);              /* enable GPIO input */    
        FGPIOA->PDDR  &= ~(1<<kbich); 
        if(RiFal) PORT->PUE0  &= ~(1<<kbich);
        else PORT->PUE0  |= (1<<kbich);
        
    }
    else if (kbix == KBIX1)
    {        
        SIM->SCGC   |= SIM_SCGC_KBI1_MASK;             /* enable clock to KBI1 */
        KBIx[kbix]->SC  &= ~KBI_SC_KBIE_MASK ;

        /****
        ��ʼ��IO
        *****/
        FGPIOB->PIDR  &= ~(1<<kbich);              /* enable GPIO input */    
        FGPIOB->PDDR  &= ~(1<<kbich); 
        if(RiFal) PORT->PUE1  &= ~(1<<kbich);
        else PORT->PUE1  |= (1<<kbich);

    }

  if(RiFal)
  {
    KBIx[kbix]->ES  |= (1<< kbich);
  }
  else
  {
    KBIx[kbix]->ES  &= ~(1<< kbich);
  }
  KBIx[kbix]->PE |= (1 << kbich) ;

  PORT->IOFLT0 |= PORT_IOFLT0_FLTDIV1(0) ;
  PORT->IOFLT0 |= PORT_IOFLT0_FLTKBI0(1) ;
  KBIx[kbix]->SC  = (0
                     //|KBI_SC_KBMOD_MASK           //�����غ�ˮƽ�ж�
                     |KBI_SC_KBIE_MASK              //�ж�ʹ��
                     |KBI_SC_KBACK_MASK             //
                     |KBI_SC_KBSPEN_MASK          //����KBxSP
                     |KBI_SC_RSTKBSP_MASK           //���KBIxSP
                      );
  
  if(kbix == KBIX0 )
   {
     NVIC_EnableIRQ(KBI0_IRQn);
   }
  else if (kbix == KBIX1)
    { 
      NVIC_EnableIRQ(KBI1_IRQn); 
    }
}

/*************************************************************************
*  �������ƣ�KBI_Disable
*  ����˵������ʼ���ж�
*  �������أ�
*  ����˵����
*  for example  KBI_Disable(KBIX0,29);//PTD5
*************************************************************************/
void KBI_Disable(KBIn_e kbix,uint8_t kbich)
{
    KBIx[kbix]->PE &= ~(1 << kbich) ;  
}
/*************************************************************************
*  �������ƣ�KBI_Enable
*  ����˵������ʼ���ж�
*  �������أ�
*  ����˵����
*  for example  KBI_Enable(KBIX0,29);//PTD5
*************************************************************************/
void KBI_Enable(KBIn_e kbix,uint8_t kbich)
{
  KBI0->SC |= KBI_SC_RSTKBSP_MASK ;    //����жϱ�־λ
  KBIx[kbix]->PE |= (1 << kbich) ;
}