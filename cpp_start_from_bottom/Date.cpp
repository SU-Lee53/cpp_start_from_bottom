#include "Date.h"
#include <iostream>

Date::Date(int year, int month, int day)
{
	std::cout << "일반 생성자 -> " << this << std::endl;
	SetDate(year, month, day);

	Adjust();
}

Date::Date(const Date& Origin)
{
	std::cout << "복사 생성자 -> " << this << std::endl;
	SetDate(Origin._year, Origin._month, Origin._day);

	Adjust();
}

Date::~Date()
{
}

void Date::SetDate(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
}

void Date::AddDay(int inc)
{
	// 더해진 날짜가 충분히 클경우 1달이 아닌 여러달이 지나갈수도 있음
	// 그러므로 더해진 직후 원래 날짜로부터 몇달이 지났는지를 구해야함
	int origin = _day;

	Endday endday = GetEndday(_month);
	int roundUp = 0;

	while (true)
	{
		if(static_cast<int>(endday) <= inc)
		{
			inc -= static_cast<int>(endday);
			AddMonth(1);
			endday = GetEndday(_month);
		}
		else
		{
			break;
		}
	}

	_day += inc;
	
}

void Date::AddMonth(int inc)
{
	_month += inc;

	// 12보다 작거나 같으면 리턴
	if (_month <= 12)
		return;

	// 12를 넘어가면 자리올림 필요
	int roundUp = _month / 12;
	_month %= 12;
	AddYear(roundUp);
}

void Date::AddYear(int inc)
{
	_year += inc;
}

void Date::ShowDate()
{
	std::cout << _year << "-" << _month << "-" << _day << std::endl;
}

Endday Date::GetEndday(int month)
{
	if (month == 2)
	{
		if (IsLeapyear())
		{
			return Endday::END_29;
		}
		return Endday::END_28;
	}
	else
	{
		// 7월까지는 짝수달의 경우 30일로 끝남
		// 8월부터는 홀수달이 30일로 끝남
		if (month <= 7)
		{
			if (month % 2 == 0)
			{
				return Endday::END_30;
			}
			return Endday::END_31;
		}
		else
		{
			if (month % 2 == 0)
			{
				return Endday::END_31;
			}
			return Endday::END_30;
		}
	}
}

bool Date::IsLeapyear()
{
	// (4의 배수인 해 AND 100의 배수가 아닌 해) OR 400의 배수인 해
	if ((_year % 4 == 0 && _year % 100 != 100) || _year % 400 == 0)
		return true;

	return false;
}

Date Date::operator+(int day)
{
	// 현재 날짜에서 하루를 더한 날짜로 새로운 인스턴스를 만들어야함
	Date ret = *this;
	ret.AddDay(day);

	return ret;
	// 이거 분명히 문제 있는 코드임 확인 후 수정
	// 아마도 기본 복사 생성자에서 얕은 복사를 수행하면 문제 발생 가능성 높음
}

Date Date::operator+(Date& date)
{
	Date ret = *this;
	ret.AddYear(date._year);
	ret.AddMonth(date._month);
	ret.AddDay(date._day);
	// 참조로 가져온 다른 객체의 private를 가져온다? 이거 맞나? 

	return ret;
	// 위와 마찬가지로 문제 발생 가능성 높음
}

void Date::Adjust()
{
	if (_month > 12)
	{
		_month -= 12;
		std::cout << "날짜 조정됨" << std::endl;
	}

	if (_day > static_cast<int>(GetEndday(_month)))
	{
		_day -= (static_cast<int>(GetEndday(_month)));
		AddMonth(1);
		std::cout << "날짜 조정됨" << std::endl;
	}
	

	std::cout << "날짜 생성됨 -> ";
	ShowDate();
	
	
}

