/**
  ******************************************************************************
  * @file    gpgpio.c
  * @author  Pierluigi,Alfonso,Erasmo (APE)
  * @version V1.0
  * @date    11-Jun-2017
  * @brief   Questo file implementa le funzioni di basso livello
  * 		 per collegare i pin del display LCM1602C ai porti di un generico
  * 		 micro-controllore STM32.
  ******************************************************************************
  */

#include "LCD_STM_Pin_Configurator.h"

/**
  * @brief  Data una configurazione, inizializza tutti i porti necessari,
  * 		e ne abilita il clock.
  * @param 	conf: struttura dati con la configurazione dei pin,
  */
void __LCD_STM_PIN_Init(PinConfig_TypeDef* conf){
	HAL_Init();

	if (conf->D4_Pin.letter == GPIOA ||
		conf->D5_Pin.letter == GPIOA ||
		conf->D6_Pin.letter == GPIOA ||
		conf->D7_Pin.letter == GPIOA ||
		conf->RS_Pin.letter == GPIOA ||
		conf->EN_Pin.letter == GPIOA){
		__HAL_RCC_GPIOA_CLK_ENABLE();
	}

	if (conf->D4_Pin.letter == GPIOB ||
		conf->D5_Pin.letter == GPIOB ||
		conf->D6_Pin.letter == GPIOB ||
		conf->D7_Pin.letter == GPIOB ||
		conf->RS_Pin.letter == GPIOB ||
		conf->EN_Pin.letter == GPIOB){
		__HAL_RCC_GPIOB_CLK_ENABLE();
	}

	if (conf->D4_Pin.letter == GPIOC ||
		conf->D5_Pin.letter == GPIOC ||
		conf->D6_Pin.letter == GPIOC ||
		conf->D7_Pin.letter == GPIOC ||
		conf->RS_Pin.letter == GPIOC ||
		conf->EN_Pin.letter == GPIOC){
		__HAL_RCC_GPIOC_CLK_ENABLE();
	}

	if (conf->D4_Pin.letter == GPIOD ||
		conf->D5_Pin.letter == GPIOD ||
		conf->D6_Pin.letter == GPIOD ||
		conf->D7_Pin.letter == GPIOD ||
		conf->RS_Pin.letter == GPIOD ||
		conf->EN_Pin.letter == GPIOD){
		__HAL_RCC_GPIOD_CLK_ENABLE();
	}

	if (conf->D4_Pin.letter == GPIOE ||
		conf->D5_Pin.letter == GPIOE ||
		conf->D6_Pin.letter == GPIOE ||
		conf->D7_Pin.letter == GPIOE ||
		conf->RS_Pin.letter == GPIOE ||
		conf->EN_Pin.letter == GPIOE){
		__HAL_RCC_GPIOE_CLK_ENABLE();
	}

	GPIO_InitTypeDef gpio;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;

	//D4 init
	gpio.Pin = conf->D4_Pin.pin_number;
	HAL_GPIO_Init(conf->D4_Pin.letter,&gpio);

	//D5 init
	gpio.Pin = conf->D5_Pin.pin_number;
	HAL_GPIO_Init(conf->D5_Pin.letter,&gpio);

	//D6 init
	gpio.Pin = conf->D6_Pin.pin_number;
	HAL_GPIO_Init(conf->D6_Pin.letter,&gpio);

	//D7 init
	gpio.Pin = conf->D7_Pin.pin_number;
	HAL_GPIO_Init(conf->D7_Pin.letter,&gpio);

	//RS init
	gpio.Pin = conf->RS_Pin.pin_number;
	HAL_GPIO_Init(conf->RS_Pin.letter,&gpio);

	//EN init
	gpio.Pin = conf->EN_Pin.pin_number;
	HAL_GPIO_Init(conf->EN_Pin.letter,&gpio);
}

/**
  * @brief  scrive un valore sul porto GPIO indicato.
  * @param 	port: porto GPIO
  * @param 	value: valore da scrivere sul porto GPIO.
  */
void __LCD_STM_PIN_Write(GPIOPort_TypeDef port,GPIO_PinState value){
	HAL_GPIO_WritePin(port.letter,port.pin_number, value);
}
