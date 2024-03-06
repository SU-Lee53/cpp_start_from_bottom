
/*
	03.05 �Ҹ���, ��Ÿũ����Ʈ �ǽ�
	03.06 
*/

// ��Ÿũ����Ʈ �ǽ�

//	#include <iostream>
//	
//	class Marine
//	{
//	public:
//		Marine();				// �⺻ ������
//		Marine(int x, int y);	// x,y ��ǥ�� ���� ����
//		Marine(int x, int y, const char* marine_name);	// x,y ��ǥ�� ���� ���� + �̸����� ����
//	
//		~Marine();
//	
//		int Attack();							// ������ ����
//		void BeAttacked(int damageEarn);		// �Դ� ������
//		void Move(int x, int y);				// ���ο� ��ġ
//	
//		void ShowStatus();		// ���� ǥ��
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
//	// strcpy�� ������ �߻���Ŵ
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
//		// - �������� ������ char[]�� ���� �޸� ����??
//		//		-> �Ҹ��ڿ��� ���������� ������ �Ҹ���� �ʰ� �޸� ������ �߻���Ŵ
//	
//	
//	}
//	
//	Marine::~Marine()
//	{
//		std::cout << _name << " �� �Ҹ��� ȣ�� ! " << std::endl;
//		if (_name != NULL)		// NULL�̸� �翬�� �Ҹ��Ϸ����ϸ� �����߻�
//		{
//			delete[] _name;		// �迭�� �����Ҵ� -> delete[]
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
//		//	std::cout << std::endl << "����1�� ����2�� ����" << std::endl;
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
//		//		����1�� ����2�� ����
//		//		*** Marine ***
//		//		 Location : ( 2 , 3 )
//		//		 HP : 50
//		//		*** Marine ***
//		//		 Location : ( 3 , 5 )
//		//		 HP : 45
//		//	*/
//	
//		//	// - ���� ��Ÿũ����Ʈ���� ������ 2�����ۿ� ���°͵� �ƴϰ� ���� ���鸶���� �����µ� �̷��Դ� �ȵǰڴٰ� �Ǵ�
//		//	//		-> �迭�� �̿��Ͽ� �������� ����
//		//	
//		//	Marine* marines[100];
//		//	
//		//	marines[0] = new Marine(2, 3);
//		//	marines[1] = new Marine(3, 5);
//		//	
//		//	marines[0]->ShowStatus();
//		//	marines[1]->ShowStatus();
//		//	
//		//	std::cout << std::endl << "����1�� ����2�� ����" << std::endl;
//		//	
//		//	marines[0]->BeAttacked(marines[1]->Attack());
//		//	
//		//	marines[0]->ShowStatus();
//		//	marines[1]->ShowStatus();
//		//	
//		//	delete marines[0];
//		//	delete marines[1];
//		//	
//		//	// ����� ���� ����
//		//	
//		//	// malloc�� new/delete�� ������ -> ��ü�� ���� ������ ������/�Ҹ��ڸ� �ڵ����� ȣ������
//		//	// �̹� ���� ����ѳ���(oop_info.txt)�̹Ƿ� PASS
//	
//		// �̹����� �̸����� �ο��ϴ� �����ڸ� �̿��Ͽ� ���� ������ �ٽ��ѹ� ����
//	
//		Marine* marines[100];
//	
//		marines[0] = new Marine(2, 3, "Marine 2");
//		marines[1] = new Marine(3, 5, "Marine 1");
//	
//		marines[0]->ShowStatus();
//		marines[1]->ShowStatus();
//	
//		std::cout << std::endl << "����1�� ����2�� ����" << std::endl;
//	
//		marines[0]->BeAttacked(marines[1]->Attack());
//	
//		marines[0]->ShowStatus();
//		marines[1]->ShowStatus();
//	
//		delete marines[0];
//		delete marines[1];
//	}


// �Ҹ����� ȣ��

//	#include <iostream>
//	
//	class Test
//	{
//	public:
//		Test(char c)
//		{
//			_c = c;
//			std::cout << "������ ȣ��" << _c <<std::endl;
//		}
//		~Test() { std::cout << "�Ҹ��� ȣ��" << _c << std::endl; }
//	
//	private:
//		char _c;
//	};
//	
//	void Simple()
//	{
//		Test b('b');
//		Test* c = new Test('c');	// �߰�
//		delete c;					// ���� ������ c�� ���⼭ �Ҹ����� �ʴ��� �Ҹ��ų ����� ����.....
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
//			������ ȣ��a
//			������ ȣ��b
//			�Ҹ��� ȣ��b
//			�Ҹ��� ȣ��a
//		*/	
//		
//		/*
//			- �������� �Ͼ�°�?
//				1) main()���� ��üa ����
//				2) Simple()�Լ� ȣ��
//				3) Simple()�Լ� ���ο��� ��üb ����
//				4) !!!!!!!  Simple()�Լ��� ����Ǹ鼭 ���� ��ü���� b�� �Ҹ��  !!!!!!!
//				5) main()�� ����Ǹ鼭 ��üa �� �Ҹ��
//	
//			- ���������� c�� �߰��Ǿ�����
//				output
//	
//				������ ȣ��a
//				������ ȣ��b
//				������ ȣ��c
//				�Ҹ��� ȣ��b
//				�Ҹ��� ȣ��a
//	
//				-> c�� �Ҹ��ڴ� ȣ����� ����!!!!!!!!!!!!
//				-> c�� ���� ��ü�� �ƴ� �������� ������ ��ü�̹Ƿ� �Լ� ���� ����/��ü���� �����ֱ�� �����ϰ� �۵��ϴ°����� ����
//				-> �Լ��� ������ �ƴ� ��ΰ� �����ϴ� ���� ��ü�� �����Ǳ� ����
//				-> ������ ���� �Ժη� �� ��ü�� ������Ű�°��� ����� ���Ǹ� �䱸��
//				-> �̰Ŷ����� �޸� ������ ���� �߻��ϹǷ� �׻� ���ǰ� �ʿ���
//	
//		
//		*/
//	
//	
//	}

// ���� ������ -> ��ü�� 1���� ����� �װ� �����ؼ� �������� ��ü�� ����� ���

//	#pragma warning (disable: 4996)
//	#include <iostream>
//	#include <string>
//	
//	class PhotonCannon
//	{
//	public:
//		PhotonCannon(int x, int y);
//		PhotonCannon(int x, int y, const char* name);
//		PhotonCannon(const PhotonCannon& pc);	// ���� ������
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
//		std::cout << "���� ������ ȣ��" << std::endl;
//		_hp = pc._hp;
//		_shield = pc._shield;
//		_coordX = pc._coordX;
//		_coordY = pc._coordY;
//		_damage = pc._damage;
//	
//		// ���� ����
//		_name = new char[strlen(pc._name) + 1];
//		strcpy(_name, pc._name);
//	
//		//	pc._damage = 30;	
//		//	// �����߻�
//		//	// E0137: ���� ������ �� �ִ� lvalue���� �մϴ�.
//		//	// C3490: '_damage'��(��) const ��ü�� ���� �׼����ǰ� �����Ƿ� ������ �� �����ϴ�.
//	}
//	
//	PhotonCannon::PhotonCannon(int x, int y)
//	{
//		std::cout << "������ ȣ��" << std::endl;
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
//		std::cout << "������ ȣ��" << std::endl;
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
//		PhotonCannon pc1(3, 3, "Cannon");		// �Ϲ� ������ ȣ���
//		PhotonCannon pc2(pc1);		// ���� ������ ȣ���
//		PhotonCannon pc3 = pc2;		// ���� ������ ȣ���
//		// PhotonCannon pc3(pc2); �� ������ �ǹ̷� �����ϵ�
//		// �翬�� pc3 = pc2 �ʹ� ������ �ٸ�
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
//			������ ȣ��
//			���� ������ ȣ��		-> pc2
//			���� ������ ȣ��		-> pc3
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
//			- ���� ������
//				- ǥ�� ���� : T(const T& a); (T = Ŭ���� �̸�)
//					-> �ٸ� T ��ü a�� ��� ���۷���(const)�� �޾ƿ�
//					-> const�� �������� ���Ͽ� ���� ������ ���ο����� a�� �����͸� ���� �Ұ�, ���ο� �ν��ϼ� �������ٰ� '����'�� ��������
//					-> ��� �����ʹ� https://modoocode.com/24�� ����
//	
//				- ����Ʈ ���� �����ڵ� ������. �׷��� �Ѱ谡 ����
//					-> char* _name�� �߰��ϰ� ���� ���� ���� �����ڸ� ����� �����غ��� ��Ÿ�� ������ �߻��Ѵ�
//					- �������� �Ͼ�°�?
//						1) PhotonCannon pc1(3, 3, "Cannon");	-> _name = Cannon�� ���� ��ü�� �ϳ� ����. _name�� Ÿ���� char*
//						2) PhotonCannon pc2(pc1);				-> pc1�� �����Ͽ� ������ pc2�� ������. pc2�� _name�� ���������� Cannon
//						3)	  pc1._name			  pc2._name
//								 |					 |
//								 |					 |
//								 |					 |
//								 ------> Cannon <-----
//							���� ���� ���·� "pc1�� pc2�� ���� �ּҰ��� ����Ű�� ����
//							-> ���� �����Ͽ� ������� Ȯ���غ� ���(�翬�� �ּҴ� �����Ҷ����� �޶���)
//								- pc1._name -> 0x0000020c74633620 "Cannon"
//								- pc2._name -> 0x0000020c74633620 "Cannon"
//						
//						!!!!!! ���⼭���� �߿� !!!!!!
//						4) main()�� ����ǰ� pc1�� �Ҹ��ڰ� ���� ȣ��� -> pc1._name�� ����Ű�� �ִ� ��ġ�� �޸� ����
//							  pc1._name			  pc2._name
//								 |					 |
//								 |					 |
//								 |					 |
//								 ------> ������ <-----
//						5) pc1�� �Ҹ�ǰ� ���� pc2�� �Ҹ��ڰ� ȣ��
//						6) !!!!! "pc2._name�� �̹� �Ҹ�ǰ� ����" !!!!!	
//						7) "�̹� ������ �޸�"�� �����Ͽ� "�ٽ� ����"�Ϸ��� �� -> ���⼭ ��Ÿ�� ������ �߻�!!!!!!!!!!!!
//	
//					- ���� ���� ������ �ذ��: ���� ����(Deep Copy) -> �״�� �������� �ʰ� �ٸ� �޸𸮿� ���� �Ҵ��� �ؼ� ���븸 �����ؿ´�
//							  pc1._name				  pc2._name
//								 |						 |
//								 |						 |
//								 |						 |
//								 ------> Cannon			 ------> Cannon		==> 2���� Cannon�� ������ �޸� ������ ������
//						�� ���� ����(Deep Copy)		: "���� ��"�� "���ο� �޸�" ������ ����
//						�� ���� ����(Shallow Copy)	: "�ּ� ��"�� ����
//						- ����Ʈ ���� �����ڴ� ���� ���縸 �����ϹǷ� ���� ���簡 �ʿ��� ��� ���� �����ڸ� ���� ��������
//							  
//		*/
//	
//	
//	}