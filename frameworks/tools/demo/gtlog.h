// gtlog.h
// Game Tool log.h
// Lichsword Video Game Enginee
//
// Report bugs to lichswordkernel@gmail.com

#ifndef __log_h__
#define __log_h__

// file io head file.
#include <stdio.h>
boolean gtensureFile();
boolean gtensureFileWithName(char * filename);
void destory();
void gtlog(char * msg);
void gtlogln(char * msg);
void gtlogWithTag(char * tag, char * msg);
void gtloglnWithTag(char * tag, char * msg);
void gtloglnWithTagFormatInt1(char * tag, char * format, int param);
void gtloglnWithTagFormatChar1(char * tag, char * format, unsigned char param);
void gtloglnWithTagFormatInt4(char * tag, char * format, int param1, int param2, int parma3, int param4);
#endif
