
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


