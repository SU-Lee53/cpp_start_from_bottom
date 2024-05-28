/*
	05.27 12-2 move ����(std::move sementics), �Ϻ��� ����(perfect forwarding)
*/

/*  MyString �� swap - �������� �̵�?  */
//	#include <iostream>
//	#include <cstring>
//	
//	class MyString
//	{
//	public:
//		MyString()
//		{
//			std::cout << "������ ȣ��" << std::endl;
//			string_length = 0;
//			memory_capacity = 0;
//			string_content = nullptr;
//		}
//	
//		MyString(const char* str)
//		{
//			std::cout << "������ ȣ��" << std::endl;
//			string_length = strlen(str);
//			memory_capacity = string_length;
//			string_content = new char[memory_capacity];
//	
//			for (int i = 0; i != string_length; i++) string_content[i] = str[i];
//		}
//	
//		MyString(const MyString& str)
//		{
//			std::cout << "���� ������ ȣ��" << std::endl;
//			string_length = str.string_length;
//			memory_capacity = str.memory_capacity;
//			string_content = new char[memory_capacity];
//	
//			for (int i = 0; i != string_length; i++) string_content[i] = str.string_content[i];
//		}
//	
//		MyString(MyString&& str)
//		{
//			std::cout << "�̵� ������ ȣ��" << std::endl;
//			string_length = str.string_length;
//			memory_capacity = str.memory_capacity;
//			string_content = str.string_content;
//	
//			str.string_content = nullptr;
//		}
//	
//		MyString &operator=(const MyString& s)
//		{
//			std::cout << "����" << std::endl;
//			if (s.string_length > memory_capacity)
//			{
//				delete[] string_content;
//				string_content = new char[s.string_length];
//				memory_capacity = s.memory_capacity;
//			}
//			string_length = s.string_length;
//			for (int i = 0; i != string_length; i++)
//			{
//				string_content[i] = s.string_content[i];
//			}
//	
//			return *this;
//		}
//	
//		int length() const { return string_length; }
//	
//		void println()
//		{
//			for (int i = 0; i != string_length; i++)
//			{
//				std::cout << string_content[i];
//			}
//			std::cout << std::endl;
//		}
//	
//		~MyString()
//		{
//			if (string_content) delete[] string_content;
//		}
//	
//	private:
//		char* string_content;
//		int string_length;
//		int memory_capacity;
//	};
//	
//	template <typename T>
//	void my_swap(T& a, T& b)
//	{
//		T tmp(a);
//		a = b;
//		b = tmp;
//	}
//	
//	int main()
//	{
//		MyString str1("abc");
//		MyString str2("def");
//		std::cout << "swap �� ------" << std::endl;
//		str1.println();
//		str2.println();
//	
//		std::cout << "swap �� ------" << std::endl;
//		my_swap(str1, str2);
//		str1.println();
//		str2.println();
//		/*
//			- output :
//			������ ȣ��
//			������ ȣ��
//			swap �� ------
//			abc
//			def
//			swap �� ------
//			���� ������ ȣ��
//			����
//			����
//			def
//			abc
//		*/
//	
//		/*
//			- �������� �̵�?
//				- �� �ڵ��� ����
//					- MyString ��ü 2���� ����� 2���� �ٲٷ��� ��
//					- �̸� ���� ���ø��� �̿��� my_swap �Լ��� �̿�
//					- �̶� my_swap �Լ� ���ø��� �̿��Ͽ� �ٲܶ� ���ʿ��� ���簡 3���̳� �Ͼ
//						- ���� �Լ��� �����鼭 ����
//	
//							template <typename T>
//							void my_swap(T& a, T& b)
//							{
//								T tmp(a);		-> 1���� �������� a�� �����صα� ���� ���� �����ڸ� ȣ��
//								a = b;			-> 2�� ����
//								b = tmp;		-> 3�� ����
//							}
//	
//							��,
//	
//							str1.string_content(a) ------- ���� 1 --------> tmp.string_content
//							          ��                                               |
//							       ���� 2                                             |
//							          |                                               |
//							str2.string_content(b) <------------ ���� 3 --------------
//							
//							�� ���·� ���簡 �Ͼ
//	
//					- "�̵�" �̶�� ������ ��� �̻� �̴� �ſ� ��ȿ������
//						-> �ܼ��� str1�� str2�� string_content �� ����Ű�� �����͸� ���� �ٲ��ָ� �Ǳ� ����
//	
//				- ��� �̵���ų��
//					- my_swap�� �Լ� ���ø��̹Ƿ� MyString �� ���� Ư��ȭ�� �ʿ���
//					- MyString�� string_content�� private �̹Ƿ� my_swap �� �ƴ� MyString �� ��� �Լ��� swap�� �����ؾ���
//						-> �� ��� my_swap �� ���� ������ �����
//	
//					- �׳� ����� ���� my_swap�� �̿��Ϸ���?
//						- tmp�� ����������� �ʰ� a�� �Űܳ��⸸ �ϸ� ��
//						- ��, T tmp(a) �� ��������� �ƴ� �̵������� �Ǿ�� ��
//						- �׷��� a�� �������� �̻� �̴� �Ұ�����
//							-> �������� ���������� �ٲ��� ���� ������? -> std::move�� �̿��ϸ� ��
//		*/
//	
//	}

/*  std::move  */
//	#include <iostream>
//	#include <utility>
//	#include <iomanip>
//	#include <vector>
//	#include <string>
//	
//	class A
//	{
//	public:
//		A() { std::cout << "�Ϲ� ������" << std::endl; }
//		A(const A& a) { std::cout << "���� ������" << std::endl; }
//		A(A&& a) { std::cout << "�̵� ������" << std::endl; }
//	};
//	
//	int main()
//	{
//		A a;
//	
//		std::cout << "------------" << std::endl;
//		A b(a);
//	
//		std::cout << "------------" << std::endl;
//		A c(std::move(a));
//	
//		/*
//			- output : 
//				�Ϲ� ������
//				------------
//				���� ������
//				------------
//				�̵� ������
//		*/
//	
//		/*
//			- std::move �� move semantics
//				- std::move : <utility> ����� ���ǵ� �Լ��� �������� ���������� ����ȯ����
//				- std::move �ܵ����δ� �̵������� ������� ����!!! ���ڷ� ���� ��ü�� ���������� Ÿ�� ��ȯ���ִ� ���Ҹ� ��
//	
//				- �� �ڵ�
//					- A a : �Ϲ� �����ڰ� ���������� ȣ��
//					- A b(a) : a�� ������ �̹Ƿ� ���� �����ڰ� ȣ��
//					- A c(std::move(a)) : std::move �� �̿��� a�� ���������� �ٲپ� �־����Ƿ� �̵� �����ڰ� ȣ��
//		*/
//	
//		/*  cppreference �ڵ� �߰� : move �� ���� ������ ��ü�� ���?  */
//		
//		std::string str = "Salut";
//		std::vector<std::string> v;
//	
//		// uses the push_back(const T&) overload, which means we'll incur the const of copying str
//		// push_back(const T&) ������ �����ε� �Լ��� �����. ��, str ���翡 ���� ����� �ʷ���
//		v.push_back(str);
//		std::cout << "After copy, str is " << std::quoted(str) << '\n';		// std::quoted : ����� ������ �����ڿ� �̽������� ���ڸ� �̿��� ���ڿ��� �аų� �� (�⺻ �����ڴ� "", �̽��������� \)
//	
//		// uses the rvalue reference push_back(T&&) overload, which means no strings will be copied.
//		// instead, the contents of str will be moved into the vector. 
//		// This is less expensive, but also means str might now be empty.
//		// 
//		// ������ ���۷����� �̿��� push_back(T&&) ������ �����ε� �Լ��� �̿���. ��, ��� ���ڿ��� ������� ����
//		// ���, str�� ������� vector ������ �̵���
//		// �̰��� ����� �� ������, str�� ���� ������� ����
//		v.push_back(std::move(str));
//		std::cout << "After move, str is " << std::quoted(str) << '\n';
//	
//		std::cout << "The contents of the vector are {" << std::quoted(v[0]) << ", " << std::quoted(v[1]) << "}\n";
//		
//		/*
//			- output :
//				After copy, str is "Salut"
//				After move, str is ""
//				The contents of the vector are {"Salut", "Salut"}
//				
//				-> �̵��� ����Ǹ� ���� ��ü�� �ƹ��͵� ������� ������ Ȯ�� ������
//		*/
//	
//	}

/*  move �� �̿��� MyString �� swap  */
//	#include <iostream>
//	#include <cstring>
//	#include <utility>
//	
//	class MyString
//	{
//	public:
//		MyString()
//		{
//			std::cout << "������ ȣ��" << std::endl;
//			string_length = 0;
//			memory_capacity = 0;
//			string_content = nullptr;
//		}
//	
//		MyString(const char* str)
//		{
//			std::cout << "������ ȣ��" << std::endl;
//			string_length = strlen(str);
//			memory_capacity = string_length;
//			string_content = new char[memory_capacity];
//	
//			for (int i = 0; i != string_length; i++) string_content[i] = str[i];
//		}
//	
//		MyString(const MyString& str)
//		{
//			std::cout << "���� ������ ȣ��" << std::endl;
//			string_length = str.string_length;
//			memory_capacity = str.memory_capacity;
//			string_content = new char[memory_capacity];
//	
//			for (int i = 0; i != string_length; i++) string_content[i] = str.string_content[i];
//		}
//	
//		MyString(MyString&& str)
//		{
//			std::cout << "�̵� ������ ȣ��" << std::endl;
//			string_length = str.string_length;
//			memory_capacity = str.memory_capacity;
//			string_content = str.string_content;
//	
//			str.string_content = nullptr;
//		}
//	
//		// �Ϲ� ���� ������
//		MyString& operator=(const MyString& s)
//		{
//			std::cout << "����" << std::endl;
//			if (s.string_length > memory_capacity)
//			{
//				delete[] string_content;
//				string_content = new char[s.string_length];
//				memory_capacity = s.memory_capacity;
//			}
//			string_length = s.string_length;
//			for (int i = 0; i != string_length; i++)
//			{
//				string_content[i] = s.string_content[i];
//			}
//	
//			return *this;
//		}
//	
//		MyString& operator=(MyString&& s)
//		{
//			std::cout << "�̵�" << std::endl;
//			string_content = s.string_content;
//			memory_capacity = s.memory_capacity;
//			string_length = s.string_length;
//	
//			s.string_content = nullptr;
//			s.memory_capacity = 0;
//			s.string_length = 0;
//	
//			return *this;
//		}
//	
//		int length() const { return string_length; }
//	
//		void println()
//		{
//			for (int i = 0; i != string_length; i++)
//			{
//				std::cout << string_content[i];
//			}
//			std::cout << std::endl;
//		}
//	
//		~MyString()
//		{
//			if (string_content) delete[] string_content;
//		}
//	
//	private:
//		char* string_content;
//		int string_length;
//		int memory_capacity;
//	};
//	
//	template <typename T>
//	void my_swap(T& a, T& b)
//	{
//		T tmp(std::move(a));
//		a = std::move(b);
//		b = std::move(tmp);
//	}
//	
//	int main()
//	{
//		MyString str1("abc");
//		MyString str2("def");
//		std::cout << "Swap �� -----" << std::endl;
//		std::cout << "str1 : ";
//		str1.println();
//		std::cout << "str2 : ";
//		str2.println();
//	
//		std::cout << "Swap �� -----" << std::endl;
//		my_swap(str1, str2);
//		std::cout << "str1 : ";
//		str1.println();
//		std::cout << "str2 : ";
//		str2.println();
//	
//		/*
//			-output :
//				������ ȣ��
//				������ ȣ��
//				Swap �� -----
//				str1 : abc
//				str2 : def
//				Swap �� -----
//				�̵� ������ ȣ��
//				�̵�
//				�̵�
//				str1 : def
//				str2 : abc
//		*/
//	
//		/*
//			- MyString swap ������ �ذ�
//				- ������ ���� : swap �� ���ʿ��� ���簡 3�� �Ͼ
//				- �ذ�
//					1) tmp�� �ӽ� �����ϰ� swap�ϴ� ��� ������ �̵����� ó��
//						-> ���ʿ��� ���縦 ����
//	
//					2) �̵� ���� ������ �����ε�
//						- 1)�� ���ؼ� �ݵ�� �ʿ���
//						- �̵� �����ڿ� ���������� �����͸� �̵���Ų �� ���� ��ü�� �����Ҵ�� �޸𸮰� �ִٸ� ������ �������
//						- ���� �̵� ���� �����ڰ� ���ٸ� ��� ������ ����� �Ͼ
//	
//				- �� �ڵ忡���� ������ std::move() ������ �̵��� ����Ǵ°��� �ƴ� ���� ���������� ����ȯ�Ͽ� �����ϱ⸸ ��
//					-> ���� �̵��� �̵� �����ڳ� �̵� ���� �����ڸ� ȣ���Ҷ� �Ͼ
//		*/
//	}

/*  ��ü ���ο� �ٸ� ��ü ���� ����  */
//	/*
//		- ����
//			- ������ ���� 2���� Ŭ������ �ִٰ� �غ���
//				- A : �Ϲ����� Ŭ����
//				- B : A�� �����ϴ� Ŭ����
//	
//			- B��ü�� ������ �� �̹� ������ A ��ü�� B�� ������ �������� ��� �����ڸ� ������ �ϴ°�?
//	*/
//	
//	#include <iostream>
//	#include <utility>
//	
//	class A
//	{
//	public:
//		A() { std::cout << "ctor" << '\n'; }
//		A(const A& a) { std::cout << "copy ctor" << '\n'; }
//		A(A&& a) { std::cout << "move ctor" << '\n'; }
//	
//	};
//	
//	class B
//	{
//	public:
//		//	B(const A& a) : a_(a) {};
//		//	B(const A& a) : a_(std::move(a)) {};
//		//	B(A&& a) : a_(a) {};
//		B(A&& a) : a_(std::move(a)) {};
//	
//		A a_;
//	};
//	
//	int main()
//	{
//		A a;	// a ����
//	
//		// ���� ���� a�� B�� ��������?
//		std::cout << "create B --" << '\n';
//		B b(std::move(a));
//	
//		/*
//			- B �ȿ� �̹� ������ A a �� �ִ¹�?
//	
//				1) B(const A& a) : a_(a) {}; : �����ڸ� ����� ��������
//					-> B �� A�� ���°��� ����
//					-> �׷��� B�� �̹� �ִ� a�� ���°��� �ƴ� a�� ��������� ���ο� A��ü�� ��
//					-> ����
//	
//				2) B(const A& a) : a_(std::move(a)) {}; : ���������� ����� �ʱ�ȭ�غ���
//					-> initializer list ���� a_(std::move(a))�� ���־����Ƿ� �̵� �����ڰ� ȣ��ǰ���? -> �ƴ�
//						-> ���� �������� ���ڰ� const A& �̹Ƿ� std::move(a) �� ����� const A&& ��
//						-> �̶� �����Ϸ��� A�� �����ڷ� A&&�� �޴� �̵������ڰ� �ƴ� const A&�� �޴� ���� �����ڸ� ������
//					-> ����
//	
//				3) B(A&& a) : a_(a) {}; : �������� �޴� �����ڸ� ����� ��������
//					-> �������� ���������� �̵� �����ڰ� ȣ��ǰ���? -> �ƴ�
//						-> a�� ������ ���۷����� ����
//						-> �ٸ� a �� ��ü�� ��������(�̸��� ����)
//						-> ���� ���� �����ڰ� ȣ���
//					-> ����
//	
//				4) B(A&& a) : a_(std::move(a)) {}; : ���ڵ� ���������� �ް� �ʱ�ȭ�� ���������� ���� ����
//					-> ����
//	
//			- ���
//				- �̹� ������ ��ü�� �ٸ� ��ü�� ������ ���
//					-> �������� �޴� �����ڸ� �����
//					-> �ʱ�ȭ���� move �������� ���������� ���־�� ���������� ��
//	
//		*/
//	
//	}

/*  �Ϻ��� ���� perfect forwarding  */
