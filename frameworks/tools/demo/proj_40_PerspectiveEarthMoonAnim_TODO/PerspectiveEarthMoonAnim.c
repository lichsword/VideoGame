/**
 * 着色的球体太阳与月亮进行环绕动画（透视效果：近大远小）
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
    // 地球和月球的旋转角度
    static float fEarthRot = 0.0f;
    static float fMoonRot = 0.0f;

    static GLTVector3 lightPos = {0, 10.0f, 10.0f};

    // 用当前清除颜色清除窗口
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 保存矩阵状态并进行旋转
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // 把整个场景移动到视图中
    glTranslatef(0.0f, 0.0f, -300.0f);
    
    // 设置材料颜色，太阳为黄色
    glColor3ub(255, 255, 0); //red + green = yellow. 
    glDisable(GL_LIGHTING);// 禁用光照
    glutSolidSphere(15.0f, 15, 15);
    glEnable(GL_LIGHTING);// 启用光照

    // 在绘制太阳之后，放置光源
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // 旋转坐标系统
    glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);
    // 绘制地球
    glColor3ub(0, 0, 255);// 地球为蓝色
    glTranslatef(105.0f, 0, 0);
    glutSolidSphere(15.0f, 15, 15);

    // 根据地球的坐标进行旋转，并绘制月球
    glColor3ub(200, 200, 200);
    glRotatef(fMoonRot, 0.0f, 1.0f, 0.0f);
    glTranslatef(30.0f, 0.0f, 0.0f);
    fMoonRot += 15.0f;
    if(fMoonRot > 360.0f){
        fMoonRot = 0.0f;// reset
    }// end if

    glutSolidSphere(6.0f, 15, 15);

    // 恢复矩阵状态
    glPopMatrix();// 现在是模型视图状态
    
    // 每次绕轨道旋转5度
    fEarthRot += 5.0f;
    if(fEarthRot > 360.0f){
        fEarthRot = 0.0f;
    }// end if
    // TODO 还是一片黑，不知道为什么?
    glutPostRedisplay(); 
    // 刷新双缓冲界面
    glutSwapBuffers(); 
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

    //--------- 核心代码 TODO ---------
    // 设置为【透视模式】
    glMatrixMode(GL_PROJECTION);
    // 重置矩阵系统
    glLoadIdentity();

    // 修改视口的裁剪区域为标准: 
    // 宽(-nRange, nRange)，高(nRange, nRange)的正方形
    aspectRatio = (GLfloat) width/ (GLfloat) height;

    // 产生透视投影
    GLdouble fovy = 45.0f;
    GLdouble zNear = 100.0f;
    GLdouble zFar = 400.0f;
    gluPerspective(fovy, aspectRatio, zNear, zFar);
    // 复位【模型视图】
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
