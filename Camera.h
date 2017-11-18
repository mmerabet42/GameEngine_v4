#pragma once

#include "Component.h"

#include "opengl.h"

namespace dn
{
	/*Component that can be added to an object, there must be only one camera in a scene. No camera, no rendering*/
	class Camera : public dn::Component
	{
	public:
		Camera(const float & p_fov = 70.0f, const float & p_near = 0.01f, const float & p_far = 1000.0f, const float & p_aspectRatio = 1);

		static dn::Camera * main;

		glm::mat4 ViewMatrix();
		glm::mat4 ProjectionMatrix();

		glm::mat4 ViewProjectionMatrix();

		void Start();
		void Update();

		float fieldOfView() const;
		float & fieldOfView();
		void SetFieldOfView(const float & p_fov);

		float nearPlane() const;
		float & nearPlane();
		void SetNear(const float & p_near);

		float farPlane() const;
		float & farPlane();
		void SetFar(const float & p_far);

		float aspectRatio() const;
		float & aspectRatio();
		void SetAspectRatio(const float  &p_aspectRatio);

	private:
		bool _projectionChanged;

		glm::vec3 _positionSave;
		glm::vec3 _rotationSave;

		glm::mat4 _projectionMat;
		glm::mat4 _viewMatrix;

		float _far;
		float _near;
		float _fov;
		float _aspectRatio;
	};
}

