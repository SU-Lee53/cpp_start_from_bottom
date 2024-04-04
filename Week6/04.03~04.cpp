
/*

	04.03 N���� �迭 ������Ʈ - �迭 �ϼ�
	04.04 �ݺ��� iterator

*/


/*
	- �� 2���� �迭 ������Ʈ�� ���̵�� : �����Ͱ� Ʈ��ó�� �����ϸ鼭 �ܸ� ��忡�� ���� �����Ͱ� �ְ� ������ �θ� ������ ��������
		- x1���� int* �迭�ȿ� x2���� int �迭 -> int arr[x1][x2]�� ���� ȿ���� �� �� ����
			- ���� : �Ÿ𸮰� ����ϴ� �� ũ�Ⱑ �ſ� ū �迭�� ������ �� ����
			- ���� : x1 * x2 + x1 + 1 ��ŭ�� ū �޸𸮸� �����(�������� x1 * x2 ��ŭ�� ���)
		- 2���� �̻��� �迭�� ���? -> N���� ��ŭ�� �����͸� �̿����� ���� ������ ���� ���� -> Adress ����ü�� �̿��Ͽ� ����
			-> ��Ʈ ���(�ۿ����� top���� ǥ��)�� ������ 0�̰� �Ʒ��� ������ ���� ����
			-> void* �ϳ��� ���� ���� ������ ���� �ʿ� ����ǥ�� ������
			-> ��������� �ܸ���忡�� ���� int���� ����ǰ� �������� ���� Address ����ü�� �迭��
		- operator[]�� �����ε�
			- Array&�� ���� -> �ᱹ ���Ϲް��� �ϴ� ���� ���� ������ int�ε� Array&�� �����ϸ� �ȵ�
			- int&�� ���� -> N���� �迭�̹Ƿ� arr[2][3]���� �������� ÷�ڸ� �̿��Ͽ����� ������ ����
			-> int�� Wrapper�� Int�� ���� �����Ͽ� �ذ�
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

		 void initialize_address(Address* current);	// address�� �ʱ�ȭ. ����Լ��� ������
		 void delete_address(Address* current);	// address ����. 
		 void copy_address(Address* dst, Address* src);

		 Int operator[](const int index);

		 // �ݺ���: �迭�� Ư���� ���ҿ� ���� ������. ��� ���ҵ��� ���������� ���� �� �� �ְ� ����
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


			 // ���� ����
			 Iterator& operator++()
			 {
				 if (location[0] >= arr->size[0]) return(*this);

				 bool carry = false;	// �޾ƿø��� �ִ���(���� level�� �Ѿ�� �޾ƿø�)
				 int i = arr->dim - 1;

				 do
				 {
					 // ������ �ٽ� ���ƿ´ٴ� ���� carry�� true��� �ǹ��̹Ƿ� ++�� �ؾ���
					 location[i]++;
					 if (location[i] >= arr->size[i] && i >= 1)
					 {
						 // i�� 0 �� ��� 0���� ������ �ʴ´� (begin�� �ߺ��ǹǷ�)
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

			 // ���� ����
			 Iterator operator++(int)
			 {
				 Iterator itr(*this);
				 ++(*this);
				 return itr;
			 }

			 // * ������(������)
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
		 const int dim;	// ������ �迭���� -> �ѹ� ������ ���ϸ� �ٲ� �� ����
		 int* size;	// size[0] * size[1] * ... * size[dim - 1]¥�� �迭

		 struct Address
		 {
			 int level;
			 // �� ������ ����(dim - 1) �� ������ �迭�� �⸮Ű��, �� �� ���� ���������� ���� Address �迭�� ����Ŵ
			 void* next;
		 };
		 Address* top;

		 friend Int;
	 };

	 void Array::initialize_address(Address* current)
	 {
		 // Ʈ���� DFS�� ��ȸ(���� ����)�ϸ鼭 �ʱ�ȭ��
		 if (!current) return;

		 if (current->level == dim - 1)	// ��������(���� ������ dim - 1 �̶�� �ּҰ� �ƴ϶� ���� ���� ���� �ϹǷ� ��������)
		 {
			 current->next = new int[size[current->level]];
			 return;
		 }

		 current->next = new Address[size[current->level]];

		 for (int i = 0; i != size[current->level]; i++)	// ���� �ܰ�� �Ѿ�� ����
		 {
			 (static_cast<Address*>(current->next) + i)->level = current->level + 1;
			 initialize_address(static_cast<Address*>(current->next) + i);
		 }
	 }

	 void Array::delete_address(Address* current)
	 {
		 // Ʈ�� ��� ������� �Ʒ����� ���� �޸𸮸� �Ҹ���Ѿ���. ���������� DFS�� ���ȣ���
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

	 // operator[]�� �����ε��� ���� int wrapper�� Int�� �ʿ���
	 class Int
	 {
	 public:
		 // ����Ʈ ����(default argument): �Լ��� ���� �������� ������ �⺻���� �� ������ ���޵ǵ��� ��
		 Int(int index, int _level = 0, void* _data = NULL, Array* _array = NULL) : level(_level), data(_data), array(_array)
		 {
			 if (_level < 1 || index >= array->size[_level - 1])
			 {
				 data = NULL;
				 return;
			 }

			 if (level == array->dim)
			 {
				 // ���� data�� �츮�� int �ڷ����� �����ϵ��� �ؾ� ��
				 data = static_cast<void*>((static_cast<int*>(static_cast<Array::Address*>(data)->next) + index));
			 }
			 else
			 {
				 // �׷��� ���� ��� data�� ���� address�� �־���
				 data = static_cast<void*>(static_cast<Array::Address*>(static_cast<Array::Address*>(data)->next) + index);
			 }
		 }

		 Int(const Int& i) : data(i.data), level(i.level), array(i.array) {}

		 Int operator[](const int index)
		 {
			 if (!data) return 0;
			 return Int(index, level + 1, data, array);
		 }

		 // ����) wrapper Ŭ������ �ʼ���� -> Ÿ�� ��ȯ ������
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
		 int level;	// ���� int�� ����ִ� ��ü���� Ȥ�� �߰� ������ �깰���� �����ϱ� ���� -> 2���� �迭���� arr[1]�� ȣ���ϸ� ���� ���� �ƴ�
		 Array* array;	// � �迭�� Int���� ����Ŵ
	 };

	 // �Ʒ� �����ε��� Int�� ���� ������ �̿��ϹǷ� Int�� ���ǰ� ����Ǿ�߸� ������ ������
	 // ���� ���漱�� �ְ� ���ǰ� ���� Array Ŭ���� ���ο����� ������ �� �� ����
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