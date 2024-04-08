
/*
	04.08 is-a�� has-a ����, �������̵�, virtual�� �����Լ�, ������
*/

// is-a, has-a ����

//	/*
//		- is-a / has-a ����
//			- ��ü�� �߻�ȭ �ܰ迡�� � ��쿡 ����� �̿������� ������ �� �ִ� ���
//			- �翬�� ����������� �����ϴ� ����� �ƴϰ� ����ڰ� �ڵ��ϸ鼭 ���� �����Ͽ� �Ǵ��ϴ� ����
//			- is-a : ~ �� ~ ��! -> ����� �̿�
//				- Week6�� Manager�� Employee���踦 �����غ���
//					- Manager�� Employee�� ��� ����� �����Ѵ�
//					- Manager�� Employee�� ����� ��� �����ϹǷ� Manager�� Employee��� Ī�ص� �����ϴ�
//					- �� ��� Manager�� Employee�̴�
//					- Manager "is a" Employee -> ���
//				- �翬�� �̸� �ڹٲٸ�(Employee is a Manager)�� ���� �ȵǹǷ� ��Ӱ��谡 ��Ȯ�ϰ� ���е�
//				- ����� ���� Ŭ������ �Ļ��Ǹ� �Ļ��ɼ��� �� �� Ư��ȭ(��üȭ, specialize)�� �Ǵ� ���� �� �� ����
//					-> Manager�� Employee�̸鼭 �� �� ��ü���� �η���. �����ε� ���α׷������� ��������
//				- �ݴ�� �Ļ��� Ŭ������ ��� Ŭ������ �Ž��� �ö󰥼��� �� �� �Ϲ�ȭ(generalize)��
//					-> Manager�� �Ϲ������� Employee �̰� �����ε� ��������
//				- ������� ����� Ŭ�������� ���Ͱ��� Ư¡���� ���� ���� �ڵ� �ۼ��� �߻�ȭ�ϴ� �������� ������ �� �� ����
//			- has-a: ~ �� ~ �� ������ �ִ� -> ����� �̿����� ����
//				- �ڵ����� �����غ���
//					- �ڵ����� ������ ������ ����
//					- �ڵ����� ������ ������ ����
//					- �ڵ����� �극��ũ�� ������ ����
//					- Car is a Wheel/Engine/Brake��� ���� �� ����
//						-> Car has a Wheel/Engine/Brake�� �� ����
//				- �̷� ��쿡�� ����� �ƴ� Ŭ������ ����� �������ִ°��� ����
//	*/
//	
//	// is-a : Manager �� Employee
//	class Employee {};
//	class Manager : public Employee {};	// ����
//	
//	// has-a : �ڵ����� �μ�ǰ��
//	class Wheel {};
//	class Engine {};
//	class Brake {};
//	class Car
//	{
//		Wheel wheel;
//		Engine engine;
//		Brake brake;
//	};	// ����

// �������̵�

#include <iostream>
#include <string>

class Base
{
public:
	Base() : s("���") { std::cout << "��� Ŭ����" << std::endl; }
	
	void what() { std::cout << s << std::endl; }
private:
	std::string s;
};

class Derived : public Base
{
public:
	Derived() : s("�Ļ�"), Base() { std::cout << "�Ļ� Ŭ����" << std::endl; }

	void what() { std::cout << s << std::endl; }
private:
	std::string s;
};

int main()
{
	{
		std::cout << " === ��� Ŭ���� ���� ===" << std::endl;
		Base p;

		p.what();

		std::cout << " === �Ļ� Ŭ���� ���� === " << std::endl;
		Derived c;

		c.what();

		/*
			output
			 === ��� Ŭ���� ���� ===
			��� Ŭ����
			���
			 === �Ļ� Ŭ���� ���� ===
			��� Ŭ����
			�Ļ� Ŭ����
			�Ļ�
		*/
	}

	// ��ĳ����
	{
		Base p;
		Derived c;

		std::cout << " === ������ ���� === " << std::endl;
		Base* p_c = &c;
		p_c->what();

		/*
			output
			��� Ŭ����
			��� Ŭ����
			�Ļ� Ŭ����
			 === ������ ���� ===
			���
		*/
	}

	/*
		- �� ĳ����
			- ���� �������� Base�� �����Ϳ� Derived�� �ּҸ� �־��ִ� �κ��� ���� ���� �۵���
				- Derived�� Base�� ��ӹް� ���� -> Derived is a Base
				- �׷��� ��ü c�� Base �̱⵵ �ϹǷ� Base �����Ͱ� ����ų �� ����
				- ���� ���̰� �غ���...
					->
						Derived c -> [string s][Base()][what()] + [string s][Derived()][what()]
									 --------------------------> �� �̸�ŭ�� Base* �� ����ų �� ����
				- �̶� p_c->what()�� �����Ű�� "���"�� ��µ�
					-> p_c�� Base�� �������̹Ƿ� Base::What()�� ����Ǵ°�
				-> �̷��� �Ļ� Ŭ�������� ��� Ŭ������ ĳ���� �ϴ°��� "�� ĳ����" �̶�� ��
	*/

	// �ٿ� ĳ����
	{
		Base p;
		Derived c;

		std::cout << " === ������ ���� === " << std::endl;
		// ��� Ŭ������ �Ļ� Ŭ������ ĳ���� �����ұ�?
		//	Derived* p_p = &p;	// C2440: '�ʱ�ȭ ��': 'Base *'���� 'Derived *'(��)�� ��ȯ�� �� �����ϴ�
		//	p_p->what();
		// �ȵ�

		// ��ĳ���� �ϰ� �ٽ� ���� Ŭ������ �������°� �����ұ�?
		//	Base* p_p = &c;
		//	Derived* p_c = p_p;	// C2440: '�ʱ�ȭ ��': 'Base *'���� 'Derived *'(��)�� ��ȯ�� �� �����ϴ�
		//	p_c->what();
		// �ȵ�

		// ������ �ǵ��� �ϸ� �ɱ�?
		//	Base* p_p = &p;
		//	Derived* p_c = static_cast<Derived*>(p_p);
		//	p_c->what();
		// ������ ��Ÿ�� ������ ��. ����� �ƹ��͵� ��µ��� �ʰ� �׳� �Ѿ

		// dynamic_cast�� �̿��غ���: ��� ���迡 �ִ� �� �����͵� ���� ĳ����
		//	Base* p_p = &p;
		//	Derived* p_c = dynamic_cast<Derived*>(p_p);	// C2683: 'dynamic_cast': 'Base'��(��) ���� ������ �ƴմϴ�.

		// �̰͸� �����ϰ� ������
		Base* p_p = &c;
		Derived* p_c = static_cast<Derived*>(p_p);
		p_c->what();
	}

	/*
		- ���� �ٿ�ĳ���õ��� �� �ȵɱ�
			- ���� ���̰� �׷����� ����
				Base ->  [string s][Base()][what()]
				Derived ->  [string s][Base()][what()] + [string s][Derived()][what()]
				�̷������� �����Ǿ� �ִµ�
				Base ->  [string s][Base()][what()] / [string s][Derived()][what()] <- �̺κ��� ���� 
						 ----------------------------------------------------------> Derived* �� ����Ű�� �κ��� �̸�ŭ�ε� Base���� �����Ƿ� ���� �۵����� �ʴ°�
			- �ٿ�ĳ������ ��Ӱ��踦 �� �ľ��ϰ� ����ؾ���
	
	*/
	return 0;

}