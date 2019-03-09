#include <iostream>
#include <numeric>
#include "utils.h"

using namespace std;

/*
수치 알고리즘(numeric algorithm)
	수치관련 원소를 다루는 알고리즘
	순차열의 모드 원소를 누적하려면 for_each()나 transform()알고리즘을 사요할 수 있지만
	누적값을 기억하기 위해 함수자를 사용해야 하므로 복잡해지므로 수치 알고리즘을 사용하면 
	간결하게 처리할 수 있다.


x2=accumulate(b,e,x), x2=accumulate(b,e,x)
	x2는 x를 초깃값으로 시작한 구간 [b,e) 순차열 원소의 합

	초깃값
		순차열의 첫 원소가 더해질 첫 번째 값
		(순차열 총 합에 추가적으로 더해지는 값)

	accumulate [əkjúːmjulèit]
		1.축적하다 2.누적하다 3.모으다 4.늘다

x2=inner_product(b,e,b2,x)
	x2는 x를 초깃값으로 시작한 구간 [b,e)와 [b2,b2+(e-b))의
	내적(두 순차열의 곱의 합)이다.

x2=inner_product(b,e,b2,x,f,f2)
	x2는 x를 초깃값으로 시작한 구간 [b,e)와 [b2,b2+(e-b))의 모든 원소끼리
	f2 연산 후 f1 연산으로 총 연산한 결과

p=adjacent_difference(b,e,t), p=adjacent_difference(b,e,t,f)
	[b,e)의 끝 반복자 p와 p-1의 값을 빼서 [t,p)에 저장한다.
	첫 원소일 경우 p-1이 없기 때문에 p를 저장한다.
	인접 원소와 사용자 정의 연산을 수행하려면 f를 사용한다.

p=partial_sum(b,e,t), p=partial_sum(b,e,t,f)
	[b,e)의 현재 원소까지의 합을 순차열 [t,p)에 저장한다.
	첫 원소는 합할 원소가 없으므로 그대로 저장된다.

	accumulate와의 차이는 초깃값뿐인듯 하다.
*/

void _0807_numeric() {

	printBlockName("x2=accumulate(b,e,x), x2=accumulate(b,e,x,f)");
	{
		vint v = INIT_012;
		int total = accumulate(v.begin(), v.end(), 1);
		cout << total << endl; // 4

		total = accumulate(v.begin(), v.end(), 1, [](int &l/*누적된값*/, int &r/*원소*/) -> int{
			return l + r + 10;
		});
		cout << total << endl; // 34

		total = accumulate(v.begin(), v.end(), 1, plus<>());
		cout << total << endl; // 4

		total = accumulate(v.begin(), v.end(), 1, multiplies<>());
		cout << total << endl; // 0
	}

	printBlockName("x2=inner_product(b,e,b2,x)");
	{
		vint v1 = INIT_012;
		vint v2 = INIT_012;
		int t = inner_product(v1.begin(), v1.end(), v2.begin(), 0);
		cout << t << endl; // 5 : 0 + 0*0 + 1*1 + 2*2
	}

	printBlockName("x2=inner_product(b,e,b2,x,f,f2)");
	{
		vint v1 = INIT_012;
		vint v2 = INIT_012;

		// 원소 끼리의 연살 결과를 총 연산
		auto f1 = [](int &l, const int &r) -> int {
			return l + r;
		};
		// 원소 끼리 연산
		auto f2 = [](int &l, const int &r) -> int {
			return l * r;
		};

		int t = inner_product(v1.begin(), v1.end(), v2.begin(), 0, f1, f2);
		cout << t << endl; // 5 : 0 + 0*0 + 1*1 + 2*2
	}

	printBlockName("p=adjacent_difference(b,e,t), p=adjacent_difference(b,e,t,f)");
	{
		vint v1 = INIT_012;
		vint v2 = {9, 9, 9};
		adjacent_difference(v1.begin(), v1.end(), v2.begin());
		printVector(v2); // 0, 1, 1 : 0, 1-0, 2-1
		
		adjacent_difference(v1.begin(), v1.end(), v2.begin(), [](int &l/*p*/, int &r/*p-1*/) {
			return l - r + 10;
		});
		printVector(v2); // 0, 11, 11 : 0, 1-0+10, 2-1+10
	}

	printBlockName("p=partial_sum(b,e,t), p=partial_sum(b,e,t,f)");
	{
		vint v1 = INIT_01234;
		vint v2(5, 9);
		partial_sum(v1.begin(), v1.end(), v2.begin());
		printVector(v2); // 0, 1, 3, 6, 10 : 0, 0+1, 1+2, 3+3, 6+4
	}
}