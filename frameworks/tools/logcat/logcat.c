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
#include<limits.h>
#include<sys/types.h>
#include<sys/stat.h>

#define BUFFER_SIZE PIPE_BUF

int main()
{
	int pipe_fp = 0;
    int res=0;
    int open_mode = O_RDONLY;
    char buffer[BUFFER_SIZE + 1];
	int bytes_read = 0;

	// clean buffer data
	memset(buffer, '\0', sizeof(buffer));

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
    pipe_fp = open(PIPO_NAME_LOG, open_mode);

	printf("open ...");
    printf("Process %d result %d\n", getpid(), res);

	if(-1 != pipe_fp)
    {
        do
		{
			res = read(pipe_fp, buffer, BUFFER_SIZE);
			bytes_read += res; 
        }while(res > 0);
		(void)close(pipe_fp);
	}// end if

    printf("Process %d finished\n", getpid());
    exit(EXIT_SUCCESS);
}
