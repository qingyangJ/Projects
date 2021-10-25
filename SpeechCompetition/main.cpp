#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#include "SManager.h"


void print1(int a) {
    cout<<a<<" ";
}
// 
void test1() {
    // Manager.CreateSpeaker();
    // for_each(Manager.m_SpkNumber.begin(), Manager.m_SpkNumber.end(), print1);
    // for(map<int, Speaker>::iterator it = Manager.m_Speaker.begin();
    //     it != Manager.m_Speaker.end(); it++) {
    //         cout<<(*it).first<<"  "<<it->second.m_name<<endl;;
    //     }
    // system("pause");
}
int main() {
    // 创建管理类
    SManager Manager;
    
    int choice = -1;
    while (true) {
        Manager.InitSpeech();
        Manager.ShowMenu();
        cout<<"Please input your choice'~' "<<endl;
        cin>>choice;
        switch (choice) {
            case 1: Manager.StartSpeech();
                break; 
            case 2: Manager.ShowLastInfo();
                break;
            case 3: Manager.ClearRec();
                break; 
            case 0: Manager.ExitSpeech();
                break;
            
            default:
                cout<<"wrong input."<<endl;
                system("cls");
                break;
        }
    }
    

    return 0;
}