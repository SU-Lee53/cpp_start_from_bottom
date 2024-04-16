
/*
	- 04.10 ~ 04.16 virtual �Ҹ���, ���� �Լ� ���̺�, ���߻��, ������
*/

// virtual �Ҹ���

//	#include <iostream>
//	
//	class Parent
//	{
//	public:
//		Parent() { std::cout << "Parent ������ ȣ��" << std::endl; }
//		virtual ~Parent() { std::cout << "Parent �Ҹ��� ȣ��" << std::endl; }
//	};
//	
//	class Child : public Parent
//	{
//	public:
//		Child() : Parent() { std::cout << "Child ������ ȣ��" << std::endl; }
//		~Child() { std::cout << "Child �Ҹ��� ȣ��" << std::endl; }
//	};
//	
//	int main()
//	{
//		// �Ҹ��ڰ� virtual�� �ƴҶ�
//		{
//			std::cout << "--- ����� Child ������� �� ---" << std::endl;
//			{ Child c; }
//			std::cout << "--- Parent �����ͷ� Child �������� �� ---" << std::endl;
//			{
//				Parent* p = new Child();
//				delete p;
//			}
//	
//			/*
//				output
//				--- ����� Child ������� �� ---
//				Parent ������ ȣ��
//				Child ������ ȣ��
//				Child �Ҹ��� ȣ��
//				Parent �Ҹ��� ȣ��
//				--- Parent �����ͷ� Child �������� �� ---
//				Parent ������ ȣ��
//				Child ������ ȣ��
//				Parent �Ҹ��� ȣ��
//			*/
//		}
//	
//		// �Ҹ��ڰ� virtual �϶�
//		{
//			std::cout << "--- ����� Child ������� �� ---" << std::endl;
//			{ Child c; }
//			std::cout << "--- Parent �����ͷ� Child �������� �� ---" << std::endl;
//			{
//				Parent* p = new Child();
//				p->~Parent();
//				delete p;
//			}
//	
//			/*
//				output
//				--- ����� Child ������� �� ---
//				Parent ������ ȣ��
//				Child ������ ȣ��
//				Child �Ҹ��� ȣ��
//				Parent �Ҹ��� ȣ��
//				--- Parent �����ͷ� Child �������� �� ---
//				Parent ������ ȣ��
//				Child ������ ȣ��
//				Child �Ҹ��� ȣ��
//				Parent �Ҹ��� ȣ��
//			*/
//		}
//	
//		/*
//			- virtual �Ҹ���
//				- �켱 �Ҹ��ڰ� virtual�� �ƴҶ��� ��°�� : 
//					--- ����� Child ������� �� ---
//					Parent ������ ȣ��
//					Child ������ ȣ��
//					Child �Ҹ��� ȣ��
//					Parent �Ҹ��� ȣ��
//						-> ������, �Ҹ����� ȣ����� : Parent() -> Child() -> ~Child() -> ~Parent()
//					--- Parent �����ͷ� Child �������� �� ---
//					Parent ������ ȣ��
//					Child ������ ȣ��
//					Parent �Ҹ��� ȣ��
//						-> ���� �ٸ��� Child�� �Ҹ��ڰ� ȣ����� �ʾ� �޸� ������ ����ų �� ����
//	
//				- �Ҹ��ڰ� virtual �϶��� ��°��
//					--- ����� Child ������� �� ---
//					Parent ������ ȣ��
//					Child ������ ȣ��
//					Child �Ҹ��� ȣ��
//					Parent �Ҹ��� ȣ��
//					--- Parent �����ͷ� Child �������� �� ---
//					Parent ������ ȣ��
//					Child ������ ȣ��
//					Child �Ҹ��� ȣ��
//					Parent �Ҹ��� ȣ��
//						-> �̹����� �ʿ��� ��� �Ҹ��ڰ� ���������� ȣ��Ǿ� �޸� ������ �Ͼ�� ����
//	
//				- ��ó�� �Ҹ��ڰ� virtual�� �ƴ϶�� ��ü �Ҹ�� �������� �Ҹ��ڰ� ȣ����� ���ϱ� ������ 
//				  """��ӵ� ������ �ִ� Base Ŭ�������� �ݵ�� �Ҹ��ڸ� virtual�� ��������"""
//	
//				++ Parent�� �Ҹ��ڴ� �� ȣ��Ǵ°�
//					-> Child�� Parent�� ��ӹް� ������ �˰��ֱ� ������ �˾Ƽ� Parent�� �Ҹ��ڸ� ȣ���� -> �Ļ� Ŭ������ ������ ��������� �˰�����
//					-> �ݸ� Parent�� �Ҹ��ڸ� ���� ȣ���ϸ� Child�� �Ҹ��ڸ� ȣ���� �� ���� -> ��� Ŭ������ ������ ������ְ� �ִ��� ��
//		*/
//	
//		return 0;
//	}

// ���۷����� ���� �Լ� ����

//	#include <iostream>
//	
//	class A
//	{
//	public:
//		virtual void show() { std::cout << "Parent" << std::endl; }
//	};
//	
//	class B : public A
//	{
//	public:
//		void show() override { std::cout << "Child" << std::endl; }
//	};
//	
//	void test(A& a) { a.show(); }
//	
//	int main()
//	{
//		A a;
//		B b;
//		test(a);
//		test(b);
//	
//		/*
//			output
//			Parent
//			Child
//		*/
//	
//		/*
//			- ���±����� ������ �Ļ� Ŭ������ �Լ��� �����Ҷ� ��� Ŭ������ �����͸� ��������� ���۷����ε� ���� ������
//			++ ������ ������ ���������� ���۷����� �����ͳ� ũ�� �ٸ��� ���� ������ �翬�Ҽ���...
//				https://www.youtube.com/watch?v=lRUiaigGIDA
//		*/
//		return 0;
//	}

// ���� �Լ��� ���� ���� : ���� �Լ� ���̺�

/*
	- ���� �Լ��� ���� ����
		- ���� �Լ��� �̷��� ������ ��� �Լ��� �� virtual ���̰� �����Լ��� ����� �ȵ�?
			- ��� ����. �׷���.....
		- ���� �Լ��� ���� ����
			- C++�� ���� �Լ��� �ϳ��� �����ϴ� Ŭ������ ���ؼ� ���� �Լ� ���̺�(virtual function table:vTable)�� ����
			- ���� �Լ� ���̺� : ��ȭ��ȣ�η� �����ϸ� ���� -> [���� �̸�(�Լ� �̸�)] --- [���� ��ȭ��ȣ(���� �Լ�)]
			- �̶� ���� �Լ��� ���� �Լ��� �ƴ� �Լ��� ȣ��Ǵ� �������� ���̰� ����
				- ���� �Լ��� �ƴ� �Լ� : Ư���� �ܰ踦 ��ġ�� �ʰ� �ٷ� �Լ��� ȣ���Ͽ� ������
				- ���� �Լ� : ���� �Լ� ���̺� ���� ���� ���ϴ� �Լ��� �� �ڿ� ȣ���Ͽ� ������
				-> ��������� �����Լ��� ���� �Լ� ���̺��� � �Լ��� ������ ���� �߰����� ������ �ɸ�(�������)
			- ������忡 ���� ���� ���̴� �̹������� ����ȭ�� �߿��� �о߿����� �̸� �����ؾ� �� �ʿ䰡 �ְ� ���� ������ ����ȭ�� �߿��� �о���...
		- ��� : �����Լ��� ȣ�� �������� ������尡 �ֱ� ������ ���� ���ϸ� �ҷ��� �� ����
*/

// ���� ���� �Լ�, �߻� Ŭ����

//	#include <iostream>
//	
//	class Animal
//	{
//	public:
//		Animal() {}
//		virtual ~Animal() {}
//		virtual void speak() = 0;
//	};
//	
//	class Dog : public Animal
//	{
//	public:
//		Dog() : Animal() {}
//		void speak() override { std::cout << "�п�" << std::endl; }
//	};
//	
//	class Cat : public Animal
//	{
//	public:
//		Cat() : Animal() {}
//		void speak() override { std::cout << "�߿˾߿�" << std::endl; }
//	};
//	
//	int main()
//	{
//		Animal* dog = new Dog();
//		Animal* cat = new Cat();
//		//	Animal* animal = new Animal();	// �Ұ� C2259: 'Animal': �߻� Ŭ������ �ν��Ͻ�ȭ �� �� �����ϴ�.
//	
//		dog->speak();
//		cat->speak();
//	
//		/*
//			output
//			�п�
//			�߿˾߿�
//		*/
//	
//		/*
//			- ���� ���� �Լ�
//				- ������ �ϴ��� ���ǵǾ� ���� �ʴ� �Լ� -> �ݵ�� �������̵� �Ǿ�� �ϴ� �Լ�
//				- �����Լ��� = 0; �� �ٿ��� ����
//					-> �� Animal Ŭ������ virtual void speak() = 0;�� ���� ���� �Լ���
//				- ���� ���� �Լ��� ��ü �� ��ü�� ���ǰ� �����Ƿ� �����ų�� ���� ������ ���� ���� �Լ��� �ִ� Ŭ������ �ν��Ͻ��� ������ �� ����
//				- private�� ���� ���� �Լ��� ������ ���� ����. �ٸ� �̰�� �������̵�� �����ϳ� �ڽ� Ŭ������ ȣ������ ����
//			- �߻� Ŭ����
//				- ���� ���� �Լ��� �ּ� �Ѱ� �����ϰ� �ִ� �ݵ�� ��ӵǾ�� �ϴ� Ŭ����
//				- �߻�Ŭ���� ��ü�� �ν��Ͻ�(��ü)�� ������ �� ����
//				- �߻� Ŭ������ �־�?
//					- �ش� Ŭ������ ��ӹ޾� ����� �� "�� ����� �Ϲ����� ��Ȳ���� ����� ����� �ʰ� ���� Ư��ȭ �Ǵ� Ŭ������ ���߾� ����� ���" ��� �ǹ̷� ���
//					- Animal::speak()�� ��쵵 ���������� ��� �������� ���� �Ҹ��� �ٸ��Ƿ� �Ϲ����� Animal�� speak()�� ���Ǹ� ������ ����� 
//					  �ش� Ŭ������ ��ӹ��� Dog/Cat ���� Ư���� ��Ȳ�� ���߾� ����� ������
//				- �߻� Ŭ������ �ν��Ͻ��� ���� �� ������ �����ʹ� �������� ���� �� ����
//					-> �������� dog�� cat�� Animal �����Ϳ� ��ĳ���� �ǰ� �������̵� �� speak()�� ��Ȳ�� �°� �� ���������
//		
//		*/
//	}

// ���� : �����Լ��� �󸶳� ������

//	#include <iostream>
//	#include <chrono>
//	
//	class A 
//	{
//	public:
//		virtual ~A() {}
//	
//		virtual int func(int num)
//		{
//			return num + 1;
//		}
//		int func2(int num)
//		{
//			return num + 1;
//		}
//	};
//	
//	class B : public A
//	{
//	public:
//		~B() {}
//	
//		int func(int num) override
//		{
//			return num + 1;
//		}
//	
//	};
//	
//	int main()
//	{
//		A* a = new B();
//	
//		for (int count = 10; count <= 1000000000; count *= 10)
//		{
//			std::cout << "execution count : " << count << std::endl;
//	
//			auto vStart = std::chrono::high_resolution_clock::now();
//			for (int i = 0; i < count;)
//			{
//				i = a->func(i);
//			}
//			auto vEnd = std::chrono::high_resolution_clock::now();
//			std::chrono::duration<double> vElapsed = vEnd - vStart;
//	
//			std::cout << "virtual function elapsed second : " << vElapsed.count() << "s" << std::endl;
//	
//	
//			auto gStart = std::chrono::high_resolution_clock::now();
//			for (int i = 0; i < count;)
//			{
//				i = a->func2(i);
//			}
//			auto gEnd = std::chrono::high_resolution_clock::now();
//			std::chrono::duration<double> gElapsed = gEnd - gStart;
//	
//			std::cout << "non-virtual function elapsed second : " << gElapsed.count() << "s" << std::endl;
//	
//			std::cout << std::endl;
//		}
//		
//		/*
//		output
//		execution count : 10
//		virtual function elapsed second : 3e-07s
//		non-virtual function elapsed second : 1e-07s
//		
//		execution count : 100
//		virtual function elapsed second : 3e-07s
//		non-virtual function elapsed second : 2e-07s
//		
//		execution count : 1000
//		virtual function elapsed second : 2.6e-06s
//		non-virtual function elapsed second : 1.4e-06s
//		
//		execution count : 10000
//		virtual function elapsed second : 2.11e-05s
//		non-virtual function elapsed second : 1.41e-05s
//		
//		execution count : 100000
//		virtual function elapsed second : 0.0002034s
//		non-virtual function elapsed second : 0.0001669s
//		
//		execution count : 1000000
//		virtual function elapsed second : 0.0019909s
//		non-virtual function elapsed second : 0.0013699s
//		
//		execution count : 10000000
//		virtual function elapsed second : 0.0195895s
//		non-virtual function elapsed second : 0.0133003s
//		
//		execution count : 100000000
//		virtual function elapsed second : 0.223024s
//		non-virtual function elapsed second : 0.159269s
//		
//		execution count : 1000000000
//		virtual function elapsed second : 2.04678s
//		non-virtual function elapsed second : 1.36539s
//
//	*/
//	
//		// ���� Ƚ���� �þ���� �ӵ����̰� Ȯ���� ����
//	}

// ���߻��

//	#include <iostream>
//	
//	class A
//	{
//	public:
//		int a;
//	
//		A() { std::cout << "A ������ ȣ��" << std::endl; }
//	};
//	
//	class B
//	{
//	public:
//		int a;
//		int b;
//	
//		B() { std::cout << "B ������ ȣ��" << std::endl; }
//	};
//	
//	class C : public A, public B
//	{
//	public:
//		int c;
//	
//		C() : A(), B() { std::cout << "C ������ ȣ��" << std::endl; }
//	};
//	
//	int main()
//	{
//		C c;
//		//	c.a = 10;	C2385: 'a' �׼����� ��ȣ�մϴ�
//	
//		/*
//			- ���� ��� (multiple inheritance)
//				- �� Ŭ������ �ٸ� ���� ���� Ŭ���� ���� ��ӹ޴°�
//				- ���� ��ӽ� �������� ȣ����� : ���� ����ϴ� ��
//					- class C : public A, public B -> A > B > C ������ �����ڰ� ȣ���
//					- class C : public B, public A -> B > A > C ������ �����ڰ� ȣ���
//					- �̴� C�� �������� �ʱ�ȭ ����Ʈ���� ������ �����Ͽ��� ������ ����
//	
//				- ���� ��ӽ� ��������
//					- ���� ���ó�� A, B ��� int a�� ������ �ִ� ��� �Ѵ� ��ӹ޴� C�� ���忡�� C::a�� ��ȣ����
//						-> ���� ��ӽ� �ߺ��Ǵ� ��� ������ �־�� �ȵ�
//					- �� Ŭ������ ���� �� �� ��ӹ޴°��� �����Ǿ����� (soen)
//						-> �翬�� �׷��� �ǵ��Ҹ��� �������� �Ʒ��� ���̾Ƹ�� ��� ������ ���������� ����Ǵ� ������ �ǵ�ġ �ʰ� �߻��� �� �ֱ⵵ ��
//		*/
//	}

// ���� ��ӽ��� ������ : ���̾Ƹ�� ���, �� �ذ�� ������

//	#include <iostream>
//	
//	class Human
//	{
//	public:
//		Human() { std::cout << "Human" << std::endl; }
//	};
//	
//	class HandsomeHuman : public virtual Human
//	{
//	public:
//		HandsomeHuman() : Human() { std::cout << "HandsomeHuman" << std::endl; }
//	};
//	
//	class SmartHuman : public virtual Human
//	{
//	public:
//		SmartHuman() : Human() { std::cout << "SmartHuman" << std::endl; }
//	};
//	
//	class Me : public HandsomeHuman, public SmartHuman
//	{
//	public:
//		Me() : Human(), HandsomeHuman(), SmartHuman() { std::cout << "Me" << std::endl; }
//	};
//	
//	int main()
//	{
//		Me m;
//	
//		/*
//			- ���� ����� �ƴѰ��
//			output :
//			Human
//			HandsomeHuman
//			Human
//			SmartHuman
//			Me
//		*/
//	
//		/*
//			- ���� ����� ���
//			output :
//			Human
//			HandsomeHuman
//			SmartHuman
//			Me
//		*/
//	
//		/*
//			- ���̾Ƹ�� ���
//				- ���� ���� ��� �ܶ����� �����Ͽ����� �� Ŭ������ �ٸ� Ŭ������ �ι� �̻� ����� �� ����
//				- �׷��� ���� Me �� Human�� 2�� ��� �޴°Ͱ� ���������� �����
//					-> �׸����� ����
//									 |----- [HandsomeHuman] <---|
//						[Human] <----							 ------ [Me]
//									 |----- [SmartHuman] <------|
//						-> HandsomeHuman�� SmartHuman ��� Human�� ��ӹް� �����Ƿ� ���� ��ӹ޴� Me�� Human�� 2�� ��ӹ޴� ���� ��
//						-> ���࿡ Human�� name�̶�� ������ �ִٸ� Me::name�� ��ӹ��� 2���� Ŭ���� ��� name�� �־� ������ ��ȣ����
//						-> ���� ���ʿ��ϰ� Human ������ 2�� ��������Ƿ� �޸𸮵� ������
//				- �̷� ������ ������ ���̾Ƹ�� ���(dreadful diamond of derivation) �̶�� �θ������� ���ǰ�����
//	
//			- ���� ���
//				- �� Ŭ������ �� �� ��ӹ޴��� �ش� Ŭ������ ����� �ѹ��� ����ϵ��� ��
//				- ���� ��ӵǴ� Ŭ������ ���� ��� Ŭ����(virtual base class)��� ��
//				- ���� ��� Ŭ�����κ��� ��ӹ��� ����� ���� Ŭ������ ���� �ʱ�ȭ���־�� ��
//					-> Me�� �����ڿ��� HandsomeHuman, SmartHuman �Ӹ� �ƴ϶� Human Ŭ�������� ���� �ʱ�ȭ ����Ʈ���� �ʱ�ȭ ���ְ� ����
//		*/
//	
//	
//	}

// �׷��� ���� ����� ���� ����ұ�

#include <iostream>

// ��� Ŭ����
class Vehicle
{

};

/************************** �۵� ȯ�濡 ���� �Ļ� Ŭ���� **************************/
class LandVehicle : public virtual Vehicle
{

};

class WaterVehicle : public virtual Vehicle
{

};

class SkyVehicle : public virtual Vehicle
{

};

class SpaceVehicle : public virtual Vehicle
{

};


/************************** ���¿��� ���� �Ļ� Ŭ���� **************************/

class GasPoweredVehicle : public virtual Vehicle
{

};

class WindPoweredVehicle : public virtual Vehicle
{

};

class NuclearPoweredVehicle : public virtual Vehicle
{

};

class PedalPoweredVehicle : public virtual Vehicle
{

};

/************************** ���� �Ļ� Ŭ���� **************************/

class GasPoweredLandVehicle : public GasPoweredVehicle, public LandVehicle
{

};

// �̷������� ���� �Ļ� Ŭ�������� ����� ������

/*
	- ���� ����� ���� ����ұ�?
		- ����� �ڵ忡���� �Ʒ��� ���ø� ��鼭 �����ϰ� ����
			- ����(Vehicle)�� ������ Ŭ������ ����ٰ� ������ �غ���
				- ������ ������ ������ �ٴϴ� ��, ������ �ٴϴ� ��, �ϴ��� ���� ��, ���ֿ��� �ٴϴ� �� <- �̷��� �ִٰ� ġ��
				- ������ ���¿��� �ֹ���, ǳ��, ���ڷ�, ���(������ó��) <- �̷��� �ִٰ� ġ��
				- ���� 2������ ����غ����� �غ���
					1) LandVehicle �� ����Ű�� Vehicle& ���۷����� �ʿ�� �ϴ°�?
						-> Vehicle&�� �����δ� LandVehicle�� ��ĳ���õǾ� �� �ִٸ� Vehicle ��� �Լ� ȣ��� LandVehicle�� ����Լ��� �������̵� �Ǿ�� �ϴ°�?
					2) ��ģ������ GasPoweredVehicle �� ���ؼ��� Vehicle& ���۷����� �ʿ�� �ϴ°�?
					-> �� �� ������ ����� ��� "YES"��� ���� ����� ����

		- ��� Vehicle�� ���� ��� �ܿ��� �ٸ��� ������ ����� �ְ� ����� �ڵ忡���� 3���� ����� ������
			- �� Vehicle�� ���� ��� ������ �ٴϴ� ȯ���� ���� N, ���¿��� ���� M�̶�� �Ѵٸ�...

				1) �긮�� ����(Bridge Pattern)
					- ������ ��Ÿ���� �� ���� ī�װ��� �ƿ� ��� �����ͷ� ��������
						-> Vehicle�� �Ļ� Ŭ������ LandVehicle, SpaceVehicle ����� N���� �Ļ� Ŭ������ �����
						-> ���¿��� ���� Vehicle::Engine* ��� ������ ����� ��
						-> ���� Engine�� �Ļ� Ŭ������ GasPowered, NuclearPowered ���� �Ļ� Ŭ������ ����� �ְ�
						-> Vehicle�� �Ļ� Ŭ�������� �� ��ü�� Engine �Ļ� Ŭ�������� ��ü�� ����Ű�� ��
						����) �� N + M���� Ŭ������ �ʿ��ϹǷ� ���� �ۼ��ϴ� �ڵ���� �پ��
						����) 1. N * M���� ��� ��Ȳ�� ���� ������ ��� �Ұ�����
							  2. ������ Ÿ�� Ÿ�� üũ�� ������ Ȱ���� �� ����
								  ex1) Engine�� ����̰� �۵�Ȯ���� ������ ������ Vehicle �Ļ� ��ü�� ������ Ÿ�ӿ� ������ ���� ����� ����(��Ÿ�ӿ��� Ȯ�ΰ���)
								  ex2) ���¿��� ������� ���ֿ��� �۵��ϴ� ��� ������ ����Ű�� ��� Ŭ������ ����� ������ (SpaceVehicle* �� ���¿��� ������� ���ֿ� �ٴϴ� ���� �ϴ� ����ų �� ����)
									   ���� ������ ������� �ֹ����� ����ϴ� ��� ������ ����Ű�� ��� Ŭ������ ���� �� ���� (GasPoweredVehicle* �� ���ʿ� ���� ���� ����)

				2) ��ø�� �Ϲ�ȭ(Nested Generalization)
					- �켱 �Ѱ��� ������ ��� �Ļ�Ŭ������ �����, ������ �Ļ� Ŭ�������� �ٸ� ������ �ش�Ǵ� �Ļ�Ŭ������ �� ����
						-> Vehicle�� �Ļ�Ŭ������ LandVehicle, WaterVehicle ����� �ϴ� �����
						-> ���� �ٸ� ������ �Ļ� Ŭ������ GasPoweredLandVehicle, NuclearPoweredLandVehicle, GasPoweredWaterVehicle... ����� ���� ����
						����) ���� �긮�� ���Ϻ��ٴ� �� �� ������ ��� ����
						����) 1. �긮�� ����ó�� �ֹ��� ���� ��ü�� ����ų ��� Ŭ������ ���� �� ���� (�̰͵� GasPoweredVehicle* �� ���ʿ� ���� ���� ����)
							  2. N * M���� Ŭ������� ����� Ŭ���� ��� ���ο� Ŭ������ �߰��ϱ� �������
								ex) ���¿��� �ϳ� �� �߰��Ǹ� �ش� ���¿��� ���� N���� Ŭ������ �� ��������.....

				3) ���� ���
					- �긮�� ����ó�� �� ī�װ��� �ش��ϴ� �Ļ� Ŭ�������� ����� ���¿��� �۵� ȯ�濡 �ش��ϴ� Ŭ������ ��ӹ޴� Ŭ������ ����
						-> LandVehicle..., GasPoweredVehicle... ����� �Ļ��Ǵ� ī�װ��� ���� Ŭ������ �� �����
						-> class GasPoweredLandVehicle : public LandVehicle, public GasPoweredVehicle <- �̷������� �ʿ��� ��쿡 ���� ���߻���� �޴� ���� Ŭ�������� ����
						-> �̷��� �ϸ� �긮�� ���ϰ� ������ �Ϲ�ȭ ����� �������� �ذ� ������
							ex1) �긮�� ������ �������� PedalPoweredSpaceVehicle ���� ������ ���� �� ����(���ʿ� ������ü�� ���ϸ� ��)
							ex2) �� �ΰ��� ��� ��� �Ұ����ϴ� �ֹ����� ����ϴ� ��� ������ ����ų ��� Ŭ������ ���� ���� �� ����(GasPoweredVehicle* �� ���� �� ����)

			- �� 3���� ����� ���������� ����� ����� ����. ��Ȳ�� �°� �ּ��� ����� ��� ����ؾ� ��.
*/