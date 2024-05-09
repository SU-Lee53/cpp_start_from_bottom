
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
//			- 처음 2개의 홀수 원소만 삭제하기 위해 멤버 변수로 num_delete를 사용
//				-> C++ 표준에서는 remove_if 에 전달되는 함수 객체의 경우 호출에 의해 내부 상태가 달라져선 안됨
//				-> 즉 num_delete는 지워지는 갯수를 카운팅 하므로 내부 상태가 달라지게 되므로 이러한 방식(인스턴스 변수 사용)은 안됨
//	
//			- 대부분의 라이브러리의 remove_if 함수의 find_if는 서술자(Pred)의 레퍼런스가 아닌 복사 버전을 받음
//			- 루프를 돌며 서술자에 조건에 만족하는 경우를 찾기 전에 한번 find_if() 함수를 호출하므로 루프 안에서 호출되는 서술자 함수는 이전의 카운트 결과를 모름
//			- 함수 본체를 직접 보면 이해가 쉬움
//	
//				_EXPORT_STD template <class _FwdIt, class _Pr>
//				_NODISCARD_REMOVE_ALG _CONSTEXPR20 _FwdIt remove_if(_FwdIt _First, const _FwdIt _Last, _Pr _Pred) {
//					// remove each satisfying _Pred
//					_Adl_verify_range(_First, _Last);
//					auto _UFirst      = _Get_unwrapped(_First);
//					const auto _ULast = _Get_unwrapped(_Last);
//					_UFirst           = _STD find_if(_UFirst, _ULast, _Pass_fn(_Pred));					<- 이부분에서 서술자 함수(Pred)를 복사하여 한번 실행
//					auto _UNext       = _UFirst;
//					if (_UFirst != _ULast) {
//						while (++_UFirst != _ULast) {
//							if (!_Pred(*_UFirst)) {														<- 여기서 Pred를 호출할 때 위에서 num_delete가 1이 된 정보가 소멸됨
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
//			- 이 문제를 해결하려면 num_delete를 객체 내부 변수가 아닌 외부로 빼야함
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
//		std::cout << "처음 vec 상태 ------" << std::endl;
//		print(vec.begin(), vec.end());
//	
//		//	std::cout << "벡터에서 값이 3인 원소 제거 ---" << std::endl;
//		//	vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());
//		//	print(vec.begin(), vec.end());
//	
//		//	std::cout << "벡터에서 홀수인 원소 제거 ---" << std::endl;
//		//	vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd()), vec.end());
//		//	print(vec.begin(), vec.end());
//	
//		//	std::cout << "벡터에서 홀수인 앞의 2개 원소 제거 ---" << std::endl;
//		//	int num_delete = 0;
//		//	vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd(num_delete)), vec.end());
//		//	print(vec.begin(), vec.end());
//	
//		// 위처럼 안해도 C++ 20 부터는 erase_if로 가능함(홀수 원소 지우기 예제, 람다 함수 이용)
//		auto count = std::erase_if(vec, [](int i) -> bool { return i % 2 == 1; });
//		print(vec.begin(), vec.end());	// [2] [4]
//		std::cout << "지워진 홀수의 갯수 :: " << count << std::endl; //	지워진 홀수의 갯수 :: 4
//	
//		/*
//			- 원소 제거
//				- remove / remove_if 가 존재. 다만 실제로 제거하지는 않고 컨테이너의 멤버함수인 erase와 함께 사용해야함
//					-> 두가지 함수를 이용하여 원소를 지우는 것을 Erase-remove idiom 이라고 부름 https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
//					-> C++ 20 부터는 erase/erase_if 만 이용하여 지울수도 있음. 아래에 설명
//		
//				- remove 가 실제로 하는일
//					- remove 함수는 인자로 받은 반복자 범위 안에 마지막 인자로 받은 변수와 동일한 인자를 발견하면 그 뒤의 원소들을 왼쪽으로 쉬프트함
//					- 위 코드의 경우 아래처럼 작동됨
//	
//						5  3  1  2  3  4	: 처음 vec 상태
//						5  1  1  2  3  4	: vec[1]의 3을 찾았으므로 그 다음 원소인 1을 쉬프트
//						5  1  2  2  3  4	: 마찬가지로 2도 쉬프트
//						5  1  2  4  3  4	: 다음 3을 발견하였으므로 무시하고 4를 쉬프트
//						            ^ 
//							해당 위치의 반복자를 리턴 -> 이 자리 앞은 3이 제외된 원소들로만 채워짐
//	
//						-> 지우고자 하는 원소를 뒤로 이동시키는 것이 아님!
//						-> 그냥 무시하고 다른 원소들을 쉬프트 시키는것이며 리턴된 반복자 뒷부분은 어차피 지워질 쓰레기값이 됨
//	
//					- 이후 컨테이너의 erase 함수가 리턴 받은 위치부터 end()까지 지워버림
//						-> C++20 이전까지의 erase 함수는 인자로 받은 위치 하나만 지우거나 first, last로 받아 그 사이를 모두 지우거나 밖에 하지 못함
//				
//				- remove_if 또한 remove와 마찬가지의 일을 하며 다른점은 서술자 함수 객체(Pred)를 받을 수 있음
//					-> remove_if에 전달되는 함수객체는 복사 가능한 인자를 1개만 받을 수 있고 const가 아니어야 하며 bool 타입을 리턴해야 함 (이를 UnaryPredicate 단항 서술자 라고 함)
//					
//				- remove_if 의 함수 객체로 bool을 리턴하는 단항 서술자가 오므로 원소에 대한 정보 말고는 추가적인 정보를 전달하기 어려움
//					- 이를 위해 함수 객체 내부에 변수를 만들어 전달하는 방법은 사용해서는 안됨
//						-> 일단 remove_if를 어떻게 구현할지에 대한 정해진 표준이 없음
//						-> 많은 라이브러리들이 함수 객체를 여러번 복사할 수 있도록 되어있기 때문에 내부 변수 정보가 소멸되기도 하기 때문임
//	
//					- 외부에 변수로 두는 방법은 가능함
//						-> 이 경우 매번 클래스나 함수를 만들어 주어야 한다는 불편함이 있고, 프로젝트가 커질수록 가독성이 떨어짐
//	
//					- 가장 좋은 방법은 C++ 11에 추가된 람다 함수를 이용하는 것임
//						-> 람다 함수는 아래 단락에서 설명
//	
//				- C++ 20부터는 erase / erase_if 를 이용하여 바로 원소를 제거할 수 있음
//	
//					std::erase_if(vec, [](int i) -> bool { return i % 2 == 1; });
//	
//					-> erase_if는 원하는 컨테이너를 레퍼런스로 받아 제거하고 몇개를 지웠는지 갯수를 세서 해당 컨테이너의 size_type으로 리턴함
//		*/
//	}

/*  람다 함수  */
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
//	// 클래스 내부에서 capture list 의 사용
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
//			// SomeClass::num_erased 는 일반 변수가 아니라 객체에 종속된 멤버 변수이므로 캡쳐할 수 없음
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
//				vec.end());	// 멤버 변수 캡쳐 필요시 객체를 통째로 넘겨받아야함
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
//		std::cout << "처음 vec 상태 ------" << std::endl;
//		print(vec.begin(), vec.end());
//	
//		//	std::cout << "벡터에서 홀수인 원소 제거 ---" << std::endl;
//		//	
//		//	vec.erase(std::remove_if(vec.begin(), vec.end(), [](int i) -> bool { return i % 2 == 1; }), vec.end());	// 기본형: [capture list](받는 인자) -> 리턴타입 { 함수 본체 }
//		//	
//		//	//	vec.erase(std::remove_if(vec.begin(), vec.end(), [](int i) { return i % 2 == 1; }), vec.end());	// 리턴 타입의 생략:  [capture list](받는 인자) { 함수 본체 }
//		//	
//		//	//	bool(*func)(int) = [](int i) -> bool { return i % 2; };						// 혹은
//		//	//	std::function<int(bool)> func = [](int i) -> bool { return i % 2 == 1; };	// 혹은(<functional> include 필요)
//		//	//	auto func = [](int i) -> bool { return i % 2 == 1; };						// auto를 사용하여 간단하게 타입추론 가능
//		//	//	vec.erase(std::remove_if(vec.begin(), vec.end(), func), vec.end());			// 람다 함수로 함수 객체를 만들어 사용
//	
//		std::cout << "벡터에서 홀수인 원소 ---" << std::endl;
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
//			- 람다 함수(lambda function)
//				- C++ 11 에서 처음 도입된 개념으로 이름이 없는 익명의 함수 객체를 말함
//				- 기본적인 정의 : [capture list](받는 인자) -> 리턴타입 { 함수 본체 }
//				- 리턴 타입을 생략하고 [capture list](인자) { 함수 본체 } 의 형태로도 가능함
//					-> 함수 본체의 return 문을 보고 리턴 타입을 추측하고, return 경로가 여러군데여서 추측할 수 없다면 컴파일 오류가 발생함
//				
//				- 람다 함수를 이용해 함수 객체를 만드는 것도 가능함.
//					-> 함수 포인터 선언법이 복잡하여 기억하기 어렵다면 std::function을 활용해도 좋고 auto를 사용해도 문제 없음
//	
//				- 캡쳐 목록(capture list)
//					- 기본적으로 람다 함수도 함수이므로 자신만의 스코프를 가짐. 즉, 람다 함수 본체 밖의 외부 변수는 참조할 수 없음
//					- capture list를 사용하면 외부 변수에 접근이 가능함
//					- capture list의 사용방법은 다양함. https://en.cppreference.com/w/cpp/language/lambda#Lambda_capture 를 참고함
//						- 기본
//							- [] : 아무것도 캡쳐 안함
//							- [&] : 외부의 모든 변수를 레퍼런스로 캡쳐
//							= [=] : 외부의 모든 변수를 복사본으로 캡쳐
//						- 심화
//							- [&a, b] : a는 레퍼런스로, b는 복사본으로 캡쳐
//							- [&, i] : 외부의 모든 변수를 레퍼런스로 캡쳐하되, i 변수만 복사본으로 캡쳐
//							- [=, &i] : 외부의 모든 변수를 복사본으로 캡쳐하되, i 변수만 레퍼런스로 캡쳐
//							- [&, this] : [&] 와 동일(클래스 내부에서)
//							- [&, this, i] : [&, i] 와 동일(클래스 내부에서)
//						- 안되는 것
//							- [&, &i] : 컴파일 오류 -> 레퍼런스 캡쳐가 기본값인데 레퍼런스로 캡쳐할것을 다시 명시함
//							- [i, i] : 컴파일 오류 -> i가 반복됨
//							- [i] (int i) {} : 컴파일 오류 -> 캡쳐된 변수와 인자의 이름이 같음
//							- [=, *this] : 컴파일 오류(C++ 17 이전) -> C++ 17 이후에는 this를 복사로 캡쳐 가능함
//							- [=, this] : 컴파일 오류(C++ 20 이전) -> C++ 20 이후에는 [=] 와 동일
//							- [this, *this] : 컴파일 오류 -> this가 반복됨
//							- [&this] : 컴파일 오류 -> this는 레퍼런스로 캡쳐할 수 없음
//	
//					- capture list는 객체의 멤버 변수를 캡쳐하지 못함. 
//						- 객체의 멤버 변수가 필요할 시 객체를 통째로 캡쳐하는 것이 좋음
//						- 객체 내부에서는 this로 캡쳐 가능함
//	
//		*/
//	
//	}

/*  원소 수정  */
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
//		// vec2 에는 6개의 0으로 초기화한다
//		std::vector<int> vec2(6, 0);
//	
//		std::cout << "처음 vec, vec2 상태 ------" << std::endl;
//		print(vec.begin(), vec.end());
//		print(vec2.begin(), vec2.end());
//	
//		std::cout << "벡터 전체에 1 을 더한다" << std::endl;
//		std::transform(vec.begin(), vec.end(), vec.begin(), [](int i) { return i + 1; });
//		print(vec.begin(), vec.end());
//	
//		std::cout << "vec 전체에 1 을 더한 것을 vec2 에 저장" << std::endl;
//		std::transform(vec.begin(), vec.end(), vec2.begin(), [](int i) {return i + 1; });
//		print(vec.begin(), vec.end());
//		print(vec2.begin(), vec2.end());
//	
//		/*
//			- 원소 수정
//				- std::transform 을 이용하여 원소를 수정할 수 있음
//				- std::transform 은 다음과 같은 형태를 가짐
//					
//					std::transform (시작 반복자, 끝 반복자, 결과를 저장할 컨테이너의 시작 반복자, Pred);
//				
//				- 위의 첫번째 예시의 경우 vec의 시작부터 끝까지 원소에 1을 더한 값을 vec.begin()부터 덮어씌움
//				- 두번째 예시는 vec의 시작부터 끝까지 원소에 1을 더한 값을 vec2.begin()에 덮어씌움
//				- 값을 저장할 컨테이너의 크기가 원래의 컨테이너보다 최소한 같거나 커야함
//					-> 위 예시에서 예를 들어
//	
//						std::transform(vec.begin(), vec.end(), vec.begin() + 1, Pred 생략)
//	
//						-> 위 같은 코드로 변경하면 오류가 발생함
//						-> vec.begin() ~ vec.end() 만큼의 원소를 vec.begin() + 1 부터 저장하려고 하면 1칸이 모자라므로 런타임 오류가 발생함
//						-> transform도 vec.begin() + 1부터 수행한다면 오류는 발생하지 않음
//		
//		*/
//	
//	}

/*  원소 탐색  */
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
//		// 파티원 모두가 15 레벨 이상이어야지 던전 입장 가능
//		bool can_join_dungeon()
//		{
//			return std::all_of(users.begin(), users.end(), [](User& user) { return user.level >= 15; });
//		}
//	
//		// 파티원 중 한명이라도 19 레벨 이상이라면 특별 아이템 사용 가능
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
	//		// 앞에서부터 3 찾기
	//		//	auto result = std::find(vec.begin(), vec.end(), 3);
	//		//	std::cout << "3 은 " << std::distance(vec.begin(), result) + 1 << " 번째 원소" << std::endl;	// +1은 0번 인덱스 부터 시작하기 때문에 더해줌
	//	
	//		// 뒤에서부터 3 찾기
	//		//	auto result = std::find(vec.rbegin(), vec.rend(), 3);
	//		//	std::cout << "3 은 " << std::distance(result, vec.rend()) << " 번째 원소" << std::endl;	// rend() 는 end()와 마찬가지로 끝보다 한칸 뒤에있으므로 +1 이 필요없음
	//	
	//		// 3 전부 찾기
	//		auto current = vec.begin();
	//		while (true)
	//		{
	//			current = std::find(current, vec.end(), 3);
	//			if (current == vec.end()) break;
	//			std::cout << "3 은 " << std::distance(vec.begin(), current) + 1 << " 번째 원소" << std::endl;
	//			current++;
	//		}
	//	
	//		// 3으로 나눈 나머지가 2인 원소 찾기
	//		current = vec.begin();
	//		while (true)
	//		{
	//			current = std::find_if(current, vec.end(), [](int i) { return i % 3 == 2; });
	//			if (current == vec.end()) break;
	//			std::cout << "3 으로 나눈 나머지가 2 인 원소는 : " << *current << " 이다" << std::endl;
	//			current++;
	//		}
	//	}
//	
//		/*  all_of, any_of  */
//		//	{
	//		Party party;
	//		party.add_user("철수", 15);
	//		party.add_user("영희", 18);
	//		party.add_user("민수", 12);
	//		party.add_user("수빈", 19);
	//	
	//		std::cout << std::boolalpha;
	//		std::cout << "던전 입장 가능 ? " << party.can_join_dungeon() << std::endl;
	//		std::cout << "특별 아이템 사용 가능 ? " << party.can_use_special_item() << std::endl;
	//	
	//		/*
	//			- output: 
	//			던전 입장 가능 ? false
	//			특별 아이템 사용 가능 ? true
	//		*/
	//	}
//	
//	
//		/*
//			- 원소 탐색
//				- find, find_if / all_of, any_of 가 있음
//	
//				- find, find_if
//					- 특정 값이나 조건에 맞는 원소의 위치를 가리키는 반복자를 리턴
//					- forward_iterator 라면 앞에서부터 찾고, reverse_iterator 라면 뒤에서부터 찾음
//					- 처음 찾으면 바로 리턴하므로 전체를 탐색하려면 반복문을 이용하여 마지막으로 찾은 위치부터 이어서 계속 탐색해야함
//					- set, map, unordered_set, unordered_map 등 이미 컨테이너가 find를 지원한다면 그걸 사용하는것이 좋음
//						-> <algorithm>의 find는 컨테이너의 종류와 상관없이 forward_iterator를 이용하여 처음부터 끝까지 밀고나가므로 O(n)의 시간이 필요한 반면
//						-> 연관 컨테이너에 내장된 find는 해당 컨테이너에 맞게 O(log N) 혹은 O(1)로 탐색할 수 있기 때문
//						-> 다만 find_if는 내장된 버전이 없음....
//		
//				- all_of, any_of
//					- all_of는 모든 원소들이 전부 조건을 충족해야 true를 리턴함 -> AND
//					- any_of는 원소들 중 하나라도 조건을 충족하면 true를 리턴함 -> OR
//	
//		*/
//	
//	}