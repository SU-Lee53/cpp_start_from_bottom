/*
	- 03.27 C++ ��Ÿ�� ĳ����

*/

// - C++ ��Ÿ�� ĳ����

#include <iostream>
#include <vector>

struct B
{
	int m = 42;
	const char* hello() const { return "This is B\n"; };
};

struct D : B
{
	const char* hello() const
	{
		return "This is D\n";
	}
};

struct type
{
	int i;
	type() :i(3) {}
	void f(int v) const
	{
		// this->i = v;	// ������ ����: this �� const��(const �Լ��ϱ�)
		const_cast<type*>(this)->i = v;	// ȣ���� ��ü�� const�� �ƴ��̻� ������ ���� ����
	}
};

enum class E { ONE = 1, TWO, THREE };
enum EU { ONE = 1, TWO, THREE };

int main()
{
	// C ��Ÿ�� ĳ����
	//	int a = 10;
	//	double b = 3.14;
	//	
	//	double c = b + (double)a;	// ��������� ĳ���� ���� �ʾƵ� �����Ϸ����� �Ͻ������� ĳ���� ����
	//	std::cout << c << std::endl;

	// C++ ��Ÿ�� ĳ����
	// �Ʒ��� ���õ��� cppreference�� ������
	// ���� �𸣴� ������� �̿��� �������� �ſ츹���� �ϴ��� �׳� �̷��� �ִ� ������ �Ѿ�� ������

	// 1. static_cast
	{

		// 1-1. static downcast ���� �ٿ�ĳ����

		D d;
		B& br = d;	// �Ͻ��� ��ȯ�� �̿��� ��ĳ����
		std::cout << "1-1) " << br.hello();	// This is B
		D& another_d = static_cast<D&>(br);	// �ٿ�ĳ����
		std::cout << "1-1) " << another_d.hello();	// This is D

		// 1-2. lvalue -> xvalue (lvalue: ��ġ�� �ǹ�(����, ǥ���� ��),  ���� ���� / xvalue: �̵� ������ ��, ���� �Ұ���
		std::vector<int> v0{ 1,2,3 };
		std::cout << "1-2) �̵� ��, v0.size() = " << v0.size() << '\n';
		std::vector<int> v2 = static_cast<std::vector<int>&&>(v0);
		std::cout << "1-2) �̵� ��, v0.size() = " << v0.size() << '\n';

		// 1-3. initializing conversion �ʱ�ȭ ��ȯ
		int n = static_cast<int>(3.14);
		std::cout << "1-3) n = " << n << '\n';	// n = 3
		std::vector<int> v = static_cast<std::vector<int>>(10);
		std::cout << "1-3) v.size = " << v.size() << '\n';	//  v.size = 10

		// 1-4. discarded-value expression ���� �������� ǥ����
		static_cast<void>(v2.size());	// void�� static_cast�� �õ��ϸ� ���� ��������

		// 1-5. inverse of implicit conversion �� �Ͻ��� ��ȯ(����� ��ȯ ���� �Ͻ������� ��ȯ�� ���� ������� �ǵ����� ���� �ǹ�)
		void* nv = &n;
		int* ni = static_cast<int*>(nv);
		std::cout << "1-5) *ni = " << *ni << '\n';	// *ni = 3
		// void* �� ��ȯ�Ǿ� ���� ���� �˼� �������� int�� �� ��ȯ���� �ٽ� ���� �� �� ����

		// 1-6. array-to-pointer followed by upcast �迭�� �����ͷ� ��ȯ�ϰ� ���� Ŭ������ ��ĳ����
		D a[10];
		B* dp = static_cast<B*>(a);

		// 1-7. scoped enum to int ���� ���� enum�� int�� ��ȯ
		E e = E::TWO;
		int two = static_cast<int>(e);
		std::cout << "1-7) " << two << '\n';	// 2

		// 1-8. int -> enum -> �ٸ� enum
		E e2 = static_cast<E>(two);	// int -> enum
		EU eu = static_cast<EU>(e2);	// enum -> �ٸ� enum

		// 1-9. pointer to member upcast ��� �������� ��ĳ����
		int D::* pm = &D::m;
		std::cout << "1-9) " << br.*static_cast<int B::*>(pm) << '\n';

		// 10. void* to any type
		void* voidp = &e;
		std::vector<int>* p = static_cast<std::vector<int>*>(voidp);
	}

	// 2. const_cast
	{
		// �����鿡 MSVC������ �����Ϸ��� �ڵ����� const ĳ������ ���־� �׳� �����ϰ� �ϴ� �͵��� �ִ°Ű����� clang�� �̿��ϸ� �Ƹ� �ȱ׷�����

		int i = 3;
		const int& rci = i;
		const_cast<int&>(rci) = 4;	// ����
		std::cout << "i = " << i << '\n';	// 4

		const type t;	// t�� const��� �ȵ�(�ٵ� MSVC�� �̻��ϰ� ��... gcc�� �� ����...)
		t.f(4);
		std::cout << "type::i = " << t.i << '\n';	// type::i = 4

		const int j = 3;
		int* pj = const_cast<int*>(&j);
		*pj = 4;	// �̰͵� �ȵǾ� �´µ� �̻��ϰ� ��

		void (type:: * pmf)(int) const = &type::f;
		// const_cast<void(type::*)(int)>(pmf);	// ������ ����: const_cast�� �Լ� �����͸� ������� �۵����� ����

	}

	/*
		- �Ͻ���(implicit) ĳ���� / �����(explicit) ĳ����
			- �Ͻ��� ĳ����: �����Ϸ��� �˾Ƽ� ��Ȳ�� �°� ĳ���� �ϴ°� ex) int �� double ���� �������� �����Ϸ��� �ڵ����� int�� double�� ĳ���ä�
			- ����� ĳ����: ����ڰ� ���� �����ϴ� ĳ����

		- ������ C��Ÿ�� ����� ĳ���� : (Ÿ��)����
	
		- C++�� 4���� ĳ����
			1) static_cast : �Ϲ������� �����ϴ� Ÿ�Ժ�ȯ
			2) const_cast : ��ü�� ������� ���ִ� Ÿ�Ժ�ȯ ex) const int -> int
			3) dynamic_cast : �Ļ� Ŭ���� ���̿����� �ٿ�ĳ����
			4) reinterpret_cast : ������ �����ϰ� �ϴ� ĳ�������� ���� ������ ���� �����͵� ������ ĳ���� (reinterpret �� �� : ���ؼ�)
			- ĳ���� ��� : (���ϴ� ĳ����)<�ٲٷ��� Ÿ��>(�ٲٷ��� ���)
	
	*/


	
}