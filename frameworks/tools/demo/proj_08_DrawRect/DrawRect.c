#include "../include/gtcommon.h"

#include <stdio.h>// use sprint() func.
#include <stdlib.h>// use rand() func.

#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 60
#define WINDOW_POS_X halfViewPort
#define WINDOW_POS_Y halfViewPort

int windowId;// window resource id.

float halfViewPort = 100.0f;// half of viewport is 100.0f.

int MAX_COLOR = 255;// max value for rand color.
int loop;// use for mark index of loop.
int r,g,b;// record color parts for points.
int l,t,r,b;// record left,top,right,bottom of rects.
int MAX_POINTS = 1;// max points display on screen.

/**
 * 界面绘制事件
 */
void onDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);// use current color to clear window.
    // reset matrix
    glLoadIdentity();

    //----- import code start --------
    
    // loop many time.
    for(loop = 0; loop < MAX_POINTS; loop++){  
        // random color
        r = rand()%MAX_COLOR;
        g = rand()%MAX_COLOR;
        b = rand()%MAX_COLOR;
        // set color.
        glColor3f(
        (float)r/(float)MAX_COLOR,
        (float)g/(float)MAX_COLOR,
        (float)b/(float)MAX_COLOR);

        // random position
        // set left and right value.
        int m,n,r;
        m = rand()%(2 * (int)halfViewPort);
        n = rand()%(2 * (int)halfViewPort); 
        if(m>n){
            r = m; m = n; n=r;
        }// end if

        l = m - halfViewPort;// set left.
        r = n - halfViewPort;// set right.

        // set top and bottom value.
        m = rand()%(2 * (int)halfViewPort);
        n = rand()%(2 * (int)halfViewPort); 
        if(m>n){
            r = m; m = n; n=r;
        }// end if

        t = m - halfViewPort;// set top.
        b = n - halfViewPort;// set bottom.

        // (left, top, right, bottom)
        glRectf(l, t, r, b);
    }// end for

    // 画一个测试样本
    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, 100.0f);
        glVertex2f(100.0f, 0.0f);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(100.0f, 0.0f);
        glVertex2f(0.0f, -100.0f);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.0f, -100.0f);
        glVertex2f(-100.0f, 0.0f);

        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex2f(-100.0f, 0.0f);
        glVertex2f(0.0f, 100.0f);
    glEnd();
    //glutPostRedisplay();// force refresh(animation effective).
    //----- import code end --------

    //--------
    //glFlush();// (Single Buffer)force flush screen buffer.
    glutSwapBuffers();// (Double Buffer)swap buffers.
}

/**
 * 键盘响应
 */
void onKeyboard(unsigned char key, int x, int y){
    if(key=='Q' | key=='q'){
        glutDestroyWindow(windowId);// close window.
        exit(0);// exit application success.
    }// end if
}
/**
 * 初始化外部资源
 */
void initGlobalRes(void){
    // r,g,b,a
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);// black
}

/**
 * 当窗口改变时
 */
void onReshape(int width, int height){
    GLfloat aspectRatio;// 裁剪比例   

    // 防止
    if(0==height)
        height=1;
    
    // 把视口设置为窗口大小
    glViewport(0,0,width, height);

    // 重置坐标系统
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 修改视口的裁剪区域为标准: 
    // 宽(-halfViewPort, halfViewPort)，高(halfViewPort, halfViewPort)的正方形
    aspectRatio = (GLfloat) width/ (GLfloat) height;
    if(width <=height)
        glOrtho(-halfViewPort, halfViewPort, -halfViewPort/aspectRatio, halfViewPort/aspectRatio, 1.0, -1.0);
    else
        glOrtho(-halfViewPort * aspectRatio, halfViewPort * aspectRatio, -halfViewPort, halfViewPort, 1.0, -1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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
    windowId = glutCreateWindow("Draw Rect in New ViewPort, (Q)quit.");
    // set display callback
    glutDisplayFunc(onDisplay);
    // set keyboard callback
    glutKeyboardFunc(onKeyboard);
    //---------- import code start ----------
    // reshape callback
    //---------- import code end ----------
    glutReshapeFunc(onReshape);
    // init recource 
    initGlobalRes();
    // start main loop
    glutMainLoop();
    return 0;
}
