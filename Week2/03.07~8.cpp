
/*
	03.07 생성자 초기화 리스트(initializer list)
	03.08 
*/


// 생성자 초기화 리스트(initializer list) - 이전에 만든 marine을 재활용

#include <iostream>
#include <initializer_list>

class Marine
{
	// 이번 marine은 모두의 코드의 네이밍 컨벤션을 따라가봄
public:
	Marine();
	Marine(int x, int y);

	int attack();
	void be_attacked(int damage_earn);
	void move(int x, int y);

	void show_status();

private:
	int hp;
	int coord_x, coord_y;
	//int damage;
	bool is_dead;

	const int default_damage;
};

// : 뒤에 붙은것들이 초기화 리스트
Marine::Marine() : hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) 
{
	//	default_damage = 5;		// const이므로 당연히 불가능함. 여기서 백날 시도해봤자 안됨
}

// 초기화 리스트가 길면 줄바꿈도 OK
Marine::Marine(int x, int y)
	: coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) {}

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
}

int main()
{
	Marine marine1(2, 3);
	Marine marine2(3, 5);

	marine1.show_status();
	marine2.show_status();

	std::cout << std::endl << "마린 1 이 마린 2 를 공격 " << std::endl;
	marine2.be_attacked(marine1.attack());

	marine1.show_status();
	marine2.show_status();

	/*
		output

		  *** Marine ***
		  Location : ( 2 , 3 )
		  HP :   50
		  *** Marine ***
		  Location : ( 3 , 5 )
		  HP :   50
		
		마린 1 이 마린 2 를 공격
		 *** Marine ***
		 Location : ( 2 , 3 )
		 HP :   50
		 *** Marine ***
		 Location : ( 3 , 5 )
		 HP :   45
	*/

	/*
		- 초기화 리스트 (Initializer list)
			- 위의 생성자 뒤에 : 이후로 나열된 것들이 초기화 리스트
				-> Marine::Marine() : "hp(50), coord_x(0), coord_y(0), damage(5), is_dead(false)" <- 이거
			- 초기화 리스트를 사용하면 생성자의 호출과 동시에 멤버 변수들을 초기화해줌
			- 사용법 : T::T() : var1(arg1), var2(arg2), ... {}
			- arg와 var의 이름이 같아도 문제없이 작동됨
				- 만약에 생성자의 인자 이름이 멤버변수의 이름과 같은 coord_x, coord_y로 들어온다면
					- 초기화 리스트의 괄호 안에서(coord_x)를 입력하면 인자로 받은 변수를 우선적으로 지칭함
					- 그 외에는 멤버 변수를 의미함
						-> 일반적으로는 이 둘을 확실히 구분하기 위해 멤버변수 이름에 규칙을 주거나 this포인터를 사용하는 편임
			- 이걸 왜씀?
				- 초기화 리스트를 사용하지 않으면 우선 객체를 먼저 생성하고 그다음에 대입됨 -> int a; a = 10; 과 같은 개념
				- 초기화 리스트를 사용하면 "생성과 동시에 초기화함" -> int a = 10; 과 같은 개념
				- 아니 그래서 이걸 언제 왜씀?
					-> 선언과 동시에 초기화 되어야하는 것들이 있을때 사용함(상수(const), 레퍼런스(&), 멤버 클래스 등등)
					-> 선언과 동시에 초기화되야하는데 초기화 리스트를 사용하지 않을시 컴파일 오류가 발생하게되므로 반드시 사용해야함
						-> const int인 default_damage 를 초기화리스트를 이용하지 않는경우
							- E0366: "Marine::Marine()"이(가) 다음에 대한 이니셜라이저를 제공하지 않습니다.
							- C2789: 'Marine::default_damage': const 한정 형식의 개체를 초기화해야 합니다.
	*/
}