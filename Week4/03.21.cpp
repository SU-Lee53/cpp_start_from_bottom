
/*
	- 03.21 연산자 오버로딩 - 산술, 비교, 대입
*/

//	- 연산자 오버로딩

/*
	- 연산자 오버로딩
		- C++은 다음의 연산자들에 대해서 사용자 정의 연산자를 사용할 수 있음
			- 산술 연산자 (+, -, * 등) 
			- 축약형 연산자 (+=, -= 등)
			- 비교 연산자 (>=, == 등)
			- 논리 연산자 (&&, || 등)
			- 멤버 선택 연산자 (->, *(역참조) 등) 
			- 증감 연산자 (++, -- 등)
			- 배열 연산자[], 함수 호출 연산자()
			- cppreference의 operator overloading 에 따르면 (https://en.cppreference.com/w/cpp/language/operators)
					op - any of the following operators : 
					+ - * / % ^ & | ~ ! = < > += -= *= /= %= ^= &= |= << >> >>= <<= == != <= >= <=>(since C++20) && || ++ -- , ->* -> ( ) [ ]
					1) overloaded operator;					-> 위에 있는 연산자들
					2) user-defined conversion function;	-> 유저가 정의한 변환 함수
					3) allocation function;					-> new, new[]
					4) deallocation function;				-> delete, delete[]
					5) user-defined literal;				-> ""
					6) overloaded co_await operator for use in co_await expressions. -> 코루틴 관련된 것으로 자세한건 아직 잘 모르겠음
		
		- 이러한 기본 연산자들을 사용자가 직접 정의하는것이 연산자 오버로딩(operator overloading)이라고 부름
*/

// - 가장 기본적으로 이전의 MyString을 간단하게만 다시 구현하여 ==를 오버로딩 해보면...

//	#include <iostream>
//	
//	class MyString
//	{
//	public:
//		MyString(const char* str)
//		{
//			string_length = strlen(str);
//			memory_capacity = string_length;
//			string_content = new char[string_length];
//			memcpy(string_content, str, string_length);
//		}
//		~MyString() { delete[] string_content; }
//	
//		int compare(MyString& str);
//	
//		// 연산자 오버로딩의 선언 : (리턴타입) operator(연산자) (연산자가 받는 인자)
//		// 이 방법이 유일한 오버로딩 방법임
//		bool operator== (MyString& str);
//	
//		void println()
//		{
//			for (int i = 0; i < string_length; i++) std::cout << string_content[i];
//			std::cout << std::endl;
//		}
//	
//	private:
//		char* string_content;
//		int string_length;
//		int memory_capacity;
//	};
//	
//	int MyString::compare(MyString& str)
//	{
//		for (int i = 0; i < std::min(string_length, str.string_length); i++)
//		{
//			if (string_content[i] > str.string_content[i])
//				return 1;
//			else if (string_content[i] < str.string_content[i])
//				return -1;
//		}
//		
//		// 두 문자열이 같은 경우 0을 리턴해줌
//		if (string_length == str.string_length) return 0;
//		else if (string_length > str.string_length) return 1;
//		else return -1;
//	
//	}
//	
//	bool MyString::operator==(MyString& str)
//	{
//		// 기존의 compare를 그대로 활용가능함
//		return !compare(str);	// compare() 함수가 두 문자열이 같다면 0을 리턴하도록 만들었으므로 0 == false임을 이용하여 쉽게 활용됨
//	}
//	
//	int main()
//	{
//		MyString str1 = MyString("a word");
//		MyString str2 = "sentence";
//		MyString str3("sentence");
//	
//		if (str1 == str2)
//			std::cout << "str1 와 str2는 같다." << std::endl;
//		else
//			std::cout << "str1 와 str2는 다르다." << std::endl;
//	
//		if (str2 == str3)
//			std::cout << "str2 와 str3는 같다." << std::endl;
//		else	
//			std::cout << "str2 와 str3는 다르다." << std::endl;
//	
//		/*
//			output:
//			str1 와 str2는 다르다.
//			str2 와 str3는 같다.
//		*/
//	
//	}

// - 복소수(Complex number)를 이용하여 연산자 오버로딩 실습

#include <iostream>

class Complex
{

};