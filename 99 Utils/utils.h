#pragma once
#include <iostream>
#include <vector>

using namespace std;

// ===== define ===== //

#define INIT_012 {0, 1, 2}
#define INIT_01234 {0, 1, 2, 3, 4}

#define INIT_0112 {0, 1, 1, 2}

#define INIT_210 {2, 1, 0}
#define INIT_43210 {4, 3, 2, 1, 0}

#define INIT_102030 {10, 20, 30}
#define INIT_1020304050 {10, 20, 30, 40, 50}

#define INIT_302010 {30, 20, 10}
#define INIT_5040302010 {50, 40, 30, 20, 10}


// ===== typedef ===== //
typedef vector<int> vint;
typedef vector<int>::iterator vinti;


// ===== 함수 템플릿 ===== //

template<typename T, typename IterT>
void printContainer(T& v, char ch = '\n') {
	bool first = true;
	for (IterT iter = v.begin(); iter != v.end(); ++iter)
	{
		if (first) {
			cout << " // ";
		}
		else {
			cout << ch;
			if (ch != '\n') {
				cout << ' ';
			}
		}

		cout << *iter;

		first = false;
	}

	if (ch != '\n') {
		cout << endl;
	}
}

inline void printVector(vector<int>& v) {
	printContainer<vector<int>, vector<int>::iterator>(v, ',');
}

template<typename T, typename IterT>
void printMap(T& v) {
	for (IterT iter = v.begin(); iter != v.end(); ++iter)
	{
		cout << iter->first << ": " << iter->second << endl;
	}
}


// ===== 가변 인자 함수 템플릿(Variadic Template)  ===== //

// 재귀의 종료를 위해 인자없는 함수가 필요
inline void print() {
}

// 파라미터가 하나 남았을 때 타입이 int인 경우 호출될 함수
// 정의하지 않거나 타입이 int가 아닌경우 print(T i) 함수가 호출된다.
inline void print(int i) {
	cout << i << endl;
}

// 파라미터가 하나 남았을 때 호출할 오버로딩 함수
// 정의하지 않으면 print(T& i, Ts& ... args) 함수가 호출된다.
template<typename T>
void print(T i) {
	cout << i << endl;
}

template<typename T, typename ... Ts>
void print(T& i, Ts& ... args) {
	cout << i << ", ";
	//cout << sizeof...(args) << endl; // 파라미터의 개수

	print(args...);

	// 오히려 이렇게 템플릿 타입을 명시하면 컴파일 에러난다.
//	print<T, Ts...>(args...); // 'print': 함수는 1개의 매개 변수를 사용하지 않습니다. 
}

// 재귀 처음에 //를 출력하려고 함수를 하나 더 만듦
// todo? size_type을 넘기려하니 에러가 났다. const를 붙이니 에러가 안났다. 왜? "unsigned int에서 T&로 변환할 수 없습니다." 에러.
template<typename T, typename ... Ts>
void printInts(const T& i, const Ts& ... args) {
	cout << " // ";
	print(i, args...);
}


// ===== Utilities Function ===== //
inline void printBlockName(const char* str, bool newline = true) {
	if (newline) cout << endl;
	cout << "===== " << str << endl;
}

//inline void printSubBlockName(const char* str, bool newline = true) {
inline void printSubBlockName(const char* str) {
	//if (newline) cout << endl;
	cout << "--- " << str << endl;
}