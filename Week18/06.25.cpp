/*
	06.25 - std::optional, std::variant, std::tuple
*/

/*  std::optional  */
//	#include <iostream>
//	#include <map>
//	#include <string>
//	#include <optional>
//	
//	//	std::string GetValueFromMap(const std::map<int, std::string>& m, int key)
//	//	{
//	//		// std::optional �� ���Ե��� �ʾ��� �� �ʿ��� ���� �������� �Լ�
//	//		// ã������ Ű�� ������ �˸��� ���� ������ �� ������ ������ �� string �� �����ϴ� �� �ۿ� ����
//	//		// �̷��� Ű�� �������� �ʴ� ���� Ű�� ���������� ���� �׳� �� string �� ��츦 ������ �� ����
//	//	
//	//		auto itr = m.find(key);
//	//		if (itr != m.end())
//	//		{
//	//			return itr->second;
//	//		}
//	//	
//	//		return std::string();
//	//	}
//	
//	//	std::pair<std::string, bool> GetValueFromMap(const std::map<int, std::string>& m, int key)
//	//	{
//	//		// std::optional �� ���Ե��� �ʾ��� �� �ʿ��� ���� �������� �Լ� 2
//	//		// �̹����� std::pair �� �̿��Ͽ� Ű�� �����ϸ� ���� true ��, Ű�� ������ �� string �� false �� ����
//	//		// �� ������� �ణ�� ������ ����. �Ʒ� �� ������ �̾
//	//	
//	//		auto itr = m.find(key);
//	//		if (itr != m.end())
//	//		{
//	//			return std::make_pair(itr->second, true);
//	//		}
//	//		
//	//		return std::make_pair(std::string(), false);
//	//	}
//	
//	std::optional<std::string> GetValueFromMap(const std::map<int, std::string>& m, int key)
//	{
//		auto itr = m.find(key);
//		if (itr != m.end())
//		{
//			return itr->second;
//		}
//	
//		// nullopt : <optional> �� ���ǵ� ��ü�� ����ִ� optional �� ����
//		return std::nullopt;
//	}
//	
//	class A
//	{
//	public:
//		A() { std::cout << "����Ʈ ����" << std::endl; }
//		A(const A& a) { std::cout << "���� ����" << std::endl; }
//	};
//	
//	int main()
//	{
//		std::map<int, std::string> data = { {1, "hi"}, {2, "hello"}, {3, "hiroo"} };
//	
//		std::cout << std::boolalpha;
//		std::cout << "�ʿ��� 2 �� �����Ǵ� ����? " << GetValueFromMap(data, 2).value() << std::endl;	// �ʿ��� 2 �� �����Ǵ� ����? hello
//		std::cout << "�ʿ� 4 �� ������? " << GetValueFromMap(data, 4).has_value() << std::endl;	// �ʿ� 4 �� ������? false
//	
//		// std::optional �� std::pair �� ������
//	
//		std::cout << "std::optonal<A> ����" << std::endl;
//		std::optional<A> maybe_a;
//	
//		std::cout << "std::pair<A, nullptr_t> ����" << std::endl;
//		std::pair<A, nullptr_t> pair_a;
//	
//		/*
//			- std::optional �� std::pair �� ������ output : 
//				std::optonal<A> ����
//				std::pair<A, nullptr_t> ����
//				����Ʈ ����
//	
//				-> std::optional �� ��������� ����Ʈ ��ü�� �������� ����
//		*/
//	
//	
//		/*
//			- std::optional
//				- ������ ���Ƿ��� optional : ������
//				- std::optional : ���������� ���� ������ ��ü
//	
//				- �ڵ� ����
//					- std::optional �� ������� �ʰ� map ���� Ű�� �����ϴ� ���� �������� GetValueFromMap() �Լ��� �����غ�
//	
//						- std::string GetValueFromMap(const std::map<int, std::string>& m, int key)
//							- ���� �������� ������� ������ GetValueFromMap()
//							- �� ��� Ű�� �����ϸ� ���� �����ϰ� Ű�� �������� ������ ����ִ� string ��ü�� ������
//							- �̶� Ű�� ���� ���� Ű�� �ִµ� ���� �׳� ����ִ� string �� ��츦 �����ϱ� �����
//	
//						- std::pair<std::string, bool> GetValueFromMap(const std::map<int, std::string>& m, int key)
//							- std::pair �� �̿��Ͽ� ������ GetValueFromMap() (�ǿܷ� std::pair �� std::tuple �� C++ 11 ���� ��������)
//							- Ű�� �����ϸ� ���� true, Ű�� �������� ������ ����ִ� string �� false �� ������
//							- std::pair �� �̿��� ��쿡�� Ű�� �������� ���� �� ����Ʈ ��ü�� �����ؾ� �ϴµ� �̴� 2���� ������ ����
//								1) ��ü�� ����Ʈ �����ڰ� ���� ���� ����
//								2) ��ü�� ����Ʈ ������ �����ɸ� �� ���� -> ������ ������ ������ �����ǵ� �����ɸ��� ������ ����
//	
//					- ������ GetValueFromMap() ������ std::optional �� �����Ͽ� �� 2���� ������ �������� �ذ���
//	
//						- std::optional<std::string>
//							- �� ó�� ������ std::optional ��ü�� std::string �� �����ϰų� ���ϰų� ���� �ϳ��� ���°� ��
//							- �� ���п� Ű�� ������ �� �׳� ���� �����ϸ� std::string �� ������ ������
//							- std::optional �� ���� ū �������� ��ü ���� �����߿� �����Ҵ��� �Ͼ�� ����
//								-> std::optional ��ü�� ��ü�� ���Ե�
//	
//						- return std::nullopt;
//							- std::nullopt : �̸� ���ǵǾ��ִ� �� std::optional ��ü
//							- �ƹ��͵� ���� �� optional �� �����ϰ� ������ ����ϸ� ��
//	
//						- GetValueFromMap(data, 2).value()
//							- optional ��ü�� ������ �ִ� ��ü�� ����
//							- ���� ����ִ� optional ��ü�� �����Ѵٸ� std::bad_optional_access ���ܰ� �߻���
//							- ������ ������ * �� ����ص� ��ü�� ���� ������
//	
//						- GetValueFromMap(data, 4).has_value()
//							- �ش� optional �� ��ü�� ������ �ִ��� Ȯ���ϴ� �Լ�
//							- bool ĳ���� �����ε��� �Ǿ������Ƿ� if (GetValueFromMap(data, 4).has_value()) ó�� ��뵵 ������
//	
//				- std::optional �� std::pair �� �޸� ��������� ����Ʈ ��ü�� ���� �ʿ䰡 ����
//					- �� �׽�Ʈ������ std::optional ������ ����Ʈ �����ڸ� ȣ������ ����
//		*/
//	}

/*  ���۷����� ���� std::optional  */
//	#include <iostream>
//	#include <optional>
//	
//	class A
//	{
//	public:
//		A() { std::cout << "����Ʈ ����" << std::endl; }
//		A(const A& a) { std::cout << "���� ����" << std::endl; }
//	
//		int data;
//	};
//	
//	int main()
//	{
//		A a;
//		a.data = 5;
//		
//		// std::optional<A&> maybe_a;	// C2338 : static_assert failed: 'T in optional<T> must meet the Cpp17Destructible requirements (N4950 [optional.optional.general]/3).'
//		std::optional<std::reference_wrapper<A>> maybe_a = std::ref(a);
//	
//		// �����ʹ�?
//		std::optional<A*> maybe_pa = &a;
//	
//	
//		maybe_a->get().data = 3;
//		std::cout << "a.data : " << a.data << std::endl;	// a.data : 3
//		std::cout << "maybe_pa : " << maybe_pa.value()->data << std::endl;	// maybe_pa : 3 -> �����ʹ� ��������
//		/*
//			- ���۷����� ���� std::optional
//				- ��Ģ������ std::optional ���� ���۷��� Ÿ���� ���� ����
//					- cppreference �� ������ ���� ������ https://en.cppreference.com/w/cpp/utility/optional
//						-> The type must meet the requirements of Destructible (in particular, array and reference types are not allowed).
//						-> ���ø� ������ Ÿ���� �ݵ�� Destructible ������ �����ؾ��� (Ư��, �迭�� ���۷��� Ÿ���� ������ ����)
//	
//					- ��??
//						- ��� ��Ȯ�� ������ ������ �ۼ��ϴ� �ñ���� ��Ȯ�� �𸣰���
//						- �ٸ�, ������ ������� �����غ����� ��
//							- �ı� �������� C++ 17 �� ǥ�� ���� ������ ���� ������ (�� static_assert ���� �ɸ��� Cpp17Destructable �� �ٷ� �� ������)
//	
//								�־��� u �� ���Ͽ� (u �� Ÿ�� T�� ǥ����) �Ʒ��� ǥ������ �ݵ�� ��ȿ�ϰ� Ư���� ȿ���� ����
//								u.~T() : u�� ��� �ڿ����� ��ȯ�ǰ�, ���ܸ� ������ ����
//							
//							- �ڿ��� ��ȯ�ǰ� ���� �� �ڸ����� ���ο� ��ü�� �Ҵ� �� �� �־�� ��
//							- �׷��� ���۷��� Ÿ���� �ѹ� ��ü�� �����ϸ� �ٸ� ��ü�� �����ϴ°��� �Ұ��� (not re-assignable)
//								-> �̶����� C++ �� ���۷��� Ÿ���� Destructible ���� �ʴٰ� ���� ������ ����
//								-> �ݸ� �����ʹ� �̷��� ������ ���� ������ Destructible �ϴٰ� ���°� ����
//									-> �� �ڵ忡���� A* �� �����ϴ� std::optional �� �������� �۵���
//	
//				- �׷��� std::optional �� ���۷����� �����ϰ� �ʹٸ�
//					- std::reference_wrapper �� �̿��ϸ� ������
//						- std::reference_wrapper �� ���۷����� �ƴ϶� ���۷���ó�� �۵��ϴ� wrapper ��
//					- get() �� �̿��Ͽ� �����ϰ� �ִ� ��ü�� ������ �� ����
//					- reference_wrapper �� �̿��Ϸ��� std::ref() �� �̿��Ͽ� ��ü�� ������ ��
//	
//		*/
//	
//	}

/*  std::variant  */
#include <iostream>
#include <string>
#include <memory>
#include <variant>

class A
{
public:
	A(int i) {}

	void a() { std::cout << "I am A" << std::endl; }
};

class B
{
public:
	B(int i) {}

	void b() { std::cout << "I am B" << std::endl; }
};

std::variant<std::monostate, A, B> GetDataFromDB(bool is_a)
{
	if (is_a)
		return A(1);
	
	return B(1);
}

int main()
{
	/*  std::variant ����  */
	//	{
	//		std::variant<int, std::string, double> v = 1;
	//		std::cout << std::get<int>(v) << std::endl;
	//	
	//		v = "hello";
	//		std::cout << std::get<std::string>(v) << std::endl;
	//	
	//		v = 3.14;
	//		std::cout << std::get<double>(v) << std::endl;
	//	}


	auto v = GetDataFromDB(true);

	std::cout << v.index() << std::endl;
	std::get<A>(v).a();

	/*
		- std::variant
	
	*/

}