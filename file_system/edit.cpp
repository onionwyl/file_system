#include"header.h"
extern vector<cataLog> catalog;
extern i_node index[128];
extern disk_block disk[10240];
extern vector<int> path;
extern vector<disk_Index> disk_index;

void txt(){
	SHELLEXECUTEINFO ShellInfo;
	memset(&ShellInfo, 0, sizeof(ShellInfo));
	ShellInfo.cbSize = sizeof(ShellInfo);
	ShellInfo.hwnd = NULL;
	ShellInfo.lpVerb = _T("open");
	ShellInfo.lpFile = _T("temp.txt");
	ShellInfo.nShow = SW_SHOWNORMAL;
	ShellInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShellExecuteEx(&ShellInfo);
	WaitForSingleObject(ShellInfo.hProcess, INFINITE);

}

bool compare_arry(vector<int> a, vector<int> b){
	if (a.size() == b.size()){
		for (unsigned int i = 0; i < a.size(); i++)
		{
			if (a[i] != b[i])
				return false;
		}
		return true;
	}
	else
		return false;
}


int find_block(string name){
	for (int i = 0; i < 128; i++){
		if (compare_arry(index[i].info.path, path) && index[i].info.name == name){
			return i;
		}
	}
	return -1;
}

void edit(string command){

	stringstream command_stream(command);
	string command1, name;
	command_stream >> command1;
	command_stream >> name;


    if(find_block(name)>=0){
	string a = disk[disk_index[index[find_block(name)].info.block].block[0]].content;
	ofstream fout;
	fout.open("temp.txt");
	fout << a;
	fout.close();                                     //将磁盘块内容写入temp.txt

	txt();                                            //调用记事本

	ifstream in("temp.txt", ios::in);
	istreambuf_iterator<char> beg(in), end;
	string strdata(beg, end);
	a = strdata;
	disk[disk_index[index[find_block(name)].info.block].block[0]].content = a;
	in.close();                                        //将记事本内容写回磁盘

	remove("temp.txt");                                 //删除临时文件

	char date[255];
	time_t t = time(0);
	strftime(date, 255, "%Y-%m-%d %H:%M:%S", localtime(&t));
	index[find_block(name)].info.last_edit_time = date;  //修改最后编辑时间
    }
    else{
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
         cout << "file not found" << endl;
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
    }
}

