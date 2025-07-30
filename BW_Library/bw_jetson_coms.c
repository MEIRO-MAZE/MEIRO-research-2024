/*==============================================================================================
								    PROJECT MEIRO
							   JETSON CAMERA RECEIVER
==============================================================================================*/

#include "bw_jetson_coms.h"

void UART4_Init(uint32_t baudrate)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;  // Pins 6 (TX) and 7 (RX) are used
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 			// the pins are configured as alternate function so the USART peripheral has access to them
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// this defines the IO speed and has nothing to do with the baudrate!
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			// this defines the output type as push pull mode (as opposed to open drain)
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			// this activates the pullup resistors on the IO pins
	GPIO_Init(GPIOC, &GPIO_InitStructure);					// now all the values are passed to the GPIO_Init() function which sets the GPIO registers

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4); // Tx
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4); // Rx

	USART_InitStructure.USART_BaudRate = baudrate;				// the baudrate is set to the value we passed into this init function
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; // we want the data frame size to be 8 bits (standard)
	USART_InitStructure.USART_StopBits = USART_StopBits_1;		// we want 1 stop bit (standard)
	USART_InitStructure.USART_Parity = USART_Parity_No;		    // we don't want a parity bit (standard)
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // we don't want flow control (standard)
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; // we want to enable the transmitter and the receiver
	USART_Init(UART4, &USART_InitStructure);					// again all the properties are passed to the USART_Init function which takes care of all the bit setting

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE); // enable the USART3 receive interrupt

	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;		 // we want to configure the USART6 interrupts
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group of the USART6 interrupts
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		 // this sets the subpriority inside the group
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			 // the USART6 interrupts are globally enabled
	NVIC_Init(&NVIC_InitStructure);							 // the properties are passed to the NVIC_Init function which takes care of the low level stuff

	USART_Cmd(UART4, ENABLE);
}

void UART4_IRQHandler(void)
{
	if( USART_GetITStatus(UART4, USART_IT_RXNE) != RESET )
	{
		received_char = UART4->DR;
		char static last_data;
		static uint8_t data[4];
		static uint8_t index;

		switch(USART_Jetson)
		{
			case 1:	data[index++]=UART4->DR;
					if(index ==4)
					{
						jetson_x = (data[0]<<24)|(data[1]<<16)|(data[2]<<8)|data[3];
						USART_Jetson+=1;
						index=0;
					}
					break;
			case 2:	data[index++] = UART4->DR;
					if(index ==4)
					{
						jetson_y = (data[0]<<24)|(data[1]<<16)|(data[2]<<8)|data[3];
						USART_Jetson+=63;
						index=0;
					}
					break;
		}
		if(received_char==COMMAND_FLAG_B && last_data==COMMAND_FLAG_A) USART_Jetson=1;
		last_data=received_char;
	}
}

//Untuk cek USART
void check_usart_error()
{
	while (1)
	{
		uint32_t sr = UART4->SR;

		if((UART4->SR & USART_SR_RXNE) != 0)
		{
			jetson_angle_tilt = 125;
			lcd_display_clear();
			while (1)
			{
				lcd_gotoxy(0,1);sprintf(lcd,"yeay");lcd_putstr(lcd);
			}
		}
		// Check for error flags
		if (sr & USART_SR_ORE)
		{
			// Overrun Error (ORE) occurred
			lcd_display_clear();
			while (1)
			{
				lcd_gotoxy(0,1);sprintf(lcd,"ORE");lcd_putstr(lcd);
			}
		}
		if (sr & USART_SR_NE)
		{
			// Noise Error (NE) occurred
			lcd_display_clear();
			while (1)
			{
				lcd_gotoxy(0,1);sprintf(lcd,"NE");lcd_putstr(lcd);
			}
		}
		if (sr & USART_SR_FE)
		{
			// Framing Error (FE) occurred
			lcd_display_clear();
			while (1)
			{
				lcd_gotoxy(0,1);sprintf(lcd,"FE");lcd_putstr(lcd);
			}
		}
		if (sr & USART_SR_PE)
		{
			// Parity Error (PE) occurred
			lcd_display_clear();
			while (1)
			{
				lcd_gotoxy(0,1);sprintf(lcd,"PE");lcd_putstr(lcd);
			}
		}
		lcd_display_clear();
		lcd_gotoxy(0,0);sprintf(lcd,"AMAN");lcd_putstr(lcd);
		delay_ms(250);
	}
}

void Display_Camera_Value()
{
	lcd_display_clear();
	lcd_gotoxy(0,0);sprintf(lcd,"  CAMERA VALUE  ");lcd_putstr(lcd);
	lcd_gotoxy(0,1);sprintf(lcd,"CNTR X : %d",jetson_x);lcd_putstr(lcd);
	lcd_gotoxy(0,2);sprintf(lcd,"CNTR Y : %d",jetson_y);lcd_putstr(lcd);
	delay_ms(50);
}
