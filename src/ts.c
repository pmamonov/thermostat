#define __ts_c__
#include "ts.h"

static volatile uint8_t ts_detected;

void I2C1_EV_IRQHandler(void){
/*  if (I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE)){
    i2c_buf[i2c_buf_pos++] = I2C_GetData(I2C1);
  }*/
}

uint8_t ts_init(){
  int i;
  volatile int j;
  uint8_t r;
  GPIO_InitTypeDef  sGPIOinit;
  I2C_InitTypeDef sI2Cinit;

  ts_detected=0;

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

//  I2C_ITConfig(I2C1, I2C_IT_BUF, ENABLE);

  I2C_Cmd(I2C1, ENABLE);

  for (i=0; i<8; i++){
    I2C_GenerateSTART(I2C1, ENABLE);
    while (I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
    I2C_ClearFlag(I2C1, I2C_FLAG_AF);
    I2C_Send7bitAddress(I2C1, 0x90 | (i<<1), I2C_Direction_Transmitter);
    while (I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS){
      if (I2C_GetFlagStatus(I2C1, I2C_FLAG_AF) == SUCCESS) goto next;
    };
//    if (I2C_GetFlagStatus(I2C1, I2C_FLAG_AF) == SUCCESS) continue;
      
    I2C_SendData(I2C1, 0xac);
    while (I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);

    // delay > 10ms
//    for(j=50000; j; j--);

    I2C_GenerateSTART(I2C1, ENABLE);
    while (I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);

    I2C_Send7bitAddress(I2C1, 0x90 | (i<<1), I2C_Direction_Receiver);
    while (I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);

//    while (I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED | I2C_FLAG_BTF) != SUCCESS);
    while (I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
    r = I2C_ReceiveData(I2C1);

    I2C_GenerateSTOP(I2C1, ENABLE);
    
//    ts_detected = r;
//    if ((r & 0x7e) ==  0x4a){
      ts_detected |= 1<<i;

      I2C_GenerateSTART(I2C1, ENABLE);
      while (I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
     
      I2C_Send7bitAddress(I2C1, 0x90 | (i<<1), I2C_Direction_Transmitter);
      while (I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
        
      I2C_SendData(I2C1, 0xee);
      while (I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
next:
      I2C_GenerateSTOP(I2C1, ENABLE);
//    }
  }
  I2C_GenerateSTOP(I2C1, ENABLE);

  return ts_detected;
}

int16_t ts_get(uint8_t id){
  int16_t t=0, i;
//  if (!(ts_detected & (1<<i))) return 0;
  I2C_Cmd(I2C1, DISABLE);
  I2C_Cmd(I2C1, ENABLE);

  I2C_GenerateSTART(I2C1, ENABLE);
  while (I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);

  I2C_ClearFlag(I2C1, I2C_FLAG_AF);
  I2C_Send7bitAddress(I2C1, 0x90 | (id<<1), I2C_Direction_Transmitter);
  while (I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS){
      if (I2C_GetFlagStatus(I2C1, I2C_FLAG_AF) == SUCCESS) goto end;
  };

  I2C_SendData(I2C1, 0xaa);
  while (I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);

  I2C_GenerateSTART(I2C1, ENABLE);
  while (I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);

  I2C_Send7bitAddress(I2C1, 0x90 | (id<<1), I2C_Direction_Receiver);
  while (I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);

  for (i=1; i>=0; i--){
//    while (I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED | I2C_FLAG_BTF) != SUCCESS);
    while (I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
    t |= (uint16_t)I2C_ReceiveData(I2C1) << 8*i;
  }
end:
  I2C_GenerateSTOP(I2C1, ENABLE);

  return t;
}
