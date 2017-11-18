#pragma once

#include "Component.h"
#include "Vertex.h"
#include "Shader.h"
#include "Shape.h"
#include "Material.h"

#include <vector>

namespace dn
{
	/*Component that can be added to an object, it makes the object drawable and representable with a shape*/
	class MeshRenderer : public dn::Component
	{
	public:
		MeshRenderer(dn::Shape * p_shape = nullptr, dn::Shader * p_shader = nullptr, const GLenum & p_drawMode = GL_TRIANGLES);

		dn::Shape * shape() const;
		void SetShape(dn::Shape * p_shape);

		dn::Shader * shader() const;
		void SetShader(dn::Shader * p_shader);

		dn::Material * material() const;
		dn::Material * material();
		void SetMaterial(dn::Material * p_material);

		void Start();
		void Update();

	private:
		enum { VERTEX_VB, INDICE_VB, SIZE_VB };

		bool _rendererGenerated;

		GLint _transformUni;
		GLint _viewProjectionUni;
		GLint _colorUni;
		GLint _texUni;

		GLuint _vao;
		GLuint _vbos[SIZE_VB];

		GLenum _drawMode;

		dn::Shader * _shader;

		dn::Shape * _shape;
		dn::Material * _material;

		void GenerateRenderer();
		void UpdateRenderer();
		void UpdateUniforms();
	};
}

