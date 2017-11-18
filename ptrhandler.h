#pragma once

#include <iostream>

template <typename T>
class ptr
{
public:
	ptr(const T & v = T()) : _ptr(new T(v)), _isValid(true) { }

	T * pointer() const { return (this->_isValid ? this->_ptr : nullptr); }
	T * pointer() { return (this->_isValid ? this->_ptr : nullptr); }
	T & value() const { return *this->_ptr; }
	T & value() { return *this->_ptr; }
	bool isValid() const { return this->_isValid; }

	void deletePtr() { this->_isValid = false; delete this->_ptr; }

	operator bool()
	{
		return this->_isValid;
	}

	bool operator==(const bool & b)
	{
		return this->_isValid == b;
	}

	bool operator!=(const bool & b)
	{
		return this->_isValid != b;
	}

	T * operator->() const
	{
		return this->pointer();
	}

	T * operator->()
	{
		return this->pointer();
	}

	T & operator=(const T & v)
	{
		return this->value() = v;
	}

private:
	T * _ptr;
	bool _isValid;
};

template <typename T>
std::ostream & operator<<(std::ostream & stream, const ptr<T> & a)
{
	return stream << a.value();
}

