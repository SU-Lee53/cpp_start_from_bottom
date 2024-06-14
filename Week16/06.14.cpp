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
	only_integer(a);	// ���⸦ �ּ�ó�� �ϸ� ������ ���� ������

	/*
	
	
	
	*/
}
