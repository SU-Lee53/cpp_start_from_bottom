/*
	06.25 - std::optional, std::variant, std::tuple
*/

/*  std::optional (C++ 17)  */
//	#include <iostream>
//	#include <map>
//	#include <string>
//	#include <optional>
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
//	#include <iostream>
//	#include <optional>
//	
//	class A
//	{
//	public:
//		A() { std::cout << "디폴트 생성" << std::endl; }
//		A(const A& a) { std::cout << "복사 생성" << std::endl; }
//	
//		int data;
//	};
//	
//	int main()
//	{
//		A a;
//		a.data = 5;
//		
//		// std::optional<A&> maybe_a;	// C2338 : static_assert failed: 'T in optional<T> must meet the Cpp17Destructible requirements (N4950 [optional.optional.general]/3).'
//		std::optional<std::reference_wrapper<A>> maybe_a = std::ref(a);
//	
//		// 포인터는?
//		std::optional<A*> maybe_pa = &a;
//	
//	
//		maybe_a->get().data = 3;
//		std::cout << "a.data : " << a.data << std::endl;	// a.data : 3
//		std::cout << "maybe_pa : " << maybe_pa.value()->data << std::endl;	// maybe_pa : 3 -> 포인터는 문제없다
//		/*
//			- 레퍼런스를 갖는 std::optional
//				- 원칙적으로 std::optional 에는 레퍼런스 타입이 들어가지 못함
//					- cppreference 는 다음과 같이 설명함 https://en.cppreference.com/w/cpp/utility/optional
//						-> The type must meet the requirements of Destructible (in particular, array and reference types are not allowed).
//						-> 템플릿 인자의 타입은 반드시 Destructible 조건을 만족해야함 (특히, 배열과 레퍼런스 타입은 허용되지 않음)
//	
//					- 왜??
//						- 사실 정확한 이유는 본문을 작성하는 시기까진 정확히 모르겠음
//						- 다만, 다음의 이유라고 추측해보려고 함
//							- 파괴 가능함을 C++ 17 의 표준 명세는 다음과 같이 정의함 (위 static_assert 에서 걸리는 Cpp17Destructable 이 바로 이 내용임)
//	
//								주어진 u 에 대하여 (u 는 타입 T의 표현식) 아래의 표현식은 반드시 유효하고 특정한 효과를 가짐
//								u.~T() : u의 모든 자원들은 반환되고, 예외를 던지지 않음
//							
//							- 자원이 반환되고 나면 그 자리에는 새로운 객체가 할당 될 수 있어야 함
//							- 그러나 레퍼런스 타입은 한번 객체를 참조하면 다른 객체를 참조하는것이 불가능 (not re-assignable)
//								-> 이때문에 C++ 는 레퍼런스 타입을 Destructible 하지 않다고 보는 것으로 추정
//								-> 반면 포인터는 이러한 제한이 없기 때문에 Destructible 하다고 보는것 같음
//									-> 위 코드에서도 A* 를 보관하는 std::optional 은 문제없이 작동함
//	
//				- 그래도 std::optional 에 레퍼런스를 보관하고 싶다면
//					- std::reference_wrapper 를 이용하면 가능함
//						- std::reference_wrapper 는 레퍼런스가 아니라 레퍼런스처럼 작동하는 wrapper 임
//					- get() 을 이용하여 참조하고 있는 객체를 가져올 수 있음
//					- reference_wrapper 를 이용하려면 std::ref() 를 이용하여 객체를 만들어야 함
//	
//		*/
//	
//	}

/*  std::variant (C++ 17)  */
//	#include <iostream>
//	#include <string>
//	#include <memory>
//	#include <variant>
//	
//	class A
//	{
//	public:
//		A(int i) {}
//	
//		void a() { std::cout << "I am A" << std::endl; }
//	};
//	
//	class B
//	{
//	public:
//		B(int i) {}
//	
//		void b() { std::cout << "I am B" << std::endl; }
//	};
//	
//	std::variant<A, B> GetDataFromDB(bool is_a)
//	{
//		if (is_a)
//			return A(1);
//		
//		return B(1);
//	}
//	
//	int main()
//	{
//		/*  std::variant 기초  */
//		//	{
	//		std::variant<int, std::string, double> v = 1;
	//		std::cout << std::get<int>(v) << std::endl;
	//	
	//		v = "hello";
	//		std::cout << std::get<std::string>(v) << std::endl;
	//	
	//		v = 3.14;
	//		std::cout << std::get<double>(v) << std::endl;
	//	}
//	
//	
//		auto v = GetDataFromDB(true);
//	
//		std::cout << v.index() << std::endl;	// 0
//		std::get<A>(v).a();	// I am A
//		// std::get<B>(v).b();	// bad_variant_access 예외 발생
//	
//		std::get<0>(v).a();	// I am A
//	
//		/*
//			- std::variant
//				- 안전한 공용체 : 컴파일 타임에 정해진 여러가지 타입들 중에 한 가지 타입의 객체를 보관하는 클래스
//				- std::variant 가 하는 일은 공용체(union) 으로도 가능하지만 공용체는 잘못쓰면 매우 위험할 수 있음
//				- std::variant 는 std::optional 처럼 객체 대입시에 동적할당이 발생하지 않음 -> 객체를 보관하는데 오버헤드가 매우 적음
//				- std::variant 도 std::optional 과 마찬가지로 레퍼런스 타입은 안됨 -> 레퍼런스는 std::reference_wrapper 를 이용
//				- std::variant 의 크기는 기본적으로 보관 가능한 타입들 중 가장 큰 타입의 크기를 따라감
//				- std::variant 의 템플릿 인자로 같은 타입을 여러번 전달하면 컴파일 오류가 발생함 -> 보관하는 객체들을 타입으로 구분하기 때문
//					- 즉, std::variant<std::string, std::string> 등의 코드는 컴파일 오류
//	
//				- 코드 설명
//					- std::variant<int, std::string, double> v = 1;
//						- 이런식으로 선언된 std::variant 객체 v 는 int, string, double 타입의 값을 가지고 있을 수 있음
//						- 기본적으로 variant 객체는 비어있을 수 없음
//							- 만약 위 코드를 1로 초기화하지 않으면 0 이 됨 -> 디폴트 생성자를 호출함을 의미
//	
//					- std::variant<std::monostate, A, B> GetDataFromDB(bool is_a)
//						- GetDataFromDB() 함수의 리턴 타입을 A 혹은 B 둘중 하나를 가질 수 있는 variant 로 선언
//						- std::monostate
//							- A 와 B 모두 디폴트 생성자가 없기 때문에 둘만으로는 variant 객체를 초기화할 수 없음(variant 는 비어있을 수 없으므로)
//							- 이를 해결하기 위해 std::monostate 를 이용하면 비어있는 variant 객체를 나타낼 수 있음
//							- 만일 A 와 B 중 하나라도 디폴트 생성자가 있으면 std::monostate 를 사용하지 않아도 됨
//							- 사실 위 코드는 리턴타입 정의 부분이라 std::monostate 없이도 잘 되지만 직접 사용하려면 필요함
//	
//					- v.index()
//						- v가 몇번째 타입인지 알려줌
//						- 안타깝게도 무슨 타입인지 직접 알려주는 함수는 없는것으로 보임
//	
//					- std::get<A>(v).a();
//						- 실제로 원하는 타입을 뽑아내주는 함수
//						- std::get(0)(v) 로 해도 동일하게 A 객체를 뽑아줌
//						- 만약 이 코드를 std::get<B>(v).b() 로 바꾸면 bad_variant_access 라는 예외를 던짐
//	
//				- std::variant 가 좋아보여도 파이썬처럼 타입에 연연하지 않고 자유롭게 프로그래밍 하는것은 어려울것으로 보임
//					- 파이썬은 기본적으로 동적타입 언어이고, C++ 은 모든 타입은 컴파일타임에 결정 가능해야하기 때문
//					- 따라서, 가능한 선 안에서 타입 오락가락은 가능하지만(템플릿 인자) 완전히 자유롭지는 못하다는것을 알아두어야 함
//		*/
//	
//	}

/*  std::tuple (C++ 11)  */
//	#include <iostream>
//	#include <string>
//	#include <tuple>
//	
//	int main()
//	{
//		std::tuple<int, double, std::string> tp;
//		tp = std::make_tuple(1, 3.14, "hi");
//	
//		std::cout << std::get<0>(tp) << ", " << std::get<1>(tp) << ", " << std::get<2>(tp) << std::endl;
//	
//		std::get<float>(tp);
//	
//		/*
//			- std::tuple
//				- 고정된 크기의 서로 다른 타입의 값들을 모은 집합
//					-> 파이썬의 그것과 거의 동일함
//	
//				- 코드 설명
//					- std::tuple<int, double, std::string> tp;
//						- 위처럼 선언한 tuple 객체에는 int, double, string 타입의 객체를 보관함
//						- std::variant 와 달리 같은 타입이 들어가 있어도 문제 없음
//						- 템플릿 인자로 들어간 순서대로 값이 보관됨
//	
//					- tp = std::make_tuple(1, 3.14, "hi");
//						- std::make_tuple() 을 이용해 tuple 객체를 생성
//					
//					- std::cout << std::get<0>(tp) << ", " << std::get<1>(tp) << ", " << std::get<2>(tp) << std::endl;
//						- 각각의 원소에 접근하기 위해 std::get 함수를 이용
//							-> 템플릿 인자에 몇번째 원소에 접근할지를 지정해주면 됨
//						- std::variant 의 get<T> 처럼 타입을 적접 명시해도 가능함
//							-> 다만 이때 템플릿 인자로 전달한 타입이 없으면 예외가 발생함
//							-> 또한, 여러개 존재하는 타입을 전달해도 예외가 발생함. 정확히 어떤 값에 접근할지 모르기 때문
//		
//		*/
//	}

/*  구조적 바인딩 Structured binding (C++ 17)  */
#include <iostream>
#include <string>
#include <tuple>
#include <map>
std::tuple<int, std::string, bool> GetStudent(int id)
{
	if (id == 0)
		return std::make_tuple(30, "철수", true);
	else
		return std::make_tuple(28, "영희", false);
}

int main()
{
	auto student = GetStudent(1);

	// 구조적 바인딩 도입 이전
	// int age = std::get<0>(student);
	// std::string name = std::get<1>(student);
	// bool is_male = std::get<2>(student);

	// 구조적 바인딩 도입
	auto [age, name, is_male] = student;

	std::cout << "이름 : " << name << std::endl;	// 이름: 영희
	std::cout << "나이 : " << age << std::endl;	// 나이: 28
	std::cout << "남자? : " << std::boolalpha << is_male << std::endl;	// 남자? : false


	std::map<int, std::string> m = { {3, "hi"}, {5, "hello"} };
	for (auto& [key, val] : m)
	{
		std::cout << "key : " << key << " value : " << val << std::endl;
	}

}