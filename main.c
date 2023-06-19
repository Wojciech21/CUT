#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Hello world!\n");
    const int c = 10;
    int* ptr = (int*)&c;
}