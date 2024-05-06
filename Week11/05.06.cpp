
/*
	05.06 STL3 알고리즘
*/

/*  STL의 <algorithm>  */
/*
	- <algirithm>
		- 컨테이너의 반복자들을 이용해 여러 작업들을 수행하는 라이브러리
		- 기본적으로 아래의 2가지의 형태로 작성됨

			template <typename Iter>
			void do_something(Iter begin, Iter end);
			
			template <typename Iter, typename Pred>
			void do_something(Iter begin, Iter end, Pred pred);
			
			-> 위는 알고리즘의 시작점과 끝점만을 받아 작업을 수행
			-> 아래는 시작점, 끝점과 함께 특정한 조건을 추가 인자로 받으며 이러한 특정한 조건을 "서술자(Predicate)"라고 부름
				-> 서술자에는 보통 bool을 리턴하는 함수 객체가 들어가거나 람다 함수가 들어감
*/

/*  정렬  */
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
//			std::cout << "정렬 전 ----" << std::endl;
//			print(vec.begin(), vec.end());
//	
//			std::sort(vec.begin(), vec.end());
//			std::cout << "오름차순 정렬 후 ----" << std::endl;
//			print(vec.begin(), vec.end());
//	
//			//	std::sort(vec.begin(), vec.end(), int_compare());	// 직접 함수 객체를 만들어 정렬
//			std::sort(vec.begin(), vec.end(), std::greater<int>());	// <functional> 헤더의 템플릿 클래스를 이용. 원하는 기본 타입을 넣으면 자동으로 함수 객체를 만듬
//			std::cout << "내림차순 정렬 후 ----" << std::endl;
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
//			std::cout << "정렬 전 ----" << std::endl;
//			print(vec.begin(), vec.end());
//	
//			std::partial_sort(vec.begin(), vec.begin() + 3, vec.end());
//			std::cout << "정렬 후 ----" << std::endl;
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
//			std::cout << "정렬 전 ----" << std::endl;
//			print(vec.begin(), vec.end());
//	
//			std::sort(vec.begin(), vec.end());
//			std::cout << "정렬 후 ----" << std::endl;
//			print(vec.begin(), vec.end());
//	
//			std::stable_sort(vec2.begin(), vec2.end());
//			std::cout << "stable_sort 의 경우" << std::endl;
//			print(vec2.begin(), vec2.end());
//		}
//	
//		/*
//			- output:
//			std::sort
//			정렬 전 ----
//			5 3 1 6 4 7 2
//			오름차순 정렬 후 ----
//			1 2 3 4 5 6 7
//			내림차순 정렬 후 ----
//			7 6 5 4 3 2 1
//			
//			std::partial_sort
//			정렬 전 ----
//			5 3 1 6 4 7 2
//			정렬 후 ----
//			1 2 3 6 5 7 4
//	
//			stable_sort는 정렬 결과 생략
//		*/
//	
//		/*
//			- <algorithm> 의 sort
//				- 기본적으로 sort, partial_sort, stable_sort 이렇게 3가지가 존재함
//				- 모든 sort는 반복자 타입이 RandomAccessIterator여야 하므로 vector, deque에서만 사용 가능함
//					-> list는 BidirectionalIterator 이므로 불가능
//					-> array는 가능함
//	
//				- std::sort
//					- 기본타입들에 대해서 별도의 서술자가 없으면 오름차순 정렬함
//					- 오름차순이 아닌 다른 정렬을 위해서는 2가지 방법이 존재함
//						1) 직접 비교를 위한 함수 객체를 만들어 서술자로 전달
//						2) functional 헤더의 템플릿 함수를 이용하여 서술자로 전달
//							-> 이 방법은 기본타입이 아니면 operator>가 별도로 오버로딩 되어있어야 함
//				
//				- std::partial_sort
//					- 원하는 일부분만 정렬함
//					- (start, mid, end) 로 3개의 인자를 받고 [start, end) 까지의 원소중 [start, mid) 까지의 원소들만 정렬함
//						-> 왜 [start, end/mid)? : 끝부분 반복자는 항상 실제 끝에서 한칸 뒤에 있음
//					- 그 외의 설명은 std::sort와 동일함
//	
//				- std::stable_sort
//					- 정렬시 삽입되어 있는 원소의 원래 순서를 보존함
//					
//				- 각각의 시간복잡도와 사용되는 알고리즘
//					- 당연히 STL 구현체마다 사용하는 알고리즘이 다름. C++ 표준에 어떤 알고리즘을 사용할지 정확한 명세가 없기 때문
//					- 일반적으로 많이 사용되는 알고리즘은 있음
//	
//					- sort, partial sort
//						- 이전에는 퀵 정렬을 이용하였으나 최악의 경우 O(N^2)의 시간복잡도를 가지는 문제점이 보고됨 https://cplusplus.github.io/LWG/issue713
//						- 현재는 Introsort를 이용하여 항상 O(N log N)을 보장
//							-> Introsort는 Timsort와 유사하지만 재귀 깊이가 깊어지면 퀵정렬에서 힙정렬로 바뀜
//							-> 재귀 깊이나 분할의 크기에 따라 퀵 -> 힙 -> 삽입 순으로 정렬을 진행
//	
//					- stable_sort
//						- 이건 정말로 구현체마다 많이 다른것으로 보임 
//						- 기본적으로 병합정렬을 많이 사용하는것으로 보임
//						- 기본적으로 O(N log N) 이지만 메모리가 부족한 경우 O(N log^2 N) 까지 내려간다고 함
//		*/
//	
//	}

/*  원소 제거, 람다 함수  */
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

	std::cout << "처음 vec 상태 ------" << std::endl;
	print(vec.begin(), vec.end());

	std::cout << "벡터에서 값이 3인 원소 제거 ---" << std::endl;
	vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());
	print(vec.begin(), vec.end());

	std::cout << "벡터에서 홀수인 원소 제거 ---" << std::endl;
	//	vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd()), vec.end());
	vec.erase(std::remove_if(vec.begin(), vec.end(), [](int i) -> bool { return i % 2 == 1; }), vec.end()); // 람다 함수 이용
	print(vec.begin(), vec.end());
}

