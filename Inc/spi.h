#include <stdint.h>
#include "stm32f407xx.h"

/*  Configuration Structure of SPI*/
typedef struct{
    uint8_t SPI_DeviceMode;        /*!< Possible values from @SPI_DEVICE_MODES       */
    uint8_t SPI_BusConfig;         /*!< Possible values from @SPI_BUS_CONFIG         */
    uint8_t SPI_SclkSpeed;         /*!< Possible values from @SPI_SCLK_SPEED         */
    uint8_t SPI_DFF;               /*!< Possible values from @SPI_DATA_FRAME_FORMAT  */
    uint8_t SPI_CPOL;              /*!< Possible values from @SPI_CLOCK_POLARITY     */
    uint8_t SPI_CPHA;              /*!< Possible values from @SPI_CLOCK_PHASE        */
    uint8_t SPI_SSM;               /*!< Possible values from @SPI_SOFTWARE_SLAVE_MANAGEMENT */
} SPI_Config_t;

typedef struct{
    SPIx_RegDef *pSPIx;               /*!< This holds the base address of the SPI port  */
    SPI_Config_t SPIConfig;           /*!< This holds SPI configuration settings        */
    uint8_t RxState;              /*!< SPI reception state                          */
    uint8_t TxState;              /*!< SPI transmission state                       */
    uint8_t *pTxBuffer;              /*!< Pointer to SPI transmission buffer          */
    uint8_t *pRxBuffer;              /*!< Pointer to SPI reception buffer             */
    uint32_t TxLen;                  /*!< SPI transmission length                      */
    uint32_t RxLen;                  /*!< SPI reception length                         */
} SPI_Handle_t;

typedef enum{
    SPI_READY,
    SPI_BUSY_IN_RX,
    SPI_BUSY_IN_TX,
    SPI_OK,
    SPI_ERROR
}SPI_State_t;

/*
    @SPI_DEVICE_MODES
    SPI Device Modes
*/
#define SPI_DEVICE_MODE_MASTER    1
#define SPI_DEVICE_MODE_SLAVE     0

/*
    @SPI_BUS_CONFIG
    SPI Bus Configurations
*/
#define SPI_BUS_CONFIG_FD         1   //Full-Duplex
#define SPI_BUS_CONFIG_HD         2   //Half-Duplex
#define SPI_BUS_CONFIG_SIMPLEX_RX 3   //Simplex Receive-Only

/*
    @SPI_SCLK_SPEED
    SPI Serial Clock Speeds
*/
#define SPI_SCLK_SPEED_DIV2       0
#define SPI_SCLK_SPEED_DIV4       1
#define SPI_SCLK_SPEED_DIV8       2
#define SPI_SCLK_SPEED_DIV16      3
#define SPI_SCLK_SPEED_DIV32      4
#define SPI_SCLK_SPEED_DIV64      5
#define SPI_SCLK_SPEED_DIV128     6
#define SPI_SCLK_SPEED_DIV256     7

/*
    @SPI_DATA_FRAME_FORMAT
    SPI Data Frame Formats
*/
#define SPI_DFF_8BITS             0
#define SPI_DFF_16BITS            1

/*
    @SPI_CLOCK_POLARITY
    SPI Clock Polarity
*/
#define SPI_CPOL_LOW              0
#define SPI_CPOL_HIGH             1

/*
    @SPI_CLOCK_PHASE
    SPI Clock Phase
*/
#define SPI_CPHA_FIRST_EDGE       0
#define SPI_CPHA_SECOND_EDGE      1

/*
    @SPI_SOFTWARE_SLAVE_MANAGEMENT
    SPI Software Slave Management
*/
#define SPI_SSM_DI                0
#define SPI_SSM_EN                1


/*
 * APIs supported by this driver
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPIx_RegDef *pSPIx);

/*SPI Configuration Functions*/
SPI_State_t SPI_ConfigurationDeviceMode(SPIx_RegDef *pSPIx, uint8_t DeviceMode);
SPI_State_t SPI_ConfigurationBusConfig(SPIx_RegDef *pSPIx, uint8_t BusConfig);
SPI_State_t SPI_ConfigurationSerialClockSpeed(SPIx_RegDef *pSPIx, uint8_t SclkSpeed);
SPI_State_t SPI_ConfigurationDataFrameFormat(SPIx_RegDef *pSPIx, uint8_t DFF);
SPI_State_t SPI_ConfigurationClockPolarity(SPIx_RegDef *pSPIx, uint8_t CPOL);
SPI_State_t SPI_ConfigurationClockPhase(SPIx_RegDef *pSPIx, uint8_t CPHA);
SPI_State_t SPI_ConfigurationSoftwareSlaveManagement(SPIx_RegDef *pSPIx, uint8_t SSM);


uint8_t SPI_SendData(SPIx_RegDef *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
uint8_t SPI_ReceiveData(SPIx_RegDef *pSPIx, uint8_t *pRxBuffer, uint32_t Len);
void SPI_MasterTransmitReceive(SPIx_RegDef *pSPIx, uint8_t *pTxBuffer, uint8_t *pRxBuffer, uint32_t Len);
uint8_t SPI_MasterTransmitIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t SPI_MasterReceiveIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len);

void SPI_PeriClockControl(SPIx_RegDef *pSPIx, uint8_t EnOrDi);
void SPI_PeripheralControl(SPIx_RegDef *pSPIx, uint8_t EnOrDi);
void SPI_SSIConfig(SPIx_RegDef *pSPIx, uint8_t EnOrDi);
void SPI_SSOEConfig(SPIx_RegDef *pSPIx, uint8_t EnOrDi);

uint8_t SPI_GetFlagStatus(SPIx_RegDef *pSPIx, uint32_t FlagName);
void SPI_ClearOVRFlag(SPIx_RegDef *pSPIx);
void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle);
void SPI_CloseReception(SPI_Handle_t *pSPIHandle);

//IRQ Configuration and ISR Handling
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi); 
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);

