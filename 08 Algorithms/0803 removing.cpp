#include <iostream>
#include <algorithm>
#include "utils.h"

using namespace std;

/*
removing algorithm
	���Ҹ� �������� �ʴ� �˰����� Ư���� ����
	���Ҹ� ������ �������� �ʰ� �������� ����(���� ���ҷ� �����)�ϱ� ������
	�������� size�� �����δ�(? capacity�� �������� �ʰ� ���̴� size�� �����Ѵ�?)�������� �ʴ´�.
	���� size�� �����Ϸ��� �����̳��� erase() ��� �Լ��� �̿�

p=remove(b,e,x)
	x�� ���� �ʵ��� ������ �̵�(�ڿ��� ��ܿ´�)
	���� size�� ������� ������ remove�� erase�� �Բ� ����Ͽ� size�� ���� �� �ִ�.

p=remove_if(b,e,f)
	f(*p)�� ���� ���Ұ� ���� �ʵ��� ������ �̵�

p=remove_copy(b,e,t,x)
	x�� �ƴ� ���Ҹ� [t,p)�� �����Ѵ�.
	������ �������� ����

p=remove_copy_if(b,e,t,f)
	f(*p)�� ���� �ƴ� ���Ҹ� [t,p)�� ����

p=unique(b,e)
	������ �ߺ� ���Ұ� ���� �ʰ� ������ �̵�
	��� ���Ҹ� �����ϰ� ������� ���� �� �����Ѵ�.
	�������θ� �����Ѵ�.
	���� ������ �����Ϸ��� ���� �� unique ������ �� erase�� �����Ѵ�.

p=unique(b,e,f)
	f(*p,*(p+1))�� ���� ���� ����

p=unique_copy(b,e,t)
	������ �ߺ� ���Ұ� �ƴ� ���Ҹ� [t,p)�� ����

p=unique_copy(b,e,t,f)
	f(*p,*(p+1))�� ���� ������ �ߺ� ���Ұ� �ƴ� ���Ҹ� [t,p)�� ����

*/

void _0803_removing() {
	printBlockName("p=remove(b,e,x)");
	{
		vint v = INIT_012;
		vinti iter = remove(v.begin(), v.end(), 1);
		printVector(v); // 0, 2, 2 : 1�� ���ŵǰ� ���� 2�� ���� ���δ�.
		printInts(v.size(), v.capacity()); // 3, 3 : size�� ���� �ʾҴ�.

		// erase�� size���� ���δ�.
		v.erase(iter, v.end());
		printVector(v); // 0, 2
		printInts(v.size(), v.capacity()); // 1, 3
	}

	printBlockName("p=remove_if(b,e,f)");
	{
		vint v = { 0, 1, 1 };
		vinti iter = remove_if(v.begin(), v.end(), [](int &i) -> bool {
			return i == 0;
		});
		printVector(v); // 1, 1, 1 : 0�� ���ŵǰ� ���� 1�� ���� ���δ�.
		printInts(v.size(), v.capacity()); // 3, 3

		// erase�� size���� ���δ�.
		v.erase(iter, v.end());
		printVector(v); // 1, 1
		printInts(v.size(), v.capacity()); // 2, 3
	}

	printBlockName("p=remove_copy(b,e,t,x)");
	{
		vint v1 = INIT_012;
		vint v2(v1.size());

		remove_copy(v1.begin(), v1.end(), v2.begin(), 1);
		printVector(v1); // 0, 1, 2
		printVector(v2); // 0, 2, 0 : 1�� �����ϰ� ����ƴ�.
	}

	printBlockName("p=remove_copy_if(b,e,t,f)");
	{
		vint v1 = { 1, 10, 2, 20, 3, 30 };
		vint v2(v1.size());

		// 10������ ���ڸ� ����
		remove_copy_if(v1.begin(), v1.end(), v2.begin(), [](int &i) -> bool {
			return i > 10; // true�̸� �������� �ʱ� ������ 10�̻��� ���ڸ� �����Ѵ�.
		});
		printVector(v1); // 1, 10, 2, 20, 3, 30
		printVector(v2); // 1, 10, 2, 3, 0, 0 : 10������ ���ڸ� �����
	}

	printBlockName("p=unique(b,e)");
	{
		vint v = { 0, 1, 1, 2, 3, 1, 9 };

		unique(v.begin(), v.end());
		printVector(v); // 0, 1, 2, 3, 1, 9, 9 : ������ ���Ҹ� ����

		sort(v.begin(), v.end());
		printVector(v); // 0, 1, 1, 2, 3, 9, 9 : ����

		vinti iter = unique(v.begin(), v.end());
		printVector(v); // 0, 1, 2, 3, 9, 9, 9 : ���� �� ��� ���� ���� ����(���� 9�� �������� ���ŵǼ� ��������)

		v.erase(iter, v.end());
		printVector(v); // 0, 1, 2, 3, 9 : ��� �ߺ� ���� ������ ����
	}

	printBlockName("p=unique(b,e,f)");
	{
		vint v = { 0, 1, 1, 2, 3, 1, 9 };

		unique(v.begin(), v.end(), [](int &l, int &r) -> bool {
			return l == r;
		});
		printVector(v); // 0, 1, 2, 3, 1, 9, 9 : ������ ���Ҹ� ����
	}

	printBlockName("p=unique_copy(b,e,t)");
	{
		vint v1 = { 0, 1, 1, 2, 3, 1, 9 };
		vint v2(v1.size());

		unique_copy(v1.begin(), v1.end(), v2.begin());
		printVector(v1);
		printVector(v2); // 0, 1, 2, 3, 1, 9, 0 : �ߺ� ���Ҹ� �����ϰ� ����
	}

	printBlockName("p=unique_copy(b,e,t,f)");
	{
		vint v1 = { 0, 1, 1, 2, 3, 1, 9 };
		vint v2(v1.size());

		sort(v1.begin(), v1.end());
		printVector(v1); // 0, 1, 1, 1, 2, 3, 9 : ����

		unique_copy(v1.begin(), v1.end(), v2.begin(), [](int &l, int &r) -> bool {
			return l == r;
		});
		printVector(v2); // 0, 1, 2, 3, 9, 0, 0 : �ߺ� ���Ҹ� �����ϰ� ����
	}
}