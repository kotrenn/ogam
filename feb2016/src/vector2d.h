#ifndef __VECTOR2D_H
#define __VECTOR2D_H

#include <math.h>
#include <iostream>

#include "common.h"

using namespace std;

class vector2d
{
public:
	vector2d();
	vector2d(double x, double y);
	vector2d(const vector2d &other);
	~vector2d();
    
	const vector2d &operator=(const vector2d &rhs);
	const double &operator[](int i) const;
	double &operator[](int i);
	const vector2d operator+(const vector2d &rhs) const;
	const vector2d operator+=(const vector2d &rhs);
	const vector2d operator-(const vector2d &rhs) const;
	const vector2d operator-=(const vector2d &rhs);
	const vector2d operator*(double rhs) const;
	const vector2d operator*=(double rhs);
	const vector2d operator/(double rhs) const;
	const vector2d operator/=(double rhs);
	double operator*(const vector2d &rhs) const;
	double operator%(const vector2d &rhs) const;
	bool operator==(const vector2d &rhs) const;
	bool operator!=(const vector2d &rhs) const;

	double get_x() const { return m_x; }
	double get_y() const { return m_y; }
	void set_x(double x) { m_x = x; }
	void set_y(double y) { m_y = y; }
	double norm() const;
	void normalize();
private:
	double m_x, m_y;
};

std::ostream &operator<<(std::ostream &out, const vector2d &rhs);
const vector2d operator*(double lhs, const vector2d &rhs);

#endif
