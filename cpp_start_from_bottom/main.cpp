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


int main()
{
	//	최초의 상황
	//
	//	int number = 5;
	//	
	//	std::cout << number << std::endl;	// 5
	//	ChangeVal(&number);
	//	std::cout << number << std::endl;	// 3


	//	참조자 reference의 도입
	//
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


	//	참조의 특징 1 -> 한번 참조된 후에는 다른 변수를 참조하지 못함
	//
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
	//	확인결과 _a와 anotherA의 주소가 다르다


	//	포인터 vs 참조
	// 
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


	//	참조는 메모리상에 존재하지 않을 수 도 있다
	//	int a = 10;
	//	int* p = &a;	// 포인터는 내부에 주소를 담아야하므로 메모리에 8바이트가 할당됨
	//	int& ref_a = a;	// 참조는 메모리가 할당될 필요가 있을까?

	//	참조가 항상 메모리상에 존재하지 않는것은 아니다
	//	int number = 5;
	//	
	//	std::cout << number << std::endl;
	//	std::cout << &number << std::endl;
	//	ChangeVal(number);
	//	std::cout << number << std::endl;
	

	//	참조의 참조따위는 없다
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


	//	리터럴은 참조할 수 없다?
	//	int& ref = 4;
	//	std::cout << ref << std::endl;

	//	리터럴도 참조할 수 있긴 하다
	//	const int& ref = 4;
	//	std::cout << ref << std::endl;


	// 참조의 배열은 불법
	//	int a, b;
	//	int& arr[2] = { a, b };	// C2234 오류 발생

	// 배열의 참조는 합법
	int arr[3] = { 1, 2, 3 };
	int(&ref)[3] = arr;

	ref[0] = 2;
	ref[1] = 3;
	ref[2] = 1;

	std::cout << arr[0] << arr[1] << arr[2] << std::endl;	// 231



	return 0;
}