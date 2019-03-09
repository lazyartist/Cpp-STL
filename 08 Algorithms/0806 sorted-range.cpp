#include <iostream>
#include <algorithm>
#include "utils.h"

using namespace std;

/*
���ĵ� ���� �˰���
	sorted range algorithm
	���ĵ� ������������ �����ϴ� �˰���
	�Ϸ� �������� �ݵ�� ���ĵ� �־�� �Ѵ�.
	���Ұ� ������ ���� �� ���� �����̳�ó�� �� ���ҿ� ���� == ������ ������� �ʰ� !(a<b)&&!(b<a) ������ ���
	�⺻ ���� ������ less( < )

binary_search(b,e,x), binary_search(b,e,x,f)
	������ x�� ���� ���Ұ� �ִ°�?
	f�� ������

includes(b,e,b2,e2), includes(b,e,b2,e2,f)
	[b2,e2) ������ ��� ���Ұ� [b,e)���� �ִ°�?
	f�� ������

p=lower_bound(b,e,x), p=lower_bound(b,e,x,f)
	p�� [b,e)���� x�� ���� ù ������ �ݺ���

p=upper_bound(b,e,x), p=upper_bound(b,e,x,f)
	p�� [b,e)���� x���� ū ù ������ �ݺ���

pair(p1,p2)=equal_range(b,e,x), pair(p1,p2)=equal_range(b,e,x,f)
	[p1,p2)�� [b,e)���� x�� ���� ������ �����̴�.
	[lower_bound(), upper_bound)�� ����.

p=merge(b,e,b2,e2,t), p=merge(b,e,b2,e2,t,f)
	[b,e), [b2,e2)�� �պ��� �����Ͽ� [t,p)�� �����Ѵ�.

inplace_merge(b,m,e), inplace_merge(b,m,e,f)
	���ĵ� �ϳ��� ������ [b,m)�� [m,e) �������� [b,e) �������� �պ��Ѵ�.
	
	inplace
		1. ���ڸ��� (�ִ�); ���� ���� �غ� �Ǿ� �ִ�
		2. ���ҿ�

p=set_union(b,e,b2,e2,t), p=set_union(b,e,b2,e2,t,f)
	[b,e)�� [b2,e2)�� ���ĵ� ���������� [t,p)�� �����Ѵ�.
	?

	union
		[����] ������(join, sum); ��ȣ ��

p=set_intersection(b,e,b2,e2,t), p=set_intersection(b,e,b2,e2,t,f)
	[b,e)�� [b2,e2)�� ���ĵ� ���������� [t,p)�� �����Ѵ�.

	intersection
		[����] ����, ����.

p=set_difference(b,e,b2,e2,t), p=set_difference(b,e,b2,e2,t,f)
	[b,e)�� [b2,e2)�� �������� ���ĵ� ���������� [t,p)�� �����Ѵ�.

p=set_symmetric_difference(b,e,b2,e2,t),p=set_symmetric_difference(b,e,b2,e2,t,f)
	[b,e)�� [b2,e2)�� �������� ���ĵ� ��Ī ���������� [t,p)�� �����Ѵ�.

	symmetric 
		��Ī
*/

void _0806_sorted_range() {
	printBlockName("binary_search(b,e,x), binary_search(b,e,x,f)");
	{
		printSubBlockName("�⺻");
		{
			vint v = INIT_01234;
			cout << binary_search(v.begin(), v.end(), 0) << endl; // 1

			// �⺻ ������ less<> ������ ��(������ ������ true)
			cout << binary_search(v.begin(), v.end(), 0, [](const int &i/*�߰���*/, const int &x/*ã�°�*/) {
				cout << i << ", " << x << endl;
				// ����Ž�� �� ����, ���������� �̵��� ������ ���´�.
				// true: ������, false: ����
				return i < x; // ã�� ���� �߰������� ũ�� ������ �������� ã�� ������ ���� �������� ã�´�.
				/*
				2, 0
				1, 0
				0, 0 // 0 < 0 -> false : ������ �ڸ����� false�� �������Ƿ� �ѹ��� ���Ѵ�. : !(a<b)&&!(b<a)
				0, 0 // �� ���� �� �� i�� x�� �ٲ㼭 ���ڷ� �����Ѵ�.(�޸� �ּ� ���� �ٲ㼭 ��)
				*/
			}) << endl; // 1
		}
		
		printSubBlockName("�� ���� ���̰� 3�����̸� ���� ����");
		{
			auto f = [](const int &l/*�߰���*/, const int &r/*ã�°�*/) {
//				return 3 > l - r; // "invalid comparator" ������, �������� �𸣰���.
				return 3 < l - r;
			};

			vint v = {40, 46, 12, 80, 10, 47, 30, 55, 90, 53};
			// �� ���� ���� 3���� ũ�� ���ʿ� ���´�.
			sort(v.begin(), v.end(), f);
			printVector(v); // 90, 80, 55, 53, 46, 47, 40, 30, 12, 10

			// 32�� ���̰� 3������ ���� ã�ƶ�
			cout << binary_search(v.begin(), v.end(), 32, f) << endl; // 1 : 32�� ã�Ҵ�.
			cout << binary_search(v.begin(), v.end(), 88, f) << endl; // 1 : 90�� ã�Ҵ�.
			cout << binary_search(v.begin(), v.end(), 95, f) << endl; // 0 : 92~98 ���̰��� ����.
			printVector(v); // 90, 80, 55, 53, 46, 47, 40, 30, 12, 10
		}
	}

	printBlockName("includes(b,e,b2,e2), includes(b,e,b2,e2,f)");
	{
		vint v1 = {0, 1, 2, 3, 4};
		vint v2 = {3, 4};
		cout << includes(v1.begin(), v1.end(), v2.begin(), v2.end()) << endl;
	}

	printBlockName("p=lower_bound(b,e,x), p=lower_bound(b,e,x,f)");
	{
		vint v = { 0, 0, 1, 2, 1 ,2, 1, 3 };
		// ���ĵ��־���Ѵ�. �ȵ������� �̻��� ����� ���´�.
		sort(v.begin(), v.end()); // 0, 0, 1, 1, 1, 2, 2, 3
		printVector(v);

		vinti iter1 = lower_bound(v.begin(), v.end(), 1);
		vinti iter2 = upper_bound(v.begin(), v.end(), 1);

		cout << *(iter1) << endl; // 1
		cout << *(iter2) << endl; // 2

		while (iter1 != iter2)
		{
			cout << *(iter1++) << endl; // 1, 1, 1
		}
	}
	
	printBlockName("pair(p1,p2)=equal_range(b,e,x), pair(p1,p2)=equal_range(b,e,x,f)");
	{
		vint v = { 0, 0, 1, 2, 1 ,2, 1, 3 };
		// ���ĵ��־���Ѵ�. �ȵ������� �̻��� ����� ���´�.
		sort(v.begin(), v.end()); // 0, 0, 1, 1, 1, 2, 2, 3
		printVector(v);

		pair<vinti, vinti> p = equal_range(v.begin(), v.end(), 1);
		//vinti iter2 = upper_bound(v.begin(), v.end(), 1);

		cout << *(p.first) << endl; // 1
		cout << *(p.second) << endl; // 2

		while (p.first != p.second)
		{
			cout << *(p.first++) << endl; // 1, 1, 1
		}
	}
	
	printBlockName("p=merge(b,e,b2,e2,t), p=merge(b,e,b2,e2,t,f)");
	{
		vint v1 = INIT_012;
		vint v2 = INIT_210;
		vint v3(v1.size() + v2.size());

		// ���� �ȵ� ������ "sequence not ordered" ����.
		sort(v2.begin(), v2.end());

		merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
		printVector(v3); // 0, 0, 1, 1, 2, 2 : �����ϸ� ������ �Ѵ�.
	}
	
	printBlockName("inplace_merge(b,m,e), inplace_merge(b,m,e,f)");
	{
		vint v = { 1, 2, 3, 10, 11, 12, 5, 6, 7, 20, 21, 22 };
		inplace_merge(v.begin(), v.begin() + 6, v.end());
		printVector(v); // 1, 2, 3, 5, 6, 7, 10, 11, 12, 20, 21, 22
	}
	
	printBlockName("p=set_union(b,e,b2,e2,t), p=set_union(b,e,b2,e2,t,f)");
	{
		vint v1 = INIT_012;
		vint v2 = INIT_01234;
		vint v3(v1.size() + v2.size());

		set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
		printVector(v3); // 0, 1, 2, 3, 4, 0, 0, 0 : 0, 1, 2�� �������̹Ƿ� �ϳ��� ����.
	}
	
	printBlockName("p=set_intersection(b,e,b2,e2,t), p=set_intersection(b,e,b2,e2,t,f)");
	{
		vint v1 = INIT_012;
		vint v2 = INIT_01234;
		vint v3(v1.size() + v2.size());

		set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
		printVector(v3); // 0, 1, 2, 0, 0, 0, 0, 0 : 3, 4�� �������̹Ƿ� ©�ȴ�.
	}
	
	printBlockName("p=set_difference(b,e,b2,e2,t), p=set_difference(b,e,b2,e2,t,f)");
	{
		vint v1 = INIT_012;
		vint v2 = INIT_01234;
		vint v3(v1.size() + v2.size());

		set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
		printVector(v3); // 0, 0, 0, 0, 0, 0, 0, 0 : v1���� v2�� ���� �� ������.

		set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), v3.begin());
		printVector(v3); // 3, 4, 0, 0, 0, 0, 0, 0 : v2���� v1�� ���� �� 3, 4�� ���Ҵ�.
	}
	
	printBlockName("p=set_symmetric_difference(b,e,b2,e2,t),p=set_symmetric_difference(b,e,b2,e2,t,f)");
	{
		vint v1 = { 0, 1, 2, 5, 6 };
		vint v2 = { 0, 1, 2, 3, 4 };
		vint v3(v1.size() + v2.size());

		set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
		printVector(v3); // 3, 4, 5, 6, 0, 0, 0, 0, 0, 0 : ��� ���տ� ���Ե��� �ʴ� ���Ҹ� ���Ҵ�.
	}
}