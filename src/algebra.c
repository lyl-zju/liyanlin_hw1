#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

// 矩阵加法
Matrix add_matrix(Matrix a, Matrix b)
{
    if (a.rows!=b.rows || a.cols!=b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    else
    {
        Matrix c;
        c.rows=a.rows;
        c.cols=a.cols;
        int i,j;
        for (i=0;i<c.rows;i++)
        {
            for(j=0;j<c.cols;j++)
            {
                c.data[i][j]=a.data[i][j]+b.data[i][j];
            }
        }
        return c;
    }
    
}

// 矩阵减法
Matrix sub_matrix(Matrix a, Matrix b)
{
    if (a.rows!=b.rows || a.cols!=b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    else
    {
        Matrix c;
        c.rows=a.rows;
        c.cols=a.cols;
        for (int i=0;i<c.rows;i++)
        {
            for(int j=0;j<c.cols;j++)
            {
                c.data[i][j]=a.data[i][j]-b.data[i][j];
            }
        }
        return c;
    }
}

//矩阵乘法
Matrix mul_matrix(Matrix a, Matrix b)
{
    if (a.cols!=b.rows)
    {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0);
    }
    else
    {
        Matrix c;
        c.rows=a.rows;
        c.cols=b.cols;
        for (int i=0;i<c.rows;i++)
        {
            for(int j=0;j<c.cols;j++)
            {
                double temp=0;
                for(int k=0;k<a.cols;k++)
                {
                    temp+=a.data[i][k]*b.data[k][j];
                }
                c.data[i][j]=temp;
            }
        }
    return c;   
    } 
}

// 矩阵数乘
Matrix scale_matrix(Matrix a, double k)
{
    Matrix c;
    c.rows=a.rows;
    c.cols=a.cols;
    for (int i=0;i<c.rows;i++)
    {
        for(int j=0;j<c.cols;j++)
        {
            c.data[i][j]=k*a.data[i][j];
        }
    }
    return c;
}

//矩阵转置
Matrix transpose_matrix(Matrix a)
{
    Matrix c;
    c.rows=a.cols;
    c.cols=a.rows;
    for (int i=0;i<c.rows;i++)
    {
        for(int j=0;j<c.cols;j++)
        {
            c.data[i][j]=a.data[j][i];
        }
    }
    return c;
}

//矩阵的行列式
double det_matrix(Matrix a)
{
    if(a.cols!=a.rows)
    {
        printf("The matrix must be a square matrix.\n");
        return 0;
    }
    
    //迭代终点
    if(a.cols==1)
        return(a.data[0][0]);
    if(a.cols==2)
        return(a.data[0][0]*a.data[1][1]-a.data[0][1]*a.data[1][0]);

    //沿第一列展开
    double result=0;
    int flag=1;
    for(int k=0;k<a.rows;k++)
    {
        //获取a_k1对应的子矩阵
        Matrix sub_a;
        sub_a.rows=a.rows-1;
        sub_a.cols=a.cols-1;
        for(int i=0,temp=0;i<sub_a.rows;i++,temp++)
        {
            if(temp==k)
                temp++;
            for(int j=0;j<sub_a.cols;j++)
            {
                sub_a.data[i][j]=a.data[temp][j+1];
            }
        }
        result+=flag*a.data[k][0]*det_matrix(sub_a);
        flag*=-1;
    }
    return result;


}

//矩阵求逆
Matrix inv_matrix(Matrix a)
{
    if(a.rows!=a.cols || det_matrix(a)==0)
    {
        printf("The matrix must be a square matrix.\n");
        return create_matrix(0, 0);
    }
    //求解矩阵a的伴随矩阵A
    Matrix A;
    A.cols=a.cols;
    A.rows=a.rows;

    for(int i=0;i<A.rows;i++)
    {
        for(int j=0;j<A.cols;j++)
        {
            //对于伴随矩阵中的每一个元素，先生成对应的子矩阵，再计算行列式
            Matrix sub_a;
            sub_a.rows=a.rows-1;
            sub_a.cols=a.cols-1;
            for(int m1=0,m2=0;m1<a.rows;m1++)
            {
            if(m1==i)
                continue;
                for(int n1=0,n2=0;n1<a.cols;n1++)
                {
                if(n1==j)
                continue;
                sub_a.data[m2][n2]=a.data[m1][n1];
                n2++;
                }
                m2++;
            }
            int sign=((i+j)%2==0)?1:-1;
            A.data[j][i]=sign*det_matrix(sub_a);
        }   
    }
    return(scale_matrix(A, 1/det_matrix(a)));
  
}

//矩阵求秩
int rank_matrix(Matrix a)
{
    int rank = 0;
    int rows = a.rows;
    int cols = a.cols;
    
    for (int i = 0, j = 0; i < rows && j < cols; j++) {
        // 寻找当前列中第一个非零元素的行
        int pivot = -1;
        for (int k = i; k < rows; k++) {
            if (fabs(a.data[k][j]) > 1e-10) { // 考虑浮点误差
                pivot = k;
                break;
            }
        }
        
        if (pivot == -1) {
            continue; // 当前列全零，处理下一列
        }
        
        // 交换当前行与主元行
        if (pivot != i) {
            for (int k = j; k < cols; k++) {
                double temp = a.data[i][k];
                a.data[i][k] = a.data[pivot][k];
                a.data[pivot][k] = temp;
            }
        }
        
        // 高斯消元：将当前列下方元素清零
        for (int k = i + 1; k < rows; k++) {
            double factor = a.data[k][j] / a.data[i][j];
            for (int l = j; l < cols; l++) {
                a.data[k][l] -= factor * a.data[i][l];
            }
        }
        
        rank++;
        i++; // 移动到下一行
    }
    
    return rank;
}

//矩阵的迹
double trace_matrix(Matrix a)
{
    if(a.cols!=a.rows)
    {
        printf("The matrix must be a square matrix.\n");
        return 0;
    }

    double trace=0;
    for(int i=0;i<a.cols;i++)
    {
        trace+=a.data[i][i];
    }
    return trace;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}