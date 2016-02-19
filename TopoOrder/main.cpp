#include <iostream>
#include <queue>
using namespace std;
void Indegree(int de[],int G[][30],int n);
void TopoOrder(int de[],int G[][30],int n);
int main()
{
    cout<<"请输入图的节点数目："<<endl;
    int n;
    cin>>n;
    int Graph[n][30];
    int in_degree[n];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            Graph[i][j]=0;
        }
        in_degree[i]=0;
    }
    cout<<"请按以下格式输入图信息（节点编号 节点编号），编号相同结束"<<endl;
    while(1)
    {
        int num1,num2;
        cin>>num1>>num2;
        if(num1==num2)
        break;
        Graph[num1][num2]=1;
    }
    Indegree(in_degree,Graph,n);
    cout<<"拓扑排序结果为："<<endl;
    TopoOrder(in_degree,Graph,n);
    return 0;
}
void Indegree(int de[],int G[][30],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(G[j][i])
            {
                de[i]=de[i]+1;
            }
        }
    }
}
void TopoOrder(int de[],int G[][30],int n)
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
        cout<<v<<"  ";
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
