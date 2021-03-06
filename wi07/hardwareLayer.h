/*-----------------------------------------------------------------------------
/
/
/----------------------------------------------------------------------------*/
#include <avr/io.h>	
#include <string.h>
#include "xprintf.h"
#include <avr/eeprom.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "xmega_digital.h"
#include "ringBuffer.h"
/*---------------------------------------------------------------------------*/
volatile uint8_t r;
volatile uint8_t g;
volatile uint8_t b;
volatile uint8_t r_counter;
volatile uint8_t g_counter;
volatile uint8_t b_counter;
#define set_rgb(rval,gval,bval) {r=rval; g=gval; b=bval;}
/*---------------------------------------------------------------------------*/
extern RingBuffer_t Buffer;
extern volatile uint8_t BufferData[1024];
/*---------------------------------------------------------------------------*/
void initClock_32Mhz();
/*---------------------------------------------------------------------------*/
void sendch_module(uint8_t ch);
/*---------------------------------------------------------------------------*/
void dbg(uint8_t ch);
/*---------------------------------------------------------------------------*/
void init_uart();
/*---------------------------------------------------------------------------*/
void init_adc();
/*---------------------------------------------------------------------------*/
uint16_t read_adc(uint8_t ch);
/*---------------------------------------------------------------------------*/
void init_hardware();
/*---------------------------------------------------------------------------*/
