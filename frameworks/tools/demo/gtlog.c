// gtlog.c
// Game Tool log.c
// Lichsword Video Game Enginee
//
// Report bugs to lichswordkernel@gmail.com
#include "gtcommon.h"
#include "gtlog.h"

FILE * fp = NULL;// define
char DEFAULT_FILE_NAME[] = "log.data";

boolean gtensureFile(){
   return gtensureFileWithName(DEFAULT_FILE_NAME);
}

boolean gtensureFileWithName(char * filename){
    boolean result = false;
    if (fp == NULL){
        // try open file
        fp = fopen(DEFAULT_FILE_NAME, "w+");
    }// end if

    // check
    result = (fp==NULL);
//    if(fp!=NULL)
//        result = true;
//    else
//        result = false;
    return result;
}

void destory(){
    if (NULL != fp){
        fclose(fp);
    }// end if
}

void gtlog(char * msg){
    fputs(msg, fp);
}

void gtlogln(char * msg){
    fputs(msg, fp);
    fputc('\n', fp);
}

void gtlogWithTag(char * tag, char * msg){
    fputs(tag, fp);
    fputc('|', fp);// divider char
    fputs(msg, fp);
}

void gtloglnWithTag(char * tag, char * msg){
   gtlogWithTag(tag, msg);
   fputc('\n', fp); 
}
