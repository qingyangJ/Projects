#pragma once
#include "Worker.h"


class Boss:public Worker
{
public:
    Boss(std::string name, int id, int jobId);
    ~Boss();
    // ��ʾ������Ϣ
    void ShowInfo();
    // ��ȡ��λ����
    std::string GetJobInfo();
};



