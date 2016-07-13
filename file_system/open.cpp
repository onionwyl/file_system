#include"header.h"

extern vector<i_node_memory> i_node_mem;
extern int username_id;
extern i_node index[128];
extern disk_block disk[10240];
extern vector<disk_Index> disk_index;
extern vector<cataLog> catalog;

int find_block(string name);

bool check(string name){
     for(int i=0;i<i_node_mem.size();i++){
        if(i_node_mem[i].info.name==name)
            return false;
     }
     return true;
}

void open_file(string command){
    stringstream command_stream(command);
	string command1, name;
	command_stream >> command1;
	command_stream >> name;
    if(find_block(name)>=0 && check(name)){
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

    char date[255];
    time_t t = time(0);
    strftime(date, 255, "%Y-%m-%d %H:%M:%S", localtime(&t));
    new_i_node_mem.open_time=date;

    i_node_mem.push_back(new_i_node_mem);


    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
    cout<<disk[disk_index[index[find_block(name)].info.block].block[0] ].content<<endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
     }
    else{
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
        cout << "file not found or already opened!" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
    }
}

void close_file(string command){
     stringstream command_stream(command);
	 string command1, name;
	 command_stream >> command1;
	 command_stream >> name;
	 if(find_block(name)>=0 && !check(name)){
	 for(unsigned int i=0;i<i_node_mem.size();i++){
        if(i_node_mem[i].id==find_block(name)){
        std::vector<i_node_memory>::iterator it = i_node_mem.begin()+i;
        i_node_mem.erase(it);
        cout<<name<<" is closed!"<<endl;
        }
	 }}
	 else{
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
        cout << "file not exist or already closed" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
	 }

}

void backstage(){
    if(i_node_mem.size()>0){
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
     cout.setf(ios::left);
     cout<<setw(10)<<"name"<<setw(10)<<"type"<<setw(20)<<"open time"<<setw(20)<<"path"<<endl;
     HANDLE hCON=GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hCON,(7%16)|(0%16*16));
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);

     for(unsigned int i=0;i<i_node_mem.size();i++){
         cout.setf(ios::left);
         cout<<setw(10)<<i_node_mem[i].info.name<<setw(10)<<i_node_mem[i].info.ftype<<setw(10)<<i_node_mem[i].open_time;
         for (unsigned j = 1; j< i_node_mem[i].info.path.size(); j++){
	       	cout << catalog[i_node_mem[i].info.path[j]].info.name << "/";
	       }
         cout<<endl;
       }
    }//if
    else{
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
         cout << "no file open" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);}
}
