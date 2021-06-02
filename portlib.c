/***************************************************************************//**
  @file     +portlib.c+
  @brief    +Funciones para modificar el estado de los puertos de entrada y salida de 8 y 16 bits+
  @author   +Grupo 1+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "portlib.h"

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

// Para crear un puerto de 16 bits formado a partir de dos puertos de 8 bits 
typedef struct PORT16{
    uint8_t portA_;
    uint8_t portB_;
} port16_t;

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static port16_t portD; //definicion del puerto D (conformado por los puertos A y B)

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/**********************************************************/

void bitSet (char port, uint16_t bit_nr){                       //enciende el bit indicado del puerto indicado

    switch(port){
        case 'D':                                               //el puerto a modificar es el D
            if (bit_nr>7){                                      //si se quiere modificar un bit del MSB (portA)
                bit_nr-=8; 
                portD.portA_=(portD.portA_|(0x01<<bit_nr));     //se enciende el bit indicado
            }
            else {                                              //si el bit a modificar pertenece al LSB (portB)
                portD.portB_=(portD.portB_|(0x01<<bit_nr));
            }
            print_bitabit(portD.portA_);                        //imprime el estado del puerto D en pantalla
            printf(" ");
            print_bitabit(portD.portB_);
            break;
        case 'A':                                               //analogo al D pero para el puerto A
            portD.portA_=(portD.portA_|(0x01<<bit_nr));
            print_bitabit(portD.portA_);
            break;
        case 'B':                                               //analogo al D pero para el puerto B
            portD.portB_=(portD.portB_|(0x01<<bit_nr));
            print_bitabit(portD.portB_);
            break;
        default:                                                //si el puerto pedido es invalido
            printf("Puerto inexistente");
            break;
    }
    printf("\n");                                               //imprime un \n despues del puerto
}

/**********************************************************/

void bitClr (char port, uint16_t bit_nr){       //funciona analogamente a bitSet pero apaga el bit indicado
   
    switch(port){
        case 'D':
            if (bit_nr>7){
            bit_nr-=8; 
            portD.portA_=(portD.portA_&(~(0x01<<bit_nr)));
            }
            else {
                portD.portB_=(portD.portB_&(~(0x01<<bit_nr)));
            }
            print_bitabit(portD.portA_);
            printf(" ");
            print_bitabit(portD.portB_);
            break;
        case 'A':
            portD.portA_=(portD.portA_&(~(0x01<<bit_nr)));
            print_bitabit(portD.portA_);
            break;
        case 'B':
            portD.portB_=(portD.portB_&(~(0x01<<bit_nr)));
            print_bitabit(portD.portB_);
            break;
        default:
            printf("Puerto inexistente");
            break;
    }
    printf("\n");
}

/**********************************************************/
int bitGet (char port, uint16_t bit_nr){

    int thebit=0;
    uint8_t auxport;  

    switch(port){
        case 'D':                                               //el puerto a modificar es el D
            if (bit_nr>7){                                      //si se quiere modificar un bit del MSB (portA)
            bit_nr-=8;
            auxport=(portD.portA_&(0x01<<bit_nr));              //se obtiene el estado del bit indicado
            thebit=(auxport>>bit_nr);
            }
            else {                                              //si el bit a modificar pertenece al LSB (portB)
                auxport=(portD.portB_&(0x01<<bit_nr));
                thebit=(auxport>>bit_nr);
            }
            break;
        case 'A':                                               //analogo al D pero para el puerto A
            auxport=(portD.portA_&(0x01<<bit_nr));
            thebit=(auxport>>bit_nr);
            break;
        case 'B':                                               //analogo al D pero para el puerto B
            auxport=(portD.portB_&(0x01<<bit_nr));
            thebit=(auxport>>bit_nr);
            break;
        default:                                                //si el puerto pedido es invalido
            printf("Puerto inexistente");
            break;
    }
    printf("%d\n",thebit);                                      //imprime el estado del bit y lo devuelve
    return thebit;
}

/**********************************************************/

void bitToggle (char port, uint16_t bit_nr){       //funciona analogamente a bitSet pero cambia al estado contrario el bit indicado

    switch(port){
        case 'D':
            if (bit_nr>7){
            bit_nr-=8;
            portD.portA_=(portD.portA_^(0x01<<bit_nr));
            }
            else {
                portD.portB_=(portD.portB_^(0x01<<bit_nr));
            }
            print_bitabit(portD.portA_);
            printf(" ");
            print_bitabit(portD.portB_);
            break;
        case 'A':
            portD.portA_=(portD.portA_^(0x01<<bit_nr));
            print_bitabit(portD.portA_);
            break;
        case 'B':
            portD.portB_=(portD.portB_^(0x01<<bit_nr));
            print_bitabit(portD.portB_);
            break;
        default:
            printf("Puerto inexistente");
            break;
    }
    printf("\n");
}

/**********************************************************/

void maskOn (char port, uint16_t bit_mask){         //enciende todos los bits del puerto que estan encendidos en la mascara

    uint8_t high_mask= (uint8_t) (bit_mask>>8);     //crea la mascara para el MSB (portA)
    uint8_t low_mask= (uint8_t) bit_mask;           //crea la mascara para el LSB (portB)
    
    switch(port){
        case 'D':                                   //si se quiere modificar el puerto D
            portD.portA_=(portD.portA_|high_mask);  //enciende los bits que corresponden del MSB
            print_bitabit(portD.portA_);            //imprime el MSB
            printf(" ");
            portD.portB_=(portD.portB_|low_mask);   //enciende los bits que corresponden del LSB 
            print_bitabit(portD.portB_);            //imprime el LSB
            break;
        case 'A':                                   //analogo al puerto D, pero para el puerto A
            portD.portA_=(portD.portA_|bit_mask);
            print_bitabit(portD.portA_);
            break;
        case 'B':                                   //analogo al puerto D, pero para el puerto B
            portD.portB_=(portD.portB_|bit_mask);
            print_bitabit(portD.portB_);
            break;
        default:                                    //si el puerto pedido es invalido
            printf("Puerto inexistente");
            break;
    }
    printf("\n");                                   //imprime un enter despues del puerto

}

/**********************************************************/

void maskOff (char port, uint16_t bit_mask){       //funciona analogamente a maskOn pero apaga todos los bits encendidos en la mascara
    
    uint8_t high_mask= (uint8_t) (bit_mask>>8);
    uint8_t low_mask= (uint8_t) bit_mask;

    switch(port){
        case 'D':
            portD.portA_=(portD.portA_&(~high_mask));
            print_bitabit(portD.portA_);
            printf(" ");
            portD.portB_=(portD.portB_&(~low_mask));
            print_bitabit(portD.portB_);
            break;
        case 'A':
            portD.portA_=(portD.portA_&(~bit_mask));
            print_bitabit(portD.portA_);
            break;
        case 'B':
            portD.portB_=(portD.portB_&(~bit_mask));
            print_bitabit(portD.portB_);
            break;
        default:
            printf("Puerto inexistente");
            break;
    }

    printf("\n");

}

/**********************************************************/

void maskToggle (char port, uint16_t bit_mask){       //funciona analogamente a maskOn pero invierte el estado de todos los bits encendidos en la mascara

    uint8_t high_mask= (uint8_t) (bit_mask>>8);
    uint8_t low_mask= (uint8_t) bit_mask;

    switch(port){
        case 'D':
            portD.portA_=(portD.portA_^high_mask);
            print_bitabit(portD.portA_);
            printf(" ");
            portD.portB_=(portD.portB_^low_mask);
            print_bitabit(portD.portB_);
            break;
        case 'A':
            portD.portA_=(portD.portA_^bit_mask);
            print_bitabit(portD.portA_);
            break;
        case 'B':
            portD.portB_=(portD.portB_^bit_mask);
            print_bitabit(portD.portB_);
            break;
        default:
            printf("Puerto inexistente");
            break;
    }
    printf("\n");
}

/**********************************************************/

void print_bitabit (uint8_t myPort){        //imprime el estado en binario de un puerto, de forma recursiva
    
    static int cont=0;

    if (myPort<=1&&cont==7){                //para imprimir el bit 0
        printf("%d",myPort);
        cont=0;
    }
    else{                                   //para imprimir los bits 1-7 en el orden correcto
        cont++;
        print_bitabit(myPort/2);
        printf("%d",myPort%2);
    }
}

/**********************************************************/