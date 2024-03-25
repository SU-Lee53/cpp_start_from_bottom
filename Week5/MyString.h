#pragma once

// �ʹ� ���� ���Ǽ� �׳� �Űܹ���

class MyString
{
public:
	MyString(char c);	// ���� �ϳ��� ����
	MyString(const char* str);	// ���ڿ��κ��� ����
	MyString(const MyString& str);	// ���� ������
	~MyString() { delete[] string_content; }

	int length() const { return string_length; }	// ���� �б⸸ �ϹǷ� ����Լ�(const)�� ���� -> ���� ��� ������ ���� �ٲ��� �ʴ´ٸ� ����Լ��� �����ϴ°��� ����
	int capacity() const { return memory_capacity; }
	void print();
	void println();

	// assign : '='�� ���� ����
	MyString& assign(const MyString& str);
	MyString& assign(const char* str);

	// reserve : �Ҵ��� ���ڿ��� ũ�⸦ �̸� �����س���
	void reserve(int size);

	// at : ������ []�� ����
	char at(int i) const;

	// insert : loc���� ���� ��ġ�� '��'�� �ٸ� ���ڿ��� ����
	MyString& insert(int loc, const MyString& str);
	MyString& insert(int loc, const char* str);
	MyString& insert(int loc, char c);

	// erase : loc���� ���� ��ġ�� �տ������� num����ŭ ����
	MyString& erase(int loc, int num);

	// find : find_from ���� �����ؼ� ���� ù��° str�� ��ġ�� ����, ������ -1 ����
	int find(int find_from, MyString& str) const;
	int find(int find_from, const char* str) const;
	int find(int find_from, char c) const;

	// compare : ������ strcmp�� ����
	int compare(const MyString& str) const;

private:
	char* string_content;	// ���ڿ� �����͸� �⸮Ű�� ������ -> ���ڿ� �������� ũ�Ⱑ �ٲ� ��, �޸� ����/�Ҵ��� �Ҽ��ֵ��� �ϱ� ���� �����ͷ� ������
	int string_length;	// ���ڿ� ���� -> ���ڿ� ���̴� Ȱ�뵵�� ū�� ���� �Ź� ���̸� ���ϴ°��� ���ʿ���
	int memory_capacity;	// �޸� �Ҵ緮 -> ª�� ���� �����Ϳ� ���� �ʹ� ū �޸𸮰� �Ҵ�Ǵ� ��ȿ������ ��츦 ���� ���� ������ ����

	// string_content���� ���� C��Ÿ�� �� ���Ḧ �������� ����. ��� string_length�� �̿��Ͽ� ���ڿ��� ���κ��� üũ�� �� ����
};


