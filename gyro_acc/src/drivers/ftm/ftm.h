#ifndef FTM_H_
#define FTM_H_
#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
* Includes
******************************************************************************/
#include "common.h"
#include "derivative.h"
/******************************************************************************
* Constants
******************************************************************************/
extern FTM_Type * FTMx[3] ;
/******************************************************************************
* Macros
******************************************************************************/

#define FTM_PRECISON               100  
#define FTMx_CV(ftmx,ch,cv)        FTMx[ftmx]->CONTROLS[ch].CnV = cv  ;
/******************************************************************************
* Types
******************************************************************************/
//����FTMģ���
typedef enum
{
    CFTM0,
    CFTM1,
    CFTM2,

    FTM_MAX,
} FTMn_e;

//����FTM ͨ����
typedef enum
{

    FTM_CH0,
    FTM_CH1,
    FTM_CH2,
    FTM_CH3,
    FTM_CH4,
    FTM_CH5,
} FTM_CHn_e;  
  /*! @brief FTM_CALLBACK function declaration                                  */

/*! @} End of ftm_callback                                                    */


/*! @} End of ftm_api_list                                                    */

/******************************************************************************
* Global functions
******************************************************************************/

void FTM_PWM_init(FTMn_e ftm, FTM_CHn_e ch, uint32_t freq, uint32_t duty);
void FTM_PWM_Duty(FTMn_e ftm, FTM_CHn_e ch, uint32_t duty);



#endif /* FTM_H_ */
