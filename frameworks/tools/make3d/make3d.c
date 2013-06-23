/*
 * main.c
 * An simple openGL demo of light ball.
 */

// local head files.
#include"../../service/log/sv_log.h"
#include"../../service/font/sv_font.h"

// system head files.
#include<OpenGL/glu.h>
#include<OpenGL/gl.h>
#include<GLUT/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h> // define can change param.
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<limits.h>
#include<sys/types.h>
#include<sys/stat.h>

#define BUFFER_SIZE 1024

#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 800

#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100

char buffer[BUFFER_SIZE];

GLuint basePos; // draw font position
GLfloat counter1; // font pos counter 1
GLfloat counter2; // font pos counter 2

GLvoid drawCoordinate(){
	//glBegin(GL_LINE_STRIP);
	//glBegin(GL_LINE);
	glBegin(GL_LINES);
		glVertex3f( 240.0f, 400.0f, 0.0f);
		glVertex3f( 240.0f, 410.0f , 0.0f);

		glVertex3f( 240.0f, 400.0f, 0.0f);
		glVertex3f( 250.0f, 400.0f, 0.0f);

		glVertex3f( 240.0f, 400.0f, 0.0f);
		glVertex3f( 250.0f, 410.0f, 0.0f);
	glEnd();
	glEnd();
}

GLvoid buildFont(GLvoid)
{
	basePos = glGenLists(96);
	// TODO
}


void init(void)
{
    //GLfloat mat_specular [ ] = { 1.0, 1.0, 1.0, 1.0 }; 
    //GLfloat mat_shininess [ ] = { 50.0 }; 
    //GLfloat light_position [ ] = { 1.0, 1.0, 1.0, 0.0 }; 

    glClearColor ( 0.0, 0.0, 0.0, 0.0 ); 
    glShadeModel ( GL_SMOOTH ); 
	makeRasterFont();

	//gluOrtho2D(WINDOW_WIDTH, WINDOW_HEIGHT); 

	// below light will hide the font display.
    //glMaterialfv ( GL_FRONT, GL_SPECULAR, mat_specular); 
    //glMaterialfv ( GL_FRONT, GL_SHININESS, mat_shininess); 
    //glLightfv ( GL_LIGHT0, GL_POSITION, light_position); 

    //glEnable (GL_LIGHTING); 
    //glEnable (GL_LIGHT0); 
    //glEnable (GL_DEPTH_TEST); 

    sv_log("init...");
} 

void display(void)
{
	GLfloat white[3] = {1.0, 1.0, 1.0};
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3fv(white);

    //glutSolidSphere(1.0, 40, 50);
// "ABCD" all can print right, so the content is right.
// now, we need make sure the position is right/wrong?	
// (0,0) position is ok, display center of screen.
// (1,0) position is ok, display right of screen.
// (1,2) position is ok, display rigth-top of screen.
	glRasterPos2i(0, 0);
	//printString("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	drawCoordinate();

    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	/*
    if (w <= h) 
        glOrtho (-1.5, 1.5, -1.5 * ( GLfloat ) h / ( GLfloat ) w, 1.5 * ( GLfloat ) h / ( GLfloat ) w, -10.0, 10.0 ); 
    else 
        glOrtho (-1.5 * ( GLfloat ) w / ( GLfloat ) h, 1.5 * ( GLfloat ) w / ( GLfloat ) h, -1.5, 1.5, -10.0, 10.0); 
    glMatrixMode ( GL_MODELVIEW ); 
    glLoadIdentity (); 
	*/
	gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
}

void keyboard ( unsigned char key, int x, int y) 
{ 
    /*按Esc键退出*/ 
    switch (key) { 
    case 27: 
    	exit ( 0 ); 
    	break; 
	default:
		sprintf(buffer, "press key = %c", key);
    	sv_log(buffer);
		break;
    } 
} 

void mouse(int button, int state, int x, int y)
{
    // TODO
    sprintf(buffer, "button = %d, state = %d, x = %d, y = %d", button, state, x, y);
    sv_log(buffer);
}

int main(int argc, char** argv)
{
  
    sv_log("start main...");

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
 
    glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);

    glutCreateWindow(argv[0]);

    init();

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard);

    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}
  

