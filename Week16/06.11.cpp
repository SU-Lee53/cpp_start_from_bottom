/*
	06.11 - constexpr
*/

/*  상수식과 constexpr  */
//	#include <iostream>
//	
//	template <int N>
//	struct A
//	{
//		int operator()() { return N; }
//	};
//	
//	int main()
//	{
//		constexpr int size = 3;
//		int arr[size];
//	
//		constexpr int N = 10;
//		A<N> a;
//		std::cout << a() << std::endl;
//	
//		constexpr int number = 3;
//		enum B { x = number, y, z };
//		std::cout << B::x << std::endl;
//	
//		/*
//			- output : 
//				10
//				3
//		*/
//	
//		/*
//			- 상수식
//				- 컴파일 타임에 값을 결정할 수 있는 식
//	
//			- constexpr
//				- constant expression 을 줄인 키워드로 어떠한 식이 상수식임을 명시해주는 키워드
//		*/
//	
//	}

/*  const vs constexpr  */
//	#include <iostream>
//	
//	int main()
//	{
//		int a;
//	
//		const int b = a;
//		// constexpr int c = a;	// C2131 : 식이 상수로 계산되지 않았습니다.
//		// constexpr int c = b;	// C2131 : 식이 상수로 계산되지 않았습니다.
//	
//		constexpr int const_a = 3;
//		constexpr int const_b = const_a;	// 가능
//	
//		/*
//			- const vs constexpr
//				- const 로 정의된 상수는 컴파일 타임에 그 값을 알지 못해도 상관 없음
//					-> 위 const int b = a; 에서 b 는 컴파일 타임에 값을 알 수 없음
//					-> 그러나 const 이므로 값을 지정하면 변경할 수 없음
//	
//				- constexpr 변수는 반드시 오른쪽에 다른 상수식이 와야만 함
//					-> 위 constexpr int c = a 는 a 가 constexpr이 아니므로 대입할 수 없음. 컴파일 타임에 값을 알 수 없기 때문
//					-> 위 constexpr int const_b = const_a 는 우변도 constexpr 이므로 대입이 가능함
//	
//				- 즉, constexpr 는 const 이지만, const 는 constexpr 이 아님
//	
//				- const int i = 3; 같은 식을 컴파일 타임에 초기화하려면 반드시 const 가 아닌 constexpr 로 정의해야함
//					-> const int i = 3; 은 컴파일 타임, 런타임 모두 초기화가 가능한 식
//		*/
//	
//	}

/*  constexpr 함수  */
//	#include <iostream>
//	
//	int factorial(int N)
//	{
//		int total = 1;
//		for (int i = 1; i <= N; i++)
//			total *= i;
//	
//		return total;
//	}
//	
//	template <int N>
//	struct A
//	{
//		int operator()() { return N; }
//	};
//	
//	template <int N>
//	struct Factorial
//	{
//		const static int value = N * Factorial<N - 1>::value;
//	};
//	
//	template <>
//	struct Factorial<0>
//	{
//		const static int value = 1;
//	};
//	
//	constexpr int c_factorial(int n)
//	{
//		int total = 1;
//		for (int i = 1; i <= n; i++)
//			total *= i;
//	
//		return total;
//	}
//	
//	// constexpr 함수가 될수 없는 예시
//	int foo() { return 1; }
//	constexpr int bar() { 
//		// return foo();	// C3615 : constexpr 함수 'bar'은(는) 상수 식을 생성할 수 없습니다. 
//		return 1;
//	}
//	
//	int main()
//	{
//		// A<factorial(5)> a;	// C2975 : 'N': 'A'의 템플릿 인수가 잘못되었습니다. 컴파일 타임 상수 식이 필요합니다.
//	
//		// TMP 코드는 컴파일 타임에 계산되므로 컴파일 타임 상수
//		A<Factorial<10>::value> a;
//		std::cout << a() << std::endl;	// 3628800
//	
//		A<c_factorial(10)> b;
//		std::cout << b() << std::endl;	// 3628800
//	
//		int ten = 10;
//		// A<c_factorial(ten)> c;	// C2975 : 'N': 'A'의 템플릿 인수가 잘못되었습니다. 컴파일 타임 상수 식이 필요합니다.
//									// constexpr 함수의 인자로 컴파일 타임 상수가 아닌 값을 넣으면 컴파일 타임 상수를 반환하지 않음
//	
//		/*
//			- constexpr 함수
//				- 컴파일 타임 상수인 객체를 만들 수 있는 함수
//				- 몇가지 제약 조건만 만족하면 constexpr 함수 내부에서 실행 가능함
//					- goto
//					- 예외 (C++ 20 부터는 가능)
//					- 리터럴 타입이 아닌 변수의 정의 -> 나중에 다시 다룸
//					- 초기화 되지 않는 변수의 정의
//					- 실행 중간에 constexpr 이 아닌 함수를 호출
//						-> C++ 표준 버전이 올라갈수록 제약조건이 조금씩 풀리기도 함 (C++ 23 에서는 위 제약들의 대부분이 풀린걸로 보임)
//						-> 가장 최신은 https://en.cppreference.com/w/cpp/language/constexpr 의 constexpr function 부분을 참고
//						-> constexpr 함수인데 위 제약 조건이 함수 본체에 사용된다면 컴파일 오류 발생함
//	
//				- 인자가 컴파일 타임 상수라면 리턴값도 컴파일 타임 상수 
//				- 인자가 컴파일 타임 상수가 아니라면 일반 함수처럼 동작하고 리턴값은 컴파일 타임 상수가 아님
//					-> 따라서 constexpr 를 붙일 수 있는 함수면 붙여주는것이 좋음
//				
//		
//		*/
//	}

/*  리터럴 타입  */
/*
	- 리터럴 타입
		- 컴파일러가 컴파일 타임에 정의할 수 있는 타입 https://en.cppreference.com/w/cpp/named_req/LiteralType
			- void
			- 스칼라 타입 (char, int, bool, long, float, double, enum, 포인터 등등 https://en.cppreference.com/w/cpp/named_req/ScalarType)
			- 레퍼런스 타입
			- 리터럴 타입의 배열
			- 아래 조건들을 만족하는 타입
				- 디폴트 소멸자를 가지고
				- 다음 중 하나를 만족하는 타입
					- 람다 함수
					- Arggregate 타입 (사용자 정의 생성자, 소멸자가 없고 모든 데이터 멤버들이 public https://en.cppreference.com/w/cpp/language/aggregate_initialization#Definitions)
					- constexpr 생성자를 가지며 복사 및 이동생성자가 없음
		
		- 위 타입들만 constexpr 함수 내부에서 다룰 수 있음
		- C++ 14 부터 constexpr 생성자를 지원하여 사용자가 직접 리터럴 타입을 만들수도 있음

*/

/*  constexpr 생성자  */
//	#include <iostream>
//	
//	class Vector
//	{
//	public:
//		constexpr Vector(int x, int y) : x_(x), y_(y) {}
//	
//		constexpr int x() const { return x_; }
//		constexpr int y() const { return y_; }
//	
//	private:
//		int x_;
//		int y_;
//	};
//	
//	constexpr Vector AddVec(const Vector& v1, const Vector& v2)
//	{
//		return { v1.x() + v2.x(), v1.y() + v2.y() };
//	}
//	
//	template <int N>
//	struct A
//	{
//		int operator()() { return N; }
//	};
//	
//	int main()
//	{
//		constexpr Vector v1{ 1,2 };
//		constexpr Vector v2{ 2,3 };
//	
//		// constexpr 객체의 constexpr 멤버 함수는 constexpr
//		A<v1.x()> a;
//		std::cout << a() << std::endl;	// 1
//	
//		A<AddVec(v1, v2).x()> b;
//		std::cout << b() << std::endl;	// 3
//	
//		/*
//			- constexpr 생성자
//				- 기본적으로 constexpr 함수의 제약 조건들이 모두 적용됨
//				- 추가로 constexpr 생성자의 인자들은 반드시 리터럴 타입이어야만 하고, 다른 클래스를 가상상속 받을 수 없음
//				- 위 코드 설명
//	
//					- constexpr Vector v1{ 1,2 };
//						-> Vector 의 생성자가 constexpr 이므로 constexpr 로 Vector를 선언할 수 있음
//	
//					- A<v1.x()> a;
//						-> x() 함수 역시 constexpr 이므로 컴파일 타임 상수를 리턴
//						-> 만약 v1 이나 x() 둘 중 하나라도 constexpr 이 아니라면 컴파일 되지 않음
//							-> constexpr 객체의 constexpr 멤버함수만 constexpr 를 리턴함
//	
//					- A<AddVec(v1, v2).x()> b;
//						-> Vector 가 리터럴 타입이고, AddVec 또한 constexpr 함수이므로 constexpr 객체 Vector 를 리턴함
//	
//		
//		*/
//	}

/*  if constexpr  */
#include <iostream>
#include <type_traits>

/*  인자가 포인터 타입인지 알려주는 함수 - TMP 버전  */
//	template<typename T>
//	void show_value(T t)
//	{
//		std::cout << "포인터가 아니다 : " << t << std::endl;
//	}
//	
//	template <typename T>
//	void show_value(T* t)
//	{
//		std::cout << "포인터 이다 : " << *t << std::endl;
//	}

/*  인자가 포인터 타입인지 알려주는 함수 - <type_traits> 이용 -> 컴파일 오류  */
//	template <typename T>
//	void show_value(T t)
//	{
//		if (std::is_pointer<T>::value) 
//			std::cout << "포인터 이다 : " << *t << std::endl;	// C2100 : 'T' 형식의 피연산자를 역참조할 수 없습니다.
//		else 
//			std::cout << "포인터가 아니다 : " << t << std::endl;
//	
//		// T 가 int 로 추론되어 * 연산자로 역참조가 불가능하므로 컴파일되지 않음
//	}

/* 인자가 포인터 타입인지 알려주는 함수 - <type_traits> + if constexpr 이용 */
//	template <typename T>
//	void show_value(T t)
//	{
//		if constexpr (std::is_pointer<T>::value)	// std::is_pointer<T>::value 는 std::is_pointer_v<T> 로 변경 가능
//			std::cout << "포인터 이다 : " << *t << std::endl;
//		else
//			std::cout << "포인터가 아니다 : " << t << std::endl;
//	}
//	
//	int main()
//	{
//		int x = 3;
//		show_value(x);
//	
//		int* p = &x;
//		show_value(&x);
//	
//		/*
//			- if constexpr
//				- bool 로 타입 변환될 수 있는 컴파일 타임 상수식이 조건으로 올때 
//					- 참이면 else 부분의 문장을 컴파일하지 않고 무시
//					- 거짓이면 else 부분만 컴파일하고 윗부분은 무시
//	
//				- 아예 컴파일되지 않으므로 위 show_value 같은 함수를 만들 수 있음
//					- 기존의 show_value 는 템플릿 인자 추론에 따라 컴파일 오류가 발생하는 if 분기가 존재함
//					- if constexpr 를 사용하면 컴파일 오류가 발생하는 부분을 컴파일하지 않으므로 문제가 없음
//		*/
//	}

/*  C++ 20 에 추가된 constexpr  */
/*
	- constexpr 소멸자 https://en.cppreference.com/w/cpp/language/constexpr 의 constexpr destructor 참고
	- constexpr new https://www.cppstories.com/2021/constexpr-new-cpp20/

	- 등등 앞으로 더 나올 예정

*/