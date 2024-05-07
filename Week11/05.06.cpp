
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

/*  원소 제거  */
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
	/*
		- 처음 2개의 홀수 원소만 삭제하기 위해 멤버 변수로 num_delete를 사용
			-> C++ 표준에서는 remove_if 에 전달되는 함수 객체의 경우 호출에 의해 내부 상태가 달라져선 안됨
			-> 즉 num_delete는 지워지는 갯수를 카운팅 하므로 내부 상태가 달라지게 되므로 이러한 방식(인스턴스 변수 사용)은 안됨

		- 대부분의 라이브러리의 remove_if 함수의 find_if는 서술자(Pred)의 레퍼런스가 아닌 복사 버전을 받음
		- 루프를 돌며 서술자에 조건에 만족하는 경우를 찾기 전에 한번 find_if() 함수를 호출하므로 루프 안에서 호출되는 서술자 함수는 이전의 카운트 결과를 모름
		- 함수 본체를 직접 보면 이해가 쉬움

			_EXPORT_STD template <class _FwdIt, class _Pr>
			_NODISCARD_REMOVE_ALG _CONSTEXPR20 _FwdIt remove_if(_FwdIt _First, const _FwdIt _Last, _Pr _Pred) {
				// remove each satisfying _Pred
				_Adl_verify_range(_First, _Last);
				auto _UFirst      = _Get_unwrapped(_First);
				const auto _ULast = _Get_unwrapped(_Last);
				_UFirst           = _STD find_if(_UFirst, _ULast, _Pass_fn(_Pred));					<- 이부분에서 서술자 함수(Pred)를 복사하여 한번 실행
				auto _UNext       = _UFirst;
				if (_UFirst != _ULast) {
					while (++_UFirst != _ULast) {
						if (!_Pred(*_UFirst)) {														<- 여기서 Pred를 호출할 때 위에서 num_delete가 1이 된 정보가 소멸됨
							*_UNext = _STD move(*_UFirst);
							++_UNext;
						}
					}
				}
			
				_Seek_wrapped(_First, _UNext);
				return _First;
			}

		- 이 문제를 해결하려면 num_delete를 객체 내부 변수가 아닌 외부로 빼야함
	*/
	//	int num_delete;
	//	is_odd() : num_delete(0) {}

	int& num_delete;
	is_odd(int& num_delete) : num_delete(num_delete) {}

	bool operator()(const int& i) 
	{ 
		if (num_delete >= 2) return false;
		if (1 % 2 == 1)
		{
			num_delete++;
			return true;
		}
		return false;
	}
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

	//	std::cout << "벡터에서 값이 3인 원소 제거 ---" << std::endl;
	//	vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());
	//	print(vec.begin(), vec.end());

	//	std::cout << "벡터에서 홀수인 원소 제거 ---" << std::endl;
	//	vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd()), vec.end());
	//	print(vec.begin(), vec.end());

	//	std::cout << "벡터에서 홀수인 앞의 2개 원소 제거 ---" << std::endl;
	//	int num_delete = 0;
	//	vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd(num_delete)), vec.end());
	//	print(vec.begin(), vec.end());

	// 위처럼 안해도 C++ 20 부터는 erase_if로 가능함(홀수 원소 지우기 예제, 람다 함수 이용)
	auto count = std::erase_if(vec, [](int i) -> bool { return i % 2 == 1; });
	print(vec.begin(), vec.end());	// [2] [4]
	std::cout << "지워진 홀수의 갯수 :: " << count << std::endl; //	지워진 홀수의 갯수 :: 4

	/*
		- 원소 제거
			- remove / remove_if 가 존재. 다만 실제로 제거하지는 않고 컨테이너의 멤버함수인 erase와 함께 사용해야함
				-> 두가지 함수를 이용하여 원소를 지우는 것을 Erase-remove idiom 이라고 부름 https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
				-> C++ 20 부터는 erase/erase_if 만 이용하여 지울수도 있음. 아래에 설명
	
			- remove 가 실제로 하는일
				- remove 함수는 인자로 받은 반복자 범위 안에 마지막 인자로 받은 변수와 동일한 인자를 발견하면 그 뒤의 원소들을 왼쪽으로 쉬프트함
				- 위 코드의 경우 아래처럼 작동됨

					5  3  1  2  3  4	: 처음 vec 상태
					5  1  1  2  3  4	: vec[1]의 3을 찾았으므로 그 다음 원소인 1을 쉬프트
					5  1  2  2  3  4	: 마찬가지로 2도 쉬프트
					5  1  2  4  3  4	: 다음 3을 발견하였으므로 무시하고 4를 쉬프트
					            ^ 
						해당 위치의 반복자를 리턴 -> 이 자리 앞은 3이 제외된 원소들로만 채워짐

					-> 지우고자 하는 원소를 뒤로 이동시키는 것이 아님!
					-> 그냥 무시하고 다른 원소들을 쉬프트 시키는것이며 리턴된 반복자 뒷부분은 어차피 지워질 쓰레기값이 됨

				- 이후 컨테이너의 erase 함수가 리턴 받은 위치부터 end()까지 지워버림
					-> C++20 이전까지의 erase 함수는 인자로 받은 위치 하나만 지우거나 first, last로 받아 그 사이를 모두 지우거나 밖에 하지 못함
			
			- remove_if 또한 remove와 마찬가지의 일을 하며 다른점은 서술자 함수 객체(Pred)를 받을 수 있음
				-> remove_if에 전달되는 함수객체는 복사 가능한 인자를 1개만 받을 수 있고 const가 아니어야 하며 bool 타입을 리턴해야 함 (이를 UnaryPredicate 단항 서술자 라고 함)
				
			- remove_if 의 함수 객체로 bool을 리턴하는 단항 서술자가 오므로 원소에 대한 정보 말고는 추가적인 정보를 전달하기 어려움
				- 이를 위해 함수 객체 내부에 변수를 만들어 전달하는 방법은 사용해서는 안됨
					-> 일단 remove_if를 어떻게 구현할지에 대한 정해진 표준이 없음
					-> 많은 라이브러리들이 함수 객체를 여러번 복사할 수 있도록 되어있기 때문에 내부 변수 정보가 소멸되기도 하기 때문임

				- 외부에 변수로 두는 방법은 가능함
					-> 이 경우 매번 클래스나 함수를 만들어 주어야 한다는 불편함이 있고, 프로젝트가 커질수록 가독성이 떨어짐

				- 가장 좋은 방법은 C++ 11에 추가된 람다 함수를 이용하는 것임
					-> 람다 함수는 아래 단락에서 설명

			- C++ 20부터는 erase / erase_if 를 이용하여 바로 원소를 제거할 수 있음

				std::erase_if(vec, [](int i) -> bool { return i % 2 == 1; });

				-> erase_if는 원하는 컨테이너를 레퍼런스로 받아 제거하고 몇개를 지웠는지 갯수를 세서 해당 컨테이너의 size_type으로 리턴함
	*/
}

/*  람다 함수  */