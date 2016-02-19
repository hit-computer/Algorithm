#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define max 26
using namespace std;

struct Rate
{
    int time;
    float value;
};
struct Bank
{
    Rate rate[max];
    int last;
};

void Initialization(Bank &b);
void Insert(Bank &b);
void Change(Bank &b);
void Del(Bank &b);
void Find(Bank b);
void Display(Bank b);
void Save(Bank &b);

int main()
{
    Bank bank;
    bank.last=0;
    Initialization(bank);
    do
    {
        system("cls");
        cout<<"1.插入利率。"<<endl<<"2.修改利率。"<<endl;
        cout<<"3.删除利率。"<<endl<<"4.查找利率。"<<endl;
        cout<<"5.显示所有利率。"<<endl<<"6.退出。"<<endl;
        cout<<"请选择：";
        int i;
        while(1)//限制只响应1-6的数字按键输入
        {
            if(kbhit())//kbhit返回1是表示有键盘按钮按下
            {
                char ch;
                ch=getch();
                if(ch>48&&ch<55)//判断按下的是不是1-6的数字键
                {
                    i=ch-48;
                    break;
                }
                fflush(stdin);//清空键盘缓冲区
            }
        }
        switch(i)
        {
            case 1:
            Insert(bank);
            cout<<endl<<"按任意键返回！";
            getch();
            break;
            case 2:
            Change(bank);
            cout<<endl<<"按任意键返回！";
            getch();
            break;
            case 3:
            Del(bank);
            cout<<endl<<"按任意键返回！";
            getch();
            break;
            case 4:
            Find(bank);
            cout<<endl<<"按任意键返回！";
            getch();
            break;
            case 5:
            Display(bank);
            cout<<endl<<"按任意键返回！";
            getch();
            break;
            case 6:
            Save(bank);
            exit(0);
            break;
        }
    }while(1);
    return 0;
}

void Initialization(Bank &b)
{
    fstream file;
    ifstream iFile("date");//判断文件是否存在，不存在则创建
    if(iFile.fail())
    {
        ofstream oFile("date");
        if(oFile.fail())
        throw("文件打开失败！");
        oFile.close();
    }
    else
    {
        iFile.close();
    }
    file.open("date",ios::in|ios::out|ios::binary);
    file.seekg(0);
    file.read((char*)&b,sizeof(Bank));
    file.close();
}
void Insert(Bank &b)
{
    char a;
    int time;
    cout << "请输入时间单位(m代表月，y代表年): ";
    cin >> a;
    cout << "请输入时间: ";
    cin >> time;
    if(a=='y' || a=='Y')
        time *= 12;
    cout<<"请输入利率：";
    float n;
    cin>>n;
    b.rate[b.last].time=time;
    b.rate[b.last].value=n;
    b.last++;
}
void Change(Bank &b)
{
    char a;
    int time;
    int i=0;
    cout << "要修改内容的时间单位(m代表月，y代表年): ";
    cin >> a;
    cout << "要修改内容的时间: ";
    cin >> time;
    if(a=='y' || a=='Y')
        time *= 12;
    for(i=0;i<b.last;i++)
    {
        if(b.rate[i].time==time)
        break;
    }
    if(i==b.last)
    cout<<"没有该时间的利率信息！";
    else
    {
        int n;
        cout<<"请输入新的利率：";
        cin>>n;
        b.rate[i].value=n;
    }
}
void Del(Bank &b)
{
    char a;
    int time;
    int i=0;
    cout << "要删除内容的时间单位(m代表月，y代表年): ";
    cin >> a;
    cout << "要删除内容的时间: ";
    cin >> time;
    if(a=='y' || a=='Y')
        time *= 12;
    for(i=0;i<b.last;i++)
    {
        if(b.rate[i].time==time)
        break;
    }
    if(i==b.last)
    cout<<"没有该时间的利率信息！";
    else
    {
        for(;i+1<b.last;i++)
        {
            b.rate[i]=b.rate[i+1];
        }
        b.last--;
    }
}
void Find(Bank b)
{
    char a;
    int time;
    int i=0;
    cout << "要查找内容的时间单位(m代表月，y代表年): ";
    cin >> a;
    cout << "要查找内容的时间: ";
    cin >> time;
    if(a=='y' || a=='Y')
        time *= 12;
    for(i=0;i<b.last;i++)
    {
        if(b.rate[i].time==time)
        break;
    }
    if(i==b.last)
    cout<<"没有该时间的利率信息！";
    else
    {
        cout<<"时间："<<b.rate[i].time<<endl;
        cout<<"利率："<<b.rate[i].value<<endl;
    }
}
void Display(Bank b)
{
    for(int i=0;i<b.last;i++)
    {
        cout<<"时间："<<b.rate[i].time<<endl;
        cout<<"利率："<<b.rate[i].value<<endl<<endl;
    }
}
void Save(Bank &b)
{
    fstream file;
    file.open("date",ios::in|ios::out|ios::binary);
    file.seekp(0,ios::beg);
    file.write((char*)&b,sizeof(Bank));
}
