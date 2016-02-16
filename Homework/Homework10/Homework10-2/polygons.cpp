#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

#include "polygons.h"
#include "utilities.h"

//==============================================================
//POLYGON


Polygon::Polygon(){}

Polygon::Polygon(const string &name, const vector <Point>& pts){
	for (int i = 0; i < pts.size(); ++i){
		verts.push_back(pts[i]);
	}
	shape_name = name;
}

bool Polygon::HasARightAngle(const Point&a, const Point&b, const Point&c){
	double angle = Angle(a, b, c);
	if(RightAngle(angle)) return true;
	else{return false;}
}

bool Polygon::HasEqualSides(const Point&a,const Point&b, const Point&c, const Point&d){
	double side1 = DistanceBetween(a,b);
	double side2 = DistanceBetween(c,d);
	if(side1 == side2) return true;
	else{return false;}
}

bool Polygon::HasParallelSides(const Point&a,const Point&b, const Point&c, const Point&d){
	Vector side1 = Vector(a,b);
	Vector side2 = Vector(c,d);
	if(Parallel(side1, side2)) return true;
	else{return false;}
}

bool Polygon::IsSymetrical(const Point&a, const Point&b, const Point&c, const Point&d){
	double angle1 = Angle(a,b,c);
	double angle2 = Angle(b,c,d);
	double angle3 = Angle(c,d,a);
	double angle4 = Angle(d,a,b);
	if(angle1 == angle2 && angle3 == angle4){
		return true;
	}
	else{
		return false;
	}
}

bool Polygon::HasAllEqualSides(){
//cout << shape_name << "3" << endl;
double side1 = DistanceBetween(verts[0], verts[1]);
	for (int i = 0, j = 1; i < verts.size(); ++i)
	{
		double side2 = DistanceBetween(verts[i], verts[j]);
		if (!EqualSides(side1, side2))
		{
		 	return false;
		}
		else{
			if (j==verts.size()-1)
			{
				j=0;
			}
			else{
				j++;
			}
		}
	}
	return true;
}

bool Polygon::HasAllEqualAngles(){
	//cout << shape_name << "2" << endl;
	double angle1 = Angle(verts[0], verts[1], verts[2]);
	
	for(int i = 0, j = 1, k = 2; i < verts.size(); i++){
		double angle2 = Angle(verts[i], verts[j], verts[k]);
		if(!EqualAngles(angle1, angle2)){
			return false;
		}

		else{
			if (k==verts.size()-1)
			{
				k=0;
			}
			else{
				k++;
			}
			if (j==verts.size()-1)
			{
				j=0;
			}
			else{
				j++;
			}
		}
	}
	return true;

}

bool Polygon::HasARightAngle(){
	for (int i = 0, j = 1, k= 2; i < verts.size(); ++i)
	{
		double angle = Angle(verts[i], verts[j], verts[k]);
		if (RightAngle(angle))
		{
		 	return true;
		}
		else{
			if (k==verts.size()-1)
			{
				k=0;
			}
			else{
				k++;
			}
			if (j==verts.size()-1)
			{
				j=0;
			}
			else{
				j++;
			}
		}
	}
	return false;


}

bool Polygon::HasAnObtuseAngle(){
for (int i = 0, j = 1, k= 2; i < verts.size(); ++i)
	{
		double angle = Angle(verts[i], verts[j], verts[k]);
		if (ObtuseAngle(angle))
		{
		 	return true;
		}
		else{
			if (k==verts.size()-1)
			{
				k=0;
			}
			else{
				k++;
			}
			if (j==verts.size()-1)
			{
				j=0;
			}
			else{
				j++;
			}
		}
	}
	return false;
}

bool Polygon::HasAnAcuteAngle(){
	cout << shape_name << "1" << endl;
	for (int i = 0, j = 1, k= 2; i < verts.size(); ++i)
	{
		double angle = Angle(verts[i], verts[j], verts[k]);
		if (AcuteAngle(angle))
		{
		 	return true;
		}
		else{
			if (k==verts.size()-1)
			{
				k=0;
			}
			else{
				k++;
			}
			if (j==verts.size()-1)
			{
				j=0;
			}
			else{
				j++;
			}
		}
	}
	return false;

}

bool Polygon::IsConvex(){	
	vector <double> angles;
	//cout << verts.size()<< endl;
	for(int i = 0, j = 1, k = 2; i < verts.size(); i++){
		double angle = Angle(verts[i], verts[j], verts[k]);
		
		angles.push_back(angle);

		if (k==verts.size()-1)
		{
			k=0;
		}
		else{
			k++;
		}
		if (j==verts.size()-1)
		{
			j=0;
		}
		else{
			j++;
		}
	}

	double total = 0;
	for (int i = 0; i < angles.size(); ++i)
	{
		cout << angles[i] << endl;
		total += angles[i];
	}

	//somehow even though the total  is right the 180 check isn't working
	//cout << shape_name<< endl;
	//cout << total << endl;
	if (total <= 180)
	{
		return true;
	}
	else{
		return false;
	}

}

bool Polygon::IsConcave(){
	vector <double> angles;
	for(int i = 0, j = 1, k = 2; i < verts.size(); i++){
		double angle = Angle(verts[i], verts[j], verts[k]);
		
		angles.push_back(angle);

		if (k==verts.size()-1)
		{
			k=0;
		}
		else{
			k++;
		}
		if (j==verts.size()-1)
		{
			j=0;
		}
		else{
			j++;
		}
	}

	for (int i = 0; i < angles.size(); ++i)
	{
		if(angles[i]> 180){
			return true;
		}

	}
	return false;

}

//=====================================================================
//QUADRILATERALS
Quadrilateral::Quadrilateral(): Polygon(){}

Quadrilateral::Quadrilateral(const string& name, const vector <Point>& verts):
Polygon(name, verts){
	if (verts.size() != 4) throw 69;
}

Trapezoid::Trapezoid(): Quadrilateral(){}

Trapezoid::Trapezoid(const string& name, const vector <Point>& verts): 
Quadrilateral(name, verts) {
	if (!HasParallelSides(verts[0], verts[1], verts[2], verts[3]) &&
	 !HasParallelSides(verts[1], verts[2], verts[3], verts[0])){
		throw 69;
	}
	
}

IsoscelesTrapezoid::IsoscelesTrapezoid(const string& name, const vector <Point>& verts):
Quadrilateral(name, verts), Trapezoid(name, verts) {
	//cout << "here" << endl;
	if(!IsSymetrical(verts[0], verts[1], verts[2], verts[3]) &&
		!IsSymetrical(verts[1], verts[2], verts[3], verts[0])){
		throw 69;
	}
}

Kite::Kite(const string& name, const vector <Point>& verts): 
Quadrilateral(name, verts){
	if(!HasEqualSides(verts[0], verts[1], verts[1], verts[2]) ||
		!HasEqualSides(verts[2], verts[3], verts[3], verts[0])){
		throw 69;
	}
	if(!HasEqualSides(verts[1], verts[2], verts[2], verts[3]) ||
		!HasEqualSides(verts[3], verts[0], verts[0], verts[1])){
		throw 69;
	}
}

Parallelogram::Parallelogram(const string& name,const vector <Point>& verts):
Trapezoid(name, verts), Quadrilateral(name, verts), Kite(name, verts){
	if(!HasEqualSides(verts[0], verts[1], verts[2], verts[3]) ||
	 !HasEqualSides(verts[1], verts[2], verts[3], verts[0])){
	 	throw 69;
	 }

	
}

Rectangle::Rectangle(const string& name, const vector <Point>& verts):
Quadrilateral(name, verts), Kite(name, verts){
	cout << "hala" << endl;
	cout << verts.size();
	if (!HasAllEqualAngles() || !HasARightAngle())
	{
		throw 69;
	}

}

Rhombus::Rhombus(const string& name, const vector <Point>& verts):
Quadrilateral(name, verts), Kite(name, verts){
	if(!HasAllEqualAngles()){
		throw 69;
	}

}

Square::Square(const string& name, const vector <Point>& verts):
Quadrilateral(name, verts), Rectangle(name, verts), Rhombus(name, verts){
	if(!HasAllEqualSides()){
		throw 69;
	}

}


//===================================================================
//TRIANGLES

Triangle::Triangle(): Polygon(){}

Triangle::Triangle(const string& name, const vector <Point>& verts): 
Polygon(name, verts) {
	if (verts.size() != 3) throw 69; 
}

IsoscelesTriangle::IsoscelesTriangle(const string& name, const vector <Point>& verts):
Triangle(name, verts){
	double side1 = DistanceBetween(verts[0], verts[1]);
	double side2 = DistanceBetween(verts[1], verts[2]);
	double side3 = DistanceBetween(verts[2], verts[0]);
	if(!EqualSides(side1, side2) && !EqualSides(side2, side3)&& 
		!EqualSides(side3, side1)){
			throw 69;
		}
}

EquilateralTriangle::EquilateralTriangle(const string& name,const vector <Point>& verts):
Triangle(name, verts), IsoscelesTriangle(name, verts){
	if(!HasAllEqualSides()){
			throw 69;
	}

}

RightTriangle::RightTriangle(const string& name, const vector <Point>& verts):
Triangle(name, verts){
	if(!HasARightAngle(verts[0], verts[1], verts[2])&&
		!HasARightAngle(verts[1], verts[2], verts[0])&&
		!HasARightAngle(verts[2], verts[0], verts[1])){
			throw 69;
		}

}

IsoscelesRightTriangle::IsoscelesRightTriangle(const string& name, const vector <Point>& verts):
Triangle(name, verts), RightTriangle(name, verts), IsoscelesTriangle(name, verts) {

}

ObtuseTriangle::ObtuseTriangle(const string& name, const vector <Point>& verts):
Triangle(name, verts){
	if(!HasAnObtuseAngle()){
		throw 69;
	}

}

IsoscelesObtuseTriangle::IsoscelesObtuseTriangle(const string& name, const vector <Point>& verts):
Triangle(name, verts), IsoscelesTriangle(name, verts), ObtuseTriangle(name, verts) {

}


//=======================================================================
//OTHER *technically this isn't even a polygon and it makes me angry that
//the class system we were forced to implement says it is because a poly-
//gon is a closed shape

Arrow::Arrow(const string& name, const vector <Point>& verts):
Quadrilateral(name, verts){

}