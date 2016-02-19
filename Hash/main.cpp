#include <iostream>
#include <windows.h>
#include <WinBase.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <fstream>
#define N 90000
using namespace std;
struct node
{
    int data;
    node *next;
};
void Creat_Close_H(int H[],int D[],int m);//H为散列表，D为数据
void Find_Close_H(int H[],int i,int m);//H为散列表，i为要查找的数据
void Creat_Open_H(node H[],int D[],int m);
void Find_Open_H(node H[],int i,int m);
void Creat_Over_H(node* H[],int D[],int m);
void Find_Over_H(node* H[],int i,int m);
void Random(int D[]);
int Prime();
int main()
{
    int rand[N];
    int m=N;//Prime();
    Random(rand);
    int Chash[N];
    Creat_Close_H(Chash,rand,m);
    node Ohash[N];
    Creat_Open_H(Ohash,rand,m);
    node* Ovhash[N];
    for(int a=0;a<N;a++)
    {
        Ovhash[a]=NULL;
    }
    Creat_Over_H(Ovhash,rand,m);

    clock_t clk1,clk2;
    clk1=clock();
    for(int i=0;i<N;i++)
    {
        Find_Close_H(Chash,rand[i],m);
    }
    clk2=clock();
    cout<<"闭散列表时间为："<<(double)(clk2-clk1)/CLOCKS_PER_SEC<<" s"<<endl;
    cout<<endl;
    clk1=clock();
    for(int i=0;i<N;i++)
    {
        Find_Open_H(Ohash,rand[i],m);
    }
    clk2=clock();
    cout<<"开散列表时间为："<<(double)(clk2-clk1)/CLOCKS_PER_SEC<<" s"<<endl;
    cout<<endl;
    clk1=clock();
    for(int i=0;i<N;i++)
    {
        Find_Over_H(Ovhash,rand[i],m);
    }
    clk2=clock();
    cout<<"外散列表时间为："<<(double)(clk2-clk1)/CLOCKS_PER_SEC<<" s"<<endl;
    return 0;
}
void Creat_Close_H(int H[],int D[],int m)
{
    int p;
    bool position[N];
    for(int a=0;a<N;a++)
    {
        position[a]=0;
    }
    for(int i=0;i<N;i++)
    {
        p=D[i]%m;
        if(!position[p])
        {
            position[p]=1;
            H[p]=D[i];
        }
        else
        {
            while(position[p])
            {
                p=(p+11)%N;
            }
            position[p]=1;
            H[p]=D[i];
        }
    }
}
void Find_Close_H(int H[],int i,int m)
{
    int p;
    p=i%m;
    while(H[p]!=i)
    {
        p=(p+11)%N;
    }
    if(H[p]!=i)
    {
        cout<<"闭散列表查找失败！"<<endl;
    }
}
void Creat_Open_H(node H[],int D[],int m)
{
    bool position[N];
    for(int a=0;a<N;a++)
    {
        position[a]=0;
    }
    int p;
    for(int i=0;i<N;i++)
    {
        p=D[i]%m;
        if(!position[p])
        {
            position[p]=1;
            H[p].data=D[i];
            H[p].next=NULL;
        }
        else
        {
            node* newn=new node();
            newn->data=D[i];
            newn->next=NULL;
            node *np=&H[p];
            while(np->next!=NULL)
            {
                np=np->next;
            }
            np->next=newn;
        }
    }
}
void Find_Open_H(node H[],int i,int m)
{
    int p;
    p=i%m;
    node *np=&H[p];
    while(np!=NULL&&np->data!=i)
    {
        np=np->next;
    }
    if(np->data!=i||np==NULL)
    {
        cout<<"开散列表查找失败！"<<endl;
    }
}
void Creat_Over_H(node* H[],int D[],int m)
{
    int p;
    node *np;
    for(int i=0;i<N;i++)
    {
        p=D[i]%m;
        if(H[p]==NULL)
        {
            H[p]=new node();
            H[p]->data=D[i];
            H[p]->next=NULL;
        }
        else
        {
            np=H[p];
            while(np->next!=NULL)
            {
                np=np->next;
            }
            np->next=new node();
            np->next->data=D[i];
            np->next->next=NULL;
        }
    }
}
void Find_Over_H(node* H[],int i,int m)
{
    int p;
    p=i%m;
    node *np=H[p];
    while(np!=NULL&&np->data!=i)
    {
        np=np->next;
    }
    if(np->data!=i||np==NULL)
    {
        cout<<"外散列表查找失败！"<<endl;
    }
}
void Random(int D[])
{
    /*srand(time(NULL));
    for(int i=0;i<N;i++)
    {
        D[i]=/*1+i*N;rand();
    }*/

    ifstream work("Data.txt");
    for(int t=0;t<N;t++)
    {
        work>>D[t];
    }
    work.close();
}
int Prime()
{
    int b,flag;
    for(int a=N;a>0;a--)
    {
        int n=sqrt(a);
		flag=1;
		for (b=2;b<=n;b++)
		{
			if (a%b==0)
			{
				flag=0;
				break;
			}
		}
		if (flag)
			return a;
    }
}

