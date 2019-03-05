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


// ===== �Լ� ���ø� ===== //

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


// ===== ���� ���� �Լ� ���ø�(Variadic Template)  ===== //

// ����� ���Ḧ ���� ���ھ��� �Լ��� �ʿ�
inline void print() {
}

// �Ķ���Ͱ� �ϳ� ������ �� Ÿ���� int�� ��� ȣ��� �Լ�
// �������� �ʰų� Ÿ���� int�� �ƴѰ�� print(T i) �Լ��� ȣ��ȴ�.
inline void print(int i) {
	cout << i << endl;
}

// �Ķ���Ͱ� �ϳ� ������ �� ȣ���� �����ε� �Լ�
// �������� ������ print(T& i, Ts& ... args) �Լ��� ȣ��ȴ�.
template<typename T>
void print(T i) {
	cout << i << endl;
}

template<typename T, typename ... Ts>
void print(T& i, Ts& ... args) {
	cout << i << ", ";
	//cout << sizeof...(args) << endl; // �Ķ������ ����

	print(args...);

	// ������ �̷��� ���ø� Ÿ���� ����ϸ� ������ ��������.
//	print<T, Ts...>(args...); // 'print': �Լ��� 1���� �Ű� ������ ������� �ʽ��ϴ�. 
}

// ��� ó���� //�� ����Ϸ��� �Լ��� �ϳ� �� ����
// todo? size_type�� �ѱ���ϴ� ������ ����. const�� ���̴� ������ �ȳ���. ��? "unsigned int���� T&�� ��ȯ�� �� �����ϴ�." ����.
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