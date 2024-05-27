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
#include <iostream>
#include <utility>
#include <iomanip>
#include <vector>
#include <string>

class A
{
public:
	A() { std::cout << "일반 생성자" << std::endl; }
	A(const A& a) { std::cout << "복사 생성자" << std::endl; }
	A(A&& a) { std::cout << "이동 생성자" << std::endl; }
};

int main()
{
	A a;

	std::cout << "------------" << std::endl;
	A b(a);

	std::cout << "------------" << std::endl;
	A c(std::move(a));

	/*
		- output : 
			일반 생성자
			------------
			복사 생성자
			------------
			이동 생성자
	*/

	/*
		- std::move 와 move semantics
			- std::move : <utility> 헤더에 정의된 함수로 좌측값을 우측값으로 형변환해줌
			- std::move 단독으로는 이동같은게 수행되지 않음!!! 인자로 받은 객체를 우측값으로 타입 변환해주는 역할만 함

			- 위 코드
				- A a : 일반 생성자가 정상적으로 호출
				- A b(a) : a가 좌측값 이므로 복사 생성자가 호출
				- A c(std::move(a)) : std::move 를 이용해 a를 우측값으로 바꾸어 주었으므로 이동 생성자가 호출
	*/

	/*  cppreference 코드 추가 : move 된 이후 원래의 객체는 어떻게?  */
	
	std::string str = "Salut";
	std::vector<std::string> v;

	// uses the push_back(const T&) overload, which means we'll incur the const of copying str
	// push_back(const T&) 버전의 오버로드 함수를 사용함. 즉, str 복사에 따른 비용을 초래함
	v.push_back(str);
	std::cout << "After copy, str is " << std::quoted(str) << '\n';		// std::quoted : 사용자 지정의 구분자와 이스케이프 문자를 이용해 문자열을 읽거나 씀 (기본 구분자는 "", 이스케이프는 \)

	// uses the rvalue reference push_back(T&&) overload, which means no strings will be copied.
	// instead, the contents of str will be moved into the vector. 
	// This is less expensive, but also means str might now be empty.
	// 
	// 우측값 레퍼런스를 이용한 push_back(T&&) 버전의 오버로드 함수를 이용함. 즉, 어떠한 문자열도 복사되지 않음
	// 대신, str의 내용들은 vector 안으로 이동됨
	// 이것은 비용이 덜 들지만, str은 이제 비어있을 것임
	v.push_back(std::move(str));
	std::cout << "After move, str is " << std::quoted(str) << '\n';

	std::cout << "The contents of the vector are {" << std::quoted(v[0]) << ", " << std::quoted(v[1]) << "}\n";
	
	/*
		- output :
			After copy, str is "Salut"
			After move, str is ""
			The contents of the vector are {"Salut", "Salut"}
			
			-> 이동이 수행되면 원래 객체는 아무것도 들고있지 않음을 확인 가능함
	*/

}