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

#ifndef BUTTONS_H
    #define BUTTONS_H
    
    #include "MasterComm.h"
    
    extern int PSoC_Button_ISR_Flag;
    
    extern void ButtonsSetup();
    extern void ButtonsLoop();
    
#endif

/* [] END OF FILE */
