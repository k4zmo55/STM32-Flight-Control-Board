#include "../Inc/gpio.h"
#include <string.h>

void GPIO_PeriClockControl(GPIOx_RegDef *pGPIOx, uint8_t EnorDi) 
{
    if(EnorDi == ENABLE)
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_EN();
        }
        else if(pGPIOx == GPIOB)
        {
            GPIOB_PCLK_EN();
        }
        else if(pGPIOx == GPIOC)
        {
            GPIOC_PCLK_EN();
        }
        else if(pGPIOx == GPIOD)
        {
            GPIOD_PCLK_EN();
        }
        else if(pGPIOx == GPIOE)
        {
            GPIOE_PCLK_EN();
        }
        else if(pGPIOx == GPIOF)
        {
            GPIOF_PCLK_EN();
        }
        else if(pGPIOx == GPIOG)
        {
            GPIOG_PCLK_EN();
        }
        else if(pGPIOx == GPIOH)
        {
            GPIOH_PCLK_EN();
        }
        else if(pGPIOx == GPIOI)
        {
            GPIOI_PCLK_EN();
        }
        else if(pGPIOx == GPIOJ)
        {
            GPIOJ_PCLK_EN();
        }
        else if(pGPIOx == GPIOK)
        {
            GPIOK_PCLK_EN();
        }
    }
    else
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_DI();
        }
        else if(pGPIOx == GPIOB)
        {
            GPIOB_PCLK_DI();
        }
        else if(pGPIOx == GPIOC)
        {
            GPIOC_PCLK_DI();
        }
        else if(pGPIOx == GPIOD)
        {
            GPIOD_PCLK_DI();
        }
        else if(pGPIOx == GPIOE)
        {
            GPIOE_PCLK_DI();
        }
        else if(pGPIOx == GPIOF)
        {
            GPIOF_PCLK_DI();
        }
        else if(pGPIOx == GPIOG)
        {
            GPIOG_PCLK_DI();
        }
        else if(pGPIOx == GPIOH)
        {
            GPIOH_PCLK_DI();
        }
        else if(pGPIOx == GPIOI)
        {
            GPIOI_PCLK_DI();
        }
        else if(pGPIOx == GPIOJ)
        {
            GPIOJ_PCLK_DI();
        }
        else if(pGPIOx == GPIOK)
        {
            GPIOK_PCLK_DI();
        }
    }
}


uint8_t GPIO_SetPinMode(GPIOx_RegDef *pGPIOx, uint8_t PinNumber, uint8_t Mode)
{
    if(pGPIOx == NULL || PinNumber > 15 || Mode > 3)
    {
        return 0; // Error
    }

    pGPIOx->MODER &= ~(0x3 << (2 * PinNumber)); // Clear the 2 bits corresponding to the pin
    pGPIOx->MODER |= (Mode << (2 * PinNumber)); // Set the mode

    return 1; //Success
}

uint8_t GPIO_SetPinSpeed(GPIOx_RegDef *pGPIOx, uint8_t PinNumber, uint8_t Speed)
{
    if(pGPIOx == NULL || PinNumber > 15 || Speed > 3)
    {
        return 0; // Error
    }

    pGPIOx->OSPEEDR &= ~(0x3 << (2 * PinNumber)); // Clear the 2 bits corresponding to the pin
    pGPIOx->OSPEEDR |= (Speed << (2 * PinNumber)); // Set the speed

    return 1; // Success
}

uint8_t GPIO_SetPinPuPdControl(GPIOx_RegDef *pGPIOx, uint8_t PinNumber, uint8_t PuPd)
{
    if(pGPIOx == NULL || PinNumber > 15 || PuPd > 2)
    {
        return 0; // Error
    }

    pGPIOx->PUPDR &= ~(0x3 << (2 * PinNumber)); // Clear the 2 bits corresponding to the pin
    pGPIOx->PUPDR |= (PuPd << (2 * PinNumber)); // Set the Pull-up/Pull-down configuration

    return 1; // Success
}

uint8_t GPIO_SetPinOPType(GPIOx_RegDef *pGPIOx, uint8_t PinNumber, uint8_t OPType)
{
    if(pGPIOx == NULL || PinNumber > 15 || OPType > 1)
    {
        return 0; // Error
    }

    pGPIOx->OTYPER &= ~(0x1 << PinNumber); // Clear the bit corresponding to the pin
    pGPIOx->OTYPER |= (OPType << PinNumber); // Set the output type
    
    return 1; // Success
}

uint8_t  GPIO_ReadFromInputPin(GPIOx_RegDef *pGPIOx, uint8_t PinNumber)
{
    uint8_t Value;
    Value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001); 
    return Value;
}

uint16_t GPIO_ReadFromInputPort(GPIOx_RegDef *pGPIOx)
{
    uint16_t Value;
    Value = (uint16_t)(pGPIOx->IDR);
    return Value;
}

void GPIO_WriteToOutputPin(GPIOx_RegDef *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
    if(Value == SET)
    {
        pGPIOx->ODR |= (1 << PinNumber);
    }
    else
    {
        pGPIOx->ODR &= ~(1 << PinNumber);
    }
}

void GPIO_WriteToOutputPort(GPIOx_RegDef *pGPIOx, uint16_t Value)
{
    pGPIOx->ODR = Value;
}


void GPIO_ToggleOutputPin(GPIOx_RegDef *pGPIOx, uint8_t PinNumber)
{
    pGPIOx->ODR ^= (1 << PinNumber); //XOR operation to toggle
}


void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    //Enable the peripheral clock
    GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

    //1. Configure the mode of GPIO pin
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {
        GPIO_SetPinMode(pGPIOHandle->pGPIOx, pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber, pGPIOHandle->GPIO_PinConfig.GPIO_PinMode);
    }
    else
    {
        //Interrupt mode configuration can be added here later
        if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
        {
            //1.Configure the FTSR
            EXTI->RTSR  &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //Clear the bit
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);  //Set the bit
        }
        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
        {
            //1.Configure the RTSR
            EXTI->FTSR  &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //Clear the bit
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);  //Set the bit

        }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
        {
            //2.Configure both FTSR and RTSR
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);  //Set the bit
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);  //Set the bit
        }

        //2.Configure the GPIO port selection in SYSCFG_EXTICR

        uint8_t temp1  = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4; //To find the EXTICR register (0-3)
        uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;  //To find the position in the EXTICR register
        uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);

        SYSCFG_PCLK_EN(); //Enable the clock for SYSCFG
        SYSCFG->EXTICR[temp1] |= (portcode << (temp2 * 4));

        //3.Enable the EXTI interrupt delivery using IMR register
        EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    }

    //2. Configure the speed
    GPIO_SetPinSpeed(pGPIOHandle->pGPIOx, pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber, pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed);

    //3. Configure the Pull-up/Pull-down settings
    GPIO_SetPinPuPdControl(pGPIOHandle->pGPIOx, pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber, pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl);

    //4. Configure the output type
    GPIO_SetPinOPType(pGPIOHandle->pGPIOx, pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber, pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType);

    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
    {
        //Configure the alternate functionality
        uint8_t AFR_Index = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
        uint8_t AFR_Position = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;

        pGPIOHandle->pGPIOx->AFR[AFR_Index] &= ~(0xF << (4 * AFR_Position)); //Clear the 4 bits
        pGPIOHandle->pGPIOx->AFR[AFR_Index] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * AFR_Position)); //Set the value
    }
}

void GPIO_DeInit(GPIOx_RegDef *pGPIOx)
{
    if(pGPIOx == GPIOA)
    {
        GPIOA_REG_RESET();
    }
    else if(pGPIOx == GPIOB)
    {
        GPIOB_REG_RESET();
    }
    else if(pGPIOx == GPIOC)
    {
        GPIOC_REG_RESET();
    }
    else if(pGPIOx == GPIOD)
    {
        GPIOD_REG_RESET();
    }
    else if(pGPIOx == GPIOE)
    {
        GPIOE_REG_RESET();
    }
    else if(pGPIOx == GPIOF)
    {
        GPIOF_REG_RESET();
    }
    else if(pGPIOx == GPIOG)
    {
        GPIOG_REG_RESET();
    }
    else if(pGPIOx == GPIOH)
    {
        GPIOH_REG_RESET();
    }
    else if(pGPIOx == GPIOI)
    {
        GPIOI_REG_RESET();
    }
    else if(pGPIOx == GPIOJ)
    {
        GPIOJ_REG_RESET();
    }
    else if(pGPIOx == GPIOK)
    {
        GPIOK_REG_RESET();
    }
}

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
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

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;
    uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

    *(NVIC_PRI_BASE_ADDR + iprx) |= (IRQPriority << shift_amount);
}

void GPIO_IRQHandling(uint8_t PinNumber)
{
    //Clear the EXTI PR register corresponding to the pin number
    if(EXTI->PR & (1 << PinNumber))
    {
        //Clear
        EXTI->PR |= (1 << PinNumber);
    }
}

