#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<conio.h>
#include<sstream>
#include<time.h>
#include<windows.h>
#include<shellapi.h>
#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<tchar.h>
#include<cstdlib>
#include<iomanip>
#include<windowsx.h>

using namespace std;

#define BLOCKSIZ 512
#define DIRNUM 128
#define MAXBLK 512

typedef struct{		//子文件目录
	string name;
	int id;
}child_catalog;

typedef struct{		//文件目录中地址
	int flag;
	vector<child_catalog> c_catalog;
	int i_node;
}address;

typedef struct{		//文件信息
	string name;
	int type;
	string ftype;
	int user;
	string create_time;
	string last_edit_time;
	int share;
	int readable;
	int writeable;
	int size;
	int block;
	vector<int> path;
}information;

typedef struct{		//文件目录
	int id;
	address addr;
	information info;
}cataLog;

typedef struct{		//磁盘i节点
	information info;
}i_node;

typedef struct{		//内存i节点
	information info;
	vector<int> user;
	int         id;//对应磁盘i节点的id
	string      open_time;
}i_node_memory;

typedef struct{		//磁盘块
	string content;
}disk_block;

typedef struct{		//磁盘块索引
	vector<int> block;
}disk_Index;

typedef struct{
    string name;
    int    id;
}INAMEindex;
typedef struct{
    string date;
    int    id;
}IDATEindex;
typedef struct{
    string type;
    int    id;
}ITYPEindex;
typedef struct{
    int    id;
    string username;
    string password;
}User;
