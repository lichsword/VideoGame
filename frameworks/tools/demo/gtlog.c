// gtlog.c
// Game Tool log.c
// Lichsword Video Game Enginee
//
// Report bugs to lichswordkernel@gmail.com
#include "gtlog.h"

void gtlog(void){
    FILE * fp = fopen("filename.log", "w+"); 
    if( fp == NULL){
        printf("Can't open%s\n", "filename.log");
    }// end if

    fputs("show me the monty", fp); 
    fwrite("Hello log",1, 9, fp);
    fclose(fp);
}
