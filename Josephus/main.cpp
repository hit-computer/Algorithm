#include <iostream>
using namespace std;

struct Queue
{
    int data[100];
    int front;//队列的头
    int rear;//队列的尾
};

void MakeNull(Queue &Q);//清空队列
bool IsEmpty(Queue Q);//判断队列是否为空
void InQueue(Queue &Q,int m);//入队
void OutQueue(Queue &Q,int &n);//出队
int LookQueue(Queue Q);//查看队首元素

int main()
{
    cout << "请输入总人数N(N<100)：" ;
    int n;
    cin>>n;
    cout<<"请输入开始的编号K(K<=N)：";
    int k;
    cin>>k;
    cout<<"请输入计数个数M：";
    int m;
    cin>>m;
    Queue q;
    int t=0;
    MakeNull(q);
    int Result[n];
    for(int i=1;i<=n;i++)//将所有人员编号入队
    {
        InQueue(q,i);
    }
    for(int i=0;i<n;i++)
    {
        if(LookQueue(q)!=k)//查找编号为K的元素
        {
            int data;
            OutQueue(q,data);
            InQueue(q,data);
        }
        else
        break;
    }
    while(!IsEmpty(q))
    {
        for(int i=0;i<m-1;i++)//循环计数，逐个出队
        {
            int data;
            OutQueue(q,data);
            InQueue(q,data);
        }
        OutQueue(q,Result[t]);
        t++;
    }
    for(int i=0;i<n;i++)
    {
        cout<<Result[i]<<"  ";
    }
    return 0;
}

/***********队列操作函数的具体实现***********/

void MakeNull(Queue &Q)
{
    Q.front=Q.rear=0;
}
bool IsEmpty(Queue Q)
{
    if(Q.front==Q.rear)
    return true;
    else
    return false;
}
void InQueue(Queue &Q,int m)
{
    Q.data[Q.rear%100]=m;
    Q.rear++;
}
void OutQueue(Queue &Q,int &n)
{
    n=Q.data[Q.front%100];
    Q.front++;
}
int LookQueue(Queue Q)
{
    return Q.data[Q.front];
}
