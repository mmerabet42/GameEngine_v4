#include "Camera.h"

#include "Object.h"
#include "Transform.h"

dn::Camera * dn::Camera::main = nullptr;

dn::Camera::Camera(const float & p_fov, const float & p_near, const float & p_far, const float & p_aspectRatio)
	: Component(nullptr, "Camera"), _fov(p_fov), _near(p_near), _far(p_far), _aspectRatio(p_aspectRatio), _projectionChanged(true), _positionSave(0, 0, 0), _rotationSave(0, 0, 0)
{
	dn::Camera::main = this;
}

glm::mat4 dn::Camera::ViewMatrix()
{
	dn::Transform * objectTransform = this->object()->GetComponent<dn::Transform>();
	if (objectTransform)
	{
		if (this->_positionSave != objectTransform->position() || this->_rotationSave != objectTransform->rotation().eulerAngles())
		{
			this->_positionSave = objectTransform->position();
			this->_rotationSave = objectTransform->rotation().eulerAngles();
			this->_viewMatrix = glm::lookAt(objectTransform->position(), objectTransform->position() + objectTransform->forward(), objectTransform->up());
		}
	}
	return this->_viewMatrix;
}

glm::mat4 dn::Camera::ProjectionMatrix()
{
	if (this->_projectionChanged)
	{
		this->_projectionChanged = false;
		this->_projectionMat = glm::perspective(this->_fov, this->_aspectRatio, this->_near, this->_far);
	}
	return this->_projectionMat;
}

glm::mat4 dn::Camera::ViewProjectionMatrix()
{
	return this->ProjectionMatrix() * this->ViewMatrix();
}

void dn::Camera::Start()
{

}

void dn::Camera::Update()
{

}

float dn::Camera::fieldOfView() const
{
	return this->_fov;
}

float & dn::Camera::fieldOfView()
{
	this->_projectionChanged = true;
	return this->_fov;
}

void dn::Camera::SetFieldOfView(const float & p_fov)
{
	this->_projectionChanged = true;
	this->_fov = p_fov;
}

float dn::Camera::nearPlane() const
{
	return this->_near;
}

float & dn::Camera::nearPlane()
{
	this->_projectionChanged = true;
	return this->_near;
}

void dn::Camera::SetNear(const float & p_near)
{
	this->_projectionChanged = true;
	this->_near = p_near;
}

float dn::Camera::farPlane() const
{
	return this->_far;
}

float & dn::Camera::farPlane()
{
	this->_projectionChanged = true;
	return this->_far;
}

void dn::Camera::SetFar(const float & p_far)
{
	this->_projectionChanged = true;
	this->_far = p_far;
}

float dn::Camera::aspectRatio() const
{
	return this->_aspectRatio;
}

float & dn::Camera::aspectRatio()
{
	this->_projectionChanged = true;
	return this->_aspectRatio;
}

void dn::Camera::SetAspectRatio(const float & p_aspectRatio)
{
	this->_projectionChanged = true;
	this->_aspectRatio = p_aspectRatio;
}
