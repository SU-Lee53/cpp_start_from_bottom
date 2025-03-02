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
//	#include <algorithm>
//	#include <functional>
//	#include <iostream>
//	#include <vector>
//	
//	using std::vector;
//	
//	int main()
//	{
//		vector<int> a(1);
//		vector<int> b(2);
//		vector<int> c(3);
//		vector<int> d(4);
//	
//		vector<vector<int>> container;
//		container.push_back(b);
//		container.push_back(d);
//		container.push_back(a);
//		container.push_back(c);
//	
//		std::function<size_t(const vector<int>&)> sz_func = &vector<int>::size;
//	
//		vector<int> size_vec(4);
//		// std::transform(container.begin(), container.end(), size_vec.begin(), &vector<int>::size); // C2064 항은 1개의 인수를 받아들이는 함수로 계산되지 않습니다.
//		
//		// std::transform(container.begin(), container.end(), size_vec.begin(), sz_func); // 혹은 
//		std::transform(container.begin(), container.end(), size_vec.begin(), std::mem_fn(&vector<int>::size));
//	
//		// std::mem_fn 없이 람다함수를 이용해도 동일함
//		// std::transform(container.begin(), container.end(), size_vec.begin(), [](const auto& v) -> size_t { return v.size(); });
//	
//	
//		for (const auto& e : size_vec)
//			std::cout << "벡터 크기 :: " << e << std::endl;
//	
//		/*
//			- std::mem_fn
//				- std::mem_fn : 멤버 함수를 함수 객체로 만들어 리턴해주는 함수
//				- 위 코드 설명
//					- 1 ~ 4 까지의 크기를 가진 vector a, b, c, d 를 만들고 각 벡터의 크기를 보관하는 size_vec 을 std::transform을 이용해 채우려는 코드
//					- std::transform 의 서술자 부분에 &vector<int>::size 함수를 직접 넘겨주면 컴파일 오류 발생
//						-> 이유를 알려면 <algorithm> 안에 있는 std::transform 함수의 모양을 봐야함
//	
//							_EXPORT_STD template <class _InIt, class _OutIt, class _Fn>
//							_CONSTEXPR20 _OutIt transform(const _InIt _First, const _InIt _Last, _OutIt _Dest, _Fn _Func) {
//								// transform [_First, _Last) with _Func
//								_STD _Adl_verify_range(_First, _Last);
//								auto _UFirst      = _STD _Get_unwrapped(_First);
//								const auto _ULast = _STD _Get_unwrapped(_Last);
//								auto _UDest       = _STD _Get_unwrapped_n(_Dest, _STD _Idl_distance<_InIt>(_UFirst, _ULast));
//								for (; _UFirst != _ULast; ++_UFirst, (void) ++_UDest) {
//									*_UDest = _Func(*_UFirst);
//								}
//							
//								_STD _Seek_wrapped(_Dest, _UDest);
//								return _Dest;
//							}
//	
//						-> 위에서 서술자 함수를 실행시키는 코드는 *_UDest = _Func(*_UFirst);
//						-> 이 부분에 &vector<int>::size 가 바로 들어가면 아래처럼 시도됨
//	
//							&vector<int>::size(*_UFirst);
//	
//						-> 멤버 함수는 (*_UFirst).(&vector<int>::size) 로 호출하는것이 맞으므로 위는 실행시킬 수 없음
//	
//					- 따라서 정상적인 std::transform 수행을 위해서는 &vector<int>::size 를 std::function 으로 만들어 주어야함
//						-> 만든 결과가 위의 sz_func 이고 아래처럼 만들어줌
//	
//							std::function<size_t(const vector<int>&)> sz_func = &vector<int>::size
//	
//					- 위처럼 매번 만드는 것이 쉽지 않으므로 std::mem_fn 을 이용해서 해결함
//						
//						std::mem_fn(&vector<int>::size)
//	
//						로 함수 객체를 직접 만들어 std::transform에 넣으면 정상 작동됨
//	
//	
//				- 생각보다 std::mem_fn은 자주 쓰이지 않는데 람다함수가 있기 때문임
//					-> std::mem_fn 이 더 코드가 깔끔하긴 하지만 <functional> 헤더를 삽입해야함
//					-> 반면 람다함수는 코드는 조금 지저분해져도 별도 헤더 없이 바로 사용 가능함
//		
//		
//		*/
//	
//	}

/*  std::bind  */
#include <functional>
#include <iostream>

void add(int x, int y)
{
	std::cout << x << " + " << y << " = " << x + y << std::endl;
}

void subtract(int x, int y)
{
	std::cout << x << " - " << y << " = " << x - y << std::endl;
}

struct S
{
	int data;
	S(int data) : data(data) { std::cout << "일반 생성자 호출" << std::endl; }	
	S(const S& s) : data(s.data) { std::cout << "복사 생성자 호출" << std::endl; }
	S(S&& s) : data(s.data) { std::cout << "이동 생성자 호출" << std::endl; }
};

void foo(S& s1, const S& s2) { s1.data = s2.data + 3; }

int main()
{
	auto add_with_2 = std::bind(add, 2, std::placeholders::_1);
	add_with_2(3);

	// 두번째 인자는 무시됨
	add_with_2(3, 4);

	auto subtract_with_2 = std::bind(subtract, std::placeholders::_1, 2);
	auto negate = std::bind(subtract, std::placeholders::_2, std::placeholders::_1);

	subtract_with_2(3);	// 3 - 2;
	negate(4, 2);	// 2 - 4;

	/*
		- 여기까지 output :
			2 + 3 = 5
			2 + 3 = 5
			3 - 2 = 1
			2 - 4 = -2
	*/


	S s1(1), s2(2);
	std::cout << "Before::s1.data :  " << s1.data << std::endl;

	std::cout << "\n복사본을 전달하는 func1 --------" << std::endl;

	// s1 이 그대로 전달된 것이 아니라 s1 의 복사본이 전달됨
	auto func = std::bind(foo, s1, std::placeholders::_1);
	func(s2);

	std::cout << "After func::s1.data : " << s1.data << std::endl;

	std::cout << "\n복사본 전달을 막는 func2 --------" << std::endl;
	
	// s1 의 복사본 전달을 막으려면 std::ref 로 참조를 넘겨주면 됨
	auto func2 = std::bind(foo, std::ref(s1), std::placeholders::_1);
	func2(s2);

	std::cout << "After func2::s1.data : " << s1.data << std::endl;

	/*
		- output
			일반 생성자 호출
			일반 생성자 호출
			Before::s1.data : 1
			
			복사본을 전달하는 func1 --------
			복사 생성자 호출
			After func::s1.data : 1
			
			복사본 전달을 막는 func2 --------
			After func2::s1.data : 5
	*/

	

	/*
		- std::bind
			- 사전적 의미 : 묶다
			- std::bind : 말 그대로 원래 함수에 특정 인자를 묶은 함수 객체를 생성해서 리턴함
			- bind 시킨 자리에도 인자가 전달이 가능하나 무시됨

			- std::placeholders : bind 가 리턴한 새로운 함수 객체의 인자
				- MSVC 기준 std::placeholders::_20 까지 있음
				- std::placeholders 의 순서대로 인자가 들어감
					-> 위의 negate 의 경우

						auto negate = std::bind(subtract, std::placeholders::_2, std::placeholders::_1);

					-> 이런식으로 반대로 넣어주면 negate(x, y) 수행을 y - x 로 수행함 (원래는 x - y)

				- 만약 placeholder 가 부족하다면 스스로 코드를 잘못짜지는 않았는지 반성이 필요한 경우가 대부분일듯

			- std::bind 사용시 주의사항 : 레퍼런스를 인자로 받는 경우
				- 원래 레퍼런스를 인자로 받는 자리에 std::bind 를 이용해 레퍼런스가 아닌 인자를 전달하면 인자가 복사되어 전달됨
				- 이를 막으려면 std::ref() 를 이용해 명시적으로 레퍼런스를 전달해야 함
				- const 레퍼런스의 경우 std::cref()를 이용하면 됨

				- std::ref() : 전달받은 인자를 복사 가능한 레퍼런스로 변환함
	
	*/

}