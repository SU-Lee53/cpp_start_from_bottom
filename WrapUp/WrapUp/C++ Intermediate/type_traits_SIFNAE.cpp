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
//								- 컴파일 오류는 발생하지 않고 넘어감. 나중에 SFINAE 에서 이를 활용하기도 함
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

/*  SFINAE : Substitution Failure Is Not An Error  */
//	#include <iostream>
//	
//	template <typename T>
//	void test(typename T::x a) { std::cout << "T::x" << '\n'; }
//	
//	template <typename T>
//	void test(typename T::y b) { std::cout << "T::y" << '\n'; }
//	
//	struct A
//	{
//		using x = int;
//	};
//	
//	struct B
//	{
//		using y = int;
//	};
//	
//	int main()
//	{
//		test<A>(33);	// T::x
//	
//		test<B>(22);	// T::y
//	
//		/*
//			- SFINAE
//				- 치환 오류는 컴파일 오류가 아니다 (Substitution Failure Is Not An Error)
//	
//				- 템플릿 함수를 컴파일 할때 템플릿 인자들을 유추한 타입으로 치환
//				- 이 과정에서 문법적으로 올바르지 않아도 컴파일 오류를 일으키지 않음
//				- 대신 오버로딩 후보군에서 제외시킴
//	
//				- 함수 내용 전체가 문법적으로 올바른지 확인하는것은 아님
//					-> 함수의 인자들과 리턴 타입만 문법적으로 올바른지 확인함
//					-> 따라서 문법적으로 올바르지 않은 내용이 있어도 오버로딩 후보군에 남을 수도 있음
//	
//				- 위 코드의 경우
//					- test<A>(33); 을 호출하면 2개의 오버로딩 함수는 다음과 같이 치환됨
//	
//						template <typename T>
//						void test(typename A::x a) { std::cout << "A::x" << '\n'; }
//						
//						template <typename T>
//						void test(typename A::y b) { std::cout << "A::y" << '\n'; }
//	
//					- class A 에는 y가 없으므로 A::y 는 문법적으로 틀림
//					- 이때 컴파일 오류가 아니라 오버로딩에서 제외함으로서 A::x 가 출력
//	
//		
//		*/
//	
//	}

/*  std::enable_if  */
//	#include <iostream>
//	#include <type_traits>
//	
//	// enable_if 의 간단한 구현 (실제 구현과 거의 같음)
//	
//	template<bool B, typename T = void>
//	struct enable_if {};
//	
//	template <typename T>
//	struct enable_if<true, T> { typedef T type; };
//	
//	// std::enable_if 를 이용하여 정수 타입만 받는 test 템플릿 함수
//	template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
//	void test(const T& t)
//	{
//		std::cout << "t : " << t << std::endl;
//	}
//	
//	struct A {};
//	
//	int main()
//	{
//		test(1);	// t : 1
//		test(false);	// t : 0
//		test('c');	// t : c
//		// test(A{});	// E0304 : 인수 목록이 일치하는 함수 템플릿 "test"의 인스턴스가 없습니다
//	
//		/*
//			- std::enable_if
//				- SFINAE 를 이용하여 조건에 맞지 않는 함수들을 오버로딩 후보군에서 쉽게 뺄 수 있도록 하는 템플릿 메타 함수
//				- 실제 정의는 아래와 같음 (MSVC)
//	
//						_EXPORT_STD template <bool _Test, class _Ty = void>
//						struct enable_if {}; // no member "type" when !_Test
//						
//						template <class _Ty>
//						struct enable_if<true, _Ty> { // type is _Ty for _Test
//						    using type = _Ty;
//						};
//	
//					- 위 간단한 구현 버전과 일치
//					- bool 인자에 원하는 조건을 넣어주면 작동
//						- true 인 경우 type 이 정의됨 (아래것으로 오버로딩)
//						- false 인 경우 type 이 정의되지 않아 ::type 호출시 컴파일 오류를 일으켜 특정 타입을 강제함 (위에것으로 오버로딩)
//	
//				- 어떻게 사용되는가
//	
//						template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
//	
//					- 위 처럼 사용시 T 에 정수타입만 오도록 강제함
//					- 코드 설명
//						- typename = 
//							-> 템플릿에 디폴트 인자를 전달하는 부분
//							-> 원래는 typename U = 이런식으로 인자를 받지만 이경우는 필요없음
//	
//						- std::enable_if 앞에 한번 더 나온 typename
//							-> std::enable_if<>::type 자체가 의존타입이므로 붙어야함
//	
//		
//		*/
//	
//	}

/*  std::enable_if 의 활용 1  */
//	#include <iostream>
//	#include <type_traits>
//	
//	template <typename T>
//	class vector
//	{
//	public:
//		// element 가 num 개 들어있는 vector 생성
//		vector(size_t num, const T& element) { std::cout << element << " 를 " << num << " 개 만들기" << std::endl; }
//	
//		// 반복자 start 부터 end 까지로 vector 생성
//		//	template <typename Iterator>
//		//	vector(Iterator start, Iterator end) { std::cout << "반복자를 이용한 생성자 호출" << std::endl; }
//		// 
//		// 이 생성자를 이용할경우 아래 main() 의 vector<int> v(10, 3); 가 여기로 오버로딩됨
//		// 이걸 막으려면 enable_if 를 이용하여 제약을 걸어야 함
//	
//		template <typename Iterator, typename = typename std::enable_if<std::_Is_iterator_v<Iterator>>::type>
//		vector(Iterator start, Iterator end) { std::cout << "반복자를 이용한 생성자 호출" << std::endl; }
//	
//	
//	};
//	
//	int main()
//	{
//		vector<int> v(10, 3);
//	
//		/*
//			- std::enable_if 의 사용
//				- 만약 우리가 vector 를 직접 만든다고 가정하고 2가지 생성자를 만들려고 할때
//					
//						1) vector(size_t num, const T& element) 로 element 를 num 개 채워서 생성하는 생성자
//						2) vector(Iterator start, Iterator end) 반복자로 시작과 끝을 받아 생성하는 생성자
//	
//					- 이때 2번 생성자를 만들때 템플릿을 많이 사용함
//					- 단순 template <typename Iterator> 를 이용하면 문제가 생김
//						- vector<int> v(10, 3); 같이 생성자를 호출하면 2번 생성자가 오버로딩됨
//	
//				- 왜?
//					- 기본적으로 size_t 는 unsigned long long 타입임
//						- <vcruntime.h> 라는 헤더에서 typedef unsigned __int64 size_t; 로 정의
//						- #ifdef 를 이용하여 OS 별로 다름 (64비트 윈도우를 제외하고는 unsigned int 로 정의됨)
//					- num 이 부호없는 정수가 와야하지만 10 은 부호가 있는 정수로 취급
//					- 마침 아무제약 없는 템플릿 함수 vector(Iterator start, Iterator end) 가 존재
//						-> 컴파일러는 이걸 더 나은 후보라고 판단하고 이 생성자를 오버로딩해버림
//		
//				- 이럴때 std::enable_if 를 이용하여 특정 타입을 강제할 수 있음
//	
//						template <typename Iterator, typename = typename std::enable_if<std::_Is_iterator_v<Iterator>>::type>
//	
//					- 앞서 본 정수타입만 받는 문장과 작동은 동일
//					- 다만 _Is_iterator_v 가 C++ 표준이 아니므로 사용하는 STL 에 따라 약간씩 달라질 수 있음
//		
//		*/
//	}

/*  std::enable_if 의 활용 2  */
//
// 특정한 멤버 함수가 존재하는 타입만을 받는 함수를 만들고 싶음
//	#include <iostream>
//	#include <vector>
//	#include <set>
//	
//	// std::enable_if 미사용
//	template <typename T, typename = decltype(std::declval<T>().func())>
//	void test(const T& t)
//	{
//		std::cout << "t.func() : " << t.func() << std::endl;
//	}
//	
//	// std::enable_if 를 사용하면 리턴타입까지 강제 가능
//	template <typename T, typename = std::enable_if_t<std::is_integral_v<decltype(std::declval<T>().func())>>>
//	void test2(const T& t)
//	{
//		std::cout << "t.func() : " << t.func() << std::endl;
//	}
//	
//	struct A
//	{
//		int func() const { return 1; }
//	};
//	
//	struct B 
//	{
//		char func() const { return 'a'; }
//	};
//	
//	struct C
//	{
//		A func() const { return A{}; }
//	};
//	
//	struct D {};
//	
//	// 여러개의 함수를 확인
//	template <typename Cont, typename = decltype(std::declval<Cont>().begin()), typename = decltype(std::declval<Cont>().end())>
//	void print(const Cont& container)
//	{
//		std::cout << "[ ";
//		for (auto it = container.begin(); it != container.end(); ++it)
//		{
//			std::cout << *it << ' ';
//		}
//		std::cout << "]\n";
//	}
//	
//	template <typename Cont, typename = std::enable_if_t<std::_Is_iterator_v<decltype(std::declval<Cont>().begin())>>, typename = std::enable_if_t<std::_Is_iterator_v<decltype(std::declval<Cont>().end())>>>
//	void print2(const Cont& container)
//	{
//		std::cout << "[ ";
//		for (auto it = container.begin(); it != container.end(); ++it)
//		{
//			std::cout << *it << ' ';
//		}
//		std::cout << "]\n";
//	}
//	
//	int main()
//	{
//		test(A{});
//		test(B{});
//		// test(C{});
//		// test(D{});	// E0304 : 인수 목록이 일치하는 함수 템플릿 "test2"의 인스턴스가 없습니다.
//	
//		test2(A{});
//		test2(B{});
//		// test2(C{});	// E0304 : 인수 목록이 일치하는 함수 템플릿 "test2"의 인스턴스가 없습니다.
//		// test2(D{});	// E0304 : 인수 목록이 일치하는 함수 템플릿 "test2"의 인스턴스가 없습니다.
//	
//		std::vector<int> v = { 1,2,3,4,5 };
//		print(v);	// [1 2 3 4 5]
//		print2(v);	// [1 2 3 4 5]
//	
//		std::set<char> s = { 'a', 'b', 'c', 'd' };
//		print(s);	// [ a b c d ]
//		print2(s);	// [ a b c d ]
//	
//		/*
//			- std::enable_if 의 활용 2
//				- 타입이 특정한 멤버함수를 가지는지도 확인이 가능함
//	
//						template <typename T, typename = std::enable_if_t<std::is_integral_v<decltype(std::declval<T>().func())>>>
//	
//					- decltype 을 이용한 버전과 다르게 리턴타입까지 강제할 수 있음
//					- 여러개의 멤버함수를 확인하는것도 가능함
//	
//						template <typename Cont, 
//								typename = std::enable_if_t<std::_Is_iterator_v<decltype(std::declval<Cont>().begin())>>, 
//								typename = std::enable_if_t<std::_Is_iterator_v<decltype(std::declval<Cont>().end())>>>
//					
//					- 위는 enable_if 를 이용하여 2개의 멤버 함수를 가지고 있는지 확인(begin(), end())
// 
//						template <typename Cont, typename = decltype(std::declval<Cont>().begin()), typename = decltype(std::declval<Cont>().end())>
// 			
//					- 위는 decltype 을 이용하여  2개의 멤버 함수를 가지고 있는지 확인
//					- 둘다 너무 길어서 가독성도 떨어지고 좋아보이지 않음 -> C++ 17 에서 도입된 void_t 로 해결가능
//		
//		
//		*/
//	}

/*  void_t  */
//	#include <iostream>
//	#include <type_traits>
//	#include <vector>
//	
//	template <typename Cont, typename = std::void_t<decltype(std::declval<Cont>().begin()), decltype(std::declval<Cont>().end())>>
//	void print(const Cont& container)
//	{
//		std::cout << "[ ";
//		for (auto it = container.begin(); it != container.end(); ++it)
//		{
//			std::cout << *it << ' ';
//		}
//		std::cout << "]\n";
//	}
//	
//	// 사용자의 실수를 방지하기 위해 타입체크를 따로 뺀 print2
//	template <typename Cont>
//	std::void_t<decltype(std::declval<Cont>().begin()), decltype(std::declval<Cont>().end())> 
//	print2(const Cont& container)
//	{
//		std::cout << "[ ";
//		for (auto it = container.begin(); it != container.end(); ++it)
//		{
//			std::cout << *it << ' ';
//		}
//		std::cout << "]\n";
//	}
//	
//	struct Bad {};
//	
//	int main()
//	{
//		std::vector<int> v = { 1,2,3,4,5 };
//		print(v);	// [ 1 2 3 4 5 ]
//		print2(v);	// [ 1 2 3 4 5 ]
//	
//		// print<Bad, void>(Bad{});	// 타입체크 부분에 void 가 들어가버려 오버로딩 후보군에서 제외되지 않음(디폴트인자가 사용 안됨)
//		// print2<Bad, void>(Bad{});	// 컴파일 오류
//	
//		/*
//			- std::void_t
//				- void_t 의 구현
//	
//						_EXPORT_STD template <class... _Types>
//						using void_t = void;
//					
//					- 임의의 개수의 타입들을 전달받음
//					- 만약 전달받은 인자들 중에 문법적으로 올바르지 않은것이 있다면 SFINAE 에 의해 제외됨
//						- 모든 인자가 문법적으로 올바를때만 void_t 가 void 가 됨
//	
//				- void_t 의 활용
//						
//						template <typename Cont, typename = std::void_t<decltype(std::declval<Cont>().begin()), decltype(std::declval<Cont>().end())>>
//					
//					- 위 문장은 이전에 decltype 으로 특정 멤버함수 2개를 확인하는 문장과 동일함
//					- 이전보다 가독성이 약간 좋아짐
//					- 만약 Cont 가 begin(), end() 중 하나라도 없다면 오버로딩에서 제외됨
//	
//				- 주의사항
//					- void_t 를 이용할 때 타입체크 부분을 분리하는 것이 좋음
//						- 사용자가 엉뚱한 템플릿 인자를 추가로 넣으면 타입체크가 작동하지 않을 수 있기 때문임
//	
//	
//		*/
//	
//	}