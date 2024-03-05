
/*
	03.05 소멸자, 스타크래프트 실습
	03.06 
*/

// 스타크래프트 실습

//	#include <iostream>
//	
//	class Marine
//	{
//	public:
//		Marine();				// 기본 생성자
//		Marine(int x, int y);	// x,y 죄표에 마린 생성
//		Marine(int x, int y, const char* marine_name);	// x,y 죄표에 마린 생성 + 이름까지 지정
//	
//		~Marine();
//	
//		int Attack();							// 데미지 리턴
//		void BeAttacked(int damageEarn);		// 입는 데미지
//		void Move(int x, int y);				// 새로운 위치
//	
//		void ShowStatus();		// 상태 표시
//	
//	private:
//		int _hp;
//		int _coordX, _coordY;
//		int _damage;
//		bool _isDead;
//		char* _name;
//	};
//	
//	Marine::Marine()
//	{
//		_hp = 50;
//		_coordX = _coordY = 0;
//		_damage = 5;
//		_isDead = false;
//		_name = NULL;
//	}
//	
//	Marine::Marine(int x, int y)
//	{
//		_hp = 50;
//		_coordX = x;
//		_coordY = y;
//		_damage = 5;
//		_isDead = false;
//		_name = NULL;
//	}
//	
//	#pragma warning (disable : 4996)
//	// strcpy가 오류를 발생시킴
//	Marine::Marine(int x, int y, const char* marine_name)
//	{
//		_hp = 50;
//		_coordX = x;
//		_coordY = y;
//		_damage = 5;
//		_isDead = false;
//	
//		_name = new char[strlen(marine_name) + 1];		
//		strcpy(_name, marine_name);
//		// - 동적으로 생성한 char[]는 언제 메모리 해제??
//		//		-> 소멸자에서 해제해주지 않으면 소멸되지 않고 메모리 누수를 발생시킴
//	
//	
//	}
//	
//	Marine::~Marine()
//	{
//		std::cout << _name << " 의 소멸자 호출 ! " << std::endl;
//		if (_name != NULL)		// NULL이면 당연히 소멸하려고하면 에러발생
//		{
//			delete[] _name;		// 배열의 동적할당 -> delete[]
//		}
//	}
//	
//	int Marine::Attack(){ return _damage; }
//	
//	void Marine::BeAttacked(int damageEarn)
//	{
//		_hp -= damageEarn;
//		if (_hp <= 0)
//			_isDead = true;
//	
//	}
//	
//	void Marine::Move(int x, int y)
//	{
//		_coordX = x;
//		_coordY = y;
//	}
//	
//	void Marine::ShowStatus()
//	{
//		std::cout << "*** Marine : " << _name << " ***" << std::endl;
//		std::cout << " Location : ( " << _coordX << " , " << _coordY << " )" << std::endl;
//		std::cout << " HP : " << _hp << std::endl;
//	}
//	
//	int main()
//	{
//		//	Marine marine1(2, 3);
//		//	Marine marine2(3, 5);
//		//	
//		//	marine1.ShowStatus();
//		//	marine2.ShowStatus();
//		//	
//		//	std::cout << std::endl << "마린1이 마린2를 공격" << std::endl;
//		//	marine2.BeAttacked(marine1.Attack());
//		//	
//		//	marine1.ShowStatus();
//		//	marine2.ShowStatus();
//		//	
//		//	/*
//		//		output
//		//	
//		//		*** Marine ***
//		//		 Location : ( 2 , 3 )
//		//		 HP : 50
//		//		*** Marine ***
//		//		 Location : ( 3 , 5 )
//		//		 HP : 50
//		//		
//		//		마린1이 마린2를 공격
//		//		*** Marine ***
//		//		 Location : ( 2 , 3 )
//		//		 HP : 50
//		//		*** Marine ***
//		//		 Location : ( 3 , 5 )
//		//		 HP : 45
//		//	*/
//	
//		//	// - 실제 스타크래프트에서 마린이 2마리밖에 없는것도 아니고 수십 수백마리가 나오는데 이렇게는 안되겠다고 판단
//		//	//		-> 배열을 이용하여 마린들을 관리
//		//	
//		//	Marine* marines[100];
//		//	
//		//	marines[0] = new Marine(2, 3);
//		//	marines[1] = new Marine(3, 5);
//		//	
//		//	marines[0]->ShowStatus();
//		//	marines[1]->ShowStatus();
//		//	
//		//	std::cout << std::endl << "마린1이 마린2를 공격" << std::endl;
//		//	
//		//	marines[0]->BeAttacked(marines[1]->Attack());
//		//	
//		//	marines[0]->ShowStatus();
//		//	marines[1]->ShowStatus();
//		//	
//		//	delete marines[0];
//		//	delete marines[1];
//		//	
//		//	// 출력은 위와 같음
//		//	
//		//	// malloc과 new/delete의 차이점 -> 객체의 동적 생성시 생성자/소멸자를 자동으로 호출해줌
//		//	// 이미 전에 언급한내용(oop_info.txt)이므로 PASS
//	
//		// 이번에는 이름까지 부여하는 생성자를 이용하여 위에 내용을 다시한번 진행
//	
//		Marine* marines[100];
//	
//		marines[0] = new Marine(2, 3, "Marine 2");
//		marines[1] = new Marine(3, 5, "Marine 1");
//	
//		marines[0]->ShowStatus();
//		marines[1]->ShowStatus();
//	
//		std::cout << std::endl << "마린1이 마린2를 공격" << std::endl;
//	
//		marines[0]->BeAttacked(marines[1]->Attack());
//	
//		marines[0]->ShowStatus();
//		marines[1]->ShowStatus();
//	
//		delete marines[0];
//		delete marines[1];
//	}


// 소멸자의 호출

//	#include <iostream>
//	
//	class Test
//	{
//	public:
//		Test(char c)
//		{
//			_c = c;
//			std::cout << "생성자 호출" << _c <<std::endl;
//		}
//		~Test() { std::cout << "소멸자 호출" << _c << std::endl; }
//	
//	private:
//		char _c;
//	};
//	
//	void Simple()
//	{
//		Test b('b');
//		Test* c = new Test('c');	// 추가
//		delete c;					// 동적 생성된 c는 여기서 소멸하지 않는한 소멸시킬 방법이 없음.....
//	}
//	
//	int main()
//	{
//		Test a('a');
//		Simple();
//	
//		/*
//			output
//	
//			생성자 호출a
//			생성자 호출b
//			소멸자 호출b
//			소멸자 호출a
//		*/	
//		
//		/*
//			- 무슨일이 일어나는가?
//				1) main()에서 객체a 생성
//				2) Simple()함수 호출
//				3) Simple()함수 내부에서 객체b 생성
//				4) !!!!!!!  Simple()함수가 종료되면서 지역 객체였던 b가 소멸됨  !!!!!!!
//				5) main()이 종료되면서 객체a 가 소멸됨
//	
//			- 동적생성된 c가 추가되었을때
//				output
//	
//				생성자 호출a
//				생성자 호출b
//				생성자 호출c
//				소멸자 호출b
//				소멸자 호출a
//	
//				-> c의 소멸자는 호출되지 않음!!!!!!!!!!!!
//				-> c는 지역 객체가 아닌 동적으로 생성된 객체이므로 함수 내부 변수/객체들의 생명주기와 무관하게 작동하는것으로 보임
//				-> 함수의 스택이 아닌 모두가 공유하는 힙에 객체가 생성되기 때문
//				-> 때문에 힙에 함부로 막 객체를 생성시키는것은 상당한 주의를 요구함
//				-> 이거때문에 메모리 누수가 자주 발생하므로 항상 주의가 필요함
//	
//		
//		*/
//	
//	
//	}

// 복사 생성자