#include "../gtcommon.h"

#include<stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100

int windowId;

// buffer string
char buffer[256];

/**
 * 鼠标响应
 */
void onMouse(int button, int state, int x, int y){
    // TODO
    sprintf(buffer, "Mouse event: button=%d, state=%d, x=%d, y=%d", button, state, x, y);
    glutSetWindowTitle(buffer);
}

/* import code here */
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
    glClearColor(0.84f, 0.82f, 0.71f, 1.0f);// set clear color value.
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
    windowId = glutCreateWindow("Press Q or q to exit application.");
    // set display callback
    glutDisplayFunc(onDisplay);
    // set keyboard callback
    glutKeyboardFunc(onKeyboard);
    /** 
     * Import code here
     */
    // set mouse callback
    glutMouseFunc(onMouse);
    // init recource 
    initGlobalRes();
    // start main loop
    glutMainLoop();
    return 0;
}
