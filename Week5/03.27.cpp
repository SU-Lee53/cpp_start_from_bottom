/*
	- 03.27 C++ ��Ÿ�� ĳ����

*/

// - C++ ��Ÿ�� ĳ����

#include <iostream>
#include <vector>
#include <cassert>

// ��� �������� ���� ����ü �̸��� ����Ͽ� namespace�� ���������

// static_cast ���� �̿�
namespace ex1
{
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


	enum class E { ONE = 1, TWO, THREE };
	enum EU { ONE = 1, TWO, THREE };

}

// const_cast ���� �̿�
namespace ex2
{
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
}

// dynamic_cast ���� �̿�
namespace ex3
{
	struct V
	{
		virtual void f() {}	// must be polymorphic to use runtime-checked dynamic_cast / ��Ÿ�� dynamic_cast�� �̿��Ϸ��� �������� �����ؾ���
	};

	struct A : virtual V {};

	struct B : virtual V
	{
		B(V* v, A* a)
		{
			// casts during construction ������ �������� ĳ����
			dynamic_cast<B*>(v);	// well - defined: v of type V*, V base of B, results in B* / �� ���ǵ�: V* Ÿ���� v, B�� �θ� V, B*�� ���
			dynamic_cast<B*>(a);	// undefined behavior: a has type A*, A not a base of B / ���ǵ��� ����: A* Ÿ���� a, A�� B�� �θ� �ƴ�
		}
	};
	
	struct D : A, B
	{
		D() : B(static_cast<A*>(this), this) {}
	};

	struct Base
	{
		virtual ~Base() {}
	};

	struct Derived : Base
	{
		virtual void name() {}
	};
}

// reinterpret_cast ���� �̿�
namespace ex4
{
	int f() { return 42; }
}

int main()
{
	// C ��Ÿ�� ĳ����
	//	int a = 10;
	//	double b = 3.14;
	//	
	//	double c = b + (double)a;	// ��������� ĳ���� ���� �ʾƵ� �����Ϸ����� �Ͻ������� ĳ���� ����
	//	std::cout << c << std::endl;

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

	// C++ ��Ÿ�� ĳ����
	// �Ʒ��� ���õ��� cppreference�� ������
	// ���� �𸣴� ������� �̿��� �������� �ſ츹���� �ϴ��� �׳� �̷��� �ִ� ������ �Ѿ�� ������

	// 1. static_cast
	{
		using namespace ex1;

		// 1-1. static downcast ���� �ٿ�ĳ����
		D d;
		B& br = d;	// �Ͻ��� ��ȯ�� �̿��� ��ĳ����
		std::cout << "1-1) " << br.hello();	// This is B
		D& another_d = static_cast<D&>(br);	// �ٿ�ĳ����
		std::cout << "1-1) " << another_d.hello();	// This is D

		// 1-2. lvalue -> xvalue (lvalue: ��ġ�� �ǹ�(����, ǥ���� ��),  ���� ���� / xvalue: �̵� ������ ��, ���� �Ұ���
		// �ڼ��� ���� https://en.cppreference.com/w/cpp/language/value_category �� ����
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
		std::cout << "1-9) " << br.*static_cast<int B::*>(pm) << '\n';	// 42

		// 10. void* to any type
		void* voidp = &e;
		std::vector<int>* p = static_cast<std::vector<int>*>(voidp);
	}

	// 2. const_cast
	{
		using namespace ex2;

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

	// 3. dynamic_cast
	{
		using namespace ex3;
		D d;	// this most derived object
		A& a = d;	// upcast, dynamic_cast may be used, but unnecessary / ���ɽ���, dynamic_cast�� ���� �� ������, �ʼ��� �ƴ�

		D& new_d = dynamic_cast<D&>(a);	// �ٿ�ĳ����
		B& new_b = dynamic_cast<B&>(a);	// ��ĳ����

		Base* b1 = new Base;

		// �Ʒ��� C++17 ���� �߰��� ����. if-else �ȿ��� ���ο� ������ ���� �� �ʱ�ȭ�� ������ https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0305r1.html
		if (Derived* d = dynamic_cast<Derived*>(b1); d != nullptr)	
		{
			std::cout << "downcast from b1 to d successful\n";
			d->name();	// ȣ���ص� ������
		}

		Base* b2 = new Derived;
		if (Derived* d = dynamic_cast<Derived*>(b2); d != nullptr)
		{
			std::cout << "downcast from b2 to d successful\n";
			d->name();	// ȣ���ص� ������
		}

		// ���� ���� ��� downcast from b2 to d successful�� ���
		// �̸� ���� ù��° Base���� Derived���� ĳ������ �����Ͽ����� �� �� ����
		//
		// the runtime check fails. If the dynamic_cast is used on pointers, the null pointer value of type target-type is returned. 
		// If it was used on references, the exception std::bad_cast is thrown.
		// ��Ÿ�ӿ��� �ٿ�ĳ������ �ȵȴٴ°��� Ȯ�� �� nullptr�� �������ذ��� �� �� ����
		// ���� ��ó�� �����Ͱ� �ƴ� ���۷����� ĳ���� �� ��� ����(std::bad_cast)�� �߻���Ŵ(�Ʒ� ����)

		try
		{
			Base base;
			Derived& d = dynamic_cast<Derived&>(base);
		}
		catch (const std::exception& e)
		{
			std::cout << "e.what(): " << e.what() << '\n';	// e.what(): Bad dynamic_cast!
		}

		delete b1;
		delete b2;
	}

	// 4. reinterpret_cast
	{
		using namespace ex4;

		int i = 7;

		// 4-1. pointer to integer and back / ������ -> int -> �ٽ� ������
		// std::uintptr_t == unsigned __int64 == unsigned long long
		std::uintptr_t v1 = reinterpret_cast<std::uintptr_t>(&i);	// static_cast�� ���� �߻�
		std::cout << "4-1. The value of &i is " << std::showbase << std::hex << v1 << '\n';	// The value of &i is 0x4170eff114 <- �翬�� �Ź� �޶���
		int* p1 = reinterpret_cast<int*>(v1);
		assert(p1 == &i);	// assert: () ���� ������ Ʋ���� ���α׷��� �ߴܽ�Ŵ(abort())

		// 4-2. pointer to function to another and back / ������ -> �Լ� -> �ٽ� ������
		void(*fp1)() = reinterpret_cast<void(*)()>(f);
		fp1();	// undefined behavior / ���ǵ��� ����
		int(*fp2)() = reinterpret_cast<int(*)()>(fp1);
		std::cout << std::dec << "4-2. " << fp2() << '\n';	// 42

		// 4-3. type aliasing through pointer / �����͸� ���� Ÿ�� ������(aliasing�� ����� �������� �� �𸣰���)
		char* p2 = reinterpret_cast<char*>(&i);
		std::cout << "4-3. " << (p2[0] == '\x7' ? "This system is little-endian\n" : "This system is big-endian\n");	// This system is little-endian
		// i�� �ּҸ� ���ڿ��� ��ȯ�Ͽ� 7�� �� �տ� �ִٸ� ��Ʋ �����, �� �ڶ�� �� �������

		// 4-4. type aliasing through reference / ������ �̿��� Ÿ�� ��ȯ
		reinterpret_cast<unsigned int&>(i) = 42;
		std::cout << "4-4. " << i << '\n';	// 42

		const int& const_iref = i;
		// int& iref = reinterpret_cast<int&>(const_iref);	// ������ ����: reinterpret_cast�� const�� ���� �� ����
		int& iref = const_cast<int&>(const_iref);	// const_cast�� �̿��ϸ� ������
	}
}