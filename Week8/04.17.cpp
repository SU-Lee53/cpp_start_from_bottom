
/*
	04.17 C++ ����� ���̺귯�� istream, ostream
*/

// !!!!!!! �Ʒ� ������ ���� MSVC �����̰� �ٸ� STL ����ü���� �ٸ����� ���� !!!!!!!

// C++ ����� ���̺귯���� ����, ios_base, ios

/*
	- C++ ����� ���̺귯���� ����

							[ios_base]
								|
								|
							  [ios]
							   / \
							  /   \
							 /	   \
							/		\
					  [istream]	  [ostream]
						|	|		|	|
						|	|		|	|
						|   [iostream]	|
						|		|		|
					[ifstream]	|   [ofstream]
								|
							[fstream]

				�� �� �׸��� cppreference �� �׸� (https://en.cppreference.com/w/cpp/io)�� �ణ �ٸ�. cppreference�� �� �ֽ��ΰ����� ����
					
		- ���� �׸����� ��Ÿ�� ����� ���̺귯���� ������ �Ʒ��� ����� �ڵ��� ����
			- ios_base : C++�� ��� ����� Ŭ������ ��� Ŭ����. ���� ���� �����ʰ� ��Ʈ���� ����� ���� ���� �����͸� ó��(�Ǽ����� ���е�, ������ ���� ǥ�� ���� ��)
			- ios : ������ ��Ʈ�� ���۸� �ʱ�ȭ(��Ʈ�� ����: �����͸� �������ų� �޾Ƶ��̱� ���� �ӽ÷� �����ϴ� ��), ���� ����� �۾��� ���¸� ó��
		
		- istream ���ʹ� ������ �ܶ����� ����

*/

// istream Ŭ����
#include <iostream>
#include <string>

int main()
{
	// istream Ŭ����

	//	{
	//		std::string s;
	//		while (true)
	//		{
	//			std::cin >> s;
	//			std::cout << "word : " << s << std::endl;
	//		}
	//	
	//		/*
	//			output:
	//			this is a long sentence
	//			word : this
	//			word : is
	//			word : a
	//			word : long
	//			word : sentence
	//			ABC DEF GHI
	//			word : ABC
	//			word : DEF
	//			word : GHI
	//		*/
	//	
	//		/*
	//			- istream Ŭ����
	//				- ������ �Է��� �����ϴ� Ŭ����: std::cin >> ;
	//					- operator>> : istream Ŭ������ ���ǵ� ������
	//						- istream ��������� ��� operator>>�� ��� �⺻ Ÿ�Ե鿡 ���Ͽ� ���� �����ε��� �Ǿ��ֱ� ������ "std::cin >>" �� �����Ӱ� ������
	//						- ����ִ°� std::string�� �����ε� �Ǿ����� ������ istream�� ����� �ƴ� �ܺ� �Լ��� ������ �����ε� �Ǿ�����(����� <xstring> ����� ����)
	//							-> ���� ������ �����ϸ� ��: istream& operator>>(istream& in, std::string s){}
	//							-> ���� <xstring>������ �̷��� ��:
	//								_EXPORT_STD template <class _Elem, class _Traits, class _Alloc>
	//								basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr, basic_string<_Elem, _Traits, _Alloc>& _Str)
	//						- operator>>�� ��� ���鹮��(����, ����, ��)�� �Է½ÿ� �����ع���
	//							-> �� �ڵ嵵 ������ �ִ� ���ڸ� �Է��ϸ� ���� �����ϰ� �Ѵܾ �и��ؼ� �ް�����
	//	
	//	
	//					- cin : istream�� ��ü�� �ϳ�. �̰� <iostream>�� ���ǵǾ������Ƿ� <istream>�� include�ϴ°����δ� cin�� ������
	//	
	//		*/
	//	}

	// istream::operator>> ������ ���ǻ���: ���� �÷���

	{
		//	int t;
		//	
		//	// ���ڿ� �Է½� ���ѷ��� �߻� (C++11���ʹ� �Էµ� ���ڿ��� ������ �ٲ��� ���ϸ� 0�� ����Ƿ� t == 0�̸� ����ǹ���)
		//	//	while (true)
		//	//	{
		//	//		std::cin >> t;
		//	//		std::cout << "�Է� :: " << t << std::endl;
		//	//		if (t == 1) break;
		//	//	}
		//	
		//	// �� ������ �������� �Ʒ��� ������� �ذᰡ��
		//	while (std::cin >> t)
		//	{
		//		std::cout << "�Է� :: " << t << std::endl;
		//		if (t == 1) break;
		//	}

		/*
			- ���� �÷���
				- �� �ڵ忡�� int t�� ������ �ƴ� ���ڿ� ���� �ٸ� ���� �Է��ϸ� ���ѷ����� ����
				- �� ������ operator>>�� ó�� ����� �����ؾ���
					1) ios Ŭ������ ��Ʈ���� ���¸� �����ϰ� ���´� 4���� �÷��װ� ������(<xiosbase>�� ���ǵ�)
						- goodbit: ��Ʈ���� ����� �۾��� ������ ��
						- badbit: ��Ʈ���� ���� �Ұ����� ���� �߻���
						- failbit: ��Ʈ���� ���� ������ ���� �߻���
						- eofbit: �Է� �۾��ÿ� EOF ���޽�
							-> ����� ���� <xiosbase> ������ ������ �̷���
									static constexpr int goodbit = 0x0;
									static constexpr int eofbit  = 0x1;
									static constexpr int failbit = 0x2;
									static constexpr int badbit  = 0x4;
					2) �̶� int t�� ���ڿ��� ���ٸ� failbit �÷��װ� ����
						-> ���� ���� ���ڿ��� ���� �ش� �κ��� ��Ʈ�� ���ۿ��� �����ϱ⸸ �ϸ� �ǰ� �̴� �ɰ��� ������ �ƴϹǷ� badbit�� �ƴ�
					3) failbit�� ������ �Է°��� ���� �ʰ� �����ϴµ�, �̶� ������ ���ڿ����� ���� ���� ����
					4) �������� ���� ���ڿ��� ���� 1~3�� ���ѹݺ�....

				- ó���� ������ ������ ������ while(std::cin >> t) �� ������. �̸� ���� ������ ���ѷ��� ������ ���� �� ����. �� ������ �Ʒ��� ����
					1) ios ��ü ���ο� operator void*() const �Լ��� ���ǵǾ� ����
						-> �� �Լ��� fallbit �� badbit�� ��� �����־�� null�� �ƴ� �����͸� ��ȯ��. ��, ���������� ������� �����Ҷ��� ����
					2) t�� ���ڿ��� ���� �� �Լ��� null�� ��ȯ�Ͽ� while ���� Ż���ϰԵ�
					
					++1) ���� �ֽſ��� operator void*() �� ���°����� ���̰� ��� operator bool�� �����ϸ� !fail()�� ������ ��
					++2) fail()�� failbit�� badbit�� ������ true, �ƴϸ� false�� ��ȯ�ϹǷ� ������ ios -> void* -> bool�� ���� 2�� ��ȯ�� ���� ���ص� �ǵ��� �ϴµ� ��
		*/

		// �����ִ� �ڵ�: t�� ���ڿ��� ������ failbit�� ���� ���� s���� �Է¹��� �� ����
		//	int t;
		//	std::cin >> t;	// ���������� ���ڸ� �Է��ϸ� failbit�� ������
		//	std::cout << "failbit�� ���� �����̹Ƿ�, �Է¹��� �ʴ´�" << std::endl;
		//	std::string s;
		//	std::cin >> s;

		// �ذ���: ���� �÷��׿� ������ ����� �÷��׸� �ʱ�ȭ��Ű�� �ٽ� �Է¹޴´�
		int t;
		while (true)
		{
			std::cin >> t;
			std::cout << "�Է� :: " << t << std::endl;
			if (std::cin.fail())
			{
				std::cout << "����� �Է����ּ���" << std::endl;
				std::cin.clear();	// �÷��׸� �ʱ�ȭ�ϰ�
				std::cin.ignore(100, '\n');	// ���๮�ڰ� ���� �� ���� �����Ѵ�
			}
			if (t == 1) break;
		}

		/*
			- �� �ڵ尡 ��� �������� �м��غ���
				- std::cin.fail() �Լ��� ������. failbit Ȥ�� badbit �� �ϳ��� ���������� true�� ������
				- �߸��� �Է��� ���� ��� if(std::cin.fail())���� true�� �Ǿ� ���ǹ��� ������
				- ���ǹ�����
					- std::cin.clear() �� �̿��Ͽ� �÷��׵��� �ʱ�ȭ��(ios�� ����)
						-> std::cin.clear()�� ���ڸ� ���� ���� ��� �÷��׸� goodbit���� �ʱ�ȭ��Ŵ
					- std::cin.ignore(100, '\n') �� �̿��Ͽ� ���۸� �������(istream�� ����)
						-> std::cin.ignore(std::streamsize count = 1, int delim = Traits::eof())�� ������ (std::streamsize == long long��. <xiosbase>�� ã�ƺ��� ����)
						-> ù��° ����(100)��ŭ �ι�° ����('\n')�� ���ö� ���� ���ۿ��� �����ع���(�ι�° ���ڱ��� ����)
					- ���ۿ� 100�� �̻��� �� ���ڿ��� ������ ���۰� �� ����������� ������ ���� ignore�� ȣ��Ǹ鼭 �� �������

		
		
		*/
	}


	return 0;

}