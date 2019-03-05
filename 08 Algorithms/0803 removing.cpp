#include <iostream>
#include <algorithm>
#include "utils.h"

using namespace std;

/*
removing algorithm
	원소를 수정하지 않는 알고리즘의 특수한 형태
	원소를 실제로 제거하지 않고 논리적으로 제거(다음 원소로 덮어쓰기)하기 때문에
	순차열의 size를 실제로는(? capacity를 변경하지 않고 보이는 size는 변경한다?)변경하지 않는다.
	실제 size를 변경하려면 컨테이너의 erase() 멤버 함수를 이용

p=remove(b,e,x)
	x가 남지 않도록 덮어쓰기로 이동(뒤에서 당겨온다)
	실제 size는 변경되지 않으며 remove와 erase를 함께 사용하여 size를 줄일 수 있다.

p=remove_if(b,e,f)
	f(*p)가 참인 원소가 남지 않도록 덮어쓰기로 이동

p=remove_copy(b,e,t,x)
	x가 아닌 원소만 [t,p)에 복사한다.
	원본을 변경하지 않음

p=remove_copy_if(b,e,t,f)
	f(*p)가 참이 아닌 원소만 [t,p)에 복사

p=unique(b,e)
	인접한 중복 원소가 남지 않게 덮어쓰기로 이동
	모든 원소를 유일하게 만드려면 정렬 후 실행한다.
	논리적으로만 제거한다.
	따라서 실제로 제거하려면 정렬 후 unique 실행한 뒤 erase를 실행한다.

p=unique(b,e,f)
	f(*p,*(p+1))가 참인 원소 제거

p=unique_copy(b,e,t)
	인접한 중복 원소가 아닌 원소를 [t,p)에 복사

p=unique_copy(b,e,t,f)
	f(*p,*(p+1))가 참인 인접한 중복 원소가 아닌 원소를 [t,p)에 복사

*/

void _0803_removing() {
	printBlockName("p=remove(b,e,x)");
	{
		vint v = INIT_012;
		vinti iter = remove(v.begin(), v.end(), 1);
		printVector(v); // 0, 2, 2 : 1이 제거되고 끝의 2가 아직 보인다.
		printInts(v.size(), v.capacity()); // 3, 3 : size도 줄지 않았다.

		// erase로 size까지 줄인다.
		v.erase(iter, v.end());
		printVector(v); // 0, 2
		printInts(v.size(), v.capacity()); // 1, 3
	}

	printBlockName("p=remove_if(b,e,f)");
	{
		vint v = { 0, 1, 1 };
		vinti iter = remove_if(v.begin(), v.end(), [](int &i) -> bool {
			return i == 0;
		});
		printVector(v); // 1, 1, 1 : 0이 제거되고 끝의 1이 아직 보인다.
		printInts(v.size(), v.capacity()); // 3, 3

		// erase로 size까지 줄인다.
		v.erase(iter, v.end());
		printVector(v); // 1, 1
		printInts(v.size(), v.capacity()); // 2, 3
	}

	printBlockName("p=remove_copy(b,e,t,x)");
	{
		vint v1 = INIT_012;
		vint v2(v1.size());

		remove_copy(v1.begin(), v1.end(), v2.begin(), 1);
		printVector(v1); // 0, 1, 2
		printVector(v2); // 0, 2, 0 : 1을 제외하고 복사됐다.
	}

	printBlockName("p=remove_copy_if(b,e,t,f)");
	{
		vint v1 = { 1, 10, 2, 20, 3, 30 };
		vint v2(v1.size());

		// 10이하의 숫자만 복사
		remove_copy_if(v1.begin(), v1.end(), v2.begin(), [](int &i) -> bool {
			return i > 10; // true이면 복사하지 않기 때문에 10이상의 숫자를 제외한다.
		});
		printVector(v1); // 1, 10, 2, 20, 3, 30
		printVector(v2); // 1, 10, 2, 3, 0, 0 : 10이하의 숫자만 복사됨
	}

	printBlockName("p=unique(b,e)");
	{
		vint v = { 0, 1, 1, 2, 3, 1, 9 };

		unique(v.begin(), v.end());
		printVector(v); // 0, 1, 2, 3, 1, 9, 9 : 인접한 원소만 제거

		sort(v.begin(), v.end());
		printVector(v); // 0, 1, 1, 2, 3, 9, 9 : 정렬

		vinti iter = unique(v.begin(), v.end());
		printVector(v); // 0, 1, 2, 3, 9, 9, 9 : 정렬 뒤 모든 인접 원소 제거(끝의 9는 논리적으로 제거되서 남아있음)

		v.erase(iter, v.end());
		printVector(v); // 0, 1, 2, 3, 9 : 모든 중복 원소 물리적 제거
	}

	printBlockName("p=unique(b,e,f)");
	{
		vint v = { 0, 1, 1, 2, 3, 1, 9 };

		unique(v.begin(), v.end(), [](int &l, int &r) -> bool {
			return l == r;
		});
		printVector(v); // 0, 1, 2, 3, 1, 9, 9 : 인접한 원소만 제거
	}

	printBlockName("p=unique_copy(b,e,t)");
	{
		vint v1 = { 0, 1, 1, 2, 3, 1, 9 };
		vint v2(v1.size());

		unique_copy(v1.begin(), v1.end(), v2.begin());
		printVector(v1);
		printVector(v2); // 0, 1, 2, 3, 1, 9, 0 : 중복 원소를 제거하고 복사
	}

	printBlockName("p=unique_copy(b,e,t,f)");
	{
		vint v1 = { 0, 1, 1, 2, 3, 1, 9 };
		vint v2(v1.size());

		sort(v1.begin(), v1.end());
		printVector(v1); // 0, 1, 1, 1, 2, 3, 9 : 정렬

		unique_copy(v1.begin(), v1.end(), v2.begin(), [](int &l, int &r) -> bool {
			return l == r;
		});
		printVector(v2); // 0, 1, 2, 3, 9, 0, 0 : 중복 원소를 제거하고 복사
	}
}