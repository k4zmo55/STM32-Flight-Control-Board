#include <stdint.h>
#include "stm32f407xx.h"


/*  Configuration Structure of GPIO*/
typedef struct
{
	uint8_t GPIO_PinNumber;           /*!< Possible values from @GPIO_PIN_NUMBERS 			*/
	uint8_t GPIO_PinMode;             /*!< Possible values from @GPIO_PIN_MODES 			*/
	uint8_t GPIO_PinSpeed;            /*!< Possible values from @GPIO_PIN_SPEED 			*/
	uint8_t GPIO_PinPuPdControl;      /*!< Possible values from @GPIO_PIN_PUPD 			*/
	uint8_t GPIO_PinOPType;           /*!< Possible values from @GPIO_PIN_OUTPUT_TYPES 	*/
	uint8_t GPIO_PinAltFunMode;       /*!< Alternate function mode (if applicable) 		*/
}GPIO_PinConfig_t;


typedef struct{
    GPIOx_RegDef *pGPIOx;               /*!< This holds the base address of the GPIO port 	*/
    GPIO_PinConfig_t GPIO_PinConfig;    /*!< This holds GPIO pin configuration settings 	*/
}GPIO_Handle_t;

/*
    @GPIO_PIN_NUMBERS
    GPIO Pin Numbers
*/
#define GPIO_PIN_NO_0       0
#define GPIO_PIN_NO_1       1
#define GPIO_PIN_NO_2       2
#define GPIO_PIN_NO_3       3
#define GPIO_PIN_NO_4       4
#define GPIO_PIN_NO_5       5
#define GPIO_PIN_NO_6       6
#define GPIO_PIN_NO_7       7
#define GPIO_PIN_NO_8       8
#define GPIO_PIN_NO_9       9
#define GPIO_PIN_NO_10      10
#define GPIO_PIN_NO_11      11
#define GPIO_PIN_NO_12      12
#define GPIO_PIN_NO_13      13
#define GPIO_PIN_NO_14      14
#define GPIO_PIN_NO_15      15

/*
    @GPIO_PIN_MODES
    GPIO Pin possible modes
*/
#define GPIO_MODE_INPUT     0
#define GPIO_MODE_OUTPUT    1
#define GPIO_MODE_ALTFN     2
#define GPIO_MODE_ANALOG    3

/*
    @GPIO_PIN_OUTPUT_TYPES
    GPIO Pin possible output types
*/
#define GPIO_OP_TYPE_PP     0  //Push-Pull
#define GPIO_OP_TYPE_OD     1  //Open-Drain

/*
    @GPIO_PIN_SPEED
    GPIO Pin possible output speeds
*/
#define GPIO_SPEED_LOW           0
#define GPIO_SPEED_MEDIUM        1
#define GPIO_SPEED_HIGH          2
#define GPIO_SPEED_VERY_HIGH     3

/*
    @GPIO_PIN_PUPD
    GPIO Pin Pull-up Pull-down configuration macros
*/
#define GPIO_NO_PUPD      0
#define GPIO_PIN_PU       1
#define GPIO_PIN_PD       2


/*
 * APIs supported by this driver
 * For more information about the APIs, check the function definitions in stm32f407xx_gpio.c file
 */
/* Peripheral Clock setup */
void GPIO_PeriClockControl(GPIOx_RegDef *pGPIOx, uint8_t EnorDi);

/* GPIO Configuration Functions*/
uint8_t GPIO_SetPinMode(GPIOx_RegDef *pGPIOx, uint8_t PinNumber, uint8_t Mode);
uint8_t GPIO_SetPinSpeed(GPIOx_RegDef *pGPIOx, uint8_t PinNumber, uint8_t Speed);
uint8_t GPIO_SetPinPuPdControl(GPIOx_RegDef *pGPIOx, uint8_t PinNumber, uint8_t PuPd);
uint8_t GPIO_SetPinOPType(GPIOx_RegDef *pGPIOx, uint8_t PinNumber, uint8_t OPType);


/* Init and De-init */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIOx_RegDef *pGPIOx);


/* Data read and write */
uint8_t  GPIO_ReadFromInputPin(GPIOx_RegDef *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIOx_RegDef *pGPIOx);
void GPIO_WriteToOutputPin(GPIOx_RegDef *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIOx_RegDef *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIOx_RegDef *pGPIOx, uint8_t PinNumber);


/* IRQ Configuration and ISR handling */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);
