/*
 * level_accel.h
 *
 *  Created on: Nov 23, 2023
 *      Author: holmb
 */

#ifndef INC_LEVEL_ACCEL_H_
#define INC_LEVEL_ACCEL_H_

// struct for holding the three accel values which are each int16_t (2 bytes), one for x, y, and z
// note that the values emerge as left-justified so in 2g fullscale mode expect +1g = 16000 counts and -1g = -16000 counts
// that is, 1000 milli-g's left-shifted by 4 bits
typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} accel_data_t;

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
} accel_math_t;

// function prototypes
// function that reads the accel and also stuffs the x, y and z values into the structure at the second address provided
void ReadAccelData(int16_t* raw_accel_data, accel_data_t * accel_data);
// function that reads the accel N times and stores each reading in an array of structs
void ReadAccelDataArray(int16_t* raw_accel_data, accel_data_t * accel_data_array, int N);

// function that averages the array of data read in by ReadAccelDataArray;
void AverageAccelData(accel_data_t* accel_data_array, accel_math_t* accel_results, int N);




#endif /* INC_LEVEL_ACCEL_H_ */
