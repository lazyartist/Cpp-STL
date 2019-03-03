#include <iostream>
#include <vector>
#include "utils.h"

using namespace std;

/*
vector 컨테이너
	시퀸스 컨테이너이므로 원소의 저장 위치가 정해지며 배열 기반 컨테이너이므로 원소가 하나의 메모리블록에 할당됨
		하나의 메모리 블록? 블록?

	원소 추가 시 메모리 재할당이 발생할 수 있고 이는 큰 비용이 들기 때문에 capacity(), reserve()등을 제공하여
	미리 메모리 할당할 수 있는 방법을 제공

	연속 메모리 구조를 사용하기 때문에 at(), [] 등으로 원소에 접근하는 속도가 빠르지만
	insert(), erase(), push_back()을 많이 호출한다면 메모리 재할당을 유발 하므로 다른 컨테이너가 다 낫다.

	앞쪽에는 원소를 추가/제거할 수 없으며 뒤쪽에만 추가/제거 가능
		deque, list는 앞쪽에 원소 추가 가능(push_front, pop_front)

	size(), max_size()는 모든 컨테이너가 가지는 멤버 함수
	capacity()는 vector만 가지는 멤버 함수
	원소가 추가될 때마다 메모리의 재할당과 복사를 하지 않고 미리 넉넉한 메모리를 확보한다.

	max_size()
		1073741823 : 이론적으로 할당할 수 있는 최대 크기, 시스템 메모리가 부족하면 할당 못할 수 있다.
		1073741823 + 1 / 1024 / 1024 / 1024 = 1GB
		32bit, 64bit 모두 같은 값이 나온다.

	iter 할당 이후 원소 추가/삭제 등으로 메모리가 재할당 됐다면 iterator가 다른 곳을 가리키게 되기 때문에 재할당 해줘야한다.
	안그러면 에러난다. "vector insert iterator outside range"

	컨테이너 연산자
		==, !=, <, <=, >=
*/

void _0601_vector() {
	cout << "===== vector 생성 =====" << endl;
	{
		cout << "--- 기본 생성" << endl;
		{
			/*
			vector<int> v(10); 는 10개의 요소를 기본값으로 초기화한다는 뜻. 따라서 요소가 10개있다.
			*/
			vector<int> v1(3); // 기본값 0으로 초기화된 3개의 원소를 갖는 vector
			vector<int> v2(3, 9); // 기본값 9로 초기화된 3개의 원소를 갖는 vector
		}

		cout << "--- 반복자를 통한 생성" << endl;
		{
			vector<int> v1(3, 1);
			vector<int> v2(v1.begin(), v1.end());

			printContainer<vector<int>, vector<int>::iterator>(v2); // 1, 1, 1
		}

		cout << "--- assign 초기화" << endl;
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
		//vector<int> v(3, 9); // 9의 값으로 3개의 원소 생성
		vector<int> v; // 9의 값으로 3개의 원소 생성
		printContainer<vector<int>, vector<int>::iterator>(v);


		/*
		컴파일 경고나지 않게 size 비교시 vector에 typedef된 size_type을 사용
			VS 2017에서는 경고 나지 않는다.
		*/
		vector<int>::size_type size = 0;
		cout << (v.size() == size) << endl; // 0
		cout << typeid(vector<int>::size_type).name() << endl; // unsigned int
		// typeid(T) : T에 대한 typeinfo 객체를 리턴

		cout << v.size() << endl; // 3
		cout << v.capacity() << endl; // 3
		cout << v.max_size() << endl; // 1073741823
	}

	// 
	cout << "===== 메모리 재할당 =====" << endl;
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
			4, 4 // 여기까지는 추가되는 요소수 만큼만 메모리를 재할당한다.
			5, 6 // 여기서부터 기존 요소 수의 1/2 만큼 늘린다.
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
			vector 생성 후 reserve 하면 capacity는 늘어나지만 요소가 늘어나지 않는다.
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
			7, 7 // 미리 잡아둔 7까지는 메모리 재할당하지 않는다.
			8, 10
			9, 10
			10, 10
			*/
		}

		cout << "--- resize" << endl;
		{
			/*
			resize로 size를 변경한다.
			size를 키우면 capacity도 늘어나지만 줄일 때는 capacity가 줄어들지 않는다.
			*/
			vector<int> v;
			v.resize(100);
			cout << v.size() << ", " << v.capacity() << endl; // 100, 100 : size와 capacity가 늘어났다.
			v.resize(10);
			cout << v.size() << ", " << v.capacity() << endl; // 10, 100 : size는 줄었지만 capacity는 줄지 않았다.

			v.resize(100, 9); // 확장하는 요소에 초기값을 9로 한다.
		}
		
	}

	cout << "===== 컨테이너 비우기 =====" << endl;
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

		cout << "--- swap()을 사용하여 capacity를 0으로 만들기" << endl;
		{
			/*
			capacity를 0으로 만드는 함수는 없지만 swap으로 할 수 있다.
			*/
			vector<int> v1;
			v1.resize(100);
			cout << v1.size() << ", " << v1.capacity() << endl; // 100, 100

			vector<int>().swap(v1); // 임시객체를 생성하고 swap() 호출
			cout << v1.size() << ", " << v1.capacity() << endl; // 0, 0
		}
		
	}

	cout << "===== 원소 조회 =====" << endl;
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
			조회뿐아니라 값 변경도 가능하다.
			*/
			v.front() = 100;
			v.back() = 999;

			cout << v.front() << endl; // 100
			cout << v.back() << endl; // 999
		}

		cout << "--- [], at()" << endl;
		{
			/*
			임의 위치 참조
			[] : 범위 점검을 하지 않아 빠르지만 위험하다.
			at : 범위 점검을 해서 느리지만 안전하다.
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
//				cout << v[10] << endl; // "vector subscript out of range(벡터 첨자가 범위를 벗어났다)" 메모리 접근 오류로 프로그램 다운. 처리 불가.
				cout << v.at(10) << endl; // 예외가  발생. 처리 가능.

			}
			catch (const std::exception& e)
			{
				cout << e.what() << endl; // invalid vector<T> subscript
			}
		}
	}

	cout << "===== 모든 원소 초기화 =====" << endl;
	{
		vector<int> v(3, 9); // 3개의 원소를 9로 초기화
		printContainer<vector<int>, vector<int>::iterator>(v); // 9, 9, 9
		v.assign(3, 0); // 3개의 원소를 0으로 초기화
		printContainer<vector<int>, vector<int>::iterator>(v); // 0, 0, 0
	}

	cout << "===== 반복자 =====" << endl;
	{
		cout << "--- 임의 접근 반복자" << endl;
		{
			/*
			vector, deque 만이 임의 접근 반복자를 가지고 있고 이로 인해 [], +, -, +=, -= 연산이 가능하다.
			*/
			vector<int> v;
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);

			vector<int>::iterator iter = v.begin();

			cout << iter[0] << endl; // 1

			iter += 1;
			cout << iter[0] << endl; // 2, 현재 iter의 위치에서 []연산하므로 3이 나온다.
			cout << iter[1] << endl; // 3, 현재 iter의 위치에서 []연산하므로 3이 나온다.

			iter -= 1;
			cout << iter[0] << endl; // 1
		}

		cout << "--- 상수 반복자" << endl;
		{
			/*
				상수 반복자를 사용하여 안전하게 순회가 가능하다.
				이동과 값 변경을 따로 제한할 수 있다.
			*/
			vector<int> v;
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);

			vector<int>::iterator iter = v.begin(); // 이동 가능, 값 변경 가능
			vector<int>::const_iterator const_iter = v.begin(); // 이동 가능, 값 변경 불가

			const vector<int>::iterator iter_const = v.begin(); // 이동 불가, 값 변경 가능
			const vector<int>::const_iterator const_iter_const = v.begin(); // 이동 불가, 값 변경 불가

			iter += 1;
			const_iter += 1;
//			iter_const += 1; // 컴파일 에러, 이동 불가
//			const_iter_const += 1; // 컴파일 에러, 이동 불가

			(*iter) = 9;
//			(*const_iter) = 9; // 컴파일 에러, 값 변경 불가
			(*iter_const) = 9;
//			(*const_iter_const) = 9; // 컴파일 에러, 값 변경 불가
		}

		cout << "--- 역방향 반복자" << endl;
		{
			/*
				역방향 반복자를 
			*/
			vector<int> v;
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);

			vector<int>::reverse_iterator riter = v.rbegin(); // 이동 가능, 값 변경 가능
			vector<int>::reverse_iterator riter_end = v.rend(); // 이동 가능, 값 변경 가능
			while (riter != riter_end)
			{
				cout << *riter << endl; // 3, 2, 1
				++riter;
			}
		}
	}

	cout << "===== 임의 위치 원소 추가/삭제 =====" << endl;
	{
		/*
		지정한 위치에 원소를 삽입하고 삽입된 원소의 반복자를 반환한다.
		원래 원소부터 끝까지 모든 원소는 뒤로 밀려난다.
		*/

		cout << "--- 원소 1개 삽입" << endl;
		{
			vector<int> v(3, 0); // 3개의 원소를 0으로 초기화
			vector<int>::iterator iter = v.begin();
			vector<int>::iterator iter2 = v.insert(iter + 1, 1); // 추가한 원소를 가리키는 반복자를 반환한다.

			printContainer<vector<int>, vector<int>::iterator>(v); // 0, 1, 0, 0
			cout << *iter2 << endl; // 1
		}

		cout << "--- 원소 여러개 삽입" << endl;
		{
			vector<int> v(3, 0); // 3개의 원소를 0으로 초기화
			vector<int>::iterator iter = v.begin();
			iter = v.begin();
			vector<int>::iterator iter3 = v.insert(iter, 2, 1); // 원소 2개 삽입

			printContainer<vector<int>, vector<int>::iterator>(v); // 1, 1, 0, 0, 0
			cout << *iter3 << endl; // 1
		}

		cout << "--- 원소 여러개 구간으로 삽입" << endl;
		{
			/*
			다른 vector의 원소 범위로 삽입
			*/
			vector<int> v1(3, 0); // 3개의 원소를 0으로 초기화
			vector<int>::iterator iter = v1.begin();
			vector<int> v2(3, 1);
			v1.insert(iter + 1, v2.begin(), v2.end());

			printContainer<vector<int>, vector<int>::iterator>(v1); // 0, 1, 1, 1, 0, 0
		}
	}

	cout << "===== 임의 위치 원소 삭제 =====" << endl;
	{
		/*
		지정한 위치에 원소를 제거하고 제거된 원소 다음 원소의 반복자를 반환
		제거된 원소의 자리를 다음 원소들이 당겨져 채운다.
		*/

		cout << "--- 원소 1개 제거" << endl;
		{
			vector<int> v; // 3개의 원소를 0으로 초기화
			v.push_back(0);
			v.push_back(1);
			v.push_back(2);

			vector<int>::iterator iter = v.begin();
			v.erase(iter + 1);

			printContainer<vector<int>, vector<int>::iterator>(v); // 0, 2
		}

		cout << "--- 원소 여러개 제거" << endl;
		{
			vector<int> v; // 3개의 원소를 0으로 초기화
			v.push_back(0);
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);
			v.push_back(4);

			vector<int>::iterator iter = v.begin();
			v.erase(iter + 1, iter + 3); // [ ) 순차열을 제거

			printContainer<vector<int>, vector<int>::iterator>(v); // 0, 3, 4
		}
	}

	cout << "===== 컨테이너 연산자 =====" << endl;
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
		cout << (v1 < v2) << endl; // 1 : 원소가 더 많은 쪽이 크다
	}
}