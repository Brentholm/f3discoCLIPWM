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
int16_t rawAccelData[3];

// declare an instance of the struct to hold the accel data in milli-g's
AccelData_t accelValueStruct;

// array of structs that can hold up to 100 accel data readings
AccelData_t accelDataArray[100]= {0};

// pointer to struct with five floats to hold the averages and angles accel data
AccelCalculations_t* accelMath = {0} ;


/*
* @brief Read the accelerometer data once and move it into a struct
* @param rawAccelData[] pointer to an array of 3 uint16_t's to hold the raw accelerometer data the supplied driver fills
* @param accel_data pointer to a struct to hold the accel data in milli-g's
* @returnval None
*/
void ReadAccelData(int16_t* rawAccelData, AccelData_t* accel_data)
{
    // Read the accelerometer data
    BSP_ACCELERO_GetXYZ(rawAccelData);

    // Move the returned array elements into their specific struct fields
    accel_data->x = rawAccelData[0];
    accel_data->y = rawAccelData[1];
    accel_data->z = rawAccelData[2];
}

void ReadAccelDataArray(int16_t* rawAccelData, AccelData_t* accelDataArray, int N)
{
	if (N > 100)
		N= 100;  //bounds check
	for (int i = 0; i < N; i++)
	{
		// Read the accelerometer data
		BSP_ACCELERO_GetXYZ(rawAccelData);
		HAL_Delay(10);

		//store the individual x, y, z reading to in the array of structs
		accelDataArray[i].x = rawAccelData[0];
		accelDataArray[i].y = rawAccelData[1];
		accelDataArray[i].z = rawAccelData[2];
	}
}

/// @brief
/// @param accel_data_array, a pointer to an array of struct that holds instances of x, y, and z
/// @param accel_results, a pointer to a struct that holds the averages and angles of the accel data
/// @param N, the number of data points to average
void AverageAccelData(AccelData_t* samplesArray, AccelCalculations_t* results, int32_t N)
{
	if (N > 100)
		N= 100;  //bounds check
	int32_t x_sum = 0;
	int32_t y_sum = 0;
	int32_t z_sum = 0;
	/*float xAvg = 0;
	float yAvg = 0;
	float zAvg = 0;
	float hTan = 0;
	float vTan = 0;*/
	for (int i = 0; i < N; i++)
	{
		x_sum += samplesArray[i].x;
		y_sum += samplesArray[i].y;
		z_sum += samplesArray[i].z;
	}
	(*results).x_avg = (float)x_sum / N;
	(*results).y_avg = (float)y_sum / N;
	(*results).z_avg = (float)z_sum / N;
	/*results->x_avg = (float)x_sum / N;
	results->y_avg = (float)y_sum / N;
	results->z_avg = (float)z_sum / N;*/
	/*xAvg = (float)x_sum / N;
	yAvg = (float)y_sum / N;
	zAvg = (float)z_sum / N;
*/
	results->horiz_angle = atan2(results->x_avg, results->y_avg);
	results->vert_angle  = atan2(results->y_avg, results->x_avg);
	/*hTan = atan2(xAvg, zAvg)* RADIANS_TO_DEGREES;
	vTan = atan2(zAvg, xAvg)* RADIANS_TO_DEGREES;*/
}

