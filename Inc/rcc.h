#include "../Inc/stm32f407xx.h"
#include <stdint.h>

/* ===============================
   RCC PLL yapılandırma yapısı
   =============================== */
typedef struct
{
  uint32_t PLLState;   /*!< PLL'in Durumu (ON/OFF). @ref RCC_PLL_State */
  uint32_t PLLSource;  /*!< PLL'in Giriş Kaynağı (HSI veya HSE). @ref RCC_PLL_Source */

  uint32_t PLLM;       /*!< PLL Bölme Faktörü (VCO girişi için). */
  uint32_t PLLN;       /*!< PLL Çarpma Faktörü (VCO çıkışı için). */
  uint32_t PLLP;       /*!< Ana Sistem Saati (SYSCLK) Bölme Faktörü (2, 4, 6, 8). @ref RCC_PLLP_Clock_Divider */
  uint32_t PLLQ;       /*!< Çevre Birimleri (USB, SDIO, RNG) Bölme Faktörü. */

} RCC_PLLInitTypeDef;


/* RCC Internal/External Oscillator (HSE, HSI, LSE and LSI) configuration structure definition  */
typedef struct
{
  uint32_t OscillatorType;       /*!< Hangi Osilatörlerin Yapılandırılacağını Belirtir. @ref RCC_OSCILLATORTYPE_ */

  uint32_t HSEState;            /*!< HSE Osilatörünün Durumu (ON/OFF/Bypass). @ref RCC_HSE_State */
  uint32_t LSEState;            /*!< LSE Osilatörünün Durumu (ON/OFF/Bypass). @ref RCC_LSE_State */
  uint32_t HSIState;            /*!< HSI Osilatörünün Durumu (ON/OFF). @ref RCC_HSI_State */
  uint32_t LSIState;            /*!< LSI Osilatörünün Durumu (ON/OFF). @ref RCC_LSI_State */

  uint32_t HSICalibrationValue; /*!< HSI Osilatörünün Kalibrasyon Değeri (0x00..0x1F). */

  RCC_PLLInitTypeDef PLL;       /*!< PLL Yapılandırmasını Tutar. */

} RCC_OscInitTypeDef;


/* RCC System, AHB and APB busses clock configuration structure definition */
typedef struct
{
  uint32_t ClockType;       /*!< Hangi Saatlerin Yapılandırılacağını Belirtir (SYSCLK, HCLK, PCLK1, PCLK2). @ref RCC_Clock_Type */

  uint32_t SYSCLKSource;    /*!< Sistem Saatinin (SYSCLK) Kaynağını Seçer (HSI, HSE veya PLL). @ref RCC_System_Clock_Source */

  uint32_t AHBCLKDivider;   /*!< AHB Veri Yolu Saatini (HCLK) Böler. @ref RCC_AHB_Clock_Divider */
  uint32_t APB1CLKDivider;  /*!< APB1 Veri Yolu Saatini (PCLK1) Böler. @ref RCC_APB1_APB2_Clock_Divider */
  uint32_t APB2CLKDivider;  /*!< APB2 Veri Yolu Saatini (PCLK2) Böler. @ref RCC_APB1_APB2_Clock_Divider */

} RCC_ClkInitTypeDef;

/* -------- HSE State --------- */
#define RCC_HSE_OFF    0x00000000U
#define RCC_HSE_ON     (1U << RCC_CR_HSEON)
#define RCC_HSE_BYPASS ((1U << RCC_CR_HSEBYP) | (1U << RCC_CR_HSEON))

/* -------- HSI State --------- */
#define RCC_HSI_OFF   ((uint8_t)0x00U)
#define RCC_HSI_ON    ((uint8_t)0x01U)

/* -------- LSI State --------- */
#define RCC_LSI_OFF   ((uint8_t)0x00U)
#define RCC_LSI_ON    ((uint8_t)0x01U)

/* -------- LSE State --------- */
#define RCC_LSE_OFF    0x00000000U
#define RCC_LSE_ON     (1U << RCC_BDCR_LSEON)
#define RCC_LSE_BYPASS ((1U << RCC_BDCR_LSEBYP) | (1U << RCC_BDCR_LSEON)) 

/* -------- PLL State --------- */
#define RCC_PLL_NONE ((uint8_t)0x00U)
#define RCC_PLL_OFF  ((uint8_t)0x01U)
#define RCC_PLL_ON   ((uint8_t)0x02U)

/* -------- PLL Source --------- */
#define RCC_PLLSOURCE_HSI  (0U << RCC_PLLCFGR_PLLSRC)
#define RCC_PLLSOURCE_HSE  (1U << RCC_PLLCFGR_PLLSRC)

/* -------- SYSCLK Source --------- */
#define RCC_OSCILLATORTYPE_NONE  0x00000000U
#define RCC_OSCILLATORTYPE_HSE   0x00000001U
#define RCC_OSCILLATORTYPE_HSI   0x00000002U
#define RCC_OSCILLATORTYPE_LSE   0x00000004U
#define RCC_OSCILLATORTYPE_LSI   0x00000008U
#define RCC_OSCILLATORTYPE_PLL   0x00000010U


/* -------- AHB Prescaler -------- */
#define RCC_AHB_DIV_1    0x00U
#define RCC_AHB_DIV_2    0x08U
#define RCC_AHB_DIV_4    0x09U
#define RCC_AHB_DIV_8    0x0AU
#define RCC_AHB_DIV_16   0x0BU
#define RCC_AHB_DIV_64   0x0CU
#define RCC_AHB_DIV_128  0x0DU
#define RCC_AHB_DIV_256  0x0EU
#define RCC_AHB_DIV_512  0x0FU

/* -------- APB1 and APB2 Prescaler -------- */
#define RCC_APB_DIV_1    0x00U
#define RCC_APB_DIV_2    0x04U
#define RCC_APB_DIV_4    0x05U
#define RCC_APB_DIV_8    0x06U
#define RCC_APB_DIV_16   0x07U

/* -------- HCLK Prescaler -------- */
#define RCC_HCLK_DIV_1  0x00U
#define RCC_HCLK_DIV_2  0x04U
#define RCC_HCLK_DIV_4  0x05U
#define RCC_HCLK_DIV_8  0x06U
#define RCC_HCLK_DIV_16 0x07U

/* -------- Clock Type -------- */
#define RCC_CLOCKTYPE_SYSCLK   0x00000001U
#define RCC_CLOCKTYPE_HCLK     0x00000002U
#define RCC_CLOCKTYPE_PCLK1    0x00000004U
#define RCC_CLOCKTYPE_PCLK2    0x00000008U
#define RCC_CLOCKTYPE_PLL      0x00000010U

/* -------- Flash Latency -------- */
#define FLASH_LATENCY_0    0x00000000U  /* 0 Wait State  */
#define FLASH_LATENCY_1    0x00000001U  /* 1 Wait State  */
#define FLASH_LATENCY_2    0x00000002U  /* 2 Wait States */
#define FLASH_LATENCY_3    0x00000003U  /* 3 Wait States  */

/* -------- HSI Calibration Default Value ------- */
#define RCC_HSICALIBRATION_DEFAULT       0x10U         

/* -------- System Clock Switch Type  -------- */
#define RCC_SYSCLKSOURCE_HSI    0x00U
#define RCC_SYSCLKSOURCE_HSE    0x01U
#define RCC_SYSCLKSOURCE_PLL    0x02U

/* Some Useful Macros */
#define HSE 8000000
#define HSI 16000000
#define VCO_IN_MIN 1000000
#define VCO_IN_MAX 2000000
#define VCO_OUT_MIN 100000000
#define VCO_OUT_MAX 432000000


/* Function Prototypes */
uint32_t RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
uint32_t RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FlashLatency);
uint32_t RCC_GetSYSClockFreq(void);
int RCC_PLL_DegerleriniHesapla(RCC_OscInitTypeDef *OscInit, uint32_t hedef_sysclk_mhz, uint32_t hedef_q_mhz);

/* ---------------- OSCILLATOR TYPE CHECK ---------------- */
#define IS_RCC_OSCILLATORTYPE(TYPE) \
          ((((TYPE) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE)   || \
           (((TYPE) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI)   || \
           (((TYPE) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE)   || \
           (((TYPE) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI)   || \
           ((TYPE) == RCC_OSCILLATORTYPE_NONE))

/* ---------------- HSE CHECK ---------------- */
#define IS_RCC_HSE(STATE) \
          (((STATE) == RCC_HSE_OFF) ||  ((STATE) == RCC_HSE_ON) ||  ((STATE) == RCC_HSE_BYPASS))
  
/* ---------------- HSI CHECK ---------------- */
#define IS_RCC_HSI(STATE) \
          (((STATE) == RCC_HSI_OFF) ||  ((STATE) == RCC_HSI_ON))

/* ---------------- Calibration CHECK ---------------- */          
#define IS_RCC_CALIBRATION_VALUE(VALUE) \
          ((VALUE) <= 0x1FU)

/* ---------------- LSI CHECK ---------------- */          
#define IS_RCC_LSI(STATE) \
          (((STATE) == RCC_LSI_OFF) ||  ((STATE) == RCC_LSI_ON)) 
          
/* ---------------- LSE CHECK ---------------- */               
#define IS_RCC_LSE(STATE) \
          (((STATE) == RCC_LSE_OFF) ||  ((STATE) == RCC_LSE_ON) ||  ((STATE) == RCC_LSE_BYPASS))

/* ---------------- PLL CHECK ---------------- */
#define IS_RCC_PLL(STATE) \
          (((STATE) == RCC_PLL_NONE) ||  ((STATE) == RCC_PLL_ON) ||  ((STATE) == RCC_PLL_OFF))


#define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSOURCE_HSI) || \
                                       ((SOURCE) == RCC_SYSCLKSOURCE_HSE) || \
                                       ((SOURCE) == RCC_SYSCLKSOURCE_PLL))

#define IS_RCC_CLOCKTYPE(TYPE)   (((TYPE) == RCC_CLOCKTYPE_SYSCLK) || \
                                  ((TYPE) == RCC_CLOCKTYPE_HCLK)   || \
                                  ((TYPE) == RCC_CLOCKTYPE_PCLK1)  || \
                                  ((TYPE) == RCC_CLOCKTYPE_PCLK2))

#define IS_FLASH_LATENCY(LATENCY) (((LATENCY) == FLASH_LATENCY_0) || \
                                   ((LATENCY) == FLASH_LATENCY_1) || \
                                   ((LATENCY) == FLASH_LATENCY_2) || \
                                   ((LATENCY) == FLASH_LATENCY_3))

#define IS_RCC_AHB_CLOCK_DIVIDER(DIVIDER)  (((DIVIDER) == RCC_AHB_DIV_1)  || \
                                             ((DIVIDER) == RCC_AHB_DIV_2)  || \
                                             ((DIVIDER) == RCC_AHB_DIV_4)  || \
                                             ((DIVIDER) == RCC_AHB_DIV_8)  || \
                                             ((DIVIDER) == RCC_AHB_DIV_16) || \
                                             ((DIVIDER) == RCC_AHB_DIV_64) || \
                                             ((DIVIDER) == RCC_AHB_DIV_128)|| \
                                             ((DIVIDER) == RCC_AHB_DIV_256)|| \
                                             ((DIVIDER) == RCC_AHB_DIV_512))
                
#define IS_RCC_PCLK(DIVIDER) (((DIVIDER) == RCC_APB_DIV_1)  || \
                                 ((DIVIDER) == RCC_APB_DIV_2)  || \
                                 ((DIVIDER) == RCC_APB_DIV_4)  || \
                                 ((DIVIDER) == RCC_APB_DIV_8)  || \
                                 ((DIVIDER) == RCC_APB_DIV_16))

#define RCC_SYSCLK_CONFIG(SOURCE) \
            MODIFY_REG(RCC->CFGR, (0x3 << RCC_CFGR_SW ), (SOURCE) << RCC_CFGR_SW)



                                                     


