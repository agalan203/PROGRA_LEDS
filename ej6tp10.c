/***************************************************************************//**
  @file     +ej6tp10.c+
  @brief    +Funcion que simula 8 leds conectados al puerto A+
  @author   +Grupo 1+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "portlib.h"

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief LIMPIAR_BUFFER: limpia el stdin
 * @return devuelve 1 si hubo entrada invalida, devuelve 0 si la entrada fue valida (caracter\n)
*/
static int limpiarBuff(void);
/**
 * @brief GET_INPUT: lee lo introducido por teclado y lo interpreta
 * @return  si se introdujo un numero de bit, devuelve ese numero. 
 *          si se introdujo t devuelve -1
 *          si se introdujo c devuelve -2
 *          si se introdujo s devuelve -3
 *          si se introdujo q devuelve -4
*/
static int get_input (void);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
/*
Por teclado, el usuario ingresará el número (del 0 al 7) del LED que se desea prender, en tiempo real.
Con la letra 't', todos los LEDs deben cambiar al estado opuesto, 
(si están encendidos apagarse y si están apagados encenderse).
Con la letra 'c', se deberán apagar todos, y con 's', prender.
Con la letra 'q', el programa finalizará.
Los leds se emulan con 1 y 0. 0 significa que el led esta apagado. 1 significa que esta encendido.
El led de mas a la izquierda corresponde al led 7 y el 0 al de mas a la derecha
*/
int main (void){

    //variables auxiliares locales     
    int input=0;
    int finish=0;

    do{
        input=get_input();          //trae la instruccion introducida por teclado por el usuario

        switch (input){
            case -1:                //si se introdujo una t(-1), se invierten los estados de todos los led conectados al puerto
            maskToggle('A',0xFF);   //funcion que invierte todos los leds 
            break;

            case -2:                //si se introdujo una c(-2), se apagan todos los leds
            maskOff('A',0xFF);      //funcion que apaga todos los leds
            break;

            case -3:                //si se introdujo una s(-3), se encienden todos los leds
            maskOn('A',0xFF);       //funcion que enciende todos los leds
            break;

            case -4:                //si se introdujo una q(-4) se finaliza la ejecucion del programa
            finish=1;
            break;

            default:                //si se introdujo un numero del 0 al 7 se enciende el led correspondiente
            bitSet('A',input);      //funcion que enciende un led
            break;
        }
    }while (finish!=1);   

    return 0;
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/**********************************************************/
/**
 * @brief GET_INPUT: lee lo introducido por teclado y lo interpreta
 * @return  si se introdujo un numero de bit, devuelve ese numero. 
 *          si se introdujo t devuelve -1
 *          si se introdujo c devuelve -2
 *          si se introdujo s devuelve -3
 *          si se introdujo q devuelve -4
*/
static int get_input(void){

    //variables auxiliares locales
    int input=0;
    int valid=0;
    int error=1;

    do{
        printf("Ingrese entrada:\n");       //pide el ingreso de una entrada
        input= getchar();
        valid= limpiarBuff();               //se fija la validez de lo ingresado
        if (valid==0){                      //si la entrada fue seguida de un \n y nada mas
            if (input>='0'&&input<='7'){    //se fija si es una de las entradas validas
                error=0;
            }
            else if ((input=='t')||(input=='c')||(input=='s')||(input=='q')){
                error=0;
            }
        }
        else{                               //si no es una de las entradas validas marca error
            error=1;
        }
        if (error==1){                      //si la entrada no fue valida, pide reingresar
            printf("Entrada invalida, reingresar\n");
        }

    }while (error==1);
    
    if (input<'0'||input>'7'){              //si la entrada fue una de las letras validas
        switch (input){
            case 't':   //le asigna a la t el -1
            input=-1;
            break;

            case 'c':   //le asigna a la c el -2
            input=-2;
            break;

            case 's':   //le asigna a la s el -3
            input=-3;
            break;

            case 'q':   //le asigna a la q el -4
            input=-4;
            break;
        }
    }
    else {              //si la entrada fue un numero valido, lo convierte de ascii a decimal
        input-='0';
    }
    return input;
}
/**********************************************************/

/**********************************************************/
/**
 * @brief LIMPIAR_BUFFER: limpia el stdin
 * @return devuelve 1 si hubo entrada invalida, devuelve 0 si la entrada fue valida (caracter\n)
*/
static int limpiarBuff(void){
    int cont=0;
    while(getchar()!='\n'){
        cont++;          //limpia el stdin 
    }
    cont=(cont==0)?0:1;  //si se introdujeron mas caracteres que \n marca error

    return cont;
}
/**********************************************************/