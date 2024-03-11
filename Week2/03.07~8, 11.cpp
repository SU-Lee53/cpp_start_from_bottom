
/*
	03.07 ������ �ʱ�ȭ ����Ʈ(initializer list)
	03.08 const, static
	03.11 ���۷����� �����ϴ� �Լ�, this, const ����Լ�
*/


//	������ �ʱ�ȭ ����Ʈ(initializer list) - ������ ���� marine�� ��Ȱ��
//	static, const

#include <iostream>

class Marine
{
	// �̹� marine�� ����� �ڵ��� ���̹� �������� ���󰡺�
public:
	Marine();
	Marine(int x, int y);
	Marine(int x, int y, int default_damage);

	~Marine() { total_marine_num--; }

	int attack() const;		// ��� ��� �Լ�
	//	void be_attacked(int damage_earn);
	Marine& be_attacked(int damage_earn);
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

Marine& Marine::be_attacked(int damage_earn)
{
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;

	return *this;
}

void Marine::move(int x, int y)
{
	coord_x = x;
	coord_y = y;
}

int Marine::attack() const { return default_damage; }

//	void Marine::be_attacked(int damage_earn)
//	{
//		hp -= damage_earn;
//		if (hp <= 0) is_dead = true;
//	}

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
	Marine::show_total_marine();
}


int main()
{
	// �ʱ�ȭ ����Ʈ
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
						++ const�� ����� ���ϸ� �ȵǴ� ���� ����� �Ǽ��ϴ��� �����Ϸ��� ������ ���⶧���� �ſ�ſ� ����.
	*/

	Marine marine1(2, 3, 5);
	Marine::show_total_marine();

	Marine marine2(3, 5, 10);
	Marine::show_total_marine();

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

		 ��ü ���� �� : 1
		 ��ü ���� �� : 2
		 ��ü ���� �� : 3	-> �Լ� ����(create_marine)�� �Բ� ��ü�� �Ҹ�Ǿ� �������� 2�� ������
		
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

	// static
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

	std::cout << std::endl << "���� 1�� ���� 2�� 2�� ����" << std::endl;
	marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack());

	marine1.show_status();
	marine2.show_status();
	
	/*
		output

		���� 1�� ���� 2�� 2�� ����
		 *** Marine ***
		 Location : ( 2 , 3 )
		 HP :   50
		 ���� �� ���� �� : 2
		 *** Marine ***
		 Location : ( 3 , 5 )
		 HP :   35
		 ���� �� ���� �� : 2
	
	*/


	// this
	/*
		- this: ��ü �ڽ��� ����Ű�� ������
			- ��� �������� ���ǵǾ��ִ� C++�� Ű����(python�� self�� ����ϰ� �����ϸ� �ɵ���)
			- ��� ��� �Լ� �������� this Ű���尡 ���ǵǾ� ������ �翬�� static �Լ��� thisŰ���尡 ���ǵǾ����� ����
				-> �׷��Ƿ� be_attacked()�� ���δ� �����̶� �Ȱ���
					Marine& Marine::be_attacked(int damage_earn)
					{
						this->hp -= damage_earn;
						if (this->hp <= 0) this->is_dead = true;
					
						return *this;
					}

	*/

	// ���۷����� �����ϴ� �Լ�
	/*
		- ���۷����� �����ϴ� �Լ� -> �Ʒ� ������ ���� ����
			- ���⼭�� be_attacked()�� Marine& �� ������
			- ���ϵǴ� ���� *this ��, �ڱ� �ڽ��̹Ƿ� ��ó�� 2�� �´� ����� ��������

			- ���۷����� �ƴ� �Ϲ� Marine ��ü�� �����Ѵٸ�?
				-> ù��°�� ȣ��� be_attacked()���� �ѹ� �ĸ��� �ڱ� �ڽ�(*this)�� �����ؼ� ������
				-> ����� �ӽð�ü�� ���ѹ� �°Ե�
				-> �ᱹ ������� marine2�� �Ѵ븸 �°� ������ �Ѵ�� ����� �������� ��� �ӽ� ��ü�� �´°�
	
	*/

	// const ����Լ�
	/*
		- const ����Լ� : ��ü���� "�б�" ���� �����. �� �ٸ� ������ ���� �ٲ� �� ���� �Լ�
			- �� ������ attack ����Լ��� const ����Լ�
			- (���� �Լ� ����) const; ���·� ����
			- ���ǿ��� const���� ������־����. ����� static�� �����൵ ��
			- ��� �Լ� �������� ��� �Լ��� ȣ���� �� ����
			++ �Ϲ������δ� ��������� �� private�� ����ְ� get_x()���� �Լ��� pubic���� ����� ���Ϲ޴� ����� ��
			++ �̷��� �ϸ� const ����Լ��� ��� �ٸ� ������ ������ �����鼭 �ش� ������ ������ �� ����

	
	*/


}


// ���۷����� �����ϴ� �Լ�
//	#include <iostream>
//	
//	class A
//	{
//	public:
//		A(int c) : x(c) {}
//	
//		int& access_x() { return x; }
//		int get_x() { return x; }
//		void show_x() { std::cout << "x : "  << x << std::endl; }
//		void show_address_x() { std::cout << "&x : " << &x << std::endl; }
//	
//	private:
//		int x;
//	};
//	
//	int main()
//	{
//		A a(5);
//		a.show_x();
//	
//		std::cout << std::endl << "int& c = a.access_x()" << std::endl;
//		int& c = a.access_x();
//		c = 4;
//		a.show_x();
//		std::cout << "&c : " << &c << std::endl;
//		a.show_address_x();
//	
//		std::cout << std::endl << "int d = a.access_x()" << std::endl;
//		int d = a.access_x();
//		d = 3;
//		a.show_x();
//		std::cout << "&d : " << &d << std::endl;
//		a.show_address_x();
//	
//		//	int& e = a.get_x();		// E0461: ��const ������ ���� �ʱ� ���� lvalue���� �մϴ�.
//		//	e = 2;
//		//	a.show_x();
//	
//		std::cout << std::endl << "int f = a.get_x()" << std::endl;
//		int f = a.get_x();
//		f = 1;
//		a.show_x();
//		std::cout << "&f : " << &f << std::endl;
//		a.show_address_x();
//	
//		std::cout << std::endl << "a.access_x() = 0" << std::endl;
//		a.access_x() = 0;
//		a.show_x();
//	
//		//	a.get_x() = 0;	// E0137: ���� ������ �� �ִ� lvalue���� �մϴ�.
//	
//		/*
//			output
//	
//			x : 5
//	
//			int& c = a.access_x()
//			x : 4
//			&c : 00000053305AF984
//			&x : 00000053305AF984
//			
//			int d = a.access_x()
//			x : 4
//			&d : 00000053305AF9C4
//			&x : 00000053305AF984
//			
//			int f = a.get_x()
//			x : 4
//			&f : 00000053305AF9E4
//			&x : 00000053305AF984
//			
//			a.access_x() = 0
//			x : 0
//		
//		*/
//	
//		/*
//			- ���۷����� �����ϴ� �Լ�
//				- �� ������ ����
//					- A Ŭ�������� ��� ���� int x, ���۷����� �����ϴ� access_x(), ���� �����ϴ� get_x(), x�� ���� ����ϴ� show_x() 4������ ������ 
//	
//					- int& c = a.access_x(); 
//						-> ���۷��� c�� x�� ���۷����� ���� -> c�� x�� "����(alias)"�� ��
//						-> ���۷����� �����ϴ� �Լ��� �� �Լ� �κ��� ������ ������ ġȯ�ߴٰ� �����ص� ������
//						-> ���� �� �ڵ�� int& c = x;�� ������
//						-> �׷��Ƿ� c�� ���� �ٲٴ� ���� a.x�� ���� �ٲٴ� �Ͱ� ������ �ǹ���. show_x() ����� Ȯ���غ��� ���� �ٲ������
//	
//					- int d = a.access_x(); 
//						-> �̹����� int ������ a.x�� ���۷����� �� -> �� d�� a.x�� ���� ���簡 �Ͼ
//						-> d�� x�� �������̹Ƿ� d�� ���� �����ص� x���� ������ ����
//	
//					- int& e = a.get_x(); 
//						-> (�ּ� ó���� �κ�) ���۷��� e�� a�� ���� ���� -> ���� �߻�
//						- ��?
//							-> ���۷����� �ƴ� ���� �����ϴ� �Լ��� ��� "���� ����"�� ���� "�ӽ� ��ü"�� ������
//							-> �� "�ӽ� ��ü"�� ���۷����� ���� �� ����! ������ ������ �ӽ� ��ü�� �Ҹ�Ǳ� ����
//							-> �Ʒ�ó�� �����غ��� ��
//								- access_x() -----> return a.x
//								- get_x() --------> �ӽð�ü int(a.x�� ������ x')�� ���� --------> return �ӽ� ��ü�� ����� x' ---------> �ӽ� ��ü �Ҹ�
//							-> ��Ȯ���� int&�� �������� ���� ���۷���, a.get_x()�� �������̶� �ȵȴٴµ� �̺κ��� ���� �� �𸣹Ƿ� PASS https://modoocode.com/189
//		
//					- int f = a.get_x();
//						-> int f�� a.x�� ���� ����
//						-> ����Ǿ� �� �������� �����̹Ƿ� f ���� ������ a.x���� ������ ��ġ�� ����
//	
//					- a.access_x() = 0;
//						-> �� ǥ����� a.x = 3; �� ������
//		
//		*/
//	
//		return 0;
//	}

