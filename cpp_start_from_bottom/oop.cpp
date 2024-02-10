#include <iostream>


//int main()
//{
//	/*	malloc/free, new/delete */
//	
//	//	int* p1 = (int*)malloc(sizeof(int));
//	//	int* p2 = new int;
//	//	
//	//	*p1 = 5;
//	//	*p2 = 10;
//	//	
//	//	std::cout << "p1 : "<< p1 << std::endl;
//	//	std::cout << "p2 : "<< p2 << std::endl;
//	//	std::cout << "value in p1 : " << *p1 << std::endl;
//	//	std::cout << "value in p2 : " << *p2 << std::endl;
//	//	
//	//	free(p1);
//	//	delete p2;
//	//	
//	//	int a = 0;
//	//	delete &a;	// 동적 할당되지 않은 변수를 delete하려고 하면 오류가 발생함 -> heap이 아닌 공간을 반환할 수 는 없기 때문
//
//
//	/* new를 이용한 배열 할당 */
//
//	int arr_size;
//	std::cout << "array size : ";
//	std::cin >> arr_size;
//	int* list = new int[arr_size];
//	for (int i = 0; i < arr_size; i++)
//	{
//		list[i] = i;
//	}
//	for (int i = 0; i < arr_size; i++)
//	{
//		std::cout << i << "th element of list : " << list[i] << std::endl;
//	}
//	delete list;
//	
//	int* list2 = (int*)malloc(sizeof(int) * arr_size);
//	for (int i = 0; i < arr_size; i++)
//	{
//		list2[i] = i+2;
//	}
//	for (int i = 0; i < arr_size; i++)
//	{
//		std::cout << i << "th element of list : " << list2[i] << std::endl;
//	}
//	
//	free(list2);
//	
//	int list3[5];
//	for (int i = 0; i < arr_size; i++)
//	{
//		std::cin >> list3[i];
//	}
//	for (int i = 0; i < arr_size; i++)
//	{
//		std::cout << i << "th element of list : " << list2[3] << std::endl;
//	}
//	//
//	//	위 3가지 배열들은 구현방법이나 메모리상의 위치만 다를뿐 메모리를 찍어보면 모두 동일한 형태로 저장됨
//
//
//	return 0;
//
//
//}


/* 실습 - 마이펫 */ 

typedef struct Animal
{
	char name[30];	// 이름
	int age;		// 나이

	int health;		// 체력
	int food;		// 배부른 정도
	int clean;		// 깨끗한 정도
}Animal;

void play(Animal& animal)
{
	animal.health += 10;
	animal.food += 20;
	animal.clean += 30;
}

void show_stat(Animal& animal)
{
	std::cout << "name : " << animal.name << std::endl
		<< "age : " << animal.age << std::endl
		<< "health : " << animal.health << std::endl
		<< "food : " << animal.food << std::endl
		<< "clean : " << animal.clean << std::endl << std::endl;
}

void create_animal(Animal& animal)
{
	std::cout << "name : ";
	std::cin >> animal.name;

	std::cout << "age : ";
	std::cin >> animal.age;

	animal.health = 100;
	animal.food = 100;
	animal.clean = 100;
}

void one_day_pass(Animal& animal)
{
	animal.health -= 10;
	animal.food -= 30;
	animal.clean -= 20;
}

int main()
{
	Animal* list[10];
	int listSize = 0;

	while (true)
	{
		std::cout << "1. 동물 추가" << std::endl
			<< "2. 놀기" << std::endl
			<< "3. 상태 보기" << std::endl
			<< ">> " << std::endl;

		int input;
		std::cin >> input;

		switch (input)
		{
		case 1:
			list[listSize] = new Animal;
			create_animal(*list[listSize]);

			listSize++;
			break;

		case 2:
			int play_with;
			std::cout << "with who : ";
			std::cin >> play_with;

			if (play_with < listSize) play(*list[play_with]);
			break;

		case 3:
			for (int i = 0; i < listSize; i++) show_stat(*list[i]);
			break;

		default:
			break;
		}

		for (int i = 0; i < listSize; i++) one_day_pass(*list[i]);

	}



}













// new 와 delete는 연산자 -> 오버로딩이 가능하네?

class test {};

void* operator new(size_t size, test&);

void operator delete(void*, test&);
