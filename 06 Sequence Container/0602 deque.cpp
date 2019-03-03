#include <iostream>
#include <deque>
#include "utils.h"

using namespace std;

/*
deque
	시퀸스 컨테이너이며 배열 기반 컨테이너.
	vector와 유사하며 임의 접근 반복자를 지원.

	vector와 deque의 차이점은 메모리 부족 시 vector는 현재보다 더 큰 크기의
	메모리 블럭을 할당받고 복사한 뒤 기존 메모리를 제거하는데
	deque은 기존 메모리를 그대로 두고 새로운 메모리를 할당 받아 연결한다.
	이로인해 원소를 앞과 뒤에 추가할 수 있고 배열 기반 컨테이너의 특징을
	가지면서 vector처럼 메모리를 제거하거나 원소를 복사하는 연산을 수행하지 않는다.	

	새로운 메모리를 할당해서 기존 메모리의 앞과 뒤에 붙일 수 있으므로
	vector와 다르게 앞에서도 원소 추가/삭제가 가능하다.
	또한 원소의 삽입/삭제 시 지정 위치를 기준으로 원소가 적은 쪽으로
	밀어내거나 당기기 때문에 뒤쪽으로만 밀어내는 vector보다 더 효율적이다.

	deque도 배열 기반 컨테이너이기 때문에 at(), [] 연산자를 제공하고
	+, -, +=, -=, [] 연산을 모두 수행할 수 있다.

	deque의 인터페이스는 vector와 거의 동일하기 때문에 따로 설명할게 없다.
	(push_front(), pop_front() 정도만 추가됨)
*/

void _0602_deque() {

	cout << "===== 원소를 앞에 추가/제거 =====" << endl;
	{
		deque<int> d(3, 0);
		d.push_front(1);

		printContainer<deque<int>, deque<int>::iterator>(d); // 1, 0, 0, 0
	}
}