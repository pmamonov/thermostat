#define __ts_c__
#include "ts.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x.h"

#define FLAG_Mask               ((uint32_t)0x00FFFFFF)

#define AF 1
#define RDY 2

static volatile uint8_t ts_detected;
static volatile uint8_t nb;
volatile uint8_t status;
static volatile uint8_t addr;
static volatile uint8_t dir;
static volatile uint8_t buf[8];

void I2C1_EV_IRQHandler(void){
  volatile uint32_t ev = I2C_GetLastEvent(I2C1);
  static uint8_t i;
  if ((ev & I2C_EVENT_MASTER_MODE_SELECT) == I2C_EVENT_MASTER_MODE_SELECT) {
    i=0;
    I2C_Send7bitAddress(I2C1, 0x90 | (addr<<1), dir);
  }

  if ((ev & I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)
    I2C_SendData(I2C1, buf[i++]);

//  if (ev & I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED == I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);

  if ((ev & I2C_EVENT_MASTER_BYTE_TRANSMITTED) == I2C_EVENT_MASTER_BYTE_TRANSMITTED){
     if (i<nb) I2C_SendData(I2C1, buf[i++]);
     else {
      status |= RDY;
      I2C_ITConfig(I2C1, I2C_IT_EVT, DISABLE); 
     }
  }

  if ((ev & I2C_EVENT_MASTER_BYTE_RECEIVED) == I2C_EVENT_MASTER_BYTE_RECEIVED){
    buf[i++] = I2C_ReceiveData(I2C1);
//      I2C_GenerateSTOP(I2C1, ENABLE);
    if (i+1==nb){
      I2C1->CR1 &= ~I2C_Ack_Enable;
      I2C_GenerateSTOP(I2C1, ENABLE); 
    }
    if (i == nb) {
      status |= RDY;
      I2C_ITConfig(I2C1, I2C_IT_EVT, DISABLE);
    }
  }
/*  if (ev & I2C_FLAG_AF & FLAG_Mask) {
    status |= AF | RDY;
    I2C_ClearFlag(I2C1, I2C_FLAG_AF);
    I2C_GenerateSTOP(I2C1, ENABLE);
    I2C_ITConfig(I2C1, I2C_IT_EVT, DISABLE);
  }*/
}

void I2C1_ER_IRQHandler(void){
  uint32_t ev = I2C_GetLastEvent(I2C1);
  if (ev & I2C_FLAG_AF & FLAG_Mask) {
    status |= AF | RDY;
    I2C_ClearFlag(I2C1, I2C_FLAG_AF);
    I2C_GenerateSTOP(I2C1, ENABLE);
    I2C_ITConfig(I2C1, I2C_IT_EVT, DISABLE);
  }
}

uint8_t ts_init(){
  int i;
  volatile int j;
  uint8_t r;
  GPIO_InitTypeDef  sGPIOinit;
  I2C_InitTypeDef sI2Cinit;
  NVIC_InitTypeDef sNVICinit;


  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,  ENABLE);
  
  // SCL
  sGPIOinit.GPIO_Pin = GPIO_Pin_6;
  sGPIOinit.GPIO_Speed = GPIO_Speed_10MHz;
  sGPIOinit.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(GPIOB, &sGPIOinit);

  // SDA
  sGPIOinit.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOB, &sGPIOinit);

  I2C_DeInit(I2C1);
  sI2Cinit.I2C_Mode = I2C_Mode_I2C;
  sI2Cinit.I2C_DutyCycle = I2C_DutyCycle_2;
  sI2Cinit.I2C_OwnAddress1 = 0x0f;
  sI2Cinit.I2C_Ack = I2C_Ack_Enable;
  sI2Cinit.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  sI2Cinit.I2C_ClockSpeed = 5000;
  I2C_Init(I2C1, &sI2Cinit);

  I2C_ITConfig(I2C1, I2C_IT_ERR, ENABLE);
  I2C_ITConfig(I2C1, I2C_IT_BUF, ENABLE);
  I2C_ITConfig(I2C1, I2C_IT_EVT, DISABLE);
  
  sNVICinit.NVIC_IRQChannel = I2C1_EV_IRQn;
  sNVICinit.NVIC_IRQChannelCmd = ENABLE;
  sNVICinit.NVIC_IRQChannelPreemptionPriority = 1;
  sNVICinit.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&sNVICinit);
  sNVICinit.NVIC_IRQChannel = I2C1_ER_IRQn;
  NVIC_Init(&sNVICinit);

  I2C_Cmd(I2C1, ENABLE);

  ts_detected=0;
  dir = I2C_Direction_Transmitter;
  nb=1;
  buf[0] = 0xee;
  for (i=0; i<8; i++){
    addr = i;
    status=0;
    I2C_GenerateSTART(I2C1, ENABLE);  
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_ITConfig(I2C1, I2C_IT_EVT, ENABLE);
    while (!(status & RDY));
//    
    if (!(status & AF)) {
      ts_detected |= 1<<i;
      I2C_GenerateSTOP(I2C1, ENABLE);
    }
  }

  return ts_detected;
}


int16_t ts_get(uint8_t id){
  if (!(ts_detected & (1<<id))) return 0;
  addr=id;
  dir = I2C_Direction_Transmitter;
  nb = 1;
  buf[0] = 0xaa;
  status = 0;
  I2C_GenerateSTART(I2C1, ENABLE);  
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_ITConfig(I2C1, I2C_IT_EVT, ENABLE);
  while (!(status & RDY));
  if (status & AF) return 0;
  
  status=0;
  dir=I2C_Direction_Receiver;
  nb=2;
//  while (I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE)) I2C_ReceiveData(I2C1); // read two extra bytes from previous receive
//  if (nb>1) 
  I2C1->CR1 |= I2C_Ack_Enable;
  I2C_GenerateSTART(I2C1, ENABLE);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_ITConfig(I2C1, I2C_IT_EVT, ENABLE);
  while (!(status & RDY));
//  if (status & AF) return 0;
//  else I2C_GenerateSTOP(I2C1, ENABLE);

  return ((uint16_t)buf[0]<<8) | buf[1];
}
