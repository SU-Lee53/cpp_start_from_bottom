
/*
	04.29 ~ 04.30 STL1 - ������ �����̳� (vector, list, deque), �ݺ���
*/

// STL

/*
	- STL
		- Standard Template Library�� ���Ӹ��� ���ø��� ����� C++�� ǥ�� ���̺귯���� ����
		- ���� STL�ϸ� ũ�� 3���� ���̺귯���� �ǹ���
			-> ���� Ÿ���� ��ü�� ������ �� �ִ� �����̳�(container)
			-> �����̳ʿ� ������ ���ҿ� ������ �� �ִ� �ݺ���(iterator)
			-> �ݺ��ڵ��� ������ �Ϸ��� �۾��� �����ϴ� �˰���(algorithm)
			+ �׹ۿ� �����(iostream), �ð� ����(chrono), ����ǥ����(regex) ����� ����
		- ���ø��� ����ϹǷ� �츮�� �ٷ���� ��ü�� Ư���� �����ϰ� �����Ӱ� ���̺귯���� ����� �� ����
		- ���� �ݺ��ڸ� �̿��Ͽ� �����̳ʸ� �߻�ȭ ��ų �� �����Ƿ� �ּ����� �ڵ�� �˰��� ���̺귯���� �ʿ��� �ڵ带 �ۼ��� �� �ְԵ�
*/

// �����̳�

/*
	- �����̳�
			- STL�� �����̳ʴ� ũ�� 2���� ������ ����
				-> ������ �����̳�(sequence container) : ��ü���� ���������� ����
					-> vector, list, deque
				-> ���� �����̳�(associative container) : Ű�� �������� ������� ���� ã����
					-> set, map, unordered_set, unordered_map

			- ��� �����̳ʵ��� �۾��� ���� �ӵ����� ���� ������ ��Ȳ�� �´� �����̳ʸ� ������ ���� ���� �߿���
*/

// std::vector

//	#include <iostream>
//	#include <vector>
//	
//	int main()
//	{
//		std::vector<int> vec;
//		vec.push_back(10);
//		vec.push_back(20);
//		vec.push_back(30);
//		vec.push_back(40);
//	
//		for (std::vector<int>::size_type i = 0; i < vec.size(); i++)
//		{
//			std::cout << "vec �� " << i + 1 << " ��° ���� :: " << vec[i] << std::endl;
//		}
//	
//		
//		/*
//			output:
//			vec �� 1 ��° ���� :: 10
//			vec �� 2 ��° ���� :: 20
//			vec �� 3 ��° ���� :: 30
//			vec �� 4 ��° ���� :: 40
//		*/
//	
//		/*
//			- std::vector
//				- ���� ���� �迭
//					-> ������ ���ҵ��� �޸𸮻� ���������� �����
//					-> ���� ������ ��ġ�� �ִ� ������ ������ �ſ� ����
//	
//				- �ð����⵵
//					-> ������ ��ġ ���� ����([], at) : O(1)
//					-> �� �ڿ� ���� �߰� �� ����(push_back / pop_back) : amortized O(1) -> �Ʒ����� ����
//					-> ������ ��ġ ���� �߰� �� ����(insert, erase) : O(n)
//	
//				- vector�� �۵����, amortized O(1)�� �ǹ�
//					- armortized : ���� ��ȯ
//					- �� ���� �߰� �� ������ �ð����⵵�� amortized O(1) �ΰ�
//						- vector�� �۵������ �����ؾ���
//							- ���� vector�� ���� ������ �ִ� ������ �������� �� ���� ������ �̸� �Ҵ��� ����
//								-> ������� ���Ұ� 10����� 20���� ��������� �̸� �Ҵ�
//							- �̶� ���ο� ���Ҹ� �߰��� �� ������ ����
//								1) ���Ӱ� ���Ҹ� �߰��� ��������� �Ҵ�Ǿ� �ִ°�� -> O(1)�� �׳� �߰� ����
//								2) �Ҵ�� ������ �� ä���� ���
//									-> ���ο� �� ū ������ ���� �Ҵ��ϰ�, ������ ���ҵ��� �����ؾ���
//									-> �� �������� n���� ���Ҹ� ���� �����ؾ� �ϹǷ� O(n)�� �ð��� �Ҹ��
//							- �ٸ� ��κ��� ��� O(1)�� ����Ǳ� ������ amortized O(1)�̶�� �θ��� ����
// 
//				- vector ���� �پ��� �Լ����� �����ϰ� �����ε�Ǵ� �پ��� �������� ������
//					-> ���߿� cppreference�� �����ϸ� �ٷ� ����
//		*/
//	}

// �ݺ���(iterator)

//	#include <iostream>
//	#include <vector>
//	#include <typeinfo>
//	
//	template <typename T>
//	void print_vector(std::vector<T>& vec)
//	{
//		for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end(); ++itr)
//		{
//			std::cout << *itr << std::endl;
//		}
//	}
//	
//	template <typename T>
//	void print_vector_range_based(std::vector<T>& vec)
//	{
//		for (const auto& elem : vec)
//		{
//			std::cout << elem << std::endl;
//		}
//	}
//	
//	int main()
//	{
//		/* �ݺ��� ���� */
//		//	{
//		//		std::vector<int> vec;
//		//		vec.push_back(10);
//		//		vec.push_back(20);
//		//		vec.push_back(30);
//		//		vec.push_back(40);
//		//	
//		//		for (std::vector<int>::iterator itr = vec.begin(); itr != vec.end(); ++itr)
//		//		{
//		//			std::cout << *itr << std::endl;
//		//		}
//		//	
//		//		auto itr = vec.begin() + 2;
//		//		std::cout << "3��° ���� :: " << *itr << std::endl;
//		//	
//		//		/*
//		//			- output:
//		//			10
//		//			20
//		//			30
//		//			40
//		//			3��° ���� :: 30
//		//		*/
//		//	}
//	
//		/* �ݺ��ڸ� �̿��� print_vector, insert, erase */
//		//	{
//		//		std::vector<int> vec;
//		//		vec.push_back(10);
//		//		vec.push_back(20);
//		//		vec.push_back(30);
//		//		vec.push_back(40);
//		//	
//		//		std::cout << "ó�� ���� ����" << std::endl;
//		//		print_vector(vec);
//		//		std::cout << "----------------------------------" << std::endl;
//		//	
//		//		// vec[2] �տ� 15 �߰�
//		//		vec.insert(vec.begin() + 2, 15);
//		//		print_vector(vec);
//		//	
//		//		std::cout << "----------------------------------" << std::endl;
//		//	
//		//		// vec[3] ����
//		//		vec.erase(vec.begin() + 3);
//		//		print_vector(vec);
//		//	
//		//		std::cout << "----------------------------------" << std::endl;
//		//	
//		//		/*
//		//			output:
//		//			ó�� ���� ����
//		//			10
//		//			20
//		//			30
//		//			40
//		//			----------------------------------
//		//			10
//		//			20
//		//			15
//		//			30
//		//			40
//		//			----------------------------------
//		//			10
//		//			20
//		//			15
//		//			40
//		//			----------------------------------
//		//		*/
//		//	
//		//		// �ݺ��ڸ� �̿��� insert, erase�� ������
//		//		std::vector<int>::iterator itr = vec.begin();
//		//		std::vector<int>::iterator end_itr = vec.end();
//		//	
//		//		//	for (; itr != end_itr; ++itr)
//		//		//	{
//		//		//		if (*itr == 20)
//		//		//		{
//		//		//			vec.erase(itr);	// ��Ÿ�� ����: can't increment invalidated vector iterator
//		//		//		}
//		//		//	}	
//		//		// �����̳ʿ� ���Ҹ� �߰��ϰų� �����ϸ� ������ ����ϴ� ��� �ݺ��ڵ��� ����� �� ����
//		//		// ��, vec.erase(itr) ���� ���� itr, end_itr ��� ��ȿȭ�ǰ� itr != end_itr�� ������ �����Ͽ� ���ѷ����� ����
//		//	
//		//		//	for (; itr != vec.end(); ++itr)
//		//		//	{
//		//		//		if (*itr == 20)
//		//		//		{
//		//		//			vec.erase(itr);
//		//		//			itr = vec.begin();
//		//		//		}
//		//		//	}	// ��ȿ����: 20�� ����� ó������ ���ư� ���Ҹ� ����
//		//	
//		//		for (std::vector<int>::size_type i = 0; i != vec.size(); i++)
//		//		{
//		//			if (vec[i] == 20)
//		//			{
//		//				vec.erase(vec.begin() + i);
//		//				i--;
//		//			}
//		//		}	// ������� ����: ���� ���� ����� ���ϵ��� ����
//		//	
//		//		// ���߿� �� ������ <algorithm> ���̺귯���� ����ϰ� �ذ��ϵ��� ��
//		//	}
//	
//		/* ��� �ݺ��� const_iterator */
//		//	{
//		//		std::vector<int> vec;
//		//		vec.push_back(10);
//		//		vec.push_back(20);
//		//		vec.push_back(30);
//		//		vec.push_back(40);
//		//	
//		//		std::cout << "ó�� ���� ����" << std::endl;
//		//		print_vector(vec);
//		//		
//		//		// itr�� vec[2]�� ����Ų��
//		//		std::vector<int>::iterator itr = vec.begin() + 2;
//		//	
//		//		// vec[2] �� ���� 50���� �ٲ۴�
//		//		*itr = 50;
//		//	
//		//		std::cout << "------------" << std::endl;
//		//		print_vector(vec);
//		//	
//		//		std::vector<int>::const_iterator citr = vec.cbegin() + 2;
//		//	
//		//		// ��� �ݺ��ڰ� ����Ű�� ���� �ٲ� �� ����
//		//		//	*citr = 30;	// C3892 'citr': const�� ������ �Ҵ��� �� �����ϴ�.
//		//	
//		//		/*
//		//			- output:
//		//			ó�� ���� ����
//		//			10
//		//			20
//		//			30
//		//			40
//		//			------------
//		//			10
//		//			20
//		//			50
//		//			40
//		//		*/
//		//	}
//	
//		/* ���ݺ��� reverse_iterator*/
//		//	{
//		//		std::vector<int> vec;
//		//		vec.push_back(10);
//		//		vec.push_back(20);
//		//		vec.push_back(30);
//		//		vec.push_back(40);
//		//	
//		//		std::cout << "ó�� ���� ����" << std::endl;
//		//		print_vector(vec);
//		//	
//		//		std::cout << "������ vec ����ϱ�" << std::endl;
//		//		std::vector<int>::reverse_iterator r_iter = vec.rbegin();
//		//		for (; r_iter != vec.rend(); r_iter++)
//		//		{
//		//			std::cout << *r_iter << std::endl;
//		//		}
//		//		
//		//		/*
//		//			- output:
//		//			ó�� ���� ����
//		//			10
//		//			20
//		//			30
//		//			40
//		//			������ vec ����ϱ�
//		//			40
//		//			30
//		//			20
//		//			10
//		//		*/
//		//	
//		//		// ���ݺ��ڸ� ������� �ʰ� ������ ��� -> ����
//		//		//	for (std::vector<int>::size_type i = vec.size() - 1; i >= 0; i--)
//		//		//	{
//		//		//		std::cout << vec[i] << std::endl;	// vector subscript out of range
//		//		//	}
//		//		//	std::cout << typeid(std::vector<int>::size_type).name() << std::endl;	// -> unsigned __int64
//		//		// vector�� index�� ����ϴ� std::vector<int>::size_type �� ��ȣ���� ����(unsigned __int64) �̹Ƿ� ���������� ������ �� ���� ���ѷ����� ����
//		//		// i�� int�� �ϸ� �����۵� �ϱ� ������ ���ݺ��ڸ� �̿��ϴ°��� �� ���� �����
//		//	}
//	
//		/* ���� ��� for �� range based for loop */
//		//	{
//		//		std::vector<int> vec;
//		//		vec.push_back(10);
//		//		vec.push_back(20);
//		//		vec.push_back(30);
//		//		vec.push_back(40);
//		//	
//		//		for (int elem : vec)
//		//		{
//		//			std::cout << "���� : " << elem << std::endl;
//		//		}
//		//	
//		//		std::cout << "print_vector" << std::endl;
//		//		print_vector(vec);
//		//		std::cout << "print_vector_range_based" << std::endl;
//		//		print_vector_range_based(vec);
//		//	
//		//		/*
//		//			- output:
//		//			���� : 10
//		//			���� : 20
//		//			���� : 30
//		//			���� : 40
//		//			print_vector
//		//			10
//		//			20
//		//			30
//		//			40
//		//			print_vector_range_based
//		//			10
//		//			20
//		//			30
//		//			40
//		//		*/
//		//	}
//	
//		/*
//			- �ݺ��� iterator
//				- �����̳��� ���ҿ� ������ �� �ִ� �����Ϳ� ���� ��ü
//				- �⺻������ �����̳� �ȿ� iterator ��� Ÿ������ ���ǵǾ� ���� -> std::vector<>::iterator
//				- vector�� ��� �ݺ��ڸ� ��� ���� �Լ���� �� ��ġ�� �Ʒ��� ����
//					-> ���� ��� std::vector<int> vec = {1, 2, 3, 4, 5, 6}; �̶�� �ϸ�
//	
//							[1][2][3][4][5][6][ ]
//							 ^                 ^
//						vec.begin()			vec.end()
//						vec.cbegin()		vec.cend()
//					
//					-> end()�� ������ ���Ұ� �ƴ� ��ĭ �ڸ� ����Ű�� �ݺ��ڸ� ������
//					-> �̸� ���� begin() == end() �̸� ���Ұ� ������ �� �� ����(����ִ� ����)
//	
//				- �ݺ����� �̿�
//					- ��ü ���͸� ����ϴ� �ڵ�
//	
//						for (std::vector<T>::iterator itr = vec.begin(); itr != vec.end(); ++itr) std::cout << *itr << std::endl;
//	
//						-> vec.begin() ���� vec.end()�� �� �ƴҶ� ���� ����ؼ� �ݺ��ϸ� ó������ ������ ���Ե�
//						-> ++itr�� itr++�� �ٲ㵵 ����� ���������� ++itr�� �� ���� ����
//							-> https://stackoverflow.com/questions/1077026/incrementing-iterators-is-it-more-efficient-than-it
//							-> ���ʿ��� ���縦 �ٿ� ���� �� �����ٰ� ��
//	
//					- �ݺ��ڸ� �̿��� insert(), erase()
//	
//						// vec[2] �տ� 15 �߰�
//						vec.insert(vec.begin() + 2, 15);
//						print_vector(vec);
//	
//						// vec[3] ����
//						vec.erase(vec.begin() + 3);
//						print_vector(vec);
//	
//					- insert(), erase() ���� ������
//	
//						std::vector<int>::iterator itr = vec.begin();
//						std::vector<int>::iterator end_itr = vec.end();
//	
//						for (; itr != end_itr; ++itr)
//						{
//							if (*itr == 20)
//							{
//								vec.erase(itr);	// ��Ÿ�� ����: can't increment invalidated vector iterator
//							}
//						}
//	
//						-> erase�� �Ǹ� �ش� ���Ϳ��� ����ϴ� �ݺ��ڵ��� ���� ��ȿȭ��
//						-> ���� itr != end_itr �� ������ �����Ǿ� ���ѷ����� ����
//						-> insert�� �Ҵ� ������ ������ ���Ҵ��� �� ��� ��ȿȭ��
//						-> �ڼ��Ѱ� https://en.cppreference.com/w/cpp/container/vector �� Iterator invalidation �� ����
//						-> �� ���ÿ� �̸� �ذ��ϴ� ����� ��� �� ������ STL�� <algorithm>�� ����� �ذ���� �����Ƿ� ����
//	
//				- ��� �ݺ��� const_iterator
//					- �Ϲ� �ݺ���ó�� �����̳ʿ� ���ǵǾ����� -> std::vector<>::const_iterator
//					- ��� ������ó�� ����Ű�� ������ ���� ������ �� ����
//					- cbegin(), cend() �� �̿��Ͽ� �ݺ��ڸ� ���� �� ����
//	
//				- ���ݺ��� reverse_iterator
//					- �ٸ� �ݺ��ڵ� ó�� �����̳ʿ� ���ǵǾ����� -> std::vector<>::reverse_iterator
//					- ���ݺ��ڸ� ��� ���� �Լ��� �����ϴ� ��ġ�� �Ʒ��� ����
//	
//							[ ][1][2][3][4][5][6]
//							 ^                 ^
//						vec.rend()			vec.rbegin()
//						vec.crend()			vec.crbegin()
//	
//					- �̰͵� ��� ���ݺ��ڰ� �����ϸ� crbegin(), crend()�� ���� �� ����
//					- �����̳��� ���Ҹ� ������ �����ϴ� ����� ���� ���� �����
//	
//				- ���� ��� for �� range based for loop
//					- ������ �پ��ϰ� ������ �ݺ��ڸ� �̿��� for���� C++11���� �ſ� �����ϰ� �� �� �ֵ��� �� ���
//					- �Ʒ��� ���� �����(vec�� ���Ұ� int �� ���)
//	
//						for (int elem : vec)
//						{
//							std::cout << "���� : " << elem << std::endl;
//						}
//						
//						-> elem �� vec�� ���Ұ� �� �������� ����Ǽ� ��
//						-> elem = vec[i] �� �Ͱ� ����
//	
//					- ���۷����� ���� ���� ����.
//					- auto�� �̿� ������. ���ô� �Ʒ��� ����
//						for (const auto& elem : vec)
//						{
//							std::cout << elem << std::endl;
//						}
//	
//					- ���� ��� for ���� �̿��ϸ� �ڵ尡 �������̰� ���������� ������ ����
//				
//		*/
//	
//	
//	}

// std::list

//	#include <iostream>
//	#include <list>
//	#include <forward_list>	// C++11�� �߰��� �ܹ��� ���Ḯ��Ʈ
//	
//	template <typename T>
//	void print_list(std::list<T>& lst)
//	{
//		std::cout << "[ ";
//		for (const auto& elem : lst)
//		{
//			std::cout << elem << " ";
//		}
//		std::cout << "]" << std::endl;
//	}
//	
//	int main()
//	{
//		std::list<int> lst;
//	
//		lst.push_back(10);
//		lst.push_back(20);
//		lst.push_back(30);
//		lst.push_back(40);
//	
//		std::cout << "ó�� ����Ʈ�� ����" << std::endl;
//		print_list(lst);
//	
//		for (std::list<int>::iterator itr = lst.begin(); itr != lst.end(); ++itr)
//		{
//			// ���� ���� ���Ұ� 20 �̶��
//			// �� �տ� 50�� ����ִ´�.
//			if (*itr == 20)
//			{
//				lst.insert(itr, 50);
//			}
//		}
//	
//		std::cout << "���� 20�� ���� �տ� 50�� �߰�" << std::endl;
//		print_list(lst);
//	
//		for (std::list<int>::iterator itr = lst.begin(); itr != lst.end(); ++itr)
//		{
//			if (*itr == 30)
//			{
//				lst.erase(itr);
//				break;
//			}
//		}
//	
//		std::cout << "���� 30�� ���Ҹ� ����" << std::endl;
//		print_list(lst);
//		
//		/*
//			- output:
//			ó�� ����Ʈ�� ����
//			[ 10 20 30 40 ]
//			���� 20�� ���� �տ� 50�� �߰�
//			[ 10 50 20 30 40 ]
//			���� 30�� ���Ҹ� ����
//			[ 10 50 20 40 ]
//		*/
//	
//		/*
//			- std::list
//				- ����� ���Ḯ��Ʈ
//				- list�� �ݺ��ڴ� vector�� �ݺ��ڿ� �ణ �ٸ�
//					- itr++, ++itr, itr--, --itr ������ ������
//					- itr + 5 ó�� ������ ��ġ�� ���Ҹ� ����Ű�� ������ �Ұ�����
//					- insert(), erase() �� �����Ͽ��� �ݺ��ڰ� ��ȿȭ���� ���� -> �� ���ҵ��� �ּҰ��� �ٲ��� �ʱ� ����
//						-> ���Ḯ��Ʈ�� list�� ������ ���� ������ �Ұ����ϰ� ��ĭ�� ���������θ� ������ �� ����
//						-> �̶����� �ݺ����� Ÿ���� �ٸ��⵵ ��. vector�� RandomAccessIterator, list�� BidirectionalIterator
//							-> �ݺ����� Ÿ���� �Ŀ� �ٷ�
//				- �ð����⵵
//					-> ������ ��ġ ���� ����([], at) : �Ұ���
//					-> �� ��,�� �ڿ� ���� �߰� �� ����(push_front, push_back / pop_front, pop_back) : O(1)
//					-> ������ ��ġ ���� �߰� �� ����(insert, erase) : O(1)
//		*/
//	}

// std::deque

//	#include <iostream>
//	#include <deque>
//	#include <concepts>
//	
//	template <typename T>
//	void print_deque(std::deque<T>& dq)
//	{
//		std::cout << "[ ";
//		for (const auto& elem : dq)
//		{
//			std::cout << elem << " ";
//		}
//		std::cout << "]" << std::endl;
//	}
//	
//	int main()
//	{
//		std::deque<int> dq;
//		dq.push_back(10);
//		dq.push_back(20);
//		dq.push_front(30);
//		dq.push_front(40);
//	
//		std::cout << "�ʱ� dq ����" << std::endl;
//		print_deque(dq);
//	
//		std::cout << "�� ���� ���� ����" << std::endl;
//		dq.pop_front();
//		print_deque(dq);
//	
//	
//		/*
//			- output:
//			�ʱ� dq ����
//			[ 40 30 10 20 ]
//			�� ���� ���� ����
//			[ 30 10 20 ]
//		*/
//	
//		/*
//			- std::deque
//				- �ſ� Ư���� ������ �Ǿ�����. ������ �Ʒ��� ����
//					
//					[		]
//					[ ���1 ]	--���1-->	[       ][       ][       ][       ][data[0]] <- deq.begin()
//					[ ���2 ]	--���2-->	[data[1]][data[2]][data[3]][data[4]][data[5]]
//					[ ���3 ]	--���3-->	[data[6]][       ][       ][       ][       ]
//					[		]						     ^
//					    ^							  deq.end()
//					������ ��ϵ��� �ּҸ� ����Ű�� �������� ����
//	
//					- ���ҵ��� �޸𸮿� ���ӵǾ� �������� �ʰ�, ���� ũ��� �߷��� ������ ��� �ӿ� ������
//					- �� ��ϵ��� �ּҸ� �����ϴ� ���Ͱ� ������ ������
//					- �̶� ù��° ����� ���ʰ� ������ ����� ������ �Ϻθ� �� �������� ���ܵ� -> �� ��, �� �� ����/������ O(1)�� �ӵ��� �����ϰ� ��
//						-> ���� �����ڸ� ���͸� �����ϰ� �ɰ��� ������ ������ ��
//	
//				- ���Ϳ� �����ϰ� ��� �����ϸ鼭�� ���ͺ��� ����
//					-> ���� ��ġ ���� ����([], at()), RandomAccessIterator ���
//				- �׷��� ���ͺ��� �޸� �Ҹ� �ſ� ŭ -> 64��Ʈ libc++ ���̺귯�� ���� 1���� ���Ҹ� �����ϴ� deque�� �� ���� ũ���� 8���� �޸𸮸� �����
//				- �Ϲ������� �Ǿ�, �ǵ� ���� �߰��� O(1)�� �ð��� ������ ��� �ּ� ���Ͱ� �� ���ٸ� ����ó�� ���簡 �Ͼ�Ƿ� ���� �� ������
//	
//				- �ð����⵵
//					-> ������ ��ġ ���� ����([], at) : O(1)
//					-> �� ��,�� �ڿ� ���� �߰� �� ����(push_front, push_back / pop_front, pop_back) : O(1)
//					-> ������ ��ġ ���� �߰� �� ����(insert, erase) : O(n)
//		*/
//	
//	}

// ����, � ������ �����̳ʸ� ����ұ�

/*
	- ����, � ������ �����̳ʸ� ����ұ�
		- � �۾��� ���� �ϴ��Ŀ� ���� �ٸ�
			-> �Ϲ����� ��Ȳ : std::vector
			-> �� ���� �ƴ� �߰����� ������ �߰� ���Ű� ���� �Ͼ, ���Ҹ� ���������θ� ������ : std::list
			-> �� ó���� �� �� ��ο��� ������ �߰��� ���� �Ͼ : std::deque
	
*/