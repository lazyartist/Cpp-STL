#include <iostream>
#include <set>
#include <algorithm>
#include "utils.h"

using namespace std;

/*
set
	��ǥ���� ���� �����̳����� ��� �����̳�

	��� ���Ҵ� �����ϴ�
	�ߺ��� ����Ϸ��� multiset�� �̿��Ѵ�.

	key�� �Ҹ��� ���Ҹ� ���� ���ؿ� ���� ���� ����Ʈ���� �����ϸ�
	�� key ���Ұ� ����, �˻�, ���� � ��� �̿�ǹǷ� key�� ������ �� ����

���� �����̳��� Ư¡
	Ư�� ���� ���ؿ� ���� ���Ұ� �ڵ� ���ĵǴ� �����̳�

	push_back, push_front, pop_back, pop_front ���� ���Ҹ� �����̳� ��, �ڿ� �߰�/�����ϴ� �Լ��� �������� ����
	
	front(), back() �������� ����
	
	���� ����Ʈ���� ���� ���� ã�Ⱑ ����(�α� �ð� ���⵵)

���� ����
	���� �������̽��� insert �� �ϳ��� �����Ѵ�.
	
	pair ��ü�� ��ȯ�ϰ� �� ��ü�� second�� ������ ����/���и� �� �� �ִ�.
	
	���Կ� �����ϸ� pair.first�� ���Ե� ���Ҹ� ����Ű�� �ݺ����̰�
	�����ϸ� �̹� ���Ե� ���Ҹ� ����Ű�� �ݺ����̴�.

	���Ե� �α� �ð� ���⵵�� ���´�.

	��ġ ���� �� ���� �����Ͽ� ���Ե� �����ϴ�.
		��ġ ���� �� ���� ��ġ�� ���ļ����� �´ٸ� �ٷ� ���Ե����� �ƴ϶�� �α� �ð��� �ɸ���.

���� ã��
	���� ���� Ʈ���� �����Ǿ� �α� �ð� ���⵵�� ���´�.

ã�� ��� �Լ�
	count, find, lower_bound, upper_bound, equal_range

�ݺ���
	����� �ݺ��� ����
	begin, end, rbegin, rend

������
	�����ڸ� ��ȯ�Ѵ�. 
	key_comp(), value_comp() 
*/

void _0701_set() {
	cout << "===== ���� / ���� =====" << endl;
	{
		cout << "--- ����" << endl;
		{
			set<int> s = INIT_210;
			printContainer<set<int>, set<int>::iterator>(s); // 0, 1, 2 : �������� �ʾƵ� �ڵ� ���ĵǾ��ִ�.
		}

		cout << "--- ����" << endl;
		{
			set<int> s = INIT_210;

			pair<set<int>::iterator, bool> p = s.insert(2);
			cout << *p.first << ", " << p.second << endl; // 2, 0 : �ߺ��Ǿ� ���� ����

			p = s.insert(3);
			cout << *p.first << ", " << p.second << endl; // 3, 1 : �ߺ� �ȵǾ� ���� ����

			printContainer<set<int>, set<int>::iterator>(s); // 0, 1, 2, 3
		}

		cout << "--- ��ġ ���� ����" << endl;
		{
			set<int> s = INIT_102030;

			set<int>::iterator iter = s.end();
			s.insert(iter, 25);
			s.insert(iter, 1);

			printContainer<set<int>, set<int>::iterator>(s); // 10, 20, 25, 30
		}

		cout << "--- Ű�� ���� �Ұ�" << endl;
		{
			set<int> s = INIT_012;
			set<int>::iterator iter = s.begin();
//			*iter = 1; // Ű �� ���� �Ұ�
		}
	}

	cout << "===== ������ =====" << endl;
	{
		cout << "--- ������ ����" << endl;
		{
			/*
			�����ڸ� ���ø� Ÿ������ ����
			*/
			set<int, greater<int>> s1 = INIT_012;

			/*
			�����ڸ� const ������ �����ϰ� ����
			*/
			const greater<int> g;
			set<int, greater<int>> s2(g); // �����ϸ� �ʱ�ȭ �� �� ����.
			s2 = INIT_012; // ���⼭�� �ʱ�ȭ ����

//			set<int, greater<int>> s3(greater<int>()); // �ӽð�ü�� �޴� �����ڴ� ������ s3 �Լ� �������� �νĵȴ�. ������ �ȳ����� s3�� �Լ��� �ν��Ѵ�.

			printContainer<set<int, greater<int>>, set<int, greater<int>>::iterator>(s1); // 2, 1, 0
			printContainer<set<int, greater<int>>, set<int, greater<int>>::iterator>(s2); // 2, 1, 0
		}

		cout << "--- ������ ��ȯ" << endl;
		{
			set<int> s1;
			set<int, greater<int>> s2;

			/*
			typedef ���� ���� ���� key_compare, value_compare ���
			*/
			set<int>::key_compare less_key_comp = s1.key_comp(); // Ű ������
			set<int, greater<int>>::value_compare greater_value_comp = s2.value_comp(); // �� ������

			// �Ʒ��� ��� ���������� �� �� ��Ȯ�� �ڵ带 ���� ��ó�� typedef �� Ÿ���� ����ϴ°� ����.
//			less<int> less_key_comp = s1.key_comp(); // Ű ������
//			greater<int> greater_value_comp = s2.value_comp(); // �� ������

			cout << less_key_comp(1, 2) << endl; // 1
			cout << greater_value_comp(1, 2) << endl; // 0
		}
	}

	cout << "===== ã�� =====" << endl;
	{
		cout << "--- ���� ���� ��ȯ count()" << endl;
		{
			/*
			set�� ���Ұ� �ϳ��̹Ƿ� count�� ���� �ʿ������ 
			���� �����̳��� �������̽� ������ ���� �����Ѵ�.
			����ð��� �α� �ð� ���⵵
			*/
			set<int> s = INIT_012;
			cout << s.count(1) << endl; // 1
			cout << s.count(9) << endl; // 0
		}

		cout << "--- ���� ã�� ��ȯ find()" << endl;
		{
			/*
			key�� �˻��Ͽ� key�� ����Ű�� �ݺ��ڸ� ��ȯ
			�˻� �� == ������ ���� �ʰ� !(a < b) && !(b < a) �̸� ���ٰ� �Ǵ��Ѵ�.
			��, a�� b���� �ռ� ���� �ʰ� b�� a���� �ռ� ���� ������ a�� b�� ���ٰ� �Ǵ��Ѵ�.
				���Ŀ� �����ڸ� ����ϱ� ������ �����ڸ� �״�� ����ؼ� �׷����ϴ�.
			*/
			set<int> s = INIT_012;
			set<int>::iterator iter = s.find(1);
			cout << *iter << ", " << (iter == s.end()) << endl; // 1, 0 : ã�� ����

			iter = s.find(9);
			cout << (iter == s.end()) << endl; // 1 : ã�� ����
											   // iter�� ��ȿ�� ���� �ƴ϶� �����ϸ� "cannot dereference end map/set iterator" ���� �߻�.
		}

		cout << "--- ���� ��ȯ lower_bound(), upper_bound()" << endl;
		{
			/*
			ã�� ���Ҹ� ���ڿ� ����(�ݺ��� ��)���� ��ȯ
				lower_bound() : ã�� ������ ���� �ݺ���
				upper_bound() : ã�� ������ ���� ������ �ݺ���

			set �����̳ʿ��� �ǹ̴� ũ�� ������ �ߺ� ���Ҹ� ���� multiset, multimap���� ������.

			find�� ���������� ã�⿡ �����ϸ� end() �ݺ��ڸ� ��ȯ��
				lower_bound�� upper_bound �ݺ��ڰ� ������ ã�� ���Ұ� ����.(�� ����� ���� ���̴�)
			*/
			set<int> s = INIT_01234;
			set<int>::iterator lower_iter = s.lower_bound(2);
			set<int>::iterator upper_iter = s.upper_bound(2);
			cout << *lower_iter << endl; // 2
			cout << *upper_iter << endl; // 3


			upper_iter = s.upper_bound(9);
			cout << (upper_iter == s.end()) << endl; // 1 : ����, end()�� ����Ų��
		}

		cout << "--- ���� ��ȯ equal_range()" << endl;
		{
			/*
			ã�� ���ҵ��� ������ pair�� ��ȯ
			*/
			set<int> s = INIT_01234;
			pair<set<int>::iterator, set<int>::iterator> equal_iter = s.equal_range(2);

			cout << *equal_iter.first << ", " << *equal_iter.second << endl;

			equal_iter = s.equal_range(9);
			cout << (equal_iter.first == equal_iter.second) << endl; // 1 : ����, first�� second�� ����.
		}
	}

}