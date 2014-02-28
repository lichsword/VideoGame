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

GLTFrame frameCamera;

/**
 * 绘制地平面
 */
void drawGround(void){
    GLfloat fExtent = 20.0f;
    GLfloat fStep = 1.0f;
    GLfloat y = -1.5f;
    GLint iLine;

    glBegin(GL_LINES);
        for(iLine=-fExtent; iLine<=fExtent; iLine+=fStep){
            glVertex3f(iLine, y, fExtent);
            glVertex3f(iLine, y, -fExtent);

            glVertex3f(fExtent, y, iLine);
            glVertex3f(-fExtent, y, iLine);
        }// end if
    glEnd();
}

/**
 * 界面绘制事件
 */
void onDisplay(){
    int i;
    static GLfloat yRot = 0.0f;

    yRot += 0.5f;

    // 清除颜色和深度缓冲
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//------ 核心代码--------
    glPushMatrix();

    // 应用相机变换
//    gltApplyCameraTransform(&frameCamera);
    // 绘制线框立方体
    drawGround();
    
    glPopMatrix();
//------ 核心代码--------

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

    /**
     * 设置以线框的形式绘制所有东西
     */
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

    //--------- 核心代码 TODO ---------
    // 矩阵模式改为透视模式
    glMatrixMode(GL_PROJECTION);
    // 重置坐标系统
    glLoadIdentity();
    // 计算横纵比
    aspectRatio = (GLfloat) width/ (GLfloat) height;
    // 产生透视投影
    GLdouble fovy = 45.0f;
    GLdouble zNear = 1.0f;
    GLdouble zFar = 400.0f;
    // 建立裁剪区域（左、右、底、顶、近、远）
    gluPerspective(fovy, aspectRatio, zNear, zFar);
    // 矩阵模式要复位为模型视图
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //--------- 核心代码 TODO ---------
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
