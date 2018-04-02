#pragma once
#include <vector>
#include <ctime>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <glm/glm.hpp>

#include "fsm/finite_state_system.hpp"

class glutscene {
public:
	enum class triggers : int32_t {
		space_bar_down = (1 << 0),
		c_down = (1 << 1),
		dolley_down = (1 << 2),
		dolley_up = (1 << 3),
		revolve_down = (1 << 4),
		revolve_up = (1 << 5),
		pan_up = (1 << 6),
		pan_down = (1 << 7),
	};
	ENABLE_BITMASK_OPERATORS(glutscene::triggers);

private:

	enum class states {
		first_person,
		first_person_look,
		revolve,
		revolve_dolley,
		revolve_revolve,
		revolve_pan,
	};

	glm::i32vec2 _raster_size;
	glm::vec2 _canvas_size;
	glm::vec2 _mouse_pos;
	glm::vec2 _mouse_offset;

	clock_t _prev_ticks;
	clock_t _curr_ticks;
	float _delta_time;

	glm::vec2 _current_rotation;
	glm::vec3 _look_at;
	glm::vec3 _eye;

	fsm::finite_state_system<states, triggers> _fsm; // state machine. 

	bool key_states[256];

	void draw_gui();
	static void draw_axes(float scale);
	void do_motion(const glm::vec3& n, const glm::vec3& u, const glm::vec3& v);

	
public:
	glutscene(glm::vec2 c, glm::i32vec2 r);
	void calc_delta_time();

	// OpenGL callback stuff. 
	void reshape(int w, int h);
	void display(void);
	void keyboard(unsigned char key, int x, int y);
	void keyboard_up(unsigned char key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void motion(int x, int y);
	void menu(int value);
	void idle();
};

