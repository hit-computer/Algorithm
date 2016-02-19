#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <bitset>
#include <string.h>
#include <stdio.h>
#include <conio.h>
using namespace std;
struct HuffmanCode//每个字符的编码
{
    char ch;
    char code[18];//编码数据
};

struct HuffmanTree//huffman树的一个节点
{
    char ch;
    HuffmanTree *lchild;
    HuffmanTree *rchild;
};
typedef HuffmanTree* HTree;
struct Char_Rate//存储字符的频率
{
    char ch;
    float rate;
    HTree ht;//该字符或该节点对应得Huffman树的节点
};
void Ctreatehuffmantree(HTree &ht,Char_Rate cr[]);//创建huffman树
void CreateCode(HTree &ht,HuffmanCode hc[]);//根据huffman树进行编码
void Min_heapify(Char_Rate cr[],int i);//使用最小堆队列来返回频率最小的节点
void Build_heap(Char_Rate cr[]);//建立最小堆数据结构
Char_Rate Heap_min(Char_Rate cr[]);//返回最小元素
void Heap_increate(Char_Rate cr[],int i,Char_Rate key);
void Heap_insert(Char_Rate cr[],Char_Rate key);//最小堆的插入操作
void CreateRate(Char_Rate cr[],char fname[]);
void Encoded(HuffmanCode hc[],char fname[]);
void Outchar(bool code[],HuffmanCode hc[],int start,int end);
void Decode();
int heap_size;//堆从1开始，heap_size是最后一个元素的位置
char CODE[60];//用于模拟栈
int flag=0;//指向栈顶元素
int main()
{
    HuffmanCode huffman_code[128];//huffman编码的直接寻址表，字符ascll码-32.
    HTree HT;
    Char_Rate CR[128];
    int i=1;
    char ch;
    int t;
    char fname[30];
    fstream _file;
    do
    {
        system("cls");
        for(int t=0;t<128;t++)
        {
            huffman_code[t].ch=0;//0表示没有该字符
        }
        cout<<"1.对文件进行编码"<<endl;
        cout<<"2.对文件进行解码"<<endl;
        cout<<"3.推出程序"<<endl;
        while(1)//限制只响应1-5的数字按键输入
        {
            if(kbhit())//kbhit返回1是表示有键盘按钮按下
            {
                ch=getch();
                if(ch>48&&ch<53)//判断按下的是不是1-5的数字键
                {
                    t=ch-48;
                    break;
                }
                fflush(stdin);//清空键盘缓冲区
            }
        }
        switch(t)
        {
            case 1:
                system("cls");
                cout<<"请输入要编码的文件名称（eg：data.txt）：";
                cin>>fname;
                _file.open(fname,ios::in);
                if(!_file)
                {
                    cout<<"文件不存在！"<<endl;
                    _file.close();
                }
                else
                {
                    _file.close();
                    CreateRate(CR,fname);
                    cout<<endl;
                    for(i=1;i<heap_size+1;i++)
                    {
                        CR[i].ht=new HuffmanTree;
                        CR[i].ht->ch=CR[i].ch;
                        CR[i].ht->lchild=NULL;
                        CR[i].ht->rchild=NULL;
                    }
                    Build_heap(CR);
                    Ctreatehuffmantree(HT,CR);
                    CreateCode(HT,huffman_code);
                    for(int t=0;t<128;t++)
                    {
                        if(huffman_code[t].ch!=0)
                        {
                            cout<<huffman_code[t].ch<<": ";
                            for(int j=0;huffman_code[t].code[j]!=-1;j++)
                            {
                                cout<<(int)huffman_code[t].code[j];
                            }
                            cout<<endl;
                        }
                    }
                    Encoded(huffman_code,fname);
                }
                cout<<"按任意键返回！"<<endl;
                getch();
                break;
            case 2:
                system("cls");
                Decode();
                cout<<endl<<"按任意键返回！"<<endl;
                getch();
                break;
            case 3:
                exit(1);
                break;
        }
    }while(1);
}
void Min_heapify(Char_Rate cr[],int i)
{
    int l=2*i;
    int r=2*i+1;
    int minimum;
    if(l<=heap_size&&cr[l].rate<cr[i].rate)
    {
        minimum=l;
    }
    else
    {
        minimum=i;
    }
    if(r<=heap_size&&cr[r].rate<cr[minimum].rate)
    {
        minimum=r;
    }
    if(minimum!=i)
    {
        Char_Rate temp;
        temp=cr[i];
        cr[i]=cr[minimum];
        cr[minimum]=temp;
        Min_heapify(cr,minimum);
    }
}
void Build_heap(Char_Rate cr[])
{
    for(int i=heap_size;i>0;i--)
    {
        Min_heapify(cr,i);
    }
}
Char_Rate Heap_min(Char_Rate cr[])
{
    if(heap_size<1)
    {
        cout<<"error";
        exit(0);
    }
    Char_Rate min;
    min=cr[1];
    cr[1]=cr[heap_size];
    heap_size=heap_size-1;
    Min_heapify(cr,1);
    return min;
}
void Heap_increate(Char_Rate cr[],int i,Char_Rate key)
{
    if(key.rate>cr[i].rate)
    {
        cout<<"error!!";
        exit(0);
    }
    cr[i]=key;
    while(i>1&&cr[i/2].rate>cr[i].rate)
    {
        Char_Rate temp;
        temp=cr[i];
        cr[i]=cr[i/2];
        cr[i/2]=temp;
        i--;
    }
}
void Heap_insert(Char_Rate cr[],Char_Rate key)
{
    heap_size=heap_size+1;
    cr[heap_size].rate=1;
    Heap_increate(cr,heap_size,key);
}
void Ctreatehuffmantree(HTree &ht,Char_Rate cr[])
{
    while(heap_size!=0)
    {
        if(heap_size==1)
        {
            ht=Heap_min(cr).ht;
        }
        else
        {
            ht=new HuffmanTree;
            Char_Rate lcr=Heap_min(cr);
            Char_Rate rcr=Heap_min(cr);
            ht->lchild=lcr.ht;
            ht->rchild=rcr.ht;
            Char_Rate Key;
            Key.rate=lcr.rate+rcr.rate;
            Key.ht=ht;
            Heap_insert(cr,Key);
        }
    }
}
void CreateCode(HTree &ht,HuffmanCode hc[])
{
    if(ht!=NULL)
    {
        CODE[flag]=0;
        flag++;
        CreateCode(ht->lchild,hc);
        CODE[flag]=1;
        flag++;
        CreateCode(ht->rchild,hc);
        if(ht->lchild==NULL)
        {
            int t=0;
            hc[ht->ch].ch=ht->ch;
            for(t=0;t<=flag;t++)
            {
                hc[ht->ch].code[t]=CODE[t];
            }
            hc[ht->ch].code[t-1]=-1;
        }
    }
    flag--;
}
void CreateRate(Char_Rate cr[],char fname[])
{
    Char_Rate temp[128];
    for(int i=0;i<128;i++)
    {
        temp[i].ch=0;
        temp[i].rate=0;
    }
    fstream ftemp;
    ftemp.open(fname,ios::in);
    char ch;
    ch=ftemp.get();
    int n=1;
    while(!ftemp.eof())
    {
        temp[ch].ch=ch;
        temp[ch].rate=temp[ch].rate+1;
        n++;
        ch=ftemp.get();
    }
    ftemp.close();
    int num=1;
    for(int t=0;t<128;t++)
    {
        if(temp[t].ch!=0)
        {
            cr[num].ch=temp[t].ch;
            cout<<temp[t].ch<<": "<<temp[t].rate<<endl;
            cr[num].rate=(float)temp[t].rate/n;
            num++;
        }
    }
    heap_size=num-1;
}
void Encoded(HuffmanCode hc[],char fname[])
{
    fstream ftemp;
    ftemp.open(fname,ios::in);
    char ch;
    ch=ftemp.get();
    bool code[2000000];
    int flag=0;
    while(!ftemp.eof())
    {
        int t=0;
        while(hc[ch].code[t]!=-1)
        {
            code[flag]=(int)hc[ch].code[t];
            flag++;
            t++;
        }
        ch=ftemp.get();
    }
    ftemp.close();
    ofstream oFile("code");
    if(oFile.fail())
    throw("文件打开失败！");
    oFile.close();
    int n=0;
    for(int i=0;i<128;i++)
    {
        if(hc[i].ch!=0)
        n++;
    }
    HuffmanCode short_hc[n];
    int t=0;
    for(int j=0;j<128;j++)
    {
        if(hc[j].ch!=0)
        {
            short_hc[t]=hc[j];
            t++;
        }
    }
    int size=sizeof(short_hc);
    bitset<8> bit;//使用C++自带的位操作类
    fstream file;
    file.open("code",ios::in|ios::out|ios::binary);
    file.seekg(0);
    file.write((char*)&size,sizeof(size));
    file.write((char*)&short_hc,sizeof(short_hc));//将编码表也存储在文件中，用于解码的时候使用
    file.write((char*)&flag,sizeof(flag));
    for(int n=0;n<flag;n++)
    {
        bit[n%8]=code[n];//对每一个位进行操作，使得编码后生成的文件比原文件小
        if(n%8==7)
        {
            file.write((char*)&bit,sizeof(char));
        }
    }
    file.write((char*)&bit,sizeof(char));
    cout<<endl<<"已输出编码后的文件code！"<<endl;
    file.close();
}
void Decode()
{
    int flag;
    int size;
    cout<<"请输入要解码的文件名称（eg：code）：";
    char fname[30];
    cin>>fname;
    fstream file;
    file.open(fname,ios::in|ios::out|ios::binary);
    if(!file)
    {
        cout<<"文件不存在！"<<endl;
        file.close();
    }
    else
    {
        file.seekg(0);
        file.read((char*)&size,sizeof(size));
        int n=size/sizeof(HuffmanCode);
        HuffmanCode hc[n];
        file.read((char*)&hc,size);
        file.read((char*)&flag,sizeof(flag));
        bitset<8> bit;
        bool code[2000000];
        for(int n=0;n<flag;n++)
        {
            if(n%8==0)
            {
                file.read((char*)&bit,sizeof(char));
            }
            code[n]=bit[n%8];
        }
        file.close();
        system("cls");
        cout<<"解码后的文件内容："<<endl;
        Outchar(code,hc,0,flag-1);
    }
}
void Outchar(bool code[],HuffmanCode hc[],int start,int end)
{
    if(start<end)
    {
        for(int i=0;;i++)
        {
            int j=0;
            for(j=0;hc[i].code[j]!=-1;j++)
            {
                if(hc[i].code[j]!=code[start+j])
                break;
            }
            if(hc[i].code[j]==-1)
            {
                cout<<hc[i].ch;
                Outchar(code,hc,start+j,end);
                break;
            }
        }
    }
}
