#pragma once

#include "opengl.h"

#include <vector>
#include <map>

namespace dn
{
	class Application;

	/*The shader is used to tell the GPU how a vertex must be drawn*/
	class Shader
	{
		friend class dn::Application;

	public:
		Shader(const std::string & p_vertexSrc, const std::string & p_fragmentSrc);

		std::string vertexSource() const;
		std::string fragmentSource() const;

		GLint GetAttrib(const std::string & p_name);
		GLint GetUniform(const std::string & p_name);

		bool IsUsed() const;
		void Use(const bool & p_use = true);

		static dn::Shader * GetUsedShader();
		static void UseShader(dn::Shader * p_shader);

		static GLint GetShaderAttrib(dn::Shader * p_shader, const std::string & p_name);
		static GLint GetShaderUniform(dn::Shader * p_shader, const std::string & p_name);

		static GLuint GetShaderId(dn::Shader * p_shader);
		static dn::Shader * GetShaderPtr(const GLuint & p_shaderId);

		static void AddShader(dn::Shader * p_shader);

		static GLuint CreateShader(const GLenum & p_shaderType, const char * p_src);
		static GLuint CreateProgram(const std::string & p_vertexSrc, const std::string & p_fragmentSrc);

	private:

		std::string _vertexSrc;
		std::string _fragmentSrc;

		std::map<std::string, GLint> _attribs;
		std::map<std::string, GLint> _uniforms;

		static dn::Shader * _usedShader;

		static std::vector<dn::Shader *> _shadersToCreate;

		static std::map<GLuint, dn::Shader *> _shaders;
		static std::map<dn::Shader *, GLuint> _shadersPointer;
		
		static void AddGLshader(dn::Shader * p_shader);

		static void CreatePrograms();
	};
}

