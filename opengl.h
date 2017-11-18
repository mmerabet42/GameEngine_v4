#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtx\matrix_decompose.hpp>

#include <random>

#include <string>

namespace dn
{
	std::string ReadFile(const std::string &fileName);
	float Random(const float & p_min, const float & p_max);
}
