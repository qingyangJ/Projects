#pragma once
#include "Worker.h"


class Manager:public Worker
{
public:
    Manager(std::string name, int id, int jobId);
    ~Manager();
    // 显示个人信息
    void ShowInfo();
    // 获取岗位内容
    std::string GetJobInfo();
};



