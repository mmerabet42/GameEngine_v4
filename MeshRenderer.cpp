#include "MeshRenderer.h"

#include "Application.h"
#include "Window.h"

#include "Camera.h"

#include "Object.h"
#include "Transform.h"

#include <thread>

dn::MeshRenderer::MeshRenderer(dn::Shape * p_shape, dn::Shader * p_shader, const GLenum & p_drawMode)
	: Component(nullptr, "MeshRenderer"), _shape(p_shape), _shader(p_shader), _material(new dn::Material(glm::vec4(1, 1, 1, 1))), _drawMode(p_drawMode), _rendererGenerated(false), _transformUni(-1), _viewProjectionUni(-1), _colorUni(-1), _texUni(-1)
{

}

dn::Shape * dn::MeshRenderer::shape() const
{
	return this->_shape;
}

void dn::MeshRenderer::SetShape(dn::Shape * p_shape)
{
	this->_shape = p_shape;
	this->UpdateRenderer();
}

dn::Shader * dn::MeshRenderer::shader() const
{
	return this->_shader;
}

void dn::MeshRenderer::SetShader(dn::Shader * p_shader)
{
	this->_shader = p_shader;
	this->UpdateUniforms();
	this->UpdateRenderer();
}

dn::Material * dn::MeshRenderer::material() const
{
	return this->_material;
}

dn::Material * dn::MeshRenderer::material()
{
	return this->_material;
}

void dn::MeshRenderer::SetMaterial(dn::Material * p_material)
{
	this->_material = p_material;
}

void dn::MeshRenderer::Start()
{
	if (!this->_rendererGenerated)
	{
		this->_rendererGenerated = true;
		this->GenerateRenderer();
	}
	this->UpdateUniforms();
	this->UpdateRenderer();
}

void dn::MeshRenderer::Update()
{
	if (this->_shape)
	{
		if (this->_shader)
		{
			dn::Transform * objectTransform = this->object()->GetComponent<dn::Transform>();
			if (this->_colorUni != -1 && this->_material)
				glUniform4f(this->_colorUni, this->_material->color().x, this->_material->color().y, this->_material->color().z, this->_material->color().w);
			if (this->_transformUni != -1 && objectTransform)
				glUniformMatrix4fv(this->_transformUni, 1, GL_FALSE, &objectTransform->ParentModelMatrix()[0][0]);
			if (this->_viewProjectionUni != -1 && dn::Camera::main)
				glUniformMatrix4fv(this->_viewProjectionUni, 1, GL_FALSE, &dn::Camera::main->ViewProjectionMatrix()[0][0]);
		}

		glBindVertexArray(this->_vao);

		if (this->_material && this->_material->texture() && this->_texUni != -1)
		{
			glUniform1i(this->_texUni, GL_TEXTURE0);
			this->_material->texture()->Use();
		}

		glDrawElements(this->_drawMode, this->_shape->indices().size(), GL_UNSIGNED_INT, (void *)(0));

		if (this->_material && this->_material->texture())
			this->_material->texture()->Use(false);
	}
}

void dn::MeshRenderer::GenerateRenderer()
{
	glGenVertexArrays(1, &this->_vao);
	glGenBuffers(SIZE_VB, this->_vbos);
}

void dn::MeshRenderer::UpdateRenderer()
{
	if (!dn::Application::IsRunning())
		return;

	if (this->_shape)
	{
		glBindVertexArray(this->_vao);

		glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[VERTEX_VB]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(dn::Vertex) * this->_shape->vertices().size(), this->_shape->vertices().data(), GL_STATIC_DRAW);

		if (this->_shader)
		{
			glEnableVertexAttribArray(this->_shader->GetAttrib("position"));
			glVertexAttribPointer(this->_shader->GetAttrib("position"), 3, GL_FLOAT, false, sizeof(dn::Vertex), (void*)(0));

			glEnableVertexAttribArray(this->_shader->GetAttrib("texCoords"));
			glVertexAttribPointer(this->_shader->GetAttrib("texCoords"), 2, GL_FLOAT, false, sizeof(dn::Vertex), (void*)(3 * sizeof(GLfloat)));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_vbos[INDICE_VB]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->_shape->indices().size(), this->_shape->indices().data(), GL_STATIC_DRAW);
		}
		glBindVertexArray(0);
	}
}

void dn::MeshRenderer::UpdateUniforms()
{
	if (this->_shader && dn::Application::IsRunning())
	{
		this->_transformUni = this->_shader->GetUniform("transform");
		this->_viewProjectionUni = this->_shader->GetUniform("viewProjection");
		this->_colorUni = this->_shader->GetUniform("color");
		this->_texUni = this->_shader->GetUniform("tex");
	}
}