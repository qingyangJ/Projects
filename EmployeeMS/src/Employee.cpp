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
    cout<<"ְ�������� " << this->m_name<<
            "\tְ�����:  " << this->m_id<<
            "\tְ����λ  " << this->GetJobInfo()<<
            "\t��λְ����ɾ�����������."<<endl;
}
// 
string Employee::GetJobInfo() {
    return string("Ա��");
}

