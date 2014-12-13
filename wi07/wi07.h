/*-----------------------------------------------------------------------------
/
/
/----------------------------------------------------------------------------*/
#include <stdint.h>
#include "ringBuffer.h"
#include <util/delay.h>
#include "xprintf.h"
/*---------------------------------------------------------------------------*/
extern RingBuffer_t Buffer;
extern uint8_t tcpData[512];
/*---------------------------------------------------------------------------*/
#define HTTP_RESPONSE_HEADER "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"
/*---------------------------------------------------------------------------*/
int8_t wait_for_message(const char* checkmsg,uint32_t timeoutLimit);
/*---------------------------------------------------------------------------*/
int8_t check_ok();
/*---------------------------------------------------------------------------*/
int8_t check_error();
/*---------------------------------------------------------------------------*/
int8_t check_busy();
/*---------------------------------------------------------------------------*/
uint16_t getMessageLength();
/*---------------------------------------------------------------------------*/
void send_TCPData(uint8_t* msg,uint8_t len);
/*---------------------------------------------------------------------------*/
uint16_t waitTCPMessage_blocking();
/*---------------------------------------------------------------------------*/
uint16_t StrTo16Uint(char * str);
/*---------------------------------------------------------------------------*/
uint16_t fill_tcp_data_len(uint8_t *buf,uint16_t pos, const uint8_t *s, uint8_t len);
/*---------------------------------------------------------------------------*/
uint16_t fill_tcp_data(uint8_t *buf,uint16_t pos, const char *s);
/*---------------------------------------------------------------------------*/