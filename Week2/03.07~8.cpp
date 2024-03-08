
/*
	03.07 생성자 초기화 리스트(initializer list)
	03.08 
*/


// 생성자 초기화 리스트(initializer list) - 이전에 만든 marine을 재활용
// static

#include <iostream>
#include <initializer_list>

class Marine
{
	// 이번 marine은 모두의 코드의 네이밍 컨벤션을 따라가봄
public:
	Marine();
	Marine(int x, int y);
	Marine(int x, int y, int default_damage);

	~Marine() { total_marine_num--; }

	int attack();
	void be_attacked(int damage_earn);
	void move(int x, int y);

	void show_status();

	static void show_total_marine();

private:
	int hp;
	int coord_x, coord_y;
	//int damage;
	bool is_dead;

	const int default_damage;

	static int total_marine_num;	// static 변수는 여기서 바로 초기화가 불가능함
									// 바로 초기화 시도시 
									// -> E1592: in-class initializer가 있는 멤버는 const여야 합니다.
									// -> C2864: 'Marine::total_marine_num': in-class initializer가 있는 정적 데이터 멤버은(는) volatile이 아닌 const 정수 형식을 포함하거나 'inline'으로 지정되어야 합니다.
	
	const static int test = 0;		// const static 변수는 바로 초기화가 가능;

};

int Marine::total_marine_num = 0;	// static 변수의 초기화 방법

// : 뒤에 붙은것들이 초기화 리스트
Marine::Marine() : hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) 
{
	//	default_damage = 5;		// const이므로 당연히 불가능함. 여기서 백날 시도해봤자 안됨
	total_marine_num++;
}

// 초기화 리스트가 길면 줄바꿈도 OK
Marine::Marine(int x, int y)
	: coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) 
{
	total_marine_num++;
}

// const 상수 멤버 변수도 받아온 인자를 집어넣어서 초기화 가능
Marine::Marine(int x, int y, int default_damage)
	: coord_x(x),
	coord_y(y),
	hp(50),
	default_damage(default_damage),
	is_dead(false) 
{
	total_marine_num++;
}

void Marine::move(int x, int y)
{
	coord_x = x;
	coord_y = y;
}

int Marine::attack() { return default_damage; }

void Marine::be_attacked(int damage_earn)
{
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;
}

void Marine::show_status()
{
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP :	" << hp << std::endl;
	std::cout << " 현재 총 마린 수 : " << total_marine_num << std::endl;
}

void Marine::show_total_marine()
{
	//	std::cout << default_damage << std::endl;	// E0245: 비정적 멤버 참조는 특정 개체에 상대적이어야 합니다. -> 이 default_damage가 누구껀데...
	std::cout << "전체 마린 수 : " << total_marine_num << std::endl;
}

void create_marine()
{
	Marine marine3(10, 10, 4);
	marine3.show_status();
	Marine::show_total_marine();
}


int main()
{
	// 초기화 리스트

	//	Marine marine1(2, 3, 10);
	//	Marine marine2(3, 5, 10);
	//	
	//	marine1.show_status();
	//	marine2.show_status();
	//	
	//	std::cout << std::endl << "마린 1 이 마린 2 를 공격 " << std::endl;
	//	marine2.be_attacked(marine1.attack());
	//	
	//	marine1.show_status();
	//	marine2.show_status();
	//	
	//	/*
	//		output
	//	
	//		  *** Marine ***
	//		  Location : ( 2 , 3 )
	//		  HP :   50
	//		  *** Marine ***
	//		  Location : ( 3 , 5 )
	//		  HP :   50
	//		
	//		마린 1 이 마린 2 를 공격
	//		 *** Marine ***
	//		 Location : ( 2 , 3 )
	//		 HP :   50
	//		 *** Marine ***
	//		 Location : ( 3 , 5 )
	//		 HP :   40
	//	*/
	//	
	//	/*
	//		- 초기화 리스트 (Initializer list)
	//			- 위의 생성자 뒤에 : 이후로 나열된 것들이 초기화 리스트
	//				-> Marine::Marine() : "hp(50), coord_x(0), coord_y(0), damage(5), is_dead(false)" <- 이거
	//			- 초기화 리스트를 사용하면 생성자의 호출과 동시에 멤버 변수들을 초기화해줌
	//			- 사용법 : T::T() : var1(arg1), var2(arg2), ... {}
	//			- arg와 var의 이름이 같아도 문제없이 작동됨
	//				- 만약에 생성자의 인자 이름이 멤버변수의 이름과 같은 coord_x, coord_y로 들어온다면
	//					- 초기화 리스트의 괄호 안에서(coord_x)를 입력하면 인자로 받은 변수를 우선적으로 지칭함
	//					- 그 외에는 멤버 변수를 의미함
	//						-> 일반적으로는 이 둘을 확실히 구분하기 위해 멤버변수 이름에 규칙을 주거나 this포인터를 사용하는 편임
	//			- 이걸 왜씀?
	//				- 초기화 리스트를 사용하지 않으면 우선 객체를 먼저 생성하고 그다음에 대입됨 -> int a; a = 10; 과 같은 개념
	//				- 초기화 리스트를 사용하면 "생성과 동시에 초기화함" -> int a = 10; 과 같은 개념
	//				- 아니 그래서 이걸 언제 왜씀?
	//					-> 선언과 동시에 초기화 되어야하는 것들이 있을때 사용함(상수(const), 레퍼런스(&), 멤버 클래스 등등)
	//					-> 선언과 동시에 초기화되야하는데 초기화 리스트를 사용하지 않을시 컴파일 오류가 발생하게되므로 반드시 사용해야함
	//						-> const int인 default_damage 를 초기화리스트를 이용하지 않는경우
	//							- E0366: "Marine::Marine()"이(가) 다음에 대한 이니셜라이저를 제공하지 않습니다.
	//							- C2789: 'Marine::default_damage': const 한정 형식의 개체를 초기화해야 합니다.
	//						++ const로 절대로 변하면 안되는 값을 만들면 실수하더라도 컴파일러가 오류를 내기때문에 매우매우 좋다.
	//	*/


	// static

	Marine marine1(2, 3, 5);
	marine1.show_status();

	Marine marine2(3, 5, 10);
	marine2.show_status();

	create_marine();

	std::cout << std::endl << "마린1 이 마린2 를 공격 " << std::endl;
	marine2.be_attacked(marine1.attack());

	marine1.show_status();
	marine2.show_status();

	//	total_marine_num을 public으로 옮기고 주소를 찍어보자
	//	std::cout << &marine1.total_marine_num << std::endl;
	//	std::cout << &marine2.total_marine_num << std::endl;

	/*
		output

		 *** Marine ***
		 Location : ( 2 , 3 )
		 HP :   50
		 현재 총 마린 수 : 1
		 *** Marine ***
		 Location : ( 3 , 5 )
		 HP :   50
		 현재 총 마린 수 : 2
		 *** Marine ***
		 Location : ( 10 , 10 )
		 HP :   50
		 현재 총 마린 수 : 3	-> 함수 종료(create_marine)와 함께 객체가 소멸되어 마린수가 2로 내려감
		
		마린1 이 마린2 를 공격
		 *** Marine ***
		 Location : ( 2 , 3 )
		 HP :   50
		 현재 총 마린 수 : 2
		 *** Marine ***
		 Location : ( 3 , 5 )
		 HP :   45
		 현재 총 마린 수 : 2

		00007FF629CCF174
		00007FF629CCF174
	*/

	/*
		- static
			- 사전적 의미: 정적인, 고정된, 정지의
			
			- 현재 프로그램 내부의 마린을 세려고 한다
				- 첫번째 방법: 마린을 보관하는 배열을 만들고 생성된 마린의 개수를 모두 센다. X
					-> 마린이 얼마나 생길줄 알고 배열에다 저장을함? (아직 vector를 배우지 않음)
				- 두번째 방법: 어떤 변수를 만들어서 마린의 생성/소멸시 ++/--. 
					-> 변수를 어떻게 만들것인가
						- 함수에 지역변수로 -> 다른 함수에서 이용하려면 매번 인자로 받아야하므로 귀찮아짐
						- 전역변수로 -> 되도록 진짜 어쩔수 없을때만 쓰는게 좋음
							-> 이때 사용할 수 있는것이 바로 static 변수

			- static
				- C에서 : 선언된 범위(scope)를 벗어나서도 소멸되지 않는 변수
				- C++에서 : 특정 인스턴스에 속하지 않는 클래스 구성원의 선언(declarations of class members not bound to specific instances) - cppreference
					-> 특정 인스턴스에 속하지 않는다 : 클래스의 static 멤버변수는 해당 클래스의 모든 객체들이 '공유'함
						-> 모든 객체(인스턴스)들이 '단 하나'의 static 멤버 변수만 참조
						-> total_marine_num을 public으로 옮기고 marine1과 marine2에서 주소를 확인해보면 같은 주소를 가리키고있음
				- static 변수는 클래스 내부에서 바로 초기화할 수 없음. 대신 자동으로 0으로 초기화됨
					-> 초기화가 필요한 경우 클래스 외부에서 초기화해야함
					-> 위에서도 클래스 외부에서 int Marine::total_marine_num = 0; 로 초기화되고있음
					-> 다만 const static 변수는 클래스 내부에서 바로 초기화가 가능함
				
				- static 함수 또한 가능. 마찬가지로 단 하나만 존재하고 객체에 종속되지 않음
				- static 함수는 객체 없이도 바로 클래스 자체에서 호출이 가능함.
					-> (클래스)::(함수이름)으로 바로 호출
				- 특정 객체에 종속되지 않으므로 static 함수는 static 변수만 이용할 수 있음.
	*/

	Marine::show_total_marine();

}