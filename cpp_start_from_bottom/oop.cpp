#include <iostream>



int main()
{
	/*	malloc/free, new/delete */
	
	//	int* p1 = (int*)malloc(sizeof(int));
	//	int* p2 = new int;
	//	
	//	*p1 = 5;
	//	*p2 = 10;
	//	
	//	std::cout << "p1 : "<< p1 << std::endl;
	//	std::cout << "p2 : "<< p2 << std::endl;
	//	std::cout << "value in p1 : " << *p1 << std::endl;
	//	std::cout << "value in p2 : " << *p2 << std::endl;
	//	
	//	free(p1);
	//	delete p2;
	//	
	//	int a = 0;
	//	delete &a;	// ���� �Ҵ���� ���� ������ delete�Ϸ��� �ϸ� ������ �߻��� -> heap�� �ƴ� ������ ��ȯ�� �� �� ���� ����


	/* new�� �̿��� �迭 �Ҵ� */

	int arr_size;
	std::cout << "array size : ";
	std::cin >> arr_size;
	int* list = new int[arr_size];
	for (int i = 0; i < arr_size; i++)
	{
		list[i] = i;
	}
	for (int i = 0; i < arr_size; i++)
	{
		std::cout << i << "th element of list : " << list[i] << std::endl;
	}
	delete list;
	
	int* list2 = (int*)malloc(sizeof(int) * arr_size);
	for (int i = 0; i < arr_size; i++)
	{
		list2[i] = i+2;
	}
	for (int i = 0; i < arr_size; i++)
	{
		std::cout << i << "th element of list : " << list2[i] << std::endl;
	}
	
	free(list2);
	
	int list3[5];
	for (int i = 0; i < arr_size; i++)
	{
		std::cin >> list3[i];
	}
	for (int i = 0; i < arr_size; i++)
	{
		std::cout << i << "th element of list : " << list2[3] << std::endl;
	}
	//	
	//	�� 3���� �迭���� ��������̳� �޸𸮻��� ��ġ�� �ٸ��� �޸𸮸� ���� ��� ������ ���·� �����


	return 0;


}



// new �� delete�� ������ -> �����ε��� �����ϳ�?

class test {};

void* operator new(size_t, test&);

void operator delete(void*, test&);

