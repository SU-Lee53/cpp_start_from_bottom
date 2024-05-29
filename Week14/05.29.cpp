/*
	05.29 스마트 포인터 1 : RAII, unique_ptr
*/

/*  자원 관리의 중요성  */
//	#include <iostream>
//	
//	class A
//	{
//	public:
//		A()
//		{
//			data = new int[100];
//			std::cout << "자원 획득" << std::endl;
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
//	void thrower()
//	{
//		throw 1;
//	}
//	
//	void throw_something()
//	{
//		A* pa = new A();
//		thrower();
//		delete pa;
//	}
//	
//	void do_something() 
//	{ 
//		A* pa = new A(); 
//	}
//	
//	int main()
//	{
//		do_something();
//	
//		try
//		{
//			throw_something();
//		}
//		catch (int i)
//		{
//			std::cout << "예외 발생" << std::endl;
//		}
//	
//		/*
//			- 자원 관리의 중요성
//				- 위 코드에서
//					- A 클래스는 생성자에서 100개의 int를 힙에 할당함. 즉 4byte * 100 = 400byte 할당됨
//	
//					- do_something()
//						- pa 객체를 heap에 생성
//						- 이후 리턴되면 pa는 소멸되지만 pa가 가리키던 힙영역 어딘가의 A 객체는 소멸되지 않음
//						- delete pa; 를 해주지 않은 이유만으로 400바이트의 메모리 누수가 발생함
//	
//					- throw_something()
//						- pa 객체가 heap에 생성되고 thrower() 함수로 인해 예외가 던져짐
//						- 즉시 catch로 이동. 이과정에서 delete pa;는 수행되지 않음 (stack unwinding으로도 동적 할당된 객체의 소멸자는 부를 수 없음)
//						- 예외는 처리되었지만 400바이트 메모리 누수가 발생
//	
//				- C++은 java, go 등의 최신 언어와 다르게 가비지 컬렉터가 없음
//				- 그러므로 본인이 획득한 자원은 본인이 반드시 직접 해제해주어야 함. 그렇지 않으면 프로그램 종료시까지 남아있음
//				- 프로그래머 본인 실수로 자원 해제를 깜빡할 수도 있지만, 해제하는 위치가 애매해서 놓치는 경우가 생기기 마련
//					-> 이를 위해 도입된 디자인 패턴이 RAII
//					-> RAII 패턴을 따르도록 설계된 포인터가 스마트 포인터
//		*/
//	
//		return 0;
//	}

/*  RAII : Resource Acquisition Is Initialization  */
/*
	- RAII
		- C++ 창시자인 Bjarne Stroustrup 이 제안한 디자인 패턴
		- Resource Acquisition Is Initialization. 즉, 자원의 획득은 초기화다!
		- 기본적으로 자원 관리를 스택에 할당한 객체를 통해 수행

		- stack winding이 수행되거나 함수가 종료되어 리턴될때 해당 함수 스택에 있는 객체들에 대한 소멸자가 모두 호출됨
		- 그러면 이 소멸자들 안에 다 사용한 자원들을 함께 해제하는 루틴을 넣으면?
			- 예를 들어
				- 위의 pa는 객체가 아닌 포인터이기 때문에 함수 스택의 객체들을 소멸시킬때 함께 소멸되지 않음
				- 그런데 pa를 포인터 '객체' 로 만든다면 함수 스택을 날릴때 함께 소멸되도록 만들 수 있음

		- 이처럼 작동하는 포인터 객체를 스마트 포인터라고 함.
		- 현재 C++ 에는 <memory>에서 3가지의 포인터 객체를 제공함
			- unique_ptr
			- shared_ptr
			- weak_ptr

		- C++ 11 이전에 사용되던 auto_ptr도 있으나 C++ 11 에서 파면(deprecatred)되었고 C++17에서 완전 삭제됨...
*/

/*  unique_ptr : 객체의 유일한 소유권  */
#include <iostream>
#include <memory>

class A
{
public:
	A()
	{
		std::cout << "자원 획득" << std::endl;
		data = new int[100];
	}

	A(const A& a) = delete;	// 함수 삭제

	void some() { std::cout << "일반 포인터와 동일하게 사용 가능" << std::endl; }

	~A()
	{
		std::cout << "자원 해제" << std::endl;
		delete[] data;
	}

private:
	int* data;
};

void do_something()
{
	std::unique_ptr<A> pa(new A());
	pa->some();
}

int main()
{

	/*  double free, use after free 버그  */
	//	{
	//		A* a1 = new A();
	//		A* a2 = a1;
	//	
	//		// a1 사용 이후 소멸
	//		delete a1;
	//	
	//		// a2 사용 이후 소멸...?
	//		delete a2;	// 런타임 에러 발생 : a2는 a1의 객체를 가리키고 a1이 소멸되었으므로 또 한번 소멸시킬 수 없음
	//		// 이러한 문제를 double free 버그라고 부름
	//	
	//	
	//		// a1 소멸 이후 사용...?
	//		a1->some();	// 런타임 에러 발생 : a1이 이미 소멸되었으므로 접근할 수 없음
	//		// MSVC는 이상하게 실제 메모리 해제를 delete 나 free 하는 시기보다 약간 뒤로 미룸... 그래서 오류가 발생하지 않음
	//		// 아무튼 이런 버그를 use after free 버그 혹은 dangling pointer 라고 부름
	//	}

	/*  std::unique_ptr  */
	//	{
	//		do_something();	// 이전과 다르게 do_something() 내부의 pa가 소멸되고 리턴됨
	//	}

	/*  unique_ptr 의 소유권 이전  */
	//	{
	//		std::unique_ptr<A> pa(new A());
	//		std::cout << "pa : ";
	//		pa->some();
	//		std::cout << "&pa : " << pa.get() << std::endl;	// 00000210152038A0
	//	
	//	
	//		std::cout << "pa -> pb 소유권 이전 ---" << std::endl;
	//		// std::unique_ptr<A> pb = pa;	// C2280 'std::unique_ptr<A,std::default_delete<A>>::unique_ptr(const std::unique_ptr<A,std::default_delete<A>> &)': 
	//										// 삭제된 함수를 참조하려고 합니다. -> 아래에서 설명
	//		
	//		std::unique_ptr<A> pb = std::move(pa);
	//		std::cout << "pb : ";
	//		pb->some();
	//		std::cout << "&pa : " << pa.get() << std::endl;	// 0000000000000000 -> 소유권이 이동되어 nullptr을 가리킴 -> dangling pointer
	//		std::cout << "&pb : " << pb.get() << std::endl;	// 00000210152038A0
	//	
	//	
	//	}

	/*  삭제된 함수?  */
	//	{
	//		A a{};
	//		A b{ a };	// 함수가 삭제되어서 호출 불가
	//	
	//	}

	/*  unique_ptr 를 함수 인자로 전달하기*/
}