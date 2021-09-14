#pragma once
#include<string>




// 职工抽象类--纯虚函数（无法实例化对象）
class Worker
{
public:
    // 显示个人信息
    virtual void ShowInfo() = 0;
    // 获取岗位内容
    virtual std::string GetJobInfo() = 0;
    /* data */
    std::string m_name;
    int m_id;
    int m_jobId;
};
