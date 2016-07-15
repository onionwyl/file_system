#include"header.h"
#include"md5.h"
extern vector<User> user;
extern int username_id;
void save_user();

void load_user()
{
	ifstream f;
	int tmp, i;
	f.open("user.txt");
	if (!f)
	{
		User new_user;
		new_user.id = 0;
		new_user.username = "admin";
		char *passwd = "admin";
		new_user.password = MD5Encode(passwd);
		user.clear();
		user.push_back(new_user);
		username_id = 0;
		save_user();
	}
	else
	{
		f >> tmp;
		for (i = 0; i < tmp; i++)
		{
			User new_user;
			f >> new_user.id >> new_user.username >> new_user.password;
			user.push_back(new_user);
		}
	}
	f.close();
}

void save_user()
{
	ofstream f;
	f.open("user.txt");
	f << user.size() << endl;
	for (auto tmp : user)
	{
		f << tmp.id << " " << tmp.username << " " << tmp.password << endl;
	}
	f.close();
}

void add_user(string command)
{
	stringstream command_stream(command);
	string subcommand, username, password, c_password;
	command_stream >> subcommand;
	command_stream >> username;
	int i = 0;
	if (username_id != 0)
	{
		cout << "You don't have permission to create a user" << endl;
		return;
	}
	if (user.size() == 8)
	{
		cout << "User full" << endl;
		return;
	}
	while (i < 3)
	{
		cout << "password:";
		char t;
		while ((t = _getch()) != '\r')
		{
			if (t == '\b')
			{
				password = password.substr(0, password.length() - 1);
			}
			else
				password += t;
		}
		cout << endl;
		cout << "retype password:";
		while ((t = _getch()) != '\r')
		{
			if (t == '\b')
			{
				c_password = c_password.substr(0, c_password.length() - 1);
			}
			else
				c_password += t;
		}
		cout << endl;
		if (password != c_password)
		{
			cout << "Sorry, passwords do not match." << endl;
			i++;
		}
		else
			break;
	}
	if (i == 3)
	{
		cout << "Have exhausted maximum number of retries for service." << endl;
		return;
	}
	User new_user;
	new_user.id = user.size();
	new_user.username = username;
	char *passwd = new char[255];
	for (i = 0; i <= password.length(); i++)
		passwd[i] = password[i];
	passwd[i] = '\0';
	new_user.password = MD5Encode(passwd);
	user.push_back(new_user);
	cout << "user " << username << "  add successfully" << endl;
	save_user();
}

int check_user(string username, string password)
{
	for (auto tmp : user)
	{
		char *passwd = new char[255];
		int i;
		for (i = 0; i <= password.length(); i++)
			passwd[i] = password[i];
		passwd[i] = '\0';
		if (tmp.username == username && tmp.password == MD5Encode(passwd))
		{
			username_id = tmp.id;
			return 1;
		}
	}
	return 0;
}

void delete_user(string command)
{
	if (username_id != 0)
	{
		cout << "You don't have permission to delete user" << endl;
		return;
	}
	stringstream command_stream(command);
	string subcommand, username, password;
	command_stream >> subcommand;
	command_stream >> username;
	int j = 0;
	if (username == "admin")
	{
		cout << "You can't delete admin user" << endl;
		return;
	}
	int num;
	for (num = 0; num < user.size(); num++)
	{
		if (user[num].username == username)
			break;
	}
	if (num == user.size())
	{
		cout << "Username no fount" << endl;
		return;
	}
	while (j < 3)
	{
		cout << "Please enter admin password to confirm:";
		char t;
		while ((t = _getch()) != '\r')
		{
			if (t == '\b')
			{
				password = password.substr(0, password.length() - 1);
			}
			else
				password += t;
		}
		cout << endl;
		char *passwd = new char[255];
		int i;
		for (i = 0; i <= password.length(); i++)
			passwd[i] = password[i];
		passwd[i] = '\0';
		if (user[username_id].password == MD5Encode(passwd))
			break;
		cout << "Password error. ";
		j++;
	}
	if (j == 3)
	{
		cout << "Have exhausted maximum number of retries for service." << endl;
		return;
	}
	
	vector<User>::iterator it;
	it = user.begin() + num;
	user.erase(it);
	save_user();
	cout << "User " << username << " delete successfully" << endl;
	
}

void change_password(string command)
{
	stringstream command_stream(command);
	string subcommand, username, password, c_password;
	command_stream >> subcommand;
	command_stream >> username;
	int j = 0;
	int num;
	for (num = 0; num < user.size(); num++)
	{
		if (user[num].username == username)
			break;
	}
	if (num == user.size())
	{
		cout << "Username no fount" << endl;
		return;
	}
	if (username_id != 0 && username_id != num)
	{
		cout << "You can't change other's password" << endl;
		return;
	}
	int i = 0;
	while (i < 3)
	{
		cout << "password:";
		char t;
		while ((t = _getch()) != '\r')
		{
			if (t == '\b')
			{
				password = password.substr(0, password.length() - 1);
			}
			else
				password += t;
		}
		cout << endl;
		cout << "retype password:";
		while ((t = _getch()) != '\r')
		{
			if (t == '\b')
			{
				c_password = c_password.substr(0, c_password.length() - 1);
			}
			else
				c_password += t;
		}
		cout << endl;
		if (password != c_password)
		{
			cout << "Sorry, passwords do not match." << endl;
			i++;
		}
		else
			break;
	}
	if (i == 3)
	{
		cout << "Have exhausted maximum number of retries for service." << endl;
		return;
	}
	char *passwd = new char[255];
	for (i = 0; i <= password.length(); i++)
		passwd[i] = password[i];
	passwd[i] = '\0';
	user[num].password = MD5Encode(passwd);
	save_user();
	cout << "password changed successfully" << endl;
}