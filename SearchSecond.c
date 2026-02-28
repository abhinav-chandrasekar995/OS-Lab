#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n;
    printf("Enter the number of elements in the array: \n");
    scanf("%d",&n);
    int arr[n];
    printf("Enter %d elements in the array: \n",n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    int search;
    printf("Enter the search element: \n");
    scanf("%d",&search);
    printf("Performing binary search: \n");
    int position=-1;
    int low=0;
    int high=n-1;
    int mid=0;
    while(low<=high)
    {
        mid=(low+high)/2;
        if(arr[mid]<search)
        {
            low=mid+1;
        }
        else if(arr[mid]>search)
        {
            high=mid-1;
        }
        else if(arr[mid]==search)
        {
            position=mid+1;
            printf("Element %d was found at position %d \n",search,position);
            break;
        }
        else{
            continue;
        }
    }
    if(position==-1)
    {
        printf("element not present \n");
    }
    else{
        printf("binary search successful! ");
    }
}

