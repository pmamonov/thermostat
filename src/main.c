#include "hw_config.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "stm32f10x_gpio.h"
#include "stdlib.h"
#include "string.h"
#include "cdcio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

void vChatTask(void* vpars);
void vBlinkTask(void* vpars);

int main(void)
{
  SystemInit();
  Set_System();

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitTypeDef sGPIOinit;
  sGPIOinit.GPIO_Mode = GPIO_Mode_Out_OD;
  sGPIOinit.GPIO_Speed = GPIO_Speed_10MHz;
  sGPIOinit.GPIO_Pin = 1<<6;
  GPIO_Init(GPIOC, &sGPIOinit);
  GPIO_ResetBits(GPIOC, 1<<6);

  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();

  xTaskCreate( vBlinkTask, "blink", 16, NULL, tskIDLE_PRIORITY+1, NULL );
  xTaskCreate( vChatTask, "chat", 128, NULL, tskIDLE_PRIORITY+1, NULL );
  vTaskStartScheduler();

  for (;1;);
/*  while (1)
  {
    cdc_gets(cmd, sizeof(cmd));

    sniprintf(s,sizeof(s),"> %s",cmd);
    cdc_write_buf(&cdc_out, s, strlen(s));

    if (GPIO_ReadOutputData(GPIOC) & (1<<6)) GPIO_ResetBits(GPIOC, 1<<6);
    else GPIO_SetBits(GPIOC, 1<<6);
//    for (i=1000000; i;i--);
  }*/
}

void vChatTask(void *vpars){
  char s[64];
  char cmd[32];
  int i=0;
  while (1){
    cdc_gets(cmd, sizeof(cmd));
//    sniprintf(s,sizeof(s),"%d> %s",i,cmd);
    cdc_write_buf(&cdc_out, cmd, strlen(cmd));
  }
}

void vBlinkTask(void *vpars){
  volatile int i;
  while (1){
    if (GPIO_ReadOutputData(GPIOC) & (1<<6)) GPIO_ResetBits(GPIOC, 1<<6);
    else GPIO_SetBits(GPIOC, 1<<6);
    for (i=1000000; i;i--);
  }
}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif
