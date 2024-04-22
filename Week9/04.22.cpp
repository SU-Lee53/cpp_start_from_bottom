// ����� �ڵ� é��8�� ���� ������ ��ŵ
// ��� ���ø����� ������ �ٸ��Ÿ� �� ����

/*
	04.22 ���ø�
*/

// ���ø�?

/*
	- ���ø�?
		- ���� C++���� ��� �ڷᱸ���� Ŭ������ ������� �Ѵٸ�...
			- Ư���� �ڷ����� �����ؼ��� ����� ��
			- ���� ��� int�� ��� �ڷ����� ����� int ����� ���� �� ����
			- �׷��� ������ �غ��� �ٸ� Ÿ�Կ� ���� �ڷᱸ���� ������ ����ٰ� �ϸ� �ߺ��Ǵ� �ڵ尡 ���� �ɰ�
			- �׷��� �׳� ����ڴ� Ʋ�� �������� Ÿ���� �����Ϸ��� �׶��׶� �������ߵ��� �ϸ� ������ ������
				-> C++������ �̸� template��� �̸����� ��������
*/

// template

//	#include <iostream>
//	#include <string>
//	
//	template <typename T>
//	class Vector
//	{
//	public:
//		// ������
//		Vector(int n = 1) : data(new T[n]), capacity(n), length(0) {}
//	
//		// �� �ڿ� ���ο� ���Ҹ� �߰��Ѵ�
//		void push_back(T s)
//		{
//			if (capacity <= length)
//			{
//				T* temp = new T[capacity * 2];
//				for (int i = 0; i < length; i++)
//				{
//					temp[i] = data[i];
//				}
//				delete[] data;
//				data = temp;
//				capacity *= 2;
//			}
//	
//			data[length] = s;
//			length++;
//		}
//	
//		// ������ ��ġ�� ���ҿ� �����Ѵ�
//		T operator[](int i) { return data[i]; }
//	
//		void remove(int x)
//		{
//			for (int i = x + 1; i < length; i++)
//			{
//				data[i - 1] = data[i];
//			}
//			length--;
//		}
//	
//		// ���� ������ ũ�⸦ ���Ѵ�
//		int size() { return length; }
//	
//		~Vector()
//		{
//			if (data)
//			{
//				delete[] data;
//			}
//		}
//	
//	private:
//		T* data;
//		int capacity;
//		int length;
//	};
//	
//	//	int main()
//	{
//		Vector<int> int_vec;
//		int_vec.push_back(3);
//		int_vec.push_back(2);
//	
//		std::cout << "------- int vector -------" << std::endl;
//		std::cout << "ù��° ���� : " << int_vec[0] << std::endl;
//		std::cout << "�ι�° ���� : " << int_vec[1] << std::endl;
//	
//		Vector<std::string> str_vec;
//		str_vec.push_back("hello");
//		str_vec.push_back("world");
//		
//		std::cout << "------- std::string vector -------" << std::endl;
//		std::cout << "ù��° ���� : " << str_vec[0] << std::endl;
//		std::cout << "�ι�° ���� : " << str_vec[1] << std::endl;
//	
//		/*
//			output:
//			------- int vector -------
//			ù��° ���� : 3
//			�ι�° ���� : 2
//			------- std::string vector -------
//			ù��° ���� : hello
//			�ι�° ���� : world
//		*/
//	
//		/*
//			- template
//				- ������ �ǹ� : ����, ��� ������ ���� Ʋ
//					-> C++�� template�� ��Ȯ�� ���� �ǹ̷� ����. ����ڰ� ���ϴ� Ÿ���� ������ �˾Ƽ� �ڵ带 ���� Ʋ
//				- ����
//					- ����Ϸ��� Ŭ���� ��ܿ� template <typename T>�� ����
//						-> �����, �Ʒ��� ���ǵǴ� Ŭ������ ���� ���ø��� ����
//						-> ���ø� ���ڷ� T�� ������ T�� �ݵ�� ��� Ÿ���� �̸����� �����
//						-> �� Vector�� Vector Ŭ������ ���� ���ø��� �����. �Լ��� ��쿡�� �Լ� ���ø��� ��������(���߿� �ٽ� ����)
//						�� template <class T> ��� ��� �Ϻ��� ������. �ٸ� C++ ǥ�ؿ����� typename T�� ���°��� ��������
//							-> class T��� ������ �Ϲ� Ÿ�Ժ��ٴ� Ŭ������ �����Ѵٰ� ȥ���ϴ� ���� ���� �Ͼ�� ����
//							-> �ٸ� ���� �ڵ���� ȣȯ���� ���� Ű���带 ������ �ʰ� ���ܵξ���
//	
//					- ���� ������ ���ø��� ������ ���� �����Ϸ��� <> �ȿ� �����
//						-> Vector<int>, Vector<std::string> �̷������� ���
//						-> �� Ȥ�� ��ü�� ���ڷ� �����ؿ��� ������ �޸� 'Ÿ��' ��ü�� ������
//						-> �̷��� Ÿ���� ���޵Ǹ� �����Ϸ��� �̰��� ���� T �ڸ��� Ÿ���� �������� �ڵ带 ������
//	
//					- �̷��� Ŭ���� ���ø��� ���ڸ� �����ؼ� ���� �ڵ带 �����ϴ°��� "Ŭ���� ���ø� �ν��Ͻ�ȭ(class template instantiation)" �̶�� �θ�
//						- ������ ���ø��� �ν��Ͻ�ȭ ���� ������ �����Ͻÿ� �ƹ��� �ڵ�ε� ��ȯ���� ����
//							-> ���ø��� �ݵ�� �ν��Ͻ�ȭ �Ǿ������ ��μ� �����Ϸ��� ���� �ڵ带 ������
//	
//		*/
//	
//	}

// ���ø� Ư��ȭ

//	// �⺻ ���ø� Ŭ����
//	template <typename A, typename B, typename C>
//	class test {};
//	
//	// �Ϻ� ���ø� Ư��ȭ : A�� int�̰� C�� double�϶� ���� ó���ϰ� �ʹٸ�
//	template <typename B>
//	class test<int, B, double> {};
//	
//	// ��ü ���ø� Ư��ȭ
//	template <>	// �ݵ�� ���
//	class test<int, int, double> {};
//	
//	// bool Ÿ�Կ� ���� class Vector ���ø� Ư��ȭ
//	template <>
//	class Vector<bool>
//	{
//		/*
//			- ��� �˰���: bool�� Ư��ȭ�ϴ� ����
//				- bool�� 0,1 �θ� ǥ���ǹǷ� 1��Ʈ�� ������ �Ǵµ� C++�� �⺻ ������ ó�� ������ 1����Ʈ��
//				- �̴� �޸� ������ �����Ǿ� bool�� ���� ���ø� Ư��ȭ�� ���� Ư���� ���� ó��
//				- 32��Ʈ¥�� unsigned int �ϳ��� bool ���� 32�� ��
//					-> n��° ���� n / 32 ��° uint �ȿ� ����ǰ� n % 32��° ��Ʈ�� n��° ����
//		*/
//	public:
//		typedef bool valuetype;
//	
//		// ������
//		Vector(int n = 1)
//			: data(new unsigned int[n / 32 + 1]), capacity(n / 32 + 1), length(0)
//		{
//			for (int i = 0; i < capacity; i++)
//			{
//				data[i] = 0;
//			}
//		}
//	
//		void push_back(bool s)
//		{
//			if (capacity * 32 <= length)
//			{
//				unsigned int* temp = new unsigned int[capacity * 2];
//				for (int i = 0; i < capacity; i++)
//				{
//					temp[i] = data[i];
//				}
//				for (int i = capacity; i < 2 * capacity; i++)
//				{
//					temp[i] = 0;
//				}
//	
//				delete[] data;
//				data = temp;
//				capacity *= 2;
//			}
//	
//			if (s)
//			{
//				data[length / 32] |= (1 << (length % 32));	// OR �������� ������ ��Ʈ�� ����� ���ϴ� �ڸ��� 1�� ����
//			}
//	
//			length++;
//		}
//	
//		// AND �������� ���ϴ� ��Ʈ�� ����� �������� 0���� ����
//		// ���ϴ� ��Ʈ�� 1�̾��ٸ� �ش� ��Ʈ�� ���� != 0 ����� true
//		// ���ϴ� ��Ʈ�� 0�̾��ٸ� != 0 ����� false
//		bool operator[](int i) { return (data[i / 32] & (1 << (i % 32))) != 0; }	
//	
//		void remove(int x)
//		{
//			for (int i = x + 1; i < length; i++)
//			{
//				int prev = i - 1;
//				int curr = i;
//	
//				// ���� curr ��ġ�� �ִ� ��Ʈ�� 1�̶��
//				// prev ��ġ�� �ִ� ��Ʈ�� 1�� �����.
//				if (data[curr / 32] & (1 << (curr % 32)))
//				{
//					data[curr / 32] |= (1 << (curr % 32));
//				}
//				// �ƴϸ� prev ��ġ�� �ִ� ��Ʈ�� 0���� ä���
//				else
//				{
//					unsigned int all_ones_except_prev = 0xFFFFFFFF;	// 0xFFFFFFFF : ��� ��Ʈ�� 1�� uint
//					all_ones_except_prev ^= (1 << (prev % 32));	// XOR �������� �ش� ��Ʈ�� 0���� �ٲ�
//					data[prev / 32] &= all_ones_except_prev;
//				}
//			}
//			length--;
//		}
//	
//		int size() { return length; }
//	
//		~Vector()
//		{
//			if (data) delete[] data;
//		}
//	
//	private:
//		unsigned int* data;	// uint�� ����: �׳� int�� shift����� ������ �߻��� �� ����(2�� ���� Ư���� ��ȣ��Ʈ ������ ���õ� �����ε�. ����� ���� ����Ʈ ����)
//		int capacity;
//		int length;
//	};
//
//	int main()
//	{
//		Vector<int> int_vec;
//		int_vec.push_back(3);
//		int_vec.push_back(2);
//	
//		std::cout << "------- int vector -------" << std::endl;
//		std::cout << "ù��° ���� : " << int_vec[0] << std::endl;
//		std::cout << "�ι�° ���� : " << int_vec[1] << std::endl;
//	
//		Vector<std::string> str_vec;
//		str_vec.push_back("hello");
//		str_vec.push_back("world");
//	
//		std::cout << "------- std::string vector -------" << std::endl;
//		std::cout << "ù��° ���� : " << str_vec[0] << std::endl;
//		std::cout << "�ι�° ���� : " << str_vec[1] << std::endl;
//	
//		Vector<bool> bool_vec;
//		bool_vec.push_back(true);
//		bool_vec.push_back(true);
//		bool_vec.push_back(false);
//		bool_vec.push_back(false);
//		bool_vec.push_back(false);
//		bool_vec.push_back(true);
//		bool_vec.push_back(false);
//		bool_vec.push_back(true);
//		bool_vec.push_back(false);
//		bool_vec.push_back(true);
//		bool_vec.push_back(false);
//		bool_vec.push_back(true);
//		bool_vec.push_back(false);
//		bool_vec.push_back(true);
//		bool_vec.push_back(false);
//		bool_vec.push_back(true);
//		bool_vec.push_back(false);
//	
//		std::cout << "------- bool vector -------" << std::endl;
//		for (int i = 0; i < bool_vec.size(); i++)
//		{
//			std::cout << bool_vec[i];
//		}
//	
//		std::cout << std::endl;
//	
//		// ��� ��Ʈ�� ���� ������ ����
//		for (int i = 0; i < bool_vec.size(); i++)
//		{
//			std::cout << "[" << std::boolalpha << bool_vec[i] << "] ";
//		}
//	
//		/*
//			output:
//			------- int vector -------
//			ù��° ���� : 3
//			�ι�° ���� : 2
//			------- std::string vector -------
//			ù��° ���� : hello
//			�ι�° ���� : world
//			------- bool vector -------
//			11000101010101010
//			[true] [true] [false] [false] [false] [true] [false] [true] [false] [true] [false] [true] [false] [true] [false] [true] [false]
//		*/
//	
//		/*
//			- ���ø� Ư��ȭ(template specialization)
//				- �Ϻ� ��쿡 ���ؼ� ���� ó���ϴ� ��
//				- ����
//					- �⺻ Ŭ���� ���ø��� template <typename A, typename B, typename C> class test �� ���ǵǾ��ִٰ� ġ��
//					- �Ϻο� ���ؼ��� Ư��ȭ �ϰ���� ���(���ô� A, C�� Ư��ȭ)
//						-> template <typename B> class test<int, B, double> : A�� int, C�� double �� ��� Ư��ȭ
//					- ��ü�� Ư��ȭ �ϰ���� ���
//						-> template <> class test<int, int, double> : A, B�� int, C�� double
//						-> �����ϴ� ���ø� ���ڰ� ��� Ư��ȭ�Ϸ��� template <>�� ������־�� ��
//	
//				- �� �ڵ忡 ���� ������ ����...
//					-> ���� std::vector�� bool�� ���ؼ��� Ư��ȭ �Ǿ�����
//		*/
//	}

// �Լ� ���ø� 1

//	#include <iostream>
//	#include <string>
//	
//	template <typename T>
//	T max(T& a, T& b)
//	{
//		return a > b ? a : b;
//	}
//	
//	int main()
//	{
//		int a = 1, b = 2;
//		std::cout << "Max (" << a << ", " << b << ") ? : " << max(a, b) << std::endl;
//	
//		std::string s = "hello", t = "world";
//		std::cout << "Max (" << s << ", " << t << ") ? : " << max(s, t) << std::endl;
//	
//		/*
//			output:
//			Max (1, 2) ? : 2
//			Max (hello, world) ? : world
//		*/
//	
//		/*
//			- �Լ� ���ø�
//				- Ŭ���� ���ø��� ���������� ���ø��� �̿��Ͽ� �Լ��� ���� �� ����
//				- Ŭ���� ���ø��� ���������� �ν��Ͻ�ȭ �Ǳ� ������ ������ �ÿ� �ƹ��� �ڵ�ε� ��ȯ���� ����
//					-> �� �ڵ忡�� ���ø� �Լ��� ���� �ν��Ͻ�ȭ �Ǵ� �κ��� max(a, b)�� ȣ��Ǵ� �κ�
//					-> <>�� �̿��Ͽ� Ÿ�� ���ڸ� �Ѱ����� �ʾƵ� �����Ϸ��� �˾Ƽ� a,b�� Ÿ���� ���� max<int>(a,b)�� �ν��Ͻ�ȭ ����
//					-> string�� ���������� max(s, t) ȣ��� max<std::string>(s,t)�� �˾Ƽ� �ν��Ͻ�ȭ ��
//		
//		*/
//	
//		return 0;
//	}

// �Լ� ���ø� 2, �Լ� ��ü�� ����

//	#include <iostream>
//	#include <string>
//	
//	template <typename T>
//	class Vector
//	{
//	public:
//		// ������
//		Vector(int n = 1) : data(new T[n]), capacity(n), length(0) {}
//	
//		// �� �ڿ� ���ο� ���Ҹ� �߰��Ѵ�
//		void push_back(T s)
//		{
//			if (capacity <= length)
//			{
//				T* temp = new T[capacity * 2];
//				for (int i = 0; i < length; i++)
//				{
//					temp[i] = data[i];
//				}
//				delete[] data;
//				data = temp;
//				capacity *= 2;
//			}
//	
//			data[length] = s;
//			length++;
//		}
//	
//		// ������ ��ġ�� ���ҿ� �����Ѵ�
//		T operator[](int i) { return data[i]; }
//	
//		void remove(int x)
//		{
//			for (int i = x + 1; i < length; i++)
//			{
//				data[i - 1] = data[i];
//			}
//			length--;
//		}
//	
//		// ���� ������ ũ�⸦ ���Ѵ�
//		int size() { return length; }
//	
//		// i��° ���ҿ� j��° ���� ��ġ�� �ٲ۴�
//		void swap(int i, int j)
//		{
//			T temp = data[i];
//			data[i] = data[j];
//			data[j] = temp;
//		}
//	
//		~Vector()
//		{
//			if (data)
//			{
//				delete[] data;
//			}
//		}
//	
//	private:
//		T* data;
//		int capacity;
//		int length;
//	};
//	
//	// �Լ� ��ü ���� �� bubble_sort : �������� ���ĸ� �����ϴ�
//	template <typename Cont>
//	void bubble_sort(Cont& cont)
//	{
//		for (int i = 0; i < cont.size(); i++)
//		{
//			for (int j = i + 1; j < cont.size(); j++)
//			{
//				if (cont[i] > cont[j])
//				{
//					cont.swap(i, j);
//				}
//			}
//		}
//	}
//	
//	// �Լ� ��ü�� ���Ե� bubble_sort
//	template <typename Cont, typename Comp>
//	void bubble_sort(Cont& cont, Comp& comp)
//	{
//		for (int i = 0; i < cont.size(); i++)
//		{
//			for (int j = i + 1; j < cont.size(); j++)
//			{
//				if (!comp(cont[i], cont[j]))
//				{
//					cont.swap(i, j);
//				}
//			}
//		}
//	}
//	
//	struct Comp1
//	{
//		bool operator()(int a, int b) { return a > b; }
//	};
//	
//	struct Comp2
//	{
//		bool operator()(int a, int b) { return a < b; }
//	};
//	
//	int main()
//	{
//		Vector<int> int_vec;
//		int_vec.push_back(3);
//		int_vec.push_back(1);
//		int_vec.push_back(2);
//		int_vec.push_back(8);
//		int_vec.push_back(5);
//		int_vec.push_back(3);
//	
//		std::cout << "���� ���� ---- " << std::endl;
//		for (int i = 0; i < int_vec.size(); i++)
//		{
//			std::cout << int_vec[i] << " ";
//		}
//	
//		std::cout << std::endl << "���� ���� ---- " << std::endl;
//		bubble_sort(int_vec);
//		for (int i = 0; i < int_vec.size(); i++)
//		{
//			std::cout << int_vec[i] << " ";
//		}
//		std::cout << std::endl;
//	
//		std::cout << std::endl << "�Լ� ��ü ����"  << std::endl;
//	
//		std::cout << "�������� ���� ���� ---- " << std::endl;
//	
//		Comp1 comp1;
//		bubble_sort(int_vec, comp1);
//	
//		for (int i = 0; i < int_vec.size(); i++)
//		{
//			std::cout << int_vec[i] << " ";
//		}
//		std::cout << std::endl;
//		
//		std::cout << "�������� ���� ���� ---- " << std::endl;
//	
//		Comp2 comp2;
//		bubble_sort(int_vec, comp2);
//	
//		for (int i = 0; i < int_vec.size(); i++)
//		{
//			std::cout << int_vec[i] << " ";
//		}
//		std::cout << std::endl;
//	
//	
//	
//		//	struct dummy {};
//		//	dummy a;
//		//	bubble_sort(a);	// ����
//	
//		/*
//			output:
//			���� ���� ----
//			3 1 2 8 5 3
//			���� ���� ----
//			1 2 3 3 5 8
//			
//			�Լ� ��ü ����
//			�������� ���� ���� ----
//			8 5 3 3 2 1
//			�������� ���� ���� ----
//			1 2 3 3 5 8
//		*/
//	
//		/*
//			- �Լ� ���ø� 2
//				- bubble_sort() �Լ��� ������ �����̳� cont�� �޾� �������ִ� �Լ�
//					- template <typename Cont>�� �Լ� ���ø��� ����, bubble_sort(int_vec) ȣ��� bubble_sort<Vector<int>>(int_vec)���� �ν��Ͻ�ȭ ��
//					- �� �Լ��� �۵��� �Ϸ��� size(), swap(), operator[] �� ���ǵǾ� �־�� ��
//						-> ���� �ƹ��͵� ���� dummy ����ü�� ����� �Լ� ȣ��� �ش� �Լ��� �����ڰ� �����Ƿ� ������ �߻���
//						-> �̷��� ������ ���α׷� ����ð� �ƴ϶� �����Ͻÿ� �߻���. �����Ͻÿ� ���ø� �ڵ尡 ���� �ڵ�� ��ȯ�Ǳ� ����
//							-> �̷��� ������ �ÿ� ��� ���ø����� �ν��Ͻ�ȭ �ȴٴ� ���� �̿��� ���α׷��� ����� ���ø� ��Ÿ ���α׷���(template meta programming)��
//				- �� �ڵ忡���� �����������θ� �����ϰ� �����������δ� ������ �Ұ���
//					-> �ذ��� 3����
//						1) bubble_sort2()�� ����� �ε�ȣ ������ �ݴ�� �ٲ� -> C��Ÿ��
//						2) operator> �� �����ε� �Ͽ� ���ϴ� ������� ���� -> ����
//						3) cont[i] �� cont[j]�� �񱳸� >�� ���� ���� Ư�� �Լ��� �־ ���� -> �Լ� ��ü�� �������� ������
//			
//			- �Լ� ��ü(Function Object - Functor)�� ����
//				- �� 3���� �ذ��� �� 3���� �ش�Ǵ� ������ �ذ��ϱ� ���� ���
//				- 2��° bubble_sort �Լ��� ����
//					- template<typename Cont, typename Comp> : Comp ��ü�� ���� ���ø� ���ڷ� ����
//					- Comp ��ü -> if(!comp(cont[i], cont[j])) : �Լ� ȣ��ó�� ����. cont[i]�� cont[j]�� �޾Ƽ� ���������� ũ�⸦ ��
//						-> !! comp�� �Լ��� �ƴ϶� ��ü�̰�, Comp Ŭ�������� ()�����ڸ� �����ε� �� �� !!
//							struct Comp1
//							{
//								bool operator()(int a, int b) { return a > b; }
//							};
//							
//							struct Comp2
//							{
//								bool operator()(int a, int b) { return a < b; }
//							};
//						-> ��ó�� �Լ��� �ƴ����� �Լ��� ô�� �ϴ� ��ü�� �Լ� ��ü(Function Object, �ٿ��� Functor)��� �θ�
//						-> ���� <algorithm>�� sort() �Լ��� ��Ŭ������ �޴� ������ ���� �ʴ� ���� 2������ ������
//	
//				- �Լ� �����Ͱ� �ִµ� �̰� �� �ʿ��Ѱ���?
//					- Ŭ���� ��ü�� �������� ���� state�� �����ؼ� �� ��ü�� ������ ��쿡�� �ս��� ����ڰ� ���ϴ� ������� ����� �� �� ����
//					- �Լ� �����ʹ� �����Ϸ��� ����ȭ�� �� ������ Functor�� operator()�� �����Ϸ��� �ζ���ȭ ���� ������ �۾��� ������ -> ������尡 �׳� ����������
//		*/
//	}

// Ÿ���� �ƴ� ���ø� ����

//	#include <iostream>
//	#include <array>
//	
//	template <typename T, int num>
//	T add_num(T t)
//	{
//		return t + num;
//	}
//	
//	// std::array<int, 5> �� ��ü�� �ϳ��� Ÿ���̹Ƿ� �Լ��� �̷��� ������ ��
//	void print_array(const std::array<int, 5>& arr)
//	{
//		for (int i = 0; i < arr.size(); i++)
//		{
//			std::cout << arr[i] << " ";
//		}
//		std::cout << std::endl;
//	}
//	
//	// ���� �׳� ���ø��ᵵ ��
//	template<typename T>
//	void print_array(const T& arr)
//	{
//		for (int i = 0; i < arr.size(); i++)
//		{
//			std::cout << arr[i] << " ";
//		}
//		std::cout << std::endl;
//	}
//	
//	int main()
//	{
//		int x = 3;
//		std::cout << "x : " << add_num<int, 5>(x) << std::endl;
//		// add_num(x);	// E0304: �μ� ����� ��ġ�ϴ� �Լ� ���ø� "add_num"�� �ν��Ͻ��� �����ϴ�.
//	
//		/*
//			output:
//			x : 8
//		*/
//	
//		// ���ø� Ư��ȭ�� Ȱ�� std::array
//	
//		std::array<int, 5> arr = { 1, 2, 3, 4, 5 };
//		// �̴� int arr[5] = {1, 2, 3, 4, 5}; �� ������
//		std::array<int, 7> arr2 = { 1, 2, 3, 4, 5, 6, 7 };
//		std::array<int, 3> arr3 = { 1, 2, 3 };
//	
//		print_array(arr);
//		print_array(arr2);
//		print_array(arr3);
//	
//		/*
//			- Ÿ���� �ƴ� ���ø� ����(non-type template arguments)
//				- ���ø��� ���ڷ� Ÿ�Ը� �� �� �ִ°��� �ƴ�
//				- �� �ڵ带 ����
//					- template <typename T, int num> T add_num(T t) : template�� ���ڷ� T�� �ް� �߰������� �Լ��� ����ó�� int num�� �ް�����
//					- add_num<int, 5>(x) : T�� int, num�� 5�� ���޵Ǿ� �����Ͻ� �Ʒ��� �Լ��� ������
//	
//						int add_num(int t) { return t + 5; }
//	
//					- �� ��� �Լ� ȣ��� �ݵ�� ���ø� ����<>�� ��������� �������־�� ��
//						-> �� ��쿡�� <>�� ������� ������ num�� ���� ������ �����Ϸ� ���忡�� �� ���� ����
//	
//				- ���ø� ���ڷ� ������ �� �ִ� Ÿ�Ե��� �Ʒ��� ���� ��������
//					- ���� Ÿ�Ե�(bool, char, int, long ���). �翬�� float, double�� ����...���µ� C++ 20 ���� ����
//					- ������ Ÿ��
//					- enum Ÿ��
//					- std::nullptr_t (�� ������)
//					- C++ 20���� �� ������ �� ��ȭ�� https://en.cppreference.com/w/cpp/language/template_parameters �� ����
//	
//				- ���ø� ���ڰ� ���� ���� Ȱ��Ǵ� ���� : ������ Ÿ�ӿ� ���� �������� �ϴ� ���(�迭�� ũ�� ��)
//					-> ���� STL�� std::array�� �̸� Ȱ����
//						-> ���� C��Ÿ�� �迭�� ������ �Լ��� �迭 ���޽� �迭�� ũ�⿡ ���� ������ ������ٴ� ���� ��������
//						-> std::array�� �翬�� ��Ÿ�ӿ� �������� ũ�Ⱑ Ŀ���� �ʰ� �����Ͻ� ���ÿ� �޸𸮸� �Ҵ���
//						-> ������ std::array<int, 5> ���� �����ϸ� ����ü�� �ϳ��� Ÿ���� �ǹǷ� �پ��� ũ�⿡ ���� �Լ��� ����� �־�� ��
//	
//							void print_array(const std::array<int, 5>& arr)
//	
//							-> ��� �׷� �ʿ� ���� �̰͵� ���ø� �Լ��� �ѹ��� �� �� ����
//	
//								template<typename T>
//								void print_array(const T& arr) {}
//		*/
//	}

// ����Ʈ ���ø� ����

#include <iostream>

template <typename T, int num = 5>
T add_num(T t)
{
	return t + num;
}

template <typename T, typename Comp = Compare<T>>
T Min(T a, T b)
{
	Comp comp;
	if (comp(a, b))
		return a;

	return b;
}

template <typename T>
struct Compare
{
	bool operator()(const T& a, const T& b) const { return a < b; }
};

int main()
{
	int x = 3;
	std::cout << "x : " << add_num(x) << std::endl;

	int a = 3, b = 5;
	std::cout << "Min " << a << " , " << b << " :: " << Min(a, b) << std::endl;

	std::string s1 = "abc", s2 = "def";
	std::cout << "Min " << s1 << " , " << s2 << " :: " << Min(s1, s2) << std::endl;

	/*
		output:
		x : 8
		Min 3 , 5 :: 3
		Min abc , def :: abc
	*/

	/*
		- ���ø� ����Ʈ ����
			- �Լ� ����Ʈ ����ó�� = (����Ʈ ��) ���� ����
			- ù��° add_num�� ��� ����Ʈ�� num�� 5�� ����
				-> ���ٸ� ���� ��� ���� add_num<int, 5>(x)�� �����Ϸ��� �˾Ƽ� �߷��Ͽ� ����
			- �ι�° Compare�� ��� ���� Min<int, Compare<int>>(a, b) �̷� ������ �Լ� ��ü�� ������� �ʿ� ������
				-> �˾Ƽ� Ÿ�Կ� �°� ����Ʈ�� Compare<T>�� Comp�� ���޵�
	
	*/
}

// �߰�: ���ø� ���� Ÿ�� ������ ��Ģ https://en.cppreference.com/w/cpp/language/template_argument_deduction