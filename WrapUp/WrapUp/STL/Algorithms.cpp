
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

/*  ���� ����  */
//	#include <algorithm>
//	#include <functional>
//	#include <iostream>
//	#include <string>
//	#include <vector>
//	
//	template <typename Iter>
//	void print(Iter begin, Iter end)
//	{
//		while (begin != end)
//		{
//			std::cout << "[" << *begin << "] ";
//			begin++;
//		}
//		std::cout << std::endl;
//	}
//	
//	struct is_odd
//	{
//		/*
//			- ó�� 2���� Ȧ�� ���Ҹ� �����ϱ� ���� ��� ������ num_delete�� ���
//				-> C++ ǥ�ؿ����� remove_if �� ���޵Ǵ� �Լ� ��ü�� ��� ȣ�⿡ ���� ���� ���°� �޶����� �ȵ�
//				-> �� num_delete�� �������� ������ ī���� �ϹǷ� ���� ���°� �޶����� �ǹǷ� �̷��� ���(�ν��Ͻ� ���� ���)�� �ȵ�
//	
//			- ��κ��� ���̺귯���� remove_if �Լ��� find_if�� ������(Pred)�� ���۷����� �ƴ� ���� ������ ����
//			- ������ ���� �����ڿ� ���ǿ� �����ϴ� ��츦 ã�� ���� �ѹ� find_if() �Լ��� ȣ���ϹǷ� ���� �ȿ��� ȣ��Ǵ� ������ �Լ��� ������ ī��Ʈ ����� ��
//			- �Լ� ��ü�� ���� ���� ���ذ� ����
//	
//				_EXPORT_STD template <class _FwdIt, class _Pr>
//				_NODISCARD_REMOVE_ALG _CONSTEXPR20 _FwdIt remove_if(_FwdIt _First, const _FwdIt _Last, _Pr _Pred) {
//					// remove each satisfying _Pred
//					_Adl_verify_range(_First, _Last);
//					auto _UFirst      = _Get_unwrapped(_First);
//					const auto _ULast = _Get_unwrapped(_Last);
//					_UFirst           = _STD find_if(_UFirst, _ULast, _Pass_fn(_Pred));					<- �̺κп��� ������ �Լ�(Pred)�� �����Ͽ� �ѹ� ����
//					auto _UNext       = _UFirst;
//					if (_UFirst != _ULast) {
//						while (++_UFirst != _ULast) {
//							if (!_Pred(*_UFirst)) {														<- ���⼭ Pred�� ȣ���� �� ������ num_delete�� 1�� �� ������ �Ҹ��
//								*_UNext = _STD move(*_UFirst);
//								++_UNext;
//							}
//						}
//					}
//				
//					_Seek_wrapped(_First, _UNext);
//					return _First;
//				}
//	
//			- �� ������ �ذ��Ϸ��� num_delete�� ��ü ���� ������ �ƴ� �ܺη� ������
//		*/
//		//	int num_delete;
//		//	is_odd() : num_delete(0) {}
//	
//		int& num_delete;
//		is_odd(int& num_delete) : num_delete(num_delete) {}
//	
//		bool operator()(const int& i) 
//		{ 
//			if (num_delete >= 2) return false;
//			if (1 % 2 == 1)
//			{
//				num_delete++;
//				return true;
//			}
//			return false;
//		}
//	};
//	
//	int main()
//	{
//		std::vector<int> vec;
//		vec.push_back(5);
//		vec.push_back(3);
//		vec.push_back(1);
//		vec.push_back(2);
//		vec.push_back(3);
//		vec.push_back(4);
//	
//		std::cout << "ó�� vec ���� ------" << std::endl;
//		print(vec.begin(), vec.end());
//	
//		//	std::cout << "���Ϳ��� ���� 3�� ���� ���� ---" << std::endl;
//		//	vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());
//		//	print(vec.begin(), vec.end());
//	
//		//	std::cout << "���Ϳ��� Ȧ���� ���� ���� ---" << std::endl;
//		//	vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd()), vec.end());
//		//	print(vec.begin(), vec.end());
//	
//		//	std::cout << "���Ϳ��� Ȧ���� ���� 2�� ���� ���� ---" << std::endl;
//		//	int num_delete = 0;
//		//	vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd(num_delete)), vec.end());
//		//	print(vec.begin(), vec.end());
//	
//		// ��ó�� ���ص� C++ 20 ���ʹ� erase_if�� ������(Ȧ�� ���� ����� ����, ���� �Լ� �̿�)
//		auto count = std::erase_if(vec, [](int i) -> bool { return i % 2 == 1; });
//		print(vec.begin(), vec.end());	// [2] [4]
//		std::cout << "������ Ȧ���� ���� :: " << count << std::endl; //	������ Ȧ���� ���� :: 4
//	
//		/*
//			- ���� ����
//				- remove / remove_if �� ����. �ٸ� ������ ���������� �ʰ� �����̳��� ����Լ��� erase�� �Բ� ����ؾ���
//					-> �ΰ��� �Լ��� �̿��Ͽ� ���Ҹ� ����� ���� Erase-remove idiom �̶�� �θ� https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
//					-> C++ 20 ���ʹ� erase/erase_if �� �̿��Ͽ� ������� ����. �Ʒ��� ����
//		
//				- remove �� ������ �ϴ���
//					- remove �Լ��� ���ڷ� ���� �ݺ��� ���� �ȿ� ������ ���ڷ� ���� ������ ������ ���ڸ� �߰��ϸ� �� ���� ���ҵ��� �������� ����Ʈ��
//					- �� �ڵ��� ��� �Ʒ�ó�� �۵���
//	
//						5  3  1  2  3  4	: ó�� vec ����
//						5  1  1  2  3  4	: vec[1]�� 3�� ã�����Ƿ� �� ���� ������ 1�� ����Ʈ
//						5  1  2  2  3  4	: ���������� 2�� ����Ʈ
//						5  1  2  4  3  4	: ���� 3�� �߰��Ͽ����Ƿ� �����ϰ� 4�� ����Ʈ
//						            ^ 
//							�ش� ��ġ�� �ݺ��ڸ� ���� -> �� �ڸ� ���� 3�� ���ܵ� ���ҵ�θ� ä����
//	
//						-> ������� �ϴ� ���Ҹ� �ڷ� �̵���Ű�� ���� �ƴ�!
//						-> �׳� �����ϰ� �ٸ� ���ҵ��� ����Ʈ ��Ű�°��̸� ���ϵ� �ݺ��� �޺κ��� ������ ������ �����Ⱚ�� ��
//	
//					- ���� �����̳��� erase �Լ��� ���� ���� ��ġ���� end()���� ��������
//						-> C++20 ���������� erase �Լ��� ���ڷ� ���� ��ġ �ϳ��� ����ų� first, last�� �޾� �� ���̸� ��� ����ų� �ۿ� ���� ����
//				
//				- remove_if ���� remove�� ���������� ���� �ϸ� �ٸ����� ������ �Լ� ��ü(Pred)�� ���� �� ����
//					-> remove_if�� ���޵Ǵ� �Լ���ü�� ���� ������ ���ڸ� 1���� ���� �� �ְ� const�� �ƴϾ�� �ϸ� bool Ÿ���� �����ؾ� �� (�̸� UnaryPredicate ���� ������ ��� ��)
//					
//				- remove_if �� �Լ� ��ü�� bool�� �����ϴ� ���� �����ڰ� ���Ƿ� ���ҿ� ���� ���� ����� �߰����� ������ �����ϱ� �����
//					- �̸� ���� �Լ� ��ü ���ο� ������ ����� �����ϴ� ����� ����ؼ��� �ȵ�
//						-> �ϴ� remove_if�� ��� ���������� ���� ������ ǥ���� ����
//						-> ���� ���̺귯������ �Լ� ��ü�� ������ ������ �� �ֵ��� �Ǿ��ֱ� ������ ���� ���� ������ �Ҹ�Ǳ⵵ �ϱ� ������
//	
//					- �ܺο� ������ �δ� ����� ������
//						-> �� ��� �Ź� Ŭ������ �Լ��� ����� �־�� �Ѵٴ� �������� �ְ�, ������Ʈ�� Ŀ������ �������� ������
//	
//					- ���� ���� ����� C++ 11�� �߰��� ���� �Լ��� �̿��ϴ� ����
//						-> ���� �Լ��� �Ʒ� �ܶ����� ����
//	
//				- C++ 20���ʹ� erase / erase_if �� �̿��Ͽ� �ٷ� ���Ҹ� ������ �� ����
//	
//					std::erase_if(vec, [](int i) -> bool { return i % 2 == 1; });
//	
//					-> erase_if�� ���ϴ� �����̳ʸ� ���۷����� �޾� �����ϰ� ��� �������� ������ ���� �ش� �����̳��� size_type���� ������
//		*/
//	}

/*  ���� �Լ�  */
//	#include <iostream>
//	#include <algorithm>
//	#include <functional>
//	#include <vector>
//	
//	template <typename It>
//	void print(It begin, It end)
//	{
//		for(;begin != end; ++begin)
//			std::cout << "[" << *begin << "] ";
//		std::cout << std::endl;
//	}
//	
//	// Ŭ���� ���ο��� capture list �� ���
//	class SomeClass
//	{
//	public:
//		SomeClass()
//		{
//			vec.push_back(5);
//			vec.push_back(3);
//			vec.push_back(1);
//			vec.push_back(2);
//			vec.push_back(3);
//			vec.push_back(4);
//	
//			num_erased = 1;
//	
//			//	vec.erase(std::remove_if(vec.begin(), vec.end(), 
//			//		[&num_erased](int i) -> bool {
//			//			if (num_erased >= 2) return false;
//			//			else if (i % 2 == 1)
//			//			{
//			//				num_erased++;
//			//				return true;
//			//			}
//			//			return false;
//			//		}),
//			//		), vec.end());
//			// SomeClass::num_erased �� �Ϲ� ������ �ƴ϶� ��ü�� ���ӵ� ��� �����̹Ƿ� ĸ���� �� ����
//	
//			vec.erase(std::remove_if(vec.begin(), vec.end(),
//				[this](int i) -> bool {
//					if (this->num_erased >= 2) return false;
//					else if (i % 2 == 1)
//					{
//						this->num_erased++;
//						return true;
//					}
//					return false;
//				}
//				), 
//				vec.end());	// ��� ���� ĸ�� �ʿ�� ��ü�� ��°�� �Ѱܹ޾ƾ���
//		}
//	
//	private:
//		std::vector<int> vec;
//		int num_erased;
//	};
//	
//	int main()
//	{
//		std::vector<int> vec;
//		vec.push_back(5);
//		vec.push_back(3);
//		vec.push_back(1);
//		vec.push_back(2);
//		vec.push_back(3);
//		vec.push_back(4);
//	
//		std::cout << "ó�� vec ���� ------" << std::endl;
//		print(vec.begin(), vec.end());
//	
//		//	std::cout << "���Ϳ��� Ȧ���� ���� ���� ---" << std::endl;
//		//	
//		//	vec.erase(std::remove_if(vec.begin(), vec.end(), [](int i) -> bool { return i % 2 == 1; }), vec.end());	// �⺻��: [capture list](�޴� ����) -> ����Ÿ�� { �Լ� ��ü }
//		//	
//		//	//	vec.erase(std::remove_if(vec.begin(), vec.end(), [](int i) { return i % 2 == 1; }), vec.end());	// ���� Ÿ���� ����:  [capture list](�޴� ����) { �Լ� ��ü }
//		//	
//		//	//	bool(*func)(int) = [](int i) -> bool { return i % 2; };						// Ȥ��
//		//	//	std::function<int(bool)> func = [](int i) -> bool { return i % 2 == 1; };	// Ȥ��(<functional> include �ʿ�)
//		//	//	auto func = [](int i) -> bool { return i % 2 == 1; };						// auto�� ����Ͽ� �����ϰ� Ÿ���߷� ����
//		//	//	vec.erase(std::remove_if(vec.begin(), vec.end(), func), vec.end());			// ���� �Լ��� �Լ� ��ü�� ����� ���
//	
//		std::cout << "���Ϳ��� Ȧ���� ���� ---" << std::endl;
//		int num_erased = 0;
//		vec.erase(std::remove_if(vec.begin(), vec.end(), 
//							[&num_erased](int i) -> bool {
//							if (num_erased >= 2) return false;
//							else if (i % 2 == 1)
//							{
//								num_erased++;
//								return true;
//							}
//							return false;
//							}),
//					vec.end());
//	
//		print(vec.begin(), vec.end());
//	
//		/*
//			- ���� �Լ�(lambda function)
//				- C++ 11 ���� ó�� ���Ե� �������� �̸��� ���� �͸��� �Լ� ��ü�� ����
//				- �⺻���� ���� : [capture list](�޴� ����) -> ����Ÿ�� { �Լ� ��ü }
//				- ���� Ÿ���� �����ϰ� [capture list](����) { �Լ� ��ü } �� ���·ε� ������
//					-> �Լ� ��ü�� return ���� ���� ���� Ÿ���� �����ϰ�, return ��ΰ� ������������ ������ �� ���ٸ� ������ ������ �߻���
//				
//				- ���� �Լ��� �̿��� �Լ� ��ü�� ����� �͵� ������.
//					-> �Լ� ������ ������� �����Ͽ� ����ϱ� ��ƴٸ� std::function�� Ȱ���ص� ���� auto�� ����ص� ���� ����
//	
//				- ĸ�� ���(capture list)
//					- �⺻������ ���� �Լ��� �Լ��̹Ƿ� �ڽŸ��� �������� ����. ��, ���� �Լ� ��ü ���� �ܺ� ������ ������ �� ����
//					- capture list�� ����ϸ� �ܺ� ������ ������ ������
//					- capture list�� ������� �پ���. https://en.cppreference.com/w/cpp/language/lambda#Lambda_capture �� ������
//						- �⺻
//							- [] : �ƹ��͵� ĸ�� ����
//							- [&] : �ܺ��� ��� ������ ���۷����� ĸ��
//							= [=] : �ܺ��� ��� ������ ���纻���� ĸ��
//						- ��ȭ
//							- [&a, b] : a�� ���۷�����, b�� ���纻���� ĸ��
//							- [&, i] : �ܺ��� ��� ������ ���۷����� ĸ���ϵ�, i ������ ���纻���� ĸ��
//							- [=, &i] : �ܺ��� ��� ������ ���纻���� ĸ���ϵ�, i ������ ���۷����� ĸ��
//							- [&, this] : [&] �� ����(Ŭ���� ���ο���)
//							- [&, this, i] : [&, i] �� ����(Ŭ���� ���ο���)
//						- �ȵǴ� ��
//							- [&, &i] : ������ ���� -> ���۷��� ĸ�İ� �⺻���ε� ���۷����� ĸ���Ұ��� �ٽ� �����
//							- [i, i] : ������ ���� -> i�� �ݺ���
//							- [i] (int i) {} : ������ ���� -> ĸ�ĵ� ������ ������ �̸��� ����
//							- [=, *this] : ������ ����(C++ 17 ����) -> C++ 17 ���Ŀ��� this�� ����� ĸ�� ������
//							- [=, this] : ������ ����(C++ 20 ����) -> C++ 20 ���Ŀ��� [=] �� ����
//							- [this, *this] : ������ ���� -> this�� �ݺ���
//							- [&this] : ������ ���� -> this�� ���۷����� ĸ���� �� ����
//	
//					- capture list�� ��ü�� ��� ������ ĸ������ ����. 
//						- ��ü�� ��� ������ �ʿ��� �� ��ü�� ��°�� ĸ���ϴ� ���� ����
//						- ��ü ���ο����� this�� ĸ�� ������
//	
//		*/
//	
//	}

/*  ���� ����  */
//	#include <iostream>
//	#include <vector>
//	#include <algorithm>
//	
//	template <typename It>
//	void print(It begin, It end)
//	{
//		while(begin != end)
//		{
//			std::cout << "[" << *begin << "] ";
//			begin++;
//		}
//		std::cout << std::endl;
//	}
//	
//	int main()
//	{
//		std::vector<int> vec;
//		vec.push_back(5);
//		vec.push_back(3);
//		vec.push_back(1);
//		vec.push_back(2);
//		vec.push_back(3);
//		vec.push_back(4);
//		
//		// vec2 ���� 6���� 0���� �ʱ�ȭ�Ѵ�
//		std::vector<int> vec2(6, 0);
//	
//		std::cout << "ó�� vec, vec2 ���� ------" << std::endl;
//		print(vec.begin(), vec.end());
//		print(vec2.begin(), vec2.end());
//	
//		std::cout << "���� ��ü�� 1 �� ���Ѵ�" << std::endl;
//		std::transform(vec.begin(), vec.end(), vec.begin(), [](int i) { return i + 1; });
//		print(vec.begin(), vec.end());
//	
//		std::cout << "vec ��ü�� 1 �� ���� ���� vec2 �� ����" << std::endl;
//		std::transform(vec.begin(), vec.end(), vec2.begin(), [](int i) {return i + 1; });
//		print(vec.begin(), vec.end());
//		print(vec2.begin(), vec2.end());
//	
//		/*
//			- ���� ����
//				- std::transform �� �̿��Ͽ� ���Ҹ� ������ �� ����
//				- std::transform �� ������ ���� ���¸� ����
//					
//					std::transform (���� �ݺ���, �� �ݺ���, ����� ������ �����̳��� ���� �ݺ���, Pred);
//				
//				- ���� ù��° ������ ��� vec�� ���ۺ��� ������ ���ҿ� 1�� ���� ���� vec.begin()���� �����
//				- �ι�° ���ô� vec�� ���ۺ��� ������ ���ҿ� 1�� ���� ���� vec2.begin()�� �����
//				- ���� ������ �����̳��� ũ�Ⱑ ������ �����̳ʺ��� �ּ��� ���ų� Ŀ����
//					-> �� ���ÿ��� ���� ���
//	
//						std::transform(vec.begin(), vec.end(), vec.begin() + 1, Pred ����)
//	
//						-> �� ���� �ڵ�� �����ϸ� ������ �߻���
//						-> vec.begin() ~ vec.end() ��ŭ�� ���Ҹ� vec.begin() + 1 ���� �����Ϸ��� �ϸ� 1ĭ�� ���ڶ�Ƿ� ��Ÿ�� ������ �߻���
//						-> transform�� vec.begin() + 1���� �����Ѵٸ� ������ �߻����� ����
//		
//		*/
//	
//	}

/*  ���� Ž��  */
//	#include <algorithm>
//	#include <vector>	
//	#include <set>
//	#include <unordered_map>
//	#include <iostream>
//	
//	template <typename It>
//	void print(It begin, It end)
//	{
//		while (begin != end)
//		{
//			std::cout << "[" << *begin << "] ";
//			begin++;
//		}
//		std::cout << std::endl;
//	}
//	
//	struct User
//	{
//		std::string name;
//		int level;
//	
//		User(std::string name, int level) : name(name), level(level) {}
//		bool operator==(const User& user) const
//		{
//			if (name == user.name && level == user.level) return true;
//			return false;
//		}
//	};
//	
//	class Party
//	{
//	public:
//		bool add_user(std::string name, int level)
//		{
//			User new_user(name, level);
//			if (std::find(users.begin(), users.end(), new_user) != users.end()) 
//				return false;
//	
//			users.push_back(new_user);
//			return true;
//		}
//	
//		// ��Ƽ�� ��ΰ� 15 ���� �̻��̾���� ���� ���� ����
//		bool can_join_dungeon()
//		{
//			return std::all_of(users.begin(), users.end(), [](User& user) { return user.level >= 15; });
//		}
//	
//		// ��Ƽ�� �� �Ѹ��̶� 19 ���� �̻��̶�� Ư�� ������ ��� ����
//		bool can_use_special_item()
//		{
//			return std::any_of(users.begin(), users.end(), [](User& user) { return user.level >= 19; });
//		}
//	
//	private:
//		std::vector<User> users;
//	};
//	
//	int main()
//	{
//		/*  find, find_if  */
//		//	{
	//		std::vector<int> vec;
	//		vec.push_back(5);
	//		vec.push_back(3);
	//		vec.push_back(1);
	//		vec.push_back(2);
	//		vec.push_back(3);
	//		vec.push_back(4);
	//	
	//		// �տ������� 3 ã��
	//		//	auto result = std::find(vec.begin(), vec.end(), 3);
	//		//	std::cout << "3 �� " << std::distance(vec.begin(), result) + 1 << " ��° ����" << std::endl;	// +1�� 0�� �ε��� ���� �����ϱ� ������ ������
	//	
	//		// �ڿ������� 3 ã��
	//		//	auto result = std::find(vec.rbegin(), vec.rend(), 3);
	//		//	std::cout << "3 �� " << std::distance(result, vec.rend()) << " ��° ����" << std::endl;	// rend() �� end()�� ���������� ������ ��ĭ �ڿ������Ƿ� +1 �� �ʿ����
	//	
	//		// 3 ���� ã��
	//		auto current = vec.begin();
	//		while (true)
	//		{
	//			current = std::find(current, vec.end(), 3);
	//			if (current == vec.end()) break;
	//			std::cout << "3 �� " << std::distance(vec.begin(), current) + 1 << " ��° ����" << std::endl;
	//			current++;
	//		}
	//	
	//		// 3���� ���� �������� 2�� ���� ã��
	//		current = vec.begin();
	//		while (true)
	//		{
	//			current = std::find_if(current, vec.end(), [](int i) { return i % 3 == 2; });
	//			if (current == vec.end()) break;
	//			std::cout << "3 ���� ���� �������� 2 �� ���Ҵ� : " << *current << " �̴�" << std::endl;
	//			current++;
	//		}
	//	}
//	
//		/*  all_of, any_of  */
//		//	{
	//		Party party;
	//		party.add_user("ö��", 15);
	//		party.add_user("����", 18);
	//		party.add_user("�μ�", 12);
	//		party.add_user("����", 19);
	//	
	//		std::cout << std::boolalpha;
	//		std::cout << "���� ���� ���� ? " << party.can_join_dungeon() << std::endl;
	//		std::cout << "Ư�� ������ ��� ���� ? " << party.can_use_special_item() << std::endl;
	//	
	//		/*
	//			- output: 
	//			���� ���� ���� ? false
	//			Ư�� ������ ��� ���� ? true
	//		*/
	//	}
//	
//	
//		/*
//			- ���� Ž��
//				- find, find_if / all_of, any_of �� ����
//	
//				- find, find_if
//					- Ư�� ���̳� ���ǿ� �´� ������ ��ġ�� ����Ű�� �ݺ��ڸ� ����
//					- forward_iterator ��� �տ������� ã��, reverse_iterator ��� �ڿ������� ã��
//					- ó�� ã���� �ٷ� �����ϹǷ� ��ü�� Ž���Ϸ��� �ݺ����� �̿��Ͽ� ���������� ã�� ��ġ���� �̾ ��� Ž���ؾ���
//					- set, map, unordered_set, unordered_map �� �̹� �����̳ʰ� find�� �����Ѵٸ� �װ� ����ϴ°��� ����
//						-> <algorithm>�� find�� �����̳��� ������ ������� forward_iterator�� �̿��Ͽ� ó������ ������ �а����Ƿ� O(n)�� �ð��� �ʿ��� �ݸ�
//						-> ���� �����̳ʿ� ����� find�� �ش� �����̳ʿ� �°� O(log N) Ȥ�� O(1)�� Ž���� �� �ֱ� ����
//						-> �ٸ� find_if�� ����� ������ ����....
//		
//				- all_of, any_of
//					- all_of�� ��� ���ҵ��� ���� ������ �����ؾ� true�� ������ -> AND
//					- any_of�� ���ҵ� �� �ϳ��� ������ �����ϸ� true�� ������ -> OR
//	
//		*/
//	
//	}