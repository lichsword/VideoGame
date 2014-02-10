// mod.c
// API for import & export model file.
// Lichsword Video Game Enginee
//
// Report bugs to lichswordkernel@gmail.com
#include "gtcommon.h"
#include "gtlog.h"
#include "gtmod.h"

#include <stdio.h>

const char FILENAME[]="data.md3";

void gtloadMod(){
    gtloglnWithTag("gtmod", "open file start.");

    FILE * fp = NULL;
    fp = fopen(FILENAME, "r+");
    if(fp==NULL){
        // file open failed.
        return;
    }// end if

    gtloglnWithTag("gtmod", "open file success.");
    // assume line max char 200.
    char buffer[200];
    char * rp;
    // fgets return NULL means read end of file.
    while((rp=fgets(buffer, 200, fp))!=NULL){
        // we use log(not ln), becase buffer contain '\n' in the end.
        gtlogWithTag("read line", buffer);
        char firstChar = buffer[0];
        if(firstChar=='P'){// Point
            // TODO handle point
        }
    }
}
