
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

#include <iostream>
#include <string>

class Base
{
public:
	Base() : s("기반") { std::cout << "기반 클래스" << std::endl; }
	
	void what() { std::cout << s << std::endl; }
private:
	std::string s;
};

class Derived : public Base
{
public:
	Derived() : s("파생"), Base() { std::cout << "파생 클래스" << std::endl; }

	void what() { std::cout << s << std::endl; }
private:
	std::string s;
};

int main()
{
	{
		std::cout << " === 기반 클래스 생성 ===" << std::endl;
		Base p;

		p.what();

		std::cout << " === 파생 클래스 생성 === " << std::endl;
		Derived c;

		c.what();

		/*
			output
			 === 기반 클래스 생성 ===
			기반 클래스
			기반
			 === 파생 클래스 생성 ===
			기반 클래스
			파생 클래스
			파생
		*/
	}

	// 업캐스팅
	{
		Base p;
		Derived c;

		std::cout << " === 포인터 버전 === " << std::endl;
		Base* p_c = &c;
		p_c->what();

		/*
			output
			기반 클래스
			기반 클래스
			파생 클래스
			 === 포인터 버전 ===
			기반
		*/
	}

	/*
		- 업 캐스팅
			- 위의 예제에서 Base의 포인터에 Derived의 주소를 넣어주는 부분이 문제 없이 작동됨
				- Derived는 Base를 상속받고 있음 -> Derived is a Base
				- 그러면 객체 c도 Base 이기도 하므로 Base 포인터가 가리킬 수 잇음
				- 눈에 보이게 해보면...
					->
						Derived c -> [string s][Base()][what()] + [string s][Derived()][what()]
									 --------------------------> 딱 이만큼은 Base* 가 가리킬 수 있음
				- 이때 p_c->what()을 실행시키면 "기반"이 출력됨
					-> p_c는 Base의 포인터이므로 Base::What()이 실행되는것
				-> 이렇게 파생 클래스에서 기반 클래스로 캐스팅 하는것을 "업 캐스팅" 이라고 함
	*/

	// 다운 캐스팅
	{
		Base p;
		Derived c;

		std::cout << " === 포인터 버전 === " << std::endl;
		// 기반 클래스를 파생 클래스로 캐스팅 가능할까?
		//	Derived* p_p = &p;	// C2440: '초기화 중': 'Base *'에서 'Derived *'(으)로 변환할 수 없습니다
		//	p_p->what();
		// 안됨

		// 업캐스팅 하고 다시 원래 클래스로 돌려놓는건 가능할까?
		//	Base* p_p = &c;
		//	Derived* p_c = p_p;	// C2440: '초기화 중': 'Base *'에서 'Derived *'(으)로 변환할 수 없습니다
		//	p_c->what();
		// 안됨

		// 강제로 되도록 하면 될까?
		//	Base* p_p = &p;
		//	Derived* p_c = static_cast<Derived*>(p_p);
		//	p_c->what();
		// 원래는 런타임 오류가 뜸. 현재는 아무것도 출력되지 않고 그냥 넘어감

		// dynamic_cast를 이용해보자: 상속 관계에 있는 두 포인터들 간의 캐스팅
		//	Base* p_p = &p;
		//	Derived* p_c = dynamic_cast<Derived*>(p_p);	// C2683: 'dynamic_cast': 'Base'은(는) 다형 형식이 아닙니다.

		// 이것만 유일하게 가능함
		Base* p_p = &c;
		Derived* p_c = static_cast<Derived*>(p_p);
		p_c->what();
	}

	/*
		- 위의 다운캐스팅들은 왜 안될까
			- 눈에 보이게 그려보면 쉬움
				Base ->  [string s][Base()][what()]
				Derived ->  [string s][Base()][what()] + [string s][Derived()][what()]
				이런식으로 구성되어 있는데
				Base ->  [string s][Base()][what()] / [string s][Derived()][what()] <- 이부분은 없음 
						 ----------------------------------------------------------> Derived* 가 가리키는 부분은 이만큼인데 Base에는 없으므로 정상 작동하지 않는것
			- 다운캐스팅은 상속관계를 잘 파악하고 사용해야함
	
	*/
	return 0;

}