// Console IO is a wrapper between the actual in and output and the console code
// In an embedded system, this might interface to a UART driver.

#include "consoleIo.h"
#include <stdio.h>
#include "usart.h"

//use the windows conio.h for kbhit, or a POSIX reproduction

//their original
/*static int getch_noblock() {
    if (_kbhit())
        return _getch();
    else
        return EOF;
}*/


eConsoleError ConsoleIoInit(void)
{
	return CONSOLE_SUCCESS;
}

//this is where the main edits went to make this code portable to STM32:
eConsoleError ConsoleIoReceive(uint8_t* buffer, const uint32_t bufferLength, uint32_t *readLength)
{
    uint32_t i = 0;
    uint8_t rxByte = 0;

 //sit and spin here in case the UART is not yet ready
 while (HAL_UART_GetState(&huart1) != HAL_UART_STATE_READY);

 //HAL_UART_Receive is blocking. It will sit and spin here for 2^32 or 4 billion ms, OR until a character arrives
 if (HAL_OK != HAL_UART_Receive(&huart1, &rxByte, 1, HAL_MAX_DELAY))
 {
  return CONSOLE_ERROR;
 }

 /* Send echo */
 HAL_UART_Transmit(&huart1, (uint8_t*)&rxByte, 1, HAL_MAX_DELAY);

 buffer[i] = rxByte;
 i++;


 *readLength = i;

 return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoSendString(const char *buffer)
{
	printf("%s", buffer);
	return CONSOLE_SUCCESS;
}

