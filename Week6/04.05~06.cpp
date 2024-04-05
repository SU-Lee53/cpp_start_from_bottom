/*

	04.05 ~ 06 std::string, ���, �������̵�, protected

*/

// ǥ�� string Ŭ���� std::string

#include <iostream>
#include <string>
#include <tchar.h>

int main()
{
	//	std::string s = "abc";
	//	std::string t = "def";
	//	std::string s2 = s;
	//	
	//	std::cout << s << " �� ���� : " << s.length() << std::endl;
	//	std::cout << s << " �ڿ� " << t << " �� ���̸� : " << s + t << std::endl;
	//	
	//	if (s == s2)
	//		std::cout << s << " �� " << s2 << " �� ���� " << std::endl;
	//	if (s != t)
	//		std::cout << s << " �� " << t << " �� �ٸ��� " << std::endl;

	/*
		output
		abc �� ���� : 3
		abc �ڿ� def �� ���̸� : abcdef
		abc �� abc �� ����
		abc �� def �� �ٸ���
	*/


	/*
		- std::string
			- C++�� ���ڿ� Ŭ����.
			- �⺻������ <string> ����ȿ��� basic_string�� char_traits �� �����Ǿ�����
				- char_traits: �⺻���� ����/���ڿ� ������ ����
				- basic_string: �������̰� �پ��� ���ڿ� ���� ����� ����
				-> �⺻������ ��ó�� std::string�� �����ϸ� std::basic_string�� �����ǰ� ����ȿ� typedef�� �Ǿ�����
			- ��ó�� �⺻���� std::string�� std::basic_string<char>�� �����ϰ� �ٸ� ������ ���ڿ��� ������(�⺻ char�� ANSI)
				- std::wstring		->		std::basic_string<wchar_t>(�����ڵ�)
				- std::u8string		->		std::basic_string<char8_t>
				- std::u16string	->		std::basic_string<char16_t>
				- std::u32string	->		std::basic_string<char32_t>
				- ���� ���� ���ø����� �Ǿ��־� ��� ��� �Լ����� ������
				- ���� �غ��ϱ� TCHAR���� ���ڵ��� ����� ����
				- �߰������� C++�� �޸� �Ҵ����� PMR�� �̿��� std::pmr::string ���� ������ �̺κ��� �ϴ� �Ѿ
			- ������ strcmp, strlen, strcat ���� �̿��ؾ��ߴ� C�� ���ڿ��� �ٸ��� �⺻���� ��ɵ��� ��� �Լ��� ������ https://en.cppreference.com/w/cpp/string/basic_string
				- length(), insert(), erase(), replace() ����� �پ��� ��� �Լ����� �⺻ ������
				- Ư�� strcmp, strcat ���� ����� �����ڷ� �����ϴٴ� ���� ���� ��� �κ��̶�� ������(��, ��Һ� �Ѵ� �����ڷ� ����)
				- ��ü ��ɵ��� �Ŀ� STL �����Ҷ� cppreference�� �ĸ鼭 �Բ� ����
	*/

	// soen.kr�� ����� �پ��� string �����ڵ�(�̰� ���� ���ο� ǥ�ص鿡�� �� ���� �߰���)

	std::string s1("test");								// string(const char *s) �� ���� ���ڿ��κ��� �����ϴ� ��ȯ ������
	std::string s2(s1);									// string(const string& str, int pos = 0, int num = npos) ���� ������
	std::string s3;										// string() �⺻ ������
	std::string s4(32, 'S');							// string(size_t n, char c) c�� n�� ä��
	std::string s5("very nice day", 8);					// string(const cchar* s, size_t n) �� ���� ���ڿ��κ��� �����ϵ� n���� Ȯ��
	const char* str = "abcdefghijllmnopqrstuvwxyz";		
	std::string s6(str + 5, str + 10);					// template<It> string(It begin, It end) begin ~ end ������ ���ڷ� ������ ���ڿ� ����

	std::cout << "s1 = " << s1 << std::endl;	// s1 = test
	std::cout << "s2 = " << s2 << std::endl;	// s2 = test
	std::cout << "s3 = " << s3 << std::endl;	// s3 =
	std::cout << "s4 = " << s4 << std::endl;	// s4 = SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
	std::cout << "s5 = " << s5 << std::endl;	// s5 = very nic
	std::cout << "s6 = " << s6 << std::endl;	// s6 = fghij

		
		



	return 0;
}