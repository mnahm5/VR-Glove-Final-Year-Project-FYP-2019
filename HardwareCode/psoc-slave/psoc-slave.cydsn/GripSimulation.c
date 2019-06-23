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

#include "GripSimulation.h"

void GripSimulationSetup()
{
    Grip_Control_En_Write(0);
    Grip_Control_Out_Write(0);
    UART_PutString("GripSimulation Setup\n");
}

void GripSimulationReset()
{
    Grip_Control_En_Write(0);
    Grip_Control_Out_Write(0);
    UART_PutString("GripSimulation Reset\n");
}

void GripSimulationPush(int finger)
{
    UART_PutString("Push\n");
    Grip_Control_En_Write(Grip_Control_En_Read() & ~finger);
    Grip_Control_Out_Write(Grip_Control_Out_Read() | finger);
    Grip_Control_En_Write(Grip_Control_En_Read() | finger);
}

void GripSimualtionPull(int finger)
{
    UART_PutString("Pull\n");
    Grip_Control_En_Write(Grip_Control_En_Read() & ~finger);
    Grip_Control_Out_Write(Grip_Control_Out_Read() & ~finger);
    Grip_Control_En_Write(Grip_Control_En_Read() | finger);
}

void GripSimulationOff(int finger)
{
    UART_PutString("Off\n");
    Grip_Control_En_Write(Grip_Control_En_Read() & ~finger);
}

void GripSimulationParseCmd(char* cmd)
{
    if (strlen(cmd) == 5)
    {
        int choosenFinger = cmd[2] - '0';
        int cmdValue = cmd[4] - '0';
        int choosenFingerInBitFormat = 0;
        
        switch (choosenFinger)
        {
            case HAPTIC_INDEX:
                choosenFingerInBitFormat = INDEX;
                break;
            case HAPTIC_THUMB:
                choosenFingerInBitFormat = THUMB;
                break;
            default:
                return;
        }
        
        switch (cmdValue)
        {
            case 0:
                GripSimualtionPull(choosenFingerInBitFormat);
                break;
            case 1:
                GripSimulationPush(choosenFingerInBitFormat);
                break;
            default:
                GripSimulationOff(choosenFingerInBitFormat);
                break;
        }
    }
    else
    {
        UART_PutString("G: Incorrect format for cmd\n");
    }
}

/* [] END OF FILE */
