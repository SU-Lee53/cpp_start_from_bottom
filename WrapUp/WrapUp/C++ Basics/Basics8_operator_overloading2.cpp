/*
	03.25, 26 ������ �����ε� 2

*/

// - friend

//	/*
//		- friend : �ٸ� Ŭ������ private ��� �Լ�, �����鿡 ���� ���� ������ �ο���
//			- ¦��� ���� ����� �Ʒ����� B�� A�� ����� ���� ���������� A�� B�� ����� ������ �� ����
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
//			//	b.private_num = 2;	// �ȵ�
//		}
//	
//	private:
//		void private_func() { }
//		int private_num;
//	
//		// B �� A�� ģ��
//		friend class B;
//	
//		// func �� A�� ģ��
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
//			// A�� private �ʵ忡 ���ǵ� �͵������� friend�̹Ƿ� ���� ��������
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
//		// A�� private �ʵ忡 ���ǵ� �͵������� friend�̹Ƿ� ���� ��������
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


	// ����Ÿ�Կ� �ָ�. Complex& �� �ƴ�!
	// �ڱ��ڽ��� �������� �ʴ� ���� �����ڴ� �ܺ��Լ��� ����������
	//	Complex operator+(const Complex& c) const;
	//	Complex operator-(const Complex& c) const;
	//	Complex operator*(const Complex& c) const;
	//	Complex operator/(const Complex& c) const;

	// ����Ÿ�Կ� �ָ�. �̹����� Complex&��!
	Complex& operator=(const Complex& c);

	// ���� ��Ģ ������ -> �̹����� ���۷����� ������
	Complex& operator+=(const Complex& c);
	Complex& operator-=(const Complex& c);
	Complex& operator*=(const Complex& c);
	Complex& operator/=(const Complex& c);

	void println() { std::cout << "( " << real << " , " << img << " )" << std::endl; }

	// Ŭ���� �ܺ��� �����ε� �Լ��� Complex�� private ��������� ���� ��������
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

/* ==================== MyString�� operator[] �����ε� ========================= */

char& MyString::operator[](const int index)
{
	return string_content[index];
}


/*====================== int Wrapper �� ���� ========================== */

// int Wrapper Int : int�� Int Ŭ������ �θż� intó�� �ٷ�� �ִ� ��ü�� ����
class Int
{
public:
	Int(int _data) : data(_data) {}
	Int(const Int& i) : data(i.data) {}

	// Ÿ�� ��ȯ ������ �����ε� -> �̸� ���� �׳� int ������ ����� �� ����
	operator int() { return data; }

private:
	int data;
};

/*====================== ����/���� ���� ������ (Test Ŭ����) ========================== */

class Test
{
public:
	Test(int x) : x(x) {}
	Test(const Test& t) : x(t.x) {}

	// ���� ���� ������ ++t -> ++���� ���� ��ü�� ��ȯ
	Test& operator++()
	{
		x++;
		std::cout << "���� ���� ������" << std::endl;
		return *this;
	}

	Test& operator++(int)
	{
		Test temp(*this);
		x++;
		std::cout << "���� ���� ������" << std::endl;
		return temp;
	}

	int get_x() const { return x; }
private:
	int x;
};

void func(const Test& t)
{
	std::cout << "x : " << t.get_x() << std::endl;
}

//	int main()
//	{
//		// - ���� ������
//	
//		/*
//			- ���� ������
//				- ������ ���� �����ε��� �Լ��� a = "-1.1 + i3.923" + a; �� ���� ������ ���� ������� ����
//					- �� ������ �����Ϸ��� �ϴ� ���� ���� ��. �����Ϸ��� �����ε��� �����ڸ� ���� �ϳ��� ������� �ؼ���(���� ������ ������ @)
//						1) *a.operator@(b);
//						2) *operator(a, b);
//						-> 1)�� ���´� a�� Ŭ���� ��� �Լ��� ����
//						-> 2)�� ���´� Ŭ���� �ܺο� ���ǵǾ� �ִ� �Ϲ����� �Լ��� �ǹ���
//					- �̰��� �ذ��ϱ� ���� �Ϲ����� �Լ��� ������ �����ε��� ���� -> Complex operator+(const Complex& a, const Complex& b)
//						- ���� �� 2)�� ���·� operator+(Complex("-1.1 + i3.923"), a);�� ���·� ������ ��
//						- �̶� ���������� ������ ���ؼ��� a �� b�� real�� img�� ������ �����ؾ� �ϴµ� �ش� �������� private��
//							-> Ŭ���� �ܺ��� �����ε� �Լ��� Ŭ������ friend�� �����ϸ� ��!
//					
//					- ���� �߻� -> 1), 2) ��� ���°� �����Ǿ� �־� �����Ϸ��� ��� ��� ���������� ���� ������ �߻���Ŵ
//						-> �ڱ� �ڽ��� �������� �ʴ� ���� ������(+,-,*,/ ��) �� �ܺ��Լ��� �����ϴ°��� ��Ģ
//						-> �ڱ� �ڽ��� �����ϴ� ���� ������(+=, -= ��) �� Ŭ���� ��� �Լ��� �����ϴ°��� ��Ģ
//						++ �������� += �����ڰ� ������ �������� ���� ������ �������
//						
//		*/
//	
//		// - ����� ������  >>, <<
//	
//		//	Complex a = Complex(-1.1, 3.923);
//		//	std::cout << a;
//		//	
//		//	/*
//		//		output
//		//		( -1.1 , 3.923 )
//		//	*/
//		//	
//		//	
//		//	/*
//		//		- ����� ������ >>, <<
//		//			- �⺻������ �츮�� std::cout << a; �ϴ� ���� std::cout.operator<<(a)�� �ϴ� ������ �����ε� �Ǿ�����
//		//				- ������ <ostream> ����� ��û�� ���� << �����ε��� �Ǿ��ְ� �� ���п� �⺻ Ÿ�Ե��� ��������� ����� ������
//		//	
//		//			- �׷��� Complex�� <<�� ����ؼ� �����Ӱ� ����ϵ��� �����ε� �����Ѱ�? -> ����
//		//				- �ٸ� <ostream>�� ���� �����ε��� �ϴ°��� ǥ�� ��������� �ǵ帮�� �����̹Ƿ� �Ұ�����
//		//				-> ��� ostream Ŭ������ Complex ��ü�� �޴� ���� ������ �����ε��� �ϸ� ������
//		//	
//		//			- ���� �غ���
//		//				- std::ostream& operator<<(std::ostream& os, const Complex& c); �� �����ε��Ͽ� ����
//		//					- �̶� �����ε� �Լ��� c�� ����� ���� �� �� ���µ� 3������ ��� ���������
//		//						1. real�� img�� �׳� public���� �ٲ۴� 
//		//							-> �翬�� ���� ���� ������� ���� �������� �ִ��� ����°��� ����
//		//						2. Complex �� print(std::ostream& os)�� ���� ����Լ��� �߰��ϰ�, �̸� operator<<���� ȣ��
//		//							-> �������� �ϴ��� skip
//		//						3. operator<< �Լ��� friend�� ����
//		//							-> �ϴ� �̰� ����ؼ� �ذ�
//		//				- ���� ������� cin�� �����غ��� ����
//		//	
//		//			++ friend�� ������ ������� ����. oop�� ��Ģ�� �ϳ��� ���� ���м��� ���μ��� Ű�����̱� ������
//		//				-> �׷��� ���� ���Ͱ��� ��Ȳ������ 2������ �ذ���� ����
//		//				-> �ٸ� �Ϻ� ��Ȳ���� �����ϰ� ���Ǳ� ��
//		//	*/
//	
//		//	- ÷�� ������
//	
//		//	MyString str("abcdef");
//		//	str[3] = 'c';	// ���۷����� ���ϵǹǷ� ���� ������ ���������� �۵���
//		//	
//		//	str.println();
//		//	
//		//	/*
//		//		output
//		//		abccef
//		//	*/
//		//	
//		//	/*
//		//		- ÷�� ������ [] (subscript)
//		//			- ����Ÿ��& operator[](const int index)�� ���·� ����. index ��°�� ���Ҹ� ����
//		//			- char& ���۷����� ���� -> �� str[3] = 'c'; �� ���� ���Կ������ �����Ϸ��� ���۷����� ���ϵǾ�� ��
//		//	*/
//	
//		// - Wrapper -> Ÿ�� ��ȯ ������ �����ε�
//	
//		//	Int x = 3;
//		//	int a = x + 4;
//		//	
//		//	x = a * 2 + x + 4;
//		//	std::cout << x << std::endl;
//		//	
//		//	/*
//		//		output
//		//		21
//		//	*/
//		//	
//		//	/*
//		//		- Wrapper : ���� �ڷ����� ��üó�� �ٷ�� ���� Ŭ������ ���δ� ��
//		//			- int�� Wrapper�� Int�� �׳� int�� ��Ȯ�ϰ� �Ȱ��� �۵��ϰ� �غ���
//		//				- int ������ �����ڸ� ���� �����ε��ϴ� ��� -> X �ʹ� ���⵵ �ϰ� ���� �̹� �ִ� ����� �����ε��� �ٽ��ϴ°��� ��ȿ����
//		//				-> Int Ŭ������ �����Ϸ��� �׳� 'int' �� �ٲܼ� �ֵ��� Ÿ�� ��ȯ
//		//	
//		//			- Ÿ�� ��ȯ ������ type()
//		//				- operator (��ȯ�ϰ��� �ϴ� Ÿ��) () �� ���·� ����
//		//				- ���� ��� operator int()�� �����ε�
//		//	*/
//	
//		// - ����/���� ���� ������ ++a / a++, --a / a--
//	
//		//	Test t = 3;
//		//	
//		//	func(++t);	// ����
//		//	func(t++);	// ����
//		//	std::cout << "x : " << t.get_x() << std::endl;
//		//	
//		//	/*
//		//		- ���� ������
//		//			- ����/���� ������ ����
//		//				- ���� : ���� ���� '����'��Ű�� ����� '����'
//		//				- ���� : ���� ���� '����'��Ű�� �� ���� '����'
//		//				-> ������ �� �����ڴ� ������ �����ε� �Ǿ�� ��
//		//	
//		//			- �����ε��� ����/���� ������ ���� -> ���� ���� �������� �����ε��� ���ڷ� int�� �޾���
//		//				- operator++() -> ���� �����ε�
//		//				- operator++(int) -> ���� �����ε�
//		//				-> ������ ���ڷ� ���� ���� ������ �ʰ� �ܼ� ���п����θ� ����
//		//	
//		//			- ���� ������ ��� ���� ���� ��ü�� �̸� ����صξ�� �� -> ���� �����ڰ� ȣ��ǹǷ� ���� ���꺸�� �� ����
//		//	*/
//	
//	
//		// ������ �����ε� �ٽ� ���
//		
//		/*	
//			- �� ���� ������ ��ü ���̿����� ���� �����ڴ� ��� �Լ��� �ƴ� �ܺ� �Լ���(����) �����ε� �ϴ°��� ����: + - * / ��
//			- �� ���� ��ü ������ ���� ���������� �� ��ü�� ���� �ٲ�ٴ��� ���� �������� ���� ��� ����Լ��� �����ε� �ϴ°��� ����: += -= *= /= ��
//			- ���� �����ڴ� ����Լ��� �����ε� �ϴ°��� ����: ++ --
//			- �Ϻ� ������ ���� �ݵ�� ����Լ��θ� �����ε� �Ǿ����: [] == ��
//		
//			https://stackoverflow.com/questions/4421706/what-are-the-basic-rules-and-idioms-for-operator-overloading <- ���⸦ �����ؼ� �� �����غ��°͵� ����
//		
//		
//		*/
//	
//	
//	
//	}




