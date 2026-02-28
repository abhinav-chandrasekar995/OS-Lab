#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n;
    printf("Enter the number of elements in the array: \n");
    scanf("%d",&n);
    int arr[n];
    int position=-1;
    printf("Enter %d elements in the array: \n",n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    int smallest=arr[0];
    for(int i=0;i<n;i++)
    {
        if(arr[i]<smallest)
        {
        smallest=arr[i];
        position=i+1;
        }
    }
    printf("The smallest element is %d and its position is %d",smallest,position);
}
