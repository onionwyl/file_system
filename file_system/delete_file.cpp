#include"header.h"

extern vector<cateLog> catelog;
extern vector<int> path;
extern i_node index[128];
void ifree(int block);
extern vector<int> disk_stack;;
void delete_file(string command){
	stringstream command_stream(command);
	string command1,name;
	command_stream >> command1;
	command_stream >> name;
	for (auto file : catelog[path.back()].addr.c_catelog)
	{
		if (name == file.name && catelog[file.id].info.type == 0)
		{
			//cout << name << file.name << catelog[file.id].id<<file.id<< endl;
			for (int id1 = 0; id1 <= catelog[file.id].id;id1++)
			{
				if (id1 == file.id)
				{
					//cout << catelog[id1].addr.i_node << endl;
					//磁盘i节点归零
					index[catelog[id1].addr.i_node].info.name = "";
					index[catelog[id1].addr.i_node].info.type = -1;
					index[catelog[id1].addr.i_node].info.block = -1;
					index[catelog[id1].addr.i_node].info.create_time = "";
					index[catelog[id1].addr.i_node].info.path.clear();
					index[catelog[id1].addr.i_node].info.share = 0;
					index[catelog[id1].addr.i_node].info.readable = 0;
					index[catelog[id1].addr.i_node].info.writeable = 0;
					index[catelog[id1].addr.i_node].info.size = 0;
					index[catelog[id1].addr.i_node].info.user = -1;
					//释放磁盘i节点为空闲i节点
					ifree(catelog[id1].addr.i_node);
					//释放磁盘块

				}
			}
		}
	}
	//文件不存在
	//cout << "file"<<" "<<name<<" not exists" << endl;
}
void free_disk_block(int inode)
{
	vector<int>free_disk;
	if (disk_stack.size() == 128)
	{
		cout << "no more size" << endl;
	}
	else
	{
		disk_stack.push_back(inode);
	}
}