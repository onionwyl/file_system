#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

#define BLOCKSIZ 512;
#define DIRNUM 128;
#define MAXBLK 512;

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
	char content[10000];
}disk_block;

typedef struct{		//���̿�����
	vector<int> block;
}disk_Index;
