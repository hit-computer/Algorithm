#include <iostream>
using namespace std;

struct node
{
    int i;//非零元素的行号
    int j;//非零元素的列号
    int e;//非零元素的值
};

int main()
{
    cout<<"矩阵的行数：";
    int row;
    cin>>row;
    cout<<"矩阵的列数：";
    int rank;
    cin>>rank;
    cout<<"矩阵非零元素的个数：";
    int number;
    cin>>number;
    node matrix[number];
    for(int i=0;i<number;i++)
    {
        cout<<"请输入矩阵非零元素的行号，列号，以及数值：";
        cin>>matrix[i].i>>matrix[i].j>>matrix[i].e;
    }

    /*******以下代码是矩阵转置的优化算法*******/

    node result_matrix[number];
    int list[rank];
    int position[rank];
    for(int i=0;i<rank;i++)
    {
        list[i]=position[i]=0;//两个数组的值清零
    }
    for(int i=0;i<number;i++)
    {
        list[matrix[i].j-1]++;//统计每一列非零元素的个数
    }
    for(int i=1;i<rank;i++)
    {
        position[i]=position[i-1]+list[i-1];//每一列第一个非零元素在新的矩阵的三元组中的序号
    }
    for(int i=0;i<number;i++)
    {
        int t=matrix[i].j-1;
        int n=position[t];
        result_matrix[n].i=matrix[i].j;
        result_matrix[n].j=matrix[i].i;
        result_matrix[n].e=matrix[i].e;
        position[t]++;
    }

    /**********以下是转置后的矩阵输出**********/

    int out[rank][row];//定义一个输出矩阵
    for(int i=0;i<rank;i++)
    {
        for(int j=0;j<row;j++)
        out[i][j]=0;//数据清零
    }
    for(int t=0;t<number;t++)
    {
        out[result_matrix[t].i-1][result_matrix[t].j-1]=result_matrix[t].e;
    }
    cout<<"转置后的矩阵："<<endl;
    for(int i=0;i<rank;i++)
    {
        for(int j=0;j<row;j++)
        {
            cout<<out[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
