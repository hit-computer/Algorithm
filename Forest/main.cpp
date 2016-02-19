#include <iostream>

using namespace std;
struct node
{
    node *lchild;
    node *rchild;
    char data;
    int num;//用于方便二叉树转森林
};
typedef node* Btree;
struct child
{
    int index;
    child *next;
};
struct forest
{
    char data;
    child *cd;
    Btree t;//用于方便森林转二叉树
    bool root;//标明该节点是否为根结点
};
int flag=0;
void Create(Btree &t);
void PreOrder(Btree t,forest ft[]);
void CForest(Btree t,forest ft[]);
void TreeToForest(Btree t,forest ft[]);
void Display(forest ft[],int n);
void ForestToTree(forest ft[],Btree &t,int n);
void PreVisite(Btree t);
int main()
{
    int n;
    cout<<"请输入节点个数：";
    cin>>n;
    Btree tree;
    cout<<"请按照先根的顺序输入二叉树的节点，为空的儿子用‘#’表示："<<endl;
    Create(tree);
    forest ft[n+3];
    TreeToForest(tree,ft);
    Display(ft,n);
    cout<<endl<<"森林转换成树的结果（先根顺序）："<<endl;
    Btree T;
    ForestToTree(ft,T,n);
    PreVisite(T);
    return 0;
}
void Create(Btree &t)
{
    char ch;
    cin>>ch;
    if(ch=='#')//输入‘#’时表示该节点为空
    t=NULL;
    else
    {
        if(!(t=new node))
        return ;
        t->data=ch;
        Create(t->lchild);//建立左儿子
        Create(t->rchild);//建立右儿子
    }
}
void PreOrder(Btree t,forest ft[])
{
    if(t!=NULL)
    {
        ft[flag].data=t->data;
        ft[flag].root=0;
        t->num=flag;
        flag++;
        PreOrder(t->lchild,ft);
        PreOrder(t->rchild,ft);
    }
}
void CForest(Btree t,forest ft[])
{
    if(t!=NULL)
    {
        if(t->lchild!=NULL)
        {
            child *sp=new child;
            Btree tem=t->lchild;
            ft[t->num].cd=sp;
            sp->index=tem->num;
            tem=tem->rchild;
            while(tem!=NULL)
            {
                child *nt=new child;
                nt->index=tem->num;
                sp->next=nt;
                sp=nt;
                tem=tem->rchild;
            }
            sp->next=NULL;
        }
        else
        {
            ft[t->num].cd=NULL;
        }
        CForest(t->lchild,ft);
        CForest(t->rchild,ft);
    }
}
void TreeToForest(Btree t,forest ft[])
{
    PreOrder(t,ft);
    CForest(t,ft);
    Btree tem=t->rchild;
    while(tem!=NULL)
    {
        ft[tem->num].root=1;
        tem=tem->rchild;
    }
}
void Display(forest ft[],int n)
{
    child *tem;
    for(int i=0;i<n;i++)
    {
        cout<<"树的父节点 "<<ft[i].data<<" :";
        tem=ft[i].cd;
        while(tem!=NULL)
        {
            cout<<ft[tem->index].data<<"  ";
            tem=tem->next;
        }
        cout<<endl;
    }
}
void ForestToTree(forest ft[],Btree &t,int n)
{
    for(int i=0;i<n;i++)
    {
        ft[i].t=new node;
        ft[i].t->data=ft[i].data;
    }
    t=ft[0].t;
    Btree tem=t;
    for(int i=0;i<n;i++)
    {
        if(ft[i].root)
        {
            tem->rchild=ft[i].t;
            tem=tem->rchild;
        }
    }
    tem->rchild=NULL;
    for(int i=0;i<n;i++)
    {
        if(ft[i].cd!=NULL)
        {
            int a=ft[i].cd->index;
            ft[i].t->lchild=ft[a].t;
            child *tem;
            tem=ft[i].cd;
            while(tem!=NULL)
            {
                int b=tem->index;
                if(tem->next!=NULL)
                {
                    int m=tem->next->index;
                    ft[b].t->rchild=ft[m].t;
                }
                else
                {
                    ft[b].t->rchild=NULL;
                }
                tem=tem->next;
            }
        }
        else
        {
            ft[i].t->lchild=NULL;
        }
    }
}
void PreVisite(Btree t)
{
    if(t!=NULL)
    {
        cout<<t->data<<"  ";
        PreVisite(t->lchild);
        PreVisite(t->rchild);
    }
}
