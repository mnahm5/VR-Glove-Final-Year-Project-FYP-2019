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

#include "FlexSensor.h"

int adc_result = 0;
int mux_select = 0;
char debug[200];

int a0;
int arrNumbers[10][25] = {0};
int pos[10] = {0};
int newAvg[10] = {0};
long sum[10] = {0};
int len = 25;


uint FlexSensorData[NO_OF_SENSORS] = { };

int movingAvg(int *ptrArrNumbers, long *ptrSum, int pos, int len, int nextNum)
{
  //Subtract the oldest number from the prev sum, add the new number
  *ptrSum = *ptrSum - ptrArrNumbers[pos] + nextNum;
  //Assign the nextNum to the position in the array
  ptrArrNumbers[pos] = nextNum;
  //return the average
  return *ptrSum / len;
}


void FlexSensorSetup()
{
    UART_Start();
    Opamp_Start();
    ADC_Start();
    Mux_Start();
    
    ADC_StartConvert();
    Mux_Select(mux_select);
    
    UART_PutString("FlexSensor Setup\n");
}

void FlexSensorLoop()
{

    FlexSensorAdcConvert();
    sprintf(debug,\
        "A0 = %d\tA1 = %d\tA2 = %d\tA3 = %d\tA4 = %d\tA5 = %d\tA6 = %d\tA7 = %d\tA8 = %d\tA9 = %d\n",\
        newAvg[0],newAvg[1],newAvg[2],newAvg[3],newAvg[4],newAvg[5],newAvg[6],newAvg[7],newAvg[8],newAvg[9]);
    UART_PutString(debug);
}

void FlexSensorReset()
{
    // Do Reset Stuff
    UART_PutString("FlexSensor Reset\n");
}

void FlexSensorAdcConvert() {
    if (ADC_IsEndConversion(ADC_RETURN_STATUS)) {
        adc_result = ADC_GetResult16();
        FlexSensorData[mux_select] = adc_result;
        mux_select++;
        if (mux_select > 9) mux_select = 0;
        Mux_Select(mux_select);
        
        for(int i = 0; i < 25; ++i) {
            newAvg[mux_select-1] = movingAvg(
                arrNumbers[mux_select-1], &sum[mux_select-1], pos[mux_select-1], len, FlexSensorData[mux_select-1]);
            pos[mux_select-1]++;
            if (pos[mux_select-1] >= len){
              pos[mux_select-1] = 0;
            }
        }
    }
}

/* [] END OF FILE */
