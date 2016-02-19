#include <iostream>
#include <stdlib.h>
#define Max 100000
using namespace std;
struct node
{
    int num;//节点编号
    int weight;//节点权重
};
typedef node* PN;
void Min_heapify(PN cr[],int i);//保持最小堆特性
void Build_heap(PN cr[]);//建立最小堆
int Heap_min(PN cr[]);//返回最小元素
void Dijkstra(int G[][30],int w,int n);//G是图的邻接矩阵表示形式，w为起始点
int heap_size;//堆的大小
int main()
{
    int n;
    cout<<"请输入节点数目：";
    cin>>n;
    int Graph[n][30];
    heap_size=n-1;
    cout<<"请按以下格式输入图信息（节点编号 节点编号 权值），编号相同结束"<<endl;
    while(1)
    {
        int num1,num2,weight;
        cin>>num1>>num2>>weight;
        if(num1==num2)
        break;
        Graph[num1][num2]=weight;
    }
    cout<<"请输入开始节点编号："<<endl;
    int w;
    cin>>w;
    Dijkstra(Graph,w,n);
    return 0;
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
void Dijkstra(int G[][30],int w,int n)
{
    PN key[n];
    PN heap[n];
    int visit[n];
    for(int i=0;i<n;i++)
    {
        key[i]=new node();
        key[i]->num=i;
        key[i]->weight=Max;
        heap[i]=key[i];
        visit[i]=0;//为零表示没有被访问过
    }
    key[w]->weight=0;
    Build_heap(heap);
    while(heap_size>=0)
    {
        int u=Heap_min(heap);
        visit[u]=1;
        for(int i=0;i<n;i++)
        {
            if(G[u][i]>0&&visit[i]==0)
            {
                if((key[u]->weight+G[u][i])<key[i]->weight)
                {
                    key[i]->weight=key[u]->weight+G[u][i];
                    Build_heap(heap);
                }
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        cout<<"从节点"<<w<<"到节点"<<i<<"的距离为："<<key[i]->weight<<endl;
    }
}
