#include "color_tint.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

glm::vec3 color_tint::get(color_tint::colors c) {
	
	switch(c) {
		case color_tint::colors::red: 
			return glm::vec3(1.0, 0.0, 0.0);
		case color_tint::colors::orange: 
			return glm::vec3(1.0, 0.64, 0.0);
		case color_tint::colors::yellow: 
			return glm::vec3(1.0, 0.95, 0.0);
		case color_tint::colors::green: 
			return glm::vec3(0.0, 1.0, 0.0);
		case color_tint::colors::blue: 
			return glm::vec3(0.0, 0.0, 1.0);
		case color_tint::colors::purple: 
			return glm::vec3(0.56, 0.0, 0.8);
	}
}