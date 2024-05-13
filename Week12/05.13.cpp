/*
	05.13 STL4 - 문자열
*/

/*  basic_string  */
/*
	- basic_string
		- 이전까지 사용해온 std::string 은 사실 basic_string 이라는 클래스 템플릿의 인스턴스화 버전임
			-> <string> 헤더에 보면 다음과 같이 선언됨

				using string = basic_string<char, char_traits<char>, allocator<char>>;

		- 실제 basic_string 은 <string> 안에서 다음과 같이 정의되어있음(libc++)
			
			template <class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
			class basic_string;

			- basic_string 은 CharT 타입의 객체들을 메모리에 연속적으로 저장하고 여러가지 문자열 연산들을 지원하는 클래스
			- 문자 인코딩 종류에 따라서 string도 여러 종류가 있음. 아래와 같음
				- std::string -> std::basic_string<char>
				- std::wstring -> std::basic_string<wchar_t>	: wchar_t의 크기는 윈도우는 2바이트 / 유닉스는 4바이트임 
				- std::u8string -> std::basic_string<char8_t>	: C++ 20 에서 추가된 string으로 char8_t는 1바이트 UTF-8 문자임
				- std::u16string -> std::basic_string<char16_t>	: char16_t는 2바이트 UTF-16 문자
				- std::u32string -> std::basic_string<char32_t> : char32_t는 4바이트 UTF-32 문자

			- Traits는 주어진 CharT 문자들에 대한 기본적인 문자열 연산들을 정의해놓은 클래스임
				-> 기본적인 문자열 연산 : 문자열 대소비교, 길이 측정 등..
				-> basic_string 의 문자열 연산들은 전부다 Traits의 기본적인 문자열 연산들로 정의됨
					-> 이를 통해 "문자열을 어떻게 보관하는지" 와 "문자열들을 어떻게 연산하는지" 에 대한 로직을 분리시킬 수 있음
					-> 전자는 basic_string 이 하고 후자는 Traits에서 함
					-> 이로써 basic_string 의 사용에 있어 더 자유로워 지고 별도의 로직이 필요한 경우 Traits를 조금만 수정하면 됨

			- 가장 기본적인 std::string의 경우 std::char_traits<char>를 사용함

			- 참고로 MSVC의 basic_string 은 <xstring> 안에서 다음과 같이 정의됨. char_traits도 <xstring>에 있음
				_EXPORT_STD template <class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>>
				class basic_string { // null-terminated transparent array of elements

*/

/*  Traits의 활용  */
//	#include <cctype>
//	#include <iostream>
//	#include <string>
//	
//	// 문자열 비교시 숫자들의 순위가 가장 낮도록 하는 char_traits
//	// 원래는 ASCII 테이블 기준으로 문자를 비교하므로 숫자가 알파벳보다 순위가 더 높은것이 정상
//	struct my_char_traits : public std::char_traits<char>
//	{
//		static int get_real_rank(char c)
//		{
//			// 숫자면 순위를 엄청 떨어뜨린다
//			if (isdigit(c))
//				return c + 256;
//			else
//				return c;
//		}
//	
//		static bool lt(char c1, char c2)
//		{
//			return get_real_rank(c1) < get_real_rank(c2);
//		}
//	
//		static int compare(const char* s1, const char* s2, size_t n)
//		{
//			while (n-- != 0)
//			{
//				if (get_real_rank(*s1) < get_real_rank(*s2)) return -1;
//				if (get_real_rank(*s1) > get_real_rank(*s2)) return 1;
//				++s1;
//				++s2;
//			}
//			return 0;
//		}
//	};
//	
//	int main()
//	{
//		std::basic_string<char, my_char_traits> my_s1 = "1a";
//		std::basic_string<char, my_char_traits> my_s2 = "a1";
//	
//		std::cout << "s1 : 1a" << std::endl;
//		std::cout << "s2 : a1" << std::endl;
//		std::cout << "s1 < s2 ?" << std::endl;
//	
//		std::cout << "숫자의 우선순위가 더 낮은 문자열 : " << std::boolalpha << (my_s1 < my_s2) << std::endl;
//	
//		std::string s1 = "1a";
//		std::string s2 = "a1";
//	
//		std::cout << "일반 문자열 : " << std::boolalpha << (s1 < s2) << std::endl;
//	
//		/*
//			- output:
//				s1 : 1a
//				s2 : a1
//				s1 < s2 ?
//				숫자의 우선순위가 더 낮은 문자열 : false
//				일반 문자열 : true
//		*/
//	
//		/*
//			- traits의 활용
//				- 기본적으로 basic_string 에 들어갈 traits 에는 char_traits 에 있는 모든 멤버함수들이 구현된 클래스가 필요함
//				- 이를 가장 간편하게 만들려면 그냥 char_traits를 상속받는 클래스를 만들고 필요한 부분들만 다시 만들면 됨
//					-> char_traits의 멤버함수들은 https://en.cppreference.com/w/cpp/string/char_traits 참고. 생각보다 많지는 않음
//	
//				- 위 코드에서의 my_char_traits 는 char_traits의 lt, compare 함수를 오버로딩 하고있음
//					-> 숫자의 순위를 알파벳보다 떨어뜨리기 위한 get_real_rank 함수를 만들어 이용함
//					-> lt 함수는 less_then의 약자로 a < b 를 수행하여 결과를 리턴 https://en.cppreference.com/w/cpp/string/char_traits/cmp
//					-> compare 함수의 경우 (const char* s1, const char* s2, size_t n) 으로 인자를 받음
//						-> s1 > s2 인 경우 양수를 리턴
//						-> s1 < s2 인 경우 음수를 리턴
//						-> s1 == s2 인 경우 0을 리턴함
//						-> char* 의 경우 템플릿 인자로 받은 문자 인코딩 종류에 따라 달라짐
//	
//					-> 이처럼 char_traits를 상속받아 약간의 수정만 해주면 원하는 대로 문자열 연산을 커스텀할 수 있음
//		*/
//	}

/*  짧은 문자열 최적화 Short String Optimization(SSO)  */
#include <iostream>
#include <string>

// 이와 같이 new 를 전역 함수로 정의하면 모든 new 연산자를 오버로딩함
// 어떤 클래스의 new 연산자를 오버로딩 하려면 해당 클래스의 멤버함수로 정의해야함
void* operator new(std::size_t count)
{
	std::cout << count << "bytes 할당" << std::endl;
	return malloc(count);
}

int main()
{
	std::cout << "s1 생성 --- " << std::endl;
	std::string s1 = "this is a pretty long sentence!!!";
	std::cout << "s1 크기 : " << sizeof(s1) << std::endl;

	std::cout << "s2 생성 --- " << std::endl;
	std::string s2 = "short sentence";
	std::cout << "s2 크기 : " << sizeof(s2) << std::endl;

	/*
		- MSVC를 이용한 output
			s1 생성 ---
			16bytes 할당
			48bytes 할당
			s1 크기 : 40
			s2 생성 ---
			16bytes 할당
			s2 크기 : 40
		
		- libc++ STL과 clang 을 이용한 컴파일 결과
			s1 생성 ---
			48바이트 할당
			s1 크기 : 24
			s2 생성 ---
			s2 크기 : 24

		- 모두의 코드의 결과
			s1 생성 ---
			34 bytes 할당
			s1 크기 : 32
			s2 생성 ---
			s2 크기 : 32

		-> MSVC에서는 위 코드를 SSO 하여 저장하지 않음....
	*/

	/*
		- 짧은 문자열 최적화 Short String Optimization (SSO)
			- 일반적으로 메모리를 할당하는작업은 매우 김
			- 그러나 문자열의 경우 긴 문자열이 만들어지는 일은 드물고 거의 대부분 짧은 문자열들이 생성되고 소멸됨
			- 이를 매번 메모리를 할당하면서 생성하고 소멸하는 짓은 매우 비효율적임
			- 그러므로 짧은 길이의 문자열은 문자 저장을 위한 메모리를 할당하지 않고 객체 자체에 내장시킴 -> 이것이 SSO의 정의

			- 위 코드에서의 SSO
				- MSVC에서는 SSO를 하지 않았으므로 pass
				- libc++의 경우 
					-> s1은 new 연산자로 48바이트를 할당함
					-> s2는 new 연산자로 메모리 할당을 하지 않고 객체 내부에 바로 저장되어 별도의 출력이 나타나지 않음
					-> 그러나 s2는 s1처럼 sizeof()로 크기를 확인해보면 같은 사이즈를 가짐
						-> 메모리 공간 크기, 문자열 길이, 문자열을 저장할 포인터 등을 별도로 가짐
						-> 이에 따라 메모리 사용량은 약간 희생하였지만 성능 향상은 가져옴

			- MSVC도 SSO를 하긴 함. 그러나 위의 s2보다 더 짧아야함. 기준은 찾아봐도 잘 안나옴...
	*/
}