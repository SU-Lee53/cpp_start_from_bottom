/*
	06.19 - <random>, <chrono>
*/

/*  C ��Ÿ�� ���� ������ ������  */
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
//			printf("���� : %d \n", rand() % 100);
//		}
//		return 0;
//	
//		/*
//			- C ��Ÿ�� ���� ������ ������
//				- ������ C ������ <stdlib.h> �� rand() �� <time.h> ���� �����ϴ� �ð��� �õ尪�� �Ͽ� ���� �����
//					- ����� time(NULL) �� ���α׷��� ������ �ʸ� ����
//				- �׷��� �� ������� ������ ��� ������
//	
//					1) ��¥ ������ �ƴ� (�̰� ��¿�� ����)
//						- ��� ��ǻ�ʹ� ��¥ ������ ������ ����
//						- �̶����� �ǻ� ����(Pseudo random number) �� ����� ���
//							- ��� ������ �̿��Ͽ� ����ó�� �������� ��� ������ �ƴ� ���� ����
//							- �õ尪���� �Ѱ��� ���� ������谡 ������ �ۿ� ����
//							- rand() �� ���� �յ� ������ ��� �˰����� �̿��ϴµ� ǰ���� ���ʿ� �پ�� ���� https://ko.wikipedia.org/wiki/%EC%84%A0%ED%98%95_%ED%95%A9%EB%8F%99_%EC%83%9D%EC%84%B1%EA%B8%B0
//	
//					2) �õ尪�� �ʹ� õõ�� ����
//						- �õ尪���� ���α׷��� ������ �ʸ� �Ѱ��� -> �õ尪�� 1�ʸ��� ����
//							-> ���� �ð��뿡 ���۵� ���α׷��� ��� ���� ������ ����
//	
//					3) 0 ~ 99 ���� �յ��ϰ� ������ �������� ����
//						- ���� �����̶�� 0 ~ 99 ���� ���� Ȯ���� ��� �����ؾ� ��
//						- 100���� ���� �������� 0 ~ 99 �� ���� ������ ������ ���� �� ����
//							- ���� rand() �� �����ϴ� ���� ū ���� RAND_MAX �� 128�̶��
//								-> 1 �� �������� rand() �� 1 Ȥ�� 101 �� �����ؾ���
//								-> 50 �� �������� rand() �� 50 �� �����ؾ���
//									-> 1 �� 50 �� ���� Ȯ�� ���̰� 2��
//									�� ���� RAND_MAX �� 0x7fff (10������ 32'767) -> �׷� 0 ~ 67 �̶� �� �̻� ~ 99 �� Ȯ���� �ٸ�
//	
//					4) ���ʿ� rand() ��ü�� ����
//						- rand() �� ���� �յ� ������ ��� �˰����� �̿��ϴµ� ǰ���� ���ʿ� �پ�� ����
//						https://ko.wikipedia.org/wiki/%EC%84%A0%ED%98%95_%ED%95%A9%EB%8F%99_%EC%83%9D%EC%84%B1%EA%B8%B0
//	
//	
//				- C++ ���� �� ���� ���� ���� �����⸦ �����ϹǷ� ���� rand() �� �ؾ������ ����
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
//		// �õ尪�� ��� ���� random_device ����
//		std::random_device rd;
//	
//		// random_device �� ���� ���� ���� ������ �ʱ�ȭ
//		std::mt19937 gen(rd());
//	
//		// 0 ~ 99 ���� �յ��ϰ� ��Ÿ���� �������� �����ϱ� ���� �յ� ���� ����
//		std::uniform_int_distribution<int> dis(0, 99);
//	
//		for (int i = 0; i < 5; i++)
//		{
//			std::cout << "���� : " << dis(gen) << std::endl;
//		}
//	
//		// �󸶳� �յ����� ���� ���� (0 ~ 99 ������ ������ 10���� -> ���ڴ� 1000 ������ ������ �յ�)
//	
//		auto start1 = std::chrono::high_resolution_clock::now();	// �ð��� �纸��
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
//		// �̹����� C ��Ÿ�� rand() �� �󸶳� �յ��ߴ��� �˾ƺ��� (���������� 0 ~ 99 ���̷� ����)
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
//		// �������
//		/*
//		- �󸶳� �յ��ұ�
//			-> C ��Ÿ�ϵ� �������� �յ��ѵ�...
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
//		- �ð�����
//			
//				C++									C
//		1Ʈ		C++ random time spent : 18ms		C random time spent : 16ms
//		2Ʈ		C++ random time spent : 19ms		C random time spent : 16ms
//		3Ʈ		C++ random time spent : 18ms		C random time spent : 17ms
//		4Ʈ		C++ random time spent : 18ms		C random time spent : 16ms
//		5Ʈ		C++ random time spent : 18ms		C random time spent : 31ms
//		6Ʈ		C++ random time spent : 27ms		C random time spent : 21ms
//		7Ʈ		C++ random time spent : 19ms		C random time spent : 20ms
//		8Ʈ		C++ random time spent : 18ms		C random time spent : 15ms
//		9Ʈ		C++ random time spent : 20ms		C random time spent : 16ms
//		10Ʈ	C++ random time spent : 20ms		C random time spent : 16ms
//
//			-> �ǿܷ� ������ �ȳ�....
//			-> ǥ���� �۾Ƽ� �׷��ɷ� �����ǰ� Ŀ������ C �� ǰ���� ������������ ����
//				-> �׷��� �ð��� �� ���� �ȳ���
//	*/
//	
//		/*
//			- <random>
//				- C++ 11 ���� �߰��� ����� �ǻ� ���� ������ ���� ���̺귯��
//				- �� �ڵ� ����(�׽�Ʈ �κ� ����)
//	
//					- std::random_device rd;	
//						- �õ尪�� �����ϴ� ��ü
//						- ���� srand(time(NULL)) ���� �� ������ �õ尪�� �������
//							-> ��ǻ�Ͱ� �����߿� ����ġ�� ���� ���������� ��ҵ��� ������� �ϱ� ������ ���� ��¥ ������ �����
//							-> OS ���� �������ָ� �۵���� Ư���� �ſ� ����
//								-> �ʱ�ȭ �Ҷ� �ѹ� ���� ���Ŀ��� ������ ������ ����ϴ� ���� �� ����
//	
//					- std::mt19937 gen(rd());
//						- ���� ���� ���� �� �ϳ��� mt19937 �� ����
//						- rd ���� ���� ������ �õ尪���� �Ͽ� �ǻ� ������ �������
//	
//					- std::uniform_int_distribution<int> dis(0, 99);
//						- ��𿡼� ���� �̾Ƴ��� �˷��ִ� ���� ��ü�� ����
//						- ���� 0 ~ 99 �������� �յ��� Ȯ��� ������ �̴� dis �� ������
//	
//					- dis(gen)
//						- �յ� ���� dis �� ���� ������ �����Ͽ� �յ�������� �������� ������ �̾Ƴ�
//	
//	
//				- ���� <random> ���� �����ϴ� ���� �������� �Ʒ��� ����
//	
//					- linear_congruential_engine
//					- mersenne_twister_engine
//					- subtract_with_carry_engine
//	
//				- ���� �������� �̿��� �̸� �����ص� ���� ��������� ����
//	
//					- minstd_rand0
//					- minstd_rand
//						-> �� 2���� linear_congruential_engine �� �̿���
//						-> C �� rand() �� ���� ������
//						-> ����� rand0 �� �� �� ������ �˰����̰� �׳� rand �� �� �� �ֽ�
//	
//					- mt19937
//					- mt19937_64
//						-> �� 2���� mersenne_twister_engine �� �̿��ϰ� _64 �� 64��Ʈ ���� ���� ������ ����
//	
//					- ranlux24_base
//					- ranlux48_base
//						-> �� 2���� subtract_with_carry_engine �� �̿���
//	
//					- ranlux24
//					- ranlus48
//						-> �� 2���� subtract_with_carry_engine �� std::discard_block_engine �̶�� ����͸� �̿���
//	
//					- knuth_b
//						-> std::shuffle_order_engine �� �̿��ϰ� �ٸ� �����鿡 �ٿ��� ����ϴ� ������� �ϳ���
//	
//					- �ᱹ ���� ���� ���Ǵ°� mt19937 �̹Ƿ� �̰͸� �˾Ƶ� �ɵ�
//	
//				- ���� <random> ���� �����ϴ� �������� ����������. �̴� �Ʒ����� �� �ٷ�
//		
//		*/
//	
//	}

/*  <random> �������� ����  */
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
//		// �յ� ���� Uniform distrubutions
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
//		// ���Ժ��� Normal distrubutions
//		std::normal_distribution<double> n_dist(/* ��� = */ 0, /* ǥ������ = */ 1);
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
//		// ���Ƽ� ���� Poisson distributions
//		std::poisson_distribution<int> p_dist(4); // � ����� ��������� 1�д� 4�� �Ͼ�ٸ� n�� �Ͼ�� �� ���� �󸶳� �Ͼ�°�? ��¶�
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
//		// �������� ���� Bernoulli distribution
//		std::bernoulli_distribution b_dist(0.25);	// true �� 0.25 �� Ȯ���� ����, false �� 0.75 �� Ȯ���� ����
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
//			- ����� ������ �ƴϹǷ� ���� ����
//				-> https://en.cppreference.com/w/cpp/header/random ������ ���������� �� �پ��� �������� ������
//		*/
//	}

/*  <chrono>  */
//	/*
//		- <chrono>
//			- <chrono> �� ũ�� 3���� ��ҵ��� ������
//	
//				1) ���� �ð��� �˷��ִ� system_clock (�ܿ��� ������)
//				2) Ư�� �ð��� �˷��ִ� time_stamp
//				3) �ð��� ������ ��Ÿ���� duration
//	
//			- �Ʒ����� �� ��ҵ��� �˾ƺ� ����
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
//			// C++ 17 ����
//			std::chrono::duration diff = end - start;	// - �������� ���� Ÿ���� constexpr �ϴ°� C++ 17 ���� ������
//	#else
//			// C++ 17 ����
//			auto diff = end - start;
//	#endif
//	
//			std::cout << std::setw(7) << total
//				<< "�� ���� ���� �� ƽ Ƚ�� : " << diff.count() 
//				<< ' ' << std::chrono::duration_cast<std::chrono::microseconds>(diff).count() << "us" << std::endl;
//		}
//	
//		/*
//			- output :
//					  1�� ���� ���� �� ƽ Ƚ�� : 4700 4us
//					 10�� ���� ���� �� ƽ Ƚ�� : 1300 1us
//					100�� ���� ���� �� ƽ Ƚ�� : 8900 8us
//				   1000�� ���� ���� �� ƽ Ƚ�� : 84100 84us
//				  10000�� ���� ���� �� ƽ Ƚ�� : 826000 826us
//				 100000�� ���� ���� �� ƽ Ƚ�� : 8836100 8836us
//				1000000�� ���� ���� �� ƽ Ƚ�� : 80207000 80207us
//		*/
//	
//		/*
//			- <chrono> �� clock ��
//				- <chrono> ������ ���� ������ �ð���� ������. �� ����� �Ʒ��� ����
//					
//					- system_clock				-> 1970.01.01 ���� ������� �߻��� ƽ�� Ƚ���� ���� (Unix time Ȥ�� Epoch time)
//					- steady_clock				-> ��ǻ�� ���ú��� ������� �߻��� ƽ�� Ƚ���� ����
//					- high_resolution_clock		-> 0.00000001��(1����� 1) ���� ƽ�� �����̴� �ſ� ������ �ð� 
//												-> system_clock / steady_clock �� ������ ���������� STL ����ü���� �ٸ�(MSVC �� steady_clock)
//					- utc_clock		
//					- tai_clock
//					- gps_clock
//					- file_clock
//						-> �Ʒ� 4���� ��� C++ 20 �� ���Ե� �ð�� �̷��� �ִ� ������ �ɵ�
//	
//				- <chrono> �� clock �� ���� �ð�ó�� ������ ������� �˷����� ����
//					-> ��� ������ �ð����� ����� ƽ�� �߻��ߴ��� �˷��ִ� time_point ��ü�� ������
//	
//				- ƽ : �ð��� ��ħ�� �ѹ� �����̴� �� -> high_resolution_clock �����ϰ� �� 1��
//	
//				- �� �ڵ� ����
//					- std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
//						- <chrono> �� ��ü���� std::chrono ��� ���ӽ����̽��� ���ǵǾ�����
//							-> �̶����� std::high_resolution_clock �� �ƴ� std::chrono::high_resolution_clock ���� �ؾ���
//						- clock ��ü���� ������ time_point �� �����ϴ� now() ��� static �Լ��� ������ ����
//						- clock ���� 1�ʿ� �߻��ϴ� ƽ�� Ƚ���� �ٸ��� ������ time_point �� clock �� ���ø� ���ڷ� ����
//	
//					- auto diff = end - start;
//						- time_point ���� ���� duration �� ������
//						- duration �� C++ 17 ���� constexpr ���� ���� �����ϹǷ� C++ 17 ���ʹ� �Ʒ�ó�� ����ص� ��
//							
//							std::chrono::duration diff = end - start;
//	
//					- diff.count() 
//						- duration �� count() �� �ش� �ð����� ����� ƽ�� �߻��Ͽ����� �˷���
//	
//					- std::chrono::duration_cast<std::chrono::microseconds>(diff).count()
//						- ���� �ð����� ĳ���� �ϴ� duration_cast �� �̿��� ���ϴ� duration ���� ĳ���� ������
//						- C++ ǥ�� ���� duration ���� �Ʒ��� ����
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

/*  <chrono> �� �̿��Ͽ� ���� �ð��� ��¥�� ǥ��  */
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
//		std::cout << "���� �ð��� : " << std::put_time(std::localtime(&t), "%F %T %z") << '\n';	// ���� �ð��� : 2024 - 06 - 22 04 : 42 : 45 + 0900
//	
//		// C++ 20 ���� ��¥ ���� ��ɵ��� �߰���
//		std::chrono::year_month_day ymd = std::chrono::floor<std::chrono::days>(now);
//		std::cout << "���� �ð��� : " << ymd.year() << " - "
//			<< ymd.month() << " - " << ymd.day() << '\n';	// ���� �ð��� : 2024 - Jun - 21 -> �ѱ� �ð��ϰ� ����ȭ�� �ȵǴµ�
//	
//		/*
//			- C++ ���� ��¥�� ǥ��
//				- �ڵ� ����
//					- std::time_t t = ch::system_clock::to_time_t(now);
//						- ��¥�� ����ϱ� ���� time_point �� time_t �� ��ȯ
//	
//					- std::put_time(std::localtime(&t), "%F %T %z")
//						- ���� �ð��� std::tm ���� ��ȯ�ϱ� ���� std::localtime �� t �� ���� https://en.cppreference.com/w/cpp/chrono/c/localtime
//							- std::tm �� <ctime> ���� ��¥�� ��Ÿ���� struct
//						- std::put_time �� �̿��� �츮�� ���ϴ� ������ ���ڿ��� ����
//							- ���ڵ��� https://en.cppreference.com/w/cpp/io/manip/put_time �� ����
//	
//								- %F : "%Y-%m-%d"
//								- %T : "%H:%M:%S"
//								- %z : UTC �κ����� ����
//	
//		*/
//	}
//	