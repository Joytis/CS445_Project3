#include <ctime> // Very simple delta time calculation. 
#include <iostream>

#include <glm/gtx/rotate_vector.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtx/vector_angle.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtx/string_cast.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include "glutscene.hpp"
#include "basic_shapes.hpp"

glutscene::glutscene(glm::vec2 c, glm::i32vec2 r) :
	_raster_size(r), _canvas_size(c),
    _curr_ticks(clock()), _eye(5.0f, 3.0f, 5.0f), _look_at(0.0f),
    _fsm(states::first_person)
{
    // Swap modes to revolve
    _fsm.add_transition(states::first_person, states::revolve, triggers::space_bar_down);
    _fsm.add_transition(states::first_person, states::revolve, triggers::c_down);

    _fsm.add_transition(states::first_person, states::first_person_look, triggers::revolve_down);
    _fsm.add_transition(states::first_person_look, states::first_person, triggers::revolve_up);

    // Swap modes to first person
    _fsm.add_transition(states::revolve, states::first_person, triggers::space_bar_down);
    _fsm.add_transition(states::revolve, states::first_person, triggers::c_down);

    // Different dolley states. 
    _fsm.add_transition(states::revolve, states::revolve_dolley, triggers::dolley_down);
    _fsm.add_transition(states::revolve_dolley, states::revolve, triggers::dolley_up);
    _fsm.add_transition(states::revolve, states::revolve_revolve, triggers::revolve_down);
    _fsm.add_transition(states::revolve_revolve, states::revolve, triggers::revolve_up);
    _fsm.add_transition(states::revolve, states::revolve_pan, triggers::pan_down);
    _fsm.add_transition(states::revolve_pan, states::revolve, triggers::pan_up);

    memset(key_states, 0, sizeof(key_states));

    _first_person_str = "First Person Camera";
    _revolve_str = "Revolve Camera";
    _state_string = _first_person_str;
}

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
    // FOV, aspect ration, near clipping plane, far clipping plane. 
    gluPerspective(90, _raster_size.x / _raster_size.y, 0.1, 100);
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

    // Draw cute axis at bottom right. 
    glTranslatef(1, 1, 0);
    glPushMatrix(); // for draw_axes
    gluLookAt( _eye.x, _eye.y, _eye.z, // eye
               _look_at.x, _look_at.y, _look_at.z,  //look at
               0, 1, 0); // up
    glTranslatef(_eye.x, _eye.y, _eye.z);
    draw_axes(1.0f); // draw axes
    glPopMatrix(); // for axes
    glTranslatef(-0.75, 8.5, 0);

    // Print text to screen
    const char current_state_str[] = "Current Camera State: ";
    glColor3f(0.4f, 0.4f, 0.4f);
    glRasterPos2f(0.0f, 0.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char*>(current_state_str));
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char*>(_state_string));

    glPopMatrix(); // Pop MV matrix

    glMatrixMode(GL_PROJECTION); 
    glPopMatrix(); // Pop proj matrix

    // Draw text of current state. 
    // screen in an 18-point Helvetica font

}

void glutscene::display() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( _eye.x, _eye.y, _eye.z, // eye
               _look_at.x, _look_at.y, _look_at.z,  //look at
               0, 1, 0); // up
        
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
    key_states[key] = true;

    switch(key) {
        case 'c': {
            _fsm.set_trigger(triggers::c_down);
        } break;

        case 32: { // space
            _fsm.set_trigger(triggers::space_bar_down);
        } break;
        
        case 27: {
            exit(1); 
        } break;
    }
}

void glutscene::keyboard_up(unsigned char key, int x, int y) {
    key_states[key] = false;
}

void glutscene::mouse(int button, int state, int x, int y) {

    bool should_reposition_mouse = false;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        should_reposition_mouse = true;
        _fsm.set_trigger(triggers::revolve_down);
    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        should_reposition_mouse = true;
        _fsm.set_trigger(triggers::revolve_up);
    }

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        should_reposition_mouse = true;
        _fsm.set_trigger(triggers::pan_down);
    }

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        should_reposition_mouse = true;
        _fsm.set_trigger(triggers::pan_up);
    }

    if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        should_reposition_mouse = true;
        _fsm.set_trigger(triggers::dolley_down);
    }

    if(button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
        should_reposition_mouse = true;
        _fsm.set_trigger(triggers::dolley_up);
    }

    if(should_reposition_mouse) {
        _mouse_pos.x = (float)x / _raster_size.x * _canvas_size.x;
        _mouse_pos.y = (float)(_raster_size.y - y) / _raster_size.y * _canvas_size.y;        
    }

}

void glutscene::motion(int x, int y) {
	
	// mouse events are handled by OS, eventually. When using mouse in the raster window,
	//  it assumes top-left is the origin.
    // Note: the raster window created by GLUT assumes bottom-left is the origin.
	float newpos_x = (float)x / _raster_size.x * _canvas_size.x;
    float newpos_y = (float)(_raster_size.y - y) / _raster_size.y * _canvas_size.y;

    _mouse_offset.x = newpos_x -_mouse_pos.x;
    _mouse_offset.y = newpos_y -_mouse_pos.y;

    _mouse_pos.x = newpos_x;
    _mouse_pos.y = newpos_y;


    glutPostRedisplay();
}

void glutscene::menu(int value) {
    
}

void glutscene::do_motion(const glm::vec3& n, const glm::vec3& u, const glm::vec3& v) {
    // Check for key input. 
    static const float move_speed = 3.0f;
    if(key_states['w']) {
        _eye += -1.0f * n * move_speed * _delta_time;
        _look_at += -1.0f * n * move_speed * _delta_time;
    }
    if(key_states['a']) {
        _eye += -1.0f * u * move_speed * _delta_time;
        _look_at += -1.0f * u * move_speed * _delta_time;
    }
    if(key_states['s']) {
        _eye += n * move_speed * _delta_time;
        _look_at += n * move_speed * _delta_time;
    }
    if(key_states['d']) {
        _eye += u * move_speed * _delta_time;
        _look_at += u * move_speed * _delta_time;
    }
}

void glutscene::idle() {
    const static float look_speed = 20.0f;
    calc_delta_time();

    _fsm.update();

    auto n = glm::normalize(_eye - _look_at);
    auto u = glm::normalize(glm::cross(glm::vec3(0, 1, 0), n));
    auto v = glm::normalize(glm::cross(n, u));

    switch(_fsm.get_current_state()) {
        case states::first_person: {
            _state_string = _first_person_str;
            do_motion(n, u, v);
        } break;

        case states::first_person_look: {
            do_motion(n, u, v);

            auto old_look_at = _look_at;

            // move it to origin
            _look_at -= _eye;
            // rotate it
            _look_at = glm::rotate(_look_at,
                                   -1.0f * glm::radians(_mouse_offset.x) * look_speed,
                                   v);

            _look_at = glm::rotate(_look_at,
                                   glm::radians(_mouse_offset.y) * look_speed,
                                   u);
            // move it back
            _look_at += _eye;    


        } break;
        case states::revolve: {
            _state_string = _revolve_str;
        } break;

        case states::revolve_dolley: {

        } break;

        case states::revolve_revolve: {

        } break;

        case states::revolve_pan: {

        } break;

    }

    // glutWarpPointer( _raster_size.x / 2 , _raster_size.y / 2 );
    _mouse_offset = glm::vec2(0.0f); // Zero out the mouse offset. We should only use it once. 

    glutPostRedisplay();
}
