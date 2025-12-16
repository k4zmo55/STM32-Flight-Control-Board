#include "../Inc/spi.h"
#include <string.h>


/*****************************************************************
 * @fn          - SPI_PeriClockControl
 *
 * @brief       - This function enables or disables peripheral
 *                clock for the given SPI port
 *
 * @param[in]   - pSPIx   : Base address of the SPI peripheral
 * @param[in]   - EnorDi  : ENABLE or DISABLE macro
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void SPI_PeriClockControl(SPIx_RegDef *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        if(pSPIx == SPI1)
        {
            SPI1_PCLK_EN();
        }
        else if(pSPIx == SPI2)
        {
            SPI2_PCLK_EN();
        }
        else if(pSPIx == SPI3)
        {
            SPI3_PCLK_EN();
        }
        else if(pSPIx == SPI4)
        {
            SPI4_PCLK_EN();
        }
        else if(pSPIx == SPI5)
        {
            SPI5_PCLK_EN();
        }
        else if(pSPIx == SPI6)
        {
            SPI6_PCLK_EN();
        }
    }
    else{
        if(pSPIx == SPI1)
        {
            SPI1_PCLK_DI();
        }
        else if(pSPIx == SPI2)
        {
            SPI2_PCLK_DI();
        }
        else if(pSPIx == SPI3)
        {
            SPI3_PCLK_DI();
        }
        else if(pSPIx == SPI4)
        {
            SPI4_PCLK_DI();
        }
        else if(pSPIx == SPI5)
        {
            SPI5_PCLK_DI();
        }
        else if(pSPIx == SPI6)
        {
            SPI6_PCLK_DI();
        }
    }
}

void SPI_PeripheralControl(SPIx_RegDef *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << SPI_CR1_SPE); // Set the SPE bit to enable SPI
    }
    else
    {
        pSPIx->CR1 &= ~(1 << SPI_CR1_SPE); // Clear the SPE bit to disable SPI
    }
}

SPI_State_t SPI_ConfigurationDeviceMode(SPIx_RegDef *pSPIx, uint8_t DeviceMode)
{
    if(pSPIx == NULL || DeviceMode > 1)
    {
        return SPI_ERROR; 
    }

    pSPIx->CR1 &= ~(1 << SPI_CR1_MSTR); // Clear MSTR bit
    pSPIx->CR1 |= (DeviceMode << SPI_CR1_MSTR); //Set MSTR bit according to DeviceMode

    return SPI_OK; 
}

SPI_State_t SPI_ConfigurationBusConfig(SPIx_RegDef *pSPIx, uint8_t BusConfig)
{
    if(pSPIx == NULL || BusConfig > 3)
    {
        return SPI_ERROR; 
    }

    if(BusConfig == SPI_BUS_CONFIG_FD)
    {
        //Full-Duplex
        pSPIx->CR1 &= ~(1 << SPI_CR1_BIDIMODE); // Clear BIDIMODE for Full-Duplex
        return SPI_OK;
    }
    else if(BusConfig == SPI_BUS_CONFIG_HD)
    {
        //Half-Duplex
        pSPIx->CR1 |= (1 << SPI_CR1_BIDIMODE); // Set BIDIMODE for Half-Duplex
        return SPI_OK;
    }
    else if(BusConfig == SPI_BUS_CONFIG_SIMPLEX_RX)
    {
        //Simplex RX Only
        pSPIx->CR1 &= ~(1 << SPI_CR1_BIDIMODE); // Clear BIDIMODE
        pSPIx->CR1 |= (1 << SPI_CR1_RXONLY);  // Set RXONLY bit
        return SPI_OK;
    }
}


SPI_State_t SPI_ConfigurationSerialClockSpeed(SPIx_RegDef *pSPIx, uint8_t SclkSpeed)
{
    if(pSPIx == NULL || SclkSpeed > 7)
    {
        return SPI_ERROR; 
    }

    pSPIx->CR1 &= ~(0x7 << SPI_CR1_BR); // Clear BR bits
    pSPIx->CR1 |= (SclkSpeed << SPI_CR1_BR); //Set BR bits according to SclkSpeed

    return SPI_OK; 
}

SPI_State_t SPI_ConfigurationDataFrameFormat(SPIx_RegDef *pSPIx, uint8_t DFF)
{
    if(pSPIx == NULL || DFF > 1)
    {
        return SPI_ERROR;
    }

    pSPIx->CR1 &= ~(1 << SPI_CR1_DFF); // Clear DFF bit
    pSPIx->CR1 |= (DFF << SPI_CR1_DFF); //Set DFF bit according to DFF

    return SPI_OK;
}

SPI_State_t SPI_ConfigurationClockPolarity(SPIx_RegDef *pSPIx, uint8_t CPOL)
{
    if(pSPIx == NULL || CPOL > 1)
    {
        return SPI_ERROR;
    }

    pSPIx->CR1 &= ~(1 << SPI_CR1_CPOL); // Clear CPOL bit
    pSPIx->CR1 |= (CPOL << SPI_CR1_CPOL); //Set CPOL bit according to CPOL

    return SPI_OK;
}

SPI_State_t SPI_ConfigurationClockPhase(SPIx_RegDef *pSPIx, uint8_t CPHA)
{
    if(pSPIx == NULL || CPHA > 1)
    {
        return SPI_ERROR;
    }

    pSPIx->CR1 &= ~(1 << SPI_CR1_CPHA); // Clear CPHA bit
    pSPIx->CR1 |= (CPHA << SPI_CR1_CPHA); //Set CPHA bit according to CPHA

    return SPI_OK;
}

SPI_State_t SPI_ConfigurationSoftwareSlaveManagement(SPIx_RegDef *pSPIx, uint8_t SSM)
{
    if(pSPIx == NULL || SSM > 1)
    {
        return SPI_ERROR;
    }

    pSPIx->CR1 &= ~(1 << SPI_CR1_SSM); // Clear SSM bit
    pSPIx->CR1 |= (SSM << SPI_CR1_SSM); //Set SSM bit according to SSM

    return SPI_OK;
}

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    //1. Enable the peripheral clock
    SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

    //2. Configure the device mode
    SPI_ConfigurationDeviceMode(pSPIHandle->pSPIx, pSPIHandle->SPIConfig.SPI_DeviceMode);

    //3. Configure the bus configuration
    SPI_ConfigurationBusConfig(pSPIHandle->pSPIx, pSPIHandle->SPIConfig.SPI_BusConfig);

    //4. Configure the serial clock speed
    SPI_ConfigurationSerialClockSpeed(pSPIHandle->pSPIx, pSPIHandle->SPIConfig.SPI_SclkSpeed);

    //5. Configure the data frame format
    SPI_ConfigurationDataFrameFormat(pSPIHandle->pSPIx, pSPIHandle->SPIConfig.SPI_DFF);

    //6. Configure the clock polarity
    SPI_ConfigurationClockPolarity(pSPIHandle->pSPIx, pSPIHandle->SPIConfig.SPI_CPOL);

    //7. Configure the clock phase
    SPI_ConfigurationClockPhase(pSPIHandle->pSPIx, pSPIHandle->SPIConfig.SPI_CPHA);

    //8. Configure the software slave management
    SPI_ConfigurationSoftwareSlaveManagement(pSPIHandle->pSPIx, pSPIHandle->SPIConfig.SPI_SSM);
}

void SPI_DeInit(SPIx_RegDef *pSPIx)
{
    if(pSPIx == SPI1)
    {
        RCC->APB2RSTR |= (1 << RCC_APB2RSTR_SPI1RST);
        RCC->APB2RSTR &= ~(1 << RCC_APB2RSTR_SPI1RST);
    }
    else if(pSPIx == SPI2)
    {
        RCC->APB1RSTR |= (1 << RCC_APB1RSTR_SPI2RST);
        RCC->APB1RSTR &= ~(1 << RCC_APB1RSTR_SPI2RST);
    }
    else if(pSPIx == SPI3)
    {
        RCC->APB1RSTR |= (1 << RCC_APB1RSTR_SPI3RST);
        RCC->APB1RSTR &= ~(1 << RCC_APB1RSTR_SPI3RST);
    }
    else if(pSPIx == SPI4)
    {
        RCC->APB2RSTR |= (1 << RCC_APB2RSTR_SPI4RST);
        RCC->APB2RSTR &= ~(1 << RCC_APB2RSTR_SPI4RST);
    }
    else if(pSPIx == SPI5)
    {
        RCC->APB2RSTR |= (1 << RCC_APB2RSTR_SPI5RST);
        RCC->APB2RSTR &= ~(1 << RCC_APB2RSTR_SPI5RST);
    }
    else if(pSPIx == SPI6)
    {
        RCC->APB2RSTR |= (1 << RCC_APB2RSTR_SPI6RST);
        RCC->APB2RSTR &= ~(1 << RCC_APB2RSTR_SPI6RST);
    }
}

uint8_t SPI_SendData(SPIx_RegDef *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
    while(Len > 0)
    {
        //1. Wait until TXE is set
        while(SPI_GetFlagStatus(pSPIx, SPI_SR_TXE) == FLAG_RESET);

        //2. Check the DFF bit in CR1
        if((pSPIx->CR1 & (1 << SPI_CR1_DFF)))
        {
            //16-bit DFF
            pSPIx->DR = *((uint16_t *)pTxBuffer); // Cast to uint16_t pointer and dereference
            Len -= 2;
            pTxBuffer++; // Increment by 2 bytes
            
        }
        else
        {
            //8-bit DFF
            pSPIx->DR = *pTxBuffer;
            Len--;
            pTxBuffer++;
        }
    }

    return 0; // Return 0 to indicate success
}

uint8_t SPI_ReceiveData(SPIx_RegDef *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
    while(Len > 0)
    {
        //1. Wait until RXNE is set
        while(SPI_GetFlagStatus(pSPIx, SPI_SR_RXNE) == FLAG_RESET);

        //2. Check the DFF bit in CR1
        if((pSPIx->CR1 & (1 << SPI_CR1_DFF)))
        {
            //16-bit DFF
            *((uint16_t *)pRxBuffer) = pSPIx->DR; // Cast to uint16_t pointer and dereference
            Len -= 2;
            pRxBuffer++; // Increment by 2 bytes
        }
        else
        {
            //8-bit DFF
            *pRxBuffer = pSPIx->DR;
            Len--;
            pRxBuffer++;
        }
    }

    return 0; // Return 0 to indicate success
}

void SPI_MasterTransmitReceive(SPIx_RegDef *pSPIx, uint8_t *pTxBuffer, uint8_t *pRxBuffer, uint32_t Len)
{
    while (Len > 0)
    {
        //1. Gönderme bufferının boş olmasını bekle
        while(SPI_GetFlagStatus(pSPIx, SPI_SR_TXE) == FLAG_RESET);

        //2. Veri yükle
        pSPIx->DR = *pTxBuffer;

        //3. Alım bufferında veri hazır olmasını bekle
        while(SPI_GetFlagStatus(pSPIx, SPI_SR_RXNE) == FLAG_RESET);

        //4. Veriyi al
        *pRxBuffer = pSPIx->DR;

        //5. İndeksleri ve uzunluğu güncelle
        pTxBuffer++;
        pRxBuffer++;

        Len--;
    }
    while(SPI_GetFlagStatus(pSPIx, SPI_SR_BSY) == FLAG_SET); // İşlemin tamamlanmasını bekle
    
}

uint8_t SPI_MasterTransmitIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len)
{

    if(pSPIHandle->TxState != SPI_BUSY_IN_TX)
    {
        pSPIHandle->pTxBuffer = pTxBuffer;
        pSPIHandle->TxLen = Len;
        pSPIHandle->TxState = SPI_BUSY_IN_TX;

        pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_TXEIE); // Enable TXEIE interrupt

        return SPI_OK;
    }

    return SPI_ERROR;
}

uint8_t SPI_MasterReceiveIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len)
{

    if(pSPIHandle->TxState != SPI_BUSY_IN_RX)
    {
        pSPIHandle->pRxBuffer = pRxBuffer;
        pSPIHandle->RxLen = Len;
        pSPIHandle->RxState = SPI_BUSY_IN_RX;

        pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_RXNEIE); // Enable RXNEIE interrupt

        if(SPI_GetFlagStatus(pSPIHandle->pSPIx, SPI_SR_TXE) == FLAG_SET)
        {
            pSPIHandle->pSPIx->DR = 0xFF; // Dummy byte to generate clock
        }

        return SPI_OK;
    }

    return SPI_ERROR;
}


uint8_t SPI_GetFlagStatus(SPIx_RegDef *pSPIx, uint32_t FlagName)
{
    if(pSPIx->SR & FlagName)
    {
        return FLAG_SET;
    }
    return FLAG_RESET;
}

void SPI_ClearOVRFlag(SPIx_RegDef *pSPIx)
{
    uint8_t temp;
    temp = pSPIx->DR; // Read DR register
    temp = pSPIx->SR; // Read SR register
    (void)temp; // To avoid compiler warning about unused variable
}

void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle)
{
    //1. Disable TXEIE control bit
    pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);

    //2. Clear the application state
    pSPIHandle->TxState = SPI_READY;
}

void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{
    //1. Disable RXNEIE control bit
    pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE);

    //2. Clear the application state
    pSPIHandle->RxState = SPI_READY;
}

