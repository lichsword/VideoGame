// gltool.h
// Lichsword Video Game Enginee
//
// Report bugs to lichswordkernel@gmail.com

#ifndef __gltools_h__
#define __gltools_h__

#define MACOSX

// Mac OS X
#if defined(__APPLE__) || defined(MACOSX) 
#include <Carbon/Carbon.h> // mac Carbon API support opengl.
#include <OpenGL/gl.h> // Opengl head file 
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#include <sys/time.h>

#else
// Assuming Linux
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <sys/time.h>

#endif

// standary C libs
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#endif
