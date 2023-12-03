/*
 * level_accel.c
 *
 *  Created on: Nov 23, 2023
 *      Author: holmb
 * @file level_accel.c
 * @brief Functions and structures for handling the accelerometer
 */
 
#include <stdint.h>
#include <math.h>
#include "stm32f3_discovery_accelerometer.h"
#include "level_accel.h"


// declare an instance of array of 3 uint16_t's to hold the raw accelerometer data
int16_t raw_accel_data[3];

// declare an instance of the struct to hold the accel data in milli-g's
accel_data_t accel_Value_struct;

// array of structs that can hold up to 100 accel data readings
accel_data_t accel_data_array[100];

// pointer to struct with five floats to hold the averages and angles accel data
accel_math_t* accel_math = {0};


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

		//store the individual x, y, z reading to in the array of structs
		accel_data_array[i].x = raw_accel_data[0];
		accel_data_array[i].y = raw_accel_data[1];
		accel_data_array[i].z = raw_accel_data[2];
	}
}

void AverageAccelData(accel_data_t* accel_data_array, accel_math_t* accel_results, int N)
{
	if (N > 100)
		N= 100;  //bounds check
	int32_t x_sum = 0;
	int32_t y_sum = 0;
	int32_t z_sum = 0;
	for (int i = 0; i < N; i++)
	{
		x_sum += accel_data_array[i].x;
		y_sum += accel_data_array[i].y;
		z_sum += accel_data_array[i].z;
	}
	accel_results->x_avg = x_sum / N;
	accel_results->y_avg = y_sum / N;
	accel_results->z_avg = z_sum / N;

	accel_results->horiz_angle = atan2(accel_results->x_avg, accel_results->y_avg);
	accel_results->vert_angle = atan2(accel_results->y_avg, accel_results->x_avg);
}

