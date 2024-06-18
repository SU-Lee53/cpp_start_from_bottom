/*
	06.18 - <regex>
*/

/*  정규 표현식 Regular Expression  */
/*
	- 정규 표현식
		- 문자열의 일정한 패턴을 표현하는 일종의 형식 언어
		- 다음의 상황에서 유용하게 많이 사용됨
			- 주어진 문자열이 주어진 규칙에 맞는지 확인할 때
			- 주어진 문자열에서 원하는 패턴의 문자열을 검색할 때
			- 주어진 문자열에서 원하는 패턴의 문자열로 치환할 때

		- 정규 표현식 문법은 여러가지가 존재함
			- 기본적이고 대표적인 문법은 https://namu.wiki/w/%EC%A0%95%EA%B7%9C%20%ED%91%9C%ED%98%84%EC%8B%9D?from=Regex 에 잘 나옴

		- C++ 11 부터 <regex> 라이브러리를 이용하여 정규 표현식을 사용할 수 있음
*/

/*  <regex> 의 활용 1 - 전체 문자열 매칭  */
//	/*
//		- 특정한 파일 이름이 주어진 패턴을 만족하는지 확인
//	
//		- 아래 코드의 상황
//			- 서버를 관리하는 상황
//			- db-(시간)-log.txt 와 같은 형태로 매 시간 마다 로그 파일이 생성됨
//				-> 여러 파일들이 섞여있는 폴더에서 우리가 원하는 로크 파일들만 간단히 읽어들이는 프로그램을 만들고자 함
//	
//		- 정규 표현식으로 위 로그파일을 표현하면 아래와 같음
//			
//				db-\d*-log\.txt
//	
//			- \d* : 임의의 갯수의 숫자
//			- \. : 그냥 . 은 임의의 문자로 해석되므로 \ 를 붙임
//	
//	*/
//	#include <iostream>
//	#include <regex>
//	#include <vector>
//	
//	int main()
//	{
//		// 폴더 내의 파일들
//		std::vector<std::string> file_names = { "db-123-log.txt", "db-124-log.txt",
//												"not-db-log.txt", "db-12-log.txt",
//												"db-12-log.jpg" };
//	
//		std::regex re("db-\\d*-log\\.txt");
//		for (const auto& file_name : file_names)
//		{
//			std::cout << file_name << " : " << std::boolalpha << std::regex_match(file_name, re) << '\n';
//		}
//	
//		/*
//			- output :
//				db-123-log.txt : true
//				db-124-log.txt : true
//				not-db-log.txt : false
//				db-12-log.txt : true
//				db-12-log.jpg : false
//		*/
//	
//		/*
//			- 전체 문자열 매칭
//				- 코드 설명
//					- std::regex re("db-\\d*-log\\.txt");
//						- 정규 표현식 객체를 정의함
//						- 정규 표현식 객체를 정의할 때 표현식의 문법, 처리하는 엔진 등의 특성 들을 추가할 수 있음
//	
//							- 문법 종류
//									static constexpr flag_type ECMAScript = regex_constants::ECMAScript;
//									static constexpr flag_type basic      = regex_constants::basic;			: 기본 POSIX 정규표현식 https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap09.html#tag_09_03
//									static constexpr flag_type extended   = regex_constants::extended;		: 확장된 POSIX 정규 표현식 https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap09.html#tag_09_04
//									static constexpr flag_type awk        = regex_constants::awk;			: POSIX 의 awk 정규표현식 https://pubs.opengroup.org/onlinepubs/9699919799/utilities/awk.html#tag_20_06_13_04
//									static constexpr flag_type grep       = regex_constants::grep;			: POSIX 의 grep 정규표현식
//									static constexpr flag_type egrep      = regex_constants::egrep;			: 위 grep 에 -E 옵션이 추가된 문법
//	
//								-> MSVC 기준 이렇게 존재하고 기본값은 ECMAScript 임 https://en.cppreference.com/w/cpp/regex/ecmascript
//	
//							- 문법 변조
//									static constexpr flag_type icase      = regex_constants::icase;			: 대소문자 구분을 없앰
//									static constexpr flag_type nosubs     = regex_constants::nosubs;		: 하위 표현식 () 를 (?:) 로 바꾼다는데 잘 모르겠음
//									static constexpr flag_type optimize   = regex_constants::optimize;		: 성능 최적화 (객체 생성시 조금 느려짐)
//									static constexpr flag_type collate    = regex_constants::collate;		: [a-b] 문자를 지역에 맞춤
//	
//								-> cppreference 에서는 C++ 17 부터 std::regex::multiline 이 추가된다고 나와있지만 MSVC에 없으므로 skip
//	
//							- 위의 특성들은 | 를 통해서 여러개 추가 가능함 (비트마스크 사용)
//								- ex) grep 문법을 사용하고 대소문자 구분을 없애고싶다면 
//									-> std::regex re("db-\\d*-log\\.txt", std::regex::grep | std::regex::icase);
//	
//							- 더 자세한 설명은 https://en.cppreference.com/w/cpp/regex/basic_regex/constants
//				
//	
//					- std::regex_match(file_name, re)
//						- 첫번째 인자로 전달된 문자열이 두번째 인자로 전달된 regex 객체와 완전히 매칭되면 true 를 리턴
//	
//		*/
//	}

/*  <regex> 의 활용 2 - 부분 매칭 뽑아내기  */
/*
	- 위 경우와 다르게 패턴 일부분만 뽑아내어 만족하는지 확인

	- 아래 코드의 상황
		- 전화번호 정규표현식을 만드려고 함
		- 전화번호는 다음의 규칙을 만족
			- (숫자)-(숫자)-(숫자) 꼴
			- 맨 앞자리는 반드시 3자리이고, 0 과 1 로만 이루어져야함
			- 가운데 자리는 3자리 혹은 4자리
			- 마지막 자리는 반드시 4자리

		- 위 규칙에 따라 아래와 같은 정규표현식이 만들어짐

				[01]{3}-\d{3,4}-\d{4}

			- [01] : 0 혹은 1
			- {3} : 해당 종류의 문자가 3번 나타날 수 있다
			- 위를 따라가면 나머지는 해석가능

			-> 이 때 조건에 만족하는 전화번호의 가운데 부분만 추출해내는 프로그램을 만들려고 함

		- 정규 표현식의 캡쳐 그룹을 사용하여 프로그램 작성
			-> () 로 일부분을 감싸면 해당 부분에 매칭된 문자열이 얻어짐
*/
#include <iostream>
#include <regex>
#include <vector>

int main()
{
	std::vector<std::string> phone_numbers = { "010-1234-5678", "010-123-4567",
											"011-1234-5567", "010-12345-6789",
											"123-4567-8901", "010-1234-567" };

	std::regex re("[01]{3}-(\\d{3,4})-\\d{4}");
	std::smatch match;
	for (const auto& number : phone_numbers)
	{
		std::cout << number << " : " << std::boolalpha << std::regex_match(number, re) << '\n';
		if (std::regex_match(number, match, re))
		{
			for (size_t i = 0; i < match.size(); i++)
			{
				std::cout << "Match : " << match[i].str() << std::endl;
			}
			std::cout << "---------------------------\n";
		}
	}
	
	/*
		- output :
			010-1234-5678 : true
			Match : 010-1234-5678
			Match : 1234
			---------------------------
			010-123-4567 : true
			Match : 010-123-4567
			Match : 123
			---------------------------
			011-1234-5567 : true
			Match : 011-1234-5567
			Match : 1234
			---------------------------
			010-12345-6789 : false
			123-4567-8901 : false
			010-1234-567 : false
	*/

	/*
		- 부분 매칭 뽑아내기
			- 코드 설명
				- std::smatch match;
					- 매칭된 문자열을 std::string 형태로 보관
					- const char* 로 보관하고 싶다면 cmatch 를 이용하면 됨

				- std::regex_match(number, match, re)
					- 두번째 인자로 std::smatch 혹은 std::cmatch 를 전달하면 매칭된 부분을 보관해줌

				- std::cout << "Match : " << match[i].str() << std::endl;
					- 첫번째 매칭은 전체 문자열이 매칭된 것이므로 match[0].str() 에는 전화번호 전체가 들어감
					- 두번째로 () 안의 문자열이 매칭되어 match[1].str() 에 원하고자 하던 가운데 부분이 들어감
						-> 여러개의 () 가 있다면 for 문으로 순차적으로 접근
	*/
}

