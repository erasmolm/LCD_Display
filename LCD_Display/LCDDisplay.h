/**
  ******************************************************************************
  * @file    gpgpio.c
  * @author  Pierluigi,Alfonso,Erasmo
  * @version V1.0
  * @date    11-Jun-2017
  * @brief   Questo file definisce le principali funzioni di controllo per il
  * 		 display LCM1602C
  ******************************************************************************
  */

#ifndef LCDDISPLAY_H_
#define LCDDISPLAY_H_

/* Includes ------------------------------------------------------------------*/
#include <inttypes.h>
#include "LCD_STM_Pin_Configurator.h"

/*
* @brief Mapping delle funzioni di basso livello.
* 		 Da modificare per un altro device (ad es. ZYBO).
* */
#define LCD_PIN_Init(conf)			__LCD_STM_PIN_Init(conf)
#define LCD_PIN_Write(prt,val)		__LCD_STM_PIN_Write(prt,val)

typedef enum { false, true } bool;					/*!< tipo booleano*/
typedef enum { COMM_REG_SEL, DATA_REG_SEL} RS_flag;	/*!< selezione registro istruzione-dato*/
typedef enum { EN_LOW, EN_HIGH} EN_flag;			/*!< valore basso-alto pin di ENABLE*/
typedef enum { SH_RIGHT, SH_LEFT} shift_dir;		/*!< direzione di shift destra-sinistra*/

/*
 * @brief Mapping delle funzioni di basso livello.
 * */
#define LCD_PIN_Init(conf)			__LCD_STM_PIN_Init(conf)	/*!< funzione di inizializzazione generica*/
#define LCD_PIN_Write(prt,val)		__LCD_STM_PIN_Write(prt,val)/*!< funzione di scrittura su pin generica*/

/*
 * @brief Function Set
 * */
#define LCD_FS_1L		0x20	/*!< Modalità 1 riga*/
#define LCD_FS_2L		0x28	/*!< Modalità 2 righe*/

/*
 * @brief Cursor Set
 * */
#define LCD_CURSOR_OFF		0x0C	/*!< Cursore non visibile*/
#define LCD_ENCUR_NOBLNK	0x0E	/*!< Cursore visibile non intermittente*/
#define LCD_ENCUR_BLNK		0x0F	/*!< Cursore visibile intermittente*/

/*
 * @brief Entry Mode Set
 * */
#define LCD_EM_DEC_MVCUR	0x04	/*!< Display fermo, cursore mobile a decremento*/
#define LCD_EM_DEC_MVDIS	0x05	/*!< Cursore fermo, display mobile a decremento*/
#define LCD_EM_INC_MVCUR	0x06	/*!< Display fermo, cursore mobile a incremento*/
#define LCD_EM_INC_MVDIS	0x07	/*!< Cursore fermo, display mobile a incremento*/

/*
 * @brief Maschere di accesso a dati
 * */
#define LCD_DATA_HIGH_MASK	0xF0	/*!< Parte alta*/
#define LCD_DATA_LOW_MASK	0x0F	/*!< Parte bassa*/

/*
 * @brief Posizione pin dati
 * */
#define D7_POS			3
#define D6_POS			2
#define D5_POS			1
#define D4_POS			0

/*
 * @brief Maschere di accesso ai pin dati
 * */
#define D7_MASK			(uint8_t)0x1	<< D7_POS
#define D6_MASK			(uint8_t)0x1	<< D6_POS
#define D5_MASK			(uint8_t)0x1	<< D5_POS
#define D4_MASK			(uint8_t)0x1	<< D4_POS

/*
 * @brief Struttura dati display
 * */
typedef struct display_t display_t;

struct display_t{
	void(*printChar)(uint8_t data);
	void(*printString)(char* string);
	void(*clear)(void);
	void(*setCursorPosition)(uint8_t addr);
	void(*displayShift)(shift_dir dir);

	uint8_t functionSet;
	uint8_t displayOnOff;
	uint8_t entryMode;
};

/**
  * @brief firma della funzione di inizializzazione
 */
void DisplayTypedef_Init(display_t*);


#endif /* LCDDISPLAY_H_ */
