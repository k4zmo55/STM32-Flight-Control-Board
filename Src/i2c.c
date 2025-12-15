#include "../Inc/i2c.h"
#include <stdint.h>
#include <stdio.h>

extern uint32_t RCC_GetSYSClockFreq(RCC_Handle_t *pHandle);

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

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
    I2C_PeriClockControl(pI2CHandle->pI2Cx,ENABLE);

    // CR1 register'ındaki PE (Peripheral Enable) bitini temizle 
    pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);

    //ACK Control 
    if(pI2CHandle->I2C_Config.AckControl == I2C_ACK_ENABLE)
    {
        pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_ACK);
    }
    else
    {
        pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
    }

    uint32_t pclk1 = RCC_GetPCLK1Value(pI2CHandle->pRCCHandle);

    uint32_t pclk1_MHz = pclk1 / 1000000U;

    // FREQ bitlerini temizle ve yaz
    uint32_t tempreg = pI2CHandle->pI2Cx->CR2;
    tempreg &= ~(0x3F);  // Bit 5:0'ı temizle
    tempreg |= (pclk1_MHz & 0x3F);  // FREQ değerini yaz
    pI2CHandle->pI2Cx->CR2 = tempreg;

    //Program the device own address
    tempreg = 0;
    tempreg |= (pI2CHandle->I2C_Config.DeviceAddress << 1);
    tempreg |= (1 << I2C_OAR1_ADDCONF); // 7-bit adresleme modu
    pI2CHandle->pI2Cx->OAR1 = tempreg;
    
    //CCR calculation
    uint16_t ccr_value = 0;
    tempreg = 0;

    if(pI2CHandle->I2C_Config.SCLSpeed <= I2C_SCL_SPEED_SM)
    {
        //Standard mode
        tempreg |= (pI2CHandle->I2C_Config.FMDutyCycle << I2C_CCR_DUTY); // DUTY bitini ayarla
        ccr_value = (pclk1) / (2 * pI2CHandle->I2C_Config.SCLSpeed);
        tempreg |= (ccr_value & 0xFFF);
        pI2CHandle->pI2Cx->CCR = tempreg;
    }
    else
    {
        //Fast mode
        tempreg |= (1 << I2C_CCR_FS); // Set FM bit
        tempreg |= (pI2CHandle->I2C_Config.FMDutyCycle << I2C_CCR_DUTY); // DUTY bitini ayarla

        if(pI2CHandle->I2C_Config.FMDutyCycle == I2C_FM_DUTY_2)
        {
            //Duty cycle 2
            ccr_value = (pclk1) / (3 * pI2CHandle->I2C_Config.SCLSpeed);
            tempreg |= (ccr_value & 0xFFF);
        }
        else if (pI2CHandle->I2C_Config.FMDutyCycle == I2C_FM_DUTY_16_9)
        {
            //Duty cycle 16/9
            ccr_value = (pclk1) / (25 * pI2CHandle->I2C_Config.SCLSpeed);
            
            tempreg |= (1 << I2C_CCR_DUTY); // Set DUTY bit
        }

        tempreg |= ( ccr_value & 0xFFF);
    }

    pI2CHandle->pI2Cx->CCR = tempreg;

    	// trise configurations
	if (pI2CHandle->I2C_Config.SCLSpeed == I2C_SCL_SPEED_SM) {
		// mode is standard mode
		tempreg = ( pclk1_MHz / 1000000U ) + 1 ;

	}else {
		// mode is fast mode
		tempreg = ((pclk1_MHz * 300) / 1000000000U) + 1 ;
	}

	pI2CHandle->pI2Cx->TRISE = ( tempreg & 0x3F) ;

    pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_PE); // Enable the I2C peripheral
}


