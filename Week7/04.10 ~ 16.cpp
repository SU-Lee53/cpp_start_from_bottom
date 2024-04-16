
/*
	- 04.10 ~ 04.16 virtual 소멸자, 가상 함수 테이블, 다중상속, 가상상속
*/

// virtual 소멸자

//	#include <iostream>
//	
//	class Parent
//	{
//	public:
//		Parent() { std::cout << "Parent 생성자 호출" << std::endl; }
//		virtual ~Parent() { std::cout << "Parent 소멸자 호출" << std::endl; }
//	};
//	
//	class Child : public Parent
//	{
//	public:
//		Child() : Parent() { std::cout << "Child 생성자 호출" << std::endl; }
//		~Child() { std::cout << "Child 소멸자 호출" << std::endl; }
//	};
//	
//	int main()
//	{
//		// 소멸자가 virtual이 아닐때
//		{
//			std::cout << "--- 평범한 Child 만들었을 때 ---" << std::endl;
//			{ Child c; }
//			std::cout << "--- Parent 포인터로 Child 가리켰을 때 ---" << std::endl;
//			{
//				Parent* p = new Child();
//				delete p;
//			}
//	
//			/*
//				output
//				--- 평범한 Child 만들었을 때 ---
//				Parent 생성자 호출
//				Child 생성자 호출
//				Child 소멸자 호출
//				Parent 소멸자 호출
//				--- Parent 포인터로 Child 가리켰을 때 ---
//				Parent 생성자 호출
//				Child 생성자 호출
//				Parent 소멸자 호출
//			*/
//		}
//	
//		// 소멸자가 virtual 일때
//		{
//			std::cout << "--- 평범한 Child 만들었을 때 ---" << std::endl;
//			{ Child c; }
//			std::cout << "--- Parent 포인터로 Child 가리켰을 때 ---" << std::endl;
//			{
//				Parent* p = new Child();
//				p->~Parent();
//				delete p;
//			}
//	
//			/*
//				output
//				--- 평범한 Child 만들었을 때 ---
//				Parent 생성자 호출
//				Child 생성자 호출
//				Child 소멸자 호출
//				Parent 소멸자 호출
//				--- Parent 포인터로 Child 가리켰을 때 ---
//				Parent 생성자 호출
//				Child 생성자 호출
//				Child 소멸자 호출
//				Parent 소멸자 호출
//			*/
//		}
//	
//		/*
//			- virtual 소멸자
//				- 우선 소멸자가 virtual이 아닐때의 출력결과 : 
//					--- 평범한 Child 만들었을 때 ---
//					Parent 생성자 호출
//					Child 생성자 호출
//					Child 소멸자 호출
//					Parent 소멸자 호출
//						-> 생성자, 소멸자의 호출순서 : Parent() -> Child() -> ~Child() -> ~Parent()
//					--- Parent 포인터로 Child 가리켰을 때 ---
//					Parent 생성자 호출
//					Child 생성자 호출
//					Parent 소멸자 호출
//						-> 위와 다르게 Child의 소멸자가 호출되지 않아 메모리 누수를 일으킬 수 있음
//	
//				- 소멸자가 virtual 일때의 출력결과
//					--- 평범한 Child 만들었을 때 ---
//					Parent 생성자 호출
//					Child 생성자 호출
//					Child 소멸자 호출
//					Parent 소멸자 호출
//					--- Parent 포인터로 Child 가리켰을 때 ---
//					Parent 생성자 호출
//					Child 생성자 호출
//					Child 소멸자 호출
//					Parent 소멸자 호출
//						-> 이번에는 필요한 모든 소멸자가 정상적으로 호출되어 메모리 누수가 일어나지 않음
//	
//				- 위처럼 소멸자가 virtual이 아니라면 객체 소멸시 정상적인 소멸자가 호출되지 못하기 때문에 
//				  """상속될 여지가 있는 Base 클래스들은 반드시 소멸자를 virtual로 만들어야함"""
//	
//				++ Parent의 소멸자는 왜 호출되는가
//					-> Child가 Parent를 상속받고 있음을 알고있기 때문에 알아서 Parent의 소멸자를 호출함 -> 파생 클래스는 누구를 상속중인지 알고있음
//					-> 반면 Parent의 소멸자를 먼저 호출하면 Child의 소멸자를 호출할 수 없음 -> 기반 클래스는 누구를 상속해주고 있는지 모름
//		*/
//	
//		return 0;
//	}

// 레퍼런스의 가상 함수 접근

//	#include <iostream>
//	
//	class A
//	{
//	public:
//		virtual void show() { std::cout << "Parent" << std::endl; }
//	};
//	
//	class B : public A
//	{
//	public:
//		void show() override { std::cout << "Child" << std::endl; }
//	};
//	
//	void test(A& a) { a.show(); }
//	
//	int main()
//	{
//		A a;
//		B b;
//		test(a);
//		test(b);
//	
//		/*
//			output
//			Parent
//			Child
//		*/
//	
//		/*
//			- 여태까지의 예제는 파생 클래스의 함수에 접근할때 기반 클래스의 포인터를 사용했지만 래퍼런스로도 접근 가능함
//			++ 솔직히 컴파일 돌려놓으면 레퍼런스나 포인터나 크게 다른게 없기 때문에 당연할수도...
//				https://www.youtube.com/watch?v=lRUiaigGIDA
//		*/
//		return 0;
//	}

// 가상 함수의 구현 원리 : 가상 함수 테이블

/*
	- 가상 함수의 구현 원리
		- 가상 함수가 이렇게 좋은데 모든 함수를 다 virtual 붙이고 가상함수로 만들면 안됨?
			- 상관 없음. 그러나.....
		- 가상 함수의 구현 원리
			- C++는 가상 함수가 하나라도 존재하는 클래스에 대해서 가상 함수 테이블(virtual function table:vTable)을 만듬
			- 가상 함수 테이블 : 전화번호부로 이해하면 쉬움 -> [가게 이름(함수 이름)] --- [가게 전화번호(실제 함수)]
			- 이때 가상 함수와 가상 함수가 아닌 함수가 호출되는 과정에서 차이가 있음
				- 가상 함수가 아닌 함수 : 특별한 단계를 거치지 않고 바로 함수를 호출하여 실행함
				- 가상 함수 : 가상 함수 테이블에 먼저 가서 원하는 함수를 고른 뒤에 호출하여 실행함
				-> 결과적으로 가상함수는 가상 함수 테이블에서 어떤 함수를 고를지에 대한 추가적인 과정이 걸림(오버헤드)
			- 오버헤드에 따른 성능 차이는 미미하지만 최적화가 중요한 분야에서는 이를 감안해야 할 필요가 있고 하필 게임이 최적화가 중요한 분야임...
		- 결론 : 가상함수은 호출 과정에서 오버헤드가 있기 때문에 성능 저하를 불러올 수 있음
*/

// 순수 가상 함수, 추상 클래스

//	#include <iostream>
//	
//	class Animal
//	{
//	public:
//		Animal() {}
//		virtual ~Animal() {}
//		virtual void speak() = 0;
//	};
//	
//	class Dog : public Animal
//	{
//	public:
//		Dog() : Animal() {}
//		void speak() override { std::cout << "왈왈" << std::endl; }
//	};
//	
//	class Cat : public Animal
//	{
//	public:
//		Cat() : Animal() {}
//		void speak() override { std::cout << "야옹야옹" << std::endl; }
//	};
//	
//	int main()
//	{
//		Animal* dog = new Dog();
//		Animal* cat = new Cat();
//		//	Animal* animal = new Animal();	// 불가 C2259: 'Animal': 추상 클래스를 인스턴스화 할 수 없습니다.
//	
//		dog->speak();
//		cat->speak();
//	
//		/*
//			output
//			왈왈
//			야옹야옹
//		*/
//	
//		/*
//			- 순수 가상 함수
//				- 무엇을 하는지 정의되어 있지 않는 함수 -> 반드시 오버라이딩 되어야 하는 함수
//				- 가상함수에 = 0; 을 붙여서 선언
//					-> 위 Animal 클래스의 virtual void speak() = 0;이 순수 가상 함수임
//				- 순수 가상 함수의 본체 그 자체는 정의가 없으므로 실행시킬수 없기 때문에 순수 가상 함수가 있는 클래스는 인스턴스를 생성할 수 없음
//				- private에 순수 가상 함수를 정의할 수도 있음. 다만 이경우 오버라이드는 가능하나 자식 클래스가 호출하지 못함
//			- 추상 클래스
//				- 순수 가상 함수를 최소 한개 포함하고 있는 반드시 상속되어야 하는 클래스
//				- 추상클래스 자체는 인스턴스(객체)를 생성할 수 없음
//				- 추상 클래스를 왜씀?
//					- 해당 클래스를 상속받아 사용할 때 "이 기능은 일반적인 상황에서 만들기 힘드니 너가 직접 특수화 되는 클래스에 맞추어 만들어 써라" 라는 의미로 사용
//					- Animal::speak()의 경우도 마찬가지로 모든 동물마다 내는 소리가 다르므로 일반적인 Animal의 speak()의 정의를 내리기 힘들고 
//					  해당 클래스를 상속받은 Dog/Cat 등의 특수한 상황에 맞추어 기능을 정의함
//				- 추상 클래스의 인스턴스는 만들 수 없지만 포인터는 문제없이 만들 수 있음
//					-> 위에서도 dog와 cat이 Animal 포인터에 업캐스팅 되고 오버라이드 된 speak()를 상황에 맞게 잘 실행시켜줌
//		
//		*/
//	}

// 번외 : 가상함수는 얼마나 느릴까

//	#include <iostream>
//	#include <chrono>
//	
//	class A 
//	{
//	public:
//		virtual ~A() {}
//	
//		virtual int func(int num)
//		{
//			return num + 1;
//		}
//		int func2(int num)
//		{
//			return num + 1;
//		}
//	};
//	
//	class B : public A
//	{
//	public:
//		~B() {}
//	
//		int func(int num) override
//		{
//			return num + 1;
//		}
//	
//	};
//	
//	int main()
//	{
//		A* a = new B();
//	
//		for (int count = 10; count <= 1000000000; count *= 10)
//		{
//			std::cout << "execution count : " << count << std::endl;
//	
//			auto vStart = std::chrono::high_resolution_clock::now();
//			for (int i = 0; i < count;)
//			{
//				i = a->func(i);
//			}
//			auto vEnd = std::chrono::high_resolution_clock::now();
//			std::chrono::duration<double> vElapsed = vEnd - vStart;
//	
//			std::cout << "virtual function elapsed second : " << vElapsed.count() << "s" << std::endl;
//	
//	
//			auto gStart = std::chrono::high_resolution_clock::now();
//			for (int i = 0; i < count;)
//			{
//				i = a->func2(i);
//			}
//			auto gEnd = std::chrono::high_resolution_clock::now();
//			std::chrono::duration<double> gElapsed = gEnd - gStart;
//	
//			std::cout << "non-virtual function elapsed second : " << gElapsed.count() << "s" << std::endl;
//	
//			std::cout << std::endl;
//		}
//		
//		/*
//		output
//		execution count : 10
//		virtual function elapsed second : 3e-07s
//		non-virtual function elapsed second : 1e-07s
//		
//		execution count : 100
//		virtual function elapsed second : 3e-07s
//		non-virtual function elapsed second : 2e-07s
//		
//		execution count : 1000
//		virtual function elapsed second : 2.6e-06s
//		non-virtual function elapsed second : 1.4e-06s
//		
//		execution count : 10000
//		virtual function elapsed second : 2.11e-05s
//		non-virtual function elapsed second : 1.41e-05s
//		
//		execution count : 100000
//		virtual function elapsed second : 0.0002034s
//		non-virtual function elapsed second : 0.0001669s
//		
//		execution count : 1000000
//		virtual function elapsed second : 0.0019909s
//		non-virtual function elapsed second : 0.0013699s
//		
//		execution count : 10000000
//		virtual function elapsed second : 0.0195895s
//		non-virtual function elapsed second : 0.0133003s
//		
//		execution count : 100000000
//		virtual function elapsed second : 0.223024s
//		non-virtual function elapsed second : 0.159269s
//		
//		execution count : 1000000000
//		virtual function elapsed second : 2.04678s
//		non-virtual function elapsed second : 1.36539s
//
//	*/
//	
//		// 실행 횟수가 늘어날수록 속도차이가 확실히 보임
//	}

// 다중상속

//	#include <iostream>
//	
//	class A
//	{
//	public:
//		int a;
//	
//		A() { std::cout << "A 생성자 호출" << std::endl; }
//	};
//	
//	class B
//	{
//	public:
//		int a;
//		int b;
//	
//		B() { std::cout << "B 생성자 호출" << std::endl; }
//	};
//	
//	class C : public A, public B
//	{
//	public:
//		int c;
//	
//		C() : A(), B() { std::cout << "C 생성자 호출" << std::endl; }
//	};
//	
//	int main()
//	{
//		C c;
//		//	c.a = 10;	C2385: 'a' 액세스가 모호합니다
//	
//		/*
//			- 다중 상속 (multiple inheritance)
//				- 한 클래스가 다른 여러 개의 클래스 들을 상속받는것
//				- 다중 상속시 생성자의 호출순서 : 먼저 상속하는 순
//					- class C : public A, public B -> A > B > C 순으로 생성자가 호출됨
//					- class C : public B, public A -> B > A > C 순으로 생성자가 호출됨
//					- 이는 C의 생성자의 초기화 리스트에서 순서를 지정하여도 변하지 않음
//	
//				- 다중 상속시 주의할점
//					- 위의 경우처럼 A, B 모두 int a를 가지고 있는 경우 둘다 상속받는 C의 입장에서 C::a가 모호해짐
//						-> 다중 상속시 중복되는 멤버 변수가 있어서는 안됨
//					- 한 클래스로 부터 두 번 상속받는것은 금지되어있음 (soen)
//						-> 당연히 그렇게 의도할리는 없겠지만 아래의 다이아몬드 상속 문제와 직접적으로 연결되는 문제로 의도치 않게 발생할 수 있기도 함
//		*/
//	}

// 다중 상속시의 주의점 : 다이아몬드 상속, 그 해결법 가상상속

//	#include <iostream>
//	
//	class Human
//	{
//	public:
//		Human() { std::cout << "Human" << std::endl; }
//	};
//	
//	class HandsomeHuman : public virtual Human
//	{
//	public:
//		HandsomeHuman() : Human() { std::cout << "HandsomeHuman" << std::endl; }
//	};
//	
//	class SmartHuman : public virtual Human
//	{
//	public:
//		SmartHuman() : Human() { std::cout << "SmartHuman" << std::endl; }
//	};
//	
//	class Me : public HandsomeHuman, public SmartHuman
//	{
//	public:
//		Me() : Human(), HandsomeHuman(), SmartHuman() { std::cout << "Me" << std::endl; }
//	};
//	
//	int main()
//	{
//		Me m;
//	
//		/*
//			- 가상 상속이 아닌경우
//			output :
//			Human
//			HandsomeHuman
//			Human
//			SmartHuman
//			Me
//		*/
//	
//		/*
//			- 가상 상속의 경우
//			output :
//			Human
//			HandsomeHuman
//			SmartHuman
//			Me
//		*/
//	
//		/*
//			- 다이아몬드 상속
//				- 위의 다중 상속 단락에서 설명하였듯이 한 클래스가 다른 클래스에 두번 이상 상속할 수 없음
//				- 그러나 위의 Me 는 Human을 2번 상속 받는것과 마찬가지인 경우임
//					-> 그림으로 보면
//									 |----- [HandsomeHuman] <---|
//						[Human] <----							 ------ [Me]
//									 |----- [SmartHuman] <------|
//						-> HandsomeHuman과 SmartHuman 모두 Human을 상속받고 있으므로 둘을 상속받는 Me는 Human을 2번 상속받는 꼴이 됨
//						-> 만약에 Human에 name이라는 변수가 있다면 Me::name은 상속받은 2개의 클래스 모두 name이 있어 변수가 모호해짐
//						-> 또한 불필요하게 Human 구조를 2개 들고있으므로 메모리도 낭비임
//				- 이런 구조는 공포의 다이아몬드 상속(dreadful diamond of derivation) 이라고 부를정도로 경계되고있음
//	
//			- 가상 상속
//				- 한 클래스를 두 번 상속받더라도 해당 클래스의 멤버는 한번만 상속하도록 함
//				- 가상 상속되는 클래스를 가상 기반 클래스(virtual base class)라고 함
//				- 가상 기반 클래스로부터 상속받은 멤버는 최종 클래스가 직접 초기화해주어야 함
//					-> Me의 생성자에서 HandsomeHuman, SmartHuman 뿐만 아니라 Human 클래스까지 같이 초기화 리스트에서 초기화 해주고 있음
//		*/
//	
//	
//	}

// 그러면 다중 상속은 언제 써야할까

#include <iostream>

// 기반 클래스
class Vehicle
{

};

/************************** 작동 환경에 따른 파생 클래스 **************************/
class LandVehicle : public virtual Vehicle
{

};

class WaterVehicle : public virtual Vehicle
{

};

class SkyVehicle : public virtual Vehicle
{

};

class SpaceVehicle : public virtual Vehicle
{

};


/************************** 동력원에 따른 파생 클래스 **************************/

class GasPoweredVehicle : public virtual Vehicle
{

};

class WindPoweredVehicle : public virtual Vehicle
{

};

class NuclearPoweredVehicle : public virtual Vehicle
{

};

class PedalPoweredVehicle : public virtual Vehicle
{

};

/************************** 최종 파생 클래스 **************************/

class GasPoweredLandVehicle : public GasPoweredVehicle, public LandVehicle
{

};

// 이런식으로 최종 파생 클래스들을 만들어 나간다

/*
	- 다중 상속은 언제 써야할까?
		- 모두의 코드에서는 아래의 예시를 들면서 설명하고 있음
			- 차량(Vehicle)에 관련한 클래스를 만든다고 생각을 해보자
				- 차량의 종류는 땅에서 다니는 차, 물에서 다니는 차, 하늘을 나는 차, 우주에서 다니는 차 <- 이렇게 있다고 치자
				- 차량의 동력원은 휘발유, 풍력, 원자력, 페달(자전거처럼) <- 이렇게 있다고 치자
				- 이제 2가지를 고려해보도록 해본다
					1) LandVehicle 을 가리키는 Vehicle& 레퍼런스를 필요로 하는가?
						-> Vehicle&에 실제로는 LandVehicle이 업캐스팅되어 들어가 있다면 Vehicle 멤버 함수 호출시 LandVehicle의 멤버함수가 오버라이드 되어야 하는가?
					2) 마친가지로 GasPoweredVehicle 에 대해서도 Vehicle& 레퍼런스를 필요로 하는가?
					-> 위 두 질문의 대답이 모두 "YES"라면 다중 상속이 좋음

		- 사실 Vehicle은 다중 상속 외에도 다르게 구현할 방법이 있고 모두의 코드에서는 3가지 방법을 보여줌
			- 위 Vehicle의 예를 들어 차량이 다니는 환경의 수를 N, 동력원의 수가 M이라고 한다면...

				1) 브리지 패턴(Bridge Pattern)
					- 차량을 나타내는 한 가지 카테고리를 아예 멤버 포인터로 만들어버림
						-> Vehicle의 파생 클래스로 LandVehicle, SpaceVehicle 등등의 N개의 파생 클래스만 만들고
						-> 동력원의 경우는 Vehicle::Engine* 멤버 변수를 만들어 줌
						-> 이제 Engine의 파생 클래스로 GasPowered, NuclearPowered 등의 파생 클래스를 만들어 주고
						-> Vehicle의 파생 클래스들의 각 객체가 Engine 파생 클래스들의 객체를 가리키게 함
						장점) 총 N + M개의 클래스만 필요하므로 직접 작성하는 코드양은 줄어듬
						단점) 1. N * M개의 모든 상황에 대한 섬세한 제어가 불가능함
							  2. 컴파일 타임 타입 체크를 적절히 활용할 수 없음
								  ex1) Engine이 페달이고 작동확경이 우주인 괴상한 Vehicle 파생 객체를 컴파일 타임에 생성을 막을 방법이 없음(런타임에나 확인가능)
								  ex2) 동력원과 상관없이 우주에서 작동하는 모든 차량을 가리키는 기반 클래스는 만들수 있지만 (SpaceVehicle* 가 동력원과 상관없이 우주에 다니는 차는 싹다 가리킬 수 있음)
									   차량 종류와 상관없이 휘발유만 사용하는 모든 차량을 가리키는 기반 클래스를 만들 수 없음 (GasPoweredVehicle* 을 애초에 만들 수가 없음)

				2) 중첩된 일반화(Nested Generalization)
					- 우선 한가지 계층을 골라 파생클래스를 만들고, 각각의 파생 클래스들의 다른 계층에 해당되는 파생클래스를 더 만듬
						-> Vehicle의 파생클래스로 LandVehicle, WaterVehicle 등등을 일단 만들고
						-> 이제 다른 계층의 파생 클래스로 GasPoweredLandVehicle, NuclearPoweredLandVehicle, GasPoweredWaterVehicle... 등등을 전부 만듬
						장점) 위의 브리지 패턴보다는 좀 더 섬세한 제어가 가능
						단점) 1. 브리지 패턴처럼 휘발유 차량 전체를 가리킬 기반 클래스를 만들 수 없음 (이것도 GasPoweredVehicle* 을 애초에 만들 수가 없음)
							  2. N * M개의 클래스라는 방대한 클래스 양과 새로운 클래스를 추가하기 힘들어짐
								ex) 동력원이 하나 더 추가되면 해당 동력원에 대해 N개의 클래스를 더 만들어야함.....

				3) 다중 상속
					- 브리지 패턴처럼 각 카테고리에 해당하는 파생 클래스들을 만들고 동력원과 작동 환경에 해당하는 클래스를 상속받는 클래스를 만듬
						-> LandVehicle..., GasPoweredVehicle... 등등의 파생되는 카테고리에 대한 클래스를 다 만들고
						-> class GasPoweredLandVehicle : public LandVehicle, public GasPoweredVehicle <- 이런식으로 필요한 경우에 맞춰 다중상속을 받는 최종 클래스들을 만듬
						-> 이렇게 하면 브리지 패턴과 중접된 일반화 방식의 단점들을 해결 가능함
							ex1) 브리지 패턴의 문제였던 PedalPoweredSpaceVehicle 등의 생성을 막을 수 있음(애초에 정의자체를 안하면 됨)
							ex2) 위 두가지 방식 모두 불가능하던 휘발유를 사용하는 모든 차량을 가리킬 기반 클래스를 이제 만들 수 있음(GasPoweredVehicle* 을 만들 수 있음)

			- 위 3가지 방식중 절대적으로 우월한 방식은 없음. 상황에 맞게 최선의 방식을 골라서 사용해야 함.
*/