#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

struct DLine
{
	//系数
    int coef;
	//指数
    int exp;
	//前一项
    DLine *pre;
	//后一项
    DLine *next;
};




int main()
{
    char cTemp[1024];
    char *pChar;
    int flag=0;
	//声明两个链表头
    DLine* phead1=new DLine();
    DLine* phead2=new DLine();
    phead1->pre=phead1->next=NULL;
    phead2->pre=phead2->next=NULL;
    DLine* phead3=NULL;
    cout<<"请在两行中分别 按照系数、指数的顺序输入两个多项式的每一项，并且指数的由大到小顺序"<<endl;
	//读入第一个字符串并且以空格进行分割放到指数系数中
    DLine* pTemp = phead1;
    cin.getline(cTemp,1024);

    pChar = strtok(cTemp," ,");
    phead1->coef = atoi(pChar);
    pChar = strtok(NULL," ,");
    phead1->exp = atoi(pChar);


    pChar =strtok(NULL," ,");
    while(pChar)
    {
        pTemp->next=new DLine();
        pTemp->next->pre = pTemp;
        pTemp = pTemp->next;
        pTemp->coef = atoi(pChar);
        pChar = strtok(NULL," ,");
        pTemp->exp = atoi(pChar);

        pChar =strtok(NULL," ,");
    }
	//读入第二个字符串处理为链表
    pTemp = phead2;
    cin.getline(cTemp,1024);

    pChar = strtok(cTemp," ,");
    phead2->coef = atoi(pChar);
    pChar = strtok(NULL," ,");
    phead2->exp = atoi(pChar);


    pChar =strtok(NULL," ,");
    while(pChar)
    {
        pTemp->next=new DLine();
        pTemp->next->pre = pTemp;
        pTemp = pTemp->next;
        pTemp->coef = atoi(pChar);
        pChar = strtok(NULL," ,");
        pTemp->exp = atoi(pChar);

        pChar =strtok(NULL," ,");
    }
    cout<<"1.多项式相加。"<<endl<<"2.多项式相减。"<<endl<<"请选择：";
    cin>>flag;
    flag=-flag+2;


	//进行运算前的准备，以最大指数链表作为头
    if(phead1->exp > phead2->exp)
    {
        phead3 = phead1;
        phead1 = phead1->next;
        phead3->next= NULL;
    }
    else if(phead1->exp < phead2->exp)
    {
        phead3= phead2;
        if(!flag)
        phead2->coef=-(phead2->coef);
        phead2 = phead2->next;
        phead3->next=NULL;
    }
    else
    {
        phead3=phead1;
        if(flag)
        phead3->coef = phead3->coef + phead2->coef;
        else
        phead3->coef = phead3->coef - phead2->coef;

        phead1 = phead1->next;
        phead2=phead2->next;
        phead3->next = NULL;
    }
    pTemp = phead3;
	//插入式排序法将两条链表合并到第三条
    while(phead1&&phead2)
    {
        if(phead1->exp > phead2->exp)
        {
            pTemp->next=phead1;
            phead1=phead1->next;
            pTemp->next->pre=pTemp;
            pTemp = pTemp->next;
            pTemp->next = NULL;
        }
        else if (phead1->exp < phead2->exp)
        {
            pTemp->next=phead2;
            if(!flag)
            phead2->coef=-(phead2->coef);
            phead2=phead2->next;
            pTemp->next->pre=pTemp;
            pTemp = pTemp->next;
            pTemp->next = NULL;
        }
        else
        {
            pTemp->next=phead1;
            if(flag)
            pTemp->next->coef = pTemp->next->coef +phead2->coef;
            else
            pTemp->next->coef = pTemp->next->coef -phead2->coef;
            phead1= phead1->next;
            phead2 = phead2->next;
            pTemp->next->pre = pTemp;
            pTemp=pTemp ->next;
            pTemp->next=NULL;
        }
    }
    //将剩余的内容追加到末尾
    if(!phead1)
    {
        pTemp->next=phead2;
        while(phead2&&!flag)
        {
            phead2->coef=-(phead2->coef);
            phead2=phead2->next;
        }
    }
    else if(!phead2)
    {
        pTemp->next=phead1;
    }

	//输出第三条链表作为结果
	cout<<endl<<"多项式运算结果为："<<endl;
    pTemp=phead3;
    while(pTemp)
    {
		if(pTemp->coef==0)
		{
			pTemp=pTemp->next;
			continue;
		}
		if(pTemp->exp==0)
		{
			cout<<pTemp->coef<<endl;
		}
		else
        cout<<pTemp->coef<<"x^"<<pTemp->exp<<" ";
        pTemp=pTemp->next;
    }
	getchar();
    return 0;
}

