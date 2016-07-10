#include"header.h"
extern vector<cateLog> catelog;
extern i_node index[128];
void transform_path(vector<int> path){
    int i;
     for(i=0;i<path.size();i++){
        cout<<catelog[path[i]].info.name<<"/";
     }
}

void search_file_date(string a) {
     int i,sign=0;
     for(i=0;i<128;i++){
        if(index[i].info.last_edit_time==a){
                sign=1;
            cout<<index[i].info.name<<"  ";
            transform_path(index[i].info.path);
     }
     if(sign==0)
        cout<<"no such file"<<endl;}
}

void search_file(){
     string in;
     cin>>in;
     if(in=="date")
        {cout<<"-";
         cin>>in;
         search_file_date(in);
        }
}


