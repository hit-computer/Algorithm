#include <iostream>

using namespace std;
struct node
{
    char data;
    int parent;
};
struct tree
{
    node T[50];
    int n;//n用于储存数据个数
};
typedef tree* Btree;
int Find_parent(Btree t,int x);
void Create(Btree &t);
void Display(Btree t);
int main()
{
    Btree T=new tree;
    Create(T);
    Display(T);
    return 0;
}

int Find_parent(Btree t,int x)
{
    if(t->T[x].parent!=x)
    t->T[x].parent=Find_parent(t,t->T[x].parent);
    return t->T[x].parent;
}
void Create(Btree &t)
{
    cout<<"请输入数据个数：";
    int n;
    cin>>n;
    t->n=n;
    for(int i=0;i<n;i++)
    {
        t->T[i].parent=i;
    }
    int a1,a2;
    cout<<"请输入有关系的两个数的编号（两数相等时结束输入）："<<endl;
    do
    {
        cin>>a1>>a2;
        if(a1==a2)
        break;
        a1=Find_parent(t,a1);
        a2=Find_parent(t,a2);
        t->T[a1].parent=a2;
    }while(1);
}
void Display(Btree t)
{
    int n=t->n;
    int a=0;
    int parent[n];
    for(int i=0;i<n;i++)
    {
        if(t->T[i].parent==i)
        {
            parent[a]=i;
            a++;
        }
    }
    for(int i=0;i<a;i++)
    {
        cout<<parent[i]<<"的等价类：";
        for(int j=0;j<n;j++)
        {
            if(Find_parent(t,j)==parent[i])
            cout<<j<<"  ";
        }
        cout<<endl;
    }
}
