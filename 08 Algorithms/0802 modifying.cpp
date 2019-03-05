#include <iostream>
#include <algorithm>
#include "utils.h"

using namespace std;

/*
modifying algorithms
	원소의 값을 변경하거나 목적지 순차열로 원소를 복사하는 알고리즘

copy(b,e,t)
	[b, e)의 순차열을 구간 [t, t+(e-b))의 순차열로 모두 복사
	기본적으로 덮어쓰기로 작동하며 삽입으로 작동하게 하려면 반복자 어댑터(insert_iterator)등을 사용
	목적 순차열은 원본 순차열 이상의 원소를 가지고 있어야함
	반환값 : 목적 순차열의 마지막 원소

copy_backward(b,e,t)
	[b,e)의 원소를 [t-(e-b), t) 순차열에 원본 마지막부터 반대로 복사
	반환값 : 목적 순차열의 첫 원소

fill(b,e,x)
	[b,e) 구간의 원소를 x로 채운다

fill_n(b,n,x)
	[b,b+n) 구간의 원소를 x로 채운다

for_each(b,e,f)
	[b,e) 구간의 모든 원소에 f(*p)를 적용(p는 반복자)
	f는 함수 객체, 함수, 함수 포인터, 람다
	출력 매개변수(out parameter)를 사용하여 원소를 변경
		for_each를 사용하여 원소를 변경시에는 출력 매개변수를 반드시 레퍼런스로 정의해야한다.

generate(b,e,f)
	[b,e) 구간의 모든 원소에 f()를 적용
		단순 f()의 반환값을 적용하기 때문에 원소의 원래값을 활용할 수 없다.
		따라서 함수 객체처럼 상태값을 갖는 함수를 사용해야 순차적으로 다른 값을 적용할 수 있다.

swap(a,b)
	a와 b를 교환

iter_swap(p,q)
	반복자가 가리키는 *p와 *q를 교환

merge(b,e,b2,e2,t)
	정렬된 두 순차열을 하나의 정렬된 순차열로 병합
		특정 조건자로 정렬된 상태라면 merge 시 해당 조건자를 사용한다.
	[b,e), [b2,e2)를 병합하여 [t, t+(e-b)+(e2-b2)) 순차열을 만든다.
	목적지 끝 반복자를 반환한다.

replace(b,e,x,x2)
	x인 원소를 모두 x2로 수정

replace_if(b,e,f,x2)
	사용자가 지정한 조건에 맞는 원소를 모두 수정
	f(*p)가 참인 원소를 모두 x2로 변경

replace_copy(b,e,t,x,x2)
	[b,e) 구간의 x원소를 x2로 수정하여 [t,p)로 복사
	원본은 변경되지 않는다

replace_copy_if(b,e,t,f,x2)
	[b,e) 구간의 f(*p)가 참인 원소를 x2로 수정하여 [t,p)로 복사
	원본은 변경되지 않는다

swap_ranges(b,e,b2)
	[b,e)과 [b2,b2+(e-b))의 모든 원소를 교환
	원소 개수가 같아야한다.

transform(b,e,t,f)
	f(*p)를 호출하여 반환값을 [t,t+(e-b))에 저장(덮어쓰기)
	함수의 반환값을 사용하여 목적지의 원소를 변경, 원본은 변경되지 않는다.
	transform의 반환값 : 목적 순차열의 끝 반복자

transform(b,e,b2,t,f)
	사용자 연산을 두 순차열의 원소에 적용하고 제3의 순차열에 저장
	[b,e), [t,t+(e-b)) 순차열의 반복자를 f(*p, *q)한 반환값을 [t,t+(e-b))에 저장
*/

void _0802_modifying() {
	printBlockName("copy(b,e,t)", false);
	{
		vector<int> v1 = INIT_012;
		vector<int> v2(v1.size()*2);

		copy(v1.begin(), v1.end(), v2.begin());
		printVector(v1); // 0, 1, 2
		printVector(v2); // 0, 1, 2, 0, 0, 0
	}

	printBlockName("copy_backward(b,e,t)");
	{
		vector<int> v1 = INIT_012;
		vector<int> v2(v1.size()*2);

		copy_backward(v1.begin(), v1.end(), v2.end());
		printVector(v1); // 0, 1, 2
		printVector(v2); // 0, 0, 0, 0, 1, 2
	}

	printBlockName("fill(b,e,x) / fill_n(b,n,x)");
	{
		vector<int> v(5);
		printVector(v); // 0, 0, 0, 0, 0

		fill(v.begin(), v.end(), 9);
		printVector(v); // 9, 9, 9, 9, 9

		fill_n(v.begin(), 2, 0);
		printVector(v); // 0, 0, 9, 9, 9
	}

	printBlockName("for_each(b,e,f)");
	{
		vint v = INIT_012;
		// 모든 원소에 +10
		for_each(v.begin(), v.end(), [](int& i) -> void {
			i += 10;
		});
		printVector(v); // 10, 11, 12
	}

	printBlockName("generate(b,e,f)");
	{
		vint v(5);
		int i = 0;
		generate(v.begin(), v.end(), [&i]() -> int {
			return i++;
		});
		printVector(v); // 0, 1, 2, 3, 4
	}

	printBlockName("swap(a,b) / iter_swap(p,q)");
	{
		int a = 0;
		int b = 1;
		swap(a, b);
		printInts(a, b); // 1, 0

		vint v1 = INIT_012;
		vint v2 = INIT_210;
		iter_swap(v1.begin(), v2.begin()); // 맨 앞의 원소를 바꿔준다.
		printVector(v1); // 2, 1, 2
		printVector(v2); // 0, 1, 0
	}

	printBlockName("merge(b,e,b2,e2,t)");
	{
		vint v1 = INIT_012;
		vint v2 = INIT_012; // 정렬되어 있어야한다.
		vint v3(v1.size() + v2.size());

		merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
		printVector(v3); // 0, 0, 1, 1, 2, 2
	}

	printBlockName("replace(b,e,x,x2)");
	{
		vint v = { 0,0,0,1,1,1,2,2,2 };
		replace(v.begin(), v.end(), 1, 9); // 1을 모두 9로 변경
		printVector(v); // 0, 0, 0, 9, 9, 9, 2, 2, 2
	}

	printBlockName("replace_if(b,e,f,x2)");
	{
		vint v = { 0,0,0,1,1,1,2,2,2 };
		// 2를 모두 9로 변경
		replace_if(v.begin(), v.end(), [](int &i) -> bool {
			return i == 2;
		}, 9);
		printVector(v); // 0, 0, 0, 1, 1, 1, 9, 9, 9
	}

	printBlockName("replace_copy(b,e,t,x,x2)");
	{
		vint v1 = { 0,0,0,1,1,1,2,2,2 };
		vint v2(v1.size());
		// 2를 모두 9로 변경하여 복사
		replace_copy(v1.begin(), v1.end(), v2.begin(), 2, 9);
		printVector(v1); // 0, 0, 0, 1, 1, 1, 2, 2, 2 : 원본은 변경되지 않았다.
		printVector(v2); // 0, 0, 0, 1, 1, 1, 9, 9, 9
	}

	printBlockName("replace_copy_if(b,e,t,f,x2)");
	{
		vint v1 = { 0,0,0,1,1,1,2,2,2 };
		vint v2(v1.size());
		// 2보다 작은 수를 모두 9로 변경하여 복사
		replace_copy_if(v1.begin(), v1.end(), v2.begin(), [](int &i) -> bool {
			return i < 2;
		}, 9);
		printVector(v1); // 0, 0, 0, 1, 1, 1, 2, 2, 2
		printVector(v2); // 9, 9, 9, 9, 9, 9, 2, 2, 2
	}

	printBlockName("swap_ranges(b,e,b2)");
	{
		vint v1 = INIT_01234;
		vint v2 = INIT_210;
		swap_ranges(v1.begin(), v1.end()-2, v2.begin()); // end-2로 길이를 맞춰준다.
		printVector(v1); // 2, 1, 0, 3, 4
		printVector(v2); // 0, 1, 2
	}

	printBlockName("transform(b,e,t,f)");
	{
		vint v1 = INIT_012;
		vint v2(v1);
		transform(v1.begin(), v1.end(), v2.begin(), [](int &i) -> int {
			return i + 10;
		});
		printVector(v1); // 0, 1, 2
		printVector(v2); // 10, 11, 12
	}

	printBlockName("transform(b,e,b2,t,f)");
	{
		vint v1 = INIT_012;
		vint v2 = INIT_012;
		vint v3(v1.size());
		transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), [](int &l, int &r) -> int {
			return l + r;
		});
		printVector(v1); // 0, 1, 2
		printVector(v2); // 0, 1, 2
		printVector(v3); // 0, 2, 4
	}
}