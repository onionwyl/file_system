#include "header.h"
extern vector<int> i_stack;		//空闲i节点,0号存大小
extern vector<int> disk_stack;		//空闲磁盘块
extern i_node index[128];
extern information file_info;
extern vector<cataLog> catalog;
extern i_node index[128];
extern vector<int> path;
extern int free_i;
int ialloc()	//分配空闲i节点
{
	if (i_stack.size() == 0)
	{
		cout << "no more free blocks" << endl;
		return -1;
	}
	else
	{
		free_i = i_stack[i_stack.back()];
		i_stack.pop_back();
		return free_i;
	}
}
void ifree(int block)			//		回收空闲i节点
{
	if (i_stack.size() == 128)
	{
		cout << "no more size" << endl;
	}
	else
	{
		i_stack.push_back(block);
	}
}