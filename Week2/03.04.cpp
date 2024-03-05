
/*
	03.04 �Լ� �����ε�
	03.05 ������
*/

/*
	- �����ε�(Overloading)  ������ ����: ����, ������
	- �Լ� �����ε�(function overloading) -> �Լ��� �����ϸ� �ش�?
		- C++�� ���� �̸��� �Լ��� ������ ������ �� ����
		- ���� �̸��� �Լ��� ����ϴ� ���ڸ� ���� �����ϰԵ�
*/


// �Լ� �����ε��� �۵�
 
//	#include <iostream>
//	
//	void print(int x) { std::cout << "int : " << x << std::endl; }			// �μ��� int�� ����
//	void print(char x) { std::cout << "char : " << x << std::endl; }		// �μ��� char�� ����
//	void print(double x) { std::cout << "double : " << x << std::endl; }	// �μ��� double�� ����
//																			// ���� �ٸ� �μ��� �޴� �Լ� �����ε� 
//																			//	-> �����Ϸ��� �μ��� ���� ������ �Լ��� ȣ�����ش�
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
//			���࿡ print(char x)�� ���ٸ� �߻��ϴ� output
//	
//			int : 1
//			int : 99
//			double : 3,2
//	
//			- ��?
//				- a �� c�� �ڽŰ� ��ġ�ϴ� ���ڸ� ���� �Լ��� ���������� ��
//				- b�� �ڽŰ� ��ġ�ϴ� ���ڸ� ���� �Լ��� ����
//					-> �̶� b�� '�ڽŰ� �ִ�� ������ �Լ�'�� ã�´�
//	
//			- �ڽŰ� �ִ�� ������ �Լ�? �װ� ��� �Ǵ��ϴ°� -> �����Ϸ��� �Լ��� �����ε��ϴ� ����
//				1) �ڽŰ� Ÿ���� ��Ȯ�ϰ� ��ġ�ϴ� �Լ��� ã�´�
//				2) ��Ȯ�� ��ġ�ϴ� Ÿ���� ���� ��� �Ʒ��� ���� ����ȯ�� ���ؼ� ��ġ�ϴ� �Լ��� ã�´�
//					- char, unsigned char, short -> int (���� ���)
//					- unsigned short -> int�� ũ�⿡ ���� int Ȥ�� unsigned int�� ��ȯ
//					- float -> double
//					- enum -> int
//				3) 2)������ ��ȯ���ε� ��ġ�ϴ°��� ���ٸ� �Ʒ��� �� �� �������� ����ȯ�� ���� ��ġ�ϴ� �Լ��� ã�´�
//					- ������ ����(numeric) Ÿ���� �ٸ� ���� Ÿ������ ��ȯ�Ѵ� ex) float -> int
//					- enum�� ������ ���� Ÿ������ ��ȯ�ȴ� ex) enum -> double
//					- 0�� ������ Ÿ���̳� ���� Ÿ������ ��ȯ�� 0�� ������ Ÿ���̳� ���� Ÿ������ ��ȯ�ȴ�
//					- �����ʹ� void �����ͷ� ��ȯ�ȴ�
//				4) ���� ���ǵ� Ÿ�� ��ȯ���� ��ġ�ϴ°��� ã�´�
//			
//			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//			�� ���� �Ǵܱ����� cppreference�� overload resolution ������ Ranking of implicit conversion sequences�� �� �ڼ��� ��������, �Ʒ��� ����
//				
//				Each type of standard conversion sequence is assigned one of three ranks:
//				������ Ÿ�Կ� ���� ǥ�� ��ȯ �������� �Ʒ� ������ �ϳ��� �Ҵ��
//	
//					1) Exact match:																	��Ȯ�� ��ġ:	
//									no conversion required,														����ȯ �ʿ�X
//									lvalue-to-rvalue conversion,												������->������ ��ȯ
//									qualification conversion,													const/volatile ��ȯ (Ȯ���ʿ�)
//									function pointer conversion,(since C++17)									�Լ� ������(C++17)
//									user-defined conversion of class type to the same class						������ ������ ����ȯ
//					2) Promotion:																	��� ��ȯ:(�� ���� ����Ʈ�� ������ Ÿ������ ����ϴ°��� ����)
//									integral promotion,															������
//									floating-point promotion													�ε��Ҽ���
//					3) Conversion:																		��ȯ:
//									integral conversion,														������ ��ȯ
//									floating-point conversion,													�ε��Ҽ��� ��ȯ
//									floating-integral conversion,												����-�ε��Ҽ� ��ȯ
//									pointer conversion,															������ ��ȯ
//									pointer-to-member conversion,												������->��� ��ȯ
//									boolean conversion,															bool ��ȯ
//									user-defined conversion of a derived class to its base						�Ļ��� Ŭ����->���� Ŭ�������� ���� ���� ��ȯ
//				
//				The rank of the standard conversion sequence is the worst of the ranks of the standard conversions it holds (there may be up to three conversions)
//				ǥ�� ��ȯ �������� ������ �ش� �������� ���� ������ �־���(���� ���� �����ϼ��� ���� ���ϴٴ� ��)
//	
//				Since ranking of conversion sequences operates with types and value categories only, 
//				a bit field can bind to a reference argument for the purpose of ranking, but if that function gets selected, it will be ill-formed,
//				��ȯ ������ ������ Ÿ�԰� �������� �۵��ϹǷ�
//				��Ʈ�ʵ�� ���� ������ ���� ���� �μ��� ���ε��� �� ������ �׷��� �Լ��� �۵��Ǹ� ����Ȯ�� ����(ill-formed)�� ����
//	
//			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	
//		*/
//	
//		/*
//		
//			���� ����� 4���� �������ε� ������ �Լ��� ã�� ���Ͽ��ų� ���� �ܰ迡�� 2�� �̻��� ��ġ�ϴ� ��쿡�� ��ȣ�ϴ�(ambiguous)��� �Ǵ��Ͽ� ������ ������
//	
//			- ����: �� ���ÿ��� print(double x)�� �ּ�ó���ϰ� ����
//				C2668 'print': �����ε�� �Լ��� ���� ȣ���� ��ȣ�մϴ�,
//				E0308 �����ε�� �Լ� "print"�� �ν��Ͻ� �� �� �� �̻��� �μ� ��ϰ� ��ġ�մϴ�,
//					�Լ� "print(int x)" (����� �� 14)
//					�Լ� "print(char x)" (����� �� 15)
//					�μ� ������ (double)�Դϴ�,
//			
//			- ��? �ٽ��ѹ� ���� 4�ܰ� ��Ģ�� ����
//				1) �ڽŰ� Ÿ���� ��Ȯ�ϰ� ��ġ�ϴ� �Լ��� ã�´�
//				2) ��Ȯ�� ��ġ�ϴ� Ÿ���� ���� ��� �Ʒ��� ���� ����ȯ�� ���ؼ� ��ġ�ϴ� �Լ��� ã�´�
//					- char, unsigned char, short -> int (���� ���)
//					- unsigned short -> int�� ũ�⿡ ���� int Ȥ�� unsigned int�� ��ȯ
//					- float -> double
//					- enum -> int
//				3) 2)������ ��ȯ���ε� ��ġ�ϴ°��� ���ٸ� �Ʒ��� �� �� �������� ����ȯ�� ���� ��ġ�ϴ� �Լ��� ã�´�
//					- ������ ����(numeric) Ÿ���� �ٸ� ���� Ÿ������ ��ȯ�Ѵ� ex) float -> int
//					- enum�� ������ ���� Ÿ������ ��ȯ�ȴ� ex) enum -> double
//					- 0�� ������ Ÿ���̳� ���� Ÿ������ ��ȯ�� 0�� ������ Ÿ���̳� ���� Ÿ������ ��ȯ�ȴ�
//					- �����ʹ� void �����ͷ� ��ȯ�ȴ�
//				4) ���� ���ǵ� Ÿ�� ��ȯ���� ��ġ�ϴ°��� ã�´�
//	
//				- �켱 double�� 1, 2�ܰ迡�� ��ġ�ϴ� �Լ��� ����
//				- 3�ܰ迡�� double�� numericŸ���̹Ƿ� int, char�� ��� �� �� �ְԵ�
//					-> ���� �ܰ迡�� 2�� �̻��� ��ġ -> ��ȣ�ϴ�!
//	
//				�� �ƴ� char�� numeric��? ����Ÿ�� �ƴ�?
//					- char�� 1����Ʈ¥�� numeric�� ����
//					- ������ �Ʒ��� ���÷� Ȯ�ΰ���
//						#include <type_traits>
//							std::cout << std::is_arithmetic<char>::value << std::endl; -> 1�� ���(true)
//					- arithmetic�� ��� ������ ������ Ÿ���� ���ϰ� numeric�� ���ԵǴ� ������
//						-> �׷��Ƿ� arithmetic Ÿ���̶�� ���ÿ� numeric Ÿ������ �ڸ���
//	
//	
//		*/
//	
//		return 0;
//	}

// �����ε��� �Ұ����� ����

//	/*
//		- �����ε��� �Ұ����� ��찡 ������(soen.kr)
//			1) ���� Ÿ�Ը� �ٸ���� - �Ʒ��� int funcA()�� double funcA()
//				-> �Լ��� ���ϰ��� �Լ��� ������ ��ģ �Ŀ� ����Ǵ� ���̹Ƿ� 
//				ȣ������� � �Լ��� ȣ���� ���ΰ��� �����ϴ� �ٰŰ� �� �� ����
//	
//			2) �μ� ��Ͽ� ���۷����� ���޵Ǵ� ���� �Ϲݺ����� ���޵Ǵ� ��� - �Ʒ��� int funcB()
//				-> ���۷���, �Ϲݺ��� ��� ȣ�� ���°� �����ϹǷ� ��ȣ���� �߻���. ���� ��ü�� ���������� �����δ� �ƹ��� �ǹ̰� ����
//				-> soen������ ����ó�� �Ѵٰ� ������ ������ �Ϲ� ���� �Լ��� �����. �Լ��� ���� �����͵� ���� ���°����� ����
//	
//			3) const �������� ���� - �Ʒ��� int funC()	!!!! �Ϲ� ���ڿ��� ���ͷ� (char* �� const char*�� �����ε� ����) !!!!
//				-> main()���� str1�� ���� �����ϹǷ� char* s��, str2�� ���ͷ��̹Ƿ� const char* s�� ȣ��ȴ�. �� ��쿡�� �����ε� ������. str3��?
//				-> str3�� ��� �����Ͱ� ����̰� ������ ���� ���� �����ϹǷ� char* ������ ȣ���
//				-> �̶� char* const s�� �����ε� �� ��� ������ �߻�: C2084 'int funC(char *)' �Լ��� �̹� ������ �ֽ��ϴ�.
//					-> �������� ������� ���μ�(��)�� ������� �ƹ��� ����� �����Ƿ� ȣ������� � �Լ��� ��Ȯ���� �Ǵ��� �� ���� ����
//	
//			4) �μ��� ���� �ǹ̸� �ٸ���� - int func(int a)�� int func(int b)�� �����ε��� �ȵȴٴ� �ǹ���. �翬�� �κ��̹Ƿ� PASS
//	
//			5) ����Ʈ �μ��� ���� ������ �� �ִ°�� - �Ʒ��� int funcD()
//				-> funcD(1,2)������ ȣ���Ͽ����� ������ ���� ����. ���� ��ü�� �����ϳ� �ƹ��� �ǹ� ���� ������ ����� �ڵ�
//	
//			6) �޶������� �����δ� ���� Ÿ���� ���(typedef, ��ũ�� � ���ؼ�) - �Ʒ��� int funcE(), int funcF()
//				-> �����Ϸ��� �翬�� �̸��� �ƴ� ���� Ÿ���� ���� �����ε� ��Ű�Ƿ� �ȵǴ°��� �翬��
//				-> int* p�� int p[]�� ���� �Ѵ� ���� ���������̹Ƿ� �����ε��� �Ұ�����
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
//		const char* str2 = "�����ٶ�";
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


// ������ �ǽ� -> Date Ŭ����

#include <iostream>

class Date
{
public:
	// ������ -> �Ʒ����� ����
	Date(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	//	����� ���� ����Ʈ ������
	//	Date()
	//	{
	//		_year = 2014;
	//		_month = 4;
	//		_day = 4;
	//	} 

	// ����� ����Ʈ ������
	// Date() = default;



	void SetDate(int year, int month, int date);
	void AddDay(int inc);
	void AddMonth(int inc);
	void AddYear(int inc);
	
	// �ش� ���� �� �ϼ��� ���Ѵ�
	int GetCurrentMonthTotalDays(int years, int month);

	void ShowDate();

private:
	int _year;
	int _month;
	int _day;
};

// Date::SetDate() -> Ŭ���� ������ �Լ� ����. �Ϲ������� ������ϰ� �и��ؼ� ���� ������ ���⼭�� �� ���Ͽ� ��� ������
// 
// cppreference�� namespace ���� (4)���� ����
// ns-name::member-name -> Namespace names (along with class names) can appear on the left hand side of the scope resolution operator, as part of qualified name lookup.
// ���ӽ����̽��� �̸�(Ŭ���� �̸� ����)�� ������ ���ӽ����̽� Ž���� �Ϻη� scope resolution operator(::)�� ���ʿ� �� �� ����
// ==> ������ ���ӽ����̽��� �̿��� ���ؼ� ���ȴٰ� ����

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
		return 29;	// ����
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
		// ���� ���� �� �ϼ�
		int currentMonthTotalDays = GetCurrentMonthTotalDays(_year, _month);

		// ���� �� �ȿ� ���´ٸ�
		if (_day + inc <= currentMonthTotalDays)
		{
			_day += inc;
			return;
		}
		else
		{
			// �����޷� �Ѿ��
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
	std::cout << "������ " << _year << " �� " << _month << " �� " << _day << " �� �Դϴ�" << std::endl;
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
	//	day.SetDate(2012, 1, 31);	// ����
	//	day.AddDay(29);
	//	day.ShowDate();
	//	
	//	day.SetDate(2012, 8, 4);
	//	day.AddDay(2500);
	//	day.ShowDate();

	/*
		output

		������ 2011 �� 3 �� 1 �� �Դϴ�
		������ 2011 �� 3 �� 31 �� �Դϴ�
		������ 2016 �� 9 �� 20 �� �Դϴ�
		������ 2012 �� 2 �� 29 �� �Դϴ�
		������ 2019 �� 6 �� 9 �� �Դϴ�
	*/

	//	���࿡ SetDate���� �ν��Ͻ��� �����Ѵٸ�?
	//	Date day2;
	//	day2.ShowDate();	// ������ -858993460 �� -858993460 �� -858993460 �� �Դϴ�

	/*
		- ��ó�� ������ �ʱ�ȭ�� �и����� �������� �ʱ�ȭ�� ���� ������ �����Ⱚ�� ���Ե�
			-> �ذ���: �������� �������� ������ ���ÿ� �ʱ�ȭ

		- ������(Constructor): ��ü ������ �ڵ����� ȣ��Ǵ� �Լ�
			- �������� ����: Ŭ�����̸�(����) {}
			- ��ü ������ �ڵ����� ȣ��Ǿ� "��ü�� �ʱ�ȭ ���ִ� ����"�� �����
			- ��ü ������ ������ ������ �������� �μ��� �°� �Լ��� ȣ���ϵ��� ���ָ� ��
	*/

	// �������� ȣ��
	Date day(2011, 1, 1);				// �Ͻ��� ���(implicit)
	Date day2 = Date(2012, 2, 2);		// ����� ���(explicit)

	Date* day3 = new Date(2013, 3, 3);	// ���� �Ҵ�

	day.ShowDate();
	day2.ShowDate();
	day3->ShowDate();

	/*
		- ���࿡ ó���� �ߴ���� �����ڸ� ������ ������ �ʾƵ� �����ڰ� ȣ���
			-> �̶� ȣ��Ǵ� �����ڸ� ����Ʈ ������(Default Constructor)��� �θ�(Ȥ�� �⺻ �����ڶ�� ���� �ҷ���)

		- ����Ʈ ������
			- Ŭ�������� ����ڰ� ��� �����ڵ� ��������� �������� ���� ��� �����Ϸ��� �ڵ����� �߰����ִ� ������
			- ���ڸ� �ϳ��� ������ ����
			- ���� ����Ʈ �����ڸ� ������� ����
	*/

	// ����� ���ǵ� ����Ʈ �������� ȣ��
	Date day4 = Date();
	day4.ShowDate();

	// !!! ������ !!!
	// �Ʒ��� ����� day5��� ��ü�� ����Ʈ �����ڸ� �̿��Ͽ� �ʱ�ȭ�ϴ°��� �ƴ�
	//	-> ���ϰ��� Date�� day5() �Լ��� �����ϰ� �Ȱ����� �ν�
	Date day5();

	/*
		- ����� ����Ʈ ������
			- C++11 �������� ����Ʈ �����ڸ� ����ϰ� ������� �׳� �����ڸ� �������� �ʴ°��� ������ ���
				-> �� ��� �ڵ带 �д� ����ڴ� �����ڰ� �����ϰ� �����ڸ� �������� ���������� �ƴϸ� �ǵ��Ѱ����� ��Ȯ�� �� �� ������
			- C++11 ���Ŀ��� ��������� ����Ʈ �����ڸ� ���� �� ����
				-> ���ڰ� ���� �⺻ �����ڿ� = default;�� �ٿ��ָ� ��
				-> �� Date() = dafault�� ����� ����Ʈ �������� ���� -> �����Ⱚ�� ���� �ʰ� ��������� 0���� �ʱ�ȭ��
	*/
	
	/*
		- ������ �����ε�
			- �����ڵ� �Լ� -> �����ε��� ����
			- ������ �ڿ������� ������̾����Ƿ� ���ô� PASS

	*/

	return 0;
}
