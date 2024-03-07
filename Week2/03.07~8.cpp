
/*
	03.07 ������ �ʱ�ȭ ����Ʈ(initializer list)
	03.08 
*/


// ������ �ʱ�ȭ ����Ʈ(initializer list) - ������ ���� marine�� ��Ȱ��

#include <iostream>
#include <initializer_list>

class Marine
{
	// �̹� marine�� ����� �ڵ��� ���̹� �������� ���󰡺�
public:
	Marine();
	Marine(int x, int y);

	int attack();
	void be_attacked(int damage_earn);
	void move(int x, int y);

	void show_status();

private:
	int hp;
	int coord_x, coord_y;
	//int damage;
	bool is_dead;

	const int default_damage;
};

// : �ڿ� �����͵��� �ʱ�ȭ ����Ʈ
Marine::Marine() : hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) 
{
	//	default_damage = 5;		// const�̹Ƿ� �翬�� �Ұ�����. ���⼭ �鳯 �õ��غ��� �ȵ�
}

// �ʱ�ȭ ����Ʈ�� ��� �ٹٲ޵� OK
Marine::Marine(int x, int y)
	: coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) {}

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
}

int main()
{
	Marine marine1(2, 3);
	Marine marine2(3, 5);

	marine1.show_status();
	marine2.show_status();

	std::cout << std::endl << "���� 1 �� ���� 2 �� ���� " << std::endl;
	marine2.be_attacked(marine1.attack());

	marine1.show_status();
	marine2.show_status();

	/*
		output

		  *** Marine ***
		  Location : ( 2 , 3 )
		  HP :   50
		  *** Marine ***
		  Location : ( 3 , 5 )
		  HP :   50
		
		���� 1 �� ���� 2 �� ����
		 *** Marine ***
		 Location : ( 2 , 3 )
		 HP :   50
		 *** Marine ***
		 Location : ( 3 , 5 )
		 HP :   45
	*/

	/*
		- �ʱ�ȭ ����Ʈ (Initializer list)
			- ���� ������ �ڿ� : ���ķ� ������ �͵��� �ʱ�ȭ ����Ʈ
				-> Marine::Marine() : "hp(50), coord_x(0), coord_y(0), damage(5), is_dead(false)" <- �̰�
			- �ʱ�ȭ ����Ʈ�� ����ϸ� �������� ȣ��� ���ÿ� ��� �������� �ʱ�ȭ����
			- ���� : T::T() : var1(arg1), var2(arg2), ... {}
			- arg�� var�� �̸��� ���Ƶ� �������� �۵���
				- ���࿡ �������� ���� �̸��� ��������� �̸��� ���� coord_x, coord_y�� ���´ٸ�
					- �ʱ�ȭ ����Ʈ�� ��ȣ �ȿ���(coord_x)�� �Է��ϸ� ���ڷ� ���� ������ �켱������ ��Ī��
					- �� �ܿ��� ��� ������ �ǹ���
						-> �Ϲ������δ� �� ���� Ȯ���� �����ϱ� ���� ������� �̸��� ��Ģ�� �ְų� this�����͸� ����ϴ� ����
			- �̰� �־�?
				- �ʱ�ȭ ����Ʈ�� ������� ������ �켱 ��ü�� ���� �����ϰ� �״����� ���Ե� -> int a; a = 10; �� ���� ����
				- �ʱ�ȭ ����Ʈ�� ����ϸ� "������ ���ÿ� �ʱ�ȭ��" -> int a = 10; �� ���� ����
				- �ƴ� �׷��� �̰� ���� �־�?
					-> ����� ���ÿ� �ʱ�ȭ �Ǿ���ϴ� �͵��� ������ �����(���(const), ���۷���(&), ��� Ŭ���� ���)
					-> ����� ���ÿ� �ʱ�ȭ�Ǿ��ϴµ� �ʱ�ȭ ����Ʈ�� ������� ������ ������ ������ �߻��ϰԵǹǷ� �ݵ�� ����ؾ���
						-> const int�� default_damage �� �ʱ�ȭ����Ʈ�� �̿����� �ʴ°��
							- E0366: "Marine::Marine()"��(��) ������ ���� �̴ϼȶ������� �������� �ʽ��ϴ�.
							- C2789: 'Marine::default_damage': const ���� ������ ��ü�� �ʱ�ȭ�ؾ� �մϴ�.
	*/
}