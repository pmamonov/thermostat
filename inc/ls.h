#include "stm32f10x_gpio.h"

#define NUM_LS 5

typedef struct stLS {
  uint32_t rcc;
  GPIO_TypeDef *gpio;
  uint16_t pin;
} LSType;

#ifdef __ls_c__
static LSType lss[NUM_LS] = {\
{RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_0},\
{RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_2},\
{RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_4},\
{RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_6},\
{RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_8}\
};
#endif

void ls_init();
uint8_t ls_get(uint8_t id);

