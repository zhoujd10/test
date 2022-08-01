#include "ftm.h"


FTM_Type * FTMx[3] = { FTM0,FTM1,FTM2};

/*************************************************************************
*  �������ƣ�FTM_PWM_init
*  ����˵����pwm��ʼ��
*  �������أ���
*  ����˵����ftm��   PWMģ��
             ch:     ͨ��
*            freq  ��Ƶ��
             duty  ��ռ�ձ� 0-100    ���Ե���FTM_PRECISON���ϵ�����ı侫��
   for example       FTM_PWM_init(CFTM0, FTM_CH1, 10000, 10);//PWM1 PTA1       
*************************************************************************/
void FTM_PWM_init(FTMn_e ftm, FTM_CHn_e ch, uint32_t freq, uint32_t duty)
{
    uint32 clk_hz ;
    uint16 mod;
    uint8  ps;
    uint16 cv;
    uint8_t   channels;
    clk_hz = CORE_CLK_HZ ;
    
    mod = (clk_hz >> (16+4) ) / freq ;     
        ps = 0;
    while((mod >> ps) >= 1)             // �� (mod >> ps) < 1 ���˳� while ѭ�� ������ PS ����Сֵ
    {
        ps++;
    }
    //ASSERT(ps <= 0x07);                // ���ԣ� PS ���Ϊ 0x07 ��������ֵ���� PWMƵ�����ù��ͣ��� Bus Ƶ�ʹ���
    if(ps)
    {
      mod = 0xffff ;
    }
    else
    {
      mod = (clk_hz >> (ps+4)) / freq; // �� MOD ��ֵ
    }
    cv = (duty * (mod - 0 + 1)) / FTM_PRECISON;  //ϵ��
    
    switch(ftm)
    {
    case CFTM0:
      channels = 2;
      SIM->SCGC |= SIM_SCGC_FTM0_MASK;
      SIM->PINSEL &=~SIM_PINSEL_FTM0PS0_MASK ;  // PWM0 PTA0
      SIM->PINSEL &=~SIM_PINSEL_FTM0PS1_MASK ;  // PWM1 PTA1
      
      break ;
    case CFTM1:
      channels = 2;
      SIM->SCGC |= SIM_SCGC_FTM1_MASK;
      SIM->PINSEL |= SIM_PINSEL_FTM1PS0_MASK ;  // PWM0 PTH2
      SIM->PINSEL |= SIM_PINSEL_FTM1PS1_MASK ;  // PWM1 PTE7
      
      break ;
    case CFTM2:
      channels = 6;
      SIM->SCGC  |= SIM_SCGC_FTM2_MASK;
      SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(2); //PWM0 PTF0
      SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(2); //PWM1 PTF1
//      SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(2); //PWM2 PTG4
//      SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(2); //PWM3 PTG5
//      SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS4_MASK; //PWM4 PTG6
//      SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS5_MASK; //PWM5 PTG7
      SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS2(2); //PWM2 PTC2
      SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS3(2); //PWM3 PTC3
      SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS4_MASK; //PWM4 PTB4
      SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS5_MASK; //PWM5 PTB5
      break ;
    default:
        break;
    }
    FTMx[ftm]->SC = 0 ;
    FTMx[ftm]->CONTROLS[ch].CnSC = 0 ;
     ASSERT(ch <= channels);          // ���ԣ� ch ���Ϊ channels ��������ֵ������ͨ��
    FTMx[ftm]->CONTROLS[ch].CnSC |= (0
                                  //  |FTM_CnSC_ELSA_MASK
                                    |FTM_CnSC_ELSB_MASK
                                 //   |FTM_CnSC_MSA_MASK
                                    |FTM_CnSC_MSB_MASK
                                 //   |FTM_CnSC_CHIE_MASK
                                //    |FTM_CnSC_CHF_MASK
                                     );
    FTMx[ftm]->SC &= ~FTM_SC_CPWMS_MASK;
    //********************
    //freq = MOD - CNTIN + 0x0001
    //duty = CnV - CNTIN ;
    //********************
//    FTMx[ftm]->CNTIN = 0 ;
    FTMx[ftm]->MOD = mod ;
    FTMx[ftm]->CONTROLS[ch].CnV = cv  ;
    FTMx[ftm]->SC = FTM_SC_CLKS(1)|FTM_SC_PS(4) ;
                      
    
}
/*************************************************************************
*  �������ƣ�FTM_PWM_Duty
*  ����˵����pwm��ֵ
*  �������أ���
*  ����˵����FTMn_e�� PWMģ��
             ch    :  ͨ��
             duty  �� ռ�ձ� 0-100    ���Ե���FTM_PRECISON���ϵ�����ı侫��
   for axample         FTM_PWM_Duty(CFTM0, FTM_CH1, 20);       
*************************************************************************/

void FTM_PWM_Duty(FTMn_e ftm, FTM_CHn_e ch, uint32_t duty)
{
    uint32_t cv;
    uint32_t mod = 0;
    uint8_t   channels;
    
    ASSERT(duty <= FTM_PRECISON); 
    switch(ftm)
    {
    case CFTM0:
      channels = 2;
      break ;
    case CFTM1:
      channels = 2;
      break ;
    case CFTM2:
      channels = 6;
      break ;
    default:
        break;
    }
     ASSERT(ch <= channels);                     // ���ԣ� ch ���Ϊ channels ��������ֵ������ͨ��
   mod = FTMx[ftm]->MOD  ;
   cv = (duty * (mod - 0 + 1)) / FTM_PRECISON;   //ϵ��
   FTMx[ftm]->CONTROLS[ch].CnV = cv  ;
}




