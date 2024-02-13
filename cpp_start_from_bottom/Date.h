#pragma once

/*
	고려해야 할 점
		- 30일로 끝나는 달과 31로 끝나는 달 == 짝/홀
		- 2월은 28일까지
		- 윤년(leap year)에는 2월이 29일까지 있음 -> 4년에 1번
		- 윤년 규칙(나무위키)
			- 먼저 끝 두자리가 4의 배수인 해는 무조건 윤년이다. (예: 1996년, 2004년, 2020년...)
			- 4의 배수라도 끝 두자리가 00인 해는 예외적으로 평년이다. (예: 1900년, 2100년, 2200년...)
			- 끝 두자리가 00인 해 중에서도 그 윗 자리가 4의 배수가 되는 해는 다시 윤년이다. (예: 2000년, 2400년)
			- 결론 : (4의 배수인 해 AND 100의 배수가 아닌 해) OR 400의 배수인 해
		- 그렇다면 이 끝나는 날짜는 무엇으로 표현?
			- 30, 31말고 2월도 있으므로 bool으로는 부족함
			- enum이 좋겠다 아님 말고
			
*/

enum class Endday
{
	END_30 = 30,
	END_31 = 31,
	END_28 = 28,
	END_29 = 29,
	None = 0
};

enum class Week
{
	SUN = 0,
	MON,
	TUE,
	WED,
	THU,
	FRI,
	SAT
};

class Date
{
public:
	Date(int year, int month, int day);
	Date(const Date& Origin);
	~Date();
	void SetDate(int year, int month, int day);
	void AddDay(int inc);
	void AddMonth(int inc);
	void AddYear(int inc);

	void ShowDate();

	Endday GetEndday(int month);
	bool IsLeapyear();

	Date operator+(int day);
	Date operator+(Date& date);

private:
	unsigned int _year;
	unsigned int _month;
	unsigned int _day;
	Week _week;

	void Adjust();


};

