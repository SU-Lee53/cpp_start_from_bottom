/*
	05.29 ����Ʈ ������ 1 : RAII, unique_ptr
*/

/*  �ڿ� ������ �߿伺  */
//	#include <iostream>
//	
//	class A
//	{
//	public:
//		A()
//		{
//			data = new int[100];
//			std::cout << "�ڿ� ȹ��" << std::endl;
//		}
//	
//		~A()
//		{
//			std::cout << "�Ҹ��� ȣ��" << std::endl;
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
//			std::cout << "���� �߻�" << std::endl;
//		}
//	
//		/*
//			- �ڿ� ������ �߿伺
//				- �� �ڵ忡��
//					- A Ŭ������ �����ڿ��� 100���� int�� ���� �Ҵ���. �� 4byte * 100 = 400byte �Ҵ��
//	
//					- do_something()
//						- pa ��ü�� heap�� ����
//						- ���� ���ϵǸ� pa�� �Ҹ������ pa�� ����Ű�� ������ ����� A ��ü�� �Ҹ���� ����
//						- delete pa; �� ������ ���� ���������� 400����Ʈ�� �޸� ������ �߻���
//	
//					- throw_something()
//						- pa ��ü�� heap�� �����ǰ� thrower() �Լ��� ���� ���ܰ� ������
//						- ��� catch�� �̵�. �̰������� delete pa;�� ������� ���� (stack unwinding���ε� ���� �Ҵ�� ��ü�� �Ҹ��ڴ� �θ� �� ����)
//						- ���ܴ� ó���Ǿ����� 400����Ʈ �޸� ������ �߻�
//	
//				- C++�� java, go ���� �ֽ� ���� �ٸ��� ������ �÷��Ͱ� ����
//				- �׷��Ƿ� ������ ȹ���� �ڿ��� ������ �ݵ�� ���� �������־�� ��. �׷��� ������ ���α׷� ����ñ��� ��������
//				- ���α׷��� ���� �Ǽ��� �ڿ� ������ ������ ���� ������, �����ϴ� ��ġ�� �ָ��ؼ� ��ġ�� ��찡 ����� ����
//					-> �̸� ���� ���Ե� ������ ������ RAII
//					-> RAII ������ �������� ����� �����Ͱ� ����Ʈ ������
//		*/
//	
//		return 0;
//	}

/*  RAII : Resource Acquisition Is Initialization  */
/*
	- RAII
		- C++ â������ Bjarne Stroustrup �� ������ ������ ����
		- Resource Acquisition Is Initialization. ��, �ڿ��� ȹ���� �ʱ�ȭ��!
		- �⺻������ �ڿ� ������ ���ÿ� �Ҵ��� ��ü�� ���� ����

		- stack winding�� ����ǰų� �Լ��� ����Ǿ� ���ϵɶ� �ش� �Լ� ���ÿ� �ִ� ��ü�鿡 ���� �Ҹ��ڰ� ��� ȣ���
		- �׷��� �� �Ҹ��ڵ� �ȿ� �� ����� �ڿ����� �Բ� �����ϴ� ��ƾ�� ������?
			- ���� ���
				- ���� pa�� ��ü�� �ƴ� �������̱� ������ �Լ� ������ ��ü���� �Ҹ��ų�� �Բ� �Ҹ���� ����
				- �׷��� pa�� ������ '��ü' �� ����ٸ� �Լ� ������ ������ �Բ� �Ҹ�ǵ��� ���� �� ����

		- ��ó�� �۵��ϴ� ������ ��ü�� ����Ʈ �����Ͷ�� ��.
		- ���� C++ ���� <memory>���� 3������ ������ ��ü�� ������
			- unique_ptr
			- shared_ptr
			- weak_ptr

		- C++ 11 ������ ���Ǵ� auto_ptr�� ������ C++ 11 ���� �ĸ�(deprecatred)�Ǿ��� C++17���� ���� ������...
*/

/*  unique_ptr : ��ü�� ������ ������  */
#include <iostream>
#include <memory>

class A
{
public:
	A()
	{
		std::cout << "�ڿ� ȹ��" << std::endl;
		data = new int[100];
	}

	A(const A& a) = delete;	// �Լ� ����

	void some() { std::cout << "�Ϲ� �����Ϳ� �����ϰ� ��� ����" << std::endl; }

	~A()
	{
		std::cout << "�ڿ� ����" << std::endl;
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

	/*  double free, use after free ����  */
	//	{
	//		A* a1 = new A();
	//		A* a2 = a1;
	//	
	//		// a1 ��� ���� �Ҹ�
	//		delete a1;
	//	
	//		// a2 ��� ���� �Ҹ�...?
	//		delete a2;	// ��Ÿ�� ���� �߻� : a2�� a1�� ��ü�� ����Ű�� a1�� �Ҹ�Ǿ����Ƿ� �� �ѹ� �Ҹ��ų �� ����
	//		// �̷��� ������ double free ���׶�� �θ�
	//	
	//	
	//		// a1 �Ҹ� ���� ���...?
	//		a1->some();	// ��Ÿ�� ���� �߻� : a1�� �̹� �Ҹ�Ǿ����Ƿ� ������ �� ����
	//		// MSVC�� �̻��ϰ� ���� �޸� ������ delete �� free �ϴ� �ñ⺸�� �ణ �ڷ� �̷�... �׷��� ������ �߻����� ����
	//		// �ƹ�ư �̷� ���׸� use after free ���� Ȥ�� dangling pointer ��� �θ�
	//	}

	/*  std::unique_ptr  */
	//	{
	//		do_something();	// ������ �ٸ��� do_something() ������ pa�� �Ҹ�ǰ� ���ϵ�
	//	}

	/*  unique_ptr �� ������ ����  */
	//	{
	//		std::unique_ptr<A> pa(new A());
	//		std::cout << "pa : ";
	//		pa->some();
	//		std::cout << "&pa : " << pa.get() << std::endl;	// 00000210152038A0
	//	
	//	
	//		std::cout << "pa -> pb ������ ���� ---" << std::endl;
	//		// std::unique_ptr<A> pb = pa;	// C2280 'std::unique_ptr<A,std::default_delete<A>>::unique_ptr(const std::unique_ptr<A,std::default_delete<A>> &)': 
	//										// ������ �Լ��� �����Ϸ��� �մϴ�. -> �Ʒ����� ����
	//		
	//		std::unique_ptr<A> pb = std::move(pa);
	//		std::cout << "pb : ";
	//		pb->some();
	//		std::cout << "&pa : " << pa.get() << std::endl;	// 0000000000000000 -> �������� �̵��Ǿ� nullptr�� ����Ŵ -> dangling pointer
	//		std::cout << "&pb : " << pb.get() << std::endl;	// 00000210152038A0
	//	
	//	
	//	}

	/*  ������ �Լ�?  */
	//	{
	//		A a{};
	//		A b{ a };	// �Լ��� �����Ǿ ȣ�� �Ұ�
	//	
	//	}

	/*  unique_ptr �� �Լ� ���ڷ� �����ϱ�*/
}