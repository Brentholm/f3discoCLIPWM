/*
 * level_accel.h
 *
 *  Created on: Nov 23, 2023
 *      Author: holmb
 */

#ifndef INC_LEVEL_ACCEL_H_
#define INC_LEVEL_ACCEL_H_

#define RADIANS_TO_DEGREES (180/3.14159)

// struct for holding the three accel values which are each int16_t (2 bytes), one for x, y, and z
// note that the values emerge as left-justified so in 2g fullscale mode expect +1g = 16000 counts and -1g = -16000 counts
// that is, 1000 milli-g's left-shifted by 4 bits
typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} AccelData_t;

// struct for holding math results
// average in three dimensions as floats
// arc-tangent of the average of the x and y components for "horizontal" angle
// arc-tangent of the average of the y and x components for "vertical" angle
typedef struct {
    float x_avg;
    float y_avg;
    float z_avg;
    float horiz_angle;
    float vert_angle;
} AccelCalculations_t;

//data types for Accelerometer
extern int16_t rawAccelData[3];          //3 sixteen-bit integers produced by the HAL call to the accelerometer read function
extern AccelData_t accelValueStruct;     //structure to contain accelerometer data organized with an x, y, and z member
extern AccelData_t accelDataArray[100];  //array of the x,y, and z values to be used for further signal processing (averaging)
extern AccelCalculations_t* accelMath;   //struct to hold the average of each component x_avg, y_avg, z_avg plus computed angles.


// function prototypes
// function that reads the accel once and stores the x, y and z values into the structure at the second address provided
void ReadAccelData(int16_t* rawAccelData, AccelData_t * accel_data);
// function that reads the accel N times and stores each x, y, and z in an array of structs
void ReadAccelDataArray(int16_t* rawAccelData, AccelData_t* accelDataArray, int N);
// function that averages the array of data read in by ReadAccelDataArray;
void AverageAccelData(AccelData_t* samplesArray, AccelCalculations_t* results, int32_t N);
//void AverageAccelData(AccelData_t* samplesArray, AccelCalculations_t* results, int32_t N)



#endif /* INC_LEVEL_ACCEL_H_ */
