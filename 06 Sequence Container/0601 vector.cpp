#include <iostream>
#include <vector>
#include "utils.h"

using namespace std;

/*
vector �����̳�
	������ �����̳��̹Ƿ� ������ ���� ��ġ�� �������� �迭 ��� �����̳��̹Ƿ� ���Ұ� �ϳ��� �޸𸮺�Ͽ� �Ҵ��
		�ϳ��� �޸� ���? ���?

	���� �߰� �� �޸� ���Ҵ��� �߻��� �� �ְ� �̴� ū ����� ��� ������ capacity(), reserve()���� �����Ͽ�
	�̸� �޸� �Ҵ��� �� �ִ� ����� ����

	���� �޸� ������ ����ϱ� ������ at(), [] ������ ���ҿ� �����ϴ� �ӵ��� ��������
	insert(), erase(), push_back()�� ���� ȣ���Ѵٸ� �޸� ���Ҵ��� ���� �ϹǷ� �ٸ� �����̳ʰ� �� ����.

	���ʿ��� ���Ҹ� �߰�/������ �� ������ ���ʿ��� �߰�/���� ����
		deque, list�� ���ʿ� ���� �߰� ����(push_front, pop_front)

	size(), max_size()�� ��� �����̳ʰ� ������ ��� �Լ�
	capacity()�� vector�� ������ ��� �Լ�
	���Ұ� �߰��� ������ �޸��� ���Ҵ�� ���縦 ���� �ʰ� �̸� �˳��� �޸𸮸� Ȯ���Ѵ�.

	max_size()
		1073741823 : �̷������� �Ҵ��� �� �ִ� �ִ� ũ��, �ý��� �޸𸮰� �����ϸ� �Ҵ� ���� �� �ִ�.
		1073741823 + 1 / 1024 / 1024 / 1024 = 1GB
		32bit, 64bit ��� ���� ���� ���´�.

	iter �Ҵ� ���� ���� �߰�/���� ������ �޸𸮰� ���Ҵ� �ƴٸ� iterator�� �ٸ� ���� ����Ű�� �Ǳ� ������ ���Ҵ� ������Ѵ�.
	�ȱ׷��� ��������. "vector insert iterator outside range"

	�����̳� ������
		==, !=, <, <=, >=
*/

void _0601_vector() {
	cout << "===== vector ���� =====" << endl;
	{
		cout << "--- �⺻ ����" << endl;
		{
			/*
			vector<int> v(10); �� 10���� ��Ҹ� �⺻������ �ʱ�ȭ�Ѵٴ� ��. ���� ��Ұ� 10���ִ�.
			*/
			vector<int> v1(3); // �⺻�� 0���� �ʱ�ȭ�� 3���� ���Ҹ� ���� vector
			vector<int> v2(3, 9); // �⺻�� 9�� �ʱ�ȭ�� 3���� ���Ҹ� ���� vector
		}

		cout << "--- �ݺ��ڸ� ���� ����" << endl;
		{
			vector<int> v1(3, 1);
			vector<int> v2(v1.begin(), v1.end());

			printContainer<vector<int>, vector<int>::iterator>(v2); // 1, 1, 1
		}

		cout << "--- assign �ʱ�ȭ" << endl;
		{
			vector<int> v1;
			v1.push_back(0);
			v1.push_back(1);
			v1.push_back(2);
			vector<int> v2(3, 0);
			v2.assign(v1.begin(), v1.end());

			printContainer<vector<int>, vector<int>::iterator>(v2); // 0, 1, 2
		}
	}

	cout << "===== size =====" << endl;
	{
		//vector<int> v(3, 9); // 9�� ������ 3���� ���� ����
		vector<int> v; // 9�� ������ 3���� ���� ����
		printContainer<vector<int>, vector<int>::iterator>(v);


		/*
		������ ����� �ʰ� size �񱳽� vector�� typedef�� size_type�� ���
			VS 2017������ ��� ���� �ʴ´�.
		*/
		vector<int>::size_type size = 0;
		cout << (v.size() == size) << endl; // 0
		cout << typeid(vector<int>::size_type).name() << endl; // unsigned int
		// typeid(T) : T�� ���� typeinfo ��ü�� ����

		cout << v.size() << endl; // 3
		cout << v.capacity() << endl; // 3
		cout << v.max_size() << endl; // 1073741823
	}

	// 
	cout << "===== �޸� ���Ҵ� =====" << endl;
	{
		cout << "--- capacity" << endl;
		{
			vector<int> v;
			for (size_t i = 0; i < 10; i++)
			{
				v.push_back(i);
				cout << v.size() << ", " << v.capacity() << endl;
			}
			/*
			1, 1
			2, 2
			3, 3
			4, 4 // ��������� �߰��Ǵ� ��Ҽ� ��ŭ�� �޸𸮸� ���Ҵ��Ѵ�.
			5, 6 // ���⼭���� ���� ��� ���� 1/2 ��ŭ �ø���.
			6, 6
			7, 9 // + 1/2
			8, 9
			9, 9
			10, 13 // + 1/1
			*/
		}

		cout << "--- reserve" << endl;
		{
			/*
			vector ���� �� reserve �ϸ� capacity�� �þ���� ��Ұ� �þ�� �ʴ´�.
			*/
			vector<int> v;
			v.reserve(7);
			for (size_t i = 0; i < 10; i++)
			{
				v.push_back(i);
				cout << v.size() << ", " << v.capacity() << endl;
			}
			/*
			1, 7
			2, 7
			3, 7
			4, 7
			5, 7
			6, 7
			7, 7 // �̸� ��Ƶ� 7������ �޸� ���Ҵ����� �ʴ´�.
			8, 10
			9, 10
			10, 10
			*/
		}

		cout << "--- resize" << endl;
		{
			/*
			resize�� size�� �����Ѵ�.
			size�� Ű��� capacity�� �þ���� ���� ���� capacity�� �پ���� �ʴ´�.
			*/
			vector<int> v;
			v.resize(100);
			cout << v.size() << ", " << v.capacity() << endl; // 100, 100 : size�� capacity�� �þ��.
			v.resize(10);
			cout << v.size() << ", " << v.capacity() << endl; // 10, 100 : size�� �پ����� capacity�� ���� �ʾҴ�.

			v.resize(100, 9); // Ȯ���ϴ� ��ҿ� �ʱⰪ�� 9�� �Ѵ�.
		}
		
	}

	cout << "===== �����̳� ���� =====" << endl;
	{
		cout << "--- clear, empty" << endl;
		{
			vector<int> v;
			v.push_back(1);
			cout << v.size() << endl; // 1
			cout << v.empty() << endl; // 0

			v.clear();
			cout << v.size() << endl; // 0
			cout << v.empty() << endl; // 1
		}

		cout << "--- swap()�� ����Ͽ� capacity�� 0���� �����" << endl;
		{
			/*
			capacity�� 0���� ����� �Լ��� ������ swap���� �� �� �ִ�.
			*/
			vector<int> v1;
			v1.resize(100);
			cout << v1.size() << ", " << v1.capacity() << endl; // 100, 100

			vector<int>().swap(v1); // �ӽð�ü�� �����ϰ� swap() ȣ��
			cout << v1.size() << ", " << v1.capacity() << endl; // 0, 0
		}
		
	}

	cout << "===== ���� ��ȸ =====" << endl;
	{
		cout << "--- front(), back()"<< endl;
		{
			vector<int> v;
			for (size_t i = 0; i < 10; i++)
			{
				v.push_back(i);
			}

			cout << v.front() << endl; // 0
			cout << v.back() << endl; // 9

			/*
			��ȸ�Ӿƴ϶� �� ���浵 �����ϴ�.
			*/
			v.front() = 100;
			v.back() = 999;

			cout << v.front() << endl; // 100
			cout << v.back() << endl; // 999
		}

		cout << "--- [], at()" << endl;
		{
			/*
			���� ��ġ ����
			[] : ���� ������ ���� �ʾ� �������� �����ϴ�.
			at : ���� ������ �ؼ� �������� �����ϴ�.
			*/
			vector<int> v;
			for (size_t i = 0; i < 10; i++)
			{
				v.push_back(i);
			}

			cout << v[1] << endl; // 1
			cout << v.at(1) << endl; // 1

			try
			{
//				cout << v[10] << endl; // "vector subscript out of range(���� ÷�ڰ� ������ �����)" �޸� ���� ������ ���α׷� �ٿ�. ó�� �Ұ�.
				cout << v.at(10) << endl; // ���ܰ�  �߻�. ó�� ����.

			}
			catch (const std::exception& e)
			{
				cout << e.what() << endl; // invalid vector<T> subscript
			}
		}
	}

	cout << "===== ��� ���� �ʱ�ȭ =====" << endl;
	{
		vector<int> v(3, 9); // 3���� ���Ҹ� 9�� �ʱ�ȭ
		printContainer<vector<int>, vector<int>::iterator>(v); // 9, 9, 9
		v.assign(3, 0); // 3���� ���Ҹ� 0���� �ʱ�ȭ
		printContainer<vector<int>, vector<int>::iterator>(v); // 0, 0, 0
	}

	cout << "===== �ݺ��� =====" << endl;
	{
		cout << "--- ���� ���� �ݺ���" << endl;
		{
			/*
			vector, deque ���� ���� ���� �ݺ��ڸ� ������ �ְ� �̷� ���� [], +, -, +=, -= ������ �����ϴ�.
			*/
			vector<int> v;
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);

			vector<int>::iterator iter = v.begin();

			cout << iter[0] << endl; // 1

			iter += 1;
			cout << iter[0] << endl; // 2, ���� iter�� ��ġ���� []�����ϹǷ� 3�� ���´�.
			cout << iter[1] << endl; // 3, ���� iter�� ��ġ���� []�����ϹǷ� 3�� ���´�.

			iter -= 1;
			cout << iter[0] << endl; // 1
		}

		cout << "--- ��� �ݺ���" << endl;
		{
			/*
				��� �ݺ��ڸ� ����Ͽ� �����ϰ� ��ȸ�� �����ϴ�.
				�̵��� �� ������ ���� ������ �� �ִ�.
			*/
			vector<int> v;
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);

			vector<int>::iterator iter = v.begin(); // �̵� ����, �� ���� ����
			vector<int>::const_iterator const_iter = v.begin(); // �̵� ����, �� ���� �Ұ�

			const vector<int>::iterator iter_const = v.begin(); // �̵� �Ұ�, �� ���� ����
			const vector<int>::const_iterator const_iter_const = v.begin(); // �̵� �Ұ�, �� ���� �Ұ�

			iter += 1;
			const_iter += 1;
//			iter_const += 1; // ������ ����, �̵� �Ұ�
//			const_iter_const += 1; // ������ ����, �̵� �Ұ�

			(*iter) = 9;
//			(*const_iter) = 9; // ������ ����, �� ���� �Ұ�
			(*iter_const) = 9;
//			(*const_iter_const) = 9; // ������ ����, �� ���� �Ұ�
		}

		cout << "--- ������ �ݺ���" << endl;
		{
			/*
				������ �ݺ��ڸ� 
			*/
			vector<int> v;
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);

			vector<int>::reverse_iterator riter = v.rbegin(); // �̵� ����, �� ���� ����
			vector<int>::reverse_iterator riter_end = v.rend(); // �̵� ����, �� ���� ����
			while (riter != riter_end)
			{
				cout << *riter << endl; // 3, 2, 1
				++riter;
			}
		}
	}

	cout << "===== ���� ��ġ ���� �߰�/���� =====" << endl;
	{
		/*
		������ ��ġ�� ���Ҹ� �����ϰ� ���Ե� ������ �ݺ��ڸ� ��ȯ�Ѵ�.
		���� ���Һ��� ������ ��� ���Ҵ� �ڷ� �з�����.
		*/

		cout << "--- ���� 1�� ����" << endl;
		{
			vector<int> v(3, 0); // 3���� ���Ҹ� 0���� �ʱ�ȭ
			vector<int>::iterator iter = v.begin();
			vector<int>::iterator iter2 = v.insert(iter + 1, 1); // �߰��� ���Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.

			printContainer<vector<int>, vector<int>::iterator>(v); // 0, 1, 0, 0
			cout << *iter2 << endl; // 1
		}

		cout << "--- ���� ������ ����" << endl;
		{
			vector<int> v(3, 0); // 3���� ���Ҹ� 0���� �ʱ�ȭ
			vector<int>::iterator iter = v.begin();
			iter = v.begin();
			vector<int>::iterator iter3 = v.insert(iter, 2, 1); // ���� 2�� ����

			printContainer<vector<int>, vector<int>::iterator>(v); // 1, 1, 0, 0, 0
			cout << *iter3 << endl; // 1
		}

		cout << "--- ���� ������ �������� ����" << endl;
		{
			/*
			�ٸ� vector�� ���� ������ ����
			*/
			vector<int> v1(3, 0); // 3���� ���Ҹ� 0���� �ʱ�ȭ
			vector<int>::iterator iter = v1.begin();
			vector<int> v2(3, 1);
			v1.insert(iter + 1, v2.begin(), v2.end());

			printContainer<vector<int>, vector<int>::iterator>(v1); // 0, 1, 1, 1, 0, 0
		}
	}

	cout << "===== ���� ��ġ ���� ���� =====" << endl;
	{
		/*
		������ ��ġ�� ���Ҹ� �����ϰ� ���ŵ� ���� ���� ������ �ݺ��ڸ� ��ȯ
		���ŵ� ������ �ڸ��� ���� ���ҵ��� ����� ä���.
		*/

		cout << "--- ���� 1�� ����" << endl;
		{
			vector<int> v; // 3���� ���Ҹ� 0���� �ʱ�ȭ
			v.push_back(0);
			v.push_back(1);
			v.push_back(2);

			vector<int>::iterator iter = v.begin();
			v.erase(iter + 1);

			printContainer<vector<int>, vector<int>::iterator>(v); // 0, 2
		}

		cout << "--- ���� ������ ����" << endl;
		{
			vector<int> v; // 3���� ���Ҹ� 0���� �ʱ�ȭ
			v.push_back(0);
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);
			v.push_back(4);

			vector<int>::iterator iter = v.begin();
			v.erase(iter + 1, iter + 3); // [ ) �������� ����

			printContainer<vector<int>, vector<int>::iterator>(v); // 0, 3, 4
		}
	}

	cout << "===== �����̳� ������ =====" << endl;
	{
		vector<int> v1;
		v1.push_back(0);
		v1.push_back(1);
		v1.push_back(2);

		vector<int> v2(v1.begin(), v1.end());

		cout << (v1 == v2) << endl; // 1

		v2.push_back(3);
		cout << (v1 == v2) << endl; // 0

		cout << (v1 > v2) << endl; // 0
		cout << (v1 < v2) << endl; // 1 : ���Ұ� �� ���� ���� ũ��
	}
}