#include"header.h"

extern vector<int> i_stack;
extern vector<int> disk_stack;
extern disk_block disk[10240];
extern i_node index[128];
extern vector<i_node_memory> i_node_mem;
extern vector<cataLog> catalog;
extern vector<disk_Index> disk_index;
extern vector<INAMEindex> inameindex;   //i½ÚµãË÷Òý
extern vector<IDATEindex> idateindex;
extern vector<ITYPEindex> itypeindex;
extern vector<int> path;
extern vector<User> user;
void init()
{
	fstream f;
	f.open("disk.txt", ios::in);
	if (!f)
	{
		for (int i = 0; i < 10240; i++){
			disk[i].content = "";
		}
		if (path.size() == 0)
			path.push_back(0);
		if (catalog.size() == 0)
		{
			information root_folder;
			address new_addr;
			cataLog new_catlog;
			root_folder.name = "root";
			root_folder.type = 1;
			root_folder.ftype = "folder";
			root_folder.share = 1;
			root_folder.readable = 1;
			root_folder.writeable = 1;
			root_folder.user = 0;
			root_folder.size = 0;
			root_folder.block = -1;
			root_folder.path = path;
			char date[255];
			time_t t = time(0);
			strftime(date, 255, "%Y-%m-%d %H:%M:%S", localtime(&t));
			root_folder.create_time = date;
			root_folder.last_edit_time = date;
			new_addr.flag = 1;
			new_addr.i_node = -1;
			new_catlog.id = catalog.size();
			new_catlog.info = root_folder;
			new_catlog.addr = new_addr;
			catalog.push_back(new_catlog);
		}
		for (int i = 0; i < 128; i++)
			disk_stack.push_back(i);
		for (int i = 0; i < 128; i++)
		{
			i_stack.push_back(i);
		}
	}
	else
	{
		int size, i, j, tmp, tmp1;
		string tmpstr, tmpstr1;
		if (path.size() == 0)
			path.push_back(0);
		f >> size;
		for (i = 0; i < size; i++)
		{
			f >> tmp;
			i_stack.push_back(tmp);
		}
		f >> size;
		for (i = 0; i < size; i++)
		{
			f >> tmp;
			disk_stack.push_back(tmp);
		}
		for (i = 0; i < 128; i++)
		{
			f >> tmp;
			if (tmp == 0)
			{
				index[i].info.name = "";
				index[i].info.type = -1;
				index[i].info.ftype = "";
				index[i].info.user = -1;
				index[i].info.create_time = "";
				index[i].info.last_edit_time = "";
				index[i].info.path.clear();
				index[i].info.share = 0;
				index[i].info.readable = 0;
				index[i].info.writeable = 0;
				index[i].info.size = 0;
				index[i].info.block = -1;
			}
			else
			{
				f >> tmpstr;
				index[i].info.name = tmpstr;
				f >> tmp;
				index[i].info.type = tmp;
				f >> tmpstr;
				index[i].info.ftype = tmpstr;
				f >> tmp;
				index[i].info.user = tmp;
				f >> tmpstr;
				f >> tmpstr1;
				tmpstr = tmpstr + ' ' + tmpstr1;
				index[i].info.create_time = tmpstr;
				f >> tmpstr;
				f >> tmpstr1;
				tmpstr = tmpstr + ' ' + tmpstr1;
				index[i].info.last_edit_time = tmpstr;
				f >> tmp;
				index[i].info.share = tmp;
				f >> tmp;
				index[i].info.readable = tmp;
				f >> tmp;
				index[i].info.writeable = tmp;
				f >> tmp;
				index[i].info.size = tmp;
				f >> tmp;
				index[i].info.block = tmp;
				f >> size;
				for (j = 0; j < size; j++)
				{
					f >> tmp;
					index[i].info.path.push_back(tmp);
				}
			}
		}
		f >> size;
		for (i = 0; i < size; i++)
		{
			cataLog new_catalog;
			child_catalog new_c_catalog;
			f >> new_catalog.id;
			f >> new_catalog.addr.flag;
			f >> new_catalog.addr.i_node;
			f >> tmp;
			for (j = 0; j < tmp; j++)
			{
				f >> new_c_catalog.id >> new_c_catalog.name;
				new_catalog.addr.c_catalog.push_back(new_c_catalog);
			}
			f >> new_catalog.info.name;
			f >> new_catalog.info.type;
			f >> new_catalog.info.ftype;
			f >> new_catalog.info.user;
			f >> tmpstr;
			f >> tmpstr1;
			tmpstr = tmpstr + ' ' + tmpstr1;
			new_catalog.info.create_time = tmpstr;
			f >> tmpstr;
			f >> tmpstr1;
			tmpstr = tmpstr + ' ' + tmpstr1;
			new_catalog.info.last_edit_time = tmpstr;
			f >> new_catalog.info.share;
			f >> new_catalog.info.readable;
			f >> new_catalog.info.writeable;
			f >> new_catalog.info.size;
			f >> new_catalog.info.block;
			f >> tmp;
			for (j = 0; j < tmp; j++)
			{
				f >> tmp1;
				new_catalog.info.path.push_back(tmp1);
			}
			catalog.push_back(new_catalog);
		}
		f >> size;
		for (i = 0; i < size; i++)
		{
			disk_Index new_disk_index;
			f >> tmp;
			for (j = 0; j < tmp; j++)
			{
				f >> tmp1;
				new_disk_index.block.push_back(tmp1);
			}
			disk_index.push_back(new_disk_index);
		}
		f >> size;
		for (i = 0; i < size; i++)
		{
			INAMEindex new_inameindex;
			f >> new_inameindex.id >> new_inameindex.name;
			inameindex.push_back(new_inameindex);
		}
		f >> size;
		for (i = 0; i < size; i++)
		{
			IDATEindex new_idateindex;
			f >> new_idateindex.id;
			f >> tmpstr;
			f >> tmpstr1;
			tmpstr = tmpstr + ' ' + tmpstr1;
			new_idateindex.date = tmpstr;
			idateindex.push_back(new_idateindex);
		}
		f >> size;
		for (i = 0; i < size; i++)
		{
			ITYPEindex new_itypeindex;
			f >> new_itypeindex.id;
			f >> new_itypeindex.type;
			itypeindex.push_back(new_itypeindex);
		}
		f.close();
		f.open("diskdata.txt", ios::in);
		char tmpcstr[10000];
		for (i = 0; i < 128; i++)
		{
			f >> size;
			if (size == 0)
				continue;
			char a[2];
			f.read(a, 1);
			f.read(tmpcstr, size);
			tmpcstr[size] = '\0';
			disk[i].content = tmpcstr;
		}
		f.close();
	}
}
