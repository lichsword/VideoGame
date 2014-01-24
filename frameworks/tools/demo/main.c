#include "gltools.h"

#include "gtlog.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100


void initGlobalRes(void){}
void onReshape(int width, int height){
    printf("onReshape()...invoked.");
    gtlog();
}
void onKeyboard(unsigned char key, int x, int y){
    printf("onKeyboard()...invoked.");
}
void onMouse(int button, int state, int x, int y){}
void onDisplay(void){}

int main(int argc, char * argv[]){
    printf("main()...invoked.");
    // init
    glutInit(&argc, argv);
    // set display mode
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // set window size
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // set window pos
    glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
    // set window title
    glutCreateWindow("Video Game 3D Enginee Demo");
    // init recource 
    initGlobalRes();
    // set reshape callback
    glutReshapeFunc(onReshape);
    // set keyboard callback
    glutKeyboardFunc(onKeyboard);
    // set mouse callback
    glutMouseFunc(onMouse);
    // set display callback
    glutDisplayFunc(onDisplay);
    // start main loop
    glutMainLoop();

    return 0;
}
