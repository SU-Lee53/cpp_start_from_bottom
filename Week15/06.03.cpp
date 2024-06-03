/*
	06.03 shared_ptr, weak_ptr
*/

/*  std::shared_ptr  */
//	#include <iostream>
//	#include <memory>
//	#include <vector>	
//	
//	class A 
//	{
//	public:
//		A()
//		{
//			data = new int[100];
//			std::cout << "자원을 획득함" << std::endl;
//		}
//	
//		~A()
//		{
//			std::cout << "소멸자 호출" << std::endl;
//			delete[] data;
//		}
//	
//	private:
//		int* data;
//	};
//	
//	int main()
//	{
//		// std::shared_ptr<A> p1(new A());
//		std::shared_ptr<A> p1 = std::make_shared<A>();	// shared_ptr는 make_shared 를 이용해서 만드는 것이 더 좋음
//		std::shared_ptr<A> p2 = p1;	// shared_ptr 는 같은 객체를 여러번 참조 가능
//	
//		std::cout << "-----------------" << std::endl;
//	
//		std::vector<std::shared_ptr<A>> vec;
//	
//		vec.push_back(std::shared_ptr<A>(new A()));
//		vec.push_back(std::shared_ptr<A>(vec[0]));
//		vec.push_back(std::shared_ptr<A>(vec[1]));
//	
//		std::cout << "vec.begin() 의 참조 개수 : " << vec.begin()->use_count() << std::endl << std::endl;
//	
//		std::cout << "첫 번째 소멸" << std::endl;
//		vec.erase(vec.begin());
//		std::cout << "vec.begin() 의 참조 개수 : " << vec.begin()->use_count() << std::endl << std::endl;
//	
//		std::cout << "다음 원소 소멸" << std::endl;
//		vec.erase(vec.begin());
//		std::cout << "vec.begin() 의 참조 개수 : " << vec.begin()->use_count() << std::endl << std::endl;
//	
//		std::cout << "마지막 원소 소멸" << std::endl;
//		vec.erase(vec.begin());
//	
//		std::cout << "프로그램 종료" << std::endl;
//		std::cout << "-----------------" << std::endl;
//	
//		/*
//			- output :
//				자원을 획득함
//				-----------------
//				자원을 획득함
//				vec.begin() 의 참조 개수 : 3
//				
//				첫 번째 소멸
//				vec.begin() 의 참조 개수 : 2
//				
//				다음 원소 소멸
//				vec.begin() 의 참조 개수 : 1
//				
//				마지막 원소 소멸
//				소멸자 호출
//				프로그램 종료
//				-----------------
//				소멸자 호출 -> 맨 위의 p1 이 생성했던 객체가 소멸되는것 -> RAII 잘 작동됨
//		*/
//	
//		/*
//			- std::shared_ptr
//				- std::shared_ptr : 하나의 객체를 여러개의 포인터가 가리킬 수 있는 스마트 포인터
//					- 유일한 소유권을 부여하던 unique_ptr 과 달리 이름 그대로 한 객체를 여러개의 shared_ptr 가 가리킴(공유)
//	
//				- 참조 개수(reference count) 를 도입
//					- 특정 객체를 참조하는 shared_ptr의 개수를 셈
//					- 참조 개수가 0 이 되어야만 해당 객체를 소멸시킴
//					- 어떤 shared_ptr의 참조 개수가 알고싶다면 use_count() 멤버 함수를 사용하면 알 수 있음
//					- 예시
//	
//						std::shared_ptr<A> p1(new A());
//						std::shared_ptr<A> p2 = p1;
//	
//						-> 이 경우 p1, p2의 참조 개수는 2
//	
//				- 위 코드의 설명
//					- shared_ptr를 담는 vector인 vec을 생성
//					- vec[0]에 A 객체를 생성하고 이를 가리키는 shared_ptr 를 push_back
//					- vec[1]에는 vec[0]을 가리키는 shared_ptr 를 push_back
//					- vec[2]에는 vec[1]을 가리키는 shared_ptr 를 push_back
//						-> [0], [1], [2] 모두 같은 A 객체를 가리키도록 함. 아래 그림과 같은 형태
//							
//								  class A <--------------+-------------------+
//							         ↑                   |                   |
//							vec	0[ shared_ptr<A> ] 1[ shared_ptr<A> ] 2[ shared_ptr<A> ]
//	
//					- [0], [1], [2] 의 안에 있는 shared_ptr의 참조 개수는 3
//					- vec.begin() 으로 맨 앞 원소 -> A의 소멸자 호출되지 않음
//					- vec.begin() 으로 vec의 모든 원소를 소멸한 뒤에 A의 소멸자가 호출
//						-> 참조 개수가 0이 되어야 비로소 객체가 소멸됨
//					
//				- 참조 개수 저장 방식
//					- 참조 개수는 shared_ptr 안에 저장되지 않음
//						- 만약 참조 개수가 shared_ptr 안에 저장된다면...
//	
//							std::shared_ptr<A> p1(new A());
//							std::shared_ptr<A> p2 = p1;
//							std::shared_ptr<A> p3 = p2;
//	
//							-> 위 같은 코드가 있을 때 참조 개수 카운트에 문제가 생김
//								-> p1.use_count() == 2
//								-> p2.use_count() == 3
//								-> p3.use_count() == 3
//								-> p3가 p2의 참조 개수는 ++ 해주지만 p1까지 건드릴 수가 없음
//	
//					- 참조 개수는 별도의 제어 블록을 통해 관리함
//						- 처음으로 실제 객체를 가리키는 shared_ptr 이 제어 블록을 동적으로 할당
//							-> 앞 예시의 경우 p1이 할당함
//						- 이후 다른 shared_ptr들은 제어들록에 필요한 정보들을 공유함
//							-> shared_ptr 복사 생성시 제어 블록의 위치만 알면 됨
//							-> shared_ptr 생성시 제저 블록에 있는 참조 개수를 ++
//							-> shared_ptr 소멸시 제어 블록에 있는 참조 개수를 --
//	
//				- std::make_shared
//					- unique_ptr 의 make_unique 처럼 shared_ptr도 make_shared 가 있음
//					- shared_ptr 의 경우 make_shared 를 이용하는 것이 더 빠름
//	
//						1) 일반적인 방법으로 shared_ptr을 만드는 경우
//							
//							std::shared_ptr<A> p(new A());
//	
//							-> A를 만드는데 동적할당 1번
//							-> shared_ptr의 제어블록을 만드는데 동적할당 1번
//								-> 총 2번의 동적할당이 일어남
//	
//						2) std::make_shared 를 이용하는 경우
//	
//							std::shared_ptr<A> p = std::make_shared<A>();
//	
//							-> 이 경우 A() 의 할당과 제어블록의 할당을 한번에 수행함
//							
//					- make_shared 또한 인자를 생성자에 전달하는 완벽한 전달을 수행함
//	
//	
//		*/
//	
//	}

/*  shared_ptr 생성 시 주의점, enable_shared_from_this */
#include <iostream>
#include <memory>

class A : public std::enable_shared_from_this<A>	// std::enable_shared_from_this 를 상속받지 않으면 this로 shared_ptr를 만들면 안됨
{
public:
	A()
	{
		data = new int[100];
		std::cout << "자원 획득" << std::endl;
	}

	~A()
	{
		std::cout << "소멸자 호출" << std::endl;
		delete[] data;
	}

	std::shared_ptr<A> get_shared_ptr() 
	{ 
		// return std::shared_ptr<A>(this); 
		return shared_from_this();
	}

private:
	int* data;
};

int main()
{
	int* a = new int(5);
	auto p1 = std::make_shared<int*>(a);
	auto p2 = std::make_shared<int*>(a);
	// p1 과 p2 는 별도의 제어 블록을 가짐
	// 참조 개수 카운트에 문제가 생겨 main 종료시 double free 버그로 런타임 오류 발생


	auto pa1 = std::make_shared<A>();
	auto pa2 = pa1->get_shared_ptr();

	std::cout << pa1.use_count() << std::endl;	// 1
	std::cout << pa2.use_count() << std::endl;	// 1
	// 마찬가지로 pa1 과 pa2는 별도의 제어블록을 가짐
	// 그러므로 이것도 double free 버그가 있음
	// std::enable_shared_from_this 를 상속받으면 문제 해결됨

	/*
		- shared_ptr 생성 시 주의점
			- shared_ptr 의 인자로 주소값이 전달되면 자신이 해당 객체를 첫번째로 소유하는 것이라고 인식함
				-> 즉, 기존에 제어블록이 있건 없건 새로운 제어 블록을 만듬
				-> 위 코드에서 p1, p2를 보면 아래와 같음

					+-------------+
					| 제어 블록   |
					|             | <----------- p1 ----------------+
					| 참조개수: 1 |                                 |
					+-------------+                                 ▼
					                                              new A()
					+-------------+                                 ▲
					| 제어 블록   |                                 |
					|             | <----------- p2 ----------------+
					| 참조개수: 1 |
					+-------------+

					-> p1 이 소멸되면 참조 개수가 0이므로 A가 소멸됨
					-> 그러나 p2 의 참조 개수는 여전히 1 이므로 A를 사용하거나 소멸시키려고 할 수 있음
						-> 이 경우 런타임 오류가 발생

				-> pa1 과 pa2 의 경우도 위와 마찬가지임
					-> pa2 는 pa1 안에서 this 를 이용해서 생성된 shared_ptr
					-> 따라서 pa2도 pa1 과는 다른 별도의 제어 블록을 만들어 관리함

			- 이러한 문제를 막으려면 shared_ptr 를 주소값을 이용해서 생성하는 것을 지양하면 됨
				-> 그러나 어쩔 수 없는 경우도 존재함

		- std::enable_shared_from_this<T>
			- 객체 내부에서 자기 자신을 가리키는 shared_ptr을 만드는 등의 어쩔수 없는 경우에 상속받아 사용함
			- enable_shared_from_this 안에 shared_from_this() 를 이용하면 this 를 이용하여 shard_ptr을 생성하여 리턴함
				-> 이때 이미 있는 제어블록을 이용하므로 반드시 해당 객체의 shared_ptr을 먼저 정의해야함
				-> shared_from_this 는 제어블록을 확인만 함. 없는 제어블록을 새로 만들어주는 일은 하지 않음
	
	*/

}

/*  shared_ptr의 순환참조 문제  */