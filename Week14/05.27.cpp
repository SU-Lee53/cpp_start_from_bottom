/*
	05.27 12-2 move 문법(std::move sementics), 완벽한 전달(perfect forwarding)
*/

/*  MyString 의 swap - 좌측값의 이동?  */
//	#include <iostream>
//	#include <cstring>
//	
//	class MyString
//	{
//	public:
//		MyString()
//		{
//			std::cout << "생성자 호출" << std::endl;
//			string_length = 0;
//			memory_capacity = 0;
//			string_content = nullptr;
//		}
//	
//		MyString(const char* str)
//		{
//			std::cout << "생성자 호출" << std::endl;
//			string_length = strlen(str);
//			memory_capacity = string_length;
//			string_content = new char[memory_capacity];
//	
//			for (int i = 0; i != string_length; i++) string_content[i] = str[i];
//		}
//	
//		MyString(const MyString& str)
//		{
//			std::cout << "복사 생성자 호출" << std::endl;
//			string_length = str.string_length;
//			memory_capacity = str.memory_capacity;
//			string_content = new char[memory_capacity];
//	
//			for (int i = 0; i != string_length; i++) string_content[i] = str.string_content[i];
//		}
//	
//		MyString(MyString&& str)
//		{
//			std::cout << "이동 생성자 호출" << std::endl;
//			string_length = str.string_length;
//			memory_capacity = str.memory_capacity;
//			string_content = str.string_content;
//	
//			str.string_content = nullptr;
//		}
//	
//		MyString &operator=(const MyString& s)
//		{
//			std::cout << "복사" << std::endl;
//			if (s.string_length > memory_capacity)
//			{
//				delete[] string_content;
//				string_content = new char[s.string_length];
//				memory_capacity = s.memory_capacity;
//			}
//			string_length = s.string_length;
//			for (int i = 0; i != string_length; i++)
//			{
//				string_content[i] = s.string_content[i];
//			}
//	
//			return *this;
//		}
//	
//		int length() const { return string_length; }
//	
//		void println()
//		{
//			for (int i = 0; i != string_length; i++)
//			{
//				std::cout << string_content[i];
//			}
//			std::cout << std::endl;
//		}
//	
//		~MyString()
//		{
//			if (string_content) delete[] string_content;
//		}
//	
//	private:
//		char* string_content;
//		int string_length;
//		int memory_capacity;
//	};
//	
//	template <typename T>
//	void my_swap(T& a, T& b)
//	{
//		T tmp(a);
//		a = b;
//		b = tmp;
//	}
//	
//	int main()
//	{
//		MyString str1("abc");
//		MyString str2("def");
//		std::cout << "swap 전 ------" << std::endl;
//		str1.println();
//		str2.println();
//	
//		std::cout << "swap 후 ------" << std::endl;
//		my_swap(str1, str2);
//		str1.println();
//		str2.println();
//		/*
//			- output :
//			생성자 호출
//			생성자 호출
//			swap 전 ------
//			abc
//			def
//			swap 후 ------
//			복사 생성자 호출
//			복사
//			복사
//			def
//			abc
//		*/
//	
//		/*
//			- 좌측값의 이동?
//				- 위 코드의 설명
//					- MyString 객체 2개를 만들어 2개를 바꾸려고 함
//					- 이를 위해 템플릿을 이용한 my_swap 함수를 이용
//					- 이때 my_swap 함수 템플릿을 이용하여 바꿀때 불필요한 복사가 3번이나 일어남
//						- 직접 함수를 뜯으면서 보면
//	
//							template <typename T>
//							void my_swap(T& a, T& b)
//							{
//								T tmp(a);		-> 1차로 좌측값인 a를 저장해두기 위해 복사 생성자를 호출
//								a = b;			-> 2차 복사
//								b = tmp;		-> 3차 복사
//							}
//	
//							즉,
//	
//							str1.string_content(a) ------- 복사 1 --------> tmp.string_content
//							          ↑                                               |
//							       복사 2                                             |
//							          |                                               |
//							str2.string_content(b) <------------ 복사 3 --------------
//							
//							위 형태로 복사가 일어남
//	
//					- "이동" 이라는 개념을 배운 이상 이는 매우 비효율적임
//						-> 단순히 str1과 str2의 string_content 가 가리키는 포인터만 서로 바꿔주면 되기 때문
//	
//				- 어떻게 이동시킬까
//					- my_swap은 함수 템플릿이므로 MyString 을 위한 특수화가 필요함
//					- MyString의 string_content가 private 이므로 my_swap 이 아닌 MyString 의 멤버 함수로 swap을 구현해야함
//						-> 이 경우 my_swap 을 만든 이유가 사라짐
//	
//					- 그냥 만들어 놓은 my_swap을 이용하려면?
//						- tmp를 복사생성하지 않고 a를 옮겨놓기만 하면 됨
//						- 즉, T tmp(a) 가 복사생성이 아닌 이동생성이 되어야 함
//						- 그러나 a가 좌측값인 이상 이는 불가능함
//							-> 좌측값을 우측값으로 바꿔줄 수는 없을까? -> std::move를 이용하면 됨
//		*/
//	
//	}

/*  std::move  */
//	#include <iostream>
//	#include <utility>
//	#include <iomanip>
//	#include <vector>
//	#include <string>
//	
//	class A
//	{
//	public:
//		A() { std::cout << "일반 생성자" << std::endl; }
//		A(const A& a) { std::cout << "복사 생성자" << std::endl; }
//		A(A&& a) { std::cout << "이동 생성자" << std::endl; }
//	};
//	
//	int main()
//	{
//		A a;
//	
//		std::cout << "------------" << std::endl;
//		A b(a);
//	
//		std::cout << "------------" << std::endl;
//		A c(std::move(a));
//	
//		/*
//			- output : 
//				일반 생성자
//				------------
//				복사 생성자
//				------------
//				이동 생성자
//		*/
//	
//		/*
//			- std::move 와 move semantics
//				- std::move : <utility> 헤더에 정의된 함수로 좌측값을 우측값으로 형변환해줌
//				- std::move 단독으로는 이동같은게 수행되지 않음!!! 인자로 받은 객체를 우측값으로 타입 변환해주는 역할만 함
//	
//				- 위 코드
//					- A a : 일반 생성자가 정상적으로 호출
//					- A b(a) : a가 좌측값 이므로 복사 생성자가 호출
//					- A c(std::move(a)) : std::move 를 이용해 a를 우측값으로 바꾸어 주었으므로 이동 생성자가 호출
//		*/
//	
//		/*  cppreference 코드 추가 : move 된 이후 원래의 객체는 어떻게?  */
//		
//		std::string str = "Salut";
//		std::vector<std::string> v;
//	
//		// uses the push_back(const T&) overload, which means we'll incur the const of copying str
//		// push_back(const T&) 버전의 오버로드 함수를 사용함. 즉, str 복사에 따른 비용을 초래함
//		v.push_back(str);
//		std::cout << "After copy, str is " << std::quoted(str) << '\n';		// std::quoted : 사용자 지정의 구분자와 이스케이프 문자를 이용해 문자열을 읽거나 씀 (기본 구분자는 "", 이스케이프는 \)
//	
//		// uses the rvalue reference push_back(T&&) overload, which means no strings will be copied.
//		// instead, the contents of str will be moved into the vector. 
//		// This is less expensive, but also means str might now be empty.
//		// 
//		// 우측값 레퍼런스를 이용한 push_back(T&&) 버전의 오버로드 함수를 이용함. 즉, 어떠한 문자열도 복사되지 않음
//		// 대신, str의 내용들은 vector 안으로 이동됨
//		// 이것은 비용이 덜 들지만, str은 이제 비어있을 것임
//		v.push_back(std::move(str));
//		std::cout << "After move, str is " << std::quoted(str) << '\n';
//	
//		std::cout << "The contents of the vector are {" << std::quoted(v[0]) << ", " << std::quoted(v[1]) << "}\n";
//		
//		/*
//			- output :
//				After copy, str is "Salut"
//				After move, str is ""
//				The contents of the vector are {"Salut", "Salut"}
//				
//				-> 이동이 수행되면 원래 객체는 아무것도 들고있지 않음을 확인 가능함
//		*/
//	
//	}

/*  move 를 이용한 MyString 의 swap  */
//	#include <iostream>
//	#include <cstring>
//	#include <utility>
//	
//	class MyString
//	{
//	public:
//		MyString()
//		{
//			std::cout << "생성자 호출" << std::endl;
//			string_length = 0;
//			memory_capacity = 0;
//			string_content = nullptr;
//		}
//	
//		MyString(const char* str)
//		{
//			std::cout << "생성자 호출" << std::endl;
//			string_length = strlen(str);
//			memory_capacity = string_length;
//			string_content = new char[memory_capacity];
//	
//			for (int i = 0; i != string_length; i++) string_content[i] = str[i];
//		}
//	
//		MyString(const MyString& str)
//		{
//			std::cout << "복사 생성자 호출" << std::endl;
//			string_length = str.string_length;
//			memory_capacity = str.memory_capacity;
//			string_content = new char[memory_capacity];
//	
//			for (int i = 0; i != string_length; i++) string_content[i] = str.string_content[i];
//		}
//	
//		MyString(MyString&& str)
//		{
//			std::cout << "이동 생성자 호출" << std::endl;
//			string_length = str.string_length;
//			memory_capacity = str.memory_capacity;
//			string_content = str.string_content;
//	
//			str.string_content = nullptr;
//		}
//	
//		// 일반 대입 연산자
//		MyString& operator=(const MyString& s)
//		{
//			std::cout << "복사" << std::endl;
//			if (s.string_length > memory_capacity)
//			{
//				delete[] string_content;
//				string_content = new char[s.string_length];
//				memory_capacity = s.memory_capacity;
//			}
//			string_length = s.string_length;
//			for (int i = 0; i != string_length; i++)
//			{
//				string_content[i] = s.string_content[i];
//			}
//	
//			return *this;
//		}
//	
//		MyString& operator=(MyString&& s)
//		{
//			std::cout << "이동" << std::endl;
//			string_content = s.string_content;
//			memory_capacity = s.memory_capacity;
//			string_length = s.string_length;
//	
//			s.string_content = nullptr;
//			s.memory_capacity = 0;
//			s.string_length = 0;
//	
//			return *this;
//		}
//	
//		int length() const { return string_length; }
//	
//		void println()
//		{
//			for (int i = 0; i != string_length; i++)
//			{
//				std::cout << string_content[i];
//			}
//			std::cout << std::endl;
//		}
//	
//		~MyString()
//		{
//			if (string_content) delete[] string_content;
//		}
//	
//	private:
//		char* string_content;
//		int string_length;
//		int memory_capacity;
//	};
//	
//	template <typename T>
//	void my_swap(T& a, T& b)
//	{
//		T tmp(std::move(a));
//		a = std::move(b);
//		b = std::move(tmp);
//	}
//	
//	int main()
//	{
//		MyString str1("abc");
//		MyString str2("def");
//		std::cout << "Swap 전 -----" << std::endl;
//		std::cout << "str1 : ";
//		str1.println();
//		std::cout << "str2 : ";
//		str2.println();
//	
//		std::cout << "Swap 후 -----" << std::endl;
//		my_swap(str1, str2);
//		std::cout << "str1 : ";
//		str1.println();
//		std::cout << "str2 : ";
//		str2.println();
//	
//		/*
//			-output :
//				생성자 호출
//				생성자 호출
//				Swap 전 -----
//				str1 : abc
//				str2 : def
//				Swap 후 -----
//				이동 생성자 호출
//				이동
//				이동
//				str1 : def
//				str2 : abc
//		*/
//	
//		/*
//			- MyString swap 문제의 해결
//				- 기존의 문제 : swap 시 불필요한 복사가 3번 일어남
//				- 해결
//					1) tmp에 임시 저장하고 swap하는 모든 과정을 이동으로 처리
//						-> 불필요한 복사를 없앰
//	
//					2) 이동 대입 연산자 오버로딩
//						- 1)을 위해서 반드시 필요함
//						- 이동 생성자와 마찬가지로 데이터를 이동시킨 뒤 원본 객체에 동적할당된 메모리가 있다면 연결을 끊어야함
//						- 만약 이동 대입 연산자가 없다면 모든 대입이 복사로 일어남
//	
//				- 위 코드에서도 보듯이 std::move() 만으로 이동이 수행되는것이 아닌 그저 우측값으로 형변환하여 리턴하기만 함
//					-> 실제 이동은 이동 생성자나 이동 대입 연산자를 호출할때 일어남
//		*/
//	}

/*  객체 내부에 다른 객체 전달 문제  */
//	/*
//		- 문제
//			- 다음과 같은 2가지 클래스가 있다고 해볼때
//				- A : 일반적인 클래스
//				- B : A를 보관하는 클래스
//	
//			- B객체를 생성할 때 이미 생성된 A 객체를 B의 안으로 넣으려면 어떻게 생성자를 만들어야 하는가?
//	*/
//	
//	#include <iostream>
//	#include <utility>
//	
//	class A
//	{
//	public:
//		A() { std::cout << "ctor" << '\n'; }
//		A(const A& a) { std::cout << "copy ctor" << '\n'; }
//		A(A&& a) { std::cout << "move ctor" << '\n'; }
//	
//	};
//	
//	class B
//	{
//	public:
//		//	B(const A& a) : a_(a) {};
//		//	B(const A& a) : a_(std::move(a)) {};
//		//	B(A&& a) : a_(a) {};
//		B(A&& a) : a_(std::move(a)) {};
//	
//		A a_;
//	};
//	
//	int main()
//	{
//		A a;	// a 생성
//	
//		// 위에 만든 a를 B에 넣으려면?
//		std::cout << "create B --" << '\n';
//		B b(std::move(a));
//	
//		/*
//			- B 안에 이미 생성된 A a 를 넣는법?
//	
//				1) B(const A& a) : a_(a) {}; : 생성자를 만들어 전달하자
//					-> B 에 A가 들어가는것은 맞음
//					-> 그러나 B에 이미 있던 a가 들어가는것이 아닌 a를 복사생성한 새로운 A객체가 들어감
//					-> 오답
//	
//				2) B(const A& a) : a_(std::move(a)) {}; : 우측값으로 만들어 초기화해보자
//					-> initializer list 에서 a_(std::move(a))를 해주었으므로 이동 생성자가 호출되겠지? -> 아님
//						-> 복사 생성자의 인자가 const A& 이므로 std::move(a) 의 결과는 const A&& 임
//						-> 이때 컴파일러는 A의 생성자로 A&&를 받는 이동생성자가 아닌 const A&를 받는 복사 생성자를 선택함
//					-> 오답
//	
//				3) B(A&& a) : a_(a) {}; : 우측값을 받는 생성자를 만들어 전달하자
//					-> 우측값을 전달했으니 이동 생성자가 호출되겠지? -> 아님
//						-> a는 우측값 레퍼런스는 맞음
//						-> 다만 a 그 자체는 좌측값임(이름이 있음)
//						-> 따라서 복사 생성자가 호출됨
//					-> 오답
//	
//				4) B(A&& a) : a_(std::move(a)) {}; : 인자도 우측값으로 받고 초기화도 우측값으로 만들어서 하자
//					-> 정답
//	
//			- 결론
//				- 이미 생성된 객체를 다른 객체에 담고싶은 경우
//					-> 우측값을 받는 생성자를 만들고
//					-> 초기화까지 move 문법으로 우측값으로 해주어야 성공적으로 됨
//	
//		*/
//	
//	}

/*  완벽한 전달 perfect forwarding, 보편적 레퍼런스 universal reference , 레퍼런스 겹침 법칙 reference collapsing, std::forward  */
#include <iostream>
#include <vector>
#include <utility>

//	template <typename T>
//	void wrapper(T u)
//	{
//		g(u);
//	}

//	template <typename T>
//	void wrapper(T& u)
//	{
//		std::cout << "T& 로 추론됨" << std::endl;
//		g(u);
//	}

//	template <typename T>
//	void wrapper(const T& u)
//	{
//		std::cout << "const T& 로 추론됨" << std::endl;
//		g(u);
//	}

// 보편적 레퍼런스 사용
template <typename T>
void wrapper(T&& u)
{
	g(u);
}

class A {};

void g(A& a) { std::cout << "좌측값 레퍼런스 호출" << std::endl; }
void g(const A& a) { std::cout << "좌측값 상수 레퍼런스 호출" << std::endl; }
void g(A&& a) { std::cout << "우측값 레퍼런스 호출" << std::endl; }

int main()
{
	A a;
	const A ca;

	std::cout << "원본 -------" << std::endl;
	g(a);
	g(ca);
	g(A());

	std::cout << "Wrapper -----" << std::endl;
	wrapper(a);
	wrapper(ca);
	wrapper(A());



	/*
		- wrapper 를 T만 받도록 만든 경우 output : 
			원본 -------
			좌측값 레퍼런스 호출
			좌측값 상수 레퍼런스 호출
			우측값 레퍼런스 호출
			Wrapper -----
			좌측값 레퍼런스 호출
			좌측값 레퍼런스 호출
			좌측값 레퍼런스 호출

		- wrapper 를 T& 와 const T& 를 별도로 오버로딩 한 경우 output : 
			원본 -------
			좌측값 레퍼런스 호출
			좌측값 상수 레퍼런스 호출
			우측값 레퍼런스 호출
			Wrapper -----
			T& 로 추론됨
			좌측값 레퍼런스 호출
			const T& 로 추론됨
			좌측값 상수 레퍼런스 호출
			const T& 로 추론됨
			좌측값 상수 레퍼런스 호출
		
		- T& 만 오버로딩 한 경우 컴파일 오류 발생함
			-> g(A()), wrapper(A()) 가 들어갈 함수가 없음

		- 보편적 레퍼런스를 사용한 경우 output : 
			원본 -------
			좌측값 레퍼런스 호출
			좌측값 상수 레퍼런스 호출
			우측값 레퍼런스 호출
			Wrapper -----
			좌측값 레퍼런스 호출
			좌측값 상수 레퍼런스 호출
			우측값 레퍼런스 호출
	*/

	/*  레퍼런스 겹침  */
	typedef int& l_ref;
	typedef int&& r_ref;
	int n;

	l_ref& r1 = n;	// int& & -> int&
	l_ref&& r2 = n;	// int& && -> int&
	r_ref& r3 = n;	// int&& & -> int&
	r_ref&& r4 = 1;	// int&& & -> int&&
	// r_ref&& r4 = n;	// E1768 rvalue 참조를 lvalue에 바인딩할 수 없습니다

	/*
		- 완벽한 전달 perfect forwarding
			- C++ 11 이전 우측값 레퍼런스가 없던 시절에는 아래의 문제가 존재하였었음

				- wrapper 함수 정의 문제
					- wrapper : 인자로 u 를 받아 g(u) 를 실행시키는 함수 경우. 즉, 

							template <typename T>
							void wrapper(T u)
							{
								g(u);
							}

						이런식의 함수가 wrapper

						-> 실제 사례 : std::vector 의 emplace_back() 함수가 위처럼 작동하는 wrapper 함수임
							-> 받은 인자들을 이용해 내부에서 vector에 저장하려는 객체의 생성자를 호출시켜 뒤에 추가함
							-> 이렇게 하면 객체를 직접 만들어 추가하는것(push_back()) 보다 복사/이동이 일어나지 않아 더 빠름
								-> 컴파일러의 발전으로 이제 push_back() 과 차이가 안남
								-> 따라서 emplace_back() 은 불필요한 생성자 호출의 위험이 있으므로 되도록 하용하지 않는것이 좋음

					- 이러한 wrapper 함수 내부에서 인자들을 다른 함수의 인자로 의도한 대로 넣기 위해 wrapper 함수의 정의를 어떻게 해야하는가?

				- wrapper 문제를 어떻게 해결하는가?
					- 그냥 wrapper(T u) 로 정의 (T는 템플릿 인자)
						- 컴파일러가 템플릿 타입을 추론할 때, 템플릿 인자 T가 레퍼런스가 아니라면 const 를 무시함
						- 따라서 wrapper 안에 들어간 인자는 const 유무와 상관없이 모두 T로 추론됨
						- 오답

					- 그러면 wrapper(T& u) 로 정의하자
						- T&는 좌측값 레퍼런스 이므로 우측값이 인자로 들어갈 수 없음
						- 위 코드를 예로 들면 아래 2개가 문제가 생김
							1) g(A()); (MSVC만 오류가 안남)
							2) wrapper(A());
							-> T& 는 우측값을 참조할 수 없으므로 위 2가지는 컴파일 오류가 발생함
						- 오답

					- 그러면 wrapper(T& u) 와 wrapper(const T& u) 로 2번 오버로딩하자
						- 일단 원하는 대로 작동은 됨(const T& 는 우측값도 받을 수 있으므로)
						- 그러나 인자가 1개가 아닌 2개만 되도 만들어야할 함수가 4개임
							- 인자가 u, v 일때
								1) wrapper(T& u, T& v)
								2) wrapper(const T& u, T& v)
								3) wrapper(T& u, const T& v)
								4) wrapper(const T& u, const T& v)
								-> 인자 n개 마다 오버로드 해야되는 함수는 n^2개임...
						- 오답

					- C++ 11 부터 도입되는 보편적 레퍼런스를 사용하면 위 문제를 해결할 수 있음



		- 보편적 레퍼런스 Universal reference
			- wrapper 문제의 해결
				- wrapper 의 인자로 T&& 를 받아버리면 해결됨. 즉

						template <typename T>
						void wrapper(T&& u)
						{
							g(std::forward<T>(u)); -> std::forward는 뒤에서 설명
						}

					로 함수를 만들면 T에 대한 좌측값, 우측값 레퍼런스 모두를 받을 수 있음

				- 단, 보편적 레퍼런스는 템플릿 타입에만 해당함. 즉,

						void func(int&& n);

					은 우측값 int 만 받을 수 있고, 좌측값은 받을 수 없음

						template <typename T>
						void func(T&& n);

					과 같이 템플릿 타입에 대한 우측값 레퍼런스만 좌측값, 우측값을 모두 받을 수 있음

				- 보편적 레퍼런스로 받은 인자에 대한 타입 추론은 레퍼런스 겹침 규칙을 따름


		- 레퍼런스 겹침 규직 reference collapsing rule
			- 우측값 레퍼런스 -> 우측값 레퍼런스 = 우측값 레퍼런스
			- 그 외에는 전부 좌측값 레퍼런스임
			- 쉽게 생각하면 & = 1, && = 0 으로 두고 OR 연산을 한다고 보면 됨

			- 예시 해석
				typedef int& l_ref;
				typedef int&& r_ref;

				l_ref& r1;
				-> 1 OR 1 = 1 
				-> 좌측값

				l_ref&& r2;
				-> 1 OR 0 = 1 
				-> 좌측값

				r_ref& r3;
				-> 0 OR 1 = 1
				-> 좌측값

				r_ref&& r4;
				-> 0 OR 0 = 0
				-> 우측값

			- 예제 코드에서 (A a, const A ca)
				- wrapper(a) -> A&로 추론
				- wrapper(ca) -> const A&로 추론
				- wrapper(A()) -> A로 추론
				- 이렇게 각각 추론된 인자 u를 g() 함수에 넘겨주어야 함
					- u는 어떠한 경우에서도 좌측값임(이름이 있음)
					- 따라서 그냥 g(u)를 할 시 우측값으로 받은 인자도 좌측값으로 오버로딩된 g()를 호출함
					- 이때 g(std::move(u))도 사용할 수 없음. 좌측값이 인자로 들어와도 전부 우측값으로 오버로딩된 g()를 호출하기 때문
						-> 이때 std::forward 를 이용해야함


		- std::forward
			- std::forward는 우측값 레퍼런스만 move를 적용한 것 처럼 동작함
			- 위 예제코드의 g(T&& u) 에서 함수 호출시 std::forward<T>(u) 로 인자를 넘겨주는 것을 볼 수 있음

			- std::forward의 원형은 아래와 같음(MSVC)

					_EXPORT_STD template <class _Ty>
					_NODISCARD _MSVC_INTRINSIC constexpr _Ty&& forward(remove_reference_t<_Ty>& _Arg) noexcept {
						return static_cast<_Ty&&>(_Arg);
					}

				※ remove_reference<T> : T 타입의 레퍼런스를 지움

			- 위를 기준으로 g(std::forward<T>(U)); 를 보면

				1) A&의 경우

						A&&& forward(remove_reference<A&>& _Arg) {
							return static_cast<A&&&>(_Arg);
						}

					로 템플릿 인스턴스화 되고, 레퍼런스 겹침 규칙에 따라 A& 를 리턴함.

				2) A&& 의 경우
					
						A&&&& forward(remove_reference<A&&>& _Arg_) {
							return static_cast<A&&&&>(_Arg);
						}
					
					로 템플릿 인스턴스화 되고, 레퍼런스 겹침 규칙에 따라 A&& 를 리턴함.

				3) A 의 경우

						A&& forward(remove_reference<A>& _Arg) {
							return static_cast<A&&>(_Arg);
						}

					로 템플릿 인스턴스화 되고, A&&를 리턴함.

			- forward 의 인자는 왜 T&일까?
				-> forward 의 인자로 우측값 그 자체가 올 이유가 없음
					-> 위에서 T&&로 받아온 u도 그 자체는 좌측값임! 이 개념이 많이 헷갈리는 경우가 잦음

				-> 실제 코드에는 T&&로 오버로딩 된 버전이 있는데

					_EXPORT_STD template <class _Ty>
					_NODISCARD _MSVC_INTRINSIC constexpr _Ty&& forward(remove_reference_t<_Ty>&& _Arg) noexcept {
						static_assert(!is_lvalue_reference_v<_Ty>, "bad forward call");
						return static_cast<_Ty&&>(_Arg);
					}

					잘못된 forward 라고 assert 시키고 그냥 받은걸 우측값으로 다시 캐스팅해서 리턴해줌

	*/




}