#include "Transform.h"

dn::Transform::Transform(dn::Transform * p_parent, const glm::vec3 & p_position, const glm::vec3 & p_rotation, const glm::vec3 & p_scale)
	: Component(nullptr, "Transform"), _parent(p_parent), _position(p_position), _rotation(p_rotation), _scale(p_scale), _positionRef(true), _scaleRef(true), _rotationRef(true)
{

}

dn::Transform::Transform(dn::Transform * p_parent, const GLfloat & p_x, const GLfloat & p_y, const GLfloat & p_z, const GLfloat & p_xr, const GLfloat & p_yr, const GLfloat & p_zr, const GLfloat & p_xs, const GLfloat & p_ys, const GLfloat & p_zs)
	: Transform(p_parent, glm::vec3(p_x, p_y, p_z), glm::vec3(p_xr, p_yr, p_zr), glm::vec3(p_xs, p_ys, p_zs))
{

}

void dn::Transform::Start()
{

}

void dn::Transform::Update()
{

}

dn::Transform * dn::Transform::parent() const
{
	return this->_parent;
}

dn::Transform const * dn::Transform::parent()
{
	return this->_parent;
}

void dn::Transform::SetParent(dn::Transform * p_parent)
{
	this->_parent = p_parent;
}

glm::vec3 dn::Transform::position() const
{
	return this->_position;
}

glm::vec3 & dn::Transform::position()
{
	this->_positionRef = true;
	return this->_position;
}

glm::vec3 dn::Transform::worldPosition()
{
	glm::vec3 a;
	glm::decompose(this->ParentModelMatrix(), glm::vec3(), glm::quat(), a, glm::vec3(), glm::vec4());
	return (a);
}

dn::Quaternion dn::Transform::rotation() const
{
	return this->_rotation;
}

dn::Quaternion & dn::Transform::rotation()
{
	this->_rotationRef = true;
	return this->_rotation;
}

dn::Quaternion dn::Transform::worldRotation()
{
	glm::quat a;
	glm::decompose(this->ParentModelMatrix(), glm::vec3(), a, glm::vec3(), glm::vec3(), glm::vec4());
	return (glm::conjugate(a));
}

glm::vec3 dn::Transform::scale() const
{
	return this->_scale;
}

glm::vec3 & dn::Transform::scale()
{
	this->_scaleRef = true;
	return this->_scale;
}

glm::vec3 dn::Transform::worldScale()
{
	glm::vec3 a;
	glm::decompose(this->ParentModelMatrix(), a, glm::quat(), glm::vec3(), glm::vec3(), glm::vec4());
	return (a);
}

glm::mat4 dn::Transform::ParentModelMatrix()
{
	if (this->_parent)
		return this->_parent->ParentModelMatrix() * this->ModelMatrix();
	return this->ModelMatrix();
}

glm::mat4 dn::Transform::ModelMatrix()
{
	return this->TranslationMatrix() * this->RotationMatrix() * this->ScaleMatrix();
}

glm::mat4 dn::Transform::TranslationMatrix()
{
	if (this->_positionRef)
	{
		this->_positionRef = false;
		this->_translationMat = glm::translate(this->_position);
	}
	return this->_translationMat;
}

glm::mat4 dn::Transform::RotationMatrix()
{
	return this->_rotation.ToMatrix4();
}

glm::mat4 dn::Transform::ScaleMatrix()
{
	if (this->_scaleRef)
	{
		this->_scaleRef = false;
		this->_scaleMat = glm::scale(this->_scale);
	}
	return this->_scaleMat;
}

glm::vec3 dn::Transform::forward()
{
	return this->RotationMatrix() * glm::vec4(0, 0, -1, 0);
}

glm::vec3 dn::Transform::right()
{
	return this->RotationMatrix() * glm::vec4(1, 0, 0, 0);
}

glm::vec3 dn::Transform::up()
{
	return this->RotationMatrix() * glm::vec4(0, 1, 0, 0);
}

