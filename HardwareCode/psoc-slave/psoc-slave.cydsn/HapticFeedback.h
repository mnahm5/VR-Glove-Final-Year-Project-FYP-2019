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

#ifndef HAPTIC_FEEDBACK_H
    #define HAPTIC_FEEDBACK_H
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h.>
    #include <string.h>
    #include "project.h"
    
    #define HAPTIC_INDEX 0
    #define HAPTIC_MIDDLE 1
    #define HAPTIC_RING 2
    #define HAPTIC_PINKY 3
    #define HAPTIC_THUMB 4
    
    extern void HapticFeedbackSetup();
    extern void HapticFeedbackReset();
    
    extern void HapticFeedbackParseCmd(char* cmd);
    
#endif

/* [] END OF FILE */
