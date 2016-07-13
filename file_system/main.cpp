#include"header.h"
vector<int> i_stack;
vector<int> disk_stack;
disk_block disk[10240];
i_node index[128];
vector<i_node_memory> i_node_mem;
vector<cataLog> catalog;
vector<disk_Index> disk_index;
vector<INAMEindex> inameindex;   //i节点索引
vector<IDATEindex> idateindex;
vector<ITYPEindex> itypeindex;
vector<int> path;
vector<User> user;
int username_id;
int free_i;						//空闲i节点号
void init();
void create_folder(string command);
void change_path(string command);
void show_folder(string  command);
void create(string command);
void delete_file(string command);
void edit(string a);            //编辑
void search_file(string command);
void open_file(string command);
bool compare_arry(vector<int> a, vector<int> b);
int find_block(string name);
void close_file(string command);
void save();
void copy(string command);
void move(string command);
void rename(string name);
void backstage();

int main()
{
	User new_user;                       //初始化用户信息
	new_user.username = "admin";
	new_user.password = "admin";
	user.push_back(new_user);

	string username;
	string password;
	string command;
	string subcommand;
	string temp_path;
	char t;
	init();
	save();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
	cout << "welcome to system" << endl;
	cout << "please login" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
	while (1)
	{
		username = "";
		password = "";
		cout << "username:";
		cin >> username;
		cout << "password:";
		while ((t = _getch()) != '\r')
		{
			if (t == '\b')
			{
				password = password.substr(0, password.length() - 1);
			}
			else
				password += t;
		}
		if (username == user[0].username && password == user[0].password){   //只有一个用户默认0,多个用户需要遍历
			username_id = user[0].id;
			break;
		}
		else{
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
			cout << endl << "username or password error" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
        }
	}
	system("cls");
	getline(cin, command);
	while (1)
	{
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);
		cout << username;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);
		cout << "@filesystem ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
		if (path.size() == 1)
			cout << "/";
		else
		{
			for (auto p : path)
			{
				if (p == 0)
					continue;
				cout << "/" << catalog[p].info.name;
			}
		}
		cout << endl << ">";
		getline(cin, command);
		stringstream command_stream(command);
		command_stream >> subcommand;
		if (subcommand == "")
		{

		}
		else if (subcommand == "cd")
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
			search_file(command);
		}
		else if (subcommand == "open")
		{
			open_file(command);
		}
		else if (subcommand == "close")
		{
			close_file(command);
		}
		else if (subcommand == "cp")
		{
			copy(command);
		}
		else if (subcommand == "mv")
		{
			move(command);
		}
		else if (subcommand == "bs"){
            backstage();
		}
		else
		{
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
			cout << "command not found" << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
		}
		cout << endl;
		save();
		command = "";
		subcommand = "";
	}
}
