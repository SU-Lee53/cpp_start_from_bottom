/*
	06.05 - 함수 객체 std::function, std::mem_fn, std::bind
*/

/*  Callable  */
//	#include <iostream>
//	#include <functional>
//	
//	struct S
//	{
//		void operator()(int a, int b) { std::cout << "a + b = " << a + b << std::endl; }
//	};
//	
//	int main()
//	{
//		S some_obj;
//		some_obj(3, 5);
//	
//		auto f = [](int a, int b) -> void {std::cout << "a + b = " << a + b << std::endl; };
//		f(3, 5);
//	
//		// INVOKE
//		std::cout << "INVOKE 연산" << std::endl;
//		std::invoke(some_obj, 3, 5);
//		std::invoke(f, 3, 5);
//	
//		/*
//			- Callable
//				- 말 그대로 "호출할 수 있는" 모든 것을 의미함
//					-> C++ 에서는 ()로 호출할 수 있는 모든 것들을 의미함
//	
//				- 위의 클래스 S의 객체인 some_obj 도 Callable
//					-> 정확히는 some_obj.operator()(3,5) 를 한 것 이지만 ()로 호출 가능하니 Callable
//				- 람다 함수인 f 도 Callable
//					-> 일반적인 함수가 아니더라도 ()로 호출이 가능하면 다 Callable
//	
//	
//				※ cppreference 에서는 다음과 같이 정의하고 있음
//					The type T satisfies Callable if
//					Given
//						- f, an object of type T,
//						- ArgTypes, suitable list of argument types,
//						- R, suitable return type.
//					The following expressions must be valid:
//					Expression									Requirements
//					INVOKE<R>(f, std::declval<ArgTypes>()...)	The expression is well-formed in unevaluated context.
//	
//					타입 T 가 아래의 사항을 만족하면 Callable임
//					주어진
//						- f 가 T 타입의 객체
//						- ArgTypes 가 인자 타입에 대한 적절한 인자들
//						- R 이 적절한 리턴 타입
//					에 대해서 다음의 표현식이 유효해야만 함
//					표현식										요구사항
//					INVOKE<R>(f, std::declval<ArgTypes>()...)	해당 표현식은 평가되지 않은 컨텍스트에서 잘 구성됨(틀린거 없이 정상작동 한다는 의미)
//	
//					-> 즉, INVOKE, INVOKE<R> 연산이 유효한 것들은 전부 Callable
//						-> INVOKE
//							- 사전적 의미의 invoke : 발생하다, 실시하다 등
//							- 무언가를 호출하는 하나의 연산 https://en.cppreference.com/w/cpp/utility/functional 의 
//						-> INVOKE<R> 은 C++ 23 부터 std::invoke_r<R> 을 사용하여 연산
//						-> 그 이전은 std::invoke() 만 존재
//	
//	
//	
//	
//	
//	
//	
//		
//		*/
//	}

/*  std::function  */
//	#include <iostream>
//	#include <functional>
//	#include <string>
//	
//	int some_func1(const std::string& a)
//	{
//		std::cout << "Func1 호출 " << a << std::endl;
//		return 0;
//	}
//	
//	struct S
//	{
//		void operator()(char c) { std::cout << "Func2 호출 " << c << std::endl; }
//	};
//	
//	int main()
//	{
//		// C의 함수 포인터
//		std::cout << "C-style function pointer examples" << std::endl;
//	
//		int (*func1)(const std::string&) = some_func1;
//		// void (*func2)(char) = S();	// 함수 포인터는 함수만 담을 수 있었음
//		void (*func3)() = []()-> void { std::cout << "Func3 호출" << std::endl; };
//	
//		func1("hello");
//		std::cout << "functor 는 함수 포인터에 담을 수 없음" << std::endl;
//		func3();
//	
//		std::cout << "------------------------------" << std::endl;
//	
//		// C++ 의 std::function
//		std::cout << "std::function examples" << std::endl;
//		std::function<int(const std::string&)> f1 = some_func1;
//		std::function<void(char)> f2 = S();
//		std::function<void()> f3 = []() {std::cout << "Func3 호출" << std::endl; };
//	
//		f1("hello");
//		f2('c');
//		f3();
//	
//	
//		/*
//			- output : 
//				C-style function pointer examples
//				Func1 호출 hello
//				functor 는 함수 포인터에 담을 수 없음
//				Func3 호출
//				------------------------------
//				std::function examples
//				Func1 호출 hello
//				Func2 호출 c
//				Func3 호출
//		*/
//	
//		/*
//			- std::function
//				- std::function : Callable 인 것들을 객체의 형태로 보관할 수 있는 클래스
//				- C 의 함수 포인터와의 차이
//					- 함수 포인터(C) : 진짜 함수만 보관 가능
//					- std::function(C++) : 모든 Callable 보관 가능
//						-> 위 코드에서 보다시피 함수, 함자(functor), 람다 함수 모두 보관 가능함
//				
//				- 사용법
//					- 템플릿 인자로는 <리턴타입(인자타입)> 을 받음
//					- 일반 함수, 함자, 람다함수 모두 동일함
//					ex) 만약 int 를 리턴하고 인자로 const string& 을 받는 f 를 만들고 싶다면 :
//						
//							std::function<int(const string&)> f;
//	
//						로 정의하면 됨
//		*/
//	}

/*  멤버 함수를 가지는 std::function  */
//	#include <functional>
//	#include <iostream>
//	#include <string>
//	
//	class A
//	{
//	public:
//		A(int c) : c(c) {}
//		
//		int some_func() 
//		{ 
//			std::cout << "비상수 함수 : " << ++c << std::endl; 
//			return c;
//		}
//	
//		int some_const_func() const
//		{
//			std::cout << "상수 함수 : " << c << std::endl;
//			return c;
//		}
//	
//	
//	private:
//		int c;
//	};
//	
//	int main()
//	{
//		A a(5);
//		//	std::function<int()> f1 = a.some_func;	// E0300 : 바인딩된 함수에 대한 포인터는 함수를 호출하는 데에만 사용할 수 있습니다
//		std::function<int(A&)> f1 = &A::some_func;
//		std::function<int(const A&)> f2 = &A::some_const_func;
//	
//		f1(a);
//		f2(a);
//	
//		/*
//			- output:
//				비상수 함수 : 6
//				상수 함수 : 6
//		*/
//	
//		/*
//			- 멤버 함수를 가지는 std::function
//				- std::function 에 일반적인 Callable 들을 담는것은 문제 없음
//				- std::function 에 멤버 함수들을 담기 위해서는 조금 달라지는 것들이 있음
//					- 위 코드에서 
//						
//							std::function<int()> f1 = a.some_func
//	
//						-> f1 호출 시 함수는 자신을 호출하는 객체가 무엇인지 알 수 없음
//						-> 그러므로 내부의 c 또한 어떤 객체의 c 인지 알 수 없음
//	
//						-> std::function 에 멤버 함수를 담기 위해선 아래처럼 하면 됨
//							1) 비상수 함수의 경우
//	
//								std::function<int(A&)> f1 = &A::some_func;
//	
//							2) 상수 함수의 경우
//	
//								std::function<int(const A&)> f2 = &A::some_const_func;
//	
//							-> 멤버 함수는 일반 함수와 달리 & 연산자를 이용해 주소값을 직접 넘겨주어야 함
//								-> C++ 표준에서 일반함수는 이름을 대입하면 주소값으로 암시적 변환을 해주지만 멤버함수는 그렇지 않음
//								-> 따라서 멤버함수는 명시적으로 주소값을 넘겨주어야 함
//							
//							-> 객체 호출시에도 반드시 호출하고자 하는 객체도 인자로 받아주어야 함
//								-> a 의 멤버함수를 호출하고 싶다면 
//	
//									f1(a);
//									f2(a);
//	
//								로 호출하면 됨
//	
//						※ python 에서 클래스 멤버 함수를 정의할때 def func(self) 처럼 반드시 첫번째 인자로 자기 자신을 넣는것과 같은 행위임
//	
//		*/
//	}

/*  mem_fn : 멤버 함수들을 함수 객체로  */
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using std::vector;

int main()
{
	vector<int> a(1);
	vector<int> b(1);
	vector<int> c(1);
	vector<int> d(1);

	vector<vector<int>> container;
	container.push_back(b);
	container.push_back(d);
	container.push_back(a);
	container.push_back(c);

	vector<int> size_vec(4);
	std::transform(container.begin(), container.end(), size_vec.begin(), &vector<int>::size);
	for (const auto& e : size_vec)
		std::cout << "벡터 크기 :: " << e << std::endl;

}


