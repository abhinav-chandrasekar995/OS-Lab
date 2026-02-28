#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n;
    printf("Enter the number of elements in the array: \n");
    scanf("%d",&n);
    int arr[n];
    int duplicate=0;
    printf("Enter %d elements in the array: \n",n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(arr[i]==arr[j])
            {
            duplicate=1;
            break;
            }
            else
            {
                continue;
            }
        }
    }
    if(duplicate==1)
    {
        printf("Duplicates are present in the array! \n");
    }
    else{
        printf("Duplicates are not present \n");
    }
}

