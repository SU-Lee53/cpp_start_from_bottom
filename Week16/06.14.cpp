/*
	06.14 - <type_traits>, SFINAE, enable_if
*/

/*  템플릿 메타 함수, type_traits - std::is_void  */
//	#include <iostream>
//	#include <type_traits>
//	
//	// 간단한 is_void
//	template <typename T>
//	struct is_void
//	{
//		static constexpr bool value = false;
//	};
//	
//	template <>
//	struct is_void<void>
//	{
//		static constexpr bool value = true;
//	};
//	
//	template <typename T>
//	void tell_type()
//	{
//		if (std::is_void<T>::value)
//		{
//			std::cout << "T 는 void" << '\n';
//		}
//		else
//		{
//			std::cout << "T 는 void 가 아님" << '\n';
//		}
//	}
//	
//	int main()
//	{
//		tell_type<int>();	// T 는 void 가 아님
//		tell_type<void>();	// T 는 void
//		
//		/*
//			- 템플릿 메타 함수
//				- 함수는 아니지만 함수처럼 동작하는 템플릿 클래스들
//				- "메타" 함수 : 타입에 대한 연산을 수행하는 함수를 메타 함수라고 함
//				- 템플릿 메타 함수는 실제로는 함수가 아님
//					- () 를 통한 호출이 아닌 <> 를 통하여 템플릿 인자를 전달함
//					- 실제로는 클래스(일단 MSVC 는 구조체) 로 구현됨
//	
//			- type_traits
//				- 타입의 속성에 대한 템플릿 메타 함수들을 제공하는 라이브러리
//	
//				- std::is_void<T>
//					- 템플릿 인자로 들어간 타입이 void 인지 알려주는 템플릿 메타 함수
//					- 위에서 간단하게 is_void 를 구현해보았지만 실제 구현은 아래와 같음
//	
//							_EXPORT_STD template <class _Ty>
//							_INLINE_VAR constexpr bool is_void_v = is_same_v<remove_cv_t<_Ty>, void>;
//							
//							_EXPORT_STD template <class _Ty>
//							struct is_void : bool_constant<is_void_v<_Ty>> {};
//	
//						- is_void_v 에서 is_same_v<remove_cv_t<_Ty>, void>;
//							- _v 가 붙은 것들은 대부분 ::value 필요없이 바로 참/거짓을 리턴
//							- is_same_v 는 두 템플릿 인자가 같은지 알려주는 템플릿 메타 함수
//							- is_void 는 is_void_v 의 값을 가지고 bool_constant<is_void<_Ty>> 를 상속받아 ::value 를 가짐
//								- bool_constant 는 integral_constant 의 bool 버전으로 뒤에서 다시 다룸
//	
//		*/
//	
//	}

/*  type_traits - std::is_integral, static_assert  */
#include <iostream>
#include <type_traits>

class A {};

template <typename T>
void only_integer(const T& t)
{
	static_assert(std::is_integral<T>::value); // C2338 : static_assert failed: 'std::is_integral<T>::value'
	std::cout << "T is an integer" << "\n";
}

int main()
{
	int n = 3;
	only_integer(n);

	A a;
	only_integer(a);	// 여기를 주석처리 하면 컴파일 오류 없어짐

	/*
	
	
	
	*/
}
