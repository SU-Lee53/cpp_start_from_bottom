/*
	06.10 - ������ �ʱ�ȭ, �ʱ�ȭ�� ����Ʈ
*/

/*  �Լ�?  */
//	#include <iostream>
//	
//	class A
//	{
//	public:
//		A() { std::cout << "A �� ������ ȣ��" << std::endl; }
//	};
//	
//	class B
//	{
//	public:
//		B(A a) { std::cout << "B �� ������ ȣ��" << std::endl; }
//	};
//	
//	int main()
//	{
//		A a();	// �ƹ��͵� ��µ��� ����
//		B b(A());	// �ƹ��͵� ��µ��� ����
//	
//		/*
//			- ������ �ʱ�ȭ�� �ʿ伺
//				- �� 2���� �ڵ�� ������ �����ڰ� ȣ��Ǿ�� �Ұ� ������ ȣ����� ����
//				- ��к��� �����ڸ� ��ü ������ ȣ���� �ƴ� �Լ��� ���Ƿ� �����ϵǱ� ������
//					-> A a() : A Ŭ���� ��ü a �� ������ ���� �ƴ� A�� �����ϴ� a() ��� �Լ��� ������
//					-> B b(A()) : B Ŭ���� ��ü b �� ������ ���� �ƴ� ���ڰ� ���� �Լ��� �޴� B�� �����ϴ� �Լ� b() ��� �Լ��� ������
//	
//				- �� �̷����� �Ͼ�°�?
//					- () �����ڰ� 2���� ������ �ϱ� ����
//						1) �Լ��� ���� ����
//						2) ��ü�� ������ ȣ��
//	
//				- C++ 11 ���� ���Ե� ������ �ʱ�ȭ�� �̿��ؼ� �� ������ �ذ��� �� ����
//		*/
//	}

/*  ������ �ʱ�ȭ Uniform Initialization  */
//	#include <iostream>
//	
//	class A
//	{
//	public:
//		A() { std::cout << "A�� ������ ȣ��" << std::endl; }
//		A(int x) { std::cout << "A�� ������ ȣ��" << std::endl; }
//	};
//	
//	A func() 
//	{ 
//		return { 1 }; 
//	}
//	
//	int main()
//	{
//		A a{};	// A�� ������ ȣ�� -> ������ �ʱ�ȭ
//	
//		// ������ �ʱ�ȭ�� Narrow-conversion �� �Ұ�����
//		A b(3.5);	// ����
//		// A c{ 3.5 };	// C2398 : ��� '1': 'double'���� 'int'(��)�� ��ȯ�Ϸ��� ��� ��ȯ�� �ʿ��մϴ�.
//	
//		func();	// �Լ� ���Ͻ� ��ü�� Ÿ���� ������� �ʾƵ� ��
//	
//		/*
//			- ������ �ʱ�ȭ
//				- ��ü ������ () ��� {} �� �̿��Ͽ� ���
//				- Ư¡
//					- Narrow-conversion �� �Ұ����� ��ġ �ʴ� ĳ������ ������ ��Ƴ� �� ����
//						- Narrow-conversion : �����Ͱ� �սǵ� �� �ִ� �Ϲ��� Ÿ�� ��ȯ
//							- �ε� �Ҽ��� Ÿ�� -> ���� Ÿ��
//							- ���� Ÿ�� -> �ε� �Ҽ��� Ÿ��
//							- long double -> double / float
//							- double -> float
//							- �� ���� �͵��� https://en.cppreference.com/w/cpp/language/list_initialization �� Narrowing conversions �� ����
//	
//					- �Լ� ���Ͻ� ���� Ÿ���� �ٽ� ������� �ʾƵ� ��
//						-> �� �ڵ��� func() ���� A{1} �� �ƴ� {1} �� �ۼ��ص� ���������� �����Ǿ� ���ϵ�
//		
//		*/
//	}

/*  �ʱ�ȭ�� ����Ʈ Initializer list  */
//	#include <iostream>
//	#include <vector>
//	#include <map>
//	#include <string>
//	class A
//	{
//	public:
//		A(std::initializer_list<int> l)
//		{
//			for (auto it = l.begin(); it != l.end(); ++it)
//			{
//				std::cout << *it << std::endl;
//			}
//		}
//	};
//	
//	template <typename T>
//	void print_vec(const std::vector<T>& vec)
//	{
//		std::cout << "[";
//		for (const auto& e : vec)
//			std::cout << e << " ";
//		std::cout << "]" << std::endl;
//	}
//	
//	template<typename K, typename V>
//	void print_map(const std::map<K, V>& map)
//	{
//		for (const auto& kv : map)
//			std::cout << kv.first << " : " << kv.second << std::endl;
//	
//	}
//	
//	int main()
//	{
//		A a = { 1,2,3,4,5 };
//		// A b(1, 2, 3, 4, 5);	// () �� initializer list �� �������� ����
//		// A b({ 1,2,3,4,5 });	// ����
//	
//		/*  initializer list �� �̿��Ͽ� STL �����̳ʵ� �ʱ�ȭ  */
//		std::vector<int> v = { 1,2,3,4,5 };
//		print_vec(v);
//	
//		std::cout << "-----------------------" << std::endl;
//		std::map<std::string, int> m = {
//			{"abc", 1}, {"hi", 3}, {"hello", 5}, {"C++", 2}, {"java", 6}
//		};
//		print_map(m);
//	
//		/*
//			- ������� output:
//				1
//				2
//				3
//				4
//				5
//				[1 2 3 4 5 ]
//				-----------------------
//				C++ : 2
//				abc : 1
//				hello : 5
//				hi : 3
//				java : 6
//		*/
//	
//		/*  initializer list ��� �� ���ǻ���  */
//		std::vector<int> v1(10);
//		std::vector<int> v2{ 10 };
//	
//		std::cout << "v1 : " << v1.size() << " ";
//		print_vec(v1);
//		
//		std::cout << "v2 : " << v2.size() << " ";
//		print_vec(v2);
//	
//		/*
//			- output :
//				v1 : 10 [0 0 0 0 0 0 0 0 0 0 ]
//				v2 : 1 [10 ]
//	
//		
//		*/
//	
//		/*
//			- �ʱ�ȭ�� ����Ʈ Initializer list
//				- {} �� ����Ͽ� �����ڸ� ȣ���� �� ������ �߿� std::initializer_list �� ���ڷ� �޴� �����ڰ� ������ ���޵�
//					- {} �� �ϳ��� �迭�� ���� ������� �����ؼ� initializer_list �� ��
//					- () �� �����ڸ� ȣ���ϸ� initializer_list �� �������� ����
//	
//				- initializer list �� �̿��ϸ� �����̳ʵ��� ���� ������ �� ����
//					- �����̳��� �����ڵ� �߿� initializer list �� �޴°� �ֱ⶧���� ����
//					- vector �� ���ε�� �Ʒ��� ����(MSVC)
//	
//						_CONSTEXPR20 vector(initializer_list<_Ty> _Ilist, const _Alloc& _Al = _Alloc())
//							: _Mypair(_One_then_variadic_args_t{}, _Al) {
//							_Construct_n(_Convert_size<size_type>(_Ilist.size()), _Ilist.begin(), _Ilist.end());
//						}
//	
//				- initializer list ���� ������ ��
//					- initializer_list �� �޴� �����ڰ� ���� �� {} �� ��ü�� �����ϸ� �ش� �����ڰ� �ֿ켱���� �����
//					- ���� : ���� v1, v2
//						- v1 �� (10), v2 �� {10} ���� ������ ȣ��
//						- ���Ϳ��� �Ʒ��� ���� �����ڰ� ����(MSVC)
//	
//							_CONSTEXPR20 explicit vector(_CRT_GUARDOVERFLOW const size_type _Count, const _Alloc& _Al = _Alloc())
//								: _Mypair(_One_then_variadic_args_t{}, _Al) {
//								_Construct_n(_Count);
//							}
//	
//							-> size_type count �� ���ڷ� �ް� �� ũ���� ���͸� ������
//	
//						- v1 (10) �� v2 {10} �� ���� ���⿣ ���� �������� �ٸ�
//							- v1 (10) �� �ٷ� ���� vector(size_type _Count) ������ �����ڸ� ȣ��
//							- v2 {10} �� vector(std::initializer_list _Ilist) ������ �����ڸ� ȣ��
//								-> �� ����� ������ ���Ͱ� ������ �ٸ�
//							
//					- Narrow-conversion �� �Ұ��� ���� ȣ���Ҽ� ���� �����ڵ� �ֿ켱���� �����
//						- ���� ���, �Ʒ� 2���� �����ڰ� ������
//	
//							A(int n, double d) {}
//							A(std::initializer_list<int> lst) {}
//	
//						- �Ʒ� �ڵ�� ������ �߻���
//	
//							A(10, 1.5);
//							A{10, 1.5};	-> ���⼭ Narrow conversion �� �Ұ����ϹǷ� ������ ������ �߻�
//	
//						- �ٸ� �ƿ� ��ȯ�� �� ���°��� �ٸ� �����ڸ� ȣ����. ��, �� ������ ���
//	
//								A(std::initializer_list<std::string> lst) {}
//							
//							��� �����ڰ� �ִٸ�
//	
//								A{10, 1.5};
//	
//							�� string ���� ��ȯ�� �� �����Ƿ� A(int n, double d) �����ڰ� ȣ���
//		*/
//	
//	}

/*  initializer_list �� auto Ÿ�� �߷�  */
//	#include <iostream>
//	#include <typeinfo>
//	
//	using namespace std::literals;
//	
//	int main()
//	{
//		auto list = { 1,2,3 };
//		std::cout << typeid(list).name() << std::endl;	// class std::initializer_list<int>
//	
//		auto list2 = { "a", "b", "cc" };
//		std::cout << typeid(list2).name() << std::endl;	// class std::initializer_list<char const * __ptr64>
//	
//		auto list3 = { "a"s, "b"s, "cc"s };	// ���ͷ� �����ڸ� �̿��ؾ� const char* �� �ƴ� std::string �� ��
//		std::cout << typeid(list3).name() << std::endl;	// class std::initializer_list<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >
//	
//		auto a = { 1 };
//		auto b{ 1 };
//		auto c = { 1,2 };
//		// auto d{ 1,2 };	// E2663 : �ڸ� ǥ���� ������ ������ '='�� ���� ����� ������ �߰�ȣ �ʱ�ȭ������ �߰�ȣ �ȿ� ��Ȯ�� �ϳ��� ��Ұ� �־�� �մϴ�.
//		
//		std::cout << "auto a = { 1 } -> " << typeid(a).name() << std::endl;	// auto a = { 1 } -> class std::initializer_list<int>
//		std::cout << "auto b{ 1 } -> " << typeid(b).name() << std::endl;	// auto b{ 1 } -> int
//		std::cout << "auto c = { 1, 2 } -> " << typeid(c).name() << std::endl;	// auto c = { 1, 2 } -> class std::initializer_list<int>
//	
//		/*
//			- initializer_list �� auto
//				- initializer_list �� auto �� Ÿ�� �߷п��� ��Ģ�� ����
//	
//					- {} �� �̿��Ͽ� ������ Ÿ������ auto �� �����ϸ� initializer_list<T> ��ü�� ������
//						
//						auto list = { 1,2,3 }; -> std::initializer_list<int>
//	
//					- ���ڿ��� �⺻������ initializer_list<const char*> �� �߷�
//	
//						auto list2 = { "a", "b", "cc" }; -> std::initializer_list<char const * __ptr64>
//	
//					- std::string ���� �߷еǰ� �Ϸ��� ���ͷ� �����ڸ� �̿��ؾ���
//	
//						auto list3 = { "a"s, "b"s, "cc"s }; -> std::initializer_list<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>>>
//	
//					- C++ 17 ���� �߰��� ��Ģ
//	
//						- auto x = { arg1, arg2 ... } ���� : arg1, arg2 ... ���� ���� Ÿ��(T)�̸� x -> std::initializer_list<T>
//							
//							auto a = { 1 }; -> std::initializer_list<int>
//							auto c = { 1,2 }; -> std::initializer_list<int>
//	
//						- auto x { arg1, arg2 ... } ���� : ���� ���ڰ� �� 1����� Ÿ������ �߷�, �������� ���� �߻�
//							
//							auto b{ 1 }; -> int
//							auto d{ 1,2 }; -> E2663 : �ڸ� ǥ���� ������ ������ '='�� ���� ����� ������ �߰�ȣ �ʱ�ȭ������ �߰�ȣ �ȿ� ��Ȯ�� �ϳ��� ��Ұ� �־�� �մϴ�.
//	
//	
//		*/
//			
//			
//	}
