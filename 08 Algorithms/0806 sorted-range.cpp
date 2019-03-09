#include <iostream>
#include <algorithm>
#include "utils.h"

using namespace std;

/*
정렬된 범위 알고리즘
	sorted range algorithm
	정렬된 순차열에서만 동작하는 알고리즘
	일력 순차열이 반드시 정렬돼 있어야 한다.
	원소가 같음을 비교할 때 연관 컨테이너처럼 두 원소에 대해 == 연산을 사용하지 않고 !(a<b)&&!(b<a) 연산을 사용
	기본 정렬 기준은 less( < )

binary_search(b,e,x), binary_search(b,e,x,f)
	구간에 x와 같은 원소가 있는가?
	f는 조건자

includes(b,e,b2,e2), includes(b,e,b2,e2,f)
	[b2,e2) 구간의 모든 원소가 [b,e)에도 있는가?
	f는 조건자

p=lower_bound(b,e,x), p=lower_bound(b,e,x,f)
	p는 [b,e)에서 x와 같은 첫 원소의 반복자

p=upper_bound(b,e,x), p=upper_bound(b,e,x,f)
	p는 [b,e)에서 x보다 큰 첫 원소의 반복자

pair(p1,p2)=equal_range(b,e,x), pair(p1,p2)=equal_range(b,e,x,f)
	[p1,p2)는 [b,e)에서 x와 같은 원소의 구간이다.
	[lower_bound(), upper_bound)와 같다.

p=merge(b,e,b2,e2,t), p=merge(b,e,b2,e2,t,f)
	[b,e), [b2,e2)을 합병해 정렬하여 [t,p)에 저장한다.

inplace_merge(b,m,e), inplace_merge(b,m,e,f)
	정렬된 하나의 순차열 [b,m)과 [m,e) 순차열을 [b,e) 순차열로 합병한다.
	
	inplace
		1. 제자리에 (있는); …을 위한 준비가 되어 있는
		2. 적소에

p=set_union(b,e,b2,e2,t), p=set_union(b,e,b2,e2,t,f)
	[b,e)와 [b2,e2)를 정렬된 합집합으로 [t,p)에 저장한다.
	?

	union
		[수학] 합집합(join, sum); 기호 ∪

p=set_intersection(b,e,b2,e2,t), p=set_intersection(b,e,b2,e2,t,f)
	[b,e)와 [b2,e2)를 정렬된 교집합으로 [t,p)에 저장한다.

	intersection
		[수학] 교선, 교점.

p=set_difference(b,e,b2,e2,t), p=set_difference(b,e,b2,e2,t,f)
	[b,e)와 [b2,e2)의 순차열을 정렬된 차집합으로 [t,p)에 저장한다.

p=set_symmetric_difference(b,e,b2,e2,t),p=set_symmetric_difference(b,e,b2,e2,t,f)
	[b,e)와 [b2,e2)의 순차열을 정렬된 대칭 차집합으로 [t,p)에 저장한다.

	symmetric 
		대칭
*/

void _0806_sorted_range() {
	printBlockName("binary_search(b,e,x), binary_search(b,e,x,f)");
	{
		printSubBlockName("기본");
		{
			vint v = INIT_01234;
			cout << binary_search(v.begin(), v.end(), 0) << endl; // 1

			// 기본 조건자 less<> 구현해 봄(왼쪽이 작으면 true)
			cout << binary_search(v.begin(), v.end(), 0, [](const int &i/*중간값*/, const int &x/*찾는값*/) {
				cout << i << ", " << x << endl;
				// 이진탐색 시 왼쪽, 오른쪽으로 이동할 로직을 적는다.
				// true: 오른쪽, false: 왼쪽
				return i < x; // 찾는 값이 중간값보다 크면 오른쪽 영역에서 찾고 작으면 왼쪽 영역에서 찾는다.
				/*
				2, 0
				1, 0
				0, 0 // 0 < 0 -> false : 마지막 자리에서 false가 나왔으므로 한번더 비교한다. : !(a<b)&&!(b<a)
				0, 0 // 한 번더 비교 시 i와 x를 바꿔서 인자로 전달한다.(메모리 주소 찍어보니 바꿔서 옴)
				*/
			}) << endl; // 1
		}
		
		printSubBlockName("두 수의 차이가 3이하이면 같은 원소");
		{
			auto f = [](const int &l/*중간값*/, const int &r/*찾는값*/) {
//				return 3 > l - r; // "invalid comparator" 에러남, 왜인지는 모르겠음.
				return 3 < l - r;
			};

			vint v = {40, 46, 12, 80, 10, 47, 30, 55, 90, 53};
			// 두 수의 차가 3보다 크면 왼쪽에 놓는다.
			sort(v.begin(), v.end(), f);
			printVector(v); // 90, 80, 55, 53, 46, 47, 40, 30, 12, 10

			// 32와 차이가 3이하인 수를 찾아라
			cout << binary_search(v.begin(), v.end(), 32, f) << endl; // 1 : 32를 찾았다.
			cout << binary_search(v.begin(), v.end(), 88, f) << endl; // 1 : 90을 찾았다.
			cout << binary_search(v.begin(), v.end(), 95, f) << endl; // 0 : 92~98 사이값이 없다.
			printVector(v); // 90, 80, 55, 53, 46, 47, 40, 30, 12, 10
		}
	}

	printBlockName("includes(b,e,b2,e2), includes(b,e,b2,e2,f)");
	{
		vint v1 = {0, 1, 2, 3, 4};
		vint v2 = {3, 4};
		cout << includes(v1.begin(), v1.end(), v2.begin(), v2.end()) << endl;
	}

	printBlockName("p=lower_bound(b,e,x), p=lower_bound(b,e,x,f)");
	{
		vint v = { 0, 0, 1, 2, 1 ,2, 1, 3 };
		// 정렬돼있어야한다. 안돼있으면 이상한 결과가 나온다.
		sort(v.begin(), v.end()); // 0, 0, 1, 1, 1, 2, 2, 3
		printVector(v);

		vinti iter1 = lower_bound(v.begin(), v.end(), 1);
		vinti iter2 = upper_bound(v.begin(), v.end(), 1);

		cout << *(iter1) << endl; // 1
		cout << *(iter2) << endl; // 2

		while (iter1 != iter2)
		{
			cout << *(iter1++) << endl; // 1, 1, 1
		}
	}
	
	printBlockName("pair(p1,p2)=equal_range(b,e,x), pair(p1,p2)=equal_range(b,e,x,f)");
	{
		vint v = { 0, 0, 1, 2, 1 ,2, 1, 3 };
		// 정렬돼있어야한다. 안돼있으면 이상한 결과가 나온다.
		sort(v.begin(), v.end()); // 0, 0, 1, 1, 1, 2, 2, 3
		printVector(v);

		pair<vinti, vinti> p = equal_range(v.begin(), v.end(), 1);
		//vinti iter2 = upper_bound(v.begin(), v.end(), 1);

		cout << *(p.first) << endl; // 1
		cout << *(p.second) << endl; // 2

		while (p.first != p.second)
		{
			cout << *(p.first++) << endl; // 1, 1, 1
		}
	}
	
	printBlockName("p=merge(b,e,b2,e2,t), p=merge(b,e,b2,e2,t,f)");
	{
		vint v1 = INIT_012;
		vint v2 = INIT_210;
		vint v3(v1.size() + v2.size());

		// 정렬 안돼 있으면 "sequence not ordered" 에러.
		sort(v2.begin(), v2.end());

		merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
		printVector(v3); // 0, 0, 1, 1, 2, 2 : 병합하며 정렬을 한다.
	}
	
	printBlockName("inplace_merge(b,m,e), inplace_merge(b,m,e,f)");
	{
		vint v = { 1, 2, 3, 10, 11, 12, 5, 6, 7, 20, 21, 22 };
		inplace_merge(v.begin(), v.begin() + 6, v.end());
		printVector(v); // 1, 2, 3, 5, 6, 7, 10, 11, 12, 20, 21, 22
	}
	
	printBlockName("p=set_union(b,e,b2,e2,t), p=set_union(b,e,b2,e2,t,f)");
	{
		vint v1 = INIT_012;
		vint v2 = INIT_01234;
		vint v3(v1.size() + v2.size());

		set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
		printVector(v3); // 0, 1, 2, 3, 4, 0, 0, 0 : 0, 1, 2는 합집합이므로 하나만 들어간다.
	}
	
	printBlockName("p=set_intersection(b,e,b2,e2,t), p=set_intersection(b,e,b2,e2,t,f)");
	{
		vint v1 = INIT_012;
		vint v2 = INIT_01234;
		vint v3(v1.size() + v2.size());

		set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
		printVector(v3); // 0, 1, 2, 0, 0, 0, 0, 0 : 3, 4는 교집합이므로 짤렸다.
	}
	
	printBlockName("p=set_difference(b,e,b2,e2,t), p=set_difference(b,e,b2,e2,t,f)");
	{
		vint v1 = INIT_012;
		vint v2 = INIT_01234;
		vint v3(v1.size() + v2.size());

		set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
		printVector(v3); // 0, 0, 0, 0, 0, 0, 0, 0 : v1에서 v2를 빼니 다 빠졌다.

		set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), v3.begin());
		printVector(v3); // 3, 4, 0, 0, 0, 0, 0, 0 : v2에서 v1를 빼니 다 3, 4가 남았다.
	}
	
	printBlockName("p=set_symmetric_difference(b,e,b2,e2,t),p=set_symmetric_difference(b,e,b2,e2,t,f)");
	{
		vint v1 = { 0, 1, 2, 5, 6 };
		vint v2 = { 0, 1, 2, 3, 4 };
		vint v3(v1.size() + v2.size());

		set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
		printVector(v3); // 3, 4, 5, 6, 0, 0, 0, 0, 0, 0 : 상대 집합에 포함되지 않는 원소만 남았다.
	}
}