#include"header.h"

extern vector<i_node_memory> i_node_mem;
extern int username_id;
extern i_node index[128];
extern disk_block disk[10240];
extern vector<disk_Index> disk_index;

int find_block(string name);

void open_file(string command){
    stringstream command_stream(command);
	string command1, name;
	command_stream >> command1;
	command_stream >> name;

    i_node_memory new_i_node_mem;                      //建立日期索引
    new_i_node_mem.info.block=index[find_block(name)].info.block;
    new_i_node_mem.info.create_time=index[find_block(name)].info.create_time;
    new_i_node_mem.info.ftype=index[find_block(name)].info.ftype;
    new_i_node_mem.info.last_edit_time=index[find_block(name)].info.last_edit_time;
    new_i_node_mem.info.name=index[find_block(name)].info.name;
    new_i_node_mem.info.path=index[find_block(name)].info.path;
    new_i_node_mem.info.readable=index[find_block(name)].info.readable;
    new_i_node_mem.info.share=index[find_block(name)].info.share;
    new_i_node_mem.info.size=index[find_block(name)].info.size;
    new_i_node_mem.info.type=index[find_block(name)].info.type;
    new_i_node_mem.info.user=index[find_block(name)].info.user;
    new_i_node_mem.info.writeable=index[find_block(name)].info.writeable;
    new_i_node_mem.user.push_back(username_id);
    new_i_node_mem.id=find_block(name);
    i_node_mem.push_back(new_i_node_mem);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);//设置蓝色
    cout<<"=========================================================="<<endl;
    cout<<disk[disk_index[index[find_block(name)].info.block].block[0] ].content<<endl;
    cout<<"=========================================================="<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);//还原为原色
}

void close_file(string command){
     stringstream command_stream(command);
	 string command1, name;
	 command_stream >> command1;
	 command_stream >> name;
	 for(unsigned int i=0;i<i_node_mem.size();i++){
        if(i_node_mem[i].id==find_block(name)){
        std::vector<i_node_memory>::iterator it = i_node_mem.begin()+i;
        i_node_mem.erase(it);
        cout<<command<<" is closed!"<<endl;
        }
	 }

}
