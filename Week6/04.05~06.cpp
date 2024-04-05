/*

	04.05 ~ 06 std::string, 상속, 오버라이딩, protected

*/

// 표준 string 클래스 std::string
#include <iostream>
#include <string>

int main()
{
	std::string s = "abcde";
	std::cout << s << std::endl;
	/*
		output
		abcde
	*/

	/*
		- std::string
			- C++의 문자열 클래스.
			- 기본적으로 <string> 헤더안에는 basic_string과 char_traits 가 구현되어있음
				- char_traits: 기본적인 문자/문자열 연산을 제공
				- basic_string: 가변적이고 다약한 문자열 조작 기능을 제공
				-> 기본적으로 위처럼 std::string을 생성하면 std::basic_string이 생성되고 헤더안에 typedef로 되어있음
			- 위처럼 기본적인 std::string은 std::basic_string<char>을 생성하고 다른 포멧의 문자열도 지원함
				- std::wstring		->		std::basic_string<wchar_t>
				- 
	
	*/

	return 0;
}