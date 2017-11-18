#pragma once

#include "Component.h"
#include "opengl.h"
#include "Quaternion.h"

namespace dn
{
	/*Component that can be added to an object, it represent the position, rotation and scale of the object*/
	class Transform : public dn::Component
	{
	public:
		Transform(dn::Transform * p_parent = nullptr, const glm::vec3 & p_position = glm::vec3(0, 0, 0), const glm::vec3 & p_rotation = glm::vec3(0, 0, 0), const glm::vec3 & p_scale = glm::vec3(1, 1, 1));
		Transform(dn::Transform * p_parent, const GLfloat & p_x, const GLfloat & p_y, const GLfloat & p_z,
			const GLfloat & p_xr = 0, const GLfloat & p_yr = 0, const GLfloat & p_zr = 0,
			const GLfloat & p_xs = 1, const GLfloat & p_ys = 1, const GLfloat & p_zs = 1);

		void Start();
		void Update();

		dn::Transform * parent() const;
		dn::Transform const * parent();
		void SetParent(dn::Transform * p_parent);

		glm::vec3 position() const;
		glm::vec3 & position();
		glm::vec3 worldPosition();
		
		dn::Quaternion rotation() const;
		dn::Quaternion & rotation();
		dn::Quaternion worldRotation();

		glm::vec3 scale() const;
		glm::vec3 & scale();
		glm::vec3 worldScale();

		glm::mat4 ParentModelMatrix();
		glm::mat4 ModelMatrix();

		glm::mat4 TranslationMatrix();
		glm::mat4 RotationMatrix();
		glm::mat4 ScaleMatrix();

		glm::vec3 forward();
		glm::vec3 right();
		glm::vec3 up();

	private:

		dn::Transform * _parent;

		bool _positionRef;
		bool _scaleRef;
		bool _rotationRef;

		glm::mat4 _translationMat;
		glm::mat4 _scaleMat;

		glm::vec3 _position;
		glm::vec3 _scale;
		dn::Quaternion _rotation;

	};
}

