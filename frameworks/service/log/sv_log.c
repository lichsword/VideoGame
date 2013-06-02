#include"sv_log.h"
#include"../pipo/pipo.h"

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<limits.h>
#include<sys/types.h>
#include<sys/stat.h>

int open_mode = O_WRONLY; // log pipe open mode.
int pipe_fp =0;

void sv_log(char * content)
{
    int res = 0;
    if(-1==access(PIPO_NAME_LOG, F_OK)) 
    {
        res = mkfifo(PIPO_NAME_LOG, 0777);
        if(0!=res)
        {
            fprintf(stderr, "Could not create fifo %s\n", PIPO_NAME_LOG);
            exit(EXIT_FAILURE);
        }// end if
    }// end if

    if(-1 == pipe_fp) 
    {
        // initial file pointer of pipo.
        pipe_fp = open(PIPO_NAME_LOG, open_mode);
        if(-1 == pipe_fp)
        {
            fprintf(stderr, "open pipo file failed!\n");
            return;
        }// end if
    }// end if

    if(-1 != pipe_fp)
    {
        write(pipe_fp, content, strlen(content));
        write(pipe_fp, "\n", 1);
    }// end if

    return; 
}
