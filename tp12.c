#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "portlib.h"

typedef struct {
    char* number; //numero pin
    char value; //0 o 1
    char* path; //direccion del puerto
}led_t;

int export_pin(led_t* led);
int unexport_pin(led_t* led);
int output_pin(led_t* led);
int set_state_pin(led_t* led);
static int get_input(void);
static int limpiarBuff(void);

int main(void){
    int i;
    int input = 0;
    int finish = 0;
    led_t led0 = {"17", '0', "/sys/class/gpio/gpio17/"};
    led_t led1 = {"4", '0', "/sys/class/gpio/gpio4/"};
    led_t led2 = {"18", '0', "/sys/class/gpio/gpio18/"};
    led_t led3 = {"23", '0', "/sys/class/gpio/gpio23/"};
    led_t led4 = {"24", '0', "/sys/class/gpio/gpio24/"};
    led_t led5 = {"25", '0', "/sys/class/gpio/gpio25/"};
    led_t led6 = {"22", '0', "/sys/class/gpio/gpio22/"};
    led_t led7 = {"27", '0', "/sys/class/gpio/gpio27/"};

    led_t* arrled[8] = {&led0, &led1, &led2, &led3, &led4, &led5, &led6, &led7};

    for(i = 0; i <= 7; i++){
        if(export_pin(arrled[i]) == 1){
            return -1;
        }
    }

    for(i = 0; i <= 7; i++){
        if(output_pin(arrled[i]) == 1){
            return -1;
        }
    }

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
            finish = 1;
            break;

            default:                //si se introdujo un numero del 0 al 7 se enciende el led correspondiente
            bitSet('A',input);      //funcion que enciende un led
            break;
        }

        for(i = 0; i <= 7; i++){
            arrled[i] -> value = (bitGet('A',i))+'0';
        }

        for(i = 0; i <= 7; i++){
            if(set_state_pin(arrled[i]) == 1){
                return -1;
            }
        }

    }while (finish != 1); 

    for(i = 0; i <= 7; i++){
        if(unexport_pin(arrled[i]) == 1){
            return -1;
        }
    }

    return 0;
}

int export_pin(led_t* led){

    /******************************************************/
    FILE *handle_export;

    if((handle_export = fopen("/sys/class/gpio/export","w+"))==NULL){
        printf("Cannot open EXPORT File. Try again later.\n");
        return 1;
    }

    if((fputs(led->number,handle_export))==-1){
        printf ("Cannot EXPORT PIN. Try again later.\n");
        return 1;
    }
    else{
       printf("EXPORT File opened succesfully \n"); 
    }

    fclose(handle_export);
    /******************************************************/

    return 0;
}

int unexport_pin(led_t* led){

    /******************************************************/
    FILE *handle_export;

    if((handle_export = fopen("/sys/class/gpio/unexport","w+"))==NULL){
        printf("Cannot open UNEXPORT File. Try again later.\n");
        return 1;
    }

    if((fputs(led->number,handle_export))==-1){
        printf ("Cannot UNEXPORT PIN. Try again later.\n");
        return 1;
    }
    else{
       printf("UNEXPORT File opened succesfully \n"); 
    }

    fclose(handle_export);
    /******************************************************/
    
    return 0;
}

int output_pin(led_t* led){

    /******************************************************/
    FILE * handle_direction;
    char cad[33] = {0};

    strcpy(cad, led->path);
    strcat(cad, "direction");
    
    if((handle_direction = fopen(cad,"w+"))==NULL){
        printf("Cannot open DIRECTION File. Try again later.\n");
        return 1;
    }

    if((fputs("out",handle_direction))==-1){
        printf ("Cannot open DIRECTION pin. Try again later.\n");
        return 1;
    }
    else{
        printf("DIRECTION File for PIN opened succesfully\n");
    }
  
    fclose(handle_direction);
    /******************************************************/

    return 0;
}

int set_state_pin(led_t* led){
    
    /******************************************************/
    FILE * handle;
    char cad[29] = {0};

    strcpy(cad, led->path);
    strcat(cad, "value");

    if((handle = fopen(cad,"w+"))==NULL){
        printf("Cannot open device. Try again later.\n");
        return 1;
    }
    
    if((fputc(led->value,handle))==-1){
        printf("Clr_Pin: Cannot write to file. Try again later.\n");
        return 1;
    }
    else{
        printf("Write to file VALUE successfully done.\n");
    }

    fclose(handle);
    /******************************************************/

    return 0;
}

static int get_input(void){
    int input = 0;
    int valid = 0;
    int error = 1;

    do{
        printf("Ingrese entrada:\n");       //pide el ingreso de una entrada
        input = getchar();
        valid = limpiarBuff();               //se fija la validez de lo ingresado
        if (valid == 0){                      //si la entrada fue seguida de un \n y nada mas
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

static int limpiarBuff(void){
    int cont=0;
    while(getchar()!='\n'){
        cont++;          //limpia el stdin 
    }
    cont=(cont==0)?0:1;  //si se introdujeron mas caracteres que \n marca error

    return cont;
}