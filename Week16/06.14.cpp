/*
	06.14 - <type_traits>, SFINAE, enable_if
*/

/*  템플릿 메타 함수, type_traits - std::is_void  */
//	#include <iostream>
//	#include <type_traits>
//	
//	// 간단한 is_void
//	template <typename T>
//	struct is_void
//	{
//		static constexpr bool value = false;
//	};
//	
//	template <>
//	struct is_void<void>
//	{
//		static constexpr bool value = true;
//	};
//	
//	template <typename T>
//	void tell_type()
//	{
//		if (std::is_void<T>::value)
//		{
//			std::cout << "T 는 void" << '\n';
//		}
//		else
//		{
//			std::cout << "T 는 void 가 아님" << '\n';
//		}
//	}
//	
//	int main()
//	{
//		tell_type<int>();	// T 는 void 가 아님
//		tell_type<void>();	// T 는 void
//		
//		/*
//			- 템플릿 메타 함수
//				- 함수는 아니지만 함수처럼 동작하는 템플릿 클래스들
//				- "메타" 함수 : 타입에 대한 연산을 수행하는 함수를 메타 함수라고 함
//				- 템플릿 메타 함수는 실제로는 함수가 아님
//					- () 를 통한 호출이 아닌 <> 를 통하여 템플릿 인자를 전달함
//					- 실제로는 클래스(일단 MSVC 는 구조체) 로 구현됨
//	
//			- type_traits
//				- 타입의 속성에 대한 템플릿 메타 함수들을 제공하는 라이브러리
//	
//				- std::is_void<T>
//					- 템플릿 인자로 들어간 타입이 void 인지 알려주는 템플릿 메타 함수
//					- 위에서 간단하게 is_void 를 구현해보았지만 실제 구현은 아래와 같음
//	
//							_EXPORT_STD template <class _Ty>
//							_INLINE_VAR constexpr bool is_void_v = is_same_v<remove_cv_t<_Ty>, void>;
//							
//							_EXPORT_STD template <class _Ty>
//							struct is_void : bool_constant<is_void_v<_Ty>> {};
//	
//						- is_void_v 에서 is_same_v<remove_cv_t<_Ty>, void>;
//							- _v 가 붙은 것들은 대부분 ::value 필요없이 바로 참/거짓을 리턴
//							- is_same_v 는 두 템플릿 인자가 같은지 알려주는 템플릿 메타 함수
//							- is_void 는 is_void_v 의 값을 가지고 bool_constant<is_void<_Ty>> 를 상속받아 ::value 를 가짐
//								- bool_constant 는 integral_constant 의 bool 버전으로 뒤에서 다시 다룸
// 
//						- remove_cv 는 const 와 volatile 키워드를 없애줌
//	
//		*/
//	
//	}

/*  type_traits - std::is_integral, static_assert  */
//	#include <iostream>
//	#include <type_traits>
//	
//	class A {};
//	
//	template <typename T>
//	void only_integer(const T& t)
//	{
//		static_assert(std::is_integral<T>::value); // C2338 : static_assert failed: 'std::is_integral<T>::value'
//		std::cout << "T is an integer" << "\n";
//	}
//	
//	int main()
//	{
//		int n = 3;
//		only_integer(n);
//	
//		A a;
//		only_integer(a);	// 여기를 주석처리 하면 컴파일 오류 없어짐
//	
//		/*
//			- static_assert
//				- C++ 11 에 추가된 키워드
//				- 인자로 전달된 식이 참인지 아닌지 컴파일 타임에 확인
//					- 즉, bool 타입의 constexpr 만 확인 가능함
//					- true 인 경우 컴파일러가 해당 식을 무시함
//					- false 인 경우 컴파일 오류를 일으킴
//	
//			- std::is_integral<T>
//				- 인자로 들어온 타입이 정수타입인지 확인함
//				- 실제 구현은 아래와 같음
//	
//						_EXPORT_STD template <class _Ty>
//						_INLINE_VAR constexpr bool is_integral_v = _Is_any_of_v<remove_cv_t<_Ty>, bool, char, signed char, unsigned char,
//							wchar_t,
//						#ifdef __cpp_char8_t
//							char8_t,
//						#endif // defined(__cpp_char8_t)
//							char16_t, char32_t, short, unsigned short, int, unsigned int, long, unsigned long, long long, unsigned long long>;
//						
//						_EXPORT_STD template <class _Ty>
//						struct is_integral : bool_constant<is_integral_v<_Ty>> {};
//	
//					- 쉽게말해 인자로 들어온 _Ty 와 모든 정수타입 간의 any_of 연산(OR) 을 한다고 보면 됨
//					- __cpp_char8_t 는 해당 기능이 사용 가능한지 확인하는 매크로로 C++ 20 부터 사용가능함 https://en.cppreference.com/w/cpp/feature_test
//						- char8_t 타입은 C++ 20 에서 추가되었으므로 #ifdef 전처리기를 이용해 확인함
//				
//				- 위 코드의 only_integer() 에서는 std::is_integer<T> 와 static_assert 를 이용해서 정수 타입을 강제하고 있음
//	
//		*/
//	}

/*  type_traits - std::is_class, std::integral_constant, 데이터 멤버를 가리키는 포인터  */
//	#include <iostream>
//	#include <type_traits>
//	
//	class A
//	{
//	public:
//		int n;
//	
//		A(int n) : n(n) {}
//	};
//	
//	struct B
//	{
//		int m;
//	
//		B(int m) : m(m) {}
//	};
//	
//	int main()
//	{
//		// 데이터 멤버를 가리키는 포인터
//		int A::* p_n = &A::n;
//	
//		A a(3);
//		std::cout << "a.n : " << a.n << std::endl;	// a.n : 3
//		std::cout << "a.*p_n : " << a.*p_n << std::endl;	// a.*p_n : 3
//	
//		int B::* p_m = &B::m;
//	
//		B b(3);
//		std::cout << "b.m : " << b.m << std::endl;
//		std::cout << "b.p_m : " << b.*p_m << std::endl;
//	
//	
//		/*
//			- 모두의 코드에 나온 std::is_class 의 구현(이전 버전의 cppreference 에서 가져오신듯함)
//	
//					namespace detail {
//					template <class T>
//					char test(int T::*);
//					struct two {
//					  char c[2];
//					};
//					template <class T>
//					two test(...);
//					}  // namespace detail
//					
//					template <class T>
//					struct is_class : std::integral_constant<bool, sizeof(detail::test<T>(0)) == 1 && !std::is_union<T>::value> {};
//	
//				- std::is_class 를 이해하려면 std::integral_constant 와 멤버 포인터에 대해서 먼저 알아봐야함
//	
//			- std::integral_constant<T, T v>
//				- v 를 static 인자로 가지는 클래스
//					-> 어떠한 값을 static 객체로 가지고 있는 클래스를 만들어 주는 템플릿
//					-> 예를 들어 std::integral_constant<bool, false> 라면 integral_constant::value 가 false 인 클래스
//	
//			- 데이터 멤버를 가리키는 포인터
//				- 특정 클래스의 멤버를 가리키는 포인터
//					-> 예를 들어 int T::*p; 는 T 의 int 멤버를 가리키는 포인터 p 를 정의한 식임
//	
//				- 실제로 존재하는 객체의 멤버를 가리키는 것이 아니고 일반 멤버에 접근하듯이 역참조로 해당 멤버에 접근함
//					- 즉 위 코드에서 a.n 과 a.*p_n 은 같은 문장임
//	
//				- 이 문법은 오직 클래스에만 사용 가능함
//					- struct 도 가능. C++ 은 사실상 class 와 struct 가 기본적인 접근 지정자 외에는 차이가 없다고 함
//	
//			- std::is_class<T>
//				- 인자로 전달된 타입이 클래스 인지 아닌지 확인하는 메타 함수
//	
//				- 위의 모두의 코드에 있는 구현에 대한 해설
//					
//					- 시작은 맨 아래부터 보아야 함
//	
//							template <class T>
//							struct is_class : std::integral_constant<bool, sizeof(detail::test<T>(0)) == 1 && !std::is_union<T>::value> {};
//	
//						- size_of(detail::test<T>(0)) == 1 과 !std::is_union<T>::value 가 모두 true 여야 is_class 가 true 가 됨을 알 수 있음
//	
//					- size_of(detail::test<T>(0)) == 1 ?
//	
//							namespace detail {
//							template <class T>
//							char test(int T::*);
//							struct two {
//							  char c[2];
//							};
//							template <class T>
//							two test(...);
//							}  // namespace detail
//	
//						- 2가지 test 함수가 있음
//	
//							1) 일단 char test(int T::*) 는 T 가 클래스가 아니면 애초에 불가능한 문장
//								- T 가 클래스라면 int 타입의 멤버가 없어도 유효한 문장임. 그저 가리킬 멤버가 없을 뿐임
//									-> 무언가를 가리킬게 있고 없고가 중요한게 아니고 그저 클래스인지 아닌지만 판별하는 문장임
//							
//							2) two test(...) 는 T 가 클래스가 아니어도 항상 인스턴스화가 가능함
//	
//						- 이제 T 가 클래스라고 가정하고 detail::test<T>(0) 을 컴파일하면
//							- 1번 char test(int T::*) 가 인자가 명시되어 있으므로 오버로딩 우선순위가 더 높음
//							- 컴파일된 test 가 char를 리턴하므로 sizeof(detail::test<T>(0)) 은 sizeof(char) 가 되어 == 1 이 true
//	
//						- 반면 T 가 클래스가 아니라고 가정하고 컴파일하면
//							- 1번 char test(int T::*) 는 불가능한 문법이므로 오버로딩 후보군에서 제외됨
//								-> 컴파일 오류는 발생하지 않고 넘어감. 나중에 SFINAE 에서 이를 활용하기도 함
//							- 그러므로 2번 two test(...) 가 오버로딩 
//								- 리턴된 two 는 char [2] 이므로 sizeof(two) 는 2 가 되어 false
//							
//						- sizeof(detail::test<T>(0)) == 1 은 T 가 union 일때도 성립하므로 !std::is_union<T>::value> 를 이용해 union 이 아님을 검증해야함
//							- C++ 에는 union 과 class 를 구분할 방법이 없음... 이는 컴파일러에 직접 의존해서 해결함
//		
//				- 참고로 현재 cppreference 에는 다른 구현으로 나와있음
//	
//						namespace detail
//						{
//							template<class T>
//							std::integral_constant<bool, !std::is_union<T>::value> test(int T::*);
//						
//							template<class>
//							std::false_type test(...);
//						}
//						
//						template<class T>
//						struct is_class : decltype(detail::test<T>(nullptr)) {};
//	
//					- 기본적으로 이전 방식과 비슷하지만 몇가지 차이가 있음
//						- detail::test<T> 함수에서 std::is_union 을 검사함
//						- sizeof 연산 없이 detail::test<T> 의 리턴 타입으로 true / false 를 이용하여 바로 구분함
//							- std::false_type 은 std::integral_constant<bool, false> 와 같음
//	
//		*/
//	
//	}

/*  SFINAE : Substitution Failure Is Not An Error*/
#include <iostream>

template <typename T>
void test(typename T::x a) { std::cout << "T::x" << '\n'; }

template <typename T>
void test(typename T::y b) { std::cout << "T::y" << '\n'; }

struct A
{
	using x = int;
};

struct B
{
	using y = int;
};

int main()
{
	test<A>(33);	// T::x

	test<B>(22);	// T::y
}