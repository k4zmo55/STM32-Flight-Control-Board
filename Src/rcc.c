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

/**
 * @brief  STM32F4xx için PLL parametrelerini otomatik hesaplar
 * 
 * @details Bu fonksiyon, istenen SYSCLK ve USB/SDIO frekanslarına göre
 *          PLL'in PLLM, PLLN, PLLP ve PLLQ değerlerini hesaplar.
 *          
 *          PLL Yapısı:
 *          ┌─────────────────────────────────────────────────┐
 *          │  HSE/HSI ──> [÷M] ──> [×N] ──> [÷P] ──> SYSCLK  │
 *          │                  VCO_IN   VCO_OUT               │
 *          │                         └──> [÷Q] ──> USB/SDIO  │
 *          └─────────────────────────────────────────────────┘
 * 
 * @details Çalışma Mantığı:
 *          1. PLLP Bulma: Hedef SYSCLK'den geriye doğru VCO çıkış frekansını hesaplar.
 *             VCO_OUT = SYSCLK × P (P değerleri: 2, 4, 6, 8 denenir)
 *             VCO_OUT limitleri: 100-432 MHz arasında olmalı
 * 
 *          2. PLLM Bulma: HSE/HSI'yi bölerek VCO giriş frekansını ayarlar.
 *             VCO_IN = HSE/HSI ÷ M
 *             VCO_IN limitleri: 1-2 MHz arasında olmalı
 * 
 *          3. PLLN Bulma: VCO'nun çarpma faktörünü hesaplar.
 *             VCO_OUT = VCO_IN × N
 *             N = VCO_OUT ÷ VCO_IN (tam sayı olmalı)
 * 
 *          4. PLLQ Bulma: USB/SDIO için bölme faktörünü hesaplar.
 *             USB_CLK = VCO_OUT ÷ Q
 *             Q limitleri: 2-15 arasında olmalı, hedef 48 MHz
 * 
 * @param  OscInit: RCC osilatör yapılandırma yapısının pointer'ı
 *         - OscillatorType: HSE veya HSI seçimi yapılmış olmalı
 *         - PLL.PLLM, PLLN, PLLP, PLLQ: Fonksiyon tarafından doldurulur
 * 
 * @param  hedef_sysclk_mhz: İstenen sistem saat frekansı (MHz cinsinden)
 *         Örnek: 168 (168 MHz için)
 *         Tipik değerler: 84, 100, 120, 168, 180 MHz
 * 
 * @param  hedef_q_mhz: İstenen USB/SDIO/RNG saat frekansı (MHz cinsinden)
 *         Örnek: 48 (USB için standart 48 MHz)
 *         Not: USB çalışması için tam olarak 48 MHz gereklidir
 * 
 * @retval  0: Başarılı - PLL parametreleri hesaplandı
 *         -1: Hata - İstenen frekanslar PLL limitleri dışında veya 
 *                    tam sayı bölünemiyor (kesirli sonuç oluşuyor)
 * 
 * @note   VCO Limitleri:
 *         - VCO giriş: 1-2 MHz
 *         - VCO çıkış: 100-432 MHz
 * 
 * @note   PLL Parametre Limitleri:
 *         - PLLM: 2-63 (Bu kodda: HSE/HSI ÷ 1 MHz)
 *         - PLLN: 50-432
 *         - PLLP: 2, 4, 6, 8
 *         - PLLQ: 2-15
 * 
 * @warning Bu fonksiyon çağrılmadan önce OscInit->OscillatorType değeri
 *          RCC_OSCILLATORTYPE_HSE veya RCC_OSCILLATORTYPE_HSI içermelidir.
 * 
 * @example
 *          RCC_OscInitTypeDef OscInit = {0};
 *          OscInit.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_PLL;
 *          OscInit.HSEState = 1;
 *          OscInit.PLL.PLLState = 1;
 *          OscInit.PLL.PLLSource = 1;
 *          
 *          if(RCC_PLL_DegerleriniHesapla(&OscInit, 168, 48) == 0) {
 *              // PLLM=8, PLLN=336, PLLP=2, PLLQ=7
 *              // SYSCLK = 168 MHz, USB = 48 MHz
 *          }
 */
int RCC_PLL_DegerleriniHesapla(RCC_OscInitTypeDef *OscInit, uint32_t hedef_sysclk_mhz, uint32_t hedef_q_mhz)
{
    // MHz'den Hz'e çeviriyoruz (1 MHz = 1,000,000 Hz)
    uint64_t hedef_sysclk_hz = (uint64_t)hedef_sysclk_mhz * 1000000;
    uint64_t hedef_q_hz = (uint64_t)hedef_q_mhz * 1000000;
    
    uint32_t p_degerleri[4] = {2, 4, 6, 8};
    uint64_t vco_ana_cikis = 0;
    uint64_t vco_giris = 0;
    
    // PLLP değerini bul
    for(int i=0; i < 4; i++)
    {
        uint32_t p_deneme = p_degerleri[i];
        uint64_t vco_cikis = hedef_sysclk_hz * p_deneme;
        
        if(vco_cikis >= VCO_OUT_MIN && vco_cikis <= VCO_OUT_MAX)
        {
            OscInit->PLL.PLLP = p_deneme;
            vco_ana_cikis = vco_cikis;
            break;
        }
    }
    
    if(vco_ana_cikis == 0)
    {
        return -1;
    }
    
    // HSE mi HSI mi kontrol et
    if((OscInit->OscillatorType & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE)
    {
        OscInit->PLL.PLLM = HSE / VCO_IN_MIN;
        vco_giris = HSE / (OscInit->PLL.PLLM);
    }
    else if((OscInit->OscillatorType & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI)
    {
        OscInit->PLL.PLLM = HSI / VCO_IN_MIN;
        vco_giris = HSI / (OscInit->PLL.PLLM);
    }
    else
    {
        return -1; // Ne HSE ne de HSI seçilmiş
    }
    
    // PLLN hesapla
    OscInit->PLL.PLLN = (uint32_t)(vco_ana_cikis / vco_giris);
    
    if(vco_ana_cikis % vco_giris != 0)
    {
        return -1;
    }
    
    // PLLQ hesapla
    OscInit->PLL.PLLQ = (uint32_t)(vco_ana_cikis / hedef_q_hz);
    
    if(vco_ana_cikis % hedef_q_hz != 0 || OscInit->PLL.PLLQ < 2 || OscInit->PLL.PLLQ > 15)
    {
        return -1;
    }
    
    return 0;
}

