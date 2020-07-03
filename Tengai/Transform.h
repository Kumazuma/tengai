#pragma once
#include<xmemory>
#include<DirectXMath.h>
class Transform
{
public:
	Transform(float x = 0.f, float y = 0.f);
	Transform(const Transform& other);
	Transform& operator = (const Transform& other);
	Transform operator + (const Transform& other) const;
	Transform operator - (const Transform& other) const;
	Transform& operator += (const Transform& other);
	Transform& operator -= (const Transform& other);
	RECT operator + (const RECT& rc) const;
	float Length() const;
	float x;
	float y;
};
inline Transform operator *(float x, const Transform& pos)
{
	return { pos.x * x, pos.y * x };
}
inline RECT operator + (const RECT& rc, const Transform& pos)
{
	return { (int)pos.x + rc.left, (int)pos.y + rc.top, (int)pos.x + rc.right, (int)pos.y + rc.bottom };
}
inline Transform::Transform(float x, float y) :
	x{ x },
	y{ y }
{
	
}
inline Transform::Transform(const Transform& other) :
	Transform{ other.x, other.y }
{
	
}
inline Transform& Transform::operator=(const Transform& other)
{
	new(this) Transform{ other };
	return *this;
}
inline Transform Transform::operator + (const Transform& other) const
{
	return { x + other.x, y + other.y };
}
inline Transform Transform::operator - (const Transform& other) const
{
	return { x - other.x, y - other.y };
}
inline Transform& Transform::operator -= (const Transform& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}
inline RECT Transform::operator+(const RECT& rc) const 
{
	return rc + *this;
}
inline float Transform::Length() const
{
	return sqrtf(x * x + y * y);
}
inline Transform& Transform::operator += (const Transform& other)
{
	x += other.x;
	y += other.y;
	return *this;
}
template<typename _floatT>
struct MatrixRow
{
public:
	MatrixRow(_floatT(&row)[3]) :row{ row } {}
	const _floatT& operator[](size_t index)const&&
	{
		return row[index];
	}
	_floatT& operator[](size_t index)&&
	{
		return row[index];
	}
	_floatT(&row)[3];
};
typedef float(&Row)[3];
struct Matrix
{
public:
	static Matrix Identity();
	static Matrix Translate(float dx, float dy);
	static Matrix Rotate(float degree);
public:
	Matrix();
	Matrix(const Matrix& other);
	Matrix(const Transform& transform);
	void operator =(const Matrix& other);
	MatrixRow<float> operator[](size_t index)
	{
		return MatrixRow<float>{ item[index] };
	}
	MatrixRow<const float> operator[](size_t index) const
	{
		return MatrixRow<const float>{ item[index] };
	}
	Matrix operator * (const Matrix& other)const;
	Matrix operator + (const Matrix& other)const;
	Matrix operator - (const Matrix& other)const;
	explicit operator Transform() const;
	float item[3][3];
};

inline Matrix Matrix::Identity()
{
	Matrix res{};
	res.item[0][0] = 1;
	res.item[1][1] = 1;
	res.item[2][2] = 1;
	return res;
}

inline Matrix Matrix::Translate(float dx, float dy)
{
	Matrix res = Identity();
	res[0][2] = dx;
	res[1][2] = dy;
	return res;
}

inline Matrix Matrix::Rotate(float degree)
{
	Matrix res{ Identity() };
	res.item[0][0] = (float)cosf(degree);
	res.item[1][0] = (float)sinf(degree);

	res.item[0][1] = -res.item[1][0];
	res.item[1][1] = res.item[0][0];

	return res;
}

inline Matrix::Matrix() :
	item{  }
{

}
inline Matrix::Matrix(const Matrix& other) :
	Matrix{}
{
	memcpy(item, other.item, sizeof(item));
}
inline Matrix::Matrix(const Transform& transform)
	: Matrix{ Identity() }
{
	item[0][2] = transform.x;
	item[1][2] = transform.y;
	//item[2][2] = 0.f;
}
inline void Matrix::operator=(const Matrix& other)
{
	memcpy(item, other.item, sizeof(item));
}
inline Matrix Matrix::operator*(const Matrix& other) const
{
	Matrix res;
	for (size_t y = 0; y < 3; ++y)
	{
		for (size_t x = 0; x < 3; ++x)
		{
			float value = 0.f;
			value += item[y][0] * other.item[0][x];
			value += item[y][1] * other.item[1][x];
			value += item[y][2] * other.item[2][x];
			res[y][x] = value;
		}
	}
	return res;
}
inline Matrix Matrix::operator+(const Matrix& other) const
{
	Matrix res;
	for (size_t x = 0; x < 3; ++x)
	{
		res.item[0][x] = item[0][x] + other.item[0][x];
		res.item[1][x] = item[1][x] + other.item[1][x];
		res.item[2][x] = item[2][x] + other.item[2][x];
	}
	return res;
}
inline Matrix Matrix::operator-(const Matrix& other) const
{
	Matrix res;
	for (size_t x = 0; x < 3; ++x)
	{
		res.item[0][x] = item[0][x] - other.item[0][x];
		res.item[1][x] = item[1][x] - other.item[1][x];
		res.item[2][x] = item[2][x] - other.item[2][x];
	}
	return res;
}
inline Matrix::operator Transform() const
{
	Transform res;
	res.x = item[0][2];
	res.y = item[1][2];
	return res;
}