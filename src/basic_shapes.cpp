#include "basic_shapes.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <cmath>

void basic_shapes::circle() {
	// Draw circle of radius 1
	glBegin(GL_TRIANGLE_FAN);

	for (int i = 0; i < 180; i++)
	{
		float x = 0.5 * cos(i);
		float y = 0.5 * sin(i);
		glVertex2f(x, y);

		x = 0.5 * cos(i + 0.1);
		y = 0.5 * sin(i + 0.1);
		glVertex2f(x, y);
	}
	glEnd();

}

void basic_shapes::square() {
	glBegin(GL_QUADS);
	glVertex2f(-0.5, -0.5);
	glVertex2f( 0.5, -0.5);
	glVertex2f( 0.5,  0.5);
	glVertex2f(-0.5,  0.5);
	glEnd();
}