#include <iostream>
#include <map>
#include "utils.h"

using namespace std;

/*
map
	���� �����̳����� ��� ��� �����̳�

	Ư�� �������� ���Ұ� �ڵ� ����

	���Ҵ� key�� value ������ �̷����

	[]�����ڸ� �̿��� ���Ҹ� �߰��ϰų� value�� ������ ��ȯ

	���� �����̳��̹Ƿ� ��/�ڿ� �߰�/�����ϴ� �Լ��� �������� ����.

	���� �����̳ʴ� ���� ���� ã�⸦ ���� ���� ���� Ʈ���� �̿��� �α� �ð� ���⵵�� ����

	�������� set�� ����
*/

void _0703_map() {
	cout << "===== ���� =====" << endl;
	{
		cout << "--- ����" << endl;
		{
			map<int, double> m = { {1, 1.0} }; // �ʱ�ȭ�� ����
			printMap<map<int, double>, map<int, double>::iterator>(m);
		}

		cout << "--- ���� ��ȯ��" << endl;
		{
			map<int, double> m = { {1, 1.0} };
			pair<map<int, double>::iterator, bool> iter = m.insert(pair<int, double>(2, 2.0));

			cout << iter.first->first << " : " << iter.first->second << ", " << iter.second << endl; // 2 : 2, 1
			// first : ���Ե� pair�� ����Ű�� iterator, second : ���� ���� ����

			iter = m.insert(pair<int, double>(2, 3.0)); // ���� Ű�� ������
			cout << iter.first->first << " : " << iter.first->second << ", " << iter.second << endl; // 2 : 2, 0
			// ���Կ� �����ϰ� �̹� �ִ� ���Ҹ� ����Ų��.

			printMap<map<int, double>, map<int, double>::iterator>(m);
		}

		cout << "--- [] ������" << endl;
		{
			map<int, double> m = { {1, 1.0} };
			m[2] = 2.0; // ������ ����
			printMap<map<int, double>, map<int, double>::iterator>(m); // 1 : 1, 2 : 2

			m[2] = 3.0; // �̹� ������ ����
			printMap<map<int, double>, map<int, double>::iterator>(m); // 1 : 1, 2 : 3
		}
	}

	cout << "===== ���� =====" << endl;
	{
		cout << "--- ������ ����" << endl;
		{
			map<int, double, greater<int>> m = { {1, 1.0}, {2, 2.0}, {3, 3.0} };
			printMap<map<int, double, greater<int>>, map<int, double>::iterator>(m); // 3 : 3, 2 : 2, 1 : 1
		}
	}

	cout << "===== ã�� =====" << endl;
	{
		cout << "--- count" << endl;
		{
			/*
			set�� ���������� �ߺ��� ������� �����Ƿ� ū �ǹ̴� ����.
			*/
			map<int, double> m = { {1, 1.0}, {2, 2.0}, {3, 3.0} };
			cout << m.count(1) << endl;
		}

		cout << "--- find" << endl;
		{
			/*
			ã�� ���Ҹ� ����Ű�� �ݺ��� ��ȯ
			*/
			map<int, double> m = { {1, 1.0}, {2, 2.0}, {3, 3.0} };
			map<int, double>::iterator iter = m.find(2);
			cout << iter->first << " : " << iter->second << endl; // 2 : 2
		}

		cout << "--- lower_bound, upper_bound" << endl;
		{
			/*
			lower_bound : ã�� ������ ù ��°
			upper_bound : ã�� ������ ���� ���� ����
			*/
			map<int, double> m = { {1, 1.0}, {2, 2.0}, {3, 3.0} };
			map<int, double>::iterator lower_iter = m.lower_bound(2);
			map<int, double>::iterator upper_iter = m.upper_bound(2);
			cout << lower_iter->first << " : " << lower_iter->second << endl; // 2 : 2
			cout << upper_iter->first << " : " << upper_iter->second << endl; // 3 : 3
		}

		cout << "--- equal_range" << endl;
		{
			/*
			pair.first : ã�� ������ ù ��°
			pair.second : ã�� ������ ���� ���� ����
			*/
			map<int, double> m = { {1, 1.0}, {2, 2.0}, {3, 3.0} };
			pair<map<int, double>::iterator, map<int, double>::iterator> pair = m.equal_range(2);
			map<int, double>::iterator upper_iter = m.upper_bound(2);
			cout << pair.first->first << " : " << pair.first->second << endl; // 2 : 2
			std::cout << pair.second->first << " : " << pair.second->second << endl; // 3 : 3
		}
	}
}