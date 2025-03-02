/*
	06.12 - decltype, �� ī�װ�, decleval
*/

/*  decltype  */
//	#include <iostream>
//	
//	struct A
//	{
//		double d;
//	};
//	
//	int main()
//	{
//		int a = 3;
//		decltype(a) b = 2;	//	int
//	
//		int& r_a = a;
//		decltype(r_a) r_b = b;	// int&
//	
//		int&& x = 3;
//		decltype(x) y = 2;	// int&&
//	
//		A* aa;
//		decltype(aa->d) dd = 0.1;	// double
//	
//		/*
//			- decltype
//				- C++ 11 �� �߰��� Ű����� Ÿ���� �˰��� �ϴ� ���� Ÿ������ ġȯ
//				- decltype() �� ���޵� ���� "��ȣ�� �ѷ������� ���� �ĺ��� ǥ����" �϶� �ش� ���� Ÿ���� �� �� ����
//	
//				- �ĺ��� ǥ���� id-expression
//					- ��� ������ ���� �ʰ� �ܼ��� ��ü �ϳ��� ����Ű�� ��
//					- ���� �̸�, �Լ� �̸�, enum �̸�, Ŭ���� ��� ����(a.b Ȥ�� a->b)
//					- �ڼ��Ѱ� https://eel.is/c++draft/expr.prim.id#2.2 �� ����
//	
//				- decltype() �� �ĺ��� ǥ������ �ƴ� ���� �����ϸ� �Ʒ�ó�� �۵�
//					- ���� �� ������ xvalue ��� T&& �� ġȯ
//					- ���� �� ������ lvalue ��� T& �� ġȯ
//					- ���� �� ������ prvalue ��� T �� ġȯ
//						-> �� ������ �Ʒ����� ��� �ٷ�
//		*/
//	}

/*  �� ���� value category  */
/*
	- �� ���� value category
		- ��� C++ �Ŀ��� "Ÿ��" �� "�� ī�װ�(== �� ����)" �� �������
		- ������ ������, ������ ������ Ȯ������ C++ ���� �� 5������ �� ������ ������
		- �� ������ �������� ũ�� 2������ ������
			
			1) ��ü�� �� �� �ִ°�?
				- �ش� ���� � �ٸ� �İ� ���������� �ƴ��� ������ �� �ִ°�?
				- ������ ��� �ּڰ��� ���Ͽ� �� �� �ְ�, �Լ��� �̸��� ���� �� �� ����

			2) �̵� ��ų �� �ִ°�?
				- �ش� ���� �ٸ� ������ �����ϰ� �̵��� �� �ִ°�?
				- �̵� ������, �̵� ���� ������ ���� ����� �� �ִ��� ���η� ���� ������

		- �� ������ �������� �Ʒ�ó�� 5������ ������ ����

					�̵� ����		�̵� �Ұ���
			��üO	xvalue			lvalue		�� ��ü�� �� �� �ִ� ��� ���� glvalue
			��üX	prvalue			���� ����
					   ��
					�̵� ������ ��� ���� rvalue

		- �� �Ʒ����� lvalue, prvalue, xvalue �� ���ؼ� �ٷ�
			-> �ſ� �����Ը� ¤�� �Ѿ�Ƿ� �ڼ��Ѱ� https://en.cppreference.com/w/cpp/language/value_category �� ����
*/

/*  lvalue  */
//	#include <iostream>
//	
//	class A
//	{
//	public:
//		int f() {}	// static �� �ƴ� ����Լ�
//		static int g() {}	// static ��� �Լ�
//	};
//	
//	void f(int&& a)
//	{
//		a;	// lvalue
//		std::cout << &a << std::endl;
//	}
//	
//	int main()
//	{
//		int i;	// lvalue
//	
//		A a;
//		a.g;	// lvalue
//		//a.f;	// lvalue �ƴ� (prvalue)
//	
//		f(3);	// 000000D471DDFC64 (�Ź� �ٸ�)
//	
//		auto p1 = &std::cin;	// lvalue �̹Ƿ� & �� �ּҰ��� ���� �� ����
//		std::cout << p1 << std::endl;	// 00007FFC2FBC2E10
//	
//		i = 0;
//		auto p2 = &++i;	// ���� ���� �������� ���ϰ��� lvalue �̹Ƿ� �ּҰ��� ���� �� ����
//		std::cout << p2 << std::endl; // 0000000194B7F514 (�Ź� �ٸ�)
//	
//		/*
//			- lvalue
//				- xvalue �� �ƴ� glvalue
//				- �̸��� ���� ��κ��� ��ü���� lvalue ��. ��ü�� �ּҰ��� ���Ҽ� �ֱ� ����(&)
//	
//				- ��ǥ���� lvalue �ĵ��� �Ʒ��� ����
//					- ����, �Լ��� �̸�, � Ÿ���� ������ ���(ex: std::cin) ���
//					- ������ ���۷����� �����ϴ� �Լ��� ȣ��� (std::cout << 1;, ������ �ݺ��� it �� ++it ���)
//					- a = b, a += b, a*= b ���� ���� ���� ������ �ĵ�
//					- ++a, --a ���� ���� ���� ������ �ĵ�
//					- a.m, p->m ���� ����� �����ϴ� ��. �̶� m �� enum ���̰ų� static �� �ƴ� ��� �Լ����� ����
//					- a[n] ���� �迭 ������
//					- ���ڿ� ���ͷ� "hi"
//	
//				- �򰥸��� ���� ���
//					void f(int&& a)
//					{
//						a;	<- �̷� �Լ��� ��� a�� lvalue��
//					}
//	
//					- a�� ������ ���۷��� �̹Ƿ� lvalue�� �ƴ϶�� �����ϴ� ��찡 ����
//						-> a �� Ÿ���� int&& ������ ���۷����� ������, �� �����δ� lvalue ��
//						-> Ÿ�� �� �� ������ ������ �ٸ� �������� ��Ȯ�� �˰� �־�� ��
//	
//		*/
//	
//	}

/*  prvalue  */
//	#include <iostream>
//	
//	int f() { return 10; }
//	
//	int main()
//	{
//		f();	// �ּҰ��� ���� �� �����Ƿ� prvalue
//	
//		const int& r = 42;
//		int&& rr = 42;
//		// int& rrr = 42;	// �Ұ�
//	
//		/*
//			- prvalue
//				- pure rvalue �� ���Ӹ�
//				- ��ü�� �� �� ���� �� -> �ּҰ��� ���� �� ���� ��
//				- prvalue �� ������ �� �� ����
//				- ������ ���۷����� ��� ������ ���۷����� �ʱ�ȭ�ϴµ� ����� �� ����
//	
//				- ��ǥ���� prvalue �ĵ��� �Ʒ��� ����
//					- ���ڿ� ���ͷ��� ������ ��� ���ͷ�(42, true, nullptr ��)
//					- ���۷����� �ƴ� ���� �����ϴ� �Լ��� ȣ��� (str.substr(1, 2), str1 + str2 ��)
//					- ���� ���� �����ڽ� a++, a--
//					- ����Ʈ ���, �� ������ �ĵ� (a + b, a && b, a < b ��)
//					- �ּҰ� ������ �� &a
//					- a.m, p->m �� ���� ����� ������ ��. �̶� m �� enum ���̰ų� static �� �ƴ� ��� �Լ�������
//					- this
//					- enum ��
//					- ���ٽ� []() { return 0;};
//		*/
//	}

/*  xvalue  */
//	#include <iostream>
//	#include <utility>
//	
//	int main()
//	{
//		int x = 3;
//		auto xv = std::move(x);
//	
//		/*
//			- xvalue
//				- ��ü�� �����鼭 �̵� ������ ��
//				- eXpiring value �� ���Ӹ�
//	
//				- ���� : std::move()
//					- std::move() �� ������ �Ʒ��� ���� ����
//	
//						_EXPORT_STD template <class _Ty>
//						_NODISCARD _MSVC_INTRINSIC constexpr remove_reference_t<_Ty>&& move(_Ty&& _Arg) noexcept {
//						    return static_cast<remove_reference_t<_Ty>&&>(_Arg);
//						}
//	
//					- std::move �� ���ϰ��� �ݵ�� ������ ���۷���
//						-> std::move �� ȣ���� ���� lvalue ó�� ������ ���۷����� �ʱ�ȭ �� �� ����
//						-> ���� prvalue ó�� ������ ���۷����� ���̰ų� �̵� �����ڿ� ������ ���� ����
//	
//	
//				- cppreference �� ���� https://en.cppreference.com/w/cpp/language/value_category
//					an xvalue (an ��eXpiring�� value) is a glvalue that denotes an object whose resources can be reused;
//					xvalue �� �ڿ��� ����� �� �ִ� ��ä�� ��Ÿ���� glvalue
//	
//		*/
//	
//	}

/*  decltype �� ���  */
//	#include <iostream>
//	#include <typeinfo>
//	
//	template <typename T, typename U>
//	void add1(T t, U u, decltype(t + u)* result)
//	{
//		*result = t + u;
//	}
//	
//	template <typename T, typename U>
//	//	decltype(t + u) add2(T t, U u) -> decltype ���� t, u �� ���ǰ� ���߿� �����Ƿ� �Ұ���
//	auto add2(T t, U u) -> decltype(t + u)	// C++ 14 ���� �߰��� ����
//	{
//		return t + u;
//	}
//	
//	template <typename T, typename U>
//	decltype(auto) add3(T t, U u)			// C++ 14 ���� �߰��� �������� �� add2�� �̷��� �ᵵ ��
//	{
//		return t + u;
//	}
//	
//	int main()
//	{
//		int a = 4;
//		auto b = a;			// auto -> int
//		decltype(a) c = a;	// decltype(a) -> int
//	
//	
//		const int i = 4;
//		auto j = i;			// auto -> int
//		decltype(i) k = i;	// decltype(i) -> const int
//	
//		int arr[10];
//		auto arr2 = arr;	// auto -> int * __ptr64
//		decltype(arr) arr3;	// decltype(arr) -> int[10]
//	
//		int n = 10;
//		double d = 10.0;
//		decltype(n + d) res = 0;	// int + double �� Ÿ���� double
//		decltype(n + d)* res_p = &res;
//	
//		add1(n, d, res_p);
//		std::cout << typeid(res).name() << " : " << res << std::endl;	// double : 20
//		std::cout << typeid(add2(n, d)).name() << " : " << add2(n, d) << std::endl;	// double : 20
//		std::cout << typeid(add3(n, d)).name() << " : " << add3(n, d) << std::endl;	// double : 20
//	
//	
//		/*
//			- decltype �� ���
//				- auto �� �ϸ� �ȵ�?
//					- �ȵ�. auto �� ��Ȯ�� Ÿ���� ǥ������ ����. �������
//						
//							const int i = 0;
//							auto j = i;
//	
//						-> �� ��� auto �� const int �� �ƴ� int �� ��ȯ��
//					
//							int arr[10];
//							auto arr2 = arr;
//	
//						-> �� ���� int [10] �� �ƴ� int* �� ��ȯ��
//						-> �� �ۿ� auto �� ��Ȯ���� ���� ���� https://en.cppreference.com/w/cpp/language/template_argument_deduction#Other_contexts �� auto type deduction �� ���� 
//	
//				- decltype �� "Ÿ�� �״��"�� ��Ȯ�ϰ� ���� ������
//				- ���ø� �Լ����� ���ø� ���ڿ� ���ؼ��� ��� ������
//	
//						template <typename T, typename U>
//						void add1(T t, U u, decltype(t + u)* result)
//	
//				- �Լ� ���ǽ� ���� Ÿ���� decltype �� �����ϰ� �ʹٸ� C++ 14 �� ���� ���� �Լ� ���ǹ��� ����ؾ���
//	
//						template <typename T, typename U>
//						decltype(t + u) add2(T t, U u) -> X ������ ����
//	
//						template <typename T, typename U>
//						auto add2(T t, U u) -> decltype(t + u)	-> O ��� ����
//		
//		*/
//	
//	}

/*  std::declval  */
//	#include <iostream>
//	#include <utility>
//	#include <typeinfo>
//	
//	template <typename T>
//	decltype(T().f()) call_f_and_return(T& t)
//	{
//		return t.f();
//	}
//	
//	template <typename T>
//	decltype(std::declval<T>().f()) declval_f_and_return(T& t)
//	{
//		return t.f();
//	}
//	
//	// C++ 14 ���� �߰��� auto ����
//	template <typename T>
//	auto auto_f_and_return(T& t)
//	{
//		return t.f();
//	}
//	
//	struct A
//	{
//		int f() { return 0; }
//	};
//	
//	struct B
//	{
//		B(int x) {}
//		int f() { return 0; }
//	};
//	
//	int main()
//	{
//		decltype(A().f()) ret;	// int
//		// decltype(B().f()) ret2;	// ������ �Ұ�
//		decltype(B(1).f()) ret2;	// ������ ��
//	
//		A a;
//		B b(1);
//	
//		call_f_and_return(a);
//		// call_f_and_return(b);	// ������ �Ұ�
//		declval_f_and_return(b);	// ����
//	
//		auto_f_and_return(a);
//		auto_f_and_return(b);
//	
//		// declval �Լ��� ��Ÿ�ӿ��� ����� �� ����
//		// B b2 = std::declval<B>);	// E0415 : "<unknown-type>" ���� "B"(��)�� ��ȯ�ϱ� ���� ������ �����ڰ� �����ϴ�.
//	
//		/*
//			- std::declval<T>
//				- �� �ڵ忡��
//					- decltype(A().f()) ret;	
//						- decltype �� �����Ͻÿ� Ÿ������ ��ȯ�ǰ� ��Ÿ�ӿ��� ������� ����
//						- �׷��� ������ Ʋ�� ���� ������ �� ����
//	
//					- decltype(B().f()) ret2; �� �������� �ȵ�
//						- B() �����ڰ� �����Ƿ� �Ұ�����
//						- ���� B() �����ڰ� �ʿ� ���µ� �̰� ���� ����°��� ��ȿ����
//							- ���� ��ü�� ���������� �ʰ� Ÿ�� ������ �ϱ� ����
//	
//					- decltype(B(1).f()) ret2;
//						- �����ϱ� ��
//						- �׷��� ���ø� �ڵ� � ���� �� ������ ����Ŵ
//							-> �Ʒ����� �Լ��� ���� ��
//								template <typename T>
//								decltype(T().f()) call_f_and_return(T& t)
//								-> B() �����ڰ� �����Ƿ� ������ �������� �Ұ�������
//								-> �̸� �ذ��ϴ� ���� std::declval
//	
//				- std::declval : <utility> �� ���ǵ� �Լ��� �������� ������ ȣ�� ���� ��ü�� ����� ������ �� �ֵ��� ��
//	
//						template <typename T>
//						decltype(std::declval<T>().f()) declval_f_and_return(T& t)
//	
//					-> ������ �ڵ带 ��ó�� std::declval �� �̿��ϸ� B() �����ڰ� ���� B �� ���� ���� ����� �� ����
//	
//				- std::declval �� Ÿ�� ���꿡���� ����ϰ� ���� ��Ÿ�ӿ��� ����� �� ����
//	
//						_EXPORT_STD template <class _Ty>
//						add_rvalue_reference_t<_Ty> declval() noexcept {
//							static_assert(_Always_false<_Ty>, "Calling declval is ill-formed, see N4950 [declval]/2.");
//						}
//					
//					- ���� declval �Լ��� �������� Ÿ�Կ����� �ƴ� ��Ÿ�ӿ� ����� static_assert �� ���α׷��� �������
//		
//	
//				- C++ 14 ���� ����Ÿ������ auto �� �����Ͽ� �����Ϸ��� ����Ÿ���� �����ϴ� ����� ����
//					- ��ó�� declval �� �̿��� ���� Ÿ�� ���� ���� �ϵ��� ����� ���� �پ��
//					- �׷��� declval �� <type_traits> �� �Բ� TMP �� ���� ����
//		
//		
//		*/
//	}