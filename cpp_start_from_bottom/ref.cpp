#include <iostream>

//	int ChangeVal(int* p)
//	{
//		*p = 3;
//	
//		return 0;
//	}

int ChangeVal(int& p)
{
	p = 3;
	std::cout << &p << std::endl;
	return 0;
}

int& functionA()
{
	int a = 2;
	return a;	// �������� a�� ����
}

int& functionB(int& a)
{
	a = 5;
	return a;	// ���ڷ� ���� a�� ����
}

int functionC()
{
	int a = 5;
	std::cout << &a << std::endl;
	return a;
}

int main()
{
	/* ������ ��Ȳ */
	
	//	int number = 5;
	//	
	//	std::cout << number << std::endl;	// 5
	//	ChangeVal(&number);
	//	std::cout << number << std::endl;	// 3


	/* ������ reference�� ���� */
	
	//	int a = 3;
	//	int& anotherA = a;
	//	int* pointA = &a;
	//	
	//	anotherA = 5;
	//	std::cout << "a : " << a << std::endl;
	//	std::cout << "anotherA : " << anotherA << std::endl;
	//	
	//	std::cout << "adress of a : " << &a << std::endl;
	//	std::cout << "adress of anotherA : " << &anotherA << std::endl;
	//	
	//	std::cout << "pointA : " << pointA << std::endl;
	//	std::cout << "value in pointA : " << *pointA << std::endl;


	/* ������ Ư¡ -> �ѹ� ������ �Ŀ��� �ٸ� ������ �������� ���� */
	
	//	int _a = 0;
	//	anotherA = _a;
	//	
	//	std::cout << "_a : " << _a << std::endl;
	//	std::cout << "anotherA : " << anotherA << std::endl;
	//	std::cout << "a : " << a << std::endl;
	//	
	//	std::cout << "adress of _a : " << &_a << std::endl;
	//	std::cout << "adress of a : " << &a << std::endl;
	//	std::cout << "adress of anotherA : " << &anotherA << std::endl;
	//	Ȯ�ΰ�� _a�� anotherA�� �ּҰ� �ٸ���


	/* ������ vs ���� */
	
	//	int a = 10;
	//	int* p = &a;
	//	std::cout << "int* p = &a" << std::endl;
	//	std::cout << "p : " << p << std::endl;
	//	std::cout << "adress of a : " << &a << std::endl;
	//	std::cout << "value of p : " << *p << "\n" << std::endl;
	//	
	//	int b = 3;
	//	p = &b;
	//	std::cout << "p = &b" << std::endl;
	//	std::cout << "p : " << p << std::endl;
	//	std::cout << "adress of b : " << &b << std::endl;
	//	std::cout << "value of p : " << *p << std::endl;

	
	/* ������ �޸𸮻� �������� ���� �� �� �ִ�*/

	//	int a = 10;
	//	int* p = &a;	// �����ʹ� ���ο� �ּҸ� ��ƾ��ϹǷ� �޸𸮿� 8����Ʈ�� �Ҵ��
	//	int& ref_a = a;	// ������ �޸𸮰� �Ҵ�� �ʿ䰡 ������?

	/* ������ �׻� �޸𸮻� �������� �ʴ°��� �ƴϴ�*/

	//	int number = 5;
	//	
	//	std::cout << number << std::endl;
	//	std::cout << &number << std::endl;
	//	ChangeVal(number);
	//	std::cout << number << std::endl;
	

	/*������ ���������� ���� */
	
	//	int x;
	//	int& y = x;
	//	int& z = y;
	//	
	//	x = 1;
	//	std::cout << "x : " << x << " y : " << y << " z : " << z << std::endl;
	//								  				  
	//	y = 2;						  				  
	//	std::cout << "x : " << x << " y : " << y << " z : " << z << std::endl;
	//								  				  
	//	z = 3;						  				  
	//	std::cout << "x : " << x << " y : " << y << " z : " << z << std::endl;
	//	
	//	std::cout << "adress of x : " << &x << std::endl;
	//	std::cout << "adress of y : " << &y << std::endl;
	//	std::cout << "adress of z : " << &z << std::endl;

	
	/* ���ͷ��� ������ �� ����? */

	//	int& ref = 4;
	//	std::cout << ref << std::endl;

	/* ���ͷ��� ������ �� �ֱ� �ϴ� */

	//	const int& ref = 4;
	//	std::cout << ref << std::endl;
	

	
	/* ������ �迭�� �ҹ�*/

	//	int a, b;
	//	int& arr[2] = { a, b };	// C2234 ���� �߻�

	/* �迭�� ������ �չ� */

	//	int arr[3] = { 1, 2, 3 };
	//	int(&ref)[3] = arr;
	//	
	//	ref[0] = 2;
	//	ref[1] = 3;
	//	ref[2] = 1;
	//	
	//	std::cout << arr[0] << arr[1] << arr[2] << std::endl;	// 231
	


	/* ���������� ������ �����ϴ� �Լ� */
 
	//	int b = functionA();
	//	b = 3;
	//	std::cout << &b << std::endl;
	//	���� ������ ���� �´µ�... vc�����Ϸ��� ������ ���� ����
	//	gcc �����Ϸ� ���� �ٷ� ������ ��´�
	//	https://stackoverflow.com/questions/50868524/why-return-local-variable-with-reference-type-works-in-vs2012
	//	����� ������ �޴� ����� �߰��Ͽ��� �Ȱ��� �������� �÷������� �̻��ϰ� �ȵ�
	//	���� : VS�� �Լ� ���� ��� �޸𸮸� ��ȯ���� �ʴ°����� ����. �޸𸮸� ��� ������ ��������.



	/* �ܺκ����� ������ �����ϴ� �Լ� */

	//	int b = 2;
	//	int c = functionB(b);
	//	std::cout << &b << std::endl;
	//	std::cout << &c << std::endl;

	/* ������ �ƴ� ���� �����ϴ� �Լ��� �����ڷ� �ޱ� */

	//	int& c = functionC();
	//	Dangling Reference!

	/* �� ������ �ذ�� : const ������ */
	//	const int& c = functionC();
	//	std::cout << c << std::endl;
	//	std::cout << &c << std::endl;


	return 0;
}