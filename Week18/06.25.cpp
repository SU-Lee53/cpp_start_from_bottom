/*
	06.25 - <untility> �� std::optional, std::variant, std::tuple
*/

// �̹� ������� ��κ� �ּ� C++ 17 �̻���� ��� ������ ��ɵ���

/*  std::optional  */
//	#include <iostream>
//	#include <map>
//	#include <string>
//	#include <optional>	// std::optional �� <utility> �� �ƴ� <optional> �� ��������...
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
#include <iostream>
#include <optional>

class A
{
public:
	A() { std::cout << "����Ʈ ����" << std::endl; }
	A(const A& a) { std::cout << "���� ����" << std::endl; }

	int data;
};

int main()
{
	A a;
	a.data = 5;
	
	// std::optional<A&> maybe_a;	// C2338 : static_assert failed: 'T in optional<T> must meet the Cpp17Destructible requirements (N4950 [optional.optional.general]/3).'
	std::optional<std::reference_wrapper<A>> maybe_a = std::ref(a);

	maybe_a->get().data = 3;
	std::cout << "a.data : " << a.data << std::endl;	// a.data : 3

}