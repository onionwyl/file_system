#include"header.h"

extern vector<int> path;
extern vector<cateLog> catelog;
vector< string> split(string str, string pattern);

int check_folder(int tmp_path_id, string folder);

void create_folder(string command)
{
	information new_information;
	address new_address;
	cateLog new_catelog;
	child_catelog new_child;
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
		cout << "mkdir: Cannot create folder\"" << folder_name << "\":directory exists" << endl;
		return;
	}
	new_information.name = folder_name;
	new_information.type = 1;
	new_information.share = 1;
	new_information.readable = 1;
	new_information.writeable = 1;
	new_information.user = 0;
	new_address.flag = 1;
	new_catelog.id = catelog.size();
	new_catelog.addr = new_address;
	new_catelog.info = new_information;
	catelog.push_back(new_catelog);

	new_child.name = folder_name;
	new_child.id = new_catelog.id;
	catelog[path.back()].addr.c_catelog.push_back(new_child);
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
	for (auto name : catelog[path.back()].addr.c_catelog)
	{
		cout << name.name << " ";
	}
	cout << endl;
}

int check_folder(int tmp_path_id, string folder)
{
	for (auto log : catelog[tmp_path_id].addr.c_catelog)
	{
		if (log.name == folder && catelog[log.id].info.type == 1)
			return log.id;
	}
	return 0;
}