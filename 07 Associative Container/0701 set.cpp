#include <iostream>
#include <set>
#include <algorithm>
#include "utils.h"

using namespace std;

/*
set
	대표적인 연관 컨테이너이자 노드 컨테이너

	모든 원소는 유일하다
	중복을 허용하려면 multiset을 이용한다.

	key라 불리는 원소를 정렬 기준에 맞춰 균형 이진트리에 저장하며
	이 key 원소가 삽입, 검색, 제거 등에 모두 이용되므로 key를 변경할 수 없음

연관 컨테이너의 특징
	특정 정렬 기준에 의해 원소가 자동 정렬되는 컨테이너

	push_back, push_front, pop_back, pop_front 등의 원소를 컨테이너 앞, 뒤에 추가/제거하는 함수를 제공하지 않음
	
	front(), back() 제공하지 않음
	
	균형 이진트리로 빠른 원소 찾기가 가능(로그 시간 복잡도)

원소 삽입
	삽입 인터페이스로 insert 단 하나만 제공한다.
	
	pair 객체를 반환하고 이 객체의 second로 삽입의 성공/실패를 알 수 있다.
	
	삽입에 성공하면 pair.first는 삽입된 원소를 가리키는 반복자이고
	실패하면 이미 삽입된 원소를 가리키는 반복자이다.

	삽입도 로그 시간 복잡도를 갖는다.

	위치 지정 및 구간 지정하여 삽입도 가능하다.
		위치 지정 시 삽입 위치가 정렬순서와 맞다면 바로 삽입되지만 아니라면 로그 시간이 걸린다.

원소 찾기
	균형 이진 트리로 구현되어 로그 시간 복잡도를 갖는다.

찾기 멤버 함수
	count, find, lower_bound, upper_bound, equal_range

반복자
	양방향 반복자 지원
	begin, end, rbegin, rend

조건자
	조건자를 반환한다. 
	key_comp(), value_comp() 
*/

void _0701_set() {
	cout << "===== 생성 / 삽입 =====" << endl;
	{
		cout << "--- 생성" << endl;
		{
			set<int> s = INIT_210;
			printContainer<set<int>, set<int>::iterator>(s); // 0, 1, 2 : 정렬하지 않아도 자동 정렬되어있다.
		}

		cout << "--- 삽입" << endl;
		{
			set<int> s = INIT_210;

			pair<set<int>::iterator, bool> p = s.insert(2);
			cout << *p.first << ", " << p.second << endl; // 2, 0 : 중복되어 삽입 실패

			p = s.insert(3);
			cout << *p.first << ", " << p.second << endl; // 3, 1 : 중복 안되어 삽입 성공

			printContainer<set<int>, set<int>::iterator>(s); // 0, 1, 2, 3
		}

		cout << "--- 위치 지정 삽입" << endl;
		{
			set<int> s = INIT_102030;

			set<int>::iterator iter = s.end();
			s.insert(iter, 25);
			s.insert(iter, 1);

			printContainer<set<int>, set<int>::iterator>(s); // 10, 20, 25, 30
		}

		cout << "--- 키값 변경 불가" << endl;
		{
			set<int> s = INIT_012;
			set<int>::iterator iter = s.begin();
//			*iter = 1; // 키 값 변경 불가
		}
	}

	cout << "===== 조건자 =====" << endl;
	{
		cout << "--- 조건자 변경" << endl;
		{
			/*
			조건자를 템플릿 타입으로 지정
			*/
			set<int, greater<int>> s1 = INIT_012;

			/*
			조건자를 const 변수로 생성하고 전달
			*/
			const greater<int> g;
			set<int, greater<int>> s2(g); // 생성하며 초기화 할 수 없다.
			s2 = INIT_012; // 여기서는 초기화 가능

//			set<int, greater<int>> s3(greater<int>()); // 임시객체를 받는 생성자는 없는지 s3 함수 선언으로 인식된다. 에러는 안나지만 s3를 함수로 인식한다.

			printContainer<set<int, greater<int>>, set<int, greater<int>>::iterator>(s1); // 2, 1, 0
			printContainer<set<int, greater<int>>, set<int, greater<int>>::iterator>(s2); // 2, 1, 0
		}

		cout << "--- 조건자 반환" << endl;
		{
			set<int> s1;
			set<int, greater<int>> s2;

			/*
			typedef 내장 정의 형식 key_compare, value_compare 사용
			*/
			set<int>::key_compare less_key_comp = s1.key_comp(); // 키 조건자
			set<int, greater<int>>::value_compare greater_value_comp = s2.value_comp(); // 값 조건자

			// 아래도 사용 가능하지만 좀 더 명확한 코드를 위해 위처럼 typedef 된 타입을 사용하는게 좋다.
//			less<int> less_key_comp = s1.key_comp(); // 키 조건자
//			greater<int> greater_value_comp = s2.value_comp(); // 값 조건자

			cout << less_key_comp(1, 2) << endl; // 1
			cout << greater_value_comp(1, 2) << endl; // 0
		}
	}

	cout << "===== 찾기 =====" << endl;
	{
		cout << "--- 원소 개수 반환 count()" << endl;
		{
			/*
			set은 원소가 하나이므로 count가 굳이 필요없지만 
			연관 컨테이너의 인터페이스 통일을 위해 제공한다.
			실행시간은 로그 시간 복잡도
			*/
			set<int> s = INIT_012;
			cout << s.count(1) << endl; // 1
			cout << s.count(9) << endl; // 0
		}

		cout << "--- 원소 찾아 반환 find()" << endl;
		{
			/*
			key를 검색하여 key를 가리키는 반복자를 반환
			검색 시 == 연산을 하지 않고 !(a < b) && !(b < a) 이면 같다고 판단한다.
			즉, a가 b보다 앞서 있지 않고 b도 a보다 앞서 있지 않으면 a와 b는 같다고 판단한다.
				정렬에 조건자를 사용하기 때문에 조건자를 그대로 사용해서 그런듯하다.
			*/
			set<int> s = INIT_012;
			set<int>::iterator iter = s.find(1);
			cout << *iter << ", " << (iter == s.end()) << endl; // 1, 0 : 찾기 성공

			iter = s.find(9);
			cout << (iter == s.end()) << endl; // 1 : 찾기 실패
											   // iter가 유효한 값이 아니라서 접근하면 "cannot dereference end map/set iterator" 에러 발생.
		}

		cout << "--- 구간 반환 lower_bound(), upper_bound()" << endl;
		{
			/*
			찾은 원소를 순자열 구간(반복자 쌍)으로 반환
				lower_bound() : 찾은 원소의 시작 반복자
				upper_bound() : 찾은 원소의 다음 원소의 반복자

			set 컨테이너에서 의미는 크기 않지만 중복 원소를 갖는 multiset, multimap에서 유용함.

			find와 마찬가지로 찾기에 실패하면 end() 반복자를 반환함
				lower_bound와 upper_bound 반복자가 같으면 찾는 원소가 없다.(위 문장과 같은 말이다)
			*/
			set<int> s = INIT_01234;
			set<int>::iterator lower_iter = s.lower_bound(2);
			set<int>::iterator upper_iter = s.upper_bound(2);
			cout << *lower_iter << endl; // 2
			cout << *upper_iter << endl; // 3


			upper_iter = s.upper_bound(9);
			cout << (upper_iter == s.end()) << endl; // 1 : 실패, end()를 가리킨다
		}

		cout << "--- 구간 반환 equal_range()" << endl;
		{
			/*
			찾은 원소들의 구간을 pair로 반환
			*/
			set<int> s = INIT_01234;
			pair<set<int>::iterator, set<int>::iterator> equal_iter = s.equal_range(2);

			cout << *equal_iter.first << ", " << *equal_iter.second << endl;

			equal_iter = s.equal_range(9);
			cout << (equal_iter.first == equal_iter.second) << endl; // 1 : 실패, first와 second가 같다.
		}
	}

}