/*==============================================================================================
								    PROJECT MEIRO
							   JETSON CAMERA RECEIVER
==============================================================================================*/

#ifndef BW_JETSON_COMS_H
#define BW_JETSON_COMS_H

#include "main.h"

//extern unsigned int RX_BUFFER_SIZE;

extern char COMMAND_FLAG_JETSON_A;
extern char COMMAND_FLAG_JETSON_B;
extern unsigned int COMMAND_FLAG_A;
extern unsigned int COMMAND_FLAG_B;
extern unsigned int USART_Jetson;
extern unsigned int jetson_x;
extern unsigned int jetson_y;
extern char received_char;

void UART4_Init(uint32_t baudrate);
void Display_Camera_Value();
void check_usart_error();

#endif




