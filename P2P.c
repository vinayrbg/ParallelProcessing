//
//  P2P.c
//  SearchAlgorithm
//
//  Created by Vinay Raju on 11/15/17.
//  Copyright © 2017 Vinay Raju. All rights reserved.
//
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<mpi.h>
void  msort(char str1[],char str2[],int len1,int len2,char *str3)
{
    int i = 0, j = 0, k = 0;
    while (i<len1 && j <len2)
    {
        if (str1[i] < str2[j])
            str3[k++] = str1[i++];
        else
            str3[k++] = str2[j++];
    }
    while (i < len1)
        str3[k++] = str1[i++];
    while (j < len2)
        str3[k++] = str2[j++];
    str3[k] = '\0';
}
int ascending(void const *a, void const *b )
{
    return (*(char*)a - *(char*)b );
}
int main(int argc, char *argv[])
{
    int npes,myrank;
    int n;
    n = atoi(argv[1]);
    printf("argv %d \n",n);
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&npes);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    MPI_Status status;
    char a[n];
    srand(time(NULL));
    for(int i=0;i<n;i++)
    {
        a[i]=rand() %(90 - 65 + 1) + 65;
    }
    for(int i=0;i<n;i++)
    {
        printf("%c", a[i]);
    }
    printf("\n");
    int sn = n/3;
    char s1[n],s2[n],s3[n],s4[n],sf[n];
    if(myrank == 0)
    {
        printf("Rank 0 : %s\n",a);
        MPI_Send(a,sn,MPI_CHAR,1,2,MPI_COMM_WORLD);
        MPI_Send(a+sn,sn,MPI_CHAR,2,22,MPI_COMM_WORLD);
        MPI_Send(a+(2*sn),n-(2*sn),MPI_CHAR,3,33,MPI_COMM_WORLD);
        MPI_Recv(s1,sn,MPI_CHAR,1,2,MPI_COMM_WORLD,&status);
        MPI_Recv(s2,sn,MPI_CHAR,2,22,MPI_COMM_WORLD,&status);
        MPI_Recv(s3,n-(2*sn),MPI_CHAR,3,33,MPI_COMM_WORLD,&status);
        printf("Rank 0 :Sort s1:%s\n",s1);
        printf("Rank 0 :Sort s2:%s\n",s2);
        printf("Rank 0 :Sort s3:%s\n",s3);
        msort(s1,s2,(strlen(s1)),(strlen(s2)),s4);
        printf("\nSorted string from s1 & s2 is:\n%s\n",s4);
        msort(s4,s3,(strlen(s4)),(strlen(s3)),sf);
        printf("\nFinal Sorted string is:\n%s\n",sf);
    }
    else if(myrank == 1)
    {
        MPI_Recv(s1,sn,MPI_CHAR,0,2,MPI_COMM_WORLD,&status);
        printf("Rank 1 : %s\n",s1);
        qsort(s1, sn, sizeof(char), ascending);
        printf("Rank 1 :Sort :%s\n",s1);
        MPI_Send(s1,sn,MPI_CHAR,0,2,MPI_COMM_WORLD);
    }
    else if(myrank == 2)
    {
        MPI_Recv(s2,sn,MPI_CHAR,0,22,MPI_COMM_WORLD,&status);
        printf("Rank 2 : %s\n",s2);
        qsort(s2, sn, sizeof(char), ascending);
        printf("Rank 2 :Sort :%s\n",s2);
        MPI_Send(s2,sn,MPI_CHAR,0,22,MPI_COMM_WORLD);
    }
    else if(myrank == 3)
    {
        MPI_Recv(s3,(n-(2*sn)),MPI_CHAR,0,33,MPI_COMM_WORLD,&status);
        printf("Rank 3 : %s\n",s3);
        qsort(s3,(n-(2*sn)), sizeof(char), ascending);
        printf("Rank 3 :Sort :%s\n",s3);
        MPI_Send(s3,(n-(2*sn)),MPI_CHAR,0,33,MPI_COMM_WORLD);
    }
    printf("\nFrom process %d out of %d, Hello World\n",myrank,npes);
    MPI_Finalize();
    return 0;
}

p2p latest

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<mpi.h>
void  msort(char str1[],char str2[],int len1,int len2,char *str3);
int compare(void const *a, void const *b );
int main(int argc, char * argv[])
{
    int npes,myrank;
    int n;
    n = atoi(argv[1]);
    char a[n];
    srand(time(NULL));
    int sn = n/3;
    char s1[n],s2[n],s3[n],s4[n],sf[n];
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&npes);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    MPI_Status status;
    if(myrank == 0)
    {
        for(int i=0;i<n;i++)
        {
            a[i]=rand() %(90 - 65 + 1) + 65;
        }
        printf("Input string is: ");
        for(int i=0;i<n;i++)
        {
            printf("%c", a[i]);
        }
        printf("\n");
        //printf("Rank 0 : %s\n",a);
        MPI_Send(a,sn,MPI_CHAR,1,2,MPI_COMM_WORLD); //Sending to rank 1
        MPI_Send(a+sn,sn,MPI_CHAR,2,22,MPI_COMM_WORLD); //Sending to rank 2
        MPI_Send(a+(2*sn),n-(2*sn),MPI_CHAR,3,33,MPI_COMM_WORLD); //Sending to rank 3
        MPI_Recv(s1,sn,MPI_CHAR,1,2,MPI_COMM_WORLD,&status);//Receive from rank 1
        MPI_Recv(s2,sn,MPI_CHAR,2,22,MPI_COMM_WORLD,&status);//Receive from rank 2
        MPI_Recv(s3,n-(2*sn),MPI_CHAR,3,33,MPI_COMM_WORLD,&status);///Receive from rank 3
        printf("Rank 0 :Sort Sub-string1 :%s\n",s1);
        printf("Rank 0 :Sort Sub-string2 :%s\n",s2);
        printf("Rank 0 :Sort Sub-string3 :%s\n",s3);
        msort(s1,s2,(strlen(s1)),(strlen(s2)),s4);
        //printf("\nSorted string from s1 & s2 is:\n%s\n",s4);
        msort(s4,s3,(strlen(s4)),(strlen(s3)),sf);
        printf("\nFinal Sorted string :\n%s\n",sf);
    }
    else if(myrank == 1)
    {
        MPI_Recv(s1,sn,MPI_CHAR,0,2,MPI_COMM_WORLD,&status);
        printf("Rank 1 : %s\n",s1);
        qsort(s1, sn, sizeof(char), compare);
        printf("Rank 1 :Sort :%s\n",s1);
        MPI_Send(s1,sn,MPI_CHAR,0,2,MPI_COMM_WORLD);
    }
    else if(myrank == 2)
    {
        MPI_Recv(s2,sn,MPI_CHAR,0,22,MPI_COMM_WORLD,&status);
        printf("Rank 2 : %s\n",s2);
        qsort(s2, sn, sizeof(char), compare);
        printf("Rank 2 :Sort :%s\n",s2);
        MPI_Send(s2,sn,MPI_CHAR,0,22,MPI_COMM_WORLD);
    }
    else if(myrank == 3)
    {
        MPI_Recv(s3,(n-(2*sn)),MPI_CHAR,0,33,MPI_COMM_WORLD,&status);
        printf("Rank 3 : %s\n",s3);
        qsort(s3,(n-(2*sn)), sizeof(char), compare);
        printf("Rank 3 :Sort :%s\n",s3);
        MPI_Send(s3,(n-(2*sn)),MPI_CHAR,0,33,MPI_COMM_WORLD);
    }
    printf("\nFrom process %d out of %d, Hello World\n",myrank,npes);
    MPI_Finalize();
    return 0;
}
void  msort(char str1[],char str2[],int len1,int len2,char *str3)
{
    int i = 0, j = 0, k = 0;
    while (i<len1 && j <len2)
    {
        if (str1[i] < str2[j])
            str3[k++] = str1[i++];
        else
            str3[k++] = str2[j++];
    }
    while (i < len1)
        str3[k++] = str1[i++];
    while (j < len2)
        str3[k++] = str2[j++];
    str3[k] = '\0';
}
int compare(void const *a, void const *b )
{
    return (*(char*)a - *(char*)b );
}

