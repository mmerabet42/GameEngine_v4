#include "Vertex.h"

dn::Vertex::Vertex(const glm::vec3 & p_position, const glm::vec2 & p_texCoords)
	: position(p_position), texCoords(p_texCoords)
{
}

dn::Vertex::Vertex(const GLfloat & p_x, const GLfloat & p_y, const GLfloat & p_z, const GLfloat & p_tx, const GLfloat & p_ty)
	: Vertex(glm::vec3(p_x, p_y, p_z), glm::vec2(p_tx, p_ty))
{
}