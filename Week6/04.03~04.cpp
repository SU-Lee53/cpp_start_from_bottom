
/*

	04.03 N차원 배열 프로젝트 - 배열 완성
	04.04 반복자 iterator

*/


/*
	- 본 2차원 배열 프로젝트의 아이디어 : 데이터가 트리처럼 존재하면서 단말 노드에만 실제 데이터가 있고 나머지 부모 노드들은 포인터임
		- x1개의 int* 배열안에 x2개의 int 배열 -> int arr[x1][x2]와 같은 효과를 낼 수 있음
			- 장점 : 매모리가 허용하는 한 크기가 매우 큰 배열을 생성할 수 있음
			- 단점 : x1 * x2 + x1 + 1 만큼의 큰 메모리를 사용함(기존에는 x1 * x2 만큼만 사용)
		- 2차원 이상의 배열은 어떻게? -> N차원 만큼의 포인터를 이용하지 말고 레벨을 따로 저장 -> Adress 구조체를 이용하여 관리
			-> 루트 노드(글에서는 top으로 표현)의 레벨이 0이고 아래로 갈수록 레벨 증가
			-> void* 하나면 전부 다중 포인터 구현 필요 없이표현 가능함
			-> 결론적으로 단말노드에만 실제 int값이 저장되고 나머지는 전부 Address 구조체의 배열임
		- operator[]의 오버로딩
			- Array&의 리턴 -> 결국 리턴받고자 하는 값은 실제 데이터 int인데 Array&를 리턴하면 안됨
			- int&의 리턴 -> N차원 배열이므로 arr[2][3]등의 여러개의 첨자를 이용하였을때 문제가 생김
			-> int의 Wrapper인 Int를 따로 도입하여 해결
 */

#include <iostream>

namespace MyArray 
{
	 class Array;
	 class Int;

	 class Array
	 {
		 struct Address;
		 class Iterator;

	 public:

		 Array(int _dim, int* array_size) : dim(_dim)
		 {
			 size = new int[dim];
			 for (int i = 0; i < dim; i++) size[i] = array_size[i];

			 top = new Address;
			 top->level = 0;

			 initialize_address(top);
		 }

		 Array(const Array& arr) : dim(arr.dim)
		 {
			 size = new int[arr.dim];
			 for (int i = 0; i < dim; i++) size[i] = arr.size[i];

			 top = new Address;
			 top->level = 0;

			 initialize_address(top);

			 copy_address(top, arr.top);
		 }

		 ~Array()
		 {
			 delete_address(top);
			 delete size;
		 }

		 void initialize_address(Address* current);	// address를 초기화. 재귀함수로 구성됨
		 void delete_address(Address* current);	// address 삭제. 
		 void copy_address(Address* dst, Address* src);

		 Int operator[](const int index);

		 // 반복자: 배열의 특정한 원소에 대한 포인터. 모든 원소들을 순차적으로 접근 할 수 있게 해줌
		 class Iterator
		 {
		 public:
			 Iterator(Array* arr, int* loc = nullptr) : arr(arr)
			 {
				 location = new int[arr->dim];
				 for (int i = 0; i != arr->dim; i++) location[i] = (loc != nullptr ? loc[i] : 0);
			 }

			 Iterator(const Iterator& itr) : arr(itr.arr)
			 {
				 location = new int[arr->dim];
				 for (int i = 0; i != arr->dim; i++) location[i] = itr.location[i];
			 }


			 // 전위 증가
			 Iterator& operator++()
			 {
				 if (location[0] >= arr->size[0]) return(*this);

				 bool carry = false;	// 받아올림이 있는지(다음 level로 넘어가는 받아올림)
				 int i = arr->dim - 1;

				 do
				 {
					 // 어차피 다시 돌아온다는 것은 carry가 true라는 의미이므로 ++을 해야함
					 location[i]++;
					 if (location[i] >= arr->size[i] && i >= 1)
					 {
						 // i가 0 일 경우 0으로 만들지 않는다 (begin과 중복되므로)
						 location[i] -= arr->size[i];
						 carry = true;
						 i--;
					 }
					 else
					 {
						 carry = false;
					 }
				 } while (i >= 0 && carry);

				 return (*this);
			 }

			 // 후위 증가
			 Iterator operator++(int)
			 {
				 Iterator itr(*this);
				 ++(*this);
				 return itr;
			 }

			 // * 연산자(역참조)
			 Int operator*();

			 bool operator!=(const Iterator& itr)
			 {
				 if (itr.arr->dim != arr->dim) return true;

				 for (int i = 0; i != arr->dim; i++)
				 {
					 if (itr.location[i] != location[i]) return true;
				 }

				 return false;
			 }

		 private:
			 int* location;
			 Array* arr;

			 friend Int;
		 };


		 Iterator begin()
		 {
			 int* arr = new int[dim];
			 for (int i = 0; i != dim; i++) arr[i] = 0;

			 Iterator temp(this, arr);
			 delete[] arr;

			 return temp;
		 }

		 Iterator end()
		 {
			 int* arr = new int[dim];
			 arr[0] = size[0];
			 for (int i = 1; i < dim; i++) arr[i] = 0;

			 Iterator temp(this, arr);
			 delete[] arr;

			 return temp;
		 }

	 private:
		 const int dim;	// 몇차원 배열인지 -> 한번 차원을 정하면 바꿀 수 없음
		 int* size;	// size[0] * size[1] * ... * size[dim - 1]짜리 배열

		 struct Address
		 {
			 int level;
			 // 맨 마지막 레벨(dim - 1) 은 데이터 배열을 기리키고, 그 위 상위 레벨에서는 다음 Address 배열을 가리킴
			 void* next;
		 };
		 Address* top;

		 friend Int;
	 };

	 void Array::initialize_address(Address* current)
	 {
		 // 트리를 DFS로 순회(전위 운행)하면서 초기화됨
		 if (!current) return;

		 if (current->level == dim - 1)	// 종료조건(현재 레벨이 dim - 1 이라면 주소가 아니라 이제 값이 들어가야 하므로 끝내야함)
		 {
			 current->next = new int[size[current->level]];
			 return;
		 }

		 current->next = new Address[size[current->level]];

		 for (int i = 0; i != size[current->level]; i++)	// 다음 단계로 넘어가는 과정
		 {
			 (static_cast<Address*>(current->next) + i)->level = current->level + 1;
			 initialize_address(static_cast<Address*>(current->next) + i);
		 }
	 }

	 void Array::delete_address(Address* current)
	 {
		 // 트리 노드 지우듯이 아래에서 위로 메모리를 소멸시켜야함. 마찬가지로 DFS로 재귀호출됨
		 for (int i = 0; current->level < dim - 1 && i < size[current->level]; i++)
		 {
			 delete_address(static_cast<Address*>(current->next) + i);
		 }

		 if (current->level == dim - 1)
		 {
			 delete[] static_cast<int*>(current->next);
		 }
		 else
		 {

			 delete[] static_cast<Address*>(current->next);
		 }
	 }

	 void Array::copy_address(Address* dst, Address* src)
	 {
		 if (dst->level == dim - 1)
		 {
			 for (int i = 0; i < size[dst->level]; i++)
				 static_cast<int*>(dst->next)[i] = static_cast<int*>(src->next)[i];
			 return;
		 }

		 for (int i = 0; i != size[dst->level]; i++)
		 {
			 Address* new_dst = static_cast<Address*>(dst->next);
			 Address* new_src = static_cast<Address*>(src->next);
			 copy_address(new_dst, new_src);
		 }
	 }

	 // operator[]의 오버로딩을 위해 int wrapper인 Int가 필요함
	 class Int
	 {
	 public:
		 // 디폴트 인자(default argument): 함수에 값을 전달하지 않으면 기본으로 이 값들이 전달되도록 함
		 Int(int index, int _level = 0, void* _data = NULL, Array* _array = NULL) : level(_level), data(_data), array(_array)
		 {
			 if (_level < 1 || index >= array->size[_level - 1])
			 {
				 data = NULL;
				 return;
			 }

			 if (level == array->dim)
			 {
				 // 이제 data에 우리의 int 자료형을 저장하도록 해야 함
				 data = static_cast<void*>((static_cast<int*>(static_cast<Array::Address*>(data)->next) + index));
			 }
			 else
			 {
				 // 그렇지 않을 경우 data에 다음 address를 넣어줌
				 data = static_cast<void*>(static_cast<Array::Address*>(static_cast<Array::Address*>(data)->next) + index);
			 }
		 }

		 Int(const Int& i) : data(i.data), level(i.level), array(i.array) {}

		 Int operator[](const int index)
		 {
			 if (!data) return 0;
			 return Int(index, level + 1, data, array);
		 }

		 // 복습) wrapper 클래스의 필수요소 -> 타입 변환 연산자
		 operator int()
		 {
			 if (data) return *static_cast<int*>(data);
			 return 0;
		 }

		 Int& operator=(const int& a)
		 {
			 if (data) *static_cast<int*>(data) = a;
			 return *this;
		 }

	 private:
		 void* data;
		 int level;	// 실제 int가 담겨있는 객체인지 혹은 중간 과정의 산물인지 구별하기 위함 -> 2차원 배열에서 arr[1]을 호출하면 실제 값이 아님
		 Array* array;	// 어떤 배열의 Int인지 가리킴
	 };

	 // 아래 오버로딩은 Int의 내부 정보를 이용하므로 Int의 정의가 선언되어야만 컴파일 가능함
	 // 따라서 전방선언만 있고 정의가 없는 Array 클래스 내부에서는 컴파일 될 수 없음
	 Int Array::operator[](const int index)
	 {
		 return Int(index, 1, static_cast<void*>(top), this);
	 }

	 Int Array::Iterator::operator*()
	 {
		 Int start = arr->operator[](location[0]);
		 for (int i = 1; i <= arr->dim - 1; i++)
		 {
			 start = start.operator[](location[i]);
		 }
		 return start;
	 }

}

int main()
{
	int size[] = { 2, 3 ,4 };
	MyArray::Array arr(3, size);

	MyArray::Array::Iterator itr = arr.begin();
	for (int i = 0; itr != arr.end(); itr++, i++) (*itr) = i;
	for (itr = arr.begin(); itr != arr.end(); itr++)
	{
		std::cout << *itr << std::endl;
	}


	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				arr[i][j][k] = (i + 1) * (j + 1) * (k + 1) + arr[i][j][k];
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				std::cout << i << " " << j << " " << k << " " << arr[i][j][k] << std::endl;
			}
		}
	}

	/*
		output

		0
		1
		2
		3
		4
		5
		6
		7
		8
		9
		10
		11
		12
		13
		14
		15
		16
		17
		18
		19
		20
		21
		22
		23
		0 0 0 1
		0 0 1 3
		0 0 2 5
		0 0 3 7
		0 1 0 6
		0 1 1 9
		0 1 2 12
		0 1 3 15
		0 2 0 11
		0 2 1 15
		0 2 2 19
		0 2 3 23
		1 0 0 14
		1 0 1 17
		1 0 2 20
		1 0 3 23
		1 1 0 20
		1 1 1 25
		1 1 2 30
		1 1 3 35
		1 2 0 26
		1 2 1 33
		1 2 2 40
		1 2 3 47
	
	
	*/


	return 0;
}