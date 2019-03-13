#include <iostream>
#include <iterator>
#include <list>
#include <algorithm>
#include "utils.h"

using namespace std;

/*
반복자의 종류
	반복자는 포인터를 추상화한 클래스 객체

	입력 반복자(input iterator) : 전방향 읽기(istream)
		*iter(읽기), ->(멤버 읽기), ++(전방향 이동), ==(비교), !=(비교), iterator(iter)(복사 생성자)
	출력 반복자(output iterator) : 전방향 쓰기(ostream)
		*iter=x(쓰기), ++(전방향 이동), iterator(iter)(복사 생성자)
	순방향 반복자(forward iterator) : 전방향 읽기, 쓰기
		*iter, ->, ++, !=, =(대입), iterator()(기본 생성자), iterator(iter)
	양방향 반복자(bidirectional iterator) : 양방향 읽기, 쓰기(list, set, multiset, map, multimap)
		순방향 반복자 기능에 --(역방향 이동) 연산을 제공
	임의 접근 반복자(random iterator) : 랜덤 읽기, 쓰기(vector, deque)
		양방향 반복자 기능에 랜덤 연산인 [], +=, -=, +, -, <, >, <=, >= 연산을 제공

	todo ? 전방향.. 앞으로만 이동?

순차열과 구간
	순차열 sequence
		순서있는 원소의 집합
	구간 range
		시작과 끝을 나타내는 반복자 쌍으로 표현
		[b,e)
			반개 구간 : b는 원소에 포함, e는 포함되지 않음

X::iterator
	정방향 반복자의 내장 형식, 반복자가 가리키는 원소 읽기, 쓰기 가능
X::const_iterator
	정방향 반복자의 내장 형식, 반복자가 가리키는 원소 읽기 가능, 쓰기 불가
X::reverse_iterator
	역방향 반복자의 내장 형식, 반복자가 가리키는 원소 읽기, 쓰기 가능
X::const_reverse_iterator
	역방향 반복자의 내장 형식, 반복자가 가리키는 원소 읽기 가능, 쓰기 불가

역방향 반복자가 가리키는 원소와 실제 값은 다르다
	정방항 반복자의 순차열과 역방향 반복자의 순차열이 같도록 하기 위해
	역방향 반복자는 가리키는 원소의 다음 값을 참조한다.

반복자의 형식 변환
	const_iterator <- base() <- const_reverse_iterator
			↑							↑
		iterator		->			reverse_iterator
					<- base() <-

		역반복자에서 정반복자로는 base를 통해야하지만 
		정반복자에서 역반복자로는 바로 대입가능하다.
			생성자에서 처리하는 듯.

	역방향 반복자는 base() 멤버 함수를 통해 정방향 반복자로 형변환 가능하다.

삽입 반복자
	순차열에 원소를 삽입(insert)할 수 있게 반복자를 반환하는 반복자 어댑터
	모든 알고리즘은 기본적으로 덮어쓰기로 동작하지만 삽입 반복자를 이용해 삽입 모드로 동작
	삽입하면 원소의 개수가 늘어난다.

	inserter()
		insert_iterator 객체 생성
		컨테이너의 insert()를 호출해 삽입 모드로 동작
		모든 컨테이너 사용 가능

	back_inserter()
		back_insert_interator 객체 생성
		컨테이너의 push_back() 호출해 뒤쪽에 삽입
		vector, deque, list 사용 가능

	front_inserter
		front_insert_iterator 객체 생성
		컨테이너의 push_front() 호출해 앞쪽에 삽입
		deque, list 사용 가능

입출력 스트림 반복자
	스트림과 연결된 반복자로 알고리즘이 스트림에 읽고 쓸 수 있게 한다.

	istream_iterator<T>
		입력 스트림과 연결된 반복자로 T 형식의 값을 스트림에서 읽을 수 있다.

	ostream_iterator<T>
		출력 스트림과 연결된 반복자로 T 형식의 값을 스트림에 쓸 수 있다.

반복자 특성과 보조 함수
	입력, 출력, 순방향, 양방향, 임의 접근 반복자는 자신만의 특징을 가지며
	이 특징을 저장하는 템플릿 클래스를 가리켜 반복자 특성(iterator traits)라 한다.
		traits [treɪt] 명사 1. (성격상의) 특성

	advance(p,n) : p반복자를 p+=n 위치로 이동
	n=distance(p1,p2) : n은 p2-p1
*/

// ===== Advance 구현 ===== //
// 특성 클래스 정의
template<typename IterT>
struct Iterator_Traits {
	typedef typename IterT::iterator_category iterator_category;
	//typedef typename IterT::value_type value_type;
	//typedef typename IterT::difference_type difference_type;
	//typedef typename IterT::pointer pointer;
	//typedef typename IterT::reference reference;
};

// 상속관계로 반복자 타입 정의
struct Bidirectional_Iterator_Tag {};
struct Random_Iterator_Tag : Bidirectional_Iterator_Tag {};

// 호출 인터페이스
template<typename IterT>
void Advance(IterT &iter, int n) {
	//_Advance(iter, n, Iterator_Traits<IterT>::iterator_category());

	// Iterator_Traits를 사용하지 않아도 에러 안난다.
	// 다른 상황에서 사용하기 위해 묶음 타입을 제공하는 것일 뿐인가?
	_Advance(iter, n, IterT::iterator_category());
};

// 실제 작동 함수
template<typename IterT>
void _Advance(IterT &iter, int n, bidirectional_iterator_tag category) {
	for (size_t i = 0; i < n; i++)
	{
		++iter;
	}
	cout << "_Advance() bidirectional_iterator_tag" << endl;
}

// 실제 작동 함수
template<typename IterT>
void _Advance(IterT &iter, int n, Random_Iterator_Tag category) {
	iter += n;
	cout << "_Advance() Random_Iterator_Tag" << endl;
}

// 컨테이너 구현
template<typename T>
class List {
public:
	struct Iterator {
		typedef bidirectional_iterator_tag iterator_category;

		Iterator& operator++() { return *this; }
	};
};

// 컨테이너 구현
template<typename T>
class Vector {
public:
	struct Iterator {
		typedef Random_Iterator_Tag iterator_category;

		Iterator& operator+=(int n) { return *this; }
	};
};

// ===== Advance 구현 ===== // end

void _1001_iterator() {
	printBlockName("X::iterator, X::const_iterator");
	{
		vint v = INIT_01234;
		// iter
		vector<int>::iterator it = v.begin();
		// const_iter
		vector<int>::const_iterator const_it = v.begin();
		// const iter
		const vector<int>::iterator constant_it = v.begin();
		// const const_iter
		const vector<int>::const_iterator constant_cst_it = v.begin();

		// iter
		*it = 9;
		++it;

		// const_iter
//		*const_it = 9; // 값 변경 불가
		++const_it;

		// const iter
		*constant_it = 9;
		//		++constant_it; // 반복자 변경 불가

				// const const_iter
		//		*constant_cst_it = 9; // 값 변경 불가
		//		*constant_cst_it = 9; // 반복자 변경 불가
	}

	printBlockName("revers_iterator 어댑터");
	{
		vint v = INIT_01234;
		reverse_iterator<vint::iterator> rbiter(v.end());
		reverse_iterator<vint::iterator> reiter(v.begin());

		cout << *rbiter << endl;
		//		cout << *reiter << endl; // 런타임 에러 : end는 끝 원소 다음을 가리키기 때문에 값을 참조하면 에러난다.
	}

	printBlockName("역방향 반복자");
	{
		vint v = INIT_01234;
		vint::reverse_iterator riter_begin = v.rbegin();
		vint::reverse_iterator riter_end = v.rend();

		while (riter_begin != riter_end)
		{
			cout << *riter_begin << endl;
			++riter_begin; // 4, 3, 2, 1 0
		}

		riter_begin = v.rbegin();
		riter_end = v.rend();

		cout << *riter_begin << endl; // 4
//		cout << *riter_end << endl; // 런타임 에러 : "can't decrement vector iterator before begin"

//		cout << *riter_begin.base() << endl; // 런타임 에러 : "can't dereference(역참조하다) out of range vector iterator"
		cout << *riter_end.base() << endl; // 0

		riter_begin += 4;
		cout << *riter_begin << endl; // 0
		cout << *riter_begin.base() << endl; // 1 : 반복자가 이동한 상태에선 정방향 끝 반복자가 아닌 이전 원소를 가리키는 반복자를 반환한다.
	}

	printBlockName("삽입 반복자");
	{
		printSubBlockName("inserter");
		{
			vint v1 = INIT_012;
			vint v2; // size 0

			// copty는 기본 덮어쓰기 모드로 동작하므로 inserter()를 사용하지 않으면
			// v2의 size()가 0이므로 런타임 오류가 난다.
			copy(v1.begin(), v1.end(), inserter<vint>(v2, v2.begin()));
			printVector(v2); // 0, 1, 2
		}

		printSubBlockName("back_inserter, front_inserter");
		{
			vint v1 = INIT_012;
			list<int> l1 = { 9 };
			list<int> l2 = { 9 };

			copy(v1.begin(), v1.end(), back_inserter<list<int>>(l1)); // 9, 0, 1, 2
			copy(v1.begin(), v1.end(), front_inserter<list<int>>(l2)); // 2, 1, 0, 9

			printList(l1);
			printList(l2);
		}
	}

	printBlockName("입출력 스트림 반복자");
	{
		printSubBlockName("출력");
		{
			vint v = INIT_012;
			copy(v.begin(), v.end(), ostream_iterator<int>(cout));
			cout << endl;
			copy(v.begin(), v.end(), ostream_iterator<int>(cout, " * "/*종료문자열*/));
			cout << endl;

			lint l = INIT_012;
			// v와 l 원소의 합을 출력
			transform(v.begin(), v.end(), l.begin(), ostream_iterator<int>(cout, "|"), plus<int>()); // 0|2|4|
		}

		printSubBlockName("입력");
		{
			vint v;

			if(false) // 테스트에 방해돼서 실행 안되게 함
			{
				copy(istream_iterator<int>(cin) /*표준 입력 스트림과 연결된 반복자를 생성*/
					, istream_iterator<int>() /*입력 스트림의 끝(Ctrl+D) 반복자를 생성*/
					, back_inserter<vint>(v)); /*v에 추가할 수 있도록 삽입 반복자 생성*/
			}

			/* 1 2 3 ctrl+d 입력 시 */
			printVector(v); // 1, 2, 3
		}
	}

	printBlockName("반복자 특성과 보조 함수");
	{
		printSubBlockName("advance(p,n)");
		{
			// 임의 접근 반복자가 아닌 list에서 += 연산자를 사용한것 같은 동작을 한다.
			lint l = INIT_012;
			linti iter = l.begin();

//			iter += 2; // 컴파일 에러 : list 같은 양방향 반복자는 위치 이동을 한번에 하나를 초과하는 연산을 지원하지 않는다.
			advance(iter, 2); // advance()를 이용해 한 번에 2개의 위치를 이동했다.
			printInts(*iter); // 2
		}

		printSubBlockName("n=distance(p1,p2)");
		{
			lint l = INIT_012;
			linti bIter = l.begin();
			linti eIter = l.end();

//			int d = iter_end - iter; // 컴파일 에러 : list 같은 양방향 반복자는 반복자끼리 +, - 연산을 지원하지 않는다.
			iterator_traits<linti>::difference_type d = distance(bIter, eIter); // distance()를 이용해 반복자간의 거리를 계산한다.
																// 반환 타입은 iterator_traits에 있는 difference_type으로 받는다.
			cout << d << endl; // 3
		}

		printSubBlockName("Advance 구현");
		{
			Vector<int> v;
			Vector<int>::Iterator viter;

			List<int> l;
			List<int>::Iterator liter;

			Advance(viter, 1);
			Advance(liter, 1);


			/*printSubBlockName("vector");
			{
				vint v = INIT_012;
				vinti vbIter = v.begin();
				Advance<vinti>(vbIter, 2);
				cout << *vbIter << endl;
			}
			
			printSubBlockName("list");
			{
				lint l = INIT_012;
				linti lbIter = l.begin();
				Advance<linti>(lbIter, 2);
				cout << *lbIter << endl;

				
			}*/

			
		}
	}

	printBlockName("");
	{
		printSubBlockName("");
		{

		}
	}
}