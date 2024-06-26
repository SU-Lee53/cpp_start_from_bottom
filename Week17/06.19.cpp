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
//					1) 진짜 난수가 아님 (이건 어쩔수 없음)
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
//					3) 0 ~ 99 까지 균등하게 난수를 생성하지 않음
//						- 좋은 랜덤이라면 0 ~ 99 까지 나올 확률이 모두 동일해야 함
//						- 100으로 나눈 나머지로 0 ~ 99 의 난수 생성은 문제가 생길 수 있음
//							- 만약 rand() 가 생성하는 가장 큰 수인 RAND_MAX 가 128이라면
//								-> 1 이 나오려면 rand() 가 1 혹은 101 을 리턴해야함
//								-> 50 이 나오려면 rand() 가 50 을 리턴해야함
//									-> 1 과 50 이 나올 확률 차이가 2배
//									※ 실제 RAND_MAX 는 0x7fff (10진수는 32'767) -> 그럼 0 ~ 67 이랑 그 이상 ~ 99 의 확률이 다름
//	
//					4) 애초에 rand() 자체가 구림
//						- rand() 는 선형 합동 생성기 라는 알고리즘을 이용하는데 품질이 애초에 뛰어나지 못함
//						https://ko.wikipedia.org/wiki/%EC%84%A0%ED%98%95_%ED%95%A9%EB%8F%99_%EC%83%9D%EC%84%B1%EA%B8%B0
//	
//	
//				- C++ 에서 더 좋은 랜덤 난수 생성기를 제공하므로 이제 rand() 는 잊어버려도 좋음
//		
//		*/
//	}

/*  <random>  */
//	#include <iostream>
//	#include <iomanip>
//	#include <random>
//	#include <map>
//	#include <cstdlib>
//	#include <ctime>
//	#include <chrono>
//	
//	int main()
//	{
//		// 시드값을 얻기 위한 random_device 생성
//		std::random_device rd;
//	
//		// random_device 를 통해 난수 생성 엔진을 초기화
//		std::mt19937 gen(rd());
//	
//		// 0 ~ 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정리
//		std::uniform_int_distribution<int> dis(0, 99);
//	
//		for (int i = 0; i < 5; i++)
//		{
//			std::cout << "난수 : " << dis(gen) << std::endl;
//		}
//	
//		// 얼마나 균등한지 직접 보자 (0 ~ 99 사이의 난수를 10만개 -> 숫자당 1000 언저리 나오면 균등)
//	
//		auto start1 = std::chrono::high_resolution_clock::now();	// 시간도 재보자
//	
//		std::map<int, int> random_counter;
//		for (int i = 0; i < 100'000; i++)
//		{
//			++random_counter[dis(gen)];
//		}
//	
//		auto end1 = std::chrono::high_resolution_clock::now();
//		auto diff1 = end1 - start1;
//	
//		std::cout << "C++ random" << std::endl;
//		for (const auto& e : random_counter)
//		{
//			std::cout << std::setw(2) << e.first << ' ' 
//				<< std::string(e.second / 100, '*') << ' ' << e.second << std::endl;
//		}
//	
//		std::cout << std::endl;
//	
//	
//	
//		// 이번에는 C 스타일 rand() 가 얼마나 균등했는지 알아보자 (마찬가지로 0 ~ 99 사이로 생성)
//	
//		auto start2 = std::chrono::high_resolution_clock::now();
//	
//		srand(time(NULL));
//		std::map<int, int> crand_counter;
//		for (int i = 0; i < 100'000; i++)
//		{
//			++crand_counter[rand() % 100];
//		}
//	
//		auto end2 = std::chrono::high_resolution_clock::now();
//		auto diff2 = end2 - start2;
//	
//		std::cout << "C random" << std::endl;
//	
//		for (const auto& e : crand_counter)
//		{
//			std::cout << std::setw(2) << e.first << ' '
//				<< std::string(e.second / 100, '*') << ' ' << e.second << std::endl;
//		}
//	
//		std::cout << "C++ random time spent : " << std::chrono::duration_cast<std::chrono::milliseconds>(diff1).count() << "ms" << std::endl;
//		std::cout << "C random time spent : " << std::chrono::duration_cast<std::chrono::milliseconds>(diff2).count() << "ms" << std::endl;
//	
//		// 실측결과
//		/*
//		- 얼마나 균등할까
//			-> C 스타일도 생각보다 균등한데...
//
//			 C++ random							C random
//			 0 ********* 985					 0 ********* 979
//			 1 ********* 981					 1 ********* 995
//			 2 ********** 1025					 2 ********* 939
//			 3 ********* 982					 3 ********* 967
//			 4 ********* 945					 4 ********* 945
//			 5 ********* 974					 5 ********* 980
//			 6 ********* 985					 6 ********** 1039
//			 7 ********* 967					 7 ********* 996
//			 8 ********** 1010					 8 ********** 1042
//			 9 ********* 919					 9 ********** 1020
//			10 ********* 974					10 ********** 1027
//			11 ********** 1063					11 ********* 974
//			12 ********** 1048					12 ********* 924
//			13 ********** 1005					13 ********** 1027
//			14 ********* 990					14 ********** 1013
//			15 ********* 993					15 ********** 1051
//			16 ********** 1007					16 ********* 968
//			17 ********* 999					17 ********* 970
//			18 ********** 1013					18 ********** 1041
//			19 ********** 1049					19 ********** 1006
//			20 ********** 1005					20 ********* 997
//			21 ********** 1027					21 ********* 993
//			22 ********** 1008					22 ********** 1004
//			23 ********* 969					23 ********** 1009
//			24 ********* 958					24 ********** 1049
//			25 ********* 960					25 ********* 983
//			26 ********* 982					26 ********** 1018
//			27 ********** 1052					27 ********** 1016
//			28 ********* 989					28 ********** 1001
//			29 ********* 976					29 ********** 1038
//			30 ********* 982					30 ********** 1013
//			31 ********** 1076					31 ********* 990
//			32 ********* 981					32 ********** 1008
//			33 ********* 956					33 ********** 1015
//			34 ********* 972					34 ********** 1022
//			35 ********** 1033					35 ********* 988
//			36 ********** 1028					36 ********** 1028
//			37 ********** 1006					37 ********* 993
//			38 ********** 1003					38 ********** 1013
//			39 ********** 1014					39 ********** 1024
//			40 ********* 991					40 ********** 1021
//			41 ********* 961					41 ********** 1031
//			42 ********* 950					42 ********* 984
//			43 ********* 982					43 ********* 976
//			44 ********* 985					44 ********** 1015
//			45 ********** 1025					45 ********* 970
//			46 ********* 975					46 ********* 986
//			47 ********** 1064					47 ********* 962
//			48 ********* 999					48 ********** 1038
//			49 ********** 1042					49 ********** 1020
//			50 ********* 973					50 ********** 1066
//			51 ********* 992					51 ********* 975
//			52 ********** 1061					52 ********** 1022
//			53 ********** 1006					53 ********* 975
//			54 ********** 1023					54 ********* 950
//			55 ********** 1002					55 ********** 1015
//			56 ********* 917					56 ********* 935
//			57 ********* 971					57 ********* 947
//			58 ********* 976					58 ********** 1014
//			59 ********* 981					59 ********** 1002
//			60 ********* 983					60 ********** 1028
//			61 ********** 1013					61 ********** 1031
//			62 ********** 1068					62 ********** 1017
//			63 ********* 959					63 ********* 954
//			64 ********** 1002					64 ********** 1026
//			65 ********** 1039					65 ********* 976
//			66 ********** 1027					66 ********** 1033
//			67 ********* 990					67 ********** 1035
//			68 ********* 982					68 ********** 1045
//			69 ********** 1029					69 ********* 995
//			70 ********** 1037					70 ********* 973
//			71 ********** 1003					71 ********* 966
//			72 ********** 1012					72 ********* 985
//			73 ********* 992					73 ********* 999
//			74 ********** 1005					74 ********* 980
//			75 ********* 947					75 ********* 980
//			76 ********* 987					76 ********* 966
//			77 ********* 949					77 ********** 1015
//			78 ********** 1038					78 ********* 991
//			79 ********* 997					79 ********** 1012
//			80 ********* 957					80 ********* 985
//			81 ********** 1071					81 ********** 1004
//			82 ********** 1013					82 ********** 1022
//			83 ********* 971					83 ********* 950
//			84 ********** 1000					84 ********* 998
//			85 ********* 994					85 ********* 945
//			86 ********** 1031					86 ********* 980
//			87 ********** 1001					87 ********* 996
//			88 ********** 1007					88 ********** 1008
//			89 ********** 1038					89 ********** 1093
//			90 ********* 978					90 ********* 996
//			91 ********** 1049					91 ********** 1031
//			92 ********* 994					92 ********** 1015
//			93 ********** 1034					93 ********** 1026
//			94 ********** 1053					94 ********* 990
//			95 ********** 1003					95 ********** 1030
//			96 ********* 999					96 ********* 999
//			97 ********* 994					97 ********** 1014
//			98 ********* 996					98 ********* 940
//			99 ********* 991					99 ********* 962
//
//		- 시간측정
//			
//				C++									C
//		1트		C++ random time spent : 18ms		C random time spent : 16ms
//		2트		C++ random time spent : 19ms		C random time spent : 16ms
//		3트		C++ random time spent : 18ms		C random time spent : 17ms
//		4트		C++ random time spent : 18ms		C random time spent : 16ms
//		5트		C++ random time spent : 18ms		C random time spent : 31ms
//		6트		C++ random time spent : 27ms		C random time spent : 21ms
//		7트		C++ random time spent : 19ms		C random time spent : 20ms
//		8트		C++ random time spent : 18ms		C random time spent : 15ms
//		9트		C++ random time spent : 20ms		C random time spent : 16ms
//		10트	C++ random time spent : 20ms		C random time spent : 16ms
//
//			-> 의외로 별차이 안남....
//			-> 표본이 작아서 그런걸로 추정되고 커질수록 C 쪽 품질이 떨어질것으로 예상
//				-> 그래도 시간은 별 차이 안날듯
//	*/
//	
//		/*
//			- <random>
//				- C++ 11 부터 추가된 헤더로 의사 난수 생성을 돕는 라이브러리
//				- 위 코드 설명(테스트 부분 제외)
//	
//					- std::random_device rd;	
//						- 시드값을 제공하는 객체
//						- 기존 srand(time(NULL)) 보다 더 양질의 시드값을 만들어줌
//							-> 컴퓨터가 실행중에 마주치는 여러 무작위적인 요소들을 기반으로 하기 때문에 거의 진짜 난수에 가까움
//							-> OS 에서 제공해주며 작동방식 특성상 매우 느림
//								-> 초기화 할때 한번 쓰고 이후에는 난수열 엔진을 사용하는 것이 더 적합
//	
//					- std::mt19937 gen(rd());
//						- 난수 생성 엔진 중 하나인 mt19937 을 생성
//						- rd 에서 만든 난수를 시드값으로 하여 의사 난수를 만들어줌
//	
//					- std::uniform_int_distribution<int> dis(0, 99);
//						- 어디에서 수를 뽑아낼지 알려주는 분포 객체를 생성
//						- 위는 0 ~ 99 범위까지 균등한 확룰로 정수를 뽑는 dis 를 생성함
//	
//					- dis(gen)
//						- 균등 분포 dis 에 난수 엔진을 전달하여 균등분포에서 무작위로 샘플을 뽑아냄
//	
//	
//				- 현재 <random> 에서 제공하는 난수 엔진들은 아래와 같음
//	
//					- linear_congruential_engine
//					- mersenne_twister_engine
//					- subtract_with_carry_engine
//	
//				- 위의 엔진들을 이용해 미리 선언해둔 난수 생성기들이 있음
//	
//					- minstd_rand0
//					- minstd_rand
//						-> 위 2개는 linear_congruential_engine 을 이용함
//						-> C 의 rand() 와 같은 엔진임
//						-> 참고로 rand0 이 좀 더 오래된 알고리즘이고 그냥 rand 가 좀 더 최신
//	
//					- mt19937
//					- mt19937_64
//						-> 위 2개는 mersenne_twister_engine 를 이용하고 _64 는 64비트 범위 안의 난수를 만듬
//	
//					- ranlux24_base
//					- ranlux48_base
//						-> 위 2개는 subtract_with_carry_engine 를 이용함
//	
//					- ranlux24
//					- ranlus48
//						-> 위 2개는 subtract_with_carry_engine 에 std::discard_block_engine 이라는 어댑터를 이용함
//	
//					- knuth_b
//						-> std::shuffle_order_engine 을 이용하고 다른 엔진들에 붙여서 사용하는 어댑터중 하나임
//	
//					- 결국 가장 많이 사용되는건 mt19937 이므로 이것만 알아도 될듯
//	
//				- 현재 <random> 에서 제공하는 분포들은 여러가지임. 이는 아래에서 더 다룸
//		
//		*/
//	
//	}

/*  <random> 분포들의 예시  */
//	#include <iostream>
//	#include <iomanip>
//	#include <random>
//	#include <map>
//	
//	int main()
//	{
//		std::random_device rd;
//		std::mt19937 gen(rd());
//	
//		// 균등 분포 Uniform distrubutions
//		std::uniform_int_distribution<int> u_dist(0, 20);
//		std::map<int, int> uniform{};
//		for (int i = 0; i < 10000; i++)
//		{
//			++uniform[u_dist(gen)];
//		}
//	
//		std::cout << "std::uniform_int_distribution" << std::endl;
//		for (const auto& p : uniform)
//		{
//			std::cout << std::setw(2)
//				<< p.first << std::string(p.second / 100, '*')
//				<< ' ' << p.second << std::endl;
//		}
//		std::cout << std::endl;
//	
//		// 정규분포 Normal distrubutions
//		std::normal_distribution<double> n_dist(/* 평균 = */ 0, /* 표준편차 = */ 1);
//		std::map<int, int> normal{};
//		for (int i = 0; i < 10000; i++)
//		{
//			++normal[std::round(n_dist(gen))];
//		}
//	
//		std::cout << "std::normal_distribution" << std::endl;
//		for (const auto& p : normal)
//		{
//			std::cout << std::setw(2)
//				<< p.first << std::string(p.second / 100, '*')
//				<< ' ' << p.second << std::endl;
//		}
//		std::cout << std::endl;
//	
//		// 포아송 분포 Poisson distributions
//		std::poisson_distribution<int> p_dist(4); // 어떤 사건이 평균적으로 1분당 4번 일어난다면 n번 일어나는 각 경우는 얼마나 일어나는가? 라는뜻
//		std::map<int, int> poisson{};
//		for (int i = 0; i < 10000; i++)
//		{
//			++poisson[p_dist(gen)];
//		}
//	
//		std::cout << "std::poisson_distribution" << std::endl;
//		for (const auto& p : poisson)
//		{
//			std::cout << std::setw(2)
//				<< p.first << std::string(p.second / 100, '*')
//				<< ' ' << p.second << std::endl;
//		}
//		std::cout << std::endl;
//	
//		// 베르누이 분포 Bernoulli distribution
//		std::bernoulli_distribution b_dist(0.25);	// true 를 0.25 의 확률로 리턴, false 를 0.75 의 확률로 리턴
//		std::map<int, int> bernoulli{};
//		for (int i = 0; i < 10000; i++)
//		{
//			++bernoulli[b_dist(gen)];
//		}
//	
//		std::cout << std::boolalpha << "std::bernoulli_distribution" << std::endl;
//		for (const auto& p : bernoulli)
//		{
//			std::cout << std::setw(2) << p.first << ' '
//				<< std::string(p.second / 500, '*') << ' ' << p.second << '\n';
//		}
//		std::cout << std::endl;
//	
//		/*
//			- output :
//	
//				std::uniform_int_distribution
//				 0**** 482
//				 1**** 465
//				 2**** 463
//				 3**** 460
//				 4**** 489
//				 5**** 480
//				 6**** 491
//				 7***** 508
//				 8**** 469
//				 9**** 481
//				10**** 481
//				11**** 444
//				12**** 494
//				13**** 461
//				14***** 510
//				15**** 476
//				16**** 426
//				17**** 496
//				18**** 465
//				19***** 500
//				20**** 459
//				
//				std::normal_distribution
//				-4 1
//				-3 51
//				-2****** 609
//				-1************************ 2430
//				 0************************************* 3796
//				 1************************ 2403
//				 2****** 654
//				 3 54
//				 4 2
//				
//				std::poisson_distribution
//				 0* 183
//				 1******* 722
//				 2************** 1474
//				 3******************* 1914
//				 4******************** 2062
//				 5*************** 1553
//				 6********* 995
//				 7***** 591
//				 8** 297
//				 9* 133
//				10 40
//				11 23
//				12 10
//				13 1
//				14 2
//				
//				std::bernoulli_distribution
//				 0 ************** 7470
//				 1 ***** 2530
//		*/
//	
//		/*
//			- 통계학 수업이 아니므로 설명 생략
//				-> https://en.cppreference.com/w/cpp/header/random 가보면 세부적으로 더 다양한 분포들이 존재함
//		*/
//	}

/*  <chrono>  */
//	/*
//		- <chrono>
//			- <chrono> 는 크게 3가지 요소들이 존재함
//	
//				1) 현재 시간을 알려주는 system_clock (외에도 더있음)
//				2) 특정 시간을 알려주는 time_stamp
//				3) 시간의 간격을 나타내는 duration
//	
//			- 아래부터 위 요소들을 알아볼 예정
//	*/
//	
//	#include <iostream>
//	#include <iomanip>
//	#include <vector>
//	#include <random>
//	#include <chrono>
//	
//	int main()
//	{
//		std::random_device rd;
//		std::mt19937 gen(rd());
//		std::uniform_int_distribution<int> dist(0, 1000);
//		
//		for (int total = 1; total <= 1'000'000; total *= 10)
//		{
//			std::vector<int> random_numbers;
//			random_numbers.reserve(total);
//	
//			std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
//	
//			for (int i = 0; i < total; i++)
//			{
//				random_numbers.push_back(dist(gen));
//			}
//		
//	
//			std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
//	
//	#if _HAS_CXX17
//			// C++ 17 이후
//			std::chrono::duration diff = end - start;	// - 연산자의 리턴 타입을 constexpr 하는걸 C++ 17 부터 지원함
//	#else
//			// C++ 17 이전
//			auto diff = end - start;
//	#endif
//	
//			std::cout << std::setw(7) << total
//				<< "개 난수 생성 시 틱 횟수 : " << diff.count() 
//				<< ' ' << std::chrono::duration_cast<std::chrono::microseconds>(diff).count() << "us" << std::endl;
//		}
//	
//		/*
//			- output :
//					  1개 난수 생성 시 틱 횟수 : 4700 4us
//					 10개 난수 생성 시 틱 횟수 : 1300 1us
//					100개 난수 생성 시 틱 횟수 : 8900 8us
//				   1000개 난수 생성 시 틱 횟수 : 84100 84us
//				  10000개 난수 생성 시 틱 횟수 : 826000 826us
//				 100000개 난수 생성 시 틱 횟수 : 8836100 8836us
//				1000000개 난수 생성 시 틱 횟수 : 80207000 80207us
//		*/
//	
//		/*
//			- <chrono> 의 clock 들
//				- <chrono> 에서는 여러 종류의 시계들을 지원함. 그 목록은 아래와 같음
//					
//					- system_clock				-> 1970.01.01 부터 현재까지 발생한 틱의 횟수를 리턴 (Unix time 혹은 Epoch time)
//					- steady_clock				-> 컴퓨터 부팅부터 현재까지 발생한 틱의 횟수를 리턴
//					- high_resolution_clock		-> 0.00000001초(1억분의 1) 마다 틱이 움직이는 매우 정밀한 시계 
//												-> system_clock / steady_clock 중 무엇을 따르는지는 STL 구현체마다 다름(MSVC 는 steady_clock)
//					- utc_clock		
//					- tai_clock
//					- gps_clock
//					- file_clock
//						-> 아래 4개는 모두 C++ 20 에 도입된 시계로 이런게 있다 정도면 될듯
//	
//				- <chrono> 의 clock 은 실제 시계처럼 지금이 몇시인지 알려주지 않음
//					-> 대신 지정된 시간부터 몇번의 틱이 발생했는지 알려주는 time_point 객체를 리턴함
//	
//				- 틱 : 시계의 초침이 한번 움직이는 것 -> high_resolution_clock 제외하고 다 1초
//	
//				- 위 코드 설명
//					- std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
//						- <chrono> 는 객체들이 std::chrono 라는 네임스페이스에 정의되어있음
//							-> 이때문에 std::high_resolution_clock 이 아닌 std::chrono::high_resolution_clock 으로 해야함
//						- clock 객체들은 현재의 time_point 를 리턴하는 now() 라는 static 함수를 가지고 있음
//						- clock 마다 1초에 발생하는 틱의 횟수가 다르기 때문에 time_point 도 clock 을 템플릿 인자로 받음
//	
//					- auto diff = end - start;
//						- time_point 끼리 빼면 duration 을 리턴함
//						- duration 은 C++ 17 부터 constexpr 으로 연산 가능하므로 C++ 17 부터는 아래처럼 사용해도 됨
//							
//							std::chrono::duration diff = end - start;
//	
//					- diff.count() 
//						- duration 의 count() 는 해당 시간동안 몇번의 틱이 발생하였는지 알려줌
//	
//					- std::chrono::duration_cast<std::chrono::microseconds>(diff).count()
//						- 실제 시간으로 캐스팅 하는 duration_cast 를 이용해 원하는 duration 으로 캐스팅 가능함
//						- C++ 표준 명세의 duration 들은 아래와 같음
//	
//							- std::chrono::nanoseconds
//							- std::chrono::microseconds
//							- std::chrono::milliseconds
//							- std::chrono::seconds
//							- std::chrono::minutes
//							- std::chrono::hours
//							- std::chrono::days (C++ 20)
//							- std::chrono::weeks (C++ 20)
//							- std::chrono::months (C++ 20)
//							- std::chrono::years (C++ 20)
//		*/
//	
//	}

/*  <chrono> 를 이용하여 현재 시간을 날짜로 표기  */
//	#define _CRT_SECURE_NO_WARNINGS
//	#include <iostream>
//	#include <ctime>
//	#include <iomanip>
//	#include <chrono>
//	
//	namespace ch = std::chrono;
//	
//	int main()
//	{
//		auto now = ch::system_clock::now();
//		std::time_t t = ch::system_clock::to_time_t(now);
//		std::cout << "현재 시간은 : " << std::put_time(std::localtime(&t), "%F %T %z") << '\n';	// 현재 시간은 : 2024 - 06 - 22 04 : 42 : 45 + 0900
//	
//		// C++ 20 부터 날짜 관련 기능들이 추가됨
//		std::chrono::year_month_day ymd = std::chrono::floor<std::chrono::days>(now);
//		std::cout << "현재 시간은 : " << ymd.year() << " - "
//			<< ymd.month() << " - " << ymd.day() << '\n';	// 현재 시간은 : 2024 - Jun - 21 -> 한국 시간하고 동기화는 안되는듯
//	
//		/*
//			- C++ 에서 날짜의 표기
//				- 코드 설명
//					- std::time_t t = ch::system_clock::to_time_t(now);
//						- 날짜를 출력하기 위해 time_point 를 time_t 로 변환
//	
//					- std::put_time(std::localtime(&t), "%F %T %z")
//						- 현재 시간을 std::tm 으로 변환하기 위해 std::localtime 에 t 를 전달 https://en.cppreference.com/w/cpp/chrono/c/localtime
//							- std::tm 은 <ctime> 에서 날짜를 나타내는 struct
//						- std::put_time 을 이용해 우리가 원하는 형태의 문자열로 구성
//							- 인자들은 https://en.cppreference.com/w/cpp/io/manip/put_time 을 참고
//	
//								- %F : "%Y-%m-%d"
//								- %T : "%H:%M:%S"
//								- %z : UTC 로부터의 시차
//	
//		*/
//	}
//	