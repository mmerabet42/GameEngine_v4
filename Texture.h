#pragma once

#include "opengl.h"
#include <map>
#include <vector>

namespace dn
{
	class Application;
	class Image;

	class Texture
	{
		friend class dn::Application;

	public:
		Texture(dn::Image * p_image);
		Texture(const std::string & p_path);

		dn::Image * image() const;
		void SetImage(dn::Image * p_image);

		void Use(const bool & p_use = true);

		static GLuint GetTextureId(dn::Texture * p_texture);
		static dn::Texture * GetTexturePtr(const GLuint & p_texId);

		static void UseTexture(dn::Texture * p_texture);

		static void AddTexture(dn::Texture * p_texture);

	private:

		dn::Image * _image;
		GLuint _texture;

		static void AddGLtexture(dn::Texture * p_texture);
		static void CreateTextures();

		static std::vector<dn::Texture *> _texturesToCreate;
		static std::map<dn::Texture *, GLuint> _textures;
		static std::map<GLuint, dn::Texture *> _texturesPointer;
	};
}

