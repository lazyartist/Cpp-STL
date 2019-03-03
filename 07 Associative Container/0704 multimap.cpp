#include <iostream>
#include <map>
#include "utils.h"

using namespace std;

/*
multimap
	map 컨테이너에 중복키를 허용할 때 사용한다.
	그외는 map과 모두 동일

	중복키를 허용하기 때문에 []연산자를 제공하지 않는다.




*/

void _0704_multimap() {
	cout << "===== 생성 =====" << endl;
	{
		multimap<int, int> m = { {1, 1}, {2, 2}, {3, 3}, {1, 10}, {2, 20}, {3, 30} };
		printMap<multimap<int, int>, multimap<int, int>::iterator>(m); // 1: 1, 1: 10, 2: 2, 2: 20, 3: 3, 3: 30
	}

	cout << "===== 찾기 =====" << endl;
	{
		cout << "--- count" << endl;
		{
			multimap<int, int> m = { {1, 1}, {2, 2}, {3, 3}, {1, 10}, {2, 20}, {3, 30} };
			cout << m.count(2) << endl; // 2
		}

		cout << "--- find" << endl;
		{
			multimap<int, int> m = { {1, 1}, {2, 2}, {3, 3}, {1, 10}, {2, 20}, {3, 30} };
			multimap<int, int>::iterator iter = m.find(2);

			cout << (iter->first) << endl; // 2
		}

		cout << "--- lower_bound, upper_bound" << endl;
		{
			/*
			lower_bound : 찾은 원소의 첫 번째
			upper_bound : 찾은 원소의 끝의 다음 원소
			*/
			multimap<int, int> m = { {1, 1}, {2, 2}, {3, 3}, {1, 10}, {2, 20}, {3, 30} };
			multimap<int, int>::iterator lower_iter = m.lower_bound(2);
			multimap<int, int>::iterator upper_iter = m.upper_bound(2);
			cout << lower_iter->first << ": " << lower_iter->second << endl; // 2: 2
			cout << upper_iter->first << ": " << upper_iter->second << endl; // 3: 3
		}

		cout << "--- equal_range" << endl;
		{
			multimap<int, int> m = { {1, 1}, {2, 2}, {3, 3}, {1, 10}, {2, 20}, {3, 30} };
			pair<multimap<int, int>::iterator, multimap<int, int>::iterator> pair = m.equal_range(2);
			cout << pair.first->first << ": " << pair.first->second << endl;   // 2: 2
			cout << pair.second->first << ": " << pair.second->second << endl; // 3: 3
		}
	}
}