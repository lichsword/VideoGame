/**
 * 使用键盘交互操控线框与着色模式切换
 */
#include "../include/gtcommon.h"
#include "../include/gtlog.h"

#include <stdio.h>// use sprint() func.
#include <stdlib.h>// use rand() func.

#define WINDOW_WIDTH 100
#define WINDOW_HEIGHT 100
#define WINDOW_POS_X nRange
#define WINDOW_POS_Y nRange

int windowId;// window resource id.

float nRange = 100.0f;// half of viewport is 100.0f.

char buffer[256];

float angle;
float angle1;

/**
 * 界面绘制事件
 */
void onDisplay(){
    GLfloat x,y,z;// position and angle
    GLfloat x1,y1,z1;// position and angle

    GLfloat size = 1.0f;// point size.

    GLfloat xRot = 30.0f;
    GLfloat yRot = 120.0f;

    glClear(GL_COLOR_BUFFER_BIT);// use current color to clean bg.

    glPushMatrix();

//------ 核心代码--------
    angle += 0.05f;
    angle1 += 0.1f;
    
    x = 30 * cos(angle);
    y = 30 * sin(angle);

    // 复位矩阵，让当前平移矩阵复位到原始点（0,0,0）
    glLoadIdentity();

    // 移动到 x = 50.0f 处，绘制第一球体
    glutSolidSphere(10.0f, 15, 15);

    // 复位矩阵，让当前平移矩阵复位到原始点（0,0,0）
    glLoadIdentity();

    // 移动到 x = 50.0f 处，绘制第二球体
    glTranslatef(x, y, z);
    glutSolidSphere(5.0f, 15, 15);
    
    // 复位矩阵，让当前平移矩阵复位到原始点（0,0,0）
    glLoadIdentity();
    
    x1 = 10 * cos(angle1) + x;
    y1 = 10 * sin(angle1) + y; 

    // 移动到 x = 50.0f 处，绘制第三球体
    glTranslatef(x1, y1, z1);
    glutSolidSphere(2.0f, 15, 15);

//------ 核心代码--------

    glPopMatrix();

    usleep(33333);
    /**
     * 刷新
     */
    glutPostRedisplay();
    // glFlush();// (single Buffer) force flush screen buffer.
    glutSwapBuffers();// (Double Buffer) swap buffers.
   
}
/**
 * 初始化外部资源
 */
void initGlobalRes(void){
    //--------- 核心代码 TODO ---------
    // init log file
    gtensureFileWithName("log.data");
    glShadeModel(GL_FLAT);// 这里也很重要，设置为平坦着色，否则会混色（默认）
    //--------- 核心代码 ---------
    // r,g,b,a
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);// black
}

/**
 * 鼠标响应
 */
void onMouse(int button, int state, int x, int y){
    sprintf(buffer, "[LOG INFO]Mouse event: button=%d, state=%d, x=%d, y=%d", button, state, x, y);
    gtloglnWithTag("[LOG INFO]", buffer);
    glutSetWindowTitle(buffer);
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
    // 宽(-nRange, nRange)，高(nRange, nRange)的正方形
    aspectRatio = (GLfloat) width/ (GLfloat) height;
    // 建立裁剪区域（左、右、底、顶、近、远）
    if(width <=height)
        glOrtho(-nRange, nRange, -nRange/aspectRatio, nRange/aspectRatio, -nRange, nRange);
    else
        glOrtho(-nRange * aspectRatio, nRange * aspectRatio, -nRange, nRange, -nRange, nRange);

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
    windowId = glutCreateWindow("Press keyboard Or drag mouse, (Q)quit.");
    // set display callback
    glutDisplayFunc(onDisplay);
    // set keyboard callback
    glutKeyboardFunc(onKeyboard);
    // mouse callback
    glutMouseFunc(onMouse);
    // reshape callback
    glutReshapeFunc(onReshape);
    // init recource 
    initGlobalRes();
    // start main loop
    glutMainLoop();
    return 0;
}
