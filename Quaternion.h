#pragma once

#include "opengl.h"

namespace dn
{
	/*A quaternion represent a 3d rotation*/
	class Quaternion
	{
	public:
		Quaternion(const glm::vec3 & p_eulerAngles = glm::vec3(0, 0, 0));
		Quaternion(const glm::quat & p_quat);
		Quaternion(const float & p_eulerX, const float & p_eulerY, const float & p_eulerZ);

		glm::quat quat();
		glm::mat4 ToMatrix4();

		glm::vec3 eulerAngles() const;
		glm::vec3 & eulerAngles();

		void SetEuler(const glm::vec3 & p_eulerAngles = glm::vec3(0, 0, 0));
		void SetEuler(const float & p_eulerX, const float & p_eulerY, const float & p_eulerZ);

	private:

		bool _matUpdate;
		glm::mat4 _quatToMat;

		bool _eulerModified;
		glm::vec3 _eulerAngles;
		glm::quat _quat;
	};
}

