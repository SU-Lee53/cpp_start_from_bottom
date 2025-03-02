
/*
	- 03.21 연산자 오버로딩 - 산술, 비교, 대입
*/

//	- 연산자 오버로딩

/*
	- 연산자 오버로딩
		- C++은 다음의 연산자들에 대해서 사용자 정의 연산자를 사용할 수 있음
			- 산술 연산자 (+, -, * 등) 
			- 축약형 연산자 (+=, -= 등)
			- 비교 연산자 (>=, == 등)
			- 논리 연산자 (&&, || 등)
			- 멤버 선택 연산자 (->, *(역참조) 등) 
			- 증감 연산자 (++, -- 등)
			- 배열 연산자[], 함수 호출 연산자()
			- cppreference의 operator overloading 에 따르면 (https://en.cppreference.com/w/cpp/language/operators)
					op - any of the following operators : 
					+ - * / % ^ & | ~ ! = < > += -= *= /= %= ^= &= |= << >> >>= <<= == != <= >= <=>(since C++20) && || ++ -- , ->* -> ( ) [ ]
					1) overloaded operator;					-> 위에 있는 연산자들(op)
					2) user-defined conversion function;	-> 유저가 정의한 변환 함수
					3) allocation function;					-> new, new[]
					4) deallocation function;				-> delete, delete[]
					5) user-defined literal;				-> ""
					6) overloaded co_await operator for use in co_await expressions. -> 코루틴 관련된 것으로 자세한건 아직 잘 모르겠음
		
		- 이러한 기본 연산자들을 사용자가 직접 정의하는것이 연산자 오버로딩(operator overloading)이라고 부름
*/

// - 가장 기본적으로 이전의 MyString을 간단하게만 다시 구현하여 ==를 오버로딩 해보면...

//	#include <iostream>
//	
//	class MyString
//	{
//	public:
//		MyString(const char* str)
//		{
//			string_length = strlen(str);
//			memory_capacity = string_length;
//			string_content = new char[string_length];
//			memcpy(string_content, str, string_length);
//		}
//		~MyString() { delete[] string_content; }
//	
//		int compare(MyString& str);
//	
//		// 연산자 오버로딩의 선언 : (리턴타입) operator(연산자) (연산자가 받는 인자)
//		// 이 방법이 유일한 오버로딩 방법임
//		bool operator== (MyString& str);
//	
//		void println()
//		{
//			for (int i = 0; i < string_length; i++) std::cout << string_content[i];
//			std::cout << std::endl;
//		}
//	
//	private:
//		char* string_content;
//		int string_length;
//		int memory_capacity;
//	};
//	
//	int MyString::compare(MyString& str)
//	{
//		for (int i = 0; i < std::min(string_length, str.string_length); i++)
//		{
//			if (string_content[i] > str.string_content[i])
//				return 1;
//			else if (string_content[i] < str.string_content[i])
//				return -1;
//		}
//		
//		// 두 문자열이 같은 경우 0을 리턴해줌
//		if (string_length == str.string_length) return 0;
//		else if (string_length > str.string_length) return 1;
//		else return -1;
//	
//	}
//	
//	bool MyString::operator==(MyString& str)
//	{
//		// 기존의 compare를 그대로 활용가능함
//		return !compare(str);	// compare() 함수가 두 문자열이 같다면 0을 리턴하도록 만들었으므로 0 == false임을 이용하여 쉽게 활용됨
//	}
//	
//	int main()
//	{
//		MyString str1 = MyString("a word");
//		MyString str2 = "sentence";
//		MyString str3("sentence");
//	
//		if (str1 == str2)
//			std::cout << "str1 와 str2는 같다." << std::endl;
//		else
//			std::cout << "str1 와 str2는 다르다." << std::endl;
//	
//		if (str2 == str3)
//			std::cout << "str2 와 str3는 같다." << std::endl;
//		else	
//			std::cout << "str2 와 str3는 다르다." << std::endl;
//	
//		/*
//			output:
//			str1 와 str2는 다르다.
//			str2 와 str3는 같다.
//		*/
//	
//	}

// - 복소수(Complex number)를 이용하여 연산자 오버로딩 실습
// + 복소수 연산들에 대한 설명들은 전부 생략

#include <iostream>

class Complex
{
public:
	Complex(double _real, double _img) : real(_real), img(_img) {}
	Complex(const Complex& c) { real = c.real, img = c.img; }
	Complex(const char* str);


	// 리턴타입에 주목. Complex& 가 아님!
	Complex operator+(const Complex& c) const;
	Complex operator-(const Complex& c) const;
	Complex operator*(const Complex& c) const;
	Complex operator/(const Complex& c) const;

	// 리턴타입에 주목. 이번에는 Complex&임!
	Complex& operator=(const Complex& c);

	// 대입 사칙 연산자 -> 이번에도 레퍼런스를 리턴함
	Complex& operator+=(const Complex& c);
	Complex& operator-=(const Complex& c);
	Complex& operator*=(const Complex& c);
	Complex& operator/=(const Complex& c);

	// 복소수를 문자열로 받아 연산을 시켜보자
	//	Complex operator+(const char* str);
	//	Complex operator-(const char* str);
	//	Complex operator*(const char* str);
	//	Complex operator/(const char* str);
	// 여기있는걸 다 지워도 정상작동함. 이유는 아래에서


	void println() { std::cout << "( " << real << " , " << img << " )" << std::endl; }

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

Complex Complex::operator+(const Complex& c) const
{
	Complex temp = Complex(real + c.real, img + c.img);
	return temp;
}

Complex Complex::operator-(const Complex& c) const
{
	Complex temp = Complex(real - c.real, img - c.img);
	return temp;
}

Complex Complex::operator*(const Complex& c) const
{
	Complex temp = Complex((real * c.real) - (img * c.img), (real * c.img) + (img * c.real));
	return temp;
}

Complex Complex::operator/(const Complex& c) const
{
	Complex temp = Complex(
		((real * c.real) + (img * c.img)) / ((c.real * c.real) + (c.img * c.img)),
		((img * c.real) - (real * c.img)) / ((c.real * c.real) + (c.img * c.img))
	);

	return temp;
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

//	Complex Complex::operator+(const char* str)
//	{
//		//	/*
	//		입력받은 문자열을 분석하여 real 부분과 img 부분을 찾아야 함
	//		문자열의 형태 -> "[부호](실수부)(부호)i(허수부)"	ex) -2 + i3
	//		이때 맨 앞의 부호는 생략가능함(생략시 +)
	//	*/
	//	
	//	int begin = 0, end = strlen(str);
	//	double str_img = 0.0, str_real = 0.0;
	//	
	//	// 먼저 가장 기준이 되는 'i'의 위치를 찾는다
	//	int pos_i = -1;
	//	for (int i = 0; i != end; i++)
	//	{
	//		if (str[i] == 'i')
	//		{
	//			pos_i = i;
	//			break;
	//		}
	//	}
	//	
	//	// 만약 'i'가 없다면 이 수는 실수 뿐임
	//	if (pos_i == -1)
	//	{
	//		str_real = get_number(str, begin, end - 1);	// get_number 함수는 cstdlib 의 atof와 같은역할 -> 여기서는 멤버함수로 직접 구현
	//	
	//		Complex temp(str_real, str_img);
	//		return (*this) + temp;
	//	}
	//	
	//	// 만약 i가 있다면, 실수부와 허수부를 나누어서 처리하면 됨
	//	str_real = get_number(str, begin, pos_i - 1);	// 시작부터 i위치 앞까지가 실수부
	//	str_img = get_number(str, pos_i + 1, end - 1);	// i위치 뒤부터 끝까지가 허수부
	//	
	//	if (pos_i >= 1 && str[pos_i - 1] == '-') str_img *= -1.0;	// 허수부의 부호 처리(i 바로앞에 허수부의 부호가 옴)
	//	
	//	Complex temp(str_real, str_img);
	//	return (*this) + temp;
//	
//		// 위 과정을 여기서 하지말고 생성자를 하나 새로 만들어서 거기로 옮겨주면
//		Complex temp(str);
//		return (*this) + temp;
//		// 이거면 끝남...
//	
//	}
//	
//	Complex Complex::operator-(const char* str)
//	{
//		Complex temp(str);
//		return (*this) - temp;
//	}
//	
//	Complex Complex::operator*(const char* str)
//	{
//		Complex temp(str);
//		return (*this) * temp;
//	}
//	
//	Complex Complex::operator/(const char* str)
//	{
//		Complex temp(str);
//		return (*this) / temp;
//	}

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

int main()
{
	//	Complex a = Complex(1.0, 2.0);
	//	Complex b = Complex(3.0, -2.0);
	//	
	//	Complex c = a * b;
	//	c.println();
	
	/*
		output
		( 7 , 4 )
	
	*/
	
	
	/*
		- +, -, *, / 의 리턴타입이 Complex& 가 아닌 Complex 인 이유
			- 만약에 리턴타입이 Complex&라고 생각하고 다음의 식을 생각해보자
				
				Complex a = b + c + b;
	
				- 일반적으로 프로그래머 입장에서는 (2 * b) + c 라고 의도하였을것임
				- 그러나 실제로는...
					-> 우선 위 식은 (b.plus(c)).plus(b) 처럼 계산됨
					-> 레퍼런스를 리턴하는 경우 b.plus(c)의 결과로 b + c의 값이 리턴되어 b에 들어감
					-> 이때 다시 b가 더해지면 (b + c) + (b + c)가 계산됨(b에 이미 (b + c)의 값이 들어가 있으므로)
					-> 따라서 의도와 달리 (2 * b) + (2 * c) 로 계산됨
						-> 결론 - 이러한 문제가 있으므로 "사칙연산"은 반드시 "값을 리턴해"야함!!!!!!!
	*/

	//	Complex a = Complex(1.0, 2.0);
	//	Complex b = Complex(3.0, -2.0);
	//	Complex c = Complex(0.0, 0.0);
	//	
	//	c = a * b + a / b + a + b;
	//	
	//	c.println();

	/*
		output
		( 10.9231 , 4.61538 )
	*/

	/*
		- 대입 연산자 = 의 오버로딩
			- = 를 오버로딩 할때는 자기 자신의 레퍼런스를 리턴해야함
				- 다음의 식을 생각해보면 됨

					a = b = c;

					-> b = c 가 b를 리턴해야 a = b가 성공적으로 수행됨
					-> 또한 대입 연산 후에 불필요한 복사를 막기 위함임

			- 디폴트 대입 연산자도 존재함. 
				-> 다만 디폴트 대입 연산자는 얕은 복사만 수행하므로 "깊은 복사가 필요한 경우 반드시 오버로딩을 해주어야함"!!!!

			- 이제 다음 2가지 코드의 차이점을 명확하게 구분할 수 있음
				1) Complex a = b;
				2) Complex a;
				   a = b;
					-> 1): 복사 생성자 호출
					-> 2): 기본 생성자로 a 생성 후, 대입 연산자 함수 호출

	*/

	//	Complex a(1.0, 2.0);
	//	Complex b(3.0, -2.0);
	//	a += b;
	//	
	//	a.println();
	//	b.println();

	/*
		output
		( 4 , 0 )
		( 3 , -2 )
	*/

	Complex a(0, 0);

	a = a + "-1.1 + i3.923";
	a.println();

	a = a - "1.2 - i1.823";
	a.println();

	a = a * "2.3+i22";
	a.println();

	a = a / "-12+i55";
	a.println();

	/*
		output
		( -1.1 , 3.923 )
		( -2.3 , 5.746 )
		( -131.702 , -37.3842 )
		( -0.150113 , 2.42733 )
	*/


	//	a = "3 + i4" + a;	// 불가능

	/*
		- 재미있게도 문자열로 받아서 연산하는 오버로딩 함수들을 전부 주석처리해도 위 계산들은 전부 정상작동함
			- 문자열로 복소수를 생성하는 생성자가 있기 때문에 컴파일러가 알아서 operator+(Complex(str))로 변환해주기 때문임

		- 또 a = "3 + i4" + a; 같은 수식은 오류가 발생함. 컴파일러가 적절하게 변환해주지 못하기 때문
	
	
	*/


}