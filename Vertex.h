#pragma once

#include "opengl.h"

namespace dn
{
	/*A vertex is defined by a vector*/
	class Vertex
	{
	public:
		Vertex(const glm::vec3 & p_position = glm::vec3(0, 0, 0), const glm::vec2 & p_texCoords = glm::vec2(0, 0));
		Vertex(const GLfloat & p_x, const GLfloat & p_y, const GLfloat & p_z,
			const GLfloat & p_tx = 0, const GLfloat & p_ty = 0);

		glm::vec3 position;
		glm::vec2 texCoords;
	};
}

