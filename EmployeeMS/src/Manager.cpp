#include "Manager.h"
#include<iostream>
using namespace std;


Manager::Manager(string name, int id, int jobId) {
    this->m_name = name;
    this->m_id = id;
    this->m_jobId = jobId;
}

Manager::~Manager() {
}

// 
void Manager::ShowInfo() {
    cout<<"���������� " << this->m_name<<
            "\t������:  " << this->m_id<<
            "\t�����λ  " << this->GetJobInfo()<<
            "\t��λְ���·������Ա��."<<endl;
}
// 
string Manager::GetJobInfo() {
    return string("����");
}

