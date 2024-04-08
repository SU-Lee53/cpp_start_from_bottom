/*

	04.05 ~ 06 std::string, 상속, 오버라이딩, protected

*/

// 표준 string 클래스 std::string

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
//		//	std::cout << s << " 의 길이 : " << s.length() << std::endl;
//		//	std::cout << s << " 뒤에 " << t << " 를 붙이면 : " << s + t << std::endl;
//		//	
//		//	if (s == s2)
//		//		std::cout << s << " 와 " << s2 << " 는 같다 " << std::endl;
//		//	if (s != t)
//		//		std::cout << s << " 와 " << t << " 는 다르다 " << std::endl;
//	
//		/*
//			output
//			abc 의 길이 : 3
//			abc 뒤에 def 를 붙이면 : abcdef
//			abc 와 abc 는 같다
//			abc 와 def 는 다르다
//		*/
//	
//	
//		/*
//			- std::string
//				- C++의 문자열 클래스.
//				- 기본적으로 <string> 헤더안에는 basic_string과 char_traits 가 구현되어있음
//					- char_traits: 기본적인 문자/문자열 연산을 제공
//					- basic_string: 가변적이고 다양한 문자열 조작 기능을 제공
//					-> 기본적으로 위처럼 std::string을 생성하면 std::basic_string이 생성되고 헤더안에 typedef로 되어있음
//				- 위처럼 기본적인 std::string은 std::basic_string<char>을 생성하고 다른 종류의 문자열도 지원함(기본 char는 ANSI)
//					- std::wstring		->		std::basic_string<wchar_t>(유니코드)
//					- std::u8string		->		std::basic_string<char8_t>
//					- std::u16string	->		std::basic_string<char16_t>
//					- std::u32string	->		std::basic_string<char32_t>
//					- 전부 같은 템플릿으로 되어있어 모든 멤버 함수들은 동일함
//					- 직접 해보니까 TCHAR등의 인코딩도 만들수 있음
//					- 추가적으로 C++의 메모리 할당자인 PMR을 이용한 std::pmr::string 들이 있으며 이부분은 일단 넘어감
//				- 기존의 strcmp, strlen, strcat 등을 이용해야했던 C의 문자열과 다르게 기본적인 기능들이 멤버 함수로 제공됨 https://en.cppreference.com/w/cpp/string/basic_string
//					- length(), insert(), erase(), replace() 등등의 다양한 멤버 함수들이 기본 제공됨
//					- 특히 strcmp, strcat 등의 기능을 연산자로 가능하다는 점이 눈에 띄는 부분이라고 생각됨(비교, 대소비교 둘다 연산자로 가능)
//					- 전체 기능들은 후에 STL 공부할때 cppreference를 파면서 함께 정리
//		*/
//	
//		// soen.kr에 설명된 다양한 string 생성자들(이거 말고도 새로운 표준들에서 더 많이 추가됨)
//	
//		std::string s1("test");								// string(const char *s) 널 종료 문자열로부터 생성하는 변환 생성자
//		std::string s2(s1);									// string(const string& str, int pos = 0, int num = npos) 복사 생성자
//		std::string s3;										// string() 기본 생성자
//		std::string s4(32, 'S');							// string(size_t n, char c) c를 n개 채움	
//		std::string s5("very nice day", 8);					// string(const cchar* s, size_t n) 널 종료 문자열로부터 생성하되 n길이 확보
//		const char* str = "abcdefghijllmnopqrstuvwxyz";		
//		std::string s6(str + 5, str + 10);					// template<It> string(It begin, It end) begin ~ end 사이의 문자로 구성된 문자열 생성
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

// 상속이 없을때... - 사원 관리 프로그램

//	#include <iostream>
//	#include <string>
//	
//	/*
//		- 사원관리 프로그램을 만들어보자
//			- 목적 : 사원들의 월급을 계산해서 한달에 총 얼마나 되는 돈을 월급으로 지출해야 하는지 알려주는 프로그램
//			- 필요한 것
//				- 사원들의 정보
//					- 이름
//					- 나이
//					- 직책
//					- 직책의 순위(평사원 : 1, 대리 : 2 ...)
//					-> 클래스로 만들어서 관리(Employee)
//				- 사원 클래스를 관리할 리스트(EmployeeList)
//			- Manager의 추가
//				- Manager : 차장 이상급들은 근속년수를 포함시켜 월급에 추가하기 위한 Employee와는 구분되는 클래스
//			- 새로 만드는 Manager가 Employee와 많은 부분을 공유하지만 이름만 바꿔서 처음부터 다시 작성하는것이 매우매우 귀찮음
//				-> 이때 상속을 이용
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
//		void print_info() { std::cout << name << " (" << position << " , " << age << ") ==> " << calculate_pay() << "만원" << std::endl; }
//		int calculate_pay() { return 200 + rank * 50; }
//	
//	
//	private:
//		std::string name;
//		int age;
//	
//		std::string position;	// 직책(이름)
//		int rank;	// 순위 (값이 클 수록 높은 순위)
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
//		// 디폴트
//		Manager() {}
//	
//		void print_info() { std::cout << name << " (" << position << " , " << age << " , " <<  year_of_service << "년차) ==> " << calculate_pay() << "만원" << std::endl; }
//		int calculate_pay() { return 200 + rank * 50 + 5 * year_of_service; }
//	
//	
//	private:
//		std::string name;
//		int age;
//	
//		std::string position;	// 직책(이름)
//		int rank;	// 순위 (값이 클 수록 높은 순위)
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
//				사실 current_employee 보다 alloc_employee 가 더 많아지는 경우 반드시 재할당을 해야 하지만,
//				여기서는 최대한 단순하게 생각해서 alloc_employee 는 언제나 current_employee 보다 크다고 생각한다.
//				즉, 할당된 크기는 현재 총 직원수 보다 많음
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
//			std::cout << "총 비용 : " << total_pay << "만원 " << std::endl;
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
//		int alloc_employee;			// 할당한 총 직원 수
//	
//		int current_employee;		// 현재 직원 수
//		int current_manager;		// 현재 매니저 수
//	
//		Employee** employee_list;	// 직원 데이터
//		Manager** manager_list;		// 매니저 데이터
//	};
//	
//	int main()
//	{
//		EmployeeList emp_list(10);
//		emp_list.add_employee(new Employee("노홍철", 34, "평사원", 1));
//		emp_list.add_employee(new Employee("하하", 34, "평사원", 1));
//	
//		emp_list.add_manager(new Manager("유재석", 41, "부장", 7, 12));
//		emp_list.add_manager(new Manager("정준하", 43, "과장", 4, 15));
//		emp_list.add_manager(new Manager("박명수", 43, "차장", 5, 13));
//		emp_list.add_employee(new Employee("정형돈", 36, "대리", 2));
//		emp_list.add_employee(new Employee("길", 36, "인턴", -2));
//	
//		emp_list.print_employee_info();
//	
//		return 0;
//	
//		/*
//			output
//			노홍철 (평사원 , 34) ==> 250만원
//			하하 (평사원 , 34) ==> 250만원
//			정형돈 (대리 , 36) ==> 300만원
//			길 (인턴 , 36) ==> 100만원
//			유재석 (부장 , 41 , 12년차) ==> 610만원
//			정준하 (과장 , 43 , 15년차) ==> 475만원
//			박명수 (차장 , 43 , 13년차) ==> 515만원
//			총 비용 : 2500만원
//		
//		*/
//	}

// 상속(inheritance)

//	#include <iostream>
//	#include <string>
//	
//	class Base
//	{
//	public:
//		Base() : parent_string("기반") { std::cout << "기반 클래스" << std::endl; }
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
//		Derived() : Base(), child_string("파생") // 초기화 리스트에서 기반 클래스의 생성자를 먼저 호출. 명시적으로 호출하지 않으면 디폴트 생성자 호출됨.
//		{ 
//			std::cout << "파생 클래스" << std::endl;
//	
//			// Base 에서 what()을 물려 받았으므로 Derived 에서 호출 가능
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
//		std::cout << " === 기반 클래스 생성 ===" << std::endl;
//		Base p;
//		std::cout << p.parent_string << std::endl;
//	
//		std::cout << " === 파생 클래스 생성 === " << std::endl;
//		Derived c;
//		std::cout << c.parent_string << std::endl;	// protected / private 상속을 받으면 아래의 오류가 발생하며 컴파일 오류가 남
//		// C2247: 'Base::parent_string'에 액세스할 수 없습니다. 이는 'Derived'이(가) 'private'을(를) 사용하여 'Base' 에서 상속하기 때문입니다
//	
//	
//		/*
//			- 상속(inheritance) : 다른 클래스의 정보를 물려 받아서 사용할 수 있도록 함
//				- 선언 -> class (파생 클래스) : (접근 지시자) (기반 클래스)
//				- 부모-자식 클래스라고도 하는데 C++은 여러개의 클래스에서 상속받을 수 있으므로 기반-파생 클래스가 더 적절함(cppreference도 Base-Derived 로 작성됨)
//				- 위의 Derived는 Base를 public으로 상속받고 있음
//					- 내부 구조
//						- Base : [string s][Base()][what()]
//						- Derived : [string s][Base()][what()] + [string s][Derived()]
//						-> 이렇게 Derived 클래스는 Base 클래스의 코드가 그래도 들어가있는 것처럼 구성됨
//					- 초기화 리스트에서 기반 클래스의 생성자를 먼저 호출해주고있음. 만약에 명시적으로 해주지 않으면 디폴트 생성자가 호출됨.
//						-> 파생 클래스가 생성되기 전에 먼저 기반 클래스가 생성됨
//						-> 직접 생성자를 지우고 실행해보면 똑같이 기반 클래스가 출력됨
//					- Derived 에서 Base의 what()의 호출
//						- Base의 모든 정보를 상속받았기 때문에 Derived에서도 what()을 호출 가능
//						- 그런데 왜 "파생" 이 아닌 "기반"이 출력될까
//							-> what() 함수는 Base에 정의되어있기 때문에 Derived::s가 아닌 Base::s가 출력되는 것
//							-> Derived 에서도 what() 함수를 만들면 "파생"이 출력됨
//								-> !!! 다른 클래스에 정의되어 있는 함수는 서로 각각 다른 함수로 취급되고 이를 오버라이딩(overriding)이라고 함 !!!
//					- 상속의 접근 지시자
//						- public: 파생 클래스 입장에서 기반 클래스의 접근 지시자들에 영향 없이 그대로 작동됨
//						- protected: 파생 클래스 입장에서 기반 클래스의 public이 protected 로 변함
//						- private: 파생 클래스 입장에서 기반 클래스의 모든 접근 지시자들이 private가 됨
//						-> 위 예제에서 c.parent_string을 접근하려고 하면 컴파일 오류가 뜨는데 private 상속을 받기 때문임. public/protected 상속을 받으면 정상적으로 작동함
//		*/		
//		return 0;
//	}

// 상속을 적용시킨 사원 관리 프로그램
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

	void print_info() { std::cout << name << " (" << position << " , " << age << ") ==> " << calculate_pay() << "만원" << std::endl; }
	int calculate_pay() { return 200 + rank * 50; }


protected:	// 상속받은 클래스들에서도 접근이 가능해야하므로 private가 아닌 protected가 되어야 함
	std::string name;
	int age;

	std::string position;	// 직책(이름)
	int rank;	// 순위 (값이 클 수록 높은 순위)

};

// 이제 Manager는 Employee를 상속받아서 만들어보자
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
			<< year_of_service << "년차) ==> " << calculate_pay() << "만원"
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
			사실 current_employee 보다 alloc_employee 가 더 많아지는 경우 반드시 재할당을 해야 하지만,
			여기서는 최대한 단순하게 생각해서 alloc_employee 는 언제나 current_employee 보다 크다고 생각한다.
			즉, 할당된 크기는 현재 총 직원수 보다 많음
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

		std::cout << "총 비용 : " << total_pay << "만원 " << std::endl;
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
	int alloc_employee;			// 할당한 총 직원 수

	int current_employee;		// 현재 직원 수
	int current_manager;		// 현재 매니저 수

	Employee** employee_list;	// 직원 데이터
	Manager** manager_list;		// 매니저 데이터
};

int main()
{
	EmployeeList emp_list(10);
	emp_list.add_employee(new Employee("노홍철", 34, "평사원", 1));
	emp_list.add_employee(new Employee("하하", 34, "평사원", 1));
	emp_list.add_manager(new Manager("유재석", 41, "부장", 7, 12));
	emp_list.add_manager(new Manager("정준하", 43, "과장", 4, 15));
	emp_list.add_manager(new Manager("박명수", 43, "차장", 5, 13));
	emp_list.add_employee(new Employee("정형돈", 36, "대리", 2));
	emp_list.add_employee(new Employee("길", 36, "인턴", -2));
	emp_list.print_employee_info();

	/*
		output
		노홍철 (평사원 , 34) ==> 250만원
		하하 (평사원 , 34) ==> 250만원
		정형돈 (대리 , 36) ==> 300만원
		길 (인턴 , 36) ==> 100만원
		유재석 (부장 , 41, 12년차) ==> 610만원
		정준하 (과장 , 43, 15년차) ==> 475만원
		박명수 (차장 , 43, 13년차) ==> 515만원
		총 비용 : 2500만원
	
	*/

	return 0;
}