#include "vector2d.h"

vector2d::vector2d()
	: m_x(0), m_y(0)
{
}

vector2d::vector2d(double x, double y)
	: m_x(x), m_y(y)
{
}

vector2d::vector2d(const vector2d &other)
	: m_x(other.m_x), m_y(other.m_y)
{
}

vector2d::~vector2d()
{
}

const vector2d &vector2d::operator=(const vector2d &rhs)
{
	m_x = rhs.m_x;
	m_y = rhs.m_y;
	return *this;
}

std::ostream &operator<<(std::ostream &out, const vector2d &rhs)
{
	out.precision(3);
	return out << fixed << "[" << rhs[0] << ", " << rhs[1] << "]";
}

const double &vector2d::operator[](int i) const
{
	if (i == 0)
		return m_x;
	else
		return m_y;
}

double &vector2d::operator[](int i)
{
	if (i == 0)
		return m_x;
	else
		return m_y;
}

const vector2d vector2d::operator+(const vector2d &rhs) const
{
	vector2d ret(m_x, m_y);
	ret.m_x += rhs.m_x;
	ret.m_y += rhs.m_y;
	return ret;
}

const vector2d vector2d::operator+=(const vector2d &rhs)
{
	m_x += rhs.m_x;
	m_y += rhs.m_y;
	return *this;
}

const vector2d vector2d::operator-(const vector2d &rhs) const
{
	vector2d ret(m_x, m_y);
	ret.m_x -= rhs.m_x;
	ret.m_y -= rhs.m_y;
	return ret;
}

const vector2d vector2d::operator-=(const vector2d &rhs)
{
	m_x -= rhs.m_x;
	m_y -= rhs.m_y;
	return *this;
}

const vector2d vector2d::operator*(double rhs) const
{
	vector2d ret(m_x, m_y);
	ret.m_x *= rhs;
	ret.m_y *= rhs;
	return ret;
}

const vector2d operator*(double lhs, const vector2d &rhs)
{
	vector2d ret(lhs * rhs[0], lhs * rhs[1]);
	return ret;
}

const vector2d vector2d::operator*=(double rhs)
{
	m_x *= rhs;
	m_y *= rhs;
	return *this;
}

const vector2d vector2d::operator/(double rhs) const
{
	vector2d ret(m_x, m_y);
	ret.m_x /= rhs;
	ret.m_y /= rhs;
	return ret;
}

const vector2d vector2d::operator/=(double rhs)
{
	m_x /= rhs;
	m_y /= rhs;
	return *this;
}

double vector2d::operator*(const vector2d &rhs) const
{
	double dot = m_x * rhs.m_x + m_y * rhs.m_y;
	return dot;
}

double vector2d::operator%(const vector2d &rhs) const
{
	double ret = m_x * rhs.m_y - rhs.m_y * m_x;
	return ret;
}

bool vector2d::operator==(const vector2d &rhs) const
{
	bool ret =
		fabs(m_x - rhs.m_x) < EPSILON &&
		fabs(m_y - rhs.m_y) < EPSILON;
	return ret;
}

bool vector2d::operator!=(const vector2d &rhs) const
{
	bool ret =
		fabs(m_x - rhs.m_x) < EPSILON &&
		fabs(m_y - rhs.m_y) < EPSILON;
	return !ret;
}

double vector2d::norm() const
{
	return sqrt(m_x * m_x + m_y * m_y);
}

void vector2d::normalize()
{
	double mag = norm();
	if (mag > EPSILON)
	{
		m_x /= mag;
		m_y /= mag;
	}
}
