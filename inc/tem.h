#include "stm32f10x_gpio.h"
#include "FreeRTOS.h"
#include "timers.h"

#define NUM_TEMS 4

typedef struct stTem {
  uint32_t en_rcc;
  GPIO_TypeDef *en_gpio;
  uint16_t en_pin;
  uint32_t dir_rcc;
  GPIO_TypeDef *dir_gpio;
  uint16_t dir_pin;
  xTimerHandle timer;
} TemType;

#ifdef __tem_c__
TemType tems[NUM_TEMS] = {\
{RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_6, RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_1, 0},\
{RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_7, RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_3, 0},\
{RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_0, RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_5, 0},\
{RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_1, RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_7, 0}\
};
#endif

void tem_init();
void tem_enable(uint8_t id, int val, uint32_t tim);
void tem_disable(uint8_t id);

