#include"header.h"

extern vector<int> path;
extern vector<int> catalog_free;
extern vector<cataLog> catalog;
vector< string> split(string str, string pattern);
extern int username_id;

int check_folder(int tmp_path_id, string folder);

void create_folder(string command)
{
	information new_information;
	address new_address;
	cataLog new_catalog;
	child_catalog new_child;
	stringstream command_stream(command);
	string subcommand, folder_name, share;
	command_stream >> subcommand;
	command_stream >> folder_name;
	command_stream >> share;
	if (folder_name == "")
	{
		cout << "mkdir: Please enter a directory name" << endl;
		return;
	}
	if (check_folder(path.back(), folder_name))
	{
		cout << "mkdir: Cannot create folder \"" << folder_name << "\":directory exists" << endl;
		return;
	}
	new_information.name = folder_name;
	new_information.type = 1;
	new_information.ftype = "folder";
	new_information.share = 1;
	new_information.readable = 1;
	new_information.writeable = 1;
	new_information.user = username_id;
	new_information.size = 0;
	new_information.block = -1;
	char date[255];
	time_t t = time(0);
	strftime(date, 255, "%Y-%m-%d %H:%M:%S", localtime(&t));
	new_information.create_time = date;
	new_information.last_edit_time = date;
	new_information.path = path;
	new_address.flag = 1;
	new_address.i_node = -1;
	if (catalog_free.size() == 0)
	{
		new_catalog.id = catalog.size();
		new_catalog.addr = new_address;
		new_catalog.info = new_information;
		catalog.push_back(new_catalog);
	}
	else
	{
		new_catalog.id = catalog_free.back();
		new_catalog.addr = new_address;
		new_catalog.info = new_information;
		catalog[catalog_free.back()] = new_catalog;
		catalog_free.pop_back();
	}

	new_child.name = folder_name;
	new_child.id = new_catalog.id;
	catalog[path.back()].addr.c_catalog.push_back(new_child);
}

void change_path(string command)
{
	stringstream command_stream(command);
	string subcommand, cd_path;
	vector<string> subpath;
	vector<int> new_path;
	int tmp_path;
	command_stream >> subcommand;
	command_stream >> cd_path;
	if (cd_path == "..")
	{
		if (path.size() == 1)
			return;
		path.pop_back();
	}
	else if (cd_path[0] == '/')
	{
		if (cd_path == "/")
		{
			new_path.push_back(0);
			path = new_path;
			return;
		}
		tmp_path = 0;
		subpath = split(cd_path, "/");
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
		path = new_path;
	}
	else
	{
		tmp_path = path.back();
		subpath = split(cd_path, "/");
		new_path = path;
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
		path = new_path;
	}
}

void show_folder(string  command)
{

	for (auto name : catalog[path.back()].addr.c_catalog)
	{
		if (catalog[name.id].info.user == username_id || username_id == 0 || catalog[name.id].info.share == 1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			if (catalog[name.id].info.type == 1)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			cout << name.name << " ";
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
	cout << endl;
}

int check_folder(int tmp_path_id, string folder)
{
	for (auto log : catalog[tmp_path_id].addr.c_catalog)
	{
		if (log.name == folder && catalog[log.id].info.type == 1)
			return log.id;
	}
	return 0;
}
