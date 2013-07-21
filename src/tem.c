#define __tem_c__
#include "tem.h"

void vTimerCallback(xTimerHandle pxTimer){
  tem_disable((uint8_t)pvTimerGetTimerID(pxTimer));
};

void tem_init(){
  int i;
  GPIO_InitTypeDef sGPIOinit;
  sGPIOinit.GPIO_Mode = GPIO_Mode_Out_PP;
  sGPIOinit.GPIO_Speed = GPIO_Speed_10MHz;

  for (i=0; i<NUM_TEMS; i++){
    RCC_APB2PeriphClockCmd(tems[i].en_rcc, ENABLE);

    sGPIOinit.GPIO_Pin = tems[i].en_pin;
    GPIO_Init(tems[i].en_gpio, &sGPIOinit);
    GPIO_SetBits(tems[i].en_gpio, tems[i].en_pin); // disable TEM

    RCC_APB2PeriphClockCmd(tems[i].dir_rcc, ENABLE);
    sGPIOinit.GPIO_Pin = tems[i].dir_pin;
    GPIO_Init(tems[i].dir_gpio, &sGPIOinit);
    GPIO_ResetBits(tems[i].dir_gpio, tems[i].dir_pin);

    tems[i].timer = xTimerCreate("T", 100, pdFALSE, (void *)i, vTimerCallback);
  }
};

void tem_enable(uint8_t i, int val, uint32_t tim){
  if (val == 0) {
    tem_disable(i);
    return;
  }
  if (val > 0)
    GPIO_SetBits(tems[i].dir_gpio, tems[i].dir_pin);
  else
    GPIO_ResetBits(tems[i].dir_gpio, tems[i].dir_pin);
  GPIO_ResetBits(tems[i].en_gpio, tems[i].en_pin); // enable TEM
  xTimerChangePeriod(tems[i].timer, tim, 0);
  xTimerStart(tems[i].timer, 0);
};

void tem_disable(uint8_t i){
  if (i<NUM_TEMS)
    GPIO_SetBits(tems[i].en_gpio, tems[i].en_pin); // disable TEM
};

