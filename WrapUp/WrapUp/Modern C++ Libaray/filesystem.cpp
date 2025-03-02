/*
	06.24 - <filesystem>
*/

/*  <filesystem> ���� - ���� ã��  */
//	#include <filesystem>	// since C++ 17
//	#include <iostream>
//	
//	int main()
//	{
//		std::cout << std::boolalpha;
//	
//		std::filesystem::path p("./some_file");
//	
//		std::cout << "Does " << p << " exist? [" << std::filesystem::exists(p) << "]" << std::endl;	// Does "./some_file" exist? [true]
//		std::cout << "Is " << p << " file? [" << std::filesystem::is_regular_file(p) << "]" << std::endl;	// Is "./some_file" file? [true]
//		std::cout << "Is " << p << " directory? [" << std::filesystem::is_directory(p) << "]" << std::endl;	// Is "./some_file" directory? [false]
//	
//		/*
//			- <filesystem> ���� - ����ã��
//				- �ڵ� ����
//					- std::filesystem::path p("./some_file");
//						- <filesystem> ���̺귯���� ���� std::filesystem �̸����� �ȿ� ����
//							-> std::chrono ó�� namespace fs = std::filesystem ���� ����ϸ� ����
//						- path ��ü p �� ����
//							- path(���) �� ������ ��ġ�� ��Ÿ���� ������ �ּ� -> �ڿ��� �ٽ�
//	
//					- std::filesystem::exists(p)
//						- <filesystem> ���� �����̳� ���丮�� �ٷ�� ��� �Լ��� path ��ü�� ���ڷ� ����
//							-> ���� ���� ������ is_regular_file, is_directory �� ����������
//						- exists() �� �ش� ��ο� ������ ������ �����ϴ��� Ȯ���ϰ� ������ true �� ������
//	
//					- std::filesystem::is_regular_file(p)
//						- �ش� ��ġ�� �ִ� ���� �������� Ȯ���Ͽ� ������ true �� ������
//	
//					- std::filesystem::is_directory(p)
//						- �ش� ��ġ�� �ִ� ���� ���丮(����) ��� true �� ������
//				
//				- ��� path
//					- ������ ��ġ�� ��Ÿ���� ������ �ּ�
//					- ��� ���� ��Ŀ��� 2������ ����
//	
//						1) ���� ���
//							- ���� �ֻ��� ���丮(root ���丮)���� ���� ���ϴ� ���ϱ����� ���
//								- windows �� ��� �ֻ��� ���丮�� C:\
//								- linus �� ��� �ֻ��� ���丮�� �׳� / ��� �θ�
//	
//						2) ��� ���
//							- ���� ���α׷��� ����ǰ� �ִ� ��ġ���� �ش� ������ ã�ư��� ���
//	
//					- std::filesystem::path p("./some_file"); �� ���?
//						- �ϴ� ������ C:\ (�������� /) �� �ƴϹǷ� �����δ� �ƴ�
//						- . �� ���� ���丮�� �ǹ��ϹǷ� ���� �� Week18 ���� �ȿ� �����ϴ� some_file �� ����
//	
//					- <filesystem> ���� ��θ� ��Ÿ���� �ٷ� �� �ִ� ���� ����Լ��� �ִ� path Ŭ������ ����
//	
//					- �⺻������ <filesystem> ���� �����̳� ���丮�� �ٷ�� �Լ��� ���� path �� ���ڷ� ����
//	
//		*/
//	}

/*  <filesystem> �� ��� ���� �Լ���  */
//	#include <filesystem>
//	#include <iostream>
//	
//	namespace fs = std::filesystem;
//	
//	int main()
//	{
//		fs::path p("./some_file.txt");
//	
//		std::error_code ec;
//	
//		std::cout << "�� ���� ��� : " << fs::current_path() << std::endl;
//		std::cout << "��� ��� : " << p.relative_path() << std::endl;
//		std::cout << "���� ��� : " << fs::absolute(p, ec) << std::endl;
//		std::cout << "�������� ���� ��� : " << fs::canonical(p) << std::endl;
//	
//		/*
//			- ��� ���� �Լ���
//				- �ڵ� ����
//					- fs::current_path()
//						- ���� ���α׷��� ����Ǵ� ��θ� ����
//						- ��� ��� ��δ� �� ���� ����Ǵ� ��θ� �������� ã�ư��� ����
//	
//					- p.relative_path()
//						- path Ŭ������ ��� �Լ��� �ش� ��ü�� ��� ��θ� ����
//	
//					- fs::absolute(p)
//						- ��� ��θ� ���� ��η� �ٲ���
//						- �ٸ� . �̳� .. ���� ���ʿ��� ��ҵ��� ���Ե� �� ����
//	
//					- fs::canonical(p)
//						- �ش� ������ ��θ� ���� ª�� ��Ÿ�� �� �ִ� �������� ���� ��θ� ����
//						- absolute() �� �޸� ���ʿ��� ��Ҹ� ���ְ� ������
//	
//					- . : ���� ������ ����
//					- .. : ���� ������ ����
//	
//				- �� �Լ����� ��� �Է� ���� ��ο� �ش� ������ ������ ��� ���ܸ� ����
//					-> ���� exists() �� �̿��Ͽ� �����ϴ��� ���� Ȯ���ϴ� ���� ����
//					-> ���ܸ� ó���ϰ� ���� �ʴٸ� ������ ���ڿ� error_code ��ü�� �����ϸ� �� (error_code ��ü���� �޴� �Լ��� ���� �����ε� �Ǿ�����)
//						-> �� ��� ���� �߻��� error_code �� ������ ������
//				
//		*/
//	
//	}

/*  <filesystem> �� ���丮 �۾� - 1. ���丮 ���� ��� ���� ��ȸ  */
//	#include <filesystem>
//	#include <iostream>
//	
//	namespace fs = std::filesystem;
//	
//	int main()
//	{
//		fs::directory_iterator itr(fs::current_path() / "a");
//		while (itr != fs::end(itr))
//		{
//			const fs::directory_entry& entry = *itr;
//			std::cout << entry.path() << std::endl;
//			itr++;
//		}
//	
//		// range based for ����
//		std::cout << std::endl;
//		for (const fs::directory_entry& entry : fs::directory_iterator(fs::current_path() / "a"))
//		{
//			std::cout << entry.path() << std::endl;
//		}
//	
//		// ���� ���丮���� ��ȸ - recursive_directory_iterator
//		std::cout << std::endl;
//		for (const fs::directory_entry& e : fs::recursive_directory_iterator(fs::current_path()))
//		{
//			std::cout << e.path() << std::endl;
//		}
//	
//		/*
//			- ���丮 ��ȸ
//				- std::filesystem::directory_iterator : ���丮�� ���� �����ϱ� ���� �����Ǵ� ���丮 �ݺ���
//				- �ڵ� ����
//					- fs::directory_iterator itr(fs::current_path() / "a");
//						- directory_iterator �� �ٸ� �ݺ��ڿ� �޸� ������ �����ϰ� �����ڿ� ��θ� �������־�� ��
//						- operator / �� �������� �ƴϰ� / �� �߰��Ͽ� ��θ� ����� ����
//							-> ��, / "a" �� /a �� �߰��� ��
//						
//					- while (itr != fs::end(itr))
//						- std::filesystem::end() �� �ش� �ݺ����� ���� ������
//	
//					- const fs::directory_entry& entry = *itr;
//						- �ݺ��ڴ� directory_entry ��� ��ü�� ����Ŵ
//						- directory_entry : ���� �̸�, ũ�� ���� ������ Ŭ����
//	
//					- std::cout << entry.path() << std::endl;
//						- ��� ���
//						- path() �� ���� directory_entry �� ��θ� path �� ������
//	
//					- for (const fs::directory_entry& e : fs::recursive_directory_iterator(fs::current_path()))
//						- std::filesystem::recursive_directory_iterator �� ���丮 ���� ���� ���丮���� ���� ��ȸ�� �� �ִ� �ݺ���
//						- directory_iterator �� range-based for �� ����� �� ����
//		*/
//	}

/*  <filesystem> �� ���丮 �۾� - 2. ���丮 ����  */
//	#include <filesystem>
//	#include <iostream>
//	
//	namespace fs = std::filesystem;
//	
//	int main()
//	{
//		std::cout << std::boolalpha;
//	
//		fs::path p("./a/c");
//		std::cout << "Does " << p << " exist? [" << fs::exists(p) << "]" << std::endl;
//	
//		fs::create_directory(p);
//	
//		std::cout << "Does " << p << " exist? [" << fs::exists(p) << "]" << std::endl;
//		std::cout << "Is " << p << " directory [" << fs::is_directory(p) << "]" << std::endl;
//	
//		fs::path p2("./c/d/e/f");
//		std::cout << "Does " << p2 << " exist? [" << fs::exists(p2) << "]" << std::endl;
//	
//		// fs::create_directory(p2);	// �θ� ���͸� (./c) �� �����Ƿ� ��Ÿ�� ���� �߻�
//		fs::create_directories(p2);
//	
//		std::cout << "Does " << p2 << " exist? [" << fs::exists(p2) << "]" << std::endl;
//		std::cout << "Is " << p2 << " directory [" << fs::is_directory(p2) << "]" << std::endl;
//	
//		system("tree");
//	
//		/*
//			- ���丮 ����
//				- ���� ofstream �� ���� ���������� ���������� ���丮�� ���� �� ������
//				- <filesystem> �� create_directory �� �̿��ϸ� ���丮�� ���� �� ����
//	
//				- �ڵ� ����
//					- fs::create_directory(p); (p �� ./a/c)
//						- create_directory() �� path �� ���ڷ� �޾� �ش� ��ο� �ش��ϴ� ���丮�� ����
//						- create_directory() �� ��� �����ϴ� ���丮�� �θ� ���丮�� �ݵ�� �����ؾ� ���� �� ����
//							- �� ���ϼ�ȸ �������� ./a �� ������ٸ� �������� �۵���
//	
//					- fs::create_directories(p2); (p2 �� ./c/d/e/f)
//						- ���������� ���丮�� ����µ� �θ� ���丮���� �Ѳ����� ���� �� ����
//	
//					- system("tree");
//						- tree ����� ����
//		*/		
//	
//	}

/*  <filesystem> �� ���丮 �۾� - 3. ����/���� ����, ����  */
//	#include <filesystem>
//	#include <iostream>
//	
//	namespace fs = std::filesystem;
//	
//	int main()
//	{
//		// ����
//		fs::path from("./a");
//		fs::path to("./c");
//	
//		fs::copy(from, to, fs::copy_options::recursive | fs::copy_options::skip_existing);
//		
//		system("tree");
//	
//		// ����
//		fs::path p("./a/1.txt");
//		std::cout << "Does " << p << "exist? [" << std::boolalpha << fs::exists(p) << "]" << std::endl;
//		
//		fs::remove(p);
//		std::cout << "Does " << p << "exist? [" << std::boolalpha << fs::exists(p) << "]" << std::endl;
//	
//		std::cout << std::endl;
//	
//		fs::path p2("./c/d");
//		std::cout << "Does " << p2 << "exist? [" << std::boolalpha << fs::exists(p2) << "]" << std::endl;
//		std::error_code err;
//		fs::remove(p2, err);	// �������� : �� ���丮�� �ƴ�
//		std::cout << err.message() << std::endl;	// ���͸��� ��� ���� �ʽ��ϴ�.
//	
//		fs::remove_all(p2, err);	// remove_all �� �̿��ϸ� ���� �� ����
//		std::cout << "Does " << p2 << "exist? [" << std::boolalpha << fs::exists(p2) << "]" << std::endl;
//	
//		/*
//			- ����/���� ����
//				- ���� ofstream �� �̿��ϸ� ���ϱ����� ���簡 ����������, ���丮�� ���簡 �Ұ�������
//				- <filesystem> �� copy �� �̿��ϸ� ���丮���� ���簡 ����
//				- �ڵ� ����
//					- fs::copy(from, to, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
//						- from �� to �� ������
//						- �ڴ� ���� �ɼ����� ��Ʈ����ũ�� �̿��ϹǷ� | (OR) �� �̿��Ͽ� ���� �ɼ��� ���� ������
//						- copy_options ���� �Ʒ��� ���� https://en.cppreference.com/w/cpp/filesystem/copy_options
//	
//							- ������ �̹� ������ ��쿡 ���� �ɼ�
//								- none					: �⺻��(error_code �߻���Ű�ų� ���� ����)
//								- skip_existing			: �̹� �����ϴ� ��� skip
//								- overwrite_existing	: �̹� �����ϴ� ��� ���
//								- update_existing		: �̹� �����ϴ� ������ �� ������ ��� ���
//	
//							- ���� ���丮�� ���� �ɼ�
//								- none					: �⺻��
//								- recursive				: ���� ���丮���� ��������� ����
//	
//							- �ɺ��� ��ũ�� ���� �ɼ�
//								- none					: �⺻��(�ɺ��� ��ũ�� ���󰡼� ���� ����)
//								- copy_symlinks			: �ɺ��� ��ũ�� �ɺ��� ��ũ�� ����
//								- skip_symlinks			: �ɺ��� ��ũ skip
//	
//							- copy() �۾��� ���� �ɼ�
//								- none					: �⺻��
//								- directories_only		: ���丮�� ����
//								- create_symlinks		: ���� ��� ������ �ɺ��� ��ũ�� ����(������ ��ΰ� ���� ��ΰ� �ƴ϶�� ���� ��δ� �ݵ�� �����ο�����)
//								- create_hardlinks		: ���� ��� ������ �ϵ� ��ũ�� ����
//	
//							�� �ɺ��� ��ũ : �������� �ٷΰ���� ���������� ��ũ�̹Ƿ� ũ�Ⱑ ���� ������ �����ϴ��� �˻����� ����. 
//								->���н� �迭�� NTFS �̻��� ���Ͻý����� �����ϴ� �����츸 ����
//							�� �ϵ� ��ũ : ������ �����͸� ����Ű�� 2���� ������ ������ ����� ��
//	
//			- ����/���� ����
//				- remove() : ���丮�� ����
//					- remove() �Լ� ���� �ش� ���丮�� �ݵ�� ����־����
//						-> ������� ������ ���� or error_code ����
//	
//				- remove_all() : ���� ���丮���� ��� ����
//					-> �� ��� ���丮�� ������� �ʾƵ� ���� �� ����
//		
//		*/
//	}

/*  directory_iterator ���� ������ ��  */
//	#include <filesystem>
//	#include <iostream>
//	
//	namespace fs = std::filesystem;
//	
//	int main()
//	{
//		fs::path p("./a");
//	
//		// .txt ������ ���� : Ʋ�� ����
//	
//		//	for (const auto& entry : fs::directory_iterator("./a"))
//		//	{
//		//		const std::string ext = entry.path().extension().generic_string();	// path::string_type �� wstring �̹Ƿ� generic_string() �� ���ľ� string �� ��
//		//		if (ext == ".txt")
//		//		{
//		//			fs::remove(entry.path());
//		//		}
//		//	}
//	
//		// .txt ������ ���� : �ùٸ� ����
//	
//		while (true)
//		{
//			bool is_modified = false;
//			for (const auto& entry : fs::directory_iterator("./a"))
//			{
//				const std::string ext = entry.path().extension().generic_string();
//				if (ext == ".txt")
//				{
//					fs::remove(entry.path());
//					is_modified = true;
//					break;
//				}
//			}
//			if (!is_modified) break;
//		}
//		
//		/*
//			- directory_iterator ���� ������ ��
//				- directory_iterator �� ���丮�� ������ �ٲ�� ��ȿȭ��
//					-> ��ȿȭ �� �ݺ��ڴ� ++ ������ ���� ���丮�� ����Ų�ٴ� ������ �� �� ����
//					-> ���� ����/���丮�� �߰��ǰų� �����Ǹ� ���̻� ����ϸ� �ȵ�
//	
//				- �� ����ó�� ����/�߰��� �ݺ��ڸ� �ʱ�ȭ���־�� �ùٸ��� �۵��� �� ����
//		*/
//	}