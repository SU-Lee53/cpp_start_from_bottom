// 모두의 코드 챕터8의 엑셀 만들기는 스킵
// 대신 템플릿까지 끝내고 다른거를 할 예정

/*
	04.22 템플릿
*/

// 템플릿?

/*
	- 템플릿?
		- 기존 C++에서 어떠한 자료구조를 클래스로 만들려고 한다면...
			- 특정한 자료형에 한정해서만 만들게 됨
			- 예를 들어 int를 담는 자료형을 만들면 int 말고는 담을 수 없음
			- 그런데 생각을 해보면 다른 타입에 대한 자료구조를 일일히 만든다고 하면 중복되는 코드가 많게 될것
			- 그러면 그냥 사용자는 틀만 만들어놓고 타입은 컴파일러가 그때그때 끼워맞추도록 하면 편하지 않을까
				-> C++에서는 이를 template라는 이름으로 지원해줌
*/

// template

//	#include <iostream>
//	#include <string>
//	
//	template <typename T>
//	class Vector
//	{
//	public:
//		// 생성자
//		Vector(int n = 1) : data(new T[n]), capacity(n), length(0) {}
//	
//		// 맨 뒤에 새로운 원소를 추가한다
//		void push_back(T s)
//		{
//			if (capacity <= length)
//			{
//				T* temp = new T[capacity * 2];
//				for (int i = 0; i < length; i++)
//				{
//					temp[i] = data[i];
//				}
//				delete[] data;
//				data = temp;
//				capacity *= 2;
//			}
//	
//			data[length] = s;
//			length++;
//		}
//	
//		// 임의의 위치에 원소에 접근한다
//		T operator[](int i) { return data[i]; }
//	
//		void remove(int x)
//		{
//			for (int i = x + 1; i < length; i++)
//			{
//				data[i - 1] = data[i];
//			}
//			length--;
//		}
//	
//		// 현재 벡터의 크기를 구한다
//		int size() { return length; }
//	
//		~Vector()
//		{
//			if (data)
//			{
//				delete[] data;
//			}
//		}
//	
//	private:
//		T* data;
//		int capacity;
//		int length;
//	};
//	
//	//	int main()
//	{
//		Vector<int> int_vec;
//		int_vec.push_back(3);
//		int_vec.push_back(2);
//	
//		std::cout << "------- int vector -------" << std::endl;
//		std::cout << "첫번째 원소 : " << int_vec[0] << std::endl;
//		std::cout << "두번째 원소 : " << int_vec[1] << std::endl;
//	
//		Vector<std::string> str_vec;
//		str_vec.push_back("hello");
//		str_vec.push_back("world");
//		
//		std::cout << "------- std::string vector -------" << std::endl;
//		std::cout << "첫번째 원소 : " << str_vec[0] << std::endl;
//		std::cout << "두번째 원소 : " << str_vec[1] << std::endl;
//	
//		/*
//			output:
//			------- int vector -------
//			첫번째 원소 : 3
//			두번째 원소 : 2
//			------- std::string vector -------
//			첫번째 원소 : hello
//			두번째 원소 : world
//		*/
//	
//		/*
//			- template
//				- 사전적 의미 : 형판, 어떠한 물건을 찍어내는 틀
//					-> C++의 template이 정확히 같은 의미로 사용됨. 사용자가 원하는 타입을 넣으면 알아서 코드를 찍어내는 틀
//				- 사용법
//					- 사용하려는 클래스 상단에 template <typename T>로 선언
//						-> 선언시, 아래에 정의되는 클래스에 대해 템플릿을 정의
//						-> 템플릿 인자로 T를 받으며 T는 반드시 어떠한 타입의 이름임을 명시함
//						-> 위 Vector는 Vector 클래스에 대한 템플릿을 명시함. 함수의 경우에는 함수 템플릿이 따로있음(나중에 다시 설명)
//						※ template <class T> 라고 적어도 완벽히 동일함. 다만 C++ 표준에서는 typename T를 쓰는것을 권장중임
//							-> class T라고 적으면 일반 타입보다는 클래스가 들어가야한다고 혼동하는 일이 자주 일어났기 때문
//							-> 다만 이전 코드와의 호환성을 위해 키워드를 지우지 않고 남겨두었음
//	
//					- 이후 정의한 템플릿에 인자의 값을 전달하려면 <> 안에 명시함
//						-> Vector<int>, Vector<std::string> 이런식으로 명시
//						-> 값 혹은 객체를 인자로 전달해오던 이전과 달리 '타입' 자체를 전달함
//						-> 이렇게 타입이 전달되면 컴파일러가 이것을 보고 T 자리에 타입을 끼워맞춰 코드를 생성함
//	
//					- 이렇게 클래스 템플릿에 인자를 전달해서 실제 코드를 생성하는것을 "클래스 템플릿 인스턴스화(class template instantiation)" 이라고 부름
//						- 실제로 템플릿을 인스턴스화 하지 않으면 컴파일시에 아무런 코드로도 변환되지 않음
//							-> 템플릿은 반드시 인스턴스화 되어야지만 비로소 컴파일러가 실제 코드를 생성함
//	
//		*/
//	
//	}

// 템플릿 특수화

//	// 기본 템플릿 클래스
//	template <typename A, typename B, typename C>
//	class test {};
//	
//	// 일부 템플릿 특수화 : A가 int이고 C가 double일때 따로 처리하고 싶다면
//	template <typename B>
//	class test<int, B, double> {};
//	
//	// 전체 템플릿 특수화
//	template <>	// 반드시 명시
//	class test<int, int, double> {};
//	
//	// bool 타입에 대한 class Vector 템플릿 특수화
//	template <>
//	class Vector<bool>
//	{
//		/*
//			- 잠깐 알고가자: bool을 특수화하는 이유
//				- bool은 0,1 로만 표현되므로 1비트만 있으면 되는데 C++의 기본 데이터 처리 단위가 1바이트임
//				- 이는 메모리 낭비라고 생각되어 bool에 대한 템플릿 특수화를 통해 특별히 따로 처리
//				- 32비트짜리 unsigned int 하나에 bool 값이 32개 들어감
//					-> n번째 값은 n / 32 번째 uint 안에 저장되고 n % 32번째 비트가 n번째 값임
//		*/
//	public:
//		typedef bool valuetype;
//	
//		// 생성자
//		Vector(int n = 1)
//			: data(new unsigned int[n / 32 + 1]), capacity(n / 32 + 1), length(0)
//		{
//			for (int i = 0; i < capacity; i++)
//			{
//				data[i] = 0;
//			}
//		}
//	
//		void push_back(bool s)
//		{
//			if (capacity * 32 <= length)
//			{
//				unsigned int* temp = new unsigned int[capacity * 2];
//				for (int i = 0; i < capacity; i++)
//				{
//					temp[i] = data[i];
//				}
//				for (int i = capacity; i < 2 * capacity; i++)
//				{
//					temp[i] = 0;
//				}
//	
//				delete[] data;
//				data = temp;
//				capacity *= 2;
//			}
//	
//			if (s)
//			{
//				data[length / 32] |= (1 << (length % 32));	// OR 연산으로 나머지 비트는 남기고 원하는 자리만 1로 만듬
//			}
//	
//			length++;
//		}
//	
//		// AND 연산으로 원하는 비트만 남기고 나머지는 0으로 만듬
//		// 원하는 비트가 1이었다면 해당 비트가 남아 != 0 연산시 true
//		// 원하는 비트가 0이었다면 != 0 연산시 false
//		bool operator[](int i) { return (data[i / 32] & (1 << (i % 32))) != 0; }	
//	
//		void remove(int x)
//		{
//			for (int i = x + 1; i < length; i++)
//			{
//				int prev = i - 1;
//				int curr = i;
//	
//				// 만일 curr 위치에 있는 비트가 1이라면
//				// prev 위치에 있는 비트를 1로 만든다.
//				if (data[curr / 32] & (1 << (curr % 32)))
//				{
//					data[curr / 32] |= (1 << (curr % 32));
//				}
//				// 아니면 prev 위치에 있는 비트를 0으로 채운다
//				else
//				{
//					unsigned int all_ones_except_prev = 0xFFFFFFFF;	// 0xFFFFFFFF : 모든 비트가 1인 uint
//					all_ones_except_prev ^= (1 << (prev % 32));	// XOR 연산으로 해당 비트만 0으로 바꿈
//					data[prev / 32] &= all_ones_except_prev;
//				}
//			}
//			length--;
//		}
//	
//		int size() { return length; }
//	
//		~Vector()
//		{
//			if (data) delete[] data;
//		}
//	
//	private:
//		unsigned int* data;	// uint인 이유: 그냥 int는 shift연산시 문제가 발생할 수 있음(2의 보수 특성상 부호비트 보존과 관련된 문제인듯. 산술적 우측 시프트 참고)
//		int capacity;
//		int length;
//	};
//
//	int main()
//	{
//		Vector<int> int_vec;
//		int_vec.push_back(3);
//		int_vec.push_back(2);
//	
//		std::cout << "------- int vector -------" << std::endl;
//		std::cout << "첫번째 원소 : " << int_vec[0] << std::endl;
//		std::cout << "두번째 원소 : " << int_vec[1] << std::endl;
//	
//		Vector<std::string> str_vec;
//		str_vec.push_back("hello");
//		str_vec.push_back("world");
//	
//		std::cout << "------- std::string vector -------" << std::endl;
//		std::cout << "첫번째 원소 : " << str_vec[0] << std::endl;
//		std::cout << "두번째 원소 : " << str_vec[1] << std::endl;
//	
//		Vector<bool> bool_vec;
//		bool_vec.push_back(true);
//		bool_vec.push_back(true);
//		bool_vec.push_back(false);
//		bool_vec.push_back(false);
//		bool_vec.push_back(false);
//		bool_vec.push_back(true);
//		bool_vec.push_back(false);
//		bool_vec.push_back(true);
//		bool_vec.push_back(false);
//		bool_vec.push_back(true);
//		bool_vec.push_back(false);
//		bool_vec.push_back(true);
//		bool_vec.push_back(false);
//		bool_vec.push_back(true);
//		bool_vec.push_back(false);
//		bool_vec.push_back(true);
//		bool_vec.push_back(false);
//	
//		std::cout << "------- bool vector -------" << std::endl;
//		for (int i = 0; i < bool_vec.size(); i++)
//		{
//			std::cout << bool_vec[i];
//		}
//	
//		std::cout << std::endl;
//	
//		// 잠깐 스트림 버퍼 조작자 복습
//		for (int i = 0; i < bool_vec.size(); i++)
//		{
//			std::cout << "[" << std::boolalpha << bool_vec[i] << "] ";
//		}
//	
//		/*
//			output:
//			------- int vector -------
//			첫번째 원소 : 3
//			두번째 원소 : 2
//			------- std::string vector -------
//			첫번째 원소 : hello
//			두번째 원소 : world
//			------- bool vector -------
//			11000101010101010
//			[true] [true] [false] [false] [false] [true] [false] [true] [false] [true] [false] [true] [false] [true] [false] [true] [false]
//		*/
//	
//		/*
//			- 템플릿 특수화(template specialization)
//				- 일부 경우에 대해서 따로 처리하는 것
//				- 사용법
//					- 기본 클래스 템플릿이 template <typename A, typename B, typename C> class test 로 정의되어있다고 치고
//					- 일부에 대해서만 특수화 하고싶은 경우(예시는 A, C만 특수화)
//						-> template <typename B> class test<int, B, double> : A가 int, C가 double 인 경우 특수화
//					- 전체를 특수화 하고싶은 경우
//						-> template <> class test<int, int, double> : A, B가 int, C가 double
//						-> 전달하는 템플릿 인자가 없어도 특수화하려면 template <>를 명시해주어야 함
//	
//				- 위 코드에 대한 내용은 생략...
//					-> 실제 std::vector도 bool에 대해서는 특수화 되어있음
//		*/
//	}

// 함수 템플릿 1

//	#include <iostream>
//	#include <string>
//	
//	template <typename T>
//	T max(T& a, T& b)
//	{
//		return a > b ? a : b;
//	}
//	
//	int main()
//	{
//		int a = 1, b = 2;
//		std::cout << "Max (" << a << ", " << b << ") ? : " << max(a, b) << std::endl;
//	
//		std::string s = "hello", t = "world";
//		std::cout << "Max (" << s << ", " << t << ") ? : " << max(s, t) << std::endl;
//	
//		/*
//			output:
//			Max (1, 2) ? : 2
//			Max (hello, world) ? : world
//		*/
//	
//		/*
//			- 함수 템플릿
//				- 클래스 템플릿과 마찬가지로 템플릿을 이용하여 함수를 만들 수 있음
//				- 클래스 템플릿과 마찬가지로 인스턴스화 되기 전까진 컴파일 시에 아무런 코드로도 변환되지 않음
//					-> 위 코드에서 템플릿 함수가 실제 인스턴스화 되는 부분은 max(a, b)가 호출되는 부분
//					-> <>를 이용하여 타입 인자를 넘겨주지 않아도 컴파일러가 알아서 a,b의 타입을 보고 max<int>(a,b)로 인스턴스화 해줌
//					-> string도 마찬가지로 max(s, t) 호출시 max<std::string>(s,t)로 알아서 인스턴스화 됨
//		
//		*/
//	
//		return 0;
//	}

// 함수 템플릿 2, 함수 객체의 도입

//	#include <iostream>
//	#include <string>
//	
//	template <typename T>
//	class Vector
//	{
//	public:
//		// 생성자
//		Vector(int n = 1) : data(new T[n]), capacity(n), length(0) {}
//	
//		// 맨 뒤에 새로운 원소를 추가한다
//		void push_back(T s)
//		{
//			if (capacity <= length)
//			{
//				T* temp = new T[capacity * 2];
//				for (int i = 0; i < length; i++)
//				{
//					temp[i] = data[i];
//				}
//				delete[] data;
//				data = temp;
//				capacity *= 2;
//			}
//	
//			data[length] = s;
//			length++;
//		}
//	
//		// 임의의 위치에 원소에 접근한다
//		T operator[](int i) { return data[i]; }
//	
//		void remove(int x)
//		{
//			for (int i = x + 1; i < length; i++)
//			{
//				data[i - 1] = data[i];
//			}
//			length--;
//		}
//	
//		// 현재 벡터의 크기를 구한다
//		int size() { return length; }
//	
//		// i번째 원소와 j번째 원소 위치를 바꾼다
//		void swap(int i, int j)
//		{
//			T temp = data[i];
//			data[i] = data[j];
//			data[j] = temp;
//		}
//	
//		~Vector()
//		{
//			if (data)
//			{
//				delete[] data;
//			}
//		}
//	
//	private:
//		T* data;
//		int capacity;
//		int length;
//	};
//	
//	// 함수 객체 도입 전 bubble_sort : 오름차순 정렬만 가능하다
//	template <typename Cont>
//	void bubble_sort(Cont& cont)
//	{
//		for (int i = 0; i < cont.size(); i++)
//		{
//			for (int j = i + 1; j < cont.size(); j++)
//			{
//				if (cont[i] > cont[j])
//				{
//					cont.swap(i, j);
//				}
//			}
//		}
//	}
//	
//	// 함수 객체가 도입된 bubble_sort
//	template <typename Cont, typename Comp>
//	void bubble_sort(Cont& cont, Comp& comp)
//	{
//		for (int i = 0; i < cont.size(); i++)
//		{
//			for (int j = i + 1; j < cont.size(); j++)
//			{
//				if (!comp(cont[i], cont[j]))
//				{
//					cont.swap(i, j);
//				}
//			}
//		}
//	}
//	
//	struct Comp1
//	{
//		bool operator()(int a, int b) { return a > b; }
//	};
//	
//	struct Comp2
//	{
//		bool operator()(int a, int b) { return a < b; }
//	};
//	
//	int main()
//	{
//		Vector<int> int_vec;
//		int_vec.push_back(3);
//		int_vec.push_back(1);
//		int_vec.push_back(2);
//		int_vec.push_back(8);
//		int_vec.push_back(5);
//		int_vec.push_back(3);
//	
//		std::cout << "정렬 이전 ---- " << std::endl;
//		for (int i = 0; i < int_vec.size(); i++)
//		{
//			std::cout << int_vec[i] << " ";
//		}
//	
//		std::cout << std::endl << "정렬 이후 ---- " << std::endl;
//		bubble_sort(int_vec);
//		for (int i = 0; i < int_vec.size(); i++)
//		{
//			std::cout << int_vec[i] << " ";
//		}
//		std::cout << std::endl;
//	
//		std::cout << std::endl << "함수 객체 도입"  << std::endl;
//	
//		std::cout << "내림차순 정렬 이후 ---- " << std::endl;
//	
//		Comp1 comp1;
//		bubble_sort(int_vec, comp1);
//	
//		for (int i = 0; i < int_vec.size(); i++)
//		{
//			std::cout << int_vec[i] << " ";
//		}
//		std::cout << std::endl;
//		
//		std::cout << "오름차순 정렬 이후 ---- " << std::endl;
//	
//		Comp2 comp2;
//		bubble_sort(int_vec, comp2);
//	
//		for (int i = 0; i < int_vec.size(); i++)
//		{
//			std::cout << int_vec[i] << " ";
//		}
//		std::cout << std::endl;
//	
//	
//	
//		//	struct dummy {};
//		//	dummy a;
//		//	bubble_sort(a);	// 오류
//	
//		/*
//			output:
//			정렬 이전 ----
//			3 1 2 8 5 3
//			정렬 이후 ----
//			1 2 3 3 5 8
//			
//			함수 객체 도입
//			내림차순 정렬 이후 ----
//			8 5 3 3 2 1
//			오름차순 정렬 이후 ----
//			1 2 3 3 5 8
//		*/
//	
//		/*
//			- 함수 템플릿 2
//				- bubble_sort() 함수는 임의의 컨테이너 cont를 받아 정렬해주는 함수
//					- template <typename Cont>로 함수 템플릿을 선언, bubble_sort(int_vec) 호출시 bubble_sort<Vector<int>>(int_vec)으로 인스턴스화 됨
//					- 이 함수가 작동을 하려면 size(), swap(), operator[] 가 정의되어 있어야 함
//						-> 따라서 아무것도 없는 dummy 구조체를 만들어 함수 호출시 해당 함수나 연산자가 없으므로 오류가 발생함
//						-> 이러한 오류는 프로그램 실행시가 아니라 컴파일시에 발생함. 컴파일시에 템플릿 코드가 실제 코드로 변환되기 때문
//							-> 이렇게 컴파일 시에 모든 템플릿들이 인스턴스화 된다는 점을 이용한 프로그래밍 방식이 템플릿 메타 프로그래밍(template meta programming)임
//				- 위 코드에서는 오름차순으로만 정렬하고 내림차순으로는 정렬이 불가능
//					-> 해결방안 3가지
//						1) bubble_sort2()를 만들어 부등호 방향을 반대로 바꿈 -> C스타일
//						2) operator> 를 오버로딩 하여 원하는 방식으로 만듬 -> 가능
//						3) cont[i] 와 cont[j]의 비교를 >로 하지 말고 특정 함수에 넣어서 전달 -> 함수 객체의 도입으로 가능함
//			
//			- 함수 객체(Function Object - Functor)의 도입
//				- 위 3가지 해결방안 중 3번에 해당되는 문제를 해결하기 위한 방법
//				- 2번째 bubble_sort 함수를 보자
//					- template<typename Cont, typename Comp> : Comp 객체를 따로 템플릿 인자로 선언
//					- Comp 객체 -> if(!comp(cont[i], cont[j])) : 함수 호출처럼 사용됨. cont[i]와 cont[j]를 받아서 내부적으로 크기를 비교
//						-> !! comp는 함수가 아니라 객체이고, Comp 클래스에서 ()연산자를 오버로딩 한 것 !!
//							struct Comp1
//							{
//								bool operator()(int a, int b) { return a > b; }
//							};
//							
//							struct Comp2
//							{
//								bool operator()(int a, int b) { return a < b; }
//							};
//						-> 이처럼 함수는 아니지만 함수인 척을 하는 객체를 함수 객체(Function Object, 줄여서 Functor)라고 부름
//						-> 실제 <algorithm>의 sort() 함수도 비교클래스를 받는 버전과 받지 않는 버전 2가지가 존재함
//	
//				- 함수 포인터가 있는데 이게 왜 필요한가요?
//					- 클래스 자체에 여러가지 내부 state를 저장해서 비교 자체가 복잡한 경우에도 손쉽게 사용자가 원하는 방식으로 만들어 낼 수 있음
//					- 함수 포인터는 컴파일러가 최적화할 수 없지만 Functor는 operator()를 컴파일러가 인라인화 시켜 빠르게 작업을 수행함 -> 오버헤드가 그냥 없어져버림
//		*/
//	}

// 타입이 아닌 템플릿 인자

//	#include <iostream>
//	#include <array>
//	
//	template <typename T, int num>
//	T add_num(T t)
//	{
//		return t + num;
//	}
//	
//	// std::array<int, 5> 그 자체가 하나의 타입이므로 함수를 이렇게 만들어야 함
//	void print_array(const std::array<int, 5>& arr)
//	{
//		for (int i = 0; i < arr.size(); i++)
//		{
//			std::cout << arr[i] << " ";
//		}
//		std::cout << std::endl;
//	}
//	
//	// 물론 그냥 템플릿써도 됨
//	template<typename T>
//	void print_array(const T& arr)
//	{
//		for (int i = 0; i < arr.size(); i++)
//		{
//			std::cout << arr[i] << " ";
//		}
//		std::cout << std::endl;
//	}
//	
//	int main()
//	{
//		int x = 3;
//		std::cout << "x : " << add_num<int, 5>(x) << std::endl;
//		// add_num(x);	// E0304: 인수 목록이 일치하는 함수 템플릿 "add_num"의 인스턴스가 없습니다.
//	
//		/*
//			output:
//			x : 8
//		*/
//	
//		// 템플릿 특수화의 활용 std::array
//	
//		std::array<int, 5> arr = { 1, 2, 3, 4, 5 };
//		// 이는 int arr[5] = {1, 2, 3, 4, 5}; 와 동일함
//		std::array<int, 7> arr2 = { 1, 2, 3, 4, 5, 6, 7 };
//		std::array<int, 3> arr3 = { 1, 2, 3 };
//	
//		print_array(arr);
//		print_array(arr2);
//		print_array(arr3);
//	
//		/*
//			- 타입이 아닌 템플릿 인자(non-type template arguments)
//				- 템플릿의 인자로 타입만 올 수 있는것이 아님
//				- 위 코드를 보자
//					- template <typename T, int num> T add_num(T t) : template의 인자로 T를 받고 추가적으로 함수의 인자처럼 int num을 받고있음
//					- add_num<int, 5>(x) : T에 int, num에 5가 전달되어 컴파일시 아래의 함수가 생성됨
//	
//						int add_num(int t) { return t + 5; }
//	
//					- 이 경우 함수 호출시 반드시 템플릿 인자<>를 명시적으로 전달해주어야 함
//						-> 위 경우에서 <>로 명시하지 않으면 num에 뭐가 들어가는지 컴파일러 입장에선 알 길이 없음
//	
//				- 템플릿 인자로 전달할 수 있는 타입들을 아래와 같이 제한적임
//					- 정수 타입들(bool, char, int, long 등등). 당연히 float, double은 제외...였는데 C++ 20 부터 가능
//					- 포인터 타입
//					- enum 타입
//					- std::nullptr_t (널 포인터)
//					- C++ 20에서 이 제한이 더 완화됨 https://en.cppreference.com/w/cpp/language/template_parameters 를 참고
//	
//				- 템플릿 인자가 가장 많이 활용되는 예시 : 컴파일 타임에 값이 정해져야 하는 경우(배열의 크기 등)
//					-> 실제 STL의 std::array가 이를 활용함
//						-> 기존 C스타일 배열의 단점인 함수에 배열 전달시 배열의 크기에 대한 정보가 사라진다는 점을 보완해줌
//						-> std::array는 당연히 런타임에 동적으로 크기가 커지지 않고 컴파일시 스택에 메모리를 할당함
//						-> 때문에 std::array<int, 5> 같이 생성하면 그자체가 하나의 타입이 되므로 다양한 크기에 대한 함수를 만들어 주어야 함
//	
//							void print_array(const std::array<int, 5>& arr)
//	
//							-> 사실 그럴 필요 없고 이것도 템플릿 함수로 한번에 할 수 있음
//	
//								template<typename T>
//								void print_array(const T& arr) {}
//		*/
//	}

// 디폴트 템플릿 인자

#include <iostream>

template <typename T, int num = 5>
T add_num(T t)
{
	return t + num;
}

template <typename T, typename Comp = Compare<T>>
T Min(T a, T b)
{
	Comp comp;
	if (comp(a, b))
		return a;

	return b;
}

template <typename T>
struct Compare
{
	bool operator()(const T& a, const T& b) const { return a < b; }
};

int main()
{
	int x = 3;
	std::cout << "x : " << add_num(x) << std::endl;

	int a = 3, b = 5;
	std::cout << "Min " << a << " , " << b << " :: " << Min(a, b) << std::endl;

	std::string s1 = "abc", s2 = "def";
	std::cout << "Min " << s1 << " , " << s2 << " :: " << Min(s1, s2) << std::endl;

	/*
		output:
		x : 8
		Min 3 , 5 :: 3
		Min abc , def :: abc
	*/

	/*
		- 템플릿 디폴트 인자
			- 함수 디폴트 인자처럼 = (디폴트 값) 으로 선언
			- 첫번째 add_num의 경우 디폴트로 num에 5가 전달
				-> 별다른 인자 명시 없이 add_num<int, 5>(x)를 컴파일러가 알아서 추론하여 만듬
			- 두번째 Compare의 경우 굳이 Min<int, Compare<int>>(a, b) 이런 식으로 함수 객체를 명시해줄 필요 없어짐
				-> 알아서 타입에 맞게 디폴트인 Compare<T>가 Comp로 전달됨
	
	*/
}

// 추가: 템플릿 인자 타입 추측의 규칙 https://en.cppreference.com/w/cpp/language/template_argument_deduction