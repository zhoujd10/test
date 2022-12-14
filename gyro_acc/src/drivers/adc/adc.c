#include "common.h"
#include "adc.h"


/*************************************************************************
*  函数名称：ADC_Init
*  功能说明：AD初始化
*  函数返回：无
*  参数说明：ch  :采集通道
*           bit ：采集位数
*  for example  : ADC_Init(ADC_CHANNEL_AD4,ADC_12BIT);
*************************************************************************/
void ADC_Init( ADCHn  ch,ADC_nbit bit)
{
        SIM->SCGC |= SIM_SCGC_ADC_MASK;   //开启时钟原
        
        ADC->SC3  = (0
                      |ADC_SC3_ADICLK(BUS_CLOCK)   //选择系统时钟
                      |ADC_SC3_MODE(bit)      //8位AD采集
                      //|ADC_SC3_ADLSMP_MASK         //低功耗采集
                      |ADC_SC3_ADIV(ADC_ADIV_1)      //分频为1
                      //|ADC_SC3_ADLPC_MASK            //长步长时间
                    ) ;
        ADC->SC2  = (0
                     // |ADC_SC2_ADTRG_MASK             //1硬件触发,0软件触发
                    //  |ADC_SC2_ACFE_MASK            //采集比较
                    //  |ADC_SC2_ACFGT_MASK           //大于比较值，比较触发
                    ) ;
       ADC->APCTL1 = ADC_APCTL1_ADPC(1<< ch) ; 
       ADC->SC1  = (0
                    |ADC_SC1_ADCH(ch)             //选择采集通道
                   // |ADC_SC1_ADCO_MASK            //连续采集
                   // |ADC_SC1_AIEN_MASK           //中断
                    ) ;
}

/*************************************************************************
*  函数名称：adc_init
*  功能说明：获取ADC采样值(不支持B通道)
*  参数说明：adcn_ch      ADC通道
*           bit          ADC精度（ ADC_8bit,ADC_12bit, ADC_10bit）
*  for example           adc_once(ADC_CHANNEL_AD4,ADC_12BIT);
*************************************************************************/
uint16_t adc_once(ADCHn adcn_ch, ADC_nbit bit) //采集某路模拟量的AD值
{
  uint16_t result = 0;
  ADC_Init( adcn_ch , bit) ;    //启动ADC转换
  while ((ADC->SC1 & ADC_SC1_COCO_MASK ) != ADC_SC1_COCO_MASK);   //只支持 A通道
  result = ADC->R;
  ADC->SC1 &= ~ADC_SC1_COCO_MASK;
  return result;
}
/*************************************************************************
*  函数名称：ad_ave
*  功能说明：多次采样，取平均值
*  参数说明： adcn_ch 通道号
*            bit     精度（ ADC_8bit,ADC_12bit, ADC_10bit, ADC_16bit ）
*            N       均值滤波次数(范围:0~255)
*  for example       adc_once(ADC_CHANNEL_AD4,ADC_12BIT,10);
*************************************************************************/
uint16_t adc_ave(ADCHn adcn_ch, ADC_nbit bit, uint8_t N) //均值滤波
{
    uint32_t tmp = 0;
    uint8_t  i;
    for(i = 0; i < N; i++)
        tmp += adc_once(adcn_ch, bit);
    tmp = tmp / N;
    return (uint16_t)tmp;
}

/*************************************************************************
*  函数名称：adc_sum
*  功能说明：多次采样，求和
*  参数说明：adcn_ch      通道号
*            bit         精度（ ADC_8bit,ADC_12bit, ADC_10bit, ADC_16bit ）
*            N           求和次数(范围:0~255)
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













