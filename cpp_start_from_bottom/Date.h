#pragma once

/*
	����ؾ� �� ��
		- 30�Ϸ� ������ �ް� 31�� ������ �� == ¦/Ȧ
		- 2���� 28�ϱ���
		- ����(leap year)���� 2���� 29�ϱ��� ���� -> 4�⿡ 1��
		- ���� ��Ģ(������Ű)
			- ���� �� ���ڸ��� 4�� ����� �ش� ������ �����̴�. (��: 1996��, 2004��, 2020��...)
			- 4�� ����� �� ���ڸ��� 00�� �ش� ���������� ����̴�. (��: 1900��, 2100��, 2200��...)
			- �� ���ڸ��� 00�� �� �߿����� �� �� �ڸ��� 4�� ����� �Ǵ� �ش� �ٽ� �����̴�. (��: 2000��, 2400��)
			- ��� : (4�� ����� �� AND 100�� ����� �ƴ� ��) OR 400�� ����� ��
		- �׷��ٸ� �� ������ ��¥�� �������� ǥ��?
			- 30, 31���� 2���� �����Ƿ� bool���δ� ������
			- enum�� ���ڴ� �ƴ� ����
			
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

