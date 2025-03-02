
/*
	04.25 ~ 04.26 TMP2
*/

// �Ҽ� �Ǻ� TMP, ���� Ÿ��

//	#include <iostream>
//	
//	template <int N>
//	struct INT { static const int num = N; };
//	
//	template <typename a, typename b>
//	struct add { typedef INT<a::num + b::num> result; };
//	
//	template <typename a, typename b>
//	struct divide { typedef INT<a::num / b::num> result; };
//	
//	using one = INT<1>;
//	using two = INT<2>;
//	using three = INT<3>;
//	
//	template <typename N, typename d>
//	struct check_div { static const bool result = (N::num % d::num == 0) || check_div<N, typename add<d, one>::result>::result; };
//	
//	template <typename N>
//	struct _is_prime { static const bool result = !check_div<N, two>::result; };
//	
//	template<>
//	struct _is_prime<two> { static const bool result = true; };
//	
//	template <>
//	struct _is_prime<three> { static const bool result = true; };
//	
//	// template <int N>
//	// struct check_div<N, N / 2> { static const bool result = (N % (N / 2)) == 0; };	// �Ұ� : ���ø� Ư��ȭ�� �����ڰ� ���� �ȵ�. �ܼ� �ĺ��ڸ� ����
//	
//	// template <typename N>
//	// struct check_div<N, divide<N, two>::result> { static const bool result = (N::num % (N::num / 2) == 0); };	// �Ұ� : divide<N, two>::result�� Ÿ���� �ƴ϶� ����
//	// �̷��� ���ø� ���ڿ� ���� ��� Ÿ���� �޶��� �� �ִ� ���� ���� Ÿ��(dependent type)�̶�� �θ�
//	
//	template <typename N>
//	struct check_div<N, typename divide<N, two>::result> { static const bool result = (N::num % (N::num / 2) == 0); };
//	
//	template <int N>
//	struct is_prime { static const bool result = _is_prime<INT<N>>::result; };
//	
//	int main()
//	{
//		std::cout << std::boolalpha;
//		std::cout << "Is 2 prime ? :: " << is_prime<2>::result << std::endl;
//		std::cout << "Is 10 prime ? :: " << is_prime<10>::result << std::endl;
//		std::cout << "Is 11 prime ? :: " << is_prime<11>::result << std::endl;
//		std::cout << "Is 61 prime ? :: " << is_prime<61>::result << std::endl;
//	
//		/*
//			- ���� Ÿ��
//				- ���ø� ���ڿ� ���� ��� Ÿ���� �޶��� �� �ִ� ��
//				- �Ʒ��� �ڵ带 ����
//	
//					template<typename T>
//					int func()
//					{
//						T::t* p;
//					}
//	
//					class A
//					{
//						const static int t;
//					};
//	
//					class B
//					{
//						using t = int;
//					};
//	
//					- func<A>() �� ���
//						-> int t �� p�� ���ϴ� �ڵ�� �����ϵ�
//					- func<B>() �� ���
//						-> int Ÿ���� ����Ű�� �����ͷ� �����ϵ�
//	
//				- �����Ϸ��� �ĺ��ڸ� �������� Ÿ�Ժ��ٴ� ���̶�� �켱������ ���ϱ� ������ �̷� ���� �Ͼ
//				- ������ ����Ÿ���� ���ø� Ư��ȭ �� ��� typename �� �ٿ� �����Ϸ����� �ĺ��ڰ� ������ Ÿ������ �˷��־����
//				- �� �ڵ忡�� divide<N, two>::result�� �� ���� �ǳ�
//					- using result = INT<a::num / b::num>;
//						-> using result �� INT<> �� Ÿ���� �ȴٰ� ����ڴ� ������
//						-> �׷��� �����Ϸ��� ������ �ĺ��ڸ� �߰��ϸ� ������ Ÿ������ �����ϴ� �������� �⺻������ ���̶�� ������
//						-> �׷��� �����Ϸ��� result �� static const int Ÿ���� ���̶�� �о����
//	
//		*/
//	
//		return 0;
//	}

// ����(Unit) ���̺귯��

//	#include <iostream>
//	#include "ratio.h"	// ������ ���� Ratio Ŭ������ �̿��ϹǷ� ������Ϸ� ���� ����� include ��
//	
//	template <typename U, typename V, typename W>
//	struct Dim
//	{
//		using M = U;	// kg
//		using L = V;	// m
//		using T = W;	// s
//	
//		using type = Dim<M, L, T>;
//	};
//	
//	template <typename U, typename V>
//	struct add_dim_
//	{
//		typedef Dim<typename Ratio_add<typename U::M, typename V::M>::type,
//					typename Ratio_add<typename U::L, typename V::L>::type,
//					typename Ratio_add<typename U::T, typename V::T>::type>
//			type;
//	};
//	
//	template <typename U, typename V>
//	struct subtract_dim_
//	{
//		typedef Dim<typename Ratio_subtract<typename U::M, typename V::M>::type,
//					typename Ratio_subtract<typename U::L, typename V::L>::type,
//					typename Ratio_subtract<typename U::T, typename V::T>::type>
//			type;
//	};
//	
//	template <typename T, typename D>
//	struct quantity
//	{
//		T q;
//		using dim_type = D;
//	
//		quantity operator+(quantity<T, D> quant) { return quantity<T, D>(q + quant.q); }
//		quantity operator-(quantity<T, D> quant) { return quantity<T, D>(q - quant.q); }
//	
//		// *, / �� ���� ������ �޶� ������ �����ؾ� �ϹǷ� ���ø� Ư��ȭ�� �̿��ؾ���
//		template <typename D2>
//		quantity<T, typename add_dim_<D, D2>::type> operator*(quantity<T, D2> quant) { return quantity<T, typename add_dim_<D, D2>::type>(q * quant.q); }
//	
//		template <typename D2>
//		quantity<T, typename subtract_dim_<D, D2>::type> operator/(quantity<T, D2> quant) { return quantity<T, typename subtract_dim_<D, D2>::type>(q / quant.q); }
//	
//		// *, / �� ���� ���(��Į��) ���굵 �����ؾ� �ϹǷ� ���� ��������
//		quantity<T, D> operator*(T scalar) { return quantity<T, D>(q * scalar); }
//		quantity<T, D> operator/(T scalar) { return quantity<T, D>(q / scalar); }
//	
//		quantity(T q) : q(q) {}
//	};
//	
//	template<typename T, typename D>
//	std::ostream& operator<<(std::ostream& out, const quantity<T, D>& q)
//	{
//		out << q.q << "kg^" << D::M::num / D::M::den << "m^" << D::L::num / D::L::den
//			<< "s^" << D::T::num / D::T::den;
//	
//		return out;
//	}
//	
//	int main()
//	{
//		using one = Ratio<1, 1>;
//		using zero = Ratio<0, 1>;
//	
//		quantity<double, Dim<one, zero, zero>> kg(2);
//		quantity<double, Dim<zero, one, zero>> meter(3);
//		quantity<double, Dim<zero, zero, one>> second(1);
//	
//		kg + kg;
//	
//		//	kg + meter;	// kg �� meter�� ������ �ٸ��⶧���� ������ �ȵ� -> ������ ���� Ÿ���� �޶��� ����
//	
//		// F = ma ��� ������ �Ѵٰ� �غ���
//		//	quantity<double, Dim<one, one, Ratio<-2, 1>>> F = kg * meter / (second * second);	// Ÿ���� ����ڰ� �˾Ƴ��⵵ ��ư� �Ź� ǥ�����ֱ⵵ ���� -> auto�� ���
//		auto F = kg * meter / (second * second);	// �����Ϸ��� �˾Ƽ� quantity<double, Dim<one, one, Ratio<-2, 1>>> ��� Ÿ������ �߷�����
//		std::cout << "2kg�� ��ü�� 3m/s^2 �� ���ӵ��� �б� ���� ���� ũ���? " << F << std::endl;
//	
//		/*
//			- output:
//				2kg�� ��ü�� 3m/s^2 �� ���ӵ��� �б� ���� ���� ũ���? 6kg^1m^1s^-2
//		*/
//	
//		return 0;
//	}

// auto

//	#include <iostream>
//	#include <typeinfo>
//	
//	int sum(int a, int b) { return a + b; }
//	
//	class SomeClass
//	{
//	public:
//		SomeClass(int d) : data(d) {}
//		SomeClass(const SomeClass& s) : data(s.data) {}
//	
//	private:
//		int data;
//	};
//	
//	int main()
//	{
//		auto c = sum(1, 2);
//		auto num = 1.0 + 2.0;
//	
//	
//		SomeClass some(10);
//		auto some2 = some;
//	
//		auto some3(10);
//	
//		std::cout << "c �� Ÿ����? :: " << typeid(c).name() << std::endl;
//		std::cout << "num �� Ÿ����? :: " << typeid(num).name() << std::endl;
//		std::cout << "some �� Ÿ����? :: " << typeid(some).name() << std::endl;
//		std::cout << "some2 �� Ÿ����? :: " << typeid(some2).name() << std::endl;
//		std::cout << "some3 �� Ÿ����? :: " << typeid(some3).name() << std::endl;
//	
//		/*
//			- output:
//				c �� Ÿ����? :: int
//				num �� Ÿ����? :: double
//				some �� Ÿ����? :: class SomeClass
//				some2 �� Ÿ����? :: class SomeClass
//				some3 �� Ÿ����? :: int
//		*/
//	
//		/*
//			- auto
//				- �����Ϸ��� �˾Ƽ� Ÿ���� �����ϵ��� �ϴ� Ÿ��
//					-> cppreference ������ Placeholder type specifiers ��� �Ұ���. 
//					-> �����Ϸ��� ���� Ÿ�� �����ڸ� placeholder�� �ξ� �˾Ƽ� ä���ֵ��� �ϴ� ���� ���ø��� �����
//				- ���� Unit ó�� Ÿ���� ���� ���������� ����ڰ� �߷������� ��������� ��쿡 ����ϸ� ����
//	
//				- ������ some3�� ���
//					-> ����ڴ� SomeClass�� �����ϰ� auto Ÿ���� �����
//					-> �׷��� �����Ϸ��� �ִ��� �ܼ��ϰ� ������ ������� �߷��ϹǷ� �׳� int�� ��������
//						-> auto Ÿ�� �߷��� ���ø� Ÿ�� �߷а� �����ϰ� �ִ��� �ܼ��ϰ� �߷��ϹǷ� ������� �ǵ��� ���� �������� ����
//						-> �׷��� ������ Ȯ���� �� �� �ְ� Ÿ���� �ʹ� ���� �ʴٸ� ���� Ÿ���� ����ϴ°��� �� ����
//		*/
//	
//		return 0;
//	}