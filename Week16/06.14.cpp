/*
	06.14 - <type_traits>, SFINAE, enable_if
*/

/*  ���ø� ��Ÿ �Լ�, type_traits - std::is_void  */
//	#include <iostream>
//	#include <type_traits>
//	
//	// ������ is_void
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
//			std::cout << "T �� void" << '\n';
//		}
//		else
//		{
//			std::cout << "T �� void �� �ƴ�" << '\n';
//		}
//	}
//	
//	int main()
//	{
//		tell_type<int>();	// T �� void �� �ƴ�
//		tell_type<void>();	// T �� void
//		
//		/*
//			- ���ø� ��Ÿ �Լ�
//				- �Լ��� �ƴ����� �Լ�ó�� �����ϴ� ���ø� Ŭ������
//				- "��Ÿ" �Լ� : Ÿ�Կ� ���� ������ �����ϴ� �Լ��� ��Ÿ �Լ���� ��
//				- ���ø� ��Ÿ �Լ��� �����δ� �Լ��� �ƴ�
//					- () �� ���� ȣ���� �ƴ� <> �� ���Ͽ� ���ø� ���ڸ� ������
//					- �����δ� Ŭ����(�ϴ� MSVC �� ����ü) �� ������
//	
//			- type_traits
//				- Ÿ���� �Ӽ��� ���� ���ø� ��Ÿ �Լ����� �����ϴ� ���̺귯��
//	
//				- std::is_void<T>
//					- ���ø� ���ڷ� �� Ÿ���� void ���� �˷��ִ� ���ø� ��Ÿ �Լ�
//					- ������ �����ϰ� is_void �� �����غ������� ���� ������ �Ʒ��� ����
//	
//							_EXPORT_STD template <class _Ty>
//							_INLINE_VAR constexpr bool is_void_v = is_same_v<remove_cv_t<_Ty>, void>;
//							
//							_EXPORT_STD template <class _Ty>
//							struct is_void : bool_constant<is_void_v<_Ty>> {};
//	
//						- is_void_v ���� is_same_v<remove_cv_t<_Ty>, void>;
//							- _v �� ���� �͵��� ��κ� ::value �ʿ���� �ٷ� ��/������ ����
//							- is_same_v �� �� ���ø� ���ڰ� ������ �˷��ִ� ���ø� ��Ÿ �Լ�
//							- is_void �� is_void_v �� ���� ������ bool_constant<is_void<_Ty>> �� ��ӹ޾� ::value �� ����
//								- bool_constant �� integral_constant �� bool �������� �ڿ��� �ٽ� �ٷ�
// 
//						- remove_cv �� const �� volatile Ű���带 ������
//	
//		*/
//	
//	}

/*  type_traits - std::is_integral, static_assert  */
//	#include <iostream>
//	#include <type_traits>
//	
//	class A {};
//	
//	template <typename T>
//	void only_integer(const T& t)
//	{
//		static_assert(std::is_integral<T>::value); // C2338 : static_assert failed: 'std::is_integral<T>::value'
//		std::cout << "T is an integer" << "\n";
//	}
//	
//	int main()
//	{
//		int n = 3;
//		only_integer(n);
//	
//		A a;
//		only_integer(a);	// ���⸦ �ּ�ó�� �ϸ� ������ ���� ������
//	
//		/*
//			- static_assert
//				- C++ 11 �� �߰��� Ű����
//				- ���ڷ� ���޵� ���� ������ �ƴ��� ������ Ÿ�ӿ� Ȯ��
//					- ��, bool Ÿ���� constexpr �� Ȯ�� ������
//					- true �� ��� �����Ϸ��� �ش� ���� ������
//					- false �� ��� ������ ������ ����Ŵ
//	
//			- std::is_integral<T>
//				- ���ڷ� ���� Ÿ���� ����Ÿ������ Ȯ����
//				- ���� ������ �Ʒ��� ����
//	
//						_EXPORT_STD template <class _Ty>
//						_INLINE_VAR constexpr bool is_integral_v = _Is_any_of_v<remove_cv_t<_Ty>, bool, char, signed char, unsigned char,
//							wchar_t,
//						#ifdef __cpp_char8_t
//							char8_t,
//						#endif // defined(__cpp_char8_t)
//							char16_t, char32_t, short, unsigned short, int, unsigned int, long, unsigned long, long long, unsigned long long>;
//						
//						_EXPORT_STD template <class _Ty>
//						struct is_integral : bool_constant<is_integral_v<_Ty>> {};
//	
//					- ���Ը��� ���ڷ� ���� _Ty �� ��� ����Ÿ�� ���� any_of ����(OR) �� �Ѵٰ� ���� ��
//					- __cpp_char8_t �� �ش� ����� ��� �������� Ȯ���ϴ� ��ũ�η� C++ 20 ���� ��밡���� https://en.cppreference.com/w/cpp/feature_test
//						- char8_t Ÿ���� C++ 20 ���� �߰��Ǿ����Ƿ� #ifdef ��ó���⸦ �̿��� Ȯ����
//				
//				- �� �ڵ��� only_integer() ������ std::is_integer<T> �� static_assert �� �̿��ؼ� ���� Ÿ���� �����ϰ� ����
//	
//		*/
//	}

/*  type_traits - std::is_class, std::integral_constant, ������ ����� ����Ű�� ������  */
//	#include <iostream>
//	#include <type_traits>
//	
//	class A
//	{
//	public:
//		int n;
//	
//		A(int n) : n(n) {}
//	};
//	
//	struct B
//	{
//		int m;
//	
//		B(int m) : m(m) {}
//	};
//	
//	int main()
//	{
//		// ������ ����� ����Ű�� ������
//		int A::* p_n = &A::n;
//	
//		A a(3);
//		std::cout << "a.n : " << a.n << std::endl;	// a.n : 3
//		std::cout << "a.*p_n : " << a.*p_n << std::endl;	// a.*p_n : 3
//	
//		int B::* p_m = &B::m;
//	
//		B b(3);
//		std::cout << "b.m : " << b.m << std::endl;
//		std::cout << "b.p_m : " << b.*p_m << std::endl;
//	
//	
//		/*
//			- ����� �ڵ忡 ���� std::is_class �� ����(���� ������ cppreference ���� �������ŵ���)
//	
//					namespace detail {
//					template <class T>
//					char test(int T::*);
//					struct two {
//					  char c[2];
//					};
//					template <class T>
//					two test(...);
//					}  // namespace detail
//					
//					template <class T>
//					struct is_class : std::integral_constant<bool, sizeof(detail::test<T>(0)) == 1 && !std::is_union<T>::value> {};
//	
//				- std::is_class �� �����Ϸ��� std::integral_constant �� ��� �����Ϳ� ���ؼ� ���� �˾ƺ�����
//	
//			- std::integral_constant<T, T v>
//				- v �� static ���ڷ� ������ Ŭ����
//					-> ��� ���� static ��ü�� ������ �ִ� Ŭ������ ����� �ִ� ���ø�
//					-> ���� ��� std::integral_constant<bool, false> ��� integral_constant::value �� false �� Ŭ����
//	
//			- ������ ����� ����Ű�� ������
//				- Ư�� Ŭ������ ����� ����Ű�� ������
//					-> ���� ��� int T::*p; �� T �� int ����� ����Ű�� ������ p �� ������ ����
//	
//				- ������ �����ϴ� ��ü�� ����� ����Ű�� ���� �ƴϰ� �Ϲ� ����� �����ϵ��� �������� �ش� ����� ������
//					- �� �� �ڵ忡�� a.n �� a.*p_n �� ���� ������
//	
//				- �� ������ ���� Ŭ�������� ��� ������
//					- struct �� ����. C++ �� ��ǻ� class �� struct �� �⺻���� ���� ������ �ܿ��� ���̰� ���ٰ� ��
//	
//			- std::is_class<T>
//				- ���ڷ� ���޵� Ÿ���� Ŭ���� ���� �ƴ��� Ȯ���ϴ� ��Ÿ �Լ�
//	
//				- ���� ����� �ڵ忡 �ִ� ������ ���� �ؼ�
//					
//					- ������ �� �Ʒ����� ���ƾ� ��
//	
//							template <class T>
//							struct is_class : std::integral_constant<bool, sizeof(detail::test<T>(0)) == 1 && !std::is_union<T>::value> {};
//	
//						- size_of(detail::test<T>(0)) == 1 �� !std::is_union<T>::value �� ��� true ���� is_class �� true �� ���� �� �� ����
//	
//					- size_of(detail::test<T>(0)) == 1 ?
//	
//							namespace detail {
//							template <class T>
//							char test(int T::*);
//							struct two {
//							  char c[2];
//							};
//							template <class T>
//							two test(...);
//							}  // namespace detail
//	
//						- 2���� test �Լ��� ����
//	
//							1) �ϴ� char test(int T::*) �� T �� Ŭ������ �ƴϸ� ���ʿ� �Ұ����� ����
//								- T �� Ŭ������� int Ÿ���� ����� ��� ��ȿ�� ������. ���� ����ų ����� ���� ����
//									-> ���𰡸� ����ų�� �ְ� ���� �߿��Ѱ� �ƴϰ� ���� Ŭ�������� �ƴ����� �Ǻ��ϴ� ������
//							
//							2) two test(...) �� T �� Ŭ������ �ƴϾ �׻� �ν��Ͻ�ȭ�� ������
//	
//						- ���� T �� Ŭ������� �����ϰ� detail::test<T>(0) �� �������ϸ�
//							- 1�� char test(int T::*) �� ���ڰ� ��õǾ� �����Ƿ� �����ε� �켱������ �� ����
//							- �����ϵ� test �� char�� �����ϹǷ� sizeof(detail::test<T>(0)) �� sizeof(char) �� �Ǿ� == 1 �� true
//	
//						- �ݸ� T �� Ŭ������ �ƴ϶�� �����ϰ� �������ϸ�
//							- 1�� char test(int T::*) �� �Ұ����� �����̹Ƿ� �����ε� �ĺ������� ���ܵ�
//								-> ������ ������ �߻����� �ʰ� �Ѿ. ���߿� SFINAE ���� �̸� Ȱ���ϱ⵵ ��
//							- �׷��Ƿ� 2�� two test(...) �� �����ε� 
//								- ���ϵ� two �� char [2] �̹Ƿ� sizeof(two) �� 2 �� �Ǿ� false
//							
//						- sizeof(detail::test<T>(0)) == 1 �� T �� union �϶��� �����ϹǷ� !std::is_union<T>::value> �� �̿��� union �� �ƴ��� �����ؾ���
//							- C++ ���� union �� class �� ������ ����� ����... �̴� �����Ϸ��� ���� �����ؼ� �ذ���
//		
//				- ����� ���� cppreference ���� �ٸ� �������� ��������
//	
//						namespace detail
//						{
//							template<class T>
//							std::integral_constant<bool, !std::is_union<T>::value> test(int T::*);
//						
//							template<class>
//							std::false_type test(...);
//						}
//						
//						template<class T>
//						struct is_class : decltype(detail::test<T>(nullptr)) {};
//	
//					- �⺻������ ���� ��İ� ��������� ��� ���̰� ����
//						- detail::test<T> �Լ����� std::is_union �� �˻���
//						- sizeof ���� ���� detail::test<T> �� ���� Ÿ������ true / false �� �̿��Ͽ� �ٷ� ������
//							- std::false_type �� std::integral_constant<bool, false> �� ����
//	
//		*/
//	
//	}

/*  SFINAE : Substitution Failure Is Not An Error*/
#include <iostream>

template <typename T>
void test(typename T::x a) { std::cout << "T::x" << '\n'; }

template <typename T>
void test(typename T::y b) { std::cout << "T::y" << '\n'; }

struct A
{
	using x = int;
};

struct B
{
	using y = int;
};

int main()
{
	test<A>(33);	// T::x

	test<B>(22);	// T::y
}