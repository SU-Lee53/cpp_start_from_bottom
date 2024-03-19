#include <iostream>

class MyString
{
public:
	MyString(char c);	// 문자 하나로 생성
	MyString(const char* str);	// 문자열로부터 생성
	MyString(const MyString& str);	// 복사 생성자
	~MyString() { delete[] string_content; }

	int length() const { return string_length; }	// 값을 읽기만 하므로 상수함수(const)로 정의 -> 내부 멤버 변수의 값을 바꾸지 않는다면 상수함수로 정의하는것이 좋음
	int capacity() const { return memory_capacity; }
	void print();
	void println();

	// assign : '='와 같은 역할
	MyString& assign(const MyString& str);
	MyString& assign(const char* str);

	// reserve : 할당할 문자열의 크기를 미리 예약해놓음
	void reserve(int size);

	// at : 기존의 []의 역할
	char at(int i) const;

	// insert : loc으로 받은 위치의 '앞'에 다른 문자열을 삽입
	MyString& insert(int loc, const MyString& str);
	MyString& insert(int loc, const char* str);
	MyString& insert(int loc, char c);

	// erase : loc으로 받은 위치의 앞에서부터 num개만큼 지움
	MyString& erase(int loc, int num);

	// find : find_from 에서 시작해서 가장 첫번째 str의 위치를 리턴, 없으면 -1 리턴
	int find(int find_from, MyString& str) const;
	int find(int find_from, const char* str) const;
	int find(int find_from, char c) const;

	// compare : 기존의 strcmp의 역할
	int compare(const MyString& str) const;

private:
	char* string_content;	// 문자열 데이터를 기리키는 포인터 -> 문자열 데이터의 크기가 바뀔 때, 메모리 헤제/할당을 할수있도록 하기 위해 포인터로 저장함
	int string_length;	// 문자열 길이 -> 문자열 길이는 활용도가 큰데 비해 매번 길이를 구하는것은 불필요함
	int memory_capacity;	// 메모리 할당량 -> 짧은 실제 데이터에 비해 너무 큰 메모리가 할당되는 비효율적인 경우를 막기 위해 별도로 저장

	// string_content에서 기존 C스타일 널 종료를 포함하지 않음. 대신 string_length를 이용하여 문자열의 끝부분을 체크할 수 있음
};

MyString::MyString(char c)
{
	string_content = new char[1];
	string_content[0] = c;
	string_length = 1;
	memory_capacity = string_length;
}

MyString::MyString(const char* str)
{
	string_length = strlen(str);
	string_content = new char[string_length];

	for (int i = 0; i != string_length; i++)
	{
		string_content[i] = str[i];
	}

	memory_capacity = string_length;
}

MyString::MyString(const MyString& str)
{
	string_length = str.string_length;
	string_content = new char[string_length];

	for (int i = 0; i != string_length; i++)
	{
		string_content[i] = str.string_content[i];
	}

	memory_capacity = string_length;
}

void MyString::print()
{
	for (int i = 0; i != string_length; i++)
	{
		std::cout << string_content[i];
	}
}

void MyString::println()
{
	for (int i = 0; i != string_length; i++)
	{
		std::cout << string_content[i];
	}
	std::cout << std::endl;
}

MyString& MyString::assign(const MyString& str)
{
	// 만약 지정하려는 문자열이 기존의 문자열보다 긴 경우 기존의 메모리 해제 후 재할당이 필요함 -> X
	// 기존 문자열의 메모리 할당량이 새로운 문자열의 길이보다 작은 경우에 재할당이 필요함
	if (str.string_length > memory_capacity)
	{
		delete[] string_content;
		string_content = new char[str.string_length]; 
		memory_capacity = str.string_length;
	}
	
	for (int i = 0; i != str.string_length; i++)
	{
		string_content[i] = str.string_content[i];

		/*
			str.string_length + 1 ~ string_length 까지는 초기화가 필요하지 않음. 아래의 예시를 보자

			ex)
			this ->	abcdefg
			str ->	hij
			기존의 문자열에서 efg 부분은 hij로 assign()이 되면 읽을일이 없기 때문에 초기화가 필요하지 않다는 의미
			저 efg 부분이 str.string_length + 1 ~ string_length 부분이다
		*/
	}
	
	string_length = str.string_length;

	return *this;

	
}

MyString& MyString::assign(const char* str)
{
	int str_length = strlen(str);
	if (str_length > memory_capacity)
	{
		delete[] string_content;
		string_content = new char[str_length];
		memory_capacity = str_length;
	}

	for (int i = 0; i != str_length; i++)
	{
		string_content[i] = str[i];
	}

	string_length = str_length;

	return *this;
}

void MyString::reserve(int size)
{
	// 만약 예약하려는 size가 할당된 memory_capacity보다 작다면 아무것도 안해도 됨. 어차피 size안에 기존 문자열을 담을수 없기때문
	if (size > memory_capacity)
	{
		char* prev_string_content = string_content;

		string_content = new char[size];
		memory_capacity = size; 
		
		for (int i = 0; i != string_length; i++)
		{
			string_content[i] = prev_string_content[i];
		}

		delete[] prev_string_content;
	}
	
}

char MyString::at(int i) const
{
	if (i >= string_length || i < 0)	// index out of bound를 막기 위함
		return NULL;
	else
		return string_content[i];
}

MyString& MyString::insert(int loc, const MyString& str)
{
	/*
		loc으로 받은 위치 앞에 문자열 삽입
		ex) "abc"에 insert(1,"d")를 하면 "adbc"가 됨
	*/

	// 범위를 넘어가면 수행 안함
	if (loc >= string_length || loc < 0) return *this;

	if (string_length + str.string_length > memory_capacity)
	{
		// 삽입된 후의 문자열의 길이가 할당된 메모리 크기보다 크다면 해제 후 재할당이 필요함
		//	memory_capacity = string_length + str.string_length;
		
		// memory_capacity가 한계일때 자잘한 insert가 반복된다면 계속 메모리 할당을 하므로 비효율적임
		// 그냥 한번에 현재 크기의 2배정도를 할당해버리는건 어떨까 -> 실제로 사용되는 기법

		if (memory_capacity * 2 > string_length + str.string_length)	// 새로 할당해야할 메모리의 크기(length + str.length)가 현재의 memory_capacity의 2배 이하라면
			memory_capacity *= 2;	// 그냥 기존의 2배만큼 늘려버리자
		else	// 그렇지 않다면 -> 삽입될 문자열이 매우 길어서 memory_capacity의 2배를 넘어버렸다면
			memory_capacity = string_length + str.string_length; // 2배 할당해도 모자르니까 그냥 필요한만큼 늘리자 -> 불필요한 공간 낭비를 막아줌


		char* prev_string_content = string_content;
		string_content = new char[memory_capacity];

		// 우선 삽입되는 위치 앞부분까지 복사한다
		int i;
		for (i = 0; i < loc; i++)
		{
			string_content[i] = prev_string_content[i];
		}

		// 이후 삽입할 문자열을 넣는다
		for (int j = 0; j != str.string_length; j++)
		{
			string_content[i + j] = str.string_content[j];
		}

		// 나머지 문자열을 넣는다
		for (i; i != string_length; i++)
		{
			string_content[i + str.string_length] = prev_string_content[i];
		}

		delete[] prev_string_content;

		string_length = string_length + str.string_length;
		return *this;
	}
	else
	{
		// 만약 이미 할당된 메모리가 삽입된 후에도 초과되지 않는다면 굳이 재할당 필요없이 뒷부분을 밀어버리고 삽입하면 됨
		// 원본에는 else 없이하지만 여기서는 else로 함 -> return되지 않는 분기가 있을 수 있기때문에 일반적으로 좋지 않다고 생각하지만 여기서는 분명하기 때문에 그냥 ㄱㄱ

		// 우선 삽입될 위치부터 문자열을 밀어버린다
		for (int i = string_length - 1; i >= loc; i--)
		{
			// 밀린 문자열도 원위치에 보존됨
			string_content[i + str.string_length] = string_content[i];
		}

		// 이후 문자 집어넣음
		for (int i = 0; i < str.string_length; i++)
		{
			string_content[i + loc] = str.string_content[i];
		}

		string_length += str.string_length;

		return *this;
	}

}

MyString& MyString::insert(int loc, const char* str)
{
	MyString temp = MyString(str);
	return insert(loc, temp);
}

MyString& MyString::insert(int loc, char c)
{
	MyString temp = MyString(c);
	return insert(loc, temp);
}

MyString& MyString::erase(int loc, int num)
{
	/*
		loc으로 받은 위치 부터 num만큼 삭제
		ex) "abcd"에 erase(1,2)를 하면 "ad"가 됨
	*/

	if (num < 0 || loc < 0 || loc > string_length || loc + num > string_length) return *this;

	// 지운다 == 앞으로 끌고와버린다 라고 생각하면 됨

	for (int i = loc + num; i < string_length; i++)
	{
		string_content[i - num] = string_content[i];
	}

	string_length -= num;

	return *this;
}

int MyString::find(int find_from, MyString& str) const
{
	int i, j;
	if (str.string_length == 0) return -1;

	for (i = find_from; i <= string_length - str.string_length; i++)
	{
		for (j = 0; j < str.string_length; j++)
		{
			if (string_content[i + j] != str.string_content[j]) break;
		}

		if (j == str.string_length) return i;
	}

	return -1;	// 찾지 못함
}

int MyString::find(int find_from, const char* str) const
{
	MyString temp = MyString(str);
	return find(find_from, temp);
}

int MyString::find(int find_from, char c) const
{
	MyString temp = MyString(c);
	return find(find_from, temp);
}

int MyString::compare(const MyString& str) const
{
	/*
		(*this) - (str)을 수행해서 1, 0, -1 로 그 결과를 리턴
		1 -> (*this) 가 사전식으로 더 뒤에 온다
		0 -> 두 문자열이 같다
		-1 -> (*this) 가 사전식으로 더 앞에 온다	
	*/

	// std::min -> 두 int 중에서 더 작은 수를 리턴, min/max는 iostream에 포함되어있음
	for (int i = 0; i < std::min(string_length, str.string_length); i++)
	{
		if (string_content[i] > str.string_content[i])
			return 1;
		else if (string_content[i] < str.string_content[i])
			return -1;
	}

	// 여기까지 왔는데 리턴이 안됬다면 짧은놈 기준으로 앞부분이 같다는 것
	// 이때 문자열의 길이가 같으면 두 문자열은 같은 문자열임

	if (string_length == str.string_length) return 0;
	else if (string_length > str.string_length) return 1;
	else return -1;
	// "abc" 와 "abcd" 중에서 "abc"가 사전순 먼저임


}

#include <string>
int main()
{
	MyString str1("very long string");
	MyString str2("<some string inserted between>");
	str1.reserve(30);

	std::cout << "Capacity : " << str1.capacity() << std::endl;
	std::cout << "String length : " << str1.length() << std::endl;
	str1.println();
	std::cout << std::endl;

	str1.insert(5, str2);
	std::cout << "Capacity : " << str1.capacity() << std::endl;
	std::cout << "String length : " << str1.length() << std::endl;
	str1.println();
	std::cout << std::endl;

	str1.erase(5, 30);
	std::cout << "Capacity : " << str1.capacity() << std::endl;
	std::cout << "String length : " << str1.length() << std::endl;
	str1.println();
	std::cout << std::endl;

	str1.assign("this is a very very long string");
	str1.println();

	std::cout << "Location of first <very> in string : " << str1.find(0, "very") << std::endl;
	std::cout << "Location of second <very> in string : " << str1.find(str1.find(0, "very") + 1, "very") << std::endl;
	std::cout << std::endl;

	str1.assign("abcde");
	str2.assign("abcde");

	str1.println();
	str2.println();
	std::cout << "str1 and str2 compare : " << str1.compare(str2) << std::endl;

}
