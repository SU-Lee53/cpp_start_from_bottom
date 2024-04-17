
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
#include <iostream>
#include <string>

int main()
{
	// istream 클래스

	//	{
	//		std::string s;
	//		while (true)
	//		{
	//			std::cin >> s;
	//			std::cout << "word : " << s << std::endl;
	//		}
	//	
	//		/*
	//			output:
	//			this is a long sentence
	//			word : this
	//			word : is
	//			word : a
	//			word : long
	//			word : sentence
	//			ABC DEF GHI
	//			word : ABC
	//			word : DEF
	//			word : GHI
	//		*/
	//	
	//		/*
	//			- istream 클래스
	//				- 실제로 입력을 수행하는 클래스: std::cin >> ;
	//					- operator>> : istream 클래스에 정의된 연산자
	//						- istream 헤더파일을 까보면 operator>>가 모든 기본 타입들에 대하여 전부 오버로딩이 되어있기 때문에 "std::cin >>" 이 자유롭게 가능함
	//						- 재미있는건 std::string은 오버로딩 되어있지 않은데 istream의 멤버가 아닌 외부 함수로 연산자 오버로딩 되어있음(참고로 <xstring> 헤더에 있음)
	//							-> 만약 없으면 직접하면 됨: istream& operator>>(istream& in, std::string s){}
	//							-> 실제 <xstring>에서는 이렇게 함:
	//								_EXPORT_STD template <class _Elem, class _Traits, class _Alloc>
	//								basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr, basic_string<_Elem, _Traits, _Alloc>& _Str)
	//						- operator>>는 모든 공백문자(띄어쓰기, 엔터, 탭)을 입력시에 무시해버림
	//							-> 위 코드도 공백이 있는 문자를 입력하면 전부 무시하고 한단어씩 분리해서 받고있음
	//	
	//	
	//					- cin : istream의 객체중 하나. 이건 <iostream>에 정의되어있으므로 <istream>만 include하는것으로는 cin을 사용못함
	//	
	//		*/
	//	}

	// istream::operator>> 사용시의 주의사항: 상태 플래그

	{
		//	int t;
		//	
		//	// 문자열 입력시 무한루프 발생 (C++11부터는 입력된 문자열을 정수로 바꾸지 못하면 0을 씌우므로 t == 0이면 종료되버림)
		//	//	while (true)
		//	//	{
		//	//		std::cin >> t;
		//	//		std::cout << "입력 :: " << t << std::endl;
		//	//		if (t == 1) break;
		//	//	}
		//	
		//	// 위 루프의 문제점은 아래의 방식으로 해결가능
		//	while (std::cin >> t)
		//	{
		//		std::cout << "입력 :: " << t << std::endl;
		//		if (t == 1) break;
		//	}

		/*
			- 상태 플래그
				- 위 코드에서 int t에 정수가 아닌 문자열 등의 다른 값을 입력하면 무한루프에 빠짐
				- 그 이유는 operator>>의 처리 방식을 이해해야함
					1) ios 클래스가 스트림의 상태를 관리하고 상태는 4개의 플래그가 존재함(<xiosbase>에 정의됨)
						- goodbit: 스트림에 입출력 작업이 가능할 때
						- badbit: 스트림에 복구 불가능한 오류 발생시
						- failbit: 스트림에 복구 가능한 오류 발생시
						- eofbit: 입력 작업시에 EOF 도달시
							-> 참고로 실제 <xiosbase> 내부의 구현은 이러함
									static constexpr int goodbit = 0x0;
									static constexpr int eofbit  = 0x1;
									static constexpr int failbit = 0x2;
									static constexpr int badbit  = 0x4;
					2) 이때 int t에 문자열이 들어간다면 failbit 플래그가 켜짐
						-> 버퍼 안의 문자열이 들어가면 해당 부분을 스트림 버퍼에서 제거하기만 하면 되고 이는 심각한 문제가 아니므로 badbit가 아님
					3) failbit가 켜지면 입력값을 받지 않고 리턴하는데, 이때 버퍼의 문자열에는 손을 대지 않음
					4) 지워지지 않은 문자열로 인해 1~3을 무한반복....

				- 처음의 루프를 수정한 루프는 while(std::cin >> t) 의 형태임. 이를 통해 기존의 무한루프 문제를 막을 수 있음. 그 이유는 아래와 같음
					1) ios 객체 내부에 operator void*() const 함수가 정의되어 있음
						-> 이 함수는 fallbit 와 badbit가 모두 꺼져있어야 null이 아닌 포인터를 반환함. 즉, 정상적으로 입출력이 가능할때를 말함
					2) t에 문자열이 들어가면 위 함수가 null을 반환하여 while 문을 탈출하게됨
					
					++1) 현재 최신에는 operator void*() 는 없는것으로 보이고 대신 operator bool이 존재하며 !fail()의 역할을 함
					++2) fail()은 failbit나 badbit이 켜지면 true, 아니면 false를 반환하므로 위에서 ios -> void* -> bool로 가는 2단 변환을 굳이 안해도 되도록 하는듯 함
		*/

		// 문제있는 코드: t에 문자열을 넣으면 failbit가 켜져 이후 s까지 입력받을 수 없다
		//	int t;
		//	std::cin >> t;	// 고의적으로 문자를 입력하면 failbit가 켜진다
		//	std::cout << "failbit가 켜진 상태이므로, 입력받지 않는다" << std::endl;
		//	std::string s;
		//	std::cin >> s;

		// 해결방안: 상태 플래그에 문제가 생기면 플래그를 초기화시키고 다시 입력받는다
		int t;
		while (true)
		{
			std::cin >> t;
			std::cout << "입력 :: " << t << std::endl;
			if (std::cin.fail())
			{
				std::cout << "제대로 입력해주세요" << std::endl;
				std::cin.clear();	// 플래그를 초기화하고
				std::cin.ignore(100, '\n');	// 개행문자가 나올 때 까지 무시한다
			}
			if (t == 1) break;
		}

		/*
			- 위 코드가 어떻게 가능한지 분석해보자
				- std::cin.fail() 함수가 존재함. failbit 혹은 badbit 중 하나라도 켜져있으면 true를 리턴함
				- 잘못된 입력이 들어온 경우 if(std::cin.fail())에서 true가 되어 조건문을 실행함
				- 조건문에서
					- std::cin.clear() 를 이용하여 플래그들을 초기화함(ios에 정의)
						-> std::cin.clear()는 인자를 주지 않을 경우 플래그를 goodbit으로 초기화시킴
					- std::cin.ignore(100, '\n') 를 이용하여 버퍼를 비워버림(istream에 정의)
						-> std::cin.ignore(std::streamsize count = 1, int delim = Traits::eof())의 형태임 (std::streamsize == long long임. <xiosbase>에 찾아보면 있음)
						-> 첫번째 인자(100)만큼 두번째 인자('\n')가 나올때 까지 버퍼에서 무시해버림(두번째 인자까지 포함)
					- 버퍼에 100자 이상의 긴 문자열이 들어오면 버퍼가 다 비워질때까지 루프를 돌며 ignore가 호출되면서 다 비워버림

		
		
		*/
	}


	return 0;

}