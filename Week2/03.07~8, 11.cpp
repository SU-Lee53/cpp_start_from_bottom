
/*
	03.07 생성자 초기화 리스트(initializer list)
	03.08 const, static
	03.11 레퍼런스를 리턴하는 함수, this, const 멤버함수
*/


//	생성자 초기화 리스트(initializer list) - 이전에 만든 marine을 재활용
//	static, const

#include <iostream>

class Marine
{
	// 이번 marine은 모두의 코드의 네이밍 컨벤션을 따라가봄
public:
	Marine();
	Marine(int x, int y);
	Marine(int x, int y, int default_damage);

	~Marine() { total_marine_num--; }

	int attack() const;		// 상수 멤버 함수
	//	void be_attacked(int damage_earn);
	Marine& be_attacked(int damage_earn);
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

Marine& Marine::be_attacked(int damage_earn)
{
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;

	return *this;
}

void Marine::move(int x, int y)
{
	coord_x = x;
	coord_y = y;
}

int Marine::attack() const { return default_damage; }

//	void Marine::be_attacked(int damage_earn)
//	{
//		hp -= damage_earn;
//		if (hp <= 0) is_dead = true;
//	}

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
	Marine::show_total_marine();
}


int main()
{
	// 초기화 리스트
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
						++ const로 절대로 변하면 안되는 값을 만들면 실수하더라도 컴파일러가 오류를 내기때문에 매우매우 좋다.
	*/

	Marine marine1(2, 3, 5);
	Marine::show_total_marine();

	Marine marine2(3, 5, 10);
	Marine::show_total_marine();

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

		 전체 마린 수 : 1
		 전체 마린 수 : 2
		 전체 마린 수 : 3	-> 함수 종료(create_marine)와 함께 객체가 소멸되어 마린수가 2로 내려감
		
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

	// static
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

	std::cout << std::endl << "마린 1이 마린 2를 2번 공격" << std::endl;
	marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack());

	marine1.show_status();
	marine2.show_status();
	
	/*
		output

		마린 1이 마린 2를 2번 공격
		 *** Marine ***
		 Location : ( 2 , 3 )
		 HP :   50
		 현재 총 마린 수 : 2
		 *** Marine ***
		 Location : ( 3 , 5 )
		 HP :   35
		 현재 총 마린 수 : 2
	
	*/


	// this
	/*
		- this: 객체 자신을 가리키는 포인터
			- 언어 차원에서 정의되어있는 C++의 키워드(python의 self와 비슷하게 생각하면 될듯함)
			- 모든 멤버 함수 내에서는 this 키워드가 정의되어 있으며 당연히 static 함수는 this키워드가 정의되어있지 않음
				-> 그러므로 be_attacked()의 내부는 다음이랑 똑같음
					Marine& Marine::be_attacked(int damage_earn)
					{
						this->hp -= damage_earn;
						if (this->hp <= 0) this->is_dead = true;
					
						return *this;
					}

	*/

	// 레퍼런스를 리턴하는 함수
	/*
		- 레퍼런스를 리턴하는 함수 -> 아래 예제와 같이 설명
			- 여기서는 be_attacked()가 Marine& 을 리턴함
			- 리턴되는 값이 *this 즉, 자기 자신이므로 위처럼 2번 맞는 방식이 가능해짐

			- 레퍼런스가 아닌 일반 Marine 객체를 리턴한다면?
				-> 첫번째로 호출된 be_attacked()에서 한번 쳐맞은 자기 자신(*this)을 복사해서 리턴함
				-> 복사된 임시객체가 또한번 맞게됨
				-> 결국 맞으라는 marine2는 한대만 맞고 나머지 한대는 복사된 독립적인 어떠한 임시 객체가 맞는것
	
	*/

	// const 멤버함수
	/*
		- const 멤버함수 : 객체들의 "읽기" 만이 수행됨. 즉 다른 변수의 값을 바꿀 수 없는 함수
			- 위 예제의 attack 멤버함수가 const 멤버함수
			- (기존 함수 정의) const; 형태로 선언
			- 정의에도 const임을 명시해주어야함. 참고로 static은 안해줘도 됨
			- 상수 함수 내에서는 상수 함수만 호출할 수 있음
			++ 일반적으로는 멤버변수를 다 private로 집어넣고 get_x()같은 함수를 pubic으로 만들어 리턴받는 방식을 씀
			++ 이렇게 하면 const 멤버함수가 없어도 다른 변수의 접근을 막으면서 해당 변수만 가져올 수 있음

	
	*/


}


// 레퍼런스를 리턴하는 함수
//	#include <iostream>
//	
//	class A
//	{
//	public:
//		A(int c) : x(c) {}
//	
//		int& access_x() { return x; }
//		int get_x() { return x; }
//		void show_x() { std::cout << "x : "  << x << std::endl; }
//		void show_address_x() { std::cout << "&x : " << &x << std::endl; }
//	
//	private:
//		int x;
//	};
//	
//	int main()
//	{
//		A a(5);
//		a.show_x();
//	
//		std::cout << std::endl << "int& c = a.access_x()" << std::endl;
//		int& c = a.access_x();
//		c = 4;
//		a.show_x();
//		std::cout << "&c : " << &c << std::endl;
//		a.show_address_x();
//	
//		std::cout << std::endl << "int d = a.access_x()" << std::endl;
//		int d = a.access_x();
//		d = 3;
//		a.show_x();
//		std::cout << "&d : " << &d << std::endl;
//		a.show_address_x();
//	
//		//	int& e = a.get_x();		// E0461: 비const 참조에 대한 초기 값은 lvalue여야 합니다.
//		//	e = 2;
//		//	a.show_x();
//	
//		std::cout << std::endl << "int f = a.get_x()" << std::endl;
//		int f = a.get_x();
//		f = 1;
//		a.show_x();
//		std::cout << "&f : " << &f << std::endl;
//		a.show_address_x();
//	
//		std::cout << std::endl << "a.access_x() = 0" << std::endl;
//		a.access_x() = 0;
//		a.show_x();
//	
//		//	a.get_x() = 0;	// E0137: 식이 수정할 수 있는 lvalue여야 합니다.
//	
//		/*
//			output
//	
//			x : 5
//	
//			int& c = a.access_x()
//			x : 4
//			&c : 00000053305AF984
//			&x : 00000053305AF984
//			
//			int d = a.access_x()
//			x : 4
//			&d : 00000053305AF9C4
//			&x : 00000053305AF984
//			
//			int f = a.get_x()
//			x : 4
//			&f : 00000053305AF9E4
//			&x : 00000053305AF984
//			
//			a.access_x() = 0
//			x : 0
//		
//		*/
//	
//		/*
//			- 레퍼런스를 리턴하는 함수
//				- 위 예제의 설명
//					- A 클래스에는 멤버 변수 int x, 레퍼런스를 리턴하는 access_x(), 값을 리턴하는 get_x(), x의 값을 출력하는 show_x() 4가지로 구성됨 
//	
//					- int& c = a.access_x(); 
//						-> 레퍼런스 c가 x의 레퍼런스를 받음 -> c는 x의 "별명(alias)"이 됨
//						-> 레퍼런스를 리턴하는 함수는 그 함수 부분을 원래의 변수로 치환했다고 생각해도 무방함
//						-> 따라서 위 코드는 int& c = x;와 동일함
//						-> 그러므로 c의 값을 바꾸는 것은 a.x의 값을 바꾸는 것과 동일한 의미임. show_x() 결과로 확인해보면 값이 바뀌어있음
//	
//					- int d = a.access_x(); 
//						-> 이번에는 int 변수에 a.x의 레퍼런스를 줌 -> 값 d에 a.x의 값의 복사가 일어남
//						-> d는 x와 독립적이므로 d의 값을 변경해도 x에는 영향이 없음
//	
//					- int& e = a.get_x(); 
//						-> (주석 처리된 부분) 레퍼런스 e에 a의 값을 받음 -> 오류 발생
//						- 왜?
//							-> 레퍼런스가 아닌 값을 리턴하는 함수의 경우 "값의 복사"를 위해 "임시 객체"를 생성함
//							-> 이 "임시 객체"의 레퍼런스는 받을 수 없음! 문장이 끝나면 임시 객체는 소멸되기 때문
//							-> 아래처럼 생각해보면 됨
//								- access_x() -----> return a.x
//								- get_x() --------> 임시객체 int(a.x를 복사한 x')를 만듬 --------> return 임시 객체로 복사된 x' ---------> 임시 객체 소멸
//							-> 정확히는 int&는 좌측값에 대한 레퍼런스, a.get_x()는 우측값이라서 안된다는데 이부분은 아직 잘 모르므로 PASS https://modoocode.com/189
//		
//					- int f = a.get_x();
//						-> int f에 a.x의 값을 복사
//						-> 복사되어 들어간 독립적인 변수이므로 f 값의 변경이 a.x에는 영향을 끼치지 못함
//	
//					- a.access_x() = 0;
//						-> 위 표현대로 a.x = 3; 과 동일함
//		
//		*/
//	
//		return 0;
//	}

