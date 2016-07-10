#include"header.h"
extern vector<cateLog> catelog;
extern i_node index[128];

void txt(){
    SHELLEXECUTEINFO ShellInfo;
    memset(&ShellInfo, 0, sizeof(ShellInfo));
    ShellInfo.cbSize = sizeof(ShellInfo);
    ShellInfo.hwnd = NULL;
    ShellInfo.lpVerb = "open";
    ShellInfo.lpFile ="temp.txt";
    ShellInfo.nShow = SW_SHOWNORMAL;
    ShellInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShellExecuteEx(&ShellInfo);
    WaitForSingleObject(ShellInfo.hProcess,INFINITE);

}
void edit(){
    string a="hello word";
    ofstream fout;
    fout.open("temp.txt");
    fout<<a<<endl;
    fout.close();                                     //将磁盘块内容写入temp.txt

    txt();                                            //调用记事本

    ifstream in("temp.txt", ios::in);
    istreambuf_iterator<char> beg(in), end;
    string strdata(beg, end);
    in.close();
    cout<<strdata<<endl;                               //将记事本内容写回磁盘
    remove("temp.txt");                                //删除临时文件

}
