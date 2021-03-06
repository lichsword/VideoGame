/**
 * 画圆锥
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
 * 记录当前旋转角度
 */
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;

/**
 * 界面绘制事件
 */
void onDisplay(){
    GLfloat x,y,z,angle;// position and angle
    GLfloat size = 1.0f;// point size.

    /**
     * 清除颜色缓冲区.
     */
    glClear(GL_COLOR_BUFFER_BIT);
    /**
     * 清除深度缓冲区.
     */
    glClear(GL_DEPTH_BUFFER_BIT);
    /**
     * 添加像素的深度测试，否则远处像素会覆盖近处，则不正确。
     */
    glEnable(GL_DEPTH_TEST);
    /**
     * 开启隐面剔除
     */
    glEnable(GL_CULL_FACE);
    glEnable(GL_CCW);// 顺时针为正面

    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    // 圆半径
    float range = 50.0f;

    // 画三角形使用连续的3个顶点
    float factor = 50;// 缩放因子(我是在草稿纸上以1.0f为单位画的，所以视口上要*50)
    // 循环局部索引变量
    int nIndex = 0;

    gtloglnWithTagFormatFloat1("INFO", "xRot=%f", xRot);

    glBegin(GL_TRIANGLE_FAN);// 开始画直线
        glVertex3f(0, 0, 50.0f);// 圆锥的顶点
        for(angle = 0.0f, nIndex=0; angle<2*GL_PI; angle+=(GL_PI/8.0f), nIndex++){
            // change color.
            if(nIndex%2==0)
                glColor3f(1.0f, 0.0f, 0.0f);// 设置前景色为红色
            else
                glColor3f(0.0f, 1.0f, 0.0f);// 设置前景色为绿色
            // count x,y
            x = range * cos(angle);
            y = range * sin(angle);
            // draw next vertex
            glVertex3f(x, y, 0);
        }// end if
        
        // 画最后一个点，来封口
        glVertex3f(50.0f, 0, 0);

    glEnd();
    //-------------------------- 
    // 画圆锥底盘（圆形）
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, 0, 0);// 先画圆盘中心

        // 循环画出扇形边
        for(angle = 0.0f, nIndex=0; angle<2.0f*GL_PI; angle+=0.5f, nIndex++){
            // change color.
            if(nIndex%2==0)
                glColor3f(1.0f, 0.0f, 0.0f);// 设置前景色为红色
            else
                glColor3f(0.0f, 1.0f, 0.0f);// 设置前景色为绿色
            // count x,y
            x = range * sin(angle);
            y = range * cos(angle);
            // draw next vertex
            glVertex3f(x, y, 0);
        }

        // 画最后一个点，来封口
        glVertex3f(0, 50.0f, 0);
    glEnd();
    
    glPopMatrix();

    /**
     * 改变角度
     * 注意：这里我故意把x,y的旋转增量设置为不同步，这样可以避免形成线性轨道。
     */
    xRot += 1.0f;
    yRot += 2.0f;

    /**
     * 设置帧数为33间隔，约30FPS，注意，这里没有实现很严格的锁定帧
     * 要改进为去掉计算时间差之后的帧间隔才合理。（不过这是优化工作）
     */
    usleep(33);// 1000/33=30(FPS)

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
