#include "Date.h"
#include <iostream>

Date::Date(int year, int month, int day)
{
	std::cout << "�Ϲ� ������ -> " << this << std::endl;
	SetDate(year, month, day);

	Adjust();
}

Date::Date(const Date& Origin)
{
	std::cout << "���� ������ -> " << this << std::endl;
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
	// ������ ��¥�� ����� Ŭ��� 1���� �ƴ� �������� ���������� ����
	// �׷��Ƿ� ������ ���� ���� ��¥�κ��� ����� ���������� ���ؾ���
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

	// 12���� �۰ų� ������ ����
	if (_month <= 12)
		return;

	// 12�� �Ѿ�� �ڸ��ø� �ʿ�
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
		// 7�������� ¦������ ��� 30�Ϸ� ����
		// 8�����ʹ� Ȧ������ 30�Ϸ� ����
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
	// (4�� ����� �� AND 100�� ����� �ƴ� ��) OR 400�� ����� ��
	if ((_year % 4 == 0 && _year % 100 != 100) || _year % 400 == 0)
		return true;

	return false;
}

Date Date::operator+(int day)
{
	// ���� ��¥���� �Ϸ縦 ���� ��¥�� ���ο� �ν��Ͻ��� ��������
	Date ret = *this;
	ret.AddDay(day);

	return ret;
	// �̰� �и��� ���� �ִ� �ڵ��� Ȯ�� �� ����
	// �Ƹ��� �⺻ ���� �����ڿ��� ���� ���縦 �����ϸ� ���� �߻� ���ɼ� ����
}

Date Date::operator+(Date& date)
{
	Date ret = *this;
	ret.AddYear(date._year);
	ret.AddMonth(date._month);
	ret.AddDay(date._day);
	// ������ ������ �ٸ� ��ü�� private�� �����´�? �̰� �³�? 

	return ret;
	// ���� ���������� ���� �߻� ���ɼ� ����
}

void Date::Adjust()
{
	if (_month > 12)
	{
		_month -= 12;
		std::cout << "��¥ ������" << std::endl;
	}

	if (_day > static_cast<int>(GetEndday(_month)))
	{
		_day -= (static_cast<int>(GetEndday(_month)));
		AddMonth(1);
		std::cout << "��¥ ������" << std::endl;
	}
	

	std::cout << "��¥ ������ -> ";
	ShowDate();
	
	
}

