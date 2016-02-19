#include <iostream>
#include <queue>
using namespace std;
struct node
{
    struct node* lchild;
    struct node* rchild;
    char data;
};
typedef node* Btree;
void Create(Btree &t);
void PreOrder(Btree t);//树的先根遍历结果与其对应二叉树表示的先序遍历结果相同
void PostOrder(Btree t);//树的后根遍历结果与其对应二叉树表示的中序遍历结果相同
void LevelOrder(Btree t);//树的层序遍历
int main()
{
    Btree tree;
    cout<<"请按照先根的顺序输入二叉树的节点，为空的儿子用‘#’表示："<<endl;
    Create(tree);
    cout<<"按照先根顺序输出：";
    PreOrder(tree);
    cout<<endl;
    cout<<"按照后根根顺序输出：";
    PostOrder(tree);
    cout<<endl;
    cout<<"按照层序遍历顺序输出：";
    LevelOrder(tree);
    cout<<endl;
    return 0;
}
void Create(Btree &t)//按照先根顺序创建左右链式结构的二叉树
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
void PreOrder(Btree t)
{
    if(t!=NULL)
    {
        cout<<t->data<<"  ";
        PreOrder(t->lchild);
        PreOrder(t->rchild);
    }
}
void PostOrder(Btree t)
{
    if(t!=NULL)
    {
        PostOrder(t->lchild);
        cout<<t->data<<"  ";
        PostOrder(t->rchild);
    }
}
void LevelOrder(Btree t)
{
    queue<Btree> q;
    while(!q.empty())
    q.pop();
    Btree tem=t;
    while(tem!=NULL)
    {
        q.push(tem);
        tem=tem->rchild;
    }
    while(!q.empty())
    {
        tem=q.front();
        q.pop();
        cout<<tem->data<<"  ";
        tem=tem->lchild;
        while(tem!=NULL)
        {
            q.push(tem);
            tem=tem->rchild;
        }
    }
}
