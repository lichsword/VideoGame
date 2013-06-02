/* Logcat app is an tool to monitor the log info.
 * @since 1.0, logcat is console, maybe upgrade to GUI app later.
 *
 * Bug list:
 *     (1) expected expression before '=' token, in many place.
 */
#include"logcat.h"
#include"../../service/pipo/pipo.h"

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main()
{
    int res=0;
    int open_mode = O_WRONLY;
    int result = access(PIPO_NAME_LOG, F_OK);

    if(access(PIPO_NAME_LOG, F_OK)==-1)
    {
        res = mkfifo(PIPO_NAME_LOG, 0777);
        if(0!=res)
        {
            fprintf(stderr, "Could not create fifo %s\n", PIPO_NAME_LOG);
            exit(EXIT_FAILURE);
        }// end if
    }// end if

    printf("Process %d opening FIFO\n", getpid());
    res = open(PIPO_NAME_LOG, open_mode);
    printf("Process %d result %d\n", getpid(), res);

    sleep(5);

    if(-1!=res)
        (void)close(res);

    printf("Process %d finished\n", getpid());
    exit(EXIT_SUCCESS);
}
