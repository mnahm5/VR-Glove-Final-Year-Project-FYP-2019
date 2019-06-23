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
#ifndef MASTER_COMM_H
    #define MASTER_COMM_H
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h.>
    #include <string.h>
    #include "project.h"
    
    #include "FlexSensor.h"
    #include "GripSimulation.h"
    #include "HapticFeedback.h"
    
    #define TRUE 1u
    #define FALSE 0u
    
    #define BUFFER_SIZE 100u // Sets Buffers size
    #define PSOC_SLAVE_ADDRESS 0x07u

    uint8_t I2CSlaveDataIn[BUFFER_SIZE];
    uint8_t I2CSlaveDataOut[BUFFER_SIZE];
    
    char latestReceivedData[BUFFER_SIZE]; 
    uint8 byteCountAtLastReceiveTransmission;
    
    extern void MasterCommSetup();
    extern void MasterCommLoop();
    extern void MasterCommReset();
    
    extern void MasterCommGetReceivedData();
    extern void MasterCommParseReceivedData();
    extern void MasterCommSendData(char* data);
    
    extern int MasterCommSlaveFinishedReceiving();
    extern int MasterCommSlaveFinishedSending();
    
    /* -- FLEX SENSOR -- */
    extern uint FlexSensorData[NO_OF_SENSORS];
    extern void MasterCommSendFlexData();
    
#endif
/* [] END OF FILE */
