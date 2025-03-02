
/*
	04.24 ���ø� ��Ÿ ���α׷��� 1
*/

// array wrapper �ǽ�, typeof

//	#include <iostream>
//	#include <typeinfo>
//	
//	template <typename T, unsigned int N>
//	class Array
//	{
//	public:
//		Array(T(&arr)[N])
//		{
//			for (int i = 0; i < N; i++)
//			{
//				data[i] = arr[i];
//			}
//		}
//	
//		T* get_array() { return data; }
//	
//		unsigned int size() { return N; }
//	
//		void print_all()
//		{
//			for (int i = 0; i < N; i++)
//			{
//				std::cout << data[i] << ", ";
//			}
//			std::cout << std::endl;
//		}
//	
//	private:
//		T data[N];
//	};
//	
//	int main()
//	{
//		int arr[3] = { 1, 2, 3 };
//		
//		Array<int, 3> arr_w(arr);
//	
//		arr_w.print_all();
//	
//		// Array<int, 3> �� Array<int, 5>�� ���� Ŭ�����ϱ� �ٸ� Ŭ�����ϱ�
//		std::cout << std::boolalpha << (typeid(Array<int, 3>) == typeid(Array<int, 5>)) << std::endl;
//	
//		/*
//			output
//			1, 2, 3,
//			false
//		*/
//	
//		/*
//			- typeid
//				- Ÿ���� �˷��ִ� ������(�Լ��� �ƴ�)
//				- ����Ϸ��� <typeinfo> ��������� include �ؾ���
//		*/
//	}

// ������ Ÿ�� ����

//	#include <iostream>
//	
//	template <int N>
//	struct Int
//	{
//		static const int num = N;
//	};
//	
//	template <typename T, typename U>
//	struct add
//	{
//		typedef Int<T::num + U::num> result;
//	};
//	
//	int main()
//	{
//		typedef Int<1> one;
//		typedef Int<2> two;
//	
//		typedef add<one, two>::result three;
//	
//		std::cout << "Addition result : " << three::num << std::endl;
//		
//		/*
//			output
//			Addition result : 3
//		*/
//	
//		/*
//			- ������ Ÿ�� ����
//				- �� �ڵ��� ����
//					- struct Int : static const int ���� �ϳ� ���� -> static const�� '�� Ŭ������ �� ���̴�' ��� �ǹ̸� ���� �� ��Ÿ��
//						- static ������ ��� Int�� �ν��Ͻ��� �����ϴ� ���̴ϱ� ���� �ȵȴ�?
//							-> Int<> �� ���ø� ���ڰ� ���� ���� �̻� ���� �ٸ� Ŭ�����̹Ƿ� ���� �ȵ�
//					- struct add : ���ø� ���ڷ� 2���� Ÿ���� �޾Ƽ� �� Ÿ���� num ����� ���� �� ���ο� Ÿ���� result�� ����
//					- typedef Int<1> one;... : ��ü�� �����ϵ��� Ÿ���� ������. ���⼭ one �� two�� 1 �� 2�� ���� ��Ÿ���� Ÿ���� ��(��ü�� �ƴ�)
//					- typedef add<one, two>::result three : one�� two�� ���� ����� ������ result Ÿ���� three ��� ������. three�� ��ó�� Ÿ����
//					- three::num�� ����� 3�� ���
//	
//				- �� �ڵ忡�� 1 + 2�� ��Ÿ�ӿ� �������°� �ƴ϶� ������ Ÿ�ӿ� ������. �� �����Ϸ��� ������ �߿� ���� three::num�� 3���� ġȯ�ϰ� ��Ÿ�ӿ��� ������ ������ ����
//					-> three::num ���� ���콺�� �÷����� �� �� ����
//				
//				- �̷��� Ÿ���� �̿��� ������ ������ ���߿� �̷����(Ÿ���� �ݵ�� ������Ÿ�ӿ� Ȯ���Ǿ�� �ϹǷ�)
//					-> �̷��� Ư¡�� �̿��Ͽ� Ÿ���� ������ ������ Ÿ�ӿ� �����Ǵ� �ڵ�� ���α׷��� �ϴ� ���� ��Ÿ ���α׷����̶�� ��
//					-> C++�� ���ø��� �̿��ؼ� ��Ÿ ���α׷����� �ϱ� ������ ���ø� ��Ÿ ���α׷���(TMP)�̶�� �θ�
//		
//		*/
//	}

// ���ø� ��Ÿ ���α׷���

//	#include <iostream>
//	
//	// TMP�� �̿����� �ʴ� ���丮�� �Լ�
//	int factorial(int n)
//	{
//		if (n == 1) return 1;
//		return n * factorial(n - 1);
//	}
//	
//	template <int N>
//	struct Factorial
//	{
//		static const int result = N * Factorial<N - 1>::result;
//	};
//	
//	template <>
//	struct Factorial<1>
//	{
//		static const int result = 1;
//	};
//	
//	int main()
//	{
//		std::cout << "6! = 1 * 2 * 3 * 4 * 5 * 6 = " << Factorial<6>::result << std::endl;
//	
//		/*
//			output:
//			6! = 1 * 2 * 3 * 4 * 5 * 6 = 720
//		*/
//	
//		/*
//			- ���ø� ��Ÿ ���α׷���
//				- C++���� ���ø��� �̿��� Ÿ���� ������ ������ Ÿ�ӿ� �����Ǵ� �ڵ�� ���α׷��� �ϴ°��� ���ø� ��Ÿ ���α׷���(TMP)�̶�� ��
//				- ���ø��� �̿��ϸ� Ÿ�Կ� ��� "��"�� �ο��� �� �ְ�, �� ������ �̿��ؼ� "����"�� �� �� ����
//				- ���� Factorial Ŭ���� ���ø��� ����...
//					- �⺻���� Ŭ������ �ܼ��� ����
//					- ���ø� Ư��ȭ�� �̿��Ͽ� Factorial<1>�� ���� ó�����־� ������� ������ ������ ����
//					- 6!�� ����� Factorial<6>�� ���� ������ ��ü�� ������ �ƴϰ� �����Ϸ��� ���� Ÿ���� �ϳ��� 
//						-> �� �ڵ常���δ� �޸� �� 720 �̶�� ���� ���� ������ �������� ����
//				- for���� �̿��� ��� �ڵ�� TMP�ε� ���� ������. ����Լ��� �̿��ϰų� �ϴ� ���� ����� ����
//				- if���� �̿��� �ڵ嵵 ���ø� Ư��ȭ�� �̿��Ͽ� ���� ������.
//		*/
//	}

// TMP�� �� ���°�?

//	/*
//		- TMP�� �� ���°�?
//			- �ſ� ū ������ ����
//				-> ������ Ÿ�ӿ� ��� ������ �����Ƿ� ���α׷� ���� �ӵ��� ����
//			- �������� ������
//				-> ��� C++ �ڵ带 TMP�� �ٲܼ��� ������ �ſ� ������
//				-> TMP�� �ۼ��� �ڵ�� ���׸� ã�� ����. ������ Ÿ�ӿ� �����ϱ� ������ ������� �� �ȵǰ� �����ÿ� C++ �����Ϸ��� ��û�� ������ ������ ������
//	
//			- ���� ���������� TMP�� ���������� �������� ���� C++ ���̺귯���� TMP�� �̿���
//				-> ���� ��ȯ���� �ڵ带 ���鶧 ������ Ÿ�� ������ ������ϱ� �����ϱ⵵ ��
//				-> ��Ÿ�� �ӵ� ����� ������ �� ���� ������
//	
//			- �Ʒ��� ���丮�󺸴ٴ� �� ������ ���ø� ������ TMP�� ��� ������� �����غ���
//	*/
//	
//	#include <iostream>
//	
//	// ��Ŭ���� ȣ������ �̿��� �ִ����� ���ϱ�
//	
//	// �Լ� ����
//	int gcd(int a, int b)
//	{
//		if (b == 0)
//			return a;
//	
//		return gcd(b, a % b);
//	}
//	
//	// TMP ����
//	template <int X, int Y>
//	struct GCD
//	{
//		static const int value = GCD<Y, X % Y>::value;
//	};
//	
//	template<int X>
//	struct GCD<X, 0>
//	{
//		static const int value = X;
//	};
//	
//	// ������ ���� �ִ� ������� ���� ���� ������(Ratio) Ŭ������ TMP�� �����
//	
//	template <int N, int D = 1>
//	struct Ratio
//	{
//	private:
//		const static int _gcd = GCD<N, D>::value;
//	
//	public:
//		typedef Ratio<N / _gcd, D / _gcd> type;	// Ŭ������ this�� ����� ������ �ϵ��� typedef�� �̿��Ͽ� �ڱ� �ڽ��� ����Ű�� Ÿ���� �־���
//		static const int num = N / _gcd;	// ����
//		static const int den = D / _gcd;	// �и�
//	
//	};
//	
//	// ������ ��Ģ����
//	
//	template<class R1, class R2>
//	struct _Ratio_add
//	{
//		typedef Ratio<R1::num* R2::den + R2::num * R1::den, R1::den* R2::den> type;
//	};
//	
//	template <class R1, class R2>
//	struct Ratio_add : _Ratio_add<R1, R2>::type {};	// _Ratio_add::type�� �Ź� ������� �ʰ� �ϵ��� �ش� Ÿ���� ��ӹ޴� Ratio_add Ŭ������ ��������
//	
//	template <class R1, class R2>
//	struct _Ratio_subtract
//	{
//		using type = Ratio < R1::num* R2::den - R2::num * R1::den, R1::den* R2::den>;
//	};
//	
//	template <class R1, class R2>
//	struct Ratio_subtract : _Ratio_subtract<R1, R2>::type {};
//	
//	template <class R1, class R2>
//	struct _Ratio_multiply
//	{
//		using type = Ratio<R1::num* R2::num, R1::den* R2::den>;
//	};
//	
//	template <class R1, class R2>
//	struct Ratio_multiply : _Ratio_multiply<R1, R2>::type {};
//	
//	template <class R1, class R2>
//	struct _Ratio_divide
//	{
//		using type = Ratio<R1::num* R2::den, R1::den* R2::num>;
//	};
//	
//	template <class R1, class R2>
//	struct Ratio_divide : _Ratio_divide<R1, R2>::type {};
//	
//	int main()
//	{
//		std::cout << "gcd(36, 24) :: " << GCD<36, 24>::value << std::endl;
//	
//		//	typedef Ratio<2, 3> rat;
//		//	typedef Ratio<3, 2> rat2;
//		//	typedef Ratio_add<rat, rat2> rat3;
//		//	�� typedef�� C++11���� using�̶�� �� �� �������� Ű���带 �̿��Ͽ� �ٲ� �� ����
//	
//		using r1 = Ratio<2, 3>;
//		using r2 = Ratio <3, 2>;
//	
//		using r3 = Ratio_add<r1, r2>;
//		std::cout << "2 / 3 + 3 / 2 = " << r3::num << " / " << r3::den << std::endl;
//	
//		using r4 = Ratio_multiply<r3, r1>;
//		std::cout << "13 / 6 * 2 / 3 = " << r4::num << " / " << r4::den << std::endl;
//	
//		/*
//			output:
//			gcd(36, 24) :: 12
//			2 / 3 + 3 / 2 = 13 / 6
//			13 / 6 * 2 / 3 = 13 / 9
//		*/
//	
//		return 0;
//	}
//	
//	/*
//		- using
//			- C++11 �� ���� ���Ե� Ű����
//			- typedef�� ���� ������ ��
//			- �Լ� �������� ��쿡�� ��� ������
//				-> void �� �����ϰ� int, int �� ���ڷ� �޴� �Լ��� func�� �����ϰ�ʹٸ�
//					-> typedef : typedef void (*func)(int, int)
//					-> using : using func = void(*)(int, int)
//	*/