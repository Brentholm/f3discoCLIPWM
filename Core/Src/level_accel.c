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

#define RAD2DEG (180/3.14159)

//data types for Accelerometer
int16_t rawAccelData[3];                 //3 sixteen-bit integers produced by the HAL call to the accelerometer read function
AccelData_t accelValueStruct = {0} ;     //structure to contain accelerometer data organized with an x, y, and z member
AccelData_t accelDataArray[100]= {0};    //array of the x,y, and z values to be used for further signal processing (averaging)
AccelCalculations_t* accelMath = {0} ;   //struct to hold the average of each component x_avg, y_avg, z_avg plus computed angles.


/*
* @brief Read the accelerometer data once and move it into a struct
* @param rawAccelData[] pointer to an array of 3 uint16_t's to hold the raw accelerometer data the supplied driver fills
* @param accel_data pointer to a struct to hold the accel data in milli-g's
* @returnval None
* @note this function was written as a starting point and was generalized to a function that reads N times below
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

/* 
* @brief Read the accelerometer data N times and move it into an array of structs
* @param rawAccelData[] pointer to an array of 3 int16_t's to hold the raw accelerometer data the supplied driver fills
* @param accel_data_array pointer to an array of structs to hold the accel data 
* @param N the number of data points to read
* @returnval None
* @note there is an intentional 10ms delay between each reading to help insure the the readings are independent
* @note this function was written as an enhancement to the original ReadAccelData function to allow collecting multiple readings
* */

//these 3 DC bias constants function as a hard-coded system calibration
#define DC_BIAS_X (342)
#define DC_BIAS_Y (-1064)
#define DC_BIAS_Z (0)

void ReadAccelDataArray(int16_t* rawAccelData, AccelData_t* accelDataArray, int N)
{
	if (N > 100)
		N= 100;  //bounds check
	for (int i = 0; i < N; i++)
	{
		// Read the accelerometer data
		BSP_ACCELERO_GetXYZ(rawAccelData);
		HAL_Delay(10);

		//store the individual x, y, z reading to the array of structs
		accelDataArray[i].x = rawAccelData[0] - DC_BIAS_X;
		accelDataArray[i].y = rawAccelData[1] - DC_BIAS_Y;
		accelDataArray[i].z = rawAccelData[2] - DC_BIAS_Z;
	}
}

/*@brief Calculate the average along each dimension and then the angle using arctan of the accelerometer data
* @param accel_data_array, a pointer to an array of struct that holds instances of x, y, and z
* @param accel_results, a pointer to a struct that holds the averages and angles of the accel data
* @param N, the number of data points to average
 */

void AverageAccelData(AccelData_t* samplesArray, AccelCalculations_t* results, int32_t N)
{
	if (N > 100)
		N= 100;  //bounds check
	int32_t x_sum = 0;
	int32_t y_sum = 0;
	int32_t z_sum = 0;
	
	for (int i = 0; i < N; i++)
	{
		x_sum += samplesArray[i].x;
		y_sum += samplesArray[i].y;
		z_sum += samplesArray[i].z;
	}
	
	results->x_avg = (float)x_sum / N;
	results->y_avg = (float)y_sum / N;
	results->z_avg = (float)z_sum / N;
	
	results->horiz_angle = RAD2DEG * atan2(results->y_avg, results->x_avg);
	results->vert_angle  = -RAD2DEG * atan2(results->x_avg, results->y_avg);  //the minus sign gives the result we expect from calculus
																				// positive angles rotate counter-clockwise
	
}

