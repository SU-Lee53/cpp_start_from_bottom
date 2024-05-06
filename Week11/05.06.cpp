
/*
	05.06 STL3 �˰���
*/

/*  STL�� <algorithm>  */
/*
	- <algirithm>
		- �����̳��� �ݺ��ڵ��� �̿��� ���� �۾����� �����ϴ� ���̺귯��
		- �⺻������ �Ʒ��� 2������ ���·� �ۼ���

			template <typename Iter>
			void do_something(Iter begin, Iter end);
			
			template <typename Iter, typename Pred>
			void do_something(Iter begin, Iter end, Pred pred);
			
			-> ���� �˰����� �������� �������� �޾� �۾��� ����
			-> �Ʒ��� ������, ������ �Բ� Ư���� ������ �߰� ���ڷ� ������ �̷��� Ư���� ������ "������(Predicate)"��� �θ�
				-> �����ڿ��� ���� bool�� �����ϴ� �Լ� ��ü�� ���ų� ���� �Լ��� ��
*/

/*  ����  */
//	#include <algorithm>
//	#include <iostream>
//	#include <vector>
//	#include <functional>
//	#include <string>
//	
//	template <typename Iter>
//	void print(Iter begin, Iter end)
//	{
//		while (begin != end)
//		{
//			std::cout << *begin << " ";
//			begin++;
//		}
//		std::cout << std::endl;
//	}
//	
//	struct int_compare
//	{
//		bool operator()(const int& a, const int& b) const { return a > b; }
//	};
//	
//	struct User
//	{
//		std::string name;
//		int age;
//	
//		User(std::string name, int age) : name(name), age(age) {}
//	
//		bool operator<(const User& u) const { return age < u.age; }
//	};
//	
//	std::ostream& operator<<(std::ostream& o, const User& u)
//	{
//		o << "[" << u.name << " , " << u.age << "]";
//		return o;
//	}
//	
//	int main()
//	{
//		/*  std::sort  */
//		{
//			std::cout << "std::sort" << std::endl;
//	
//			std::vector<int> vec;
//			vec.push_back(5);
//			vec.push_back(3);
//			vec.push_back(1);
//			vec.push_back(6);
//			vec.push_back(4);
//			vec.push_back(7);
//			vec.push_back(2);
//	
//			std::cout << "���� �� ----" << std::endl;
//			print(vec.begin(), vec.end());
//	
//			std::sort(vec.begin(), vec.end());
//			std::cout << "�������� ���� �� ----" << std::endl;
//			print(vec.begin(), vec.end());
//	
//			//	std::sort(vec.begin(), vec.end(), int_compare());	// ���� �Լ� ��ü�� ����� ����
//			std::sort(vec.begin(), vec.end(), std::greater<int>());	// <functional> ����� ���ø� Ŭ������ �̿�. ���ϴ� �⺻ Ÿ���� ������ �ڵ����� �Լ� ��ü�� ����
//			std::cout << "�������� ���� �� ----" << std::endl;
//			print(vec.begin(), vec.end());
//		}
//	
//		std::cout << std::endl;
//	
//		/*  std::partial_sort  */
//		{
//			std::cout << "std::partial_sort" << std::endl;
//	
//			std::vector<int> vec;
//			vec.push_back(5);
//			vec.push_back(3);
//			vec.push_back(1);
//			vec.push_back(6);
//			vec.push_back(4);
//			vec.push_back(7);
//			vec.push_back(2);
//	
//			std::cout << "���� �� ----" << std::endl;
//			print(vec.begin(), vec.end());
//	
//			std::partial_sort(vec.begin(), vec.begin() + 3, vec.end());
//			std::cout << "���� �� ----" << std::endl;
//			print(vec.begin(), vec.end());
//		}
//	
//		std::cout << std::endl;
//	
//		/* std::stable_sort  */
//		{
//			std::cout << "std::stable_sort" << std::endl;
//	
//			std::vector<User> vec;
//			for (int i = 0; i < 100; i++)
//			{
//				std::string name = "";
//				name.push_back('a' + i / 26);
//				name.push_back('a' + i % 26);
//				vec.push_back(User(name, static_cast<int>(rand() % 10)));
//			}
//	
//			std::vector<User> vec2 = vec;
//	
//			std::cout << "���� �� ----" << std::endl;
//			print(vec.begin(), vec.end());
//	
//			std::sort(vec.begin(), vec.end());
//			std::cout << "���� �� ----" << std::endl;
//			print(vec.begin(), vec.end());
//	
//			std::stable_sort(vec2.begin(), vec2.end());
//			std::cout << "stable_sort �� ���" << std::endl;
//			print(vec2.begin(), vec2.end());
//		}
//	
//		/*
//			- output:
//			std::sort
//			���� �� ----
//			5 3 1 6 4 7 2
//			�������� ���� �� ----
//			1 2 3 4 5 6 7
//			�������� ���� �� ----
//			7 6 5 4 3 2 1
//			
//			std::partial_sort
//			���� �� ----
//			5 3 1 6 4 7 2
//			���� �� ----
//			1 2 3 6 5 7 4
//	
//			stable_sort�� ���� ��� ����
//		*/
//	
//		/*
//			- <algorithm> �� sort
//				- �⺻������ sort, partial_sort, stable_sort �̷��� 3������ ������
//				- ��� sort�� �ݺ��� Ÿ���� RandomAccessIterator���� �ϹǷ� vector, deque������ ��� ������
//					-> list�� BidirectionalIterator �̹Ƿ� �Ұ���
//					-> array�� ������
//	
//				- std::sort
//					- �⺻Ÿ�Ե鿡 ���ؼ� ������ �����ڰ� ������ �������� ������
//					- ���������� �ƴ� �ٸ� ������ ���ؼ��� 2���� ����� ������
//						1) ���� �񱳸� ���� �Լ� ��ü�� ����� �����ڷ� ����
//						2) functional ����� ���ø� �Լ��� �̿��Ͽ� �����ڷ� ����
//							-> �� ����� �⺻Ÿ���� �ƴϸ� operator>�� ������ �����ε� �Ǿ��־�� ��
//				
//				- std::partial_sort
//					- ���ϴ� �Ϻκи� ������
//					- (start, mid, end) �� 3���� ���ڸ� �ް� [start, end) ������ ������ [start, mid) ������ ���ҵ鸸 ������
//						-> �� [start, end/mid)? : ���κ� �ݺ��ڴ� �׻� ���� ������ ��ĭ �ڿ� ����
//					- �� ���� ������ std::sort�� ������
//	
//				- std::stable_sort
//					- ���Ľ� ���ԵǾ� �ִ� ������ ���� ������ ������
//					
//				- ������ �ð����⵵�� ���Ǵ� �˰���
//					- �翬�� STL ����ü���� ����ϴ� �˰����� �ٸ�. C++ ǥ�ؿ� � �˰����� ������� ��Ȯ�� ���� ���� ����
//					- �Ϲ������� ���� ���Ǵ� �˰����� ����
//	
//					- sort, partial sort
//						- �������� �� ������ �̿��Ͽ����� �־��� ��� O(N^2)�� �ð����⵵�� ������ �������� ����� https://cplusplus.github.io/LWG/issue713
//						- ����� Introsort�� �̿��Ͽ� �׻� O(N log N)�� ����
//							-> Introsort�� Timsort�� ���������� ��� ���̰� ������� �����Ŀ��� �����ķ� �ٲ�
//							-> ��� ���̳� ������ ũ�⿡ ���� �� -> �� -> ���� ������ ������ ����
//	
//					- stable_sort
//						- �̰� ������ ����ü���� ���� �ٸ������� ���� 
//						- �⺻������ ���������� ���� ����ϴ°����� ����
//						- �⺻������ O(N log N) ������ �޸𸮰� ������ ��� O(N log^2 N) ���� �������ٰ� ��
//		*/
//	
//	}

/*  ���� ����, ���� �Լ�  */
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename Iter>
void print(Iter begin, Iter end)
{
	while (begin != end)
	{
		std::cout << "[" << *begin << "] ";
		begin++;
	}
	std::cout << std::endl;
}

struct is_odd
{
	bool operator()(const int& i) { return i % 2 == 1; }
};

int main()
{
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	std::cout << "ó�� vec ���� ------" << std::endl;
	print(vec.begin(), vec.end());

	std::cout << "���Ϳ��� ���� 3�� ���� ���� ---" << std::endl;
	vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());
	print(vec.begin(), vec.end());

	std::cout << "���Ϳ��� Ȧ���� ���� ���� ---" << std::endl;
	//	vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd()), vec.end());
	vec.erase(std::remove_if(vec.begin(), vec.end(), [](int i) -> bool { return i % 2 == 1; }), vec.end()); // ���� �Լ� �̿�
	print(vec.begin(), vec.end());
}

