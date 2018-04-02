#include "transform.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

transform::transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scal) 
	: _position(pos), _rotation(rot), _scale(scal) 
{}


void transform::apply_all() {
	apply_translate();
	apply_rotation();
	apply_scale();
}

void transform::apply_translate() {
	glTranslatef(_position.x, _position.y, _position.z); // translate	
}

void transform::apply_rotation() {
	glRotatef(_rotation.x, 1.0, 0.0, 0.0); // rotate
	glRotatef(_rotation.y, 0.0, 1.0, 0.0);
	glRotatef(_rotation.z, 0.0, 0.0, 1.0);	
}

void transform::apply_scale() {
	glScalef(_scale.x, _scale.y, _scale.z); // scale
}
void transform::apply_inverse_scale() {
	if(_scale.x != 0 || _scale.y != 0 || _scale.z != 0)
		glScalef(1 / _scale.x, 1 / _scale.y, 1 / _scale.z); // scale
}

glm::vec3 transform::get_position() { return _position; }
glm::vec3 transform::get_rotation() { return _rotation; }
glm::vec3 transform::get_scale() { return _scale; }

void transform::set_position(glm::vec3 pos) { _position = pos; }
void transform::set_rotation(glm::vec3 rot) { _rotation = rot; }
void transform::set_scale(glm::vec3 scl) { _scale = scl; }

std::ostream& operator<<(std::ostream& os, const transform& t) {
	os << "T: (" << t._position.x << ", " << t._position.y << ", " << t._position.z << ")" << std::endl;
	os << "R: (" << t._rotation.x << ", " << t._rotation.y << ", " << t._rotation.z << ")" << std::endl;
	os << "S: (" << t._scale.x << ", " << t._scale.y << ", " << t._scale.z << ")" << std::endl;
	return os;
}
