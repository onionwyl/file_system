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
    fout.close();                                     //�����̿�����д��temp.txt

    txt();                                            //���ü��±�

    ifstream in("temp.txt", ios::in);
    istreambuf_iterator<char> beg(in), end;
    string strdata(beg, end);
    in.close();
    cout<<strdata<<endl;                               //�����±�����д�ش���
    remove("temp.txt");                                //ɾ����ʱ�ļ�

}
