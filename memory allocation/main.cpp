#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
using namespace std;

struct node
{
    char data;//一个字节的数据
    int next;//下一个内容的下标
};
struct RAM
{
    node Memory[600];//600个字节的总内存空间
    int head;//已用空间的首地址
    int tail;//已用空间的尾地址
    int first;//空余空间的首地址
    int last;//空余空间的尾地址
    int Nuse;//未用空间大小
};
void Initialization(RAM &r);//初始化计算机内存
int Malloc(RAM &r,int size);//申请一个大小为size的内存空间，返回内存首地址
void Del(RAM &r,int h,int size);//释放首地址为h的大小为size的内存空间
int SizeOf(RAM r,int h);//返回从h地址开始到结尾的总空间大小
int main()
{
    RAM Ram;
    Initialization(Ram);
    do
    {
        system("cls");
        cout<<"1.申请内存空间。"<<endl;
        cout<<"2.释放内存空间。"<<endl;
        cout<<"3.退出。"<<endl;
        cout<<"请输入选择："<<endl;
        int i;
        int n,t;//内存大小和内存首地址
        while(1)//限制只响应1-3的数字按键输入
        {
            if(kbhit())//kbhit返回1是表示有键盘按钮按下
            {
                char ch;
                ch=getch();
                if(ch>48&&ch<52)//判断按下的是不是1-3的数字键
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
            cout<<"请输入要分配的内存大小：";
            cin>>n;
            t=Malloc(Ram,n);
            if(t!=-1)
            cout<<"所分配的空间首地址为"<<t<<endl;
            cout<<"按任意键返回！";
            getch();
            break;
            case 2:
            cout<<"需要释放的内存的首地址以及空间大小：";
            cin>>t>>n;
            Del(Ram,t,n);
            cout<<"按任意键返回！";
            getch();
            break;
            case 3:
            exit(0);
            break;
        }
    }while(1);
    return 0;
}

void Initialization(RAM &r)
{
    r.head=r.tail=0;
    r.first=1;//初始化第一个地址内存已被使用
    r.last=599;
    r.Nuse=600;
    for(int i=0;i<600;i++)
    {
        if(i!=599)
        r.Memory[i].next=i+1;
        else
        r.Memory[i].next=-1;
    }
}

int Malloc(RAM &r,int size)
{
    if(r.Nuse>=size)
    {
        int n,m,result;
        n=r.tail;
        result=m=r.first;
        for(int i=0;i<size;i++)
        {
            r.Memory[n].next=m;
            n=m;
            m=r.Memory[m].next;
        }
        r.tail=n;
        r.first=m;
        r.Nuse=r.Nuse-size;
        return result;
    }
    else
    {
        cout<<"没用足够的剩余空间可分配！"<<endl;
        return -1;
    }
}

void Del(RAM &r,int h,int size)
{
    int n,m;
    n=h;
    m=r.last;
    int i=0;
    if(SizeOf(r,h)<size)
    {
        cout<<"释放的空间过多！"<<endl;
    }
    else
    {
        r.Nuse=r.Nuse+size;
        for(int i=1;i<size;i++)
        {
            n=r.Memory[n].next;
        }
        r.Memory[r.last].next=h;
        r.last=n;
        int t=r.head;
        while(r.Memory[t].next!=h)
        {
            t=r.Memory[t].next;
        }
        if(n==r.tail)
        {
            r.tail=t;
        }
        else
        {
            r.Memory[t].next=r.Memory[n].next;
        }
    }
}
int SizeOf(RAM r,int h)
{
    int n,m;
    n=h;
    m=1;
    while(n!=r.tail)
    {
        n=r.Memory[n].next;
        m++;
    }
    return m;
}
