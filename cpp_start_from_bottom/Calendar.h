#pragma once


class Date;




class Calendar
{
public:
	Calendar(int year);
	~Calendar();

	void SetCalendar(int year);
	

private:
	Date _standard;

	void GetStartWeek(int year);

};

