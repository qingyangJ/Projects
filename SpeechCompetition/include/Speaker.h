#pragma once

#include <iostream>


class Speaker {    
public:
    Speaker(/* args */);
    ~Speaker();
    int m_number;
    std::string m_name;
    double m_ArrScore[2]; // 记录两轮得分
};

