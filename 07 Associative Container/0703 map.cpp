#include <iostream>
#include <map>
#include "utils.h"

using namespace std;

/*
map
	연관 컨테이너이자 노드 기반 컨테이너

	특정 기준으로 원소가 자동 정렬

	원소는 key와 value 쌍으로 이루어짐

	[]연산자를 이용해 원소를 추가하거나 value의 참조를 반환

	연관 컨테이너이므로 앞/뒤에 추가/제거하는 함수를 제공하지 않음.

	연관 컨테이너는 빠른 원소 찾기를 위해 균형 이진 트리를 이용한 로그 시간 복잡도를 보장

	나머지는 set과 동일
*/

void _0703_map() {
	cout << "===== 생성 =====" << endl;
	{
		cout << "--- 생성" << endl;
		{
			map<int, double> m = { {1, 1.0} }; // 초기화도 가능
			printMap<map<int, double>, map<int, double>::iterator>(m);
		}

		cout << "--- 삽입 반환값" << endl;
		{
			map<int, double> m = { {1, 1.0} };
			pair<map<int, double>::iterator, bool> iter = m.insert(pair<int, double>(2, 2.0));

			cout << iter.first->first << " : " << iter.first->second << ", " << iter.second << endl; // 2 : 2, 1
			// first : 삽입된 pair를 가리키는 iterator, second : 삽입 성공 여부

			iter = m.insert(pair<int, double>(2, 3.0)); // 같은 키를 넣으면
			cout << iter.first->first << " : " << iter.first->second << ", " << iter.second << endl; // 2 : 2, 0
			// 삽입에 실패하고 이미 있는 원소를 가리킨다.

			printMap<map<int, double>, map<int, double>::iterator>(m);
		}

		cout << "--- [] 연산자" << endl;
		{
			map<int, double> m = { {1, 1.0} };
			m[2] = 2.0; // 없으니 삽입
			printMap<map<int, double>, map<int, double>::iterator>(m); // 1 : 1, 2 : 2

			m[2] = 3.0; // 이미 있으니 갱신
			printMap<map<int, double>, map<int, double>::iterator>(m); // 1 : 1, 2 : 3
		}
	}

	cout << "===== 정렬 =====" << endl;
	{
		cout << "--- 조건자 변경" << endl;
		{
			map<int, double, greater<int>> m = { {1, 1.0}, {2, 2.0}, {3, 3.0} };
			printMap<map<int, double, greater<int>>, map<int, double>::iterator>(m); // 3 : 3, 2 : 2, 1 : 1
		}
	}

	cout << "===== 찾기 =====" << endl;
	{
		cout << "--- count" << endl;
		{
			/*
			set과 마찬가지로 중복을 허용하지 않으므로 큰 의미는 없다.
			*/
			map<int, double> m = { {1, 1.0}, {2, 2.0}, {3, 3.0} };
			cout << m.count(1) << endl;
		}

		cout << "--- find" << endl;
		{
			/*
			찾은 원소를 가리키는 반복자 반환
			*/
			map<int, double> m = { {1, 1.0}, {2, 2.0}, {3, 3.0} };
			map<int, double>::iterator iter = m.find(2);
			cout << iter->first << " : " << iter->second << endl; // 2 : 2
		}

		cout << "--- lower_bound, upper_bound" << endl;
		{
			/*
			lower_bound : 찾은 원소의 첫 번째
			upper_bound : 찾은 원소의 끝의 다음 원소
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
			pair.first : 찾은 원소의 첫 번째
			pair.second : 찾은 원소의 끝의 다음 원소
			*/
			map<int, double> m = { {1, 1.0}, {2, 2.0}, {3, 3.0} };
			pair<map<int, double>::iterator, map<int, double>::iterator> pair = m.equal_range(2);
			map<int, double>::iterator upper_iter = m.upper_bound(2);
			cout << pair.first->first << " : " << pair.first->second << endl; // 2 : 2
			std::cout << pair.second->first << " : " << pair.second->second << endl; // 3 : 3
		}
	}
}