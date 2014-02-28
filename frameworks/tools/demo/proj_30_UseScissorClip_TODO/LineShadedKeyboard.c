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

/**
 * 0=disable; 1=enable
 * 启用着色
 */
int bOutline = 0;

/**
 * 界面绘制事件
 */
void onDisplay(){
    GLfloat x,y,z,angle;// position and angle
    GLfloat size = 1.0f;// point size.

    GLfloat xRot = 45.0f;
    GLfloat yRot = 45.5f;

    glClear(GL_COLOR_BUFFER_BIT);// use current color to clean bg.

    /**
     * TODO
     * GL_FRONT = 正面
     * GL_BACK = 背面
     * GL_FRONT_AND_BACK = 两面都有
     * 因为此示例中是使用正面，所以要使用GL_FRONT 或 GL_FRONT_AND_BACK
     * 否则，无法实现线框和着色的切换效果
     */
    if(1==bOutline)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glPushMatrix();
    //glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    //glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    float range = 50.0f;

//------ 核心代码--------
    // 画三角形使用连续的3个顶点
    float factor = 50;// 缩放因子(我是在草稿纸上以1.0f为单位画的，所以视口上要*50)
    glBegin(GL_TRIANGLE_FAN);// 开始画直线
        // triangle 1
        glColor3f(0.0f, 1.0f, 0.0f);// 设置前景色为绿色
        glVertex3f(0, 0, 0);
        glVertex3f(-2.0f*factor, 0, 0);
        glVertex3f(-1.0f*factor, -1.732f*factor, 0);

        // triangle 2
        glColor3f(1.0f, 0.0f, 0.0f);// 设置前景色为红色
        glVertex3f(1.0f*factor, -1.732f*factor, 0);
        // triangle 3
        glColor3f(0.0f, 1.0f, 0.0f);// 设置前景色为绿色
        glVertex3f(2.0f*factor, 0, 0);
        // triangle 4
        glColor3f(1.0f, 0.0f, 0.0f);// 设置前景色为红色
        glVertex3f(1.0f*factor, 1.732f*factor, 0);
        // triangle 5
        glColor3f(0.0f, 1.0f, 0.0f);// 设置前景色为绿色
        glVertex3f(-1.0f*factor, 1.732f*factor, 0);
        // triangle 6
        glColor3f(1.0f, 0.0f, 0.0f);// 设置前景色为绿色
        glVertex3f(-2.0f*factor, 0, 0);
    glEnd();
//------ 核心代码--------
    glPopMatrix();

    usleep(33);
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

    if(key==' '){
        if(0==bOutline)
            bOutline = 1;
        else
            bOutline = 0;
    }// end if

    gtloglnWithTagFormatInt1("INFO", "current bOutline=%d", bOutline);
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
