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

#include "HapticFeedback.h"

void HapticFeedbackSetup()
{
    PWM_Index_Middle_Start();
    PWM_Ring_Pinky_Start();
    PWM_Thumb_Start();
    PWM_Index_Middle_WriteCompare1(0);
    PWM_Index_Middle_WriteCompare2(0);
    PWM_Ring_Pinky_WriteCompare1(0);
    PWM_Ring_Pinky_WriteCompare2(0);
    PWM_Thumb_WriteCompare(0);
    UART_PutString("Haptic Feedback Setup\n");
}

void HapticFeedbackReset()
{
    PWM_Index_Middle_WriteCompare1(0);
    PWM_Index_Middle_WriteCompare2(0);
    PWM_Ring_Pinky_WriteCompare1(0);
    PWM_Ring_Pinky_WriteCompare2(0);
    PWM_Thumb_WriteCompare(0);
    UART_PutString("Haptic Feedback Reset\n");
}
    
void HapticFeedbackParseCmd(char* cmd)
{
    if (strlen(cmd) == 5)
    {
        int choosenFinger = cmd[2] - '0';
        int cmdValue = cmd[4] - '0';
        int pwmValue = 0;
        switch (cmdValue)
        {
            case 0:
                pwmValue = 0;
                break;
            case 1:
                pwmValue = 120;
                break;
            default:
                pwmValue = 0;
                break;
        }
        switch (choosenFinger)
        {
            case HAPTIC_INDEX:
                PWM_Index_Middle_WriteCompare1(pwmValue);
                break;
            case HAPTIC_MIDDLE:
                PWM_Index_Middle_WriteCompare2(pwmValue);
                break;
            case HAPTIC_RING:
                PWM_Ring_Pinky_WriteCompare1(pwmValue);
                break;
            case HAPTIC_PINKY:
                PWM_Ring_Pinky_WriteCompare2(pwmValue);
                break;
            case HAPTIC_THUMB:
                PWM_Thumb_WriteCompare(pwmValue);
                break;
        }
        char out[20];
        sprintf(out, "H-%d-%d\n", choosenFinger, pwmValue);
        UART_PutString(out);
    }
    else
    {
        UART_PutString("H: Incorrect format for cmd\n");
    }
}

/* [] END OF FILE */
