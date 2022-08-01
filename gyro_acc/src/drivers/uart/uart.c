#include "uart.h"

volatile UART_Type *UARTx[3]={UART0,UART1,UART2};


/*************************************************************************
*  函数名称：uart_init
*  功能说明：初始化uart模块
*  函数返回：无
*  参数说明：UARTn  :    通道
*           baud_rate  ：波特率  9600   115200
*  for example           uart_init(UARTR1,9600);
*************************************************************************/
void uart_init (UARTn uratn,uint32_t baud_rate){
  uint8_t temp;
  uint16_t  sbr;
  sbr = (uint16_t)(BUS_CLK_HZ/(16*baud_rate)); 
  switch(uratn)
  {
    case UARTR0:
      SIM->SCGC |=  SIM_SCGC_UART0_MASK;
      SIM->PINSEL |= SIM_PINSEL_UART0PS_MASK;   //PTA3 TX ,PTA2 RX
      SIM->SOPT0 &= ~SIM_SOPT0_TXDME_MASK ;
      SIM->SOPT0 &= ~SIM_SOPT0_RXDFE_MASK ;
      SIM->SOPT0 &= ~SIM_SOPT0_RXDCE_MASK ;
     break;
    case UARTR1:
      SIM->SCGC |=  SIM_SCGC_UART1_MASK;
      SIM->PINSEL1 |= SIM_PINSEL1_UART1PS_MASK ;  //PTF3 TX ,PTF2 RX 
     break ;
    case UARTR2:
      SIM->SCGC |=  SIM_SCGC_UART2_MASK;
   //   SIM->PINSEL1 |= SIM_PINSEL1_UART2PS_MASK ;  //PTD6 TX ,PTD7 RX
      break;
    default:
        break;
  }
    temp = UARTx[uratn]->BDH&~UART_BDH_SBR(0X1F);  
    UARTx[uratn]->BDH = temp|UART_BDH_SBR(((sbr & 0x1F00) >> 8)) ;
    UARTx[uratn]->BDL = (uint8_t)(sbr&UART_BDL_SBR_MASK);
    UARTx[uratn]->C1  = 0 ;
    UARTx[uratn]->C2  = (0
                         |UART_C2_TE_MASK
                         |UART_C2_RE_MASK
                         );
      

  
  
}

/*************************************************************************
*  函数名称：Uart_SendChar
*  功能说明：发送一个字节
*  函数返回：无
*  参数说明：UARTn :模块号（UART0~UART2）
*           send   :发送的数据
*  for example      Uart_SendChar(UARTR1,1);
*************************************************************************/
void Uart_SendChar(UARTn uratn,uint8_t send)
{
	while((UARTx[uratn]->S1&UART_S1_TDRE_MASK)==0);		/* Wait for transmit buffer to be empty*/							/* Read UART2_S1 register*/
	(void)UARTx[uratn]->S1;					/* Read UART2_S1 register*/
        UARTx[uratn]->D=send;						/* Send data*/
}

/*************************************************************************
*  函数名称：Uart_GetChar
*  功能说明：接受一个数据
*  函数返回：接受数据
*  参数说明：UARTn  :模块号（UART0~UART2）
*  for example       data = Uart_GetChar(UART1);
*************************************************************************/
uint8_t Uart_GetChar(UARTn uratn)
{

  uint8_t recieve;
  while(( UARTx[uratn]->S1 & UART_S1_RDRF_MASK)==0);	/* Wait for received buffer to be full*/								/* Read UART2_S1 register*/
  recieve= UARTx[uratn]->D;								/* Read received data*/
  return recieve;

}












