#include <iostream>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <glm/glm.hpp>


#include "glutscene.hpp"
#include "basic_shapes.hpp"

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
    glm::i32vec2 raster_size(800, 600);
    glm::vec2 canvas_size(10.0f, 10.0f);


    scene = new glutscene(canvas_size, raster_size);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(raster_size.x, raster_size.y);
    glutCreateWindow("Dope-Camera Stuff My Dude");

    // Callbacks
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(motion);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}