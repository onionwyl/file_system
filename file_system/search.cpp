#include"header.h"
extern vector<cateLog> catelog;
extern i_node index[128];
extern vector<INAMEindex> inameindex;   //i节点索引
extern vector<IDATEindex> idateindex;
extern vector<ITYPEindex> itypeindex;
void transform_path(vector<int> path){
     int i;
     for(i=1;i<path.size();i++){
        cout<<catelog[path[i]].info.name<<"/";
     }
}

void dichotomy_name(int a,int b,string name){    //名字检索用到的二分法

    int frist=a;
    int last=b;
    int mid=ceil((frist+last)/2);
    cout<<frist<<" "<<mid<<" "<<last<<endl;
    if(frist<=last){
    while(frist<=last){
      if( /*inameindex[mid].name.find( name )!=string::npos*/inameindex[mid].name==name){ //   找到了
         vector<int> answer;
         answer.push_back(mid);
         int temp;
         if(mid>frist){
         temp=mid-1;
         while(temp>=frist && inameindex[temp].name==name ){
               answer.push_back(temp);
               temp=temp-1;}
               }
        if(mid<last){
        temp=mid+1;
        while(  temp<=last && inameindex[temp].name==name){
        answer.push_back(temp);
        temp=temp+1;}
        }
        for(int i=0;i<answer.size();i++){  //输出结果
        cout<<inameindex[answer[i]].name<<" ";
        transform_path(index[inameindex[i].id].info.path);
        cout<<endl;
        }
        return;
        }

      else if(name>inameindex[mid].name){//name大于中间值
            frist=mid+1;
            dichotomy_name(frist,last,name);
            return;
           }
     else if(name<inameindex[mid].name){ //
            last=mid-1;
            dichotomy_name(frist,last,name);
            return;
             }
     system("pause");
    }  //while
    }//if
    else
        cout<<"no such file"<<endl;
}


bool Less1( INAMEindex s1,  INAMEindex s2)
{
return s1.name < s2.name;
}



void search_file_name(string in) {        //按名字检索
     sort(inameindex.begin(), inameindex.end(), Less1);
   /* for(int i=0;i<2;i++){
        cout<<inameindex[i].name<<endl;
     }*/ // 输出索引，调试时用的

     int a=0;
     int b=inameindex.size()-1;
     dichotomy_name(a,b,in);

     }

void search_file_date(string in) {
   //  sort(inameindex.begin(), inameindex.end(), Less);
   /* for(int i=0;i<2;i++){
        cout<<inameindex[i].name<<endl;
     }*/ // 输出索引，调试时用的

     int a=0;
     int b=inameindex.size()-1;
     dichotomy_name(a,b,in);
}


void search_file(){
     string in;
     cout<<"search>";
     cin>>in;
     if(in=="date")
        {cout<<"search by date>";
         cin>>in;
         search_file_date(in);
         return;
        }
     if(in=="name"){
        cout<<"search by name>";
        cin>>in;
        search_file_name(in);
        return;
     }
}


