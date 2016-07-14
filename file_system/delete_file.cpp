#include"header.h"

extern vector<int>catalog_free;
extern vector<cataLog> catalog;
extern vector<int>disk_index_free;
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

void delete_folder(string name);
void delete_f(int path, int num);


void delete_file(string command){
	stringstream command_stream(command);
	string command1, command2, name;
	command_stream >> command1;
	command_stream >> command2;
	command_stream >> name;
	if (command2 == "file")
	{

	}
	else if (command2 == "folder")
	{
		delete_folder(name);
		return;
	}
	else
	{
		name = command2;
	}
	int i = 0;
	int flag = 0;
	information clear_info;
	clear_info.name = "clear";
	clear_info.type = -1;
	clear_info.ftype = "clear";
	clear_info.block = -1;
	clear_info.create_time = "clear";
	clear_info.last_edit_time = "clear";
	clear_info.path.clear();
	clear_info.share = 0;
	clear_info.readable = 0;
	clear_info.writeable = 0;
	clear_info.size = 0;
	clear_info.user = -1;
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
			index[catalog[file.id].addr.i_node].info = clear_info;

			//删除目录中的信息
			catalog[file.id].info = clear_info;
			catalog[file.id].addr.c_catalog.clear();
			catalog[file.id].addr.flag = -1;
			catalog[file.id].addr.i_node = -1;
			catalog_free.push_back(file.id);
			
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
		disk_index[block].block.clear();
		disk_index_free.push_back(block);
	}
}

void delete_folder(string name)
{
	int flag = 0;
	int i = 0;
	for (auto folder : catalog[path.back()].addr.c_catalog)
	{
		if (folder.name == name && catalog[folder.id].info.type == 1)
		{
			flag = 1;
			break;
		}
		i++;
	}
	if (!flag)
	{
		cout << "No such folder" << endl;
		return;
	}
	delete_f(path.back(), i);
	vector<child_catalog>::iterator it1;
	it1 = catalog[path.back()].addr.c_catalog.begin() + i;
	catalog[path.back()].addr.c_catalog.erase(it1);
}

void delete_f(int path, int num)
{
	int i = 0;
	int tmpid = catalog[path].addr.c_catalog[num].id;
	information clear_info;
	clear_info.name = "clear";
	clear_info.type = -1;
	clear_info.ftype = "clear";
	clear_info.block = -1;
	clear_info.create_time = "clear";
	clear_info.last_edit_time = "clear";
	clear_info.path.clear();
	clear_info.share = 0;
	clear_info.readable = 0;
	clear_info.writeable = 0;
	clear_info.size = 0;
	clear_info.user = -1;
	for (auto tmp : catalog[tmpid].addr.c_catalog)
	{
		if (catalog[tmp.id].info.type == 0)
		{
			for (auto block1 : disk_index[catalog[tmp.id].info.block].block)
				disk[block1].content = "";
			//释放磁盘i节点为空闲i节点
			ifree(catalog[tmp.id].addr.i_node);
			//释放磁盘块
			free_disk_block(index[catalog[tmp.id].addr.i_node].info.block);
			//磁盘i节点归零
			index[catalog[tmp.id].addr.i_node].info = clear_info;

			//删除目录中的信息
			catalog[tmp.id].info = clear_info;
			catalog[tmp.id].addr.c_catalog.clear();
			catalog[tmp.id].addr.flag = -1;
			catalog[tmp.id].addr.i_node = -1;
			catalog_free.push_back(tmp.id);
		}
		else
		{
			delete_f(tmpid, i);
		}
		i++;
	}
	catalog[tmpid].info = clear_info;
	catalog[tmpid].addr.c_catalog.clear();
	catalog[tmpid].addr.flag = -1;
	catalog[tmpid].addr.i_node = -1;
	catalog_free.push_back(tmpid);
}