#include <iostream>
#include <stdlib.h>
#define Max 100000
using namespace std;
struct child
{
    int index;
    child *next;
};
struct forest
{
    char data;
    child *cd;
};
struct node
{
    int num;//节点编号
    int weight;//节点权重
};
typedef node* PN;
void MST_Prim(int G[][30],forest ft[],int root,int n);
void Insert_Forest(forest ft[],int F,int chi);//用于向森林中插入一个节点
void Min_heapify(PN cr[],int i);//保持最小堆特性
void Build_heap(PN cr[]);//建立最小堆
int Heap_min(PN cr[]);//返回最小元素
void Display(forest ft[],int n);
int heap_size;//堆的大小
int main()
{
    cout<<"请输入图的节点数目："<<endl;
    int n;
    cin>>n;
    heap_size=n-1;
    int Graph[n][30];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j)
            Graph[i][j]=Max;
            else
            Graph[i][j]=0;
        }
    }
    forest ft[n];
    cout<<"请按以下格式输入图信息（节点编号 节点编号 权值），编号相同结束"<<endl;
    while(1)
    {
        int num1,num2,weight;
        cin>>num1>>num2>>weight;
        if(num1==num2)
        break;
        Graph[num1][num2]=weight;
        Graph[num2][num1]=weight;
    }
    for(int i=0;i<n;i++)
    {
        ft[i].cd=NULL;
    }
    MST_Prim(Graph,ft,0,n);
    Display(ft,n);
    return 0;
}
void MST_Prim(int G[][30],forest ft[],int root,int n)
{
    PN key[n];
    PN Heap[n];
    int result[n];
    int Father[n];
    for(int i=0;i<n;i++)
    {
        key[i]=new node();
        Heap[i]=key[i];
        key[i]->num=i;
        key[i]->weight=Max;
        result[i]=0;
        Father[i]=-1;
    }
    key[root]->weight=0;
    Build_heap(Heap);
    while(heap_size>=0)
    {
        int u=Heap_min(Heap);
        result[u]=1;
        for(int t=0;t<n;t++)
        {
            if(G[u][t]!=0)
            {
                if(!result[t]&&G[u][t]<key[t]->weight)
                {
                    Father[t]=u;
                    key[t]->weight=G[u][t];
                    //cout<<"!"<<t<<":"<<key[t]->weight<<"  ";
                    Build_heap(Heap);
                }
            }
        }
        //cout<<u<<"   ";
    }
    for(int i=0;i<n;i++)
    {
        if(Father[i]!=-1)
        Insert_Forest(ft,Father[i],i);
    }
}
void Insert_Forest(forest ft[],int F,int chi)
{
    child *cl=NULL;
    cl=new child();
    cl->index=chi;
    cl->next=NULL;
    child *tem=ft[F].cd;
    if(tem==NULL)
    {
        ft[F].cd=cl;
    }
    else
    {
        while(tem->next!=NULL)
        tem=tem->next;
        tem->next=cl;
    }
}
void Min_heapify(PN cr[],int i)
{
    int l=2*i;
    int r=2*i+1;
    int min;
    if(l<=heap_size&&cr[l]->weight<cr[i]->weight)
        min=l;
    else
        min=i;
    if(r<=heap_size&&cr[r]->weight<cr[min]->weight)
        min=r;
    if(min!=i)
    {
        PN temp=cr[i];
        cr[i]=cr[min];
        cr[min]=temp;
        Min_heapify(cr,min);
    }

}
void Build_heap(PN cr[])
{
    int t=heap_size;
    for(int i=t/2;i>=0;i--)
    {
        Min_heapify(cr,i);
    }
}
int Heap_min(PN cr[])
{
    if(heap_size<0)
        exit(0);
    int min=cr[0]->num;
    cr[0]=cr[heap_size];
    heap_size--;
    Min_heapify(cr,0);
    return min;
}
void Display(forest ft[],int n)
{
    child *tem;
    for(int i=0;i<n;i++)
    {
        cout<<"树的父节点 "<<i<<" :";
        tem=ft[i].cd;
        while(tem!=NULL)
        {
            cout<<tem->index<<"  ";
            tem=tem->next;
        }
        cout<<endl;
    }
}
