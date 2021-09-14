#include "GlobalFunc.h"
#include "Management.h"
#include "Worker.h"
#include "Employee.h"
#include "Manager.h"
#include "Boss.h"

#define FILENAME "./../wokersInfo.txt"

#include <iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>



Management::Management(/* args */) {
    m_count = 0;
    m_Size = MaxSize;
    m_WorkerArr =new Worker*[MaxSize];
    if(!m_WorkerArr) exit(-1);
    
    // �ļ�
    m_FileIsEmpty = true;
    m_ifs.open(FILENAME, ios::in);
    if(m_ifs.is_open()) {
        // ˵���ļ�����
        char ch;
        m_ifs>>ch;
        if(m_ifs.eof()) {
            // ˵���ļ�Ϊ��
            cout<<"�ļ�Ϊ�գ�"<<endl;
        } else {
             // ˵���ļ�buΪ��
            m_FileIsEmpty = false;
            cout<<"�ļ�buΪ�գ�"<<endl;
        }
       
    } else {
        cout<<"�ļ������ڣ�"<<endl;
    }
    m_ifs.close();
}

Management::~Management() 
{
    if(m_WorkerArr != nullptr)  {
        for(int i = 0; i<m_count; i++) {
            if(m_WorkerArr[i] != nullptr) {
                delete m_WorkerArr[i];
                m_WorkerArr[i] = nullptr;
            }
        }
        delete []m_WorkerArr;
        m_WorkerArr = nullptr;
    }
}

void Management::ShowMenu() {
    cout<<"\t########################################"<<endl;
    cout<<"\t######### ��ӭʹ��ְ������ϵͳ #########"<<endl;
    cout<<"\t###########0���˳�����ϵͳ #############"<<endl;
    cout<<"\t###########1������ְ����Ϣ #############"<<endl;
    cout<<"\t###########2����ʾְ����Ϣ #############"<<endl;
    cout<<"\t###########3��ɾ����ְְ�� #############"<<endl;
    cout<<"\t###########4���޸�ְ����Ϣ #############"<<endl;
    cout<<"\t###########5������ְ����Ϣ #############"<<endl;
    cout<<"\t###########6�����ձ������ #############"<<endl;
    cout<<"\t###########7����������ĵ� #############"<<endl;
    cout<<"\t########################################"<<endl;
    // �û�����˵�ѡ�0-7��������ʾ������ʾ�������롣
    cout<<"######### ������˵�ѡ���ţ�0-7��#####"<<endl;
}

void Management::Exit() {
    cout<<"�˳�ϵͳ--Bye:)"<<endl;
    // system("pause");
}

void Management::JobMenu() {
    cout<<"�������ְ���ĸ�λ��"<<endl;
    cout<<"\t1. ��ְͨ��"<<endl;
    cout<<"\t2. ����   "<<endl;
    cout<<"\t3. �ϰ�   "<<endl;
}
// 
void Management::ExpandSpace(int size) {
    cout<<"���·������ڴ棺"<<endl;
    system("pause");
    // ���·����ڴ�-������ԭ��������
    Worker **temp = new Worker*[size];
    if(!temp) exit(-1);
    // copy��ͬʱ����Workers��ָ��ָ��
    for(int i =0; i<m_count; i++) {
        temp[i] = m_WorkerArr[i];
        m_WorkerArr[i] = nullptr;
    }
    // �ͷ�ԭ�ѿռ�
    delete []m_WorkerArr;
    m_WorkerArr = temp;
}
// ѡ������-�����
void Management::ChoiceJob(int pos, string &name, int &id) {
    int choice = 0;
    Worker *worker = nullptr;
    while(1){
        while (!SafeIntCin(choice)) {
            JobMenu();
        }
        switch (choice) {
            case 1:
                worker = new Employee(name, id, 1);
                break;
            case 2:
                worker = new Manager(name, id, 2);
                break;
            case 3:
                worker = new Boss(name, id, 3);
                break;
            default:
                cout<<"�������������루1-3��������:) (�������������"<<endl;
                system("pause");
                break;
        }
        if(choice>=1 && choice<=3) {
            break;
        }
    }    
    //������������ݱ���������
    m_WorkerArr[m_count+pos] = worker;
    cout<<"���� :"<<m_WorkerArr[m_count+pos]->m_name<<endl;
 }


void Management::Add(int &num) {
    // ���
    for(int i = 0; i<num; i++) {
        // ���
        int id = 0;
        string name = "";
        // ���������� ����
        cout<<"�������"<<i+1<<"��ְ������:  ";
        cin>>name;
        cout<<"�������"<<i+1<<"��ְ�����  ";
        while (!SafeIntCin(id)) {
            cout<<"�������"<<i+1<<"��ְ����ţ� ";
        }
        // ѡ��������
        JobMenu();
        ChoiceJob(i, name, id);
        // ��ʾ��ӳɹ�
        cout<<"��ӳɹ�:)"<<endl;
        system("pause");
    }
}
// ���ְ����֧����Ӷ��
void Management::AddWorker() {
    // ��Ҫ��ӵ�����
    int num = 0;
    cout<<"Ҫ��ӵ�ְ������"<<endl;
    while (!SafeIntCin(num)) {
        cout<<"Ҫ��ӵ�ְ������"<<endl;
    }
    if(num>0) {
        // �жϿռ��Ƿ��㹻
        if((m_count + num) > m_Size) {
           ExpandSpace(m_count + num);
        }
        Add(num);
        // ������������
        m_count += num;
        
    }
    SaveToFile();
}

// д�ļ�
void Management::SaveToFile() {
    ofstream ofs;
    cout<<"Save.Count: "<<m_count<<endl;
    ofs.open(FILENAME, ios::out);
    ofs <<setiosflags(ios::left)<<setw(15)<<"name"<<
            setw(25)<< "id  "<< "job_Id" << endl;
    for(int i = 0; i<m_count; i++) {
        ofs <<setiosflags(ios::left)<<setw(15)<<
                m_WorkerArr[i]->m_name <<setw(25)<<
                m_WorkerArr[i]->m_id <<
                m_WorkerArr[i]->m_jobId << endl;
    }
    ofs.close();
    if(m_count == 0) {
        m_FileIsEmpty = true;
    } else {
            m_FileIsEmpty = false;
    }
}
// �ļ����ڴ��ļ����������
void Management::AddFormFile() {
    ifstream ifs;
    string line;
    string name;
    int id;
    int jobId;
    // �ж��ļ��Ƿ����,�����Ƿ�Ϊ��
    if(m_FileIsEmpty) return;
    // ͳ����Ҫ���ٵĿռ���
    int num = GetNum();
    // �жϿռ��Ƿ��㹻
    if(num > MaxSize) {
        ExpandSpace(num);
    }
    ifs.open(FILENAME, ios::in);
    // ��ӽ������ļ��е�һ��ְ����ʼ,��ȡ��һ�У���¼�룩
    getline(ifs, line, '\n');
    // ��ʼ¼������
    int pos = 0;
    while (ifs>>name && ifs>>id && ifs>>jobId)
    {
        // ���ݲ�ͬ�Ĳ���ID������ͬ����
        Worker *worker = nullptr;
        switch (jobId)
        {
            case 1:
                worker = new Employee(name, id, 1);
                break;
            case 2:
                worker = new Manager(name, id, 2);
                break;
            case 3:
                worker = new Boss(name, id, 3);
                break;
            default:
                cout<<"�ļ���ʽ���ݴ���!ֹͣ����"<<endl;
                break;
        }
        // ��ӽ�����
        m_WorkerArr[pos] = worker;
        pos++;
    } 
    ifs.close();
    m_count = num;
}
// 
int Management::GetNum() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    string line;
    string name;
    int id;
    int jobId;
    int num = 0;
    // ��ȡ��һ��
    getline(ifs, line, '\n');
    // �����һ��
    cout<<line<<endl;
    while (ifs>>name && ifs>>id && ifs>>jobId) {
        num++;
    }
    ifs.close();
    return num; 
}

void Management::ShowWorker() {
    if(m_FileIsEmpty) {
        cout<<"�ļ���¼Ϊ�գ�"<<endl;
    } else {
        for(int i = 0; i<m_count; i++) {
            m_WorkerArr[i]->ShowInfo();
        }
    }
    system("pause");
}

// 
void Management::DelWorker() {
    int index = -1;
    SearchWorker(index);
    if(index != -1) {
        // ����-ɾ��
        for(int i = index; i<m_count-1; i++) {
            m_WorkerArr[i] = m_WorkerArr[i+1];
        }
        m_count--;
        SaveToFile();
        cout<<"ɾ���ɹ�."<<endl;
    } else {
        cout<<"δ�ҵ���Ա����ɾ��ʧ�ܣ�"<<endl;
    }
    system("pause");
}

void Management::ModifyWorker() {
    int index = -1;
    int id = 0;
    string name = "";
    SearchWorker(index);
    if(index == -1) {
        cout<<"���޴���"<<endl;
        return;
    }
    delete m_WorkerArr[index];
    m_WorkerArr[index] = nullptr;

    cout<<"�����������Ա����Ϣ��"<<endl;
    // ���������� ����
    cout<<"������ְ������:  ";
    cin>>name;
    cout<<"������ְ�����:  ";
    while (!SafeIntCin(id)) {
        cout<<"������ְ����ţ� ";
    }
    // ѡ��������
    JobMenu();
    ChoiceJob(index-m_count, name, id);
    cout<<"�޸ĳɹ���"<<m_WorkerArr[index]->m_id<<endl;;
    SaveToFile();
    system("pause");
}
// ����ģʽ�˵�
void Management::ModeMenu() {
    cout<<"��ѡ�����ģʽ��"<<endl;
    cout<<"\t1. ����������"<<endl;
    cout<<"\t2. ����Ų���"<<endl;
}
//
int Management::SearchName() {
    int all = 0;
    cout<<"���룺0��Ĭ��ѡ���ʾ�ҵ��ĵ�һ����"<<endl;
    cout<<"���룺1����ʾ�ҵ���ȫ��,�����һ��Ϊ׼��"<<endl;
    // ����Ƿ�����
    while(!SafeIntCin(all)) {
        cout<<"���룺0��Ĭ��ѡ���ʾ�ҵ��ĵ�һ����"<<endl;
        cout<<"���룺1����ʾ�ҵ���ȫ��,�����һ��Ϊ׼��"<<endl;
    }
    // last��¼���ҵ������һ��
    int last = -1;
    cout<<"������ְ������:  ";
    string name = "";
    cin>>name;
    // �ж�Ա���Ƿ����
    for(int i =0; i<m_count; i++) {
        if(m_WorkerArr[i]->m_name == name) {
            if(all == 1) {
                cout<<"Ա����Ϣ����"<<endl;
                m_WorkerArr[i]->ShowInfo();
                last = i;
            } else {
                cout<<"Ա����Ϣ����"<<endl;
                m_WorkerArr[i]->ShowInfo();
                system("pause");
                return i;
            }
            
        }
    }
    system("pause");
    return last;
}
//
int Management::SearchId() {
    int all = 0;
    cout<<"���룺0��Ĭ��ѡ���ʾ�ҵ��ĵ�һ����"<<endl;
    cout<<"���룺1����ʾ�ҵ���ȫ��,�����һ��Ϊ׼��"<<endl;
    // ����Ƿ�����
    while(!SafeIntCin(all)) {
        cout<<"���룺0��Ĭ��ѡ���ʾ�ҵ��ĵ�һ����"<<endl;
        cout<<"���룺1����ʾ�ҵ���ȫ��,�����һ��Ϊ׼��"<<endl;
    }
    // ��¼���ҵ������һ��
    int last = -1;
    int id = 0;
    cout<<"������ְ�����:  ";
    // ����Ƿ�����
    while(!SafeIntCin(id)) {
        cout<<"������ְ�����:  ";
    }
    // �ж�Ա���Ƿ����
    for(int i =0; i<m_count; i++) {
        if(m_WorkerArr[i]->m_id == id) {
            if(all == 1) {
                cout<<"Ա����Ϣ����"<<endl;
                m_WorkerArr[i]->ShowInfo();
                last = i;
            } else {
                cout<<"Ա����Ϣ����"<<endl;
                m_WorkerArr[i]->ShowInfo();
                system("pause");
                return i;
            }  
        }
    }
    system("pause");
    return last;
}
//
void Management::SearchWorker(int &index) {
    
    int mode = 0;
    // �Ƿ����
    if(m_FileIsEmpty) {
        cout<<"�ļ���¼Ϊ�գ�"<<endl;
    } else {
        // ѡ��ģʽ
        ModeMenu();
        // ����Ƿ�����
        while(!SafeIntCin(mode)) {
            ModeMenu();
        }
        //
        if(mode == 1) {
            index = SearchName();
            if(index == -1) {
                cout<<"δ�ҵ�"<<endl;
            }
            return;
        }
        if(mode == 2) {
            index = SearchId();
            if(index == -1) {
                cout<<"δ�ҵ�"<<endl;
            }
            return;
        }
    } 
}
//
void Management::SortMenu() {
    cout<<"��ѡ������ʽ"<<endl;
    cout<<"���룺1����ְ����������"<<endl;
    cout<<"���룺2����ְ�����Ž���"<<endl;
}
//
void Management::SortUp() {
    // ����
    for(int i = 0; i<m_count; i++) {
        for(int j = i+1; j<m_count; j++) {
            if(m_WorkerArr[i]->m_id > m_WorkerArr[j]->m_id) {
                Worker *temp = m_WorkerArr[i];
                m_WorkerArr[i] = m_WorkerArr[j];
                m_WorkerArr[j] = temp;
            }
        }
    }
}
//
void Management::SortDown() {
    // ����
    for(int i = 0; i<m_count; i++) {
        for(int j = i+1; j<m_count; j++) {
            if(m_WorkerArr[i]->m_id < m_WorkerArr[j]->m_id) {
                Worker *temp = m_WorkerArr[i];
                m_WorkerArr[i] = m_WorkerArr[j];
                m_WorkerArr[j] = temp;
            }
        }
    }
}
//
void Management::SortId() {
    if(m_FileIsEmpty) {
        cout<<"�ļ���¼Ϊ�գ�"<<endl;
        return;
    }
    int mode = 0;
    SortMenu();
    // ����Ƿ�����
    while(!SafeIntCin(mode)) {
        SortMenu();
    }
    if(mode == 1) {
        SortUp();
    }
    if(mode ==2) {
        SortDown();
    }
    cout<<"����ɹ���������Ϊ��"<<endl;
    SaveToFile();
    ShowWorker();
}
//
void Management::CleanFile() {
    int select = 0;
    cout<<"ȷ����գ�"<<endl;
    cout<<"1�� ȷ��"<<endl;
    cout<<"2�� ����"<<endl;
    // ����Ƿ�����
    while(!SafeIntCin(select)) {
        cout<<"ȷ����գ�"<<endl;
        cout<<"1�� ȷ��"<<endl;
        cout<<"2�� ����"<<endl;
    }
    if(select == 1) {
        // ����ios::trunc �������ɾ���ļ������´���
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();
        // �������
        if(m_WorkerArr != nullptr) {
            for(int i = 0; i<m_count; i++) {
                if(m_WorkerArr[i] != nullptr) {
                    delete m_WorkerArr[i];
                    m_WorkerArr[i] = nullptr;
                }
            }
            m_count = 0;
            m_FileIsEmpty = true;
        }
        cout<<"��ճɹ���"<<endl;
    }
    system("pause");
    system("cls");
}