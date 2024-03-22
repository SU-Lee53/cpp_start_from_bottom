
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

	// ����Ÿ�Կ� �ָ�. Complex& �� �ƴ�!
	Complex operator+(const Complex& c) const;
	Complex operator-(const Complex& c) const;
	Complex operator*(const Complex& c) const;
	Complex operator/(const Complex& c) const;

	// ����Ÿ�Կ� �ָ�. �̹����� Complex&��!
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

}