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
    cout<<"老板姓名： " << this->m_name<<
            "\t老板编号:  " << this->m_id<<
            "\t老板岗位  " << this->GetJobInfo()<<
            "\t岗位职责：下发任务给经理."<<endl;
}
// 
string Boss::GetJobInfo() {
    return string("老板");
}

