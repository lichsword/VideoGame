/*
 * main.c
 * An simple openGL demo of light ball.
 */

// local head files.
#include"../service/log/log.h"
// system head files.
#include<OpenGL/glu.h>
#include<OpenGL/gl.h>
#include<GLUT/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<limits.h>
#include<sys/types.h>
#include<sys/stat.h>



void init(void)
{
    GLfloat mat_specular [ ] = { 1.0, 1.0, 1.0, 1.0 }; 
    GLfloat mat_shininess [ ] = { 50.0 }; 
    GLfloat light_position [ ] = { 1.0, 1.0, 1.0, 0.0 }; 

    glClearColor ( 0.0, 0.0, 0.0, 0.0 ); 
    glShadeModel ( GL_SMOOTH ); 

    glMaterialfv ( GL_FRONT, GL_SPECULAR, mat_specular); 
    glMaterialfv ( GL_FRONT, GL_SHININESS, mat_shininess); 
    glLightfv ( GL_LIGHT0, GL_POSITION, light_position); 

    glEnable (GL_LIGHTING); 
    glEnable (GL_LIGHT0); 
    glEnable (GL_DEPTH_TEST); 

    char* text="Hello, world!";
    //log("Hello world");  
    log_abcd(text); 
} 

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutSolidSphere(1.0, 40, 50);

    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h) 
        glOrtho (-1.5, 1.5, -1.5 * ( GLfloat ) h / ( GLfloat ) w, 1.5 * ( GLfloat ) h / ( GLfloat ) w, -10.0, 10.0 ); 
    else 
        glOrtho (-1.5 * ( GLfloat ) w / ( GLfloat ) h, 1.5 * ( GLfloat ) w / ( GLfloat ) h, -1.5, 1.5, -10.0, 10.0); 
    glMatrixMode ( GL_MODELVIEW ); 
    glLoadIdentity (); 
}

void keyboard ( unsigned char key, int x, int y) 
{ 
    /*按Esc键退出*/ 
    switch (key) { 
    case 27: 
    exit ( 0 ); 
    break; 
    } 
} 

void mouse(int button, int state, int x, int y)
{
    // TODO
}

int main(int argc, char** argv)
{
  
    printf("start main...");

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(480, 800);
 
    glutInitWindowPosition(100, 100);

    glutCreateWindow(argv[0]);

    init();

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard);

    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}
  

