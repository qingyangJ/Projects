#pragma once
#include "Worker.h"


class Employee:public Worker
{
public:
    Employee(std::string name, int id, int jobId);
    ~Employee();
    // 显示个人信息
    void ShowInfo();
    // 获取岗位内容
    std::string GetJobInfo();
};



