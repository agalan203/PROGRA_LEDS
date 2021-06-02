#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main (void){

    FILE *handle_export;

    handle_export = fopen("/sys/class/gpio/export","w+");
 
    fputs("17",handle_export);
   
    fclose(handle_export);

    FILE * handle_direction;
    
    handle_direction = fopen("/sys/class/gpio/gpio17/direction","w+");

    fputs("out",handle_direction);
  
    fclose(handle_direction);

    FILE * handle;

    handle = fopen("/sys/class/gpio/gpio17/value","w+");
    
    fputc('1',handle);
   
    fclose(handle);

    /*FILE *handle_unexport;

    handle_unexport = fopen("/sys/class/gpio/unexport","w+");
    
    fputs("17",handle_unexport);

    fflush(handle_unexport);
    
    fclose(handle_unexport);
    */

    return 0;
}

