#include "gtcommon.h"

#include "gtmod.h"
#include "gtlog.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100

typedef struct{
    int xRot;
    int yRot;
}MouseOper;

int startX;
int startY;
int currentX;
int currentY;
int windowId;

// gloable variable
int bCull = 0;
int bDepth = 1;
int bOutline = 0;

MouseOper mouseOper;

void onMouseDown(int button, int x, int y){
    switch(button){
    case GLUT_LEFT_BUTTON:
        startX = x;
        startY = y;
        break;
    case GLUT_RIGHT_BUTTON:
        break;
    case GLUT_MIDDLE_BUTTON:
        break;
    }
}

void onMouseUp(int button, int x, int y){
    switch(button){
    case GLUT_LEFT_BUTTON:
        startX = 0;
        startY = 0;
        break;
    case GLUT_RIGHT_BUTTON:
        break;
    case GLUT_MIDDLE_BUTTON:
        break;
    }
}

// glutTimerFunc(33, onTimer, 1);

void onMouseMotion(int x, int y){
    gtloglnWithTagFormatInt2("MouseMotion", "x=%d, y=%d", x, y);
    currentX = x;
    currentY = y;

    mouseOper.xRot = (currentY - startY)*180/400;
    mouseOper.yRot = (currentX - startX)*180/400;
//    mouseOper.rotateZ = (currentZ - startZ)/100;
    // rotate
    gtloglnWithTagFormatInt2("rotate", "xRot=%f, yRot=%f", mouseOper.xRot, mouseOper.yRot);

    glutPostRedisplay();
}

/**
 * 初始化外部资源
 */
void initGlobalRes(void){
    // test log
    gtensureFile();
    gtlogln("onReshape()...invoked.");
    gtloglnWithTag("lichsword", "onReshape()...invoked.");

    // blue(0.0, 1.0, 1.0)
    // novel(0.84,0.82,0.71)
    // r,g,b,a
    glClearColor(0.84f, 0.82f, 0.71f, 1.0f);// set clear color value.
    // TODO load mod 3d
    gtloadMod();

    glShadeModel(GL_FLAT);// 纯色着色，区别于渐变色 GL_SMOOTH
    glFrontFace(GL_CW);// 设置顺时针为正面
}


/**
 * 当窗口改变时
 */
void onReshape(int width, int height){
    gtlogln("onReshape()...invoked.");
    gtloglnWithTag("lichsword", "onReshape()...invoked.");
    // TODO
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
 * 键盘响应
 */
void onKeyboard(unsigned char key, int x, int y){
    // TODO
    gtloglnWithTagFormatChar1("Press key: ", "%c", key);
    if( key == ' ' ){// press space key
        mouseOper.xRot = 0;
        mouseOper.yRot = 0;
        glutPostRedisplay();
    }else if(key == 'q' | key == 'Q'){
        glutDestroyWindow(windowId);// close window.
        exit(0);// exit app.
    }// end if
}


/**
 * 鼠标响应
 */
void onMouse(int button, int state, int x, int y){
    // TODO
    gtloglnWithTagFormatInt4("Mouse Event: ", "button=%d,state=%d,x=%d,y=%d", button, state, x, y);
    if(GLUT_DOWN==state){
        onMouseDown(button, x, y);
    }else if(GLUT_UP==state){
        onMouseUp(button, x, y);
    }else{
        // log error
    }
}

/**
 * 界面绘制事件
 */
void onDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);// use current color to clear window.
    glClear(GL_DEPTH_BUFFER_BIT);// clear depth buffer
    // reset matrix
    glLoadIdentity();

   // gluLookAt(
   // 0.0f, 0.0f, 1.0f,
   // 0.0f, 0.0f, 0.0f,
   // 0.0f, 1.0f, 0.0f);
    //glRotatef(mouseOper.xRot, 1.0f, 0.0f, 0.0f);
    //glRotatef(mouseOper.yRot, 0.0f, 1.0f, 0.0f);
    //--------
    //glutStrokeLength(GLUT_STROKE_ROMAN, "Show me the Money!");
    //glRectf(-25.0f, 25.0f, 25.0f, -25.0f);// draw a rect with red color
    // start draw lines

    /*
    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);// change currnet color to red
        glVertex3f(0.0f, 0.0f, 0.0f);// draw x
        glVertex3f(25.0f, 0.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);// change currnet color to green
        glVertex3f(0.0f, 0.0f, 0.0f);// draw y
        glVertex3f(0.0f, 25.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);// change currnet color to yellow
        glVertex3f(0.0f, 0.0f, 0.0f);// draw z
        glVertex3f(0.0f, 0.0f, 25.0f);
    glEnd();
    */

//    glRotatef(mouseOper.rotateZ, 0.0f, 0.0f, 1.0f);
    // end draw lines
    // TODO test
    GLfloat x,y,angle;// save position and angle.
    int iPivot = 1;// save color index.

    // check cull face flag.
    if(bCull)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    // check depth test flag.
    if(bDepth)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    // check outline flag.
    if(bOutline)
        glPolygonMode(GL_BACK, GL_LINE);
    else
        glPolygonMode(GL_BACK, GL_FILL);

    // save matrix and rotation
    glPushMatrix();
    //glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    //glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(mouseOper.xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(mouseOper.yRot, 0.0f, 1.0f, 0.0f);

    // start draw triangle fans
    glBegin(GL_TRIANGLE_FAN);

    // 画圆锥的顶点
    glVertex3f(0.0f, 0.0f, 75.0f);

    // draw circle
    for(angle = 0.0f;  angle < (2.0f * GL_PI); angle += (GL_PI/8.0f))
    {
        // count next point pos
        x = 50.0f * sin(angle);
        y = 50.0f * cos(angle);

        // toggle red/green color
        if(iPivot %2 ==0)
            glColor3f(0.0f, 1.0f, 0.0f);// green color
        else 
            glColor3f(1.0f, 0.0f, 0.0f);

        // inc index
        iPivot ++;

        // draw next point
        glVertex2f(x, y);
    }

    glEnd();

    glPopMatrix();
    // 
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
    windowId = glutCreateWindow("Video Game 3D Enginee Demo");
    // set reshape callback
    glutReshapeFunc(onReshape);
    // set keyboard callback
    glutKeyboardFunc(onKeyboard);
    // set mouse callback
    glutMouseFunc(onMouse);
    // set mouse motion callback
    glutMotionFunc(onMouseMotion);
    // set display callback
    glutDisplayFunc(onDisplay);
    // init recource 
    initGlobalRes();
    // start main loop
    glutMainLoop();
    return 0;
}
