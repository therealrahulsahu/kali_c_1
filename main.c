#include <stdio.h>
#include <stdlib.h>
int main()
{
    //int *arr=(int * )malloc(5* sizeof(int));
    int arr[5];
    for (int i = 0; i < 5; ++i) {
        arr[i]=0;
    }
    printf("%d\n", sizeof(arr));
}