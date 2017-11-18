#include "Shape.h"

#include <cstdlib>

dn::Shape * dn::Shape::triangle = new dn::Shape({
	dn::Vertex(0, 0.5f, 0),
	dn::Vertex(0.5f, -0.5f, 0),
	dn::Vertex(-0.5f, -0.5f, 0)
}, { 0, 1, 2 });

dn::Shape * dn::Shape::cube = new dn::Shape({

	dn::Vertex(-0.5f, 0.5f, 0.5f,	0, 0),
	dn::Vertex(0.5f, 0.5f, 0.5f,	1, 0),
	dn::Vertex(0.5f, -0.5f, 0.5f,	1, 1),
	dn::Vertex(-0.5f, -0.5f, 0.5f,	0, 1),

	dn::Vertex(-0.5f, 0.5f, -0.5f,	0, 0),
	dn::Vertex(0.5f, 0.5f, -0.5f,	1, 0),
	dn::Vertex(0.5f, -0.5f, -0.5f,	1, 1),
	dn::Vertex(-0.5f, -0.5f, -0.5f,	0, 1)

}, {
	0, 1, 2, 3,
	2, 6, 5, 1,
	5, 4, 7, 6,
	7, 3, 0, 4
});

dn::Shape * dn::Shape::cubeForm = new dn::Shape({

	// FRONT FACE
	dn::Vertex(-0.5f, 0.5f, 0.5f,	0, 0),//0
	dn::Vertex(0.5f, 0.5f, 0.5f,	1, 0),//1
	dn::Vertex(-0.5f, -0.5f, 0.5f,	0, 1),//2
	dn::Vertex(0.5f, -0.5f, 0.5f,	1, 1),//3

	// BACK FACE
	dn::Vertex(0.5f, 0.5f, -0.5f,	0, 0),//4
	dn::Vertex(-0.5f, 0.5f, -0.5f,	1, 0),//5
	dn::Vertex(0.5f, -0.5f, -0.5f,	0, 1),//6
	dn::Vertex(-0.5f, -0.5f, -0.5f,	1, 1),//7

	// TOP FACE
	dn::Vertex(-0.5f, 0.5f, -0.5f,	0, 0),//8
	dn::Vertex(0.5f, 0.5f, -0.5f,	1, 0),//9
	dn::Vertex(-0.5f, 0.5f, 0.5f,	0, 1),//10
	dn::Vertex(0.5f, 0.5f, 0.5f,	1, 1),//11

	// BOTTOM FACE
	dn::Vertex(0.5f, -0.5f, -0.5f,	0, 0),//12
	dn::Vertex(-0.5f, -0.5f, -0.5f,	1, 0),//13
	dn::Vertex(0.5f, -0.5f, 0.5f,	0, 1),//14
	dn::Vertex(-0.5f, -0.5f, 0.5f,	1, 1),//15

	// LEFT FACE
	dn::Vertex(-0.5f, 0.5f, -0.5f,	0, 0),//16
	dn::Vertex(-0.5f, 0.5f, 0.5f,	1, 0),//17
	dn::Vertex(-0.5f, -0.5f, -0.5f,	0, 1),//18
	dn::Vertex(-0.5f, -0.5f, 0.5f,	1, 1),//19

	// RIGHT FACE
	dn::Vertex(0.5f, 0.5f, 0.5f,	0, 0),//20
	dn::Vertex(0.5f, 0.5f, -0.5f,	1, 0),//21
	dn::Vertex(0.5f, -0.5f, 0.5f,	0, 1),//22
	dn::Vertex(0.5f, -0.5f, -0.5f,	1, 1)//23
	
}, {
	// FRONT FACE
	0, 1, 2, 1, 2, 3,
	// BACK FACE
	4, 5, 6, 5, 6, 7,
	// TOP FACE
	8, 9, 10, 9, 10, 11,
	// BOTTOM FACE
	12, 13, 14, 13, 14, 15,
	// LEFT FACE
	16, 17, 18, 17, 18, 19,
	// RIGHT FACE
	20, 21, 22, 21, 22, 23
});

dn::Shape * dn::Shape::quad = new dn::Shape({
	dn::Vertex(-0.5f, 0.5f, 0,		0, 0),
	dn::Vertex(0.5f, 0.5f, 0,		1, 0),
	dn::Vertex(-0.5f, -0.5f, 0,		0, 1),
	dn::Vertex(0.5f, -0.5f, 0,		1, 1)
}, {
	0, 1, 2, 3
});

dn::Shape::Shape(const dn::VertexArray & p_vertices, const dn::IndiceArray & p_indices)
	: _vertices(p_vertices), _indices(p_indices)
{

}

dn::VertexArray dn::Shape::vertices() const
{
	return this->_vertices;
}

dn::IndiceArray dn::Shape::indices() const
{
	return this->_indices;
}

dn::Shape * dn::Shape::random(const size_t & p_verticesNumber, const float & p_radius)
{
	dn::VertexArray vertices;
	dn::IndiceArray indices;

	for (int i = 0; i < p_verticesNumber; ++i)
	{
		vertices.push_back(
			dn::Vertex(
				dn::Random(-p_radius, p_radius),
				dn::Random(-p_radius, p_radius),
				dn::Random(-p_radius, p_radius)));
		indices.push_back((GLuint)i);
	}

	return new dn::Shape(vertices, indices);
}
