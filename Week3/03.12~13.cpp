
/*
	03.12,13 Mystring 직접 만들자
	03.14 Mystring 모두의 코드 예제 탐구
*/

/*
	- Mystring에 포함되어야 하는것들 :
		1. 문자(char)로부터의 문자열 생성, C문자열(char*)로 부터의 생성
		2. 문자열 길이를 구하는 함수
		3. 문자열 뒤에 다른 문자열 붙이기
		4. 문자열 내에 포함되어 있는 문자열 구하기
		5. 문자열이 같은지 비교
		6. 문자열 크기 비교
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
	
	// src를 이어붙임
	void Catch(MyString& src);

	// 문자열에서 특정 문자열이 있는지 없는지 반환
	bool Find(const char* target);

	// 문자열 비교
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
	// tmp에 미리 원본 복사. _string을 추가로 allocation 하기전에 지워야하기 때문
	char* tmp = new char[GetLength() + src.GetLength() + 1];
	strcpy(tmp, _string);

	// _string 삭제
	delete[] _string;

	// 새로운 _string 할당
	_string = new char[GetLength() + src.GetLength() + 1];
	strcat(tmp, src._string);
	strcpy(_string, tmp);

	// 길이 업데이트
	_length += src.GetLength();

	// 복사본 삭제
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
	int range = GetLength() < s.GetLength() ? GetLength() : s.GetLength();	// 원본 vs 비교 -> 더 작은 길이가 비교범위
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

	// s3 = stringtest, s2 = test -> s3가 사전순 먼저임
	if (s3 > s2)
		std::cout << "s3 comes first" << std::endl;
	else
		std::cout << "s2 comes first" << std::endl;


}


