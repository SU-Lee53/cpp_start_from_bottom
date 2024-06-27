/*
	06.25 - <untility> 의 std::optional, std::variant, std::tuple
*/

// 이번 내용들은 대부분 최소 C++ 17 이상부터 사용 가능한 기능들임

/*  std::optional  */
//	#include <iostream>
//	#include <map>
//	#include <string>
//	#include <optional>	// std::optional 은 <utility> 가 아닌 <optional> 에 따로있음...
//	
//	//	std::string GetValueFromMap(const std::map<int, std::string>& m, int key)
//	//	{
//	//		// std::optional 이 도입되지 않았을 때 맵에서 값을 가져오는 함수
//	//		// 찾으려는 키가 있으면 알맞은 값을 리턴할 수 있지만 없으면 빈 string 을 리턴하는 수 밖에 없음
//	//		// 이러면 키가 존재하지 않는 경우와 키는 존재하지만 값이 그냥 빈 string 인 경우를 구분할 수 없음
//	//	
//	//		auto itr = m.find(key);
//	//		if (itr != m.end())
//	//		{
//	//			return itr->second;
//	//		}
//	//	
//	//		return std::string();
//	//	}
//	
//	//	std::pair<std::string, bool> GetValueFromMap(const std::map<int, std::string>& m, int key)
//	//	{
//	//		// std::optional 이 도입되지 않았을 때 맵에서 값을 가져오는 함수 2
//	//		// 이번에는 std::pair 을 이용하여 키가 존재하면 값과 true 를, 키가 없으면 빈 string 과 false 를 리턴
//	//		// 이 방법에는 약간의 문제가 있음. 아래 본 설명에서 이어감
//	//	
//	//		auto itr = m.find(key);
//	//		if (itr != m.end())
//	//		{
//	//			return std::make_pair(itr->second, true);
//	//		}
//	//		
//	//		return std::make_pair(std::string(), false);
//	//	}
//	
//	std::optional<std::string> GetValueFromMap(const std::map<int, std::string>& m, int key)
//	{
//		auto itr = m.find(key);
//		if (itr != m.end())
//		{
//			return itr->second;
//		}
//	
//		// nullopt : <optional> 에 정의된 객체로 비어있는 optional 을 말함
//		return std::nullopt;
//	}
//	
//	class A
//	{
//	public:
//		A() { std::cout << "디폴트 생성" << std::endl; }
//		A(const A& a) { std::cout << "복사 생성" << std::endl; }
//	};
//	
//	int main()
//	{
//		std::map<int, std::string> data = { {1, "hi"}, {2, "hello"}, {3, "hiroo"} };
//	
//		std::cout << std::boolalpha;
//		std::cout << "맵에서 2 에 대응되는 값은? " << GetValueFromMap(data, 2).value() << std::endl;	// 맵에서 2 에 대응되는 값은? hello
//		std::cout << "맵에 4 가 존재함? " << GetValueFromMap(data, 4).has_value() << std::endl;	// 맵에 4 가 존재함? false
//	
//		// std::optional 과 std::pair 의 차이점
//	
//		std::cout << "std::optonal<A> 생성" << std::endl;
//		std::optional<A> maybe_a;
//	
//		std::cout << "std::pair<A, nullptr_t> 생성" << std::endl;
//		std::pair<A, nullptr_t> pair_a;
//	
//		/*
//			- std::optional 과 std::pair 의 차이점 output : 
//				std::optonal<A> 생성
//				std::pair<A, nullptr_t> 생성
//				디폴트 생성
//	
//				-> std::optional 은 비어있을때 디폴트 객체를 생성하지 않음
//		*/
//	
//	
//		/*
//			- std::optional
//				- 사전적 정의로의 optional : 선택적
//				- std::optional : 선택적으로 값을 가지는 객체
//	
//				- 코드 설명
//					- std::optional 을 사용하지 않고 map 에서 키가 존재하는 값을 가져오는 GetValueFromMap() 함수를 구현해봄
//	
//						- std::string GetValueFromMap(const std::map<int, std::string>& m, int key)
//							- 가장 기초적인 방법으로 구현한 GetValueFromMap()
//							- 이 경우 키가 존재하면 값을 리턴하고 키가 존재하지 않으면 비어있는 string 객체를 리턴함
//							- 이때 키가 없는 경우와 키는 있는데 값이 그냥 비어있는 string 인 경우를 구분하기 어려움
//	
//						- std::pair<std::string, bool> GetValueFromMap(const std::map<int, std::string>& m, int key)
//							- std::pair 를 이용하여 구현한 GetValueFromMap() (의외로 std::pair 와 std::tuple 은 C++ 11 부터 존재했음)
//							- 키가 존재하면 값과 true, 키가 존재하지 않으면 비어있는 string 과 false 를 리턴함
//							- std::pair 를 이용한 경우에는 키가 존재하지 않을 때 디폴트 객체를 리턴해야 하는데 이는 2가지 문제가 있음
//								1) 객체의 디폴트 생성자가 없을 수도 있음
//								2) 객체의 디폴트 생성이 오래걸릴 수 있음 -> 어차피 없으면 쓰지도 않을건데 오래걸리면 더더욱 손해
//	
//					- 마지막 GetValueFromMap() 에서는 std::optional 을 도입하여 위 2가지 버전의 문제들을 해결함
//	
//						- std::optional<std::string>
//							- 위 처럼 선언한 std::optional 객체는 std::string 을 보관하거나 안하거나 둘중 하나의 상태가 됨
//							- 이 덕분에 키가 존재할 때 그냥 값을 리턴하면 std::string 을 온전히 리턴함
//							- std::optional 의 가장 큰 장점으로 객체 보관 과정중에 동적할당이 일어나지 않음
//								-> std::optional 자체에 객체가 포함됨
//	
//						- return std::nullopt;
//							- std::nullopt : 미리 정의되어있는 빈 std::optional 객체
//							- 아무것도 없는 빈 optional 을 리턴하고 싶을때 사용하면 됨
//	
//						- GetValueFromMap(data, 2).value()
//							- optional 객체가 가지고 있는 객체에 접근
//							- 만약 비어있는 optional 객체에 접근한다면 std::bad_optional_access 예외가 발생함
//							- 역참조 연산자 * 을 사용해도 객체에 접근 가능함
//	
//						- GetValueFromMap(data, 4).has_value()
//							- 해당 optional 이 객체를 가지고 있는지 확인하는 함수
//							- bool 캐스팅 오버로딩이 되어있으므로 if (GetValueFromMap(data, 4).has_value()) 처럼 사용도 가능함
//	
//				- std::optional 은 std::pair 과 달리 비어있을때 디폴트 객체를 가질 필요가 없음
//					- 위 테스트에서도 std::optional 생성시 디폴트 생성자를 호출하지 않음
//		*/
//	}

/*  레퍼런스를 갖는 std::optional  */
#include <iostream>
#include <optional>

class A
{
public:
	A() { std::cout << "디폴트 생성" << std::endl; }
	A(const A& a) { std::cout << "복사 생성" << std::endl; }

	int data;
};

int main()
{
	A a;
	a.data = 5;
	
	// std::optional<A&> maybe_a;	// C2338 : static_assert failed: 'T in optional<T> must meet the Cpp17Destructible requirements (N4950 [optional.optional.general]/3).'
	std::optional<std::reference_wrapper<A>> maybe_a = std::ref(a);

	maybe_a->get().data = 3;
	std::cout << "a.data : " << a.data << std::endl;	// a.data : 3

}