#include"header.h"
#include <limits.h>
extern vector<cataLog> catalog;
extern vector<int> path;
extern i_node index[128];
extern vector<int> allocata(int size);
extern vector<disk_Index> disk_index;
int ialloc();
extern int free_i;
vector<string> split(string str, string pattern);
int check_folder(int tmp_path_id, string folder);
int pre_file_id;
int check_file(string fname, int path);
child_catalog child_file;
void rename(string name);
void copy(string command)
{
	stringstream command_stream(command);
	string command1, name, old_path;
	command_stream >> command1;
	command_stream >> name;
	command_stream >> old_path;
	information info_file;			//新的
	vector<int> new_path;
	vector<string> subpath;
	
	int tmp_path;

	//查询原来的name是否存在
	pre_file_id = check_file(name, path.back());
	if (pre_file_id == 0)		//b
	{
		cout << "No such file" << endl;
		return;
	}
	//找到文件将要粘贴的位置
	if (old_path[0] == '/')
	{
		if (old_path == "/")
		{
			new_path.push_back(0);
		}
		else
		{
			tmp_path = 0;
			subpath = split(old_path, "/");
			new_path.push_back(0);
			for (auto p : subpath)
			{
				if (tmp_path = check_folder(tmp_path, p))
				{
					new_path.push_back(tmp_path);
				}
				else
				{
					cout << "no such directory" << endl;
					return;
				}
			}
		}
	}
	if (check_file(name, new_path.back()) != 0)
	{
		cout << "file exists" << endl;
		return;
	}
	info_file = catalog[pre_file_id].info;
	char date[255];
	time_t t = time(0);
	strftime(date, 255, "%Y-%m-%d %H:%M:%S", localtime(&t));
	info_file.last_edit_time = info_file.create_time = date;
	disk_Index new_disk_index;					//分配磁盘块
	new_disk_index.block = allocata(info_file.size);
	if (new_disk_index.block.size() == 0)
	{
		return;
	}
	free_i = ialloc();							//分配i节点
	if (free_i == -1)
	{
		return;
	}
	info_file.path = new_path;
	index[free_i].info = info_file;

	//添加进目录
	cataLog new_catalog;
	new_catalog.id = catalog.size();
	new_catalog.info = info_file;
	new_catalog.addr.flag = 0;
	new_catalog.addr.i_node = free_i;
	catalog.push_back(new_catalog);
	child_file.id = new_catalog.id;
	child_file.name = name;
	catalog[new_path.back()].addr.c_catalog.push_back(child_file);
	disk_index.push_back(new_disk_index);
}
void move(string command)
{
	stringstream command_stream(command);
	string command1, name, old_path;
	command_stream >> command1;
	command_stream >> name;
	command_stream >> old_path;
	int tmp_path;
	int pre_file_id;
	information info_file;			//新的
	vector<int> new_path;
	vector<string> subpath;
	//路径
	if (old_path[0] == '/')
	{
		if (old_path == "/")
		{
			new_path.push_back(0);
			
		}
		tmp_path = 0;
		subpath = split(old_path, "/");
		new_path.push_back(0);
		for (auto p : subpath)
		{
			if (tmp_path = check_folder(tmp_path, p))
			{
				new_path.push_back(tmp_path);
			}
			else
			{
				cout << "no such directory" << endl;
				return;
			}
		}
	}
	pre_file_id = check_file(name, path.back());
	if (pre_file_id == 0)
	{
		cout << "No such file" << endl;
		return;
	}
	if (check_file(name, new_path.back()) != 0)
	{
		cout << "file exists" << endl;
		return;
	}
	char date[255];
	time_t t = time(0);
	strftime(date, 255, "%Y-%m-%d %H:%M:%S", localtime(&t));
	catalog[pre_file_id].info.last_edit_time = catalog[pre_file_id].info.create_time = date;
	catalog[pre_file_id].info.path = new_path;
	index[free_i].info.path = new_path;
	int i = 0;
	for (auto file : catalog[path.back()].addr.c_catalog)
	{
		if (name == file.name && catalog[file.id].info.type == 0)
		{

			//删除子文件目录
			vector<child_catalog>::iterator it1;
			it1 = catalog[path.back()].addr.c_catalog.begin() + i;
			catalog[path.back()].addr.c_catalog.erase(it1);
			break;
		}
		i++;
	}
	cataLog new_catalog;
	new_catalog.id = catalog.size();
	child_file.id = new_catalog.id;
	/*cout << "Do you want rename file " << name <<"? Y or N"<< endl;
	char rename;
	cin >> rename;
	/*if (rename == 'Y')
	/*{	
		string newname;
		/*cout << "new name is:"<<endl;
		cin >> newname;
		if (check_file(newname, path.back()) != 0)
		{
			return;
		}
		child_file.name = newname;
		catalog[pre_file_id].info.name = newname;
		index[free_i].info.name = newname;
		
		rename(newname);
	}
	else if (rename == 'N')
		child_file.name = name;*/
	rename(name);
	catalog[new_path.back()].addr.c_catalog.push_back(child_file);
}
void rename(string name)
{
	cout << "Do you want rename file " << name << "? Y or N" << endl;
	string rename;
	getline(cin, rename);
	if (rename == "Y")
	{
		//cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	cout << "new name is:"<<endl;
		string newname;
		getline(cin, newname);
		if (check_file(newname, path.back()) != 0)
		{
		return;
		}
		child_file.name = newname;
		catalog[pre_file_id].info.name = newname;
		index[free_i].info.name = newname;
	}
	else 
		child_file.name = name;
}