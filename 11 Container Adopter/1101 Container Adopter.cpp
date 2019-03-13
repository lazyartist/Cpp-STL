#include <iostream>
#include <stack>
#include <queue>
#include "utils.h"

using namespace std;

/*
컨테이너 어댑터
	다른 컨테이너의 인터페이스를 변경한 컨테이너

stack
	LIFO(Last-In First-Out)
	기본 컨테이너 deque
	
	인자 컨테이너는 empty, size, push_back, pop_back, back 등의 인터페이스를 지원해야함
	따라서 vector, deque, list 등이 사용가능하고 이 인터페이스를 지원하면 사용자 컨테이너도 가능

queue
	FIFO(First-In First-Out)

	인자 컨테이너는 empty, size, push_back, pop_front, front 등의 인터페이스를 지원해야함
	따라서 vector를 사용할 수 없고 deque, list 등 이 인터페이스를 지원하는 컨테이너만 사용 가능

	기본 컨테이너 deque

priority_queue
	우선순위에 의해 관리되는 큐
	기본 정렬기준은 less
		less는 최대힙
			새로운 원소는 가장 끝 노드에 추가된다.
			부모가 자식 보다 작으면 교체한다.  -> 부모는 자식보다 크다 -> 최대힙
		greater 최소힙
			새로운 원소는 가장 끝 노드에 추가된다.
			부모가 자식 보다 크면 교체한다.  -> 부모는 자식보다 작다 -> 최소힙

	내부적으로 STL의 힙 알고리즘인 make_heap(), push_heap(), pop_heap()을 사용하여 구현
	따라서 컨테이너는 임의 접근 반복자를 제공해야함

	인자 컨테이너는 empty, size, push_back, pop_back, front 등의 인터페이스를 제공
	따라서 vector, deque 컨테이너 사용 가능

	기본 컨테이너 vector




*/

void _1101_container_adopter() {
	printBlockName("stack");
	{
		stack<int> s;
		for (size_t i = 0; i < 3; i++)
		{
			s.push(i);
		}

		while (!s.empty())
		{
			cout << s.top() << endl; // 2, 1, 0
			s.pop();
		}
	}

	printBlockName("queue");
	{
		queue<int, list<int>> q; // list 사용하는 queue 생성
		for (size_t i = 0; i < 3; i++)
		{
			q.push(i);
		}

		while (!q.empty())
		{
			cout << q.front() << endl; // 0, 1, 2
			q.pop();
		}
	}

	printBlockName("priority_queue");
	{
		// 랜덤 정수를 저장하고 우선순위로 출력
		priority_queue<int> p;
		for (size_t i = 0; i < 10; i++)
		{
			p.push(rand() % 10);
		}

		while (!p.empty())
		{
			cout << p.top() << endl; // 9, 8, 8, 7, 4, 4, 4, 2, 1, 0
			p.pop();
		}
	}
}