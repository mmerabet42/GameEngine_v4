#pragma once

#include "opengl.h"
#include "Texture.h"

namespace dn
{
	/*A material tells the MeshRenderer component of an object how to be colored*/
	class Material
	{
	public:
		Material(const glm::vec4 & p_color = glm::vec4(1, 1, 1, 1));

		glm::vec4 color() const;
		glm::vec4 & color();
		void SetColor(const glm::vec4 & p_color);

		dn::Texture * texture() const;
		dn::Texture *& texture();
		void SetTexture(dn::Texture * p_texture);

		static dn::Material * defaultMaterial;

	private:

		glm::vec4 _color;
		dn::Texture * _texture;
	};
}

