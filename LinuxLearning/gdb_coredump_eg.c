/**
 * gcc -ggdb3 -std=c99 -Wall -Wextra -pedantic -o gdb_coredump_eg.out gdb_coredump_eg.c
 * ulimit -c unlimited
 * rm -f core
 * ./gdb_coredump_eg.out
 **/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int myfunc(int i) {
    *(int*)(NULL) = i; /* line 7 */
    return i - 1;
}

int main(int argc, char **argv) {
    /* Setup some memory. */
    char data_ptr[] = "string in data segment";
    char *mmap_ptr;
    char *text_ptr = "string in text segment";
    (void)argv;
    mmap_ptr = (char *)malloc(sizeof(data_ptr) + 1);
    strcpy(mmap_ptr, data_ptr);
    mmap_ptr[10] = 'm';
    mmap_ptr[11] = 'm';
    mmap_ptr[12] = 'a';
    mmap_ptr[13] = 'p';
    printf("text addr: %p\n", text_ptr);
    printf("data addr: %p\n", data_ptr);
    printf("mmap addr: %p\n", mmap_ptr);

    /* Call a function to prepare a stack trace. */
    return myfunc(argc);
}