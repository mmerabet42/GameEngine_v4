#pragma once

#include <string>

namespace dn
{
	class Object;

	/*Basic component, that should be inherited in order to control an object during runtime*/
	class Component
	{
	public:
		Component(dn::Object * p_object = nullptr, const std::string & p_name = "Component Script");

		bool active() const;
		void SetActive(const bool & p_active);

		std::string name() const;
		void SetName(const std::string & p_name);

		dn::Object * object() const;
		void SetObject(dn::Object * p_object);

		virtual void Start() = 0;
		virtual void Update() = 0;

	private:
		bool _active;

		dn::Object * _object;
		std::string _name;
	};
}

