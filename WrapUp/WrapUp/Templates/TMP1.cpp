
/*
	04.24 템플릿 메타 프로그래밍 1
*/

// array wrapper 실습, typeof

//	#include <iostream>
//	#include <typeinfo>
//	
//	template <typename T, unsigned int N>
//	class Array
//	{
//	public:
//		Array(T(&arr)[N])
//		{
//			for (int i = 0; i < N; i++)
//			{
//				data[i] = arr[i];
//			}
//		}
//	
//		T* get_array() { return data; }
//	
//		unsigned int size() { return N; }
//	
//		void print_all()
//		{
//			for (int i = 0; i < N; i++)
//			{
//				std::cout << data[i] << ", ";
//			}
//			std::cout << std::endl;
//		}
//	
//	private:
//		T data[N];
//	};
//	
//	int main()
//	{
//		int arr[3] = { 1, 2, 3 };
//		
//		Array<int, 3> arr_w(arr);
//	
//		arr_w.print_all();
//	
//		// Array<int, 3> 과 Array<int, 5>는 같은 클래스일까 다른 클래스일까
//		std::cout << std::boolalpha << (typeid(Array<int, 3>) == typeid(Array<int, 5>)) << std::endl;
//	
//		/*
//			output
//			1, 2, 3,
//			false
//		*/
//	
//		/*
//			- typeid
//				- 타입을 알려주는 연산자(함수가 아님)
//				- 사용하려면 <typeinfo> 헤더파일을 include 해야함
//		*/
//	}

// 컴파일 타임 연산

//	#include <iostream>
//	
//	template <int N>
//	struct Int
//	{
//		static const int num = N;
//	};
//	
//	template <typename T, typename U>
//	struct add
//	{
//		typedef Int<T::num + U::num> result;
//	};
//	
//	int main()
//	{
//		typedef Int<1> one;
//		typedef Int<2> two;
//	
//		typedef add<one, two>::result three;
//	
//		std::cout << "Addition result : " << three::num << std::endl;
//		
//		/*
//			output
//			Addition result : 3
//		*/
//	
//		/*
//			- 컴파일 타임 연산
//				- 위 코드의 설명
//					- struct Int : static const int 값을 하나 저장 -> static const는 '이 클래스는 이 것이다' 라는 의미를 가장 잘 나타냄
//						- static 변수는 모든 Int의 인스턴스가 공유하는 값이니까 말이 안된다?
//							-> Int<> 에 템플릿 인자가 같지 않은 이상 전부 다른 클래스이므로 공유 안됨
//					- struct add : 템플릿 인자로 2개의 타입을 받아서 그 타입의 num 멤버를 더한 뒤 새로운 타입인 result를 만들어냄
//					- typedef Int<1> one;... : 객체를 생성하듯이 타입을 생성함. 여기서 one 과 two는 1 과 2의 값을 나타내는 타입이 됨(객체가 아님)
//					- typedef add<one, two>::result three : one과 two를 더한 결과를 내부의 result 타입을 three 라고 정의함. three도 위처럼 타입임
//					- three::num의 결과로 3이 출력
//	
//				- 위 코드에서 1 + 2가 런타임에 더해지는게 아니라 컴파일 타임에 더해짐. 즉 컴파일러가 컴파일 중에 더해 three::num을 3으로 치환하고 런타임에는 실제로 더하지 않음
//					-> three::num 위에 마우스를 올려보면 알 수 있음
//				
//				- 이렇게 타입을 이용한 연산은 컴파일 도중에 이루어짐(타입은 반드시 컴파일타임에 확정되어야 하므로)
//					-> 이러한 특징을 이용하여 타입을 가지고 컴파일 타임에 생성되는 코드로 프로그래밍 하는 것을 메타 프로그래밍이라고 함
//					-> C++은 템플릿을 이용해서 메타 프로그래밍을 하기 때문에 템플릿 메타 프로그래밍(TMP)이라고 부름
//		
//		*/
//	}

// 템플릿 메타 프로그래밍

//	#include <iostream>
//	
//	// TMP를 이용하지 않는 팩토리얼 함수
//	int factorial(int n)
//	{
//		if (n == 1) return 1;
//		return n * factorial(n - 1);
//	}
//	
//	template <int N>
//	struct Factorial
//	{
//		static const int result = N * Factorial<N - 1>::result;
//	};
//	
//	template <>
//	struct Factorial<1>
//	{
//		static const int result = 1;
//	};
//	
//	int main()
//	{
//		std::cout << "6! = 1 * 2 * 3 * 4 * 5 * 6 = " << Factorial<6>::result << std::endl;
//	
//		/*
//			output:
//			6! = 1 * 2 * 3 * 4 * 5 * 6 = 720
//		*/
//	
//		/*
//			- 템플릿 메타 프로그래밍
//				- C++에서 템플릿을 이용해 타입을 가지고 컴파일 타임에 생성되는 코드로 프로그래밍 하는것을 템플릿 메타 프로그래밍(TMP)이라고 함
//				- 템플릿을 이용하면 타입에 어떠한 "값"을 부여할 수 있고, 그 값들을 이용해서 "연산"을 할 수 있음
//				- 위의 Factorial 클래스 템플릿을 보면...
//					- 기본적인 클래스는 단순히 곱함
//					- 템플릿 특수화를 이용하여 Factorial<1>을 따로 처리해주어 재귀적인 곱셈을 끝나게 해줌
//					- 6!의 결과인 Factorial<6>은 값을 가지는 객체나 변수가 아니고 컴파일러가 만들어낸 타입중 하나임 
//						-> 위 코드만으로는 메모리 상에 720 이라는 값을 가진 변수는 존재하지 않음
//				- for문을 이용한 모든 코드는 TMP로도 구현 가능함. 재귀함수를 이용하거나 하는 등의 방법이 있음
//				- if문을 이용한 코드도 템플릿 특수화를 이용하여 구현 가능함.
//		*/
//	}

// TMP를 왜 쓰는가?

//	/*
//		- TMP를 왜 쓰는가?
//			- 매우 큰 장점이 있음
//				-> 컴파일 타임에 모든 연산이 끝나므로 프로그램 실행 속도가 향상됨
//			- 단점또한 존재함
//				-> 모든 C++ 코드를 TMP로 바꿀수도 있지만 매우 복잡함
//				-> TMP로 작성된 코드는 버그를 찾기 힘듬. 컴파일 타임에 연산하기 때문에 디버깅이 잘 안되고 오류시에 C++ 컴파일러가 엄청난 길이의 오류를 내뿜음
//	
//			- 위의 단점때문에 TMP는 제한적으로 사용되지만 많은 C++ 라이브러리가 TMP를 이용함
//				-> 단위 변환등의 코드를 만들때 컴파일 타임 연산이 디버깅하기 유리하기도 함
//				-> 런타임 속도 향상이 무시할 수 없는 수준임
//	
//			- 아래의 팩토리얼보다는 더 복잡한 예시를 가지고 TMP를 어떻게 사용할지 생각해보자
//	*/
//	
//	#include <iostream>
//	
//	// 유클리드 호제법을 이용한 최대공약수 구하기
//	
//	// 함수 버전
//	int gcd(int a, int b)
//	{
//		if (b == 0)
//			return a;
//	
//		return gcd(b, a % b);
//	}
//	
//	// TMP 버전
//	template <int X, int Y>
//	struct GCD
//	{
//		static const int value = GCD<Y, X % Y>::value;
//	};
//	
//	template<int X>
//	struct GCD<X, 0>
//	{
//		static const int value = X;
//	};
//	
//	// 위에서 구한 최대 공약수로 오차 없는 유리수(Ratio) 클래스를 TMP로 만들기
//	
//	template <int N, int D = 1>
//	struct Ratio
//	{
//	private:
//		const static int _gcd = GCD<N, D>::value;
//	
//	public:
//		typedef Ratio<N / _gcd, D / _gcd> type;	// 클래스의 this와 비슷한 역할을 하도록 typedef를 이용하여 자기 자신을 가리키는 타입을 넣어줌
//		static const int num = N / _gcd;	// 분자
//		static const int den = D / _gcd;	// 분모
//	
//	};
//	
//	// 유리수 사칙연산
//	
//	template<class R1, class R2>
//	struct _Ratio_add
//	{
//		typedef Ratio<R1::num* R2::den + R2::num * R1::den, R1::den* R2::den> type;
//	};
//	
//	template <class R1, class R2>
//	struct Ratio_add : _Ratio_add<R1, R2>::type {};	// _Ratio_add::type을 매번 명시하지 않게 하도록 해당 타입을 상속받는 Ratio_add 클래스를 만들어버림
//	
//	template <class R1, class R2>
//	struct _Ratio_subtract
//	{
//		using type = Ratio < R1::num* R2::den - R2::num * R1::den, R1::den* R2::den>;
//	};
//	
//	template <class R1, class R2>
//	struct Ratio_subtract : _Ratio_subtract<R1, R2>::type {};
//	
//	template <class R1, class R2>
//	struct _Ratio_multiply
//	{
//		using type = Ratio<R1::num* R2::num, R1::den* R2::den>;
//	};
//	
//	template <class R1, class R2>
//	struct Ratio_multiply : _Ratio_multiply<R1, R2>::type {};
//	
//	template <class R1, class R2>
//	struct _Ratio_divide
//	{
//		using type = Ratio<R1::num* R2::den, R1::den* R2::num>;
//	};
//	
//	template <class R1, class R2>
//	struct Ratio_divide : _Ratio_divide<R1, R2>::type {};
//	
//	int main()
//	{
//		std::cout << "gcd(36, 24) :: " << GCD<36, 24>::value << std::endl;
//	
//		//	typedef Ratio<2, 3> rat;
//		//	typedef Ratio<3, 2> rat2;
//		//	typedef Ratio_add<rat, rat2> rat3;
//		//	위 typedef는 C++11부터 using이라는 좀 더 직관적인 키워드를 이용하여 바꿀 수 있음
//	
//		using r1 = Ratio<2, 3>;
//		using r2 = Ratio <3, 2>;
//	
//		using r3 = Ratio_add<r1, r2>;
//		std::cout << "2 / 3 + 3 / 2 = " << r3::num << " / " << r3::den << std::endl;
//	
//		using r4 = Ratio_multiply<r3, r1>;
//		std::cout << "13 / 6 * 2 / 3 = " << r4::num << " / " << r4::den << std::endl;
//	
//		/*
//			output:
//			gcd(36, 24) :: 12
//			2 / 3 + 3 / 2 = 13 / 6
//			13 / 6 * 2 / 3 = 13 / 9
//		*/
//	
//		return 0;
//	}
//	
//	/*
//		- using
//			- C++11 에 새로 도입된 키워드
//			- typedef와 같은 역할을 함
//			- 함수 포인터의 경우에도 사용 가능함
//				-> void 를 리턴하고 int, int 를 인자로 받는 함수를 func로 정의하고싶다면
//					-> typedef : typedef void (*func)(int, int)
//					-> using : using func = void(*)(int, int)
//	*/