#include"log.h"
#include"../pipo/pipo.h"

int open_mode = O_WRONLY; // log pipe open mode.

void log_abcd(char * content)
{
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
            fprintf(stderr, "open pipo file failedi\n");
            return EXIT_FAILURE;
        }// end if
    }// end if

    if(-1 != pipe_fp)
    {
        write(pipe_fp, content, strlen(content));
    }// end if
 
}
