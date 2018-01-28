#pragma once

#include <iostream>
#include <initializer_list>
#include <cmath>
#include <cassert>
#include "addon_func.h"

template<unsigned int _dimensions, typename vecType = float>
class mVector
{
	static_assert(mStaticCondition<(_dimensions > 0)>::value, "Vectors must have at least one dimension.");

	template<typename ... Components>
	void setVector(unsigned int i, vecType n, Components ... components)
	{
		_data[i] = n;
		setVector(i + 1, components...);
	}
	void setVector(unsigned int i, vecType n)
	{
		_data[i] = n;
	}
public:
	template<typename ... Components>
	mVector(vecType n, Components ... components)
	{
		static const size_t compsize = sizeof...(components);
		static_assert(mStaticCondition<(compsize < _dimensions)>::value, "The number of arguments must be equal to the number of dimensions.");
		_data[0] = n;
		setVector(1, components...);
	}
	mVector(vecType scalar)
	{
		for (size_t i = 0; i < _dimensions; ++i)
			_data[i] = scalar;
	}
	mVector(const std::initializer_list<vecType> &pdata)
	{
		for (size_t i = 0; i < _dimensions; ++i)
			_data[i] = *(pdata.begin() + i);
	}
	mVector()
	{
		for (size_t i = 0; i < _dimensions; ++i)
			_data[i] = vecType();
	}

	vecType &operator()(const unsigned int &d)
	{
		int nd = (int)d;
		while (nd >= _dimensions) nd -= _dimensions;
		return _data[nd];
	}
	size_t dimensions() const { return _dimensions; }
	size_t length(const bool &doSqrt = true)
	{
		vecType result = 0;
		for (size_t i = 0; i < _dimensions; ++i)
			result += pow(_data[i], 2);
		return (doSqrt ? sqrt(result) : result);
	}
	vecType add()
	{
		vecType rslt = _data[0];
		for (size_t i = 1; i < _dimensions; ++i)
			rslt += _data[i];
		return rslt;
	}
	vecType multiply()
	{
		vecType rslt = _data[0];
		for (size_t i = 1; i < _dimensions; ++i)
			rslt *= _data[i];
		return rslt;
	}

	mVector<_dimensions, vecType> operator+(mVector<_dimensions, vecType> vec)
	{
		mVector<_dimensions, vecType> resultVec;
		for (size_t i = 0; i < _dimensions; ++i)
			resultVec.operator()(i) = this->operator()(i) + vec.operator()(i);
		return resultVec;
	}
	mVector<_dimensions, vecType> operator-(mVector<_dimensions, vecType> vec)
	{
		mVector<_dimensions, vecType> resultVec;
		for (size_t i = 0; i < _dimensions; ++i)
			resultVec.operator()(i) = this->operator()(i) - vec.operator()(i);
		return resultVec;
	}
	mVector<_dimensions, vecType> operator*(mVector<_dimensions, vecType> vec)
	{
		mVector<_dimensions, vecType> resultVec;
		for (size_t i = 0; i < _dimensions; ++i)
			resultVec.operator()(i) = this->operator()(i) * vec.operator()(i);
		return resultVec;
	}
	mVector<_dimensions, vecType> operator/(mVector<_dimensions, vecType> vec)
	{
		mVector<_dimensions, vecType> resultVec;
		for (size_t i = 0; i < _dimensions; ++i)
			resultVec.operator()(i) = this->operator()(i) / vec.operator()(i);
		return resultVec;
	}

	mVector<_dimensions, vecType> &operator+=(mVector<_dimensions, vecType> vec)
	{
		for (size_t i = 0; i < _dimensions; ++i)
			_data[i] += vec(i);
		return (*this);
	}
	mVector<_dimensions, vecType> &operator-=(mVector<_dimensions, vecType> vec)
	{
		for (size_t i = 0; i < _dimensions; ++i)
			_data[i] -= vec(i);
		return (*this);
	}
	mVector<_dimensions, vecType> &operator*=(mVector<_dimensions, vecType> vec)
	{
		for (size_t i = 0; i < _dimensions; ++i)
			_data[i] *= vec(i);
		return (*this);
	}
	mVector<_dimensions, vecType> &operator/=(mVector<_dimensions, vecType> vec)
	{
		for (size_t i = 0; i < _dimensions; ++i)
			_data[i] += vec(i);
		return (*this);
	}

	mVector<_dimensions, vecType> &operator+=(vecType scalar)
	{
		for (size_t i = 0; i < _dimensions; ++i)
			_data[i] += scalar;
		return (*this);
	}
	mVector<_dimensions, vecType> &operator-=(vecType scalar)
	{
		for (size_t i = 0; i < _dimensions; ++i)
			_data[i] -= scalar;
		return (*this);
	}
	mVector<_dimensions, vecType> &operator*=(vecType scalar)
	{
		for (size_t i = 0; i < _dimensions; ++i)
			_data[i] *= scalar;
		return (*this);
	}
	mVector<_dimensions, vecType> &operator/=(vecType scalar)
	{
		for (size_t i = 0; i < _dimensions; ++i)
			_data[i] /= scalar;
		return (*this);
	}

private:
	vecType _data[_dimensions];
};

template<unsigned int _dimensions, typename vecType>
vecType mDot(mVector<_dimensions, vecType> vec1, mVector<_dimensions, vecType> vec2)
{
	return (vec1 * vec2).add();
}
