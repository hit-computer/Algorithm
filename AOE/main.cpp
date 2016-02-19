#include <iostream>
#include <queue>
#include <stack>
using namespace std;
struct Edge
{
    int start;
    int end;
    int weight;
};
void Indegree(int de[],int G[][30],int n);
void TopoOrderE(int de[],int G[][30],int VE[],int n);
void TopoOrderL(int de[],int G[][30],int VL[],int n);
int main()
{
    cout<<"请输入图的节点数目和边数："<<endl;
    int n,e;
    cin>>n>>e;
    int Graph[n][30];
    int in_degree[n];
    int in_degree1[n];
    int Ve[n];
    int Vl[n];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            Graph[i][j]=-1;
        }
        in_degree[i]=0;
        Ve[i]=Vl[i]=0;
    }
    Edge E[e];
    cout<<"请按以下格式输入图信息（节点编号 节点编号 边的权值）"<<endl;
    for(int i=0;i<e;i++)
    {
        int num1,num2,weight;
        cin>>num1>>num2>>weight;
        Graph[num1][num2]=weight;
        E[i].start=num1;
        E[i].end=num2;
        E[i].weight=weight;
    }
    Indegree(in_degree,Graph,n);
    for(int i=0;i<n;i++)
    {
        in_degree1[i]=in_degree[i];
    }
    TopoOrderE(in_degree,Graph,Ve,n);
    Vl[n-1]=Ve[n-1];
    TopoOrderL(in_degree1,Graph,Vl,n);
    int AOE_e[e];
    int AOE_l[e];
    for(int i=0;i<e;i++)
    {
        int es=E[i].start;
        int ee=E[i].end;
        AOE_e[i]=Ve[es];
        AOE_l[i]=Vl[ee]-Graph[es][ee];
        cout<<"活动"<<i<<"的最早开始时间和最迟开始时间："<<AOE_e[i]<<"  "<<AOE_l[i]<<endl;
    }
    return 0;
}
void Indegree(int de[],int G[][30],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(G[j][i]>=0)
            {
                de[i]=de[i]+1;
            }
        }
    }
}
void TopoOrderE(int de[],int G[][30],int VE[],int n)
{
    int nodecount;
    queue<int> Q;
    for(int i=0;i<n;i++)
    {
        if(de[i]==0)
        {
            Q.push(i);
        }
    }
    nodecount=0;
    while(!Q.empty())
    {
        int v=Q.front();
        Q.pop();
        for(int i=0;i<n;i++)
        {
            if(G[i][v]>0&&(VE[v]<VE[i]+G[i][v]))
            VE[v]=VE[i]+G[i][v];
        }
        nodecount++;
        for(int i=0;i<n;i++)
        {
            if(G[v][i])
            {
                de[i]=de[i]-1;
                if(de[i]==0)
                {
                    Q.push(i);
                }
            }
        }
    }
    if(nodecount<n)
    cout<<"图中有环路"<<endl;
}
void TopoOrderL(int de[],int G[][30],int VL[],int n)
{
    int nodecount;
    queue<int> Q;
    stack<int> S;
    for(int i=0;i<n;i++)
    {
        if(de[i]==0)
        {
            Q.push(i);
        }
    }
    nodecount=0;
    while(!Q.empty())
    {
        int v=Q.front();
        Q.pop();
        S.push(v);
        nodecount++;
        for(int i=0;i<n;i++)
        {
            if(G[v][i])
            {
                de[i]=de[i]-1;
                if(de[i]==0)
                {
                    Q.push(i);
                }
            }
        }
    }
    int j;
    while(!S.empty())
    {
        j=S.top();
        S.pop();
        for(int i=0;i<n;i++)
        {
            if(G[j][i]>0&&(VL[j]<VL[i]-G[j][i]))
            VL[j]=VL[i]-G[j][i];
        }
    }
    if(nodecount<n)
    cout<<"图中有环路"<<endl;
}
