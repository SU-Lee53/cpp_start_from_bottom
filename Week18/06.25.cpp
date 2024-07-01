/*
	06.25 - std::optional, std::variant, std::tuple
*/

/*  std::optional (C++ 17)  */
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

/*  std::variant (C++ 17)  */
//	#include <iostream>
//	#include <string>
//	#include <memory>
//	#include <variant>
//	
//	class A
//	{
//	public:
//		A(int i) {}
//	
//		void a() { std::cout << "I am A" << std::endl; }
//	};
//	
//	class B
//	{
//	public:
//		B(int i) {}
//	
//		void b() { std::cout << "I am B" << std::endl; }
//	};
//	
//	std::variant<A, B> GetDataFromDB(bool is_a)
//	{
//		if (is_a)
//			return A(1);
//		
//		return B(1);
//	}
//	
//	int main()
//	{
//		/*  std::variant ����  */
//		//	{
	//		std::variant<int, std::string, double> v = 1;
	//		std::cout << std::get<int>(v) << std::endl;
	//	
	//		v = "hello";
	//		std::cout << std::get<std::string>(v) << std::endl;
	//	
	//		v = 3.14;
	//		std::cout << std::get<double>(v) << std::endl;
	//	}
//	
//	
//		auto v = GetDataFromDB(true);
//	
//		std::cout << v.index() << std::endl;	// 0
//		std::get<A>(v).a();	// I am A
//		// std::get<B>(v).b();	// bad_variant_access ���� �߻�
//	
//		std::get<0>(v).a();	// I am A
//	
//		/*
//			- std::variant
//				- ������ ����ü : ������ Ÿ�ӿ� ������ �������� Ÿ�Ե� �߿� �� ���� Ÿ���� ��ü�� �����ϴ� Ŭ����
//				- std::variant �� �ϴ� ���� ����ü(union) ���ε� ���������� ����ü�� �߸����� �ſ� ������ �� ����
//				- std::variant �� std::optional ó�� ��ü ���Խÿ� �����Ҵ��� �߻����� ���� -> ��ü�� �����ϴµ� ������尡 �ſ� ����
//				- std::variant �� std::optional �� ���������� ���۷��� Ÿ���� �ȵ� -> ���۷����� std::reference_wrapper �� �̿�
//				- std::variant �� ũ��� �⺻������ ���� ������ Ÿ�Ե� �� ���� ū Ÿ���� ũ�⸦ ����
//				- std::variant �� ���ø� ���ڷ� ���� Ÿ���� ������ �����ϸ� ������ ������ �߻��� -> �����ϴ� ��ü���� Ÿ������ �����ϱ� ����
//					- ��, std::variant<std::string, std::string> ���� �ڵ�� ������ ����
//	
//				- �ڵ� ����
//					- std::variant<int, std::string, double> v = 1;
//						- �̷������� ����� std::variant ��ü v �� int, string, double Ÿ���� ���� ������ ���� �� ����
//						- �⺻������ variant ��ü�� ������� �� ����
//							- ���� �� �ڵ带 1�� �ʱ�ȭ���� ������ 0 �� �� -> ����Ʈ �����ڸ� ȣ������ �ǹ�
//	
//					- std::variant<std::monostate, A, B> GetDataFromDB(bool is_a)
//						- GetDataFromDB() �Լ��� ���� Ÿ���� A Ȥ�� B ���� �ϳ��� ���� �� �ִ� variant �� ����
//						- std::monostate
//							- A �� B ��� ����Ʈ �����ڰ� ���� ������ �Ѹ����δ� variant ��ü�� �ʱ�ȭ�� �� ����(variant �� ������� �� �����Ƿ�)
//							- �̸� �ذ��ϱ� ���� std::monostate �� �̿��ϸ� ����ִ� variant ��ü�� ��Ÿ�� �� ����
//							- ���� A �� B �� �ϳ��� ����Ʈ �����ڰ� ������ std::monostate �� ������� �ʾƵ� ��
//							- ��� �� �ڵ�� ����Ÿ�� ���� �κ��̶� std::monostate ���̵� �� ������ ���� ����Ϸ��� �ʿ���
//	
//					- v.index()
//						- v�� ���° Ÿ������ �˷���
//						- ��Ÿ���Ե� ���� Ÿ������ ���� �˷��ִ� �Լ��� ���°����� ����
//	
//					- std::get<A>(v).a();
//						- ������ ���ϴ� Ÿ���� �̾Ƴ��ִ� �Լ�
//						- std::get(0)(v) �� �ص� �����ϰ� A ��ü�� �̾���
//						- ���� �� �ڵ带 std::get<B>(v).b() �� �ٲٸ� bad_variant_access ��� ���ܸ� ����
//	
//				- std::variant �� ���ƺ����� ���̽�ó�� Ÿ�Կ� �������� �ʰ� �����Ӱ� ���α׷��� �ϴ°��� ���������� ����
//					- ���̽��� �⺻������ ����Ÿ�� ����̰�, C++ �� ��� Ÿ���� ������Ÿ�ӿ� ���� �����ؾ��ϱ� ����
//					- ����, ������ �� �ȿ��� Ÿ�� ���������� ����������(���ø� ����) ������ ���������� ���ϴٴ°��� �˾Ƶξ�� ��
//		*/
//	
//	}

/*  std::tuple (C++ 11)  */
//	#include <iostream>
//	#include <string>
//	#include <tuple>
//	
//	int main()
//	{
//		std::tuple<int, double, std::string> tp;
//		tp = std::make_tuple(1, 3.14, "hi");
//	
//		std::cout << std::get<0>(tp) << ", " << std::get<1>(tp) << ", " << std::get<2>(tp) << std::endl;
//	
//		std::get<float>(tp);
//	
//		/*
//			- std::tuple
//				- ������ ũ���� ���� �ٸ� Ÿ���� ������ ���� ����
//					-> ���̽��� �װͰ� ���� ������
//	
//				- �ڵ� ����
//					- std::tuple<int, double, std::string> tp;
//						- ��ó�� ������ tuple ��ü���� int, double, string Ÿ���� ��ü�� ������
//						- std::variant �� �޸� ���� Ÿ���� �� �־ ���� ����
//						- ���ø� ���ڷ� �� ������� ���� ������
//	
//					- tp = std::make_tuple(1, 3.14, "hi");
//						- std::make_tuple() �� �̿��� tuple ��ü�� ����
//					
//					- std::cout << std::get<0>(tp) << ", " << std::get<1>(tp) << ", " << std::get<2>(tp) << std::endl;
//						- ������ ���ҿ� �����ϱ� ���� std::get �Լ��� �̿�
//							-> ���ø� ���ڿ� ���° ���ҿ� ���������� �������ָ� ��
//						- std::variant �� get<T> ó�� Ÿ���� ���� ����ص� ������
//							-> �ٸ� �̶� ���ø� ���ڷ� ������ Ÿ���� ������ ���ܰ� �߻���
//							-> ����, ������ �����ϴ� Ÿ���� �����ص� ���ܰ� �߻���. ��Ȯ�� � ���� �������� �𸣱� ����
//		
//		*/
//	}

/*  ������ ���ε� Structured binding (C++ 17)  */
#include <iostream>
#include <string>
#include <tuple>
#include <map>
std::tuple<int, std::string, bool> GetStudent(int id)
{
	if (id == 0)
		return std::make_tuple(30, "ö��", true);
	else
		return std::make_tuple(28, "����", false);
}

int main()
{
	auto student = GetStudent(1);

	// ������ ���ε� ���� ����
	// int age = std::get<0>(student);
	// std::string name = std::get<1>(student);
	// bool is_male = std::get<2>(student);

	// ������ ���ε� ����
	auto [age, name, is_male] = student;

	std::cout << "�̸� : " << name << std::endl;	// �̸�: ����
	std::cout << "���� : " << age << std::endl;	// ����: 28
	std::cout << "����? : " << std::boolalpha << is_male << std::endl;	// ����? : false


	std::map<int, std::string> m = { {3, "hi"}, {5, "hello"} };
	for (auto& [key, val] : m)
	{
		std::cout << "key : " << key << " value : " << val << std::endl;
	}

}