
/*
	04.23 ���� ���� ���ø�, �Ķ���� ��, Fold ����
*/

// ���� ���� ���ø�, �Ķ���� ��

//	#include <iostream>
//	
//	template <typename T>
//	void print(T arg)
//	{
//		std::cout << arg << std::endl;
//	}
//	
//	template <typename T, typename... Types>
//	void print(T arg, Types... args)
//	{
//		std::cout << arg << ", ";
//		print(args...);
//	}
//	
//	int main()
//	{
//		print(1, 3.1, "abc");
//		print(1, 2, 3, 4, 5, 6, 7);
//	
//		/*
//			output:
//			1, 3.1, abc
//			1, 2, 3, 4, 5, 6, 7
//		*/
//	
//		/*
//			- ���� ���� ���ø�, �Ķ���� ��
//				- ���� print �Լ��� ���̽��� print()ó�� ������ Ÿ���̳� ������ ������� ��� ����ϴ� �Լ�
//					- C++������ ���� ���� ���ø��� �̿��Ͽ� �̷��� ����� ������ �� ����
//	
//				- �Ķ���� ��(parameter pack)
//					- cppreference�� ���� ����
//						- A template parameter pack is a template parameter that accepts zero or more template arguments (non-types, types, or templates)
//							-> ���ø� �Ķ���� ��: 0�� �̻��� ���ø� ���ڸ� �޴� ���ø� �Ű�����
//						- A function parameter pack is a function parameter that accepts zero or more function arguments.
//							-> �Լ� �Ķ���� ��: 0�� �̻��� �Լ� ���ڸ� �޴� �Լ� �Ű�����
//					- �Ķ���� ���� ����
//						- ���ø� �Ķ���� ��: Ÿ�� �տ� ... ���� ����
//							-> template<typename... Types>
//						- �Լ� �Ķ���� ��: Ÿ�� �ڿ� ... ���� ����
//							-> void print(Types... args) {}
//					- �Ķ���� ���� �߷е� ���ڸ� ������ ������ ���ڵ��� ��Ÿ��
//						- ���� print(1, 3.1, "abc"); �� ����...
//							- �Լ� ȣ��� �����Ϸ��� 2���� print() �Լ��� ���Ǹ� ���� ������� ������ ���ؾ���
//								-> void print(T arg) �� ���ڰ� �� 1���̹Ƿ� �ĺ����� ���ܵǰ�, 2��° void print(T arg, Types... args)�� ���õ�
//							- print()�� ù��° ���ڴ� 1�̹Ƿ� T�� int�� �߷еǰ� arg�� 1�� ��.
//							- args���� ������ 3.1�� "abc"�� ��
//								-> �̰��� ������ �ν��Ͻ�ȭ �Ǹ� �Ʒ�ó�� ��
//									
//									void print(int arg, double arg2, const char* arg3)
//									{
//										std::cout << arg << ", ";
//										print(arg2, arg3);
//									}
//							
//							- ������ arg�� ����� ���� �ٽ� ��������� print�� ȣ����
//								-> �̹��� �ν��Ͻ�ȭ �Ǹ� �Ʒ�ó�� ��
//	
//									void print(double arg, const char* arg2)
//									{
//										std::cout << arg << ", ";
//										print(arg2);
//									}
//	
//							- �� �ѹ� ��� ȣ��� print�� ���ڰ� 1�� ����
//								-> �̹����� ���ڰ� 1���� void print(T arg) �� ȣ���
//								-> C++ ��Ģ�� �Ķ���� ���� ���� �Լ��� �켱������ �� ���� ����
//							- �׷��Ƿ� �������� std::endl�� ��µ� �� �ְԵ�
//	
//					- �Ķ���� �� ������ ������
//						- ���� �� print �Լ��� ��ġ�� �ٲ㼭 ���� ������ ������ �߻���
//							-> C++ �����Ϸ��� �Լ� �����Ͻÿ�, �ڽ��� �տ� ���ǵǾ� �ִ� �Լ���ۿ� ���� ���ϱ� ������
//							-> ������ �ڹٲ�� void print(T arg, Types... args) �� void print(T arg)�� ���縦 �𸣰� ������ �������� �ڵ带 �ν��Ͻ�ȭ �� �� ����������
//								-> ���ø� �Լ� �ۼ��ÿ��� �ݵ�� ������ �����ؾ���
//		*/
//	}

// ���� ���� ���ø��� ���� - ������ ������ ���ڿ� ��ġ��

//	/*
//		- ������ ������ ���ڿ� ��ġ��
//			- std::string�� ���ڿ��� ��ġ�� ���ؼ��� operator+�� �̿���
//			- �̶� ������ ������ ���ڿ��� ��ġ���� �غ���
//				- concat = s1 + s2 + s3;
//					-> s2�� ���Ҷ� �޸� �Ҵ��� �߻��ϰ� �ű⿡ s3�� ���Ҷ� �� �޸� �Ҵ��� �߻�
//					-> ���� �ѹ��� �ʿ��� ��ŭ �޸𸮸� �Ҵ��ع����°� �� ����
//						-> �̸� ���� �������� ���ڿ��� ��ġ�� StrCat �Լ��� ����� ������ ��
//	*/
//	
//	#include <iostream>
//	#include <string>
//	
//	size_t GetStringSize(const char* s) { return strlen(s); }
//	size_t GetStringSize(const std::string& s) { return s.size(); }
//	
//	template<typename String, typename... Strings>
//	size_t GetStringSize(const String& s, Strings... strs)
//	{
//		return GetStringSize(s) + GetStringSize(strs...);
//	}
//	
//	void AppendToString(std::string* concat_str) { return; }
//	
//	template <typename String, typename... Strings>
//	void AppendToString(std::string* concat_str, const String& s, Strings... strs)
//	{
//		concat_str->append(s);
//		AppendToString(concat_str, strs...);	// strs�� ���� ���ڿ��� ������ void AppendToString(std::string* concat_str)�� ȣ��Ǿ� ����
//	}
//	
//	template <typename String>
//	std::string StrCat(const String& s)
//	{
//		return std::string(s);
//	}
//	
//	template <typename String, typename... Strings>
//	std::string StrCat(const String& s, Strings... strs)
//	{
//		// ���� ������ ���ڿ��� �� ���̸� ���Ѵ�
//		size_t total_size = GetStringSize(s, strs...);
//	
//		// reserve�� ���� �̸� ������ �Ҵ��� ���´�
//		std::string concat_str;
//		concat_str.reserve(total_size);
//	
//		concat_str = s;
//	
//		AppendToString(&concat_str, strs...);
//	
//		return concat_str;
//	}
//	
//	int main()
//	{
//		// std::string �� const char*�� ȥ���ؼ� ��� ����
//		std::cout << StrCat(std::string("this"), " ", "is", " ", std::string("a"), " ", std::string("sentence"));
//	
//		/*
//			output:
//			this is a sentence
//		*/
//	
//		// �� ������ �о�� ����� �����Ƿ� ���� ����
//	}

// sizeof...

//	#include <iostream>
//	
//	// ��� ȣ�� ���Ḧ ���� ���̽� ���̽�
//	int sum_all() { return 0; }
//	
//	template <typename... Ints>
//	int sum_all(int num, Ints... nums)
//	{
//		return num + sum_all(nums...);
//	}
//	
//	template <typename... Ints>
//	double average(Ints... nums)
//	{
//		return static_cast<double>(sum_all(nums...)) / sizeof...(nums);
//	}
//	
//	int main()
//	{
//		// (1 + 4 + 2 + 3 + 10) / 5
//		std::cout << average(1, 4, 2, 3, 10) << std::endl;
//		
//		/*
//			output:
//			4
//		*/
//	
//		/*
//			- sizeof...
//				- �Ϲ� sizeof: ������ ũ�⸦ ����(����Ʈ)
//				- sizeof...() �� �Ķ���� �ѿ� ���� ��ü ������ ������ ������
//		*/
//	}

// Fold Expression

#include <iostream>

template <typename... Ints>
int sum_all(Ints... nums)
{
	// ���� ���� Fold(Unary left fold)
	return (... + nums);
}

template <typename Int, typename... Ints>
Int diff_from(Int start, Ints... nums)
{
	// ���� ���� Fold(Binary left fold)
	return (start - ... - nums);
}

class A
{
public:
	void do_something(int x) const
	{
		std::cout << "Do something with " << x << std::endl;
	}
};

template <typename T, typename... Ints>
void do_many_things(const T& t, Ints... nums)
{
	// ������ ���ڵ鿡 ���� do_something �Լ����� ȣ���Ѵ�
	(t.do_something(nums), ...);
}

int main()
{
	// 1 + 4 + 2 + 3 + 10
	std::cout << sum_all(1, 4, 2, 3, 10) << std::endl;

	// 100 - 1 - 4 - 2 - 3 - 10
	std::cout << diff_from(100, 1, 4, 2, 3, 10) << std::endl;

	A a;
	do_many_things(a, 1, 2, 3, 4);

	/*
		output:
		20
		80
		Do something with 1
		Do something with 2
		Do something with 3
		Do something with 4

		�� �ڵ� ����� ������Ʈ �ɼǿ��� C++ ��� ǥ���� C++ 17 �̻����� �÷�����
	*/

	/*
		- Fold Expression
			- ������ ���� ���� ���ø��� �ſ� �������� �ݵ�� ��� ȣ�� ���Ḧ ���� �Լ��� ���� ������ �Ѵٴ� ������ ����
				-> C++ 17 ���� ���� ���Ե� Fold Expression�� ����ϸ� �׷��ʿ� ���� �ξ� �����ϰ� ǥ���� �� ����

			- Fold Expression
				- Fold ����� �Ʒ��� 4������ ����
					1) ���� ���� Fold (Unary right fold): (E op ...)
						-> (E1 op (... op (EN-1 op EN)))
					2) ���� ���� Fold (Unary left fold): (... op E)
						-> (((E1 op E2) op ...) op EN)
					3) ���� ���� Fold (Binary right fold): (E op ... op I)
						-> (E1 op (... op (EN-1 op (EN op I))))
					4) ���� ���� Fold (Binary left fold): (I op ... op E)
						-> ((((I op E1) op E2) op ...) op EN
					-> op �ڸ����� ��κ��� ���� �����ڵ��� ���Ե�(+ - * / % ^ & | = < > << >> += -= *= /= %= ^= &= |= <<= >>= == != <= >= && || , .* ->*)
					-> I �� �ʱⰪ�� �ǹ��ϸ� �Ķ���� ���� �ƴ�
				- �� �ڵ带 ���� �����ϸ� ����
					- int sum_all(Ints... nums)�� return (... + nums) �κ�
						-> (... + nums) ���� ���°� ���� ���� fold�� �Ʒ��� ���� �����Ϸ����� �ؼ���
							return ((((1 + 4) + 2) + 3) + 10);
					- Int diff_from(Int start, Ints... nums)�� return (start - ... - nums) �κ�
						-> (start - ... - nums) ���� ���°� ���� ���� fold�� �Ʒ��� ���� �����Ϸ����� �ؼ���
							return (((((100 - 1) - 4) - 2) - 3) - 10);
					- void do_many_things(const T& t, Ints... nums)�� (t.do_something(nums), ...) �κ�
						-> �Ķ���� �� ���� ��� ���ڵ鿡 ���ؼ� ���� t.do_something(x)�� ������ �Ͱ� ����. ��, �Ʒ��� ���� �����ϵ�
							t.do_something(1);
							t.do_something(3);
							t.do_something(2);
							t.do_something(4);
						-> , �� ���� �������� �ϳ����� �� �� ����
				- Fold ���� ������ �ݵ�� ()�� �����־�� ��
					-> return (... + nums); �� �ƴ϶� return ... + nums; �� �ۼ��ϸ� ������ �߻���
	
	*/

}


