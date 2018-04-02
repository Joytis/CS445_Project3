#pragma once

#include <iostream>

#include <glm/vec3.hpp>

class transform {
	glm::vec3 _position; // applies to children. 
	glm::vec3 _rotation; // applies to children
	glm::vec3 _scale; // We don't have parents enforce scale. 

public:
	transform(glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0), 
			  glm::vec3 rot = glm::vec3(0.0, 0.0, 0.0), 
			  glm::vec3 scal = glm::vec3(1.0, 1.0, 1.0));

	void apply_translate();
	void apply_rotation();
	void apply_scale();
	void apply_inverse_scale();
	void apply_all();

	void apply_gl_matrix();

	glm::vec3 get_position();
	glm::vec3 get_rotation();
	glm::vec3 get_scale();

	void set_position(glm::vec3 rot);
	void set_rotation(glm::vec3 rot);
	void set_scale(glm::vec3 rot);

	friend std::ostream& operator<<(std::ostream& os, const transform& t);
};