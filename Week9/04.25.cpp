
/*
	04.25 TMP2
*/

// 소수 판별 TMP

#include <iostream>

template <int N>
struct INT { static const int num = N; };

template <typename a, typename b>
struct add { typedef INT<a::num + b::num> result; };

template <typename a, typename b>
struct divide { typedef INT<a::num / b::num> result; };

using one = INT<1>;
using two = INT<2>;
using three = INT<3>;

template <typename N, typename d>
struct check_div { static const bool result = (N::num % d::num == 0) || check_div<N, typename add<d, one>::result>::result; };

template <typename N>
struct _is_prime { static const bool result = !check_div<N, two>::result; };

template<>
struct _is_prime<two> { static const bool result = true; };

template <>
struct _is_prime<three> { static const bool result = true; };

// template <int N>
// struct check_div<N, N / 2> { static const bool result = (N % (N / 2)) == 0; };	// 불가 : 템플릿 특수화시 연산자가 오면 안됨. 단순 식별자만 받음

// template <typename N>
// struct check_div<N, divide<N, two>::result> { static const bool result = (N::num % (N::num / 2) == 0); };	// 불가 : divide<N, two>::result가 타입이 아니라 값임
// 이렇게 템플릿 인자에 따라서 어떠한 타입이 달라질 수 있는 것을 의존 타입(dependent type)이라고 부름

/*
	- divide<N, two>::result가 왜 값이 되나
		- using result = INT<a::num / b::num>;
			-> using result 가 INT<> 인 타입이 된다고 사용자는 생각함
			-> 그러나 컴파일러가 구조상 식별자를 발견하면 값인지 타입인지 결정하는 과정에서 기본적으로 값이라고 생각함
			-> 그래서 컴파일러는 result 를 static const int 타입의 값이라고 읽어버림

*/
template <typename N>
struct check_div<N, typename divide<N, two>::result> { static const bool result = (N::num % (N::num / 2) == 0); };

template <int N>
struct is_prime { static const bool result = _is_prime<INT<N>>::result; };

int main()
{
	std::cout << std::boolalpha;
	std::cout << "Is 2 prime ? :: " << is_prime<2>::result << std::endl;
	std::cout << "Is 10 prime ? :: " << is_prime<10>::result << std::endl;
	std::cout << "Is 11 prime ? :: " << is_prime<11>::result << std::endl;
	std::cout << "Is 61 prime ? :: " << is_prime<61>::result << std::endl;

	/*
		- 의존 타입 다시 
		위에 내용이 왜 값이 되는건지 도저히 이해를 몬하겠음
	*/

	return 0;
}