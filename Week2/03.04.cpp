
/*
	03.04 함수 오버로딩
	03.05 생성자
*/

/*
	- 오버로딩(Overloading)  사전적 정의: 과적, 과부하
	- 함수 오버로딩(function overloading) -> 함수에 과부하를 준다?
		- C++은 같은 이름의 함수가 여러개 존재할 수 있음
		- 같은 이름의 함수는 사용하는 인자를 보고 결정하게됨
*/


// 함수 오버로딩의 작동
 
//	#include <iostream>
//	
//	void print(int x) { std::cout << "int : " << x << std::endl; }			// 인수로 int를 받음
//	void print(char x) { std::cout << "char : " << x << std::endl; }		// 인수로 char를 받음
//	void print(double x) { std::cout << "double : " << x << std::endl; }	// 인수로 double을 받음
//																			// 서로 다른 인수를 받는 함수 오버로딩 
//																			//	-> 컴파일러가 인수에 따라 적절한 함수를 호출해준다
//	
//	int main()
//	{
//		int a = 1;
//		char b = 'c';
//		double c = 3,2f;
//	
//		print(a);
//		print(b);
//		print(c);
//	
//		/*
//			output
//	
//			int : 1
//			char : c
//			double : 3,2
//		*/
//	
//		/*
//			만약에 print(char x)가 없다면 발생하는 output
//	
//			int : 1
//			int : 99
//			double : 3,2
//	
//			- 왜?
//				- a 와 c는 자신과 일치하는 인자를 가진 함수에 정상적으로 들어감
//				- b는 자신과 일치하는 인자를 가진 함수가 없음
//					-> 이때 b는 '자신과 최대로 근접한 함수'를 찾는다
//	
//			- 자신과 최대로 근접한 함수? 그걸 어떻게 판단하는가 -> 컴파일러가 함수를 오버로딩하는 과정
//				1) 자신과 타입이 정확하게 일치하는 함수를 찾는다
//				2) 정확히 일치하는 타입이 없는 경우 아래와 같은 형변환을 통해서 일치하는 함수를 찾는다
//					- char, unsigned char, short -> int (위의 경우)
//					- unsigned short -> int의 크기에 따라 int 혹은 unsigned int로 변환
//					- float -> double
//					- enum -> int
//				3) 2)에서의 변환으로도 일치하는것이 없다면 아래의 좀 더 포괄적인 형변환을 통해 일치하는 함수를 찾는다
//					- 임의의 숫자(numeric) 타입은 다른 숫자 타입으로 변환한다 ex) float -> int
//					- enum도 임의의 숫자 타입으로 변환된다 ex) enum -> double
//					- 0은 포인터 타입이나 숫자 타입으로 변환된 0은 포인터 타입이나 숫자 타입으로 변환된다
//					- 포인터는 void 포인터로 변환된다
//				4) 유저 정의된 타입 변환으로 일치하는것을 찾는다
//			
//			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//			※ 위의 판단기준은 cppreference의 overload resolution 문서의 Ranking of implicit conversion sequences에 더 자세히 나와있음, 아래에 설명
//				
//				Each type of standard conversion sequence is assigned one of three ranks:
//				각각의 타입에 대한 표준 변환 시퀀스는 아래 순위중 하나가 할당됨
//	
//					1) Exact match:																	정확한 일치:	
//									no conversion required,														형변환 필요X
//									lvalue-to-rvalue conversion,												좌측값->우측값 변환
//									qualification conversion,													const/volatile 변환 (확인필요)
//									function pointer conversion,(since C++17)									함수 포인터(C++17)
//									user-defined conversion of class type to the same class						유저가 지정한 현변환
//					2) Promotion:																	상승 변환:(더 많은 바이트를 가지는 타입으로 상승하는것을 말함)
//									integral promotion,															정수형
//									floating-point promotion													부동소수형
//					3) Conversion:																		변환:
//									integral conversion,														정수형 변환
//									floating-point conversion,													부동소수형 변환
//									floating-integral conversion,												정수-부동소수 변환
//									pointer conversion,															포인터 변환
//									pointer-to-member conversion,												포인터->멤버 변환
//									boolean conversion,															bool 변환
//									user-defined conversion of a derived class to its base						파생된 클래스->기존 클래스로의 유저 정의 변환
//				
//				The rank of the standard conversion sequence is the worst of the ranks of the standard conversions it holds (there may be up to three conversions)
//				표준 변환 시퀀스의 순위는 해당 시퀀스가 가진 순위중 최악임(대충 낮은 순위일수록 좋지 못하다는 뜻)
//	
//				Since ranking of conversion sequences operates with types and value categories only, 
//				a bit field can bind to a reference argument for the purpose of ranking, but if that function gets selected, it will be ill-formed,
//				변환 시퀀스 순위는 타입과 값에서만 작동하므로
//				비트필드는 순위 지정을 위해 참조 인수에 바인딩될 수 있지만 그렇게 함수가 작동되면 부정확한 형식(ill-formed)일 것임
//	
//			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	
//		*/
//	
//		/*
//		
//			위에 설명된 4가지 과정으로도 적절한 함수를 찾지 못하였거나 같은 단계에서 2개 이상이 일치하는 경우에는 모호하다(ambiguous)라고 판단하여 오류를 내보냄
//	
//			- 예시: 위 예시에서 print(double x)를 주석처리하고 실행
//				C2668 'print': 오버로드된 함수에 대한 호출이 모호합니다,
//				E0308 오버로드된 함수 "print"의 인스턴스 중 두 개 이상이 인수 목록과 일치합니다,
//					함수 "print(int x)" (선언됨 줄 14)
//					함수 "print(char x)" (선언됨 줄 15)
//					인수 형식이 (double)입니다,
//			
//			- 왜? 다시한번 위의 4단계 규칙을 보자
//				1) 자신과 타입이 정확하게 일치하는 함수를 찾는다
//				2) 정확히 일치하는 타입이 없는 경우 아래와 같은 형변환을 통해서 일치하는 함수를 찾는다
//					- char, unsigned char, short -> int (위의 경우)
//					- unsigned short -> int의 크기에 따라 int 혹은 unsigned int로 변환
//					- float -> double
//					- enum -> int
//				3) 2)에서의 변환으로도 일치하는것이 없다면 아래의 좀 더 포괄적인 형변환을 통해 일치하는 함수를 찾는다
//					- 임의의 숫자(numeric) 타입은 다른 숫자 타입으로 변환한다 ex) float -> int
//					- enum도 임의의 숫자 타입으로 변환된다 ex) enum -> double
//					- 0은 포인터 타입이나 숫자 타입으로 변환된 0은 포인터 타입이나 숫자 타입으로 변환된다
//					- 포인터는 void 포인터로 변환된다
//				4) 유저 정의된 타입 변환으로 일치하는것을 찾는다
//	
//				- 우선 double은 1, 2단계에서 일치하는 함수가 없음
//				- 3단계에서 double은 numeric타입이므로 int, char에 모두 들어갈 수 있게됨
//					-> 같은 단계에서 2개 이상의 일치 -> 모호하다!
//	
//				※ 아니 char이 numeric임? 문자타입 아님?
//					- char도 1바이트짜리 numeric이 맞음
//					- 간단히 아래의 예시로 확인가능
//						#include <type_traits>
//							std::cout << std::is_arithmetic<char>::value << std::endl; -> 1이 출력(true)
//					- arithmetic은 산술 연산이 가능한 타입을 말하고 numeric에 포함되는 개념임
//						-> 그러므로 arithmetic 타입이라면 동시에 numeric 타입임은 자명함
//	
//	
//		*/
//	
//		return 0;
//	}

// 오버로딩이 불가능한 경우들

//	/*
//		- 오버로딩이 불가능한 경우가 존재함(soen.kr)
//			1) 리턴 타입만 다른경우 - 아래의 int funcA()와 double funcA()
//				-> 함수의 리턴값은 함수의 실행을 마친 후에 적용되는 것이므로 
//				호출시점에 어떤 함수를 호출할 것인가를 결정하는 근거가 될 수 없음
//	
//			2) 인수 목록에 레퍼런스가 전달되는 경우와 일반변수가 전달되는 경우 - 아래의 int funcB()
//				-> 레퍼런스, 일반변수 모두 호출 형태가 동일하므로 모호함이 발생함. 정의 자체는 가능하지만 실제로는 아무런 의미가 없음
//				-> soen에서는 에러처리 한다고 하지만 실행결과 일반 변수 함수로 실행됨. 함수의 선언 순서와도 관계 없는것으로 보임
//	
//			3) const 지정자의 유무 - 아래의 int funC()	!!!! 일반 문자열과 리터럴 (char* 과 const char*은 오버로딩 가능) !!!!
//				-> main()에서 str1은 변경 가능하므로 char* s가, str2는 리터럴이므로 const char* s가 호출된다. 이 경우에는 오버로딩 가능함. str3은?
//				-> str3의 경우 포인터가 상수이고 내부의 값은 변경 가능하므로 char* 버전이 호출됨
//				-> 이때 char* const s를 오버로딩 할 경우 오류가 발생: C2084 'int funC(char *)' 함수에 이미 본문이 있습니다.
//					-> 포인터의 상수성은 실인수(값)의 상수성과 아무런 상관이 없으므로 호출시점에 어떤 함수가 정확한지 판단할 수 없기 때문
//	
//			4) 인수의 논리적 의미만 다른경우 - int func(int a)와 int func(int b)는 오버로딩이 안된다는 의미임. 당연한 부분이므로 PASS
//	
//			5) 디폴트 인수에 의해 같아질 수 있는경우 - 아래의 int funcD()
//				-> funcD(1,2)등으로 호출하였을때 구분이 되지 않음. 정의 자체는 가능하나 아무런 의미 없이 오류만 만드는 코드
//	
//			6) 달라보이지만 실제로는 같은 타입인 경우(typedef, 매크로 등에 의해서) - 아래의 int funcE(), int funcF()
//				-> 컴파일러는 당연히 이름이 아닌 실제 타입을 보고 오버로딩 시키므로 안되는것이 당연함
//				-> int* p와 int p[]의 경우는 둘다 같은 포인터형이므로 오버로딩이 불가능함
//	
//	*/
//	
//	#include <iostream>
//	
//	int funcA(int a, double b){ return a; }
//	//double funcA(int a, double b) { return a; }
//	
//	int funcB(int a, int B)
//	{
//		return a;
//	}
//	int funcB(int& a, int& b)
//	{
//		return a;
//	}
//	
//	int funcC(char *s) 
//	{
//		std::cout << "char*" << std::endl;
//		return 0;
//	}
//	int funcC(const char* s) 
//	{
//		std::cout << "const char*" << std::endl;
//		return 0;
//	}
//	//int funcC(char* const s) {}
//	
//	int funcD(int a, int b) { return a; }
//	int funcD(int a, int b, int c = 0) { return a; }
//	
//	#define THISISINTPTR int*
//	typedef int* THISISALSOINTPTR;
//	
//	int funcE(int* a) { return *a; }
//	int funcE(THISISINTPTR a) { return *a; }
//	int funcE(THISISALSOINTPTR a) { return *a; }
//	
//	int funcF(int* p) { return *p; }
//	int funcF(int p[]) { return *p; }
//	
//	int main()
//	{
//		char str1[] = "1234";
//		const char* str2 = "가나다라";
//		char* const str3 = str1;
//	
//		funcC(str1);
//		funcC(str2);
//		funcC(str3);
//		/*
//			output:
//				char*
//				const char*
//				char* 
//		
//		*/
//	
//	
//	
//	}


// 생성자 실습 -> Date 클래스

#include <iostream>

class Date
{
public:
	// 생성자 -> 아래에서 설명
	Date(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	//	사용자 지정 디폴트 생성자
	//	Date()
	//	{
	//		_year = 2014;
	//		_month = 4;
	//		_day = 4;
	//	} 

	// 명시적 디폴트 생성자
	// Date() = default;



	void SetDate(int year, int month, int date);
	void AddDay(int inc);
	void AddMonth(int inc);
	void AddYear(int inc);
	
	// 해당 월의 총 일수를 구한다
	int GetCurrentMonthTotalDays(int years, int month);

	void ShowDate();

private:
	int _year;
	int _month;
	int _day;
};

// Date::SetDate() -> 클래스 내부의 함수 정의. 일반적으로 헤더파일과 분리해서 많이 적던데 여기서는 한 파일에 모두 정의함
// 
// cppreference의 namespace 문서 (4)번의 설명
// ns-name::member-name -> Namespace names (along with class names) can appear on the left hand side of the scope resolution operator, as part of qualified name lookup.
// 네임스페이스의 이름(클래스 이름 포함)은 안정된 네임스페이스 탐색의 일부로 scope resolution operator(::)의 왼쪽에 올 수 있음
// ==> 정해진 네임스페이스의 이용을 위해서 사용된다고 이해

void Date::SetDate(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
}

int Date::GetCurrentMonthTotalDays(int year, int month)
{
	static int month_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month != 2)
	{
		return month_day[month - 1];
	}
	else if (year % 4 == 0 && year % 100 != 0)
	{
		return 29;	// 윤년
	}
	else
	{
		return 28;
	}
}

void Date::AddDay(int inc)
{
	while (true)
	{
		// 현재 달의 총 일수
		int currentMonthTotalDays = GetCurrentMonthTotalDays(_year, _month);

		// 같은 달 안에 들어온다면
		if (_day + inc <= currentMonthTotalDays)
		{
			_day += inc;
			return;
		}
		else
		{
			// 다음달로 넘어간다
			inc -= (currentMonthTotalDays - _day + 1);
			_day = 1;
			AddMonth(1);
		}
	}
}

void Date::AddMonth(int inc)
{
	AddYear((inc + _month - 1) / 12);
	_month = _month + inc % 12;
	_month = (_month == 12 ? 12 : _month % 12);
}

void Date::AddYear(int inc)
{
	_year += inc;
}

void Date::ShowDate()
{
	std::cout << "오늘은 " << _year << " 년 " << _month << " 월 " << _day << " 일 입니다" << std::endl;
}

int main(int argc, char** argv)
{
	//	Date day;
	//	day.SetDate(2011, 3, 1);
	//	day.ShowDate();
	//	
	//	day.AddDay(30);
	//	day.ShowDate();
	//	
	//	day.AddDay(2000);
	//	day.ShowDate();
	//	
	//	day.SetDate(2012, 1, 31);	// 윤년
	//	day.AddDay(29);
	//	day.ShowDate();
	//	
	//	day.SetDate(2012, 8, 4);
	//	day.AddDay(2500);
	//	day.ShowDate();

	/*
		output

		오늘은 2011 년 3 월 1 일 입니다
		오늘은 2011 년 3 월 31 일 입니다
		오늘은 2016 년 9 월 20 일 입니다
		오늘은 2012 년 2 월 29 일 입니다
		오늘은 2019 년 6 월 9 일 입니다
	*/

	//	만약에 SetDate없이 인스턴스를 생성한다면?
	//	Date day2;
	//	day2.ShowDate();	// 오늘은 -858993460 년 -858993460 월 -858993460 일 입니다

	/*
		- 위처럼 생성과 초기화를 분리시켜 놓았을때 초기화를 하지 않으면 쓰레기값이 들어가게됨
			-> 해결방안: 생성자의 도입으로 생성과 동시에 초기화

		- 생성자(Constructor): 객체 생성시 자동으로 호출되는 함수
			- 생성자의 정의: 클래스이름(인자) {}
			- 객체 생성시 자동으로 호출되어 "객체를 초기화 해주는 역할"을 담당함
			- 객체 생성시 본인이 정의한 생성자의 인수에 맞게 함수를 호출하듯이 해주면 됨
	*/

	// 생성자의 호출
	Date day(2011, 1, 1);				// 암시적 방법(implicit)
	Date day2 = Date(2012, 2, 2);		// 명시적 방법(explicit)

	Date* day3 = new Date(2013, 3, 3);	// 동적 할당

	day.ShowDate();
	day2.ShowDate();
	day3->ShowDate();

	/*
		- 만약에 처음에 했던대로 생성자를 별도로 만들지 않아도 생성자가 호출됨
			-> 이때 호출되는 생성자를 디폴트 생성자(Default Constructor)라고 부름(혹은 기본 생성자라고도 많이 불렀음)

		- 디폴트 생성자
			- 클래스에서 사용자가 어떠한 생성자도 명시적으로 정의하지 않은 경우 컴파일러가 자동으로 추가해주는 생성자
			- 인자를 하나도 가지지 않음
			- 직접 디폴트 생성자를 만들수도 있음
	*/

	// 사용자 정의된 디폴트 생성자의 호출
	Date day4 = Date();
	day4.ShowDate();

	// !!! 주의점 !!!
	// 아래의 방법은 day5라는 객체를 디폴트 생성자를 이용하여 초기화하는것이 아님
	//	-> 리턴값이 Date인 day5() 함수를 정의하게 된것으로 인식
	Date day5();

	/*
		- 명시적 디폴트 생성자
			- C++11 이전에는 디폴트 생성자를 사용하고 싶은경우 그냥 생성자를 정의하지 않는것이 유일한 방법
				-> 이 경우 코드를 읽는 사용자는 개발자가 깜빡하고 생성자를 정의하지 않은것인지 아니면 의도한것인지 정확히 알 수 없었음
			- C++11 이후에는 명시적으로 디폴트 생성자를 만들 수 있음
				-> 인자가 없는 기본 생성자에 = default;를 붙여주면 됨
				-> 위 Date() = dafault가 명시적 디폴트 생성자의 예시 -> 쓰레기값이 들어가지 않고 멤버변수가 0으로 초기화됨
	*/
	
	/*
		- 생성자 오버로딩
			- 생성자도 함수 -> 오버로딩이 가능
			- 위에서 자연스럽게 사용중이었으므로 예시는 PASS

	*/

	return 0;
}
