/*
	05.22 12 - 1 ������ ���۷����� �̵� ������
*/

// ���� ������ C++ 11 ���� �߰��� �������� ���� ���������� �۵����� ����

/*  ���� ���� Copy Elision  */
//	#include <iostream>
//	
//	class A
//	{
//	public:
//		A(int data) : _data(data) { std::cout << "�Ϲ� ������ ȣ��" << std::endl; }
//	
//		A(const A& a) : _data(a._data) { std::cout << "���� ������ ȣ��" << std::endl; }
//	
//	private:
//		int _data;
//	};
//	
//	int main()
//	{
//		A a(1);	// �Ϲ� ������ ȣ��
//		A b(a);	// ���� ������ ȣ��
//	
//		A c(A(2));	// �Ϲ� ������ ȣ��
//	
//		/*
//			- ���� ���� Copy elision
//				- �� �ڵ��� ���
//					- A a(1) : �Ϲ� �����ڰ� ���������� ȣ��Ǿ� ������
//					- A b(a) : ���� �����ڰ� ���������� ȣ��Ǿ� ������
//					- A c(A(2)) �� ����?
//						- ���� : A(2)�� �Ϲ� �����ڷ� ȣ��Ǿ� �����ǰ� ������ ��ü�� ���� �����ڰ� ȣ��Ǿ� c�� ����
//						- ��� : �Ϲ� ������ �ѹ����� ȣ��
//							-> �̰��� ���� ������ �Ͼ�� ���
//	
//				- ���� ����
//					- �� �ڵ��� c�� ����
//						- ���� A(2)�� �ӽð�ü�� ����� ���� ������ �ʿ䰡 ����
//							-> ������ A(2)�� c�� ���鲨��� c �� A(2)�� ������� ��ü�� �ٷ� �ع����°��̶� ���� ����
//	
//					- �����Ϸ��� �̷� ��츦 ���� ���� ������ ���� �ʰ� �˾Ƽ� ������� A(2) ��ü�� c�� ����� ����
//						-> �̷��� ���縦 �����ع����� ���� "���� ����"(Copy elision) ��
//					
//					- �����Ϸ��� ���� ������ �ϴ� ���
//						-> (�Լ��� ���ڰ� �ƴ�) �Լ� ���ο��� ������ ��ü�� �״�� ������ ��
//						-> �� �ܿ��� ���� ��찡 ����. �ٸ� "�ݵ�� ���� ������ �ض�" �� �ƴ� "�Ҽ��� �ִ�" ����
//							-> https://en.cppreference.com/w/cpp/language/copy_elision �� Non-mandatory copy/move(since C++11) elision �� ����
//	
//					- C++ 17 ���ʹ� �Ϻ� ��� �ݵ�� ���� ������ ���� https://en.cppreference.com/w/cpp/language/copy_elision 
//						-> ��ũ�� ���۷����� Prvalue semantics ("guaranteed copy elision") �� ����
//		*/
//	
//	}

/*  MyString �� ���� ����  */
//
//	// ������ ���� MyString�� �Ϻκи� �籸���Ͽ� ���� ������ �Ͼ�� ��츦 �˾ƺ���
//	#include <iostream>
//	#include <cstring>
//	
//	class MyString
//	{
//	public:
//		MyString();
//	
//		// ���ڿ��κ��� ����
//		MyString(const char* str);
//	
//		// ���� ������
//		MyString(const MyString& str);
//	
//		void reserve(int size);
//		int length() const { return string_length; };
//		void print();
//		void println();
//		
//		MyString operator+(const MyString& s);
//	
//		~MyString() { delete[] string_content; }
//	
//	private:
//		char* string_content;
//		int string_length;
//		int memory_capacity;
//	};
//	
//	MyString::MyString()
//	{
//		std::cout << "������ ȣ��" << std::endl;
//		string_length = 0;
//		memory_capacity = 0;
//		string_content = nullptr;
//	}
//	
//	MyString::MyString(const char* str)
//	{
//		std::cout << "������ ȣ��" << std::endl;
//		string_length = strlen(str);
//		memory_capacity = string_length;
//		string_content = new char[string_length];
//	
//		for (int i = 0; i < string_length; i++) string_content[i] = str[i];
//	}
//	
//	MyString::MyString(const MyString& str)
//	{
//		std::cout << "���� ������ ȣ��" << std::endl;
//		string_length = str.string_length;
//		memory_capacity = str.memory_capacity;
//		string_content = new char[string_length];
//	
//		for (int i = 0; i < string_length; i++) string_content[i] = str.string_content[i];
//	}
//	
//	void MyString::reserve(int size)
//	{
//		if (size > memory_capacity)
//		{
//			char* prev_string_content = string_content;
//			
//			string_content = new char[size];
//			memory_capacity = size;
//	
//			for (int i = 0; i < string_length; i++)
//				string_content[i] = prev_string_content[i];
//			
//			if (prev_string_content != nullptr) delete[] prev_string_content;
//		}
//	}
//	
//	MyString MyString::operator+(const MyString& s)
//	{
//		MyString str;
//		str.reserve(string_length + s.string_length);
//		for (int i = 0; i < string_length; i++)
//		{
//			str.string_content[i] = string_content[i];
//		}
//		for (int i = 0; i < s.string_length; i++)
//		{
//			str.string_content[string_length + i] = s.string_content[i];
//		}
//		str.string_length = string_length + s.string_length;
//		return str;
//	}
//	
//	void MyString::print()
//	{
//		for (int i = 0; i != string_length; i++) std::cout << string_content[i];
//	}
//	
//	void MyString::println()
//	{
//		for (int i = 0; i != string_length; i++) std::cout << string_content[i];
//	
//		std::cout << std::endl;
//	}
//	
//	int main()
//	{
//		MyString str1("abc");
//		MyString str2("def");
//		std::cout << "----------------" << std::endl;
//		MyString str3 = str1 + str2;
//		str3.println();
//	
//		/*
//			- output:
//				������ ȣ��
//				������ ȣ��
//				----------------
//				������ ȣ��
//				abcdef
//			
//			-> ����� �ڵ� ������ ���� �����ڱ��� ȣ������� ���⼭�� ������(MSVC C++14)
//			-> clang ���� �غ��� ���� ������(C++11)
//		*/
//	
//		/*
//			- MyString �� �������
//				- �ϴ� ����� �ڵ� ����ó�� ���� ������ �Ͼ�� �ʾҴٰ� �����ϰ� ����
//	
//				- �� �ڵ忡��
//					- MyString str3 = str1 + str2; �� �����Ҷ� operator+ �� ������ ���ڿ��� �����ؼ� ������
//	
//						str1 + str2 �� ������ �ӽ� ��ü --------> "abcdef" -> �޸� �󿡼� ����
//						                                             ��
//						                                           ����!
//																	 ��
//						str3 �� ���� ������ --------------------> �� ���� �Ҵ� ----> "abcdef"
//	
//					- ���� �����ڰ� str1 + str2 �� ����� ���� �޾� str3�� ����
//					- ���� ���� ���簡 2�� �Ͼ
//						-> ���ϵ� ���ڿ� ��ü�� str3�� ���� �����ڷ� ����
//						-> ���� �����ڿ��� ����� ���ڿ��� ����
//	
//					- str1 + str2 �� ũ�Ⱑ ũ�� Ŭ���� �ſ� ��ȿ����
//					- �׳� str1 + str2 �� ������� �ٷ� str3 �� �ǵ��� �ϴ� ���� ȿ������ -> ���� ������ ����
//		
//		*/
//	
//	}

/*  ������(lvalue) �� ������(rvalue)  */
//	#include <iostream>
//	
//	int& func1(int& a) { return a; }
//	int func2(int b) { return b; }
//	
//	int main()
//	{
//		int a = 3;
//		func1(a) = 4;
//		std::cout << &func1(a) << std::endl;
//		std::cout << a << std::endl;	// 4
//	
//		int b = 2;
//		a = func2(b);
//		//	func2(b) = 5;	// C2106 '=': ���� �ǿ����ڴ� l-value�̾�� �մϴ�
//		//	std::cout << &func2(b) << std::endl;	// C2102 '&'�� l-value�� �־�� �մϴ�
//	
//		/*
//			- �������� ������ https://en.cppreference.com/w/cpp/language/value_category
//				- ��� C++�� ǥ������ �ΰ��� ī�װ��� ������ �� ���� 
//				- ���� ���Ǵ� �� ���۷������� ������ �ſ� ���������� �����ϰ� �Ʒ�ó�� �����ϸ� ��
//					- ������(lvalue) : �ּҰ��� ���� �� �ִ� ��
//					- ������(rvalue) : �ּҰ��� ���� �� ���� ��
//	
//				- �������� ��� ��� ǥ������ ���� ������ ��� �� �� ����(���ʸ� �Ǽ� �������� �ƴ�)
//				- �������� ��쿡�� �ݵ�� ǥ������ �����ʿ��� �� �� ����
//	
//				- ����
//					- int a = 3;
//						-> 'a' : �޸� �� �����ϴ� �����̹Ƿ� & �����ڷ� �ּڰ��� ���� �� ���� -> ������
//						-> '3' : �� ǥ������ ���� ��� �����ϴ� ������ ���� ����ǰ� ���� �����. ��, '3'�� ��ü�� ���� -> ������
//	
//					- int& l_a = a;
//						-> a�� ������ �̹Ƿ� l_a �� �������� ���� ���۷���
//						-> & �ϳ��� �����ϴ� ���۷����� ������ ���۷���(lvalue reference) ��� �θ�
//	
//					- int& r_b = 3;
//						-> 3�� ������ �̹Ƿ� &���� ������ ���۷����� ���� �� ����
//				
//				- �� ���� �ڵ�
//					- func1() �� int& ������ ���۷����� ����
//					- func2() �� �Ϲ����� int �� ����
//	
//					- func1(a) = 4;
//						- func1(a) �� int& �� �����ϹǷ� a�� ���� 4�� �ٲ� -> ��������
//	
//					- a = func2(b);
//						- func2(b) �� ������ int ���� ���� ������ ������ ����� 
//						- �� func2(b) �� ������
//	
//					- func2(b) = 5;
//						- �� func1�� ���ʹ� �ݴ�� ������ �߻�
//						- func2(b) �� �������̹Ƿ� ������ ���ʿ� �� �� ����
//	
//					- std::cout << &func2(b) << std::endl;
//						- ���������� func2(b) �� �������̹Ƿ� & �����ڷ� �ּҰ��� ���� �� ����
//				
//				- const ���۷����� �������� ������ �� ����. const �� �����ϴ� ��ü�� ���� �����ϰ� ������ ���� ���� ����
//		*/
//	
//	}

/*  ������ ���۷����� �̵� ������  */
//	#include <iostream>
//	#include <utility>
//	
//	class foo
//	{
//	public:
//		// �⺻ ������
//		foo(int n) : _data(n) { std::cout << "�Ϲ� ������" << std::endl; }
//	
//		// ���� ������
//		foo(const foo& f) : _data(f._data) { std::cout << "���� ������" << std::endl; }
//	
//		// �̵� ������
//		foo(foo&& f) noexcept;
//	
//		foo operator+(const foo& f) { return _data + f._data; }
//	
//		friend std::ostream& operator<<(std::ostream&, const foo&);
//	
//	private:
//		int _data;
//	
//	};
//	
//	foo::foo(foo&& f) noexcept
//	{
//		std::cout << "�̵� ������" << std::endl;
//		_data = f._data;
//	}
//	
//	std::ostream& operator<<(std::ostream& o, const foo& f)
//	{
//		o << f._data;
//		return o;
//	}
//	
//	int main()
//	{
//		foo a(1);
//		foo b(2);
//	
//		//	foo& rvalue_ref = a + b;	// E0461 ��const ������ ���� �ʱ� ���� lvalue���� �մϴ�
//		//	foo&& rvalue_ref = a;	// E1768 rvalue ������ lvalue�� ���ε��� �� �����ϴ�
//		foo&& rvalue_ref = a + b;	// ������ ���۷���
//		std::cout << &rvalue_ref << std::endl;	// rvalue_ref �� ��������
//		std::cout << rvalue_ref << std::endl;
//	
//		std::cout << "------------------" << std::endl;
//		foo c = std::move(a + b);
//		std::cout << c << std::endl;
//	
//		/*
//			- output : 
//				�Ϲ� ������
//				�Ϲ� ������
//				�Ϲ� ������
//				000000DBD875FA54
//				3
//				------------------
//				�Ϲ� ������
//				�̵� ������
//				3
//		*/
//		
//		/*
//			- ������ ���۷���
//				- ������ ������ ���۷����� �޸� &&���� �����ϰ� �����
//				- ������ ���۷����� �������� ���������� ������ ��������
//					-> �� �ڵ忡��
//	
//						std::cout << &rvalue_ref << std::endl;	
//	
//						�� �������� �۵��Ǵ� ������
//	
//				- �������� ���� ���۷��� �̹Ƿ� �翬�� �������� �������� ����
//				- �����ϴ� �ӽ� ��ü�� �Ҹ���� �ʵ��� �ٵ�� ����
//					-> �� �ڵ忡��
//						
//						foo&& rvalue_ref = a + b;
//	
//						�� ������ ���۷����� ����ǹǷ� a + b �� ����� ���ϵ� �ӽð�ü�� �Ҹ���� ���� 
//	
//					-> ����
//	
//						std::cout << rvalue_ref << std::endl;
//	
//						�� �ڵ尡 �������� �۵���
//	
//	
//			- �̵� ������
//				- ������ ���۷����� �޾� ��ü�� �����ϴ� ������
//				- ���� �ӽ� ��ü�� ��� ���ǰ� ���� �Ҹ�ǹǷ� ��� �Ű澵�͵��� ����
//					-> �Ʒ����� MyString ������ �ذ��ϸ鼭 ����
//	
//		*/
//	
//	}

/*  MyString ������ �ذ�, �̵� ������ ������ ������ ��  */
/*
	- MyString ������ �ذ�
		- ���� : ������ str3 = str1 + str2 ����� ���ʿ��� ���簡 2�� �Ͼ
		- �ذ�
			-> ����

				str1 + str2 �� ������ �ӽ� ��ü --------> "abcdef" -> �޸� �󿡼� ����
						                                      ��
						                                    ����!
				                                              ��
				str3 �� ���� ������ --------------------> �� ���� �Ҵ� ----> "abcdef"

			-> �ذ�
			                                       1) ���� ������ �������(�Ҹ��� ȣ��� ���ڿ�(string_content)�� delete ���� �ʵ���)
				str1 + str2 �� ������ �ӽ� ��ü ---X---> "abcdef" 
															 ��
															 ��	2) ���ڿ� ��ü ���� ���� str3�� �ӽ� ��ü�� ���ڿ�(string_content)�� ����Ű���� ��
															 ��
				str3 �� �̵� ������ --------------------------

				- ���� ���� �����ڿ����� �Ұ����� �����
					-> ���� �����ڴ� ���ڸ� const MyString& ���� �����Ƿ� �ӽ� ��ü�� string_content ���� ������ �� ���� ����
*/

#include <iostream>
#include <cstring>
#include <utility>
#include <vector>

class MyString
{
public:
	MyString();

	// ���ڿ��κ��� ����
	MyString(const char* str);

	// ���� ������
	MyString(const MyString& str);

	// �̵� ������
	MyString(MyString&& str) noexcept;

	void reserve(int size);
	int length() const { return string_length; };
	void print();
	void println();

	MyString operator+(const MyString& s);

	~MyString();

private:
	char* string_content;
	int string_length;
	int memory_capacity;
};

MyString::MyString()
{
	std::cout << "������ ȣ��" << std::endl;
	string_length = 0;
	memory_capacity = 0;
	string_content = nullptr;
}

MyString::MyString(const char* str)
{
	std::cout << "������ ȣ��" << std::endl;
	string_length = strlen(str);
	memory_capacity = string_length;
	string_content = new char[string_length];

	for (int i = 0; i < string_length; i++) string_content[i] = str[i];
}

MyString::MyString(const MyString& str)
{
	std::cout << "���� ������ ȣ��" << std::endl;
	string_length = str.string_length;
	memory_capacity = str.memory_capacity;
	string_content = new char[string_length];

	for (int i = 0; i < string_length; i++) string_content[i] = str.string_content[i];
}

MyString::MyString(MyString&& str) noexcept
{
	std::cout << "�̵� ������ ȣ��" << std::endl;
	string_length = str.string_length;
	memory_capacity = str.memory_capacity;
	string_content = str.string_content;

	// �ӽ� ��ü �Ҹ�� �޸� ������ ���ϵ��� ������ ����
	str.string_content = nullptr;
}

MyString::~MyString()
{
	if (string_content) delete[] string_content;
}

void MyString::reserve(int size)
{
	if (size > memory_capacity)
	{
		char* prev_string_content = string_content;

		string_content = new char[size];
		memory_capacity = size;

		for (int i = 0; i < string_length; i++)
			string_content[i] = prev_string_content[i];

		if (prev_string_content != nullptr) delete[] prev_string_content;
	}
}

MyString MyString::operator+(const MyString& s)
{
	MyString str;
	str.reserve(string_length + s.string_length);
	for (int i = 0; i < string_length; i++)
	{
		str.string_content[i] = string_content[i];
	}
	for (int i = 0; i < s.string_length; i++)
	{
		str.string_content[string_length + i] = s.string_content[i];
	}
	str.string_length = string_length + s.string_length;
	return str;
}

void MyString::print()
{
	for (int i = 0; i != string_length; i++) std::cout << string_content[i];
}

void MyString::println()
{
	for (int i = 0; i != string_length; i++) std::cout << string_content[i];

	std::cout << std::endl;
}

int main()
{
	/*  MyString ������ �ذ�  */
	//	{
	//		MyString str1("abc");
	//		MyString str2("def");
	//		std::cout << "----------------" << std::endl;
	//		MyString str3 = std::move(str1 + str2);
	//		str3.println();
	//	
	//		/*
	//			- output :
	//				������ ȣ��
	//				������ ȣ��
	//				----------------
	//				������ ȣ��
	//				abcdef
	//	
	//				-> ���� �̵� �����ڵ� �׳� �����ؼ� ����ȭ��Ű�� ����̴�... https://en.cppreference.com/w/cpp/language/move_constructor �� Explanation �� ����
	//				When the initializer is a prvalue, the move constructor call is often optimized out(until C++17)never made(since C++17), see copy elision.
	//				-> str1 + str2 �� ����� prvalue �̹Ƿ� �����Ǵ� �����. xvalue �� �ƴ� �������� �̵����� ��ų���� std::move�� ����ؾ� �Ǵµ� ��
	//	
	//			- std::move �� ����� output:
	//				������ ȣ��
	//				������ ȣ��
	//				----------------
	//				������ ȣ��
	//				�̵� ������ ȣ��
	//				abcdef
	//	
	//				-> ������ ����� �ڵ� ������ �Ȱ��� ����� ����
	//	
	//				MSVC C++14�� �����
	//		*/
	//	}

	/*  �̵� ������ ������ ������ �� - noexcept  */
	{
		MyString s("abc");
		std::vector<MyString> vec;
		vec.resize(0);

		std::cout << "ù ��° �߰� ---" << std::endl;
		vec.push_back(s);
		std::cout << std::endl;

		std::cout << "�� ��° �߰� ---" << std::endl;
		vec.push_back(s);
		std::cout << std::endl;

		std::cout << "�� ��° �߰� ---" << std::endl;
		vec.push_back(s);

		/*
			- �ʱ� output : 
				������ ȣ��
				ù ��° �߰� ---
				���� ������ ȣ��
				
				�� ��° �߰� ---
				���� ������ ȣ��
				���� ������ ȣ��
				
				�� ��° �߰� ---
				���� ������ ȣ��
				���� ������ ȣ��
				���� ������ ȣ��
			
			- �̵� �����ڿ� noexcept �߰� �� output :
				������ ȣ��
				ù ��° �߰� ---
				���� ������ ȣ��
				
				�� ��° �߰� ---
				���� ������ ȣ��
				�̵� ������ ȣ��
				
				�� ��° �߰� ---
				���� ������ ȣ��
				�̵� ������ ȣ��
				�̵� ������ ȣ��
		*/

		/*
			- �̵� ������ ���� ������ ��
				- std::vector ���� STL �����̳ʿ� ����� Ŭ������ �̵� �����ڴ� �ݵ�� noexcept �� ������־�� ��
				- ��? : vector �� ���÷� ����
					-> ���࿡ vector�� �޸𸮰� ���� ���� ���ο� ������ �Ҵ��� �� �޸𸮸� �Ҵ��� ���� ������ ���Ҹ� �ű�
					-> �ű�� �������� ���ܰ� �߻��Ѵٰ� �ĺ���

						- ���� �����ڸ� ����ϴ� ���
							-> �׳� �Ҵ���ѳ��� �޸𸮸� �Ҹ��Ű�� ����ڿ��� ���ܸ� ����
							-> �Ҵ��� �޸𸮸� �Ҹ��Ű�鼭 ����� ���ҵ鵵 �Ҹ�ǹǷ� �ڿ��� ������� ����
							-> ����� ������ ���������Ƿ� ���ܸ� ������ �ٽ� ������� ���ư��⸸ �ϸ� ��

						- �̵� �����ڸ� ����ϴ� ���
							-> ���Ұ� ��°�� �̵��Ǿ���ȱ� ������ ������ �������� ����
							-> ���� �Ҵ��� �޸𸮸� �Ҹ��Ű�� ���ҵ鵵 ��°�� ���ư��Ƿ� �Ժη� �Ҹ��ų �� ����

					-> �̷��� ������ vector�� �̵� �����ڿ��� ���ܰ� �߻��ϸ� �̸� ����� ó���� �� ����

				- �� ������ vector�� ��������� STL�� �����̳ʴ� �� �̷�
				- �ذ��� : �̵� �����ڿ� noexcept�� ���
					-> �̵� �����ڰ� ���ܸ� ������ �����Ƿ� �Ƚ��ϰ� �̵���ų �� ����
					
				- <utility>�� std::move_if_noexcept() ��� �Լ��� STL �����̳ʵ��� �̵��� ������
					-> noexcept �϶��� �̵��� �����ϴ� �Լ� -> noexcept�� �ƴϸ� ���縦 ����
				
		*/
	}

	return 0;
}
