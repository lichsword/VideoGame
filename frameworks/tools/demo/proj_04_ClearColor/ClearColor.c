#include "../include/gtcommon.h"

#include<stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100

int windowId;

/**
 * 键盘响应
 */
void onKeyboard(unsigned char key, int x, int y){
    if(key=='Q' | key=='q'){
        glutDestroyWindow(windowId);// close window.
        exit(0);// exit application success.
    }// end if

    // ----------- import code start -------------
    if(key=='R' | key=='r'){
        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);// red
        glutPostRedisplay();// force redisplay
        return;
    }// end if
    
    if(key=='G' | key=='g'){
        glClearColor(0.0f, 1.0f, 0.0f, 0.0f);// green
        glutPostRedisplay();// force redisplay
        return;
    }// end if

    if(key=='B' | key=='b'){
        glClearColor(0.0f, 0.0f, 1.0f, 0.0f);// blue
        glutPostRedisplay();// force redisplay
        return;
    }// end if

    if(key=='Y' | key=='y'){
        glClearColor(0.84f, 0.82f, 0.71f, 1.0f);// yellow
        glutPostRedisplay();// force redisplay
        return;
    }// end if
    // ----------- import code end ------------
}

/**
 * 初始化外部资源
 */
void initGlobalRes(void){
    // r,g,b,a
    glClearColor(0.84f, 0.82f, 0.71f, 1.0f);// yellow
}

/**
 * 界面绘制事件
 */
void onDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);// use current color to clear window.
    // reset matrix
    glLoadIdentity();
    //--------
    //glFlush();// (Single Buffer)force flush screen buffer.
    glutSwapBuffers();// (Double Buffer)swap buffers.
}

/**
 * 主程序入口
 */
int main(int argc, char * argv[]){
    // init
    glutInit(&argc, argv);
    // set display mode(doubel/single buffer mode ?)
    //glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    // set window size
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // set window pos
    glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
    // set window title
    windowId = glutCreateWindow("(Q)quit (R)red (G)green (B)blue (Y)yellow.");
    // set display callback
    glutDisplayFunc(onDisplay);
    // set keyboard callback
    glutKeyboardFunc(onKeyboard);
    // init recource 
    initGlobalRes();
    // start main loop
    glutMainLoop();
    return 0;
}
