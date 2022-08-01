#include "common.h"
#include "adc.h"


/*************************************************************************
*  �������ƣ�ADC_Init
*  ����˵����AD��ʼ��
*  �������أ���
*  ����˵����ch  :�ɼ�ͨ��
*           bit ���ɼ�λ��
*  for example  : ADC_Init(ADC_CHANNEL_AD4,ADC_12BIT);
*************************************************************************/
void ADC_Init( ADCHn  ch,ADC_nbit bit)
{
        SIM->SCGC |= SIM_SCGC_ADC_MASK;   //����ʱ��ԭ
        
        ADC->SC3  = (0
                      |ADC_SC3_ADICLK(BUS_CLOCK)   //ѡ��ϵͳʱ��
                      |ADC_SC3_MODE(bit)      //8λAD�ɼ�
                      //|ADC_SC3_ADLSMP_MASK         //�͹��Ĳɼ�
                      |ADC_SC3_ADIV(ADC_ADIV_1)      //��ƵΪ1
                      //|ADC_SC3_ADLPC_MASK            //������ʱ��
                    ) ;
        ADC->SC2  = (0
                     // |ADC_SC2_ADTRG_MASK             //1Ӳ������,0�������
                    //  |ADC_SC2_ACFE_MASK            //�ɼ��Ƚ�
                    //  |ADC_SC2_ACFGT_MASK           //���ڱȽ�ֵ���Ƚϴ���
                    ) ;
       ADC->APCTL1 = ADC_APCTL1_ADPC(1<< ch) ; 
       ADC->SC1  = (0
                    |ADC_SC1_ADCH(ch)             //ѡ��ɼ�ͨ��
                   // |ADC_SC1_ADCO_MASK            //�����ɼ�
                   // |ADC_SC1_AIEN_MASK           //�ж�
                    ) ;
}

/*************************************************************************
*  �������ƣ�adc_init
*  ����˵������ȡADC����ֵ(��֧��Bͨ��)
*  ����˵����adcn_ch      ADCͨ��
*           bit          ADC���ȣ� ADC_8bit,ADC_12bit, ADC_10bit��
*  for example           adc_once(ADC_CHANNEL_AD4,ADC_12BIT);
*************************************************************************/
uint16_t adc_once(ADCHn adcn_ch, ADC_nbit bit) //�ɼ�ĳ·ģ������ADֵ
{
  uint16_t result = 0;
  ADC_Init( adcn_ch , bit) ;    //����ADCת��
  while ((ADC->SC1 & ADC_SC1_COCO_MASK ) != ADC_SC1_COCO_MASK);   //ֻ֧�� Aͨ��
  result = ADC->R;
  ADC->SC1 &= ~ADC_SC1_COCO_MASK;
  return result;
}
/*************************************************************************
*  �������ƣ�ad_ave
*  ����˵������β�����ȡƽ��ֵ
*  ����˵���� adcn_ch ͨ����
*            bit     ���ȣ� ADC_8bit,ADC_12bit, ADC_10bit, ADC_16bit ��
*            N       ��ֵ�˲�����(��Χ:0~255)
*  for example       adc_once(ADC_CHANNEL_AD4,ADC_12BIT,10);
*************************************************************************/
uint16_t adc_ave(ADCHn adcn_ch, ADC_nbit bit, uint8_t N) //��ֵ�˲�
{
    uint32_t tmp = 0;
    uint8_t  i;
    for(i = 0; i < N; i++)
        tmp += adc_once(adcn_ch, bit);
    tmp = tmp / N;
    return (uint16_t)tmp;
}

/*************************************************************************
*  �������ƣ�adc_sum
*  ����˵������β��������
*  ����˵����adcn_ch      ͨ����
*            bit         ���ȣ� ADC_8bit,ADC_12bit, ADC_10bit, ADC_16bit ��
*            N           ��ʹ���(��Χ:0~255)
*  for example           adc_sum(ADC_CHANNEL_AD4,ADC_12BIT,10);
*************************************************************************/
uint16_t adc_sum(ADCHn adcn_ch, ADC_nbit bit, uint8_t N)
{
    uint32_t tmp = 0;
    uint8_t  i;
    for(i = 0; i < N; i++)
        tmp += adc_once(adcn_ch, bit);
    return (uint16_t)tmp;
}













