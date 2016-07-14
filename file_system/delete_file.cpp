#include"header.h"

extern vector<cataLog> catalog;
extern vector<disk_Index> disk_index;
extern vector<int> path;
extern i_node index[128];
void ifree(int block);
void free_disk_block(int inode);
extern vector<int> disk_stack;
extern disk_block disk[10240];
extern vector<INAMEindex> inameindex;   //i节点索引
extern vector<IDATEindex> idateindex;
extern vector<ITYPEindex> itypeindex;

void delete_file(string command){
	stringstream command_stream(command);
	string command1, name;
	command_stream >> command1;
	command_stream >> name;
	int i = 0;
	int flag = 0;
	for (auto file : catalog[path.back()].addr.c_catalog)
	{
		if (name == file.name && catalog[file.id].info.type == 0)
		{
			flag = 1;
			for (auto block1 : disk_index[catalog[file.id].info.block].block)
				disk[block1].content = "";
			//释放磁盘i节点为空闲i节点
			ifree(catalog[file.id].addr.i_node);
			//释放磁盘块
			free_disk_block(index[catalog[file.id].addr.i_node].info.block);
			//磁盘i节点归零
			index[catalog[file.id].addr.i_node].info.name = "";
			index[catalog[file.id].addr.i_node].info.type = -1;
			index[catalog[file.id].addr.i_node].info.ftype = "";
			index[catalog[file.id].addr.i_node].info.block = -1;
			index[catalog[file.id].addr.i_node].info.create_time = "";
			index[catalog[file.id].addr.i_node].info.last_edit_time = "";
			index[catalog[file.id].addr.i_node].info.path.clear();
			index[catalog[file.id].addr.i_node].info.share = 0;
			index[catalog[file.id].addr.i_node].info.readable = 0;
			index[catalog[file.id].addr.i_node].info.writeable = 0;
			index[catalog[file.id].addr.i_node].info.size = 0;
			index[catalog[file.id].addr.i_node].info.user = -1;

			//删除目录中的信息
			vector<cataLog>::iterator it;
			it = catalog.begin() + file.id;
			catalog.erase(it);
			//删除子文件目录
			vector<child_catalog>::iterator it1;
			it1 = catalog[path.back()].addr.c_catalog.begin() + i;
			catalog[path.back()].addr.c_catalog.erase(it1);
			//删除文件名索引
			for(unsigned i=0;i<inameindex.size();i++){
                if(inameindex[i].id == catalog[file.id].addr.i_node){
                     std::vector<INAMEindex>::iterator it2 = inameindex.begin()+i;
                     inameindex.erase(it2);
                }
			}
			//删除日期索引
			for(unsigned i=0;i<idateindex.size();i++){
                if(idateindex[i].id==catalog[file.id].addr.i_node){
                     std::vector<IDATEindex>::iterator it3 = idateindex.begin()+i;
                     idateindex.erase(it3);
                }
			}
			//删除文件名索引
			for(unsigned i=0;i<itypeindex.size();i++){
                if(itypeindex[i].id==catalog[file.id].addr.i_node){
                     std::vector<ITYPEindex>::iterator it3 = itypeindex.begin()+i;
                     itypeindex.erase(it3);
                }
			}

			break;
		}
		i++;
	}

	if (!flag)
		cout << "file" << " \"" << name << "\" not exists" << endl;
}
void free_disk_block(int block)
{
	if (disk_stack.size() == 128)
	{
		cout << "no more size" << endl;
	}
	else
	{
		for (auto tmp : disk_index[block].block)
		{
			disk_stack.push_back(tmp);
		}
		vector<disk_Index>::iterator it;
		it = disk_index.begin() + block;
		disk_index.erase(it);
	}
}
