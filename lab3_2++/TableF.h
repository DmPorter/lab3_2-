#pragma once
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <sstream>

struct Point {
	double x, y;
	Point(double x0 = 0, double y0 = 0) :x(x0), y(y0) {}
};

class function
{

	friend std::ostream& operator << (std::ostream&, const function&);
	friend std::istream& operator >> (std::istream&, function&);

public:
	
	function(double x = 0, double y = 0, int i = 0);
	function(double* x);
	function(double* x, double(*f)(double));
	function(Point P);
	function& operator +=(const function&);
	function& operator +=(const Point&);
	function operator +(const Point& A) const;
	function operator +(const function& A) const;
	int SetPoint(double x, double y);
	int findPos(double key) const;
	double GetMinMax(int(*f)(double, double));
	int GetType();
	double operator()(double) const;
	double operator[](const double x);

private:

	static const int SZ = 20;
	Point P[SZ];
	int i; 

};


