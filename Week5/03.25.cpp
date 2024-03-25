/*
	03.25 연산자 오버로딩 2

*/

// - friend

//	/*
//		- friend : 다른 클래스의 private 멤버 함수, 변수들에 대한 접근 권한을 부여함
//			- 짝사랑 같은 관계로 아래에서 B는 A의 멤버에 접근 가능하지만 A는 B의 멤버에 접근할 수 없음
//	*/
//	
//	#include <iostream>
//	
//	class A
//	{
//	public:
//		void a()
//		{
//			B b;
//	
//			//	b.private_num = 2;	// 안됨
//		}
//	
//	private:
//		void private_func() { }
//		int private_num;
//	
//		// B 는 A의 친구
//		friend class B;
//	
//		// func 은 A의 친구
//		friend void func();
//	};
//	
//	class B
//	{
//	public:
//		void b()
//		{
//			A a;
//	
//			// A의 private 필드에 정의된 것들이지만 friend이므로 접근 가능해짐
//			a.private_func();
//			a.private_num = 2;
//		}
//	
//	private:
//		int private_num;
//	};
//	
//	void func()
//	{
//		A a;
//	
//		// A의 private 필드에 정의된 것들이지만 friend이므로 접근 가능해짐
//		a.private_func();
//		a.private_num = 2;
//	}
//	
//	int main()
//	{
//	
//	}

#include <iostream>
#include "MyString.h"

class Complex
{
public:
	Complex(double _real, double _img) : real(_real), img(_img) {}
	Complex(const Complex& c) { real = c.real, img = c.img; }
	Complex(const char* str);


	// 리턴타입에 주목. Complex& 가 아님!
	// 자기자신을 리턴하지 않는 이항 연산자는 외부함수로 정의해주자
	//	Complex operator+(const Complex& c) const;
	//	Complex operator-(const Complex& c) const;
	//	Complex operator*(const Complex& c) const;
	//	Complex operator/(const Complex& c) const;

	// 리턴타입에 주목. 이번에는 Complex&임!
	Complex& operator=(const Complex& c);

	// 대입 사칙 연산자 -> 이번에도 레퍼런스를 리턴함
	Complex& operator+=(const Complex& c);
	Complex& operator-=(const Complex& c);
	Complex& operator*=(const Complex& c);
	Complex& operator/=(const Complex& c);

	void println() { std::cout << "( " << real << " , " << img << " )" << std::endl; }

	// 클래스 외부의 오버로딩 함수가 Complex의 private 멤버변수에 접근 가능해짐
	friend Complex operator+(const Complex& a, const Complex& b);
	friend Complex operator-(const Complex& a, const Complex& b);
	friend Complex operator*(const Complex& a, const Complex& b);
	friend Complex operator/(const Complex& a, const Complex& b);
	friend std::ostream& operator<<(std::ostream& os, const Complex& c);

private:
	double get_number(const char* str, int from, int to);

	double real, img;

};

Complex::Complex(const char* str)
{
	/*
		입력받은 문자열을 분석하여 real 부분과 img 부분을 찾아야 함
		문자열의 형태 -> "[부호](실수부)(부호)i(허수부)"	ex) -2 + i3
		이때 맨 앞의 부호는 생략가능함(생략시 +)
	*/

	int begin = 0, end = strlen(str);
	img = 0.0;
	real = 0.0;

	// 먼저 가장 기준이 되는 'i'의 위치를 찾는다
	int pos_i = -1;
	for (int i = 0; i != end; i++)
	{
		if (str[i] == 'i')
		{
			pos_i = i;
			break;
		}
	}

	// 만약 'i'가 없다면 이 수는 실수 뿐임
	if (pos_i == -1)
	{
		real = get_number(str, begin, end - 1);	// get_number 함수는 cstdlib 의 atof와 같은역할 -> 여기서는 멤버함수로 직접 구현
		return;
	}

	// 만약 i가 있다면, 실수부와 허수부를 나누어서 처리하면 됨
	real = get_number(str, begin, pos_i - 1);	// 시작부터 i위치 앞까지가 실수부
	img = get_number(str, pos_i + 1, end - 1);	// i위치 뒤부터 끝까지가 허수부

	if (pos_i >= 1 && (str[pos_i - 1] == '-' || str[pos_i - 2] == '-')) img *= -1.0;	// 허수부의 부호 처리(i 바로앞에 허수부의 부호가 옴)

}

Complex& Complex::operator=(const Complex& c)
{
	real = c.real;
	img = c.img;
	return *this;
}

Complex& Complex::operator+=(const Complex& c)
{
	(*this) = (*this) + c;
	return *this;
}

Complex& Complex::operator-=(const Complex& c)
{
	(*this) = (*this) - c;
	return *this;
}

Complex& Complex::operator*=(const Complex& c)
{
	(*this) = (*this) * c;
	return *this;
}

Complex& Complex::operator/=(const Complex& c)
{
	(*this) = (*this) / c;
	return *this;
}

double Complex::get_number(const char* str, int from, int to)
{
	bool minus = false;
	if (from > to) return 0;	// 시작 인덱스가 끝 인덱스보다 크면 잘못된 입력이므로 그냥 리턴

	if (str[from] == '-') minus = true;
	if (str[from] == '-' || str[from] == '+') from++;	// 시작 인덱스에 부호가 있으면 시작 인덱스 옮김

	double num = 0.0;
	double decimal = 1.0;

	bool integer_part = true;
	for (int i = from; i <= to; i++)
	{
		if (isdigit(str[i]) && integer_part)	// isdigit -> cctype에 정의된 함수로 숫자가 아니면 0을 리턴함
		{
			// 해당 연산은 다음과 같음. 예를 들어 123.456 이 주어진다면
			// 1 -> 12 -> 123 이런식으로 자릿수를 올려가면서 더함
			num *= 10.0;
			num += (str[i] - '0');	// ASCII값을 이용한 연산 -> ASCII -> 실제 숫자를 구함
		}
		else if (str[i] == '.')
		{
			integer_part = false;
		}
		else if (isdigit(str[i]) && !integer_part)
		{
			// 위와 반대로 자릿수를 내려가면서 더함
			decimal /= 10.0;
			num += ((str[i] - '0') * decimal);
		}
		else
			break;	// 숫자가 아닌 이상한 문자인 경우
	}

	if (minus) num *= -1.0;

	return num;

}

Complex operator+(const Complex& a, const Complex& b)
{
	Complex temp = Complex(a.real + b.real, a.img + b.img);
	return temp;
}

Complex operator-(const Complex& a, const Complex& b)
{
	Complex temp = Complex(a.real - b.real, a.img - b.img);
	return temp;
}

Complex operator*(const Complex& a, const Complex& b)
{
	Complex temp = Complex((a.real * b.real) - (a.img * b.img), (a.real * b.img) + (a.img * b.real));
	return temp;
}

Complex operator/(const Complex& a, const Complex& b)
{
	Complex temp = Complex(
		((a.real * b.real) + (a.img * b.img)) / ((b.real * b.real) + (b.img * b.img)),
		((a.img * b.real) - (a.real * b.img)) / ((b.real * b.real) + (b.img * b.img))
	);

	return temp;
}

std::ostream& operator<<(std::ostream& os, const Complex& c)
{
	os << "( " << c.real << " , " << c.img << " ) ";
	return os;
}

int main()
{
	// - 이항 연산자
	/*
		- 이항 연산자
			- 이전에 만든 오버로딩된 함수는 a = "-1.1 + i3.923" + a; 와 같은 형태의 식을 계산하지 못함
				- 그 이유는 컴파일러가 하는 일을 보면 됨. 컴파일러는 오버로딩된 연산자를 둘중 하나의 방색으로 해석함(대충 임의의 연산자 @)
					1) *a.operator@(b);
					2) *operator(a, b);
					-> 1)의 형태는 a의 클래스 멤버 함수로 사용됨
					-> 2)의 형태는 클래스 외부에 정의되어 있는 일반적인 함수를 의미함
				- 이것을 해결하기 위해 일반적인 함수로 연산자 오버로딩을 시행 -> Complex operator+(const Complex& a, const Complex& b)
					- 이제 위 2)의 형태로 operator+(Complex("-1.1 + i3.923"), a);의 형태로 컴파일 됨
					- 이때 정상적으로 연산을 위해서는 a 와 b의 real과 img에 접근이 가능해야 하는데 해당 변수들은 private임
						-> 클래스 외부의 오버로딩 함수를 클래스의 friend로 지정하면 됨!
				
				- 문제 발생 -> 1), 2) 모든 형태가 구현되어 있어 컴파일러가 어떤걸 골라 컴파일할지 몰라 오류를 발생시킴
					-> 자기 자신을 리턴하지 않는 이항 연산자(+,-,*,/ 등) 은 외부함수로 선언하는것이 원칙
					-> 자기 자신을 리턴하는 이항 연산자(+=, -= 등) 은 클래스 멤버 함수로 선언하는것이 원칙
					++ 위에서도 += 연산자가 무엇을 선택할지 몰라 오류를 뱉고있음
					
	*/

	// - 입출력 연산자  >>, <<
	/*
		- 입출력 연산자 >>, <<
			- 기본적으로 우리가 std::cout << a; 하는 것은 std::cout.operator<<(a)를 하는 것으로 오버로딩 되어있음
				- 실제로 <ostream> 헤더에 엄청난 양의 << 오버로딩이 되어있고 이 덕분에 기본 타입들은 자유자재로 출력이 가능함

			- 그러면 Complex를 <<를 사용해서 자유롭게 출력하도록 오버로딩 가능한가? -> 가능
				- 다만 <ostream>에 직접 오버로딩을 하는것은 표준 헤더파일을 건드리는 행위이므로 불가능함
				-> 대신 ostream 클래스와 Complex 객체를 받는 전역 연산자 오버로딩을 하면 가능함
	
			- 직접 해보자
				- std::ostream& operator<<(std::ostream& os, const Complex& c); 로 오버로딩하여 구현
					- 이때 오버로딩 함수가 c의 멤버를 접근 할 수 없는데 3가지의 방법 고려가능함
						1. real과 img를 그냥 public으로 바꾼다 
							-> 당연히 좋지 못한 방법으로 구현 디테일은 최대한 숨기는것이 좋음
						2. Complex 에 print(std::ostream& os)와 같은 멤버함수를 추가하고, 이를 operator<<에서 호출
							-> 괜찮은데 일단은 skip
						3. operator<< 함수를 friend로 지정
							-> 일단 이걸 사용해서 해결
				- 같은 방법으로 cin도 구현해볼수 있음

			++ friend의 남발은 권장되지 않음. oop의 원칙중 하나인 정보 은닉성을 깨부수는 키워드이기 때문임
				-> 그러니 차라리 위와같은 상황에서는 2번같은 해결법이 좋음
				-> 다만 일부 상황에서 유용하게 사용되긴 함
	*/

	Complex a = Complex(-1.1, 3.923);
	std::cout << a;
	/*
		output
		( -1.1 , 3.923 )
	*/

	//	- 첨자 연산자

	/*
	
	
	
	
	*/

}




