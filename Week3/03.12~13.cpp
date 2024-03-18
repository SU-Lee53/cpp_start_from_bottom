
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
#pragma warning (disable:4996)

class MyString
{
public:
	MyString(char c);
	MyString(const char* cstring);
	MyString(const MyString& s);

	~MyString();

	void Print() { std::cout << _string << std::endl; }

	int GetLength() const { return _length; }
	
	// src�� �̾����
	void Catch(MyString& src);

	// ���ڿ����� Ư�� ���ڿ��� �ִ��� ������ ��ȯ
	bool Find(const char* target);

	// ���ڿ� ��
	bool operator ==(const MyString& s);


	bool operator > (const MyString& s);
	char operator [](int index) { return _string[index]; }

private:

	char* _string;
	int _length;

};

MyString::MyString(char c)
{
	_length = 1;
	_string = new char[1];
	_string[0] = c;
}

MyString::MyString(const char* cstring)
{
	_length = strlen(cstring);
	_string = new char[_length + 1];
	strcpy(_string, cstring);
}

MyString::MyString(const MyString& s)
{
	_length = s.GetLength();
	_string = new char[_length + 1];
	strcpy(_string, s._string);
}

MyString::~MyString()
{
	delete[] _string;
}

void MyString::Catch(MyString& src)
{
	// tmp�� �̸� ���� ����. _string�� �߰��� allocation �ϱ����� �������ϱ� ����
	char* tmp = new char[GetLength() + src.GetLength() + 1];
	strcpy(tmp, _string);

	// _string ����
	delete[] _string;

	// ���ο� _string �Ҵ�
	_string = new char[GetLength() + src.GetLength() + 1];
	strcat(tmp, src._string);
	strcpy(_string, tmp);

	// ���� ������Ʈ
	_length += src.GetLength();

	// ���纻 ����
	delete[] tmp;
}

bool MyString::Find(const char* target)
{
	int tLength = strlen(target);
	for (int i = 0; i <= GetLength() - tLength; i++)
	{
		int counter = 0;
		for (int j = i; j < i + tLength; j++)
		{
			if (_string[j] == target[counter]) counter++;
			else break;
		}

		if (counter == tLength) return true;
	}

	return false;

}

bool MyString::operator==(const MyString& s)
{
	if (GetLength() != s.GetLength()) return false;

	int counter = 0;
	for (int i = 0; i < GetLength(); i++)
	{
		if (_string[i] == s._string[i]) counter++;
	}
	
	if (counter == GetLength()) return true;
	else return false;

}

bool MyString::operator>(const MyString& s)
{
	int range = GetLength() < s.GetLength() ? GetLength() : s.GetLength();	// ���� vs �� -> �� ���� ���̰� �񱳹���
	for (int i = 0; i < range; i++)
	{
		if (_string[i] < s._string[i])
			return true;
		else if (_string[i] > s._string[i])
			return false;
		else
			continue;
	}
}



int main()
{
	char tmp = 't';

	MyString s(tmp);
	s.Print();

	const char* tmp2 = "test";
	MyString s2(tmp2);
	s2.Print();

	const char* tmp3 = "string";
	MyString s3(tmp3);
	s3.Print();

	s3.Catch(s2);
	s3.Print();

	std::cout << s3[0] << std::endl;

	if (s3.Find("ringte"))
		std::cout << "found ringte" << std::endl;
	else
		std::cout << "not found" << std::endl;

	MyString s4("test");
	if(s2 == s4)
		std::cout << "equal" << std::endl;
	else
		std::cout << "not equal" << std::endl;

	if (s3 == s4)
		std::cout << "equal" << std::endl;
	else
		std::cout << "not equal" << std::endl;

	// s3 = stringtest, s2 = test -> s3�� ������ ������
	if (s3 > s2)
		std::cout << "s3 comes first" << std::endl;
	else
		std::cout << "s2 comes first" << std::endl;


}


