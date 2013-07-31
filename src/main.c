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
#include "com.h"

#define SYS_LED_RCC RCC_APB2Periph_GPIOC
#define SYS_LED_GPIO GPIOC
#define SYS_LED_PIN GPIO_Pin_15

volatile uint8_t sensors;

void vChatTask(void* vpars);
void vBlinkTask(void* vpars);
void status_err();
void status_ok();

int main(void){
  portBASE_TYPE err;
  char s[64];

  SystemInit();
  Set_System();

  // Enable System LED
  GPIO_InitTypeDef sGPIOinit;
  sGPIOinit.GPIO_Mode = GPIO_Mode_Out_PP;
  sGPIOinit.GPIO_Speed = GPIO_Speed_10MHz;
  sGPIOinit.GPIO_Pin = SYS_LED_PIN;
  GPIO_Init(SYS_LED_GPIO, &sGPIOinit);
  GPIO_SetBits(SYS_LED_GPIO, SYS_LED_PIN);

  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();


  ls_init();
  tem_init();
  sensors = ts_init();

  err = xTaskCreate( vBlinkTask, "blink", 64, NULL, tskIDLE_PRIORITY+1, NULL );
  if ( err == pdPASS)
    cdc_write_buf(&cdc_out, "blink started\n", 0);
  else{
    sniprintf(s, sizeof(s),"blink failed %d", err);
    cdc_write_buf(&cdc_out, s, 0);
  }
  err = xTaskCreate( vChatTask, "chat", 1024, NULL, tskIDLE_PRIORITY+1, NULL );
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
  uint8_t com_stop;
  uint32_t baudrate;
  uint16_t bytesize, parity, stopbits, hwfc;
  int tem_id, tem_val, tem_tim;

  while (1){
    cdc_gets(cmd, sizeof(cmd));
//    cdc_write_buf(&cdc_out, cmd, strlen(cmd));

    tk = _strtok(cmd, " \n");
    if (strcmp(tk, "temp") == 0){
      for (i=0; i<8; i++){
        if (sensors & (1<<i)){
          sniprintf(s,sizeof(s),"%d:%d ", i, ts_get(i));
          cdc_write_buf(&cdc_out, s, strlen(s));
        }
      }
        status_ok();//cdc_write_buf(&cdc_out, "\nOK\n", 4);
    }
    else
    if (strcmp(tk, "snsi") == 0){
      sniprintf(s,sizeof(s),"%d", sensors=ts_init());
      cdc_write_buf(&cdc_out, s, strlen(s));
      status_ok();
    }
    else
    if (strcmp(tk, "comi") == 0){
      if (!((tk = _strtok(0,0)) && (baudrate=atoi(tk)))) goto com_parse_err;


      if (!(tk = _strtok(0,0))) goto com_parse_err;
      switch (tk[0]){
        case '8':
          bytesize = USART_WordLength_8b;
          break;
        case '9':
          bytesize = USART_WordLength_9b;
          break;
        default:
          goto com_parse_err;          
      }
      
      if (!(tk = _strtok(0,0))) goto com_parse_err;
      switch (tk[0]){
        case 'N':
          parity = USART_Parity_No;
          break;
        case 'E':
          bytesize = USART_Parity_Even;
          break;
        case 'O':
          bytesize = USART_Parity_Even;
          break;
        default:
          goto com_parse_err;          
      }

      if (!(tk = _strtok(0,0))) goto com_parse_err;
      switch (tk[0]){
        case '1':
          stopbits = USART_StopBits_1;
          break;
        case '2':
          stopbits = USART_StopBits_2;
          break;
        default:
          goto com_parse_err;          
      }

      if (!(tk = _strtok(0,0))) goto com_parse_err;
      switch (tk[0]){
        case '0':
          hwfc = USART_HardwareFlowControl_None;
          break;
        case '1':
          hwfc = USART_HardwareFlowControl_RTS_CTS;
          break;
        default:
          goto com_parse_err;          
      }
      com_init(baudrate, bytesize, parity, stopbits, hwfc);
      status_ok();//cdc_write_buf(&cdc_out, "\nOK\n", 4);
      continue;
com_parse_err:
      status_err();//cdc_write_buf(&cdc_out, "\nERR\n", 5);
    }
    else
    if (strcmp(tk, "com") == 0){
      status_ok();
      com_stop=0;
      while(!com_stop){
        i = cdc_read_buf(&com_in, cmd, sizeof(cmd));
        if (i) cdc_write_buf(&cdc_out, cmd, i);
        
        i=0;
        while(1){
          if (cdc_read_buf(&cdc_in, cmd, 1)) {
            if (cmd[0]!=0xff){
              cdc_write_buf(&com_out, cmd, 1);
              i++;
            }
            else {
              com_stop=1;
              break;
            }
          }
          else break;
        }
        if (i) com_send();
      }
      status_ok();//cdc_write_buf(&cdc_out, "\nOK\n", 4);
    }
    else
    if (strcmp(tk, "tem") == 0){
      if (!(tk = _strtok(0,0))) goto tem_parse_err;
      tem_id=atoi(tk);
      if (!(tk = _strtok(0,0))) goto tem_parse_err;
      tem_val=atoi(tk);
      if (!((tk = _strtok(0,0)) && (tem_tim=atoi(tk)))) goto tem_parse_err;

      tem_enable(tem_id, tem_val, tem_tim);
      status_ok(); //cdc_write_buf(&cdc_out, "OK\n", 4);
      continue;
tem_parse_err:      
      status_err(); //cdc_write_buf(&cdc_out, "\nERR\n", 5);
    }
    else
    if (strcmp(tk, "temq") == 0){
      if (!(tk = _strtok(0,0)))
        status_err();//cdc_write_buf(&cdc_out, "\nERR\n", 4);
      else{
      tem_val = tem_get(atoi(tk));
      sniprintf(s, sizeof(s),"%d", (tem_val & 1) ? 0 : (tem_val & 2 ? 1 : -1));
      cdc_write_buf(&cdc_out, s, strlen(s));
      status_ok();//cdc_write_buf(&cdc_out, "\nOK\n", 4);
      }
    }
    else
    if (strcmp(tk, "lsq") == 0){
      sniprintf(s, sizeof(s),"%d", ls_get());
      cdc_write_buf(&cdc_out, s, strlen(s));
      status_ok();//cdc_write_buf(&cdc_out, "\nOK\n", 4);
    }
    else
    if (strcmp(tk, "test") == 0){
      while (tk=_strtok(0,0)){
        cdc_write_buf(&cdc_out, tk, strlen(tk));
        cdc_write_buf(&cdc_out, ",", 1);
      }
      status_ok(); //cdc_write_buf(&cdc_out, "OK\n", 4);
    }
    else{
      cdc_write_buf(&cdc_out, "Unknown command", 15);
      status_err();
    }
//    cdc_write_buf(&cdc_out, s, strlen(s));
  }
}

void vBlinkTask(void *vpars){
  volatile int i, c=0, x=0, d=1;
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
/*  while (1){
    if (GPIO_ReadOutputData(GPIOC) & (1<<6)) GPIO_ResetBits(GPIOC, 1<<6);
    else GPIO_SetBits(GPIOC, 1<<6);
    for (i=1000000; i;i--);
  }*/
  while (1){
    if (c==0){
      c = 1;
      if (x==0) d=1;
      if (x==10) d=-1;
      x = x + d;
      if (x==0) c=5;
    }
    else
      c--;

    if (x>0) GPIO_SetBits(SYS_LED_GPIO, SYS_LED_PIN);
    for (i=0; i<10; i++) {
      if (i>=x) GPIO_ResetBits(SYS_LED_GPIO, SYS_LED_PIN);
      vTaskDelay(1);
    }
  }
}

void vApplicationStackOverflowHook( xTaskHandle xTask, signed portCHAR *pcTaskName ){
  while(1);
}

void status_err(){
  cdc_write_buf(&cdc_out, "\nERR\n", 5);
}

void status_ok(){
  cdc_write_buf(&cdc_out, "\nOK\n", 4);
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
