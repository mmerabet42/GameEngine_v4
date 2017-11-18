#include "Quaternion.h"

dn::Quaternion::Quaternion(const glm::vec3 & p_eulerAngles)
	: _quat(p_eulerAngles), _eulerAngles(p_eulerAngles), _eulerModified(false), _matUpdate(true)
{

}

dn::Quaternion::Quaternion(const glm::quat & p_quat)
	: Quaternion(glm::eulerAngles(p_quat))
{

}

dn::Quaternion::Quaternion(const float & p_eulerX, const float & p_eulerY, const float & p_eulerZ)
	: Quaternion(glm::vec3(p_eulerX, p_eulerY, p_eulerZ))
{

}

glm::quat dn::Quaternion::quat()
{
	if (this->_eulerModified)
	{
		this->_eulerModified = false;
		this->_matUpdate = true;
		this->_quat = glm::quat(this->_eulerAngles);
	}
	return this->_quat;
}

glm::mat4 dn::Quaternion::ToMatrix4()
{
	if (this->_matUpdate)
	{
		this->_quatToMat = glm::toMat4(this->quat());
		this->_matUpdate = false;
	}
	return this->_quatToMat;
}

glm::vec3 dn::Quaternion::eulerAngles() const
{
	return this->_eulerAngles;
}

glm::vec3 & dn::Quaternion::eulerAngles()
{
	this->_eulerModified = true;
	this->_matUpdate = true;
	return this->_eulerAngles;
}

void dn::Quaternion::SetEuler(const glm::vec3 & p_eulerAngles)
{
	this->_quat = glm::quat(p_eulerAngles);
	this->_eulerAngles = p_eulerAngles;
	this->_matUpdate = true;
}

void dn::Quaternion::SetEuler(const float & p_eulerX, const float & p_eulerY, const float & p_eulerZ)
{
	this->SetEuler(glm::vec3(p_eulerX, p_eulerY, p_eulerZ));
}