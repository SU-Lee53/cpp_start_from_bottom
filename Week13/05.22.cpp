/*
	05.22 ������ ���۷����� �̵� ������
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

/*  MyString ������ �ذ� : ������ ���۷����� �̵� ������  */