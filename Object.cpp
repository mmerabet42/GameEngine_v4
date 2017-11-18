#include "Object.h"

#include "Component.h"

dn::Object::Object(const std::string & p_name)
	: _name(p_name), _active(true), _running(false)
{

}

dn::Object::~Object()
{
	for (std::map<std::string, dn::Component *>::iterator it = this->_components.begin(); it != this->_components.end(); ++it)
		if (it->second)
			delete it->second;
	this->_components.clear();
}

bool dn::Object::active() const
{
	return this->_active;
}

void dn::Object::SetActive(const bool & p_active)
{
	this->_active = p_active;
}

std::string dn::Object::name() const
{
	return this->_name;
}

void dn::Object::SetName(const std::string & p_name)
{
	this->_name = p_name;
}

void dn::Object::Start()
{
	this->_running = true;
	for (std::map<std::string, dn::Component *>::iterator it = this->_components.begin(); it != this->_components.end(); ++it)
		if (it->second && it->second->active())
			it->second->Start();
}
#include "MeshRenderer.h"
void dn::Object::Update()
{
	for (std::map<std::string, dn::Component *>::iterator it = this->_components.begin(); it != this->_components.end(); ++it)
		if (it->second && it->second->active())
			it->second->Update();
}
