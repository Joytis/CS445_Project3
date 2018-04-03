#include <iostream>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <glm/glm.hpp>


#include "glutscene.hpp"

glutscene* scene;

// Doing 'pseudobinding' here so I don't have to use the boost library. 
void reshape(int w, int h)  {
    scene->reshape(w, h); 
}

void display()  {
    scene->display(); 
}
void keyboard(unsigned char key, int x, int y) {
    scene->keyboard(key, x, y); 
}
void keyboard_up(unsigned char key, int x, int y) {
    scene->keyboard_up(key, x, y); 
}

void mouse(int button, int state, int x, int y) {
    scene->mouse(button, state, x, y); 
}
void motion(int x, int y) {
    scene->motion(x, y); 
}
void idle() {
    scene->idle(); 
}

// TODO(clark): Hey. 

// NOTE(clark): This code isn't great. There's finite state machines everywhere, virtual calls, and 
//              whatever I thought of to try out some new design patterns. I had a blast making it!
int main(int argc, char *argv[]) {
    glm::i32vec2 raster_size(1024, 512);
    glm::vec2 canvas_size(10.0f, 10.0f);


    scene = new glutscene(canvas_size, raster_size);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(raster_size.x, raster_size.y);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Dope-Camera Stuff My Dude");



    // Other initialization
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // define ambient, diffuse and specular light components
    GLfloat lightAmb[] = {0.2, 0.1, 0.0, 1.0};
    GLfloat lightDiff[] = {1.0, 1.0, 0.0, 1.0};
    GLfloat lightSpec[] = {1.0, 1.0, 0.0, 1.0};
    // attach ambient, diffuse and specular to light0
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
    

    // define the material for surfaces
    GLfloat objAmb[] = {1.0, 1.0, 0.0, 1.0};
    GLfloat objDiff[] = {0.8, 0.2, 0.0, 1.0};
    GLfloat objSpec[] = {0.0, 1.0, 0.0, 1.0};
    GLfloat objExp = 40.0f;
    // add material
    glMaterialfv(GL_FRONT, GL_AMBIENT, objAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, objDiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, objSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, objExp);
    
    glEnable(GL_DEPTH_TEST);
    glClearColor (1.0f, 1.0f, 1.0f, 0.0f);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();

    // Callbacks
    // glutSetCursor(GLUT_CURSOR_NONE);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(motion);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}