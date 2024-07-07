/*
	Concepts
*/

/*
	- Container 인지 판별하는 is_container 를 만들어보자
		- 기본 개념 https://www.youtube.com/watch?v=_doRiQS4GS8 의 25:20

			- range-based for 문을 이용하여 순회 가능한 컨테이너 C 는 아래를 만족한다
				1. std::begin(C&) 이 begin 반복자를 리턴
				2. std::end(C&) 이 tail 반복자를 리턴
				3. beginIter 와 tailIter 는 != 로 비교 가능함
				4. beginIter 는 ++ 를 가짐
				5. beginIter 는 void 가 아닌 * 타입을 가짐
				6. beginIter 와 tailIter 는 복사 생성 가능하고 파괴 가능함
*/

#include <iostream>
#include <utility>
#include <type_traits>
#include <vector>
#include <array>
#include <tuple>
#include <string_view>

template <typename C>
using TBegin = decltype(std::begin(std::declval<C&>));	// 1

template <typename C>
using TEnd = decltype(std::end(std::declval<C&>));	// 2

template <typename BI, typename EI>
using TNotEqualAble = decltype(std::declval<BI>() != std::declval<EI>());	// 3

template <typename BI>
using TIncable = decltype(++std::declval<BI&>());	// 4

template <typename BI>
using TDerefable = decltype(*std::declval<BI>());	// 5

template <typename C, typename = void>
struct is_container : std::false_type {};

template <typename C>
struct is_container <C, std::void_t<
	TBegin<C>,
	TEnd<C>,
	TIncable<TBegin<C>>,
	TNotEqualAble<TBegin<C>, TEnd<C>>,
	TDerefable<TBegin<C>>>>
	: std::integral_constant<bool,
	std::is_convertible_v < TNotEqualAble<TBegin<C>, TEnd<C>>, bool>
	&& !std::is_void_v<TDerefable<TBegin<C>>>
	&& std::is_destructible_v<TBegin<C>>
	&& std::is_copy_constructible_v<TBegin<C>>
	&& std::is_destructible_v<TEnd<C>>
	&& std::is_copy_constructible_v<TEnd<C>>> {};

template <typename C>
constexpr bool isContainer(const C& c)
{
	return is_container<C>::value;
}

template <typename C>
constexpr std::enable_if<is_container<C>::value, typename C::value_type>
getFirst1(const C& c)
{
	return *c.begin();
}

template <typename C, std::enable_if_t<is_container<C>::value, bool> = true>
constexpr auto getFirst2(const C& c)
{
	return *c.begin();
}

/*
	- 여기까지가 template 로 구현한 is_container
	- 문제점
		- 에러 메세지가 매우 매우 매우 난해함
		- enable_if, void_t 는 많은 사람들이 보기에 쉽지 않음

	- C++ 20 의 concepts 를 이용하여 더 쉽게 해보자
*/

template <typename BI, typename EI>
concept Neqable = requires(BI bi, EI ei)	// requires 의 도입으로 declval 따위를 갖다버릴 수 있음
{
	{ bi != ei } -> std::convertible_to <bool>;
};

template <typename C>
concept NeqableBeginAndEnd = requires(C c)
{
	{ std::begin(c) != std::end(c) } -> std::same_as<bool>;
};

template <typename C>
concept Beginable = requires(C c)
{
	std::begin(c);
};

template <typename C>
concept Endable = requires(C c)
{
	std::end(c);
};

template <typename C>
concept BeginIncrementable = requires(C c)
{
	std::begin(c)++;
};

template <typename C>
concept BeginDerefable = requires(C c)
{
	*std::begin(c);
};

template <typename C>
concept BeginDerefToVoid = requires(C c)
{
	{ *std::begin(c) } -> std::same_as<void>;
};

template <typename C>
concept BeginAndEndCopyConstructibleAndDestructible = requires(C c)
{
	std::destructible<decltype(std::begin(c))>&&
		std::destructible<decltype(std::end(c))>&&
		std::copy_constructible<decltype(std::begin(c))>&&
		std::copy_constructible<decltype(std::end(c))>;
};

template <typename C>
concept Container =
	Beginable<C> && Endable<C> &&
	BeginIncrementable<C> && BeginDerefable<C> &&
	NeqableBeginAndEnd<C> &&
	!BeginDerefToVoid<C> &&
	BeginAndEndCopyConstructibleAndDestructible<C>;

static_assert(Container<std::vector<int>>, "Must Be a container");

constexpr bool isFirstElemTheSame(Container auto c1, Container auto c2)
{
	return *std::begin(c1) == *std::begin(c2);
}

int main()
{
	using namespace std::literals;

	std::vector v{ 1,2,3 };
	std::array a{ 1,1,1 };
	std::tuple t{ 1, "hello"sv };	// tuple 은 container 가 아님

	std::cout << std::boolalpha;

	isFirstElemTheSame(v, a);
	// isFirstElemTheSame(v, t);	// 컴파일 되지 않지만 무수한 컴파일 에러의 향연이 벌어지지는 않음
	
	
}

/*
	- 바로 비교

		- template 버전
			template <typename C>
			struct is_container <C, std::void_t<
				TBegin<C>,
				TEnd<C>,
				TIncable<TBegin<C>>,
				TNotEqualAble<TBegin<C>, TEnd<C>>,
				TDerefable<TBegin<C>>>>
				: std::integral_constant<bool,
				std::is_convertible_v < TNotEqualAble<TBegin<C>, TEnd<C>>, bool>
				&& !std::is_void_v<TDerefable<TBegin<C>>>
				&& std::is_destructible_v<TBegin<C>>
				&& std::is_copy_constructible_v<TBegin<C>>
				&& std::is_destructible_v<TEnd<C>>
				&& std::is_copy_constructible_v<TEnd<C>>> {};


		- concepts 버전
			template <typename C>
			concept Container =
				Beginable<C> && Endable<C> &&
				BeginIncrementable<C> && BeginDerefable<C> &&
				NeqableBeginAndEnd<C> &&
				!BeginDerefToVoid<C> &&
				BeginAndEndCopyConstructibleAndDestructible<C>;


		-> concepts 가 훨씬 알아보기 쉽다
			-> 여전히 뭔가 어려워 보이지만 템플릿보다 수백배 낫다
*/