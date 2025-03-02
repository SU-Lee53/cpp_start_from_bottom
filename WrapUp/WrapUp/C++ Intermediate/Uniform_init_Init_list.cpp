/*
	06.10 - 균일한 초기화, 초기화자 리스트
*/

/*  함수?  */
//	#include <iostream>
//	
//	class A
//	{
//	public:
//		A() { std::cout << "A 의 생성자 호출" << std::endl; }
//	};
//	
//	class B
//	{
//	public:
//		B(A a) { std::cout << "B 의 생성자 호출" << std::endl; }
//	};
//	
//	int main()
//	{
//		A a();	// 아무것도 출력되지 않음
//		B b(A());	// 아무것도 출력되지 않음
//	
//		/*
//			- 균일한 초기화의 필요성
//				- 위 2줄의 코드는 각각의 생성자가 호출되어야 할것 같지만 호출되지 않음
//				- 결론부터 말하자면 객체 생성자 호출이 아닌 함수의 정의로 컴파일되기 때문임
//					-> A a() : A 클래스 객체 a 를 생성한 것이 아닌 A를 리턴하는 a() 라는 함수로 컴파일
//					-> B b(A()) : B 클래스 객체 b 를 생성한 것이 아닌 인자가 없는 함수를 받는 B를 리턴하는 함수 b() 라는 함수로 컴파일
//	
//				- 왜 이런일이 일어나는가?
//					- () 연산자가 2가지 역할을 하기 때문
//						1) 함수의 인자 정의
//						2) 객체의 생성자 호출
//	
//				- C++ 11 에서 도입된 균일한 초기화를 이용해서 위 문제를 해결할 수 있음
//		*/
//	}

/*  균일한 초기화 Uniform Initialization  */
//	#include <iostream>
//	
//	class A
//	{
//	public:
//		A() { std::cout << "A의 생성자 호출" << std::endl; }
//		A(int x) { std::cout << "A의 생성자 호출" << std::endl; }
//	};
//	
//	A func() 
//	{ 
//		return { 1 }; 
//	}
//	
//	int main()
//	{
//		A a{};	// A의 생성자 호출 -> 균일한 초기화
//	
//		// 균일한 초기화는 Narrow-conversion 이 불가능함
//		A b(3.5);	// 가능
//		// A c{ 3.5 };	// C2398 : 요소 '1': 'double'에서 'int'(으)로 변환하려면 축소 변환이 필요합니다.
//	
//		func();	// 함수 리턴시 객체의 타입을 명시하지 않아도 됨
//	
//		/*
//			- 균일한 초기화
//				- 객체 생성시 () 대신 {} 를 이용하여 사용
//				- 특징
//					- Narrow-conversion 이 불가능해 원치 않는 캐스팅을 사전에 잡아낼 수 있음
//						- Narrow-conversion : 데이터가 손실될 수 있는 암묵적 타입 변환
//							- 부동 소수점 타입 -> 정수 타입
//							- 정수 타입 -> 부동 소수점 타입
//							- long double -> double / float
//							- double -> float
//							- 더 많은 것들은 https://en.cppreference.com/w/cpp/language/list_initialization 의 Narrowing conversions 를 참고
//	
//					- 함수 리턴시 리턴 타입을 다시 명시하지 않아도 됨
//						-> 위 코드의 func() 에서 A{1} 이 아닌 {1} 만 작성해도 정상적으로 생성되어 리턴됨
//		
//		*/
//	}

/*  초기화자 리스트 Initializer list  */
//	#include <iostream>
//	#include <vector>
//	#include <map>
//	#include <string>
//	class A
//	{
//	public:
//		A(std::initializer_list<int> l)
//		{
//			for (auto it = l.begin(); it != l.end(); ++it)
//			{
//				std::cout << *it << std::endl;
//			}
//		}
//	};
//	
//	template <typename T>
//	void print_vec(const std::vector<T>& vec)
//	{
//		std::cout << "[";
//		for (const auto& e : vec)
//			std::cout << e << " ";
//		std::cout << "]" << std::endl;
//	}
//	
//	template<typename K, typename V>
//	void print_map(const std::map<K, V>& map)
//	{
//		for (const auto& kv : map)
//			std::cout << kv.first << " : " << kv.second << std::endl;
//	
//	}
//	
//	int main()
//	{
//		A a = { 1,2,3,4,5 };
//		// A b(1, 2, 3, 4, 5);	// () 는 initializer list 를 생성하지 않음
//		// A b({ 1,2,3,4,5 });	// 가능
//	
//		/*  initializer list 를 이용하여 STL 컨테이너들 초기화  */
//		std::vector<int> v = { 1,2,3,4,5 };
//		print_vec(v);
//	
//		std::cout << "-----------------------" << std::endl;
//		std::map<std::string, int> m = {
//			{"abc", 1}, {"hi", 3}, {"hello", 5}, {"C++", 2}, {"java", 6}
//		};
//		print_map(m);
//	
//		/*
//			- 여기까지 output:
//				1
//				2
//				3
//				4
//				5
//				[1 2 3 4 5 ]
//				-----------------------
//				C++ : 2
//				abc : 1
//				hello : 5
//				hi : 3
//				java : 6
//		*/
//	
//		/*  initializer list 사용 시 주의사항  */
//		std::vector<int> v1(10);
//		std::vector<int> v2{ 10 };
//	
//		std::cout << "v1 : " << v1.size() << " ";
//		print_vec(v1);
//		
//		std::cout << "v2 : " << v2.size() << " ";
//		print_vec(v2);
//	
//		/*
//			- output :
//				v1 : 10 [0 0 0 0 0 0 0 0 0 0 ]
//				v2 : 1 [10 ]
//	
//		
//		*/
//	
//		/*
//			- 초기화자 리스트 Initializer list
//				- {} 를 사용하여 생성자를 호출할 때 생성자 중에 std::initializer_list 를 인자로 받는 생성자가 있을때 전달됨
//					- {} 를 하나의 배열로 보고 내용들을 복사해서 initializer_list 가 됨
//					- () 로 생성자를 호출하면 initializer_list 가 생성되지 않음
//	
//				- initializer list 를 이용하면 컨테이너들을 쉽게 정의할 수 있음
//					- 컨테이너의 생성자들 중에 initializer list 를 받는게 있기때문에 가능
//					- vector 를 예로들면 아래와 같음(MSVC)
//	
//						_CONSTEXPR20 vector(initializer_list<_Ty> _Ilist, const _Alloc& _Al = _Alloc())
//							: _Mypair(_One_then_variadic_args_t{}, _Al) {
//							_Construct_n(_Convert_size<size_type>(_Ilist.size()), _Ilist.begin(), _Ilist.end());
//						}
//	
//				- initializer list 사용시 주의할 점
//					- initializer_list 를 받는 생성자가 있을 때 {} 로 객체를 생성하면 해당 생성자가 최우선으로 고려됨
//					- 예시 : 위의 v1, v2
//						- v1 은 (10), v2 는 {10} 으로 생성자 호출
//						- 벡터에는 아래와 같은 생성자가 있음(MSVC)
//	
//							_CONSTEXPR20 explicit vector(_CRT_GUARDOVERFLOW const size_type _Count, const _Alloc& _Al = _Alloc())
//								: _Mypair(_One_then_variadic_args_t{}, _Al) {
//								_Construct_n(_Count);
//							}
//	
//							-> size_type count 를 인자로 받고 그 크기의 벡터를 생성함
//	
//						- v1 (10) 과 v2 {10} 이 얼핏 보기엔 같아 보이지만 다름
//							- v1 (10) 은 바로 위의 vector(size_type _Count) 버전의 생성자를 호출
//							- v2 {10} 은 vector(std::initializer_list _Ilist) 버전의 생성자를 호출
//								-> 그 결과로 생성된 벡터가 완전히 다름
//							
//					- Narrow-conversion 의 불가로 인해 호출할수 없는 생성자도 최우선으로 고려됨
//						- 예를 들어, 아래 2개의 생성자가 있을때
//	
//							A(int n, double d) {}
//							A(std::initializer_list<int> lst) {}
//	
//						- 아래 코드는 문제가 발생함
//	
//							A(10, 1.5);
//							A{10, 1.5};	-> 여기서 Narrow conversion 이 불가능하므로 컴파일 오류가 발생
//	
//						- 다만 아예 변환될 수 없는경우는 다른 생성자를 호출함. 즉, 위 생성자 대신
//	
//								A(std::initializer_list<std::string> lst) {}
//							
//							라는 생성자가 있다면
//	
//								A{10, 1.5};
//	
//							는 string 으로 변환될 수 없으므로 A(int n, double d) 생성자가 호출됨
//		*/
//	
//	}

/*  initializer_list 와 auto 타입 추론  */
//	#include <iostream>
//	#include <typeinfo>
//	
//	using namespace std::literals;
//	
//	int main()
//	{
//		auto list = { 1,2,3 };
//		std::cout << typeid(list).name() << std::endl;	// class std::initializer_list<int>
//	
//		auto list2 = { "a", "b", "cc" };
//		std::cout << typeid(list2).name() << std::endl;	// class std::initializer_list<char const * __ptr64>
//	
//		auto list3 = { "a"s, "b"s, "cc"s };	// 리터럴 연산자를 이용해야 const char* 가 아닌 std::string 이 됨
//		std::cout << typeid(list3).name() << std::endl;	// class std::initializer_list<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >
//	
//		auto a = { 1 };
//		auto b{ 1 };
//		auto c = { 1,2 };
//		// auto d{ 1,2 };	// E2663 : 자리 표시자 형식은 있으나 '='는 없이 선언된 변수의 중괄호 초기화에서는 중괄호 안에 정확히 하나의 요소가 있어야 합니다.
//		
//		std::cout << "auto a = { 1 } -> " << typeid(a).name() << std::endl;	// auto a = { 1 } -> class std::initializer_list<int>
//		std::cout << "auto b{ 1 } -> " << typeid(b).name() << std::endl;	// auto b{ 1 } -> int
//		std::cout << "auto c = { 1, 2 } -> " << typeid(c).name() << std::endl;	// auto c = { 1, 2 } -> class std::initializer_list<int>
//	
//		/*
//			- initializer_list 와 auto
//				- initializer_list 와 auto 의 타입 추론에는 규칙이 있음
//	
//					- {} 를 이용하여 생성시 타입으로 auto 를 지정하면 initializer_list<T> 객체로 생성됨
//						
//						auto list = { 1,2,3 }; -> std::initializer_list<int>
//	
//					- 문자열은 기본적으로 initializer_list<const char*> 로 추론
//	
//						auto list2 = { "a", "b", "cc" }; -> std::initializer_list<char const * __ptr64>
//	
//					- std::string 으로 추론되게 하려면 리터럴 연산자를 이용해야함
//	
//						auto list3 = { "a"s, "b"s, "cc"s }; -> std::initializer_list<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>>>
//	
//					- C++ 17 부터 추가된 규칙
//	
//						- auto x = { arg1, arg2 ... } 형태 : arg1, arg2 ... 들이 같은 타입(T)이면 x -> std::initializer_list<T>
//							
//							auto a = { 1 }; -> std::initializer_list<int>
//							auto c = { 1,2 }; -> std::initializer_list<int>
//	
//						- auto x { arg1, arg2 ... } 형태 : 만일 인자가 단 1개라면 타입으로 추론, 여러개면 오류 발생
//							
//							auto b{ 1 }; -> int
//							auto d{ 1,2 }; -> E2663 : 자리 표시자 형식은 있으나 '='는 없이 선언된 변수의 중괄호 초기화에서는 중괄호 안에 정확히 하나의 요소가 있어야 합니다.
//	
//	
//		*/
//			
//			
//	}
