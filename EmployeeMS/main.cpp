#include <iostream>
using namespace std;

#include "GlobalFunc.h"
#include "Management.h"
#include "Worker.h"
#include "Employee.h"
#include "Manager.h"
#include "Boss.h"

// ����
int main_0() {
    Worker *worker = nullptr;
    worker = new Employee("����", 1, 2);
    worker->ShowInfo();
    Worker *manager = nullptr;
    manager = new Manager("li", 2, 3);
    manager->ShowInfo();
    Worker *boss = nullptr;
    boss = new Boss("sir", 3, 4);
    boss->ShowInfo();
    return 0;
}
int main() {
    Management m1;
    int choice = 0;
    
    while (1)
    {
        // ���ļ�����
        m1.AddFormFile();
        // ��ʾ�˵�
        m1.ShowMenu();
        // ����Ƿ�����
        while(!SafeIntCin(choice)) {
            m1.ShowMenu();
        }
        // ���ȴ��ļ��ж�ȡ����

        // ѡ�񷽰�
        switch (choice) {
            case 0: m1.Exit();
                    return 0;
                break;
            case 1: m1.AddWorker();
                break;
            case 2: m1.ShowWorker();
                break;
            case 3: m1.DelWorker();
                break;
            case 4: m1.ModifyWorker();
                break;
            case 5: 
            {   int index = -1;
                m1.SearchWorker(index);
            }
                break;
            case 6: m1.SortId();
                break;
            case 7: m1.CleanFile();
                break;
            
            default:
                cout<<"�������������루0-7��������:) (�������������"<<endl;
                system("pause");
                break;
        }
        // ����
        system("cls");
        
    }
    return 0;
}