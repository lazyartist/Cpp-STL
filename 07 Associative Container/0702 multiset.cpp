#include <iostream>
#include <set> // multiset�� ����.
#include "utils.h"

using namespace std;

/*
multiset
	key�� �ߺ� ����Ǵ� �� ����� set�� ���� ����

	���� �� �ߺ��� ���� �������� �ʱ� ������ �ݺ��ڸ� ��ȯ

	�ߺ� ��� ���������� ����ǳ�?
*/
#define INIT_0112 { 0, 1, 1, 2 };

void _0702_multiset() {
	cout << "===== ���� / ���� =====" << endl;
	{
		cout << "--- ����" << endl;
		{
			multiset<int> m = INIT_0112;
			printContainer<multiset<int>, multiset<int>::iterator>(m); // 0, 1, 1, 2
		}
	}

	cout << "===== ã�� =====" << endl;
	{
		cout << "--- count" << endl;
		{
			multiset<int> m = INIT_0112;
			cout << m.count(1) << endl; // 2
		}

		cout << "--- find" << endl;
		{
			multiset<int> m = INIT_0112;
			cout << *m.find(1) << endl; // 1
		}

		cout << "--- lower_bound, upper_bound" << endl;
		{
			multiset<int> m = INIT_0112;
			multiset<int>::iterator lower_iter = m.lower_bound(1);
			multiset<int>::iterator upper_iter = m.upper_bound(1);
			cout << *lower_iter << endl; // 1
			cout << *upper_iter << endl; // 2
		}

		cout << "--- equal_range" << endl;
		{
			multiset<int> m = INIT_0112;
			pair<multiset<int>::iterator, multiset<int>::iterator> equal_pair = m.equal_range(1);
			cout << (*equal_pair.first) << ", " << (*equal_pair.second) << endl; // 1, 2
		}
	}
}