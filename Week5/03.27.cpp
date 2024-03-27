/*
	- 03.27 C++ 스타일 캐스팅

*/

// - C++ 스타일 캐스팅

#include <iostream>

int main()
{
	// C 스타일 캐스팅
	int a = 10;
	double b = 3.14;

	double c = b + (double)a;	// 명시적으로 캐스팅 하지 않아도 컴파일러에서 암시적으로 캐스팅 가능
	std::cout << c << std::endl;

	// C++ 스타일 캐스팅



	/*
		- 암시적(implicit) 캐스팅 / 명시적(explicit) 캐스팅
			- 암시적 캐스팅: 컴파일러가 알아서 상황에 맞게 캐스팅 하는것 ex) int 와 double 간의 덧셈에서 컴파일러가 자동으로 int를 double로 캐스팅ㅈ
			- 명시적 캐스팅: 사용자가 직접 지정하는 캐스팅

		- 기존의 C스타일 명시적 캐스팅 : (타입)변수
	
		- C++의 4가지 캐스팅
			1) static_cast : 일반적으로 생각하는 타입변환
			2) const_cast : 객체의 상수성을 없애는 타입변환 ex) const int -> int
			3) dynamic_cast : 파생 클래스 사이에서의 다운캐스팅
			4) reinterpret_cast : 위험을 감수하고 하는 캐스팅으로 서로 관련이 없는 포인터들 사이의 캐스팅 (reinterpret 의 뜻 : 재해석)
			- 캐스팅 방법 : (원하는 캐스팅)<바꾸려는 타입>(바꾸려는 대상)
	
	*/


	
}