#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
using namespace std;
#define max 80
template <class T> //使用C++模版，使堆栈适用于各种数据类型
struct STACK
{
    int top;
    T data[max];
};
template <class T>
void MakeNull(STACK<T> &s);//将栈s置空
template <class T>
bool Empty(STACK<T> s);//判断s是否为空
template <class T>
T Looktop(STACK<T> s);//查看栈顶元素
template <class T>
T Pop(STACK<T> &s);//返回栈顶元素
template <class T>
void Push(STACK<T> &s,T x);//将元素x压入栈顶
void Calcolate(char str[]);//计算表达式的值
int main()
{
    STACK<char> stack;
    int t=0;
    char ch;
    char array[max];
    char final[max+max];
    cout<<"请输入中缀表达式（负数直接输入不用加括号，如-1.32*-2.6--3.2）："<<endl;
    cin>>array;
    MakeNull(stack);
    for(int i=0;array[i]!='\0';i++)
    {
        switch(array[i])
        {
            case '(':
            Push(stack,array[i]);//左括号直接压入栈
            break;
            case ')':
            while(Looktop(stack)!='('&&!Empty(stack)) //右括号开始弹栈
            {
                final[t]=Pop(stack);
                t++;
            }
            ch=Pop(stack);
            break;
            case '+':
            case '-':
            if(array[i]=='-'&&(i==0||array[i-1]=='+'||array[i-1]=='-'||array[i-1]=='*'||array[i-1]=='/'||array[i-1]=='%'||array[i-1]=='('))
            {
                final[t]='!';
                t++;
            }
            else
            {
                if(Looktop(stack)!='('&&!Empty(stack))
                {
                    while(!Empty(stack)&&Looktop(stack)!='(')
                    {
                        final[t]=Pop(stack);
                        t++;
                    }
                    Push(stack,array[i]);
                }
                else
                {
                    Push(stack,array[i]);
                    final[t]=' ';
                    t++;
                }
            }
            break;
            case '*':
            case '/':
            case '%':
            if(Looktop(stack)=='/'||Looktop(stack)=='*'||Looktop(stack)=='%')
            {
                while((Looktop(stack)=='/'||Looktop(stack)=='*'||Looktop(stack)=='%')&&!Empty(stack)&&Looktop(stack)!='(')
                {
                    final[t]=Pop(stack);
                    t++;
                }
                Push(stack,array[i]);
            }
            else
            {
                Push(stack,array[i]);
                final[t]=' ';
                t++;
            }
            break;
            default:
            final[t]=array[i];
            t++;
            break;
        }
    }
    while(!Empty(stack))
    {
        final[t]=Pop(stack);
        t++;
    }
    final[t]='\0';
    cout<<"输出的后缀表达式（！号表示负号）："<<endl;
    cout<<final<<endl;
    Calcolate(final);//计算数值并且输出
    return 0;
}
template <class T>
void MakeNull(STACK<T> &s)
{
    s.top=max;
}
template <class T>
bool Empty(STACK<T> s)
{
    if(s.top>max-1)
    return true;
    else
    return false;
}
template <class T>
T Looktop(STACK<T> s)
{
    if(Empty(s))
    return ' ';
    else
    return (s.data[s.top]);
}
template <class T>
T Pop(STACK<T> &s)
{
    if(Empty(s))
    {
        cout<<"stack is empty!"<<endl;
        exit(0);
    }
    else
    {
        s.top=s.top+1;
        return (s.data[s.top-1]);
    }
}
template <class T>
void Push(STACK<T> &s,T x)
{
    if(s.top==0)
    {
        cout<<"stack is full!"<<endl;
        exit(0);
    }
    else
    {
        s.top=s.top-1;
        s.data[s.top]=x;
    }
}

void Calcolate(char str[])//遇到运算符是弹出栈顶两元素计算后压入栈顶
{
    STACK<float> f_stack;
    STACK<int> i_stack;
    MakeNull(f_stack);
    MakeNull(i_stack);
    float result=0;
    int flag=0;
    float ft1;
    float ft2;
    for(int i=0;str[i]!='\0';i++)
    {
        float final=0;
        if(str[i]=='!')
        {
            flag=1;
        }
        if((str[i]>='0'&&str[i]<='9')||str[i]=='.')
        {
            if(str[i]!='.')
            {
                Push(i_stack,str[i]-48);//将字符转换成int型数据
            }
            else
            {
                int t=0;
                while(!Empty(i_stack))
                {
                    final=Pop(i_stack)*pow(10,t)+final;
                    t++;
                }
                i++;
                int t1=1;
                for(;str[i]>='0'&&str[i]<='9';i++)
                {
                    final=pow(0.1,t1)*(str[i]-48)+final;//将各个位上的int型数据计算得到float型的数据
                    t1++;
                }
                if(flag==1)
                {
                    final=(-1)*final;
                    flag=0;
                }
                Push(f_stack,final);
            }
        }
        else
        {
            if(!Empty(i_stack))
            {
                int t=0;
                while(!Empty(i_stack))
                {
                    final=Pop(i_stack)*pow(10,t)+final;
                    t++;
                }
                if(flag==1)
                {
                    final=(-1)*final;
                    flag=0;
                }
                Push(f_stack,final);
            }
        }
        switch(str[i])
        {
            case '+':
            result=Pop(f_stack)+Pop(f_stack);
            Push(f_stack,result);
            break;
            case '-':
            result=(-1)*Pop(f_stack);
            result=result+Pop(f_stack);
            Push(f_stack,result);
            break;
            case '*':
            result=Pop(f_stack)*Pop(f_stack);
            Push(f_stack,result);
            break;
            case '/':
            result=pow(Pop(f_stack),-1)*Pop(f_stack);
            Push(f_stack,result);
            break;
            case '%':
            ft1=Pop(f_stack);
            ft2=Pop(f_stack);
            result=(int)ft2%(int)ft1;
            Push(f_stack,result);
            break;
            default:
            break;
        }
    }
    result=Pop(f_stack);
    cout<<"计算结果为："<<result<<endl;
}
