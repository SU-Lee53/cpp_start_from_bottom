/*
	06.18 - <regex>
*/

/*  ���� ǥ���� Regular Expression  */
/*
	- ���� ǥ����
		- ���ڿ��� ������ ������ ǥ���ϴ� ������ ���� ���
		- ������ ��Ȳ���� �����ϰ� ���� ����
			- �־��� ���ڿ��� �־��� ��Ģ�� �´��� Ȯ���� ��
			- �־��� ���ڿ����� ���ϴ� ������ ���ڿ��� �˻��� ��
			- �־��� ���ڿ����� ���ϴ� ������ ���ڿ��� ġȯ�� ��

		- ���� ǥ���� ������ ���������� ������
			- �⺻���̰� ��ǥ���� ������ https://namu.wiki/w/%EC%A0%95%EA%B7%9C%20%ED%91%9C%ED%98%84%EC%8B%9D?from=Regex �� �� ����

		- C++ 11 ���� <regex> ���̺귯���� �̿��Ͽ� ���� ǥ������ ����� �� ����
*/

/*  <regex> �� Ȱ�� 1 - ��ü ���ڿ� ��Ī  */
//	/*
//		- Ư���� ���� �̸��� �־��� ������ �����ϴ��� Ȯ��
//	
//		- �Ʒ� �ڵ��� ��Ȳ
//			- ������ �����ϴ� ��Ȳ
//			- db-(�ð�)-log.txt �� ���� ���·� �� �ð� ���� �α� ������ ������
//				-> ���� ���ϵ��� �����ִ� �������� �츮�� ���ϴ� ��ũ ���ϵ鸸 ������ �о���̴� ���α׷��� ������� ��
//	
//		- ���� ǥ�������� �� �α������� ǥ���ϸ� �Ʒ��� ����
//			
//				db-\d*-log\.txt
//	
//			- \d* : ������ ������ ����
//			- \. : �׳� . �� ������ ���ڷ� �ؼ��ǹǷ� \ �� ����
//	
//	*/
//	#include <iostream>
//	#include <regex>
//	#include <vector>
//	
//	int main()
//	{
//		// ���� ���� ���ϵ�
//		std::vector<std::string> file_names = { "db-123-log.txt", "db-124-log.txt",
//												"not-db-log.txt", "db-12-log.txt",
//												"db-12-log.jpg" };
//	
//		std::regex re("db-\\d*-log\\.txt");
//		for (const auto& file_name : file_names)
//		{
//			std::cout << file_name << " : " << std::boolalpha << std::regex_match(file_name, re) << '\n';
//		}
//	
//		/*
//			- output :
//				db-123-log.txt : true
//				db-124-log.txt : true
//				not-db-log.txt : false
//				db-12-log.txt : true
//				db-12-log.jpg : false
//		*/
//	
//		/*
//			- ��ü ���ڿ� ��Ī
//				- �ڵ� ����
//					- std::regex re("db-\\d*-log\\.txt");
//						- ���� ǥ���� ��ü�� ������
//						- ���� ǥ���� ��ü�� ������ �� ǥ������ ����, ó���ϴ� ���� ���� Ư�� ���� �߰��� �� ����
//	
//							- ���� ����
//									static constexpr flag_type ECMAScript = regex_constants::ECMAScript;
//									static constexpr flag_type basic      = regex_constants::basic;			: �⺻ POSIX ����ǥ���� https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap09.html#tag_09_03
//									static constexpr flag_type extended   = regex_constants::extended;		: Ȯ��� POSIX ���� ǥ���� https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap09.html#tag_09_04
//									static constexpr flag_type awk        = regex_constants::awk;			: POSIX �� awk ����ǥ���� https://pubs.opengroup.org/onlinepubs/9699919799/utilities/awk.html#tag_20_06_13_04
//									static constexpr flag_type grep       = regex_constants::grep;			: POSIX �� grep ����ǥ����
//									static constexpr flag_type egrep      = regex_constants::egrep;			: �� grep �� -E �ɼ��� �߰��� ����
//	
//								-> MSVC ���� �̷��� �����ϰ� �⺻���� ECMAScript �� https://en.cppreference.com/w/cpp/regex/ecmascript
//	
//							- ���� ����
//									static constexpr flag_type icase      = regex_constants::icase;			: ��ҹ��� ������ ����
//									static constexpr flag_type nosubs     = regex_constants::nosubs;		: ���� ǥ���� () �� (?:) �� �ٲ۴ٴµ� �� �𸣰���
//									static constexpr flag_type optimize   = regex_constants::optimize;		: ���� ����ȭ (��ü ������ ���� ������)
//									static constexpr flag_type collate    = regex_constants::collate;		: [a-b] ���ڸ� ������ ����
//	
//								-> cppreference ������ C++ 17 ���� std::regex::multiline �� �߰��ȴٰ� ���������� MSVC�� �����Ƿ� skip
//	
//							- ���� Ư������ | �� ���ؼ� ������ �߰� ������ (��Ʈ����ũ ���)
//								- ex) grep ������ ����ϰ� ��ҹ��� ������ ���ְ�ʹٸ� 
//									-> std::regex re("db-\\d*-log\\.txt", std::regex::grep | std::regex::icase);
//	
//							- �� �ڼ��� ������ https://en.cppreference.com/w/cpp/regex/basic_regex/constants
//				
//	
//					- std::regex_match(file_name, re)
//						- ù��° ���ڷ� ���޵� ���ڿ��� �ι�° ���ڷ� ���޵� regex ��ü�� ������ ��Ī�Ǹ� true �� ����
//	
//		*/
//	}

/*  <regex> �� Ȱ�� 2 - �κ� ��Ī �̾Ƴ���  */
/*
	- �� ���� �ٸ��� ���� �Ϻκи� �̾Ƴ��� �����ϴ��� Ȯ��

	- �Ʒ� �ڵ��� ��Ȳ
		- ��ȭ��ȣ ����ǥ������ ������� ��
		- ��ȭ��ȣ�� ������ ��Ģ�� ����
			- (����)-(����)-(����) ��
			- �� ���ڸ��� �ݵ�� 3�ڸ��̰�, 0 �� 1 �θ� �̷��������
			- ��� �ڸ��� 3�ڸ� Ȥ�� 4�ڸ�
			- ������ �ڸ��� �ݵ�� 4�ڸ�

		- �� ��Ģ�� ���� �Ʒ��� ���� ����ǥ������ �������

				[01]{3}-\d{3,4}-\d{4}

			- [01] : 0 Ȥ�� 1
			- {3} : �ش� ������ ���ڰ� 3�� ��Ÿ�� �� �ִ�
			- ���� ���󰡸� �������� �ؼ�����

			-> �� �� ���ǿ� �����ϴ� ��ȭ��ȣ�� ��� �κи� �����س��� ���α׷��� ������� ��

		- ���� ǥ������ ĸ�� �׷��� ����Ͽ� ���α׷� �ۼ�
			-> () �� �Ϻκ��� ���θ� �ش� �κп� ��Ī�� ���ڿ��� �����
*/
#include <iostream>
#include <regex>
#include <vector>

int main()
{
	std::vector<std::string> phone_numbers = { "010-1234-5678", "010-123-4567",
											"011-1234-5567", "010-12345-6789",
											"123-4567-8901", "010-1234-567" };

	std::regex re("[01]{3}-(\\d{3,4})-\\d{4}");
	std::smatch match;
	for (const auto& number : phone_numbers)
	{
		std::cout << number << " : " << std::boolalpha << std::regex_match(number, re) << '\n';
		if (std::regex_match(number, match, re))
		{
			for (size_t i = 0; i < match.size(); i++)
			{
				std::cout << "Match : " << match[i].str() << std::endl;
			}
			std::cout << "---------------------------\n";
		}
	}
	
	/*
		- output :
			010-1234-5678 : true
			Match : 010-1234-5678
			Match : 1234
			---------------------------
			010-123-4567 : true
			Match : 010-123-4567
			Match : 123
			---------------------------
			011-1234-5567 : true
			Match : 011-1234-5567
			Match : 1234
			---------------------------
			010-12345-6789 : false
			123-4567-8901 : false
			010-1234-567 : false
	*/

	/*
		- �κ� ��Ī �̾Ƴ���
			- �ڵ� ����
				- std::smatch match;
					- ��Ī�� ���ڿ��� std::string ���·� ����
					- const char* �� �����ϰ� �ʹٸ� cmatch �� �̿��ϸ� ��

				- std::regex_match(number, match, re)
					- �ι�° ���ڷ� std::smatch Ȥ�� std::cmatch �� �����ϸ� ��Ī�� �κ��� ��������

				- std::cout << "Match : " << match[i].str() << std::endl;
					- ù��° ��Ī�� ��ü ���ڿ��� ��Ī�� ���̹Ƿ� match[0].str() ���� ��ȭ��ȣ ��ü�� ��
					- �ι�°�� () ���� ���ڿ��� ��Ī�Ǿ� match[1].str() �� ���ϰ��� �ϴ� ��� �κ��� ��
						-> �������� () �� �ִٸ� for ������ ���������� ����
	*/
}

