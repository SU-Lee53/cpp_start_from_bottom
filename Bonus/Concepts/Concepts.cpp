/*
	Concepts
*/

/*
	- Container ���� �Ǻ��ϴ� is_container �� ������
		- �⺻ ���� https://www.youtube.com/watch?v=_doRiQS4GS8 �� 25:20

			- range-based for ���� �̿��Ͽ� ��ȸ ������ �����̳� C �� �Ʒ��� �����Ѵ�
				1. std::begin(C&) �� begin �ݺ��ڸ� ����
				2. std::end(C&) �� tail �ݺ��ڸ� ����
				3. beginIter �� tailIter �� != �� �� ������
				4. beginIter �� ++ �� ����
				5. beginIter �� void �� �ƴ� * Ÿ���� ����
				6. beginIter �� tailIter �� ���� ���� �����ϰ� �ı� ������
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
	- ��������� template �� ������ is_container
	- ������
		- ���� �޼����� �ſ� �ſ� �ſ� ������
		- enable_if, void_t �� ���� ������� ���⿡ ���� ����

	- C++ 20 �� concepts �� �̿��Ͽ� �� ���� �غ���
*/

template <typename BI, typename EI>
concept Neqable = requires(BI bi, EI ei)	// requires �� �������� declval ������ ���ٹ��� �� ����
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
	std::tuple t{ 1, "hello"sv };	// tuple �� container �� �ƴ�

	std::cout << std::boolalpha;

	isFirstElemTheSame(v, a);
	// isFirstElemTheSame(v, t);	// ������ ���� ������ ������ ������ ������ �⿬�� ���������� ����
	
	
}

/*
	- �ٷ� ��

		- template ����
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


		- concepts ����
			template <typename C>
			concept Container =
				Beginable<C> && Endable<C> &&
				BeginIncrementable<C> && BeginDerefable<C> &&
				NeqableBeginAndEnd<C> &&
				!BeginDerefToVoid<C> &&
				BeginAndEndCopyConstructibleAndDestructible<C>;


		-> concepts �� �ξ� �˾ƺ��� ����
			-> ������ ���� ����� �������� ���ø����� ����� ����
*/