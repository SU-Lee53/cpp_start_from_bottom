
/*
	- 04.10 virtual 소멸자, 가상 함수 테이블, 다중상속, 가상상속
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