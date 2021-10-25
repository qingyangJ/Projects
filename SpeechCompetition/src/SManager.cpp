#include "SManager.h"

#include <iostream>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <fstream>

#define FILENAME "../Result.txt"

using namespace std;


SManager::SManager(/* args */) {
    // 初始化容器和属性
    InitSpeech();
}

SManager::~SManager() {

}

// show
void SManager::ShowMenu() {
    cout<<"---------------------------------"<<endl;
    cout<<"--------Speech Competition-------"<<endl;
    cout<<"-----------1. 开始比赛------------"<<endl;
    cout<<"-----------2.查看往届记录---------"<<endl;
    cout<<"-----------3.清空比赛记录---------"<<endl;
    cout<<"-----------0.退出比赛-------------"<<endl;
    cout<<"----------------------------------"<<endl;
    cout<<endl;
}
// EXIT
void SManager::ExitSpeech() {
    cout<<"HAVE FUN:) Bye~"<<endl;
    system("pause");
    exit(0);
}

void SManager::InitSpeech() {
    this->m_SpkNumber.clear();
    this->m_Speaker.clear();
    this->m_Round = 0;
    CreateSpeaker();
}

//
void SManager::CreateSpeaker() {
    string nameSeed = "ABCDEFGHIJKL";
    for(int i = 0; i < nameSeed.size(); i++) {
        string name = "选手";
        name += nameSeed[i];
        Speaker spk;
        spk.m_name = name;
        // 初始化分数
        int j = sizeof(spk.m_ArrScore)/sizeof(double);
        // cout<<"j:"<<j<<endl;
        while (j--) {
            spk.m_ArrScore[j] = 0;
        }
        // 为选手编号并放入vector m_SpkNumber
        this->m_SpkNumber.push_back(i + 1001);
        // 将编号和对应演讲者放入map
        this->m_Speaker.insert(make_pair(i+1001, spk));
    }
}

void SManager::StartSpeech() {
    // 抽签
    srand(time(NULL));

    // 比赛
    int num = m_SpkNumber.size();
    // 剩余参赛者大于3个那么再比，如果一次没比赛过那么进去比
    while (num>3 || this->m_Round<1) {
        SpeechLots();
        // 比赛
        // 未比赛者
        int temp = num;
        int groupSize = 6;
        int groupNumber = 0;
        // 如果还有人没比赛那么比，每次进6个人
        while (temp) {
            // 打分
            groupNumber++;
            Mark(groupSize, temp, groupNumber);
        }
        num = m_SpkNumber.size();
        system("pause");
    }
    // 保存结果
    cout<<"比赛结束"<<endl;
}

class printV {
public:
    void operator() (int v) {
        cout<<v<<" ";
    }
};

// 抽签
void SManager::SpeechLots() {
    // 将m_SpkNumber随机打乱
    this->m_Round++;
    cout<<"第"<<this->m_Round<<"轮比赛选手正在抽签"<<endl;
    cout<<"-----------------------"<<endl;
    cout<<"---抽签后演讲顺序如下---"<<endl;
    random_shuffle(m_SpkNumber.begin(), m_SpkNumber.end());
    for_each(m_SpkNumber.begin(), m_SpkNumber.end(),printV());
    cout<<"-----------------------"<<endl;
    system("pause");
}
void SManager::Mark(int groupSize, int &num, int &groupNumber) {
    // 平均分
    int average = 0;
    deque<int> sorces(10,0);
    multimap<double, int> group;
    for(int i = 0; i<groupSize && (num-- != 0); i++) {
        // 打分  
        int sorce = 0;
        for(int j = 0; j<10; j++) {
            sorce = rand()%101;
            sorces.push_back(sorce);
        }
        // 默认从小到大
        sort(sorces.begin(), sorces.end());
        sorces.pop_back();
        sorces.pop_front();
        average = accumulate(sorces.begin(), sorces.end(),0)/8;
        // 存入临时group map<double, int>
        group.insert(make_pair(average, m_SpkNumber.front()));
        // 存入对应m_Speaker map<int, Speaker>
        map<int, Speaker>::iterator key = m_Speaker.find(m_SpkNumber.front());
        if(key != m_Speaker.end()) {
            key->second.m_ArrScore[m_Round-1] = average;
        }
        // 打完分存入了group中后原deque中删掉
        m_SpkNumber.pop_front();
    }
    SaveToFile(group, groupNumber);
    // 取出该组前三名，因为map是关联式容器,默认从小到大排序
    cout<<"第"<<m_Round<<"轮，第"<<groupNumber<<"组前三名晋级选手的编号分别是："<<endl;
    multimap<double, int>::iterator it = group.end();
    for(int i = 0; i<3; i++) {
        it--;
        string name = "";
        map<int, Speaker>::iterator key = m_Speaker.find(it->second);
        if(key != m_Speaker.end()) {
            name = key->second.m_name;
        }
        cout<<"     第"<<i+1<<"名-编号："<<it->second<<"姓名： "<<name<<"分数："<<it->first<<endl;
        m_SpkNumber.push_back(it->second);
    }
    cout<<endl;
}


void SManager::SaveToFile(multimap<double, int> &group, int &groupNumber) {
    ofstream ofs;
    ofs.open(FILENAME, ios::app);
    ofs<<"第"<<m_Round<<"轮,第"<<groupNumber<<""<<"组比赛成绩如下："<<endl;
    int order= 1;
    for(multimap<double, int>::reverse_iterator it = group.rbegin(); it != group.rend(); it++) {
        string name = "";
        map<int, Speaker>::iterator key = m_Speaker.find(it->second);
        if(key != m_Speaker.end()) {
            name = key->second.m_name;
        }
        ofs<<"     第"<<order++<<"名-编号："<<it->second<<"姓名： "<<name<<"分数："<<it->first<<endl;
    }
    ofs.close();
}

void SManager::ShowLastInfo() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    if(!ifs.is_open()) {
        cout<<"open error"<<endl;
        return;
    }
    string buf = "";
    while (getline(ifs, buf)) {
        cout<<buf<<endl;
    }
    ifs.close();
    system("pause");
}

void SManager::ClearRec() {
    int select = 0;
    cout<<"确认清空？"<<endl;
    cout<<"1： 确认"<<endl;
    cout<<"2： 返回"<<endl;
    cin>>select;
    if(select == 1) {
        // 利用ios::trunc 如果存在删除文件并重新创建
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();
        cout<<"清空成功！"<<endl;
    }
    system("pause");
    system("cls");
}