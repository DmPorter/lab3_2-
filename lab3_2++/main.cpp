#pragma once
#include"tablef.h"
#include"menu.h"
#include"util.h"
#include <iostream>


int main() {
	Point P1 = { 0, 1 };
	function f1(P1);
	Point P2 = { 2, 2 };
	Point P3 = { 3, 4 };
	Point P4 = { 5, 4 };
	function f4(P4);
	function f3;
	f3 = f1 + P2 + f4 + P3;
	std::cout << f3 << std::endl;
	std::cout << f3[2.5];
	//function table;
	//dialog(table);
	return 0;
}