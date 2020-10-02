#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void swap(int *a,int *b)
{
    int tmp;
    tmp=(*a);(*a)=(*b);(*b)=tmp;
}

void print(int array[],int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%3d ",array[i]);
    printf("\n");
}

void selection(int array[],int n)
{
    //pick min over the unsorted array and concatenate it to the back of sorted array(the concatenating place's num will be send to min's original place)
    printf("selection sort:\n");
    
    int sorted,unsorted,i,min_i,totalstep;
    totalstep=0;
    //sorted means sorted array's back,unsorted means unsorted array's front
    for(unsorted=0,sorted=-1;sorted<n-1;sorted++,unsorted++)
    {
        //pick min over the unsorted array
        min_i=unsorted;
        for(i=unsorted;i<n;i++)
            if(array[i]<array[min_i])
                min_i=i;
        //concatenate it to the back of sorted array(the concatenating place's num will be send to min's original place)
        swap(&array[min_i],&array[sorted+1]);
        totalstep++;
        print(array,n);
    }
    printf("Total step: %d\n",totalstep);
}

void bubble(int array[],int n)
{
    //compare two num in order and swap them if necessary
    printf("bubble sort:\n");
    
    int j,i,sorted,totalstep;
    totalstep=0;sorted=n-1;
    //sorted means the sorted front in the back of array
    while(sorted>0)
    {
        for(i=0,j=1;j<n;i++,j++)
        {
            if(array[i]>array[j])
                swap(&array[i],&array[j]);
        }
        print(array,n);
        totalstep++;sorted--;
    }
    printf("Total step: %d\n",totalstep);
}

void insertion(int array[],int n)
{
    //pick the first data in the unsorted array and insert it to the right place in the sorted array
    printf("insertion sort:\n");
    
    int i,sorted,unsorted,totalstep;
    totalstep=0;
    for(sorted=-1,unsorted=0;sorted<n-1;sorted++,unsorted++)
    {
        //insert the first data in the unsorted array to the right place in the sorted array
        for(i=sorted;i>=0;i--)
            if(array[unsorted]<array[i])
            {
                swap(&array[unsorted],&array[i]);
                unsorted=i;
            }
        unsorted=sorted+1;
        print(array,n);
        totalstep++;
    }
    printf("Total step: %d\n",totalstep);
}

void quick(int array[],int n,int L,int R)
{
    int l,r,pivot;
    pivot=L;
    //printf("L=%d,R=%d\n",L,R);
    if(L<R)
    {
        l=L+1;//or l=L , l will stop at pivot
        r=R;
        while(1)
        {
            for(;array[l]<array[pivot];l++);//stop at a[l]>a[pivot],which is not okay
            for(;array[r]>array[pivot];r--);//stop at a[r]<a[pivot],which is not okay
            if(l<r) swap(&array[l],&array[r]);
            else break;
        }
        swap(&array[r],&array[pivot]);//r will stop at a[r]<a[pivot],l will stop at a[l]>a[pivot],so pick a[r] to make sure small,pivot,large
        print(array,n);
        quick(array,n,L,r-1);//now array[r]==array[pivot]
        quick(array,n,r+1,R);
    }
}

int main()
{
    FILE *fin;
    fin=fopen("test.txt","r");
    
    int array[10001],tmp[10001],n,i;
    
    //read file
    n=0;
    while(fscanf(fin,"%d",&array[n])!=EOF)
        n++;
    printf("Input array:\n");
    print(array,n);
    printf("\n");
    
    for(i=0;i<n;i++) tmp[i]=array[i];
    //implementing 4 algorithm
    selection(tmp,n);printf("\n");for(i=0;i<n;i++) tmp[i]=array[i];
    bubble(tmp,n);printf("\n");for(i=0;i<n;i++) tmp[i]=array[i];
    insertion(tmp,n);printf("\n");for(i=0;i<n;i++) tmp[i]=array[i];
    
    printf("quick sort:\n");quick(tmp,n,0,n-1);
    fclose(fin);
    return 0;
}
