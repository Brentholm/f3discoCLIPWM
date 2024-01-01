// Console IO is a wrapper between the actual in and output and the console code
// In an embedded system, this might interface to a UART driver.

#include "consoleIo.h"
#include <stdio.h>
#include "usart.h"
#include "consoleCommands.h"

uint8_t ch = 0; // received individual character
uint8_t rx_buffer[CONSOLE_COMMAND_MAX_LENGTH]; // buffer for received commands
uint8_t rx_write = 0; // counter to keep track of write position
uint8_t rx_read = 0; // counter to keep track of read position
//taken together, the functions in this file implement a circular buffer
//the buffer is used to store received characters the ConsoleProcess function is called
// which is once per pass through the main loop.  

/*
@brief calculates the length of the receive buffer
@param None
@return  the length of the buffer in bytes
*/
uint8_t RXLength(){
	uint8_t t = 0;
	t = (rx_write - rx_read) & (CONSOLE_COMMAND_MAX_LENGTH -1);
	return t;
}

/*
@brief writes the received character to the buffer rxbuffer, provided there's room
@param None
@return SUCCESS OR ERROR as an enum, defined in consoleIo.h
*/
uint8_t RXWrite(){
	if (RXLength() == (CONSOLE_COMMAND_MAX_LENGTH -1)){ return CONSOLE_ERROR;} //Buffer Full
	rx_buffer[rx_write] = ch; // load each character to buffer
	rx_write = (rx_write + 1) & (CONSOLE_COMMAND_MAX_LENGTH -1); // Increment and wrap when necessary
	return CONSOLE_SUCCESS;
}

/*
@brief reads bytes from the buffer rxbuffer, provided there's something there
@param None
@return the character read from the buffer
*/
uint8_t RXRead(){
	uint8_t t = 0;
	if (RXLength() == 0 ) {return '\n';} //Buffer Empty
	t = rx_buffer[rx_read];  // Return each character from rx_Buffer.
	rx_read = (rx_read+1) & (CONSOLE_COMMAND_MAX_LENGTH -1); //Increment and wrap
	return t;
}

/*
@brief callback function for the UART receive interrupt
@param huart pointer to the UART handle
@return None
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
 {
	RXWrite(); //Write character to rx_buffer.
	HAL_UART_Transmit_IT(&huart1, (uint8_t*)&ch, 1);  //echo the character back to the console
    HAL_UART_Receive_IT(huart, &ch, 1); // continue receiving character(s)
}

/*
@brief function called by ConsoleProcess, this will move characters from the circular buffer 'rx_buffer' to the command buffer 'buffer 
@param buffer pointer to the buffer to hold the command
@param bufferLength the length of the buffer
@param readLength pointer to the variable to hold the number of bytes read
@return SUCCESS OR ERROR as an enum, defined in consoleIo.h
*/
eConsoleError ConsoleIoReceive(uint8_t *buffer, const uint32_t bufferLength, uint32_t *readLength)
{
	uint32_t i = 0;
	uint8_t xch;

	xch = RXRead();
	while ( (xch != '\n') && ( i < bufferLength ) )
		{
			buffer[i] = (uint8_t) xch;
			i++;
			xch = RXRead();
		}
		*readLength = i;
		return CONSOLE_SUCCESS;
}

/*
@brief initializes the UART for console IO in interrupt mode
@param None
@return SUCCESS OR ERROR as an enum, defined in consoleIo.h
*/
eConsoleError ConsoleIoInit(void)
{
	HAL_UART_Receive_IT(&huart1, &ch, 1); // initiate reception
	return CONSOLE_SUCCESS;
}

/*
@brief sends a string to the console
@note this function exists as a bridge between the console code and the actual output
@note here it is implemented as a wrapper to printf
@note but it could also be implemented as a wrapper to a UART driver, such as HAL_UART_Transmit
@param buffer pointer to the buffer to hold the command
@return SUCCESS OR ERROR as an enum, defined in consoleIo.h
*/
eConsoleError ConsoleIoSendString(const char *buffer)
{
	printf("%s", buffer);
	return CONSOLE_SUCCESS;
}

