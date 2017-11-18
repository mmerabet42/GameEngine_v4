#pragma once

#include <vector>

#include "Vertex.h"
#include "opengl.h"

namespace dn
{
	typedef std::vector<dn::Vertex> VertexArray;
	typedef std::vector<GLuint> IndiceArray;

	/*A shape is defined by vertices and indices*/
	class Shape
	{
	public:
		Shape(const dn::VertexArray & p_vertices = {}, const dn::IndiceArray & p_indices = {});

		dn::VertexArray vertices() const;
		dn::IndiceArray indices() const;

		/*A simple triangle shape*/
		static dn::Shape * triangle;
		/*A simple cube shape*/
		static dn::Shape * cube;
		/*Cube borders*/
		static dn::Shape * cubeForm;
		/*A simple quad shape*/
		static dn::Shape * quad;
		/*A random shape, with vertices placed randomly*/
		static dn::Shape * random(const size_t & p_verticesNumber, const float & p_radius);

	private:

		dn::VertexArray _vertices;
		dn::IndiceArray _indices;

	};
}

