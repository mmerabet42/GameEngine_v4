#pragma once

#include <vector>
#include <map>

namespace dn
{
	class Window;
	class Application;

	template <class ... _Args>
	class Event
	{
	public:
		Event() : _triggering(false) { }

		virtual dn::Event<_Args ...> & AddListener(void(*p_func)(_Args ...))
		{
			_listeners.push_back(p_func);
			return *this;
		}

		virtual dn::Event<_Args ...> & RemoveListener(void(*p_func)(_Args ...))
		{
			std::vector<void(*)(_Args ...)>::iterator itErase = std::find(this->_listeners.begin(), this->_listeners.end(), p_func);
			if (itErase != this->_listeners.end())
				this->_listeners.erase(itErase);
			return *this;
		}

		virtual void Trigger(_Args ... p_args)
		{
			this->_triggering = true;
			for (size_t i = 0; this->_triggering && i < _listeners.size(); ++i)
				if (this->_listeners[i])
					this->_listeners[i](p_args ...);
		}

		virtual void ClearListeners()
		{
			this->_listeners.clear();
		}

		virtual void Release()
		{
			this->_triggering = false;
		}

	protected:
		
		bool _triggering;

		std::vector<void(*)(_Args ...)> _listeners;
	};

	template <class ... _Args>
	class PriorityEvent : public Event<_Args ...>
	{
	public:
		PriorityEvent() : Event<_Args ...>() { }

		virtual dn::PriorityEvent<_Args ...> & AddListener(void(*p_func)(_Args ...))
		{
			this->AddListener(0, p_func);
			return *this;
		}

		virtual dn::PriorityEvent<_Args ...> & AddListener(const int & priority, void(*p_func)(_Args ...))
		{
			this->_orderedListeners[priority].push_back(p_func);
			return *this;
		}

		virtual dn::PriorityEvent<_Args ...> & RemoveListener(void(*p_func)(_Args ...))
		{
			for (std::map<int, std::vector<void(*)(_Args ...)>>::iterator it = this->_orderedListeners.begin(); it != this->_orderedListeners.end(); ++it)
			{
				std::vector<void(*)(_Args ...)>::iterator itErase = std::find(it->second.begin(), it->second.end(), p_func);
				if (itErase != it->second.end())
					it->second.erase(itErase);
			}
			return *this;
		}

		virtual dn::PriorityEvent<_Args ...> & RemoveListener(const int & p_priority, void(*p_func)(_Args ...))
		{
			if (this->_orderedListeners.count(p_priority))
			{
				std::vector<void(*)(_Args ...)>::iterator itErase = std::find(this->_orderedListeners[p_priority].begin(), this->_orderedListeners[p_priority].end(), p_func);
				if (itErase != this->_orderedListeners[p_priority].end())
					this->_orderedListeners[p_priority].erase(itErase);
			}
			return *this;
		}
		
		virtual void Trigger(_Args ... p_args)
		{
			this->_triggering = true;
			for (std::map<int, std::vector<void(*)(_Args ...)>>::iterator it = this->_orderedListeners.begin(); this->_triggering && it != this->_orderedListeners.end(); ++it)
				for (size_t i = 0; i < it->second.size(); ++i)
					it->second[i](p_args ...);
		}

		virtual void ClearListeners()
		{
			for (std::map<int, std::vector<void(*)(_Args ...)>>::iterator it = this->_orderedListeners.begin(); this->_triggering && it != this->_orderedListeners.end(); ++it)
				it->second.clear();
			this->_orderedListeners.clear();
		}

		virtual void ClearListeners(const int & priority)
		{
			if (this->_orderedListeners.count(priority))
				this->_orderedListeners[priority].clear();
		}

	private:

		std::map<int, std::vector<void(*)(_Args ...)>> _orderedListeners;
	};

	template <class ... _Args>
	void Connect(dn::Event<_Args ...> & p_event, void(*p_func)(_Args ...))
	{
		p_event.AddListener(p_func);
	}
}

