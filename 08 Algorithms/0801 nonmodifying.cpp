#include <iostream>
#include <algorithm>
#include "utils.h"

using namespace std;

/*
원소를 수정하지 않는 알고리즘
	원소의 순서나 원소의 값을 변경하지 않고 원소를 읽기만 하는 알고리즘

adjacent_find
count
count_if
equal
find
find_if
find_end
find_first_of
for_each
lexicographical_compare
max
min
max_element
min_element
mismatch
search
search_n
*/

void _0801_nonmodifying() {
	cout << "===== adjacent =====" << endl;
	{
		/*
		adjacent
			adjacent [əˈdʒeɪsnt]
			형용사 1. 지역·건물 등이인접한, 가까운

		순차열에서 현재 원소와 다음 원소가 같아지는 첫 원소의 반복자를 반환
		만약 없으면 구간의 끝 반복자를 반환(컨테이너의 끝 반복자가 아님)
		*/

		cout << "--- 중복 원소 찾기 adjacent_find" << endl;
		{
			vector<int> v = INIT_0112;
			vector<int>::iterator iter = adjacent_find(v.begin(), v.end());

			// 찾음
			cout << *iter << endl; // 1
			cout << *(iter + 1) << endl; // 1
			cout << *(iter + 2) << endl; // 2

			// 못 찾음
			iter = adjacent_find(v.begin() + 2, v.end());
			cout << (iter == v.end()) << endl; // 1 : 중복된 원소가 없어서 순차열의 마지막 반복자를 반환함.(무조건 컨테이너의 end가 아니다)
		}

		cout << "--- 특정 조건으로 중복 원소 찾기 adjacent_find" << endl;
		{
			/*
			이항 조건자를 전달
				bool을 반환하는 함수, 함수 객체, 함수 포인터
			*/

			vector<int> v = {0, 1, 2, 3};
			// 다음 원소가 3인 원소 찾기
			vector<int>::iterator iter = adjacent_find(v.begin(), v.end(), [](int& l, int&r) -> bool {
				return r == 3;
			});

			cout << *iter << endl; // 2
		}

	}

	cout << "===== count =====" << endl;
	{
		/*
		순차열에서 특정 원소의 개수
		*/
		cout << "--- 순차열에서 특정 원소의 개수 count" << endl;
		{
			vector<int> v = INIT_0112;
			cout << count(v.begin(), v.end(), 1) << endl; // 2
		}

		cout << "--- 순차열에서 조건에 맞는 특정 원소의 개수 count_if" << endl;
		{
			/*
			단항 조건자로 특정 원소의 개수 알아내기
			*/
			vector<int> v = INIT_0112;
			cout << count_if(v.begin(), v.end(), [](int& i) -> bool {return i == 1; }) << endl; // 2
		}
	}

	cout << "===== equal =====" << endl;
	{
		/*
		두 순차열의 원소가 모두 같은지 판단

		기본적으로 두 순차열은 같은 길이라고 가정하기 때문에 
		두 번재 순차열의 끝을 지정하지 않아도 첫 번째 순차열의 반복자로 끝 반복자를 계산해낸다.
			첫 번째 순차열 : [b, e)
			두 번재 순차렬 : [b2, e2)
			e2를 전달하지 않아도 b2 + (e - b)가 e2이다.
		*/
		cout << "--- 기본 조건자 equal" << endl;
		{
			vector<int> v1 = INIT_012;
			vector<int> v2 = INIT_0112;
			cout << equal(v1.begin(), v1.end(), v2.begin()) << endl; // 0 : 다름

			v2 = INIT_012;
			cout << equal(v1.begin(), v1.end(), v2.begin()) << endl; // 1 : 같음
		}

		cout << "--- 특정 조건자 equal" << endl;
		{
			vector<int> v1 = INIT_012;
			vector<int> v2 = INIT_210;

			// 두 순차열의 원소의 합이 2이면 같다.
			cout << equal(v1.begin(), v1.end(), v2.begin(), [](int& l, int& r) -> bool {
				return l + r == 2;
			}) << endl; // 1 : 같음
		}
	}


	cout << "===== find =====" << endl;
	{
		/*
		순차열에서 원소 찾기
		순차열에서 순차열 찾기
		*/
		cout << "--- 원소 찾기 find" << endl;
		{
			vector<int> v = INIT_0112;
			cout << (*find(v.begin(), v.end(), 2)) << endl; // 2
		}

		cout << "--- 특정 조건자로 원소 찾기 find_if" << endl;
		{
			/*
			단항 조건자로 특정 원소를 찾았는지 판단
			*/
			vector<int> v = INIT_0112;
			// 0보다 큰 원소
			cout << (*find_if(v.begin(), v.end(), [](int& i) -> bool {return i > 0; })) << endl; // 1
		}

		cout << "--- 순차열에서 순차열 찾기 find_end" << endl;
		{
			/*
			일치하는 순차열 구간이 여러 개이면 마지막 순차열 구간의 첫 원소를 반환
			*/
			vector<int> v1 = {0, 1, 2, 3, 1, 2};
			vector<int> v2 = { 1, 2 };

			vector<int>::iterator iter = find_end(v1.begin(), v1.end(), v2.begin(), v2.end());
			cout << *iter << endl; // 1
			cout << *(iter - 1) << endl; // 3
			cout << *(iter + 1) << endl; // 2
		}

		cout << "--- 특정 조건자로 순차열에서 순차열 찾기 find_end" << endl;
		{
			/*
			조건자를 지정하여 일치하는 마지막 순차열의 첫 원소의 반복자 반환
			*/
			vector<int> v1 = { 0, 1, 2, 3, 1, 2 };
			vector<int> v2 = { 1, 2 };

			// 첫 번째 순차열보다 1작은 순차열 찾기
			vector<int>::iterator iter = find_end(v1.begin(), v1.end(), v2.begin(), v2.end(), [](int &l, int &r) -> bool {
				return l == r + 1;
			});
			cout << *iter << endl; // 2
			cout << *(iter - 1) << endl; // 1
			cout << *(iter + 1) << endl; // 3
		}

		cout << "--- 두 순차열의 같은 원소중 첫 번째 find_first_of" << endl;
		{
			/*
			두 순차열의 모든 원소중 같은 원소들의 첫 번째 원소의 반복자 반환
			*/
			vector<int> v1 = { 0, 1, 2, 3 };
			vector<int> v2 = { 2, 1 };

			vector<int>::iterator iter = find_first_of(v1.begin(), v1.end(), v2.begin(), v2.end());
			cout << *iter << endl; // 1 : 같은 원소 2, 1 중에 1이 먼저 있으므로 1이 반환된다.
		}

		cout << "--- 조건자를 사용하여 두 순차열의 같은 원소중 첫 번째 find_first_of" << endl;
		{
			/*
			조건자를 사용하여 두 순차열의 모든 원소중 같은 원소들의 첫 번째 원소의 반복자 반환
			*/
			vector<int> v1 = { 0, 1, 2, 3 };
			vector<int> v2 = { 2, 1 };

			// 두 번째 순차열에서 1뺀 값과 같은 원소 찾기
			vector<int>::iterator iter = find_first_of(v1.begin(), v1.end(), v2.begin(), v2.end(), [](int &l, int &r) -> bool {
				return l == r - 1;
			});
			cout << *iter << endl; // 0
		}
	}


	cout << "===== for_each =====" << endl;
	{
		/*
		순차열의 모든 원소에 사용자 동작을 적용

		for_each는 원소를 수정하는 알고리즘과 하지 않는 알고리즘 둘다에 포함됨
		*/

		cout << "--- 함수를 이용한 for_each" << endl;
		{
			vector<int> v = INIT_012;
			for_each(v.begin(), v.end(), [](int &i) -> void {
				cout << i << endl; // 0, 1, 2
			});
		}

		cout << "--- 함수 객체를 이용한 for_each" << endl;
		{
			/*
			함수 객체를 이용하면 함수에 상태를 설정하여 전달 할 수 있기 때문에 더 유연하게 사용할 수 있다.
			*/
			struct F {
				char m_ch;
				F(char ch) : m_ch(ch) {}
				void operator()(int &i){
					cout << i << m_ch << endl;
				}
			};
			vector<int> v = INIT_012;
			for_each(v.begin(), v.end(), F('*')); // 0*, 1*, 2*
		}
	}


	cout << "===== lexicographical_compare =====" << endl;
	{
		/*
		lexicographical
			[lèksəkάgrəfik]
			형용사 1. 사전편집

		두 순차열의 모든 원소를 문자열처럼 사전순 비교할 때 사용

		< 연산자와 같은 반환값
		
		모든 원소가 같으면 false를 반환
		*/
		cout << "--- 두 순차열의 사전순 비교 lexicographical_compare" << endl;
		{
			vector<int> v1 = {0, 1, 2};
			
			vector<int> v2 = {0, 1, 3};
			cout << lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()) << endl; // 1 : v1이 v2보다 작다.

			vector<int> v3 = {0, 0, 99};
			cout << lexicographical_compare(v1.begin(), v1.end(), v3.begin(), v3.end()) << endl; // 0 : v1보다 v2가 작다.
		}

		cout << "--- 특정 조건자로 두 순차열의 사전순 비교 lexicographical_compare" << endl;
		{
			vector<int> v1 = { 100, 101, 102 };
			vector<int> v2 = { 5, 6, 7 };
			// 1의 자릿수가 더 작은지 비교
			cout << lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), [](int &l, int &r) -> bool {
				return (l % 10) < (r % 10);
			}) << endl; // 1
		}
	}

	cout << "===== max, min =====" << endl;
	{
		cout << "--- 크거나 작은값 찾기 max min" << endl;
		{
			cout << max(1, 2) << endl; // 2
			cout << min(1, 2) << endl; // 1
		}

		cout << "--- 조건자로 크거나 작은값 찾기 max min" << endl;
		{
			// 1의 자릿수가 큰 값 반환
			cout << max(101, 202, [](const int &l, const int &r) -> bool {
				return ((l % 10) < (r % 10));
			}) << endl; // 202
		}

		cout << "--- 순차열에서 가장 크거나 작은 값 찾기 max_element min_element" << endl;
		{
			/*
			가장 크거나 작은 원소중에 첫 반복자를 반환
			*/
			vector<int> v = { 2, 0, 4, 7, 2, 9, 4, 8, 9, 3, 0, 8 }; // 가장 큰값: 9, 가장 작은값: 0

			// 가장 큰 값 출력
			vector<int>::iterator iter_max = max_element(v.begin(), v.end());
			cout << *iter_max << endl; // 9
			cout << *(iter_max - 1) << endl; // 2
			cout << *(iter_max + 1) << endl; // 4

			// 가장 작은 값 출력
			vector<int>::iterator iter_min = min_element(v.begin(), v.end());
			cout << *iter_min << endl; // 0
			cout << *(iter_min - 1) << endl; // 2
			cout << *(iter_min + 1) << endl; // 4
		}

		cout << "--- 조건자로 순차열에서 가장 크거나 작은 값 찾기 max_element min_element" << endl;
		{
			/*
			조건자로 가장 크거나 작은 원소중에 첫 반복자를 반환
			*/
			class A {
			public:
				A(int i) : i(i) {}
				int i;
			};

			vector<A> v = { 2, 0, 4, 7, 2, 9, 4, 8, 9, 3, 0, 8 }; // 가장 큰값: 9, 가장 작은값: 0

			// 가장 큰 값 출력
			vector<A>::iterator iter = max_element(v.begin(), v.end(), [](A &l, A &r) -> bool {
				return l.i < r.i; 
			});
			cout << iter->i << endl; // 9
			cout << (iter - 1)->i << endl; // 2
			cout << (iter + 1)->i << endl; // 4
		}
	}

	cout << "===== mismatch =====" << endl;
	{
		/*
		두 순차열의 원소의 값이 서로 다른 위치의 반복자 쌍을 반환

		두 번째 순차열의 길이는 첫 번째보다 짧으면 런타임 에러난다. "cannot seek vector iterator after end"
		긴건 된다.
		*/
		cout << "--- 원소가 다른 위치 반환 mismatch" << endl;
		{
			vector<int> v1 = { 0, 1, 2, 3, 4 };
			vector<int> v2 = { 0, 1, 2, 9, 5 };

			pair<vector<int>::iterator, vector<int>::iterator> pair = mismatch(v1.begin(), v1.end(), v2.begin());
			cout << *pair.first << endl; // 3
			cout << *pair.second << endl; // 9
		}

		cout << "--- 조건자로 원소가 다른 위치 반환 mismatch" << endl;
		{
			vector<int> v1 = { 0, 1, 2, 3, 4 };
			vector<int> v2 = { 1, 2, 3, 9, 5 };

			// 두 원소의 차이가 5이상 나는 위치 반환
			// 조건자 반환값 : true(같다), false(다르다)
			pair<vector<int>::iterator, vector<int>::iterator> pair = mismatch(v1.begin(), v1.end(), v2.begin(), [](int &l, int &r) -> bool {
				return abs(l - r) < 5;
			});
			cout << *pair.first << endl; // 3
			cout << *pair.second << endl; // 9
		}

		cout << "--- " << endl;
		{

		}

		cout << "--- " << endl;
		{

		}
	}

	cout << "===== search =====" << endl;
	{
		/*
		하나의 순차열에서 다른 순차열을 찾을 때 find_end는 
		마지막 일치하는 순차열의 첫 원소의 반복자를 반환하지만 
		search는 첫 순차열의 첫 원소의 반복자를 반환한다.
		*/
		cout << "--- 순차열에서 순차열을 찾기 search" << endl;
		{
			vector<int> v1 = { 0, 1, 2, 3, 4, 1, 2, 0 };
			vector<int> v2 = { 1, 2 };
			vector<int>::iterator iter = search(v1.begin(), v1.end(), v2.begin(), v2.end());
			 
			cout << *iter << endl; // 1
			cout << *(iter - 1) << endl; // 0
			cout << *(iter + 1) << endl; // 2
		}

		cout << "--- 원소가 n번 연속하게 반복되는지 찾기 search_n" << endl;
		{
			/*
			특정값의 원소가 n번 반복하는 순차열의 첫 원소 반복자 반환
			없으면 순차열의 끝 반환
			*/
			vector<int> v = { 0, 1, 1, 2, 3, 4, 4, 4, 1, 2, 0 };
			vector<int>::iterator iter = search_n(v.begin(), v.end(), 9, 3); // 3이 9번 연속해서 반복하는가
			cout << (iter == v.end()) << endl; // 1 : 못찾음

			iter = search_n(v.begin(), v.end(), 2, 1); // 1이 2번 연속해서 반복하는가
			cout << (iter == v.end()) << endl; // 0 : 찾음
			cout << *iter << endl; // 1
			cout << *(iter - 1) << endl; // 0
		}

		cout << "--- 조건자로 원소가 n번 연속하게 반복되는지 찾기 search_n" << endl;
		{
			/*
			조건자로 특정값의 원소가 n번 반복하는 순차열의 첫 원소 반복자 반환
			없으면 순차열의 끝 반환
			*/
			vector<int> v = { 101, 209, 309, 401 };

			// 나머지가 9인 원소가 2번 반복되는 순차열의 첫 반복자 반환
			vector<int>::iterator iter = search_n(v.begin(), v.end(), 2, 9, [](const int &i, const int &v) -> bool {
				return (i % 10) == v;
			}); // 3이 9번 연속해서 반복하는가
			cout << (iter == v.end()) << endl; // 0 : 찾음
			cout << *iter << endl; // 209
			cout << *(iter - 1) << endl; // 101
			cout << *(iter + 1) << endl; // 309
		}
	}

	cout << "=====  =====" << endl;
	{
		cout << "--- " << endl;
		{

		}
	}
}