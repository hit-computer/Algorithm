#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <Queue>
#include <windows.h>
#include <WinBase.h>
#include <fstream>
using namespace std;
void BubbleSort(int D[],int n);
void InsertSort(int D[],int n);
void ShellSort(int D[],int n);
void SelectSort(int D[],int n);
void QuickSort(int D[],int i,int j);
int Partition(int D[],int i,int j,int pivot);
void MERGE(int ar[],int p,int q,int r);
void MergeSort(int arr[],int p,int r);
void HeapSort(int D[],int n);
void Min_heapify(int cr[],int i);//保持最小堆特性
void Build_heap(int cr[]);//建立最小堆
int Heap_min(int cr[]);//返回最小元素
int heap_size;//堆的大小
void RadixSort(int D[],int n,int figure);
int Radix(int k,int p);
void Random(int D[],int n);
int main()
{
    //cout<<"请输入数据量：";
    //int n;
    //cin>>n;
    int n=50000;
    int Data[n];
    int Data1[n];
    int Data2[n];
    int Data3[n];
    int Data4[n];
    int Data5[n];
    int Data6[n];
    int Data7[n];
    ifstream work("Data.txt");
    for(int t=0;t<n;t++)
    {
        work>>Data[t];
        Data1[t]=Data[t];
        Data2[t]=Data[t];
        Data3[t]=Data[t];
        Data4[t]=Data[t];
        Data5[t]=Data[t];
        Data6[t]=Data[t];
        Data7[t]=Data[t];
    }
    work.close();
    //Random(Data,n);

    DWORD st;
    st=GetTickCount();
    BubbleSort(Data,n);
    cout<<"冒泡排序时间为："<<GetTickCount()-st<<" ms"<<endl;
    cout<<endl;

    st=GetTickCount();
    InsertSort(Data1,n);
    cout<<"插入排序时间为："<<GetTickCount()-st<<" ms"<<endl;
    cout<<endl;

    st=GetTickCount();
    ShellSort(Data2,n);
    cout<<"希尔排序时间为："<<GetTickCount()-st<<" ms"<<endl;
    cout<<endl;
    /*for(int i=0;i<n;i++)
    {
        cout<<Data2[i]<<"   ";
    }*/

    st=GetTickCount();
    SelectSort(Data3,n);
    cout<<"选择排序时间为："<<GetTickCount()-st<<" ms"<<endl;
    cout<<endl;

    st=GetTickCount();
    QuickSort(Data4,0,n-1);
    cout<<"快速排序时间为："<<GetTickCount()-st<<" ms"<<endl;
    cout<<endl;

    st=GetTickCount();
    MergeSort(Data5,0,n-1);
    cout<<"归并排序时间为："<<GetTickCount()-st<<" ms"<<endl;
    cout<<endl;

    st=GetTickCount();
    HeapSort(Data6,n);
    cout<<"堆排序时间为："<<GetTickCount()-st<<" ms"<<endl;
    cout<<endl;

    st=GetTickCount();
    RadixSort(Data7,n,7);
    cout<<"基数序时间为："<<GetTickCount()-st<<" ms"<<endl;
    cout<<endl;
    return 0;
}
void Random(int D[],int n)
{
    srand(time(NULL));
    for(int i=0;i<n;i++)
    {
        D[i]=rand();
    }
}
void BubbleSort(int D[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=n-1;j>i;j--)
        {
            if(D[j]<D[j-1])
            {
                int temp=D[j];
                D[j]=D[j-1];
                D[j-1]=temp;
            }
        }
    }
}
void InsertSort(int D[],int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        j=i;
        while(j>0&&D[j]<D[j-1])
        {
            int temp=D[j];
            D[j]=D[j-1];
            D[j-1]=temp;
            j=j-1;
        }
    }
}
void ShellSort(int D[],int n)
{
    int d, i, j, temp;
    for(d=n/2;d>=1;d=d/2)
    {
        for(i=d;i<n;i++)
        {
            temp = D[i];
            for(j=i-d;(j>=0) && (D[j]>temp);j=j-d)
            {
                D[j+d] = D[j];
            }
            D[j+d] = temp;
        }
    }
}
void SelectSort(int D[],int n)
{
    int lowkey;
    int lowindex;
    for(int i=0;i<n;i++)
    {
        lowindex=i;
        lowkey=D[i];
        int j;
        for(j=i;j<n;j++)
        {
            if(D[j]<lowkey)
            {
                lowkey=D[j];
                lowindex=j;
            }
        }
        int temp=D[lowindex];
        D[lowindex]=D[i];
        D[i]=temp;
    }
}
void QuickSort(int D[],int i,int j)
{
    int pivot;
    int pivotindex;
    int k;
    pivotindex=i;
    if(pivotindex!=0)
    {
        pivot=D[pivotindex];
        k=Partition(D,i,j,pivot);
        QuickSort(D,i,k-1);
        QuickSort(D,k,j);
    }
}
int Partition(int D[],int i,int j,int pivot)
{
    int l,r;
    l=i;
    r=j;
    do
    {
        int temp=D[r];
        D[r]=D[l];
        D[l]=temp;
        while(D[l]<pivot)
        l++;
        while(D[r]>=pivot)
        r--;
    }while(l<=r);
    return l;
}
void MergeSort(int arr[],int p,int r)
{
    if(p<r)
    {
        int q=(p+r)/2;
        MergeSort(arr,p,q);
        MergeSort(arr,q+1,r);
        MERGE(arr,p,q,r);
    }
}
void MERGE(int ar[],int p,int q,int r)
{
    int i,j;
    i=q-p+1;
    j=r-q;
    int L[i];
    int R[j];
    for(int t=0;t<i;t++)
    {
        L[t]=ar[p+t];
    }
    for(int t=0;t<j;t++)
    {
        R[t]=ar[q+1+t];
    }
    int a,b;
    a=b=0;
    for(int t=p;t<r+1;t++)
    {
        if(a<i&&((b>j-1)||L[a]<R[b]))
        {
            ar[t]=L[a];
            a++;
        }
        else
        {
            ar[t]=R[b];
            b++;
        }
    }
}
void HeapSort(int D[],int n)
{
    heap_size=n-1;
    int Data[n+10];//申请一个稍微大一点的内存空间
    for(int i=0;i<n;i++)
    {
        Data[i]=D[i];
    }
    Build_heap(Data);
    for(int i=0;i<n;i++)
    {
        D[i]=Heap_min(Data);
    }
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
void RadixSort(int D[],int n,int figure)
{
    queue<int> Q[10];
    int data;
    int pass,r,i;
    int t=0;
    for(pass=1;pass<=figure;pass++)
    {
        for(int t=0;t<n;t++)
        {
            data=D[t];
            r=Radix(data,pass);
            Q[r].push(data);
        }
        for(i=0;i<=9;i++)
        {
            while(!Q[i].empty())
            {
                D[t]=Q[i].front();
                Q[i].pop();
            }
        }
    }
}
int Radix(int k,int p)
{
    int power,i;
    power=1;
    for(i=1;i<=p-1;i++)
    power=power*10;
    return ((k%power*10)/power);
}
