/*

	04.05 ~ 06 std::string, ���, �������̵�, protected

*/

// ǥ�� string Ŭ���� std::string
#include <iostream>
#include <string>

int main()
{
	std::string s = "abcde";
	std::cout << s << std::endl;
	/*
		output
		abcde
	*/

	/*
		- std::string
			- C++�� ���ڿ� Ŭ����.
			- �⺻������ <string> ����ȿ��� basic_string�� char_traits �� �����Ǿ�����
				- char_traits: �⺻���� ����/���ڿ� ������ ����
				- basic_string: �������̰� �پ��� ���ڿ� ���� ����� ����
				-> �⺻������ ��ó�� std::string�� �����ϸ� std::basic_string�� �����ǰ� ����ȿ� typedef�� �Ǿ�����
			- ��ó�� �⺻���� std::string�� std::basic_string<char>�� �����ϰ� �ٸ� ������ ���ڿ��� ������
				- std::wstring		->		std::basic_string<wchar_t>
				- 
	
	*/

	return 0;
}