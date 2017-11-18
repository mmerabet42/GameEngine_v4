#include "Shader.h"

#include "Application.h"

dn::Shader * dn::Shader::_usedShader = nullptr;

std::map<GLuint, dn::Shader *> dn::Shader::_shaders;
std::map<dn::Shader *, GLuint> dn::Shader::_shadersPointer;

dn::Shader::Shader(const std::string & p_vertexSrc, const std::string & p_fragmentSrc)
	: _vertexSrc(p_vertexSrc), _fragmentSrc(p_fragmentSrc)
{
	dn::Shader::AddShader(this);
}

std::string dn::Shader::vertexSource() const
{
	return this->_vertexSrc;
}

std::string dn::Shader::fragmentSource() const
{
	return this->_fragmentSrc;
}

GLint dn::Shader::GetAttrib(const std::string & p_name)
{
	return dn::Shader::GetShaderAttrib(this, p_name);
}

GLint dn::Shader::GetUniform(const std::string & p_name)
{
	return dn::Shader::GetShaderUniform(this, p_name);
}

bool dn::Shader::IsUsed() const
{
	return this == dn::Shader::GetUsedShader();
}

void dn::Shader::Use(const bool & p_use)
{
	(p_use ? dn::Shader::UseShader(this) : dn::Shader::UseShader(nullptr));
}

dn::Shader * dn::Shader::GetUsedShader()
{
	return dn::Shader::_usedShader;
}

void dn::Shader::UseShader(dn::Shader * p_shader)
{
	if (dn::Application::IsRunning())
	{
		if (p_shader)
			glUseProgram(dn::Shader::GetShaderId(p_shader));
		else if (!p_shader)
			glUseProgram(0);
	}
}

GLint dn::Shader::GetShaderAttrib(dn::Shader * p_shader, const std::string & p_name)
{
	GLint id = -1;
	if (p_shader)
	{
		if (p_shader->_attribs.count(p_name))
			return p_shader->_attribs.at(p_name);
		if (dn::Application::IsRunning())
		{
			p_shader->Use(true);
			id = glGetAttribLocation(dn::Shader::GetShaderId(p_shader), p_name.c_str());
		}
		if (id != -1)
			p_shader->_attribs.insert(std::make_pair(p_name, id));
	}

	return id;
}

GLint dn::Shader::GetShaderUniform(dn::Shader * p_shader, const std::string & p_name)
{
	GLint id = -1;
	if (p_shader)
	{
		if (p_shader->_uniforms.count(p_name))
			return p_shader->_uniforms.at(p_name);
		if (dn::Application::IsRunning())
		{
			p_shader->Use(true);
			id = glGetUniformLocation(dn::Shader::GetShaderId(p_shader), p_name.c_str());
		}
		if (id != -1)
			p_shader->_uniforms.insert(std::make_pair(p_name, id));
	}

	return id;
}

GLuint dn::Shader::GetShaderId(dn::Shader * p_shader)
{
	if (dn::Shader::_shadersPointer.count(p_shader))
		return dn::Shader::_shadersPointer.at(p_shader);
	return 0;
}

dn::Shader * dn::Shader::GetShaderPtr(const GLuint & p_shaderId)
{
	if (dn::Shader::_shaders.count(p_shaderId))
		return dn::Shader::_shaders.at(p_shaderId);
	return nullptr;
}

void dn::Shader::AddShader(dn::Shader * p_shader)
{
	if (dn::Application::IsRunning())
		dn::Shader::AddGLshader(p_shader);
	else
		dn::Shader::_shadersToCreate.push_back(p_shader);
}

GLuint dn::Shader::CreateShader(const GLenum & p_shaderType, const char * p_src)
{
	GLuint shaderId = glCreateShader(p_shaderType);
	glShaderSource(shaderId, 1, &p_src, nullptr);
	glCompileShader(shaderId);

	GLint status;
	GLchar log[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
	if (!status)
		dn::Application::ExitFailure("Shader failed to compile : " + std::string(log));
	return shaderId;
}

GLuint dn::Shader::CreateProgram(const std::string & p_vertexSrc, const std::string & p_fragmentSrc)
{
	GLuint programId = glCreateProgram();
	GLuint vertexId = dn::Shader::CreateShader(GL_VERTEX_SHADER, p_vertexSrc.c_str());
	GLuint fragmentId = dn::Shader::CreateShader(GL_FRAGMENT_SHADER, p_fragmentSrc.c_str());

	glAttachShader(programId, vertexId);
	glAttachShader(programId, fragmentId);
	glLinkProgram(programId);

	glDetachShader(programId, vertexId);
	glDeleteShader(vertexId);

	glDetachShader(programId, fragmentId);
	glDeleteShader(fragmentId);

	return programId;
}

void dn::Shader::AddGLshader(dn::Shader * p_shader)
{
	if (dn::Application::IsRunning())
	{
		GLuint programId = dn::Shader::CreateProgram(p_shader->vertexSource(), p_shader->fragmentSource());
		dn::Shader::_shaders.insert(std::make_pair(programId, p_shader));
		dn::Shader::_shadersPointer.insert(std::make_pair(p_shader, programId));
	}
}

void dn::Shader::CreatePrograms()
{
	if (dn::Application::IsRunning())
	{
		for (size_t i = 0; i < dn::Shader::_shadersToCreate.size(); ++i)
		{
			dn::Shader::AddGLshader(dn::Shader::_shadersToCreate[i]);
		}
	}
}
