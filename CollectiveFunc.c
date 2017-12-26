//
//  CollectiveFunc.c
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
void  msort(char str1[],char str2[],int len1,int len2,char *str3);
int compare(void const *a, void const *b );
int main(int argc, char * argv[])
{
    int npes,myrank;
    int n;
    n = atoi(argv[1]);//Converting argument values into interger
    //printf("argv %d \n",n);
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&npes);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    MPI_Status status;
    char input[n];
    srand(time(NULL));
    for(int i=0;i<n;i++)
    {
        input[i]=rand() %(90 - 65 + 1) + 65;
    }
    //Display the input stirng
    /*for(int i=0;i<n;i++)
     {
     printf("%c", input[i]);
     }*/
    printf("\n");
    int sn = n/npes;
    int extra;
    if(n%npes > 0) //If it is not dividing equally, increasing the string size
        sn=sn+1;
    char rcvbuf[n],rcv[n],s1[n],s3[n],s2[n],s4[n],s5[n],s6[n],sf[n];
    // Clearing strings by assigning NULL
    memset(s1,'\0',sizeof(s1));
    memset(s2,'\0',sizeof(s2));
    memset(s3,'\0',sizeof(s3));
    memset(s5,'\0',sizeof(s5));
    MPI_Scatter(input, sn, MPI_CHAR, rcvbuf, sn, MPI_CHAR, 0, MPI_COMM_WORLD); //Scatter function
    qsort(rcvbuf, strlen(rcvbuf), sizeof(char), compare);
    printf("Main: %s  -> RANK: %d \t Sorted substring: %s\n",input,myrank,rcvbuf);
    MPI_Gather(rcvbuf, sn, MPI_CHAR, rcv, sn, MPI_CHAR, 0,MPI_COMM_WORLD ); //Gather function
    if(myrank == 0)
    {
        //Spliting up the recieve buffer into substrings
        strncpy(s1,rcv,sn);
        strncpy(s2,rcv+sn,sn);
        strncpy(s3,rcv+(2*sn),(sn));
        strncpy(s5,rcv+(3*sn),(n-(3*sn)));
        printf("%s -> %s -> %s -> %s\n",s1,s2,s3,s5);
        msort(s1,s2,(strlen(s1)),(strlen(s2)),s4); // calling sort function for string1 and string2
        //printf("\nSorted string from s1 & s2 is:\n%s\n",s4);
        msort(s4,s3,(strlen(s4)),(strlen(s3)),sf); // calling sort function for string3 and output from first
        msort(sf,s5,(strlen(sf)),(strlen(s5)),s6);
        printf("\nFinal Sorted string is:%s\n",s6); //Displaying the final string
    }
    printf("\n\t\t******  From process %d out of %d ******\n",myrank,npes);
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
