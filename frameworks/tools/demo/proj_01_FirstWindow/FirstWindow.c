#include "../include/gtcommon.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100

int windowId;

/**
 * 初始化外部资源
 */
void initGlobalRes(void){
    // blue(0.0, 1.0, 1.0)
    // novel(0.84,0.82,0.71)
    // r,g,b,a
    glClearColor(0.84f, 0.82f, 0.71f, 1.0f);// set clear color value.
}

/**
 * 界面绘制事件
 */
void onDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);// use current color to clear window.



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
    windowId = glutCreateWindow("Video Game 3D Enginee Demo");
    // set display callback
    glutDisplayFunc(onDisplay);
    // init recource 
    initGlobalRes();
    // start main loop
    glutMainLoop();
    return 0;
}
