#include <ctime> // Very simple delta time calculation. 

#include "glutscene.hpp"
#include "basic_shapes.hpp"

glutscene::glutscene(glm::vec2 c, glm::i32vec2 r) :
	_raster_size(r), _canvas_size(c),
    _curr_ticks(clock()), _current_rotation(0.0f)
{}

void glutscene::calc_delta_time() {
	_curr_ticks = clock();
	_delta_time = ((float)(_curr_ticks - _prev_ticks)) / CLOCKS_PER_SEC;
	_prev_ticks = _curr_ticks;
}

void glutscene::reshape(int w, int h) {
	_raster_size.x = w;
    _raster_size.y = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // FOW, aspect ration, near clipping plane, far clipping plane. 
    gluPerspective(45, _raster_size.x/ _raster_size.y, 0.1, 100);

    glViewport(0, 0, w, h);
}

void glutscene::draw_axes(float scale) {
    // Draws the cs
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLineWidth(2.5f);
    glScalef(scale, scale, scale);
    glBegin(GL_LINES);
//axis x
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.3f, 0.0f, 0.0f);
//text x
    glVertex3f(0.4f, 0.05f, 0.0f);
    glVertex3f(0.5f, -0.05f, 0.0f);
    glVertex3f(0.4f, -0.05f, 0.0f);
    glVertex3f(0.5f, 0.05f, 0.0f);
//axis y
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.3f, 0.0f);
//text y
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.0f, 0.4f, 0.0f);
    glVertex3f(-0.05f, 0.55f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.05f, 0.55f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
//axis z
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.3f);
//text z
    glVertex3f(-0.025f, 0.025f, 0.4f);
    glVertex3f(0.025f, 0.025f, 0.4f);
    glVertex3f(0.025f, 0.025f, 0.4f);
    glVertex3f(-0.025f, -0.025f, 0.4f);
    glVertex3f(-0.025f, -0.025f, 0.4f);
    glVertex3f(0.025f, -0.025f, 0.4f);
    glEnd();
    glLineWidth(1.0f);
    glPopMatrix();
    // End drawing the cs. 
}

void glutscene::draw_gui() {
    // Attempt GUI stuff. 
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); // Push a projection matrix
    glLoadIdentity(); // Load identity to reset display
    gluOrtho2D(0.0, _canvas_size.x, 0.0, _canvas_size.y);
    glViewport(0, 0, _raster_size.x, _raster_size.y);

    glMatrixMode(GL_MODELVIEW); 
    glPushMatrix(); // Push a MV matrix
    glLoadIdentity();
    glTranslatef(1, 1, 0);
    glRotatef(_current_rotation.x, 1, 0, 0);
    glRotatef(_current_rotation.y, 0, 1, 0);
    draw_axes(1.0f); // draw axes
    glPopMatrix(); // Pop MV matrix


    glMatrixMode(GL_PROJECTION); 
    glPopMatrix(); // Pop proj matrix


    // GUI stuff.     
}

void glutscene::display() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( 0, 0, 10, 0, 0, 0, 0, 1, 0);
    glRotatef(_current_rotation.x, 1, 0, 0);
    glRotatef(_current_rotation.y, 0, 1, 0);
        
    // Draws the grid we'll walk around on. 
    int size = 25;  // determining the grid size and the numbers of cells
    if(size%2 != 0) ++size;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    // glScalef(30.0f, 30.0f, 30.0f);
    glBegin(GL_LINES);
    for (int i =0; i<size+1; i++) {
        if(i == size / 2) {
            glColor3f(0.0f, 0.0f, 0.0f);
        } else {
            glColor3f(0.8f, 0.8f, 0.8f);
        }
        glVertex3f(-size/2.0f, 0.0f, -size/2.0f+i);
        glVertex3f(size/2.0f, 0.0f, -size/2.0f+i);
        glVertex3f(-size/2.0f+i, 0.0f, -size/2.0f);
        glVertex3f(-size/2.0f+i, 0.0f, size/2.0f);
    }
    glEnd();
    glPopMatrix();
    // End drawing grid. 

    draw_axes(10.0f);

    // Cube for testing. 
    glutSolidCube(1.0);

    draw_gui();

    glutSwapBuffers();
}

void glutscene::keyboard(unsigned char key, int x, int y) {

}

void glutscene::mouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // _mouse_pos.x = (float)x / _raster_size.x * _canvas_size.x;
        // _mouse_pos.y = (float)(_raster_size.y - y) / _raster_size.y * _canvas_size.y;
    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        // _mouse_pos.x = (float)x / _raster_size.x * _canvas_size.x;
        // _mouse_pos.y = (float)(_raster_size.y - y) / _raster_size.y * _canvas_size.y;
    }

}

void glutscene::motion(int x, int y) {
	
	// mouse events are handled by OS, eventually. When using mouse in the raster window,
	//  it assumes top-left is the origin.
    // Note: the raster window created by GLUT assumes bottom-left is the origin.
	// _mouse_pos.x = (float)x / _raster_size.x * _canvas_size.x;
    // _mouse_pos.y = (float)(_raster_size.y - y) / _raster_size.y * _canvas_size.y;

    glutPostRedisplay();
}

void glutscene::menu(int value) {
    
}

void glutscene::idle() {
	calc_delta_time();

	// calculate how much to rotate
	_current_rotation.y += 20.0f * _delta_time;

	glutPostRedisplay();
}
