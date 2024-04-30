
/*
	04.30 ~ 04.31 STL1 - 연관 컨테이너 (set, map, multiset, multimap, unordered_set, unordered_map)
*/

/*  연관 컨테이너  */
/*
	- 연관 컨테이너
		- 키(key) - 값(value) 구조를 저장하는 컨테이너
			-> 특정한 키를 넣으면 이에 대응되는 값을 돌려줌
			-> 템플릿 라이브러리 이므로 키, 값 모두 임의의 타입의 객체가 올 수도 있음

		- 이러한 자료구조의 경우 보통 2가지 종류의 작업이 가능함
			1) 특정 키가 연관 컨테이너에 존재하는지 유무 : OOO 가 데이터에 존재하는가?
			2) 특정 키에 대응되는 값을 확인 : OOO가 존재한다면 대응되는 값이 무엇인가?

		- STL의 연관 컨테이너는 위 2가지 작업에 대해 다음의 컨테이너들을 제공함
			1) set, multiset -> 키만 저장하여 존재 유무만 알 수 있음
			2) map, multimap -> 키와 값을 모두 저장하여 특정 키에 대응되는 값을 알 수 있음

*/

/*  std::set  */
//	#include <iostream>
//	#include <set>
//	
//	template <typename T>
//	void print_set(std::set<T>& s)
//	{
//		std::cout << "[ ";
//		for (typename std::set<T>::iterator itr = s.begin(); itr != s.end(); ++itr)
//		{
//			std::cout << *itr << " ";
//		}
//		std::cout << "]" << std::endl;
//	}
//	
//	int main()
//	{
//		std::set<int> s;
//		s.insert(10);
//		s.insert(50);
//		s.insert(20);
//		s.insert(40);
//		s.insert(30);
//		s.insert(20);
//		s.insert(10);
//	
//		std::cout << "순서대로 정렬되서 나온다" << std::endl;
//		print_set(s);
//	
//		std::cout << "20 이 s 의 원소인가요? :: ";
//		auto itr = s.find(20);
//		if (itr != s.end())
//			std::cout << "Yes" << std::endl;
//		else
//			std::cout << "No" << std::endl;
//	
//		std::cout << "25 가 s 의 원소인가요? :: ";
//		itr = s.find(25);
//		if (itr != s.end())
//			std::cout << "Yes" << std::endl;
//		else
//			std::cout << "No" << std::endl;
//	
//		/*
//			- output:
//			순서대로 정렬되서 나온다
//			[ 10 20 30 40 50 ]
//			20 이 s 의 원소인가요? :: Yes
//			25 가 s 의 원소인가요? :: No
//		*/
//	
//		/*
//			- std::set
//				- 키의 존재 유무만 알고싶을때 사용하는 컨테이너
//					-> 키만 저장하고 값은 저장하지 않음
//	
//				- 원소를 추가하려면 insert() 함수를 사용함
//					-> 이때 시퀀스 컨테이너와 다르게 "어디에" 저장할지에 대한 인자가 없음
//					-> 연관 컨테이너는 시퀀스 컨테이너와 달리 원소가 어디에 있는지 중요하지 않고, 원소가 있냐/없냐 가 중요하기 때문
//					-> insert()의 시간복잡도는 O(logN) 
//	
//				- 반복자는 BidirectionalIterator 타입임. 즉 임의의 위치의 원소에는 접근할 수 없고, 순차적으로만 접근 가능함
//					-> 그러나 반복자를 이용하여 출력해보면 항상 정렬된 상태로 출력됨. 
//					-> 원소를 추가하거나 제거하여도 항상 정렬된 상태를 유지함
//	
//				- 특정 원소의 존재유무는 find() 함수를 이용하여 알 수 있음
//					-> 해당하는 원소가 존재하면 이를 가리키는 반복자를 리턴함
//					-> 해당하는 원소가 존재하지 않는다면 end()를 리턴함
//					-> find()의 시간복잡도는 O(logN)
//	
//				- 위의 특징들이 가능한 이유는 내부의 원소들이 트리의 형태로 저장되어있기 때문임
//					-> 정확히는 Red-black tree 형태로 저장됨. 이는 자가 균형 이진 탐색 트리의 일종임
//					-> Red-black tree는 자가 균형 트리이므로 균형잡히지 않은 트리(사향 이진 트리)의 형태가 만들어지지 않게 유지됨
//	
//				- 또한 set 안에는 중복된 원소들이 없음
//					-> 위 예제코드 에서도 10과 20을 2번 넣었지만 1개만 저장됨
//					-> 이미 같은 원소가 있으면 그냥 insert() 하지 않음
//					-> 원소를 중복하여 넣고싶다면 multiset을 이용해야 함
//	
//				- 시퀀스 컨테이너들 처럼 범위 기반 for 문을 지원함
//					-> 반복자를 이용한 for문 처럼 항상 정렬된 상태로 출력됨
//		*/
//	}

/*  직접 만든 클래스 객체를 set에 넣기  */
//	#include <iostream>
//	#include <string>
//	#include <set>
//	
//	template <typename T>
//	void print_set(std::set<T>& s)
//	{
//		for (const auto& elem : s)
//		{
//			std::cout << elem << " " << std::endl;
//		}
//	}
//	
//	template <typename T, typename C>
//	void print_set(std::set<T,C>& s)
//	{
//		for (const auto& elem : s)
//		{
//			std::cout << elem << " " << std::endl;
//		}
//	}
//	
//	class Todo
//	{
//	public:
//		Todo(int priority, std::string job_desc) : priority(priority), job_desc(job_desc) {}
//	
//		bool operator<(const Todo& t) const
//		{
//			if (priority == t.priority)
//				return job_desc < t.job_desc;
//			return priority > t.priority;
//		}
//	
//		friend struct TodoCmp;
//		friend std::ostream& operator<<(std::ostream&, const Todo&);
//	private:
//		int priority;
//		std::string job_desc;
//	};
//	
//	struct TodoCmp
//	{
//		bool operator()(const Todo& t1, const Todo& t2) const
//		{
//			if (t1.priority == t2.priority)
//				return t1.job_desc < t2.job_desc;
//			return t1.priority > t2.priority;
//		}
//	};
//	
//	std::ostream& operator<<(std::ostream& o, const Todo& td)
//	{
//		o << "[중요도: " << td.priority << "] " << td.job_desc;
//		return o;
//	}
//	
//	int main()
//	{
//		//	std::set<Todo> todos;
//		std::set<Todo, TodoCmp> todos;	// 객체간 비교하는 함수 객체가 있다면 다음과 같이 해도 정상작동함
//	
//	
//		todos.insert(Todo(1, "농구 하기"));
//		todos.insert(Todo(2, "수학 숙제 하기"));
//		todos.insert(Todo(1, "프로그래밍 프로젝트"));
//		todos.insert(Todo(3, "친구 만나기"));
//		todos.insert(Todo(2, "영화 보기"));
//	
//		print_set(todos);
//	
//		std::cout << "-------------" << std::endl;
//		std::cout << "숙제를 끝냈다면!" << std::endl;
//		todos.erase(todos.find(Todo(2, "수학 숙제 하기")));
//		print_set(todos);
//	
//		/*
//			- output:
//			[중요도: 3] 친구 만나기
//			[중요도: 2] 수학 숙제 하기
//			[중요도: 2] 영화 보기
//			[중요도: 1] 농구 하기
//			[중요도: 1] 프로그래밍 프로젝트
//			-------------
//			숙제를 끝냈다면!
//			[중요도: 3] 친구 만나기
//			[중요도: 2] 영화 보기
//			[중요도: 1] 농구 하기
//			[중요도: 1] 프로그래밍 프로젝트
//		*/
//	
//		/*
//			- 직접 만든 클래스 객체를 set에 넣기
//				- 위 코드에서 operator<가 오버로딩 되어있지 않거나 TodoCmp 함수 객체가 없다면 컴파일 오류가 발생함
//					-> set이 내부적으로 정렬된 상태를 유지하기 위해서는 원소간의 비교를 수행할 방법이 필요하기 때문임
//	
//				- 이를 위해서 2가지 방법이 있음
//					1) operator< 를 오버로딩
//						- 오버로딩 함수는 반드시 const 객체를 레퍼런스로 받아야 함
//							-> 내부적으로 정렬시 상수 반복자를 사용하기 때문임
//						- 원소가 서로 같음을 판별하기 위해서 == 연산자를 별도로 사용하지 않음
//							-> A.operator(B) 와 B.operator(A) 둘다 false 인 경우 A == B를 의미함
//						- Todo 클래스와 같이 대소비교의 기준이 우선순위가 있을때 높은 우선순위의 기준이 같을 경우도 처리해주어야 함
//							-> Todo의 경우 중요도(priority)가 같을때를 따로 처리하지 않는다면 중요도가 같은 객체들은 같은 객체라고 판단함
//							-> 그러므로 중복을 허용하지 않는 set에서는 추가되지 않음
//						- operator< 는 다음과 같은 조건을 만족해야 함
//							- A < A 는 false
//							- A < B != B < A
//							- A < B 이고 B < C 이면 A < C
//							- A == B 이면 A < B 와 B < A 둘 다 거짓
//							- A == B 이고 B == C 이면 A == C
//								-> 이러한 연산자를 strict weak ordering을 만족한다고 함
//								-> 이중 하나라도 만족하지 않으면 제대로 동작하지 않음
//	
//					2) 비교 함수 객체를 만들어 사용
//						- 비교 함수 객체를 만들어 두번째 템플릿 인자로 넘겨주면 이를 바탕으로 모든 비교를 수행하는 set이 생성됨
//						- 만약 두번째 인자로 아무것도 전달하지 않으면 기본적으로 std::less<key>를 사용함. 이는 그냥 key 클래스의 operator<로 비교를 수행함을 의미함
//		*/
//	}