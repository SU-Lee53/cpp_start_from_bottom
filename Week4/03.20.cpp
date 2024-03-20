
/*
	03.20 explicit, mutable
*/

//	#include <iostream>
//	
//	class MyString
//	{
//	public:
//		explicit MyString(int capacity);
//		MyString(const char* str);
//		MyString(const MyString& str);
//		~MyString();
//	
//		int length() const { return string_length; };
//		char operator[] (int idx) { return string_content[idx]; }
//	
//		void DoSomething(int x) const 
//		{ 
//			//	something_not_mutable = x;	// �ȵ�
//			something_mutable = x;
//		}
//	
//	private:
//		char* string_content;
//		int string_length;
//		int memory_capacity;
//	
//		int something_not_mutable;
//		mutable int something_mutable;
//	};
//	
//	MyString::MyString(int capacity)
//	{
//		string_content = new char[capacity];
//		string_length = 0;
//		memory_capacity = capacity;
//		std::cout << "Capacity : " << capacity << std::endl;
//	}
//	
//	MyString::MyString(const char* str)
//	{
//		string_length = 0;
//		while (str[string_length++]) {}	// �Ƹ��� ���ڿ� ���� ��°��ε���...
//		
//		string_content = new char[string_length];
//		memory_capacity = string_length;
//	
//		for (int i = 0; i != string_length; i++) string_content[i] = str[i];
//	}
//	
//	MyString::MyString(const MyString& str)
//	{
//		string_length = str.string_length;
//		string_content = new char[string_length];
//	
//		for (int i = 0; i < string_length; i++) string_content[i] = str.string_content[i];
//	}
//	
//	MyString::~MyString()
//	{
//		delete[] string_content;
//	}
//	
//	void DoSomethingWithString(MyString s) 
//	{
//		for (int i = 0; i <= s.length(); i++)
//		{
//			std::cout << s[i];
//		}
//		std::cout << std::endl;
//	}
//	
//	int main()
//	{
//		MyString s(3);	// output -> Capacity : 3
//	
//		DoSomethingWithString(MyString("abc"));	// �����۵�
//		DoSomethingWithString("abcde");	// �����۵�...��?
//	
//		/*
//			- �Ͻ��� ��ȯ
//				- "abcde"�� MyString Ÿ���� �ƴԿ��� �ұ��ϰ� DoSomethingWithString("abcde")�� ���������� �۵��ȴ�?
//					-> �����Ϸ��� �˾Ƽ� "abcde"�� MyString���� �ٲ� ����� ã�� �� ��� MyString(const char* str) �����ڸ� ã�Ƽ� �����߱� ����
//					-> ��������� DoSomethingWithString(MyString("abcde"))�� ��ȯ�Ǿ� ����� ��
//						-> �̷��� ��ȯ�� �Ͻ��� ��ȯ(implicit conversion)�̶�� �θ�
//		*/
//	
//		// �Ͻ��� ��ȯ���� �Լ��� �۵������� ���ڿ��� �޴� �Լ��� int�� �־��µ��� �۵���
//		// �����ڿ� explicit Ű���带 ���̸� �۵� �ȵ�
//		//	DoSomethingWithString(3);
//	
//		//	MyString s1 = "abc";
//		//	MyString s2 = 3;		// explicit�� ������ ���������� �����
//		//	MyString s3(3);			// ��������� ���� �����ڸ� ȣ�������Ƿ� ���� �����
//	
//		/*
//			- explicit
//				- DoSomethingWithString(3);
//					- MyString(int capacity) �����ڰ� �����Ƿ� �Ͻ��� ��ȯ�� �Ͼ �Լ��� �۵��� �Ǳ� ��
//					- �׷��� ���ڿ��� �޾ƾ� �ϴµ� ������ �޾Ƽ� ������ �Ǵ°��� �ǵ����� ���� ��Ȳ�̰� �̸� ���ƾ� ��
//						-> MyString(int capacity) �������� �տ� explicit�� �ٿ� �̸� �ذ��� �� ����
//				
//				- explicit
//					- implicit�� �ݴ븻�� "�����"�̶�� �ǹ̸� ��������
//					- �� Ű���带 ����Ͽ� �����ڸ� ����� �ش� �����ڸ� �̿��� �Ͻ��� ��ȯ�� ���ϵ��� ����
//					- ���� ���� �������� ���·ε� ȣ���� �� ������ ����
//	
//				-> ���: explicit�� ���� �����ڴ� ���� ��������� �����ڸ� ȣ���ϴ� ��츸 �����
//		*/
//	
//		s.DoSomething(3);	// C3490: 'something_not_mutable'��(��) const ��ü�� ���� �׼����ǰ� �����Ƿ� ������ �� �����ϴ�.
//	
//		/*
//			- mutable
//				- mutable�� ���� ������ const �Լ������� ���� ������ �� ����
//				- �̰� ���ʿ���? -> �Ʒ����� ���� �ٽ� ����
//		*/
//	
//	}

#include <iostream>

// mutable�� �ʿ��� ���� -> ���� ���α׷��� ����ٰ� �����غ���



class User
{
	// �����...
public:
	User(Data data) {}
};

class Data
{
public:
	// ������...
};

class Database
{
	// �����ͺ��̽�...
public:
	Data* find(int id) const {}	// ���� db���� �˻��ϴ� �Լ�
};

class Cache
{
	// ĳ��...
public:
	Data* find(int id) const {}	// ���� ĳ�ÿ��� �˻��ϴ� �Լ�
	void update(int id, Data data) {} // ���� ĳ�ø� ������Ʈ�ϴ� �Լ�
};

class Server
{
public:
	// ������ ���� ���α׷��� ���� -> db���� user_id�� �ش�Ǵ� ������ ������ �о ��ȯ
	// �̶� ĳ�� �޸𸮰� ���ȴٰ� �����غ���
	User GetUserInfo(const int user_id) const
	{
		// 1. ĳ�ÿ��� user_id �˻�
		Data* user_data = cache.find(user_id);

		// 2. ĳ�ÿ��� �����͸� ã�� ���Ͽ��ٸ� db�� ��û
		if (!user_data)
		{
			user_data = database.find(user_id);

			// ���� ĳ�ÿ� user_data ���
			cache.update(user_id, *user_data); // mutable �� ������ �̺κ��� �Ұ�����
		}

		// 3. ���ϵ� ������ User ��ü ����
		return User(*user_data);
	}


private:
	mutable Cache cache;	// mutable�� �������μ� ����Լ� ���ο����� ���� ������ �������� 
	Database database;
};

int main()
{
	/*
		- mutable�� �ʿ伺
			- �� Ŭ������ GetUserInfo()�� ����...
				- ĳ�ÿ��� �����͸� ã�� ���Ѱ�� �����ͺ��̽��� �ϴ� ��û�ؼ� ã��
				- ���� ĳ�ø� ������Ʈ �Ϸ��� �ϴµ�
					- GetUserInfo �Լ��� ���� ���� ������ �Ͼ�� �����Ƿ� const �Լ��̰�
					- cache.update �Լ��� ���� ���� �����ؾ� �ϹǷ� const �Լ��ϼ��� ���µ�
					- const �Լ��� ���ο��� const�� �ƴ� �ٸ� �Լ��� ����� �� ����....
					- �׷��ٰ� GetUserInfo�� const�� �ƴϰ� ����°͵� ������ ������ �׸� ��������� �ƴ϶�� �Ǵܵ�
						-> �̷� ��Ȳ�� cache�� mutable�� ���� �����ϰ� �Ѵٸ� ��� ������ �ذ��!
	
	
	*/
}
