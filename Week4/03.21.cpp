
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

	// 리턴타입에 주목. Complex& 가 아님!
	Complex operator+(const Complex& c) const;
	Complex operator-(const Complex& c) const;
	Complex operator*(const Complex& c) const;
	Complex operator/(const Complex& c) const;

	// 리턴타입에 주목. 이번에는 Complex&임!
	Complex& operator=(const Complex& c);

	void println() { std::cout << "( " << real << " , " << img << " )" << std::endl; }

private:
	double real, img;

};

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

	Complex a = Complex(1.0, 2.0);
	Complex b = Complex(3.0, -2.0);
	Complex c = Complex(0.0, 0.0);

	c = a * b + a / b + a + b;

	c.println();

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

}