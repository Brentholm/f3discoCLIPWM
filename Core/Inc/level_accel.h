/*
 * level_accel.h
 *
 *  Created on: Nov 23, 2023
 *      Author: holmb
 */

#ifndef INC_LEVEL_ACCEL_H_
#define INC_LEVEL_ACCEL_H_

// create a struct for holding the three accel values which are each int16_t (2 bytes), one for x, y, and z
// note that the values emerge as left-justified so in 2g fullscale mode expect +1g = 16000 counts and -1g = -16000 counts
typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} accel_data_t;

// function prototypes
// function that reads the accel and also stuffs the x, y and z values into the structure at the second address provided
void ReadAccelData(int16_t* raw_accel_data, accel_data_t * accel_data);
// function that reads the accel N times and stores each reading in an array of structs
void ReadAccelDataArray(int16_t* raw_accel_data, accel_data_t * accel_data_array, int N);



#endif /* INC_LEVEL_ACCEL_H_ */
