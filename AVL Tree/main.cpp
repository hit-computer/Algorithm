#include <iostream>

using namespace std;
struct node
{
    int data;
    int bf;
    node *lchild,*rchild;
};
typedef node* AVL;
void AVL_Insert(AVL &t,int in,int &unbalanced);
void LeftRotation(AVL &t,int &unbalanced);
void RightRotation(AVL &t,int &unbalanced);
void PreOrder(AVL t);
void InOrder(AVL t);
void PostOrder(AVL t);
int main()
{
    cout<<"请输入数据的个数："<<endl;
    int n;
    cin>>n;
    int data[n];
    for(int i=0;i<n;i++)
    {
        cout<<"第"<<i+1<<"个数据：";
        cin>>data[i];
    }
    int unbalanced=0;
    AVL T=NULL;
    for(int i=0;i<n;i++)
    {
        unbalanced=0;
        AVL_Insert(T,data[i],unbalanced);
    }
    PreOrder(T);
    cout<<endl;
    InOrder(T);
    cout<<endl;
    PostOrder(T);
    return 0;
}
void AVL_Insert(AVL &t,int in,int &unbalanced)//unbalanced用于标记是否修改bf的值
{
    if(t==NULL)
    {
        unbalanced=1;
        t=new node;
        t->data=in;
        t->lchild=t->rchild=NULL;
        t->bf=0;
    }
    else if(in<t->data)
    {
        AVL_Insert(t->lchild,in,unbalanced);
        if(unbalanced)
        {
            switch(t->bf)
            {
                case -1:
                t->bf=0;
                unbalanced=0;
                break;
                case 0:
                t->bf=1;
                break;
                case 1:
                LeftRotation(t,unbalanced);
            }
        }
    }
    else if(in>t->data)
    {
        AVL_Insert(t->rchild,in,unbalanced);
        if(unbalanced)
        {
            switch(t->bf)
            {
                case -1:
                RightRotation(t,unbalanced);
                break;
                case 0:
                t->bf=-1;
                break;
                case 1:
                t->bf=0;
                unbalanced=0;
            }
        }
    }
    else
    unbalanced=0;
}
void LeftRotation(AVL &t,int &unbalanced)
{
    AVL tc,lc;
    lc=t->lchild;
    if(lc->bf==1)//ll旋转
    {
        tc=lc->rchild;
        lc->rchild=t;
        t->lchild=tc;
        t->bf=0;
        t=lc;
    }
    else//lr旋转
    {
        tc=lc->rchild;
        lc->rchild=tc->lchild;
        t->lchild=tc->rchild;
        tc->lchild=lc;
        tc->rchild=t;
        switch(tc->bf)
        {
            case 1:
            t->bf=-1;
            lc->bf=0;
            break;
            case 0:
            t->bf=lc->bf=0;
            break;
            case -1:
            t->bf=0;
            lc->bf=1;
            break;
        }
        t=tc;
    }
    t->bf=0;
    unbalanced=0;
}
void RightRotation(AVL &t,int &unbalanced)
{
    AVL tc,rc;
    rc=t->rchild;
    if(rc->bf==-1)//rr旋转
    {
        t->rchild=rc->lchild;
        rc->lchild=t;
        t->bf=0;
        t=rc;
    }
    else//rl旋转
    {
        tc=rc->lchild;
        rc->lchild=tc->rchild;
        t->rchild=tc->lchild;
        tc->rchild=rc;
        tc->lchild=t;
        switch(tc->bf)
        {
            case 1:
            rc->bf=-1;
            t->bf=0;
            break;
            case 0:
            t->bf=rc->bf=0;
            break;
            case -1:
            t->bf=1;
            rc->bf=0;
            break;
        }
        t=tc;
    }
    t->bf=0;
    unbalanced=0;
}
void PreOrder(AVL t)
{
    if(t!=NULL)
    {
        cout<<t->data<<"  ";
        PreOrder(t->lchild);
        PreOrder(t->rchild);
    }
}
void InOrder(AVL t)
{
    if(t!=NULL)
    {
        InOrder(t->lchild);
        cout<<t->data<<"  ";
        InOrder(t->rchild);
    }
}
void PostOrder(AVL t)
{
    if(t!=NULL)
    {
        PostOrder(t->lchild);
        PostOrder(t->rchild);
        cout<<t->data<<"  ";
    }
}
