
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

// ���� ������