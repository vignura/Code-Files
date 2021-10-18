#include <stdio.h>

#define ARRAY_SIZE  3
#define ARRAY_SIZE_1 3

void print_array_1(int* array, int size);
void print_array_2(int (*array)[ARRAY_SIZE_1]);
void test_1();
void test_2();
void test_3();
void test_4();
void test_5();

int main()
{
    int array[ARRAY_SIZE] = {0};
    // array of interger pointers
    int *ptr[ARRAY_SIZE] = {NULL};
    // pointer to array of int of size ARRAY_SIZE
    int (*arrPtr)[ARRAY_SIZE] = {NULL};
    // int (*arrPtr) = NULL;
    // int *arrPtr = NULL;

    // fill the array
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        array[i] = (i + 1);
    }

    ptr[0] = array;
    // this copies the address of all elements in the array to arrPtr
    arrPtr = &array;
    // arrPtr = array;

    // printf("ptr: %d arrPtr: %d\n", ptr[0][2], (*arrPtr)[2]);
    // printf("ptr: %d arrPtr: %d\n", ptr[0][2], arrPtr[2]);
    
    // printf("print_array_1\n");
    // print_array_1(array, (sizeof(array) / sizeof(int)));
    // printf("print_array_2\n");
    // print_array_2(&array);
    // test_1();
    // test_2();
    // test_3();
    test_5();

    return 0;
}

void print_array_1(int* array, int size)
{
    printf("Size of pointer: %d\n", sizeof(array));

    printf("[ ");
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\b]\n");
}

void print_array_2(int (*array)[ARRAY_SIZE_1])
{
    int size = sizeof(*array) / sizeof(int);
    printf("Size of pointer: %d\n", size);

    printf("[ ");
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", (*array)[i]);
    }
    printf("\b]\n");
}

void test_1()
{
    printf("%s\n", __func__);
    int a;
    char *x;
    x = (char *) &a;
    a = 512;
    x[0] = 1;
    x[1] = 2;
    printf("%d\n", a);
}

void fun(int *p)
{
    int q = 10;
    p = &q;
}

void test_2()
{
    printf("%s\n", __func__);
    int r = 20;
    int *p = &r;
    fun(p);
    printf("%d", *p);
}

void test_3()
{
    int i = 5;
    void *vptr; 
    vptr = &i;
    // uncomment to check for the error
    // printf("\nValue of iptr = %d ", *vptr);
}


void test_4()
{
    char *ptr = "void pointer";
    void *vptr;

    printf("%s\n" , ptr);

    vptr = &ptr;
    printf("%s\n" , *(char**)vptr);

    vptr = ptr;
    printf("%s\n" , (char*)vptr);
}


void test_5()
{
    char *ptr = NULL;
    printf("%s", ptr);
}