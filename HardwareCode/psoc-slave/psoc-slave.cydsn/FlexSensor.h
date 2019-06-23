/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef FLEX_SENSOR_H
    #define FLEX_SENSOR_H
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h.>
    #include <string.h>
    #include "project.h"
    
    #define NO_OF_SENSORS 10
    
    extern uint FlexSensorData[NO_OF_SENSORS];
    
    extern void FlexSensorSetup();
    extern void FlexSensorLoop();
    extern void FlexSensorReset();
    
    extern void FlexSensorAdcConvert();
    extern int movingAvg(int *ptrArrNumbers, long *ptrSum, int pos, int len, int nextNum);
    
#endif

/* [] END OF FILE */
