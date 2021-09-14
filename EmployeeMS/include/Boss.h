#pragma once
#include "Worker.h"


class Boss:public Worker
{
public:
    Boss(std::string name, int id, int jobId);
    ~Boss();
    // 显示个人信息
    void ShowInfo();
    // 获取岗位内容
    std::string GetJobInfo();
};



