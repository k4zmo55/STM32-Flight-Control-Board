#include <stdint.h>
#include "stm32f407xx.h"
#include "rcc.h"
#include "gpio.h"

typedef struct{
    uint32_t SCLSpeed;        /*!< Possible values from @I2C_SCL_SPEED          */
    uint8_t  DeviceAddress;   /*!< Device address assigned in case of slave     */
    uint8_t  AckControl;      /*!< Possible values from @I2C_ACK_CONTROL        */
    uint8_t  FMDutyCycle;     /*!< Possible values from @I2C_FM_DUTY_CYCLE      */  
}I2C_Config_t;


typedef struct{
    I2Cx_RegDef *pI2Cx;
    I2C_Config_t I2C_Config;
    uint32_t TxLen;
    uint32_t RxLen;
    uint8_t *pTxBuffer;
    uint8_t *pRxBuffer;
    uint8_t TxRxState;
    uint8_t DevAddr;
    uint8_t Sr;
    RCC_Handle_t *pRCCHandle;
}I2C_Handle_t;

/*
    @I2C_SCL_SPEED
    I2C SCL Speed Macros
*/
#define I2C_SCL_SPEED_SM       100000U   //Standard mode
#define I2C_SCL_SPEED_FM4K     400000U   //Fast mode 400kHz
#define I2C_SCL_SPEED_FM2K     200000U   //Fast mode 200kHz 

/*
    @I2C_ACK_CONTROL
    I2C Acknowledgement Control Macros
*/
#define I2C_ACK_ENABLE         1
#define I2C_ACK_DISABLE        0

/*
    @I2C_FM_DUTY_CYCLE
    I2C Fast Mode Duty Cycle Macros
*/
#define I2C_FM_DUTY_2          0
#define I2C_FM_DUTY_16_9       1


void I2C_PeriClockControl(I2Cx_RegDef *pI2Cx, uint8_t EnOrDi);

void I2C_Init(I2C_Handle_t *pI2CHandle);

void I2C_DeInit(I2Cx_RegDef *pI2Cx);

uint8_t I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);

uint8_t I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);

uint8_t I2C_SendIT(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);

uint8_t I2C_ReceiveIT(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);

void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnOrDi);

void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);

void I2C_EV_IRQHandling(I2C_Handle_t *pI2CHandle);

void I2C_ER_IRQHandling(I2C_Handle_t *pI2CHandle);

uint8_t I2C_GetFlagStatus(I2Cx_RegDef *pI2Cx, uint32_t FlagName);

void I2C_CloseReceiveData(I2C_Handle_t *pI2CHandle);

void I2C_CloseSendData(I2C_Handle_t *pI2CHandle);

void I2C_ManageAcking(I2Cx_RegDef *pI2Cx, uint8_t EnOrDi);


/* I2C status definition  */

#define I2C_READY	 		0
#define I2C_BUSY_IN_TX 		1
#define I2C_BUSY_IN_RX 		2

#define I2C_WRITE         0
#define I2C_READ          1

/* I2C application event complete definition  */

#define I2C_EVENT_TX_CMPLT		0
#define I2C_EVENT_RX_CMPLT		1
#define I2C_EVENT_STOP			2

#define IRQ_NO_I2C1_EV    31
#define IRQ_NO_I2C1_ER    32
#define IRQ_NO_I2C2_EV    33
#define IRQ_NO_I2C2_ER    34
#define IRQ_NO_I2C3_EV    72
#define IRQ_NO_I2C3_ER    73


#define I2C_SB_FLAG     (1 << I2C_SR1_SB)
#define I2C_ADDR_FLAG   (1 << I2C_SR1_ADDR)
#define I2C_BTF_FLAG    (1 << I2C_SR1_BTF)
#define I2C_ADD10_FLAG  (1 << I2C_SR1_ADD10)
#define I2C_STOPF_FLAG  (1 << I2C_SR1_STOPF)
#define I2C_RxNE_FLAG   (1 << I2C_SR1_RxNE)
#define I2C_TxE_FLAG    (1 << I2C_SR1_TxE)

#define I2C_MSL_FLAG    (1 << I2C_SR2_MSL)
#define I2C_BUSY_FLAG   (1 << I2C_SR2_BUSY)
#define I2C_TRA_FLAG    (1 << I2C_SR2_TRA)
