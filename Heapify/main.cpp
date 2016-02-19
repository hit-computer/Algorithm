
/******本程序实现用堆排序算法排序int型数据******/
#include <iostream>
#include <stdlib.h>
using namespace std;

void Min_heapify(int cr[],int i);//保持最小堆特性
void Build_heap(int cr[]);//建立最小堆
int Heap_min(int cr[]);//返回最小元素
void Heap_insert(int cr[],int key);//最小堆插入元素
int heap_size;//堆的大小
int main()
{
    cout << "输入元素的个数：" ;
    int n;
    cin>>n;
    heap_size=n-1;
    int Data[n+10];//申请一个稍微大一点的内存空间
    cout<<"请输入每一个数据："<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>Data[i];
    }
    Build_heap(Data);
    int result[n];
    for(int i=0;i<n;i++)
    {
        result[i]=Heap_min(Data);
    }
    cout<<"堆排序的结果为："<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<result[i]<<" ";
    }
    return 0;
}

void Min_heapify(int cr[],int i)
{
    int l=2*i;
    int r=2*i+1;
    int min;
    if(l<=heap_size&&cr[l]<cr[i])
        min=l;
    else
        min=i;
    if(r<=heap_size&&cr[r]<cr[min])
        min=r;
    if(min!=i)
    {
        int temp=cr[i];
        cr[i]=cr[min];
        cr[min]=temp;
        Min_heapify(cr,min);
    }

}
void Build_heap(int cr[])
{
    int t=heap_size;
    for(int i=t/2;i>=0;i--)
    {
        Min_heapify(cr,i);
    }
}
int Heap_min(int cr[])
{
    if(heap_size<0)
        exit(0);
    int min=cr[0];
    cr[0]=cr[heap_size];
    heap_size--;
    Min_heapify(cr,0);
    return min;
}
void Heap_insert(int cr[],int key)
{
    heap_size++;
    cr[heap_size]=key;
    int i=heap_size;
    while(i>0&&cr[i/2]>cr[i])
    {
        int temp=cr[i/2];
        cr[i/2]=cr[i];
        cr[i]=temp;
        i=i/2;
    }
}
