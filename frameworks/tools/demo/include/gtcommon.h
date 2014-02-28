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
#include <unistd.h>

#else
    // Assuming Linux
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <sys/time.h>
#include <unistd.h>

#endif

// standary C libs
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define boolean int
#define false 0
#define true 1

#define GLT_PI 3.14159265358979323846
#define GLT_PI_DIV_180 0.017453292519943296
#define GLT_INV_PI_DIV_180 57.2957795130823229

// Some data types
typedef GLfloat GLTVector2[2];      // Two component floating point vector
typedef GLfloat GLTVector3[3];      // Three component floating point vector
typedef GLfloat GLTVector4[4];      // Four component floating point vector
typedef GLfloat GLTMatrix[16];      // A column major 4x4 matrix of type GLfloat

typedef struct{                     // The Frame of reference container
    GLTVector3 vLocation;
    GLTVector3 vUp;
    GLTVector3 vForward;
}GLTFrame;

#endif
