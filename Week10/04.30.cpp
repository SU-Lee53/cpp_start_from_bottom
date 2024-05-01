
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

/*  std::map  */
//	#include <iostream>
//	#include <map>
//	#include <string>
//	
//	template<typename K, typename V>
//	void print_map(std::map<K, V>& m)
//	{
//		//	for (auto itr = m.begin(); itr != m.end(); ++itr)
//		//		std::cout << itr->first << " " << itr->second << std::endl;
//	
//		// 범위 기반 for 문을 이용할 수 도 있음
//		for (const auto& kv : m)
//			std::cout << kv.first << " " << kv.second << std::endl;
//	}
//	
//	template<typename K, typename V>
//	void search_and_print(std::map<K, V>& m, K key)
//	{
//		auto itr = m.find(key);
//		if (itr != m.end())
//			std::cout << key << " ---> " << itr->second << std::endl;
//		else
//			std::cout << key << "은(는) 목록에 없습니다" << std::endl;
//	}
//	
//	int main()
//	{
//		std::map<std::string, double> pitcher_list;
//	
//		pitcher_list.insert(std::pair<std::string, double>("박세웅", 2.23));
//		pitcher_list.insert(std::pair<std::string, double>("해커", 2.93));
//		pitcher_list.insert(std::pair<std::string, double>("피어밴드", 2.95));
//	
//		pitcher_list.insert(std::make_pair("차우찬", 3.04));
//		pitcher_list.insert(std::make_pair("장원준", 3.05));
//		pitcher_list.insert(std::make_pair("핵터", 3.09));
//	
//		pitcher_list["니퍼트"] = 3.56;
//		pitcher_list["박종훈"] = 3.76;
//		pitcher_list["켈리"] = 3.90;
//	
//		print_map(pitcher_list);
//	
//		std::cout << "박세웅 방어율은? :: " << pitcher_list["박세웅"] << std::endl;
//	
//		// 잘못된 find - operator[] 사용시 주의
//		//	std::cout << "류현진 방어율은? :: " << pitcher_list["류현진"] << std::endl;	// 류현진 방어율은? :: 0
//		// 추가한적이 없는 류현진의 방어율이 출력됨 -> operator[]는 맵에 없는 키를 참조하면 자동으로 값의 디폴트 생성자를 호출하여 원소를 추가함
//	
//		// 올바른 find - 위 search_and_print() 함수를 참고
//		search_and_print(pitcher_list, std::string("류현진"));	// 류현진은(는) 목록에 없습니다
//		search_and_print(pitcher_list, std::string("박세웅"));	// 박세웅 ---> 2.23
//	
//		// set과 마찬가지로 중복을 무시함. 이미 같은 키가 존재한다면 나중에 오는 insert는 무시됨
//		pitcher_list.insert(std::pair<std::string, double>("박세웅", 2.93));
//		std::cout << "박세웅 방어율은? :: " << pitcher_list["박세웅"] << std::endl;	// 박세웅 방어율은? :: 2.23
//	
//		/*
//			- output
//			니퍼트 3.56
//			박세웅 2.23
//			박종훈 3.76
//			장원준 3.05
//			차우찬 3.04
//			켈리 3.9
//			피어밴드 2.95
//			해커 2.93
//			핵터 3.09
//			박세웅 방어율은? :: 2.23
//			류현진은(는) 목록에 없습니다
//			박세웅 ---> 2.23
//			박세웅 방어율은? :: 2.23
//		*/
//	
//		/*
//			- std::map
//				- set과 거의 유사하지만 키와 대응되는 값까지 같이 저장함
//				- std::map<K,V> 같은 형태로 선언하고 첫번째 인자에 키의 타입, 두번째 인자에 값의 타입이 옴
//				- std::pair 객체로 원소들이 저장됨
//					-> 단순히 2개의 객체를 갖는 객체임
//					-> first, second 로 각각의 객체를 호출할 수 있고, map의 경우 first에 키, second에 값이 옴
//					-> std::make_pair 함수를 이용해서 만들 수 도 있음
//	
//				- map에 원소를 추가하는 방법은 3가지임
//					- pitcher_list.insert(std::pair<std::string, double>("박세웅", 2.23));
//						-> 직접 pair를 만들어서 추가
//					- pitcher_list.insert(std::make_pair("박세웅", 2.23));
//						-> std::make_pair() 함수를 이용해 pair를 만들고 추가
//					- pitcher_list["박세웅"] = 2.23;
//						-> operator[]를 이용하여 추가
//						-> 이 경우 유일하게 키가 이미 존재할경우 값이 대체됨(위에 2가지는 무시됨)
//	
//				- map에서 operator[]를 사용할 때 주의사항
//					- operator[]를 이용해서 값을 찾거나 참조할 때 맵에 없는 키를 참조하면 값의 디폴트 인자를 이용해서 새로 추가해버림
//					- 따라서 map에서 원하는 원소를 찾고자 한다면 find() 함수를 사용하는 것이 바람직함
//						-> find() 함수의 경우 키가 맵에 존재하면 해당 pair를 가리키는 반복자를 리턴함
//						-> 반대로 키가 맵에 없는경우 end()의 위치를 리턴함
//	
//				- map 역시 범위 기반 for 문이 사용 가능함
//		*/
//	}

/*  std::multiset, std::multimap  */
//	#include <iostream>
//	#include <set>
//	#include <map>
//	#include <string>
//	
//	template <typename T>
//	void print_set(const std::multiset<T>& s)
//	{
//		for (const auto& elem : s)
//			std::cout << elem << std::endl;
//	}
//	
//	template <typename K, typename V>
//	void print_map(const std::multimap<K, V>& m)
//	{
//		for (const auto& kv : m)
//			std::cout << kv.first << " " << kv.second << std::endl;
//	}
//	
//	int main()
//	{
//		std::multiset<std::string> s;
//	
//		s.insert("a");
//		s.insert("b");
//		s.insert("a");
//		s.insert("c");
//		s.insert("d");
//		s.insert("c");
//	
//		print_set(s);
//	
//		/*
//			- multiset 부분 output:
//			a
//			a
//			b
//			c
//			c
//			d
//		*/
//	
//		std::multimap<int, std::string> m;
//		m.insert(std::make_pair(1, "hello"));
//		m.insert(std::make_pair(1, "hi"));
//		m.insert(std::make_pair(1, "ahihi"));
//		m.insert(std::make_pair(2, "bye"));
//		m.insert(std::make_pair(2, "baba"));
//		//	m[1]; 오류: multimap은 operator[]를 사용할 수 없음
//	
//		print_map(m);
//	
//		std::cout << "-------------------------" << std::endl;
//		std::cout << m.find(1)->second << std::endl;
//	
//	
//		std::cout << "-------------------------" << std::endl;
//		
//		auto range = m.equal_range(1);
//		for (auto itr = range.first; itr != range.second; ++itr)
//		{
//			std::cout << itr->first << " : " << itr->second << " " << std::endl;
//		}
//	
//		/*
//			- multimap 부분 output:
//			a
//			a
//			b
//			c
//			c
//			d
//			1 hello
//			1 hi
//			1 ahihi
//			2 bye
//			2 baba
//			-------------------------
//			hello
//			-------------------------
//			1 : hello
//			1 : hi
//			1 : ahihi
//		*/
//	
//		/*
//			- std::multiset, std::multimap
//				- 기존의 set, map 과 달리 중복을 허용하는 연관 컨테이너
//				- multimap의 경우 기존에 사용하던 operator[]를 사용할 수 없음
//					-> 중복을 허용하므로 중복된 키를 호출하면 어떤 값을 리턴할지 알 수 없기 때문
//	
//				- 또한 multimap은 중복을 허용하므로 기존의 find()의 사용에 문제가 있음
//					-> find() 함수가 존재하긴 함. 다만 multimap의 경우 중복된 키가 있을때 어떤 값을 리턴할지에 대한 정해진 표준이 없음 
//					-> 그러므로 위에서는 hello를 출력하였지만 다른 STL 구현체를 쓰면 뭐가 나올지 모름
//	
//				- 이를 위해 multiset, multimap 모두 equal_range() 라는 함수를 제공함
//					-> equal_range()의 인자로 찾으려는 키를 전달하면 대응되는 원소들의 반복자들 중에서 시작과 끝 바로 다음을 가리키는 pair 객체를 리턴함
//					-> pair로 리턴해주므로 first, second 에 각각 begin(), end()가 담겨있음. end()는 다른 것들과 마찬가지로 끝점 바로 뒤를 가리킴
//						-> 그러므로 first == second 라면 대응되는 원소가 없는것임
//		*/
//	}

/*  std::unordered_set, std::unordered_map  */
#include <iostream>
#include <string>
#include <unordered_set>

template <typename K>
void print_unordered_set(const std::unordered_set<K>& m)
{
	for (const auto& elem : m)
		std::cout << elem << std::endl;
}

int main()
{
	std::unordered_set<std::string> s;

	s.insert("hi");
	s.insert("my");
	s.insert("name");
	s.insert("is");
	s.insert("psi");
	s.insert("welcome");
	s.insert("to");
	s.insert("c++");
	
	print_unordered_set(s);

	/*
		- output
		hi
		welcome
		my
		name
		is
		psi
		to
		c++

		++ vscode에서 g++을 이용하여 같은 코드를 실행한 결과
		to
		psi
		is
		welcome
		name
		my
		c++
		hi

		-> STL은 같은 MSVC STL을 사용
		-> 정렬되지 않는 컨테이너이므로 컴파일러만 바뀌어도 출력 순서가 달라짐
	*/

	/*
		- std::unordered_set, std::unordered_map
			- 기존의 set, map 과 달리 insert/erase/find가 모두 O(1)로 수행됨
				-> Red-Black tree 를 사용하지 않고 해시 함수를 사용하기 때문
			- 해시 함수
	
	*/
}