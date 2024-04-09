
/*
	04.08 is-a와 has-a 관계, 오버라이딩, virtual과 가상함수, 다형성
*/

// is-a, has-a 관계

//	/*
//		- is-a / has-a 관계
//			- 객체의 추상화 단계에서 어떤 경우에 상속을 이용할지를 결정할 수 있는 방법
//			- 당연히 언어차원에서 지원하는 기능이 아니고 사용자가 코딩하면서 직접 생각하여 판단하는 것임
//			- is-a : ~ 는 ~ 다! -> 상속을 이용
//				- Week6의 Manager와 Employee관계를 생각해보면
//					- Manager는 Employee의 모든 기능을 포함한다
//					- Manager는 Employee의 기능을 모두 수행하므로 Manager를 Employee라고 칭해도 무방하다
//					- 즉 모든 Manager는 Employee이다
//					- Manager "is a" Employee -> 상속
//				- 당연히 이를 뒤바꾸면(Employee is a Manager)는 말이 안되므로 상속관계가 명확하게 구분됨
//				- 상속을 통해 클래스가 파생되면 파생될수록 좀 더 특수화(구체화, specialize)가 되는 것을 알 수 있음
//					-> Manager는 Employee이면서 좀 더 구체적인 부류임. 실제로든 프로그램에서든 마찬가지
//				- 반대로 파생된 클래스가 기반 클래스로 거슬러 올라갈수록 좀 더 일반화(generalize)됨
//					-> Manager는 일반적으로 Employee 이고 실제로도 마찬가지
//				- 상속으로 관계된 클래스들은 위와같은 특징들을 갖고 실제 코드 작성시 추상화하는 과정에서 도움을 줄 수 있음
//			- has-a: ~ 는 ~ 를 가지고 있다 -> 상속을 이용하지 않음
//				- 자동차를 생각해보면
//					- 자동차는 바퀴를 가지고 있음
//					- 자동차는 엔진을 가지고 있음
//					- 자동차는 브레이크를 가지고 있음
//					- Car is a Wheel/Engine/Brake라고 말할 수 없음
//						-> Car has a Wheel/Engine/Brake가 더 적합
//				- 이런 경우에는 상속이 아닌 클래스의 멤버로 가지고있는것이 맞음
//	*/
//	
//	// is-a : Manager 와 Employee
//	class Employee {};
//	class Manager : public Employee {};	// 적합
//	
//	// has-a : 자동차와 부속품들
//	class Wheel {};
//	class Engine {};
//	class Brake {};
//	class Car
//	{
//		Wheel wheel;
//		Engine engine;
//		Brake brake;
//	};	// 적합

// 오버라이딩

//	#include <iostream>
//	#include <string>
//	
//	class Base
//	{
//	public:
//		Base() : s("기반") { std::cout << "기반 클래스" << std::endl; }
//		
//		void what() { std::cout << s << std::endl; }
//	private:
//		std::string s;
//	};
//	
//	class Derived : public Base
//	{
//	public:
//		Derived() : s("파생"), Base() { std::cout << "파생 클래스" << std::endl; }
//	
//		void what() { std::cout << s << std::endl; }
//	private:
//		std::string s;
//	};
//	
//	int main()
//	{
//		{
//			std::cout << " === 기반 클래스 생성 ===" << std::endl;
//			Base p;
//	
//			p.what();
//	
//			std::cout << " === 파생 클래스 생성 === " << std::endl;
//			Derived c;
//	
//			c.what();
//	
//			/*
//				output
//				 === 기반 클래스 생성 ===
//				기반 클래스
//				기반
//				 === 파생 클래스 생성 ===
//				기반 클래스
//				파생 클래스
//				파생
//			*/
//		}
//	
//		// 업캐스팅
//		{
//			Base p;
//			Derived c;
//	
//			std::cout << " === 포인터 버전 === " << std::endl;
//			Base* p_c = &c;
//			p_c->what();
//	
//			/*
//				output
//				기반 클래스
//				기반 클래스
//				파생 클래스
//				 === 포인터 버전 ===
//				기반
//			*/
//		}
//	
//		/*
//			- 업 캐스팅
//				- 위의 예제에서 Base의 포인터에 Derived의 주소를 넣어주는 부분이 문제 없이 작동됨
//					- Derived는 Base를 상속받고 있음 -> Derived is a Base
//					- 그러면 객체 c도 Base 이기도 하므로 Base 포인터가 가리킬 수 잇음
//					- 눈에 보이게 해보면...
//						->
//							Derived c -> [string s][Base()][what()] + [string s][Derived()][what()]
//										 --------------------------> 딱 이만큼은 Base* 가 가리킬 수 있음
//					- 이때 p_c->what()을 실행시키면 "기반"이 출력됨
//						-> p_c는 Base의 포인터이므로 Base::What()이 실행되는것
//					-> 이렇게 파생 클래스에서 기반 클래스로 캐스팅 하는것을 "업 캐스팅" 이라고 함
//		*/
//	
//		// 다운 캐스팅
//		{
//			Base p;
//			Derived c;
//	
//			std::cout << " === 포인터 버전 === " << std::endl;
//			// 기반 클래스를 파생 클래스로 캐스팅 가능할까?
//			//	Derived* p_p = &p;	// C2440: '초기화 중': 'Base *'에서 'Derived *'(으)로 변환할 수 없습니다
//			//	p_p->what();
//			// 안됨
//	
//			// 업캐스팅 하고 다시 원래 클래스로 돌려놓는건 가능할까?
//			//	Base* p_p = &c;
//			//	Derived* p_c = p_p;	// C2440: '초기화 중': 'Base *'에서 'Derived *'(으)로 변환할 수 없습니다
//			//	p_c->what();
//			// 안됨
//	
//			// 강제로 되도록 하면 될까?
//			//	Base* p_p = &p;
//			//	Derived* p_c = static_cast<Derived*>(p_p);
//			//	p_c->what();
//			// 원래는 런타임 오류가 뜸. 현재는 아무것도 출력되지 않고 그냥 넘어감
//	
//			// dynamic_cast를 이용해보자: 상속 관계에 있는 두 포인터들 간의 캐스팅
//			//	Base* p_p = &p;
//			//	Derived* p_c = dynamic_cast<Derived*>(p_p);	// C2683: 'dynamic_cast': 'Base'은(는) 다형 형식이 아닙니다.
//	
//			// 이것만 유일하게 가능함
//			Base* p_p = &c;
//			Derived* p_c = static_cast<Derived*>(p_p);
//			p_c->what();
//		}
//	
//		/*
//			- 위의 다운캐스팅들은 왜 안될까
//				- 눈에 보이게 그려보면 쉬움
//					Base ->  [string s][Base()][what()]
//					Derived ->  [string s][Base()][what()] + [string s][Derived()][what()]
//					이런식으로 구성되어 있는데
//					Base ->  [string s][Base()][what()] / [string s][Derived()][what()] <- 이부분은 없음 
//							 ----------------------------------------------------------> Derived* 가 가리키는 부분은 이만큼인데 Base에는 없으므로 정상 작동하지 않는것
//				- 다운캐스팅은 상속관계를 잘 파악하고 사용해야함
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
//		Base() { std::cout << "기반 클래스" << std::endl; }
//		
//		virtual void what() { std::cout << "기반 클래스의 what()" << std::endl; }
//	
//		virtual void incorrect() { std::cout << "기반 클래스" << std::endl; }
//	};
//	
//	class Derived : public Base
//	{
//	
//	public:
//		Derived() : Base() { std::cout << "파생 클래스" << std::endl; }
//	
//		virtual void what() override { std::cout << "파생 클래스의 what()" << std::endl; }
//	
//		//	virtual void incorrect() const { std::cout << "파생 클래스" << std::endl; }	// 오버라이드 불가 -> 함수의 꼴이 다르므로 암시적으로 오버라이드 되지 않음
//		//	virtual void incorrect() const override { std::cout << "파생 클래스" << std::endl; }	// 오버라이드 불가 -> 함수의 꼴이 다르므로 명시하더라도 오버라이드 될 수 없음
//		virtual void incorrect() override { std::cout << "파생 클래스" << std::endl; }	// 오버라이드 가능
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
//		std::cout << " == 실제 객체는 Base ==" << std::endl;
//		p_p->what();
//	
//		std::cout << " == 실제 객체는 Derived == " << std::endl;
//		p_c->what();
//		
//		//	std::cout << " == incorrect() ==" << std::endl;
//		//	std::cout << " == 실제 객체는 Base ==" << std::endl;
//		//	p_p->incorrect();
//		//	
//		//	std::cout << " == 실제 객체는 Derived == " << std::endl;
//		//	p_c->incorrect();
//	
//		/*
//			output
//			기반 클래스
//			기반 클래스
//			파생 클래스
//			 == 실제 객체는 Base ==
//			기반 클래스의 what()
//			 == 실제 객체는 Derived ==
//			파생 클래스의 what()
//		*/
//	
//		/*
//			- virtual
//				- 위 코드에서 p_c는 Base* 인데 p_c->what()의 결과로 파생 클래스의 what()이 호출됨
//					- 마치 업캐스팅된 p_c가 원래 무슨 클래스인지 아는것처럼 적절한 함수를 호출해 준것
//						-> virtual 키워드 덕분에 가능한 일
//				- virtual : The virtual specifier specifies that a non-static member function is virtual and supports dynamic dispatch.(cppreference)
//							virtual 지정자는 비정적 멤버 함수가 가상 함수이고 동적 디스패치를 지원하도록 함.
//					-> 쉽게 말하면 "컴파일시에 어떤 함수가 실행될 지 정해지지 않고 런타임 시에 정해지도록" 하는 키워드임
//					++ 모두의 코드에서는 이것을 동적 바인딩(dynamic binding)이라고 부른다고 하지만 이는 함수뿐만 아니라 변수, 메서드, 다른 식별자 등 전체를 아우르는 정의인것으로 보임
//					++ 함수에 대한 동적 바인딩은 동적 디스패치(dynamic dispatch)라고 부른다고 함
//				- 가상함수 : Virtual functions are member functions whose behavior can be overridden in derived classes.
//							 가상 함수는 파생 클래스가 함수의 동작을 오버라이드 할 수 있는 멤버 함수
//				- 파생 클래스가 기반 클래스의 함수를 오버라이드 하려면 두 함수의 꼴이 정확히 같아야함. 
//	
//			- override
//				- C++ 11에서 도입된 키워드로 가상함수의 오버라이드를 명시적으로 나타낼 수 있도록 함
//					- 이를 통해 실수로 오버라이드 하지 않는 경우를 막을 수 있음
//				- 위의 예제의 incorrect() 함수를 보면...
//					- Base()에서는 일반 함수, Derived()에서는 상수함수임
//					- 두 함수의 꼴이 다르므로 override를 명시하지 않으면 오버라이드 되지 않고 둘 다 Base::incorrect()를 호출함
//					- 그런데 Derived의 incorrect()에 override를 명시하면 오류가 발생 -> 두 함수의 꼴이 다르므로 오버라이드 할 수 없음
//					- 정상적으로 오버라이드 하기 위해서는 const를 없애서 일반적인 함수로 만들어야 함.
//		*/
//		return 0;
//	}

// 가상 함수를 이용한 Manager, Employee, EmployeeList 의 수정 ++ 다형성

//	// 이전까지 불필요한 부분들은 virtual 키워드를 도입하여 해결함
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
//		virtual void print_info() { std::cout << name << " (" << position << " , " << age << ") ==> " << calculate_pay() << "만원" << std::endl; }
//		virtual int calculate_pay() { return 200 + rank * 50; }
//	
//	
//	protected:	// 상속받은 클래스들에서도 접근이 가능해야하므로 private가 아닌 protected가 되어야 함
//		std::string name;
//		int age;
//	
//		std::string position;	// 직책(이름)
//		int rank;	// 순위 (값이 클 수록 높은 순위)
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
//				<< year_of_service << "년차) ==> " << calculate_pay() << "만원"
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
//				사실 current_employee 보다 alloc_employee 가 더 많아지는 경우 반드시 재할당을 해야 하지만,
//				여기서는 최대한 단순하게 생각해서 alloc_employee 는 언제나 current_employee 보다 크다고 생각한다.
//				즉, 할당된 크기는 현재 총 직원수 보다 많음
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
//			std::cout << "총 비용 : " << total_pay << "만원 " << std::endl;
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
//		int alloc_employee;			// 할당한 총 직원 수
//	
//		int current_employee;		// 현재 직원 수
//	
//		Employee** employee_list;	// 직원 데이터
//	};
//	
//	int main()
//	{
//		EmployeeList emp_list(10);
//		emp_list.add_employee(new Employee("노홍철", 34, "평사원", 1));
//		emp_list.add_employee(new Employee("하하", 34, "평사원", 1));
//		emp_list.add_employee(new Manager("유재석", 41, "부장", 7, 12));
//		emp_list.add_employee(new Manager("정준하", 43, "과장", 4, 15));
//		emp_list.add_employee(new Manager("박명수", 43, "차장", 5, 13));
//		emp_list.add_employee(new Employee("정형돈", 36, "대리", 2));
//		emp_list.add_employee(new Employee("길", 36, "인턴", -2));
//		emp_list.print_employee_info();
//	
//		/*
//			output
//			노홍철 (평사원 , 34) ==> 250만원
//			하하 (평사원 , 34) ==> 250만원
//			유재석 (부장 , 41, 12년차) ==> 610만원
//			정준하 (과장 , 43, 15년차) ==> 475만원
//			박명수 (차장 , 43, 13년차) ==> 515만원
//			정형돈 (대리 , 36) ==> 300만원
//			길 (인턴 , 36) ==> 100만원
//			총 비용 : 2500만원
//	
//		*/
//	
//		/*
//			- 다형성(polymorphism)
//				- employee_list 에서 각각의 객체가 Employee이냐 Manager이냐에 따라 다르게 동작하고 있음
//					-> 이처럼 하나의 메소드를 호출하였음에도 불구하고 여러가지 다른 작업을 하는 것을 다형성(polymorphism)이라고 함
//				- 이전 Week1의 oop2_class_info.txt에 한번 설명한 적 있음
//	
//						다형성(Polymorphism) == 사용편의
//						- 하나의 객체가 여러 가지 형태를 가질 수 있는것
//						- 오버라이딩(Overriding)
//							- 부모 클래스에 정의되어 있는 메서드를 자식 클래스에서 재정의하여 사용하는것
//						- 오버로딩(Overloading)
//							- 같은 이름을 가진 메서드를 인자값의 종류나 개수를 다르게 하여 다른 기능을 구현하도록 정의하는것
//	
//				- 다형성은 객체지향 프로그램의 3요소중 하나로 매우 유용하게 사용됨
//		*/
//		return 0;
//	}