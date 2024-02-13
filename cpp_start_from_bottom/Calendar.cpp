#include "Calendar.h"
#include "Date.h"

Calendar::Calendar(int year) : _standard(Date(year,1,1))
{
	GetStartWeek(year);
}

Calendar::~Calendar()
{
}

void Calendar::SetCalendar(int year)
{
	_standard.~Date();
	_standard = Date(year, 1, 1);
}

void Calendar::GetStartWeek(int year)
{
	

}
