#include "header.h"

extern vector<cateLog> catelog;
extern vector<int> disk_stack;		//空闲磁盘块
extern i_node index[128];
extern vector<int> path;
extern vector<disk_Index> disk_index;
extern address addr;
extern vector<INAMEindex> inameindex;   //i节点索引
extern vector<IDATEindex> idateindex;
extern vector<ITYPEindex> itypeindex;
extern vector<int> allocate(int size);
int check_file(string fname,int path);
int ialloc();
extern int free_i;

void create(string command)
{
	child_catelog child_file;
	information file_info;
	stringstream command_stream(command);
	string command1, name, size, share;
	command_stream >> command1;
	command_stream >> name;
	command_stream >> size;
	command_stream >> share ;
	int zhengsize = 0;

	if (name == "")
	{
		cout << "Please input filename" << endl;
		return;
	}
	else
	{
		//判断重名
		if(check_file(name, path.back()))
			return;
		//写入文件信息，磁盘i节点信息
		file_info.name = name;
		file_info.type = 0;
		char date[255];
		time_t t = time(0);
		strftime(date, 255, "%Y-%m-%d %H:%M:%S\n", localtime(&t));
		file_info.last_edit_time = file_info.create_time = date;
		//cout << file_info.create_time << endl;
		file_info.user = 0;
		if (size == "")
		{
			zhengsize = 512;
		}
		else if ((size[(size.size() - 1)] == 'k') || size[(size.size() - 1)] == 'K')
		{
			for (int i = size.size() - 2; i >= 0; i--)
			{
				zhengsize = zhengsize + (size[i] - '0') * (int)pow(10, size.size() - 2 - i);
			}
		}

		else if ((size[(size.size() - 1)] == 'm') || size[(size.size() - 1)] == 'M')
		{
			for (int i = size.size() - 2; i >= 0; i--)
			{
				zhengsize += (size[i] - '0') * (int)pow(10, size.size() - 2 - i);
			}
			zhengsize = zhengsize * 1000;
		}
		else
		{
			cout << "size is illegal" << endl;
			return;
		}
		file_info.size = zhengsize;
		disk_Index new_disk_index;					//分配磁盘块
		new_disk_index.block = allocate(file_info.size);
		if (new_disk_index.block.size() == 0)
		{
			return;
		}
		if (share == "n")
		{
			file_info.share = 0;
			file_info.readable = 0;
			file_info.writeable = 0;
		}
		else if (share == "swr" || share == "srw")
		{
			file_info.share = 1;
			file_info.readable = 1;
			file_info.writeable = 1;

		}
		else if (share == "sr")
		{
			file_info.share = 1;
			file_info.readable = 1;
			file_info.writeable = 0;
		}
		else if (share == "")
		{
			file_info.share = 0;
			file_info.readable = 0;
			file_info.writeable = 0;

		}
		else{
			cout << "command is not exists" << endl;
			return;
		}
		free_i = ialloc();
		if (free_i == -1)
		{
			return;
		}
		file_info.path = path;
		file_info.block = disk_index.size();
		index[free_i].info = file_info;

		INAMEindex new_inameindex;                       //建立文件名索引
		new_inameindex.id=free_i;
		new_inameindex.name=index[free_i].info.name;
		inameindex.push_back(new_inameindex);

		IDATEindex new_idateindex;                      //建立日期索引
		new_idateindex.id=free_i;
		new_idateindex.date=index[free_i].info.create_time;
		inameindex.push_back(new_inameindex);

        ITYPEindex new_itypeindex;                      //建立类型索引
		new_itypeindex.id=free_i;
		new_itypeindex.type=index[free_i].info.ftype;
		itypeindex.push_back(new_itypeindex);

		cateLog new_catelog;
		new_catelog.id = catelog.size();
		new_catelog.info = file_info;
		new_catelog.addr.flag = 0;
		new_catelog.addr.i_node = free_i;
		catelog.push_back(new_catelog);
		child_file.id = new_catelog.id;
		child_file.name = name;
		catelog[path.back()].addr.c_catelog.push_back(child_file);
		disk_index.push_back(new_disk_index);		//磁盘索引内容增加



	}

}

//分配空闲磁盘块
vector<int> allocate(int size)
{
	vector<int> free_block;
	int block_num = ceil(size / BLOCKSIZ );
	if (disk_stack.size() < block_num)
	{
		cout << "no more free blocks" << endl;
		return free_block;
	}
	else
	{

		for (int i = 0; i < block_num; i++)
		{
			free_block.push_back(disk_stack.back());
			disk_stack.pop_back();
		}
		return free_block;
	}
}
//检查重名
int check_file(string fname, int path)
{
	for (auto file : catelog[path].addr.c_catelog)
	{
		if (fname == file.name && catelog[file.id].info.type == 0)
		{
			cout << "create: Cannot create file \"" << fname << "\":file exists" << endl;
			return file.id;
		}
	}
	return 0;
}
