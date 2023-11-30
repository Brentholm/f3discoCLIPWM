/*
 * level_accel.c
 *
 *  Created on: Nov 23, 2023
 *      Author: holmb
 * @file level_accel.c
 * @brief Functions and structures for handling the accelerometer
 */
 
#include <stdint.h>
#include "stm32f3_discovery_accelerometer.h"
#include "level_accel.h"


// declare an instance of array of 3 uint16_t's to hold the raw accelerometer data
uint16_t raw_accel_data[3];

// declare an instance of the struct to hold the accel data in milli-g's
accel_data_t accel_data;

// declare an array of structs that can hold up to 100 accel data readings
accel_data_t accel_data_array[100];

/*
* @brief Read the accelerometer data once and move it into a struct
* @param raw_accel_data[] pointer to an array of 3 uint16_t's to hold the raw accelerometer data the supplied driver fills
* @param accel_data pointer to a struct to hold the accel data in milli-g's
* @returnval None
*/
void ReadAccelData(int16_t* raw_accel_data, accel_data_t* accel_data)
{
    // Read the accelerometer data
    BSP_ACCELERO_GetXYZ(raw_accel_data);

    // Convert the raw data to milli-g's
    accel_data->x = raw_accel_data[0];
    accel_data->y = raw_accel_data[1];
    accel_data->z = raw_accel_data[2];
}

void ReadAccelDataArray(int16_t* raw_accel_data, accel_data_t* accel_data_array, int N)
{
	if (N > 100)
		N= 100;  //bounds check
	for (int i = 0; i < N; i++)
	{
		// Read the accelerometer data
		BSP_ACCELERO_GetXYZ(raw_accel_data);
		HAL_Delay(10);

		// Convert the raw data to milli-g's and store it in the array of structs
		accel_data_array[i].x = raw_accel_data[0];
		accel_data_array[i].y = raw_accel_data[1];
		accel_data_array[i].z = raw_accel_data[2];
	}
}

