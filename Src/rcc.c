#include "../Inc/rcc.h"
#include <stdio.h>

volatile uint32_t uwTick = 0;

uint32_t GetTick(void)
{
    return uwTick;
}


#define CLOCK_TIMEOUT 100U

uint32_t RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct)
{
    uint32_t tickstart; // Zaman aşımı başlangıç değeri

    if(RCC_OscInitStruct == NULL)
    {
        return ERROR;
    }

    /* Check the paramaters*/
    assert_param(IS_RCC_OSCILLATORTYPE(RCC_OscInitStruct->OscillatorType));

    /* ---------------- HSE ---------------- */
    if(RCC_OscInitStruct->OscillatorType & RCC_OSCILLATORTYPE_HSE)
    {
        assert_param(IS_RCC_HSE(RCC_OscInitStruct->HSEState));

        if(RCC_OscInitStruct->HSEState == RCC_HSE_BYPASS)
        {
            RCC->CR &= ~(1 << RCC_CR_HSEON);  // HSE disable
            RCC->CR |= (1 << RCC_CR_HSEBYP);  // HSE bypass enable

            tickstart = GetTick();
            while(!(RCC->CR & (1 << RCC_CR_HSERDY))) // HSE hazır olana kadar bekle
            {
                if((GetTick() - tickstart) > CLOCK_TIMEOUT) return HAL_TIMEOUT; // Timeout kontrolü
            }
        }
        else if(RCC_OscInitStruct->HSEState == RCC_HSE_ON)
        {
            RCC->CR &= ~(1 << RCC_CR_HSEBYP); // HSE bypass disable
            RCC->CR |= (1 << RCC_CR_HSEON);   // HSE enable

            tickstart = GetTick();
            while(!(RCC->CR & (1 << RCC_CR_HSERDY))) // HSE hazır olana kadar bekle
            {
                if((GetTick() - tickstart) > CLOCK_TIMEOUT) return HAL_TIMEOUT; // Timeout kontrolü
            }
        }
        else // RCC_HSE_OFF
        {
            RCC->CR &= ~(1 << RCC_CR_HSEON);  // HSE disable
            RCC->CR &= ~(1 << RCC_CR_HSEBYP); // HSE bypass disable

            tickstart = GetTick();
            while((RCC->CR & (1 << RCC_CR_HSERDY))) // Bayrağın RESET olmasını bekle (Kapanma)
            {
                if((GetTick() - tickstart) > CLOCK_TIMEOUT) return HAL_TIMEOUT;
            }
        }
    }

    /* ---------------- HSI ---------------- */
    if(RCC_OscInitStruct->OscillatorType & RCC_OSCILLATORTYPE_HSI)
    {
        assert_param(IS_RCC_HSI(RCC_OscInitStruct->HSIState));
        assert_param(IS_RCC_CALIBRATION_VALUE(RCC_OscInitStruct->HSICalibrationValue));

        if(RCC_OscInitStruct->HSIState == RCC_HSI_ON)
        {
            RCC->CR &= ~(0x1F << RCC_CR_HSITRIM);
            RCC->CR |= (RCC_OscInitStruct->HSICalibrationValue << RCC_CR_HSITRIM); // Kalibrasyon ayarla
            RCC->CR |= (1 << RCC_CR_HSION); // HSI enable

            tickstart = GetTick();
            while(!(RCC->CR & (1 << RCC_CR_HSIRDY))) // HSI hazır olmasını bekle
            {
                if((GetTick() - tickstart) > CLOCK_TIMEOUT) return HAL_TIMEOUT;
            }
        }
        else // RCC_HSI_OFF
        {
            RCC->CR &= ~(1 << RCC_CR_HSION); // HSI disable

            tickstart = GetTick();
            while((RCC->CR & (1 << RCC_CR_HSIRDY))) // Bayrağın RESET olmasını bekle (Kapanma)
            {
                if((GetTick() - tickstart) > CLOCK_TIMEOUT) return HAL_TIMEOUT;
            }
        }
    }

    /* ---------------- LSI ---------------- */
    if(RCC_OscInitStruct->OscillatorType & RCC_OSCILLATORTYPE_LSI)
    {
        assert_param(IS_RCC_LSI(RCC_OscInitStruct->LSIState));

        if(RCC_OscInitStruct->LSIState == RCC_LSI_ON)
        {
            RCC->CSR |= (1 << RCC_CSR_LSION); // LSI enable

            tickstart = GetTick();
            while(!(RCC->CSR & (1 << RCC_CSR_LSIRDY))) // LSI hazır olana kadar bekle
            {
                if((GetTick() - tickstart) > CLOCK_TIMEOUT) return HAL_TIMEOUT;
            }
        }
        else // RCC_LSI_OFF
        {
            RCC->CSR &= ~(1 << RCC_CSR_LSION); // LSI disable

            tickstart = GetTick();
            while((RCC->CSR & (1 << RCC_CSR_LSIRDY))) // Bayrağın RESET olmasını bekle (Kapanma)
            {
                if((GetTick() - tickstart) > CLOCK_TIMEOUT) return HAL_TIMEOUT;
            }
        }
    }

    /* ---------------- LSE ---------------- */
    if(RCC_OscInitStruct->OscillatorType & RCC_OSCILLATORTYPE_LSE)
    {
        assert_param(IS_RCC_LSE(RCC_OscInitStruct->LSEState));

        if(RCC_OscInitStruct->LSEState == RCC_LSE_ON)
        {
            RCC->BDCR &= ~(1 << RCC_BDCR_LSEBYP); // LSE bypass disable
            RCC->BDCR |= (1 << RCC_BDCR_LSEON);   // LSE enable

            tickstart = GetTick();
            while(!(RCC->BDCR & (1 << RCC_BDCR_LSERDY))) // LSE hazır olana kadar bekle
            {
                if((GetTick() - tickstart) > CLOCK_TIMEOUT) return HAL_TIMEOUT;
            }
        }
        else if(RCC_OscInitStruct->LSEState == RCC_LSE_BYPASS)
        {
            RCC->BDCR &= ~(1 << RCC_BDCR_LSEON);  // LSE disable
            RCC->BDCR |= (1 << RCC_BDCR_LSEBYP); // LSE bypass enable

            tickstart = GetTick();
            while(!(RCC->BDCR & (1 << RCC_BDCR_LSERDY))) // LSE hazır olana kadar bekle
            {
                if((GetTick() - tickstart) > CLOCK_TIMEOUT) return HAL_TIMEOUT;
            }
        }
        else // RCC_LSE_OFF
        {
            RCC->BDCR &= ~(1 << RCC_BDCR_LSEON);  // LSE disable
            RCC->BDCR &= ~(1 << RCC_BDCR_LSEBYP); // LSE bypass disable

            tickstart = GetTick();
            while((RCC->BDCR & (1 << RCC_BDCR_LSERDY))) // Bayrağın RESET olmasını bekle (Kapanma)
            {
                if((GetTick() - tickstart) > CLOCK_TIMEOUT) return HAL_TIMEOUT;
            }
        }
    }

    /* ---------------- PLL ---------------- */
    if(RCC_OscInitStruct->PLL.PLLState != RCC_PLL_NONE)
    {
        assert_param(IS_RCC_PLL(RCC_OscInitStruct->PLL.PLLState));

        if(RCC_OscInitStruct->PLL.PLLState == RCC_PLL_ON)
        {
            /* PLL Parametre Kontrolü (Doğrulama) */

            //PLLM Kontrolü
            if(RCC_OscInitStruct->PLL.PLLM < 2 || RCC_OscInitStruct->PLL.PLLM > 63)
            {
                return ERROR;
            }

            //PLLP Kontrolü
            uint32_t pllp = RCC_OscInitStruct->PLL.PLLP;
            if(pllp != 2 && pllp != 4 && pllp != 6 && pllp != 8)
            {
                return ERROR;
            }

            //PLLN Kontrolü
            if(RCC_OscInitStruct->PLL.PLLN < 50 || RCC_OscInitStruct->PLL.PLLN > 432)
            {
                return ERROR;
            }

            //PLLQ Kontrolü
            if(RCC_OscInitStruct->PLL.PLLQ < 2 || RCC_OscInitStruct->PLL.PLLQ > 15)
            {
                return ERROR;
            }

            /* PLL kaynak seçimi, PLLM, PLLN, PLLP, PLLQ ayarları (değişiklik yapılmadı) */
            RCC->PLLCFGR &= ~(1 << RCC_PLLCFGR_PLLSRC);
            RCC->PLLCFGR |= (RCC_OscInitStruct->PLL.PLLSource << RCC_PLLCFGR_PLLSRC);
            
            // ... Diğer PLL ayarları ...
            
            RCC->PLLCFGR &= ~(0x3F << RCC_PLLCFGR_PLLM);
            RCC->PLLCFGR |= (RCC_OscInitStruct->PLL.PLLM << RCC_PLLCFGR_PLLM);

            RCC->PLLCFGR &= ~(0x1FF << RCC_PLLCFGR_PLLN);
            RCC->PLLCFGR |= (RCC_OscInitStruct->PLL.PLLN << RCC_PLLCFGR_PLLN);

            RCC->PLLCFGR &= ~(0x3 << RCC_PLLCFGR_PLLP);
            RCC->PLLCFGR |= (RCC_OscInitStruct->PLL.PLLP << RCC_PLLCFGR_PLLP);

            RCC->PLLCFGR &= ~(0x0F << RCC_PLLCFGR_PLLQ);
            RCC->PLLCFGR |= (RCC_OscInitStruct->PLL.PLLQ << RCC_PLLCFGR_PLLQ);
            
            /* PLL enable */
            RCC->CR |= (1 << RCC_CR_PLLON);

            tickstart = GetTick();
            while(!(RCC->CR & (1 << RCC_CR_PLLRDY))) // PLL hazır olana kadar bekle
            {
                if((GetTick() - tickstart) > CLOCK_TIMEOUT) return HAL_TIMEOUT;
            }
        }
        else // RCC_PLL_OFF
        {
            RCC->CR &= ~(1 << RCC_CR_PLLON); // PLL disable
            
            tickstart = GetTick();
            while((RCC->CR & (1 << RCC_CR_PLLRDY))) // Bayrağın RESET olmasını bekle (Kapanma)
            {
                if((GetTick() - tickstart) > CLOCK_TIMEOUT) return HAL_TIMEOUT;
            }
        }
    }

    return 0;
}


uint32_t RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FlashLatency)
{
    if(RCC_ClkInitStruct == NULL)
    {
        return ERROR;
    }

    assert_param(IS_RCC_CLOCKTYPE(RCC_ClkInitStruct->ClockType));
    assert_param(IS_FLASH_LATENCY(FlashLatency));

    /* -------------------- Flash Latency -------------------- */
    FLASH->ACR &= ~0x7U;
    FLASH->ACR |= (FlashLatency & 0x7U);

    /* -------------------- HCLK (AHB) Configuration -------------------- */
    if((RCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_HCLK) == RCC_CLOCKTYPE_HCLK)
    {
        assert_param(IS_RCC_AHB_CLOCK_DIVIDER(RCC_ClkInitStruct->AHBCLKDivider));
        MODIFY_REG(RCC->CFGR, (0x7 << RCC_CFGR_HPRE), RCC_ClkInitStruct->AHBCLKDivider << RCC_CFGR_HPRE);
    }

    /*------------------------- SYSCLK Configuration ---------------------------*/
    if((RCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_SYSCLK) == RCC_CLOCKTYPE_SYSCLK)
    {
        assert_param(IS_RCC_SYSCLK_SOURCE(RCC_ClkInitStruct->SYSCLKSource));

                /* Eğer hedef SYSCLK PLL ise PLLRDY kontrolü yap */
        if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_PLL)
        {
            /* PLL ready olmalı */
            if((RCC->CR & (1U << RCC_CR_PLLRDY)) == 0U)
                return ERROR;
        }
        else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_HSE)
        {
            if((RCC->CR & (1U << RCC_CR_HSERDY)) == 0U)
                return ERROR;
        }
        else /* HSI */
        {
            if((RCC->CR & (1U << RCC_CR_HSIRDY)) == 0U)
                return ERROR;
        }
        
        RCC_SYSCLK_CONFIG(RCC_ClkInitStruct->SYSCLKSource);
    }

    /*-------------------------- PCLK1 Configuration ---------------------------*/
    if((RCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_PCLK1) == RCC_CLOCKTYPE_PCLK1)
    {
        assert_param(IS_RCC_PCLK(RCC_ClkInitStruct->APB1CLKDivider));
        MODIFY_REG(RCC->CFGR, (0x7 << RCC_CFGR_PPRE1),(RCC_ClkInitStruct->APB1CLKDivider << RCC_CFGR_PPRE1));

    }

    /*-------------------------- PCLK2 Configuration ---------------------------*/
    if((RCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_PCLK2) == RCC_CLOCKTYPE_PCLK2)
    {
        assert_param(IS_RCC_PCLK(RCC_ClkInitStruct->APB2CLKDivider));
        MODIFY_REG(RCC->CFGR, (0x7 << RCC_CFGR_PPRE2), (RCC_ClkInitStruct->APB2CLKDivider << RCC_CFGR_PPRE2));
    }

    return 0;
}

