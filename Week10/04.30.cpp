
/*
	04.30 ~ 04.31 STL1 - ���� �����̳� (set, map, multiset, multimap, unordered_set, unordered_map)
*/

/*  ���� �����̳�  */
/*
	- ���� �����̳�
		- Ű(key) - ��(value) ������ �����ϴ� �����̳�
			-> Ư���� Ű�� ������ �̿� �����Ǵ� ���� ������
			-> ���ø� ���̺귯�� �̹Ƿ� Ű, �� ��� ������ Ÿ���� ��ü�� �� ���� ����

		- �̷��� �ڷᱸ���� ��� ���� 2���� ������ �۾��� ������
			1) Ư�� Ű�� ���� �����̳ʿ� �����ϴ��� ���� : OOO �� �����Ϳ� �����ϴ°�?
			2) Ư�� Ű�� �����Ǵ� ���� Ȯ�� : OOO�� �����Ѵٸ� �����Ǵ� ���� �����ΰ�?

		- STL�� ���� �����̳ʴ� �� 2���� �۾��� ���� ������ �����̳ʵ��� ������
			1) set, multiset -> Ű�� �����Ͽ� ���� ������ �� �� ����
			2) map, multimap -> Ű�� ���� ��� �����Ͽ� Ư�� Ű�� �����Ǵ� ���� �� �� ����

*/

/*  std::set  */
//	#include <iostream>
//	#include <set>
//	
//	template <typename T>
//	void print_set(std::set<T>& s)
//	{
//		std::cout << "[ ";
//		for (typename std::set<T>::iterator itr = s.begin(); itr != s.end(); ++itr)
//		{
//			std::cout << *itr << " ";
//		}
//		std::cout << "]" << std::endl;
//	}
//	
//	int main()
//	{
//		std::set<int> s;
//		s.insert(10);
//		s.insert(50);
//		s.insert(20);
//		s.insert(40);
//		s.insert(30);
//		s.insert(20);
//		s.insert(10);
//	
//		std::cout << "������� ���ĵǼ� ���´�" << std::endl;
//		print_set(s);
//	
//		std::cout << "20 �� s �� �����ΰ���? :: ";
//		auto itr = s.find(20);
//		if (itr != s.end())
//			std::cout << "Yes" << std::endl;
//		else
//			std::cout << "No" << std::endl;
//	
//		std::cout << "25 �� s �� �����ΰ���? :: ";
//		itr = s.find(25);
//		if (itr != s.end())
//			std::cout << "Yes" << std::endl;
//		else
//			std::cout << "No" << std::endl;
//	
//		/*
//			- output:
//			������� ���ĵǼ� ���´�
//			[ 10 20 30 40 50 ]
//			20 �� s �� �����ΰ���? :: Yes
//			25 �� s �� �����ΰ���? :: No
//		*/
//	
//		/*
//			- std::set
//				- Ű�� ���� ������ �˰������ ����ϴ� �����̳�
//					-> Ű�� �����ϰ� ���� �������� ����
//	
//				- ���Ҹ� �߰��Ϸ��� insert() �Լ��� �����
//					-> �̶� ������ �����̳ʿ� �ٸ��� "���" ���������� ���� ���ڰ� ����
//					-> ���� �����̳ʴ� ������ �����̳ʿ� �޸� ���Ұ� ��� �ִ��� �߿����� �ʰ�, ���Ұ� �ֳ�/���� �� �߿��ϱ� ����
//					-> insert()�� �ð����⵵�� O(logN) 
//	
//				- �ݺ��ڴ� BidirectionalIterator Ÿ����. �� ������ ��ġ�� ���ҿ��� ������ �� ����, ���������θ� ���� ������
//					-> �׷��� �ݺ��ڸ� �̿��Ͽ� ����غ��� �׻� ���ĵ� ���·� ��µ�. 
//					-> ���Ҹ� �߰��ϰų� �����Ͽ��� �׻� ���ĵ� ���¸� ������
//	
//				- Ư�� ������ ���������� find() �Լ��� �̿��Ͽ� �� �� ����
//					-> �ش��ϴ� ���Ұ� �����ϸ� �̸� ����Ű�� �ݺ��ڸ� ������
//					-> �ش��ϴ� ���Ұ� �������� �ʴ´ٸ� end()�� ������
//					-> find()�� �ð����⵵�� O(logN)
//	
//				- ���� Ư¡���� ������ ������ ������ ���ҵ��� Ʈ���� ���·� ����Ǿ��ֱ� ������
//					-> ��Ȯ���� Red-black tree ���·� �����. �̴� �ڰ� ���� ���� Ž�� Ʈ���� ������
//					-> Red-black tree�� �ڰ� ���� Ʈ���̹Ƿ� ���������� ���� Ʈ��(���� ���� Ʈ��)�� ���°� ��������� �ʰ� ������
//	
//				- ���� set �ȿ��� �ߺ��� ���ҵ��� ����
//					-> �� �����ڵ� ������ 10�� 20�� 2�� �־����� 1���� �����
//					-> �̹� ���� ���Ұ� ������ �׳� insert() ���� ����
//					-> ���Ҹ� �ߺ��Ͽ� �ְ�ʹٸ� multiset�� �̿��ؾ� ��
//	
//				- ������ �����̳ʵ� ó�� ���� ��� for ���� ������
//					-> �ݺ��ڸ� �̿��� for�� ó�� �׻� ���ĵ� ���·� ��µ�
//		*/
//	}

/*  ���� ���� Ŭ���� ��ü�� set�� �ֱ�  */
//	#include <iostream>
//	#include <string>
//	#include <set>
//	
//	template <typename T>
//	void print_set(std::set<T>& s)
//	{
//		for (const auto& elem : s)
//		{
//			std::cout << elem << " " << std::endl;
//		}
//	}
//	
//	template <typename T, typename C>
//	void print_set(std::set<T,C>& s)
//	{
//		for (const auto& elem : s)
//		{
//			std::cout << elem << " " << std::endl;
//		}
//	}
//	
//	class Todo
//	{
//	public:
//		Todo(int priority, std::string job_desc) : priority(priority), job_desc(job_desc) {}
//	
//		bool operator<(const Todo& t) const
//		{
//			if (priority == t.priority)
//				return job_desc < t.job_desc;
//			return priority > t.priority;
//		}
//	
//		friend struct TodoCmp;
//		friend std::ostream& operator<<(std::ostream&, const Todo&);
//	private:
//		int priority;
//		std::string job_desc;
//	};
//	
//	struct TodoCmp
//	{
//		bool operator()(const Todo& t1, const Todo& t2) const
//		{
//			if (t1.priority == t2.priority)
//				return t1.job_desc < t2.job_desc;
//			return t1.priority > t2.priority;
//		}
//	};
//	
//	std::ostream& operator<<(std::ostream& o, const Todo& td)
//	{
//		o << "[�߿䵵: " << td.priority << "] " << td.job_desc;
//		return o;
//	}
//	
//	int main()
//	{
//		//	std::set<Todo> todos;
//		std::set<Todo, TodoCmp> todos;	// ��ü�� ���ϴ� �Լ� ��ü�� �ִٸ� ������ ���� �ص� �����۵���
//	
//	
//		todos.insert(Todo(1, "�� �ϱ�"));
//		todos.insert(Todo(2, "���� ���� �ϱ�"));
//		todos.insert(Todo(1, "���α׷��� ������Ʈ"));
//		todos.insert(Todo(3, "ģ�� ������"));
//		todos.insert(Todo(2, "��ȭ ����"));
//	
//		print_set(todos);
//	
//		std::cout << "-------------" << std::endl;
//		std::cout << "������ ���´ٸ�!" << std::endl;
//		todos.erase(todos.find(Todo(2, "���� ���� �ϱ�")));
//		print_set(todos);
//	
//		/*
//			- output:
//			[�߿䵵: 3] ģ�� ������
//			[�߿䵵: 2] ���� ���� �ϱ�
//			[�߿䵵: 2] ��ȭ ����
//			[�߿䵵: 1] �� �ϱ�
//			[�߿䵵: 1] ���α׷��� ������Ʈ
//			-------------
//			������ ���´ٸ�!
//			[�߿䵵: 3] ģ�� ������
//			[�߿䵵: 2] ��ȭ ����
//			[�߿䵵: 1] �� �ϱ�
//			[�߿䵵: 1] ���α׷��� ������Ʈ
//		*/
//	
//		/*
//			- ���� ���� Ŭ���� ��ü�� set�� �ֱ�
//				- �� �ڵ忡�� operator<�� �����ε� �Ǿ����� �ʰų� TodoCmp �Լ� ��ü�� ���ٸ� ������ ������ �߻���
//					-> set�� ���������� ���ĵ� ���¸� �����ϱ� ���ؼ��� ���Ұ��� �񱳸� ������ ����� �ʿ��ϱ� ������
//	
//				- �̸� ���ؼ� 2���� ����� ����
//					1) operator< �� �����ε�
//						- �����ε� �Լ��� �ݵ�� const ��ü�� ���۷����� �޾ƾ� ��
//							-> ���������� ���Ľ� ��� �ݺ��ڸ� ����ϱ� ������
//						- ���Ұ� ���� ������ �Ǻ��ϱ� ���ؼ� == �����ڸ� ������ ������� ����
//							-> A.operator(B) �� B.operator(A) �Ѵ� false �� ��� A == B�� �ǹ���
//						- Todo Ŭ������ ���� ��Һ��� ������ �켱������ ������ ���� �켱������ ������ ���� ��쵵 ó�����־�� ��
//							-> Todo�� ��� �߿䵵(priority)�� �������� ���� ó������ �ʴ´ٸ� �߿䵵�� ���� ��ü���� ���� ��ü��� �Ǵ���
//							-> �׷��Ƿ� �ߺ��� ������� �ʴ� set������ �߰����� ����
//						- operator< �� ������ ���� ������ �����ؾ� ��
//							- A < A �� false
//							- A < B != B < A
//							- A < B �̰� B < C �̸� A < C
//							- A == B �̸� A < B �� B < A �� �� ����
//							- A == B �̰� B == C �̸� A == C
//								-> �̷��� �����ڸ� strict weak ordering�� �����Ѵٰ� ��
//								-> ���� �ϳ��� �������� ������ ����� �������� ����
//	
//					2) �� �Լ� ��ü�� ����� ���
//						- �� �Լ� ��ü�� ����� �ι�° ���ø� ���ڷ� �Ѱ��ָ� �̸� �������� ��� �񱳸� �����ϴ� set�� ������
//						- ���� �ι�° ���ڷ� �ƹ��͵� �������� ������ �⺻������ std::less<key>�� �����. �̴� �׳� key Ŭ������ operator<�� �񱳸� �������� �ǹ���
//		*/
//	}

/*  std::map  */
//	#include <iostream>
//	#include <map>
//	#include <string>
//	
//	template<typename K, typename V>
//	void print_map(std::map<K, V>& m)
//	{
//		//	for (auto itr = m.begin(); itr != m.end(); ++itr)
//		//		std::cout << itr->first << " " << itr->second << std::endl;
//	
//		// ���� ��� for ���� �̿��� �� �� ����
//		for (const auto& kv : m)
//			std::cout << kv.first << " " << kv.second << std::endl;
//	}
//	
//	template<typename K, typename V>
//	void search_and_print(std::map<K, V>& m, K key)
//	{
//		auto itr = m.find(key);
//		if (itr != m.end())
//			std::cout << key << " ---> " << itr->second << std::endl;
//		else
//			std::cout << key << "��(��) ��Ͽ� �����ϴ�" << std::endl;
//	}
//	
//	int main()
//	{
//		std::map<std::string, double> pitcher_list;
//	
//		pitcher_list.insert(std::pair<std::string, double>("�ڼ���", 2.23));
//		pitcher_list.insert(std::pair<std::string, double>("��Ŀ", 2.93));
//		pitcher_list.insert(std::pair<std::string, double>("�Ǿ���", 2.95));
//	
//		pitcher_list.insert(std::make_pair("������", 3.04));
//		pitcher_list.insert(std::make_pair("�����", 3.05));
//		pitcher_list.insert(std::make_pair("����", 3.09));
//	
//		pitcher_list["����Ʈ"] = 3.56;
//		pitcher_list["������"] = 3.76;
//		pitcher_list["�̸�"] = 3.90;
//	
//		print_map(pitcher_list);
//	
//		std::cout << "�ڼ��� �������? :: " << pitcher_list["�ڼ���"] << std::endl;
//	
//		// �߸��� find - operator[] ���� ����
//		//	std::cout << "������ �������? :: " << pitcher_list["������"] << std::endl;	// ������ �������? :: 0
//		// �߰������� ���� �������� ������� ��µ� -> operator[]�� �ʿ� ���� Ű�� �����ϸ� �ڵ����� ���� ����Ʈ �����ڸ� ȣ���Ͽ� ���Ҹ� �߰���
//	
//		// �ùٸ� find - �� search_and_print() �Լ��� ����
//		search_and_print(pitcher_list, std::string("������"));	// ��������(��) ��Ͽ� �����ϴ�
//		search_and_print(pitcher_list, std::string("�ڼ���"));	// �ڼ��� ---> 2.23
//	
//		// set�� ���������� �ߺ��� ������. �̹� ���� Ű�� �����Ѵٸ� ���߿� ���� insert�� ���õ�
//		pitcher_list.insert(std::pair<std::string, double>("�ڼ���", 2.93));
//		std::cout << "�ڼ��� �������? :: " << pitcher_list["�ڼ���"] << std::endl;	// �ڼ��� �������? :: 2.23
//	
//		/*
//			- output
//			����Ʈ 3.56
//			�ڼ��� 2.23
//			������ 3.76
//			����� 3.05
//			������ 3.04
//			�̸� 3.9
//			�Ǿ��� 2.95
//			��Ŀ 2.93
//			���� 3.09
//			�ڼ��� �������? :: 2.23
//			��������(��) ��Ͽ� �����ϴ�
//			�ڼ��� ---> 2.23
//			�ڼ��� �������? :: 2.23
//		*/
//	
//		/*
//			- std::map
//				- set�� ���� ���������� Ű�� �����Ǵ� ������ ���� ������
//				- std::map<K,V> ���� ���·� �����ϰ� ù��° ���ڿ� Ű�� Ÿ��, �ι�° ���ڿ� ���� Ÿ���� ��
//				- std::pair ��ü�� ���ҵ��� �����
//					-> �ܼ��� 2���� ��ü�� ���� ��ü��
//					-> first, second �� ������ ��ü�� ȣ���� �� �ְ�, map�� ��� first�� Ű, second�� ���� ��
//					-> std::make_pair �Լ��� �̿��ؼ� ���� �� �� ����
//	
//				- map�� ���Ҹ� �߰��ϴ� ����� 3������
//					- pitcher_list.insert(std::pair<std::string, double>("�ڼ���", 2.23));
//						-> ���� pair�� ���� �߰�
//					- pitcher_list.insert(std::make_pair("�ڼ���", 2.23));
//						-> std::make_pair() �Լ��� �̿��� pair�� ����� �߰�
//					- pitcher_list["�ڼ���"] = 2.23;
//						-> operator[]�� �̿��Ͽ� �߰�
//						-> �� ��� �����ϰ� Ű�� �̹� �����Ұ�� ���� ��ü��(���� 2������ ���õ�)
//	
//				- map���� operator[]�� ����� �� ���ǻ���
//					- operator[]�� �̿��ؼ� ���� ã�ų� ������ �� �ʿ� ���� Ű�� �����ϸ� ���� ����Ʈ ���ڸ� �̿��ؼ� ���� �߰��ع���
//					- ���� map���� ���ϴ� ���Ҹ� ã���� �Ѵٸ� find() �Լ��� ����ϴ� ���� �ٶ�����
//						-> find() �Լ��� ��� Ű�� �ʿ� �����ϸ� �ش� pair�� ����Ű�� �ݺ��ڸ� ������
//						-> �ݴ�� Ű�� �ʿ� ���°�� end()�� ��ġ�� ������
//	
//				- map ���� ���� ��� for ���� ��� ������
//		*/
//	}

/*  std::multiset, std::multimap  */
//	#include <iostream>
//	#include <set>
//	#include <map>
//	#include <string>
//	
//	template <typename T>
//	void print_set(const std::multiset<T>& s)
//	{
//		for (const auto& elem : s)
//			std::cout << elem << std::endl;
//	}
//	
//	template <typename K, typename V>
//	void print_map(const std::multimap<K, V>& m)
//	{
//		for (const auto& kv : m)
//			std::cout << kv.first << " " << kv.second << std::endl;
//	}
//	
//	int main()
//	{
//		std::multiset<std::string> s;
//	
//		s.insert("a");
//		s.insert("b");
//		s.insert("a");
//		s.insert("c");
//		s.insert("d");
//		s.insert("c");
//	
//		print_set(s);
//	
//		/*
//			- multiset �κ� output:
//			a
//			a
//			b
//			c
//			c
//			d
//		*/
//	
//		std::multimap<int, std::string> m;
//		m.insert(std::make_pair(1, "hello"));
//		m.insert(std::make_pair(1, "hi"));
//		m.insert(std::make_pair(1, "ahihi"));
//		m.insert(std::make_pair(2, "bye"));
//		m.insert(std::make_pair(2, "baba"));
//		//	m[1]; ����: multimap�� operator[]�� ����� �� ����
//	
//		print_map(m);
//	
//		std::cout << "-------------------------" << std::endl;
//		std::cout << m.find(1)->second << std::endl;
//	
//	
//		std::cout << "-------------------------" << std::endl;
//		
//		auto range = m.equal_range(1);
//		for (auto itr = range.first; itr != range.second; ++itr)
//		{
//			std::cout << itr->first << " : " << itr->second << " " << std::endl;
//		}
//	
//		/*
//			- multimap �κ� output:
//			a
//			a
//			b
//			c
//			c
//			d
//			1 hello
//			1 hi
//			1 ahihi
//			2 bye
//			2 baba
//			-------------------------
//			hello
//			-------------------------
//			1 : hello
//			1 : hi
//			1 : ahihi
//		*/
//	
//		/*
//			- std::multiset, std::multimap
//				- ������ set, map �� �޸� �ߺ��� ����ϴ� ���� �����̳�
//				- multimap�� ��� ������ ����ϴ� operator[]�� ����� �� ����
//					-> �ߺ��� ����ϹǷ� �ߺ��� Ű�� ȣ���ϸ� � ���� �������� �� �� ���� ����
//	
//				- ���� multimap�� �ߺ��� ����ϹǷ� ������ find()�� ��뿡 ������ ����
//					-> find() �Լ��� �����ϱ� ��. �ٸ� multimap�� ��� �ߺ��� Ű�� ������ � ���� ���������� ���� ������ ǥ���� ���� 
//					-> �׷��Ƿ� �������� hello�� ����Ͽ����� �ٸ� STL ����ü�� ���� ���� ������ ��
//	
//				- �̸� ���� multiset, multimap ��� equal_range() ��� �Լ��� ������
//					-> equal_range()�� ���ڷ� ã������ Ű�� �����ϸ� �����Ǵ� ���ҵ��� �ݺ��ڵ� �߿��� ���۰� �� �ٷ� ������ ����Ű�� pair ��ü�� ������
//					-> pair�� �������ֹǷ� first, second �� ���� begin(), end()�� �������. end()�� �ٸ� �͵�� ���������� ���� �ٷ� �ڸ� ����Ŵ
//						-> �׷��Ƿ� first == second ��� �����Ǵ� ���Ұ� ���°���
//		*/
//	}

/*  std::unordered_set, std::unordered_map  */
#include <iostream>
#include <string>
#include <unordered_set>

template <typename K>
void print_unordered_set(const std::unordered_set<K>& m)
{
	for (const auto& elem : m)
		std::cout << elem << std::endl;
}

int main()
{
	std::unordered_set<std::string> s;

	s.insert("hi");
	s.insert("my");
	s.insert("name");
	s.insert("is");
	s.insert("psi");
	s.insert("welcome");
	s.insert("to");
	s.insert("c++");
	
	print_unordered_set(s);

	/*
		- output
		hi
		welcome
		my
		name
		is
		psi
		to
		c++

		++ vscode���� g++�� �̿��Ͽ� ���� �ڵ带 ������ ���
		to
		psi
		is
		welcome
		name
		my
		c++
		hi

		-> STL�� ���� MSVC STL�� ���
		-> ���ĵ��� �ʴ� �����̳��̹Ƿ� �����Ϸ��� �ٲ� ��� ������ �޶���
	*/

	/*
		- std::unordered_set, std::unordered_map
			- ������ set, map �� �޸� insert/erase/find�� ��� O(1)�� �����
				-> Red-Black tree �� ������� �ʰ� �ؽ� �Լ��� ����ϱ� ����
			- �ؽ� �Լ�
	
	*/
}