#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<conio.h>
#include<sstream>
#include<time.h>

using namespace std;

#define BLOCKSIZ 512;
#define DIRNUM 128;
#define MAXBLK 512;

typedef struct{		//子文件目录
	string name;
	int id;
}child_catelog;

typedef struct{		//文件目录中地址
	int flag;
	vector<child_catelog> c_catelog;
	int i_node;
}address;

typedef struct{		//文件信息
	string name;
	int type;
	int user;
	string create_time;
	string last_edit_time;
	int share;
	int readable;
	int writeable;
	int size;
	int block;
}information;

typedef struct{		//文件目录
	int id;
	address addr;
	information info;
}cateLog;

typedef struct{		//磁盘i节点
	information info;
}i_node;

typedef struct{		//内存i节点
	information info;
	vector<int> user;
}i_node_memory;

typedef struct{		//磁盘块
	char content[10000];
}disk_block;

typedef struct{		//磁盘块索引
	vector<int> block;
}disk_Index;

