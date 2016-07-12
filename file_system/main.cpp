#include "header.h"

vector<int> i_stack;
vector<int> disk_stack;
disk_block disk[10240];
i_node index[128];
vector<i_node_memory> i_node_mem;
vector<cateLog> catelog;
vector<disk_Index> disk_index;
vector<INAMEindex> inameindex;   //i节点索引
vector<IDATEindex> idateindex;
vector<ITYPEindex> itypeindex;
vector<int> path;
int free_i;						//空闲i节点号
void init();
void create_folder(string command);
void change_path(string command);
void show_folder(string  command);
void create(string command);
void delete_file(string command);
void edit(string a);            //编辑
void search_file();
void save();

int main()
{
	string username;
	string password;
	string command;
	string subcommand;
	string temp_path;
	char t;
	init();
	cout << "welcome to system" << endl;
	cout << "please login" << endl;
	while (1)
	{
		username = "";
		password = "";
		cout << "username:";
		cin >> username;
		cout << "password:";
		while ((t = getch()) != '\r')
		{
			password += t;
		}
		if (username == "admin" && password == "admin")
			break;
		else
			cout << endl << "username or password error" << endl;
	}
	system("cls");
	getline(cin, command);
	while (1)
	{
		cout << username << "@filesystem ";
		if (path.size() == 1)
			cout << "/";
		else
		{
			for (auto p : path)
			{
				if (p == 0)
					continue;
				cout << "/" << catelog[p].info.name;
			}
		}
		cout << endl << ">";
		getline(cin, command);
		stringstream command_stream(command);
		command_stream >> subcommand;
		if (subcommand == "cd")
		{
			change_path(command);
		}
		else if (subcommand == "ls")
		{
			show_folder(command);
		}
		else if (subcommand == "create")
		{
			create(command);
		}
		else if (subcommand == "mkdir")
		{
			create_folder(command);
		}
		else if (subcommand == "delete")
		{
			delete_file(command);
		}
		else if (subcommand == "edit")
		{
            edit(command);
		}
		else if (subcommand == "search")
		{
            search_file();
		}
		else
		{
			cout << "command not found" << endl;
		}
		cout << endl;
		save();
	}
}
