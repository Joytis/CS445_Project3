#pragma once
#include <glm/vec3.hpp>

class color_tint {
public:
	enum class colors {
		red, 
		orange, 
		yellow, 
		green, 
		blue,
		purple
	};

	static glm::vec3 get(colors c);
};