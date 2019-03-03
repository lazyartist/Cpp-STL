#pragma once
#include <iostream>
#include <vector>

using namespace std;

#define INIT_012 {0, 1, 2}
#define INIT_01234 {0, 1, 2, 3, 4}

#define INIT_012_R {2, 1, 0}

#define INIT_012x10 {10, 11, 12}
#define INIT_01234x10 {10, 11, 12, 13, 14}

#define INIT_012x10_R {12, 11, 10}

template<typename T, typename IterT>
void printContainer(T& v) {
	for (IterT iter = v.begin(); iter != v.end(); ++iter)
	{
		cout << *iter << endl;
	}
}