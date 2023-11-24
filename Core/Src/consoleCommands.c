// ConsoleCommands.c
// This is where you add commands:
//		1. Add a protoype
//			static eCommandResult_T ConsoleCommandVer(const char buffer[]);
//		2. Add the command to mConsoleCommandTable
//		    {"ver", &ConsoleCommandVer, HELP("Get the version string")},
//		3. Implement the function, using ConsoleReceiveParam<Type> to get the parameters from the buffer.

#include <string.h>
#include "consoleCommands.h"
#include "console.h"
#include "consoleIo.h"
#include "version.h"
#include "stm32f3_discovery_accelerometer.h"
#include "LedRelated.h"
#include "level_accel.h"

//extern CompassLed_t myLedStructArray;

#define IGNORE_UNUSED_VARIABLE(x)     if ( &x == &x ) {}

static eCommandResult_T ConsoleCommandComment(const char buffer[]);
static eCommandResult_T ConsoleCommandVer(const char buffer[]);
static eCommandResult_T ConsoleCommandHelp(const char buffer[]);
static eCommandResult_T ConsoleCommandParamExampleInt16(const char buffer[]);
static eCommandResult_T ConsoleCommandParamExampleHexUint16(const char buffer[]);
static eCommandResult_T ConsoleCommandReadAccelS(const char buffer[]);
static eCommandResult_T ConsoleCommandReadAccelA(const char buffer[]);
static eCommandResult_T ConsoleCommandReadAccelZ(const char buffer[]);
static eCommandResult_T ConsoleCommandReadAccel(const char buffer[]);
static eCommandResult_T ConsoleCommandLedsRose(const char buffer[]);
static eCommandResult_T ConsoleCommandLedsRocker(const char buffer[]);
static eCommandResult_T ConsoleCommandButtonState(const char buffer[]);

static const sConsoleCommandTable_T mConsoleCommandTable[] =
{
    {";", &ConsoleCommandComment, HELP("Comment! You do need a space after the semicolon. ")},
    {"help", &ConsoleCommandHelp, HELP("Lists the commands available")},
    {"ver", &ConsoleCommandVer, HELP("Get the version string")},
    {"int", &ConsoleCommandParamExampleInt16, HELP("How to get a signed int16 from params list: int -321")},
    {"u16h", &ConsoleCommandParamExampleHexUint16, HELP("How to get a hex u16 from the params list: u16h aB12")},
	{"acs" , &ConsoleCommandReadAccelS, HELP("reads accel once, puts values in struct, reports that struct")},
	{"aca" , &ConsoleCommandReadAccelA, HELP("Reads the accel N times and prints each one to the console")},
	{"acz" , &ConsoleCommandReadAccelZ, HELP("Reports the current Acceleration (z-direction) in milli-g")},
	{"acc" , &ConsoleCommandReadAccel, HELP("reports the current 3 axis acceleration")},
	{"leds" ,&ConsoleCommandLedsRose, HELP("Briefly flashes the 8 LEDs to show they are working")},
	{"rokr" ,&ConsoleCommandLedsRocker, HELP("LED teeter totter for ~2seconds")},
	{"buts",&ConsoleCommandButtonState, HELP("Prints the present state of the Blue user button")},
	CONSOLE_COMMAND_TABLE_END // must be LAST
};

static eCommandResult_T ConsoleCommandComment(const char buffer[])
{
	// do nothing
	IGNORE_UNUSED_VARIABLE(buffer);
	return COMMAND_SUCCESS;
}

static eCommandResult_T ConsoleCommandHelp(const char buffer[])
{
	uint32_t i;
	uint32_t tableLength;
	eCommandResult_T result = COMMAND_SUCCESS;

    IGNORE_UNUSED_VARIABLE(buffer);

	tableLength = sizeof(mConsoleCommandTable) / sizeof(mConsoleCommandTable[0]);
	for ( i = 0u ; i < tableLength - 1u ; i++ )
	{
		ConsoleIoSendString(mConsoleCommandTable[i].name);
#if CONSOLE_COMMAND_MAX_HELP_LENGTH > 0
		ConsoleIoSendString(" : ");
		ConsoleIoSendString(mConsoleCommandTable[i].help);
#endif // CONSOLE_COMMAND_MAX_HELP_LENGTH > 0
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}

static eCommandResult_T ConsoleCommandParamExampleInt16(const char buffer[])
{
	int16_t parameterInt;
	eCommandResult_T result;
	result = ConsoleReceiveParamInt16(buffer, 1, &parameterInt);
	if ( COMMAND_SUCCESS == result )
	{
		ConsoleIoSendString("Parameter is ");
		ConsoleSendParamInt16(parameterInt);
		ConsoleIoSendString(" (0x");
		ConsoleSendParamHexUint16((uint16_t)parameterInt);
		ConsoleIoSendString(")");
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}
static eCommandResult_T ConsoleCommandParamExampleHexUint16(const char buffer[])
{
	uint16_t parameterUint16;
	eCommandResult_T result;
	result = ConsoleReceiveParamHexUint16(buffer, 1, &parameterUint16);
	if ( COMMAND_SUCCESS == result )
	{
		ConsoleIoSendString("Parameter is 0x");
		ConsoleSendParamHexUint16(parameterUint16);
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}

static eCommandResult_T ConsoleCommandVer(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;
    IGNORE_UNUSED_VARIABLE(buffer);
	ConsoleIoSendString(VERSION_STRING);
	ConsoleIoSendString(STR_ENDLINE);
	return result;
}

static eCommandResult_T ConsoleCommandReadAccelS(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;
	IGNORE_UNUSED_VARIABLE(buffer);
	int16_t accelData[3] = {0};
	accel_data_t accelValStruct = {0};
	ReadAccelData(accelData, &accelValStruct);
	ConsoleIoSendString("    x accel = ");
	ConsoleSendParamInt16(accelValStruct.x);
	ConsoleIoSendString("    y accel = ");
	ConsoleSendParamInt16(accelValStruct.y);
	ConsoleIoSendString("    z accel = ");
	ConsoleSendParamInt16(accelValStruct.z);
	ConsoleIoSendString(STR_ENDLINE);
	return result;

	ConsoleIoSendString(STR_ENDLINE);
	return result;
}

static eCommandResult_T ConsoleCommandReadAccelA(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;
	IGNORE_UNUSED_VARIABLE(buffer);
	int16_t accelData[3] = {0};
	accel_data_t accel_struct_array[100] = {0};
	int N=40;
	ReadAccelDataArray(accelData, accel_struct_array, N );
	ConsoleIoSendString("x, y, z ");
	ConsoleIoSendString(STR_ENDLINE);
	for (int i=0; i<N; i++)
	{
		ConsoleSendParamInt16(accel_struct_array[i].x);
		ConsoleIoSendString(" , ");
		ConsoleSendParamInt16(accel_struct_array[i].y);
		ConsoleIoSendString(" , ");
		ConsoleSendParamInt16(accel_struct_array[i].z);
		ConsoleIoSendString(STR_ENDLINE);
	}
	
	ConsoleIoSendString(STR_ENDLINE);
	return result;
}

static eCommandResult_T ConsoleCommandReadAccelZ(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;
	IGNORE_UNUSED_VARIABLE(buffer);
	ConsoleIoSendString("z = 3 ");
	ConsoleIoSendString(STR_ENDLINE);
	return result;
}

static eCommandResult_T ConsoleCommandReadAccel(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;
	IGNORE_UNUSED_VARIABLE(buffer);
	int16_t accelData[3] = {0};
	BSP_ACCELERO_GetXYZ(accelData);
	ConsoleIoSendString("x accel = ");
	ConsoleSendParamInt16(accelData[0]);
	ConsoleIoSendString("    y accel = ");
	ConsoleSendParamInt16(accelData[1]);
	ConsoleIoSendString("    z accel = ");
	ConsoleSendParamInt16(accelData[2]);
	ConsoleIoSendString(STR_ENDLINE);
	return result;
}

static eCommandResult_T ConsoleCommandLedsRocker(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;
	IGNORE_UNUSED_VARIABLE(buffer);
	ConsoleIoSendString("LEDs will light two at a time and cycle through 3 states representing a very crude teeter-totter ");
	ConsoleIoSendString(STR_ENDLINE);

	for (int i=1; i<21; i++)
	{
		switch(i%4)  // only spell out the ones that need to be turned ON
		{
		case 0:
		case 2:
		{
			//this is the horizontal case - light "east" and "west" LEDs
			SetLedState(&myLedStructArray[LD6_Green_W], LED_ON);
			SetLedState(&myLedStructArray[LD7_Green_E], LED_ON);
			break;
		}
		case 1:
		{
			//this is the left side high case - light "southeast" and "northwest" LEDs
			SetLedState(&myLedStructArray[LD9_Blue_SE], LED_ON);
			SetLedState(&myLedStructArray[LD4_Blue_NW], LED_ON);
			break;
		}
		case 3:
		{
			//this is the right  side high case - light "southwest" and "northeast" LEDs
			SetLedState(&myLedStructArray[LD8_Orange_SW], LED_ON);
			SetLedState(&myLedStructArray[LD5_Orange_NE], LED_ON);
			break;
		}
		}

		//write out the LEDs
		LedRoseUpdate(myLedStructArray,0);
		// turn them all off but don't write them out- they'll get updated next time through the loop
		LedRoseClearAll(myLedStructArray);
		HAL_Delay(250);
	}
		// clear them all and write them out
		LedRoseClearAll(myLedStructArray);
		LedRoseUpdate(myLedStructArray,0);
	return result;
}

static eCommandResult_T ConsoleCommandLedsRose(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;
	IGNORE_UNUSED_VARIABLE(buffer);
	ConsoleIoSendString("LEDs should light in a circular pattern and then extinguish the same way ");
	ConsoleIoSendString(STR_ENDLINE);
	LedRoseSetAll(myLedStructArray);
	LedRoseUpdate(myLedStructArray,50);
	HAL_Delay(50);
	LedRoseClearAll(myLedStructArray);
	LedRoseUpdate(myLedStructArray,50);
	return result;
}


static eCommandResult_T ConsoleCommandButtonState(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;
	IGNORE_UNUSED_VARIABLE(buffer);
	ConsoleIoSendString("the present state of the Blue user button is: ");
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)) {
		ConsoleIoSendString("DOWN, Depressed ");
	}
	else {
		ConsoleIoSendString("UP, Unpressed ");
	}
	ConsoleIoSendString(STR_ENDLINE);
	return result;
}

const sConsoleCommandTable_T* ConsoleCommandsGetTable(void)
{
	return (mConsoleCommandTable);
}


