#include "../Inc/rcc.h"
#include <stdio.h>

volatile uint32_t uwTick = 0;

uint32_t GetTick(void)
{
    return uwTick;
}


#define CLOCK_TIMEOUT 100U

/**
 * @brief  STM32F4xx osilatörlerini (HSE, HSI, LSE, LSI) ve PLL'i yapılandırır
 * 
 * @details Bu fonksiyon, sistem saat kaynaklarını başlatır ve yapılandırır.
 *          Desteklenen osilatörler:
 *          - HSE (High Speed External): Harici kristal osilatör (genellikle 8-25 MHz)
 *          - HSI (High Speed Internal): Dahili RC osilatör (16 MHz)
 *          - LSE (Low Speed External): Harici 32.768 kHz kristal (RTC için)
 *          - LSI (Low Speed Internal): Dahili ~32 kHz RC osilatör
 *          - PLL (Phase Locked Loop): Yüksek frekanslı saat üretimi için
 * 
 * @details Çalışma Mantığı:
 *          Fonksiyon, OscillatorType biti kontrol ederek hangi osilatörlerin
 *          yapılandırılacağını belirler. Her osilatör için:
 *          1. İlgili kontrol bitlerini ayarlar (ENABLE/DISABLE/BYPASS)
 *          2. Osilatörün hazır olmasını bekler (READY flag)
 *          3. Timeout kontrolü yapar (sonsuz döngü önleme)
 * 
 * @details HSE Modları:
 *          - RCC_HSE_ON: Harici kristal/rezonatör kullanımı
 *          - RCC_HSE_BYPASS: Harici saat sinyali girişi (kristal yok)
 *          - RCC_HSE_OFF: HSE devre dışı
 * 
 * @details PLL Yapılandırması:
 *          PLL açılmadan önce tüm parametreler doğrulanır:
 *          - PLLM: 2-63 (VCO giriş bölücü)
 *          - PLLN: 50-432 (VCO çarpan)
 *          - PLLP: 2, 4, 6, 8 (SYSCLK bölücü)
 *          - PLLQ: 2-15 (USB/SDIO bölücü)
 *          
 *          Register yazma sırası:
 *          1. PLL kaynak seçimi (HSE veya HSI)
 *          2. PLLM, PLLN, PLLP, PLLQ değerlerini yaz
 *          3. PLL'i etkinleştir
 *          4. PLLRDY bayrağını bekle
 * 
 * @param  RCC_OscInitStruct: Osilatör yapılandırma yapısının pointer'ı
 *         Doldurulması gereken alanlar:
 *         - OscillatorType: Hangi osilatörlerin yapılandırılacağı (bitwise OR)
 *         - HSEState: HSE durumu (ON/OFF/BYPASS)
 *         - HSIState: HSI durumu (ON/OFF)
 *         - HSICalibrationValue: HSI kalibrasyon değeri (0x00-0x1F)
 *         - LSEState: LSE durumu (ON/OFF/BYPASS)
 *         - LSIState: LSI durumu (ON/OFF)
 *         - PLL.PLLState: PLL durumu (ON/OFF/NONE)
 *         - PLL.PLLSource: PLL kaynak seçimi (HSE/HSI)
 *         - PLL.PLLM, PLLN, PLLP, PLLQ: PLL parametreleri
 * 
 * @retval 0 (SUCCESS): İşlem başarılı
 *         ERROR: Parametre hatası veya NULL pointer
 *         HAL_TIMEOUT: Osilatör hazır olmadı (timeout aşıldı)
 * 
 * @note   Timeout Mekanizması:
 *         Her osilatör için GetTick() kullanılarak zaman aşımı kontrolü yapılır.
 *         CLOCK_TIMEOUT süresi içinde osilatör hazır olmazsa HAL_TIMEOUT döner.
 * 
 * @note   Register İşlemleri:
 *         - RCC->CR: HSE, HSI, PLL kontrol registeri
 *         - RCC->CSR: LSI kontrol registeri
 *         - RCC->BDCR: LSE kontrol registeri (Backup Domain)
 *         - RCC->PLLCFGR: PLL yapılandırma registeri
 * 
 * @warning PLL yapılandırması değiştirilirken:
 *          1. Önce PLL kapatılmalı
 *          2. Parametreler değiştirilmeli
 *          3. Tekrar açılmalı
 *          PLL açıkken parametre değişikliği yapılamaz!
 * 
 * @warning HSE/HSI kapatılırken:
 *          Eğer o an SYSCLK kaynağı olarak kullanılıyorsa kapatılamaz!
 *          Önce SYSCLK başka kaynağa alınmalı.
 * 
 * @example HSE + PLL ile 168 MHz yapılandırma:
 *          RCC_OscInitTypeDef OscInit = {0};
 *          OscInit.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_PLL;
 *          OscInit.HSEState = RCC_HSE_ON;
 *          OscInit.PLL.PLLState = RCC_PLL_ON;
 *          OscInit.PLL.PLLSource = RCC_PLLSOURCE_HSE;
 *          OscInit.PLL.PLLM = 8;
 *          OscInit.PLL.PLLN = 336;
 *          OscInit.PLL.PLLP = 2;
 *          OscInit.PLL.PLLQ = 7;
 *          
 *          if(RCC_OscConfig(&OscInit) != 0) {
 *              // Hata işleme
 *          }
 */
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

/**
 * @brief  STM32F4xx sistem saatlerini (SYSCLK, HCLK, PCLK1, PCLK2) yapılandırır
 * 
 * @details Bu fonksiyon, sistem saat ağacını oluşturur ve tüm veri yolu saatlerini ayarlar.
 *          
 *          Saat Hiyerarşisi:
 *          ┌──────────────────────────────────────────────┐
 *          │  SYSCLK (Sistem Saati - Ana Kaynak)         │
 *          │     ↓                                        │
 *          │  HCLK (AHB Bus - CPU, Memory, DMA)          │
 *          │     ├─→ PCLK1 (APB1 - Düşük Hızlı Çevreler) │
 *          │     └─→ PCLK2 (APB2 - Yüksek Hızlı Çevreler)│
 *          └──────────────────────────────────────────────┘
 * 
 * @details Yapılandırma Sırası:
 *          1. Flash Latency Ayarı (CRITICAL!)
 *             - Yüksek frekanslarda Flash Wait State gereklidir
 *             - Yanlış latency → sistem çökmesi, veri hatası
 *          
 *          2. HCLK (AHB Clock) Ayarı
 *             - CPU, bellek, DMA saati
 *             - SYSCLK'den türetilir (bölücü: 1, 2, 4, 8...)
 *          
 *          3. SYSCLK Kaynak Seçimi
 *             - HSI, HSE veya PLL seçilebilir
 *             - Seçilen kaynak HAZIR (READY) olmalı!
 *          
 *          4. PCLK1 (APB1) Ayarı
 *             - Düşük hızlı çevre birimleri (UART, I2C, SPI1-2)
 *             - MAX 42 MHz (STM32F4 için)
 *          
 *          5. PCLK2 (APB2) Ayarı
 *             - Yüksek hızlı çevre birimleri (SPI3, USART1, ADC)
 *             - MAX 84 MHz (STM32F4 için)
 * 
 * @details Flash Latency Tablosu (STM32F4 @ 3.3V):
 *          SYSCLK Aralığı    | Flash Latency
 *          ------------------|---------------
 *          0-30 MHz          | 0 WS (1 cycle)
 *          30-60 MHz         | 1 WS (2 cycles)
 *          60-90 MHz         | 2 WS (3 cycles)
 *          90-120 MHz        | 3 WS (4 cycles)
 *          120-150 MHz       | 4 WS (5 cycles)
 *          150-168 MHz       | 5 WS (6 cycles)
 * 
 * @param  RCC_ClkInitStruct: Saat yapılandırma yapısının pointer'ı
 *         Doldurulması gereken alanlar:
 *         - ClockType: Hangi saatlerin yapılandırılacağı (bitwise OR)
 *                      RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | 
 *                      RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2
 *         - SYSCLKSource: SYSCLK kaynak seçimi (HSI/HSE/PLL)
 *         - AHBCLKDivider: HCLK bölücü (DIV1, DIV2, DIV4, ..., DIV512)
 *         - APB1CLKDivider: PCLK1 bölücü (DIV1, DIV2, DIV4, DIV8, DIV16)
 *         - APB2CLKDivider: PCLK2 bölücü (DIV1, DIV2, DIV4, DIV8, DIV16)
 * 
 * @param  FlashLatency: Flash Wait State değeri (0-7)
 *         SYSCLK frekansına göre seçilmelidir!
 *         - FLASH_LATENCY_0: 0 WS (0-30 MHz)
 *         - FLASH_LATENCY_1: 1 WS (30-60 MHz)
 *         - FLASH_LATENCY_2: 2 WS (60-90 MHz)
 *         - FLASH_LATENCY_3: 3 WS (90-120 MHz)
 *         - FLASH_LATENCY_4: 4 WS (120-150 MHz)
 *         - FLASH_LATENCY_5: 5 WS (150-168 MHz)
 * 
 * @retval 0 (SUCCESS): İşlem başarılı
 *         ERROR: NULL pointer veya seçilen kaynak hazır değil
 * 
 * @note   Güvenlik Kontrolleri:
 *         - SYSCLK kaynağı seçilmeden önce ilgili osilatör/PLL'in
 *           READY bayrağı kontrol edilir
 *         - PLL → PLLRDY kontrolü
 *         - HSE → HSERDY kontrolü
 *         - HSI → HSIRDY kontrolü
 * 
 * @note   Register İşlemleri:
 *         - FLASH->ACR: Flash Access Control (Latency ayarı)
 *         - RCC->CFGR: Clock Configuration Register
 *           * SW[1:0]: SYSCLK kaynak seçimi
 *           * HPRE[3:0]: AHB prescaler
 *           * PPRE1[2:0]: APB1 prescaler
 *           * PPRE2[2:0]: APB2 prescaler
 * 
 * @warning KRITIK: Flash Latency Önce Ayarlanmalı!
 *          Yanlış sıra → sistem çökmesi:
 *          ✗ YANLIŞ: SYSCLK artır → sonra latency ayarla
 *          ✓ DOĞRU: Latency ayarla → sonra SYSCLK artır
 * 
 * @warning APB Saat Limitleri:
 *          - PCLK1 MAX 42 MHz (STM32F4 için)
 *          - PCLK2 MAX 84 MHz (STM32F4 için)
 *          Bu limitler aşılırsa çevre birimleri çalışmaz!
 * 
 * @warning Timer Saatleri:
 *          - APB prescaler = 1 ise: Timer clock = APBx clock
 *          - APB prescaler > 1 ise: Timer clock = 2 × APBx clock
 * 
 * @example 168 MHz sistem yapılandırması (HSE 8 MHz, PLL):
 *          // 1. Önce PLL'i yapılandır (RCC_OscConfig ile)
 *          // 2. Sonra saat ağacını ayarla:
 *          
 *          RCC_ClkInitTypeDef ClkInit = {0};
 *          ClkInit.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
 *                              RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
 *          ClkInit.SYSCLKSource = RCC_SYSCLKSOURCE_PLL;  // PLL'den al
 *          ClkInit.AHBCLKDivider = RCC_HCLK_DIV1;        // 168 MHz
 *          ClkInit.APB1CLKDivider = RCC_HCLK_DIV4;       // 42 MHz (MAX!)
 *          ClkInit.APB2CLKDivider = RCC_HCLK_DIV2;       // 84 MHz (MAX!)
 *          
 *          // Flash Latency: 168 MHz için 5 WS gerekli
 *          if(RCC_ClockConfig(&ClkInit, FLASH_LATENCY_5) != 0) {
 *              // Hata işleme
 *          }
 *          
 *          // Sonuç:
 *          // SYSCLK = 168 MHz (PLL)
 *          // HCLK   = 168 MHz (CPU, AHB, Memory)
 *          // PCLK1  = 42 MHz  (APB1 çevreleri)
 *          // PCLK2  = 84 MHz  (APB2 çevreleri)
 */
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

