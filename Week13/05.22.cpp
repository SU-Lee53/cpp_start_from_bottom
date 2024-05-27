/*
	05.22 12 - 1 우측값 레퍼런스와 이동 생성자
*/

// 본문 내용은 C++ 11 부터 추가된 내용으로 이전 버전에서는 작동하지 않음

/*  복사 생략 Copy Elision  */
//	#include <iostream>
//	
//	class A
//	{
//	public:
//		A(int data) : _data(data) { std::cout << "일반 생성자 호출" << std::endl; }
//	
//		A(const A& a) : _data(a._data) { std::cout << "복사 생성자 호출" << std::endl; }
//	
//	private:
//		int _data;
//	};
//	
//	int main()
//	{
//		A a(1);	// 일반 생성자 호출
//		A b(a);	// 복사 생성자 호출
//	
//		A c(A(2));	// 일반 생성자 호출
//	
//		/*
//			- 복사 생략 Copy elision
//				- 위 코드의 경우
//					- A a(1) : 일반 생성자가 정상적으로 호출되어 생성됨
//					- A b(a) : 복사 생성자가 정상적으로 호출되어 생성됨
//					- A c(A(2)) 의 경우는?
//						- 예상 : A(2)가 일반 생성자로 호출되어 생성되고 생성된 객체로 복사 생성자가 호출되어 c가 생성
//						- 결과 : 일반 생성자 한번으로 호출
//							-> 이것이 복사 생략이 일어나는 경우
//	
//				- 복사 생략
//					- 위 코드의 c를 보면
//						- 굳이 A(2)의 임시객체를 만들어 복사 생성할 필요가 없음
//							-> 어차피 A(2)로 c를 만들꺼라면 c 를 A(2)로 만들어진 객체로 바로 해버리는것이랑 같기 때문
//	
//					- 컴파일러는 이런 경우를 보면 복사 생성을 하지 않고 알아서 만들어진 A(2) 자체를 c로 만들어 버림
//						-> 이렇게 복사를 생략해버리는 것이 "복사 생략"(Copy elision) 임
//					
//					- 컴파일러가 복사 생략을 하는 경우
//						-> (함수의 인자가 아닌) 함수 내부에서 생성된 객체를 그대로 리턴할 때
//						-> 이 외에도 여러 경우가 있음. 다만 "반드시 복사 생략을 해라" 가 아닌 "할수도 있다" 정도
//							-> https://en.cppreference.com/w/cpp/language/copy_elision 의 Non-mandatory copy/move(since C++11) elision 을 참고
//	
//					- C++ 17 부터는 일부 경우 반드시 복사 생략을 수행 https://en.cppreference.com/w/cpp/language/copy_elision 
//						-> 링크한 레퍼런스의 Prvalue semantics ("guaranteed copy elision") 를 참고
//		*/
//	
//	}

/*  MyString 의 복사 생략  */
//
//	// 이전에 만든 MyString의 일부분만 재구현하여 복사 생략이 일어나는 경우를 알아보자
//	#include <iostream>
//	#include <cstring>
//	
//	class MyString
//	{
//	public:
//		MyString();
//	
//		// 문자열로부터 생성
//		MyString(const char* str);
//	
//		// 복사 생성자
//		MyString(const MyString& str);
//	
//		void reserve(int size);
//		int length() const { return string_length; };
//		void print();
//		void println();
//		
//		MyString operator+(const MyString& s);
//	
//		~MyString() { delete[] string_content; }
//	
//	private:
//		char* string_content;
//		int string_length;
//		int memory_capacity;
//	};
//	
//	MyString::MyString()
//	{
//		std::cout << "생성자 호출" << std::endl;
//		string_length = 0;
//		memory_capacity = 0;
//		string_content = nullptr;
//	}
//	
//	MyString::MyString(const char* str)
//	{
//		std::cout << "생성자 호출" << std::endl;
//		string_length = strlen(str);
//		memory_capacity = string_length;
//		string_content = new char[string_length];
//	
//		for (int i = 0; i < string_length; i++) string_content[i] = str[i];
//	}
//	
//	MyString::MyString(const MyString& str)
//	{
//		std::cout << "복사 생성자 호출" << std::endl;
//		string_length = str.string_length;
//		memory_capacity = str.memory_capacity;
//		string_content = new char[string_length];
//	
//		for (int i = 0; i < string_length; i++) string_content[i] = str.string_content[i];
//	}
//	
//	void MyString::reserve(int size)
//	{
//		if (size > memory_capacity)
//		{
//			char* prev_string_content = string_content;
//			
//			string_content = new char[size];
//			memory_capacity = size;
//	
//			for (int i = 0; i < string_length; i++)
//				string_content[i] = prev_string_content[i];
//			
//			if (prev_string_content != nullptr) delete[] prev_string_content;
//		}
//	}
//	
//	MyString MyString::operator+(const MyString& s)
//	{
//		MyString str;
//		str.reserve(string_length + s.string_length);
//		for (int i = 0; i < string_length; i++)
//		{
//			str.string_content[i] = string_content[i];
//		}
//		for (int i = 0; i < s.string_length; i++)
//		{
//			str.string_content[string_length + i] = s.string_content[i];
//		}
//		str.string_length = string_length + s.string_length;
//		return str;
//	}
//	
//	void MyString::print()
//	{
//		for (int i = 0; i != string_length; i++) std::cout << string_content[i];
//	}
//	
//	void MyString::println()
//	{
//		for (int i = 0; i != string_length; i++) std::cout << string_content[i];
//	
//		std::cout << std::endl;
//	}
//	
//	int main()
//	{
//		MyString str1("abc");
//		MyString str2("def");
//		std::cout << "----------------" << std::endl;
//		MyString str3 = str1 + str2;
//		str3.println();
//	
//		/*
//			- output:
//				생성자 호출
//				생성자 호출
//				----------------
//				생성자 호출
//				abcdef
//			
//			-> 모두의 코드 원본은 복사 생성자까지 호출되지만 여기서는 생략됨(MSVC C++14)
//			-> clang 으로 해봐도 복사 생략됨(C++11)
//		*/
//	
//		/*
//			- MyString 과 복사생략
//				- 일단 모두의 코드 본문처럼 복사 생략이 일어나지 않았다고 가정하고 서술
//	
//				- 위 코드에서
//					- MyString str3 = str1 + str2; 를 수행할때 operator+ 는 합쳐진 문자열을 생성해서 리턴함
//	
//						str1 + str2 가 리턴한 임시 객체 --------> "abcdef" -> 메모리 상에서 지움
//						                                             ↓
//						                                           복사!
//																	 ↓
//						str3 의 복사 생성자 --------------------> 빈 공간 할당 ----> "abcdef"
//	
//					- 복사 생성자가 str1 + str2 의 결과를 복사 받아 str3을 생성
//					- 쓸데 없는 복사가 2번 일어남
//						-> 리턴된 문자열 객체가 str3의 복사 생성자로 복사
//						-> 복사 생성자에서 복사된 문자열을 복사
//	
//					- str1 + str2 의 크기가 크면 클수록 매우 비효율적
//					- 그냥 str1 + str2 가 복사없이 바로 str3 이 되도록 하는 것이 효율적임 -> 복사 생성의 이유
//		
//		*/
//	
//	}

/*  좌측값(lvalue) 과 우측값(rvalue)  */
//	#include <iostream>
//	
//	int& func1(int& a) { return a; }
//	int func2(int b) { return b; }
//	
//	int main()
//	{
//		int a = 3;
//		func1(a) = 4;
//		std::cout << &func1(a) << std::endl;
//		std::cout << a << std::endl;	// 4
//	
//		int b = 2;
//		a = func2(b);
//		//	func2(b) = 5;	// C2106 '=': 왼쪽 피연산자는 l-value이어야 합니다
//		//	std::cout << &func2(b) << std::endl;	// C2102 '&'에 l-value가 있어야 합니다
//	
//		/*
//			- 좌측값과 우측값 https://en.cppreference.com/w/cpp/language/value_category
//				- 모든 C++의 표현식은 두가지 카테고리로 구분할 수 있음 
//				- 실제 정의는 위 레퍼런스에서 보듯이 매우 복잡하지만 간단하게 아래처럼 이해하면 됨
//					- 좌측값(lvalue) : 주소값을 취할 수 있는 값
//					- 우측값(rvalue) : 주소값을 취할 수 없는 값
//	
//				- 좌측값의 경우 어떠한 표현식의 왼쪽 오른쪽 모두 올 수 있음(왼쪽만 되서 좌측값이 아님)
//				- 우측값의 경우에는 반드시 표현식의 오른쪽에만 올 수 있음
//	
//				- 예시
//					- int a = 3;
//						-> 'a' : 메모리 상에 존재하는 변수이므로 & 연산자로 주솟값을 취할 수 있음 -> 좌측값
//						-> '3' : 위 표현식을 위해 잠깐 존재하는 값으로 식이 연산되고 나면 사라짐. 즉, '3'은 실체가 없음 -> 우측값
//	
//					- int& l_a = a;
//						-> a가 좌측값 이므로 l_a 는 좌측값에 대한 레퍼런스
//						-> & 하나로 정의하는 레퍼런스를 좌측값 레퍼런스(lvalue reference) 라고 부름
//	
//					- int& r_b = 3;
//						-> 3이 우측값 이므로 &으로 좌측값 레퍼런스를 만들 수 없음
//				
//				- 위 예제 코드
//					- func1() 은 int& 좌측값 레퍼런스를 리턴
//					- func2() 는 일반적인 int 를 리턴
//	
//					- func1(a) = 4;
//						- func1(a) 가 int& 를 리턴하므로 a의 값이 4로 바뀜 -> 문제없음
//	
//					- a = func2(b);
//						- func2(b) 가 리턴한 int 값은 문장 실행이 끝나면 사라짐 
//						- 즉 func2(b) 는 우측값
//	
//					- func2(b) = 5;
//						- 위 func1의 경우와는 반대로 오류가 발생
//						- func2(b) 가 우측값이므로 문장의 왼쪽에 올 수 없음
//	
//					- std::cout << &func2(b) << std::endl;
//						- 마찬가지로 func2(b) 가 우측값이므로 & 연산자로 주소값을 취할 수 없음
//				
//				- const 레퍼런스는 우측값을 참조할 수 있음. const 로 존재하는 객체의 값만 참조하고 변경할 수는 없기 때문
//		*/
//	
//	}

/*  우측값 레퍼런스와 이동 생성자  */
//	#include <iostream>
//	#include <utility>
//	
//	class foo
//	{
//	public:
//		// 기본 생성자
//		foo(int n) : _data(n) { std::cout << "일반 생성자" << std::endl; }
//	
//		// 복사 생성자
//		foo(const foo& f) : _data(f._data) { std::cout << "복사 생성자" << std::endl; }
//	
//		// 이동 생성자
//		foo(foo&& f) noexcept;
//	
//		foo operator+(const foo& f) { return _data + f._data; }
//	
//		friend std::ostream& operator<<(std::ostream&, const foo&);
//	
//	private:
//		int _data;
//	
//	};
//	
//	foo::foo(foo&& f) noexcept
//	{
//		std::cout << "이동 생성자" << std::endl;
//		_data = f._data;
//	}
//	
//	std::ostream& operator<<(std::ostream& o, const foo& f)
//	{
//		o << f._data;
//		return o;
//	}
//	
//	int main()
//	{
//		foo a(1);
//		foo b(2);
//	
//		//	foo& rvalue_ref = a + b;	// E0461 비const 참조에 대한 초기 값은 lvalue여야 합니다
//		//	foo&& rvalue_ref = a;	// E1768 rvalue 참조를 lvalue에 바인딩할 수 없습니다
//		foo&& rvalue_ref = a + b;	// 우측값 레퍼런스
//		std::cout << &rvalue_ref << std::endl;	// rvalue_ref 는 좌측값임
//		std::cout << rvalue_ref << std::endl;
//	
//		std::cout << "------------------" << std::endl;
//		foo c = std::move(a + b);
//		std::cout << c << std::endl;
//	
//		/*
//			- output : 
//				일반 생성자
//				일반 생성자
//				일반 생성자
//				000000DBD875FA54
//				3
//				------------------
//				일반 생성자
//				이동 생성자
//				3
//		*/
//		
//		/*
//			- 우측값 레퍼런스
//				- 기존의 좌측값 레퍼런스와 달리 &&으로 선언하고 사용함
//				- 우측값 레퍼런스는 우측값을 참조하지만 엄연히 좌측값임
//					-> 위 코드에서
//	
//						std::cout << &rvalue_ref << std::endl;	
//	
//						가 문제없이 작동되는 이유임
//	
//				- 우측값에 대한 레퍼런스 이므로 당연히 좌측값은 참조하지 못함
//				- 참조하는 임시 객체를 소멸되지 않도록 붙들고 있음
//					-> 위 코드에서
//						
//						foo&& rvalue_ref = a + b;
//	
//						로 우측값 레퍼런스가 선언되므로 a + b 의 결과로 리턴된 임시객체는 소멸되지 않음 
//	
//					-> 따라서
//	
//						std::cout << rvalue_ref << std::endl;
//	
//						이 코드가 문제없이 작동됨
//	
//	
//			- 이동 생성자
//				- 우측값 레퍼런스를 받아 객체를 생성하는 생성자
//				- 원본 임시 객체의 경우 사용되고 나면 소멸되므로 몇가지 신경쓸것들이 있음
//					-> 아래에서 MyString 문제를 해결하면서 설명
//	
//		*/
//	
//	}

/*  MyString 문제의 해결, 이동 생성자 사용시의 주의할 점  */
/*
	- MyString 문제의 해결
		- 문제 : 기존의 str3 = str1 + str2 수행시 불필요한 복사가 2번 일어남
		- 해결
			-> 기존

				str1 + str2 가 리턴한 임시 객체 --------> "abcdef" -> 메모리 상에서 지움
						                                      ↓
						                                    복사!
				                                              ↓
				str3 의 복사 생성자 --------------------> 빈 공간 할당 ----> "abcdef"

			-> 해결
			                                       1) 기존 연결을 끊어버림(소멸자 호출시 문자열(string_content)을 delete 하지 않도록)
				str1 + str2 가 리턴한 임시 객체 ---X---> "abcdef" 
															 ↑
															 ↑	2) 문자열 전체 복사 없이 str3이 임시 객체의 문자열(string_content)을 가리키도록 함
															 ↑
				str3 의 이동 생성자 --------------------------

				- 위는 복사 생성자에서는 불가능한 방법임
					-> 복사 생성자는 인자를 const MyString& 으로 받으므로 임시 객체의 string_content 값을 수정할 수 없기 때문
*/

#include <iostream>
#include <cstring>
#include <utility>
#include <vector>

class MyString
{
public:
	MyString();

	// 문자열로부터 생성
	MyString(const char* str);

	// 복사 생성자
	MyString(const MyString& str);

	// 이동 생성자
	MyString(MyString&& str) noexcept;

	void reserve(int size);
	int length() const { return string_length; };
	void print();
	void println();

	MyString operator+(const MyString& s);

	~MyString();

private:
	char* string_content;
	int string_length;
	int memory_capacity;
};

MyString::MyString()
{
	std::cout << "생성자 호출" << std::endl;
	string_length = 0;
	memory_capacity = 0;
	string_content = nullptr;
}

MyString::MyString(const char* str)
{
	std::cout << "생성자 호출" << std::endl;
	string_length = strlen(str);
	memory_capacity = string_length;
	string_content = new char[string_length];

	for (int i = 0; i < string_length; i++) string_content[i] = str[i];
}

MyString::MyString(const MyString& str)
{
	std::cout << "복사 생성자 호출" << std::endl;
	string_length = str.string_length;
	memory_capacity = str.memory_capacity;
	string_content = new char[string_length];

	for (int i = 0; i < string_length; i++) string_content[i] = str.string_content[i];
}

MyString::MyString(MyString&& str) noexcept
{
	std::cout << "이동 생성자 호출" << std::endl;
	string_length = str.string_length;
	memory_capacity = str.memory_capacity;
	string_content = str.string_content;

	// 임시 객체 소멸시 메모리 해제를 못하도록 연결을 끊음
	str.string_content = nullptr;
}

MyString::~MyString()
{
	if (string_content) delete[] string_content;
}

void MyString::reserve(int size)
{
	if (size > memory_capacity)
	{
		char* prev_string_content = string_content;

		string_content = new char[size];
		memory_capacity = size;

		for (int i = 0; i < string_length; i++)
			string_content[i] = prev_string_content[i];

		if (prev_string_content != nullptr) delete[] prev_string_content;
	}
}

MyString MyString::operator+(const MyString& s)
{
	MyString str;
	str.reserve(string_length + s.string_length);
	for (int i = 0; i < string_length; i++)
	{
		str.string_content[i] = string_content[i];
	}
	for (int i = 0; i < s.string_length; i++)
	{
		str.string_content[string_length + i] = s.string_content[i];
	}
	str.string_length = string_length + s.string_length;
	return str;
}

void MyString::print()
{
	for (int i = 0; i != string_length; i++) std::cout << string_content[i];
}

void MyString::println()
{
	for (int i = 0; i != string_length; i++) std::cout << string_content[i];

	std::cout << std::endl;
}

int main()
{
	/*  MyString 문제의 해결  */
	//	{
	//		MyString str1("abc");
	//		MyString str2("def");
	//		std::cout << "----------------" << std::endl;
	//		MyString str3 = std::move(str1 + str2);
	//		str3.println();
	//	
	//		/*
	//			- output :
	//				생성자 호출
	//				생성자 호출
	//				----------------
	//				생성자 호출
	//				abcdef
	//	
	//				-> 이젠 이동 생성자도 그냥 생략해서 최적화시키는 모양이다... https://en.cppreference.com/w/cpp/language/move_constructor 의 Explanation 을 보면
	//				When the initializer is a prvalue, the move constructor call is often optimized out(until C++17)never made(since C++17), see copy elision.
	//				-> str1 + str2 의 결과가 prvalue 이므로 생략되는 모양임. xvalue 가 아닌 우측값을 이동생성 시킬려면 std::move를 사용해야 되는듯 함
	//	
	//			- std::move 를 사용한 output:
	//				생성자 호출
	//				생성자 호출
	//				----------------
	//				생성자 호출
	//				이동 생성자 호출
	//				abcdef
	//	
	//				-> 이제야 모두의 코드 원문과 똑같은 결과가 나옴
	//	
	//				MSVC C++14를 사용함
	//		*/
	//	}

	/*  이동 생성자 사용시의 주의할 점 - noexcept  */
	{
		MyString s("abc");
		std::vector<MyString> vec;
		vec.resize(0);

		std::cout << "첫 번째 추가 ---" << std::endl;
		vec.push_back(s);
		std::cout << std::endl;

		std::cout << "두 번째 추가 ---" << std::endl;
		vec.push_back(s);
		std::cout << std::endl;

		std::cout << "세 번째 추가 ---" << std::endl;
		vec.push_back(s);

		/*
			- 초기 output : 
				생성자 호출
				첫 번째 추가 ---
				복사 생성자 호출
				
				두 번째 추가 ---
				복사 생성자 호출
				복사 생성자 호출
				
				세 번째 추가 ---
				복사 생성자 호출
				복사 생성자 호출
				복사 생성자 호출
			
			- 이동 생성자에 noexcept 추가 후 output :
				생성자 호출
				첫 번째 추가 ---
				복사 생성자 호출
				
				두 번째 추가 ---
				복사 생성자 호출
				이동 생성자 호출
				
				세 번째 추가 ---
				복사 생성자 호출
				이동 생성자 호출
				이동 생성자 호출
		*/

		/*
			- 이동 생성자 사용시 주의할 점
				- std::vector 등의 STL 컨테이너에 사용할 클래스의 이동 생성자는 반드시 noexcept 로 명시해주어야 함
				- 왜? : vector 를 예시로 보자
					-> 만약에 vector의 메모리가 가득 차서 새로운 공간을 할당할 때 메모리를 할당한 수에 기존의 원소를 옮김
					-> 옮기는 과정에서 예외가 발생한다고 쳐보자

						- 복사 생성자를 사용하는 경우
							-> 그냥 할당시켜놓은 메모리를 소멸시키고 사용자에게 예외를 던짐
							-> 할당한 메모리를 소멸시키면서 복사된 원소들도 소멸되므로 자원이 낭비되지 않음
							-> 복사된 원본은 남아있으므로 예외를 던지고 다시 원래대로 돌아가기만 하면 됨

						- 이동 생성자를 사용하는 경우
							-> 원소가 통째로 이동되어버렸기 때문에 원본이 남아있지 않음
							-> 새로 할당한 메모리를 소멸시키면 원소들도 통째로 날아가므로 함부로 소멸시킬 수 없음

					-> 이러한 이유로 vector는 이동 생성자에서 예외가 발생하면 이를 제대로 처리할 수 없음

				- 위 내용은 vector의 경우이지만 STL의 컨테이너는 다 이럼
				- 해결방안 : 이동 생성자에 noexcept를 명시
					-> 이동 생성자가 예외를 던지지 않으므로 안심하고 이동시킬 수 있음
					
				- <utility>에 std::move_if_noexcept() 라는 함수로 STL 컨테이너들이 이동을 수행함
					-> noexcept 일때만 이동을 수행하는 함수 -> noexcept가 아니면 복사를 수행
				
		*/
	}

	return 0;
}
