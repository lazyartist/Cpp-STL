#include <iostream>
#include <algorithm>
#include <ctime>
#include "utils.h"

using namespace std;

/*
mutaing algorithm
	순차열의 원소를 서로 교환하거나 이동하여 순차열 원소의 순서를 변경하는 알고리즘

	mutate[mjúːteit]
		변화시키다 돌연변이시키다

bool=next_permutaion(b,e)
	permutation [pə̀ːrmjətéiʃən]
		치환 순열 변경

	순차열을 사전순의 다음 순열로 변경시킨다.
	마지막 순열에서 false를 반환한다.

	순열(permutation)
		순서있는 나열
		순서가 부여된 임의의 집합을 다른 순서로 뒤섞는 연산

		A, B, C, D, E 순열
			5개의 숫자를 뽑아서 나열하는 경우의 수
				5 * 4 * 3 * 2 * 1 = 5!(팩토리얼)
			3개의 숫자를 봅아서 나열하는 경우의 수 
				5 * 4 * 3 = 5!/2! = 5P3(5개에서 3개를 뽑아 나열한다. P = permutation)

bool=next_permutaion(b,e,f)
	순차열을 사전순의 다음 순열로 변경시킨다.
	비교 연산에 f를 사용한다.

bool=prev_permutation(b,e)
bool=prev_permutation(b,e,f)
	next_permutaion과 다른 점은 이전 순열을 만든다는 것뿐이다.

p=partition(b,e,f)
	f(*p)가 참인 원소는 [b,p) 순차열에, 거짓인 원소는 [p,e) 순차열로 분류한다.
	알고리즘
		퀵정렬과 비슷하게 양 끝의 포인터가 원소를 검색하여 f값이 참이면 왼쪽으로 거짓이면 오른쪽으로 서로 교환하여
		두 포인터가 같은 위치를 가리키면 반환하고 종료한다.

stable_partition(b,e,f)
	p=partition(b,e,f)과 같고 원소의 상대적인 순서를 유지한다.
	순서를 유지하기에 성능은 조금 떨어진다.
	알고리즘
		포인터 하나는 처음부터 하나는 중간부터 끝으로 이동하며 f의 값이 참이면 왼쪽으로 거짓이면 오른쪽으로 교환한다
		첫 포인터가 가운데로 이동하면 종료한다.

random_shuffle(b,e)
	순차열을 랜덤으로 뒤섞는다.
	srand()을 사용하지 않으면 매번 일정한 결과가 나온다.
	다음을 사용하여 매번 다른 값이 나오게 한다.
		#include <ctime>
		srand((unsigned)time(NULL));

random_shuffle(b,e,f)
	f를 랜덤기로 사용하여 뒤섞는다.
	f는 (현재 인덱스 + 1) 값을 받아서 현재 인덱스의 값과 교체할 인덱스 번호를 반환한다.

reverse(b,e)
	순차열을 뒤집는다.

p=reverse_copy(b,e,t)
	[b,e)를 뒤집어 [t,p)에 복사한다.
	원본은 변경되지 않는다.

rotate(b,m,e)
	순차열을 왼쪽으로 회전시킨다.
	첫 원소와 마지막 원소가 연결된 것처럼 모든 원소가 왼쪽으로 (m-b)만큼 이동한다.
		(m이 첫 원소의 위치가 되게 왼쪽으로 이동시킨다.)

p=rotate_copy(b,m,e,t)
	순차열을 회전하여 목적 순차열 [t,p)에 복사한다.
	원본은 변경되지 않는다.
*/

void _0804_mutating() {
	printBlockName("bool=next_permutaion(b,e)");
	{
		vint v = INIT_012;
		printVector(v); // 0, 1, 2
		while (next_permutation(v.begin(), v.end()))
		{
			printVector(v);
			// 0, 2, 1
			// 1, 0, 2
			// 1, 2, 0
			// 2, 0, 1
			// 2, 1, 0
		}
		printVector(v); // 0, 1, 2
	}

	printBlockName("bool=next_permutaion(b,e,f)");
	{
		// 비교연산으로 어떤 원리로 순열 조합이 만들어지는지 모르겠다.
		vint v = INIT_012;
		printVector(v); // 0, 1, 2
		while (next_permutation(v.begin(), v.end(), [](int &l, int &r) -> bool {
			return l < r;
		}))
		{
			printVector(v);
			// 0, 2, 1
			// 1, 0, 2
			// 1, 2, 0
			// 2, 0, 1
			// 2, 1, 0
		}
		printVector(v); // 0, 1, 2
	}

	printBlockName("p=partition(b,e,f)");
	{
		vint v = INIT_01234;
		vinti iter = partition(v.begin(), v.end(), [](int &i) -> bool {
			return i > 2;
		});
		cout << *iter << endl; // 2
		// 반환값 iter를 기준으로 참은 왼쪽으로 거짓은 오른쪽으로 이동했다.
		printVector(v); // 4, 3, 2, 1, 0
	}

	printBlockName("stable_partition(b,e,f)");
	{
		vint v = INIT_01234;
		vinti iter = stable_partition(v.begin(), v.end(), [](int &i) -> bool {
			return i > 2;
		});
		cout << *iter << endl; // 2
		// 반환값 iter를 기준으로 참은 왼쪽으로 거짓은 오른쪽으로 순서를 유지하며 이동했다.
		printVector(v); // 3, 4, 0, 1, 2
	}

	printBlockName("random_shuffle(b,e)");
	{
		vint v = INIT_01234;
		random_shuffle(v.begin(), v.end());
		printVector(v); // 4, 1, 3, 2, 0 : 몇번을 실행해도 결과가 똑같다.

		srand((unsigned)time(NULL)); // 시작값(seed)를 바꿔준다.
		random_shuffle(v.begin(), v.end());
		printVector(v); // 2, 4, 0, 1, 3 : 실행 마다 결과가 달라진다.
	}

	printBlockName("random_shuffle(b,e,f)");
	{
		vint v = INIT_01234;
		srand((unsigned)time(NULL)); // 시작값(seed)를 바꿔준다. rand()의 값이 달라진다.
		random_shuffle(v.begin(), v.end(), [](int i) -> int {
			printInts(i); // 2, 3, 4, 5 : 현재 자릿수를 가지고 앞의 어떤 자릿수와 교체할지 계산하도록 이런 값이 들어온다.
			return (rand()%i); // 반환값이 원소 인덱스 범위를 벗어나면 안된다.
//			return 0; // 현재 원소를 0번 인덱스로 계속 보낸다. 결과는 무조건 4, 0, 1, 2, 3
		});
		printVector(v); // 4, 1, 3, 2, 0 : 몇번을 실행해도 결과가 똑같다.
	}

	printBlockName("reverse(b,e)");
	{
		vint v = INIT_012;
		reverse(v.begin(), v.end());
		printVector(v); // 2, 1, 0
	}

	printBlockName("p=reverse_copy(b,e,t)");
	{
		vint v1 = INIT_012;
		vint v2(v1.size());
		reverse_copy(v1.begin(), v1.end(), v2.begin());
		printVector(v1); // 0, 1, 2 : 원본은 그대로이다.
		printVector(v2); // 2, 1, 0 : 뒤집어 복사한다.
	}

	printBlockName("rotate(b,m,e)");
	{
		vint v = INIT_01234;
		rotate(v.begin(), v.begin() + 2, v.end()); // 두 번째 인자가 순차열 맨 앞에 오도록 왼쪽으로 회전
		printVector(v);  // 2, 3, 4, 0, 1
	}

	printBlockName("p=rotate_copy(b,m,e,t)");
	{
		vint v1 = INIT_01234;
		vint v2(v1.size());
		rotate_copy(v1.begin(), v1.begin() + 2, v1.end(), v2.begin()); // 두 번째 인자가 순차열 맨 앞에 오도록 왼쪽으로 회전
		printVector(v1); // 0, 1, 2, 3, 4 : 원본 변경 안됨
		printVector(v2); // 2, 3, 4, 0, 1 : 변경된 순차열이 복사됨
	}
}