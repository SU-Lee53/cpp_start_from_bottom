
/*
	- 03.21 ������ �����ε� - ���, ��, ����
*/

//	- ������ �����ε�

/*
	- ������ �����ε�
		- C++�� ������ �����ڵ鿡 ���ؼ� ����� ���� �����ڸ� ����� �� ����
			- ��� ������ (+, -, * ��) 
			- ����� ������ (+=, -= ��)
			- �� ������ (>=, == ��)
			- �� ������ (&&, || ��)
			- ��� ���� ������ (->, *(������) ��) 
			- ���� ������ (++, -- ��)
			- �迭 ������[], �Լ� ȣ�� ������()
			- cppreference�� operator overloading �� ������ (https://en.cppreference.com/w/cpp/language/operators)
					op - any of the following operators : 
					+ - * / % ^ & | ~ ! = < > += -= *= /= %= ^= &= |= << >> >>= <<= == != <= >= <=>(since C++20) && || ++ -- , ->* -> ( ) [ ]
					1) overloaded operator;					-> ���� �ִ� �����ڵ�(op)
					2) user-defined conversion function;	-> ������ ������ ��ȯ �Լ�
					3) allocation function;					-> new, new[]
					4) deallocation function;				-> delete, delete[]
					5) user-defined literal;				-> ""
					6) overloaded co_await operator for use in co_await expressions. -> �ڷ�ƾ ���õ� ������ �ڼ��Ѱ� ���� �� �𸣰���
		
		- �̷��� �⺻ �����ڵ��� ����ڰ� ���� �����ϴ°��� ������ �����ε�(operator overloading)�̶�� �θ�
*/

// - ���� �⺻������ ������ MyString�� �����ϰԸ� �ٽ� �����Ͽ� ==�� �����ε� �غ���...

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
//		// ������ �����ε��� ���� : (����Ÿ��) operator(������) (�����ڰ� �޴� ����)
//		// �� ����� ������ �����ε� �����
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
//		// �� ���ڿ��� ���� ��� 0�� ��������
//		if (string_length == str.string_length) return 0;
//		else if (string_length > str.string_length) return 1;
//		else return -1;
//	
//	}
//	
//	bool MyString::operator==(MyString& str)
//	{
//		// ������ compare�� �״�� Ȱ�밡����
//		return !compare(str);	// compare() �Լ��� �� ���ڿ��� ���ٸ� 0�� �����ϵ��� ��������Ƿ� 0 == false���� �̿��Ͽ� ���� Ȱ���
//	}
//	
//	int main()
//	{
//		MyString str1 = MyString("a word");
//		MyString str2 = "sentence";
//		MyString str3("sentence");
//	
//		if (str1 == str2)
//			std::cout << "str1 �� str2�� ����." << std::endl;
//		else
//			std::cout << "str1 �� str2�� �ٸ���." << std::endl;
//	
//		if (str2 == str3)
//			std::cout << "str2 �� str3�� ����." << std::endl;
//		else	
//			std::cout << "str2 �� str3�� �ٸ���." << std::endl;
//	
//		/*
//			output:
//			str1 �� str2�� �ٸ���.
//			str2 �� str3�� ����.
//		*/
//	
//	}

// - ���Ҽ�(Complex number)�� �̿��Ͽ� ������ �����ε� �ǽ�
// + ���Ҽ� ����鿡 ���� ������� ���� ����

#include <iostream>

class Complex
{
public:
	Complex(double _real, double _img) : real(_real), img(_img) {}
	Complex(const Complex& c) { real = c.real, img = c.img; }
	Complex(const char* str);


	// ����Ÿ�Կ� �ָ�. Complex& �� �ƴ�!
	Complex operator+(const Complex& c) const;
	Complex operator-(const Complex& c) const;
	Complex operator*(const Complex& c) const;
	Complex operator/(const Complex& c) const;

	// ����Ÿ�Կ� �ָ�. �̹����� Complex&��!
	Complex& operator=(const Complex& c);

	// ���� ��Ģ ������ -> �̹����� ���۷����� ������
	Complex& operator+=(const Complex& c);
	Complex& operator-=(const Complex& c);
	Complex& operator*=(const Complex& c);
	Complex& operator/=(const Complex& c);

	// ���Ҽ��� ���ڿ��� �޾� ������ ���Ѻ���
	//	Complex operator+(const char* str);
	//	Complex operator-(const char* str);
	//	Complex operator*(const char* str);
	//	Complex operator/(const char* str);
	// �����ִ°� �� ������ �����۵���. ������ �Ʒ�����


	void println() { std::cout << "( " << real << " , " << img << " )" << std::endl; }

private:
	double get_number(const char* str, int from, int to);

	double real, img;

};

Complex::Complex(const char* str)
{
	/*
		�Է¹��� ���ڿ��� �м��Ͽ� real �κа� img �κ��� ã�ƾ� ��
		���ڿ��� ���� -> "[��ȣ](�Ǽ���)(��ȣ)i(�����)"	ex) -2 + i3
		�̶� �� ���� ��ȣ�� ����������(������ +)
	*/

	int begin = 0, end = strlen(str);
	img = 0.0;
	real = 0.0;

	// ���� ���� ������ �Ǵ� 'i'�� ��ġ�� ã�´�
	int pos_i = -1;
	for (int i = 0; i != end; i++)
	{
		if (str[i] == 'i')
		{
			pos_i = i;
			break;
		}
	}

	// ���� 'i'�� ���ٸ� �� ���� �Ǽ� ����
	if (pos_i == -1)
	{
		real = get_number(str, begin, end - 1);	// get_number �Լ��� cstdlib �� atof�� �������� -> ���⼭�� ����Լ��� ���� ����
		return;
	}

	// ���� i�� �ִٸ�, �Ǽ��ο� ����θ� ����� ó���ϸ� ��
	real = get_number(str, begin, pos_i - 1);	// ���ۺ��� i��ġ �ձ����� �Ǽ���
	img = get_number(str, pos_i + 1, end - 1);	// i��ġ �ں��� �������� �����

	if (pos_i >= 1 && (str[pos_i - 1] == '-' || str[pos_i - 2] == '-')) img *= -1.0;	// ������� ��ȣ ó��(i �ٷξտ� ������� ��ȣ�� ��)

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
	//		�Է¹��� ���ڿ��� �м��Ͽ� real �κа� img �κ��� ã�ƾ� ��
	//		���ڿ��� ���� -> "[��ȣ](�Ǽ���)(��ȣ)i(�����)"	ex) -2 + i3
	//		�̶� �� ���� ��ȣ�� ����������(������ +)
	//	*/
	//	
	//	int begin = 0, end = strlen(str);
	//	double str_img = 0.0, str_real = 0.0;
	//	
	//	// ���� ���� ������ �Ǵ� 'i'�� ��ġ�� ã�´�
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
	//	// ���� 'i'�� ���ٸ� �� ���� �Ǽ� ����
	//	if (pos_i == -1)
	//	{
	//		str_real = get_number(str, begin, end - 1);	// get_number �Լ��� cstdlib �� atof�� �������� -> ���⼭�� ����Լ��� ���� ����
	//	
	//		Complex temp(str_real, str_img);
	//		return (*this) + temp;
	//	}
	//	
	//	// ���� i�� �ִٸ�, �Ǽ��ο� ����θ� ����� ó���ϸ� ��
	//	str_real = get_number(str, begin, pos_i - 1);	// ���ۺ��� i��ġ �ձ����� �Ǽ���
	//	str_img = get_number(str, pos_i + 1, end - 1);	// i��ġ �ں��� �������� �����
	//	
	//	if (pos_i >= 1 && str[pos_i - 1] == '-') str_img *= -1.0;	// ������� ��ȣ ó��(i �ٷξտ� ������� ��ȣ�� ��)
	//	
	//	Complex temp(str_real, str_img);
	//	return (*this) + temp;
//	
//		// �� ������ ���⼭ �������� �����ڸ� �ϳ� ���� ���� �ű�� �Ű��ָ�
//		Complex temp(str);
//		return (*this) + temp;
//		// �̰Ÿ� ����...
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
	if (from > to) return 0;	// ���� �ε����� �� �ε������� ũ�� �߸��� �Է��̹Ƿ� �׳� ����

	if (str[from] == '-') minus = true;
	if (str[from] == '-' || str[from] == '+') from++;	// ���� �ε����� ��ȣ�� ������ ���� �ε��� �ű�

	double num = 0.0;
	double decimal = 1.0;

	bool integer_part = true;
	for (int i = from; i <= to; i++)
	{
		if (isdigit(str[i]) && integer_part)	// isdigit -> cctype�� ���ǵ� �Լ��� ���ڰ� �ƴϸ� 0�� ������
		{
			// �ش� ������ ������ ����. ���� ��� 123.456 �� �־����ٸ�
			// 1 -> 12 -> 123 �̷������� �ڸ����� �÷����鼭 ����
			num *= 10.0;
			num += (str[i] - '0');	// ASCII���� �̿��� ���� -> ASCII -> ���� ���ڸ� ����
		}
		else if (str[i] == '.')
		{
			integer_part = false;
		}
		else if (isdigit(str[i]) && !integer_part)
		{
			// ���� �ݴ�� �ڸ����� �������鼭 ����
			decimal /= 10.0;
			num += ((str[i] - '0') * decimal);
		}
		else
			break;	// ���ڰ� �ƴ� �̻��� ������ ���
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
		- +, -, *, / �� ����Ÿ���� Complex& �� �ƴ� Complex �� ����
			- ���࿡ ����Ÿ���� Complex&��� �����ϰ� ������ ���� �����غ���
				
				Complex a = b + c + b;
	
				- �Ϲ������� ���α׷��� ���忡���� (2 * b) + c ��� �ǵ��Ͽ�������
				- �׷��� �����δ�...
					-> �켱 �� ���� (b.plus(c)).plus(b) ó�� ����
					-> ���۷����� �����ϴ� ��� b.plus(c)�� ����� b + c�� ���� ���ϵǾ� b�� ��
					-> �̶� �ٽ� b�� �������� (b + c) + (b + c)�� ����(b�� �̹� (b + c)�� ���� �� �����Ƿ�)
					-> ���� �ǵ��� �޸� (2 * b) + (2 * c) �� ����
						-> ��� - �̷��� ������ �����Ƿ� "��Ģ����"�� �ݵ�� "���� ������"����!!!!!!!
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
		- ���� ������ = �� �����ε�
			- = �� �����ε� �Ҷ��� �ڱ� �ڽ��� ���۷����� �����ؾ���
				- ������ ���� �����غ��� ��

					a = b = c;

					-> b = c �� b�� �����ؾ� a = b�� ���������� �����
					-> ���� ���� ���� �Ŀ� ���ʿ��� ���縦 ���� ������

			- ����Ʈ ���� �����ڵ� ������. 
				-> �ٸ� ����Ʈ ���� �����ڴ� ���� ���縸 �����ϹǷ� "���� ���簡 �ʿ��� ��� �ݵ�� �����ε��� ���־����"!!!!

			- ���� ���� 2���� �ڵ��� �������� ��Ȯ�ϰ� ������ �� ����
				1) Complex a = b;
				2) Complex a;
				   a = b;
					-> 1): ���� ������ ȣ��
					-> 2): �⺻ �����ڷ� a ���� ��, ���� ������ �Լ� ȣ��

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


	//	a = "3 + i4" + a;	// �Ұ���

	/*
		- ����ְԵ� ���ڿ��� �޾Ƽ� �����ϴ� �����ε� �Լ����� ���� �ּ�ó���ص� �� ������ ���� �����۵���
			- ���ڿ��� ���Ҽ��� �����ϴ� �����ڰ� �ֱ� ������ �����Ϸ��� �˾Ƽ� operator+(Complex(str))�� ��ȯ���ֱ� ������

		- �� a = "3 + i4" + a; ���� ������ ������ �߻���. �����Ϸ��� �����ϰ� ��ȯ������ ���ϱ� ����
	
	
	*/


}