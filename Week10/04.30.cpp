
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