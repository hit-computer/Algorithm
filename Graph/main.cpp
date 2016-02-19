#include <iostream>
#include <stack>
#include <queue>
using namespace std;
typedef struct node
{
    int adjvex;
    node *next;
}Edgenode;
typedef struct
{
    char data;
    Edgenode *firstedge;
}Vertexnode;
void CreateGraph(Vertexnode G[],int n,int e);//图的邻接表的构造
void Dfs(Vertexnode G[],int i);//深度优先搜索
void Bfs(Vertexnode G[],int i);//广度优先搜索
void Make_visited_null();//初始化visited数组
bool visited[50];//visited数组用于存储节点是否被访问过

int main()
{
    cout<<"请输入顶点数和边数：";
    int n,e;
    cin>>n>>e;
    Vertexnode G[n];//声明一个图的邻接表
    CreateGraph(G,n,e);//建立图的邻接表
    Make_visited_null();
    cout<<"深度优先搜索：";
    for(int i=0;i<n;i++)
    {
        Dfs(G,i);
    }
    Make_visited_null();
    cout<<endl<<"广度优先搜索：";
    for(int i=0;i<n;i++)
    {
        Bfs(G,i);
    }
}
void CreateGraph(Vertexnode G[],int n,int e)
{
    for(int i=0;i<n;i++)
    {
        cout<<"第"<<i+1<<"个顶点的名称";
        cin>>G[i].data;
        G[i].firstedge=NULL;
    }
    cout<<"请输入边的信息"<<endl;
    int head,tail;
    for(int i=0;i<e;i++)
    {
        cin>>head>>tail;//节点的编号从1开始
        head--;
        tail--;
        Edgenode *p=new Edgenode;
        p->adjvex=tail;
        p->next=G[head].firstedge;
        G[head].firstedge=p;
    }
}
void Dfs(Vertexnode G[],int i)
{
    if(!visited[i])
    {
        Edgenode *p;
        int w;
        stack<int> S;//使用c++自带的栈
        cout<<G[i].data<<" ";
        visited[i]=1;
        S.push(i);
        p=G[i].firstedge;
        while(!S.empty())
        {
            while(p!=NULL)
            {
                w=p->adjvex;
                if(!visited[w])
                {
                    cout<<G[w].data<<" ";
                    S.push(w);
                    visited[w]=1;
                    p=G[w].firstedge;
                }
                else
                {
                    p=p->next;
                }
            }
            if(!S.empty())
            {
                S.pop();
                if(!S.empty())
                {
                    int t=S.top();
                    p=G[t].firstedge;
                }
            }
        }
    }
}
void Bfs(Vertexnode G[],int i)
{
   if(!visited[i])
   {
       int t;
       Edgenode *p;
       queue<int> Q;//使用C++自带的队列
       Q.push(i);
       visited[i]=1;
       while(!Q.empty())
       {
           t=Q.front();
           Q.pop();
           cout<<G[t].data<<" ";
           p=G[t].firstedge;
           while(p!=NULL)
           {
               if(!visited[p->adjvex])
               {
                   Q.push(p->adjvex);
                   visited[p->adjvex]=1;
               }
               p=p->next;
           }
       }
   }
}
void Make_visited_null()
{
    for(int i=0;i<30;i++)
    {
        visited[i]=0;
    }
}
