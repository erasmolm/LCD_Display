/**
  ******************************************************************************
  * @file    gpgpio.c
  * @author  Pierluigi,Alfonso,Erasmo
  * @version V1.0
  * @date    11-Jun-2017
  * @brief   Questo file definisce le funzioni di basso livello
  * 		 per collegare i pin del display LCM1602C ai porti di un generico
  * 		 micro-controllore STM32.
  ******************************************************************************
  */

#ifndef LCD_STM_PIN_CONFIGURATOR_H_
#define LCD_STM_PIN_CONFIGURATOR_H_

/* Includes ------------------------------------------------------------------*/
#include <stm32f4xx_hal.h>

typedef struct GPIOPort_TypeDef GPIOPort_TypeDef;
typedef struct PinConfig_TypeDef PinConfig_TypeDef;

/**
  * @brief tipo di dato astratto GPIOPort_TypeDef per il singolo porto GPIO.
  **/
typedef struct GPIOPort_TypeDef{
	GPIO_TypeDef* letter;
	uint16_t pin_number;
}GPIOPort_TypeDef;

/**
  * @brief tipo di dato astratto PinConfig_TypeDef per gestire la configurazione
  * 	   dei pin del display.
  **/
struct PinConfig_TypeDef{
	GPIOPort_TypeDef RS_Pin;
	GPIOPort_TypeDef EN_Pin;
	GPIOPort_TypeDef D4_Pin;
	GPIOPort_TypeDef D5_Pin;
	GPIOPort_TypeDef D6_Pin;
	GPIOPort_TypeDef D7_Pin;
};

/**
  * @brief firma delle funzioni
 */
void __LCD_STM_PIN_Init(PinConfig_TypeDef*);
void __LCD_STM_PIN_Write(GPIOPort_TypeDef,GPIO_PinState);

#endif /* LCD_STM_PIN_CONFIGURATOR_H_ */
