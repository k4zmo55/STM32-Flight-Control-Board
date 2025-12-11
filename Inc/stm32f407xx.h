#ifndef STM32F407XX_H
#define STM32F407XX_H

#include <stdint.h>
#include <stdio.h>

/* Peripheral base addresses */
#define AHB2PERIPH_BASE       ((uint32_t)0x50000000U)
#define AHB1PERIPH_BASE       ((uint32_t)0x40020000U)
#define APB2PERIPH_BASE       ((uint32_t)0x40010000U)
#define APB1PERIPH_BASE       ((uint32_t)0x40000000U)

#define NVIC_PRI_BASE_ADDR    ((volatile uint32_t*)0xE000E400U)
#define NO_PR_BITS_IMPLEMENTED 4
/*

      AHB2 Peripheral base address definations

*/
#define USB_OTG_FS_PERIPH_BASE    (AHB2PERIPH_BASE + 0x0000U)

/*
 
      AHB1 Peripheral base address definations
  
*/

/* GPIOx Peripherals base address defination hanging on AHB1 Buss*/
#define GPIOA_BASE               (AHB1PERIPH_BASE + 0x0000U)
#define GPIOB_BASE               (AHB1PERIPH_BASE + 0x0400U)
#define GPIOC_BASE               (AHB1PERIPH_BASE + 0x0800U)
#define GPIOD_BASE               (AHB1PERIPH_BASE + 0x0C00U)
#define GPIOE_BASE               (AHB1PERIPH_BASE + 0x1000U)
#define GPIOF_BASE               (AHB1PERIPH_BASE + 0x1400U)
#define GPIOG_BASE               (AHB1PERIPH_BASE + 0x1800U)
#define GPIOH_BASE               (AHB1PERIPH_BASE + 0x1C00U)
#define GPIOI_BASE               (AHB1PERIPH_BASE + 0x2000U)
#define GPIOJ_BASE               (AHB1PERIPH_BASE + 0x2400U)
#define GPIOK_BASE               (AHB1PERIPH_BASE + 0x2800U)

/* CRC Peripheral base address definations hanging on AHB1 Bus*/
#define CRC_BASE (AHB1PERIPH_BASE + 0x3000U)

/* RCC Peripheral base address definations hanging on AHB1 Bus*/
#define RCC_BASE (AHB1PERIPH_BASE + 0x3800U)

/* Flash Interface Register Peripheral base address definations hanging on AHB1 Bus*/
#define FLASH_BASE (AHB1PERIPH_BASE + 0x3C00U)

/* DMA Peripherals base addres definations hanging on AHB1 Bus*/
#define DMA1_BASE (AHB1PERIPH_BASE + 0x6000U)
#define DMA2_BASE (AHB1PERIPH_BASE + 0x6400U)

/*
 
      APB2 Peripheral base address definations
  
*/

/* TIMx Peripheral base address definations hanging on APB2 Bus*/
#define TIM1_BASE    (APB2PERIPH_BASE + 0x0000U)
#define TIM8_BASE    (APB2PERIPH_BASE + 0x0400U)
#define TIM9_BASE    (APB2PERIPH_BASE + 0x4000U)
#define TIM10_BASE   (APB2PERIPH_BASE + 0x4400U)

/* USARTx Peripheral base addres definations hanging on APB2 Bus*/
#define USART1_BASE  (APB2PERIPH_BASE + 0x1000U)
#define USART6_BASE  (APB2PERIPH_BASE + 0x1400U)

/* ADCx Peripheral base address definatinos hanging on APB2 Bus*/
#define ADCx_BASE    (APB2PERIPH_BASE + 0x2000U)

/* SPIx Peripheral base address definations hanging on APB2 Bus*/
#define SPI1_BASE    (APB2PERIPH_BASE + 0x3000U)
#define SPI4_BASE    (APB2PERIPH_BASE + 0x3400U)
#define SPI5_BASE    (APB2PERIPH_BASE + 0x5000U)
#define SPI6_BASE    (APB2PERIPH_BASE + 0x5400U)

/* SYSCFG Peripheral base addres defination hanging on APB2 Bus*/
#define SYSCFG_BASE  (APB1PERIPH_BASE + 0x3800U)

/* EXTI Peripheral base address definations hanging on APB2 Bus*/
#define EXTI_BASE    (APB2PERIPH_BASE + 0x3C00U)

/*
 
      APB1 Peripheral base address definations
  
*/

/* TIMx Peripheral base address definations*/
#define TIM2_BASE    (APB1PERIPH_BASE + 0x0000U)
#define TIM3_BASE    (APB1PERIPH_BASE + 0x0400U)
#define TIM4_BASE    (APB1PERIPH_BASE + 0x0800U)
#define TIM5_BASE    (APB1PERIPH_BASE + 0x0C00U)
#define TIM6_BASE    (APB1PERIPH_BASE + 0x1000U)
#define TIM7_BASE    (APB1PERIPH_BASE + 0x1400U)
#define TIM12_BASE   (APB1PERIPH_BASE + 0x1800U)
#define TIM13_BASE   (APB1PERIPH_BASE + 0x1C00U)
#define TIM14_BASE   (APB1PERIPH_BASE + 0x2000U)

/* RTC Peripheral base address definations hanging on APB1 Bus*/
#define RTC_BASE     (APB1PERIPH_BASE + 0x2800U)

/* WWDG Peripheral base address definations hanging on APB1 Bus*/
#define WWDG_BASE    (APB1PERIPH_BASE + 0x2C00U)

/* SPIx Peripheral base address definatinos hanging on APB1 Bus*/
#define SPI2_BASE    (APB1PERIPH_BASE + 0x3800U)
#define SPI3_BASE    (APB1PERIPH_BASE + 0x3C00U)

/* USARTx Peripheral base addres definations hanging on APB1 Bus*/
#define USART2_BASE  (APB1PERIPH_BASE + 0x4400U)
#define USART3_BASE  (APB1PERIPH_BASE + 0x4800U)
#define UART4_BASE   (APB1PERIPH_BASE + 0x4C00U)
#define UART5_BASE   (APB1PERIPH_BASE + 0x5000U)
#define UART7_BASE   (APB1PERIPH_BASE + 0x7800U)
#define UART8_BASE   (APB1PERIPH_BASE + 0x7C00U)

/* I2Cx Peripheral base address definations hanging on APB1 Bus*/
#define I2C1_BASE    (APB1PERIPH_BASE + 0x5400U)
#define I2C2_BASE    (APB1PERIPH_BASE + 0x5800U)
#define I2C3_BASE    (APB1PERIPH_BASE + 0x5C00U)

/* PWR Peripheral base address definations hanging on APB1 Bus*/
#define PWR_BASE     (APB1PERIPH_BASE + 0x7000U)


/* Peripheral Register Mapping Structures*/

typedef struct{
   uint32_t MODER;      /*!< GPIO port mode register,               Address offset: 0x00 */
   uint16_t OTYPER;     /*!< GPIO port output type register,        Address offset: 0x04 */
   uint32_t OSPEEDR;    /*!< GPIO port output speed register,       Address offset: 0x08 */
   uint32_t PUPDR;      /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C */
   uint16_t IDR;        /*!< GPIO port input data register,         Address offset: 0x10 */
   uint16_t ODR;        /*!< GPIO port output data register,        Address offset: 0x14 */
   uint32_t BSRR;       /*!< GPIO port bit set/reset register,      Address offset: 0x18 */
   uint16_t LCKR;       /*!< GPIO port configuration lock register, Address offset: 0x1C */
   uint32_t AFR[2];     /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
}GPIOx_RegDef;

typedef struct {
    uint32_t CR;            /*!< Clock control register                       Address Offset: 0x00*/
    uint32_t PLLCFGR;       /*!< PLL configuration register                   Address Offset: 0x04*/
    uint32_t CFGR;          /*!< Clock configuration register                 Address Offset: 0x08*/
    uint32_t CIR;           /*!< Clock interrupt register                     Address Offset: 0x0C*/
    uint32_t AHB1RSTR;      /*!< AHB1 peripheral reset register               Address Offset: 0x10*/
    uint32_t AHB2RSTR;      /*!< AHB2 peripheral reset register               Address Offset: 0x14*/
    uint32_t AHB3RSTR;      /*!< AHB3 peripheral reset register               Address Offset: 0x18*/
    uint32_t RESERVED0;     /*!< Reserved (Boşluk/Yedek)                      Address Offset: 0x1C*/
    uint32_t APB1RSTR;      /*!< APB1 peripheral reset register               Address Offset: 0x20*/
    uint32_t APB2RSTR;      /*!< APB2 peripheral reset register               Address Offset: 0x24*/
    uint32_t RESERVED1;     /*!< Reserved (Boşluk/Yedek)                      Address Offset: 0x28*/
    uint32_t RESERVED2;     /*!< Reserved (Boşluk/Yedek)                      Address Offset: 0x2C*/
    uint32_t AHB1ENR;       /*!< AHB1 peripheral clock enable register        Address Offset: 0x30*/
    uint32_t AHB2ENR;       /*!< AHB2 peripheral clock enable register        Address Offset: 0x34*/
    uint32_t AHB3ENR;       /*!< AHB3 peripheral clock enable register        Address Offset: 0x38*/
    uint32_t RESERVED3;     /*!< Reserved (Boşluk/Yedek)                      Address Offset: 0x3C*/
    uint32_t APB1ENR;       /*!< APB1 peripheral clock enable register        Address Offset: 0x40*/
    uint32_t APB2ENR;       /*!< APB2 peripheral clock enable register        Address Offset: 0x44*/
    uint32_t RESERVED4;     /*!< Reserved (Boşluk/Yedek)                      Address Offset: 0x48*/
    uint32_t RESERVED5;     /*!< Reserved (Boşluk/Yedek)                      Address Offset: 0x4C*/
    uint32_t AHB1LPENR;     /*!< AHB1 low power mode clock enable register    Address Offset: 0x50*/
    uint32_t AHB2LPENR;     /*!< AHB2 low power mode clock enable register    Address Offset: 0x54*/
    uint32_t AHB3LPENR;     /*!< AHB3 low power mode clock enable register    Address Offset: 0x58*/
    uint32_t RESERVED6;     /*!< Reserved (Boşluk/Yedek)                      Address Offset: 0x5C*/
    uint32_t APB1LPENR;     /*!< APB1 low power mode clock enable register    Address Offset: 0x60*/
    uint32_t APB2LPENR;     /*!< APB2 low power mode clock enable register    Address Offset: 0x64*/
    uint32_t RESERVED7;     /*!< Reserved (Boşluk/Yedek)                      Address Offset: 0x68*/
    uint32_t RESERVED8;     /*!< Reserved (Boşluk/Yedek)                      Address Offset: 0x6C*/
    uint32_t BDCR;          /*!< Backup domain control register               Address Offset: 0x70*/
    uint32_t CSR;           /*!< Clock security system register               Address Offset: 0x74*/
    uint32_t RESERVED9;     /*!< Reserved (Boşluk/Yedek)                      Address Offset: 0x78*/
    uint32_t RESERVED10;    /*!< Reserved (Boşluk/Yedek)                      Address Offset: 0x7C*/
    uint32_t SSCGR;         /*!< Spread spectrum clock generation register    Address Offset: 0x80*/
    uint32_t PLLI2SCFGR;    /*!< PLLI2S configuration register                Address Offset: 0x84*/
    uint32_t PLLSAICFGR;    /*!< PLLSAI configuration register                Address Offset: 0x88*/
    uint32_t DCKFGR;        /*!< Dedicated clock configuration register       Address Offset: 0x8C*/
} RCC_TypeDef;

typedef struct{
      uint16_t CR1;           /*!< Control register 1        Address offset: 0x00 */
      uint8_t  CR2;           /*!< Control register 2        Address offset: 0x04 */
      uint16_t SR;            /*!< Status register           Address offset: 0x08 */
      uint16_t DR;            /*!< Data register             Address offset: 0x0C */         
      uint16_t CRCPR;         /*!< CRC polynomial register   Address offset: 0x10 */
      uint16_t RXCRCR;        /*!< RX CRC register           Address offset: 0x14 */
      uint16_t TXCRCR;        /*!< TX CRC register           Address offset: 0x18 */
      uint16_t I2SCFGR;       /*!< I2S configuration register Address offset: 0x1C */
      uint16_t I2SPR;         /*!< I2S prescaler register    Address offset: 0x20 */
} SPIx_RegDef;

typedef struct{
     uint16_t CR1;          /*!< Control register 1        Address offset: 0x00 */
     uint16_t CR2;          /*!< Control register 2        Address offset: 0x04 */
     uint16_t OAR1;         /*!< Own address register 1    Address offset: 0x08 */
     uint8_t  OAR2;         /*!< Own address register 2    Address offset: 0x0C */
     uint8_t  DR;           /*!< Data register             Address offset: 0x10 */
     uint16_t SR1;          /*!< Status register 1         Address offset: 0x14 */
     uint16_t SR2;          /*!< Status register 2         Address offset: 0x18 */
     uint16_t CCR;          /*!< Clock control register    Address offset: 0x1C */
     uint8_t TRISE;         /*!< Rise time register        Address offset: 0x20 */
     uint8_t FLTR;          /*!< Filter register           Address offset: 0x24 */
}I2Cx_RegDef;

typedef struct{
     uint16_t ACR;      /*!< Flash access control register, Address offset: 0x00 */
     uint32_t KEYR;     /*!< Flash key register,            Address offset: 0x04 */
     uint32_t OPTKEYR;  /*!< Flash option key register,     Address offset: 0x08 */
     uint16_t SR;       /*!< Flash status register,         Address offset: 0x0C */
     uint16_t CR;       /*!< Flash control register,        Address offset: 0x10 */
     uint32_t OPTCR;    /*!< Flash option control register, Address offset: 0x14 */
}FLASH_RegDef;

typedef struct{
      uint32_t IMR;      /*!< Interrupt mask register,                    Address offset: 0x00 */
      uint32_t EMR;      /*!< Event mask register,                        Address offset: 0x04 */
      uint32_t RTSR;     /*!< Rising trigger selection register,          Address offset: 0x08 */
      uint32_t FTSR;     /*!< Falling trigger selection register,         Address offset: 0x0C */
      uint32_t SWIER;    /*!< Software interrupt event register,          Address offset: 0x10 */
      uint32_t PR;       /*!< Pending register,                           Address offset: 0x14 */
}EXTI_RegDef_t;

typedef struct{
      uint32_t MEMRMP;       /*!< Memory remap register,                    Address offset: 0x00 */
      uint32_t PMC;          /*!< Peripheral mode configuration register,   Address offset: 0x04 */
      uint32_t EXTICR[4];    /*!< External interrupt configuration registers,Address offset: 0x08-0x14 */
      uint32_t CMPCR;        /*!< Compensation cell control register,       Address offset: 0x20 */
      uint32_t RESERVED[2];
      uint32_t CFGR;         /*!< SYSCFG configuration register,            Address offset: 0x2C */
}SYSCFG_RegDef_t;

/* Peripheral Definations*/
#define GPIOA               ((GPIOx_RegDef *)GPIOA_BASE)
#define GPIOB               ((GPIOx_RegDef *)GPIOB_BASE)
#define GPIOC               ((GPIOx_RegDef *)GPIOC_BASE)
#define GPIOD               ((GPIOx_RegDef *)GPIOD_BASE)
#define GPIOE               ((GPIOx_RegDef *)GPIOE_BASE)
#define GPIOF               ((GPIOx_RegDef *)GPIOF_BASE)
#define GPIOG               ((GPIOx_RegDef *)GPIOG_BASE)
#define GPIOH               ((GPIOx_RegDef *)GPIOH_BASE)
#define GPIOI               ((GPIOx_RegDef *)GPIOI_BASE)
#define GPIOJ               ((GPIOx_RegDef *)GPIOJ_BASE)
#define GPIOK               ((GPIOx_RegDef *)GPIOK_BASE)

#define RCC                 ((RCC_TypeDef *)RCC_BASE)

#define SPI1                ((SPIx_RegDef *)SPI1_BASE)
#define SPI2                ((SPIx_RegDef *)SPI2_BASE)
#define SPI3                ((SPIx_RegDef *)SPI3_BASE)
#define SPI4                ((SPIx_RegDef *)SPI4_BASE)
#define SPI5                ((SPIx_RegDef *)SPI5_BASE)
#define SPI6                ((SPIx_RegDef *)SPI6_BASE)

#define I2C1                ((I2Cx_RegDef *)I2C1_BASE)
#define I2C2                ((I2Cx_RegDef *)I2C2_BASE)
#define I2C3                ((I2Cx_RegDef *)I2C3_BASE)

#define FLASH               ((FLASH_RegDef *)FLASH_BASE)

#define EXTI                ((EXTI_RegDef_t *)EXTI_BASE)
#define SYSCFG              ((SYSCFG_RegDef_t *)SYSCFG_BASE)

/***********************************

   Peripheral Clock Enable Macros

************************************/

/*    GPIOx Clock Enable Macros hanging on AHB1 Bus */
#define GPIOA_PCLK_EN()    (RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()    (RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()    (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()    (RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()    (RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()    (RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()    (RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()    (RCC->AHB1ENR |= (1 << 7))
#define GPIOI_PCLK_EN()    (RCC->AHB1ENR |= (1 << 8))
#define GPIOJ_PCLK_EN()    (RCC->AHB1ENR |= (1 << 9))
#define GPIOK_PCLK_EN()    (RCC->AHB1ENR |= (1 << 10))

/*    AHB1 Other Peripheral Clock Enable Macros    */
#define CRC_PCLK_EN()      (RCC->AHB1ENR |= (1 << 12))   

/*    TIMx Clock Enable Macros hanging on APB1 and APB2 Bus */
#define TIM1_PCLK_EN()    (RCC->APB2ENR |= (1 << 0))
#define TIM2_PCLK_EN()    (RCC->APB1ENR |= (1 << 0))
#define TIM3_PCLK_EN()    (RCC->APB1ENR |= (1 << 1))
#define TIM4_PCLK_EN()    (RCC->APB1ENR |= (1 << 2))
#define TIM5_PCLK_EN()    (RCC->APB1ENR |= (1 << 3))
#define TIM6_PCLK_EN()    (RCC->APB1ENR |= (1 << 4))
#define TIM7_PCLK_EN()    (RCC->APB1ENR |= (1 << 5))
#define TIM8_PCLK_EN()    (RCC->APB2ENR |= (1 << 1))
#define TIM9_PCLK_EN()    (RCC->APB2ENR |= (1 << 16))
#define TIM10_PCLK_EN()   (RCC->APB2ENR |= (1 << 17))
#define TIM11_PCLK_EN()   (RCC->APB2ENR |= (1 << 18))
#define TIM12_PCLK_EN()   (RCC->APB1ENR |= (1 << 6))
#define TIM13_PCLK_EN()   (RCC->APB1ENR |= (1 << 7))
#define TIM14_PCLK_EN()   (RCC->APB1ENR |= (1 << 8))

/*    WWDG Clock Enable Macros hanging on APB1 Bus */
#define WWDG_PCLK_EN()    (RCC->APB1ENR |= (1 << 11))

/*    SPIx Clock Enable Macros hanging on APB1 and APB2 Bus */
#define SPI1_PCLK_EN()    (RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()    (RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()    (RCC->APB1ENR |= (1 << 15))
#define SPI4_PCLK_EN()    (RCC->APB2ENR |= (1 << 13))
#define SPI5_PCLK_EN()    (RCC->APB2ENR |= (1 << 20))
#define SPI6_PCLK_EN()    (RCC->APB2ENR |= (1 << 21))

/*    USARTx Clock Enable Macros hanging on APB1 and APB2 Bus */
#define USART1_PCLK_EN()  (RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN()  (RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN()  (RCC->APB1ENR |= (1 << 18))
#define USART6_PCLK_EN()  (RCC->APB2ENR |= (1 << 5))
#define UART4_PCLK_EN()   (RCC->APB1ENR |= (1 << 19))
#define UART5_PCLK_EN()   (RCC->APB1ENR |= (1 << 20))
#define UART7_PCLK_EN()   (RCC->APB1ENR |= (1 << 30))
#define UART8_PCLK_EN()   (RCC->APB1ENR |= (1 << 31))
  
/*    I2Cx Clock Enable Macros hanging on APB1 Bus */
#define I2C1_PCLK_EN()    (RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()    (RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()    (RCC->APB1ENR |= (1 << 23))

/*    CANx Clock Enable Macros hanging on APB1 Bus */
#define CAN1_PCLK_EN()    (RCC->APB1ENR |= (1 << 25))
#define CAN2_PCLK_EN()    (RCC->APB1ENR |= (1 << 26))

/*    PWR Clock Enable Macro hanging on APB1 Bus   */
#define PWR_PCLK_EN()     (RCC->APB1ENR |= (1 << 28))

/*    ADCx Clock Enable Macros hanging on APB2 Bus */
#define ADC1_PCLK_EN()    (RCC->APB2ENR |= (1 << 8))
#define ADC2_PCLK_EN()    (RCC->APB2ENR |= (1 << 9))
#define ADC3_PCLK_EN()    (RCC->APB2ENR |= (1 << 10))

/*    SYSCFG Clock Enable Macro hanging on APB2 Bus */
#define SYSCFG_PCLK_EN()  (RCC->APB2ENR |= (1 << 14))
     

/*****************************************

      Peripheral Clock Disable Macros

******************************************/

/* GPIOx Clock Disable Macros hanging on AHB1 Bus */
#define GPIOA_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 5)) // Not: Orijinalde 'AHB1NER' hatası vardı, 'AHB1ENR' olarak düzeltildi.
#define GPIOG_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 7))
#define GPIOI_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 8))
#define GPIOJ_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 9))
#define GPIOK_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 10))

/* AHB1 Other Peripheral Clock Disable Macros */
#define CRC_PCLK_DI()       (RCC->AHB1ENR &= ~(1 << 12))

/* TIMx Clock Disable Macros hanging on APB1 and APB2 Bus */
#define TIM1_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 0))
#define TIM2_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 0))
#define TIM3_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 1))
#define TIM4_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 2))
#define TIM5_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 3))
#define TIM6_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 4))
#define TIM7_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 5))
#define TIM8_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 1))
#define TIM9_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 16))
#define TIM10_PCLK_DI()     (RCC->APB2ENR &= ~(1 << 17))
#define TIM11_PCLK_DI()     (RCC->APB2ENR &= ~(1 << 18))
#define TIM12_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 6))
#define TIM13_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 7))
#define TIM14_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 8))

/* WWDG Clock Disable Macros hanging on APB1 Bus */
#define WWDG_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 11))

/* I2Cx Clock Disable Macros hanging on APB1 Bus */
#define I2C1_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 23))

/* CANx Clock Disable Macros hanging on APB1 Bus */
#define CAN1_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 25))
#define CAN2_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 26))

/* PWR Clock Disable Macro hanging on APB1 Bus */
#define PWR_PCLK_DI()       (RCC->APB1ENR &= ~(1 << 28))

/* UARTx Clock Disable Macros hanging on APB1 Bus */
#define USART2_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 17))
#define USART3_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 18))
#define UART4_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 19))
#define UART5_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 20))
#define UART7_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 30))
#define UART8_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 31))

/* SPIx Clock Disable Macros hanging on APB1 and APB2 Bus */
#define SPI1_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 15))
#define SPI4_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 13))
#define SPI5_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 20))
#define SPI6_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 21))

/* USARTx Clock Disable Macros hanging on APB2 Bus */
#define USART1_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 4))
#define USART6_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 5))

/* ADCx Clock Disable Macros hanging on APB2 Bus */
#define ADC1_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 8))
#define ADC2_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 9))
#define ADC3_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 10))

/* SYSCFG Clock Disable Macro hanging on APB2 Bus */
#define SYSCFG_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 14))


/*SPIx_CR1 Register Definations*/
#define SPI_CR1_CPHA      0
#define SPI_CR1_CPOL      1
#define SPI_CR1_MSTR      2
#define SPI_CR1_BR        3
#define SPI_CR1_SPE       6
#define SPI_CR1_LSBFIRST  7
#define SPI_CR1_SSI       8
#define SPI_CR1_SSM       9
#define SPI_CR1_RXONLY    10
#define SPI_CR1_DFF       11
#define SPI_CR1_CRCNEXT   12
#define SPI_CR1_CRCEN     13
#define SPI_CR1_BIDIOE    14
#define SPI_CR1_BIDIMODE  15

/*SPIx_CR2 Register Definations*/
#define SPI_CR2_RXDMAEN   0
#define SPI_CR2_TXDMAEN   1
#define SPI_CR2_SSOE      2
#define SPI_CR2_FRF       4
#define SPI_CR2_ERRIE     5
#define SPI_CR2_RXNEIE    6
#define SPI_CR2_TXEIE     7

/*SPIx_SR Register Definations*/
#define SPI_SR_RXNE       0
#define SPI_SR_TXE        1
#define SPI_SR_CHSIDE     2
#define SPI_SR_UDR        3
#define SPI_SR_CRCERR     4
#define SPI_SR_MODF       5
#define SPI_SR_OVR        6
#define SPI_SR_BSY        7
#define SPI_SR_FRE        8

/*RCC_APB2RSTR Register Definations*/
#define RCC_APB2RSTR_TIM1RST    0
#define RCC_APB2RSTR_TIM8RST    1
#define RCC_APB2RSTR_USART1RST  4
#define RCC_APB2RSTR_USART6RST  5
#define RCC_APB2RSTR_ADCRST     8
#define RCC_APB2RSTR_SDIORST    11
#define RCC_APB2RSTR_SPI1RST    12
#define RCC_APB2RSTR_SPI4RST    13
#define RCC_APB2RSTR_SYSCFGRST  14
#define RCC_APB2RSTR_TIM9RST    16
#define RCC_APB2RSTR_TIM10RST   17
#define RCC_APB2RSTR_TIM11RST   18
#define RCC_APB2RSTR_SPI5RST    20
#define RCC_APB2RSTR_SPI6RST    21
#define RCC_APB2RSTR_SAI1RST    22
#define RCC_APB2RSTR_LTDCRST    26

/*RCC_APB1RSTR Register Definations*/
#define RCC_APB1RSTR_TIM2RST    0
#define RCC_APB1RSTR_TIM3RST    1
#define RCC_APB1RSTR_TIM4RST    2
#define RCC_APB1RSTR_TIM5RST    3
#define RCC_APB1RSTR_TIM6RST    4
#define RCC_APB1RSTR_TIM7RST    5
#define RCC_APB1RSTR_TIM12RST   6
#define RCC_APB1RSTR_TIM13RST   7
#define RCC_APB1RSTR_TIM14RST   8
#define RCC_APB1RSTR_WWDGRST    11
#define RCC_APB1RSTR_SPI2RST    14
#define RCC_APB1RSTR_SPI3RST    15
#define RCC_APB1RSTR_USART2RST  17
#define RCC_APB1RSTR_USART3RST  18
#define RCC_APB1RSTR_UART4RST   19
#define RCC_APB1RSTR_UART5RST   20
#define RCC_APB1RSTR_I2C1RST    21
#define RCC_APB1RSTR_I2C2RST    22
#define RCC_APB1RSTR_I2C3RST    23
#define RCC_APB1RSTR_CAN1RST    25
#define RCC_APB1RSTR_CAN2RST    26
#define RCC_APB1RSTR_PWRRST     28
#define RCC_APB1RSTR_DACRST     29
#define RCC_APB1RSTR_UART7RST   30
#define RCC_APB1RSTR_UART8RST   31

/*RCC_CR Register Definations*/
#define RCC_CR_HSION            0
#define RCC_CR_HSIRDY           1
#define RCC_CR_HSITRIM          3
#define RCC_CR_HSICAL           8
#define RCC_CR_HSEON            16
#define RCC_CR_HSERDY           17
#define RCC_CR_HSEBYP           18
#define RCC_CR_CSSON            19
#define RCC_CR_PLLON            24
#define RCC_CR_PLLRDY           25

/*RCC_PLLCFGR Register Definations*/
#define RCC_PLLCFGR_PLLM         0
#define RCC_PLLCFGR_PLLN         6
#define RCC_PLLCFGR_PLLP         16
#define RCC_PLLCFGR_PLLSRC       22
#define RCC_PLLCFGR_PLLQ         24

/*RCC_CFGR Register Definations */
#define RCC_CFGR_SW              0
#define RCC_CFGR_SWS             2
#define RCC_CFGR_HPRE            4  //AHB1 Prescaler
#define RCC_CFGR_PPRE1           10 //APB1 Prescaler
#define RCC_CFGR_PPRE2           13 //APB2 Prescaler
#define RCC_CFGR_RTCPRE          16
#define RCC_CFGR_MCO1            21
#define RCC_CFGR_MCO1PRE         24
#define RCC_CFGR_MCO2PRE         27
#define RCC_CFGR_MCO2            30

/*RCC_BDCR Register Definations */
#define RCC_BDCR_LSEON           0
#define RCC_BDCR_LSERDY          1
#define RCC_BDCR_LSEBYP          2
#define RCC_BDCR_RTCSEL          8
#define RCC_BDCR_RTCEN           15
#define RCC_BDCR_BDRST           16

/*RCC_CSR Register Definations */
#define RCC_CSR_LSION           0
#define RCC_CSR_LSIRDY          1

/*I2Cx_CR1 register bit definations*/
#define I2C_CR1_PE              0
#define I2C_CR1_SMBUS           1
#define I2C_CR1_SMBTYPE         3
#define I2C_CR1_ENARP           4
#define I2C_CR1_ENPEC           5
#define I2C_CR1_ENGC            6
#define I2C_CR1_NOSTRETCH       7
#define I2C_CR1_START           8
#define I2C_CR1_STOP            9
#define I2C_CR1_ACK             10
#define I2C_CR1_POS             11
#define I2C_CR1_PEC             12
#define I2C_CR1_ALERT           13
#define I2C_CR1_SWRST           15

/*I2Cx_CR2 register bit definations*/
#define I2C_CR2_FREQ            0
#define I2C_CR2_ITERREN         8
#define I2C_CR2_ITEVTEN         9
#define I2C_CR2_ITBUFEN         10
#define I2C_CR2_DMAEN           11
#define I2C_CR2_LAST            12

/*I2Cx_OAR1 register bit definations*/
#define I2C_OAR1_ADD0           0
#define I2C_OAR1_ADD_7_BIT      1
#define I2C_OAR1_ADD_10_BIT     8
#define I2C_OAR1_ADDMODE        15

/*I2Cx_OAR2 register bit definations*/
#define I2C_OAR2_ENDUAL         0
#define I2C_OAR2_ADD2           1

/*I2Cx_SR1 register bit definations*/
#define I2C_SR1_SB              0
#define I2C_SR1_ADDR            1
#define I2C_SR1_BTF             2
#define I2C_SR1_ADD10           3
#define I2C_SR1_STOPF           4
#define I2C_SR1_RxNE            6
#define I2C_SR1_TxE             7
#define I2C_SR1_BERR            8
#define I2C_SR1_ARLO            9
#define I2C_SR1_AF              10
#define I2C_SR1_OVR             11
#define I2C_SR1_PECERR          12
#define I2C_SR1_TIMEOUT         14
#define I2C_SR1_SMBALERT        15

/*I2Cx_SR2 register bit definations*/
#define I2C_SR2_MSL             0
#define I2C_SR2_BUSY            1
#define I2C_SR2_TRA             2
#define I2C_SR2_GENCALL         4
#define I2C_SR2_SMBDEFAULT      5
#define I2C_SR2_SMBHOST         6
#define I2C_SR2_DUALF           7
#define I2C_SR2_PEC             8

/*I2Cx_CCR register bit definations*/
#define I2C_CCR_CCR             0
#define I2C_CCR_DUTY            14
#define I2C_CCR_FS              15

#define GPIO_BASEADDR_TO_CODE(x)   ( (x == GPIOA) ? 0 :\
                                        (x == GPIOB) ? 1 :\
                                        (x == GPIOC) ? 2 :\
                                        (x == GPIOD) ? 3 :\
                                        (x == GPIOE) ? 4 :\
                                        (x == GPIOF) ? 5 :\
                                        (x == GPIOG) ? 6 :\
                                        (x == GPIOH) ? 7 :\
                                        (x == GPIOI) ? 8 :\
                                        (x == GPIOJ) ? 9 :\
                                        (x == GPIOK) ? 10 :0 )

#define GPIOA_REG_RESET()    do{ (RCC->AHB1RSTR |= (1 << 0));  (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()    do{ (RCC->AHB1RSTR |= (1 << 1));  (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()    do{ (RCC->AHB1RSTR |= (1 << 2));  (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()    do{ (RCC->AHB1RSTR |= (1 << 3));  (RCC->AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()    do{ (RCC->AHB1RSTR |= (1 << 4));  (RCC->AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOF_REG_RESET()    do{ (RCC->AHB1RSTR |= (1 << 5));  (RCC->AHB1RSTR &= ~(1 << 5)); }while(0)
#define GPIOG_REG_RESET()    do{ (RCC->AHB1RSTR |= (1 << 6));  (RCC->AHB1RSTR &= ~(1 << 6)); }while(0)
#define GPIOH_REG_RESET()    do{ (RCC->AHB1RSTR |= (1 << 7));  (RCC->AHB1RSTR &= ~(1 << 7)); }while(0)
#define GPIOI_REG_RESET()    do{ (RCC->AHB1RSTR |= (1 << 8));  (RCC->AHB1RSTR &= ~(1 << 8)); }while(0)
#define GPIOJ_REG_RESET()    do{ (RCC->AHB1RSTR |= (1 << 9));  (RCC->AHB1RSTR &= ~(1 << 9)); }while(0)
#define GPIOK_REG_RESET()    do{ (RCC->AHB1RSTR |= (1 << 10)); (RCC->AHB1RSTR &= ~(1 << 10));}while(0)

#define GPIO_BASEADDR_TO_CODE(pGPIOx) ((pGPIOx == GPIOA) ? 0: \
                                      (pGPIOx == GPIOB) ? 1 : \
                                      (pGPIOx == GPIOC) ? 2 : \
                                      (pGPIOx == GPIOD) ? 3 : \
                                      (pGPIOx == GPIOE) ? 4 : \
                                      (pGPIOx == GPIOF) ? 5 : \
                                      (pGPIOx == GPIOG) ? 6 : \
                                      (pGPIOx == GPIOH) ? 7 : \
                                      (pGPIOx == GPIOI) ? 8 : 0)

/*SPI related status flags definations*/
#define SPI_TXE_FLAG    (1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG   (1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG   (1 << SPI_SR_BSY)

#define MODIFY_REG(REG, CLEARMASK, SETMASK) ((REG) = (((REG) & ~(CLEARMASK)) | (SETMASK)))

#define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
void assert_failed(uint8_t* file, uint32_t line) {while(1);}




/* Some Useful Macros*/
#define ERROR -1
#define SET 1
#define RESET 0
#define ENABLE 1
#define DISABLE 0
#define FLAG_SET 1
#define FLAG_RESET 0
#define HAL_TIMEOUT 0x03

#endif /* STM32F407XX_H */
