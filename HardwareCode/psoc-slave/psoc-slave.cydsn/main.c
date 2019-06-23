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
#include "project.h"
#include "stdio.h"
#include "MasterComm.h"
#include "Buttons.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    FlexSensorSetup();
    GripSimulationSetup();
    HapticFeedbackSetup();
    MasterCommSetup();
    ButtonsSetup();
    
    UART_PutString("Setup Complete\n");
    
    for(;;)
    {
        MasterCommLoop();
        FlexSensorLoop();
        ButtonsLoop(); // For testing purposes
    }
}

/* [] END OF FILE */
