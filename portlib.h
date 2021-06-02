/***************************************************************************//**
  @file     +portlib.h+
  @brief    +Funciones para modificar el estado de los puertos de entrada y salida de 8 y 16 bits+
  @author   +Grupo 1+
 ******************************************************************************/

#ifndef _PORTLIB_H_
#define _PORTLIB_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>
#include <stdio.h>

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief BitSet: cambia el estado de un bit de un puerto a 1
 * @param port El puerto a modificar
 * @param bit_nr El bit a modificar
*/
void bitSet (char port, uint16_t bit_nr);
/**
 * @brief BitClr: cambia el estado de un bit de un puerto a 1
 * @param port El puerto a modificar
 * @param bit_nr El bit a modificar
*/
void bitClr (char port, uint16_t bit_nr);
/**
 * @brief BitGet: devuelve el estado de un bit de un puerto
 * @param port El puerto a evaluar
 * @param bit_nr El bit a evaluar
*/
int bitGet (char port, uint16_t bit_nr);
/**
 * @brief BitToggle: cambia el estado del bit dado al estado opuesto
 * @param port El puerto a modificar
 * @param bit_nr El bit a modificar
*/
void bitToggle (char port, uint16_t bit_nr);
/**
 * @brief MaskOn: enciende todos los bits que estan encendidos en la mascara sin modificar los otros
 * @param port El puerto a modificar
 * @param bit_mask La mascara a aplicar
*/
void maskOn (char port, uint16_t bit_mask);
/**
 * @brief MaskOff: apaga todos los bits que estan encendidos en la mascara sin modificar los otros
 * @param port El puerto a modificar
 * @param bit_mask La mascara a aplicar
*/
void maskOff (char port, uint16_t bit_mask);
/**
 * @brief MaskToggle: cambia al estado opuesto todos los bits que estan encendidos en la mascara sin modificar los otros
 * @param port El puerto a modificar
 * @param bit_mask La mascara a aplicar
*/
void maskToggle (char port, uint16_t bit_mask);
/**
 * @brief Print_bitabit: imprime los bits de un puerto en forma de string
 * @param myPort El puerto a imprimir
*/
void print_bitabit (uint8_t myPort);

/*******************************************************************************
 ******************************************************************************/

#endif // _PORTLIB_H_
