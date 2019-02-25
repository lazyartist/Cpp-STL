#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <set>
#include <algorithm> // find 사용
#include <functional> // not 사용
#include "utils.h"

using namespace std;

/*
STL
	Standard Template Library
	프로그램에 필요한 자료구조와 알고리즘을 제공하는 라이브러리
	자료구조와 알고리즘은 반복자라는 구성 요소를 통해 연결됨.

STL의 구성요소
	컨테이너 Container
		객체를 저장. 컬렉션 혹은 자료구조라 함
	반복자 Iterator
		포인터와 비슷한 개념
		컨테이너의 원소를 가리키고 원소에 접근하고 이동
	알고리즘 Algorithm
		정렬, 삭제, 검색, 연산 등을 해결하는 일반화된 방법을 제공
	함수 객체 Function Object
		함수처럼 동작하는 객체, operator() 연산자를 오버로딩한 객체
		컨테이너와 알고리즘 등에 클라이언트 정책을 반영하게 함.
	어댑터 Adaptor
		구성 요소의 인터페이스를 변경해 새로운 인터페이스를 갖는 구성 요소로 변경(새로운 구성 요소처럼 보임)
	할당기 Allocator
		컨테이너의 메모리 할당 정책을 캡슐화한 클래스 객체.
		모든 컨테이너는 자신만의 기본 할당기를 보유
		대부분의 프로그램은 STL에서 제공하는 기본 할당기로 충분

STL의 특징
	효율성
	일반화 프로그램
	확장성

컨테이너
	표준 시퀸스 컨테이너
		컨테이너 원소가 자신만의 삽입 위치를 가진다. 선형적이다.
			vector, deque, list
		저장된 원소가 삽입된 순서와 다르게 특정 정렬 기준에 의해 자동 정렬된다. 비선형적이다.
			set, multiset, map, multimap
		string 컨테이너
			시퀸스 컨테이너의 일종이지만 문자만을 저장하는 컨테이너로 표준 컨테이너의 요구사항을 지키지 못한다.
			따라서 근사(유사) 컨테이너라하고 내장 배열(arr[n] 형태), valarray도 근사 컨테이너이다.
	표준 시퀸스 컨테이너의 종류
		배열 기반 컨테이너(array based container)
			데이터 여러 개가 하나의 메모리 단위에 저장됨(vector, deque)
			push_back(), pop_back(), size(), [] 지원
		노드 기반 컨테이너(array based container)
			데이터 하나를 하나의 메모리 단위에 저장(list, set, multiset, map, multimap)

반복자
	컨테이너에 저장된 원소를 순회하고 접근하는 일반화된 방법을 제공
	반복자는 컨테이너와 알고리즘이 하나로 동작하게 묶어주는 인터페이스 역할

	반복자의 특징
		컨테이너 내부 원소를 가리카고 접근할 수 있어야한다.(*연산자 제공)
		다음 원소로 이동하고 컨테이너의 모든 원소를 순회할 수 있어야한다.

	순차열(sequence)
		원소의 순서가 있는 집합
		하나의 시작과 끝을 갖는다.

	반복자는 순차열의 한 원소를 가리킨다.

	모든 컨테이너는 자신만의 반복자를 반환합니다.
	반복자는 begin(), end()로 반환

	begin(), end()를 구간이라하며 수학 표기법을 사용해 반개 구간(half-open range)을
	[begin, end)처럼 표기한다.

	순차열은 순서 있는 원소의 집합이므로 구간 [begin, end)뿐만 아니라 [begin, iter)와
	[iter, end)도 모두 순차열이다.

	begin(), end()는 순차열의 시작과 끝을 가리키는 반복자를 반환
		end()는 실제 끝 원소가 아니라 끝을 표시하는 원소

	모든 컨테이너의 반복자는 내포 클래스 또는 typedef이다.
		typedef라는 말이 무슨뜻이지?

	반복자의 종류
		입력 반복자(input iterator)
			현 위치의 원소를 한 번만 '읽을 수 있는' 반복자
				읽는데 입력이라고 하는 이유
					stream에 있는 데이터에 접근하여 읽어오는 istream과 개념이 동이하기 때문?
					스트림에서 읽어온다. -> 원소 집합에서 읽어온다.
		출력 반복자(output interator)
			현 위치의 원소를 한 번만 쓸수 있는 반복자
		순방향 반복자(forward iterator)
			입/출력 반복자 기능에 추가로 순방향으로 이동이 가능하고 재할당(다음 원소 가리킴) 될 수 있는 반복자
		양방향 반복자(bidirection iterator)
			입/출력 반복자 기능에 추가로 역방향으로 이동이 가능하고 재할당 될 수 있는 반복자
		임의 접근 반복자(random access iterator)
			양방향 반복자 기능에 추가로 +, -, +=, -=, [] 연산이 가능한 반복자

	모든 컨테이너는 양방향 반복자 이상을 제공
	배열 기반 컨테이너인 vector, deque은 임의 접근 방복자를 제공

알고리즘
	STL은 순차렬의 원소를 조사, 변경, 관리, 처리할 목적으로 알골즘이라는 구성 요소를 제공
	한쌍의 반복자(begin, end)를 필요로하고 대부분 순방향 반복자를 요구하지만 몇몇은 임의 접근 반복자를 반복자를 요구

	분류
		원소를 수정하지 않는 알고리즘 nonmodifying algorithms
		원소를 수정하는 알고리즘 modifying algorithms
		제거 알고리즘 removing algorithms
		변경 알고리즘 mutating algorithms
		정렬 알고리즘 sorting algorithms
		정렬된 범위 알고리즘 sorted range algorithms
		수치 알고리즘 numeric algorithms

함수 객체
	클라이언트가 정의한 동작을 다른 구성 요소에 반영하려 할 때 사용
	함수 객체, 함수, 함수 포인터 등으로 알고리즘이 유연해짐

어댑터
	구성 요소의 인터페이스를 변경

	종류
		컨테이너 어댑터(container adaptor) : stack, queue, priority_queue
		반복자 어댑터(iterator adaptor) : reverse_iterator, back_insert_iterator, front_insert_iterator, insert_iterator
		함수 어댑터(function adaptor) : 바인더(binder), 부정자(negator), 함수 포인터 어댑터(adaptor for pointers to functions)

할당기
	컨테이너의 메모리 할당 정보와 정책(메모리 할당 모델)을 캡슐화한 STL 구성 요소
	할당기는 템플릿 클래스이며 모든 컨테이너는 기본 할당기를 사용
	사용자가 직접 정의하고 사용할 수 있음.
		특정 구현 환경에 최적화된 메모리 할당 몸델을 구축할 수 있음
		대부분 STL의 기본 할당기만으로 충분하므로 자세히 다루지 않음.

*/

int main() {
	cout << "===== vector =====" << endl;
	{
		vector<int> v;
		v.push_back(0);
		v.push_back(1);

		for (size_t i = 0; i < v.size(); i++)
		{
			cout << v[i] << endl; // 넣은 순서대로 출력 : 0, 1
		}

		// 반복자를 사용하여 모든 원소 출력
		for (vector<int>::iterator iter = v.begin(); iter != v.end(); ++iter)
		{
			cout << *iter << endl; // 0, 1
		}

		// 임의 접근 반복자
		vector<int>::iterator iter = v.begin();
		cout << iter[0] << endl; // 0, 임의 접근하면 값이 나오기 때문에 *를 사용하지 않는다.
	}

	cout << "===== iterator =====" << endl;
	{
		vector<int> v;
		v.push_back(0);
		v.push_back(1);

		for (size_t i = 0; i < v.size(); i++)
		{
			cout << v[i] << endl; // 넣은 순서대로 출력 : 0, 1
		}

		// 반복자를 사용하여 모든 원소 출력
		for (vector<int>::iterator iter = v.begin(); iter != v.end(); ++iter)
		{
			cout << *iter << endl; // 0, 1
		}

		// 임의 접근 반복자
		vector<int>::iterator iter = v.begin();
		cout << iter[0] << endl; // 0, 임의 접근하면 값이 나오기 때문에 *를 사용하지 않는다.
	}

	cout << "===== algorithm =====" << endl;
	{
		/*
		find 알고리즘
			값을 찾아 iterator를 반환
			찾지 못하는 end() 값을 반환
		*/
		cout << "--- find" << endl;
		{
			vector<int> v;
			v.push_back(0);
			v.push_back(1);
			v.push_back(2);

			int valueToFind = 1;
			vector<int>::iterator iter = find(v.begin(), v.end(), valueToFind);
			cout << *iter << endl; // 1
		}

		/*
		sort 알고리즘
			임의 접근 반복자를 요구하므로 vector, deque만 적용가능
			list는 임의 점근 반복자를 사용하지 못하므로 sort 정렬 못함.
			연관 컨테이너는 컨테이너만의 정렬 기준을 가지고 잇기 때문에 근본적으로 sort 알고리즘 적용이 안된다.
		*/
		cout << "--- sort" << endl;
		{
			vector<int> v;
			v.push_back(4);
			v.push_back(2);
			v.push_back(3);
			v.push_back(1);
			sort(v.begin(), v.end());

			printContainer<vector<int>, vector<int>::iterator>(v);

			list<int> l;
			l.push_back(1);
//			sort(l.begin(), l.end()); // compile error : sort는 임의접근 반복자를 요구하므로 list를 정렬할 수 없다.
		}
	}

	cout << "===== 함수 객체 =====" << endl;
	{
		cout << "--- less, greater" << endl;
		{
			vector<int> v;
			v.push_back(4);
			v.push_back(2);
			v.push_back(1);
			v.push_back(3);

			/*
			sort에 알고리즘을 지정하지 않으면 less가 기본 알고리즘으로 적용된다.
			*/

			sort(v.begin(), v.end(), less<int>()); // 오름차순
			printContainer<vector<int>, vector<int>::iterator>(v);
			
			sort(v.begin(), v.end(), greater<int>()); // 내림차순
			printContainer<vector<int>, vector<int>::iterator>(v);
		}
	}

	cout << "===== 어댑터 =====" << endl;
	{
		cout << "--- stack" << endl;
		{
			/*
			stack 컨테이너
				일반 컨테이너를 LIFO(Last-In First-Out) 방식의 스택(Stack) 컨테이너로 변환
				empty(), size(), push_back, pop_back, back 인터페이스를 지원하는 컨테이너는 
				stack 컨테이너 어댑터를 사용하여 LIFO 방식의 스택으로 변환 가능하다.
					모든 시퀸스 컨테이너는 위의 인테페이스를 가지므로 stack의 컨테이너로 사용될 수 있다.
				디폴트 컨테이너는 deque 컨테이너

				내부 컨테이너로 deque과 vector의 차이
					stack은 인터페이스를 변환해주는 껍데기일 뿐이라서 deque과 vector의 성능 차이가 차이점이다.

				vector를 stack처럼 사용할 수 있지만 stack을 사용하면 코드의 의도를 명확하게 할 수 있다.
			*/
			stack<int> deque_stack; // deque를 컨테이너로 사용
			deque_stack.push(0);
			deque_stack.push(1);
			deque_stack.push(2);

			cout << deque_stack.top() << endl; // 2
			deque_stack.pop();
			cout << deque_stack.top() << endl; // 1
			deque_stack.pop();
			cout << deque_stack.top() << endl; // 0
			deque_stack.pop();

			cout << deque_stack.empty() << endl; // 1 : true

			cout << "---" << endl;

			stack<int, vector<int>> vector_stack; // vector를 컨테이너로 사용
			vector_stack.push(10);
			vector_stack.push(11);
			vector_stack.push(12);

			cout << vector_stack.top() << endl; // 12
			vector_stack.pop();
			cout << vector_stack.top() << endl; // 11
			vector_stack.pop();
			cout << vector_stack.top() << endl; // 10
			vector_stack.pop();

			cout << vector_stack.empty() << endl; // 1 : true
		}

		cout << "--- reverse_iterator" << endl;
		{
			/*
			reverse_iterator 반복자 어댑터
				일반 반복자의 동작 방식을 반대로 동작시키는 역방향 반복자(reverse iterator)로 변환
				역방향 반복자의 실제 값은 현재 요소 값이 아닌 다음 요소의 값이다.
					이로인해 반복자 순회시 ++ 연산만 사용해도 되는 편리함이 있다.
			*/
			vector<int> v;
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);
			printContainer<vector<int>, vector<int>::iterator>(v);
			cout << "---" << endl;

			/*
			정방향 Iterator를 역방향 iterator로 변경
			*/
			{
				vector<int>::reverse_iterator riterBegin(v.end());
				vector<int>::reverse_iterator riterEnd(v.begin());
				while (riterBegin != riterEnd)
				{
					cout << *(riterBegin++) << endl;
				}
			}
			cout << "---" << endl;

			/*
			컨테이너에서 역방향 반복자 얻기
			*/
			{
				vector<int>::reverse_iterator riterBegin = v.rbegin();
				vector<int>::reverse_iterator riterEnd = v.rend();
				while (riterBegin != riterEnd)
				{
					cout << *(riterBegin++) << endl;
				}
			}
		}

		cout << "--- not1, not2" << endl;
		{
			/*
			not1, not2 함수 어댑터
				조건자 함수 객체를 반대 의미(NOT(반대))의 조건자 함수 객체로 변경
				not1 : 단항 조건자
				not2 : 이항 조건자
			*/
			cout << less<int>()(1, 0) << endl; // 0 : 1이 1보다 작지 않다.
			cout << less<int>()(1, 1) << endl; // 0 : 1이 1보다 작지 않다.
			cout << less<int>()(1, 2) << endl; // 1 : 1이 2보다 작다.
			cout << not2(less<int>())(1, 0) << endl; // 1
			cout << not2(less<int>())(1, 1) << endl; // 1
			cout << not2(less<int>())(1, 2) << endl; // 0
		}

	}

	cout << "===== 할당기 =====" << endl;
	{
		/*
		vector, set의 기본 할당기 명시적 지정
		*/
		vector<int, allocator<int>> v;
		set<int, less<int>/*정렬기준*/, allocator<int>> s;
	}

	return 0;
}