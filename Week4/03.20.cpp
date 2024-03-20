
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
//			//	something_not_mutable = x;	// 안됨
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
//		while (str[string_length++]) {}	// 아마도 문자열 길이 재는거인듯함...
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
//		DoSomethingWithString(MyString("abc"));	// 정상작동
//		DoSomethingWithString("abcde");	// 정상작동...왜?
//	
//		/*
//			- 암시적 변환
//				- "abcde"가 MyString 타입이 아님에도 불구하고 DoSomethingWithString("abcde")가 정상적으로 작동된다?
//					-> 컴파일러가 알아서 "abcde"를 MyString으로 바꿀 방법을 찾고 그 결과 MyString(const char* str) 생성자를 찾아서 생성했기 때문
//					-> 결과적으로 DoSomethingWithString(MyString("abcde"))로 변환되어 실행된 것
//						-> 이러한 변환을 암시적 변환(implicit conversion)이라고 부름
//		*/
//	
//		// 암시적 변환으로 함수는 작동되지만 문자열을 받는 함수에 int를 넣었는데도 작동됨
//		// 생성자에 explicit 키워드를 붙이면 작동 안됨
//		//	DoSomethingWithString(3);
//	
//		//	MyString s1 = "abc";
//		//	MyString s2 = 3;		// explicit이 없으면 정상적으로 실행됨
//		//	MyString s3(3);			// 명시적으로 직접 생성자를 호출했으므로 정상 실행됨
//	
//		/*
//			- explicit
//				- DoSomethingWithString(3);
//					- MyString(int capacity) 생성자가 있으므로 암시적 변환이 일어나 함수가 작동이 되긴 함
//					- 그러나 문자열을 받아야 하는데 정수를 받아서 실행이 되는것은 의도되지 않은 상황이고 이를 막아야 함
//						-> MyString(int capacity) 생성자의 앞에 explicit을 붙여 이를 해결할 수 있음
//				
//				- explicit
//					- implicit의 반대말로 "명시적"이라는 의미를 갖고있음
//					- 이 키워드를 사용하여 생성자를 만들면 해당 생성자를 이용한 암시적 변환을 못하도록 막음
//					- 또한 복사 생성자의 형태로도 호출할 수 없도록 막음
//	
//				-> 결론: explicit이 붙은 생성자는 직접 명시적으로 생성자를 호출하는 경우만 허용함
//		*/
//	
//		s.DoSomething(3);	// C3490: 'something_not_mutable'은(는) const 개체를 통해 액세스되고 있으므로 수정할 수 없습니다.
//	
//		/*
//			- mutable
//				- mutable이 붙은 변수는 const 함수에서도 값을 변경할 수 있음
//				- 이게 왜필요함? -> 아래에서 새로 다시 설명
//		*/
//	
//	}

#include <iostream>

// mutable이 필요한 이유 -> 서버 프로그램을 만든다고 가정해보자



class User
{
	// 사용자...
public:
	User(Data data) {}
};

class Data
{
public:
	// 데이터...
};

class Database
{
	// 데이터베이스...
public:
	Data* find(int id) const {}	// 대충 db에서 검색하는 함수
};

class Cache
{
	// 캐시...
public:
	Data* find(int id) const {}	// 대충 캐시에서 검색하는 함수
	void update(int id, Data data) {} // 대충 캐시를 업데이트하는 함수
};

class Server
{
public:
	// 간단한 서버 프로그램의 예시 -> db에서 user_id에 해당되는 유저의 정보를 읽어서 반환
	// 이때 캐시 메모리가 사용된다고 생각해보자
	User GetUserInfo(const int user_id) const
	{
		// 1. 캐시에서 user_id 검색
		Data* user_data = cache.find(user_id);

		// 2. 캐시에서 데이터를 찾지 못하였다면 db에 요청
		if (!user_data)
		{
			user_data = database.find(user_id);

			// 이후 캐시에 user_data 등록
			cache.update(user_id, *user_data); // mutable 이 없으면 이부분이 불가능함
		}

		// 3. 리턴된 정보로 User 객체 생성
		return User(*user_data);
	}


private:
	mutable Cache cache;	// mutable이 붙음으로서 상수함수 내부에서도 값의 변경이 가능해짐 
	Database database;
};

int main()
{
	/*
		- mutable의 필요성
			- 위 클래스의 GetUserInfo()를 보면...
				- 캐시에서 데이터를 찾지 못한경우 데이터베이스에 일단 요청해서 찾음
				- 이후 캐시를 업데이트 하려고 하는데
					- GetUserInfo 함수는 내부 값의 변경이 일어나지 않으므로 const 함수이고
					- cache.update 함수는 내부 값을 변경해야 하므로 const 함수일수가 없는데
					- const 함수는 내부에서 const가 아닌 다른 함수를 사용할 수 없음....
					- 그렇다고 GetUserInfo를 const가 아니게 만드는것도 가능은 하지만 그리 좋은방법은 아니라고 판단됨
						-> 이런 상황에 cache를 mutable로 변경 가능하게 한다면 모든 문제가 해결됨!
	
	
	*/
}
