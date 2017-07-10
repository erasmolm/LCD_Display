/**
  ******************************************************************************
  * @file    gpgpio.c
  * @author  Pierluigi,Alfonso,Erasmo (APE)
  * @version V1.0
  * @date    11-Jun-2017
  * @brief   Questo file implementa le principali funzioni di controllo per il
  * 		 display LCM1602C
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "LCDDisplay.h"

/**
  * @brief  Scrive un valore sul pin RS del display
  * @param 	RS_pin_state: indirizzo base del registro
  *   Questo parametro può assumere i seguenti valori:
  *     @arg COMM_REG_SEL (0)
  *     @arg DATA_REG_SEL (1)
  */
void LCD_RS_write(RS_flag RS_pin_state){
	LCD_PIN_Write(RS_PIN,RS_pin_state);
}

/**
  * @brief  Genera un impulso ALTO-BASSO sul pin EN
  */
void LCD_pulse_EN(){
	LCD_PIN_Write(EN_PIN,EN_HIGH);
	HAL_Delay(10);
	LCD_PIN_Write(EN_PIN,EN_LOW);
	HAL_Delay(10);
}

/**
  * @brief  Scrive un valore di 4 bit sui pin D7-D4 del display.
  * @param 	value: valore da scrivere, solo i 4 bit meno significativi
  * 			   vengono considerati.
  */
void LCD_write_nibble(uint8_t value){
	bool pin_value;

	//Write D7
	pin_value =(value & D7_MASK) >> D7_POS;
	LCD_PIN_Write(D7_PIN,pin_value);

	//Write D6
	pin_value = (value & D6_MASK) >> D6_POS;
	LCD_PIN_Write(D6_PIN,pin_value);

	//Write D5
	pin_value = (value & D5_MASK) >> D5_POS;
	LCD_PIN_Write(D5_PIN,pin_value);

	//Write D4
	pin_value = (value & D4_MASK) >> D4_POS;
	LCD_PIN_Write(D4_PIN,pin_value);
}

/**
  * @brief  Scrive un valore di 1 byte sui pin D7-D4 del display.
  * 		La scrittura avviene in 2 passi: parte alta - parte bassa
  * @param 	value: valore da scrivere
  */
void LCD_write_data(uint8_t value){
	uint8_t mask;

	mask = value & LCD_DATA_HIGH_MASK;
	mask = mask >> 4;
	LCD_write_nibble(mask);

	LCD_pulse_EN();

	mask = value & LCD_DATA_LOW_MASK;
	LCD_write_nibble(mask);

	LCD_pulse_EN();
}

/**
  * @brief  Stampa sul display un carattere ASCII e incrementa il cursore di una posizione.
  * @param 	c: carattere da stampare
  */
void LCD_printChar(uint8_t c){
	LCD_RS_write(DATA_REG_SEL);
	LCD_write_data(c);
}

/**
  * @brief  Stampa sul display una stringa di caratteri ASCII.
  * @param 	s: stringa da stampare
  */
void LCD_printString(char* s){
	int i=0;
	uint8_t c;

	do{
		c = (uint8_t)s[i++];
		if(c != '\0'){
			LCD_printChar(c);
		}
	}while(c != '\0' && i<80);
}

/**
  * @brief  Posiziona il cursore su una casella specificata.
  * @param 	address: indirizzo della casella su cui posizionarsi
  */
void LCD_setCursorPosition(uint8_t address){
	LCD_RS_write(COMM_REG_SEL);
	LCD_write_data(0x80|address);
}

/**
  * @brief  Pulisce lo schermo e svuota la memoria del display.
  */
void LCD_clear(){
	LCD_RS_write(COMM_REG_SEL);
	LCD_write_data(0b00000001);
}

/**
  * @brief  Sposta il display di una posizione sulla memoria
  * @param 	dir: direzione dello spostamento
  *   Questo parametro può assumere i seguenti valori:
  *     @arg  SH_RIGHT (0) spostamento a destra
  *     @arg  SH_LEFT  (1) spostamento a sinistra
  */
void LCD_displayShift(shift_dir dir){
	uint8_t mask = 0x18 | (dir << 2);

	LCD_RS_write(COMM_REG_SEL);
	LCD_write_data(mask);
}

/**
  * @brief  Inizializzazione della struttura dati, configurazione dei pin
  * 		sui porti GPIO, ciclo di inizializzazione del dispositivo display.
  * @param 	self: puntatore alla struttura
  */
void DisplayTypedef_Init(display_t* self){

	self->printChar = &LCD_printChar;
	self->printString = &LCD_printString;
	self->clear = &LCD_clear;
	self->setCursorPosition = &LCD_setCursorPosition;
	self->displayShift = &LCD_displayShift;

	//Pin Configuration
	PinConfig_TypeDef conf;
	conf.D4_Pin = D4_PIN;
	conf.D5_Pin = D5_PIN;
	conf.D6_Pin = D6_PIN;
	conf.D7_Pin = D7_PIN;
	conf.RS_Pin = RS_PIN;
	conf.EN_Pin = EN_PIN;

	LCD_PIN_Init(&conf);

	//Init Steps
	LCD_RS_write(COMM_REG_SEL);
	for(int i=0;i<3;i++){
		LCD_write_nibble(0b0011);
		LCD_pulse_EN();
	}
	LCD_write_nibble(0b0010);
	LCD_pulse_EN();

	//Function Set
	LCD_write_data(self->functionSet);

	//Display On/Off set
	LCD_write_data(self->displayOnOff);

	//Entry Mode Set
	LCD_write_data(self->entryMode);

	//Cursor Position
	self->clear();

}
