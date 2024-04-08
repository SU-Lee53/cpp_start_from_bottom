/*

	04.05 ~ 06 std::string, ���, �������̵�, protected

*/

// ǥ�� string Ŭ���� std::string

//	#include <iostream>
//	#include <string>
//	#include <tchar.h>
//	
//	int main()
//	{
//		//	std::string s = "abc";
//		//	std::string t = "def";
//		//	std::string s2 = s;
//		//	
//		//	std::cout << s << " �� ���� : " << s.length() << std::endl;
//		//	std::cout << s << " �ڿ� " << t << " �� ���̸� : " << s + t << std::endl;
//		//	
//		//	if (s == s2)
//		//		std::cout << s << " �� " << s2 << " �� ���� " << std::endl;
//		//	if (s != t)
//		//		std::cout << s << " �� " << t << " �� �ٸ��� " << std::endl;
//	
//		/*
//			output
//			abc �� ���� : 3
//			abc �ڿ� def �� ���̸� : abcdef
//			abc �� abc �� ����
//			abc �� def �� �ٸ���
//		*/
//	
//	
//		/*
//			- std::string
//				- C++�� ���ڿ� Ŭ����.
//				- �⺻������ <string> ����ȿ��� basic_string�� char_traits �� �����Ǿ�����
//					- char_traits: �⺻���� ����/���ڿ� ������ ����
//					- basic_string: �������̰� �پ��� ���ڿ� ���� ����� ����
//					-> �⺻������ ��ó�� std::string�� �����ϸ� std::basic_string�� �����ǰ� ����ȿ� typedef�� �Ǿ�����
//				- ��ó�� �⺻���� std::string�� std::basic_string<char>�� �����ϰ� �ٸ� ������ ���ڿ��� ������(�⺻ char�� ANSI)
//					- std::wstring		->		std::basic_string<wchar_t>(�����ڵ�)
//					- std::u8string		->		std::basic_string<char8_t>
//					- std::u16string	->		std::basic_string<char16_t>
//					- std::u32string	->		std::basic_string<char32_t>
//					- ���� ���� ���ø����� �Ǿ��־� ��� ��� �Լ����� ������
//					- ���� �غ��ϱ� TCHAR���� ���ڵ��� ����� ����
//					- �߰������� C++�� �޸� �Ҵ����� PMR�� �̿��� std::pmr::string ���� ������ �̺κ��� �ϴ� �Ѿ
//				- ������ strcmp, strlen, strcat ���� �̿��ؾ��ߴ� C�� ���ڿ��� �ٸ��� �⺻���� ��ɵ��� ��� �Լ��� ������ https://en.cppreference.com/w/cpp/string/basic_string
//					- length(), insert(), erase(), replace() ����� �پ��� ��� �Լ����� �⺻ ������
//					- Ư�� strcmp, strcat ���� ����� �����ڷ� �����ϴٴ� ���� ���� ��� �κ��̶�� ������(��, ��Һ� �Ѵ� �����ڷ� ����)
//					- ��ü ��ɵ��� �Ŀ� STL �����Ҷ� cppreference�� �ĸ鼭 �Բ� ����
//		*/
//	
//		// soen.kr�� ����� �پ��� string �����ڵ�(�̰� ���� ���ο� ǥ�ص鿡�� �� ���� �߰���)
//	
//		std::string s1("test");								// string(const char *s) �� ���� ���ڿ��κ��� �����ϴ� ��ȯ ������
//		std::string s2(s1);									// string(const string& str, int pos = 0, int num = npos) ���� ������
//		std::string s3;										// string() �⺻ ������
//		std::string s4(32, 'S');							// string(size_t n, char c) c�� n�� ä��	
//		std::string s5("very nice day", 8);					// string(const cchar* s, size_t n) �� ���� ���ڿ��κ��� �����ϵ� n���� Ȯ��
//		const char* str = "abcdefghijllmnopqrstuvwxyz";		
//		std::string s6(str + 5, str + 10);					// template<It> string(It begin, It end) begin ~ end ������ ���ڷ� ������ ���ڿ� ����
//	
//		std::cout << "s1 = " << s1 << std::endl;	// s1 = test
//		std::cout << "s2 = " << s2 << std::endl;	// s2 = test
//		std::cout << "s3 = " << s3 << std::endl;	// s3 =
//		std::cout << "s4 = " << s4 << std::endl;	// s4 = SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
//		std::cout << "s5 = " << s5 << std::endl;	// s5 = very nic
//		std::cout << "s6 = " << s6 << std::endl;	// s6 = fghij
//	
//		return 0;
//	}

// ����� ������... - ��� ���� ���α׷�

//	#include <iostream>
//	#include <string>
//	
//	/*
//		- ������� ���α׷��� ������
//			- ���� : ������� ������ ����ؼ� �Ѵ޿� �� �󸶳� �Ǵ� ���� �������� �����ؾ� �ϴ��� �˷��ִ� ���α׷�
//			- �ʿ��� ��
//				- ������� ����
//					- �̸�
//					- ����
//					- ��å
//					- ��å�� ����(���� : 1, �븮 : 2 ...)
//					-> Ŭ������ ���� ����(Employee)
//				- ��� Ŭ������ ������ ����Ʈ(EmployeeList)
//			- Manager�� �߰�
//				- Manager : ���� �̻�޵��� �ټӳ���� ���Խ��� ���޿� �߰��ϱ� ���� Employee�ʹ� ���еǴ� Ŭ����
//			- ���� ����� Manager�� Employee�� ���� �κ��� ���������� �̸��� �ٲ㼭 ó������ �ٽ� �ۼ��ϴ°��� �ſ�ſ� ������
//				-> �̶� ����� �̿�
//	*/
//	
//	class Employee
//	{
//	public:
//		Employee(std::string name, int age, std::string position, int rank)
//			: name(name), age(age), position(position), rank(rank) {}
//		Employee(const Employee& e)
//		{
//			name = e.name;
//			age = e.age;
//			position = e.position;
//			rank = e.rank;
//		}
//	
//		Employee() {}
//	
//		void print_info() { std::cout << name << " (" << position << " , " << age << ") ==> " << calculate_pay() << "����" << std::endl; }
//		int calculate_pay() { return 200 + rank * 50; }
//	
//	
//	private:
//		std::string name;
//		int age;
//	
//		std::string position;	// ��å(�̸�)
//		int rank;	// ���� (���� Ŭ ���� ���� ����)
//	
//	};
//	
//	class Manager
//	{
//	public:
//		Manager(std::string name, int age, std::string position, int rank, int year_of_service)
//			: name(name), age(age), position(position), rank(rank), year_of_service(year_of_service) {}
//		Manager(const Manager& m)
//		{
//			name = m.name;
//			age = m.age;
//			position = m.position;
//			rank = m.rank;
//			year_of_service = m.year_of_service;
//		}
//	
//		// ����Ʈ
//		Manager() {}
//	
//		void print_info() { std::cout << name << " (" << position << " , " << age << " , " <<  year_of_service << "����) ==> " << calculate_pay() << "����" << std::endl; }
//		int calculate_pay() { return 200 + rank * 50 + 5 * year_of_service; }
//	
//	
//	private:
//		std::string name;
//		int age;
//	
//		std::string position;	// ��å(�̸�)
//		int rank;	// ���� (���� Ŭ ���� ���� ����)
//		int year_of_service;
//	};
//	
//	class EmployeeList
//	{
//	public:
//		EmployeeList(int alloc_employee) : alloc_employee(alloc_employee)
//		{
//			employee_list = new Employee* [alloc_employee];
//			manager_list = new Manager* [alloc_employee];
//	
//			current_employee = 0;
//			current_manager = 0;
//		}
//	
//		void add_employee(Employee* employee)
//		{
//			/*
//				��� current_employee ���� alloc_employee �� �� �������� ��� �ݵ�� ���Ҵ��� �ؾ� ������,
//				���⼭�� �ִ��� �ܼ��ϰ� �����ؼ� alloc_employee �� ������ current_employee ���� ũ�ٰ� �����Ѵ�.
//				��, �Ҵ�� ũ��� ���� �� ������ ���� ����
//			*/
//			employee_list[current_employee] = employee;
//			current_employee++;
//		}
//	
//		void add_manager(Manager* manager)
//		{
//			manager_list[current_manager] = manager;
//			current_manager++;
//		}
//	
//		int current_employee_num() { return current_employee + current_manager; }
//	
//		void print_employee_info() {
//			int total_pay = 0;
//			for (int i = 0; i < current_employee; i++)
//			{
//				employee_list[i]->print_info();
//				total_pay += employee_list[i]->calculate_pay();
//			}
//			for (int i = 0; i < current_manager; i++)
//			{
//				manager_list[i]->print_info();
//				total_pay += manager_list[i]->calculate_pay();
//			}
//	
//			std::cout << "�� ��� : " << total_pay << "���� " << std::endl;
//		}
//	
//		~EmployeeList()
//		{
//			for (int i = 0; i < current_employee; i++)
//			{
//				delete employee_list[i];
//			}
//			for (int i = 0; i < current_manager; i++)
//			{
//				delete manager_list[i];
//			}
//	
//			delete[] employee_list;
//			delete[] manager_list;
//		}
//	private:
//		int alloc_employee;			// �Ҵ��� �� ���� ��
//	
//		int current_employee;		// ���� ���� ��
//		int current_manager;		// ���� �Ŵ��� ��
//	
//		Employee** employee_list;	// ���� ������
//		Manager** manager_list;		// �Ŵ��� ������
//	};
//	
//	int main()
//	{
//		EmployeeList emp_list(10);
//		emp_list.add_employee(new Employee("��ȫö", 34, "����", 1));
//		emp_list.add_employee(new Employee("����", 34, "����", 1));
//	
//		emp_list.add_manager(new Manager("���缮", 41, "����", 7, 12));
//		emp_list.add_manager(new Manager("������", 43, "����", 4, 15));
//		emp_list.add_manager(new Manager("�ڸ��", 43, "����", 5, 13));
//		emp_list.add_employee(new Employee("������", 36, "�븮", 2));
//		emp_list.add_employee(new Employee("��", 36, "����", -2));
//	
//		emp_list.print_employee_info();
//	
//		return 0;
//	
//		/*
//			output
//			��ȫö (���� , 34) ==> 250����
//			���� (���� , 34) ==> 250����
//			������ (�븮 , 36) ==> 300����
//			�� (���� , 36) ==> 100����
//			���缮 (���� , 41 , 12����) ==> 610����
//			������ (���� , 43 , 15����) ==> 475����
//			�ڸ�� (���� , 43 , 13����) ==> 515����
//			�� ��� : 2500����
//		
//		*/
//	}

// ���(inheritance)

//	#include <iostream>
//	#include <string>
//	
//	class Base
//	{
//	public:
//		Base() : parent_string("���") { std::cout << "��� Ŭ����" << std::endl; }
//	
//		void what() { std::cout << parent_string << std::endl; }
//	
//		std::string parent_string;
//	private:
//		
//	};
//	
//	class Derived : public Base
//	{
//	public:
//		Derived() : Base(), child_string("�Ļ�") // �ʱ�ȭ ����Ʈ���� ��� Ŭ������ �����ڸ� ���� ȣ��. ��������� ȣ������ ������ ����Ʈ ������ ȣ���.
//		{ 
//			std::cout << "�Ļ� Ŭ����" << std::endl;
//	
//			// Base ���� what()�� ���� �޾����Ƿ� Derived ���� ȣ�� ����
//			what();
//		}
//	
//		void what() { std::cout << child_string << std::endl; }
//	
//	private:
//		std::string child_string;
//	};
//	
//	int main()
//	{
//		std::cout << " === ��� Ŭ���� ���� ===" << std::endl;
//		Base p;
//		std::cout << p.parent_string << std::endl;
//	
//		std::cout << " === �Ļ� Ŭ���� ���� === " << std::endl;
//		Derived c;
//		std::cout << c.parent_string << std::endl;	// protected / private ����� ������ �Ʒ��� ������ �߻��ϸ� ������ ������ ��
//		// C2247: 'Base::parent_string'�� �׼����� �� �����ϴ�. �̴� 'Derived'��(��) 'private'��(��) ����Ͽ� 'Base' ���� ����ϱ� �����Դϴ�
//	
//	
//		/*
//			- ���(inheritance) : �ٸ� Ŭ������ ������ ���� �޾Ƽ� ����� �� �ֵ��� ��
//				- ���� -> class (�Ļ� Ŭ����) : (���� ������) (��� Ŭ����)
//				- �θ�-�ڽ� Ŭ������� �ϴµ� C++�� �������� Ŭ�������� ��ӹ��� �� �����Ƿ� ���-�Ļ� Ŭ������ �� ������(cppreference�� Base-Derived �� �ۼ���)
//				- ���� Derived�� Base�� public���� ��ӹް� ����
//					- ���� ����
//						- Base : [string s][Base()][what()]
//						- Derived : [string s][Base()][what()] + [string s][Derived()]
//						-> �̷��� Derived Ŭ������ Base Ŭ������ �ڵ尡 �׷��� ���ִ� ��ó�� ������
//					- �ʱ�ȭ ����Ʈ���� ��� Ŭ������ �����ڸ� ���� ȣ�����ְ�����. ���࿡ ��������� ������ ������ ����Ʈ �����ڰ� ȣ���.
//						-> �Ļ� Ŭ������ �����Ǳ� ���� ���� ��� Ŭ������ ������
//						-> ���� �����ڸ� ����� �����غ��� �Ȱ��� ��� Ŭ������ ��µ�
//					- Derived ���� Base�� what()�� ȣ��
//						- Base�� ��� ������ ��ӹ޾ұ� ������ Derived������ what()�� ȣ�� ����
//						- �׷��� �� "�Ļ�" �� �ƴ� "���"�� ��µɱ�
//							-> what() �Լ��� Base�� ���ǵǾ��ֱ� ������ Derived::s�� �ƴ� Base::s�� ��µǴ� ��
//							-> Derived ������ what() �Լ��� ����� "�Ļ�"�� ��µ�
//								-> !!! �ٸ� Ŭ������ ���ǵǾ� �ִ� �Լ��� ���� ���� �ٸ� �Լ��� ��޵ǰ� �̸� �������̵�(overriding)�̶�� �� !!!
//					- ����� ���� ������
//						- public: �Ļ� Ŭ���� ���忡�� ��� Ŭ������ ���� �����ڵ鿡 ���� ���� �״�� �۵���
//						- protected: �Ļ� Ŭ���� ���忡�� ��� Ŭ������ public�� protected �� ����
//						- private: �Ļ� Ŭ���� ���忡�� ��� Ŭ������ ��� ���� �����ڵ��� private�� ��
//						-> �� �������� c.parent_string�� �����Ϸ��� �ϸ� ������ ������ �ߴµ� private ����� �ޱ� ������. public/protected ����� ������ ���������� �۵���
//		*/		
//		return 0;
//	}

// ����� �����Ų ��� ���� ���α׷�
#include <iostream>
#include <string>

class Employee
{
public:
	Employee(std::string name, int age, std::string position, int rank)
		: name(name), age(age), position(position), rank(rank) {}
	Employee(const Employee& e)
	{
		name = e.name;
		age = e.age;
		position = e.position;
		rank = e.rank;
	}

	Employee() {}

	void print_info() { std::cout << name << " (" << position << " , " << age << ") ==> " << calculate_pay() << "����" << std::endl; }
	int calculate_pay() { return 200 + rank * 50; }


protected:	// ��ӹ��� Ŭ�����鿡���� ������ �����ؾ��ϹǷ� private�� �ƴ� protected�� �Ǿ�� ��
	std::string name;
	int age;

	std::string position;	// ��å(�̸�)
	int rank;	// ���� (���� Ŭ ���� ���� ����)

};

// ���� Manager�� Employee�� ��ӹ޾Ƽ� ������
class Manager : public Employee
{
public:
	Manager(std::string name, int age, std::string position, int rank, int year_of_service)
		:year_of_service(year_of_service), Employee(name, age, position, rank) {}

	Manager(const Manager& m)
		: Employee(m.name, m.age, m.position, m.rank)
	{
		year_of_service = m.year_of_service;
	}

	Manager() : Employee() {}

	int calculate_pay() { return 200 + rank * 50 + 5 * year_of_service; }

	void print_info()
	{
		std::cout << name << " (" << position << " , " << age << ", "
			<< year_of_service << "����) ==> " << calculate_pay() << "����"
			<< std::endl;
	}

private:
	int year_of_service;

};

class EmployeeList
{
public:
	EmployeeList(int alloc_employee) : alloc_employee(alloc_employee)
	{
		employee_list = new Employee * [alloc_employee];
		manager_list = new Manager * [alloc_employee];

		current_employee = 0;
		current_manager = 0;
	}

	void add_employee(Employee* employee)
	{
		/*
			��� current_employee ���� alloc_employee �� �� �������� ��� �ݵ�� ���Ҵ��� �ؾ� ������,
			���⼭�� �ִ��� �ܼ��ϰ� �����ؼ� alloc_employee �� ������ current_employee ���� ũ�ٰ� �����Ѵ�.
			��, �Ҵ�� ũ��� ���� �� ������ ���� ����
		*/
		employee_list[current_employee] = employee;
		current_employee++;
	}

	void add_manager(Manager* manager)
	{
		manager_list[current_manager] = manager;
		current_manager++;
	}

	int current_employee_num() { return current_employee + current_manager; }

	void print_employee_info() {
		int total_pay = 0;
		for (int i = 0; i < current_employee; i++)
		{
			employee_list[i]->print_info();
			total_pay += employee_list[i]->calculate_pay();
		}
		for (int i = 0; i < current_manager; i++)
		{
			manager_list[i]->print_info();
			total_pay += manager_list[i]->calculate_pay();
		}

		std::cout << "�� ��� : " << total_pay << "���� " << std::endl;
	}

	~EmployeeList()
	{
		for (int i = 0; i < current_employee; i++)
		{
			delete employee_list[i];
		}
		for (int i = 0; i < current_manager; i++)
		{
			delete manager_list[i];
		}

		delete[] employee_list;
		delete[] manager_list;
	}
private:
	int alloc_employee;			// �Ҵ��� �� ���� ��

	int current_employee;		// ���� ���� ��
	int current_manager;		// ���� �Ŵ��� ��

	Employee** employee_list;	// ���� ������
	Manager** manager_list;		// �Ŵ��� ������
};

int main()
{
	EmployeeList emp_list(10);
	emp_list.add_employee(new Employee("��ȫö", 34, "����", 1));
	emp_list.add_employee(new Employee("����", 34, "����", 1));
	emp_list.add_manager(new Manager("���缮", 41, "����", 7, 12));
	emp_list.add_manager(new Manager("������", 43, "����", 4, 15));
	emp_list.add_manager(new Manager("�ڸ��", 43, "����", 5, 13));
	emp_list.add_employee(new Employee("������", 36, "�븮", 2));
	emp_list.add_employee(new Employee("��", 36, "����", -2));
	emp_list.print_employee_info();

	/*
		output
		��ȫö (���� , 34) ==> 250����
		���� (���� , 34) ==> 250����
		������ (�븮 , 36) ==> 300����
		�� (���� , 36) ==> 100����
		���缮 (���� , 41, 12����) ==> 610����
		������ (���� , 43, 15����) ==> 475����
		�ڸ�� (���� , 43, 13����) ==> 515����
		�� ��� : 2500����
	
	*/

	return 0;
}