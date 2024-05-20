/*
	05.20 C++의 예외처리
*/

/*  예외  */
//	#include <iostream>
//	#include <vector>
//	
//	int main()
//	{
//		//	std::vector<int> v(3);
//		//	std::cout << v.at(4);	// 크기가 3인데 4번 인덱스 접근 -> 예외
//		//	
//		//	std::vector <int> v2(1'000'000'000'000);	// 과도하게 큰 메모리 할당 -> 예외
//	
//		/*
//	
//			- 예외
//				- 정상적인 상황에서 벗어난 모든 예외적인 상황
//				- 위 코드들이 예외의 간단한 예시로 문법상 틀린것이 없지만 오류가 발생함
//	
//		*/
//	}

/*  C 스타일 예외처리  */
//	#include <iostream>
//	
//	bool func2(int* addr);
//	bool func3(int* addr);
//	
//	bool func1(int* addr)
//	{
//		if (func2(addr))
//		{
//			// Do something
//		}
//		return false;
//	}
//	
//	bool func2(int* addr)
//	{
//		if (func3(addr))
//		{
//			// Do something
//		}
//		return false;
//	}
//	
//	bool func3(int* addr)
//	{
//		addr = (int*)malloc(1'000'000'000'000);
//		if (addr == NULL) return false;
//	
//		return true;
//	}
//	
//	int main()
//	{
//		/*  예외처리 : 간단하고 분명한 경우  */
//		//	{
//		//		char* c = (char*)malloc(1'000'000'000'000);
//		//		if (c == NULL)
//		//		{
//		//			printf("메모리 할당 오류");
//		//			return 0;
//		//		}
//		//	}
//	
//		/*  예외처리 : 복잡한 경우  */
//		{
//			int* addr = NULL;
//			if (func1(addr))
//			{
//				printf("성공");
//			}
//			else
//			{
//				printf("예외발생");
//			}
//		}
//	
//		/*
//			- C 에서의 예외처리
//				- 기본적으로 C에서는 예외 처리가 존재하지 않음 https://en.cppreference.com/w/c/keyword 진짜로
//					-> 나중에 추가된 <errno.h> 를 이용하면 일부 가능하긴 함 https://www.geeksforgeeks.org/error-handling-in-c/
//	
//				- C에서는 대부분의 라이브러리 함수들이 오류가 발생하면 -1 혹은 NULL을 반환함
//					- malloc 을 예시로 메모리 할당에 실패하면 NULL를 반환함
//	
//				- 이를 이용하여 작업 후 결과값을 확인하는 방식으로 예외처리를 함
//				- 그러나 함수가 깊어질수록 어디서 문제가 발생하였는지 알기 힘들다는 문제가 있음
//					- 예를 들어 위 코드의 복잡한 경우를 보면
//						-> func1 에서 func2 를 호출
//						-> func2 에서 func3 를 호출
//						-> func3 에서 메모리 할당 실패
//							-> 만약 func1 나 func2 에서도 예외가 발생할 수 있는 작업이 있다면 어디서 예외가 발생하는지 알기 어려움
//	
//				- 이런 문제점들 때문에 C++는 새로운 예외 처리 방식을 도입함
//		*/
//	
//		return 0;
//	}

/*  C++ 의 예외처리1 - 예외 발생 throw  */
//	#include <iostream>
//	
//	template <typename T>
//	class Vector
//	{
//	public:
//		Vector(size_t size) : _size(size)
//		{
//			_data = new T[_size];
//			for (int i = 0; i < _size; i++)
//			{
//				_data[i] = 3;
//			}
//		}
//	
//		const T& at(size_t index) const
//		{
//			if (index >= _size)
//			{
//				// 예외 발생
//				throw std::out_of_range("Vector 의 index 가 범위를 초과하였습니다.");
//			}
//			return _data[index];
//		}
//	
//		~Vector() { delete[] _data; }
//	
//	private:
//		T* _data;
//		size_t _size;
//	};
//	
//	int main()
//	{
//		Vector<int> v(3);
//		v.at(4);
//	
//		/*
//			- 예외 발생 throw
//				- 예외를 발생시키고 싶을때 사용하는 키워드
//				- 예외로 전달하고 싶은 객체를 던질 수 있음
//	
//				- C++ 표준에 이미 여러 종류의 예외 객체들이 존재하므로 이것들을 사용하는 것도 좋음
//					- 예외들은 <stdexcept> 헤더에 존재함 https://en.cppreference.com/w/cpp/header/stdexcept
//					- 기본적으로 아래의 예외 객체들이 있음
//						- logic_error
//							- invalid_argument
//							- domain_error
//							- length_error
//							- out_of_range
//						- runtime_error
//							- range_error
//							- overflow_error
//							- underflow_error
//	
//	
//	
//		*/
//	
//	}

/*  C++ 의 예외처리2 - 예외 처리 try-catch  */
//	#include <iostream>
//	#include <stdexcept>
//	
//	template <typename T>
//	class Vector
//	{
//	public:
//		Vector(size_t size) : _size(size)
//		{
//			_data = new T[_size];
//			for (int i = 0; i < _size; i++)
//			{
//				_data[i] = 3;
//			}
//		}
//	
//		const T& at(size_t index) const
//		{
//			if (index >= _size)
//			{
//				// 예외 발생
//				throw std::out_of_range("Vector 의 index 가 범위를 초과하였습니다.");
//			}
//			return _data[index];
//		}
//	
//		~Vector() { delete[] _data; }
//	
//	private:
//		T* _data;
//		size_t _size;
//	};
//	
//	int main()
//	{
//		Vector<int> v(3);
//	
//		int index, data = 0;
//		std::cin >> index;
//	
//		try
//		{
//			data = v.at(index);
//		}
//		catch (std::out_of_range& e)
//		{
//			std::cout << "예외 발생! " << e.what() << std::endl;
//		}
//	
//		// 예외가 발생하지 않는다면 3 출력
//		// 예외가 발생하면 원래 data에 들어가 있던 0이 출력
//		std::cout << "읽은 데이터 : " << data << std::endl;
//	
//	
//		/*
//			- input : 1
//			- output :
//				읽은 데이터 : 3
//	
//			- input : 3
//			- output :
//				예외 발생! Vector 의 index 가 범위를 초과하였습니다.
//				읽은 데이터 : 0
//		*/
//	
//		/*
//			- try-catch
//				- throw 로 던진 예외를 받아 처리하는 방법
//				- 기본적으로 다음과 같이 사용
//				
//					try { ... } catch (const std::exception& e) { ... }
//	
//				- try 블록에서는 예외가 발생할 수 있는 코드를 실행
//					-> 예외가 발생 : 즉시 가장 가까운 catch 문을 실행 + 블록 내부에서 생성된 모든 객체들의 소멸됨
//					-> 예외 발생 안함 : catch 문을 무시
//	
//				- catch 블록
//					- throw 가 던진 예외 중에서 () 안에 정의된 예외를 받음
//					- 알맞은 예외를 받았다면 {} 블록 내부의 코드를 실행함
//	
//			++ std::out_of_range
//				- 예외에 관한 내용을 저장하는 문자열 필드 하나만 존재함
//				- 멤버 함수인 what() 를 사용하면 예외에 관한 내용을 볼 수 있음
//					-> 때문에 위의 catch 블록 내부의 e.what() 에서 "Vector 의 index 가 범위를 초과하였습니다." 를 볼 수 있음
//	
//		*/
//	
//	
//	
//	}

/*  스택 풀기  */
//	#include <iostream>
//	#include <stdexcept>
//	
//	class Resource
//	{
//	public:
//		Resource(int id) : _id(id) {}
//		~Resource() { std::cout << "리소스 해제 : " << _id << std::endl; }
//	
//	private:
//		int _id;
//	};
//	
//	int func3()
//	{
//		Resource r(3);
//		throw std::runtime_error("Exception from 3!\n");
//		
//		// 예외 미발생의 경우
//		// return 0;
//	}
//	
//	int func2()
//	{
//		Resource r(2);
//		func3();
//		std::cout << "실행!" << std::endl;
//		return 0;
//	}
//	
//	int func1()
//	{
//		Resource r(1);
//		func2();
//		std::cout << "실행!" << std::endl;
//		return 0;
//	}
//	
//	int main()
//	{
//		Resource r(-1);
//		try
//		{
//			Resource r(0);
//			func1();
//		}
//		catch (std::exception& e)
//		{
//			std::cout << "Exception : " << e.what();
//		}
//	
//		/*
//			- 예외 발생 output:
//				리소스 해제 : 3
//				리소스 해제 : 2
//				리소스 해제 : 1
//				리소스 해제 : 0
//				Exception : Exception from 3!
//				리소스 해제 : -1
//		
//			- 예외 미발생 output:
//				리소스 해제 : 3
//				실행!
//				리소스 해제 : 2
//				실행!
//				리소스 해제 : 1
//				리소스 해제 : 0
//				리소스 해제 : -1
//		*/
//	
//		/*
//			- 스택 풀기 stack unwinding
//				- 스택 풀기
//					- 예외 객체가 생성되고 나면 가장 가까운 알맞은 catch를 찾기위해 호출 스택을 타고 내려가면서 try 문의 시작지점까지 이동함
//					- 호출스택을 타고 내려가면서 try 문의 시작 이후 파괴되지 않은 지역 객체들의 파괴자가 생성된 순서의 역순으로 호출됨
//						-> 이렇게 스택을 타고 catch로 점프 하면서 스택 상에 정의된 객체들을 소멸시키는 과정을 스택 풀기(stack unwinding) 이라고 함
//	
//				- 예제 코드
//					- func1() -> func2() -> func3() 순으로 실행되고 func3() 에서 예외 발생
//						-> 각 함수에서 1, 2, 3 지역 객체가 생성
//					- func3() 에서 예외가 발생하면 즉시 catch 문을 찾아 스택을 타고 역으로 이동
//						-> 현재 스택
//							[ func3() ]
//							[ func2() ]
//							[ func1() ]
//							[  main() ]
//					
//					- 알맞은 catch 문은 main()에 있으므로 func3() -> func2() -> func1() -> main() 순으로 제어 흐름이 이동함
//					- catch 문에 오면 try 이후 func3, 2, 1, main 의 객체들의 파괴자가 생성된 순의 반대로 호출됨
//	
//					- 만약 func3() 이 예외를 던지지 않는다면 func2, 1 의 "실행" 을 먼저 출력하고 함수가 종료될때 객체가 소멸됨
//	
//				- 주의사항
//					- 생성자/소멸자 에서 예외가 발생하면 소멸자가 호출되지 않음
//						-> 따라서 예외를 던지기 전에 할당된 자원이 있다면 catch 에서 직접 해제해야함
// 
//					- heap 에 동적할당된 객체는 소멸되지 않음
//		*/
//	}