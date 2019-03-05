#include <iostream>
#include <algorithm>
#include "utils.h"

using namespace std;

/*
modifying algorithms
	������ ���� �����ϰų� ������ �������� ���Ҹ� �����ϴ� �˰���

copy(b,e,t)
	[b, e)�� �������� ���� [t, t+(e-b))�� �������� ��� ����
	�⺻������ ������ �۵��ϸ� �������� �۵��ϰ� �Ϸ��� �ݺ��� �����(insert_iterator)���� ���
	���� �������� ���� ������ �̻��� ���Ҹ� ������ �־����
	��ȯ�� : ���� �������� ������ ����

copy_backward(b,e,t)
	[b,e)�� ���Ҹ� [t-(e-b), t) �������� ���� ���������� �ݴ�� ����
	��ȯ�� : ���� �������� ù ����

fill(b,e,x)
	[b,e) ������ ���Ҹ� x�� ä���

fill_n(b,n,x)
	[b,b+n) ������ ���Ҹ� x�� ä���

for_each(b,e,f)
	[b,e) ������ ��� ���ҿ� f(*p)�� ����(p�� �ݺ���)
	f�� �Լ� ��ü, �Լ�, �Լ� ������, ����
	��� �Ű�����(out parameter)�� ����Ͽ� ���Ҹ� ����
		for_each�� ����Ͽ� ���Ҹ� ����ÿ��� ��� �Ű������� �ݵ�� ���۷����� �����ؾ��Ѵ�.

generate(b,e,f)
	[b,e) ������ ��� ���ҿ� f()�� ����
		�ܼ� f()�� ��ȯ���� �����ϱ� ������ ������ �������� Ȱ���� �� ����.
		���� �Լ� ��üó�� ���°��� ���� �Լ��� ����ؾ� ���������� �ٸ� ���� ������ �� �ִ�.

swap(a,b)
	a�� b�� ��ȯ

iter_swap(p,q)
	�ݺ��ڰ� ����Ű�� *p�� *q�� ��ȯ

merge(b,e,b2,e2,t)
	���ĵ� �� �������� �ϳ��� ���ĵ� �������� ����
		Ư�� �����ڷ� ���ĵ� ���¶�� merge �� �ش� �����ڸ� ����Ѵ�.
	[b,e), [b2,e2)�� �����Ͽ� [t, t+(e-b)+(e2-b2)) �������� �����.
	������ �� �ݺ��ڸ� ��ȯ�Ѵ�.

replace(b,e,x,x2)
	x�� ���Ҹ� ��� x2�� ����

replace_if(b,e,f,x2)
	����ڰ� ������ ���ǿ� �´� ���Ҹ� ��� ����
	f(*p)�� ���� ���Ҹ� ��� x2�� ����

replace_copy(b,e,t,x,x2)
	[b,e) ������ x���Ҹ� x2�� �����Ͽ� [t,p)�� ����
	������ ������� �ʴ´�

replace_copy_if(b,e,t,f,x2)
	[b,e) ������ f(*p)�� ���� ���Ҹ� x2�� �����Ͽ� [t,p)�� ����
	������ ������� �ʴ´�

swap_ranges(b,e,b2)
	[b,e)�� [b2,b2+(e-b))�� ��� ���Ҹ� ��ȯ
	���� ������ ���ƾ��Ѵ�.

transform(b,e,t,f)
	f(*p)�� ȣ���Ͽ� ��ȯ���� [t,t+(e-b))�� ����(�����)
	�Լ��� ��ȯ���� ����Ͽ� �������� ���Ҹ� ����, ������ ������� �ʴ´�.
	transform�� ��ȯ�� : ���� �������� �� �ݺ���

transform(b,e,b2,t,f)
	����� ������ �� �������� ���ҿ� �����ϰ� ��3�� �������� ����
	[b,e), [t,t+(e-b)) �������� �ݺ��ڸ� f(*p, *q)�� ��ȯ���� [t,t+(e-b))�� ����
*/

void _0802_modifying() {
	printBlockName("copy(b,e,t)", false);
	{
		vector<int> v1 = INIT_012;
		vector<int> v2(v1.size()*2);

		copy(v1.begin(), v1.end(), v2.begin());
		printVector(v1); // 0, 1, 2
		printVector(v2); // 0, 1, 2, 0, 0, 0
	}

	printBlockName("copy_backward(b,e,t)");
	{
		vector<int> v1 = INIT_012;
		vector<int> v2(v1.size()*2);

		copy_backward(v1.begin(), v1.end(), v2.end());
		printVector(v1); // 0, 1, 2
		printVector(v2); // 0, 0, 0, 0, 1, 2
	}

	printBlockName("fill(b,e,x) / fill_n(b,n,x)");
	{
		vector<int> v(5);
		printVector(v); // 0, 0, 0, 0, 0

		fill(v.begin(), v.end(), 9);
		printVector(v); // 9, 9, 9, 9, 9

		fill_n(v.begin(), 2, 0);
		printVector(v); // 0, 0, 9, 9, 9
	}

	printBlockName("for_each(b,e,f)");
	{
		vint v = INIT_012;
		// ��� ���ҿ� +10
		for_each(v.begin(), v.end(), [](int& i) -> void {
			i += 10;
		});
		printVector(v); // 10, 11, 12
	}

	printBlockName("generate(b,e,f)");
	{
		vint v(5);
		int i = 0;
		generate(v.begin(), v.end(), [&i]() -> int {
			return i++;
		});
		printVector(v); // 0, 1, 2, 3, 4
	}

	printBlockName("swap(a,b) / iter_swap(p,q)");
	{
		int a = 0;
		int b = 1;
		swap(a, b);
		printInts(a, b); // 1, 0

		vint v1 = INIT_012;
		vint v2 = INIT_210;
		iter_swap(v1.begin(), v2.begin()); // �� ���� ���Ҹ� �ٲ��ش�.
		printVector(v1); // 2, 1, 2
		printVector(v2); // 0, 1, 0
	}

	printBlockName("merge(b,e,b2,e2,t)");
	{
		vint v1 = INIT_012;
		vint v2 = INIT_012; // ���ĵǾ� �־���Ѵ�.
		vint v3(v1.size() + v2.size());

		merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
		printVector(v3); // 0, 0, 1, 1, 2, 2
	}

	printBlockName("replace(b,e,x,x2)");
	{
		vint v = { 0,0,0,1,1,1,2,2,2 };
		replace(v.begin(), v.end(), 1, 9); // 1�� ��� 9�� ����
		printVector(v); // 0, 0, 0, 9, 9, 9, 2, 2, 2
	}

	printBlockName("replace_if(b,e,f,x2)");
	{
		vint v = { 0,0,0,1,1,1,2,2,2 };
		// 2�� ��� 9�� ����
		replace_if(v.begin(), v.end(), [](int &i) -> bool {
			return i == 2;
		}, 9);
		printVector(v); // 0, 0, 0, 1, 1, 1, 9, 9, 9
	}

	printBlockName("replace_copy(b,e,t,x,x2)");
	{
		vint v1 = { 0,0,0,1,1,1,2,2,2 };
		vint v2(v1.size());
		// 2�� ��� 9�� �����Ͽ� ����
		replace_copy(v1.begin(), v1.end(), v2.begin(), 2, 9);
		printVector(v1); // 0, 0, 0, 1, 1, 1, 2, 2, 2 : ������ ������� �ʾҴ�.
		printVector(v2); // 0, 0, 0, 1, 1, 1, 9, 9, 9
	}

	printBlockName("replace_copy_if(b,e,t,f,x2)");
	{
		vint v1 = { 0,0,0,1,1,1,2,2,2 };
		vint v2(v1.size());
		// 2���� ���� ���� ��� 9�� �����Ͽ� ����
		replace_copy_if(v1.begin(), v1.end(), v2.begin(), [](int &i) -> bool {
			return i < 2;
		}, 9);
		printVector(v1); // 0, 0, 0, 1, 1, 1, 2, 2, 2
		printVector(v2); // 9, 9, 9, 9, 9, 9, 2, 2, 2
	}

	printBlockName("swap_ranges(b,e,b2)");
	{
		vint v1 = INIT_01234;
		vint v2 = INIT_210;
		swap_ranges(v1.begin(), v1.end()-2, v2.begin()); // end-2�� ���̸� �����ش�.
		printVector(v1); // 2, 1, 0, 3, 4
		printVector(v2); // 0, 1, 2
	}

	printBlockName("transform(b,e,t,f)");
	{
		vint v1 = INIT_012;
		vint v2(v1);
		transform(v1.begin(), v1.end(), v2.begin(), [](int &i) -> int {
			return i + 10;
		});
		printVector(v1); // 0, 1, 2
		printVector(v2); // 10, 11, 12
	}

	printBlockName("transform(b,e,b2,t,f)");
	{
		vint v1 = INIT_012;
		vint v2 = INIT_012;
		vint v3(v1.size());
		transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), [](int &l, int &r) -> int {
			return l + r;
		});
		printVector(v1); // 0, 1, 2
		printVector(v2); // 0, 1, 2
		printVector(v3); // 0, 2, 4
	}
}