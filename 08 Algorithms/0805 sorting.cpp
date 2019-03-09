#include <iostream>
#include <algorithm>
#include "utils.h"

using namespace std;

/*
https://zeddios.tistory.com/56

heap
	부모 노드가 자식 노드보다 우선순위가 높은 구조
	이에 따라 루트 노드는 가장 우선순위가 높다.

	힙 구조 만들기
		"부모-자식x2" 구조를 삼각구조라 했을 때 최하단 레벨의 개별 삼각 레벨을 힙구조로 만든다.
		그 윗 레벨의 개별 삼각구조를 힙구조로 만들고 자식의 자식 삼각구조까지 포함하여 힙구조를 만든다.
		이것을 최상위 삼각구조까지 반복하면 힙구조가 만들어진다.

	힙 구조는 일반적으로 배열 기반으로 구현하는데 이 배열을 봤을 때 일직선상으로 정렬되어있지 않다.

	푸시, 팝 후에 다운힙을 진행하기 때문에 로그 시간으로 푸시, 팝을 할 수 있다.

heap sort
	힙 구조를 일직선상으로 정렬시킨다.

	힙 정렬하기
		1. 최상위 노드와 가장 끝 노드를 교환한다. 끝으로 간 노드는 정렬 대상에서 제외한다.
		2. 최상위 노드 자리에 있는 노드를 대상으로 다운힙을 실행한다.
		3. 다운힙이 완료되면 차우선순위 노드가 가장 앞에 오게 된다.
		이 차우선순위 노드를 대상으로 1~3 과정을 반복한다.
		최종적으로 최대힙일 경우 오름차순 배열로 정렬 되고 최소힙은 내림차순으로 정렬된다.

	다운힙
		마지막 노드를 루트 노드에 넣고 순서조건을 만족하도록 내려주는 것.
		
시간 복잡도
	힙 만들기 : n
	다운힙 : n(데이터) * log₂n(한 노드에 대해) * 2(비교 연산) = 2nlog₂n
	힙 정렬 시간복잡도 : O(n + 2nlog₂n) -> 상수 시간 제거 -> O(nlog₂n)

	최악의 경우에도 O(nlog₂n)

*/

/*
sorting
	정렬 알고리즘은 변경(mutating) 알고리즘의 특수한 형태
	특정 정렬 기준으로 원소의 순서를 변경하며 정렬

p=partition(b,e,f)
	f(*p)가 참인 원소는 [b,p) 순차열에, 거짓인 원소는 [p,e) 순차열로 분류한다.
	변경 알고리즘 참고.

stable_partition(b,e,f)
	p=partition(b,e,f)과 같고 원소의 상대적인 순서를 유지한다.
	순서를 유지하기에 성능은 조금 떨어진다.
	변경 알고리즘 참고.

make_heap(b,e)
	순차열을 힙 구조로 변경한다.
	임의 접근 반복자를 지원하는 컨테이너만 make_heap을 사용할 수 있다.(vector, deque)

	힙은 우선순위 큐 구현에 사용되는데 priority_queue 어댑터가 이런 자료 구조를 잘 제공하므로
	직접 사용할 일은 거의 없다.

make_heap(b,e,f)
	f 비교 조건자로 힙을 생성한다.

push_heap(b,e)
	보통 push_back() 멤버 함수와 같이 사용되며 
	push_back()으로 추가된 원소로 인해 깨진 힙 구조를 다시 힙 구조가 되게 만든다.
	순차열 끝에 새로운 원소가 추가됐다고 가정하고 힙 구조로 재배치한다.

push_heap(b,e,f)
	push_heap(b,e)와 같고 f는 조건자로 사용된다.

pop_heap(b,e)
	루트 노드를 가장 끝 노드와 교환하고 끝으로 간 루트 노드를 제외한 영역을 힙으로 만든다.
	끝으로 간 원소는 pop_back()등으로 제거한다.

pop_heap(b,e,f)
	pop_heap(b,e)과 같고 f는 조건자로 사용된다.

sort_heap(b,e)
	힙 구조를 이용한 정렬이기 때문에 힙 구간을 정렬하는데 일반적인 정렬함수보다 훨씬 빠르다.
	정렬 후에도 is_heap()해보면 false가 나온다. 
		가장 앞에 원소가 최대<->최소로 바뀌긴 하지만 힙 구조아닌가?

sort_heap(b,e,f)
	sort_heap(b,e)와 같고 f는 조건자

nth_element(b,m,e)
	상위 m-b개의 원소를 선별하여 [b,m) 순차열에 놓이게 한다.

nth_elememt(b,m,e,f)
	nth_element(b,m,e)과 동일하고 f는 조건자

sort(b,e)
	퀵 정렬을 기반으로 정렬한다.
	평균 O(N log₂N)을 보장하고 최악의 경우 O(N²)

sort(b,e,f)
	퀵 정렬을 기반으로 정렬한다. f는 조건자

stable_sort(b,e)
	머지 정렬을 기반으로 정렬한다.
	정렬 시 값이 같은 "원소의 상대적인 순서"를 유지한다.
	메모리가 넉넉하면 평균 O(N log₂N)을 보장하고 그렇지 않으면 O(N log₂N log₂N), 최악의 경우?(책에 없다)

stable_sort(b,e,f)
	stable_sort(b,e)와 같고 f는 조건자

partial_sort(b,m,e)
	힙 정렬을 기반으로 정렬
	언제나 O(N log₂N)을 보장하지만 힙 정렬 단계마다 다운힙을 추가적으로 하기 때문에 
	일반적으로 퀵정렬보다 성능이 떨어진다.
	
	m-b개 만큼의 상위 원소를 정렬하여 [b,m)에 놓는다.

partial_sort(b,m,e,f)
	partial_sort(b,m,e)와 동일하고 f는 조건자

partial_sort_copy(b,e,b2,e2)
	[b,e) 원소중 [b2,e2) 원소만큼만 정렬하여 [b2,e2)로 복사한다.

partial_sort_copy(b,e,b2,e2,f)
	partial_sort_copy(b,e,b2,e2)와 동일하고 f는 조건자

*/

void _0805_sorting() {
	printBlockName("make_heap(b,e)");
	{
		vint v = INIT_01234;
		make_heap(v.begin(), v.end()); // 기본이 최대힙, less<>
		printVector(v); // 4, 3, 2, 0, 1

		make_heap(v.begin(), v.end(), greater<>());
		printVector(v); // 0, 1, 2, 3, 4
	}

	printBlockName("push_heap(b,e)");
	{
		vint v = INIT_01234;
		make_heap(v.begin(), v.end());
		printVector(v); // 4, 3, 2, 0, 1

		v.push_back(5);
		printVector(v); // 4, 3, 2, 0, 1, 5

		push_heap(v.begin(), v.end());
		printVector(v); // 5, 3, 4, 0, 1, 2
	}

	printBlockName("sort_heap(b,e)");
	{
		auto a = less<>()(1, 2);
		vint v = INIT_01234;
		make_heap(v.begin(), v.end()); // less : 자식이 부모보다 낮은 우선순위
		printVector(v); // 4, 3, 2, 0, 1
		cout << is_heap(v.begin(), v.end()) << endl; // 1 : 힙 구조

		sort_heap(v.begin(), v.end()); // less : 오름차순 정렬
		printVector(v); // 0, 1, 2, 3, 4
		cout << is_heap(v.begin(), v.end()) << endl; // 0 : 힙 구조 아님
	}

	printBlockName("nth_element(b,m,e)");
	{
		vint v;
		for (size_t i = 0; i < 100; i++)
		{
			v.push_back(rand() % 100);
		}
		printVector(v);
		// 41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61, 91, 95, 42, 27, 36, 91, 4, 2, 53, 92, 82, 21, 16, 18, 95, 47, 26, 71, 38, 69, 12, 67, 99, 35, 94, 3, 11, 22, 33, 73, 64, 41, 11, 53, 68, 47, 44, 62, 57, 37, 59, 23, 41, 29, 78, 16, 35, 90, 42, 88, 6, 40, 42, 64, 48, 46, 5, 90, 29, 70, 50, 6, 1, 93, 48, 29, 23, 84, 54, 56, 40, 66, 76, 31, 8, 44, 39, 26, 23, 37, 38, 18, 82, 29, 41

		nth_element(v.begin(), v.begin() + 4, v.end());
		printVector(v);
		// 0, 1, 2, 3, 4, 5, 5, 6, 6, 8, 11, 11, 12, 16, 16, 18, 18, 31, 34, 29, 27, 22, 33, 29, 29, 26, 21, 23, 27, 24, 23, 26, 23, 29, 35, 35, 40, 36, 47, 42, 41, 41, 47, 45, 48, 40, 41, 42, 37, 44, 48, 41, 39, 38, 42, 37, 38, 46, 44, 50, 99, 67, 90, 69, 88, 71, 95, 82, 64, 92, 53, 91, 90, 95, 70, 91, 61, 64, 93, 62, 58, 78, 84, 54, 56, 69, 66, 81, 67, 68, 62, 57, 53, 59, 64, 73, 94, 82, 78, 76
		// 원소 개수가 20개 이하면 전체가 정렬된 것처럼 보이기 때문에 20개 이상돼야 앞부분만 정렬된걸 확인할 수 있다.
	}
	
	printBlockName("sort(b,e)");
	{
		vint v = INIT_43210;
		sort(v.begin(), v.end());
		printVector(v); // 0, 1, 2, 3, 4
	}
	
	printBlockName("stable_sort(b,e,f)");
	{
		vint v = INIT_43210;
		stable_sort(v.begin(), v.end());
		printVector(v); // 0, 1, 2, 3, 4
	}
	
	printBlockName("partial_sort(b,m,e)");
	{
		vint v = INIT_43210;
		sort(v.begin(), v.end());
		printVector(v); // 0, 1, 2, 3, 4
	}
	
	printBlockName("partial_sort_copy(b,e,b2,e2)");
	{
		vint v1 = INIT_43210;
		vint v2 = INIT_43210;
		partial_sort_copy(v1.begin(), v1.begin()+2, v2.begin(), v2.end());
		printVector(v1);
		printVector(v2);
	}
}