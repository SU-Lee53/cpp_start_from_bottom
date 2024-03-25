#include "MyString.h"
#include <iostream>
#include <string>

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
	// ���� �����Ϸ��� ���ڿ��� ������ ���ڿ����� �� ��� ������ �޸� ���� �� ���Ҵ��� �ʿ��� -> X
	// ���� ���ڿ��� �޸� �Ҵ緮�� ���ο� ���ڿ��� ���̺��� ���� ��쿡 ���Ҵ��� �ʿ���
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
			str.string_length + 1 ~ string_length ������ �ʱ�ȭ�� �ʿ����� ����. �Ʒ��� ���ø� ����

			ex)
			this ->	abcdefg
			str ->	hij
			������ ���ڿ����� efg �κ��� hij�� assign()�� �Ǹ� �������� ���� ������ �ʱ�ȭ�� �ʿ����� �ʴٴ� �ǹ�
			�� efg �κ��� str.string_length + 1 ~ string_length �κ��̴�
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
	// ���� �����Ϸ��� size�� �Ҵ�� memory_capacity���� �۴ٸ� �ƹ��͵� ���ص� ��. ������ size�ȿ� ���� ���ڿ��� ������ ���⶧��
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
	if (i >= string_length || i < 0)	// index out of bound�� ���� ����
		return NULL;
	else
		return string_content[i];
}

MyString& MyString::insert(int loc, const MyString& str)
{
	/*
		loc���� ���� ��ġ �տ� ���ڿ� ����
		ex) "abc"�� insert(1,"d")�� �ϸ� "adbc"�� ��
	*/

	// ������ �Ѿ�� ���� ����
	if (loc >= string_length || loc < 0) return *this;

	if (string_length + str.string_length > memory_capacity)
	{
		// ���Ե� ���� ���ڿ��� ���̰� �Ҵ�� �޸� ũ�⺸�� ũ�ٸ� ���� �� ���Ҵ��� �ʿ���
		//	memory_capacity = string_length + str.string_length;

		// memory_capacity�� �Ѱ��϶� ������ insert�� �ݺ��ȴٸ� ��� �޸� �Ҵ��� �ϹǷ� ��ȿ������
		// �׳� �ѹ��� ���� ũ���� 2�������� �Ҵ��ع����°� ��� -> ������ ���Ǵ� ���

		if (memory_capacity * 2 > string_length + str.string_length)	// ���� �Ҵ��ؾ��� �޸��� ũ��(length + str.length)�� ������ memory_capacity�� 2�� ���϶��
			memory_capacity *= 2;	// �׳� ������ 2�踸ŭ �÷�������
		else	// �׷��� �ʴٸ� -> ���Ե� ���ڿ��� �ſ� �� memory_capacity�� 2�踦 �Ѿ���ȴٸ�
			memory_capacity = string_length + str.string_length; // 2�� �Ҵ��ص� ���ڸ��ϱ� �׳� �ʿ��Ѹ�ŭ �ø��� -> ���ʿ��� ���� ���� ������


		char* prev_string_content = string_content;
		string_content = new char[memory_capacity];

		// �켱 ���ԵǴ� ��ġ �պκб��� �����Ѵ�
		int i;
		for (i = 0; i < loc; i++)
		{
			string_content[i] = prev_string_content[i];
		}

		// ���� ������ ���ڿ��� �ִ´�
		for (int j = 0; j != str.string_length; j++)
		{
			string_content[i + j] = str.string_content[j];
		}

		// ������ ���ڿ��� �ִ´�
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
		// ���� �̹� �Ҵ�� �޸𸮰� ���Ե� �Ŀ��� �ʰ����� �ʴ´ٸ� ���� ���Ҵ� �ʿ���� �޺κ��� �о������ �����ϸ� ��
		// �������� else ���������� ���⼭�� else�� �� -> return���� �ʴ� �бⰡ ���� �� �ֱ⶧���� �Ϲ������� ���� �ʴٰ� ���������� ���⼭�� �и��ϱ� ������ �׳� ����

		// �켱 ���Ե� ��ġ���� ���ڿ��� �о������
		for (int i = string_length - 1; i >= loc; i--)
		{
			// �и� ���ڿ��� ����ġ�� ������
			string_content[i + str.string_length] = string_content[i];
		}

		// ���� ���� �������
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
		loc���� ���� ��ġ ���� num��ŭ ����
		ex) "abcd"�� erase(1,2)�� �ϸ� "ad"�� ��
	*/

	if (num < 0 || loc < 0 || loc > string_length || loc + num > string_length) return *this;

	// ����� == ������ �����͹����� ��� �����ϸ� ��

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

	return -1;	// ã�� ����
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
		(*this) - (str)�� �����ؼ� 1, 0, -1 �� �� ����� ����
		1 -> (*this) �� ���������� �� �ڿ� �´�
		0 -> �� ���ڿ��� ����
		-1 -> (*this) �� ���������� �� �տ� �´�
	*/

	// std::min -> �� int �߿��� �� ���� ���� ����, min/max�� iostream�� ���ԵǾ�����
	for (int i = 0; i < std::min(string_length, str.string_length); i++)
	{
		if (string_content[i] > str.string_content[i])
			return 1;
		else if (string_content[i] < str.string_content[i])
			return -1;
	}

	// ������� �Դµ� ������ �ȉ�ٸ� ª���� �������� �պκ��� ���ٴ� ��
	// �̶� ���ڿ��� ���̰� ������ �� ���ڿ��� ���� ���ڿ���

	if (string_length == str.string_length) return 0;
	else if (string_length > str.string_length) return 1;
	else return -1;
	// "abc" �� "abcd" �߿��� "abc"�� ������ ������


}