#include <stdio.h>

int main(void)
{
int arr[] = {10, 20};
int *p = arr;
++*p;
printf("arr[0] = %d, arr[1] = %d, *p = %d",
arr[0], arr[1], *p);
printf("2 power : %d", (1 << 3));
return 0;
}