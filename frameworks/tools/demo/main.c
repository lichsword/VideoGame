#include "gtcommon.h"

#include "gtlog.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100

int Exit = 0;

/**
 * 初始化外部资源
 */
void initGlobalRes(void){
    // test log
    gtensureFile();
    gtlogln("onReshape()...invoked.");
    gtloglnWithTag("lichsword", "onReshape()...invoked.");

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);// set clear color value.
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
    //printf("onKeyboard()...invoked.");
}

/**
 * 鼠标响应
 */
void onMouse(int button, int state, int x, int y){
    // TODO
    gtloglnWithTagFormatInt4("Mouse Event: ", "button=%d,state=%d,x=%d,y=%d", button, state, x, y);
}

/**
 * 界面绘制事件
 */
void onDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);// use current color to clear window.
    //--------
    //glutStrokeLength(GLUT_STROKE_ROMAN, "Show me the Money!");
    glColor3f(1.0f, 0.0f, 0.0f);// change currnet color to red
    glRectf(-25.0f, 25.0f, 25.0f, -25.0f);// draw a rect with red color
    // TODO
    //--------
    //glFlush();// (Single Buffer)force flush screen buffer.
    glutSwapBuffers();// (Double Buffer)swap buffers.
}

/**
 * 主程序入口
 */
int main(int argc, char * argv[]){
    printf("main()...invoked.");
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
    glutCreateWindow("Video Game 3D Enginee Demo");
    // set reshape callback
    glutReshapeFunc(onReshape);
    // set keyboard callback
    glutKeyboardFunc(onKeyboard);
    // set mouse callback
    glutMouseFunc(onMouse);
    // set display callback
    glutDisplayFunc(onDisplay);
    // init recource 
    initGlobalRes();
    // start main loop
    glutMainLoop();

    return 0;
}
