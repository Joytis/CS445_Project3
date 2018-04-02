#pragma once
#include <vector>
#include <ctime>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif


#include <glm/glm.hpp>


class glutscene {

private:

	glm::i32vec2 _raster_size;
	glm::vec2 _canvas_size;
	glm::vec2 _mouse_pos;

	clock_t _prev_ticks;
	clock_t _curr_ticks;
	float _delta_time;

	glm::vec2 _current_rotation;

	void draw_gui();
	static void draw_axes(float scale);
	
public:
	glutscene(glm::vec2 c, glm::i32vec2 r);
	void calc_delta_time();

	// OpenGL callback stuff. 
	void reshape(int w, int h);
	void display(void);
	void keyboard(unsigned char key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void motion(int x, int y);
	void menu(int value);
	void idle();
};