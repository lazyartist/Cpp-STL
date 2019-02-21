#include <iostream>
#include <string>

using namespace std;

/*
기본 타입들이 연산이 되는 이유는 컴파일러 내부에 연산이 정의되어있기 때문이다.
사용자 정의 타입에 연산자를 사용하려면 정의해서 사용하면 된다.
*/

void operator_overloading() {
	cout << "operator_overloading" << endl;

	{
		class A {
		public:
			A(string name, int v) {
				this->name = name;
				this->i = v;
				cout << "cst" << name << ", " << v << endl;
			}
			~A() {
				//name = nullptr;
				i = 0;
				cout << "dst" << name << ", " << i << endl;
			}

			string name;
			int i;

			A& operator+(const A& r) {
				A tmp = { "tmp", 9 };
				return tmp;
			}
		};

		class F {
		public:
			int operator()() {
				return 0;
			}
		};

		auto ii = F()();
		//auto iii = ii();

		A a = { "a", 1 };
		A b = { "b", 1 };

		{
			// c는 이미 메모리 해제된 객체를 가리킨다.
			// 경우에 따라 제대로 작동하는 것처럼 보일 수도 있지만 해제된 메모리에 다른 변수가 할당되면 이상 작동을 하게된다.
			A& c = (a + b);
			c.name = "c"; // 런타임 예외발생, "위치를 기록하는 동안 액세스 위반이 발생했습니다.."
			c.i = 9;
		}

		cout << a.i << endl;

	}
}

