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
    cout<<"经理姓名： " << this->m_name<<
            "\t经理编号:  " << this->m_id<<
            "\t经理岗位  " << this->GetJobInfo()<<
            "\t岗位职责：下发任务给员工."<<endl;
}
// 
string Manager::GetJobInfo() {
    return string("经理");
}

