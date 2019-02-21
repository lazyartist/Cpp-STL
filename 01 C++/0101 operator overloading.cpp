#include <iostream>
#include <string>

using namespace std;

/*
�⺻ Ÿ�Ե��� ������ �Ǵ� ������ �����Ϸ� ���ο� ������ ���ǵǾ��ֱ� �����̴�.
����� ���� Ÿ�Կ� �����ڸ� ����Ϸ��� �����ؼ� ����ϸ� �ȴ�.
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
			// c�� �̹� �޸� ������ ��ü�� ����Ų��.
			// ��쿡 ���� ����� �۵��ϴ� ��ó�� ���� ���� ������ ������ �޸𸮿� �ٸ� ������ �Ҵ�Ǹ� �̻� �۵��� �ϰԵȴ�.
			A& c = (a + b);
			c.name = "c"; // ��Ÿ�� ���ܹ߻�, "��ġ�� ����ϴ� ���� �׼��� ������ �߻��߽��ϴ�.."
			c.i = 9;
		}

		cout << a.i << endl;

	}
}

