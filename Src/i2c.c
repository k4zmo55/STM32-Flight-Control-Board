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

void I2C_ManageAcking(I2Cx_RegDef *pI2Cx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        //Enable the ACK bit
        pI2Cx->CR1 |= (1 << I2C_CR1_ACK);
    }
    else
    {
        //Disable the ACK bit
        pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
    }
}

static void I2C_executeAddresPhase(I2Cx_RegDef *pI2Cx, uint8_t SlaveAddr, uint8_t ReadOrWrite)
{
    SlaveAddr = SlaveAddr << 1; //7-bit adresi sola kaydır

    if(ReadOrWrite == I2C_WRITE)
    {
        //Slave adresinin 0. bitini temizle (Write işlemi için)
        SlaveAddr &= ~(1 << 0); 
    }
    else if (ReadOrWrite == I2C_READ)
    {
        //Slave adresinin 0. bitini set et (Read işlemi için)
        SlaveAddr |= (1 << 0); 
    }

    //Slave adresini DR registerına yaz
    pI2Cx->DR = SlaveAddr;
}

static void Clear_ADDR_Flag(I2C_Handle_t *pI2CHandle)
{
    uint32_t dummyread = 0;

    if(pI2CHandle->pI2Cx->SR2 & (1 << I2C_SR2_MSL))
    {
        //Master MODE
        if(pI2CHandle->TxRxState == I2C_BUSY_IN_RX)
        {
            if(pI2CHandle->RxLen == 1)
            {
                //Disable ACK
                I2C_ManageAcking(pI2CHandle->pI2Cx, DISABLE);

                dummyread = pI2CHandle->pI2Cx->SR1;
                dummyread = pI2CHandle->pI2Cx->SR2;
                (void)dummyread;
            }
            else{
                //Device is in transmitter mode 
                dummyread = pI2CHandle->pI2Cx->SR1;
                dummyread = pI2CHandle->pI2Cx->SR2;
                (void)dummyread;
            }
        }
    }
    else
    {
        //Slave Mode
        dummyread = pI2CHandle->pI2Cx->SR1;
        dummyread = pI2CHandle->pI2Cx->SR2;
        (void)dummyread;
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

uint8_t I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr)
{
    //Generate the START condition
    I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

    /* SR1 hazır olana kadar bekle*/
    while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_SB_FLAG)));

    I2C_executeAddresPhase(pI2CHandle->pI2Cx, SlaveAddr, I2C_WRITE);

    while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_ADDR_FLAG)));

    Clear_ADDR_Flag(pI2CHandle);

    while(Len > 0)
    {
        while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_TxE_FLAG)));

        //Transferring 1 byte of data to DR register
        pI2CHandle->pI2Cx->DR = *pTxBuffer;

        pTxBuffer++;
        Len--;
    }

    while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_TxE_FLAG)));
    while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_BTF_FLAG)));

    if(Sr == DISABLE)
    {
        //Generate STOP condition
        I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
    }
}

uint8_t I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr)
{
    //Generate the START condition
    I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

    /* SR1 hazır olana kadar bekle*/
    while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_SB_FLAG)));

    I2C_executeAddresPhase(pI2CHandle->pI2Cx, SlaveAddr, I2C_READ);

    while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_ADDR_FLAG)));

    if(Len == 1)
    {
        //Disable ACK
        I2C_ManageAcking(pI2CHandle->pI2Cx, DISABLE);

        Clear_ADDR_Flag(pI2CHandle);

        while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_RxNE_FLAG)));

        if(Sr == DISABLE)
        {
            //Generate STOP condition
            I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
        }

        //Read data from DR register
        *pRxBuffer = pI2CHandle->pI2Cx->DR;
    }
    if(Len > 1)
    {
        //Clear the ADDR flag
        Clear_ADDR_Flag(pI2CHandle);

        for(uint32_t i = Len; i > 0; i--)
        {
            while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_RxNE_FLAG)));

            if(i == 2)
            {
                //Disable ACK
                I2C_ManageAcking(pI2CHandle->pI2Cx, DISABLE);

                if(Sr == DISABLE)
                {
                    //Generate STOP condition
                    I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
                }
            }

            //Read data from DR register
            *pRxBuffer = pI2CHandle->pI2Cx->DR;
            pRxBuffer++;
        }
    }
    if(pI2CHandle->I2C_Config.AckControl == I2C_ACK_ENABLE)
    {
        //Re-Enable ACKing
        I2C_ManageAcking(pI2CHandle->pI2Cx, ENABLE);
    }
}

void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        if(IRQNumber <= 31)
        {
            //ISER0
            *NVIC_ISER0 |= (1 << IRQNumber);
        }
        else if(IRQNumber > 31 && IRQNumber < 64)
        {
            //ISER1
            *NVIC_ISER1 |= (1 << (IRQNumber % 32));
        }
        else if(IRQNumber >= 64 && IRQNumber < 96)
        {
            //ISER2
            *NVIC_ISER2 |= (1 << (IRQNumber % 64));
        }
    }
    else
    {
        if(IRQNumber <= 31)
        {
            //ICER0
            *NVIC_ICER0 |= (1 << IRQNumber);
        }
        else if(IRQNumber > 31 && IRQNumber < 64)
        {
            //ICER1
            *NVIC_ICER1 |= (1 << (IRQNumber % 32));
        }
        else if(IRQNumber >= 64 && IRQNumber < 96)
        {
            //ICER2
            *NVIC_ICER2 |= (1 << (IRQNumber % 64));
        }
    }
}

void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;
    uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

    *(NVIC_PRI_BASE_ADDR + iprx) |= (IRQPriority << shift_amount);
}

uint8_t I2C_SendIT(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr)
{
    uint8_t bussystate = pI2CHandle->TxRxState;

    if((bussystate != I2C_BUSY_IN_TX) && (bussystate != I2C_BUSY_IN_RX))
    {
        pI2CHandle->DevAddr = SlaveAddr;
        pI2CHandle->TxLen = Len;
        pI2CHandle->TxRxState = I2C_BUSY_IN_TX;
        pI2CHandle->pTxBuffer = pTxBuffer;
        pI2CHandle->Sr = Sr;

        I2C_GenerateStartCondition(pI2CHandle->pI2Cx);
    }

    pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_ITBUFEN);
    pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_ITERREN);
    pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_ITEVTEN);

    return bussystate;
}

uint8_t I2C_ReceiveIT(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr)
{
    uint8_t bussystate = pI2CHandle->TxRxState;

    if((bussystate != I2C_BUSY_IN_TX) && (bussystate != I2C_BUSY_IN_RX))
    {
        pI2CHandle->DevAddr = SlaveAddr;
        pI2CHandle->RxLen = Len;
        pI2CHandle->TxRxState = I2C_BUSY_IN_RX;
        pI2CHandle->pRxBuffer = pRxBuffer;
        pI2CHandle->Sr = Sr;

        I2C_GenerateStartCondition(pI2CHandle->pI2Cx);
    }

    pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_ITBUFEN);
    pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_ITERREN);
    pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_ITEVTEN);

    return bussystate;
}