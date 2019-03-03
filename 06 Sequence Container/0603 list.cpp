#include <iostream>
#include <list>
#include "utils.h"

using namespace std;

/*
list
	시퀸스 컨테이너이며 노드 기반 컨테이너(이중 연결 리스트)

	순차열 중간에 삽입, 제거가 빈번하게 발생하며 원소의 상대적 순서가 중요하면
	list 컨테이너를 사용

	이중 연결 리스트 구조로 원소를 앞, 뒤에 모두 추가 가능

	시퀸스 컨테이너이므로 처음과 마지막 원소의 참조를 반환하는 front(), back() 제공

	노드 기반이므로 insert, erase는 배열 기반보다 효율적으로 동작하며 
	상수 시간 복잡도의 수행 성능을 보인다.
	추가적으로 값의 비교로 원소를 제거하는 remove, remove_it을 제공
	
	노드 기반 컨테이너의 insert, erase 동작은 반복자를 무효화 시키지 않음
	반복자가 가리키는 원소 자체가 제거되지 않는 한 반복자는 계속 해당 원소를 가리킴

	다른 list와 결합 시 좋은 컨테이너
		splice() 함수는 노드 연결 연산만으로 두 list를 하나의 list로 결합
		merge() 함수는 두 list를 하나의 list로 정렬하여 결합(단 이미 정렬되어 있어야함)

	노드 기반이므로 at(), [] 연산자가 없으며 양방향 반복자를 제공.
		양방향 반복자는 +, - 연산이 불가능하므로 ++, -- 연산으로 이동
*/

void _0603_list() {

	cout << "===== 생성 =====" << endl;
	{
		list<int> l(3, 0);
		printContainer<list<int>, list<int>::iterator>(l); // 0, 0, 0
	}

	cout << "===== 원소 제거 =====" << endl;
	{
		list<int> l;
		l.push_back(0);
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);

		cout << "--- erase" << endl;
		{
			/*
			반복자 위치의 원소 제거
			*/
			list<int>::iterator iter = l.begin();
			l.erase(iter);
			printContainer<list<int>, list<int>::iterator>(l); // 1, 2, 3, 1, 2, 3
//			cout << (*iter) << endl; // 런타임 에러. iter의 원소는 더 이상 유효하지 않다.
		}
		

		cout << "--- remove" << endl;
		{
			/*
			인자와 같은 값인 원소 모두 제거
			*/
			l.remove(2);
			printContainer<list<int>, list<int>::iterator>(l); // 1, 3, 1, 3
		}

		cout << "--- remove_if" << endl;
		{
			/*
			단항 조건자(predicate)가 참인 모든 원소를 제거
				단항 조건자 : bool 형식을 반환하는 함수류(함수, 함수 객체, 함수 포인터)
			*/
			l.remove_if([](int& i) -> bool {return i < 3; }); // 단항 조건자를 람다로 전달
			printContainer<list<int>, list<int>::iterator>(l); // 3, 3
		}
	}

	cout << "===== 두 list 합치기 =====" << endl;
	{
		cout << "--- 모든 원소를 다른 list에 잘라 붙이기" << endl;
		{
			list<int> l1 = INIT_012;
			list<int> l2 = INIT_102030;

			/*
			splice : [splaɪs]
				동사
					1. (밧줄의 두 끝을 함께 꼬아서) 잇다
					2. (필름테이프 등의 두 끝을) 붙이다[잇다]
				명사
					1. (필름테이프밧줄 등의 두 끝을) 붙인[이은] 부분
			*/
			list<int>::iterator iter1 = l1.begin();
			l1.splice(++iter1, l2); // 반복자 앞에 붙여 넣는다.

			printContainer<list<int>, list<int>::iterator>(l1); // 0, [10, 20, 30], 1, 2
			cout << (*iter1) << endl; // 1
			cout << "~~~" << endl;
			printContainer<list<int>, list<int>::iterator>(l2); // (없음)
		}

		cout << "--- 하나의 원소만 다른 list에 잘라 붙이기" << endl;
		{
			list<int> l1 = INIT_012;
			list<int> l2 = INIT_102030;

			list<int>::iterator iter1 = l1.begin();
			list<int>::iterator iter2 = l2.begin();
			l1.splice(++iter1, l2, ++iter2);

			printContainer<list<int>, list<int>::iterator>(l1); // 0, [20], 1, 2
			cout << (*iter1) << endl; // 1
			cout << "~~~" << endl;
			printContainer<list<int>, list<int>::iterator>(l2); // 10, 30
		}

		cout << "--- 순차열을 다른 list에 잘라 붙이기" << endl;
		{
			list<int> l1 = INIT_012;
			list<int> l2 = INIT_102030;

			list<int>::iterator iter1 = l1.begin();
			list<int>::iterator iter2 = l2.begin();
			l1.splice(++iter1, l2, iter2, --l2.end());

			printContainer<list<int>, list<int>::iterator>(l1); // 0, [10, 20], 1, 2
			cout << (*iter1) << endl; // 1
			cout << "~~~" << endl;
			printContainer<list<int>, list<int>::iterator>(l2); // 30
		}
	}

	cout << "===== list 순차열 반대로 뒤집기 =====" << endl;
	{
		list<int> l = INIT_012;
		l.reverse();
		printContainer<list<int>, list<int>::iterator>(l); // 2, 1, 0

	}

	cout << "===== 인접한 원소의 중복 제거 unique =====" << endl;
	{
		cout << "--- 기본 unique" << endl;
		{
			/*
			인접하지 않은 원소의 중복은 제거하지 않는다.
			정렬 후 unique를 수행하면 모든 중복을 제거할 수 있다.
			*/
			list<int> l = { 0, 0, 1, 1, 2, 0, 1, 2 };
			l.unique();
			printContainer<list<int>, list<int>::iterator>(l); // 0, 1, 2, 0, 1, 2
		}

		cout << "--- 이항 조건자 제공 unique" << endl;
		{
			/*
			이항 조건자
				인접한 두 원소를 받아 bool 값을 반환하는 함수류(함수, 함수 객체, 함수 포인터)
			*/
			list<int> l = { 0, 0, 1, 1, 2, 0, 1, 2 };
			l.unique([](int& l, int&r) -> bool { return l == r; }); // 이항 조건자를 람다로 제공
			printContainer<list<int>, list<int>::iterator>(l); // 0, 1, 2, 0, 1, 2
		}
		
	}

	cout << "===== 정렬 sort =====" << endl;
	{
		/*
		list는 vector, deque과 다르게 sort 알고리즘을 사용하지 못 하기 때문에 
		자체 sort 멤버 함수를 제공한다.
			sort 알고리즘(대부준 quick sort로 구현)은 임의 접근 반복자를 지원하는 컨테이너만 사용가능

		less, greater 조건자는 functional 헤더에 들어있지만 일반적으로 컨테이너 헤더에서 포함하므로 
		include 생략 가능하다.
		*/
		cout << "--- sort()" << endl;
		{
			list<int> l = INIT_012;
			l.sort();
			printContainer<list<int>, list<int>::iterator>(l); // 0, 1, 2

			l.sort(greater<int>());
			printContainer<list<int>, list<int>::iterator>(l); // 2, 1, 0

			l.sort([](int& l, int&r) -> bool { return l < r; }); // 반환값이 false이면 바꾼다.
			printContainer<list<int>, list<int>::iterator>(l); // 0, 1, 2
		}
	}

	cout << "===== 두 list 병합 =====" << endl;
	{
		cout << "--- 정렬하며 병합 merge()" << endl;
		{
			/*
			같은 방식으로 정렬된 리스트를 정렬하며 병합한다.
			조건자를 지정할 수 있지만 역시 정렬방식과 같은 방식의 조건자를 지정해야한다.
			*/
			list<int> l1 = INIT_102030; // 10, 20, 30
			list<int> l2 = INIT_012; // 0, 1, 2

//			l1.merge(l2, greater<int>()); // 오름차준으로 정렬된 리스트에 내림차준 조건자 전달시 에러. "sequence not ordered"
			l1.merge(l2, less<int>()); // less는 기본 조건자

			printContainer<list<int>, list<int>::iterator>(l1); // 0, 1, 2, 10, 20, 30
			printContainer<list<int>, list<int>::iterator>(l2); // (없다)

			list<int> l3 = INIT_210; // 2, 1, 0
//			l1.merge(l3); // l3이 오름차순 정렬이 아니므로 런타임 에러. "sequence not ordered"
		}
	}
}