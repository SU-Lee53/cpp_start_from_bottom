/*
	06.19 - <random>, <chrono>
*/

/*  C 스타일 난수 생성의 문제점  */
//	#include <stdio.h>
//	#include <stdlib.h>
//	#include <time.h>
//	
//	int main()
//	{
//		srand(time(NULL));
//	
//		for (int i = 0; i < 5; i++)
//		{
//			printf("난수 : %d \n", rand() % 100);
//		}
//		return 0;
//	
//		/*
//			- C 스타일 난수 생성의 문제점
//				- 기존의 C 에서는 <stdlib.h> 의 rand() 와 <time.h> 에서 제공하는 시간을 시드값로 하여 많이 사용함
//					- 참고로 time(NULL) 은 프로그램을 실행한 초를 리턴
//				- 그러나 이 방법에는 문제가 몇가지 존재함
//	
//					1) 진짜 난수가 아님
//						- 사실 컴퓨터는 진짜 난수를 만들지 못함
//						- 이때문에 의사 난수(Pseudo random number) 를 만들어 사용
//							- 어떠한 수열을 이용하여 난수처럼 보이지만 사실 난수가 아닌 수를 생성
//							- 시드값으로 넘겨준 값과 상관관계가 있을수 밖에 없음
//							- rand() 는 선형 합동 생성기 라는 알고리즘을 이용하는데 품질이 애초에 뛰어나지 못함 https://ko.wikipedia.org/wiki/%EC%84%A0%ED%98%95_%ED%95%A9%EB%8F%99_%EC%83%9D%EC%84%B1%EA%B8%B0
//	
//					2) 시드값이 너무 천천히 변함
//						- 시드값으로 프로그램을 실행한 초를 넘겨줌 -> 시드값이 1초마다 변경
//							-> 같은 시간대에 시작된 프로그램은 모두 같은 난수를 뱉음
//		
//		*/
//	}


#include <iostream>

struct s_a
{

};

class c_a
{

};

int main()
{
	c_a* a = new c_a{};
	c_a* b = a;



	s_a c{};
	s_a d = std::move(c);
	
	std::cout << &c << '\n';
	std::cout << &d << '\n';
}