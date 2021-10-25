#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <map>

#include "Speaker.h"



class SManager
{
private:
    /* data */
public:
    SManager(/* args */);
    ~SManager();
    void ShowMenu();
    void ExitSpeech();
    // 初始化容器和属性
    void InitSpeech();
    // 创建选手
    void CreateSpeaker();
    // 开始比赛
    void StartSpeech();
    // 抽签
    void SpeechLots();
    // 打分 num剩余未打分人数
    void Mark(int groupSize, int &num, int &groupNumber);
    // SAVE TO FILE
    void SaveToFile(std::multimap<double, int> &group, int &groupNumber);
    // 查看往届记录
    void ShowLastInfo();
    // 清空记录
    void ClearRec();
    // 存放参赛人员编号
    std::deque<int> m_SpkNumber;
    // 存放编号和对应的人员的容器
    std::map<int, Speaker> m_Speaker;
    // 记录比赛轮数
    int m_Round;

};

