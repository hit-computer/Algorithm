#include <iostream>
#include <fstream>
#define tree_t 4  //每个节点的关键字数目<=2*t-1
using namespace std;
typedef int Key;
typedef char data;

struct Data//定义数据
{
    Key key;//数据关键字
    data content[26];//数据内容
};

struct node //定义B树的每一个节点信息
{
    Data* key[2*tree_t-1];//节点中的7个指向数据的关键字
    node* child[2*tree_t];//7个关键字应有8棵子树
    bool leaf;//是否为叶子
    int n;//节点中关键字的数目
};

typedef node* Bnode;

void B_tree_create(Bnode &T);
void B_tree_split_child(Bnode &x,int i,Bnode &y);
void B_tree_insert(Bnode &T,Data* K);
void B_tree_insert_nonfull(Bnode &x,Data* K);
Data* B_tree_search(Bnode x,Key K);
void B_tree_delete(Bnode &x,Key K);
void B_tree_union(Bnode &x,int i);
int main()
{
    Bnode Btree;//声明一个B树的根结点
    B_tree_create(Btree);
    int N=140;
    Data K[N];
    ifstream work("Data.txt");
    for(int t=0;t<N;t++)
    {
        work>>K[t].key;
        work>>K[t].content;
    }
    work.close();
    for(int i=0;i<N;i++)
    {
        B_tree_insert(Btree,&K[i]);
    }
    Data* result=new Data();
    Key ky=126;
    int t=0;
    for(int a=0;a<N-3;a++)
    {
        int di=K[a].key;
        //cout<<di<<"  *"<<endl;
        B_tree_delete(Btree,di);
        t=0;
        for(int i=0;i<N;i++)
        {
            ky=K[i].key;
            result=B_tree_search(Btree,ky);
            if(result==NULL)
            continue;
            //cout<<result->key<<"  ";
            //cout<<result->content<<endl;
            t++;
        }
        cout<<t<<endl;
    }
    return 0;
}
void B_tree_create(Bnode &T)
{
    T=new node();
    T->leaf=true;
    T->n=0;
}
void B_tree_split_child(Bnode &x,int i,Bnode &y)
{
    Bnode z=new node();
    z->leaf=y->leaf;
    z->n=tree_t-1;
    for(int j=0;j<tree_t-1;j++)
    {
        z->key[j]=y->key[j+tree_t];
    }
    if(!y->leaf)
    {
        for(int j=0;j<tree_t;j++)
        {
            z->child[j]=y->child[j+tree_t];
        }
    }
    y->n=tree_t-1;
    for(int j=x->n;j>i;j--)
    {
        x->child[j+1]=x->child[j];
    }
    x->child[i+1]=z;
    for(int j=x->n;j>i;j--)
    {
        x->key[j]=x->key[j-1];
    }
    x->key[i]=y->key[tree_t-1];
    x->n=x->n+1;
}
void B_tree_insert(Bnode &T,Data* K)
{
    if(T->n==2*tree_t-1)
    {
        Bnode s=new node();
        Bnode r=T;
        s->leaf=false;
        s->n=0;
        s->child[0]=r;
        T=s;
        B_tree_split_child(s,0,r);
        B_tree_insert_nonfull(s,K);
    }
    else
    {
        B_tree_insert_nonfull(T,K);
    }
}
void B_tree_insert_nonfull(Bnode &x,Data* K)
{
    int i=(x->n)-1;
    if(x->leaf)
    {
        while(i>=0&&K->key<x->key[i]->key)
        {
            x->key[i+1]=x->key[i];
            i--;
        }
        i++;
        x->key[i]=K;
        x->n=(x->n)+1;
    }
    else
    {
        while(i>=0&&K->key<x->key[i]->key)
        {
            i--;
        }
        i++;
        if(x->child[i]->n==2*tree_t-1)
        {
            B_tree_split_child(x,i,x->child[i]);
            if(K->key>x->key[i]->key)
            {
                i=i+1;
            }
        }
        B_tree_insert_nonfull(x->child[i],K);
    }
}
Data* B_tree_search(Bnode x,Key K)
{
    int i=0;
    while(i<x->n&&K>x->key[i]->key)
    {
        i++;
    }
    if(i<x->n&&K==x->key[i]->key)
    {
        return x->key[i];
    }
    if(x->leaf)
    {
        return NULL;
    }
    else
    {
        return B_tree_search(x->child[i],K);
    }
}
void B_tree_delete(Bnode &x,Key K)
{
    int i=0;
    while(i<x->n&&K>x->key[i]->key)
    {
        i++;
    }
    if(i<x->n&&K==x->key[i]->key)
    {
        if(x->leaf)
        {
            for(int j=i;j<(x->n)-1;j++)
            {
                x->key[j]=x->key[j+1];
            }
            x->n=x->n-1;
        }
        else if(i+1<=(x->n))
        {
            Bnode y1=x->child[i];
            Bnode y2=x->child[i+1];
            int t;
            if(y1->n>=tree_t)
            {
                t=(y1->n)-1;
                x->key[i]=y1->key[t];
                B_tree_delete(y1,y1->key[t]->key);
            }
            else if(y2->n>=tree_t)
            {
                x->key[i]=y2->key[0];
                B_tree_delete(y2,y2->key[0]->key);
            }
            else
            {
                Bnode y;
                B_tree_union(x,i);
                B_tree_delete(x->child[i],K);
            }
        }
        else
        {
            cout<<"删除错误！"<<endl;
        }
    }
    else if(x->leaf)
    {
        cout<<"没有改节点！"<<endl;
    }
    else
    {
        if(x->child[i]->n>=tree_t)
        {
            B_tree_delete(x->child[i],K);
        }
        else
        {
            if(i+1<=(x->n)&&x->child[i+1]->n<tree_t)
            {
                B_tree_union(x,i);
            }
            else if(i+1<=(x->n))
            {
                Bnode y1=x->child[i];
                Bnode y2=x->child[i+1];
                y1->key[y1->n]=x->key[i];
                y1->n=y1->n+1;
                x->key[i]=y2->key[0];
                y1->child[y1->n]=y2->child[0];
                int t=0;
                for(t=0;t<y2->n-1;t++)
                {
                    y2->key[t]=y2->key[t+1];
                    y2->child[t]=y2->child[t+1];
                }
                y2->child[t]=y2->child[t+1];
                y2->n=(y2->n)-1;
            }
            else if(i-1>=0&&x->child[i-1]->n<tree_t)
            {
                B_tree_union(x,i-1);
                i--;
            }
            else if(i-1>=0)
            {
                Bnode y1=x->child[i];
                Bnode y2=x->child[i-1];
                int t=0;
                for(t=y1->n;t>0;t++)
                {
                    y1->key[t]=y1->key[t-1];
                    y1->child[t+1]=y1->child[t];
                }
                y1->child[t+1]=y1->child[t];
                y1->key[0]=x->key[i];
                y1->n=y1->n+1;
                x->key[i]=y2->key[y2->n-1];
                y1->child[0]=y2->child[y2->n];
                y2->n=(y2->n)-1;
                B_tree_delete(x->child[i],K);
            }
            B_tree_delete(x->child[i],K);
        }
    }
}
void B_tree_union(Bnode &x,int i)
{
    Bnode y1=x->child[i];
    Bnode y2=x->child[i+1];
    int n1=y1->n;
    int n2=y2->n;
    y1->key[n1]=x->key[i];
    int a=0;
    for(a=0;a<n2;a++)
    {
        y1->key[n1+a+1]=y2->key[a];
        y1->child[n1+a+1]=y2->child[a];
    }
    y1->child[n1+a+1]=y2->child[a];
    for(int t=i;t<(x->n)-1;t++)
    {
        x->key[t]=x->key[t+1];
        x->child[t+1]=x->child[t+2];
    }
    x->n=(x->n)-1;
    y1->n=n1+n2+1;
    delete y2;
}
