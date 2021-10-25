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
    // ��ʼ������������
    void InitSpeech();
    // ����ѡ��
    void CreateSpeaker();
    // ��ʼ����
    void StartSpeech();
    // ��ǩ
    void SpeechLots();
    // ��� numʣ��δ�������
    void Mark(int groupSize, int &num, int &groupNumber);
    // SAVE TO FILE
    void SaveToFile(std::multimap<double, int> &group, int &groupNumber);
    // �鿴�����¼
    void ShowLastInfo();
    // ��ռ�¼
    void ClearRec();
    // ��Ų�����Ա���
    std::deque<int> m_SpkNumber;
    // ��ű�źͶ�Ӧ����Ա������
    std::map<int, Speaker> m_Speaker;
    // ��¼��������
    int m_Round;

};

