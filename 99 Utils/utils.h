#pragma once
#include <iostream>
#include <vector>

using namespace std;

template<typename T, typename IterT>
void printContainer(T& v) {
	for (IterT iter = v.begin(); iter != v.end(); ++iter)
	{
		cout << *iter << endl;
	}
}