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
void gtloglnWithTagFormatInt1(char * tag, char * format, int p);
void gtloglnWithTagFormatInt2(char * tag, char * format, int p1, int p2);
void gtloglnWithTagFormatInt3(char * tag, char * format, int p1, int p2, int p3);
void gtloglnWithTagFormatInt4(char * tag, char * format, int p1, int p2, int p3, int p4);
void gtloglnWithTagFormatChar1(char * tag, char * format, unsigned char p);
void gtloglnWithTagFormatFloat1(char * tag, char * format, float p1);
void gtloglnWithTagFormatFloat2(char * tag, char * format, float p1, float p2);

#endif
