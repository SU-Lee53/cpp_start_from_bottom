
/*
	04.29 STL1 - 시퀀스 컨테이너 vector, list, deque
*/

// STL

/*
	- STL
		- Standard Template Library의 줄임말로 템플릿을 사용한 C++의 표준 라이브러리를 말함
		- 보통 STL하면 크게 3가지 라이브러리를 의미함
			-> 임의 타입의 객체를 보관할 수 있는 컨테이너(container)
			-> 컨테이너에 보관된 원소에 접근할 수 있는 반복자(iterator)
			-> 반복자들을 가지고 일련의 작업을 수행하는 알고리즘(algorithm)
			+ 그밖에 입출력(iostream), 시간 관련(chrono), 정규표현식(regex) 등등이 있음
		- 템플릿을 사용하므로 우리가 다루려는 객체의 특성과 무관하게 자유롭게 라이브러리를 사용할 수 있음
		- 또한 반복자를 이용하여 컨테이너를 추상화 시킬 수 있으므로 최소한의 코드로 알고리즘 라이브러리에 필요한 코드를 작성할 수 있게됨
*/

// 컨테이너

/*
	- 컨테이너
			- STL의 컨테이너는 크게 2가지 종류로 나뉨
				-> 시퀀스 컨테이너(sequence container) : 객체들을 순차적으로 보관
					-> vector, list, deque
				-> 연관 컨테이너(associative container) : 키를 바탕으로 대응대는 값을 찾아줌
					-> set, map, unordered_set, unordered_map

			- 모든 컨테이너들은 작업에 따라 속도차가 나기 때문에 상황에 맞는 컨테이너를 적절히 고르는 것이 중요함
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
//			std::cout << "vec 의 " << i + 1 << " 번째 원소 :: " << vec[i] << std::endl;
//		}
//	
//		
//		/*
//			output:
//			vec 의 1 번째 원소 :: 10
//			vec 의 2 번째 원소 :: 20
//			vec 의 3 번째 원소 :: 30
//			vec 의 4 번째 원소 :: 40
//		*/
//	
//		/*
//			- std::vector
//				- 가변 길이 배열
//					-> 실제로 원소들이 메모리상에 순차적으로 저장됨
//					-> 따라서 임의의 위치에 있는 원소의 접근이 매우 빠름
//	
//				- 시간복잡도
//					-> 임의의 위치 원소 접근([], at) : O(1)
//					-> 맨 뒤에 원소 추가 및 제거(push_back / pop_back) : amortized O(1) -> 아래에서 설명
//					-> 임의의 위치 원소 추가 및 제거(insert, erase) : O(n)
//	
//				- vector의 작동방식, amortized O(1)의 의미
//					- armortized : 분할 상환
//					- 왜 원소 추가 및 제거의 시간복잡도가 amortized O(1) 인가
//						- vector의 작동방식을 이해해야함
//							- 보통 vector는 현재 가지고 있는 원소의 갯수보다 더 많은 공간을 미리 할당해 놓음
//								-> 예를들어 원소가 10개라면 20개의 저장공간을 미리 할당
//							- 이때 새로운 원소를 추가할 때 문제가 생김
//								1) 새롭게 원소를 추가할 저장공간이 할당되어 있는경우 -> O(1)로 그냥 추가 가능
//								2) 할당된 공간을 다 채웠을 경우
//									-> 새로운 더 큰 공간을 새로 할당하고, 기존의 원소들을 복사해야함
//									-> 이 과정에서 n개의 원소를 전부 복사해야 하므로 O(n)의 시간이 소모됨
//							- 다만 대부분의 경우 O(1)로 수행되기 때문에 amortized O(1)이라고 부르는 것임
// 
//				- vector 에는 다양한 함수들이 존재하고 오버로드되는 다양한 버전들이 존재함
//					-> 나중에 cppreference로 정리하며 다룰 예정
//		*/
//	}

// 반복자(iterator)

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
//		/* 반복자 기초 */
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
//		//		std::cout << "3번째 원소 :: " << *itr << std::endl;
//		//	
//		//		/*
//		//			- output:
//		//			10
//		//			20
//		//			30
//		//			40
//		//			3번째 원소 :: 30
//		//		*/
//		//	}
//	
//		/* 반복자를 이용한 print_vector, insert, erase */
//		//	{
//		//		std::vector<int> vec;
//		//		vec.push_back(10);
//		//		vec.push_back(20);
//		//		vec.push_back(30);
//		//		vec.push_back(40);
//		//	
//		//		std::cout << "처음 벡터 상태" << std::endl;
//		//		print_vector(vec);
//		//		std::cout << "----------------------------------" << std::endl;
//		//	
//		//		// vec[2] 앞에 15 추가
//		//		vec.insert(vec.begin() + 2, 15);
//		//		print_vector(vec);
//		//	
//		//		std::cout << "----------------------------------" << std::endl;
//		//	
//		//		// vec[3] 제거
//		//		vec.erase(vec.begin() + 3);
//		//		print_vector(vec);
//		//	
//		//		std::cout << "----------------------------------" << std::endl;
//		//	
//		//		/*
//		//			output:
//		//			처음 벡터 상태
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
//		//		// 반복자를 이용한 insert, erase의 주의점
//		//		std::vector<int>::iterator itr = vec.begin();
//		//		std::vector<int>::iterator end_itr = vec.end();
//		//	
//		//		//	for (; itr != end_itr; ++itr)
//		//		//	{
//		//		//		if (*itr == 20)
//		//		//		{
//		//		//			vec.erase(itr);	// 런타임 오류: can't increment invalidated vector iterator
//		//		//		}
//		//		//	}	
//		//		// 컨테이너에 원소를 추가하거나 제거하면 기존에 사용하던 모든 반복자들을 사용할 수 없음
//		//		// 즉, vec.erase(itr) 수행 이후 itr, end_itr 모두 무효화되고 itr != end_itr이 영원히 성림하여 무한루프에 빠짐
//		//	
//		//		//	for (; itr != vec.end(); ++itr)
//		//		//	{
//		//		//		if (*itr == 20)
//		//		//		{
//		//		//			vec.erase(itr);
//		//		//			itr = vec.begin();
//		//		//		}
//		//		//	}	// 비효율적: 20을 지우고 처음으로 돌아가 원소를 지움
//		//	
//		//		for (std::vector<int>::size_type i = 0; i != vec.size(); i++)
//		//		{
//		//			if (vec[i] == 20)
//		//			{
//		//				vec.erase(vec.begin() + i);
//		//				i--;
//		//			}
//		//		}	// 권장되지 않음: 원소 접근 방식이 통일되지 않음
//		//	
//		//		// 나중에 이 문제를 <algorithm> 라이브러리를 깔끔하게 해결하도록 함
//		//	}
//	
//		/* 상수 반복자 const_iterator */
//		//	{
//		//		std::vector<int> vec;
//		//		vec.push_back(10);
//		//		vec.push_back(20);
//		//		vec.push_back(30);
//		//		vec.push_back(40);
//		//	
//		//		std::cout << "처음 벡터 상태" << std::endl;
//		//		print_vector(vec);
//		//		
//		//		// itr은 vec[2]를 가리킨다
//		//		std::vector<int>::iterator itr = vec.begin() + 2;
//		//	
//		//		// vec[2] 의 값을 50으로 바꾼다
//		//		*itr = 50;
//		//	
//		//		std::cout << "------------" << std::endl;
//		//		print_vector(vec);
//		//	
//		//		std::vector<int>::const_iterator citr = vec.cbegin() + 2;
//		//	
//		//		// 상수 반복자가 가리키는 값은 바꿀 수 없다
//		//		//	*citr = 30;	// C3892 'citr': const인 변수에 할당할 수 없습니다.
//		//	
//		//		/*
//		//			- output:
//		//			처음 벡터 상태
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
//		/* 역반복자 reverse_iterator*/
//		//	{
//		//		std::vector<int> vec;
//		//		vec.push_back(10);
//		//		vec.push_back(20);
//		//		vec.push_back(30);
//		//		vec.push_back(40);
//		//	
//		//		std::cout << "처음 벡터 상태" << std::endl;
//		//		print_vector(vec);
//		//	
//		//		std::cout << "역으로 vec 출력하기" << std::endl;
//		//		std::vector<int>::reverse_iterator r_iter = vec.rbegin();
//		//		for (; r_iter != vec.rend(); r_iter++)
//		//		{
//		//			std::cout << *r_iter << std::endl;
//		//		}
//		//		
//		//		/*
//		//			- output:
//		//			처음 벡터 상태
//		//			10
//		//			20
//		//			30
//		//			40
//		//			역으로 vec 출력하기
//		//			40
//		//			30
//		//			20
//		//			10
//		//		*/
//		//	
//		//		// 역반복자를 사용하지 않고 역으로 출력 -> 오류
//		//		//	for (std::vector<int>::size_type i = vec.size() - 1; i >= 0; i--)
//		//		//	{
//		//		//		std::cout << vec[i] << std::endl;	// vector subscript out of range
//		//		//	}
//		//		//	std::cout << typeid(std::vector<int>::size_type).name() << std::endl;	// -> unsigned __int64
//		//		// vector의 index를 담당하는 std::vector<int>::size_type 이 부호없는 정수(unsigned __int64) 이므로 종료조건을 만족할 수 없어 무한루프에 빠짐
//		//		// i를 int로 하면 정상작동 하긴 하지만 역반복자를 이용하는것이 더 좋은 방법임
//		//	}
//	
//		/* 범위 기반 for 문 range based for loop */
//		//	{
//		//		std::vector<int> vec;
//		//		vec.push_back(10);
//		//		vec.push_back(20);
//		//		vec.push_back(30);
//		//		vec.push_back(40);
//		//	
//		//		for (int elem : vec)
//		//		{
//		//			std::cout << "원소 : " << elem << std::endl;
//		//		}
//		//	
//		//		std::cout << "print_vector" << std::endl;
//		//		print_vector(vec);
//		//		std::cout << "print_vector_range_based" << std::endl;
//		//		print_vector_range_based(vec);
//		//	
//		//		/*
//		//			- output:
//		//			원소 : 10
//		//			원소 : 20
//		//			원소 : 30
//		//			원소 : 40
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
//			- 반복자 iterator
//				- 컨테이너의 원소에 접근할 수 있는 포인터와 같은 객체
//				- 기본적으로 컨테이너 안에 iterator 멤버 타입으로 정의되어 있음 -> std::vector<>::iterator
//				- vector의 경우 반복자를 얻기 위한 함수들과 그 위치는 아래와 같음
//					-> 예를 들어 std::vector<int> vec = {1, 2, 3, 4, 5, 6}; 이라고 하면
//	
//							[1][2][3][4][5][6][ ]
//							 ^                 ^
//						vec.begin()			vec.end()
//						vec.cbegin()		vec.cend()
//					
//					-> end()는 마지막 원소가 아닌 한칸 뒤를 가리키는 반복자를 리턴함
//					-> 이를 통해 begin() == end() 이면 원소가 없음을 알 수 있음(비어있는 벡터)
//	
//				- 반복자의 이용
//					- 전체 벡터를 출력하는 코드
//	
//						for (std::vector<T>::iterator itr = vec.begin(); itr != vec.end(); ++itr) std::cout << *itr << std::endl;
//	
//						-> vec.begin() 부터 vec.end()가 가 아닐때 까지 계속해서 반복하면 처음부터 끝까지 돌게됨
//						-> ++itr을 itr++로 바꿔도 결과는 동일하지만 ++itr이 더 많이 사용됨
//							-> https://stackoverflow.com/questions/1077026/incrementing-iterators-is-it-more-efficient-than-it
//							-> 불필요한 복사를 줄여 조금 더 빠르다고 함
//	
//					- 반복자를 이용한 insert(), erase()
//	
//						// vec[2] 앞에 15 추가
//						vec.insert(vec.begin() + 2, 15);
//						print_vector(vec);
//	
//						// vec[3] 제거
//						vec.erase(vec.begin() + 3);
//						print_vector(vec);
//	
//					- insert(), erase() 시의 주의점
//	
//						std::vector<int>::iterator itr = vec.begin();
//						std::vector<int>::iterator end_itr = vec.end();
//	
//						for (; itr != end_itr; ++itr)
//						{
//							if (*itr == 20)
//							{
//								vec.erase(itr);	// 런타임 오류: can't increment invalidated vector iterator
//							}
//						}
//	
//						-> erase가 되면 해당 벡터에서 사용하던 반복자들은 전부 무효화됨
//						-> 따라서 itr != end_itr 이 영원히 성립되어 무한루프에 빠짐
//						-> insert도 할당 공간이 꽉차서 재할당을 할 경우 무효화됨
//						-> 자세한건 https://en.cppreference.com/w/cpp/container/vector 의 Iterator invalidation 을 참고
//						-> 위 예시에 이를 해결하는 방법이 몇가지 더 있지만 STL의 <algorithm>에 깔끔한 해결법이 있으므로 참고만
//	
//				- 상수 반복자 const_iterator
//					- 일반 반복자처럼 컨테이너에 정의되어있음 -> std::vector<>::const_iterator
//					- 상수 포인터처럼 가리키는 원소의 값을 변경할 수 없음
//					- cbegin(), cend() 를 이용하여 반복자를 얻을 수 있음
//	
//				- 역반복자 reverse_iterator
//					- 다른 반복자들 처럼 컨테이너에 정의되어있음 -> std::vector<>::reverse_iterator
//					- 역반복자를 얻기 위한 함수와 리턴하는 위치는 아래와 같음
//	
//							[ ][1][2][3][4][5][6]
//							 ^                 ^
//						vec.rend()			vec.rbegin()
//						vec.crend()			vec.crbegin()
//	
//					- 이것도 상수 역반복자가 존재하며 crbegin(), crend()로 얻을 수 있음
//					- 컨테이너의 원소를 역으로 참조하는 방법중 가장 좋은 방법임
//	
//				- 범위 기반 for 문 range based for loop
//					- 기존의 다양하고 복잡한 반복자를 이용한 for문을 C++11에서 매우 간결하게 할 수 있도록 한 방식
//					- 아래와 같이 사용함(vec의 원소가 int 인 경우)
//	
//						for (int elem : vec)
//						{
//							std::cout << "원소 : " << elem << std::endl;
//						}
//						
//						-> elem 에 vec의 원소가 매 루프마다 복사되서 들어감
//						-> elem = vec[i] 한 것과 같음
//	
//					- 레퍼런스를 얻을 수도 있음.
//					- auto도 이용 가능함. 예시는 아래와 같음
//						for (const auto& elem : vec)
//						{
//							std::cout << elem << std::endl;
//						}
//	
//					- 범위 기반 for 문을 이용하면 코드가 직관적이고 간결해지는 장점이 있음
//				
//		*/
//	
//	
//	}

// std::list

//	#include <iostream>
//	#include <list>
//	#include <forward_list>	// C++11에 추가된 단방향 연결리스트
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
//		std::cout << "처음 리스트의 상태" << std::endl;
//		print_list(lst);
//	
//		for (std::list<int>::iterator itr = lst.begin(); itr != lst.end(); ++itr)
//		{
//			// 만일 현재 원소가 20 이라면
//			// 그 앞에 50을 집어넣는다.
//			if (*itr == 20)
//			{
//				lst.insert(itr, 50);
//			}
//		}
//	
//		std::cout << "값이 20인 원소 앞에 50을 추가" << std::endl;
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
//		std::cout << "값이 30인 원소를 제거" << std::endl;
//		print_list(lst);
//		
//		/*
//			- output:
//			처음 리스트의 상태
//			[ 10 20 30 40 ]
//			값이 20인 원소 앞에 50을 추가
//			[ 10 50 20 30 40 ]
//			값이 30인 원소를 제거
//			[ 10 50 20 40 ]
//		*/
//	
//		/*
//			- std::list
//				- 양방향 연결리스트
//				- list의 반복자는 vector의 반복자와 약간 다름
//					- itr++, ++itr, itr--, --itr 연산은 가능함
//					- itr + 5 처럼 임의의 위치의 원소를 가리키는 연산은 불가능함
//					- insert(), erase() 를 수행하여도 반복자가 무효화되지 않음 -> 각 원소들의 주소값은 바뀌지 않기 때문
//						-> 연결리스트인 list의 구조상 임의 접근이 불가능하고 한칸씩 순차적으로만 접근할 수 있음
//						-> 이때문에 반복자의 타입이 다르기도 함. vector는 RandomAccessIterator, list는 BidirectionalIterator
//							-> 반복자의 타입은 후에 다룸
//				- 시간복잡도
//					-> 임의의 위치 원소 접근([], at) : 불가능
//					-> 맨 앞,맨 뒤에 원소 추가 및 제거(push_front, push_back / pop_front, pop_back) : O(1)
//					-> 임의의 위치 원소 추가 및 제거(insert, erase) : O(1)
//		*/
//	}

// std::deque : 내일