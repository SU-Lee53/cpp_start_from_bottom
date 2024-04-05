/*

	04.05 ~ 06 std::string, 상속, 오버라이딩, protected

*/

// 표준 string 클래스 std::string

#include <iostream>
#include <string>
#include <tchar.h>

int main()
{
	//	std::string s = "abc";
	//	std::string t = "def";
	//	std::string s2 = s;
	//	
	//	std::cout << s << " 의 길이 : " << s.length() << std::endl;
	//	std::cout << s << " 뒤에 " << t << " 를 붙이면 : " << s + t << std::endl;
	//	
	//	if (s == s2)
	//		std::cout << s << " 와 " << s2 << " 는 같다 " << std::endl;
	//	if (s != t)
	//		std::cout << s << " 와 " << t << " 는 다르다 " << std::endl;

	/*
		output
		abc 의 길이 : 3
		abc 뒤에 def 를 붙이면 : abcdef
		abc 와 abc 는 같다
		abc 와 def 는 다르다
	*/


	/*
		- std::string
			- C++의 문자열 클래스.
			- 기본적으로 <string> 헤더안에는 basic_string과 char_traits 가 구현되어있음
				- char_traits: 기본적인 문자/문자열 연산을 제공
				- basic_string: 가변적이고 다양한 문자열 조작 기능을 제공
				-> 기본적으로 위처럼 std::string을 생성하면 std::basic_string이 생성되고 헤더안에 typedef로 되어있음
			- 위처럼 기본적인 std::string은 std::basic_string<char>을 생성하고 다른 종류의 문자열도 지원함(기본 char는 ANSI)
				- std::wstring		->		std::basic_string<wchar_t>(유니코드)
				- std::u8string		->		std::basic_string<char8_t>
				- std::u16string	->		std::basic_string<char16_t>
				- std::u32string	->		std::basic_string<char32_t>
				- 전부 같은 템플릿으로 되어있어 모든 멤버 함수들은 동일함
				- 직접 해보니까 TCHAR등의 인코딩도 만들수 있음
				- 추가적으로 C++의 메모리 할당자인 PMR을 이용한 std::pmr::string 들이 있으며 이부분은 일단 넘어감
			- 기존의 strcmp, strlen, strcat 등을 이용해야했던 C의 문자열과 다르게 기본적인 기능들이 멤버 함수로 제공됨 https://en.cppreference.com/w/cpp/string/basic_string
				- length(), insert(), erase(), replace() 등등의 다양한 멤버 함수들이 기본 제공됨
				- 특히 strcmp, strcat 등의 기능을 연산자로 가능하다는 점이 눈에 띄는 부분이라고 생각됨(비교, 대소비교 둘다 연산자로 가능)
				- 전체 기능들은 후에 STL 공부할때 cppreference를 파면서 함께 정리
	*/

	// soen.kr에 설명된 다양한 string 생성자들(이거 말고도 새로운 표준들에서 더 많이 추가됨)

	std::string s1("test");								// string(const char *s) 널 종료 문자열로부터 생성하는 변환 생성자
	std::string s2(s1);									// string(const string& str, int pos = 0, int num = npos) 복사 생성자
	std::string s3;										// string() 기본 생성자
	std::string s4(32, 'S');							// string(size_t n, char c) c를 n개 채움
	std::string s5("very nice day", 8);					// string(const cchar* s, size_t n) 널 종료 문자열로부터 생성하되 n길이 확보
	const char* str = "abcdefghijllmnopqrstuvwxyz";		
	std::string s6(str + 5, str + 10);					// template<It> string(It begin, It end) begin ~ end 사이의 문자로 구성된 문자열 생성

	std::cout << "s1 = " << s1 << std::endl;	// s1 = test
	std::cout << "s2 = " << s2 << std::endl;	// s2 = test
	std::cout << "s3 = " << s3 << std::endl;	// s3 =
	std::cout << "s4 = " << s4 << std::endl;	// s4 = SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
	std::cout << "s5 = " << s5 << std::endl;	// s5 = very nic
	std::cout << "s6 = " << s6 << std::endl;	// s6 = fghij

		
		



	return 0;
}