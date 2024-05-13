/*
	05.13 STL4 - ���ڿ�
*/

/*  basic_string  */
/*
	- basic_string
		- �������� ����ؿ� std::string �� ��� basic_string �̶�� Ŭ���� ���ø��� �ν��Ͻ�ȭ ������
			-> <string> ����� ���� ������ ���� �����

				using string = basic_string<char, char_traits<char>, allocator<char>>;

		- ���� basic_string �� <string> �ȿ��� ������ ���� ���ǵǾ�����(libc++)
			
			template <class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
			class basic_string;

			- basic_string �� CharT Ÿ���� ��ü���� �޸𸮿� ���������� �����ϰ� �������� ���ڿ� ������� �����ϴ� Ŭ����
			- ���� ���ڵ� ������ ���� string�� ���� ������ ����. �Ʒ��� ����
				- std::string -> std::basic_string<char>
				- std::wstring -> std::basic_string<wchar_t>	: wchar_t�� ũ��� ������� 2����Ʈ / ���н��� 4����Ʈ�� 
				- std::u8string -> std::basic_string<char8_t>	: C++ 20 ���� �߰��� string���� char8_t�� 1����Ʈ UTF-8 ������
				- std::u16string -> std::basic_string<char16_t>	: char16_t�� 2����Ʈ UTF-16 ����
				- std::u32string -> std::basic_string<char32_t> : char32_t�� 4����Ʈ UTF-32 ����

			- Traits�� �־��� CharT ���ڵ鿡 ���� �⺻���� ���ڿ� ������� �����س��� Ŭ������
				-> �⺻���� ���ڿ� ���� : ���ڿ� ��Һ�, ���� ���� ��..
				-> basic_string �� ���ڿ� ������� ���δ� Traits�� �⺻���� ���ڿ� ������ ���ǵ�
					-> �̸� ���� "���ڿ��� ��� �����ϴ���" �� "���ڿ����� ��� �����ϴ���" �� ���� ������ �и���ų �� ����
					-> ���ڴ� basic_string �� �ϰ� ���ڴ� Traits���� ��
					-> �̷ν� basic_string �� ��뿡 �־� �� �����ο� ���� ������ ������ �ʿ��� ��� Traits�� ���ݸ� �����ϸ� ��

			- ���� �⺻���� std::string�� ��� std::char_traits<char>�� �����

			- ����� MSVC�� basic_string �� <xstring> �ȿ��� ������ ���� ���ǵ�. char_traits�� <xstring>�� ����
				_EXPORT_STD template <class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>>
				class basic_string { // null-terminated transparent array of elements

*/

/*  Traits�� Ȱ��  */
//	#include <cctype>
//	#include <iostream>
//	#include <string>
//	
//	// ���ڿ� �񱳽� ���ڵ��� ������ ���� ������ �ϴ� char_traits
//	// ������ ASCII ���̺� �������� ���ڸ� ���ϹǷ� ���ڰ� ���ĺ����� ������ �� �������� ����
//	struct my_char_traits : public std::char_traits<char>
//	{
//		static int get_real_rank(char c)
//		{
//			// ���ڸ� ������ ��û ����߸���
//			if (isdigit(c))
//				return c + 256;
//			else
//				return c;
//		}
//	
//		static bool lt(char c1, char c2)
//		{
//			return get_real_rank(c1) < get_real_rank(c2);
//		}
//	
//		static int compare(const char* s1, const char* s2, size_t n)
//		{
//			while (n-- != 0)
//			{
//				if (get_real_rank(*s1) < get_real_rank(*s2)) return -1;
//				if (get_real_rank(*s1) > get_real_rank(*s2)) return 1;
//				++s1;
//				++s2;
//			}
//			return 0;
//		}
//	};
//	
//	int main()
//	{
//		std::basic_string<char, my_char_traits> my_s1 = "1a";
//		std::basic_string<char, my_char_traits> my_s2 = "a1";
//	
//		std::cout << "s1 : 1a" << std::endl;
//		std::cout << "s2 : a1" << std::endl;
//		std::cout << "s1 < s2 ?" << std::endl;
//	
//		std::cout << "������ �켱������ �� ���� ���ڿ� : " << std::boolalpha << (my_s1 < my_s2) << std::endl;
//	
//		std::string s1 = "1a";
//		std::string s2 = "a1";
//	
//		std::cout << "�Ϲ� ���ڿ� : " << std::boolalpha << (s1 < s2) << std::endl;
//	
//		/*
//			- output:
//				s1 : 1a
//				s2 : a1
//				s1 < s2 ?
//				������ �켱������ �� ���� ���ڿ� : false
//				�Ϲ� ���ڿ� : true
//		*/
//	
//		/*
//			- traits�� Ȱ��
//				- �⺻������ basic_string �� �� traits ���� char_traits �� �ִ� ��� ����Լ����� ������ Ŭ������ �ʿ���
//				- �̸� ���� �����ϰ� ������� �׳� char_traits�� ��ӹ޴� Ŭ������ ����� �ʿ��� �κе鸸 �ٽ� ����� ��
//					-> char_traits�� ����Լ����� https://en.cppreference.com/w/cpp/string/char_traits ����. �������� ������ ����
//	
//				- �� �ڵ忡���� my_char_traits �� char_traits�� lt, compare �Լ��� �����ε� �ϰ�����
//					-> ������ ������ ���ĺ����� ����߸��� ���� get_real_rank �Լ��� ����� �̿���
//					-> lt �Լ��� less_then�� ���ڷ� a < b �� �����Ͽ� ����� ���� https://en.cppreference.com/w/cpp/string/char_traits/cmp
//					-> compare �Լ��� ��� (const char* s1, const char* s2, size_t n) ���� ���ڸ� ����
//						-> s1 > s2 �� ��� ����� ����
//						-> s1 < s2 �� ��� ������ ����
//						-> s1 == s2 �� ��� 0�� ������
//						-> char* �� ��� ���ø� ���ڷ� ���� ���� ���ڵ� ������ ���� �޶���
//	
//					-> ��ó�� char_traits�� ��ӹ޾� �ణ�� ������ ���ָ� ���ϴ� ��� ���ڿ� ������ Ŀ������ �� ����
//		*/
//	}

/*  ª�� ���ڿ� ����ȭ Short String Optimization(SSO)  */
#include <iostream>
#include <string>

// �̿� ���� new �� ���� �Լ��� �����ϸ� ��� new �����ڸ� �����ε���
// � Ŭ������ new �����ڸ� �����ε� �Ϸ��� �ش� Ŭ������ ����Լ��� �����ؾ���
void* operator new(std::size_t count)
{
	std::cout << count << "bytes �Ҵ�" << std::endl;
	return malloc(count);
}

int main()
{
	std::cout << "s1 ���� --- " << std::endl;
	std::string s1 = "this is a pretty long sentence!!!";
	std::cout << "s1 ũ�� : " << sizeof(s1) << std::endl;

	std::cout << "s2 ���� --- " << std::endl;
	std::string s2 = "short sentence";
	std::cout << "s2 ũ�� : " << sizeof(s2) << std::endl;

	/*
		- MSVC�� �̿��� output
			s1 ���� ---
			16bytes �Ҵ�
			48bytes �Ҵ�
			s1 ũ�� : 40
			s2 ���� ---
			16bytes �Ҵ�
			s2 ũ�� : 40
		
		- libc++ STL�� clang �� �̿��� ������ ���
			s1 ���� ---
			48����Ʈ �Ҵ�
			s1 ũ�� : 24
			s2 ���� ---
			s2 ũ�� : 24

		- ����� �ڵ��� ���
			s1 ���� ---
			34 bytes �Ҵ�
			s1 ũ�� : 32
			s2 ���� ---
			s2 ũ�� : 32

		-> MSVC������ �� �ڵ带 SSO �Ͽ� �������� ����....
	*/

	/*
		- ª�� ���ڿ� ����ȭ Short String Optimization (SSO)
			- �Ϲ������� �޸𸮸� �Ҵ��ϴ��۾��� �ſ� ��
			- �׷��� ���ڿ��� ��� �� ���ڿ��� ��������� ���� �幰�� ���� ��κ� ª�� ���ڿ����� �����ǰ� �Ҹ��
			- �̸� �Ź� �޸𸮸� �Ҵ��ϸ鼭 �����ϰ� �Ҹ��ϴ� ���� �ſ� ��ȿ������
			- �׷��Ƿ� ª�� ������ ���ڿ��� ���� ������ ���� �޸𸮸� �Ҵ����� �ʰ� ��ü ��ü�� �����Ŵ -> �̰��� SSO�� ����

			- �� �ڵ忡���� SSO
				- MSVC������ SSO�� ���� �ʾ����Ƿ� pass
				- libc++�� ��� 
					-> s1�� new �����ڷ� 48����Ʈ�� �Ҵ���
					-> s2�� new �����ڷ� �޸� �Ҵ��� ���� �ʰ� ��ü ���ο� �ٷ� ����Ǿ� ������ ����� ��Ÿ���� ����
					-> �׷��� s2�� s1ó�� sizeof()�� ũ�⸦ Ȯ���غ��� ���� ����� ����
						-> �޸� ���� ũ��, ���ڿ� ����, ���ڿ��� ������ ������ ���� ������ ����
						-> �̿� ���� �޸� ��뷮�� �ణ ����Ͽ����� ���� ����� ������

			- MSVC�� SSO�� �ϱ� ��. �׷��� ���� s2���� �� ª�ƾ���. ������ ã�ƺ��� �� �ȳ���...
	*/
}