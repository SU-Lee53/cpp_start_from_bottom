
/*
	03.05 소멸자, 스타크래프트 실습
	03.06 복사 생성자
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

// 복사 생성자 -> 객체를 1개만 만들고 그걸 복사해서 여러개의 객체를 만드는 방법

//	#pragma warning (disable: 4996)
//	#include <iostream>
//	#include <string>
//	
//	class PhotonCannon
//	{
//	public:
//		PhotonCannon(int x, int y);
//		PhotonCannon(int x, int y, const char* name);
//		PhotonCannon(const PhotonCannon& pc);	// 복사 생성자
//	
//		~PhotonCannon();
//	
//		void ShowStatus();
//	
//		void ShowNameAddress() { printf("0x%.16x \n", _name); }
//	
//	private:
//		int _hp, _shield;
//		int _coordX, _coordY;
//		int _damage;
//	
//		char* _name;
//	};
//	
//	PhotonCannon::PhotonCannon(const PhotonCannon& pc)
//	{
//		std::cout << "복사 생성자 호출" << std::endl;
//		_hp = pc._hp;
//		_shield = pc._shield;
//		_coordX = pc._coordX;
//		_coordY = pc._coordY;
//		_damage = pc._damage;
//	
//		// 깊은 복사
//		_name = new char[strlen(pc._name) + 1];
//		strcpy(_name, pc._name);
//	
//		//	pc._damage = 30;	
//		//	// 오류발생
//		//	// E0137: 식이 수정할 수 있는 lvalue여야 합니다.
//		//	// C3490: '_damage'은(는) const 개체를 통해 액세스되고 있으므로 수정할 수 없습니다.
//	}
//	
//	PhotonCannon::PhotonCannon(int x, int y)
//	{
//		std::cout << "생성자 호출" << std::endl;
//		_hp = _shield = 100;
//		_coordX = x;
//		_coordY = y;
//		_damage = 20;
//	
//		_name = NULL;
//	}
//	
//	PhotonCannon::PhotonCannon(int x, int y, const char* name)
//	{
//		std::cout << "생성자 호출" << std::endl;
//		_hp = _shield = 100;
//		_coordX = x;
//		_coordY = y;
//		_damage = 20;
//	
//		_name = new char[strlen(name) + 1];
//		strcpy(_name, name);
//	}
//	
//	PhotonCannon::~PhotonCannon()
//	{
//		if (_name) delete[] _name;
//	}
//	
//	void PhotonCannon::ShowStatus()
//	{
//		std::cout << "Photon Cannon " << std::endl;
//		std::cout << " Location : ( " << _coordX << " , " << _coordY << " ) " << std::endl;
//		std::cout << " HP : " << _hp << std::endl;
//	}
//	
//	int main()
//	{
//		PhotonCannon pc1(3, 3, "Cannon");		// 일반 생성자 호출됨
//		PhotonCannon pc2(pc1);		// 복사 생성자 호출됨
//		PhotonCannon pc3 = pc2;		// 복사 생성자 호출됨
//		// PhotonCannon pc3(pc2); 와 동일한 의미로 컴파일됨
//		// 당연히 pc3 = pc2 와는 엄연히 다름
//	
//		pc1.ShowStatus();
//		pc2.ShowStatus();
//		pc3.ShowStatus();
//	
//		pc1.ShowNameAddress();
//		pc2.ShowNameAddress();
//	
//		/*
//			output
//	
//			생성자 호출
//			복사 생성자 호출		-> pc2
//			복사 생성자 호출		-> pc3
//			Photon Cannon
//			 Location : (3, 3)
//			 HP : 100
//			Photon Cannon
//			 Location : (3, 3)
//			 HP : 100
//			Photon Cannon
//			 Location : (3, 3)
//			 HP : 100
//		
//		*/
//	
//		/*
//			- 복사 생성자
//				- 표준 정의 : T(const T& a); (T = 클래스 이름)
//					-> 다른 T 객체 a를 상수 레퍼런스(const)로 받아옴
//					-> const가 붙음으로 인하여 복사 생성자 내부에서는 a의 데이터를 변경 불가, 새로운 인스턴수 변수에다가 '복사'만 가능해짐
//					-> 상수 포인터는 https://modoocode.com/24를 참고
//	
//				- 디폴트 복사 생성자도 존재함. 그러나 한계가 있음
//					-> char* _name을 추가하고 원래 만든 복사 생성자를 지운뒤 실행해보면 런타임 오류가 발생한다
//					- 무슨일이 일어나는가?
//						1) PhotonCannon pc1(3, 3, "Cannon");	-> _name = Cannon인 가진 객체가 하나 생김. _name의 타입은 char*
//						2) PhotonCannon pc2(pc1);				-> pc1를 복사하여 생성된 pc2가 생성됨. pc2의 _name도 마찬가지로 Cannon
//						3)	  pc1._name			  pc2._name
//								 |					 |
//								 |					 |
//								 |					 |
//								 ------> Cannon <-----
//							위와 같은 형태로 "pc1과 pc2는 같은 주소값을 가리키고 있음
//							-> 실제 실행하여 조사식을 확인해본 결과(당연히 주소는 실행할때마다 달라짐)
//								- pc1._name -> 0x0000020c74633620 "Cannon"
//								- pc2._name -> 0x0000020c74633620 "Cannon"
//						
//						!!!!!! 여기서부터 중요 !!!!!!
//						4) main()이 종료되고 pc1의 소멸자가 먼저 호출됨 -> pc1._name이 가리키고 있던 위치의 메모리 해제
//							  pc1._name			  pc2._name
//								 |					 |
//								 |					 |
//								 |					 |
//								 ------> 해제됨 <-----
//						5) pc1이 소멸되고 다음 pc2의 소멸자가 호출
//						6) !!!!! "pc2._name이 이미 소멸되고 없음" !!!!!	
//						7) "이미 해제된 메모리"에 접근하여 "다시 해제"하려고 함 -> 여기서 런타임 오류가 발생!!!!!!!!!!!!
//	
//					- 위와 같은 문제의 해결법: 깊은 복사(Deep Copy) -> 그대로 복사하지 않고 다른 메모리에 동적 할당을 해서 내용만 복사해온다
//							  pc1._name				  pc2._name
//								 |						 |
//								 |						 |
//								 |						 |
//								 ------> Cannon			 ------> Cannon		==> 2개의 Cannon은 별도의 메모리 공간에 생성됨
//						※ 깊은 복사(Deep Copy)		: "실제 값"을 "새로운 메모리" 공간에 복사
//						※ 얕은 복사(Shallow Copy)	: "주소 값"을 복사
//						- 디폴트 복사 생성자는 얕은 복사만 가능하므로 깊은 복사가 필요한 경우 복사 생성자를 직접 만들어야함
//							  
//				++ 03.07 추가
//				- 복사 생성자는 왜 인자를 상수 레퍼런스 (const T&)로 받을까 (soen.kr)
//					- 상수로 받는 이유는 위에서도 적혀있듯이 생성자에서 복사 대상의 데이터를 변경하는것을 막기 위함임
//					- 레퍼런스를 받는 이유 - 만약에 레퍼런스를 받지 않는다면?
//						- T(const T a)로 만들어진 복사 생성자가 있다고 생각해보자
//							- 생성자도 함수이기 때문에 인자로 받아온 a를 복사해야함
//							- 이때 a를 복사하기 위해 다시한번 복사 생성자를 호출
//								-> 위 두 과정이 무한히 반복됨. 때문에 컴파일러에서 오류를 발생시켜 이것을 원천적으로 막은것
//						- 포인터로 만드는 것은 가능하긴 하지만 컴파일러가 복사 생성자라고 인지해주지 않음.
//							-> 굳이 만들 필요도 의미도 없다
//						- 레퍼런스를 인자로 받아 만든다면 별도의 값 복사가 일어나지 않으므로 무한루프에 빠질일도 없고 컴파일러도 잘 알아먹음
// 
// 
//		*/
//		
//	
//	}