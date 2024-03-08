
/*
	03.07 ������ �ʱ�ȭ ����Ʈ(initializer list)
	03.08 
*/


// ������ �ʱ�ȭ ����Ʈ(initializer list) - ������ ���� marine�� ��Ȱ��
// static

#include <iostream>
#include <initializer_list>

class Marine
{
	// �̹� marine�� ����� �ڵ��� ���̹� �������� ���󰡺�
public:
	Marine();
	Marine(int x, int y);
	Marine(int x, int y, int default_damage);

	~Marine() { total_marine_num--; }

	int attack();
	void be_attacked(int damage_earn);
	void move(int x, int y);

	void show_status();

	static void show_total_marine();

private:
	int hp;
	int coord_x, coord_y;
	//int damage;
	bool is_dead;

	const int default_damage;

	static int total_marine_num;	// static ������ ���⼭ �ٷ� �ʱ�ȭ�� �Ұ�����
									// �ٷ� �ʱ�ȭ �õ��� 
									// -> E1592: in-class initializer�� �ִ� ����� const���� �մϴ�.
									// -> C2864: 'Marine::total_marine_num': in-class initializer�� �ִ� ���� ������ �����(��) volatile�� �ƴ� const ���� ������ �����ϰų� 'inline'���� �����Ǿ�� �մϴ�.
	
	const static int test = 0;		// const static ������ �ٷ� �ʱ�ȭ�� ����;

};

int Marine::total_marine_num = 0;	// static ������ �ʱ�ȭ ���

// : �ڿ� �����͵��� �ʱ�ȭ ����Ʈ
Marine::Marine() : hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) 
{
	//	default_damage = 5;		// const�̹Ƿ� �翬�� �Ұ�����. ���⼭ �鳯 �õ��غ��� �ȵ�
	total_marine_num++;
}

// �ʱ�ȭ ����Ʈ�� ��� �ٹٲ޵� OK
Marine::Marine(int x, int y)
	: coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) 
{
	total_marine_num++;
}

// const ��� ��� ������ �޾ƿ� ���ڸ� ����־ �ʱ�ȭ ����
Marine::Marine(int x, int y, int default_damage)
	: coord_x(x),
	coord_y(y),
	hp(50),
	default_damage(default_damage),
	is_dead(false) 
{
	total_marine_num++;
}

void Marine::move(int x, int y)
{
	coord_x = x;
	coord_y = y;
}

int Marine::attack() { return default_damage; }

void Marine::be_attacked(int damage_earn)
{
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;
}

void Marine::show_status()
{
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP :	" << hp << std::endl;
	std::cout << " ���� �� ���� �� : " << total_marine_num << std::endl;
}

void Marine::show_total_marine()
{
	//	std::cout << default_damage << std::endl;	// E0245: ������ ��� ������ Ư�� ��ü�� ������̾�� �մϴ�. -> �� default_damage�� ��������...
	std::cout << "��ü ���� �� : " << total_marine_num << std::endl;
}

void create_marine()
{
	Marine marine3(10, 10, 4);
	marine3.show_status();
	Marine::show_total_marine();
}


int main()
{
	// �ʱ�ȭ ����Ʈ

	//	Marine marine1(2, 3, 10);
	//	Marine marine2(3, 5, 10);
	//	
	//	marine1.show_status();
	//	marine2.show_status();
	//	
	//	std::cout << std::endl << "���� 1 �� ���� 2 �� ���� " << std::endl;
	//	marine2.be_attacked(marine1.attack());
	//	
	//	marine1.show_status();
	//	marine2.show_status();
	//	
	//	/*
	//		output
	//	
	//		  *** Marine ***
	//		  Location : ( 2 , 3 )
	//		  HP :   50
	//		  *** Marine ***
	//		  Location : ( 3 , 5 )
	//		  HP :   50
	//		
	//		���� 1 �� ���� 2 �� ����
	//		 *** Marine ***
	//		 Location : ( 2 , 3 )
	//		 HP :   50
	//		 *** Marine ***
	//		 Location : ( 3 , 5 )
	//		 HP :   40
	//	*/
	//	
	//	/*
	//		- �ʱ�ȭ ����Ʈ (Initializer list)
	//			- ���� ������ �ڿ� : ���ķ� ������ �͵��� �ʱ�ȭ ����Ʈ
	//				-> Marine::Marine() : "hp(50), coord_x(0), coord_y(0), damage(5), is_dead(false)" <- �̰�
	//			- �ʱ�ȭ ����Ʈ�� ����ϸ� �������� ȣ��� ���ÿ� ��� �������� �ʱ�ȭ����
	//			- ���� : T::T() : var1(arg1), var2(arg2), ... {}
	//			- arg�� var�� �̸��� ���Ƶ� �������� �۵���
	//				- ���࿡ �������� ���� �̸��� ��������� �̸��� ���� coord_x, coord_y�� ���´ٸ�
	//					- �ʱ�ȭ ����Ʈ�� ��ȣ �ȿ���(coord_x)�� �Է��ϸ� ���ڷ� ���� ������ �켱������ ��Ī��
	//					- �� �ܿ��� ��� ������ �ǹ���
	//						-> �Ϲ������δ� �� ���� Ȯ���� �����ϱ� ���� ������� �̸��� ��Ģ�� �ְų� this�����͸� ����ϴ� ����
	//			- �̰� �־�?
	//				- �ʱ�ȭ ����Ʈ�� ������� ������ �켱 ��ü�� ���� �����ϰ� �״����� ���Ե� -> int a; a = 10; �� ���� ����
	//				- �ʱ�ȭ ����Ʈ�� ����ϸ� "������ ���ÿ� �ʱ�ȭ��" -> int a = 10; �� ���� ����
	//				- �ƴ� �׷��� �̰� ���� �־�?
	//					-> ����� ���ÿ� �ʱ�ȭ �Ǿ���ϴ� �͵��� ������ �����(���(const), ���۷���(&), ��� Ŭ���� ���)
	//					-> ����� ���ÿ� �ʱ�ȭ�Ǿ��ϴµ� �ʱ�ȭ ����Ʈ�� ������� ������ ������ ������ �߻��ϰԵǹǷ� �ݵ�� ����ؾ���
	//						-> const int�� default_damage �� �ʱ�ȭ����Ʈ�� �̿����� �ʴ°��
	//							- E0366: "Marine::Marine()"��(��) ������ ���� �̴ϼȶ������� �������� �ʽ��ϴ�.
	//							- C2789: 'Marine::default_damage': const ���� ������ ��ü�� �ʱ�ȭ�ؾ� �մϴ�.
	//						++ const�� ����� ���ϸ� �ȵǴ� ���� ����� �Ǽ��ϴ��� �����Ϸ��� ������ ���⶧���� �ſ�ſ� ����.
	//	*/


	// static

	Marine marine1(2, 3, 5);
	marine1.show_status();

	Marine marine2(3, 5, 10);
	marine2.show_status();

	create_marine();

	std::cout << std::endl << "����1 �� ����2 �� ���� " << std::endl;
	marine2.be_attacked(marine1.attack());

	marine1.show_status();
	marine2.show_status();

	//	total_marine_num�� public���� �ű�� �ּҸ� ����
	//	std::cout << &marine1.total_marine_num << std::endl;
	//	std::cout << &marine2.total_marine_num << std::endl;

	/*
		output

		 *** Marine ***
		 Location : ( 2 , 3 )
		 HP :   50
		 ���� �� ���� �� : 1
		 *** Marine ***
		 Location : ( 3 , 5 )
		 HP :   50
		 ���� �� ���� �� : 2
		 *** Marine ***
		 Location : ( 10 , 10 )
		 HP :   50
		 ���� �� ���� �� : 3	-> �Լ� ����(create_marine)�� �Բ� ��ü�� �Ҹ�Ǿ� �������� 2�� ������
		
		����1 �� ����2 �� ����
		 *** Marine ***
		 Location : ( 2 , 3 )
		 HP :   50
		 ���� �� ���� �� : 2
		 *** Marine ***
		 Location : ( 3 , 5 )
		 HP :   45
		 ���� �� ���� �� : 2

		00007FF629CCF174
		00007FF629CCF174
	*/

	/*
		- static
			- ������ �ǹ�: ������, ������, ������
			
			- ���� ���α׷� ������ ������ ������ �Ѵ�
				- ù��° ���: ������ �����ϴ� �迭�� ����� ������ ������ ������ ��� ����. X
					-> ������ �󸶳� ������ �˰� �迭���� ��������? (���� vector�� ����� ����)
				- �ι�° ���: � ������ ���� ������ ����/�Ҹ�� ++/--. 
					-> ������ ��� ������ΰ�
						- �Լ��� ���������� -> �ٸ� �Լ����� �̿��Ϸ��� �Ź� ���ڷ� �޾ƾ��ϹǷ� ��������
						- ���������� -> �ǵ��� ��¥ ��¿�� �������� ���°� ����
							-> �̶� ����� �� �ִ°��� �ٷ� static ����

			- static
				- C���� : ����� ����(scope)�� ������� �Ҹ���� �ʴ� ����
				- C++���� : Ư�� �ν��Ͻ��� ������ �ʴ� Ŭ���� �������� ����(declarations of class members not bound to specific instances) - cppreference
					-> Ư�� �ν��Ͻ��� ������ �ʴ´� : Ŭ������ static ��������� �ش� Ŭ������ ��� ��ü���� '����'��
						-> ��� ��ü(�ν��Ͻ�)���� '�� �ϳ�'�� static ��� ������ ����
						-> total_marine_num�� public���� �ű�� marine1�� marine2���� �ּҸ� Ȯ���غ��� ���� �ּҸ� ����Ű������
				- static ������ Ŭ���� ���ο��� �ٷ� �ʱ�ȭ�� �� ����. ��� �ڵ����� 0���� �ʱ�ȭ��
					-> �ʱ�ȭ�� �ʿ��� ��� Ŭ���� �ܺο��� �ʱ�ȭ�ؾ���
					-> �������� Ŭ���� �ܺο��� int Marine::total_marine_num = 0; �� �ʱ�ȭ�ǰ�����
					-> �ٸ� const static ������ Ŭ���� ���ο��� �ٷ� �ʱ�ȭ�� ������
				
				- static �Լ� ���� ����. ���������� �� �ϳ��� �����ϰ� ��ü�� ���ӵ��� ����
				- static �Լ��� ��ü ���̵� �ٷ� Ŭ���� ��ü���� ȣ���� ������.
					-> (Ŭ����)::(�Լ��̸�)���� �ٷ� ȣ��
				- Ư�� ��ü�� ���ӵ��� �����Ƿ� static �Լ��� static ������ �̿��� �� ����.
	*/

	Marine::show_total_marine();

}