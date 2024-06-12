/*
	06.12 - decltype, 값 카테고리, decleval
*/

/*  decltype  */
//	#include <iostream>
//	
//	struct A
//	{
//		double d;
//	};
//	
//	int main()
//	{
//		int a = 3;
//		decltype(a) b = 2;	//	int
//	
//		int& r_a = a;
//		decltype(r_a) r_b = b;	// int&
//	
//		int&& x = 3;
//		decltype(x) y = 2;	// int&&
//	
//		A* aa;
//		decltype(aa->d) dd = 0.1;	// double
//	
//		/*
//			- decltype
//				- C++ 11 에 추가된 키워드로 타입을 알고자 하는 식의 타입으로 치환
//				- decltype() 에 전달된 식이 "괄호로 둘러쌓이지 않은 식별자 표현식" 일때 해당 식의 타입을 알 수 있음
//	
//				- 식별자 표현식 id-expression
//					- 어떠한 연산을 하지 않고 단순히 객체 하나만 가리키는 식
//					- 변수 이름, 함수 이름, enum 이름, 클래스 멤버 변수(a.b 혹은 a->b)
//					- 자세한건 https://eel.is/c++draft/expr.prim.id#2.2 를 참고
//	
//				- decltype() 에 식별자 표현식이 아닌 식을 전달하면 아래처럼 작동
//					- 식의 값 종류가 xvalue 라면 T&& 로 치환
//					- 식의 값 종류가 lvalue 라면 T& 로 치환
//					- 식의 값 종류가 prvalue 라면 T 로 치환
//						-> 값 종류는 아래에서 계속 다룸
//		*/
//	}

/*  값 종류 value category  */
/*
	- 값 종류 value category
		- 모든 C++ 식에는 "타입" 과 "값 카테고리(== 값 종류)" 가 따라붙음
		- 이전의 우측값, 좌측값 개념의 확장으로 C++ 에는 총 5가지의 값 종류가 존재함
		- 값 종류를 따질때는 크게 2가지로 구분함
			
			1) 정체를 알 수 있는가?
				- 해당 식이 어떤 다른 식과 같은것인지 아닌지 구분할 수 있는가?
				- 변수의 경우 주솟값을 취하여 알 수 있고, 함수는 이름을 보고 알 수 있음

			2) 이동 시킬 수 있는가?
				- 해당 식을 다른 곳으로 안전하게 이동할 수 있는가?
				- 이동 생성자, 이동 대입 연산자 등을 사용할 수 있는지 여부로 구분 가능함

		- 위 내용을 바탕으로 아래처럼 5가지의 종류를 나눔

					이동 가능		이동 불가능
			정체O	xvalue			lvalue		→ 정체를 알 수 있는 모든 식은 glvalue
			정체X	prvalue			쓸모 없음
					   ↓
					이동 가능한 모든 식은 rvalue

		- 이 아래부터 lvalue, prvalue, xvalue 에 대해서 다룸
			-> 매우 가볍게만 짚고 넘어가므로 자세한건 https://en.cppreference.com/w/cpp/language/value_category 를 참고
*/

/*  lvalue  */
//	#include <iostream>
//	
//	class A
//	{
//	public:
//		int f() {}	// static 이 아닌 멤버함수
//		static int g() {}	// static 멤버 함수
//	};
//	
//	void f(int&& a)
//	{
//		a;	// lvalue
//		std::cout << &a << std::endl;
//	}
//	
//	int main()
//	{
//		int i;	// lvalue
//	
//		A a;
//		a.g;	// lvalue
//		//a.f;	// lvalue 아님 (prvalue)
//	
//		f(3);	// 000000D471DDFC64 (매번 다름)
//	
//		auto p1 = &std::cin;	// lvalue 이므로 & 로 주소값을 취할 수 있음
//		std::cout << p1 << std::endl;	// 00007FFC2FBC2E10
//	
//		i = 0;
//		auto p2 = &++i;	// 전위 증감 연산자의 리턴값은 lvalue 이므로 주소값을 취할 수 있음
//		std::cout << p2 << std::endl; // 0000000194B7F514 (매번 다름)
//	
//		/*
//			- lvalue
//				- xvalue 가 아닌 glvalue
//				- 이름을 가진 대부분의 객체들은 lvalue 임. 객체의 주소값을 취할수 있기 때문(&)
//	
//				- 대표적인 lvalue 식들은 아래와 같음
//					- 변수, 함수의 이름, 어떤 타입의 데이터 멤버(ex: std::cin) 등등
//					- 좌측값 레퍼런스를 리턴하는 함수의 호출식 (std::cout << 1;, 임의의 반복자 it 의 ++it 등등)
//					- a = b, a += b, a*= b 같은 복합 대입 연산자 식들
//					- ++a, --a 같은 전위 증감 연산자 식들
//					- a.m, p->m 같이 멤버를 참조하는 식. 이때 m 은 enum 값이거나 static 이 아닌 멤버 함수들은 제외
//					- a[n] 같은 배열 참조식
//					- 문자열 리터럴 "hi"
//	
//				- 헷갈리기 쉬운 경우
//					void f(int&& a)
//					{
//						a;	<- 이런 함수의 경우 a는 lvalue임
//					}
//	
//					- a가 우측값 레퍼런스 이므로 lvalue가 아니라고 생각하는 경우가 잦음
//						-> a 의 타입은 int&& 우측값 레퍼런스가 맞지만, 값 종류로는 lvalue 임
//						-> 타입 과 값 종류는 엄연히 다른 개념임을 정확히 알고 있어야 함
//	
//		*/
//	
//	}


/*  prvalue  */
#include <iostream>

int f() { return 10; }

int main()
{
	f();	// 주소값을 취할 수 없으므로 prvalue

	const int& r = 42;
	int&& rr = 42;
	// int& rrr = 42;	// 불가

	/*
		- prvalue
			- pure rvalue 의 줄임말
			- 정체를 알 수 없는 식 -> 주소값을 취할 수 없는 식
			- prvalue 는 좌측에 올 수 없음
			- 우측값 레퍼런스와 상수 좌측값 레퍼런스를 초기화하는데 사용할 수 있음

			- 대표적인 prvalue 식들은 아래와 같음
				- 문자열 리터럴을 제외한 모든 리터럴(42, true, nullptr 등)
				- 레퍼런스가 아닌 것을 리턴하는 함수의 호출식 (str.substr(1, 2), str1 + str2 등)
				- 후위 증감 연산자식 a++, a--
				- 디폴트 산술, 논리 연산자 식들 (a + b, a && b, a < b 등)
				- 주소값 연산자 식 &a
				- a.m, p->m 과 같이 멤버를 참조할 때. 이때 m 은 enum 값이거나 static 이 아닌 멤버 함수여야함
				- this
				- enum 값
				- 람다식 []() { return 0;};
	*/
}
