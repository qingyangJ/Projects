#pragma once
#define MaxSize 100

#include "Worker.h"
#include<string>
#include<fstream>

using namespace std;

class Management
{
public:
    Management(/* args */);
    ~Management();
    void ShowMenu();
    void Exit();
    // ���ְ����֧����Ӷ��
    void AddWorker();
    // ְλ�˵�
    void JobMenu();
    // ѡ�����-�����
   void ChoiceJob(int pos, std::string &name, int &id);
    // ��ӣ�num��ӵ�����
    void Add(int &num);
    // ����ռ�
    void ExpandSpace(int size);
    // д�ļ�
    void SaveToFile();
    // �ļ����ڴ��ļ����������
    void AddFormFile();
    // ͳ���ļ��е�����
    int GetNum();
    // ��ʾְ��
    void ShowWorker();
    // ɾ��
    void DelWorker();
    // �޸�
    void ModifyWorker();
    // ����ģʽ�˵�
    void ModeMenu();
    // ����������,δ�ҵ�����ֵ-1
    int SearchName();
    // ��ְ����Ų��ң�δ�ҵ�����ֵ-1
    int SearchId();
    // Ĭ����ʾ�����ҵ���
    void SearchWorker(int &index);
    // ����˵�
    void SortMenu();
    // ����ͽ���
    void SortUp();
    void SortDown();
    void SortId();
    void CleanFile();
private:
    /* data */
    // Ա������
    int m_count;
    // ����ָ��ָ����worker*������
    Worker **m_WorkerArr;
    // ����Ĵ�С
    int m_Size;
    // �ļ�
    std::ifstream m_ifs;
    // �ļ��Ƿ�Ϊ�յı�־
    bool m_FileIsEmpty;
};


