#include "Boss.h"
#include<iostream>
using namespace std;


Boss::Boss(string name, int id, int jobId) {
    this->m_name = name;
    this->m_id = id;
    this->m_jobId = jobId;
}

Boss::~Boss() {
}

// 
void Boss::ShowInfo() {
    cout<<"�ϰ������� " << this->m_name<<
            "\t�ϰ���:  " << this->m_id<<
            "\t�ϰ��λ  " << this->GetJobInfo()<<
            "\t��λְ���·����������."<<endl;
}
// 
string Boss::GetJobInfo() {
    return string("�ϰ�");
}

