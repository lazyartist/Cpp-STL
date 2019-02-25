#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <set>
#include <algorithm> // find ���
#include <functional> // not ���
#include "utils.h"

using namespace std;

/*
STL
	Standard Template Library
	���α׷��� �ʿ��� �ڷᱸ���� �˰����� �����ϴ� ���̺귯��
	�ڷᱸ���� �˰����� �ݺ��ڶ�� ���� ��Ҹ� ���� �����.

STL�� �������
	�����̳� Container
		��ü�� ����. �÷��� Ȥ�� �ڷᱸ���� ��
	�ݺ��� Iterator
		�����Ϳ� ����� ����
		�����̳��� ���Ҹ� ����Ű�� ���ҿ� �����ϰ� �̵�
	�˰��� Algorithm
		����, ����, �˻�, ���� ���� �ذ��ϴ� �Ϲ�ȭ�� ����� ����
	�Լ� ��ü Function Object
		�Լ�ó�� �����ϴ� ��ü, operator() �����ڸ� �����ε��� ��ü
		�����̳ʿ� �˰��� � Ŭ���̾�Ʈ ��å�� �ݿ��ϰ� ��.
	����� Adaptor
		���� ����� �������̽��� ������ ���ο� �������̽��� ���� ���� ��ҷ� ����(���ο� ���� ���ó�� ����)
	�Ҵ�� Allocator
		�����̳��� �޸� �Ҵ� ��å�� ĸ��ȭ�� Ŭ���� ��ü.
		��� �����̳ʴ� �ڽŸ��� �⺻ �Ҵ�⸦ ����
		��κ��� ���α׷��� STL���� �����ϴ� �⺻ �Ҵ��� ���

STL�� Ư¡
	ȿ����
	�Ϲ�ȭ ���α׷�
	Ȯ�强

�����̳�
	ǥ�� ������ �����̳�
		�����̳� ���Ұ� �ڽŸ��� ���� ��ġ�� ������. �������̴�.
			vector, deque, list
		����� ���Ұ� ���Ե� ������ �ٸ��� Ư�� ���� ���ؿ� ���� �ڵ� ���ĵȴ�. �������̴�.
			set, multiset, map, multimap
		string �����̳�
			������ �����̳��� ���������� ���ڸ��� �����ϴ� �����̳ʷ� ǥ�� �����̳��� �䱸������ ��Ű�� ���Ѵ�.
			���� �ٻ�(����) �����̳ʶ��ϰ� ���� �迭(arr[n] ����), valarray�� �ٻ� �����̳��̴�.
	ǥ�� ������ �����̳��� ����
		�迭 ��� �����̳�(array based container)
			������ ���� ���� �ϳ��� �޸� ������ �����(vector, deque)
			push_back(), pop_back(), size(), [] ����
		��� ��� �����̳�(array based container)
			������ �ϳ��� �ϳ��� �޸� ������ ����(list, set, multiset, map, multimap)

�ݺ���
	�����̳ʿ� ����� ���Ҹ� ��ȸ�ϰ� �����ϴ� �Ϲ�ȭ�� ����� ����
	�ݺ��ڴ� �����̳ʿ� �˰����� �ϳ��� �����ϰ� �����ִ� �������̽� ����

	�ݺ����� Ư¡
		�����̳� ���� ���Ҹ� ����ī�� ������ �� �־���Ѵ�.(*������ ����)
		���� ���ҷ� �̵��ϰ� �����̳��� ��� ���Ҹ� ��ȸ�� �� �־���Ѵ�.

	������(sequence)
		������ ������ �ִ� ����
		�ϳ��� ���۰� ���� ���´�.

	�ݺ��ڴ� �������� �� ���Ҹ� ����Ų��.

	��� �����̳ʴ� �ڽŸ��� �ݺ��ڸ� ��ȯ�մϴ�.
	�ݺ��ڴ� begin(), end()�� ��ȯ

	begin(), end()�� �����̶��ϸ� ���� ǥ����� ����� �ݰ� ����(half-open range)��
	[begin, end)ó�� ǥ���Ѵ�.

	�������� ���� �ִ� ������ �����̹Ƿ� ���� [begin, end)�Ӹ� �ƴ϶� [begin, iter)��
	[iter, end)�� ��� �������̴�.

	begin(), end()�� �������� ���۰� ���� ����Ű�� �ݺ��ڸ� ��ȯ
		end()�� ���� �� ���Ұ� �ƴ϶� ���� ǥ���ϴ� ����

	��� �����̳��� �ݺ��ڴ� ���� Ŭ���� �Ǵ� typedef�̴�.
		typedef��� ���� ����������?

	�ݺ����� ����
		�Է� �ݺ���(input iterator)
			�� ��ġ�� ���Ҹ� �� ���� '���� �� �ִ�' �ݺ���
				�дµ� �Է��̶�� �ϴ� ����
					stream�� �ִ� �����Ϳ� �����Ͽ� �о���� istream�� ������ �����ϱ� ����?
					��Ʈ������ �о�´�. -> ���� ���տ��� �о�´�.
		��� �ݺ���(output interator)
			�� ��ġ�� ���Ҹ� �� ���� ���� �ִ� �ݺ���
		������ �ݺ���(forward iterator)
			��/��� �ݺ��� ��ɿ� �߰��� ���������� �̵��� �����ϰ� ���Ҵ�(���� ���� ����Ŵ) �� �� �ִ� �ݺ���
		����� �ݺ���(bidirection iterator)
			��/��� �ݺ��� ��ɿ� �߰��� ���������� �̵��� �����ϰ� ���Ҵ� �� �� �ִ� �ݺ���
		���� ���� �ݺ���(random access iterator)
			����� �ݺ��� ��ɿ� �߰��� +, -, +=, -=, [] ������ ������ �ݺ���

	��� �����̳ʴ� ����� �ݺ��� �̻��� ����
	�迭 ��� �����̳��� vector, deque�� ���� ���� �溹�ڸ� ����

�˰���
	STL�� �������� ���Ҹ� ����, ����, ����, ó���� �������� �˰����̶�� ���� ��Ҹ� ����
	�ѽ��� �ݺ���(begin, end)�� �ʿ���ϰ� ��κ� ������ �ݺ��ڸ� �䱸������ ����� ���� ���� �ݺ��ڸ� �ݺ��ڸ� �䱸

	�з�
		���Ҹ� �������� �ʴ� �˰��� nonmodifying algorithms
		���Ҹ� �����ϴ� �˰��� modifying algorithms
		���� �˰��� removing algorithms
		���� �˰��� mutating algorithms
		���� �˰��� sorting algorithms
		���ĵ� ���� �˰��� sorted range algorithms
		��ġ �˰��� numeric algorithms

�Լ� ��ü
	Ŭ���̾�Ʈ�� ������ ������ �ٸ� ���� ��ҿ� �ݿ��Ϸ� �� �� ���
	�Լ� ��ü, �Լ�, �Լ� ������ ������ �˰����� ��������

�����
	���� ����� �������̽��� ����

	����
		�����̳� �����(container adaptor) : stack, queue, priority_queue
		�ݺ��� �����(iterator adaptor) : reverse_iterator, back_insert_iterator, front_insert_iterator, insert_iterator
		�Լ� �����(function adaptor) : ���δ�(binder), ������(negator), �Լ� ������ �����(adaptor for pointers to functions)

�Ҵ��
	�����̳��� �޸� �Ҵ� ������ ��å(�޸� �Ҵ� ��)�� ĸ��ȭ�� STL ���� ���
	�Ҵ��� ���ø� Ŭ�����̸� ��� �����̳ʴ� �⺻ �Ҵ�⸦ ���
	����ڰ� ���� �����ϰ� ����� �� ����.
		Ư�� ���� ȯ�濡 ����ȭ�� �޸� �Ҵ� ������ ������ �� ����
		��κ� STL�� �⺻ �Ҵ�⸸���� ����ϹǷ� �ڼ��� �ٷ��� ����.

*/

int main() {
	cout << "===== vector =====" << endl;
	{
		vector<int> v;
		v.push_back(0);
		v.push_back(1);

		for (size_t i = 0; i < v.size(); i++)
		{
			cout << v[i] << endl; // ���� ������� ��� : 0, 1
		}

		// �ݺ��ڸ� ����Ͽ� ��� ���� ���
		for (vector<int>::iterator iter = v.begin(); iter != v.end(); ++iter)
		{
			cout << *iter << endl; // 0, 1
		}

		// ���� ���� �ݺ���
		vector<int>::iterator iter = v.begin();
		cout << iter[0] << endl; // 0, ���� �����ϸ� ���� ������ ������ *�� ������� �ʴ´�.
	}

	cout << "===== iterator =====" << endl;
	{
		vector<int> v;
		v.push_back(0);
		v.push_back(1);

		for (size_t i = 0; i < v.size(); i++)
		{
			cout << v[i] << endl; // ���� ������� ��� : 0, 1
		}

		// �ݺ��ڸ� ����Ͽ� ��� ���� ���
		for (vector<int>::iterator iter = v.begin(); iter != v.end(); ++iter)
		{
			cout << *iter << endl; // 0, 1
		}

		// ���� ���� �ݺ���
		vector<int>::iterator iter = v.begin();
		cout << iter[0] << endl; // 0, ���� �����ϸ� ���� ������ ������ *�� ������� �ʴ´�.
	}

	cout << "===== algorithm =====" << endl;
	{
		/*
		find �˰���
			���� ã�� iterator�� ��ȯ
			ã�� ���ϴ� end() ���� ��ȯ
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
		sort �˰���
			���� ���� �ݺ��ڸ� �䱸�ϹǷ� vector, deque�� ���밡��
			list�� ���� ���� �ݺ��ڸ� ������� ���ϹǷ� sort ���� ����.
			���� �����̳ʴ� �����̳ʸ��� ���� ������ ������ �ձ� ������ �ٺ������� sort �˰��� ������ �ȵȴ�.
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
//			sort(l.begin(), l.end()); // compile error : sort�� �������� �ݺ��ڸ� �䱸�ϹǷ� list�� ������ �� ����.
		}
	}

	cout << "===== �Լ� ��ü =====" << endl;
	{
		cout << "--- less, greater" << endl;
		{
			vector<int> v;
			v.push_back(4);
			v.push_back(2);
			v.push_back(1);
			v.push_back(3);

			/*
			sort�� �˰����� �������� ������ less�� �⺻ �˰������� ����ȴ�.
			*/

			sort(v.begin(), v.end(), less<int>()); // ��������
			printContainer<vector<int>, vector<int>::iterator>(v);
			
			sort(v.begin(), v.end(), greater<int>()); // ��������
			printContainer<vector<int>, vector<int>::iterator>(v);
		}
	}

	cout << "===== ����� =====" << endl;
	{
		cout << "--- stack" << endl;
		{
			/*
			stack �����̳�
				�Ϲ� �����̳ʸ� LIFO(Last-In First-Out) ����� ����(Stack) �����̳ʷ� ��ȯ
				empty(), size(), push_back, pop_back, back �������̽��� �����ϴ� �����̳ʴ� 
				stack �����̳� ����͸� ����Ͽ� LIFO ����� �������� ��ȯ �����ϴ�.
					��� ������ �����̳ʴ� ���� �������̽��� �����Ƿ� stack�� �����̳ʷ� ���� �� �ִ�.
				����Ʈ �����̳ʴ� deque �����̳�

				���� �����̳ʷ� deque�� vector�� ����
					stack�� �������̽��� ��ȯ���ִ� �������� ���̶� deque�� vector�� ���� ���̰� �������̴�.

				vector�� stackó�� ����� �� ������ stack�� ����ϸ� �ڵ��� �ǵ��� ��Ȯ�ϰ� �� �� �ִ�.
			*/
			stack<int> deque_stack; // deque�� �����̳ʷ� ���
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

			stack<int, vector<int>> vector_stack; // vector�� �����̳ʷ� ���
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
			reverse_iterator �ݺ��� �����
				�Ϲ� �ݺ����� ���� ����� �ݴ�� ���۽�Ű�� ������ �ݺ���(reverse iterator)�� ��ȯ
				������ �ݺ����� ���� ���� ���� ��� ���� �ƴ� ���� ����� ���̴�.
					�̷����� �ݺ��� ��ȸ�� ++ ���길 ����ص� �Ǵ� ������ �ִ�.
			*/
			vector<int> v;
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);
			printContainer<vector<int>, vector<int>::iterator>(v);
			cout << "---" << endl;

			/*
			������ Iterator�� ������ iterator�� ����
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
			�����̳ʿ��� ������ �ݺ��� ���
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
			not1, not2 �Լ� �����
				������ �Լ� ��ü�� �ݴ� �ǹ�(NOT(�ݴ�))�� ������ �Լ� ��ü�� ����
				not1 : ���� ������
				not2 : ���� ������
			*/
			cout << less<int>()(1, 0) << endl; // 0 : 1�� 1���� ���� �ʴ�.
			cout << less<int>()(1, 1) << endl; // 0 : 1�� 1���� ���� �ʴ�.
			cout << less<int>()(1, 2) << endl; // 1 : 1�� 2���� �۴�.
			cout << not2(less<int>())(1, 0) << endl; // 1
			cout << not2(less<int>())(1, 1) << endl; // 1
			cout << not2(less<int>())(1, 2) << endl; // 0
		}

	}

	cout << "===== �Ҵ�� =====" << endl;
	{
		/*
		vector, set�� �⺻ �Ҵ�� ����� ����
		*/
		vector<int, allocator<int>> v;
		set<int, less<int>/*���ı���*/, allocator<int>> s;
	}

	return 0;
}