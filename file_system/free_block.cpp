#include "header.h"
//©уоп╢еел©И╥жеД
extern vector<int> i_stack;		//©уопi╫з╣Ц,0╨е╢Ф╢Сп║
extern vector<int> disk_stack;		//©уоп╢еел©И
extern i_node index[128];
extern int free_i;
extern information file_info;
int ialloc()	//╥жеД©уопi╫з╣Ц
{
	if (i_stack.size() == 128)
	{
		cout << "no more free blocks" << endl;
		return 0;
	}
	else
	{
		free_i = i_stack[i_stack.size() - 1];
		i_stack.pop_back();
		return free_i;
	}
}
