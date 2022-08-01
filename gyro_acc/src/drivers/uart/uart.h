#ifndef _UART_H_
#define _UART_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
//#include "wdog.h"
#include "derivative.h"

typedef enum  UARTn
{
    //��ʼ��Ĭ������       --TXD--      --RXD--     ���Ը�������ͨ�����������޸� uart_init
    UARTR0 = 0,    //           
    UARTR1 = 1,    //           
    UARTR2 = 2,    //           

} UARTn;

void uart_init (UARTn uratn,uint32_t baud_rate) ;
void Uart_SendChar(UARTn uratn,uint8_t send);
uint8_t Uart_GetChar(UARTn uratn) ;
#endif /* #ifndef _UART_H_ */
