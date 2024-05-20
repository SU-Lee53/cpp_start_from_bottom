/*
	05.20 C++�� ����ó��
*/

/*  ����  */
//	#include <iostream>
//	#include <vector>
//	
//	int main()
//	{
//		//	std::vector<int> v(3);
//		//	std::cout << v.at(4);	// ũ�Ⱑ 3�ε� 4�� �ε��� ���� -> ����
//		//	
//		//	std::vector <int> v2(1'000'000'000'000);	// �����ϰ� ū �޸� �Ҵ� -> ����
//	
//		/*
//	
//			- ����
//				- �������� ��Ȳ���� ��� ��� �������� ��Ȳ
//				- �� �ڵ���� ������ ������ ���÷� ������ Ʋ������ ������ ������ �߻���
//	
//		*/
//	}

/*  C ��Ÿ�� ����ó��  */
//	#include <iostream>
//	
//	bool func2(int* addr);
//	bool func3(int* addr);
//	
//	bool func1(int* addr)
//	{
//		if (func2(addr))
//		{
//			// Do something
//		}
//		return false;
//	}
//	
//	bool func2(int* addr)
//	{
//		if (func3(addr))
//		{
//			// Do something
//		}
//		return false;
//	}
//	
//	bool func3(int* addr)
//	{
//		addr = (int*)malloc(1'000'000'000'000);
//		if (addr == NULL) return false;
//	
//		return true;
//	}
//	
//	int main()
//	{
//		/*  ����ó�� : �����ϰ� �и��� ���  */
//		//	{
//		//		char* c = (char*)malloc(1'000'000'000'000);
//		//		if (c == NULL)
//		//		{
//		//			printf("�޸� �Ҵ� ����");
//		//			return 0;
//		//		}
//		//	}
//	
//		/*  ����ó�� : ������ ���  */
//		{
//			int* addr = NULL;
//			if (func1(addr))
//			{
//				printf("����");
//			}
//			else
//			{
//				printf("���ܹ߻�");
//			}
//		}
//	
//		/*
//			- C ������ ����ó��
//				- �⺻������ C������ ���� ó���� �������� ���� https://en.cppreference.com/w/c/keyword ��¥��
//					-> ���߿� �߰��� <errno.h> �� �̿��ϸ� �Ϻ� �����ϱ� �� https://www.geeksforgeeks.org/error-handling-in-c/
//	
//				- C������ ��κ��� ���̺귯�� �Լ����� ������ �߻��ϸ� -1 Ȥ�� NULL�� ��ȯ��
//					- malloc �� ���÷� �޸� �Ҵ翡 �����ϸ� NULL�� ��ȯ��
//	
//				- �̸� �̿��Ͽ� �۾� �� ������� Ȯ���ϴ� ������� ����ó���� ��
//				- �׷��� �Լ��� ��������� ��� ������ �߻��Ͽ����� �˱� ����ٴ� ������ ����
//					- ���� ��� �� �ڵ��� ������ ��츦 ����
//						-> func1 ���� func2 �� ȣ��
//						-> func2 ���� func3 �� ȣ��
//						-> func3 ���� �޸� �Ҵ� ����
//							-> ���� func1 �� func2 ������ ���ܰ� �߻��� �� �ִ� �۾��� �ִٸ� ��� ���ܰ� �߻��ϴ��� �˱� �����
//	
//				- �̷� �������� ������ C++�� ���ο� ���� ó�� ����� ������
//		*/
//	
//		return 0;
//	}

/*  C++ �� ����ó��1 - ���� �߻� throw  */
//	#include <iostream>
//	
//	template <typename T>
//	class Vector
//	{
//	public:
//		Vector(size_t size) : _size(size)
//		{
//			_data = new T[_size];
//			for (int i = 0; i < _size; i++)
//			{
//				_data[i] = 3;
//			}
//		}
//	
//		const T& at(size_t index) const
//		{
//			if (index >= _size)
//			{
//				// ���� �߻�
//				throw std::out_of_range("Vector �� index �� ������ �ʰ��Ͽ����ϴ�.");
//			}
//			return _data[index];
//		}
//	
//		~Vector() { delete[] _data; }
//	
//	private:
//		T* _data;
//		size_t _size;
//	};
//	
//	int main()
//	{
//		Vector<int> v(3);
//		v.at(4);
//	
//		/*
//			- ���� �߻� throw
//				- ���ܸ� �߻���Ű�� ������ ����ϴ� Ű����
//				- ���ܷ� �����ϰ� ���� ��ü�� ���� �� ����
//	
//				- C++ ǥ�ؿ� �̹� ���� ������ ���� ��ü���� �����ϹǷ� �̰͵��� ����ϴ� �͵� ����
//					- ���ܵ��� <stdexcept> ����� ������ https://en.cppreference.com/w/cpp/header/stdexcept
//					- �⺻������ �Ʒ��� ���� ��ü���� ����
//						- logic_error
//							- invalid_argument
//							- domain_error
//							- length_error
//							- out_of_range
//						- runtime_error
//							- range_error
//							- overflow_error
//							- underflow_error
//	
//	
//	
//		*/
//	
//	}

/*  C++ �� ����ó��2 - ���� ó�� try-catch  */
//	#include <iostream>
//	#include <stdexcept>
//	
//	template <typename T>
//	class Vector
//	{
//	public:
//		Vector(size_t size) : _size(size)
//		{
//			_data = new T[_size];
//			for (int i = 0; i < _size; i++)
//			{
//				_data[i] = 3;
//			}
//		}
//	
//		const T& at(size_t index) const
//		{
//			if (index >= _size)
//			{
//				// ���� �߻�
//				throw std::out_of_range("Vector �� index �� ������ �ʰ��Ͽ����ϴ�.");
//			}
//			return _data[index];
//		}
//	
//		~Vector() { delete[] _data; }
//	
//	private:
//		T* _data;
//		size_t _size;
//	};
//	
//	int main()
//	{
//		Vector<int> v(3);
//	
//		int index, data = 0;
//		std::cin >> index;
//	
//		try
//		{
//			data = v.at(index);
//		}
//		catch (std::out_of_range& e)
//		{
//			std::cout << "���� �߻�! " << e.what() << std::endl;
//		}
//	
//		// ���ܰ� �߻����� �ʴ´ٸ� 3 ���
//		// ���ܰ� �߻��ϸ� ���� data�� �� �ִ� 0�� ���
//		std::cout << "���� ������ : " << data << std::endl;
//	
//	
//		/*
//			- input : 1
//			- output :
//				���� ������ : 3
//	
//			- input : 3
//			- output :
//				���� �߻�! Vector �� index �� ������ �ʰ��Ͽ����ϴ�.
//				���� ������ : 0
//		*/
//	
//		/*
//			- try-catch
//				- throw �� ���� ���ܸ� �޾� ó���ϴ� ���
//				- �⺻������ ������ ���� ���
//				
//					try { ... } catch (const std::exception& e) { ... }
//	
//				- try ��Ͽ����� ���ܰ� �߻��� �� �ִ� �ڵ带 ����
//					-> ���ܰ� �߻� : ��� ���� ����� catch ���� ���� + ��� ���ο��� ������ ��� ��ü���� �Ҹ��
//					-> ���� �߻� ���� : catch ���� ����
//	
//				- catch ���
//					- throw �� ���� ���� �߿��� () �ȿ� ���ǵ� ���ܸ� ����
//					- �˸��� ���ܸ� �޾Ҵٸ� {} ��� ������ �ڵ带 ������
//	
//			++ std::out_of_range
//				- ���ܿ� ���� ������ �����ϴ� ���ڿ� �ʵ� �ϳ��� ������
//				- ��� �Լ��� what() �� ����ϸ� ���ܿ� ���� ������ �� �� ����
//					-> ������ ���� catch ��� ������ e.what() ���� "Vector �� index �� ������ �ʰ��Ͽ����ϴ�." �� �� �� ����
//	
//		*/
//	
//	
//	
//	}

/*  ���� Ǯ��  */
//	#include <iostream>
//	#include <stdexcept>
//	
//	class Resource
//	{
//	public:
//		Resource(int id) : _id(id) {}
//		~Resource() { std::cout << "���ҽ� ���� : " << _id << std::endl; }
//	
//	private:
//		int _id;
//	};
//	
//	int func3()
//	{
//		Resource r(3);
//		throw std::runtime_error("Exception from 3!\n");
//		
//		// ���� �̹߻��� ���
//		// return 0;
//	}
//	
//	int func2()
//	{
//		Resource r(2);
//		func3();
//		std::cout << "����!" << std::endl;
//		return 0;
//	}
//	
//	int func1()
//	{
//		Resource r(1);
//		func2();
//		std::cout << "����!" << std::endl;
//		return 0;
//	}
//	
//	int main()
//	{
//		Resource r(-1);
//		try
//		{
//			Resource r(0);
//			func1();
//		}
//		catch (std::exception& e)
//		{
//			std::cout << "Exception : " << e.what();
//		}
//	
//		/*
//			- ���� �߻� output:
//				���ҽ� ���� : 3
//				���ҽ� ���� : 2
//				���ҽ� ���� : 1
//				���ҽ� ���� : 0
//				Exception : Exception from 3!
//				���ҽ� ���� : -1
//		
//			- ���� �̹߻� output:
//				���ҽ� ���� : 3
//				����!
//				���ҽ� ���� : 2
//				����!
//				���ҽ� ���� : 1
//				���ҽ� ���� : 0
//				���ҽ� ���� : -1
//		*/
//	
//		/*
//			- ���� Ǯ�� stack unwinding
//				- ���� Ǯ��
//					- ���� ��ü�� �����ǰ� ���� ���� ����� �˸��� catch�� ã������ ȣ�� ������ Ÿ�� �������鼭 try ���� ������������ �̵���
//					- ȣ�⽺���� Ÿ�� �������鼭 try ���� ���� ���� �ı����� ���� ���� ��ü���� �ı��ڰ� ������ ������ �������� ȣ���
//						-> �̷��� ������ Ÿ�� catch�� ���� �ϸ鼭 ���� �� ���ǵ� ��ü���� �Ҹ��Ű�� ������ ���� Ǯ��(stack unwinding) �̶�� ��
//	
//				- ���� �ڵ�
//					- func1() -> func2() -> func3() ������ ����ǰ� func3() ���� ���� �߻�
//						-> �� �Լ����� 1, 2, 3 ���� ��ü�� ����
//					- func3() ���� ���ܰ� �߻��ϸ� ��� catch ���� ã�� ������ Ÿ�� ������ �̵�
//						-> ���� ����
//							[ func3() ]
//							[ func2() ]
//							[ func1() ]
//							[  main() ]
//					
//					- �˸��� catch ���� main()�� �����Ƿ� func3() -> func2() -> func1() -> main() ������ ���� �帧�� �̵���
//					- catch ���� ���� try ���� func3, 2, 1, main �� ��ü���� �ı��ڰ� ������ ���� �ݴ�� ȣ���
//	
//					- ���� func3() �� ���ܸ� ������ �ʴ´ٸ� func2, 1 �� "����" �� ���� ����ϰ� �Լ��� ����ɶ� ��ü�� �Ҹ��
//	
//				- ���ǻ���
//					- ������/�Ҹ��� ���� ���ܰ� �߻��ϸ� �Ҹ��ڰ� ȣ����� ����
//						-> ���� ���ܸ� ������ ���� �Ҵ�� �ڿ��� �ִٸ� catch ���� ���� �����ؾ���
// 
//					- heap �� �����Ҵ�� ��ü�� �Ҹ���� ����
//		*/
//	}