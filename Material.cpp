#include "Material.h"

dn::Material * dn::Material::defaultMaterial = new dn::Material(glm::vec4(1, 1, 1, 1));

dn::Material::Material(const glm::vec4 & p_color)
	: _color(p_color), _texture(nullptr)
{

}

glm::vec4 dn::Material::color() const
{
	return this->_color;
}

glm::vec4 & dn::Material::color()
{
	return this->_color;
}

void dn::Material::SetColor(const glm::vec4 & p_color)
{
	this->_color = p_color;
}

dn::Texture * dn::Material::texture() const
{
	return this->_texture;
}

dn::Texture *& dn::Material::texture()
{
	return this->_texture;
}

void dn::Material::SetTexture(dn::Texture * p_texture)
{
	this->_texture = p_texture;
}
