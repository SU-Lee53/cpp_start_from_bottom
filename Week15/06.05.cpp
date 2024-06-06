/*
	06.05 - �Լ� ��ü std::function, std::mem_fn, std::bind
*/

/*  Callable  */
//	#include <iostream>
//	#include <functional>
//	
//	struct S
//	{
//		void operator()(int a, int b) { std::cout << "a + b = " << a + b << std::endl; }
//	};
//	
//	int main()
//	{
//		S some_obj;
//		some_obj(3, 5);
//	
//		auto f = [](int a, int b) -> void {std::cout << "a + b = " << a + b << std::endl; };
//		f(3, 5);
//	
//		// INVOKE
//		std::cout << "INVOKE ����" << std::endl;
//		std::invoke(some_obj, 3, 5);
//		std::invoke(f, 3, 5);
//	
//		/*
//			- Callable
//				- �� �״�� "ȣ���� �� �ִ�" ��� ���� �ǹ���
//					-> C++ ������ ()�� ȣ���� �� �ִ� ��� �͵��� �ǹ���
//	
//				- ���� Ŭ���� S�� ��ü�� some_obj �� Callable
//					-> ��Ȯ���� some_obj.operator()(3,5) �� �� �� ������ ()�� ȣ�� �����ϴ� Callable
//				- ���� �Լ��� f �� Callable
//					-> �Ϲ����� �Լ��� �ƴϴ��� ()�� ȣ���� �����ϸ� �� Callable
//	
//	
//				�� cppreference ������ ������ ���� �����ϰ� ����
//					The type T satisfies Callable if
//					Given
//						- f, an object of type T,
//						- ArgTypes, suitable list of argument types,
//						- R, suitable return type.
//					The following expressions must be valid:
//					Expression									Requirements
//					INVOKE<R>(f, std::declval<ArgTypes>()...)	The expression is well-formed in unevaluated context.
//	
//					Ÿ�� T �� �Ʒ��� ������ �����ϸ� Callable��
//					�־���
//						- f �� T Ÿ���� ��ü
//						- ArgTypes �� ���� Ÿ�Կ� ���� ������ ���ڵ�
//						- R �� ������ ���� Ÿ��
//					�� ���ؼ� ������ ǥ������ ��ȿ�ؾ߸� ��
//					ǥ����										�䱸����
//					INVOKE<R>(f, std::declval<ArgTypes>()...)	�ش� ǥ������ �򰡵��� ���� ���ؽ�Ʈ���� �� ������(Ʋ���� ���� �����۵� �Ѵٴ� �ǹ�)
//	
//					-> ��, INVOKE, INVOKE<R> ������ ��ȿ�� �͵��� ���� Callable
//						-> INVOKE
//							- ������ �ǹ��� invoke : �߻��ϴ�, �ǽ��ϴ� ��
//							- ���𰡸� ȣ���ϴ� �ϳ��� ���� https://en.cppreference.com/w/cpp/utility/functional �� 
//						-> INVOKE<R> �� C++ 23 ���� std::invoke_r<R> �� ����Ͽ� ����
//						-> �� ������ std::invoke() �� ����
//	
//	
//	
//	
//	
//	
//	
//		
//		*/
//	}

/*  std::function  */
//	#include <iostream>
//	#include <functional>
//	#include <string>
//	
//	int some_func1(const std::string& a)
//	{
//		std::cout << "Func1 ȣ�� " << a << std::endl;
//		return 0;
//	}
//	
//	struct S
//	{
//		void operator()(char c) { std::cout << "Func2 ȣ�� " << c << std::endl; }
//	};
//	
//	int main()
//	{
//		// C�� �Լ� ������
//		std::cout << "C-style function pointer examples" << std::endl;
//	
//		int (*func1)(const std::string&) = some_func1;
//		// void (*func2)(char) = S();	// �Լ� �����ʹ� �Լ��� ���� �� �־���
//		void (*func3)() = []()-> void { std::cout << "Func3 ȣ��" << std::endl; };
//	
//		func1("hello");
//		std::cout << "functor �� �Լ� �����Ϳ� ���� �� ����" << std::endl;
//		func3();
//	
//		std::cout << "------------------------------" << std::endl;
//	
//		// C++ �� std::function
//		std::cout << "std::function examples" << std::endl;
//		std::function<int(const std::string&)> f1 = some_func1;
//		std::function<void(char)> f2 = S();
//		std::function<void()> f3 = []() {std::cout << "Func3 ȣ��" << std::endl; };
//	
//		f1("hello");
//		f2('c');
//		f3();
//	
//	
//		/*
//			- output : 
//				C-style function pointer examples
//				Func1 ȣ�� hello
//				functor �� �Լ� �����Ϳ� ���� �� ����
//				Func3 ȣ��
//				------------------------------
//				std::function examples
//				Func1 ȣ�� hello
//				Func2 ȣ�� c
//				Func3 ȣ��
//		*/
//	
//		/*
//			- std::function
//				- std::function : Callable �� �͵��� ��ü�� ���·� ������ �� �ִ� Ŭ����
//				- C �� �Լ� �����Ϳ��� ����
//					- �Լ� ������(C) : ��¥ �Լ��� ���� ����
//					- std::function(C++) : ��� Callable ���� ����
//						-> �� �ڵ忡�� ���ٽ��� �Լ�, ����(functor), ���� �Լ� ��� ���� ������
//				
//				- ����
//					- ���ø� ���ڷδ� <����Ÿ��(����Ÿ��)> �� ����
//					- �Ϲ� �Լ�, ����, �����Լ� ��� ������
//					ex) ���� int �� �����ϰ� ���ڷ� const string& �� �޴� f �� ����� �ʹٸ� :
//						
//							std::function<int(const string&)> f;
//	
//						�� �����ϸ� ��
//		*/
//	}

/*  ��� �Լ��� ������ std::function  */
//	#include <functional>
//	#include <iostream>
//	#include <string>
//	
//	class A
//	{
//	public:
//		A(int c) : c(c) {}
//		
//		int some_func() 
//		{ 
//			std::cout << "���� �Լ� : " << ++c << std::endl; 
//			return c;
//		}
//	
//		int some_const_func() const
//		{
//			std::cout << "��� �Լ� : " << c << std::endl;
//			return c;
//		}
//	
//	
//	private:
//		int c;
//	};
//	
//	int main()
//	{
//		A a(5);
//		//	std::function<int()> f1 = a.some_func;	// E0300 : ���ε��� �Լ��� ���� �����ʹ� �Լ��� ȣ���ϴ� ������ ����� �� �ֽ��ϴ�
//		std::function<int(A&)> f1 = &A::some_func;
//		std::function<int(const A&)> f2 = &A::some_const_func;
//	
//		f1(a);
//		f2(a);
//	
//		/*
//			- output:
//				���� �Լ� : 6
//				��� �Լ� : 6
//		*/
//	
//		/*
//			- ��� �Լ��� ������ std::function
//				- std::function �� �Ϲ����� Callable ���� ��°��� ���� ����
//				- std::function �� ��� �Լ����� ��� ���ؼ��� ���� �޶����� �͵��� ����
//					- �� �ڵ忡�� 
//						
//							std::function<int()> f1 = a.some_func
//	
//						-> f1 ȣ�� �� �Լ��� �ڽ��� ȣ���ϴ� ��ü�� �������� �� �� ����
//						-> �׷��Ƿ� ������ c ���� � ��ü�� c ���� �� �� ����
//	
//						-> std::function �� ��� �Լ��� ��� ���ؼ� �Ʒ�ó�� �ϸ� ��
//							1) ���� �Լ��� ���
//	
//								std::function<int(A&)> f1 = &A::some_func;
//	
//							2) ��� �Լ��� ���
//	
//								std::function<int(const A&)> f2 = &A::some_const_func;
//	
//							-> ��� �Լ��� �Ϲ� �Լ��� �޸� & �����ڸ� �̿��� �ּҰ��� ���� �Ѱ��־�� ��
//								-> C++ ǥ�ؿ��� �Ϲ��Լ��� �̸��� �����ϸ� �ּҰ����� �Ͻ��� ��ȯ�� �������� ����Լ��� �׷��� ����
//								-> ���� ����Լ��� ��������� �ּҰ��� �Ѱ��־�� ��
//							
//							-> ��ü ȣ��ÿ��� �ݵ�� ȣ���ϰ��� �ϴ� ��ü�� ���ڷ� �޾��־�� ��
//								-> a �� ����Լ��� ȣ���ϰ� �ʹٸ� 
//	
//									f1(a);
//									f2(a);
//	
//								�� ȣ���ϸ� ��
//	
//						�� python ���� Ŭ���� ��� �Լ��� �����Ҷ� def func(self) ó�� �ݵ�� ù��° ���ڷ� �ڱ� �ڽ��� �ִ°Ͱ� ���� ������
//	
//		*/
//	}

/*  mem_fn : ��� �Լ����� �Լ� ��ü��  */
//	#include <algorithm>
//	#include <functional>
//	#include <iostream>
//	#include <vector>
//	
//	using std::vector;
//	
//	int main()
//	{
//		vector<int> a(1);
//		vector<int> b(2);
//		vector<int> c(3);
//		vector<int> d(4);
//	
//		vector<vector<int>> container;
//		container.push_back(b);
//		container.push_back(d);
//		container.push_back(a);
//		container.push_back(c);
//	
//		std::function<size_t(const vector<int>&)> sz_func = &vector<int>::size;
//	
//		vector<int> size_vec(4);
//		// std::transform(container.begin(), container.end(), size_vec.begin(), &vector<int>::size); // C2064 ���� 1���� �μ��� �޾Ƶ��̴� �Լ��� ������ �ʽ��ϴ�.
//		
//		// std::transform(container.begin(), container.end(), size_vec.begin(), sz_func); // Ȥ�� 
//		std::transform(container.begin(), container.end(), size_vec.begin(), std::mem_fn(&vector<int>::size));
//	
//		// std::mem_fn ���� �����Լ��� �̿��ص� ������
//		// std::transform(container.begin(), container.end(), size_vec.begin(), [](const auto& v) -> size_t { return v.size(); });
//	
//	
//		for (const auto& e : size_vec)
//			std::cout << "���� ũ�� :: " << e << std::endl;
//	
//		/*
//			- std::mem_fn
//				- std::mem_fn : ��� �Լ��� �Լ� ��ü�� ����� �������ִ� �Լ�
//				- �� �ڵ� ����
//					- 1 ~ 4 ������ ũ�⸦ ���� vector a, b, c, d �� ����� �� ������ ũ�⸦ �����ϴ� size_vec �� std::transform�� �̿��� ä����� �ڵ�
//					- std::transform �� ������ �κп� &vector<int>::size �Լ��� ���� �Ѱ��ָ� ������ ���� �߻�
//						-> ������ �˷��� <algorithm> �ȿ� �ִ� std::transform �Լ��� ����� ������
//	
//							_EXPORT_STD template <class _InIt, class _OutIt, class _Fn>
//							_CONSTEXPR20 _OutIt transform(const _InIt _First, const _InIt _Last, _OutIt _Dest, _Fn _Func) {
//								// transform [_First, _Last) with _Func
//								_STD _Adl_verify_range(_First, _Last);
//								auto _UFirst      = _STD _Get_unwrapped(_First);
//								const auto _ULast = _STD _Get_unwrapped(_Last);
//								auto _UDest       = _STD _Get_unwrapped_n(_Dest, _STD _Idl_distance<_InIt>(_UFirst, _ULast));
//								for (; _UFirst != _ULast; ++_UFirst, (void) ++_UDest) {
//									*_UDest = _Func(*_UFirst);
//								}
//							
//								_STD _Seek_wrapped(_Dest, _UDest);
//								return _Dest;
//							}
//	
//						-> ������ ������ �Լ��� �����Ű�� �ڵ�� *_UDest = _Func(*_UFirst);
//						-> �� �κп� &vector<int>::size �� �ٷ� ���� �Ʒ�ó�� �õ���
//	
//							&vector<int>::size(*_UFirst);
//	
//						-> ��� �Լ��� (*_UFirst).(&vector<int>::size) �� ȣ���ϴ°��� �����Ƿ� ���� �����ų �� ����
//	
//					- ���� �������� std::transform ������ ���ؼ��� &vector<int>::size �� std::function ���� ����� �־����
//						-> ���� ����� ���� sz_func �̰� �Ʒ�ó�� �������
//	
//							std::function<size_t(const vector<int>&)> sz_func = &vector<int>::size
//	
//					- ��ó�� �Ź� ����� ���� ���� �����Ƿ� std::mem_fn �� �̿��ؼ� �ذ���
//						
//						std::mem_fn(&vector<int>::size)
//	
//						�� �Լ� ��ü�� ���� ����� std::transform�� ������ ���� �۵���
//	
//	
//				- �������� std::mem_fn�� ���� ������ �ʴµ� �����Լ��� �ֱ� ������
//					-> std::mem_fn �� �� �ڵ尡 ����ϱ� ������ <functional> ����� �����ؾ���
//					-> �ݸ� �����Լ��� �ڵ�� ���� ������������ ���� ��� ���� �ٷ� ��� ������
//		
//		
//		*/
//	
//	}

/*  std::bind  */
#include <functional>
#include <iostream>

void add(int x, int y)
{
	std::cout << x << " + " << y << " = " << x + y << std::endl;
}

void subtract(int x, int y)
{
	std::cout << x << " - " << y << " = " << x - y << std::endl;
}

struct S
{
	int data;
	S(int data) : data(data) { std::cout << "�Ϲ� ������ ȣ��" << std::endl; }	
	S(const S& s) : data(s.data) { std::cout << "���� ������ ȣ��" << std::endl; }
	S(S&& s) : data(s.data) { std::cout << "�̵� ������ ȣ��" << std::endl; }
};

void foo(S& s1, const S& s2) { s1.data = s2.data + 3; }

int main()
{
	auto add_with_2 = std::bind(add, 2, std::placeholders::_1);
	add_with_2(3);

	// �ι�° ���ڴ� ���õ�
	add_with_2(3, 4);

	auto subtract_with_2 = std::bind(subtract, std::placeholders::_1, 2);
	auto negate = std::bind(subtract, std::placeholders::_2, std::placeholders::_1);

	subtract_with_2(3);	// 3 - 2;
	negate(4, 2);	// 2 - 4;

	/*
		- ������� output :
			2 + 3 = 5
			2 + 3 = 5
			3 - 2 = 1
			2 - 4 = -2
	*/


	S s1(1), s2(2);
	std::cout << "Before::s1.data :  " << s1.data << std::endl;

	std::cout << "\n���纻�� �����ϴ� func1 --------" << std::endl;

	// s1 �� �״�� ���޵� ���� �ƴ϶� s1 �� ���纻�� ���޵�
	auto func = std::bind(foo, s1, std::placeholders::_1);
	func(s2);

	std::cout << "After func::s1.data : " << s1.data << std::endl;

	std::cout << "\n���纻 ������ ���� func2 --------" << std::endl;
	
	// s1 �� ���纻 ������ �������� std::ref �� ������ �Ѱ��ָ� ��
	auto func2 = std::bind(foo, std::ref(s1), std::placeholders::_1);
	func2(s2);

	std::cout << "After func2::s1.data : " << s1.data << std::endl;

	/*
		- output
			�Ϲ� ������ ȣ��
			�Ϲ� ������ ȣ��
			Before::s1.data : 1
			
			���纻�� �����ϴ� func1 --------
			���� ������ ȣ��
			After func::s1.data : 1
			
			���纻 ������ ���� func2 --------
			After func2::s1.data : 5
	*/

	

	/*
		- std::bind
			- ������ �ǹ� : ����
			- std::bind : �� �״�� ���� �Լ��� Ư�� ���ڸ� ���� �Լ� ��ü�� �����ؼ� ������
			- bind ��Ų �ڸ����� ���ڰ� ������ �����ϳ� ���õ�

			- std::placeholders : bind �� ������ ���ο� �Լ� ��ü�� ����
				- MSVC ���� std::placeholders::_20 ���� ����
				- std::placeholders �� ������� ���ڰ� ��
					-> ���� negate �� ���

						auto negate = std::bind(subtract, std::placeholders::_2, std::placeholders::_1);

					-> �̷������� �ݴ�� �־��ָ� negate(x, y) ������ y - x �� ������ (������ x - y)

				- ���� placeholder �� �����ϴٸ� ������ �ڵ带 �߸�¥���� �ʾҴ��� �ݼ��� �ʿ��� ��찡 ��κ��ϵ�

			- std::bind ���� ���ǻ��� : ���۷����� ���ڷ� �޴� ���
				- ���� ���۷����� ���ڷ� �޴� �ڸ��� std::bind �� �̿��� ���۷����� �ƴ� ���ڸ� �����ϸ� ���ڰ� ����Ǿ� ���޵�
				- �̸� �������� std::ref() �� �̿��� ��������� ���۷����� �����ؾ� ��
				- const ���۷����� ��� std::cref()�� �̿��ϸ� ��

				- std::ref() : ���޹��� ���ڸ� ���� ������ ���۷����� ��ȯ��
	
	*/

}