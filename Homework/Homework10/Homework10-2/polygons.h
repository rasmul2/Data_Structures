
#ifndef POLYGONS_H
#define POLYGONS_H


#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

#include "utilities.h"

class Polygon {
public:
	Polygon();
	Polygon(const string& name,const vector <Point>& pts);
	virtual ~Polygon() {}
	int NumVerts() { return verts.size(); }
	bool HasARightAngle (const Point&a, const Point&b, const Point&c);
	bool HasEqualSides (const Point&a, const Point&b, const Point&c, const Point&d);
	bool HasParallelSides (const Point&a, const Point&b, const Point&c, const Point&d);
	bool IsSymetrical (const Point&a, const Point&b, const Point&c, const Point&d);
	bool HasAnAcuteAngle();
	bool HasARightAngle();
	bool HasAllEqualSides();
	bool HasAllEqualAngles();
	bool HasAnObtuseAngle();
	bool IsConvex();
	bool IsConcave();
	string getName() {return shape_name; }

protected:
	vector<Point> verts;
	string shape_name;
};


class Quadrilateral : public Polygon {
public:
	Quadrilateral();
	Quadrilateral(const string& name, const vector <Point>& pts);
};

class Trapezoid: public virtual Quadrilateral {
public:
	Trapezoid();
	Trapezoid(const string& name, const vector <Point>& pts);
};

class Kite: public virtual Quadrilateral{
public:
	Kite(const string& name, const vector <Point>& pts);
};

class IsoscelesTrapezoid: public Trapezoid {
public:
	IsoscelesTrapezoid(const string& name, const vector <Point>& pts);
};

class Rhombus: public Kite {
public: 
	Rhombus(const string& name, const vector <Point>& pts);
};

class Rectangle: public Kite {
public:
	Rectangle(const string& name, const vector <Point>& pts);
};

class Square: public Rectangle, public Rhombus {
public: 
	Square(const string& name, const vector <Point>& pts);
};

class Parallelogram: public Trapezoid, public Kite {
public:
	Parallelogram(const string& name,const vector <Point>& pts);
};


class Arrow: public Quadrilateral {
public:
	Arrow(const string& name, const vector <Point>& pts);
};

class Triangle : public Polygon {
public:
	Triangle();
	Triangle(const string& name,const vector <Point>& pts);
};

class IsoscelesTriangle: public virtual Triangle {
public:
	IsoscelesTriangle(const string& name, const vector <Point>& pts);
};

class RightTriangle: public virtual Triangle {
public:
	RightTriangle(const string& name, const vector <Point>& pts);
};

class IsoscelesRightTriangle: public IsoscelesTriangle, public RightTriangle {
public:
	IsoscelesRightTriangle(const string& name, const vector <Point>& pts);
};

class ObtuseTriangle: public virtual Triangle {
public: 
	ObtuseTriangle(const string& name, const vector <Point>& pts);
};

class IsoscelesObtuseTriangle: public ObtuseTriangle, public IsoscelesTriangle {
public:
	IsoscelesObtuseTriangle(const string& name, const vector <Point>& pts);
};

class EquilateralTriangle: public IsoscelesTriangle{
public:
	EquilateralTriangle(const string& name, const vector <Point>& pts);
};

#endif

