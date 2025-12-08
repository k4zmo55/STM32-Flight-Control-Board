#include "../Inc/i2c.h"
#include <stdint.h>
#include <stdio.h>

void I2C_PeriClockControl(I2Cx_RegDef *pI2Cx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        if(pI2Cx == I2C1)
        {
            I2C1_PCLK_EN();
        }
        else if(pI2Cx == I2C2)
        {
            I2C2_PCLK_EN();
        }
        else if(pI2Cx == I2C3)
        {
            I2C3_PCLK_EN();
        }
    }
    else{
        if(pI2Cx == I2C1)
        {
            I2C1_PCLK_DI();
        }
        else if(pI2Cx == I2C2)
        {
            I2C2_PCLK_DI();
        }
        else if(pI2Cx == I2C3)
        {
            I2C3_PCLK_DI();
        }
    }
}

static void I2C_GenerateStartCondition(I2Cx_RegDef *pI2Cx)
{
    //Set the START bit in CR1 register
    pI2Cx->CR1 |= (1 << I2C_CR1_START);
}

static void I2C_GenerateStopCondition(I2Cx_RegDef *pI2Cx)
{
    //Set the STOP bit in CR1 register
    pI2Cx->CR1 |= (1 << I2C_CR1_STOP);
}

uint8_t I2C_GetFlagStatus(I2Cx_RegDef *pI2Cx, uint32_t FlagName)
{
    if(pI2Cx->SR1 & FlagName)
    {
        return FLAG_SET;
    }
    return FLAG_RESET;
}


void I2C_CloseSendData(I2C_Handle_t *pI2CHandle)
{
    printf("closing data transfer in interrupt mode \n");

    //disable the all interrupts
    pI2CHandle->pI2Cx->CR2 &= ~(1 << I2C_CR2_ITBUFEN);
    pI2CHandle->pI2Cx->CR2 &= ~(1 << I2C_CR2_ITEVTEN);
    
    printf("interrupts disabled trasmission \n");
    pI2CHandle->TxRxState = I2C_READY;
    pI2CHandle->pTxBuffer = NULL;
    pI2CHandle->TxLen = 0;

    printf("handle variables reset transmission \n");
}


uint32_t RCC_GetPCLK1Value(void)
{
    uint16_t AHB_PreScaler[9] = {2,4,8,16,32,64,128,256,512};
    uint8_t APB1_PreScaler[4] = {2,4,8,16};
    uint32_t psclk1;
    uint8_t clksrc,temp, ahbp, apb1p;
    uint32_t SystemClock = 0;

    clksrc = ((RCC->CFGR >> 2) & 0x3); //check the clock source

    if(clksrc == 0)
    {
        SystemClock = 16000000;  //hsi is selected
    }
    else if (clksrc == 1)
    {
        SystemClock = 8000000; //hse is selected
    }
    else{
        SystemClock = 0;      //pll is selected
    }

    //get the value of ahb prescaler value
    temp = ((RCC->CFGR >> 4) & 0xF);

    if(temp < 8){
        ahbp = 1;
    }
    else{
        ahbp = AHB_PreScaler[temp - 8];
    }

    //get the vakue of apb1 prescaler value
    temp = ((RCC->CFGR >> 10) & 0x7);

    if(temp < 4)
    {
        apb1p = 1;
    }
    else{
        apb1p = APB1_PreScaler[temp - 4];
    }

    psclk1 = ((SystemClock / ahbp) / apb1p );

    return psclk1;
}
