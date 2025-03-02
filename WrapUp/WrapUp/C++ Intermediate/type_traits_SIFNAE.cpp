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
//								- ������ ������ �߻����� �ʰ� �Ѿ. ���߿� SFINAE ���� �̸� Ȱ���ϱ⵵ ��
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

/*  SFINAE : Substitution Failure Is Not An Error  */
//	#include <iostream>
//	
//	template <typename T>
//	void test(typename T::x a) { std::cout << "T::x" << '\n'; }
//	
//	template <typename T>
//	void test(typename T::y b) { std::cout << "T::y" << '\n'; }
//	
//	struct A
//	{
//		using x = int;
//	};
//	
//	struct B
//	{
//		using y = int;
//	};
//	
//	int main()
//	{
//		test<A>(33);	// T::x
//	
//		test<B>(22);	// T::y
//	
//		/*
//			- SFINAE
//				- ġȯ ������ ������ ������ �ƴϴ� (Substitution Failure Is Not An Error)
//	
//				- ���ø� �Լ��� ������ �Ҷ� ���ø� ���ڵ��� ������ Ÿ������ ġȯ
//				- �� �������� ���������� �ùٸ��� �ʾƵ� ������ ������ ����Ű�� ����
//				- ��� �����ε� �ĺ������� ���ܽ�Ŵ
//	
//				- �Լ� ���� ��ü�� ���������� �ùٸ��� Ȯ���ϴ°��� �ƴ�
//					-> �Լ��� ���ڵ�� ���� Ÿ�Ը� ���������� �ùٸ��� Ȯ����
//					-> ���� ���������� �ùٸ��� ���� ������ �־ �����ε� �ĺ����� ���� ���� ����
//	
//				- �� �ڵ��� ���
//					- test<A>(33); �� ȣ���ϸ� 2���� �����ε� �Լ��� ������ ���� ġȯ��
//	
//						template <typename T>
//						void test(typename A::x a) { std::cout << "A::x" << '\n'; }
//						
//						template <typename T>
//						void test(typename A::y b) { std::cout << "A::y" << '\n'; }
//	
//					- class A ���� y�� �����Ƿ� A::y �� ���������� Ʋ��
//					- �̶� ������ ������ �ƴ϶� �����ε����� ���������μ� A::x �� ���
//	
//		
//		*/
//	
//	}

/*  std::enable_if  */
//	#include <iostream>
//	#include <type_traits>
//	
//	// enable_if �� ������ ���� (���� ������ ���� ����)
//	
//	template<bool B, typename T = void>
//	struct enable_if {};
//	
//	template <typename T>
//	struct enable_if<true, T> { typedef T type; };
//	
//	// std::enable_if �� �̿��Ͽ� ���� Ÿ�Ը� �޴� test ���ø� �Լ�
//	template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
//	void test(const T& t)
//	{
//		std::cout << "t : " << t << std::endl;
//	}
//	
//	struct A {};
//	
//	int main()
//	{
//		test(1);	// t : 1
//		test(false);	// t : 0
//		test('c');	// t : c
//		// test(A{});	// E0304 : �μ� ����� ��ġ�ϴ� �Լ� ���ø� "test"�� �ν��Ͻ��� �����ϴ�
//	
//		/*
//			- std::enable_if
//				- SFINAE �� �̿��Ͽ� ���ǿ� ���� �ʴ� �Լ����� �����ε� �ĺ������� ���� �� �� �ֵ��� �ϴ� ���ø� ��Ÿ �Լ�
//				- ���� ���Ǵ� �Ʒ��� ���� (MSVC)
//	
//						_EXPORT_STD template <bool _Test, class _Ty = void>
//						struct enable_if {}; // no member "type" when !_Test
//						
//						template <class _Ty>
//						struct enable_if<true, _Ty> { // type is _Ty for _Test
//						    using type = _Ty;
//						};
//	
//					- �� ������ ���� ������ ��ġ
//					- bool ���ڿ� ���ϴ� ������ �־��ָ� �۵�
//						- true �� ��� type �� ���ǵ� (�Ʒ������� �����ε�)
//						- false �� ��� type �� ���ǵ��� �ʾ� ::type ȣ��� ������ ������ ������ Ư�� Ÿ���� ������ (���������� �����ε�)
//	
//				- ��� ���Ǵ°�
//	
//						template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
//	
//					- �� ó�� ���� T �� ����Ÿ�Ը� ������ ������
//					- �ڵ� ����
//						- typename = 
//							-> ���ø��� ����Ʈ ���ڸ� �����ϴ� �κ�
//							-> ������ typename U = �̷������� ���ڸ� ������ �̰��� �ʿ����
//	
//						- std::enable_if �տ� �ѹ� �� ���� typename
//							-> std::enable_if<>::type ��ü�� ����Ÿ���̹Ƿ� �پ����
//	
//		
//		*/
//	
//	}

/*  std::enable_if �� Ȱ�� 1  */
//	#include <iostream>
//	#include <type_traits>
//	
//	template <typename T>
//	class vector
//	{
//	public:
//		// element �� num �� ����ִ� vector ����
//		vector(size_t num, const T& element) { std::cout << element << " �� " << num << " �� �����" << std::endl; }
//	
//		// �ݺ��� start ���� end ������ vector ����
//		//	template <typename Iterator>
//		//	vector(Iterator start, Iterator end) { std::cout << "�ݺ��ڸ� �̿��� ������ ȣ��" << std::endl; }
//		// 
//		// �� �����ڸ� �̿��Ұ�� �Ʒ� main() �� vector<int> v(10, 3); �� ����� �����ε���
//		// �̰� �������� enable_if �� �̿��Ͽ� ������ �ɾ�� ��
//	
//		template <typename Iterator, typename = typename std::enable_if<std::_Is_iterator_v<Iterator>>::type>
//		vector(Iterator start, Iterator end) { std::cout << "�ݺ��ڸ� �̿��� ������ ȣ��" << std::endl; }
//	
//	
//	};
//	
//	int main()
//	{
//		vector<int> v(10, 3);
//	
//		/*
//			- std::enable_if �� ���
//				- ���� �츮�� vector �� ���� ����ٰ� �����ϰ� 2���� �����ڸ� ������� �Ҷ�
//					
//						1) vector(size_t num, const T& element) �� element �� num �� ä���� �����ϴ� ������
//						2) vector(Iterator start, Iterator end) �ݺ��ڷ� ���۰� ���� �޾� �����ϴ� ������
//	
//					- �̶� 2�� �����ڸ� ���鶧 ���ø��� ���� �����
//					- �ܼ� template <typename Iterator> �� �̿��ϸ� ������ ����
//						- vector<int> v(10, 3); ���� �����ڸ� ȣ���ϸ� 2�� �����ڰ� �����ε���
//	
//				- ��?
//					- �⺻������ size_t �� unsigned long long Ÿ����
//						- <vcruntime.h> ��� ������� typedef unsigned __int64 size_t; �� ����
//						- #ifdef �� �̿��Ͽ� OS ���� �ٸ� (64��Ʈ �����츦 �����ϰ�� unsigned int �� ���ǵ�)
//					- num �� ��ȣ���� ������ �;������� 10 �� ��ȣ�� �ִ� ������ ���
//					- ��ħ �ƹ����� ���� ���ø� �Լ� vector(Iterator start, Iterator end) �� ����
//						-> �����Ϸ��� �̰� �� ���� �ĺ���� �Ǵ��ϰ� �� �����ڸ� �����ε��ع���
//		
//				- �̷��� std::enable_if �� �̿��Ͽ� Ư�� Ÿ���� ������ �� ����
//	
//						template <typename Iterator, typename = typename std::enable_if<std::_Is_iterator_v<Iterator>>::type>
//	
//					- �ռ� �� ����Ÿ�Ը� �޴� ����� �۵��� ����
//					- �ٸ� _Is_iterator_v �� C++ ǥ���� �ƴϹǷ� ����ϴ� STL �� ���� �ణ�� �޶��� �� ����
//		
//		*/
//	}

/*  std::enable_if �� Ȱ�� 2  */
//
// Ư���� ��� �Լ��� �����ϴ� Ÿ�Ը��� �޴� �Լ��� ����� ����
//	#include <iostream>
//	#include <vector>
//	#include <set>
//	
//	// std::enable_if �̻��
//	template <typename T, typename = decltype(std::declval<T>().func())>
//	void test(const T& t)
//	{
//		std::cout << "t.func() : " << t.func() << std::endl;
//	}
//	
//	// std::enable_if �� ����ϸ� ����Ÿ�Ա��� ���� ����
//	template <typename T, typename = std::enable_if_t<std::is_integral_v<decltype(std::declval<T>().func())>>>
//	void test2(const T& t)
//	{
//		std::cout << "t.func() : " << t.func() << std::endl;
//	}
//	
//	struct A
//	{
//		int func() const { return 1; }
//	};
//	
//	struct B 
//	{
//		char func() const { return 'a'; }
//	};
//	
//	struct C
//	{
//		A func() const { return A{}; }
//	};
//	
//	struct D {};
//	
//	// �������� �Լ��� Ȯ��
//	template <typename Cont, typename = decltype(std::declval<Cont>().begin()), typename = decltype(std::declval<Cont>().end())>
//	void print(const Cont& container)
//	{
//		std::cout << "[ ";
//		for (auto it = container.begin(); it != container.end(); ++it)
//		{
//			std::cout << *it << ' ';
//		}
//		std::cout << "]\n";
//	}
//	
//	template <typename Cont, typename = std::enable_if_t<std::_Is_iterator_v<decltype(std::declval<Cont>().begin())>>, typename = std::enable_if_t<std::_Is_iterator_v<decltype(std::declval<Cont>().end())>>>
//	void print2(const Cont& container)
//	{
//		std::cout << "[ ";
//		for (auto it = container.begin(); it != container.end(); ++it)
//		{
//			std::cout << *it << ' ';
//		}
//		std::cout << "]\n";
//	}
//	
//	int main()
//	{
//		test(A{});
//		test(B{});
//		// test(C{});
//		// test(D{});	// E0304 : �μ� ����� ��ġ�ϴ� �Լ� ���ø� "test2"�� �ν��Ͻ��� �����ϴ�.
//	
//		test2(A{});
//		test2(B{});
//		// test2(C{});	// E0304 : �μ� ����� ��ġ�ϴ� �Լ� ���ø� "test2"�� �ν��Ͻ��� �����ϴ�.
//		// test2(D{});	// E0304 : �μ� ����� ��ġ�ϴ� �Լ� ���ø� "test2"�� �ν��Ͻ��� �����ϴ�.
//	
//		std::vector<int> v = { 1,2,3,4,5 };
//		print(v);	// [1 2 3 4 5]
//		print2(v);	// [1 2 3 4 5]
//	
//		std::set<char> s = { 'a', 'b', 'c', 'd' };
//		print(s);	// [ a b c d ]
//		print2(s);	// [ a b c d ]
//	
//		/*
//			- std::enable_if �� Ȱ�� 2
//				- Ÿ���� Ư���� ����Լ��� ���������� Ȯ���� ������
//	
//						template <typename T, typename = std::enable_if_t<std::is_integral_v<decltype(std::declval<T>().func())>>>
//	
//					- decltype �� �̿��� ������ �ٸ��� ����Ÿ�Ա��� ������ �� ����
//					- �������� ����Լ��� Ȯ���ϴ°͵� ������
//	
//						template <typename Cont, 
//								typename = std::enable_if_t<std::_Is_iterator_v<decltype(std::declval<Cont>().begin())>>, 
//								typename = std::enable_if_t<std::_Is_iterator_v<decltype(std::declval<Cont>().end())>>>
//					
//					- ���� enable_if �� �̿��Ͽ� 2���� ��� �Լ��� ������ �ִ��� Ȯ��(begin(), end())
// 
//						template <typename Cont, typename = decltype(std::declval<Cont>().begin()), typename = decltype(std::declval<Cont>().end())>
// 			
//					- ���� decltype �� �̿��Ͽ�  2���� ��� �Լ��� ������ �ִ��� Ȯ��
//					- �Ѵ� �ʹ� �� �������� �������� ���ƺ����� ���� -> C++ 17 ���� ���Ե� void_t �� �ذᰡ��
//		
//		
//		*/
//	}

/*  void_t  */
//	#include <iostream>
//	#include <type_traits>
//	#include <vector>
//	
//	template <typename Cont, typename = std::void_t<decltype(std::declval<Cont>().begin()), decltype(std::declval<Cont>().end())>>
//	void print(const Cont& container)
//	{
//		std::cout << "[ ";
//		for (auto it = container.begin(); it != container.end(); ++it)
//		{
//			std::cout << *it << ' ';
//		}
//		std::cout << "]\n";
//	}
//	
//	// ������� �Ǽ��� �����ϱ� ���� Ÿ��üũ�� ���� �� print2
//	template <typename Cont>
//	std::void_t<decltype(std::declval<Cont>().begin()), decltype(std::declval<Cont>().end())> 
//	print2(const Cont& container)
//	{
//		std::cout << "[ ";
//		for (auto it = container.begin(); it != container.end(); ++it)
//		{
//			std::cout << *it << ' ';
//		}
//		std::cout << "]\n";
//	}
//	
//	struct Bad {};
//	
//	int main()
//	{
//		std::vector<int> v = { 1,2,3,4,5 };
//		print(v);	// [ 1 2 3 4 5 ]
//		print2(v);	// [ 1 2 3 4 5 ]
//	
//		// print<Bad, void>(Bad{});	// Ÿ��üũ �κп� void �� ������ �����ε� �ĺ������� ���ܵ��� ����(����Ʈ���ڰ� ��� �ȵ�)
//		// print2<Bad, void>(Bad{});	// ������ ����
//	
//		/*
//			- std::void_t
//				- void_t �� ����
//	
//						_EXPORT_STD template <class... _Types>
//						using void_t = void;
//					
//					- ������ ������ Ÿ�Ե��� ���޹���
//					- ���� ���޹��� ���ڵ� �߿� ���������� �ùٸ��� �������� �ִٸ� SFINAE �� ���� ���ܵ�
//						- ��� ���ڰ� ���������� �ùٸ����� void_t �� void �� ��
//	
//				- void_t �� Ȱ��
//						
//						template <typename Cont, typename = std::void_t<decltype(std::declval<Cont>().begin()), decltype(std::declval<Cont>().end())>>
//					
//					- �� ������ ������ decltype ���� Ư�� ����Լ� 2���� Ȯ���ϴ� ����� ������
//					- �������� �������� �ణ ������
//					- ���� Cont �� begin(), end() �� �ϳ��� ���ٸ� �����ε����� ���ܵ�
//	
//				- ���ǻ���
//					- void_t �� �̿��� �� Ÿ��üũ �κ��� �и��ϴ� ���� ����
//						- ����ڰ� ������ ���ø� ���ڸ� �߰��� ������ Ÿ��üũ�� �۵����� ���� �� �ֱ� ������
//	
//	
//		*/
//	
//	}