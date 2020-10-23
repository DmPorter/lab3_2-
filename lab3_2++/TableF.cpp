
#include "tablef.h"
#include "util.h"
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iostream>

function::function(double x, double y, int i) {
	for (int l = 0; l < this->SZ; l++) {
		this->P[i].x = x;
		this->P[i].y = y;
	}
	this->i = i;
}

function::function(double* x) {
	this->i = 0;
	for (int l = 0; l < this->SZ; l++) {
		SetPoint(*x, 0);
		*x++;
	}
}

function::function(double* x, double(*f)(double)) {
	this->i = 0;
	for (int l = 0; l < this->SZ; l++) {
		SetPoint(*x, f(*x));
		*x++;
	}
}

function::function(Point P) {
	this->i = 0;
	SetPoint(P.x, P.y);
}

function& function::operator +=(const Point& A){

	SetPoint(A.x, A.y);

	return *this;
}

function function::operator +(const Point& A) const {
	function T;

	for (int l = 0; l < this->i; l++){
		T.P[l] = this->P[l];
		T.i = this->i;
	}

	int i = T.i - 1;
	if (i == T.SZ - 1);
	else if (T.P[findPos(A.x)].x == A.x);
	else {
		while (i >= 0 && T.P[i].x > A.x) {
			T.P[i + 1].x = T.P[i].x;
			T.P[i + 1].y = this->P[i].y;
			i = i - 1;
		}
		T.P[i + 1].x = A.x;
		T.P[i + 1].y = A.y;
		T.i++;
	}

	return T;
}

function function::operator +(const function& F) const {
	function T;

	for (int l = 0; l < this->i; l++) {
		T.P[l] = this->P[l];
		T.i = this->i;
	}

	for (int j = 0; j < F.i; j++) {
		int i = T.i - 1;
		if (i == T.SZ - 1);
		else if (T.P[findPos(F.P[j].x)].x == F.P[j].x);
		else {
			while (i >= 0 && T.P[i].x > F.P[j].x) {
				T.P[i + 1].x = T.P[i].x;
				T.P[i + 1].y = this->P[i].y;
				i = i - 1;
			}
			T.P[i + 1] = F.P[j];
			T.i++;
		}
	}
	return T;
}

function& function::operator +=(const function& F) {
	for (int i = 0; i < F.i; i++)
	{
		SetPoint(F.P[i].x, F.P[i].y);
	}
	return *this;
}


int function::SetPoint(double x, double y) {
	int i = this->i - 1;
	if (i == this->SZ - 1)
		return -1;
	else if (this->P[findPos(x)].x == x)
		return -2;
	else {
		while (i >= 0 && this->P[i].x > x) {
			this->P[i + 1].x = this->P[i].x;
			this->P[i + 1].y = this->P[i].y;
			i = i - 1;
		}
		this->P[i + 1].x = x;
		this->P[i + 1].y = y;
		this->i++;
	}
	return 1;
}

int function::findPos(double key) const {
	bool flag = false;
	int l = 0;
	int r = this->i;
	int mid;

	if (this->i == 0 && key == 0)
		return -1;
	while ((l <= r) && (flag != true)) {
		mid = (l + r) / 2; // считываем срединный индекс отрезка [l,r]
		if (this->P[mid].x == key) flag = true;
		if (this->P[mid].x > key)
			r = mid - 1; // проверяем, какую часть нужно отбросить
		else l = mid + 1;
	}
	return mid;
}

std::ostream& operator << (std::ostream& s, const function& st) {
	if (st.i == 0)
		s << "Table is free";
	for (int i = 0; i < st.i; i++)
		s << " i = " << i << ": (" << st.P[i].x << "; " << st.P[i].y << ")" << std::endl << std::endl;
	return s;
}


std::istream& operator >> (std::istream& s, function& st) {
	double x, y;

	s >> x >> y;
	if (!s.good())
		s.setstate(std::ios::failbit);
	else {
		Point P;
		P.x = x;
		P.y = y;
		st += P;
	}

	return s;
}

double function::GetMinMax(int(*f)(double, double))
{
	double res = this->P[0].y;
	int i;
	for (i = 0; i < this->i; ++i)
		if (f(this->P[i].y, res) > 0)
			res = this->P[i].y;
	return res;
}

int function::GetType() {
	if (this->i == 0)
		return -3;
	else if (this->i == 1)
		return 0;
	else {
		int flagi = 0; int flagd = 0; int flagc = 0;
		for (int l = 1; l < this->i; l++) {
			if (this->P[l - 1].y < this->P[l].y)
				flagi = 1;
			else if (this->P[l - 1].y > this->P[l].y)
				flagd = 1;
			else flagc = 1;
			if (flagi == 1 && flagd == 1)
				return -2;
		}
		if (flagi == 1)
			return 1;
		else if (flagd == 1)
			return -1;
		else if (flagc == 1)
			return 0;
	}
}

double function::operator() (double x) const {
	int i = findPos(x);
	double a0, a1;
	if (this->i == 0)
		return 0;
	if (i == 0) i++;
	a1 = (this->P[i].y - this->P[i - 1].y) / (this->P[i].x - this->P[i - 1].x);
	a0 = this->P[i - 1].y - a1 * this->P[i - 1].x;

	return a0 + a1 * x;
}

double function::operator[](const double x) {
	int i = findPos(x);
	double x1 = abs(this->P[i].x - x);
	double x2 = abs(this->P[i + 1].x - x);
	if (min(x1, x2) == x2)
		i++;
	return this->P[i].y;
}