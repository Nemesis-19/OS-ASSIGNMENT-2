#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

#define __NR_kernel_2d_memcpy 448

int main()
{
    int row=10, col=10, num=0;

    float** arr1=(float**)malloc(row*sizeof(float*));

    for (int i=0; i<row; i=i+1)
    {
        arr1[i] = (float*)malloc(col * sizeof(float));
    }

    float** arr2=(float**)malloc(row*sizeof(float*));

    for (int i=0; i<row; i=i+1)
    {
        arr2[i] = (float*)malloc(col * sizeof(float));
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            num=num+5;

            arr1[i][j]=num;
        }
    }

    long tmp = 5;

    tmp = syscall(__NR_kernel_2d_memcpy, arr2, arr1, row,col);

    printf("Output of Array 1: \n");

    for (int i=0; i<row; i=i+1)
    {
        for (int j=0; j<col; j=j+1)
        {
            printf("%.2f ",arr1[i][j]);
        }

        printf("\n");
    }

    printf("\nOutput of Array 2: \n");

    for (int i=0; i<row; i=i+1)
    {
        for (int j=0; j<col; j=j+1)
        {
            printf("%.2f ",arr2[i][j]);
        }

        printf("\n");
    }

    return 0;
}