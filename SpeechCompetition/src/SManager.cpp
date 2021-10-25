#include "SManager.h"

#include <iostream>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <fstream>

#define FILENAME "../Result.txt"

using namespace std;


SManager::SManager(/* args */) {
    // ��ʼ������������
    InitSpeech();
}

SManager::~SManager() {

}

// show
void SManager::ShowMenu() {
    cout<<"---------------------------------"<<endl;
    cout<<"--------Speech Competition-------"<<endl;
    cout<<"-----------1. ��ʼ����------------"<<endl;
    cout<<"-----------2.�鿴�����¼---------"<<endl;
    cout<<"-----------3.��ձ�����¼---------"<<endl;
    cout<<"-----------0.�˳�����-------------"<<endl;
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
        string name = "ѡ��";
        name += nameSeed[i];
        Speaker spk;
        spk.m_name = name;
        // ��ʼ������
        int j = sizeof(spk.m_ArrScore)/sizeof(double);
        // cout<<"j:"<<j<<endl;
        while (j--) {
            spk.m_ArrScore[j] = 0;
        }
        // Ϊѡ�ֱ�Ų�����vector m_SpkNumber
        this->m_SpkNumber.push_back(i + 1001);
        // ����źͶ�Ӧ�ݽ��߷���map
        this->m_Speaker.insert(make_pair(i+1001, spk));
    }
}

void SManager::StartSpeech() {
    // ��ǩ
    srand(time(NULL));

    // ����
    int num = m_SpkNumber.size();
    // ʣ������ߴ���3����ô�ٱȣ����һ��û��������ô��ȥ��
    while (num>3 || this->m_Round<1) {
        SpeechLots();
        // ����
        // δ������
        int temp = num;
        int groupSize = 6;
        int groupNumber = 0;
        // ���������û������ô�ȣ�ÿ�ν�6����
        while (temp) {
            // ���
            groupNumber++;
            Mark(groupSize, temp, groupNumber);
        }
        num = m_SpkNumber.size();
        system("pause");
    }
    // ������
    cout<<"��������"<<endl;
}

class printV {
public:
    void operator() (int v) {
        cout<<v<<" ";
    }
};

// ��ǩ
void SManager::SpeechLots() {
    // ��m_SpkNumber�������
    this->m_Round++;
    cout<<"��"<<this->m_Round<<"�ֱ���ѡ�����ڳ�ǩ"<<endl;
    cout<<"-----------------------"<<endl;
    cout<<"---��ǩ���ݽ�˳������---"<<endl;
    random_shuffle(m_SpkNumber.begin(), m_SpkNumber.end());
    for_each(m_SpkNumber.begin(), m_SpkNumber.end(),printV());
    cout<<"-----------------------"<<endl;
    system("pause");
}
void SManager::Mark(int groupSize, int &num, int &groupNumber) {
    // ƽ����
    int average = 0;
    deque<int> sorces(10,0);
    multimap<double, int> group;
    for(int i = 0; i<groupSize && (num-- != 0); i++) {
        // ���  
        int sorce = 0;
        for(int j = 0; j<10; j++) {
            sorce = rand()%101;
            sorces.push_back(sorce);
        }
        // Ĭ�ϴ�С����
        sort(sorces.begin(), sorces.end());
        sorces.pop_back();
        sorces.pop_front();
        average = accumulate(sorces.begin(), sorces.end(),0)/8;
        // ������ʱgroup map<double, int>
        group.insert(make_pair(average, m_SpkNumber.front()));
        // �����Ӧm_Speaker map<int, Speaker>
        map<int, Speaker>::iterator key = m_Speaker.find(m_SpkNumber.front());
        if(key != m_Speaker.end()) {
            key->second.m_ArrScore[m_Round-1] = average;
        }
        // ����ִ�����group�к�ԭdeque��ɾ��
        m_SpkNumber.pop_front();
    }
    SaveToFile(group, groupNumber);
    // ȡ������ǰ��������Ϊmap�ǹ���ʽ����,Ĭ�ϴ�С��������
    cout<<"��"<<m_Round<<"�֣���"<<groupNumber<<"��ǰ��������ѡ�ֵı�ŷֱ��ǣ�"<<endl;
    multimap<double, int>::iterator it = group.end();
    for(int i = 0; i<3; i++) {
        it--;
        string name = "";
        map<int, Speaker>::iterator key = m_Speaker.find(it->second);
        if(key != m_Speaker.end()) {
            name = key->second.m_name;
        }
        cout<<"     ��"<<i+1<<"��-��ţ�"<<it->second<<"������ "<<name<<"������"<<it->first<<endl;
        m_SpkNumber.push_back(it->second);
    }
    cout<<endl;
}


void SManager::SaveToFile(multimap<double, int> &group, int &groupNumber) {
    ofstream ofs;
    ofs.open(FILENAME, ios::app);
    ofs<<"��"<<m_Round<<"��,��"<<groupNumber<<""<<"������ɼ����£�"<<endl;
    int order= 1;
    for(multimap<double, int>::reverse_iterator it = group.rbegin(); it != group.rend(); it++) {
        string name = "";
        map<int, Speaker>::iterator key = m_Speaker.find(it->second);
        if(key != m_Speaker.end()) {
            name = key->second.m_name;
        }
        ofs<<"     ��"<<order++<<"��-��ţ�"<<it->second<<"������ "<<name<<"������"<<it->first<<endl;
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
    cout<<"ȷ����գ�"<<endl;
    cout<<"1�� ȷ��"<<endl;
    cout<<"2�� ����"<<endl;
    cin>>select;
    if(select == 1) {
        // ����ios::trunc �������ɾ���ļ������´���
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();
        cout<<"��ճɹ���"<<endl;
    }
    system("pause");
    system("cls");
}