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

using namespace std;

#define BLOCKSIZ 512
#define DIRNUM 128
#define MAXBLK 512

typedef struct{		//���ļ�Ŀ¼
	string name;
	int id;
}child_catelog;

typedef struct{		//�ļ�Ŀ¼�е�ַ
	int flag;
	vector<child_catelog> c_catelog;
	int i_node;
}address;

typedef struct{		//�ļ���Ϣ
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
	vector<int> path;
}information;

typedef struct{		//�ļ�Ŀ¼
	int id;
	address addr;
	information info;
}cateLog;

typedef struct{		//����i�ڵ�
	information info;
}i_node;

typedef struct{		//�ڴ�i�ڵ�
	information info;
	vector<int> user;
}i_node_memory;

typedef struct{		//���̿�
	string content;
}disk_block;

typedef struct{		//���̿�����
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
    int    nameid;
    int    dateid;
    vector<int> node;
}ITYPEindex;
