#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(){
    printf("Hello World\n");
    unsigned char hash1[] = {0x02};
    unsigned char hash2[] = {0x09};
    printf("%02X\n", hash1[0]*hash2[0]);
    return 0;
}