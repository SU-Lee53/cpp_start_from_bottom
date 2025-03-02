
/*
	04.19 C++������ ���� ����� ifstream, ofstream, stringstream
*/

// fstream

//	#include <fstream>
//	#include <iostream>
//	#include <string>
//	
//	int main()
//	{
//		{
//			//	std::ifstream in("test.txt");
//			//	std::string s;
//			//	
//			//	if (in.is_open())
//			//	{
//			//		in >> s;
//			//		std::cout << "�Է¹��� ���ڿ� :: " << s << std::endl;
//			//	}
//			//	else
//			//	{
//			//		std::cout << "������ ã�� �� �����ϴ�" << std::endl;
//			//	}
//			//	
//			//	in.close();
//			//	in.open("other.txt");
//			//	
//			//	if (in.is_open())
//			//	{
//			//		in >> s;
//			//		std::cout << "�Է¹��� ���ڿ� :: " << s << std::endl;
//			//	}
//			//	else
//			//	{
//			//		std::cout << "������ ã�� �� �����ϴ�" << std::endl;
//			//	}
//		}
//	
//		{
//			std::ifstream in("test.txt", std::ios::binary);
//			std::string s;
//	
//			int x;
//			if (in.is_open())
//			{
//				in.read((char*)(&x), 4);
//				std::cout << std::hex << x << std::endl;
//			}
//			else
//			{
//				std::cout << "������ ã�� �� �����ϴ�" << std::endl;
//			}
//		}
//		
//	
//	
//		/*
//			- fstream
//				- fstream: C++�� ���� ����� ��Ʈ��
//				- fstream ��ü ������ �����ϰ��� �ϴ� ������ ��θ� �����ϸ� ��. �⺻�����δ� ����η� �ҽ����� ��ġ���� ã��
//					- ������ �������� �ʴ� ���� ������ �߻��Ͽ� ������ �ʾҴٸ� std::ifstream::is_open() �Լ��� false�� ��������
//				- cin(istream) ����ϴ°� ó�� operator>>�� �̿��Ͽ� ������ ���� �� ����. ���� ���õ� ���� �ܼ� ����� ��Ʈ���� ������
//					- �̴� fstream�� istream���� ��ӹ޾� ������̱� ������
//						-> ���� �ҽ� ����
//	
//							_EXPORT_STD template <class _Elem, class _Traits>
//							class basic_fstream : public basic_iostream<_Elem, _Traits>
//	
//						-> ������ �׸� C++ ����� ��Ʈ���� ��ӱ����� ���� iostream�� istream�� ostream�� ���߻�� ����
//	
//				- ���� C�� fopen�� �޸� ���� close �� �ʿ䰡 ���µ� �̴� fstream�� �Ҹ��ڿ��� �ڵ����� close ���ֱ� ������
//					-> �ٸ� ���� ���� ��Ʈ���� ������ �ݰ� ���ο� ������ ��������ַ��� close�� ���־����. 
//					-> ���ο� ������ ������ ���� �����ڸ� �ٽ� �� �ʿ�� ���� open() �Լ��� �̿��ϸ� ��
//				- ���� �÷��׸� �̿��ؼ� �ٸ� ���·� �а� ���⵵ ������
//					- �� �ڵ忡�� in("test.txt", std::ios::binary); ���� ifstream ��ü ������ binary ���·� �ްڴٰ� �����(����)
//					- ���� in.read((char*)(&x), 4); ������ 4����Ʈ ¥�� ������ ������� �ǹ̷� int������ 4����Ʈ char �迭�� ĳ�����Ͽ� ����
//						-> read() �Լ� ���ÿ��� �ݵ�� �����Ʈ�� ������ ����ؾ���
//						-> ���� ������ ��� std::hex �����ڸ� �̿��Ͽ� 16������ �����. ����� ��Ʋ ����� �ý����̹Ƿ� ���� �ּҺ��� ���
//		
//		*/
//		return 0;
//	}

// ���� ��ü �б�: �ѹ��� �� �б�, ���پ� �б�

//	#include <fstream>
//	#include <iostream>
//	#include <string>
//	
//	int main()
//	{
//		// ���� ��ü�� �ѹ��� �б�
//	
//		{
//			std::ifstream in("test.txt");
//			std::string s;
//	
//			if (in.is_open())
//			{
//				// ��ġ �����ڸ� ���� ������ �ű��
//				in.seekg(0, std::ios::end);
//	
//				// �׸��� �� ��ġ�� �д´�. (������ ũ��)
//				int size = in.tellg();
//	
//				// �� ũ���� ���ڿ��� �Ҵ��Ѵ�.
//				s.resize(size);
//	
//				// ��ġ �����ڸ� �ٽ� ���� �� ������ �ű��
//				in.seekg(0, std::ios::beg);
//	
//				// ���� ��ü ������ �о ���ڿ��� �����Ѵ�.
//				in.read(&s[0], size);
//				std::cout << s << std::endl;
//			}
//			else
//			{
//				std::cout << "������ ã�� �� �����ϴ�" << std::endl;
//			}
//	
//			/*
//				- ���� ��ü �ѹ��� �б�
//					- �ڵ� ����
//						- in.seekg(0, std::ios::end)
//							-> seekg(): C�� fseek�� ���� �Լ���, ���� ��ġ �����ڸ� �Ը��� �°� ������ �� ����
//							-> �ι�° ���ڰ� ���� �� ��ġ�� �ǹ��ϰ�, ù��° ��ġ�� �� ��ġ�κ��� ��ŭ ������ �ִ��ĸ� �ǹ���
//								-> ������ ��(std::ios::end)���� 0��ŭ ������ �� ��, ������ ������ �̵���
//						- int size = in.tellg()
//							-> tellg(): ��ġ �������� ��ġ(�����������κ���)�� ��ȯ
//							-> ������ ��ġ �����ڸ� ���� ������ �̵��������Ƿ� ��ġ �������� ��ġ�� ������ ũ��(����Ʈ ũ��)�� ��ȯ��
//							-> ���� string�� ���� ũ�⸸ŭ �Ҵ�
//						- in.read(&s[0], size);
//							-> ���� ��ü ������ ���ڿ��� ����
//			
//			*/
//		}
//	
//		// ���� ��ü�� ���پ� �б�
//	
//		{
//			std::ifstream in("test.txt");
//			char buf[100];
//			std::string s;
//	
//			if (!in.is_open())
//			{
//				std::cout << "������ ã�� �� �����ϴ� " << std::endl;
//				return 0;
//			}
//	
//			while (in)
//			{
//				//	in.getline(buf, 100);
//				//	std::cout << buf << std::endl;
//				getline(in, s);
//				std::cout << s << std::endl;
//			}
//	
//			/*
//				- ���� ��ü ���پ� �б�
//					- �ڵ� ����
//						- while(in)
//							-> ifstream ���� �ڱ� �ڽ��� bool�� ĳ�����ϴ� operator bool() ĳ���� �����ڰ� �����ε� �Ǿ�����(��Ȯ���� ios���� ��ӹ���)
//							-> bool�� ����� true���� "���� �Է� �۾��� ������"�̿��� ��
//							-> !!!!! ����� in.eof()�� ������ �������� ���� �ȵ� !!!!!
//								-> in.eof()�� ���� ��ġ �����ڰ� ������ ��(eof)�� ������ "����"�� true�� ������
//								-> in.eof()�� ���� �Է��̰� ���� ������ ���� ��ġ�ڸ� ���� ������ ���� �Է� �۾��� eof���� true�� �������� ����
//								-> ��, in.eof()�� "���� �бⰡ �����ϴ�" ��� ���� �������� ����!!
//								-> �׷��Ƿ� in.eof()�� ����Ͽ� while���� ���� �� ���������� �ƹ��͵� ���� ����
//						- in.getline(buf, 100)
//							-> ù��° ���ڿ��� ������ ��ġ, �ι�° ���ڷδ� ������ ��ġ�� �ִ� ũ�⸦ ����
//							-> ���๮�� '\n'�� ������ ������ (�ִ� ������ ũ�� - 1)��ŭ�� ������ �о����. -1�� ������ �� ���� ���ڸ� �ֱ� ������
//							-> ���� ���๮�ڰ� �ƴ� �ٸ� ����� ���� ���ڱ����� �а�ʹٸ� ���ڰ� 3���� ������ ����
//								-> getline(buf, 100, '.') �̷� ������, ����° ���ڿ� ������ ���ڰ� ���ö����� �о����
//							-> �׷��� ifstream�� getline()�� ���๮��(Ȥ�� ������ ����) �� ������ ���� ������ ������ ũ�Ⱑ �� ���� failbit�� �ѹ���
//								-> �׷��Ƿ� ������ ���۸� ����� ũ�� ����� �ְų� �Ʒ��� ����� ����ؾ���
//							-> std::string�� ���ǵ� getline()
//								-> ifstream(��Ȯ���� istream�� ����)�� getline�� �޸� string�� ���ǵǾ��ִ� �ٸ� �Լ���
//								-> ù��° ���ڷ� istream ���ڸ� �ް�, �ι�° ���ڷ� �Է¹��� ���ڿ��� ������ string ��ü�� ����
//								-> string�� ���� ���� ���ڿ��̹Ƿ� ifstream::getline()�� �޸� ������ ũ�⸦ �Ű澵 �ʿ䰡 ���� �˾Ƽ� ���๮�ڱ��� �о���
//			*/
//		}
//	
//		return 0;
//	}

// ���Ͽ� ����

//	#include <iostream>
//	#include <fstream>
//	#include <string>
//	
//	class Human
//	{
//	public:
//		Human(const std::string& name, int age) : name(name), age(age) {}
//	
//		std::string get_info()
//		{
//			return "Name :: " + name + " / Age :: " + std::to_string(age);
//		}
//	
//		friend std::ofstream& operator<<(std::ofstream& o, Human& h);
//	
//	private:
//		std::string name;
//		int age;
//	};
//	
//	std::ofstream& operator<<(std::ofstream& o, Human& h)
//	{
//		o << h.get_info();
//		return o;
//	}
//	
//	int main()
//	{
//		// ���� ���� �⺻
//		{
//			std::ofstream out("outtest.txt");
//		
//			std::string s;
//			if (out.is_open())
//			{
//				out << "�̰� ����";
//			}
//		
//			/*
//				- ���Ͽ� ����
//					- �ڵ� ����
//						- std::ofstream out("outtest.txt")
//							-> ofstream�� �� ������ ��θ� ���ڷ� �޾� �����ϰ� ������ ������
//							-> Ư���� ������ ���� ������ �ش� ���� ������ �� �������� ���ο� �������� ���
//						- out << "�̰� ����:
//							-> ostream�� ������� �ϴ� Ŭ�����̹Ƿ� cout ������ operator<< �� �̿��Ͽ� �Է� ������
//			*/
//		}
//	
//		// ���� ����: �����̱�
//		//	{
//		//		std::ofstream out("outtest.txt", std::ios::app);
//		//	
//		//		std::string s;
//		//		if (out.is_open())
//		//		{
//		//			out << "�����̱�";
//		//		}
//		//	
//		//		/*
//		//			- ���Ͽ� ����: �����̱�
//		//				- �ڵ� ����
//		//					- std::ofstream out("outtest.txt", std::ios::app)
//		//						-> ofstream ��ü ������ �ɼ����� std::ios::app�� �ָ� ���� ������ �������ʰ� �� �ڿ� ������
//		//						-> ������ ���� �ɼ����� �� �� �ִ� �÷��׷� �Ʒ����� �̾ ����
//		//		*/
//		//	}
//	
//		// ���Ͼ���: Openmode
//		{
//			// abc1, abc2 ��� abc�� ��������
//			std::ofstream out("abc1.txt", std::ios::app);
//			std::ofstream out2("abc2.txt", std::ios::ate);
//		
//			out.seekp(3, std::ios::beg);
//			out2.seekp(3, std::ios::beg);
//		
//			out << "�߰�";
//			out2 << "�߰�";
//	
//			/*
//				- Openmode
//					- ���� �÷��׳� ���� �÷���ó�� ios Ŭ������ ���ǵǾ��� �÷��׷� ������ ���� ��� ������ ������ �� ����
//						-> ���� ����. <xiosbase>�� ���ǵǾ�����
//							enum _Openmode { // constants for file opening options
//								_Openmask = 0xff
//							};
//	
//							static constexpr int in         = 0x01;
//							static constexpr int out        = 0x02;
//							static constexpr int ate        = 0x04;
//							static constexpr int app        = 0x08;
//							static constexpr int trunc      = 0x10;
//							static constexpr int _Nocreate  = 0x40;
//							static constexpr int _Noreplace = 0x80;
//							static constexpr int binary     = 0x20;
//						-> ������ ����ߴ� app, binary�� ����
//	
//					- ������ �÷��׿� ���ؼ��� �Ʒ��� ����
//						- ios::app : �ڵ����� ���� ������ ���� �б�� ���⸦ �ǽ���(��, ������ ���� ��ġ �����ڰ� ���� ���� ����Ŵ)
//						- ios::ate : �ڵ����� ���� ������ ���� �б�� ���⸦ �ǽ���(��, ������ ���� ��ġ �����ڰ� ���� ���� ����Ŵ)
//						- ios::trunc : ���� ��Ʈ���� ���� ������ �ִ� ������� ��� ������
//							-> �⺻������ ofstream ��ü ������ �� �ɼ��� �����
//						- ios::in, ios::out : ���Ͽ� �Է��� �� ��, ����� �� �� ������. 
//							-> ifstream�� ofstream��ü ������ �⺻���� ���� �Ǿ��ְ� ���� �ٸ� �÷��׵�� ��Ʈ����ũ ����� �Բ� ����Ǵ°����� ����
//								-> �ߺ��� ������ ��Ʈ 2���� ������ �۵� �����ѵ� 01�̸� in, 10�̸� out, 11�̸� �Ѵ� �Ǵµ�. ��Ȯ���� �𸣰���
//								-> �׳� fstream�� �⺻ �������� openmode ������ ����Ʈ�� ios_base::in | ios_base::out ���� ���ִ°� ���� �Ƹ��� ������
//					- ios::app�� ios::ate�� ������
//						-> ios::app : ���� ������ ������ ������ ���� -> ��ġ �����ڰ� ���� ������ ���� �������̶�� �����Ͽ� ������ (seek to the end of stream before each write)
//						-> ios::ate : ���� ������ ������ �������� ���� -> ��ġ �����ڰ� ���� ������ �����ؼ� ������ (seek to the end of stream immediately after open)
//							-> �� �ڵ忡��...
//								- ios::app���� �� abc1.txt 
//									-> ���� ������ ���� ���������� ������
//									-> �׷��Ƿ� seekp()�� ��ġ �����ڰ� ������ ������ ���� abc �� �����ϰ� "�߰�"�� ������
//								- ios::ate���� �� abc2.txt
//									-> ������ ���� ������ ������
//									-> �׷��Ƿ� seekp() ��ġ �����ڰ� ���������κ��� 3��ŭ ������ ������ �̵���
//									-> ���� "�߰�"�� ���ٿ����� ������ abc�� ��� ������
//								-> ���: ios::ate�� �̿��ص� ���� ���Ͽ� �����̰ų� �����ִ� ���� �Ұ�����
//			*/
//		}
//	
//		// ���� ����: ofstream ������ �����ε�
//		{
//			std::ofstream out("test.txt");
//		
//			Human h("������", 20);
//			out << h << std::endl;
//		
//			/*
//				- operator<< �����ε�
//					std::ofstream& operator<<(std::ofstream& o, Human& h)
//					{
//						o << h.get_info();
//						return o;
//					}
//					- ofstream ��ü�� ���۷����� ����� Ÿ���� ���ڷ� �޾� �����ε� ��Ŵ
//					- ��Ʈ���� ������ �Է��� ���� ofstream ��ü�� �����ϸ� ��
//	
//			*/
//		}
//	
//		
//	
//		return 0;
//	}

// stringstream

#include <iostream>
#include <sstream>
#include <string>
double to_number(std::string s)
{
	std::istringstream ss(s);
	double x;

	ss >> x;
	return x;
}

std::string to_str(int x)
{
	std::ostringstream ss;
	ss << x;

	return ss.str();	// std::ostringstream::str() : ���ڿ� ��Ʈ���� ���� ���ڿ��� �ҷ���
}

int main()
{
	// stringstream

	//	{
	//		std::istringstream ss("123");
	//		int x;
	//		ss >> x;
	//	
	//		std::cout << "�Է¹��� ������ :: " << x << std::endl;
	//	
	//		/*
	//			output:
	//			�Է¹��� ������ :: 123
	//		*/
	//	}

	// stringstream���� ���ڿ� < - > ���ڷ� ����� �Լ� �����
	{
		std::cout << "���ڿ� -> ���� ��ȯ:: 1 + 2 = " << to_number("1") + to_number("2") << std::endl;
		std::cout << "���� -> ���ڿ� ��ȯ:: 1 + 2 = " << to_str(1 + 2) << std::endl;
		
		/*
			output:
			���ڿ� -> ���� ��ȯ:: 1 + 2 = 3
			���� -> ���ڿ� ��ȯ:: 1 + 2 = 3
		*/
	}

	/*
		- stringstream
			- ���ڿ��� �ϳ��� ��Ʈ���̶� �����ϰ� ���ִ� ����ȭ ��ġ
			- �� �ڵ��� �м�
				- std::istringstream ss("123") : ���ڿ� "123"�� ��ϵǾ� �ִ� �Է� ��Ʈ�� ����
					-> ���Ͽ� 123 �� ����س��� �Է¹޴°Ͱ� �����ϰ� ���� ��
				- ss >> x : ���Ͽ��� ���ڸ� �о�°� ó�� 123�� ���� �� ����
					-> �� atoi() ���� �Լ� ���� �����ϰ� ���ڿ����� ���ڷ� ��ȯ�� �� ����
					-> ���� �Լ��� ���ô� �� to_number�� to_str�� ����
			- �Ϲ� stream�� ���������� �Է½ÿ��� istringstream, ��½ÿ��� ostringstream�� ����ϸ� ��

	
	
	*/

	return 0;
}
