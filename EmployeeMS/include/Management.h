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
    // 添加职工，支持添加多个
    void AddWorker();
    // 职位菜单
    void JobMenu();
    // 选择类别-并添加
   void ChoiceJob(int pos, std::string &name, int &id);
    // 添加，num添加的数量
    void Add(int &num);
    // 扩充空间
    void ExpandSpace(int size);
    // 写文件
    void SaveToFile();
    // 文件存在从文件中添加数据
    void AddFormFile();
    // 统计文件中的人数
    int GetNum();
    // 显示职工
    void ShowWorker();
    // 删除
    void DelWorker();
    // 修改
    void ModifyWorker();
    // 查找模式菜单
    void ModeMenu();
    // 按姓名查找,未找到返回值-1
    int SearchName();
    // 按职工编号查找，未找到返回值-1
    int SearchId();
    // 默认显示最先找到的
    void SearchWorker(int &index);
    // 排序菜单
    void SortMenu();
    // 升序和降序
    void SortUp();
    void SortDown();
    void SortId();
    void CleanFile();
private:
    /* data */
    // 员工人数
    int m_count;
    // 数组指针指向存放worker*的数组
    Worker **m_WorkerArr;
    // 数组的大小
    int m_Size;
    // 文件
    std::ifstream m_ifs;
    // 文件是否为空的标志
    bool m_FileIsEmpty;
};


