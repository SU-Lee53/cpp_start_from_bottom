/*
	06.11 - constexpr
*/

/*  ����İ� constexpr  */
//	#include <iostream>
//	
//	template <int N>
//	struct A
//	{
//		int operator()() { return N; }
//	};
//	
//	int main()
//	{
//		constexpr int size = 3;
//		int arr[size];
//	
//		constexpr int N = 10;
//		A<N> a;
//		std::cout << a() << std::endl;
//	
//		constexpr int number = 3;
//		enum B { x = number, y, z };
//		std::cout << B::x << std::endl;
//	
//		/*
//			- output : 
//				10
//				3
//		*/
//	
//		/*
//			- �����
//				- ������ Ÿ�ӿ� ���� ������ �� �ִ� ��
//	
//			- constexpr
//				- constant expression �� ���� Ű����� ��� ���� ��������� ������ִ� Ű����
//		*/
//	
//	}

/*  const vs constexpr  */
//	#include <iostream>
//	
//	int main()
//	{
//		int a;
//	
//		const int b = a;
//		// constexpr int c = a;	// C2131 : ���� ����� ������ �ʾҽ��ϴ�.
//		// constexpr int c = b;	// C2131 : ���� ����� ������ �ʾҽ��ϴ�.
//	
//		constexpr int const_a = 3;
//		constexpr int const_b = const_a;	// ����
//	
//		/*
//			- const vs constexpr
//				- const �� ���ǵ� ����� ������ Ÿ�ӿ� �� ���� ���� ���ص� ��� ����
//					-> �� const int b = a; ���� b �� ������ Ÿ�ӿ� ���� �� �� ����
//					-> �׷��� const �̹Ƿ� ���� �����ϸ� ������ �� ����
//	
//				- constexpr ������ �ݵ�� �����ʿ� �ٸ� ������� �;߸� ��
//					-> �� constexpr int c = a �� a �� constexpr�� �ƴϹǷ� ������ �� ����. ������ Ÿ�ӿ� ���� �� �� ���� ����
//					-> �� constexpr int const_b = const_a �� �캯�� constexpr �̹Ƿ� ������ ������
//	
//				- ��, constexpr �� const ������, const �� constexpr �� �ƴ�
//	
//				- const int i = 3; ���� ���� ������ Ÿ�ӿ� �ʱ�ȭ�Ϸ��� �ݵ�� const �� �ƴ� constexpr �� �����ؾ���
//					-> const int i = 3; �� ������ Ÿ��, ��Ÿ�� ��� �ʱ�ȭ�� ������ ��
//		*/
//	
//	}

/*  constexpr �Լ�  */
//	#include <iostream>
//	
//	int factorial(int N)
//	{
//		int total = 1;
//		for (int i = 1; i <= N; i++)
//			total *= i;
//	
//		return total;
//	}
//	
//	template <int N>
//	struct A
//	{
//		int operator()() { return N; }
//	};
//	
//	template <int N>
//	struct Factorial
//	{
//		const static int value = N * Factorial<N - 1>::value;
//	};
//	
//	template <>
//	struct Factorial<0>
//	{
//		const static int value = 1;
//	};
//	
//	constexpr int c_factorial(int n)
//	{
//		int total = 1;
//		for (int i = 1; i <= n; i++)
//			total *= i;
//	
//		return total;
//	}
//	
//	// constexpr �Լ��� �ɼ� ���� ����
//	int foo() { return 1; }
//	constexpr int bar() { 
//		// return foo();	// C3615 : constexpr �Լ� 'bar'��(��) ��� ���� ������ �� �����ϴ�. 
//		return 1;
//	}
//	
//	int main()
//	{
//		// A<factorial(5)> a;	// C2975 : 'N': 'A'�� ���ø� �μ��� �߸��Ǿ����ϴ�. ������ Ÿ�� ��� ���� �ʿ��մϴ�.
//	
//		// TMP �ڵ�� ������ Ÿ�ӿ� ���ǹǷ� ������ Ÿ�� ���
//		A<Factorial<10>::value> a;
//		std::cout << a() << std::endl;	// 3628800
//	
//		A<c_factorial(10)> b;
//		std::cout << b() << std::endl;	// 3628800
//	
//		int ten = 10;
//		// A<c_factorial(ten)> c;	// C2975 : 'N': 'A'�� ���ø� �μ��� �߸��Ǿ����ϴ�. ������ Ÿ�� ��� ���� �ʿ��մϴ�.
//									// constexpr �Լ��� ���ڷ� ������ Ÿ�� ����� �ƴ� ���� ������ ������ Ÿ�� ����� ��ȯ���� ����
//	
//		/*
//			- constexpr �Լ�
//				- ������ Ÿ�� ����� ��ü�� ���� �� �ִ� �Լ�
//				- ��� ���� ���Ǹ� �����ϸ� constexpr �Լ� ���ο��� ���� ������
//					- goto
//					- ���� (C++ 20 ���ʹ� ����)
//					- ���ͷ� Ÿ���� �ƴ� ������ ���� -> ���߿� �ٽ� �ٷ�
//					- �ʱ�ȭ ���� �ʴ� ������ ����
//					- ���� �߰��� constexpr �� �ƴ� �Լ��� ȣ��
//						-> C++ ǥ�� ������ �ö󰥼��� ���������� ���ݾ� Ǯ���⵵ �� (C++ 23 ������ �� ������� ��κ��� Ǯ���ɷ� ����)
//						-> ���� �ֽ��� https://en.cppreference.com/w/cpp/language/constexpr �� constexpr function �κ��� ����
//						-> constexpr �Լ��ε� �� ���� ������ �Լ� ��ü�� ���ȴٸ� ������ ���� �߻���
//	
//				- ���ڰ� ������ Ÿ�� ������ ���ϰ��� ������ Ÿ�� ��� 
//				- ���ڰ� ������ Ÿ�� ����� �ƴ϶�� �Ϲ� �Լ�ó�� �����ϰ� ���ϰ��� ������ Ÿ�� ����� �ƴ�
//					-> ���� constexpr �� ���� �� �ִ� �Լ��� �ٿ��ִ°��� ����
//				
//		
//		*/
//	}

/*  ���ͷ� Ÿ��  */
/*
	- ���ͷ� Ÿ��
		- �����Ϸ��� ������ Ÿ�ӿ� ������ �� �ִ� Ÿ�� https://en.cppreference.com/w/cpp/named_req/LiteralType
			- void
			- ��Į�� Ÿ�� (char, int, bool, long, float, double, enum, ������ ��� https://en.cppreference.com/w/cpp/named_req/ScalarType)
			- ���۷��� Ÿ��
			- ���ͷ� Ÿ���� �迭
			- �Ʒ� ���ǵ��� �����ϴ� Ÿ��
				- ����Ʈ �Ҹ��ڸ� ������
				- ���� �� �ϳ��� �����ϴ� Ÿ��
					- ���� �Լ�
					- Arggregate Ÿ�� (����� ���� ������, �Ҹ��ڰ� ���� ��� ������ ������� public https://en.cppreference.com/w/cpp/language/aggregate_initialization#Definitions)
					- constexpr �����ڸ� ������ ���� �� �̵������ڰ� ����
		
		- �� Ÿ�Ե鸸 constexpr �Լ� ���ο��� �ٷ� �� ����
		- C++ 14 ���� constexpr �����ڸ� �����Ͽ� ����ڰ� ���� ���ͷ� Ÿ���� ������� ����

*/

/*  constexpr ������  */
//	#include <iostream>
//	
//	class Vector
//	{
//	public:
//		constexpr Vector(int x, int y) : x_(x), y_(y) {}
//	
//		constexpr int x() const { return x_; }
//		constexpr int y() const { return y_; }
//	
//	private:
//		int x_;
//		int y_;
//	};
//	
//	constexpr Vector AddVec(const Vector& v1, const Vector& v2)
//	{
//		return { v1.x() + v2.x(), v1.y() + v2.y() };
//	}
//	
//	template <int N>
//	struct A
//	{
//		int operator()() { return N; }
//	};
//	
//	int main()
//	{
//		constexpr Vector v1{ 1,2 };
//		constexpr Vector v2{ 2,3 };
//	
//		// constexpr ��ü�� constexpr ��� �Լ��� constexpr
//		A<v1.x()> a;
//		std::cout << a() << std::endl;	// 1
//	
//		A<AddVec(v1, v2).x()> b;
//		std::cout << b() << std::endl;	// 3
//	
//		/*
//			- constexpr ������
//				- �⺻������ constexpr �Լ��� ���� ���ǵ��� ��� �����
//				- �߰��� constexpr �������� ���ڵ��� �ݵ�� ���ͷ� Ÿ���̾�߸� �ϰ�, �ٸ� Ŭ������ ������ ���� �� ����
//				- �� �ڵ� ����
//	
//					- constexpr Vector v1{ 1,2 };
//						-> Vector �� �����ڰ� constexpr �̹Ƿ� constexpr �� Vector�� ������ �� ����
//	
//					- A<v1.x()> a;
//						-> x() �Լ� ���� constexpr �̹Ƿ� ������ Ÿ�� ����� ����
//						-> ���� v1 �̳� x() �� �� �ϳ��� constexpr �� �ƴ϶�� ������ ���� ����
//							-> constexpr ��ü�� constexpr ����Լ��� constexpr �� ������
//	
//					- A<AddVec(v1, v2).x()> b;
//						-> Vector �� ���ͷ� Ÿ���̰�, AddVec ���� constexpr �Լ��̹Ƿ� constexpr ��ü Vector �� ������
//	
//		
//		*/
//	}

/*  if constexpr  */
#include <iostream>
#include <type_traits>

/*  ���ڰ� ������ Ÿ������ �˷��ִ� �Լ� - TMP ����  */
//	template<typename T>
//	void show_value(T t)
//	{
//		std::cout << "�����Ͱ� �ƴϴ� : " << t << std::endl;
//	}
//	
//	template <typename T>
//	void show_value(T* t)
//	{
//		std::cout << "������ �̴� : " << *t << std::endl;
//	}

/*  ���ڰ� ������ Ÿ������ �˷��ִ� �Լ� - <type_traits> �̿� -> ������ ����  */
//	template <typename T>
//	void show_value(T t)
//	{
//		if (std::is_pointer<T>::value) 
//			std::cout << "������ �̴� : " << *t << std::endl;	// C2100 : 'T' ������ �ǿ����ڸ� �������� �� �����ϴ�.
//		else 
//			std::cout << "�����Ͱ� �ƴϴ� : " << t << std::endl;
//	
//		// T �� int �� �߷еǾ� * �����ڷ� �������� �Ұ����ϹǷ� �����ϵ��� ����
//	}

/* ���ڰ� ������ Ÿ������ �˷��ִ� �Լ� - <type_traits> + if constexpr �̿� */
//	template <typename T>
//	void show_value(T t)
//	{
//		if constexpr (std::is_pointer<T>::value)	// std::is_pointer<T>::value �� std::is_pointer_v<T> �� ���� ����
//			std::cout << "������ �̴� : " << *t << std::endl;
//		else
//			std::cout << "�����Ͱ� �ƴϴ� : " << t << std::endl;
//	}
//	
//	int main()
//	{
//		int x = 3;
//		show_value(x);
//	
//		int* p = &x;
//		show_value(&x);
//	
//		/*
//			- if constexpr
//				- bool �� Ÿ�� ��ȯ�� �� �ִ� ������ Ÿ�� ������� �������� �ö� 
//					- ���̸� else �κ��� ������ ���������� �ʰ� ����
//					- �����̸� else �κи� �������ϰ� ���κ��� ����
//	
//				- �ƿ� �����ϵ��� �����Ƿ� �� show_value ���� �Լ��� ���� �� ����
//					- ������ show_value �� ���ø� ���� �߷п� ���� ������ ������ �߻��ϴ� if �бⰡ ������
//					- if constexpr �� ����ϸ� ������ ������ �߻��ϴ� �κ��� ���������� �����Ƿ� ������ ����
//		*/
//	}

/*  C++ 20 �� �߰��� constexpr  */
/*
	- constexpr �Ҹ��� https://en.cppreference.com/w/cpp/language/constexpr �� constexpr destructor ����
	- constexpr new https://www.cppstories.com/2021/constexpr-new-cpp20/

	- ��� ������ �� ���� ����

*/