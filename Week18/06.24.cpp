/*
	06.24 - <filesystem>
*/

/*  <filesystem> 기초 - 파일 찾기  */
//	#include <filesystem>	// since C++ 17
//	#include <iostream>
//	
//	int main()
//	{
//		std::cout << std::boolalpha;
//	
//		std::filesystem::path p("./some_file");
//	
//		std::cout << "Does " << p << " exist? [" << std::filesystem::exists(p) << "]" << std::endl;	// Does "./some_file" exist? [true]
//		std::cout << "Is " << p << " file? [" << std::filesystem::is_regular_file(p) << "]" << std::endl;	// Is "./some_file" file? [true]
//		std::cout << "Is " << p << " directory? [" << std::filesystem::is_directory(p) << "]" << std::endl;	// Is "./some_file" directory? [false]
//	
//		/*
//			- <filesystem> 기초 - 파일찾기
//				- 코드 설명
//					- std::filesystem::path p("./some_file");
//						- <filesystem> 라이브러리는 전부 std::filesystem 이름공간 안에 있음
//							-> std::chrono 처럼 namespace fs = std::filesystem 같이 사용하면 편함
//						- path 객체 p 를 선언
//							- path(경로) 는 파일의 위치를 나타내는 고유의 주소 -> 뒤에서 다시
//	
//					- std::filesystem::exists(p)
//						- <filesystem> 에서 파일이나 디렉토리를 다루는 모든 함수는 path 객체를 인자로 받음
//							-> 따라서 이후 나오는 is_regular_file, is_directory 도 마찬가지임
//						- exists() 는 해당 경로에 파일이 실제로 존재하는지 확인하고 있으면 true 를 리턴함
//	
//					- std::filesystem::is_regular_file(p)
//						- 해당 위치에 있는 것이 파일인지 확인하여 맞으면 true 를 리턴함
//	
//					- std::filesystem::is_directory(p)
//						- 해당 위치에 있는 것이 디렉토리(폴더) 라면 true 를 리턴함
//				
//				- 경로 path
//					- 파일의 위치를 나타내는 고유의 주소
//					- 경로 지정 방식에는 2가지가 있음
//	
//						1) 절대 경로
//							- 가장 최상위 디렉토리(root 디렉토리)에서 내가 원하는 파일까지의 경로
//								- windows 의 경우 최상위 디렉토리는 C:\
//								- linus 의 경우 최상위 디렉토리는 그냥 / 라고 부름
//	
//						2) 상대 경로
//							- 현재 프로그램이 실행되고 있는 위치에서 해당 파일을 찾아가는 경로
//	
//					- std::filesystem::path p("./some_file"); 는 어디?
//						- 일단 시작이 C:\ (리눅스는 /) 이 아니므로 절대경로는 아님
//						- . 은 현재 디렉토리를 의미하므로 지금 이 Week18 폴더 안에 존재하는 some_file 을 말함
//	
//					- <filesystem> 에는 경로를 나타내고 다룰 수 있는 여러 멤버함수가 있는 path 클래스가 있음
//	
//					- 기본적으로 <filesystem> 에서 파일이나 디렉토리를 다루는 함수는 전부 path 를 인자로 받음
//	
//		*/
//	}

/*  <filesystem> 의 경로 관련 함수들  */
//	#include <filesystem>
//	#include <iostream>
//	
//	namespace fs = std::filesystem;
//	
//	int main()
//	{
//		fs::path p("./some_file.txt");
//	
//		std::error_code ec;
//	
//		std::cout << "내 현재 경로 : " << fs::current_path() << std::endl;
//		std::cout << "상대 경로 : " << p.relative_path() << std::endl;
//		std::cout << "절대 경로 : " << fs::absolute(p, ec) << std::endl;
//		std::cout << "공식적인 절대 경로 : " << fs::canonical(p) << std::endl;
//	
//		/*
//			- 경로 관련 함수들
//				- 코드 설명
//					- fs::current_path()
//						- 현재 프로그램이 실행되는 경로를 리턴
//						- 모든 상대 경로는 이 현재 실행되는 경로를 기준으로 찾아가서 구함
//	
//					- p.relative_path()
//						- path 클래스의 멤버 함수로 해당 객체의 상대 경로를 리턴
//	
//					- fs::absolute(p)
//						- 상대 경로를 절대 경로로 바꿔줌
//						- 다만 . 이나 .. 같은 불필요한 요소들이 포함될 수 있음
//	
//					- fs::canonical(p)
//						- 해당 파일의 경로를 가장 짧게 나타낼 수 있는 공식적인 절대 경로를 리턴
//						- absolute() 와 달리 불필요한 요소를 없애고 리턴함
//	
//					- . : 현재 폴더를 말함
//					- .. : 상위 폴더를 말함
//	
//				- 위 함수들의 경우 입력 받은 경로에 해당 파일이 없으면 모두 예외를 던짐
//					-> 따라서 exists() 를 이용하여 존재하는지 먼저 확인하는 것이 좋음
//					-> 예외를 처리하고 싶지 않다면 마지막 인자에 error_code 객체를 전달하면 됨 (error_code 객체까지 받는 함수가 전부 오버로딩 되어있음)
//						-> 이 경우 예외 발생시 error_code 에 오류를 설정함
//				
//		*/
//	
//	}

/*  <filesystem> 의 디렉토리 작업 - 1. 디렉토리 안의 모든 파일 순회  */
//	#include <filesystem>
//	#include <iostream>
//	
//	namespace fs = std::filesystem;
//	
//	int main()
//	{
//		fs::directory_iterator itr(fs::current_path() / "a");
//		while (itr != fs::end(itr))
//		{
//			const fs::directory_entry& entry = *itr;
//			std::cout << entry.path() << std::endl;
//			itr++;
//		}
//	
//		// range based for 가능
//		std::cout << std::endl;
//		for (const fs::directory_entry& entry : fs::directory_iterator(fs::current_path() / "a"))
//		{
//			std::cout << entry.path() << std::endl;
//		}
//	
//		// 서브 디렉토리까지 순회 - recursive_directory_iterator
//		std::cout << std::endl;
//		for (const fs::directory_entry& e : fs::recursive_directory_iterator(fs::current_path()))
//		{
//			std::cout << e.path() << std::endl;
//		}
//	
//		/*
//			- 디렉토리 순회
//				- std::filesystem::directory_iterator : 디렉토리에 쉽게 접근하기 위해 제공되는 디렉토리 반복자
//				- 코드 설명
//					- fs::directory_iterator itr(fs::current_path() / "a");
//						- directory_iterator 는 다른 반복자와 달리 스스로 정의하고 생성자에 경로를 전달해주어야 함
//						- operator / 는 나눗셈이 아니고 / 를 추가하여 경로를 만드는 것임
//							-> 즉, / "a" 는 /a 를 추가한 것
//						
//					- while (itr != fs::end(itr))
//						- std::filesystem::end() 는 해당 반복자의 끝을 가져옴
//	
//					- const fs::directory_entry& entry = *itr;
//						- 반복자는 directory_entry 라는 객체를 가리킴
//						- directory_entry : 파일 이름, 크기 등이 보관된 클래스
//	
//					- std::cout << entry.path() << std::endl;
//						- 경로 출력
//						- path() 는 현재 directory_entry 의 경로를 path 로 리턴함
//	
//					- for (const fs::directory_entry& e : fs::recursive_directory_iterator(fs::current_path()))
//						- std::filesystem::recursive_directory_iterator 는 디렉토리 안의 서브 디렉토리까지 전부 순회할 수 있는 반복자
//						- directory_iterator 는 range-based for 를 사용할 수 있음
//		*/
//	}

/*  <filesystem> 의 디렉토리 작업 - 2. 디렉토리 생성  */
//	#include <filesystem>
//	#include <iostream>
//	
//	namespace fs = std::filesystem;
//	
//	int main()
//	{
//		std::cout << std::boolalpha;
//	
//		fs::path p("./a/c");
//		std::cout << "Does " << p << " exist? [" << fs::exists(p) << "]" << std::endl;
//	
//		fs::create_directory(p);
//	
//		std::cout << "Does " << p << " exist? [" << fs::exists(p) << "]" << std::endl;
//		std::cout << "Is " << p << " directory [" << fs::is_directory(p) << "]" << std::endl;
//	
//		fs::path p2("./c/d/e/f");
//		std::cout << "Does " << p2 << " exist? [" << fs::exists(p2) << "]" << std::endl;
//	
//		// fs::create_directory(p2);	// 부모 디렉터리 (./c) 가 없으므로 런타임 오류 발생
//		fs::create_directories(p2);
//	
//		std::cout << "Does " << p2 << " exist? [" << fs::exists(p2) << "]" << std::endl;
//		std::cout << "Is " << p2 << " directory [" << fs::is_directory(p2) << "]" << std::endl;
//	
//		system("tree");
//	
//		/*
//			- 디렉토리 생성
//				- 기존 ofstream 은 파일 생성까지는 가능했으나 디렉토리는 만들 수 없었음
//				- <filesystem> 의 create_directory 를 이용하면 디렉토리를 만들 수 있음
//	
//				- 코드 설명
//					- fs::create_directory(p); (p 는 ./a/c)
//						- create_directory() 는 path 를 인자로 받아 해당 경로에 해당하는 디렉토리를 만듬
//						- create_directory() 의 경우 생성하는 디렉토리의 부모 디렉토리가 반드시 존재해야 만들 수 있음
//							- 위 파일순회 예제에서 ./a 를 만들었다면 문제없이 작동됨
//	
//					- fs::create_directories(p2); (p2 는 ./c/d/e/f)
//						- 마찬가지로 디렉토리를 만드는데 부모 디렉토리까지 한꺼번에 만들 수 있음
//	
//					- system("tree");
//						- tree 명령을 실행
//		*/		
//	
//	}

/*  <filesystem> 의 디렉토리 작업 - 3. 파일/폴더 복사, 삭제  */
//	#include <filesystem>
//	#include <iostream>
//	
//	namespace fs = std::filesystem;
//	
//	int main()
//	{
//		// 복사
//		fs::path from("./a");
//		fs::path to("./c");
//	
//		fs::copy(from, to, fs::copy_options::recursive | fs::copy_options::skip_existing);
//		
//		system("tree");
//	
//		// 삭제
//		fs::path p("./a/1.txt");
//		std::cout << "Does " << p << "exist? [" << std::boolalpha << fs::exists(p) << "]" << std::endl;
//		
//		fs::remove(p);
//		std::cout << "Does " << p << "exist? [" << std::boolalpha << fs::exists(p) << "]" << std::endl;
//	
//		std::cout << std::endl;
//	
//		fs::path p2("./c/d");
//		std::cout << "Does " << p2 << "exist? [" << std::boolalpha << fs::exists(p2) << "]" << std::endl;
//		std::error_code err;
//		fs::remove(p2, err);	// 안지워짐 : 빈 디렉토리가 아님
//		std::cout << err.message() << std::endl;	// 디렉터리가 비어 있지 않습니다.
//	
//		fs::remove_all(p2, err);	// remove_all 을 이용하면 지울 수 있음
//		std::cout << "Does " << p2 << "exist? [" << std::boolalpha << fs::exists(p2) << "]" << std::endl;
//	
//		/*
//			- 파일/폴더 복사
//				- 기존 ofstream 을 이용하면 파일까지는 복사가 가능하지만, 디렉토리는 복사가 불가능했음
//				- <filesystem> 의 copy 를 이용하면 디렉토리까지 복사가 가능
//				- 코드 설명
//					- fs::copy(from, to, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
//						- from 을 to 로 복사함
//						- 뒤는 복사 옵션으로 비트마스크를 이용하므로 | (OR) 을 이용하여 여러 옵션을 적용 가능함
//						- copy_options 들은 아래와 같음 https://en.cppreference.com/w/cpp/filesystem/copy_options
//	
//							- 파일이 이미 존재할 경우에 대한 옵션
//								- none					: 기본값(error_code 발생시키거나 예외 던짐)
//								- skip_existing			: 이미 존재하는 경우 skip
//								- overwrite_existing	: 이미 존재하는 경우 덮어씀
//								- update_existing		: 이미 존재하는 파일이 더 오래된 경우 덮어씀
//	
//							- 서브 디렉토리에 대한 옵션
//								- none					: 기본값
//								- recursive				: 서브 디렉토리까지 재귀적으로 복사
//	
//							- 심볼릭 링크에 대한 옵션
//								- none					: 기본값(심볼릭 링크를 따라가서 원본 복사)
//								- copy_symlinks			: 심볼릭 링크를 심볼릭 링크로 복사
//								- skip_symlinks			: 심볼릭 링크 skip
//	
//							- copy() 작업에 대한 옵션
//								- none					: 기본값
//								- directories_only		: 디렉토리만 복사
//								- create_symlinks		: 복사 대신 원본의 심볼릭 링크를 만듬(목적지 경로가 현재 경로가 아니라면 원본 경로는 반드시 절대경로여야함)
//								- create_hardlinks		: 복사 대신 원본의 하드 링크를 만듬
//	
//							※ 심볼릭 링크 : 윈도우의 바로가기와 유사하지만 링크이므로 크기가 없고 원본이 존재하는지 검사하지 않음. 
//								->유닉스 계열과 NTFS 이상의 파일시스템을 지원하는 윈도우만 가능
//							※ 하드 링크 : 동일한 데이터를 가리키는 2개의 논리적인 파일을 만드는 것
//	
//			- 파일/폴더 삭제
//				- remove() : 디렉토리를 지움
//					- remove() 함수 사용시 해당 디렉토리는 반드시 비어있어야함
//						-> 비어있지 않으면 예외 or error_code 생김
//	
//				- remove_all() : 서브 디렉토리까지 모두 지움
//					-> 이 경우 디렉토리가 비어있지 않아도 지울 수 있음
//		
//		*/
//	}

/*  directory_iterator 사용시 주의할 점  */
//	#include <filesystem>
//	#include <iostream>
//	
//	namespace fs = std::filesystem;
//	
//	int main()
//	{
//		fs::path p("./a");
//	
//		// .txt 파일을 지움 : 틀린 예시
//	
//		//	for (const auto& entry : fs::directory_iterator("./a"))
//		//	{
//		//		const std::string ext = entry.path().extension().generic_string();	// path::string_type 이 wstring 이므로 generic_string() 을 거쳐야 string 이 됨
//		//		if (ext == ".txt")
//		//		{
//		//			fs::remove(entry.path());
//		//		}
//		//	}
//	
//		// .txt 파일을 지움 : 올바른 예시
//	
//		while (true)
//		{
//			bool is_modified = false;
//			for (const auto& entry : fs::directory_iterator("./a"))
//			{
//				const std::string ext = entry.path().extension().generic_string();
//				if (ext == ".txt")
//				{
//					fs::remove(entry.path());
//					is_modified = true;
//					break;
//				}
//			}
//			if (!is_modified) break;
//		}
//		
//		/*
//			- directory_iterator 사용시 주의할 점
//				- directory_iterator 는 디렉토리의 구조가 바뀌면 무효화됨
//					-> 무효화 된 반복자는 ++ 연산이 다음 디렉토리를 가리킨다는 보장을 할 수 없음
//					-> 따라서 파일/디렉토리가 추가되거나 삭제되면 더이상 사용하면 안됨
//	
//				- 위 예제처럼 삭제/추가시 반복자를 초기화해주어야 올바르게 작동할 수 있음
//		*/
//	}