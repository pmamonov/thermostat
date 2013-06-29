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
#include "ts.h"
#include "strtok.h"

void vChatTask(void* vpars);
void vBlinkTask(void* vpars);

int main(void){
  portBASE_TYPE err;
  char s[64];


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

  err = xTaskCreate( vBlinkTask, "blink", 32, NULL, tskIDLE_PRIORITY+1, NULL );
  if ( err == pdPASS)
    cdc_write_buf(&cdc_out, "blink started\n", 0);
  else{
    sniprintf(s, sizeof(s),"blink failed %d", err);
    cdc_write_buf(&cdc_out, s, 0);
  }
  err = xTaskCreate( vChatTask, "chat", 256, NULL, tskIDLE_PRIORITY+1, NULL );
  if (err == pdPASS)
    cdc_write_buf(&cdc_out, "chat started\n", 0);
  else{
    sniprintf(s, sizeof(s),"chat failed %d", err);
    cdc_write_buf(&cdc_out, s, 0);
  }

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
  char cmd[64];
  char *tk;
  int16_t i;

  while (1){
    cdc_gets(cmd, sizeof(cmd));
//    cdc_write_buf(&cdc_out, cmd, strlen(cmd));

    tk = _strtok(cmd, " \n");
    if (strcmp(tk, "temp") == 0){
      for (i=0; i<8; i++){
        sniprintf(s,sizeof(s),"%d:%d ", i, ts_get(i));
        cdc_write_buf(&cdc_out, s, strlen(s));
      }
        cdc_write_buf(&cdc_out, "\nOK\n", 4);
    }
    else
    if (strcmp(tk, "snsi") == 0){
      sniprintf(s,sizeof(s),"%d\nOK\n", ts_init());
      cdc_write_buf(&cdc_out, s, strlen(s));
    }
    else
    if (strcmp(tk, "test") == 0){
      while (tk=_strtok(0,0)){
        cdc_write_buf(&cdc_out, tk, strlen(tk));
        cdc_write_buf(&cdc_out, "\n", 1);
      }
      cdc_write_buf(&cdc_out, "OK\n", 4);
    }
    else
      cdc_write_buf(&cdc_out, "ERR\n", 4);

//    cdc_write_buf(&cdc_out, s, strlen(s));
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

void vApplicationStackOverflowHook( xTaskHandle xTask, signed portCHAR *pcTaskName ){
  while(1);
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
