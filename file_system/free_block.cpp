#include "header.h"
//©уоп╢еел©И╥жеД
extern vector<int> i_stack;		//©уопi╫з╣Ц,0╨е╢Ф╢Сп║
extern vector<int> disk_stack;		//©уоп╢еел©И
extern i_node index[128];
extern information file_info;
extern int free_i;
int ialloc()	//╥жеД©уопi╫з╣Ц
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
