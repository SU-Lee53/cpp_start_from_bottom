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
//	#include <iostream>
//	
//	int f() { return 10; }
//	
//	int main()
//	{
//		f();	// 주소값을 취할 수 없으므로 prvalue
//	
//		const int& r = 42;
//		int&& rr = 42;
//		// int& rrr = 42;	// 불가
//	
//		/*
//			- prvalue
//				- pure rvalue 의 줄임말
//				- 정체를 알 수 없는 식 -> 주소값을 취할 수 없는 식
//				- prvalue 는 좌측에 올 수 없음
//				- 우측값 레퍼런스와 상수 좌측값 레퍼런스를 초기화하는데 사용할 수 있음
//	
//				- 대표적인 prvalue 식들은 아래와 같음
//					- 문자열 리터럴을 제외한 모든 리터럴(42, true, nullptr 등)
//					- 레퍼런스가 아닌 것을 리턴하는 함수의 호출식 (str.substr(1, 2), str1 + str2 등)
//					- 후위 증감 연산자식 a++, a--
//					- 디폴트 산술, 논리 연산자 식들 (a + b, a && b, a < b 등)
//					- 주소값 연산자 식 &a
//					- a.m, p->m 과 같이 멤버를 참조할 때. 이때 m 은 enum 값이거나 static 이 아닌 멤버 함수여야함
//					- this
//					- enum 값
//					- 람다식 []() { return 0;};
//		*/
//	}

/*  xvalue  */
//	#include <iostream>
//	#include <utility>
//	
//	int main()
//	{
//		int x = 3;
//		auto xv = std::move(x);
//	
//		/*
//			- xvalue
//				- 정체가 있으면서 이동 가능한 식
//				- eXpiring value 의 줄임말
//	
//				- 예시 : std::move()
//					- std::move() 의 원형은 아래와 같이 생김
//	
//						_EXPORT_STD template <class _Ty>
//						_NODISCARD _MSVC_INTRINSIC constexpr remove_reference_t<_Ty>&& move(_Ty&& _Arg) noexcept {
//						    return static_cast<remove_reference_t<_Ty>&&>(_Arg);
//						}
//	
//					- std::move 의 리턴값은 반드시 우측값 레퍼런스
//						-> std::move 를 호출한 식은 lvalue 처럼 좌측값 레퍼런스를 초기화 할 수 있음
//						-> 또한 prvalue 처럼 우측값 레퍼런스에 붙이거나 이동 생성자에 전달할 수도 있음
//	
//	
//				- cppreference 의 설명 https://en.cppreference.com/w/cpp/language/value_category
//					an xvalue (an “eXpiring” value) is a glvalue that denotes an object whose resources can be reused;
//					xvalue 는 자원이 재사용될 수 있는 객채를 나타내는 glvalue
//	
//		*/
//	
//	}

/*  decltype 의 사용  */
//	#include <iostream>
//	#include <typeinfo>
//	
//	template <typename T, typename U>
//	void add1(T t, U u, decltype(t + u)* result)
//	{
//		*result = t + u;
//	}
//	
//	template <typename T, typename U>
//	//	decltype(t + u) add2(T t, U u) -> decltype 안의 t, u 의 정의가 나중에 나오므로 불가능
//	auto add2(T t, U u) -> decltype(t + u)	// C++ 14 에서 추가된 문법
//	{
//		return t + u;
//	}
//	
//	template <typename T, typename U>
//	decltype(auto) add3(T t, U u)			// C++ 14 에서 추가된 문법으로 위 add2를 이렇게 써도 됨
//	{
//		return t + u;
//	}
//	
//	int main()
//	{
//		int a = 4;
//		auto b = a;			// auto -> int
//		decltype(a) c = a;	// decltype(a) -> int
//	
//	
//		const int i = 4;
//		auto j = i;			// auto -> int
//		decltype(i) k = i;	// decltype(i) -> const int
//	
//		int arr[10];
//		auto arr2 = arr;	// auto -> int * __ptr64
//		decltype(arr) arr3;	// decltype(arr) -> int[10]
//	
//		int n = 10;
//		double d = 10.0;
//		decltype(n + d) res = 0;	// int + double 의 타입은 double
//		decltype(n + d)* res_p = &res;
//	
//		add1(n, d, res_p);
//		std::cout << typeid(res).name() << " : " << res << std::endl;	// double : 20
//		std::cout << typeid(add2(n, d)).name() << " : " << add2(n, d) << std::endl;	// double : 20
//		std::cout << typeid(add3(n, d)).name() << " : " << add3(n, d) << std::endl;	// double : 20
//	
//	
//		/*
//			- decltype 의 사용
//				- auto 로 하면 안됨?
//					- 안됨. auto 는 정확한 타입을 표현하지 못함. 예를들어
//						
//							const int i = 0;
//							auto j = i;
//	
//						-> 위 경우 auto 는 const int 가 아닌 int 로 변환됨
//					
//							int arr[10];
//							auto arr2 = arr;
//	
//						-> 위 경우는 int [10] 이 아닌 int* 로 변환됨
//						-> 그 밖에 auto 가 정확하지 않은 경우는 https://en.cppreference.com/w/cpp/language/template_argument_deduction#Other_contexts 의 auto type deduction 을 참고 
//	
//				- decltype 은 "타입 그대로"를 정확하게 전달 가능함
//				- 템플릿 함수에서 템플릿 인자에 대해서도 사용 가능함
//	
//						template <typename T, typename U>
//						void add1(T t, U u, decltype(t + u)* result)
//	
//				- 함수 정의시 리턴 타입을 decltype 로 지정하고 싶다면 C++ 14 에 새로 생긴 함수 정의법을 사용해야함
//	
//						template <typename T, typename U>
//						decltype(t + u) add2(T t, U u) -> X 컴파일 오류
//	
//						template <typename T, typename U>
//						auto add2(T t, U u) -> decltype(t + u)	-> O 사용 가능
//		
//		*/
//	
//	}

/*  std::declval  */
//	#include <iostream>
//	#include <utility>
//	#include <typeinfo>
//	
//	template <typename T>
//	decltype(T().f()) call_f_and_return(T& t)
//	{
//		return t.f();
//	}
//	
//	template <typename T>
//	decltype(std::declval<T>().f()) declval_f_and_return(T& t)
//	{
//		return t.f();
//	}
//	
//	// C++ 14 부터 추가된 auto 리턴
//	template <typename T>
//	auto auto_f_and_return(T& t)
//	{
//		return t.f();
//	}
//	
//	struct A
//	{
//		int f() { return 0; }
//	};
//	
//	struct B
//	{
//		B(int x) {}
//		int f() { return 0; }
//	};
//	
//	int main()
//	{
//		decltype(A().f()) ret;	// int
//		// decltype(B().f()) ret2;	// 컴파일 불가
//		decltype(B(1).f()) ret2;	// 가능은 함
//	
//		A a;
//		B b(1);
//	
//		call_f_and_return(a);
//		// call_f_and_return(b);	// 컴파일 불가
//		declval_f_and_return(b);	// 가능
//	
//		auto_f_and_return(a);
//		auto_f_and_return(b);
//	
//		// declval 함수는 런타임에서 사용할 수 없음
//		// B b2 = std::declval<B>);	// E0415 : "<unknown-type>" 에서 "B"(으)로 변환하기 위한 적절한 생성자가 없습니다.
//	
//		/*
//			- std::declval<T>
//				- 위 코드에서
//					- decltype(A().f()) ret;	
//						- decltype 은 컴파일시에 타입으로 변환되고 런타임에는 실행되지 않음
//						- 그러나 문법상 틀린 식은 전달할 수 없음
//	
//					- decltype(B().f()) ret2; 는 컴파일이 안됨
//						- B() 생성자가 없으므로 불가능함
//						- 굳이 B() 생성자가 필요 없는데 이걸 위해 만드는것은 비효율적
//							- 실제 객체를 생성하지도 않고 타입 참조만 하기 때문
//	
//					- decltype(B(1).f()) ret2;
//						- 가능하긴 함
//						- 그러나 템플릿 코드 등에 들어갔을 때 문제를 일으킴
//							-> 아래같은 함수가 있을 때
//								template <typename T>
//								decltype(T().f()) call_f_and_return(T& t)
//								-> B() 생성자가 없으므로 문제가 컴파일이 불가능해짐
//								-> 이를 해결하는 것이 std::declval
//	
//				- std::declval : <utility> 에 정의된 함수로 직접적인 생성자 호출 없이 객체의 멤버에 접근할 수 있도록 함
//	
//						template <typename T>
//						decltype(std::declval<T>().f()) declval_f_and_return(T& t)
//	
//					-> 이전의 코드를 위처럼 std::declval 을 이용하면 B() 생성자가 없는 B 도 문제 없이 사용할 수 있음
//	
//				- std::declval 은 타입 연산에서만 사용하고 실제 런타임에는 사용할 수 없음
//	
//						_EXPORT_STD template <class _Ty>
//						add_rvalue_reference_t<_Ty> declval() noexcept {
//							static_assert(_Always_false<_Ty>, "Calling declval is ill-formed, see N4950 [declval]/2.");
//						}
//					
//					- 위는 declval 함수의 원형으로 타입연산이 아닌 런타임에 실행시 static_assert 로 프로그램을 멈춰버림
//		
//	
//				- C++ 14 에서 리턴타입으로 auto 로 지정하여 컴파일러가 리턴타입을 유추하는 기능이 생김
//					- 위처럼 declval 을 이용한 리턴 타입 정의 같은 일들은 사용할 일이 줄어듬
//					- 그러나 declval 은 <type_traits> 와 함께 TMP 에 많이 사용됨
//		
//		
//		*/
//	}