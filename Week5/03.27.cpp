/*
	- 03.27 C++ 스타일 캐스팅

*/

// - C++ 스타일 캐스팅

#include <iostream>
#include <vector>
#include <cassert>

// 몇가지 예제들이 같은 구조체 이름을 사용하여 namespace로 나누어놓음

// static_cast 예제 이용
namespace ex1
{
	struct B
	{
		int m = 42;
		const char* hello() const { return "This is B\n"; };
	};

	struct D : B
	{
		const char* hello() const
		{
			return "This is D\n";
		}
	};


	enum class E { ONE = 1, TWO, THREE };
	enum EU { ONE = 1, TWO, THREE };

}

// const_cast 예제 이용
namespace ex2
{
	struct type
	{
		int i;
		type() :i(3) {}
		void f(int v) const
		{
			// this->i = v;	// 컴파일 오류: this 가 const임(const 함수니까)
			const_cast<type*>(this)->i = v;	// 호출한 객체가 const가 아닌이상 오류가 나지 않음
		}
	};
}

// dynamic_cast 예제 이용
namespace ex3
{
	struct V
	{
		virtual void f() {}	// must be polymorphic to use runtime-checked dynamic_cast / 런타임 dynamic_cast를 이용하려면 다형성을 만족해야함
	};

	struct A : virtual V {};

	struct B : virtual V
	{
		B(V* v, A* a)
		{
			// casts during construction 생성자 실행중의 캐스팅
			dynamic_cast<B*>(v);	// well - defined: v of type V*, V base of B, results in B* / 잘 정의됨: V* 타입의 v, B의 부모 V, B*의 결과
			dynamic_cast<B*>(a);	// undefined behavior: a has type A*, A not a base of B / 정의되지 않음: A* 타입의 a, A는 B의 부모가 아님
		}
	};
	
	struct D : A, B
	{
		D() : B(static_cast<A*>(this), this) {}
	};

	struct Base
	{
		virtual ~Base() {}
	};

	struct Derived : Base
	{
		virtual void name() {}
	};
}

// reinterpret_cast 예제 이용
namespace ex4
{
	int f() { return 42; }
}

int main()
{
	// C 스타일 캐스팅
	//	int a = 10;
	//	double b = 3.14;
	//	
	//	double c = b + (double)a;	// 명시적으로 캐스팅 하지 않아도 컴파일러에서 암시적으로 캐스팅 가능
	//	std::cout << c << std::endl;

	/*
		- 암시적(implicit) 캐스팅 / 명시적(explicit) 캐스팅
			- 암시적 캐스팅: 컴파일러가 알아서 상황에 맞게 캐스팅 하는것 ex) int 와 double 간의 덧셈에서 컴파일러가 자동으로 int를 double로 캐스팅ㅈ
			- 명시적 캐스팅: 사용자가 직접 지정하는 캐스팅

		- 기존의 C스타일 명시적 캐스팅 : (타입)변수
	
		- C++의 4가지 캐스팅
			1) static_cast : 일반적으로 생각하는 타입변환
			2) const_cast : 객체의 상수성을 없애는 타입변환 ex) const int -> int
			3) dynamic_cast : 파생 클래스 사이에서의 다운캐스팅
			4) reinterpret_cast : 위험을 감수하고 하는 캐스팅으로 서로 관련이 없는 포인터들 사이의 캐스팅 (reinterpret 의 뜻 : 재해석)
			- 캐스팅 방법 : (원하는 캐스팅)<바꾸려는 타입>(바꾸려는 대상)
	
	*/

	// C++ 스타일 캐스팅
	// 아래의 예시들은 cppreference의 예제들
	// 아직 모르는 개념들을 이용한 예제들이 매우많은데 일단은 그냥 이런게 있다 정도로 넘어가면 좋을듯

	// 1. static_cast
	{
		using namespace ex1;

		// 1-1. static downcast 정적 다운캐스팅
		D d;
		B& br = d;	// 암시적 변환을 이용한 업캐스팅
		std::cout << "1-1) " << br.hello();	// This is B
		D& another_d = static_cast<D&>(br);	// 다운캐스팅
		std::cout << "1-1) " << another_d.hello();	// This is D

		// 1-2. lvalue -> xvalue (lvalue: 위치를 의미(변수, 표현식 등),  참조 가능 / xvalue: 이동 가능한 값, 참조 불가능
		// 자세한 것은 https://en.cppreference.com/w/cpp/language/value_category 를 참조
		std::vector<int> v0{ 1,2,3 };
		std::cout << "1-2) 이동 전, v0.size() = " << v0.size() << '\n';
		std::vector<int> v2 = static_cast<std::vector<int>&&>(v0);
		std::cout << "1-2) 이동 후, v0.size() = " << v0.size() << '\n';

		// 1-3. initializing conversion 초기화 변환
		int n = static_cast<int>(3.14);
		std::cout << "1-3) n = " << n << '\n';	// n = 3
		std::vector<int> v = static_cast<std::vector<int>>(10);
		std::cout << "1-3) v.size = " << v.size() << '\n';	//  v.size = 10

		// 1-4. discarded-value expression 값이 버려지는 표현식
		static_cast<void>(v2.size());	// void로 static_cast를 시도하면 값을 버려버림

		// 1-5. inverse of implicit conversion 역 암시적 변환(명시적 변환 말고 암시적으로 변환된 값을 원래대로 되돌리는 것을 의미)
		void* nv = &n;
		int* ni = static_cast<int*>(nv);
		std::cout << "1-5) *ni = " << *ni << '\n';	// *ni = 3
		// void* 로 변환되어 내부 값을 알수 없던것을 int로 역 변환시켜 다시 값을 볼 수 있음

		// 1-6. array-to-pointer followed by upcast 배열을 포인터로 변환하고 상위 클래스로 업캐스팅
		D a[10];
		B* dp = static_cast<B*>(a);

		// 1-7. scoped enum to int 범위 내의 enum을 int로 변환
		E e = E::TWO;
		int two = static_cast<int>(e);
		std::cout << "1-7) " << two << '\n';	// 2

		// 1-8. int -> enum -> 다른 enum
		E e2 = static_cast<E>(two);	// int -> enum
		EU eu = static_cast<EU>(e2);	// enum -> 다른 enum

		// 1-9. pointer to member upcast 멤버 포인터의 업캐스팅
		int D::* pm = &D::m;
		std::cout << "1-9) " << br.*static_cast<int B::*>(pm) << '\n';	// 42

		// 10. void* to any type
		void* voidp = &e;
		std::vector<int>* p = static_cast<std::vector<int>*>(voidp);
	}

	// 2. const_cast
	{
		using namespace ex2;

		// 예제들에 MSVC에서는 컴파일러가 자동으로 const 캐스팅을 해주어 그냥 가능하게 하는 것들이 있는거같은데 clang을 이용하면 아마 안그럴듯함

		int i = 3;
		const int& rci = i;
		const_cast<int&>(rci) = 4;	// 가능
		std::cout << "i = " << i << '\n';	// 4

		const type t;	// t가 const라면 안됨(근데 MSVC는 이상하게 됨... gcc도 됨 왜지...)
		t.f(4);
		std::cout << "type::i = " << t.i << '\n';	// type::i = 4

		const int j = 3;
		int* pj = const_cast<int*>(&j);
		*pj = 4;	// 이것도 안되야 맞는데 이상하게 됨

		void (type:: * pmf)(int) const = &type::f;
		// const_cast<void(type::*)(int)>(pmf);	// 컴파일 오류: const_cast는 함수 포인터를 대상으로 작동하지 않음

	}

	// 3. dynamic_cast
	{
		using namespace ex3;
		D d;	// this most derived object
		A& a = d;	// upcast, dynamic_cast may be used, but unnecessary / 업케스팅, dynamic_cast가 사용될 수 있지만, 필수는 아님

		D& new_d = dynamic_cast<D&>(a);	// 다운캐스팅
		B& new_b = dynamic_cast<B&>(a);	// 업캐스팅

		Base* b1 = new Base;

		// 아래는 C++17 에서 추가된 구문. if-else 안에서 새로운 변수의 선언 및 초기화가 가능함 https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0305r1.html
		if (Derived* d = dynamic_cast<Derived*>(b1); d != nullptr)	
		{
			std::cout << "downcast from b1 to d successful\n";
			d->name();	// 호출해도 안전함
		}

		Base* b2 = new Derived;
		if (Derived* d = dynamic_cast<Derived*>(b2); d != nullptr)
		{
			std::cout << "downcast from b2 to d successful\n";
			d->name();	// 호출해도 안전함
		}

		// 최종 실행 결과 downcast from b2 to d successful만 출력
		// 이를 통해 첫번째 Base에서 Derived로의 캐스팅이 실패하였음을 알 수 있음
		//
		// the runtime check fails. If the dynamic_cast is used on pointers, the null pointer value of type target-type is returned. 
		// If it was used on references, the exception std::bad_cast is thrown.
		// 런타임에서 다운캐스팅이 안된다는것을 확인 후 nullptr을 리턴해준것을 알 수 있음
		// 만약 위처럼 포인터가 아닌 레퍼런스로 캐스팅 할 경우 예외(std::bad_cast)를 발생시킴(아래 참고)

		try
		{
			Base base;
			Derived& d = dynamic_cast<Derived&>(base);
		}
		catch (const std::exception& e)
		{
			std::cout << "e.what(): " << e.what() << '\n';	// e.what(): Bad dynamic_cast!
		}

		delete b1;
		delete b2;
	}

	// 4. reinterpret_cast
	{
		using namespace ex4;

		int i = 7;

		// 4-1. pointer to integer and back / 포인터 -> int -> 다시 포인터
		// std::uintptr_t == unsigned __int64 == unsigned long long
		std::uintptr_t v1 = reinterpret_cast<std::uintptr_t>(&i);	// static_cast는 에러 발생
		std::cout << "4-1. The value of &i is " << std::showbase << std::hex << v1 << '\n';	// The value of &i is 0x4170eff114 <- 당연히 매번 달라짐
		int* p1 = reinterpret_cast<int*>(v1);
		assert(p1 == &i);	// assert: () 안의 내용이 틀리면 프로그램을 중단시킴(abort())

		// 4-2. pointer to function to another and back / 포인터 -> 함수 -> 다시 포인터
		void(*fp1)() = reinterpret_cast<void(*)()>(f);
		fp1();	// undefined behavior / 정의되지 않음
		int(*fp2)() = reinterpret_cast<int(*)()>(fp1);
		std::cout << std::dec << "4-2. " << fp2() << '\n';	// 42

		// 4-3. type aliasing through pointer / 포인터를 통한 타입 재지정(aliasing을 뭐라고 번역할지 잘 모르겠음)
		char* p2 = reinterpret_cast<char*>(&i);
		std::cout << "4-3. " << (p2[0] == '\x7' ? "This system is little-endian\n" : "This system is big-endian\n");	// This system is little-endian
		// i의 주소를 문자열로 반환하여 7이 맨 앞에 있다면 리틀 엔디안, 맨 뒤라면 빅 엔디안임

		// 4-4. type aliasing through reference / 참조를 이용한 타입 변환
		reinterpret_cast<unsigned int&>(i) = 42;
		std::cout << "4-4. " << i << '\n';	// 42

		const int& const_iref = i;
		// int& iref = reinterpret_cast<int&>(const_iref);	// 컴파일 오류: reinterpret_cast로 const를 없앨 수 없음
		int& iref = const_cast<int&>(const_iref);	// const_cast를 이용하면 가능함
	}
}