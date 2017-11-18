#pragma once

#include <map>
#include <typeinfo>

namespace dn
{
	class Component;

	/*Basic representation of an object, where components can be added in*/
	class Object
	{
	public:
		Object(const std::string & p_name = "Object");
		~Object();

		bool active() const;
		void SetActive(const bool & p_active);

		std::string name() const;
		void SetName(const std::string & p_name);
		
		template <typename T>
		T * GetComponent()
		{
			if (std::is_base_of<dn::Component, T>::value)
			{
				std::string tname = typeid(T).name();
				if (this->_components.count(tname))
					return dynamic_cast<T *>(this->_components.at(tname));
			}
			return nullptr;
		}

		/*Add the component to the object*/
		template <typename T>
		T * AddComponent()
		{
			if (std::is_base_of<dn::Component, T>::value)
			{
				std::string tname = typeid(T).name();
				if (!this->_components.count(tname))
				{
					T * comp = new T();
					comp->SetObject(this);
					if (this->_running)
						comp->Start();
					this->_components.insert(std::make_pair(tname, comp));
					return comp;
				}
			}
			return nullptr;
		}

		/*Add an already created component to the object*/
		template <typename T>
		T * AddComponent(T * p_component)
		{
			if (std::is_base_of<dn::Component, T>::value)
			{
				std::string tname = typeid(T).name();
				if (!this->_components.count(tname))
				{
					p_component->SetObject(this);
					if (this->_running)
						p_component->Start();
					this->_components.insert(std::make_pair(tname, p_component));
					return p_component;
				}
			}
			return nullptr;
		}

		template <typename T>
		void RemoveComponent()
		{
			if (std::is_base_of<dn::Component, T>::value)
			{
				std::string tname = typeid(T).name();
				if (this->_components.count(tname))
				{
					T * comp = this->_components.at(tname);
					this->_components.erase(tname);
					delete comp;
				}
			}
		}

		virtual void Start();
		virtual void Update();

	protected:
		bool _active;
		bool _running;

		std::string _name;

		std::map<std::string, dn::Component *> _components;
	};
}

