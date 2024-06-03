/*
	06.03 shared_ptr, weak_ptr
*/

/*  std::shared_ptr  */
//	#include <iostream>
//	#include <memory>
//	#include <vector>	
//	
//	class A 
//	{
//	public:
//		A()
//		{
//			data = new int[100];
//			std::cout << "�ڿ��� ȹ����" << std::endl;
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
//	int main()
//	{
//		// std::shared_ptr<A> p1(new A());
//		std::shared_ptr<A> p1 = std::make_shared<A>();	// shared_ptr�� make_shared �� �̿��ؼ� ����� ���� �� ����
//		std::shared_ptr<A> p2 = p1;	// shared_ptr �� ���� ��ü�� ������ ���� ����
//	
//		std::cout << "-----------------" << std::endl;
//	
//		std::vector<std::shared_ptr<A>> vec;
//	
//		vec.push_back(std::shared_ptr<A>(new A()));
//		vec.push_back(std::shared_ptr<A>(vec[0]));
//		vec.push_back(std::shared_ptr<A>(vec[1]));
//	
//		std::cout << "vec.begin() �� ���� ���� : " << vec.begin()->use_count() << std::endl << std::endl;
//	
//		std::cout << "ù ��° �Ҹ�" << std::endl;
//		vec.erase(vec.begin());
//		std::cout << "vec.begin() �� ���� ���� : " << vec.begin()->use_count() << std::endl << std::endl;
//	
//		std::cout << "���� ���� �Ҹ�" << std::endl;
//		vec.erase(vec.begin());
//		std::cout << "vec.begin() �� ���� ���� : " << vec.begin()->use_count() << std::endl << std::endl;
//	
//		std::cout << "������ ���� �Ҹ�" << std::endl;
//		vec.erase(vec.begin());
//	
//		std::cout << "���α׷� ����" << std::endl;
//		std::cout << "-----------------" << std::endl;
//	
//		/*
//			- output :
//				�ڿ��� ȹ����
//				-----------------
//				�ڿ��� ȹ����
//				vec.begin() �� ���� ���� : 3
//				
//				ù ��° �Ҹ�
//				vec.begin() �� ���� ���� : 2
//				
//				���� ���� �Ҹ�
//				vec.begin() �� ���� ���� : 1
//				
//				������ ���� �Ҹ�
//				�Ҹ��� ȣ��
//				���α׷� ����
//				-----------------
//				�Ҹ��� ȣ�� -> �� ���� p1 �� �����ߴ� ��ü�� �Ҹ�Ǵ°� -> RAII �� �۵���
//		*/
//	
//		/*
//			- std::shared_ptr
//				- std::shared_ptr : �ϳ��� ��ü�� �������� �����Ͱ� ����ų �� �ִ� ����Ʈ ������
//					- ������ �������� �ο��ϴ� unique_ptr �� �޸� �̸� �״�� �� ��ü�� �������� shared_ptr �� ����Ŵ(����)
//	
//				- ���� ����(reference count) �� ����
//					- Ư�� ��ü�� �����ϴ� shared_ptr�� ������ ��
//					- ���� ������ 0 �� �Ǿ�߸� �ش� ��ü�� �Ҹ��Ŵ
//					- � shared_ptr�� ���� ������ �˰�ʹٸ� use_count() ��� �Լ��� ����ϸ� �� �� ����
//					- ����
//	
//						std::shared_ptr<A> p1(new A());
//						std::shared_ptr<A> p2 = p1;
//	
//						-> �� ��� p1, p2�� ���� ������ 2
//	
//				- �� �ڵ��� ����
//					- shared_ptr�� ��� vector�� vec�� ����
//					- vec[0]�� A ��ü�� �����ϰ� �̸� ����Ű�� shared_ptr �� push_back
//					- vec[1]���� vec[0]�� ����Ű�� shared_ptr �� push_back
//					- vec[2]���� vec[1]�� ����Ű�� shared_ptr �� push_back
//						-> [0], [1], [2] ��� ���� A ��ü�� ����Ű���� ��. �Ʒ� �׸��� ���� ����
//							
//								  class A <--------------+-------------------+
//							         ��                   |                   |
//							vec	0[ shared_ptr<A> ] 1[ shared_ptr<A> ] 2[ shared_ptr<A> ]
//	
//					- [0], [1], [2] �� �ȿ� �ִ� shared_ptr�� ���� ������ 3
//					- vec.begin() ���� �� �� ���� -> A�� �Ҹ��� ȣ����� ����
//					- vec.begin() ���� vec�� ��� ���Ҹ� �Ҹ��� �ڿ� A�� �Ҹ��ڰ� ȣ��
//						-> ���� ������ 0�� �Ǿ�� ��μ� ��ü�� �Ҹ��
//					
//				- ���� ���� ���� ���
//					- ���� ������ shared_ptr �ȿ� ������� ����
//						- ���� ���� ������ shared_ptr �ȿ� ����ȴٸ�...
//	
//							std::shared_ptr<A> p1(new A());
//							std::shared_ptr<A> p2 = p1;
//							std::shared_ptr<A> p3 = p2;
//	
//							-> �� ���� �ڵ尡 ���� �� ���� ���� ī��Ʈ�� ������ ����
//								-> p1.use_count() == 2
//								-> p2.use_count() == 3
//								-> p3.use_count() == 3
//								-> p3�� p2�� ���� ������ ++ �������� p1���� �ǵ帱 ���� ����
//	
//					- ���� ������ ������ ���� ����� ���� ������
//						- ó������ ���� ��ü�� ����Ű�� shared_ptr �� ���� ����� �������� �Ҵ�
//							-> �� ������ ��� p1�� �Ҵ���
//						- ���� �ٸ� shared_ptr���� �����Ͽ� �ʿ��� �������� ������
//							-> shared_ptr ���� ������ ���� ����� ��ġ�� �˸� ��
//							-> shared_ptr ������ ���� ��Ͽ� �ִ� ���� ������ ++
//							-> shared_ptr �Ҹ�� ���� ��Ͽ� �ִ� ���� ������ --
//	
//				- std::make_shared
//					- unique_ptr �� make_unique ó�� shared_ptr�� make_shared �� ����
//					- shared_ptr �� ��� make_shared �� �̿��ϴ� ���� �� ����
//	
//						1) �Ϲ����� ������� shared_ptr�� ����� ���
//							
//							std::shared_ptr<A> p(new A());
//	
//							-> A�� ����µ� �����Ҵ� 1��
//							-> shared_ptr�� �������� ����µ� �����Ҵ� 1��
//								-> �� 2���� �����Ҵ��� �Ͼ
//	
//						2) std::make_shared �� �̿��ϴ� ���
//	
//							std::shared_ptr<A> p = std::make_shared<A>();
//	
//							-> �� ��� A() �� �Ҵ�� �������� �Ҵ��� �ѹ��� ������
//							
//					- make_shared ���� ���ڸ� �����ڿ� �����ϴ� �Ϻ��� ������ ������
//	
//	
//		*/
//	
//	}

/*  shared_ptr ���� �� ������, enable_shared_from_this */
#include <iostream>
#include <memory>

class A : public std::enable_shared_from_this<A>	// std::enable_shared_from_this �� ��ӹ��� ������ this�� shared_ptr�� ����� �ȵ�
{
public:
	A()
	{
		data = new int[100];
		std::cout << "�ڿ� ȹ��" << std::endl;
	}

	~A()
	{
		std::cout << "�Ҹ��� ȣ��" << std::endl;
		delete[] data;
	}

	std::shared_ptr<A> get_shared_ptr() 
	{ 
		// return std::shared_ptr<A>(this); 
		return shared_from_this();
	}

private:
	int* data;
};

int main()
{
	int* a = new int(5);
	auto p1 = std::make_shared<int*>(a);
	auto p2 = std::make_shared<int*>(a);
	// p1 �� p2 �� ������ ���� ����� ����
	// ���� ���� ī��Ʈ�� ������ ���� main ����� double free ���׷� ��Ÿ�� ���� �߻�


	auto pa1 = std::make_shared<A>();
	auto pa2 = pa1->get_shared_ptr();

	std::cout << pa1.use_count() << std::endl;	// 1
	std::cout << pa2.use_count() << std::endl;	// 1
	// ���������� pa1 �� pa2�� ������ �������� ����
	// �׷��Ƿ� �̰͵� double free ���װ� ����
	// std::enable_shared_from_this �� ��ӹ����� ���� �ذ��

	/*
		- shared_ptr ���� �� ������
			- shared_ptr �� ���ڷ� �ּҰ��� ���޵Ǹ� �ڽ��� �ش� ��ü�� ù��°�� �����ϴ� ���̶�� �ν���
				-> ��, ������ �������� �ְ� ���� ���ο� ���� ����� ����
				-> �� �ڵ忡�� p1, p2�� ���� �Ʒ��� ����

					+-------------+
					| ���� ���   |
					|             | <----------- p1 ----------------+
					| ��������: 1 |                                 |
					+-------------+                                 ��
					                                              new A()
					+-------------+                                 ��
					| ���� ���   |                                 |
					|             | <----------- p2 ----------------+
					| ��������: 1 |
					+-------------+

					-> p1 �� �Ҹ�Ǹ� ���� ������ 0�̹Ƿ� A�� �Ҹ��
					-> �׷��� p2 �� ���� ������ ������ 1 �̹Ƿ� A�� ����ϰų� �Ҹ��Ű���� �� �� ����
						-> �� ��� ��Ÿ�� ������ �߻�

				-> pa1 �� pa2 �� ��쵵 ���� ����������
					-> pa2 �� pa1 �ȿ��� this �� �̿��ؼ� ������ shared_ptr
					-> ���� pa2�� pa1 ���� �ٸ� ������ ���� ����� ����� ������

			- �̷��� ������ �������� shared_ptr �� �ּҰ��� �̿��ؼ� �����ϴ� ���� �����ϸ� ��
				-> �׷��� ��¿ �� ���� ��쵵 ������

		- std::enable_shared_from_this<T>
			- ��ü ���ο��� �ڱ� �ڽ��� ����Ű�� shared_ptr�� ����� ���� ��¿�� ���� ��쿡 ��ӹ޾� �����
			- enable_shared_from_this �ȿ� shared_from_this() �� �̿��ϸ� this �� �̿��Ͽ� shard_ptr�� �����Ͽ� ������
				-> �̶� �̹� �ִ� �������� �̿��ϹǷ� �ݵ�� �ش� ��ü�� shared_ptr�� ���� �����ؾ���
				-> shared_from_this �� �������� Ȯ�θ� ��. ���� �������� ���� ������ִ� ���� ���� ����
	
	*/

}

/*  shared_ptr�� ��ȯ���� ����  */