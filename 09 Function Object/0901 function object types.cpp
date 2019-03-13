#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include "utils.h"

using namespace std;

/*
함수 객체(function object)
	함수자(functor)라는 애칭으로 더 많이 사용되며
	operator() 연산자를 오버로딩한 클래스 객체

STL 함수 객체의 분류
	일반 함수 객체 : 특정 기능을 수행하는 함수 객체
		산술 연산 함수 객체
			산술 연산 기능을 수행 
				plus, minus, multiplies, devides, modulus, negate
					negate [nɪˈɡeɪt]
						1.…을 무효로 하다 2.…을 부정하다 3.부인하다
		비교 연산 함수 객체 조건자
			비교 조건자
				equal_to(==), not_equal_to(!=), less(<), less_equal(<=), greater(>), greater_equal(>=)
		논리 연산 함수 객체 조건자
			논리 조건자
				logical_and(&&), logical_or(||), logical_not(!)

	함수 어댑터(function adapter) : 함수류(함수 객체, 함수, 함수 포인터, 람다)를 인자로 받아 다른 함수 객체로 변환
		바인더(binder)
			이항 함수 객체를 단항 함수 객체로 변환
			binder1st : 첫 번째 인자를 고정
			binder2nd : 두 번재 인자를 고정
		부정자(negator)
			함수 객체 조건자를 반대로 변환
			not1 : 단항 조건자를 반대의 조건자로 변환
			not2 : 이항 조건자를 반대의 조건자로 변환
		함수 포인터 어댑터
			함수 포인터를 STL이 요구하는 함수 객체로 변환
			일반 함수를 어댑터에 전달할 수 있는 함수 객체로 만들어줌
			ptr_fun
		멤버 함수 포인터 어댑터
			멤버 함수 포인터를 STL이 요구하는 함수 객체로 변환
			인자를 받는 함수는 변환할 수 없다.
			인자를 받지 않고 반환값을 활용하는 것도 아니기 때문에 함수 어댑터의 인자로 전달할 수 있는 구조가 아니어도 된다.
				unary_function, binary_function를 상속 받지 않아도 된다.

			mem_fun_ref : 객체로 멤버 함수를 호출(컨테이너의 원소 타입이 객체)
			mem_fun : 객체의 주소로 멤버 함수를 호출(컨테이너의 원소 타입이 객체 포인터)

STL에서의 조건자
	내부 상태가 변경되지 않는 bool 형식을 반환하는 함수 객체

	객체의 상태값을 변경할 수 없다는 요구조건을 만족해야하기 때문에 
	operator() 연산자 오버로딩 함수는 모두 const 함수이다.

	조건자가 변경되지 않는 다는 전제 하에 조건자를 내부적으로 복사하기 때문에 
	상태값이 변경되면 예기치 못한 동작이 발생한다.

사용자 정의 함수가 어댑터의 인자로 사용될 수 있는 방법
	방법 1. 다음 이름의 타입을 함수 내부에 정의한다.
		단항 함수
			타입 정의(typedef) : argument_type, result_type
		이항 함수
			타입 정의(typedef) : first_argument_type, second_argument_type, result_type

	방법 2. 위 방법이 이미 구현된 unary_function, binary_function을 상속받는다.
*/

// 사용자 정의 이항 함수
template<typename T>
struct Plus {
	T operator()(const int &l, const int &r) const {
		return l + r;
	}
};

// 사용자 정의 이항 함수, 어댑터에 전달 가능
template<typename T>
struct Plus2 {
	// 어댑터에 사용될 수 있게 타입 정의
	typedef T first_argument_type;
	typedef T second_argument_type;
	typedef T result_type;

	T operator()(const int &l, const int &r) const {
		return l + r;
	}
};

// 사용자 정의 이항 함수, unary_function 상속받아 어댑터에 전달 가능
template<typename T>
struct Plus3 : public binary_function<T, T, T> {
	T operator()(const int &l, const int &r) const {
		return l + r;
	}
};

// 사용자 정의 이항 함수
template<typename T>
struct Less : public binary_function<T, T, T> {
	bool operator()(const T &l, const T &r) const {
		return l < r;
	}
};

// 사용자 정의 이항 함수
template<typename T>
struct EqaulTo :public binary_function<T, T, T> {
	bool operator()(const T &l, const T &r) const {
		return l == r;
	}
};

bool greater0(const int &i) {
	return i > 0;
};

//template<typename Arg, typename Result, typename Fn = Result (*)(Arg)>
//unary_function<Arg, Result> Ptr_Fun(Fn fn) {
//	return unary_function<Arg, Result>(fn);
//}

// 단항 함수를 함수 객체로 변환
template<typename Arg, typename Result>
class Ptr_Fun_Class : public unary_function<Arg, Result> {
public:
	Ptr_Fun_Class(Result(*fn) (Arg)) {
		_fn = fn;
	}
	Result operator()(Arg arg) const {
		return _fn(arg);
	}
private:
	Result(*_fn) (Arg);
};
// Ptr_Fun_Class를 생성하여 반환하는 함수
template<typename Arg, typename Result>
Ptr_Fun_Class<Arg, Result> Ptr_Fun(Result(*fn)(Arg)) {
	return Ptr_Fun_Class<Arg, Result>(fn);
}

// 멤버 함수를 함수 객체로 변환 : 객체로 호출
template <typename T, typename FResult>
class Mem_Fun_Ref_Class {
public:
	FResult(T::*mf)();
	Mem_Fun_Ref_Class(FResult(T::*mf)()) {
		this->mf = mf;
	}
	void operator()(T &o) const {
		(o.*mf)();
	}
};

template<typename T, typename FResult>
Mem_Fun_Ref_Class<T, FResult> Mem_Fun_Ref(FResult(T::*mf)()) {
	return Mem_Fun_Ref_Class<T, FResult>(mf);
}

// 멤버 함수를 함수 객체로 변환 : 객체의 포인터로 호출
template<typename T, typename FResult>
class Mem_Fun_Class {
public:
	FResult(T::*mf)();
	Mem_Fun_Class(FResult(T::*mf)()) {
		this->mf = mf;
	}
	void operator()(T *o) {
		(o->*mf)();
	}
};

template<typename T, typename FResult>
Mem_Fun_Class<T, FResult> Mem_Fun(FResult(T::*mf)()) {
	return Mem_Fun_Class<T, FResult>(mf);
}

void _0901_function_object_types() {
	printBlockName("어댑터를 사용하여 이항 함수 객체를 단항 함수 객체로 사용하기");
	{
		printSubBlockName("이항 함수 plus");
		{
			vint v1 = INIT_012;
			vint v2 = INIT_102030;
			vint v3(v1.size());

			transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), plus<int>());
			printVector(v3); // 10, 21, 32
		}

		printSubBlockName("이항 함수 plus를 adopter를 이용해 단항 함수로 사용");
		{
			vint v1 = INIT_012;
			//vint v2 = INIT_102030;
			vint v3(v1.size());

			// 두번재 인자를 100으로 고정하기 때문에 두번째 순차열이 필요없다.
			transform(v1.begin(), v1.end(), v3.begin(), binder1st<plus<int>>(plus<int>(), 100));
			printVector(v3); // 100, 101, 102
		}

		printSubBlockName("사용자 정의 이항 함수를 이항 함수로 사용");
		{
			vint v1 = INIT_012;
			vint v2 = INIT_102030;
			vint v3(v1.size());

			transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), Plus<int>());
			printVector(v3); // 10, 21, 32
		}

		printSubBlockName("사용자 정의 이항 함수를 adopter를 이용하여 단항 함수로 사용");
		{
			vint v1 = INIT_012;
			vint v3(v1.size());

			transform(v1.begin(), v1.end(), v3.begin(), binder1st<Plus3<int>>(Plus3<int>(), 1000));
			printVector(v3); // 1000, 1001, 1002
		}
	}

	printBlockName("산술 연산 함수 객체");
	{
		printSubBlockName("multiplies");
		{
			vint v1 = INIT_102030;
			//vint v2 = INIT_012;
			vint v3(v1.size());

			// 원소의 곱 누적
			partial_sum(v1.begin(), v1.end(), v3.begin(), multiplies<>());
			printVector(v3); // 0, 1, 1
		}

		printSubBlockName("negate");
		{
			vint v1 = INIT_012;
			//vint v2 = INIT_012;
			vint v3(v1.size());

			transform(v1.begin(), v1.end(), v3.begin(), negate<>());
			printVector(v3); // 0, -1, -2
		}

		printSubBlockName("minus");
		{
			vint v1 = INIT_012;
			//vint v2 = INIT_012;
			vint v3(v1.size());

			// 인접 원소와의 차
			adjacent_difference(v1.begin(), v1.end(), v3.begin(), minus<>());
			printVector(v3); // 0, 1, 1
		}
	}

	printBlockName("비교 연산 함수 객체(조건자)");
	{
		vint v1 = INIT_012;
		// 이항 함수 객체를 단일 함수 객체로 만들어 2보다 작은 원소의 개수를 알아냄
		printInts(count_if(v1.begin(), v1.end(), binder2nd<Less<int>>(Less<int>(), 2))); // 2
	}

	printBlockName("논리 연산 함수 객체 조건자");
	{
		vector<bool> v1 = {true, false, true};
		// 이항 함수 객체를 단일 함수 객체로 만들어 원소의 값이 true인 원소의 개수를 알아냄
		printInts(count_if(v1.begin(), v1.end(), binder1st<EqaulTo<bool>>(EqaulTo<bool>(), true))); // 2
	}

	printBlockName("바인더(binder)");
	{
		printInts(binder1st<less<int>>(less<int>(), 1)(0)); // 0 : 1은 0보다 작다 -> false
		printInts(binder2nd<less<int>>(less<int>(), 1)(0)); // 1 : 0은 1보다 작다 -> true
	}
	
	printBlockName("부정자(negator)");
	{
		// not1
		printInts(logical_not<bool>()(true)); // 0 : false
		printInts(not1<logical_not<bool>>(logical_not<bool>())(true)); // 1 : !(true) -> false
		// not2
		printInts(less<int>()(0, 1)); // 1 : 0은 1보다 작다 -> true
		printInts(not2<less<int>>(less<int>())(0, 1)); // 0 : !(0은 1보다 작다) -> false
	}
	
	printBlockName("함수 포인터 어댑터");
	{
		printSubBlockName("ptr_fun");
		{
			printInts(greater0(1)); // 1
//			printInts(not1(greater0)(1)); // 컴파일 에러, greater0를 함수 객체로 변경해야함.
			printInts(not1(ptr_fun(greater0))(1)); // 0
			printInts(not1<pointer_to_unary_function<const int&, bool>>(ptr_fun(greater0))(1)); // 0
		}

		printSubBlockName("ptr_fun 제작");
		{
			printInts(not1(Ptr_Fun_Class<const int&, bool>(greater0))(1)); // 0
			printInts(not1(Ptr_Fun(greater0))(1)); // Ptr_Fun를 따로 정의하여 템플릿 인자 없이도 호출 가능
		}
	}
		
	printBlockName("멤버 함수 포인터 어댑터");
	{
		struct A {
			A(int i) { _i = i; }
			void print() { cout << _i << endl; }
			int _i;
		};

		printSubBlockName("객체로 멤버 함수 포인터 호출");
		{
			void (A::*print)() = &A::print; // 멤버함수 포인터 선언
			A a(0);
			(a.*print)(); // 객체를 통해 멤버 함수 포인터 호출
		}

		printSubBlockName("주소로 멤버 함수 포인터 호출");
		{
			void (A::*print)() = &A::print; // 멤버함수 포인터 선언
			A a(0);
			A *b = &a; // A* 타입 변수 선언
			(b->*print)(); // 객체를 통해 멤버 함수 포인터 호출
		}

		printSubBlockName("mem_fun_ref : 객체의 멤버 함수 호출");
		{
			vector<A> v = {1, 2, 3};
			for_each(v.begin(), v.end(), mem_fun_ref(&A::print)); // 1, 2, 3
		}

		printSubBlockName("mem_fun : 포인터 객체 멤버 함수 호출");
		{
			vector<A*> v;
			for (size_t i = 0; i < 3; i++)
			{
				v.push_back(new A(i));
			}
			for_each(v.begin(), v.end(), mem_fun(&A::print)); // 0, 1, 2
		}

		printSubBlockName("사용자 정의 mem_fun_ref");
		{
			Mem_Fun_Ref_Class<A, void> mfrc(&A::print);
			A a(1);
			mfrc(a); // 1

			//Mem_Fun_Ref_Class<A, void> mfr = Mem_Fun_Ref<A, void>(&A::print); // Mem_Fun_Ref를 정의하여 템플릿 인자 없이 호출 가능
			Mem_Fun_Ref_Class<A, void> mfr = Mem_Fun_Ref(&A::print); // Mem_Fun_Ref를 정의하여 템플릿 인자 없이 호출 가능
			A b(2);
			mfr(b); // 2

			vector<A> v = { 1, 2, 3 };
			for_each(v.begin(), v.end(), Mem_Fun_Ref(&A::print)); // 1, 2, 3
		}

		printSubBlockName("사용자 정의 mem_fun");
		{
			Mem_Fun_Class<A, void> mfrc(&A::print);
			A a(1);
			mfrc(&a); // 1

			//Mem_Fun_Ref_Class<A, void> mfr = Mem_Fun_Ref<A, void>(&A::print); // Mem_Fun_Ref를 정의하여 템플릿 인자 없이 호출 가능
			Mem_Fun_Class<A, void> mfr = Mem_Fun(&A::print); // Mem_Fun_Ref를 정의하여 템플릿 인자 없이 호출 가능
			A b(2);
			mfr(&b); // 2

			vector<A*> v;
			for (size_t i = 0; i < 3; i++)
			{
				v.push_back(new A(i));
			}
			for_each(v.begin(), v.end(), Mem_Fun(&A::print)); // 0, 1, 2

			// delete
			vector<A*>::iterator iter = v.begin();
			while (iter != v.end())
			{
				SAFE_DELETE(*iter);
				++iter;
			}
		}
	}
}