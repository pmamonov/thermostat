#define __ls_c__
#include "ls.h"

void ls_init(){
  int i;
  GPIO_InitTypeDef sGPIOinit;
  sGPIOinit.GPIO_Mode = GPIO_Mode_IPU;
  sGPIOinit.GPIO_Speed = GPIO_Speed_10MHz;

  for (i=0; i<NUM_LS; i++){
    RCC_APB2PeriphClockCmd(lss[i].rcc, ENABLE);
    sGPIOinit.GPIO_Pin = lss[i].pin;
    GPIO_Init(lss[i].gpio, &sGPIOinit);
  }
}
uint8_t ls_get(uint8_t id){
  uint8_t i,x=0;
  for (i=0; i<NUM_LS; i++){
    if (GPIO_ReadInputDataBit(lss[i].gpio, lss[i].pin))
      x |= 1<<i;
  }
  return x;
}

