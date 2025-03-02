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
#include <vector>
#include <memory>

class A
{
public:
	A()
	{
		std::cout << "�ڿ� ȹ��" << std::endl;
		data = new int[100];
	}

	A(int i)
	{
		std::cout << "�ڿ� ȹ��" << std::endl;
		data = new int[100];
		data[0] = i;
	}

	A(const A& a) = delete;	// �Լ� ����

	void some() { std::cout << "�Ϲ� �����Ϳ� �����ϰ� ��� ����" << std::endl; }

	void do_sth(int a)
	{
		std::cout << "���𰡸� �Ѵ�" << std::endl;
		data[0] = a;
	}

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

// �Լ� ���ڷ� unique_ptr�� �޾ƺ��� - �߸��� ����
void func(std::unique_ptr<A>& ptr) { ptr->do_sth(3); }

// �Լ� ���ڷ� unique_ptr�� �޾ƺ��� - �ùٸ� ����
void func(A* ptr) { ptr->do_sth(3); }

class Foo
{
public:
	Foo(int a, int b) : a(a), b(b) { std::cout << "������ ȣ��" << std::endl; }
	void print() { std::cout << "a : " << a << "b : " << b << std::endl; }
	~Foo() { std::cout << "�Ҹ��� ȣ��" << std::endl; }
private:
	int a, b;
};

int main()
{

	/*  ���� �������� ������ - double free, use after free ����  */
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
	//		/*  ���ǻ��� : �Ϲ� �����ʹ� ������ ���������� �ʿ���� unique_ptr�� ��ü�� ����ų �� ����  */
	//		A* normal_ptr = pa.get();
	//		normal_ptr->some();	// �����۵�;;
	//	
	//	}

	/*  ������ �Լ�?  */
	//	{
	//		A a{};
	//		A b{ a };	// �Լ��� �����Ǿ ȣ�� �Ұ�
	//	
	//		// ���� <memory> �ȿ����� �Ʒ�ó�� unique_ptr�� ���� �����̳� ������ �Ʒ�ó�� �����Ǿ�����
	//		// unique_ptr(const unique_ptr&)            = delete;
	//		// unique_ptr& operator=(const unique_ptr&) = delete;
	//	}

	/*  unique_ptr �� �Լ� ���ڷ� �����ϱ�  */
	//	{
	//		std::unique_ptr<A> pa(new A());
	//		func(pa);	// �߸��� ����
	//		func(pa.get());	// �ùٸ� ����
	//	
	//		// �߸��� ������ �Լ��� �۵��� ��
	//		// unique_ptr�� ���� ������ �������� �ǹ̰� ������� ������ �߸��� ������ ��
	//	}

	/*  std::make_unique  */
	//	{
	//		// std::unique_ptr<Foo> ptr(new Foo(3, 5));	// �� ������ std::make_unique �� �̿��ؼ� �Ʒ�ó�� �ۼ�����
	//		auto ptr = std::make_unique<Foo>(3, 5);
	//		ptr->print();
	//	}

	/*  unique_ptr �� �����̳ʿ� ���ҷ� ���  */
	{
		std::vector<std::unique_ptr<A>> vec;
		std::unique_ptr<A> pa(new A(1));

		//	vec.push_back(pa);	// C2280 'std::unique_ptr<A,std::default_delete<A>>::unique_ptr(const std::unique_ptr<A,std::default_delete<A>> &)': ������ �Լ��� �����Ϸ��� �մϴ�
		// push_back() �� ���ڸ� �����ؼ� ��������� unique_ptr�� ���� �����ڰ� ���⶧���� ������ �߻���

		vec.push_back(std::move(pa));	// ��������� pa�� vector ������ �̵���Ų�ٸ� ������ �߻����� ����
		// pa�� vec ������ �̵��Ǿ����Ƿ� �翬�� pa�� dangling pointer �� �Ǹ� ����ؼ��� �ȵ�

		vec.push_back(std::unique_ptr<A>(new A(1)));
		vec.emplace_back(new A(1));
		// �� �Ʒ� ������ ������ ���� ��

		/*  emplace_back ���� ���ǻ���  */
		std::vector<int> v1;
		std::vector<std::vector<int>> v2;

		v1.emplace_back(100000);	// std::vector<int> v1 �ȿ� 100000 �� int ���� �߰�
		v2.emplace_back(100000);	// std::vector<std::vector<int>> v2 �ȿ� ���Ұ� 100000���� std::vector<int> �� �߰�
		// emplace_back ����� vector ���� Ÿ���� �⺻ �����ڸ� �̿��� ��ü�� �����Ͽ� �߰���
		// ���� ��Ȳ�� ���� ��ġ �ʴ� �����ڰ� ȣ��� ���輺�� ����
	}

	/*
		- std::unique_ptr<T>
			- ���� �������� ������
				- ������ �����ʹ� ��뿡 �־� ������ ���ϴٴ� ������ ������ �޸� ���׿� ���� ������ġ�� ���� ����
				- ��ǥ������ ���� �߻��ϴ� ���� 2������ �Ʒ��� ����
					1) double free
						- ���� �ּ�(�ڿ�)�� A, B �����Ͱ� �����ϰ� �ִٰ� �Ҷ�
						- A�� �ش� �ڿ� ����� ��ġ�� free() Ȥ�� delete�� ���� �޸𸮸� �Ҹ������ ��
						- B�� �ش� �ڿ��� �ٽ� �ѹ� �Ҹ��Ű���� �ϸ� ������ �߻���
							-> ���� �ּҸ� 2�� �̻� �Ҹ��Ű���� �ؼ� �Ͼ�� ������ �̸� double free ��� �θ�

					2) use after free
						- ���������� ���� �ڿ��� A, B �����Ͱ� �����ϰ� ������
						- A�� ����� ��ġ�� �޸𸮸� �Ҹ�
						- �̶� B�� �̹� �Ҹ�� �ڿ��� ����Ϸ��� �ϸ� ������ �߻���
							-> �̹� �Ҹ�� �ڿ��� ����Ϸ��� �ؼ� �Ͼ�� ������ �̸� use after free ��� �θ�

					- �� �ܿ��� �ܼ��� �� ������ ������Ų �ڿ��� ���� �Ҹ��Ű�� �ʾ� �޸� ������ �߻��ϴ� ���� ������ ����

			- std::unique_ptr
				- std::unique_ptr : Ư�� ��ü�� ������ �������� �ο��ϴ� ������ ��ü
				- ������ ������ : �� unique_ptr �� ����Ű�� ��ü�� �ٸ� unique_ptr�� ������ �� ����
					-> �̸��� ��, unique_ptr�� �ƴ� �Ϲ� �����ʹ� �ش� ��ü�� ����Ű�� ���� ������;;
					-> ����Ʈ �����͸� ����� ���̶�� ó������ ������ ����Ʈ �����͸� ���°��� ������ ������ ������ ����

				- ����Ʈ �������� �ϳ��̹Ƿ� RAII���� ��� ������
				
			- unique_ptr �� ������ ����
				- unique_ptr �� ����Ű�� ��ü -> ������ �����Ѵٰ� �θ�
				- unique_ptr�� Ư�� ��ü�� ���� ������ �������� �ο������Ƿ� �ٸ� unique_ptr�� �ش� ��ü�� �����Ϸ��� �����Ǳ��� �Ѱܾ� ��
					-> ������ ���� ���� �ܼ� ����� �Ұ�����
					-> <memory> ����� ���� unique_ptr �� ���� �����ڿ� ���� �����ڸ� �ƿ� ������ �Լ��� �����ξ� ���� ���ɼ��� ��õ ������

						unique_ptr(const unique_ptr&)            = delete;
						unique_ptr& operator=(const unique_ptr&) = delete;

				- �ٸ� unique_ptr�� �������� ������Ű���� std::move() �� ����ϸ� ��
					-> �������� ������ ������ �����ʹ� �翬�� �ƹ��͵� ����Ű�� ����(nullptr)
					-> �̰��� dangling pointer ��� �θ�
					-> dangling pointer�� �ٽ� �������Ϸ��� �ϸ� ��Ÿ�� ������ �߻���Ű�Ƿ� ���� �ٽ� �������� �ʴ´ٴ� Ȯ���� �������� �̵��ؾ���

			- ������ �Լ�
				- C++ 11 ���� ���Ե� ���
				- ��������� �ش� �Լ��� ����� ���� �� ����. Ȥ�ó� ����Ϸ��� �Ѵٸ� ������ ������ �߻���
				- �Լ��� ���� �ڿ� = delete; �� �ٿ� �����

			- unique_ptr �� �Լ� ���ڷ� �����ϱ�
				- ��ó�� std::unique_ptr<A> pa(new A()); �� �����͸� ����� �Լ� ���ڷ� �Ѱ��ִ� ���(func())

					1) void func(std::unique_ptr<A>& p) <- �̷������� unique_ptr�� ���۷����� ����
						- unique_ptr�� ��ü�� ������ �������� �ο��ϴ� ������
						- �� ������� ���ڸ� �ѱ�� func() ���� unique_ptr�� p�� pa�� ��ü�� ����
							-> "������ ������" �̶�� ��Ģ�� ����ǹǷ� ���� ����� �ƴ�

					2) void func(A* p) <- �̷������� �Ϲ� �����ͷ� ����
						- �Ϲ� �����ʹ� �������� ������ �����Ƿ� ��Ģ�� ����� ���� ����
						- ���ڷ� ���� �� pa.get()�� �̿��Ͽ� ���� ��ü�� �ּҰ��� �Ѱ��־�� ��
							-> �� ����� ���� �� ������

					����) void func(std::unique_ptr<A> p) �� ������?
						- ȣ���� ���ؼ� �ƿ� �ٸ� �Լ��� unique_ptr�� �������� �Ѱ������
						- ȣ�� ���� pa�� dangling pointer�� ��
							-> Ư���� ��쿡�� �������� �Ϲ����� ��쿡�� ���� ����� ����������

			- std::make_unique
				- C++ 14 ���� ���Ե� �Լ��� unique_ptr�� ���� ���� �� ����
				- ���ڵ��� ���ø� ������ �����ڿ� �״�� �Ѱ��־� �Ϻ��� ������ ������
				- ������ �Ʒ��� ����(�� �ڵ��� A Ŭ������ ���÷�)

					auto ptr = std::make_unique<A>(1);
					-> �̴� �Ʒ��� ������
					std::unique_ptr<A> ptr(new A(1));

			- unique_ptr �� �����̳ʿ� ���ҷ� ���
				- �����̳ʿ� ���Ҹ� �������� �⺻������ �����ؼ� ��
				- unique_ptr�� ���簡 �Ұ����ϹǷ� �����̳� ���η� �̵����Ѿ� �� �� ����
				- vector�� ��� �Ϻ��� ������ ���� unique_ptr�� �������Ѽ� ���� �� �ִ� emplace_back() �Լ��� ����
					-> emplace_back ���� vector�� ���ø� ���ڿ� ���� �����ڰ� �����ǹǷ� �� Ȯ���ϰ� ����ؾ� ��

	*/
}