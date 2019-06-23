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

#ifndef GRIP_SIMULATION_H
    #define GRIP_SIMULATION_H
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h.>
    #include <string.h>
    #include "project.h"
    #include "HapticFeedback.h"
    
    #define INDEX 1
//    #define MIDDLE 2
//    #define RING 4
//    #define PINKY 8
    #define THUMB 2
    
    extern void GripSimulationSetup();
    extern void GripSimulationReset();
    
    extern void GripSimulationParseCmd(char* cmd);
    extern void GripSimulationPush(int finger);
    extern void GripSimualtionPull(int finger);
    extern void GripSimulationOff(int finger);
    
#endif

/* [] END OF FILE */
