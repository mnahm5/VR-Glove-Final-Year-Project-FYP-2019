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

#include "Buttons.h"

int PSoC_Button_ISR_Flag = FALSE;
CY_ISR(PSoC_Button_ISR)
{
    PSoC_Button_ISR_Flag = TRUE;
}
int test_number = 0;

void ButtonsSetup()
{
    //PSoC_Button_Interrupt_StartEx(PSoC_Button_ISR);
    /* 
    PSoC Button always registers a pulse when the PSoC is restarted (probably noise).
    Hence we reset the button flag after 100 ms to avoid registering this pulse.
    */
    CyDelay(100);
    PSoC_Button_ISR_Flag = FALSE;
}

void ButtonsLoop()
{
    if (PSoC_Button_ISR_Flag == TRUE)
    {
        UART_PutString("PSoC_Button_ISR_Flag\n");
        //Blue_LED_Write(~Blue_LED_Read());
        PSoC_Button_ISR_Flag = FALSE;
        
        //Blue_LED_Write(~Blue_LED_Read());
        
        switch(test_number)
        {
            case 0:
                GripSimulationPush(1);
                break;
            case 1:
                GripSimualtionPull(1);
                break;
            case 2:
                GripSimulationOff(1);
                break;
        }
        test_number++;
        if (test_number > 2) test_number = 0;
    }
}

/* [] END OF FILE */
