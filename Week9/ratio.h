#pragma once
#include <iostream>

template <int X, int Y>
struct GCD
{
	static const int value = GCD<Y, X% Y>::value;
};

template<int X>
struct GCD<X, 0>
{
	static const int value = X;
};

template <int N, int D = 1>
struct Ratio
{
private:
	const static int _gcd = GCD<N, D>::value;

public:
	typedef Ratio<N / _gcd, D / _gcd> type;	// 클래스의 this와 비슷한 역할을 하도록 typedef를 이용하여 자기 자신을 가리키는 타입을 넣어줌
	static const int num = N / _gcd;	// 분자
	static const int den = D / _gcd;	// 분모

};

template<class R1, class R2>
struct _Ratio_add
{
	typedef Ratio<R1::num* R2::den + R2::num * R1::den, R1::den* R2::den> type;
};

template <class R1, class R2>
struct Ratio_add : _Ratio_add<R1, R2>::type {};	// _Ratio_add::type을 매번 명시하지 않게 하도록 해당 타입을 상속받는 Ratio_add 클래스를 만들어버림

template <class R1, class R2>
struct _Ratio_subtract
{
	using type = Ratio < R1::num* R2::den - R2::num * R1::den, R1::den* R2::den>;
};

template <class R1, class R2>
struct Ratio_subtract : _Ratio_subtract<R1, R2>::type {};

template <class R1, class R2>
struct _Ratio_multiply
{
	using type = Ratio<R1::num* R2::num, R1::den* R2::den>;
};

template <class R1, class R2>
struct Ratio_multiply : _Ratio_multiply<R1, R2>::type {};

template <class R1, class R2>
struct _Ratio_divide
{
	using type = Ratio<R1::num* R2::den, R1::den* R2::num>;
};

template <class R1, class R2>
struct Ratio_divide : _Ratio_divide<R1, R2>::type {};
