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

#include "MasterComm.h"

int i;

void MasterCommSetup()
{
    I2C_Slave_SlaveSetAddress(PSOC_SLAVE_ADDRESS);
    I2C_Slave_SlaveInitReadBuf((uint8 *) I2CSlaveDataOut, BUFFER_SIZE);
    I2C_Slave_SlaveInitWriteBuf((uint8 *) I2CSlaveDataIn, BUFFER_SIZE);
    
    I2C_Slave_Start();
    
    UART_PutString("MasterComm Setup\n");
}

void MasterCommLoop()
{
    if (MasterCommSlaveFinishedReceiving() == TRUE)
    {
        MasterCommGetReceivedData();
        MasterCommParseReceivedData();
    }
}

void MasterCommReset()
{
    // Do reset stuff
    I2C_Slave_SlaveClearReadBuf();
    UART_PutString("MasterComm Reset\n");
}

void MasterCommParseReceivedData()
{
//    UART_PutString(latestReceivedData);
//    UART_PutString("\n");
    if (strcmp((char*) latestReceivedData, "flexData") == 0)
    {
        MasterCommSendFlexData();
    }
    else if (strcmp((char*) latestReceivedData, "Done") == 0)
    {
        I2C_Slave_SlaveClearReadBuf();
    }
    else if (strcmp((char*) latestReceivedData, "Reset") == 0)
    {
        UART_PutString("\n\n\n\nPSoC Slave Reset\n\n\n");
        FlexSensorReset();
        GripSimulationReset();
        HapticFeedbackReset();
        MasterCommReset();
    }
    else if ((strlen(latestReceivedData) > 2) && (latestReceivedData[0] == 'G') && (latestReceivedData[1] == ':'))
    {
        GripSimulationParseCmd(latestReceivedData);
    }
    else if ((strlen(latestReceivedData) > 2) && (latestReceivedData[0] == 'H') && (latestReceivedData[1] == ':'))
    {
        HapticFeedbackParseCmd(latestReceivedData);
    }
    else
    {
        UART_PutString(latestReceivedData);
        UART_PutString("\n");
    }
}

void MasterCommSendFlexData()
{
    char output[100] = "";
    char data[3];
    for (i = 0; i < NO_OF_SENSORS; i++)
    {
        sprintf(data, "%03X", FlexSensorData[i]);
        strcat(output, data);
    }
    MasterCommSendData(output);
}

void MasterCommSendData(char* data)
{
    int size = strlen(data);
    for (i = 0; i < size; i++)
    {
        I2CSlaveDataOut[i] = data[i];
    }
    I2CSlaveDataOut[size] = '\0';
}

void MasterCommGetReceivedData()
{
    byteCountAtLastReceiveTransmission = I2C_Slave_SlaveGetWriteBufSize();
    I2C_Slave_SlaveClearWriteStatus();

    for (i =0; i<byteCountAtLastReceiveTransmission; i++)
    {
        latestReceivedData[i] = I2CSlaveDataIn[i];
    }
    latestReceivedData[byteCountAtLastReceiveTransmission] = '\0';

    I2C_Slave_SlaveClearWriteBuf();
}

int MasterCommSlaveFinishedReceiving()
{
    return (0u != (I2C_Slave_SlaveStatus() & I2C_Slave_SSTAT_WR_CMPLT));
}

int MasterCommSlaveFinishedSending()
{
    return (0u != (I2C_Slave_SlaveStatus() & I2C_Slave_SSTAT_RD_CMPLT));
}


/* [] END OF FILE */
