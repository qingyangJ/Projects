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
    
    // 文件
    m_FileIsEmpty = true;
    m_ifs.open(FILENAME, ios::in);
    if(m_ifs.is_open()) {
        // 说明文件存在
        char ch;
        m_ifs>>ch;
        if(m_ifs.eof()) {
            // 说明文件为空
            cout<<"文件为空！"<<endl;
        } else {
             // 说明文件bu为空
            m_FileIsEmpty = false;
            cout<<"文件bu为空！"<<endl;
        }
       
    } else {
        cout<<"文件不存在！"<<endl;
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
    cout<<"\t######### 欢迎使用职工管理系统 #########"<<endl;
    cout<<"\t###########0：退出管理系统 #############"<<endl;
    cout<<"\t###########1：增加职工信息 #############"<<endl;
    cout<<"\t###########2：显示职工信息 #############"<<endl;
    cout<<"\t###########3：删除离职职工 #############"<<endl;
    cout<<"\t###########4：修改职工信息 #############"<<endl;
    cout<<"\t###########5：查找职工信息 #############"<<endl;
    cout<<"\t###########6：按照编号排序 #############"<<endl;
    cout<<"\t###########7：清空所有文档 #############"<<endl;
    cout<<"\t########################################"<<endl;
    // 用户输入菜单选项，0-7其他的显示错误并提示重新输入。
    cout<<"######### 请输入菜单选项编号（0-7）#####"<<endl;
}

void Management::Exit() {
    cout<<"退出系统--Bye:)"<<endl;
    // system("pause");
}

void Management::JobMenu() {
    cout<<"请输入该职工的岗位："<<endl;
    cout<<"\t1. 普通职工"<<endl;
    cout<<"\t2. 经理   "<<endl;
    cout<<"\t3. 老板   "<<endl;
}
// 
void Management::ExpandSpace(int size) {
    cout<<"重新分配了内存："<<endl;
    system("pause");
    // 重新分配内存-并拷贝原来的数据
    Worker **temp = new Worker*[size];
    if(!temp) exit(-1);
    // copy的同时更改Workers内指针指向
    for(int i =0; i<m_count; i++) {
        temp[i] = m_WorkerArr[i];
        m_WorkerArr[i] = nullptr;
    }
    // 释放原堆空间
    delete []m_WorkerArr;
    m_WorkerArr = temp;
}
// 选择类型-并添加
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
                cout<<"输入有误，请输入（1-3）的整数:) (按任意键继续）"<<endl;
                system("pause");
                break;
        }
        if(choice>=1 && choice<=3) {
            break;
        }
    }    
    //将新添加数数据保存至数组
    m_WorkerArr[m_count+pos] = worker;
    cout<<"保存 :"<<m_WorkerArr[m_count+pos]->m_name<<endl;
 }


void Management::Add(int &num) {
    // 添加
    for(int i = 0; i<num; i++) {
        // 编号
        int id = 0;
        string name = "";
        // 输入姓名， 年龄
        cout<<"请输入第"<<i+1<<"个职工姓名:  ";
        cin>>name;
        cout<<"请输入第"<<i+1<<"个职工编号  ";
        while (!SafeIntCin(id)) {
            cout<<"请输入第"<<i+1<<"个职工编号： ";
        }
        // 选择类别并添加
        JobMenu();
        ChoiceJob(i, name, id);
        // 提示添加成功
        cout<<"添加成功:)"<<endl;
        system("pause");
    }
}
// 添加职工，支持添加多个
void Management::AddWorker() {
    // 想要添加的数量
    int num = 0;
    cout<<"要添加的职工数："<<endl;
    while (!SafeIntCin(num)) {
        cout<<"要添加的职工数："<<endl;
    }
    if(num>0) {
        // 判断空间是否足够
        if((m_count + num) > m_Size) {
           ExpandSpace(m_count + num);
        }
        Add(num);
        // 更新现有人数
        m_count += num;
        
    }
    SaveToFile();
}

// 写文件
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
// 文件存在从文件中添加数据
void Management::AddFormFile() {
    ifstream ifs;
    string line;
    string name;
    int id;
    int jobId;
    // 判断文件是否存在,存在是否为空
    if(m_FileIsEmpty) return;
    // 统计需要开辟的空间数
    int num = GetNum();
    // 判断空间是否足够
    if(num > MaxSize) {
        ExpandSpace(num);
    }
    ifs.open(FILENAME, ios::in);
    // 添加进来从文件中第一个职工开始,读取第一行（不录入）
    getline(ifs, line, '\n');
    // 开始录入数据
    int pos = 0;
    while (ifs>>name && ifs>>id && ifs>>jobId)
    {
        // 根据不同的部门ID创建不同对象
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
                cout<<"文件格式数据错误!停止读入"<<endl;
                break;
        }
        // 添加进数组
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
    // 读取第一行
    getline(ifs, line, '\n');
    // 输出第一行
    cout<<line<<endl;
    while (ifs>>name && ifs>>id && ifs>>jobId) {
        num++;
    }
    ifs.close();
    return num; 
}

void Management::ShowWorker() {
    if(m_FileIsEmpty) {
        cout<<"文件记录为空！"<<endl;
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
        // 存在-删除
        for(int i = index; i<m_count-1; i++) {
            m_WorkerArr[i] = m_WorkerArr[i+1];
        }
        m_count--;
        SaveToFile();
        cout<<"删除成功."<<endl;
    } else {
        cout<<"未找到该员工，删除失败！"<<endl;
    }
    system("pause");
}

void Management::ModifyWorker() {
    int index = -1;
    int id = 0;
    string name = "";
    SearchWorker(index);
    if(index == -1) {
        cout<<"查无此人"<<endl;
        return;
    }
    delete m_WorkerArr[index];
    m_WorkerArr[index] = nullptr;

    cout<<"请重新输入该员工信息："<<endl;
    // 输入姓名， 年龄
    cout<<"请输入职工姓名:  ";
    cin>>name;
    cout<<"请输入职工编号:  ";
    while (!SafeIntCin(id)) {
        cout<<"请输入职工编号： ";
    }
    // 选择类别并添加
    JobMenu();
    ChoiceJob(index-m_count, name, id);
    cout<<"修改成功！"<<m_WorkerArr[index]->m_id<<endl;;
    SaveToFile();
    system("pause");
}
// 查找模式菜单
void Management::ModeMenu() {
    cout<<"请选择查找模式："<<endl;
    cout<<"\t1. 按姓名查找"<<endl;
    cout<<"\t2. 按编号查找"<<endl;
}
//
int Management::SearchName() {
    int all = 0;
    cout<<"输入：0（默认选项，显示找到的第一个）"<<endl;
    cout<<"输入：1（显示找到的全部,以最后一个为准）"<<endl;
    // 处理非法输入
    while(!SafeIntCin(all)) {
        cout<<"输入：0（默认选项，显示找到的第一个）"<<endl;
        cout<<"输入：1（显示找到的全部,以最后一个为准）"<<endl;
    }
    // last记录查找到的最后一个
    int last = -1;
    cout<<"请输入职工姓名:  ";
    string name = "";
    cin>>name;
    // 判断员工是否存在
    for(int i =0; i<m_count; i++) {
        if(m_WorkerArr[i]->m_name == name) {
            if(all == 1) {
                cout<<"员工信息如下"<<endl;
                m_WorkerArr[i]->ShowInfo();
                last = i;
            } else {
                cout<<"员工信息如下"<<endl;
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
    cout<<"输入：0（默认选项，显示找到的第一个）"<<endl;
    cout<<"输入：1（显示找到的全部,以最后一个为准）"<<endl;
    // 处理非法输入
    while(!SafeIntCin(all)) {
        cout<<"输入：0（默认选项，显示找到的第一个）"<<endl;
        cout<<"输入：1（显示找到的全部,以最后一个为准）"<<endl;
    }
    // 记录查找到的最后一个
    int last = -1;
    int id = 0;
    cout<<"请输入职工编号:  ";
    // 处理非法输入
    while(!SafeIntCin(id)) {
        cout<<"请输入职工编号:  ";
    }
    // 判断员工是否存在
    for(int i =0; i<m_count; i++) {
        if(m_WorkerArr[i]->m_id == id) {
            if(all == 1) {
                cout<<"员工信息如下"<<endl;
                m_WorkerArr[i]->ShowInfo();
                last = i;
            } else {
                cout<<"员工信息如下"<<endl;
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
    // 是否存在
    if(m_FileIsEmpty) {
        cout<<"文件记录为空！"<<endl;
    } else {
        // 选择模式
        ModeMenu();
        // 处理非法输入
        while(!SafeIntCin(mode)) {
            ModeMenu();
        }
        //
        if(mode == 1) {
            index = SearchName();
            if(index == -1) {
                cout<<"未找到"<<endl;
            }
            return;
        }
        if(mode == 2) {
            index = SearchId();
            if(index == -1) {
                cout<<"未找到"<<endl;
            }
            return;
        }
    } 
}
//
void Management::SortMenu() {
    cout<<"请选择排序方式"<<endl;
    cout<<"输入：1（按职工工号升序）"<<endl;
    cout<<"输入：2（按职工工号降序）"<<endl;
}
//
void Management::SortUp() {
    // 升序
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
    // 降序
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
        cout<<"文件记录为空！"<<endl;
        return;
    }
    int mode = 0;
    SortMenu();
    // 处理非法输入
    while(!SafeIntCin(mode)) {
        SortMenu();
    }
    if(mode == 1) {
        SortUp();
    }
    if(mode ==2) {
        SortDown();
    }
    cout<<"排序成功后：排序结果为："<<endl;
    SaveToFile();
    ShowWorker();
}
//
void Management::CleanFile() {
    int select = 0;
    cout<<"确认清空？"<<endl;
    cout<<"1： 确认"<<endl;
    cout<<"2： 返回"<<endl;
    // 处理非法输入
    while(!SafeIntCin(select)) {
        cout<<"确认清空？"<<endl;
        cout<<"1： 确认"<<endl;
        cout<<"2： 返回"<<endl;
    }
    if(select == 1) {
        // 利用ios::trunc 如果存在删除文件并重新创建
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();
        // 清除数据
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
        cout<<"清空成功！"<<endl;
    }
    system("pause");
    system("cls");
}