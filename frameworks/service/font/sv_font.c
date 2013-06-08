#include"sv_font.h"

#include<string.h>
#include<OpenGL/glu.h>
#include<OpenGL/gl.h>

GLuint fontOffset;

GLubyte space[]=
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

GLubyte letters[][13]={
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
};

void makeRasterFont(void)
{
	GLuint i;
	GLuint j;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	/* initial buffer of font list */
	fontOffset = glGenLists(LETTER_BUFFER_SIZE); 
	/* fill bitmap of font into letter buffer list */
	for(i = 0; j = 'A', i < 1; i++, j++)
	{
		glNewList(fontOffset + j, GL_COMPILE);
		glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, letters[i]);
		glEndList();
	}
	glNewList(fontOffset + " ", GL_COMPILE);
	glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0,space);
	glEndList();
}

void printString(char * s)
{
	glPushAttrib(GL_LIST_BIT);
	glListBase(fontOffset);
	glCallLists(strlen(s), GL_UNSIGNED_BYTE, (GLubyte *) s);
	glPopAttrib();
}
