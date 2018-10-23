#pragma once

#include <iostream>
#include <initializer_list>
#include <vector>

#include "mVector.h"

template<unsigned int _rows, unsigned int _columns = _rows, typename matType = float>
class mMatrix
{
	static_assert(mStaticCondition<(_columns > 0)>::value, "The columns of a matrix cannot be set to 0.");
	static_assert(mStaticCondition<(_rows > 0)>::value, "The rows of a matrix cannot be set to 0.");

	template<typename ... Data>
	void setMatrix(unsigned int i, matType n, Data ... datas)
	{
		_data[i] = n;
		setMatrix(i + 1, datas...);
	}
	void setMatrix(unsigned int i, matType n)
	{
		_data[i] = n;
	}

public:
	template<typename ... Data>
	mMatrix(matType n, Data ... datas)
	{
		static const size_t compsize = sizeof...(datas);
		static_assert(mStaticCondition<(compsize < _columns * _rows)>::value, "The arguments doesn't match the dimensions of the matrix (number of argumments < columns * rows).");
		_data[0] = n;
		setMatrix(1, datas...);
	}
	template<unsigned int rows, unsigned int columns>
	mMatrix(mMatrix<rows, columns, matType> mat)
	{
		this->operator=(mat);
	}
	mMatrix(const std::initializer_list<matType> &pdata)
	{
		for (size_t i = 0, pdataSize = pdata.size(); i < _size; ++i)
			_data[i] = (i < pdataSize ? *(pdata.begin() + i) : matType());
	}
	mMatrix(matType n)
	{
		if (_columns == _rows)
		{
			for (size_t y = 0; y < _rows; ++y)
			{
				for (size_t x = 0; x < _columns; ++x)
				{
					if (x == y) _data[x + _columns * y] = n;
					else _data[x + _columns * y] = matType();
				}
			}
		}
	}
	mMatrix()
	{
		for (size_t i = 0, rc = _columns * _rows; i < rc; ++i)
			_data[i] = matType();
	}

	size_t columns() const { return _columns; }
	size_t rows() const { return _rows; }
	matType &operator()(const unsigned int &x, const unsigned int &y)
	{
		int nx = (int)x, ny = (int)y;

		while (nx >= _columns) nx -= _columns;
		while (ny >= _rows) ny -= _rows;
		return _data[nx + _columns * ny];
	}
	matType &operator()(const unsigned int &i)
	{
		int ni = (int)i;
		while (ni >= (int)_size) ni -= (int)_size;
		return _data[ni];
	}

	matType *data() { return (matType *)_data; }

	mVector<_rows, matType> operator*(mVector< _columns, matType> vec)
	{
		mVector<_rows, matType> rslt;

		for (size_t y = 0; y < _rows; ++y)
			for (size_t x = 0; x < _columns; ++x)
				rslt.operator()(y) += (this->operator()(x, y) * vec.operator()(x));

		return rslt;
	}
	template<unsigned int ncol>
	mMatrix<_rows, ncol, matType> operator*(mMatrix<_columns, ncol, matType> mat)
	{
		mMatrix<_rows, ncol, matType> rslt;

		for (size_t i0 = 0; i0 < _rows; ++i0)
			for (size_t i1 = 0; i1 < ncol; ++i1)
				for (size_t x = 0; x < _columns; ++x)
					rslt.operator()(i1, i0) += this->operator()(x, i0) * mat.operator()(i1, x);

		return rslt;
	}

	mMatrix<_rows, _columns, matType> operator+(mMatrix<_rows, _columns, matType> mat)
	{
		mMatrix<_rows, _columns, matType> rslt;

		for (size_t i = 0; i < _size; ++i)
			rslt.operator()(i) = this->operator()(i) + mat.operator()(i);

		return rslt;
	}

	mMatrix<_rows, _columns, matType> operator*(matType a)
	{
		mMatrix<_rows, _columns, matType> rslt;

		for (size_t i = 0; i < _size; ++i)
			rslt.operator()(i) = this->operator()(i) * a;

		return rslt;
	}
	mMatrix<_rows, _columns, matType> operator/(matType a)
	{
		mMatrix<_rows, _columns, matType> rslt;

		for (size_t i = 0; i < _size; ++i)
			rslt.operator()(i) = this->operator()(i) / a;

		return rslt;
	}
	mMatrix<_rows, _columns, matType> operator+(matType a)
	{
		mMatrix<_rows, _columns, matType> rslt;

		for (size_t i = 0; i < _size; ++i)
			rslt.operator()(i) = this->operator()(i) + a;

		return rslt;
	}
	mMatrix<_rows, _columns, matType> operator-(matType a)
	{
		mMatrix<_rows, _columns, matType> rslt;

		for (size_t i = 0; i < _size; ++i)
			rslt.operator()(i) = this->operator()(i) - a;

		return rslt;
	}

	mMatrix<_rows, _columns, matType> &operator*=(matType a)
	{
		for (size_t i = 0; i < _size; ++i)
			_data[i] *= a;
	}
	mMatrix<_rows, _columns, matType> &operator/=(matType a)
	{
		for (size_t i = 0; i < _size; ++i)
			_data[i] /= a;
	}
	mMatrix<_rows, _columns, matType> &operator+=(matType a)
	{
		for (size_t i = 0; i < _size; ++i)
			_data[i] += a;
	}
	mMatrix<_rows, _columns, matType> &operator-=(matType a)
	{
		for (size_t i = 0; i < _size; ++i)
			_data[i] -= a;
	}

	std::vector<mVector<_rows, matType>> getVectorsPerColumns()
	{
		std::vector<mVector<_rows, matType>> vectors(_columns);

		for (size_t x = 0; x < _columns; ++x)
			for (size_t y = 0; y < _rows; ++y)
				vectors[x].operator()(y) = this->operator()(x, y);

		return vectors;
	}
	std::vector<mVector<_columns, matType>> getVectorsPerRows()
	{
		std::vector<mVector<_columns, matType>> vectors(_rows);

		for (size_t y = 0; y < _rows; ++y)
			for (size_t x = 0; x < _columns; ++x)
				vectors[y].operator()(x) = this->operator()(x, y);

		return vectors;
	}

	size_t size() const { return _size; }

	template<unsigned int rows, unsigned int columns>
	mMatrix<_rows, _columns, matType> &operator=(mMatrix<rows, columns, matType> mat)
	{
		for (size_t y = 0; y < _rows; ++y)
			for (size_t x = 0; x < _columns; ++x)
				this->operator()(x, y) = ((x < columns && y < rows) ? mat.operator()(x, y) : matType());

		return (*this);
	}

	mMatrix<_rows, _columns, matType> &operator=(mMatrix<_rows, _columns, matType> mat)
	{
		for (size_t i = 0; i < _size; ++i)
			_data[i] = mat._data[i];
		return (*this);
	}

private:
	const size_t _size = _columns * _rows;
	matType _data[_columns * _rows];
};

template<unsigned int _rows, unsigned int _columns, typename matType>
mMatrix<_rows, _columns, matType> operator*(matType a, mMatrix<_rows, _columns, matType> mat)
{
	mMatrix<_rows, _columns, matType> rslt;

	for (size_t i = 0; i < mat.size(); ++i)
		rslt.operator()(i) = a * mat.operator()(i);

	return rslt;
}
template<unsigned int _rows, unsigned int _columns, typename matType>
mMatrix<_rows, _columns, matType> operator/(matType a, mMatrix<_rows, _columns, matType> mat)
{
	mMatrix<_rows, _columns, matType> rslt;

	for (size_t i = 0; i < mat.size(); ++i)
		rslt.operator()(i) = a / mat.operator()(i);

	return rslt;
}
template<unsigned int _rows, unsigned int _columns, typename matType>
mMatrix<_rows, _columns, matType> operator+(matType a, mMatrix<_rows, _columns, matType> mat)
{
	mMatrix<_rows, _columns, matType> rslt;

	for (size_t i = 0; i < mat.size(); ++i)
		rslt.operator()(i) = a + mat.operator()(i);

	return rslt;
}
template<unsigned int _rows, unsigned int _columns, typename matType>
mMatrix<_rows, _columns, matType> operator-(matType a, mMatrix<_rows, _columns, matType> mat)
{
	mMatrix<_rows, _columns, matType> rslt;

	for (size_t i = 0; i < mat.size(); ++i)
		rslt.operator()(i) = a - mat.operator()(i);

	return rslt;
}

