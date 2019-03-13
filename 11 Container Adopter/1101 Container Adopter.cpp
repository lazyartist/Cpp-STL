#include <iostream>
#include <stack>
#include <queue>
#include "utils.h"

using namespace std;

/*
�����̳� �����
	�ٸ� �����̳��� �������̽��� ������ �����̳�

stack
	LIFO(Last-In First-Out)
	�⺻ �����̳� deque
	
	���� �����̳ʴ� empty, size, push_back, pop_back, back ���� �������̽��� �����ؾ���
	���� vector, deque, list ���� ��밡���ϰ� �� �������̽��� �����ϸ� ����� �����̳ʵ� ����

queue
	FIFO(First-In First-Out)

	���� �����̳ʴ� empty, size, push_back, pop_front, front ���� �������̽��� �����ؾ���
	���� vector�� ����� �� ���� deque, list �� �� �������̽��� �����ϴ� �����̳ʸ� ��� ����

	�⺻ �����̳� deque

priority_queue
	�켱������ ���� �����Ǵ� ť
	�⺻ ���ı����� less
		less�� �ִ���
			���ο� ���Ҵ� ���� �� ��忡 �߰��ȴ�.
			�θ� �ڽ� ���� ������ ��ü�Ѵ�.  -> �θ�� �ڽĺ��� ũ�� -> �ִ���
		greater �ּ���
			���ο� ���Ҵ� ���� �� ��忡 �߰��ȴ�.
			�θ� �ڽ� ���� ũ�� ��ü�Ѵ�.  -> �θ�� �ڽĺ��� �۴� -> �ּ���

	���������� STL�� �� �˰����� make_heap(), push_heap(), pop_heap()�� ����Ͽ� ����
	���� �����̳ʴ� ���� ���� �ݺ��ڸ� �����ؾ���

	���� �����̳ʴ� empty, size, push_back, pop_back, front ���� �������̽��� ����
	���� vector, deque �����̳� ��� ����

	�⺻ �����̳� vector




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
		queue<int, list<int>> q; // list ����ϴ� queue ����
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
		// ���� ������ �����ϰ� �켱������ ���
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