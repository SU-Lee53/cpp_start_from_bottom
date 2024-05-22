/*
	05.22 우측값 레퍼런스와 이동 생성자
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

/*  MyString 문제의 해결 : 우측값 레퍼런스와 이동 생성자  */