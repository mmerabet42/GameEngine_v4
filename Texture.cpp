#include "Texture.h"
#include "Image.h"

#include "Application.h"

std::vector<dn::Texture *> dn::Texture::_texturesToCreate;
std::map<dn::Texture *, GLuint> dn::Texture::_textures;
std::map<GLuint, dn::Texture *> dn::Texture::_texturesPointer;

dn::Texture::Texture(dn::Image * p_image)
	: _image(p_image)
{
	dn::Texture::AddTexture(this);
}

dn::Texture::Texture(const std::string & p_path)
	: Texture(new dn::Image(p_path))
{

}

dn::Image * dn::Texture::image() const
{
	return this->_image;
}

void dn::Texture::SetImage(dn::Image * p_image)
{
	this->_image = p_image;
}

void dn::Texture::Use(const bool & p_use)
{
	dn::Texture::UseTexture(p_use ? this : nullptr);
}

GLuint dn::Texture::GetTextureId(dn::Texture * p_texture)
{
	if (p_texture && dn::Texture::_textures.count(p_texture))
		return dn::Texture::_textures.at(p_texture);
	return 0;
}

dn::Texture * dn::Texture::GetTexturePtr(const GLuint & p_texId)
{
	if (dn::Texture::_texturesPointer.count(p_texId))
		return dn::Texture::_texturesPointer.at(p_texId);
	return nullptr;
}

void dn::Texture::UseTexture(dn::Texture * p_texture)
{
	if (dn::Application::IsRunning())
	{
		if (p_texture)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, dn::Texture::GetTextureId(p_texture));
		}
		else
			glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void dn::Texture::AddTexture(dn::Texture * p_texture)
{
	if (dn::Application::IsRunning())
		dn::Texture::AddGLtexture(p_texture);
	else
		dn::Texture::_texturesToCreate.push_back(p_texture);
}

void dn::Texture::AddGLtexture(dn::Texture * p_texture)
{
	if (dn::Application::IsRunning() && p_texture)
	{
		GLuint texId;
		glGenTextures(1, &texId);

		glBindTexture(GL_TEXTURE_2D, texId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, p_texture->_image->width(), p_texture->_image->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, p_texture->_image->pixels());

		glBindTexture(GL_TEXTURE_2D, 0);

		dn::Texture::_textures.insert(std::make_pair(p_texture, texId));
		dn::Texture::_texturesPointer.insert(std::make_pair(texId, p_texture));
	}
}

void dn::Texture::CreateTextures()
{
	if (dn::Application::IsRunning())
	{
		for (int i = 0; i < dn::Texture::_texturesToCreate.size(); ++i)
			dn::Texture::AddGLtexture(dn::Texture::_texturesToCreate[i]);
	}
}