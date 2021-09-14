#include "Employee.h"
#include<iostream>
using namespace std;


Employee::Employee(string name, int id, int jobId) {
    this->m_name = name;
    this->m_id = id;
    this->m_jobId = jobId;
}

Employee::~Employee() {
}

// 
void Employee::ShowInfo() {
    cout<<"职工姓名： " << this->m_name<<
            "\t职工编号:  " << this->m_id<<
            "\t职工岗位  " << this->GetJobInfo()<<
            "\t岗位职责：完成经理交给的任务."<<endl;
}
// 
string Employee::GetJobInfo() {
    return string("员工");
}

