#pragma once

#include "Object.h"

namespace dn
{
	class MeshRenderer;
	class Transform;

	class GameObject : public dn::Object
	{
	public:
		GameObject();


	private:

		dn::MeshRenderer * _mesh;
		dn::Transform * _transform;

	};
}

