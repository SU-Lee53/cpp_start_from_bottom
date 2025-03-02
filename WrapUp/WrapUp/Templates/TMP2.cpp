
/*
	04.25 ~ 04.26 TMP2
*/

// 소수 판별 TMP, 의존 타입

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
//	// struct check_div<N, N / 2> { static const bool result = (N % (N / 2)) == 0; };	// 불가 : 템플릿 특수화시 연산자가 오면 안됨. 단순 식별자만 받음
//	
//	// template <typename N>
//	// struct check_div<N, divide<N, two>::result> { static const bool result = (N::num % (N::num / 2) == 0); };	// 불가 : divide<N, two>::result가 타입이 아니라 값임
//	// 이렇게 템플릿 인자에 따라서 어떠한 타입이 달라질 수 있는 것을 의존 타입(dependent type)이라고 부름
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
//			- 의존 타입
//				- 템플릿 인자에 따라 어떠한 타입이 달라질 수 있는 것
//				- 아래의 코드를 보자
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
//					- func<A>() 의 경우
//						-> int t 와 p를 곱하는 코드로 컴파일됨
//					- func<B>() 의 경우
//						-> int 타입을 가리키는 포인터로 컴파일됨
//	
//				- 컴파일러는 식별자를 보았을때 타입보다는 값이라고 우선적으로 평가하기 때문에 이런 일이 일어남
//				- 때문에 의존타입을 템플릿 특수화 할 경우 typename 을 붙여 컴파일러에게 식별자가 무조건 타입임을 알려주어야함
//				- 위 코드에서 divide<N, two>::result가 왜 값이 되나
//					- using result = INT<a::num / b::num>;
//						-> using result 가 INT<> 인 타입이 된다고 사용자는 생각함
//						-> 그러나 컴파일러가 구조상 식별자를 발견하면 값인지 타입인지 결정하는 과정에서 기본적으로 값이라고 생각함
//						-> 그래서 컴파일러는 result 를 static const int 타입의 값이라고 읽어버림
//	
//		*/
//	
//		return 0;
//	}

// 단위(Unit) 라이브러리

//	#include <iostream>
//	#include "ratio.h"	// 이전에 만든 Ratio 클래스를 이용하므로 헤더파일로 따로 만들어 include 함
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
//		// *, / 의 경우는 단위가 달라도 연산이 가능해야 하므로 템플릿 특수화를 이용해야함
//		template <typename D2>
//		quantity<T, typename add_dim_<D, D2>::type> operator*(quantity<T, D2> quant) { return quantity<T, typename add_dim_<D, D2>::type>(q * quant.q); }
//	
//		template <typename D2>
//		quantity<T, typename subtract_dim_<D, D2>::type> operator/(quantity<T, D2> quant) { return quantity<T, typename subtract_dim_<D, D2>::type>(q / quant.q); }
//	
//		// *, / 의 경우는 상수(스칼라) 연산도 가능해야 하므로 따로 만들어야함
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
//		//	kg + meter;	// kg 와 meter가 단위가 다르기때문에 연산이 안됨 -> 단위에 따라 타입이 달라져 버림
//	
//		// F = ma 라는 연산을 한다고 해보자
//		//	quantity<double, Dim<one, one, Ratio<-2, 1>>> F = kg * meter / (second * second);	// 타입을 사용자가 알아내기도 어렵고 매번 표기해주기도 힘듬 -> auto의 사용
//		auto F = kg * meter / (second * second);	// 컴파일러가 알아서 quantity<double, Dim<one, one, Ratio<-2, 1>>> 라는 타입으로 추론해줌
//		std::cout << "2kg의 물체를 3m/s^2 의 가속도로 밀기 위한 함의 크기는? " << F << std::endl;
//	
//		/*
//			- output:
//				2kg의 물체를 3m/s^2 의 가속도로 밀기 위한 함의 크기는? 6kg^1m^1s^-2
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
//		std::cout << "c 의 타입은? :: " << typeid(c).name() << std::endl;
//		std::cout << "num 의 타입은? :: " << typeid(num).name() << std::endl;
//		std::cout << "some 의 타입은? :: " << typeid(some).name() << std::endl;
//		std::cout << "some2 의 타입은? :: " << typeid(some2).name() << std::endl;
//		std::cout << "some3 의 타입은? :: " << typeid(some3).name() << std::endl;
//	
//		/*
//			- output:
//				c 의 타입은? :: int
//				num 의 타입은? :: double
//				some 의 타입은? :: class SomeClass
//				some2 의 타입은? :: class SomeClass
//				some3 의 타입은? :: int
//		*/
//	
//		/*
//			- auto
//				- 컴파일러가 알아서 타입을 유추하도록 하는 타입
//					-> cppreference 에서는 Placeholder type specifiers 라고 소개함. 
//					-> 컴파일러를 위해 타입 지정자를 placeholder로 두어 알아서 채워넣도록 하는 것이 템플릿과 비슷함
//				- 위의 Unit 처럼 타입이 점점 복잡해지고 사용자가 추론해지기 힘들어지는 경우에 사용하면 좋음
//	
//				- 위에서 some3의 경우
//					-> 사용자는 SomeClass를 생각하고 auto 타입을 사용함
//					-> 그러나 컴파일러는 최대한 단순하게 가능한 방법으로 추론하므로 그냥 int로 만들어버림
//						-> auto 타입 추론은 템플릿 타입 추론과 동일하게 최대한 단순하게 추론하므로 사용자의 의도와 맞지 않을수도 있음
//						-> 그러니 본인이 확실히 알 수 있고 타입이 너무 길지 않다면 직접 타입을 명시하는것이 더 좋음
//		*/
//	
//		return 0;
//	}