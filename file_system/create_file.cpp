#include "header.h"
#include<time.h>
#include<math.h>
information file_info;
child_catelog child_file;
extern vector<int> disk_stack;		//空闲磁盘块
extern i_node index[128];
extern vector<int> path;
extern int free_i;
extern vector<disk_Index> disk_index;
vector<int> allocate();
void create(string command)
{
	stringstream command_stream(command);
	string command1, name, size, share;
	command_stream >> command1;
	command_stream >> name;
	command_stream >> size;
	command_stream >> share;
	int zhengsize = 0;
	/*while (child_file.name != "\n" && child_file.id == path[path.size() - 2])
	{
	if (child_file.name == name)		//查重名
	{
	cout << "filename has exists" << endl;
	return;
	}
	}*/
	if (name == "")
	{
		cout << "Please input filename" << endl;
		return;
	}
	else
	{
		//写入文件信息，磁盘i节点信息
		file_info.name = name;
		file_info.type = 0;
		time_t t;
		time(&t);
		file_info.create_time = ctime(&t);
		file_info.user = 0;
		if ((size[(size.size() - 1)] == 'k') || size[(size.size() - 1)] == 'K')
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
		else if (size == ""){
			zhengsize = 512;

		}
		file_info.size = zhengsize;
		if (share == "n")
		{
			file_info.share = 0;
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
		}
		else{
			cout << "command is not exists" << endl;
		}

		file_info.path.push_back(path[path.size() - 1]);
		file_info.block = disk_index.size();
		index[free_i].info = file_info;
		disk_Index new_disk_index;					//分配磁盘i节点
		new_disk_index.block = allocate();
		if (new_disk_index.block.size() == 0)
		{
			return;
		}
		disk_index.push_back(new_disk_index);		//磁盘索引内容增加
	}

}

vector<int> allocate()
{

	vector<int> free_block;
	int block_num = file_info.size / BLOCKSIZ + 1;
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
