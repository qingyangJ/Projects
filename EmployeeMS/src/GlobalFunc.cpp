#include "GlobalFunc.h"
#include<iostream>
#include<string>

using namespace std;

// ����int������ķǷ�����
bool SafeIntCin(int &num) {
    cin>>num;
    // ��һ�֣���Int������
    if(cin.fail()) {
        cout<<"����Ƿ�������������"<<endl;
        cin.clear();
        cin.sync();
        system("pause");
        system("cls");
        return false;
    }
    // �ڶ��֣�int�����ݵ����м��пո񣬵����Զ���ȡ��
    // ��������1231231 1 2���ո���1��2��������Ҳ�ᱻ��ȡ��
    // Ӱ����һ������룬���³��������
    // ���յ���һ���ո�����������
    string str = "";
    getline(cin, str);
    if(str != "")  {
        cout<<"����Ƿ�������������"<<endl;
        system("pause");
        system("cls");
        return false;
    }
    return true;
}

