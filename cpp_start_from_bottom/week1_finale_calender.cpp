#include <iostream>
#include "Date.h"

/*
	목표
		- 간단하게 달력을 CPP로 작성
		- 달력을 객체로 만듬 -> 연, 월, 일
			- 객체 생성시 연도를 받고 1년치 달력을 통째로 만든다
			- 1년 통째로 출력과 달별 출력을 만든다
		- 날짜 Date 객체도 만듬
		- 모두의 코드 연습문데 그대로 함수를 구현
			- SetDate(int year, int month, int date)
			- AddDay(int inc)
			- AddMonth(int inc)
			- AddYear(int inc)
		- 나중에 Winapi 공부시 달력을 만들어 출력해볼 예정

	고민사항
		- Date를 Calendar를 상속받는 클래스로 만들어도 될까?
			- is-a/has-a 관계를 생각해보면 Date 는 Calendar라기 보다 Calendar 안에 Date가 존재하는것이 더 적절
			- Date를 먼저 만들고 Calendar가 멤버로 들고있는게 낫겠다
		- Add 시리즈 함수를 만들때 연산자 오버로딩과 함수 오버로딩을 사용할 수 있을까?
			- 해보고 판단
		- SetDate는 생성자로 대체하는것이 좋지 않을까
			- 그냥 생성자로 ㄱㄱ 
			- 별도로 날짜를 재지정할 필요도 있으므로 함수는 만드는게 좋을듯함
		- 자리올림의 고려순서
			- 일 -> 월 -> 연?
			- 연 -> 일 -> 월? 이게 더 옳은듯 하다
*/

int main()
{
	Date* day = new Date(2023, 1, 1);
	std::cout << day << std::endl;

	for (int i = 0; i < 730; i++)
	{
		(*day + i).ShowDate();
	}


}