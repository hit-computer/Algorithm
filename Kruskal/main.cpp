#include <iostream>

using namespace std;
struct Edge
{
    int bgn;
    int end;
    int weight;
};
void Sort(Edge E[],int e);//E为边的集合，e为边的数量
int Father(int father[],int i);
void Kruskal(Edge E[],int e,int n);//e为边的数量，n为点的数量
int main()
{
    cout<<"请输入图的节点数目和边数："<<endl;
    int n,e;
    cin>>n>>e;
    Edge E[e];
    cout<<"请按以下格式输入图信息（节点编号 节点编号 权值）:"<<endl;//节点编号从零开始
    for(int i=0;i<e;i++)
    {
        cin>>E[i].bgn>>E[i].end>>E[i].weight;
    }
    Sort(E,e);
    Kruskal(E,e,n);
    return 0;
}
void Sort(Edge E[],int e)
{
    for(int i=0;i<e;i++)
    {
        for(int j=e-1;j>i;j--)
        {
            if(E[j].weight<E[j-1].weight)
            {
                Edge temp;
                temp=E[j];
                E[j]=E[j-1];
                E[j-1]=temp;
            }
        }
    }
}
int Father(int fa[],int v)
{
    int f=v;
    while(fa[f]>=0&&f!=0)
    {
        f=fa[f];
    }
    return f;
}
void Kruskal(Edge E[],int e,int n)
{
    int fa[n];
    int bnf,edf,i;
    for(i=0;i<n;i++)
    {
        fa[i]=-i;
    }
    for(i=0;i<e;i++)
    {
        bnf=Father(fa,E[i].bgn);
        edf=Father(fa,E[i].end);
        if(bnf!=edf)
        {
            fa[E[i].end]=E[i].bgn;
        }
    }
    for(i=0;i<n;i++)
    {
        if(fa[i]>=0)
        cout<<"节点"<<i<<"的父节点： "<<fa[i]<<endl;
    }
}
