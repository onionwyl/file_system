#include"header.h"

extern vector<int> path;
extern vector<cateLog> catelog;

void init()
{
	
	if (path.size() == 0)
		path.push_back(0);
	if (catelog.size() == 0)
	{
		information root_folder;
		address new_addr;
		cateLog new_catlog;
		root_folder.name = "root";
		root_folder.type = 1;
		root_folder.share = 1;
		root_folder.readable = 1;
		root_folder.writeable = 1;
		root_folder.user = 0;
		new_addr.flag = 1;
		new_catlog.id = catelog.size();
		new_catlog.info = root_folder;
		new_catlog.addr = new_addr;
		catelog.push_back(new_catlog);
	}
}