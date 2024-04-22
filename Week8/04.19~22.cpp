
/*
	04.19 C++에서의 파일 입출력 ifstream, ofstream, stringstream
*/

// fstream

//	#include <fstream>
//	#include <iostream>
//	#include <string>
//	
//	int main()
//	{
//		{
//			//	std::ifstream in("test.txt");
//			//	std::string s;
//			//	
//			//	if (in.is_open())
//			//	{
//			//		in >> s;
//			//		std::cout << "입력받은 문자열 :: " << s << std::endl;
//			//	}
//			//	else
//			//	{
//			//		std::cout << "파일을 찾을 수 없습니다" << std::endl;
//			//	}
//			//	
//			//	in.close();
//			//	in.open("other.txt");
//			//	
//			//	if (in.is_open())
//			//	{
//			//		in >> s;
//			//		std::cout << "입력받은 문자열 :: " << s << std::endl;
//			//	}
//			//	else
//			//	{
//			//		std::cout << "파일을 찾을 수 없습니다" << std::endl;
//			//	}
//		}
//	
//		{
//			std::ifstream in("test.txt", std::ios::binary);
//			std::string s;
//	
//			int x;
//			if (in.is_open())
//			{
//				in.read((char*)(&x), 4);
//				std::cout << std::hex << x << std::endl;
//			}
//			else
//			{
//				std::cout << "파일을 찾을 수 없습니다" << std::endl;
//			}
//		}
//		
//	
//	
//		/*
//			- fstream
//				- fstream: C++의 파일 입출력 스트림
//				- fstream 객체 생성시 연동하고자 하는 파일의 경로를 전달하면 됨. 기본적으로는 상대경로로 소스파일 위치에서 찾음
//					- 파일이 존재하지 않는 등의 문제가 발생하여 열리지 않았다면 std::ifstream::is_open() 함수가 false를 리턴해줌
//				- cin(istream) 사용하는것 처럼 operator>>를 이용하여 내용을 읽을 수 있음. 공백 무시도 이전 콘솔 입출력 스트림과 동일함
//					- 이는 fstream이 istream에서 상속받아 사용중이기 때문임
//						-> 실제 소스 내용
//	
//							_EXPORT_STD template <class _Elem, class _Traits>
//							class basic_fstream : public basic_iostream<_Elem, _Traits>
//	
//						-> 이전에 그린 C++ 입출력 스트림의 상속구조를 보면 iostream은 istream과 ostream를 다중상속 받음
//	
//				- 기존 C의 fopen과 달리 직접 close 할 필요가 없는데 이는 fstream이 소멸자에서 자동으로 close 해주기 때문임
//					-> 다만 기존 파일 스트림과 연결을 닫고 새로운 파일을 연결시켜주려면 close를 해주어야함. 
//					-> 새로운 파일을 열때는 굳이 생성자를 다시 쓸 필요는 없고 open() 함수를 이용하면 됨
//				- 형식 플래그를 이용해서 다른 형태로 읽고 쓰기도 가능함
//					- 위 코드에서 in("test.txt", std::ios::binary); 에서 ifstream 객체 생성시 binary 형태로 받겠다고 명시함(이진)
//					- 이후 in.read((char*)(&x), 4); 에서는 4바이트 짜리 내용을 읽으라는 의미로 int변수를 4바이트 char 배열로 캐스팅하여 저장
//						-> read() 함수 사용시에는 반드시 몇바이트를 읽을지 명시해야함
//						-> 이후 이전에 배운 std::hex 조작자를 이용하여 16진수로 출력함. 참고로 리틀 엔디안 시스템이므로 높은 주소부터 출력
//		
//		*/
//		return 0;
//	}

// 파일 전체 읽기: 한번에 다 읽기, 한줄씩 읽기

//	#include <fstream>
//	#include <iostream>
//	#include <string>
//	
//	int main()
//	{
//		// 파일 전체를 한번에 읽기
//	
//		{
//			std::ifstream in("test.txt");
//			std::string s;
//	
//			if (in.is_open())
//			{
//				// 위치 지정자를 파일 끝으로 옮긴다
//				in.seekg(0, std::ios::end);
//	
//				// 그리고 그 위치를 읽는다. (파일의 크기)
//				int size = in.tellg();
//	
//				// 그 크기의 문자열을 할당한다.
//				s.resize(size);
//	
//				// 위치 지정자를 다시 파일 맨 앞으로 옮긴다
//				in.seekg(0, std::ios::beg);
//	
//				// 파일 전체 내용을 읽어서 문자열에 저장한다.
//				in.read(&s[0], size);
//				std::cout << s << std::endl;
//			}
//			else
//			{
//				std::cout << "파일을 찾을 수 없습니다" << std::endl;
//			}
//	
//			/*
//				- 파일 전체 한번에 읽기
//					- 코드 설명
//						- in.seekg(0, std::ios::end)
//							-> seekg(): C의 fseek과 같은 함수로, 파일 위치 지정자를 입맛에 맞게 움직일 수 있음
//							-> 두번째 인자가 파일 내 위치를 의미하고, 첫번째 위치는 그 위치로부터 얼만큼 떨어져 있느냐를 의미함
//								-> 파일의 끝(std::ios::end)에서 0만큼 떨어진 곳 즉, 파일의 끝으로 이동됨
//						- int size = in.tellg()
//							-> tellg(): 위치 지정자의 위치(시작지점으로부터)를 반환
//							-> 위에서 위치 지정자를 파일 끝으로 이동시켰으므로 위치 지정자의 위치는 파일의 크기(바이트 크기)를 반환함
//							-> 이후 string을 파일 크기만큼 할당
//						- in.read(&s[0], size);
//							-> 파일 전체 내용을 문자열에 저장
//			
//			*/
//		}
//	
//		// 파일 전체를 한줄씩 읽기
//	
//		{
//			std::ifstream in("test.txt");
//			char buf[100];
//			std::string s;
//	
//			if (!in.is_open())
//			{
//				std::cout << "파일을 찾을 수 없습니다 " << std::endl;
//				return 0;
//			}
//	
//			while (in)
//			{
//				//	in.getline(buf, 100);
//				//	std::cout << buf << std::endl;
//				getline(in, s);
//				std::cout << s << std::endl;
//			}
//	
//			/*
//				- 파일 전체 한줄씩 읽기
//					- 코드 설명
//						- while(in)
//							-> ifstream 에는 자기 자신을 bool로 캐스팅하는 operator bool() 캐스팅 연산자가 오버로딩 되어있음(정확히는 ios에서 상속받음)
//							-> bool의 결과가 true려면 "다음 입력 작업이 성공적"이여만 함
//							-> !!!!! 절대로 in.eof()가 루프의 조건으로 오면 안됨 !!!!!
//								-> in.eof()는 파일 위치 지시자가 파일의 끝(eof)에 도달한 "이후"에 true를 리턴함
//								-> in.eof()는 다음 입력이고 뭐고 현재의 파일 위치자를 보기 때문에 다음 입력 작업이 eof여도 true를 리턴하지 않음
//								-> 즉, in.eof()는 "파일 읽기가 안전하다" 라는 것을 보장하지 못함!!
//								-> 그러므로 in.eof()를 사용하여 while문을 돌면 맨 마지막에는 아무것도 들어가지 않음
//						- in.getline(buf, 100)
//							-> 첫번째 인자에는 저장할 위치, 두번째 인자로는 저장할 위치의 최대 크기를 받음
//							-> 개행문자 '\n'이 나오기 전까지 (최대 지정한 크기 - 1)만큼의 파일을 읽어들임. -1은 마지막 널 종료 문자를 넣기 위함임
//							-> 만약 개행문자가 아닌 다른 사용자 지정 문자까지만 읽고싶다면 인자가 3개인 버전이 있음
//								-> getline(buf, 100, '.') 이런 식으로, 세번째 인자에 전달한 문자가 나올때까지 읽어들임
//							-> 그러나 ifstream의 getline()은 개행문자(혹은 지정한 문자) 가 나오기 전에 지정한 버퍼의 크기가 다 차면 failbit을 켜버림
//								-> 그러므로 저장할 버퍼를 충분히 크게 만들어 주거나 아래의 방법을 사용해야함
//							-> std::string에 정의된 getline()
//								-> ifstream(정확히는 istream에 있음)의 getline과 달리 string에 정의되어있는 다른 함수임
//								-> 첫번째 인자로 istream 인자를 받고, 두번째 인자로 입력받은 문자열을 저장할 string 객체를 받음
//								-> string이 가변 길이 문자열이므로 ifstream::getline()과 달리 버퍼의 크기를 신경쓸 필요가 없이 알아서 개행문자까지 읽어줌
//			*/
//		}
//	
//		return 0;
//	}

// 파일에 쓰기

//	#include <iostream>
//	#include <fstream>
//	#include <string>
//	
//	class Human
//	{
//	public:
//		Human(const std::string& name, int age) : name(name), age(age) {}
//	
//		std::string get_info()
//		{
//			return "Name :: " + name + " / Age :: " + std::to_string(age);
//		}
//	
//		friend std::ofstream& operator<<(std::ofstream& o, Human& h);
//	
//	private:
//		std::string name;
//		int age;
//	};
//	
//	std::ofstream& operator<<(std::ofstream& o, Human& h)
//	{
//		o << h.get_info();
//		return o;
//	}
//	
//	int main()
//	{
//		// 파일 쓰기 기본
//		{
//			std::ofstream out("outtest.txt");
//		
//			std::string s;
//			if (out.is_open())
//			{
//				out << "이걸 쓰자";
//			}
//		
//			/*
//				- 파일에 쓰기
//					- 코드 설명
//						- std::ofstream out("outtest.txt")
//							-> ofstream은 열 파일의 경로를 인자로 받아 생성하고 없으면 생성함
//							-> 특별한 설정을 하지 않으면 해당 파일 내용이 다 지워지고 새로운 내용으로 덮어씀
//						- out << "이걸 쓰자:
//							-> ostream을 기반으로 하는 클래스이므로 cout 쓰듯이 operator<< 를 이용하여 입력 가능함
//			*/
//		}
//	
//		// 파일 쓰기: 덧붙이기
//		//	{
//		//		std::ofstream out("outtest.txt", std::ios::app);
//		//	
//		//		std::string s;
//		//		if (out.is_open())
//		//		{
//		//			out << "덧붙이기";
//		//		}
//		//	
//		//		/*
//		//			- 파일에 쓰기: 덧붙이기
//		//				- 코드 설명
//		//					- std::ofstream out("outtest.txt", std::ios::app)
//		//						-> ofstream 객체 생성시 옵션으로 std::ios::app를 주면 기존 파일을 지우지않고 그 뒤에 덧붙임
//		//						-> 파일을 열때 옵션으로 줄 수 있는 플래그로 아래에서 이어서 설명
//		//		*/
//		//	}
//	
//		// 파일쓰기: Openmode
//		{
//			// abc1, abc2 모두 abc만 적혀있음
//			std::ofstream out("abc1.txt", std::ios::app);
//			std::ofstream out2("abc2.txt", std::ios::ate);
//		
//			out.seekp(3, std::ios::beg);
//			out2.seekp(3, std::ios::beg);
//		
//			out << "추가";
//			out2 << "추가";
//	
//			/*
//				- Openmode
//					- 상태 플래그나 형식 플래그처럼 ios 클래스에 정의되었는 플래그로 파일을 열때 어떻게 열지를 선택할 수 있음
//						-> 실제 구현. <xiosbase>에 정의되어있음
//							enum _Openmode { // constants for file opening options
//								_Openmask = 0xff
//							};
//	
//							static constexpr int in         = 0x01;
//							static constexpr int out        = 0x02;
//							static constexpr int ate        = 0x04;
//							static constexpr int app        = 0x08;
//							static constexpr int trunc      = 0x10;
//							static constexpr int _Nocreate  = 0x40;
//							static constexpr int _Noreplace = 0x80;
//							static constexpr int binary     = 0x20;
//						-> 이전에 사용했던 app, binary도 보임
//	
//					- 각각의 플래그에 대해서는 아래와 같음
//						- ios::app : 자동으로 파일 끝에서 부터 읽기와 쓰기를 실시함(즉, 파일을 열때 위치 지정자가 파일 끝을 가리킴)
//						- ios::ate : 자동으로 파일 끝에서 부터 읽기와 쓰기를 실시함(즉, 파일을 열때 위치 지정자가 파일 끝을 가리킴)
//						- ios::trunc : 파일 스트림을 열면 기존의 있던 내용들이 모두 지워짐
//							-> 기본적으로 ofstream 객체 생성시 이 옵션을 사용함
//						- ios::in, ios::out : 파일에 입력을 할 지, 출력을 할 지 결정함. 
//							-> ifstream과 ofstream객체 생성시 기본으로 설정 되어있고 위의 다른 플래그들과 비트마스크 연산과 함께 적용되는것으로 추정
//								-> 잘보면 최하위 비트 2개만 가지고 작동 가능한데 01이면 in, 10이면 out, 11이면 둘다 되는듯. 정확히는 모르겠음
//								-> 그냥 fstream의 기본 생성자의 openmode 인자의 디폴트가 ios_base::in | ios_base::out 으로 되있는거 보면 아마도 맞을듯
//					- ios::app과 ios::ate의 차이점
//						-> ios::app : 원본 파일의 내용을 무조건 보장 -> 위치 지정자가 기존 파일의 끝이 시작점이라고 생각하여 움직임 (seek to the end of stream before each write)
//						-> ios::ate : 원본 파일의 내용을 보장하지 않음 -> 위치 지정자가 기존 파일을 포함해서 움직임 (seek to the end of stream immediately after open)
//							-> 위 코드에서...
//								- ios::app으로 연 abc1.txt 
//									-> 기존 파일의 끝을 시작점으로 생각함
//									-> 그러므로 seekp()로 위치 지정자가 움직일 공간이 없어 abc 를 보존하고 "추가"를 덧붙임
//								- ios::ate으로 연 abc2.txt
//									-> 기존의 파일 내용을 포함함
//									-> 그러므로 seekp() 위치 지정자가 시작점으로부터 3만큼 떨어진 곳으로 이동됨
//									-> 이후 "추가"를 덧붙였지만 기존의 abc는 모두 지워짐
//								-> 결론: ios::ate를 이용해도 기존 파일에 덧붙이거나 끼워넣는 것이 불가능함
//			*/
//		}
//	
//		// 파일 쓰기: ofstream 연산자 오버로딩
//		{
//			std::ofstream out("test.txt");
//		
//			Human h("ㅇㅇㅇ", 20);
//			out << h << std::endl;
//		
//			/*
//				- operator<< 오버로딩
//					std::ofstream& operator<<(std::ofstream& o, Human& h)
//					{
//						o << h.get_info();
//						return o;
//					}
//					- ofstream 객체의 레퍼런스와 사용할 타입을 인자로 받아 오버로딩 시킴
//					- 스트림에 내용을 입력한 다음 ofstream 객체를 리턴하면 됨
//	
//			*/
//		}
//	
//		
//	
//		return 0;
//	}

// stringstream

#include <iostream>
#include <sstream>
#include <string>
double to_number(std::string s)
{
	std::istringstream ss(s);
	double x;

	ss >> x;
	return x;
}

std::string to_str(int x)
{
	std::ostringstream ss;
	ss << x;

	return ss.str();	// std::ostringstream::str() : 문자열 스트림의 값을 문자열로 불러옴
}

int main()
{
	// stringstream

	//	{
	//		std::istringstream ss("123");
	//		int x;
	//		ss >> x;
	//	
	//		std::cout << "입력받은 데이터 :: " << x << std::endl;
	//	
	//		/*
	//			output:
	//			입력받은 데이터 :: 123
	//		*/
	//	}

	// stringstream으로 문자열 < - > 숫자로 만드는 함수 만들기
	{
		std::cout << "문자열 -> 숫자 변환:: 1 + 2 = " << to_number("1") + to_number("2") << std::endl;
		std::cout << "숫자 -> 문자열 변환:: 1 + 2 = " << to_str(1 + 2) << std::endl;
		
		/*
			output:
			문자열 -> 숫자 변환:: 1 + 2 = 3
			숫자 -> 문자열 변환:: 1 + 2 = 3
		*/
	}

	/*
		- stringstream
			- 문자열을 하나의 스트림이라 생각하게 해주는 가상화 장치
			- 위 코드의 분석
				- std::istringstream ss("123") : 문자열 "123"이 기록되어 있는 입력 스트림 생성
					-> 파일에 123 을 기록해놓고 입력받는것과 동일하게 보면 됨
				- ss >> x : 파일에서 숫자를 읽어내는것 처럼 123을 읽을 수 있음
					-> 즉 atoi() 같은 함수 없이 간편하게 문자열에서 숫자로 변환할 수 있음
					-> 실제 함수의 예시는 위 to_number와 to_str를 참고
			- 일반 stream과 마찬가지로 입력시에는 istringstream, 출력시에는 ostringstream을 사용하면 됨

	
	
	*/

	return 0;
}
