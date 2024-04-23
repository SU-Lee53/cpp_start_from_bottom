
/*
	04.23 가변 길이 템플릿, 파라미터 팩, Fold 형식
*/

// 가변 길이 템플릿, 파라미터 팩

//	#include <iostream>
//	
//	template <typename T>
//	void print(T arg)
//	{
//		std::cout << arg << std::endl;
//	}
//	
//	template <typename T, typename... Types>
//	void print(T arg, Types... args)
//	{
//		std::cout << arg << ", ";
//		print(args...);
//	}
//	
//	int main()
//	{
//		print(1, 3.1, "abc");
//		print(1, 2, 3, 4, 5, 6, 7);
//	
//		/*
//			output:
//			1, 3.1, abc
//			1, 2, 3, 4, 5, 6, 7
//		*/
//	
//		/*
//			- 가변 길이 템플릿, 파라미터 팩
//				- 위의 print 함수는 파이썬의 print()처럼 인자의 타입이나 갯수에 상관없이 모두 출력하는 함수
//					- C++에서도 가변 길이 템플릿을 이용하여 이러한 기능을 구현할 수 있음
//	
//				- 파라미터 팩(parameter pack)
//					- cppreference에 나온 정의
//						- A template parameter pack is a template parameter that accepts zero or more template arguments (non-types, types, or templates)
//							-> 템플릿 파라미터 팩: 0개 이상의 템플릿 인자를 받는 템플릿 매개변수
//						- A function parameter pack is a function parameter that accepts zero or more function arguments.
//							-> 함수 파라미터 팩: 0개 이상의 함수 인자를 받는 함수 매개변수
//					- 파라미터 팩의 선언
//						- 템플릿 파라미터 팩: 타입 앞에 ... 으로 선언
//							-> template<typename... Types>
//						- 함수 파라미터 팩: 타입 뒤에 ... 으로 선언
//							-> void print(Types... args) {}
//					- 파라미터 팩은 추론된 인자를 제외한 나머지 인자들을 나타냄
//						- 위의 print(1, 3.1, "abc"); 를 보면...
//							- 함수 호출시 컴파일러는 2개의 print() 함수의 정의를 보고 어느것을 택할지 정해야함
//								-> void print(T arg) 는 인자가 단 1개이므로 후보에서 제외되고, 2번째 void print(T arg, Types... args)가 선택됨
//							- print()의 첫번째 인자는 1이므로 T는 int로 추론되고 arg에 1이 들어감.
//							- args에는 나머지 3.1과 "abc"가 들어감
//								-> 이것이 실제로 인스턴스화 되면 아래처럼 됨
//									
//									void print(int arg, double arg2, const char* arg3)
//									{
//										std::cout << arg << ", ";
//										print(arg2, arg3);
//									}
//							
//							- 위에서 arg를 출력한 다음 다시 재귀적으로 print를 호출함
//								-> 이번에 인스턴스화 되면 아래처럼 됨
//	
//									void print(double arg, const char* arg2)
//									{
//										std::cout << arg << ", ";
//										print(arg2);
//									}
//	
//							- 또 한번 재귀 호출된 print는 인자가 1개 남음
//								-> 이번에는 인자가 1개인 void print(T arg) 가 호출됨
//								-> C++ 규칙상 파라미터 팩이 없는 함수가 우선순위가 더 높기 때문
//							- 그러므로 마지막에 std::endl이 출력될 수 있게됨
//	
//					- 파라미터 팩 사용시의 주의점
//						- 위의 두 print 함수의 위치를 바꿔서 쓰면 컴파일 오류가 발생함
//							-> C++ 컴파일러가 함수 컴파일시에, 자신의 앞에 정의되어 있는 함수들밖에 보지 못하기 때문임
//							-> 순서가 뒤바뀌면 void print(T arg, Types... args) 가 void print(T arg)의 존재를 모르게 때문에 마지막에 코드를 인스턴스화 할 수 없어져버림
//								-> 템플릿 함수 작성시에는 반드시 순서에 유의해야함
//		*/
//	}

// 가변 길이 템플릿의 적용 - 임의의 개수의 문자열 합치기

//	/*
//		- 임의의 개수의 문자열 합치기
//			- std::string의 문자열을 합치기 위해서는 operator+를 이용함
//			- 이때 임의의 개수의 문자열을 합치려고 해보자
//				- concat = s1 + s2 + s3;
//					-> s2를 더할때 메모리 할당이 발생하고 거기에 s3를 더할때 또 메모리 할당이 발생
//					-> 차라리 한번에 필요한 만큼 메모리를 할당해버리는게 더 빠름
//						-> 이를 위해 여러개의 문자열을 합치는 StrCat 함수를 만들어 보고자 함
//	*/
//	
//	#include <iostream>
//	#include <string>
//	
//	size_t GetStringSize(const char* s) { return strlen(s); }
//	size_t GetStringSize(const std::string& s) { return s.size(); }
//	
//	template<typename String, typename... Strings>
//	size_t GetStringSize(const String& s, Strings... strs)
//	{
//		return GetStringSize(s) + GetStringSize(strs...);
//	}
//	
//	void AppendToString(std::string* concat_str) { return; }
//	
//	template <typename String, typename... Strings>
//	void AppendToString(std::string* concat_str, const String& s, Strings... strs)
//	{
//		concat_str->append(s);
//		AppendToString(concat_str, strs...);	// strs에 남은 문자열이 없으면 void AppendToString(std::string* concat_str)이 호출되어 끝남
//	}
//	
//	template <typename String>
//	std::string StrCat(const String& s)
//	{
//		return std::string(s);
//	}
//	
//	template <typename String, typename... Strings>
//	std::string StrCat(const String& s, Strings... strs)
//	{
//		// 먼저 합쳐질 문자열의 총 길이를 구한다
//		size_t total_size = GetStringSize(s, strs...);
//	
//		// reserve를 통해 미리 공간을 할당해 놓는다
//		std::string concat_str;
//		concat_str.reserve(total_size);
//	
//		concat_str = s;
//	
//		AppendToString(&concat_str, strs...);
//	
//		return concat_str;
//	}
//	
//	int main()
//	{
//		// std::string 과 const char*를 혼합해서 사용 가능
//		std::cout << StrCat(std::string("this"), " ", "is", " ", std::string("a"), " ", std::string("sentence"));
//	
//		/*
//			output:
//			this is a sentence
//		*/
//	
//		// 위 구현은 읽어보면 어렵지 않으므로 설명 생략
//	}

// sizeof...

//	#include <iostream>
//	
//	// 재귀 호출 종료를 위한 베이스 케이스
//	int sum_all() { return 0; }
//	
//	template <typename... Ints>
//	int sum_all(int num, Ints... nums)
//	{
//		return num + sum_all(nums...);
//	}
//	
//	template <typename... Ints>
//	double average(Ints... nums)
//	{
//		return static_cast<double>(sum_all(nums...)) / sizeof...(nums);
//	}
//	
//	int main()
//	{
//		// (1 + 4 + 2 + 3 + 10) / 5
//		std::cout << average(1, 4, 2, 3, 10) << std::endl;
//		
//		/*
//			output:
//			4
//		*/
//	
//		/*
//			- sizeof...
//				- 일반 sizeof: 인자의 크기를 리턴(바이트)
//				- sizeof...() 은 파라미터 팩에 사용시 전체 인자의 개수를 리턴함
//		*/
//	}

// Fold Expression

#include <iostream>

template <typename... Ints>
int sum_all(Ints... nums)
{
	// 단항 좌측 Fold(Unary left fold)
	return (... + nums);
}

template <typename Int, typename... Ints>
Int diff_from(Int start, Ints... nums)
{
	// 이항 좌측 Fold(Binary left fold)
	return (start - ... - nums);
}

class A
{
public:
	void do_something(int x) const
	{
		std::cout << "Do something with " << x << std::endl;
	}
};

template <typename T, typename... Ints>
void do_many_things(const T& t, Ints... nums)
{
	// 각각의 인자들에 대해 do_something 함수들을 호출한다
	(t.do_something(nums), ...);
}

int main()
{
	// 1 + 4 + 2 + 3 + 10
	std::cout << sum_all(1, 4, 2, 3, 10) << std::endl;

	// 100 - 1 - 4 - 2 - 3 - 10
	std::cout << diff_from(100, 1, 4, 2, 3, 10) << std::endl;

	A a;
	do_many_things(a, 1, 2, 3, 4);

	/*
		output:
		20
		80
		Do something with 1
		Do something with 2
		Do something with 3
		Do something with 4

		위 코드 실행시 프로젝트 옵션에서 C++ 언어 표준을 C++ 17 이상으로 올려야함
	*/

	/*
		- Fold Expression
			- 기존의 가변 길이 템플릿은 매우 편리하지만 반드시 재귀 호출 종료를 위한 함수를 따로 만들어야 한다는 단점이 있음
				-> C++ 17 에서 새로 도입된 Fold Expression을 사용하면 그럴필요 없이 훨씬 간단하게 표현할 수 있음

			- Fold Expression
				- Fold 방식은 아래의 4가지가 있음
					1) 단항 우측 Fold (Unary right fold): (E op ...)
						-> (E1 op (... op (EN-1 op EN)))
					2) 단항 좌측 Fold (Unary left fold): (... op E)
						-> (((E1 op E2) op ...) op EN)
					3) 이항 우측 Fold (Binary right fold): (E op ... op I)
						-> (E1 op (... op (EN-1 op (EN op I))))
					4) 이항 좌측 Fold (Binary left fold): (I op ... op E)
						-> ((((I op E1) op E2) op ...) op EN
					-> op 자리에는 대부분의 이항 연산자들이 포함됨(+ - * / % ^ & | = < > << >> += -= *= /= %= ^= &= |= <<= >>= == != <= >= && || , .* ->*)
					-> I 는 초기값을 의미하며 파라미터 팩이 아님
				- 위 코드를 보고 이해하면 쉬움
					- int sum_all(Ints... nums)의 return (... + nums) 부분
						-> (... + nums) 같은 형태가 단항 좌측 fold로 아래와 같이 컴파일러에서 해석함
							return ((((1 + 4) + 2) + 3) + 10);
					- Int diff_from(Int start, Ints... nums)의 return (start - ... - nums) 부분
						-> (start - ... - nums) 같은 형태가 이항 좌측 fold로 아래와 같이 컴파일러에서 해석함
							return (((((100 - 1) - 4) - 2) - 3) - 10);
					- void do_many_things(const T& t, Ints... nums)의 (t.do_something(nums), ...) 부분
						-> 파라미터 팩 내의 모든 인자들에 대해서 각각 t.do_something(x)를 실행한 것과 같음. 즉, 아래와 같이 컴파일됨
							t.do_something(1);
							t.do_something(3);
							t.do_something(2);
							t.do_something(4);
						-> , 도 이항 연산자중 하나임을 알 수 있음
				- Fold 식을 쓸때는 반드시 ()로 감싸주어야 함
					-> return (... + nums); 가 아니라 return ... + nums; 로 작성하면 오류가 발생함
	
	*/

}


