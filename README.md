# f3discoCLI
making embedded systems command line interface project
## Week 5 Submission - Add a command line interface

### Brent Holm     


Overview: Used CubeMX to create a basic project for my board, the STM32F3Discovery. Turned on USART1 because it's wired to the Virtual COM port on the built-in debugger on the board. Pulled in command line interface files from [eleciawhite/reusable](https://github.dev/eleciawhite/reusable/tree/master/source)

The main edits to port the CLI to the STM32 platform went in to:  
eConsoleError ConsoleIoReceive(uint8_t* buffer, const uint32_t bufferLength, uint32_t *readLength) 

Commands implemented include:

- acx _a dummy command that will eventually read the onboard accel x-direction_
- acy _a dummy command that will eventually read the onboard accel y-direction_
- acz _a dummy command that will eventually read the onboard accel z-direction_
- leds _test the LEDs by lighting all 8 of them in a chasing circle then back off the same way_
- buts _test the button by printing its status to the console_

 

