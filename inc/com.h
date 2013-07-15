#include <stdint.h>
#include "stm32f10x_usart.h"
#include "cdcio.h"

#define COMBUFLEN 128

#ifdef __com_c__
volatile char com_in_buf[COMBUFLEN];
volatile char com_out_buf[COMBUFLEN];
volatile cdc_buf_t com_in = {com_in_buf, 0,0,0,0};
volatile cdc_buf_t com_out = {com_out_buf, 0,0,0,0};
#else
extern volatile cdc_buf_t com_in;
extern volatile cdc_buf_t com_out;
#endif

void com_init(uint32_t baudrate, uint8_t bytesize, char parity, uint8_t stopbits, uint8_t hwfc);
void com_send();
