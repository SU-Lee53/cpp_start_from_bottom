
/*
	04.17 C++ 입출력 라이브러리 istream, ostream
*/

// !!!!!!! 아래 내용은 전부 MSVC 기준이고 다른 STL 구현체에선 다를수도 있음 !!!!!!!

// C++ 입출력 라이브러리의 구조, ios_base, ios

/*
	- C++ 입출력 라이브러리의 구조

							[ios_base]
								|
								|
							  [ios]
							   / \
							  /   \
							 /	   \
							/		\
					  [istream]	  [ostream]
						|	|		|	|
						|	|		|	|
						|   [iostream]	|
						|		|		|
					[ifstream]	|   [ofstream]
								|
							[fstream]

				※ 위 그림은 cppreference 의 그림 (https://en.cppreference.com/w/cpp/io)과 약간 다름. cppreference가 더 최신인것으로 보임
					
		- 위가 그림으로 나타낸 입출력 라이브러리의 구조로 아래는 모두의 코드의 설명
			- ios_base : C++의 모든 입출력 클래스의 기반 클래스. 많은 일은 하지않고 스트림의 입출력 형식 관련 데이터를 처리(실수형의 정밀도, 정수형 진수 표기 결정 등)
			- ios : 실제로 스트림 버퍼를 초기화(스트림 버퍼: 데이터를 내보내거나 받아들이기 전에 임시로 저장하는 곳), 현재 입출력 작업의 상태를 처리
		
		- istream 부터는 별도의 단락으로 설명

*/

// istream 클래스

//	#include <iostream>
//	#include <string>
//	
//	int main()
//	{
//		// istream 클래스
//	
//		//	{
//		//		std::string s;
//		//		while (true)
//		//		{
//		//			std::cin >> s;
//		//			std::cout << "word : " << s << std::endl;
//		//		}
//		//	
//		//		/*
//		//			output:
//		//			this is a long sentence
//		//			word : this
//		//			word : is
//		//			word : a
//		//			word : long
//		//			word : sentence
//		//			ABC DEF GHI
//		//			word : ABC
//		//			word : DEF
//		//			word : GHI
//		//		*/
//		//	
//		//		/*
//		//			- istream 클래스
//		//				- 실제로 입력을 수행하는 클래스: std::cin >> ;
//		//					- operator>> : istream 클래스에 오버로딩된 연산자
//		//						- istream 헤더파일을 까보면 operator>>가 모든 기본 타입들에 대하여 전부 오버로딩이 되어있기 때문에 "std::cin >>" 이 자유롭게 가능함
//		//						- 재미있는건 std::string은 오버로딩 되어있지 않은데 istream의 멤버가 아닌 외부 함수로 연산자 오버로딩 되어있음(참고로 <xstring> 헤더에 있음)
//		//							-> 만약 없으면 직접하면 됨: istream& operator>>(istream& in, std::string s){}
//		//							-> 실제 <xstring>에서는 이렇게 함:
//		//								_EXPORT_STD template <class _Elem, class _Traits, class _Alloc>
//		//								basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr, basic_string<_Elem, _Traits, _Alloc>& _Str)
//		//						- operator>>는 모든 공백문자(띄어쓰기, 엔터, 탭)을 입력시에 무시해버림
//		//							-> 위 코드도 공백이 있는 문자를 입력하면 전부 무시하고 한단어씩 분리해서 받고있음
//		//	
//		//	
//		//					- cin : istream의 객체중 하나. 이건 <iostream>에 정의되어있으므로 <istream>만 include하는것으로는 cin을 사용못함
//		//	
//		//		*/
//		//	}
//	
//		// istream::operator>> 사용시의 주의사항: 상태 플래그
//	
//		{
//			//	int t;
//			//	
//			//	// 문자열 입력시 무한루프 발생 (C++11부터는 입력된 문자열을 정수로 바꾸지 못하면 0을 씌우므로 t == 0이면 종료되버림)
//			//	//	while (true)
//			//	//	{
//			//	//		std::cin >> t;
//			//	//		std::cout << "입력 :: " << t << std::endl;
//			//	//		if (t == 1) break;
//			//	//	}
//			//	
//			//	// 위 루프의 문제점은 아래의 방식으로 해결가능
//			//	while (std::cin >> t)
//			//	{
//			//		std::cout << "입력 :: " << t << std::endl;
//			//		if (t == 1) break;
//			//	}
//	
//			/*
//				- 상태 플래그
//					- 위 코드에서 int t에 정수가 아닌 문자열 등의 다른 값을 입력하면 무한루프에 빠짐
//					- 그 이유는 operator>>의 처리 방식을 이해해야함
//						1) ios 클래스가 스트림의 상태를 관리하고 상태는 4개의 플래그가 존재함(<xiosbase>에 정의됨)
//							- goodbit: 스트림에 입출력 작업이 가능할 때
//							- badbit: 스트림에 복구 불가능한 오류 발생시
//							- failbit: 스트림에 복구 가능한 오류 발생시
//							- eofbit: 입력 작업시에 EOF 도달시
//								-> 참고로 실제 <xiosbase> 내부의 구현은 이러함
//										static constexpr int goodbit = 0x0;
//										static constexpr int eofbit  = 0x1;
//										static constexpr int failbit = 0x2;
//										static constexpr int badbit  = 0x4;
//						2) 이때 int t에 문자열이 들어간다면 failbit 플래그가 켜짐
//							-> 버퍼 안의 문자열이 들어가면 해당 부분을 스트림 버퍼에서 제거하기만 하면 되고 이는 심각한 문제가 아니므로 badbit가 아님
//						3) failbit가 켜지면 입력값을 받지 않고 리턴하는데, 이때 버퍼의 문자열에는 손을 대지 않음
//						4) 지워지지 않은 문자열로 인해 1~3을 무한반복....
//	
//					- 처음의 루프를 수정한 루프는 while(std::cin >> t) 의 형태임. 이를 통해 기존의 무한루프 문제를 막을 수 있음. 그 이유는 아래와 같음
//						1) ios 객체 내부에 operator void*() const 함수가 정의되어 있음
//							-> 이 함수는 fallbit 와 badbit가 모두 꺼져있어야 null이 아닌 포인터를 반환함. 즉, 정상적으로 입출력이 가능할때를 말함
//						2) t에 문자열이 들어가면 위 함수가 null을 반환하여 while 문을 탈출하게됨
//						
//						++1) 현재 최신에는 operator void*() 는 없는것으로 보이고 대신 operator bool이 존재하며 !fail()의 역할을 함
//						++2) fail()은 failbit나 badbit이 켜지면 true, 아니면 false를 반환하므로 위에서 ios -> void* -> bool로 가는 2단 변환을 굳이 안해도 되도록 하는듯 함
//			*/
//	
//			// 문제있는 코드: t에 문자열을 넣으면 failbit가 켜져 이후 s까지 입력받을 수 없다
//			//	int t;
//			//	std::cin >> t;	// 고의적으로 문자를 입력하면 failbit가 켜진다
//			//	std::cout << "failbit가 켜진 상태이므로, 입력받지 않는다" << std::endl;
//			//	std::string s;
//			//	std::cin >> s;
//	
//			// 해결방안: 상태 플래그에 문제가 생기면 플래그를 초기화시키고 다시 입력받는다
//			int t;
//			while (true)
//			{
//				std::cin >> t;
//				std::cout << "입력 :: " << t << std::endl;
//				if (std::cin.fail())
//				{
//					std::cout << "제대로 입력해주세요" << std::endl;
//					std::cin.clear();	// 플래그를 초기화하고
//					std::cin.ignore(100, '\n');	// 개행문자가 나올 때 까지 무시한다
//				}
//				if (t == 1) break;
//			}
//	
//			/*
//				- 위 코드가 어떻게 가능한지 분석해보자
//					- std::cin.fail() 함수가 존재함. failbit 혹은 badbit 중 하나라도 켜져있으면 true를 리턴함
//					- 잘못된 입력이 들어온 경우 if(std::cin.fail())에서 true가 되어 조건문을 실행함
//					- 조건문에서
//						- std::cin.clear() 를 이용하여 플래그들을 초기화함(ios에 정의)
//							-> std::cin.clear()는 인자를 주지 않을 경우 플래그를 goodbit으로 초기화시킴
//						- std::cin.ignore(100, '\n') 를 이용하여 버퍼를 비워버림(istream에 정의)
//							-> std::cin.ignore(std::streamsize count = 1, int delim = Traits::eof())의 형태임 (std::streamsize == long long임. <xiosbase>에 찾아보면 있음)
//							-> 첫번째 인자(100)만큼 두번째 인자('\n')가 나올때 까지 버퍼에서 무시해버림(두번째 인자까지 포함)
//						- 버퍼에 100자 이상의 긴 문자열이 들어오면 버퍼가 다 비워질때까지 루프를 돌며 ignore가 호출되면서 다 비워버림
//	
//			
//			
//			*/
//		}
//	
//	
//		return 0;
//	
//	}

// 형식 플래그, 조작자

//	#include <iostream>
//	#include <string>
//	
//	int main()
//	{
//		// setf() 함수를 이용한 형식 플래그 지정
//		//	{
//		//		int t;
//		//		while (true)
//		//		{
//		//			std::cin.setf(std::ios_base::hex, std::ios_base::basefield);
//		//			std::cin >> t;
//		//			std::cout << "입력 :: " << t << std::endl;
//		//			if (std::cin.fail())
//		//			{
//		//				std::cout << "제대로 입력해주세요" << std::endl;
//		//				std::cin.clear();
//		//				std::cin.ignore(100, '\n');
//		//			}
//		//			if(t == 1) break;
//		//		}
//		//	}
//	
//		// 조작자를 이용한 형식 플래그 지정
//		//	{
//		//		int t;
//		//		while (true)
//		//		{
//		//			std::cin >> std::hex >> t;
//		//			std::cout << "입력 :: " << std::endl;
//		//			if (std::cin.fail())
//		//			{
//		//				std::cout << "제대로 입력해주세요" << std::endl;
//		//				std::cin.clear();
//		//				std::cin.ignore(100, '\n');
//		//			}
//		//			if (t == 1) break;
//		//		}
//		//	}
//	
//	
//		/*
//			output:
//			123
//			입력 :: 291
//			ff
//			입력 :: 255
//			0xff
//			입력 :: 255
//			aBcDE
//			입력 :: 703710
//			-> 위 루프와 아래 루프 모두 동일하게 작동함
//	
//			-> 16진수로 입력값을 받아서 출력함
//			-> 출력 형식은 바꾸지 않았으므로 10진수로 출력함
//			-> 재미있는 점은 A~F까지의 수를 대,소문자를 가리지 않고 잘 받아줌
//		*/
//	
//		/*
//			- 형식 플래그, 조작자
//				- 맨 위 단락에서 ios_base 클래스에서 스트림의 입출력 형식을 바꿀 수 있다고 하였음
//				- 이는 상태 플래그처럼 형식 플래그가 존재하며 이 플래그를 이용하여 가능함
//					-> 실제 구현부는 <xiosbase>에 있음. 분량이 꽤 많아서 상태 플래그처럼 복붙은 힘들듯
//						- 형식 플래그는 일단 서식 플래그(fmtfl)와 마스크(mask)필드 비트마스크 2가지로 나뉜다고 생각하면 될듯함. https://en.cppreference.com/w/cpp/io/ios_base/setf
//							-> 각 서식 플래그에 에 맞는 마스크 필드 비트마스크 는 아래와 같음
//									fmtfl							mask
//									left, right, internal	->		adjustfiled
//									dec, oct, hex			->		basefield
//									scientific, fixed		->		floatfield
//							-> 서식 플래그에 맞는 마스크 필드 비트마스크로 초기화를 해야 정상 사용 가능함
//							-> 위의 것들 말고도 단독으로 사용가능한 형식 플래그들이 있음. 이를 단항 서식 플래그라고 부름
//								-> boolalpha, showbase, showpoint, showpos, skipws, unitbuf, uppercase 가 있음
//	
//				- 위 코드에서 첫번째 루프는 std::cin.setf() 함수로 형식 플래그를 적용하고 있음
//					- std::cin.setf()는 2가지 버전이 있음
//						1) fmtflags __CLR_OR_THIS_CALL setf(fmtflags _Newfmtflags) noexcept
//							- 인자를 하나만 받는 버전으로 그냥 인자로 준 플래그를 적용
//							- 주로 단항 서식 플래그를 설정할때 사용됨
//						2) fmtflags __CLR_OR_THIS_CALL setf(fmtflags _Newfmtflags, fmtflags _Mask) noexcept
//							- 인자를 2개 받는 버전으로 두번째 인자로 받은 마스크로 초기화하고 첫번째 인자의 플래그를 적용함
//							- 위에서는 진법 처리를 위한 basefield 플래그로 마스크시키고 hex 플래그로 16진수를 적용시킴
//					- 위의 진법 처리는 직접 함수를 만들어도 좋지만 기본 제공 라이브러리가 0x를 붙이는 경우나 대소문자 이미 잘 처리해주므로 굳이 필요없음
//	
//				- 위 코드에서 두번째 루프는 std::hex 조작자를 이용해서 형식 플래그를 적용하고 있음
//					- 조작자(Manipulator) : 스트림을 조작하여 입력 혹은 출력 방식을 바꿔주는 함수
//					- 조작자는 ios 클래스의 함수이기 때문에 ios_base::hex 가 아닌 cin::hex로 호출함
//						-> 실제 구현은 이러함. <ios>의 base_ios 클래스에 있음
//	
//							inline ios_base& __CLRCALL_OR_CDECL hex(ios_base& _Iosbase) { // set basefield to hex
//							    _Iosbase.setf(ios_base::hex, ios_base::basefield);
//							    return _Iosbase;
//							}
//	
//						-> 단순히 setf()로 형식 플래그를 적용시키고 리턴시켜줌
//	
//					- 이걸 >> 뒤에 붙여도 작동되는 이유
//						- operator >> 가 함수포인터를 받도록 오버로딩 되어있기 때문
//							-> 실제 구현은 이러함. <istream>에 정의되어있음
//	
//							basic_istream& __CLR_OR_THIS_CALL operator>>(ios_base&(__cdecl* _Pfn)(ios_base&) ) { // call ios_base manipulator
//								_Pfn(*this);
//								return *this;
//							}
//	
//							-> this가 함수 포인터로 받아온 함수를 실행시키고 리턴하도록 오버로딩 되어있음
//	
//						- 지금까지 쓰던 std::endl도 같은 방식으로 작동됨
//							-> 실제 구현은 이러함. <ostream>에 정의되어있고 이건 operator<<로 오버로딩하여 사용됨
//	
//							basic_ostream<_Elem, _Traits>& __CLRCALL_OR_CDECL endl(
//								basic_ostream<_Elem, _Traits>& _Ostr) { // insert newline and flush stream
//								_Ostr.put(_Ostr.widen('\n'));
//								_Ostr.flush();
//								return _Ostr;
//							}
//						
//							-> 개행 문자 하나 넣고 버퍼를 전부 내보내는 flush()를 호출함
//						
//						- 이외에도 다양하게 있으므로 더 알고싶다면 https://en.cppreference.com/w/cpp/io/manip 로
//							- 모두의 코드에 간략하게 설명된 조작자
//								- boolalpha : true/false를 0/1 대신 문자열 그대로 입력받음
//								- left/right : 출력 형식을 왼쪽/오른쪽으로 정렬시킴
//	
//		*/
//	}

// 스트림 버퍼에 대하여

#include <iostream>
#include <string>

int main()
{
	std::string s;
	std::cin >> s;

	// 위치 지정자를 한 칸 옮기고, 그 다음 문자를 훔쳐본다(이때는 움직이지 않음)
	char peek = std::cin.rdbuf()->snextc();
	if (std::cin.fail()) std::cout << "Failed";
	std::cout << "두 번째 단어 맨 앞글자 : " << peek << std::endl;
	std::cin >> s;
	std::cout << "다시 읽으면 : " << s << std::endl;

	/*
		output:
		hello world
		두 번째 단어 맨 앞글자 : w
		다시 읽으면 : world
	*/

	/*
		- 스트림 버퍼
			- 모든 입출력 객체들은 이에 대응되는 스트림 객체를 가지고 있음
				- stream : 사전적으로는 시냇물이라는 의미. 문자들의 순차적인 나열이라고 보면 됨. 시냇물처럼 문자들이 순차적으로 쭉 들어오는걸 생각해보자
			- C++의 입출력 라이브러리도 마찬가지로 스트림 버퍼 클래스가 있는데 이것이 streambuf
				- 추가적으로 std::stringstream 으로 평범한 문자열을 스트림인것 처럼 이용할 수도 있음
	
		- C++의 streambuf 클래스
			- <streambuf> 클래스에 base_streambuf 클래스로 존재
			- 기본적으로 스트림에서 입력, 출력 혹은 동시에 수행할 수 있음(C의 "rw"옵션)
			- 입력 버퍼와 출력 버퍼가 구분되어있고 이를 각각 get area, put area라고 부름. 구분을 위해 각각의 포인터에도 g와 p를 붙여 표시함
			- 스트림의 상태를 나타내기 위한 3개의 포인터가 있음
				- 시작 포인터 : 버퍼의 시작 부분을 가리킴.				->	get area: eback()		put area: pbase()
				- 스트림 위치 지정자 : 다음으로 읽을 문자를 가리킴		->	get area: gptr()		put area: pptr()
				- 끝 포인터 : 버퍼의 끝 부분을 가리킴					->	get area: egptr()		put area: epptr()
																		-> 참고로 위는 protected 멤버라 클래스 외부에선 호출 안됨
			- streambuf를 통한 문자열 조작: 위 코드 분석
				- char peek = std::cin.rdbuf()->snextc();
					- std::cin.rdbuf(): cin 객체가 입력을 수행하고 있던 streambuf 객체를 가리키는 포인터를 리턴함
						-> cin은 istream 객체이므로 리턴받은 streambuf에는 get area만 존재함
					- snextc(): streambuf의 위치 지정자를 한 칸 전진시킨 후, 그 자리에 해당하는 문자를 엿봄(seek_next_character의 약자인듯)
						-> 엿본다 vs 읽는다
							- 엿본다: 해당 문자를 읽고 스트림 위치 지정자를 움직이지 않음
							- 읽는다: 해당 문자를 읽고 다음 문자를 읽기 위해 스트림 위치 지정자를 한칸 전진시킴
				- peek의 결과가 w인 이유
					- hello world를 입력하고 std::cin >> s; 를 한 이후의 cin의 streambuf 상태를 보면...

						['h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\n']
					                               ^
							          현재 스트림 위치 지정자 상태
										-> 이게 왜 여기있나요? : operator>>가 공백문자를 무시하기 때문. 그러므로 s에는 현재 hello만 들어가있음
					
					- snextc() 함수 호출 후의 streambuf의 상태
						['h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\n']
												        ^
									       현재 스트림 위치 지정자 상태 : snextc()가 스트림 위치 지정자를 한칸 전진시키고 읽은다음 지정자를 건드리지 않고 리턴함

				- 이후 std::cin >> s; 에서 현재 스트림 위치 지정자에서부터 읽어들여 다시 읽으면 world가 출력되는 것임

			- 그래서 streambuf를 왜 쓰는가
				- wchar_t 등의 다중 바이트 문자들에 대한 처리를 용이하게 하기 위함
					- 다중 바이트 문자는 필요에 따라 1바이트 이상이 필요한 경우가 있기 때문에 이러한 것들을 스트림 객체에서 처리하도록 하여 사용자가 쓰기 용이하게 만듬
	*/

	return 0;
}
/*


*/