#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main (void){

    /******************************************************/
    FILE *handle_export;

    if((handle_export = fopen("/sys/class/gpio/export","w+"))==NULL){
        printf("Cannot open EXPORT File. Try again later.\n");
        return 1;
    }

    if((fputs("17",handle_export))==-1){
        printf ("Cannot EXPORT PIN. Try again later.\n");
        return 1;
    }
    else{
       printf("UNEXPORT File opened succesfully \n"); 
    }

    fclose(handle_export);
    /******************************************************/
    FILE * handle_direction;
    
    if((handle_direction = fopen("/sys/class/gpio/gpio17/direction","w+"))==NULL){
        printf("Cannot open DIRECTION File. Try again later.\n");
        return 1;
    }

    if((fputs("out",handle_direction))==-1){
        printf ("Cannot upen DIRECTION pin. Try again later.\n");
        return 1;
    }
    else{
        printf("DIRECTION File for PIN opened succesfully\n");
    }
  
    fclose(handle_direction);
    /******************************************************/
    FILE * handle;

    if((handle = fopen("/sys/class/gpio/gpio17/value","w+"))==NULL){
        printf("Cannot open device. Try again later.\n");
        return 1;
    }
    
    if((fputc('1',handle))==-1){
        printf("Clr_Pin: Cannot write to file. Try again later.\n");
        return -1;
    }
    else{
        printf("Write to file VALUE successfully done.\n");
    }

    fclose(handle);
    /******************************************************/

    /*FILE *handle_unexport;

    handle_unexport = fopen("/sys/class/gpio/unexport","w+");
    
    fputs("17",handle_unexport);

    fflush(handle_unexport);
    
    fclose(handle_unexport);
    */

    return 0;
}

