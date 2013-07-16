#define __com_c__
#include "com.h"

void USART2_IRQHandler(void){
  uint16_t x;

  if (USART_GetFlagStatus(USART2, USART_FLAG_TXE)){
    if (cdc_read_buf(&com_out, &x, 1)) USART_SendData(USART2, x);
    else USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
  }
  
  if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE)){
    x=USART_ReceiveData(USART2);
    cdc_write_buf(&com_in, &x, 1);
  }
}

void com_init(uint32_t baudrate, uint16_t bytesize, uint16_t parity, uint16_t stopbits, uint16_t hwfc){
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef  sGPIOinit;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,  ENABLE);
  
  // TX
  sGPIOinit.GPIO_Pin = GPIO_Pin_2;
  sGPIOinit.GPIO_Speed = GPIO_Speed_10MHz;
  sGPIOinit.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &sGPIOinit);

  //RTS
  sGPIOinit.GPIO_Pin = GPIO_Pin_1;
  GPIO_Init(GPIOA, &sGPIOinit);

  // RX 
  sGPIOinit.GPIO_Pin = GPIO_Pin_3;
  sGPIOinit.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &sGPIOinit);

  // CTS
  sGPIOinit.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOA, &sGPIOinit);

  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  USART_InitStructure.USART_BaudRate = baudrate;
  USART_InitStructure.USART_WordLength = bytesize; //USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = stopbits; // USART_StopBits_1;
  USART_InitStructure.USART_Parity = parity;//USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = hwfc; //USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_DeInit(USART2);
  USART_Init(USART2, &USART_InitStructure);
  USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  USART_Cmd(USART2, ENABLE);
}

void com_send(){
  uint8_t x;
  if (cdc_read_buf(&com_out, &x, 1)){
    USART_SendData(USART2, x);
    USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
  }
}
