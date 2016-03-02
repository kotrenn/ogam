#ifndef __GEOMETRY_H
#define __GEOMETRY_H

#include "vector2d.h"

class vector2d;

class Circle;
class Line;
class Rect;

class Shape
{
public:
	virtual ~Shape();
	virtual bool collides(const Shape *shape) const = 0;
	virtual bool visit_collides(const Circle *circle) const = 0;
	virtual bool visit_collides(const Line *line) const = 0;
	virtual bool visit_collides(const Rect *rect) const = 0;
	virtual vector2d get_center() const = 0;
	virtual const Shape &operator+=(const vector2d &rhs) = 0;
	void fix_rect(const Rect &rect, vector2d *v = NULL);
	virtual void fix_rect_x(const Rect &rect, vector2d *v) = 0;
	virtual void fix_rect_y(const Rect &rect, vector2d *v) = 0;
	virtual void print() const = 0;
};

class Circle : public Shape
{
public:
	Circle();
	Circle(double x, double y, double r);
	Circle(const vector2d &c, double r);

	const double &operator[](int i) const;
	double &operator[](int i);

	bool collides(const Shape *shape) const;
	bool visit_collides(const Circle *circle) const;
	bool visit_collides(const Line *line) const;
	bool visit_collides(const Rect *rect) const;
	vector2d get_center() const;
	const Shape &operator+=(const vector2d &rhs);
	void fix_rect_x(const Rect &rect, vector2d *v = NULL);
	void fix_rect_y(const Rect &rect, vector2d *v = NULL);
	void print() const;

	double get_x() const { return m_x; }
	double get_y() const { return m_y; }
	double get_r() const { return m_r; }
	void set_x(double x) { m_x = x; }
	void set_y(double y) { m_y = y; }
	void set_r(double r) { m_r = r; }
private:
	double m_x, m_y;
	double m_r;
};

class Line : public Shape
{
public:
	Line();
	Line(double x1, double y1, double x2, double y2);
	Line(const vector2d &p1, const vector2d &p2);

	const double &operator[](int i) const;
	double &operator[](int i);

	bool collides(const Shape *shape) const;
	bool visit_collides(const Circle *circle) const;
	bool visit_collides(const Line *line) const;
	bool visit_collides(const Rect *rect) const;
	vector2d get_center() const;
	const Shape &operator+=(const vector2d &rhs);
	void fix_rect_x(const Rect &rect, vector2d *v = NULL);
	void fix_rect_y(const Rect &rect, vector2d *v = NULL);
	void print() const;

	Rect get_bounds() const;
	double len() const;

	double get_x1() const { return m_x1; }
	double get_y1() const { return m_y1; }
	double get_x2() const { return m_x2; }
	double get_y2() const { return m_y2; }
	double get_dx() const { return m_x2 - m_x1; }
	double get_dy() const { return m_y2 - m_y1; }
	void set_x1(double x1) { m_x1 = x1; }
	void set_y1(double y1) { m_y1 = y1; }
	void set_x2(double x2) { m_x2 = x2; }
	void set_y2(double y2) { m_y2 = y2; }
private:
	double m_x1, m_y1;
	double m_x2, m_y2;
};

class Rect : public Shape
{
public:
	Rect();
	Rect(double x, double y, double w, double h);

	const double &operator[](int i) const;
	double &operator[](int i);

	bool collides(const Shape *shape) const;
	bool visit_collides(const Circle *circle) const;
	bool visit_collides(const Line *line) const;
	bool visit_collides(const Rect *rect) const;
	vector2d get_center() const;
	const Shape &operator+=(const vector2d &rhs);
	void fix_rect_x(const Rect &rect, vector2d *v = NULL);
	void fix_rect_y(const Rect &rect, vector2d *v = NULL);
	void print() const;

	bool contains(double x, double y) const;

	double get_x() const { return m_x; }
	double get_y() const { return m_y; }
	double get_w() const { return m_w; }
	double get_h() const { return m_h; }
	void set_x(double x) { m_x = x; }
	void set_y(double y) { m_y = y; }
	void set_w(double w) { m_w = w; }
	void set_h(double h) { m_h = h; }
private:
	double m_x, m_y;
	double m_w, m_h;
};

#endif
