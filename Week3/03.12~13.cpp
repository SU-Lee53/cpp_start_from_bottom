
/*
	03.12,13 Mystring ���� ������
	03.14 Mystring ����� �ڵ� ���� Ž��
*/

/*
	- Mystring�� ���ԵǾ�� �ϴ°͵� :
		1. ����(char)�κ����� ���ڿ� ����, C���ڿ�(char*)�� ������ ����
		2. ���ڿ� ���̸� ���ϴ� �Լ�
		3. ���ڿ� �ڿ� �ٸ� ���ڿ� ���̱�
		4. ���ڿ� ���� ���ԵǾ� �ִ� ���ڿ� ���ϱ�
		5. ���ڿ��� ������ ��
		6. ���ڿ� ũ�� ��
*/

#include <iostream>

class MyString
{
public:
	MyString(char c);
	MyString(const char* cstring);
	MyString(const MyString& s);

	void Print() { std::cout << _string << std::endl; }

	int GetLength() { return _length; }
	MyString& StrCatch(MyString src, MyString dst);
	MyString& FindIn(MyString tg);
	bool StrCompare(MyString s1, MyString s2);

	bool operator >= (const MyString s);
	char operator [](int index);

private:

	char* _string;
	int _length = 0;

};

MyString::MyString(const char* cstring)
{
	_length = strlen(cstring);
	_string = (char*)malloc(_length);
	memcpy(_string, cstring, _length);
}

int main()
{
	const char* tmp = "test";

	MyString s(tmp);
	s.Print();

}


