#pragma once
#include <iostream>
#include <vector>

using namespace std;

#define INIT_012 {0, 1, 2}
#define INIT_01234 {0, 1, 2, 3, 4}

#define INIT_210 {2, 1, 0}
#define INIT_43210 {4, 3, 2, 1, 0}

#define INIT_102030 {10, 20, 30}
#define INIT_1020304050 {10, 20, 30, 40, 50}

#define INIT_302010 {30, 20, 10}
#define INIT_5040302010 {50, 40, 30, 20, 10}

template<typename T, typename IterT>
void printContainer(T& v) {
	for (IterT iter = v.begin(); iter != v.end(); ++iter)
	{
		cout << *iter << endl;
	}
}

template<typename T, typename IterT>
void printMap(T& v) {
	for (IterT iter = v.begin(); iter != v.end(); ++iter)
	{
		cout << iter->first << ": " << iter->second << endl;
	}
}