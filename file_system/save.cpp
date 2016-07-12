#include"header.h"

extern vector<int> i_stack;
extern vector<int> disk_stack;
extern disk_block disk[10240];
extern i_node index[128];
extern vector<cateLog> catelog;
extern vector<disk_Index> disk_index;
extern vector<INAMEindex> inameindex;   //i½ÚµãË÷Òý
extern vector<IDATEindex> idateindex;
extern vector<ITYPEindex> itypeindex;

void save()
{
	ofstream f;
	int i;
	f.open("disk.txt");
	f << i_stack.size() << endl;
	for (auto tmp : i_stack)
	{
		f << tmp << " ";
	}
	f << endl;
	f << disk_stack.size() << endl;
	for (auto tmp : disk_stack)
	{
		f << tmp << " ";
	}
	f << endl;
	for (i = 0; i < 128; i++)
	{
		f << index[i].info.name << " " << index[i].info.type << " " << index[i].info.user << " ";
		f << index[i].info.create_time << " " << index[i].info.last_edit_time << " ";
		f << index[i].info.share << " " << index[i].info.readable << " " << index[i].info.writeable << " ";
		f << index[i].info.size << " " << index[i].info.block << endl;
		f << index[i].info.path.size() << endl;
		for (auto tmp : index[i].info.path)
		{
			f << tmp << " ";
		}
		f << endl;
	}
	f << catelog.size() << endl;
	for (auto tmp : catelog)
	{
		f << tmp.id << " ";
		f << tmp.addr.flag << " ";
		f << tmp.addr.i_node << " ";
		f << tmp.addr.c_catelog.size() << endl;
		for (auto tmp1 : tmp.addr.c_catelog)
		{
			f << tmp1.id << " " << tmp1.name << " ";
		}
		f << endl;
		f << tmp.info.name << " " << tmp.info.type << " " << tmp.info.user << " ";
		f << tmp.info.create_time << " " << tmp.info.last_edit_time << " ";
		f << tmp.info.share << " " << tmp.info.readable << " " << tmp.info.writeable << " ";
		f << tmp.info.size << " " << tmp.info.block << endl;
		f << tmp.info.path.size() << endl;
		for (auto tmp1 : tmp.info.path)
		{
			f << tmp1 << " ";
		}
		f << endl;
	}
	f << disk_index.size() << endl;
	for (auto tmp : disk_index)
	{
		f << tmp.block.size() << endl;
		for (auto tmp1 : tmp.block)
		{
			f << tmp1 << " ";
		}
		f << endl;
	}
	f << inameindex.size() << endl;
	for (auto tmp : inameindex)
	{
		f << tmp.id << " " << tmp.name << " ";
	}
	f << endl;
	f << idateindex.size() << endl;
	for (auto tmp : idateindex)
	{
		f << tmp.id << " " << tmp.date << " ";
	}
	f << endl;
	f << itypeindex.size() << endl;
	for (auto tmp : itypeindex)
	{
		f << tmp.type << " " << tmp.id << " ";
	}
	f << endl;
	f.close();
	f.open("diskdata.txt");
	for (i = 0; i < 128; i++)
	{
		f << disk[i].content.size() << endl;
		f << disk[i].content << endl;
	}
	f.close();
}