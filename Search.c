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
    printf("Performing linear search: \n");
    int position=-1;
    for(int i=0;i<n;i++)
    {
        if(arr[i]==search)
        {
            position=(i+1);
            printf("%d found in position %d \n",search,position);
        }
        else{
            continue;
        }
    }
    if(position==-1)
    {
        printf("%d was not found in the array \n",search);
    }
    else
    {
        printf("Linear search completed! \n");
    }
}
