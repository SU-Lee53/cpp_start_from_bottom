
/*
	04.08 is-a�� has-a ����, �������̵�, virtual�� �����Լ�, ������
*/

// is-a, has-a ����

//	/*
//		- is-a / has-a ����
//			- ��ü�� �߻�ȭ �ܰ迡�� � ��쿡 ����� �̿������� ������ �� �ִ� ���
//			- �翬�� ����������� �����ϴ� ����� �ƴϰ� ����ڰ� �ڵ��ϸ鼭 ���� �����Ͽ� �Ǵ��ϴ� ����
//			- is-a : ~ �� ~ ��! -> ����� �̿�
//				- Week6�� Manager�� Employee���踦 �����غ���
//					- Manager�� Employee�� ��� ����� �����Ѵ�
//					- Manager�� Employee�� ����� ��� �����ϹǷ� Manager�� Employee��� Ī�ص� �����ϴ�
//					- �� ��� Manager�� Employee�̴�
//					- Manager "is a" Employee -> ���
//				- �翬�� �̸� �ڹٲٸ�(Employee is a Manager)�� ���� �ȵǹǷ� ��Ӱ��谡 ��Ȯ�ϰ� ���е�
//				- ����� ���� Ŭ������ �Ļ��Ǹ� �Ļ��ɼ��� �� �� Ư��ȭ(��üȭ, specialize)�� �Ǵ� ���� �� �� ����
//					-> Manager�� Employee�̸鼭 �� �� ��ü���� �η���. �����ε� ���α׷������� ��������
//				- �ݴ�� �Ļ��� Ŭ������ ��� Ŭ������ �Ž��� �ö󰥼��� �� �� �Ϲ�ȭ(generalize)��
//					-> Manager�� �Ϲ������� Employee �̰� �����ε� ��������
//				- ������� ����� Ŭ�������� ���Ͱ��� Ư¡���� ���� ���� �ڵ� �ۼ��� �߻�ȭ�ϴ� �������� ������ �� �� ����
//			- has-a: ~ �� ~ �� ������ �ִ� -> ����� �̿����� ����
//				- �ڵ����� �����غ���
//					- �ڵ����� ������ ������ ����
//					- �ڵ����� ������ ������ ����
//					- �ڵ����� �극��ũ�� ������ ����
//					- Car is a Wheel/Engine/Brake��� ���� �� ����
//						-> Car has a Wheel/Engine/Brake�� �� ����
//				- �̷� ��쿡�� ����� �ƴ� Ŭ������ ����� �������ִ°��� ����
//	*/
//	
//	// is-a : Manager �� Employee
//	class Employee {};
//	class Manager : public Employee {};	// ����
//	
//	// has-a : �ڵ����� �μ�ǰ��
//	class Wheel {};
//	class Engine {};
//	class Brake {};
//	class Car
//	{
//		Wheel wheel;
//		Engine engine;
//		Brake brake;
//	};	// ����

// �������̵�

//	#include <iostream>
//	#include <string>
//	
//	class Base
//	{
//	public:
//		Base() : s("���") { std::cout << "��� Ŭ����" << std::endl; }
//		
//		void what() { std::cout << s << std::endl; }
//	private:
//		std::string s;
//	};
//	
//	class Derived : public Base
//	{
//	public:
//		Derived() : s("�Ļ�"), Base() { std::cout << "�Ļ� Ŭ����" << std::endl; }
//	
//		void what() { std::cout << s << std::endl; }
//	private:
//		std::string s;
//	};
//	
//	int main()
//	{
//		{
//			std::cout << " === ��� Ŭ���� ���� ===" << std::endl;
//			Base p;
//	
//			p.what();
//	
//			std::cout << " === �Ļ� Ŭ���� ���� === " << std::endl;
//			Derived c;
//	
//			c.what();
//	
//			/*
//				output
//				 === ��� Ŭ���� ���� ===
//				��� Ŭ����
//				���
//				 === �Ļ� Ŭ���� ���� ===
//				��� Ŭ����
//				�Ļ� Ŭ����
//				�Ļ�
//			*/
//		}
//	
//		// ��ĳ����
//		{
//			Base p;
//			Derived c;
//	
//			std::cout << " === ������ ���� === " << std::endl;
//			Base* p_c = &c;
//			p_c->what();
//	
//			/*
//				output
//				��� Ŭ����
//				��� Ŭ����
//				�Ļ� Ŭ����
//				 === ������ ���� ===
//				���
//			*/
//		}
//	
//		/*
//			- �� ĳ����
//				- ���� �������� Base�� �����Ϳ� Derived�� �ּҸ� �־��ִ� �κ��� ���� ���� �۵���
//					- Derived�� Base�� ��ӹް� ���� -> Derived is a Base
//					- �׷��� ��ü c�� Base �̱⵵ �ϹǷ� Base �����Ͱ� ����ų �� ����
//					- ���� ���̰� �غ���...
//						->
//							Derived c -> [string s][Base()][what()] + [string s][Derived()][what()]
//										 --------------------------> �� �̸�ŭ�� Base* �� ����ų �� ����
//					- �̶� p_c->what()�� �����Ű�� "���"�� ��µ�
//						-> p_c�� Base�� �������̹Ƿ� Base::What()�� ����Ǵ°�
//					-> �̷��� �Ļ� Ŭ�������� ��� Ŭ������ ĳ���� �ϴ°��� "�� ĳ����" �̶�� ��
//		*/
//	
//		// �ٿ� ĳ����
//		{
//			Base p;
//			Derived c;
//	
//			std::cout << " === ������ ���� === " << std::endl;
//			// ��� Ŭ������ �Ļ� Ŭ������ ĳ���� �����ұ�?
//			//	Derived* p_p = &p;	// C2440: '�ʱ�ȭ ��': 'Base *'���� 'Derived *'(��)�� ��ȯ�� �� �����ϴ�
//			//	p_p->what();
//			// �ȵ�
//	
//			// ��ĳ���� �ϰ� �ٽ� ���� Ŭ������ �������°� �����ұ�?
//			//	Base* p_p = &c;
//			//	Derived* p_c = p_p;	// C2440: '�ʱ�ȭ ��': 'Base *'���� 'Derived *'(��)�� ��ȯ�� �� �����ϴ�
//			//	p_c->what();
//			// �ȵ�
//	
//			// ������ �ǵ��� �ϸ� �ɱ�?
//			//	Base* p_p = &p;
//			//	Derived* p_c = static_cast<Derived*>(p_p);
//			//	p_c->what();
//			// ������ ��Ÿ�� ������ ��. ����� �ƹ��͵� ��µ��� �ʰ� �׳� �Ѿ
//	
//			// dynamic_cast�� �̿��غ���: ��� ���迡 �ִ� �� �����͵� ���� ĳ����
//			//	Base* p_p = &p;
//			//	Derived* p_c = dynamic_cast<Derived*>(p_p);	// C2683: 'dynamic_cast': 'Base'��(��) ���� ������ �ƴմϴ�.
//	
//			// �̰͸� �����ϰ� ������
//			Base* p_p = &c;
//			Derived* p_c = static_cast<Derived*>(p_p);
//			p_c->what();
//		}
//	
//		/*
//			- ���� �ٿ�ĳ���õ��� �� �ȵɱ�
//				- ���� ���̰� �׷����� ����
//					Base ->  [string s][Base()][what()]
//					Derived ->  [string s][Base()][what()] + [string s][Derived()][what()]
//					�̷������� �����Ǿ� �ִµ�
//					Base ->  [string s][Base()][what()] / [string s][Derived()][what()] <- �̺κ��� ���� 
//							 ----------------------------------------------------------> Derived* �� ����Ű�� �κ��� �̸�ŭ�ε� Base���� �����Ƿ� ���� �۵����� �ʴ°�
//				- �ٿ�ĳ������ ��Ӱ��踦 �� �ľ��ϰ� ����ؾ���
//		
//		*/
//		return 0;
//	
//	}

// virtual, override

//	#include <iostream>
//	
//	class Base {
//	
//	public:
//		Base() { std::cout << "��� Ŭ����" << std::endl; }
//		
//		virtual void what() { std::cout << "��� Ŭ������ what()" << std::endl; }
//	
//		virtual void incorrect() { std::cout << "��� Ŭ����" << std::endl; }
//	};
//	
//	class Derived : public Base
//	{
//	
//	public:
//		Derived() : Base() { std::cout << "�Ļ� Ŭ����" << std::endl; }
//	
//		virtual void what() override { std::cout << "�Ļ� Ŭ������ what()" << std::endl; }
//	
//		//	virtual void incorrect() const { std::cout << "�Ļ� Ŭ����" << std::endl; }	// �������̵� �Ұ� -> �Լ��� ���� �ٸ��Ƿ� �Ͻ������� �������̵� ���� ����
//		//	virtual void incorrect() const override { std::cout << "�Ļ� Ŭ����" << std::endl; }	// �������̵� �Ұ� -> �Լ��� ���� �ٸ��Ƿ� ����ϴ��� �������̵� �� �� ����
//		virtual void incorrect() override { std::cout << "�Ļ� Ŭ����" << std::endl; }	// �������̵� ����
//	
//	};
//	
//	int main()
//	{
//		Base p;
//		Derived c;
//	
//		Base* p_c = &c;
//		Base* p_p = &p;
//	
//		std::cout << " == what() ==" << std::endl;
//		std::cout << " == ���� ��ü�� Base ==" << std::endl;
//		p_p->what();
//	
//		std::cout << " == ���� ��ü�� Derived == " << std::endl;
//		p_c->what();
//		
//		//	std::cout << " == incorrect() ==" << std::endl;
//		//	std::cout << " == ���� ��ü�� Base ==" << std::endl;
//		//	p_p->incorrect();
//		//	
//		//	std::cout << " == ���� ��ü�� Derived == " << std::endl;
//		//	p_c->incorrect();
//	
//		/*
//			output
//			��� Ŭ����
//			��� Ŭ����
//			�Ļ� Ŭ����
//			 == ���� ��ü�� Base ==
//			��� Ŭ������ what()
//			 == ���� ��ü�� Derived ==
//			�Ļ� Ŭ������ what()
//		*/
//	
//		/*
//			- virtual
//				- �� �ڵ忡�� p_c�� Base* �ε� p_c->what()�� ����� �Ļ� Ŭ������ what()�� ȣ���
//					- ��ġ ��ĳ���õ� p_c�� ���� ���� Ŭ�������� �ƴ°�ó�� ������ �Լ��� ȣ���� �ذ�
//						-> virtual Ű���� ���п� ������ ��
//				- virtual : The virtual specifier specifies that a non-static member function is virtual and supports dynamic dispatch.(cppreference)
//							virtual �����ڴ� ������ ��� �Լ��� ���� �Լ��̰� ���� ����ġ�� �����ϵ��� ��.
//					-> ���� ���ϸ� "�����Ͻÿ� � �Լ��� ����� �� �������� �ʰ� ��Ÿ�� �ÿ� ����������" �ϴ� Ű������
//					++ ����� �ڵ忡���� �̰��� ���� ���ε�(dynamic binding)�̶�� �θ��ٰ� ������ �̴� �Լ��Ӹ� �ƴ϶� ����, �޼���, �ٸ� �ĺ��� �� ��ü�� �ƿ츣�� �����ΰ����� ����
//					++ �Լ��� ���� ���� ���ε��� ���� ����ġ(dynamic dispatch)��� �θ��ٰ� ��
//				- �����Լ� : Virtual functions are member functions whose behavior can be overridden in derived classes.
//							 ���� �Լ��� �Ļ� Ŭ������ �Լ��� ������ �������̵� �� �� �ִ� ��� �Լ�
//				- �Ļ� Ŭ������ ��� Ŭ������ �Լ��� �������̵� �Ϸ��� �� �Լ��� ���� ��Ȯ�� ���ƾ���. 
//	
//			- override
//				- C++ 11���� ���Ե� Ű����� �����Լ��� �������̵带 ��������� ��Ÿ�� �� �ֵ��� ��
//					- �̸� ���� �Ǽ��� �������̵� ���� �ʴ� ��츦 ���� �� ����
//				- ���� ������ incorrect() �Լ��� ����...
//					- Base()������ �Ϲ� �Լ�, Derived()������ ����Լ���
//					- �� �Լ��� ���� �ٸ��Ƿ� override�� ������� ������ �������̵� ���� �ʰ� �� �� Base::incorrect()�� ȣ����
//					- �׷��� Derived�� incorrect()�� override�� ����ϸ� ������ �߻� -> �� �Լ��� ���� �ٸ��Ƿ� �������̵� �� �� ����
//					- ���������� �������̵� �ϱ� ���ؼ��� const�� ���ּ� �Ϲ����� �Լ��� ������ ��.
//		*/
//		return 0;
//	}

// ���� �Լ��� �̿��� Manager, Employee, EmployeeList �� ���� ++ ������

//	// �������� ���ʿ��� �κе��� virtual Ű���带 �����Ͽ� �ذ���
//	
//	#include <iostream>
//	#include <string>
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
//		virtual void print_info() { std::cout << name << " (" << position << " , " << age << ") ==> " << calculate_pay() << "����" << std::endl; }
//		virtual int calculate_pay() { return 200 + rank * 50; }
//	
//	
//	protected:	// ��ӹ��� Ŭ�����鿡���� ������ �����ؾ��ϹǷ� private�� �ƴ� protected�� �Ǿ�� ��
//		std::string name;
//		int age;
//	
//		std::string position;	// ��å(�̸�)
//		int rank;	// ���� (���� Ŭ ���� ���� ����)
//	
//	};
//	
//	class Manager : public Employee
//	{
//	public:
//		Manager(std::string name, int age, std::string position, int rank, int year_of_service)
//			:year_of_service(year_of_service), Employee(name, age, position, rank) {}
//	
//		Manager(const Manager& m)
//			: Employee(m.name, m.age, m.position, m.rank)
//		{
//			year_of_service = m.year_of_service;
//		}
//	
//		Manager() : Employee() {}
//	
//		int calculate_pay() override { return 200 + rank * 50 + 5 * year_of_service; }
//	
//		void print_info() override
//		{
//			std::cout << name << " (" << position << " , " << age << ", "
//				<< year_of_service << "����) ==> " << calculate_pay() << "����"
//				<< std::endl;
//		}
//	
//	private:
//		int year_of_service;
//	
//	};
//	
//	class EmployeeList
//	{
//	public:
//		EmployeeList(int alloc_employee) : alloc_employee(alloc_employee)
//		{
//			employee_list = new Employee * [alloc_employee];
//			current_employee = 0;
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
//		int current_employee_num() { return current_employee; }
//	
//		void print_employee_info() {
//			int total_pay = 0;
//			for (int i = 0; i < current_employee; i++)
//			{
//				employee_list[i]->print_info();
//				total_pay += employee_list[i]->calculate_pay();
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
//	
//			delete[] employee_list;
//		}
//	private:
//		int alloc_employee;			// �Ҵ��� �� ���� ��
//	
//		int current_employee;		// ���� ���� ��
//	
//		Employee** employee_list;	// ���� ������
//	};
//	
//	int main()
//	{
//		EmployeeList emp_list(10);
//		emp_list.add_employee(new Employee("��ȫö", 34, "����", 1));
//		emp_list.add_employee(new Employee("����", 34, "����", 1));
//		emp_list.add_employee(new Manager("���缮", 41, "����", 7, 12));
//		emp_list.add_employee(new Manager("������", 43, "����", 4, 15));
//		emp_list.add_employee(new Manager("�ڸ��", 43, "����", 5, 13));
//		emp_list.add_employee(new Employee("������", 36, "�븮", 2));
//		emp_list.add_employee(new Employee("��", 36, "����", -2));
//		emp_list.print_employee_info();
//	
//		/*
//			output
//			��ȫö (���� , 34) ==> 250����
//			���� (���� , 34) ==> 250����
//			���缮 (���� , 41, 12����) ==> 610����
//			������ (���� , 43, 15����) ==> 475����
//			�ڸ�� (���� , 43, 13����) ==> 515����
//			������ (�븮 , 36) ==> 300����
//			�� (���� , 36) ==> 100����
//			�� ��� : 2500����
//	
//		*/
//	
//		/*
//			- ������(polymorphism)
//				- employee_list ���� ������ ��ü�� Employee�̳� Manager�̳Ŀ� ���� �ٸ��� �����ϰ� ����
//					-> ��ó�� �ϳ��� �޼ҵ带 ȣ���Ͽ������� �ұ��ϰ� �������� �ٸ� �۾��� �ϴ� ���� ������(polymorphism)�̶�� ��
//				- ���� Week1�� oop2_class_info.txt�� �ѹ� ������ �� ����
//	
//						������(Polymorphism) == �������
//						- �ϳ��� ��ü�� ���� ���� ���¸� ���� �� �ִ°�
//						- �������̵�(Overriding)
//							- �θ� Ŭ������ ���ǵǾ� �ִ� �޼��带 �ڽ� Ŭ�������� �������Ͽ� ����ϴ°�
//						- �����ε�(Overloading)
//							- ���� �̸��� ���� �޼��带 ���ڰ��� ������ ������ �ٸ��� �Ͽ� �ٸ� ����� �����ϵ��� �����ϴ°�
//	
//				- �������� ��ü���� ���α׷��� 3����� �ϳ��� �ſ� �����ϰ� ����
//		*/
//		return 0;
//	}