#pragma once

// 너무 자주 사용되서 그냥 옮겨버림

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


