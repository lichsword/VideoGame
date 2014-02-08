#include "../gtcommon.h"

#include <stdio.h>// use sprint() func.
#include <stdlib.h>// use rand() func.

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100

int windowId;// window resource id.

int MAX_COLOR = 100;// max value for rand color.
int loop;// use for mark index of loop.
int r,g,b;// record color parts for points.
int x,y;// record position of points.
int MAX_POINTS = 100000;// max points display on screen.

/**
 * 界面绘制事件
 */
void onDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);// use current color to clear window.
    // reset matrix
    glLoadIdentity();

    //----- import code start --------
    int halfWidth = WINDOW_WIDTH / 2;
    int halfHeight = WINDOW_HEIGHT / 2;

    int doubleWidth = WINDOW_WIDTH * 2;
    int doubleHeight = WINDOW_HEIGHT * 2;

    glBegin(GL_POINTS);
        // loop many time.
        for(loop = 0; loop < MAX_POINTS; loop++){  
            // random color and position.
            x = rand()%WINDOW_WIDTH;
            y = rand()%WINDOW_HEIGHT; 
            r = rand()%MAX_COLOR;
            g = rand()%MAX_COLOR;
            b = rand()%MAX_COLOR;
            // set color.
            glColor3f(
            (float)r/(float)MAX_COLOR,
            (float)g/(float)MAX_COLOR,
            (float)b/(float)MAX_COLOR);
            // draw point with position.
            glVertex2f(
            (float)x/(float)WINDOW_WIDTH - 0.5f,
            (float)y/(float)WINDOW_HEIGHT - 0.5f
            );
        }// end for
    glEnd();

    glutPostRedisplay();// force refresh(animation effective).
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

    // 修改视口的裁剪区域为标准: 宽(-100, 100)，高(100, 100)的正方形
    aspectRatio = (GLfloat) width/ (GLfloat) height;
    if(width <=height)
        glOrtho(-100.0, 100.0, -100/aspectRatio, 100.0/aspectRatio, 1.0, -1.0);
    else
        glOrtho(-100.0 * aspectRatio, 100.0 * aspectRatio, -100.0, 100.0, 1.0, -1.0);

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
    windowId = glutCreateWindow("Random draw points, (Q)quit.");
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
