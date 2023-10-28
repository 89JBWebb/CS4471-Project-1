#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "sha256.h"

void printh(BYTE* word, int n){
    char outword[n*2+1];
    int i, len;

    len = SHA256_BLOCK_SIZE;
    if(word[len-1]=='\n')
        word[--len] = '\0';

    for(i = 0; i<len; i++){
        sprintf(outword+i*2, "%02X", word[i]);
    }
    printf("%s\n", outword);
}

int main(){

    for(int i = 0; i < 10; i++){

        char b [3];
        sprintf(b, "%02d", i);
        BYTE buf[SHA256_BLOCK_SIZE];

        SHA256_CTX ctx;
        sha256_init(&ctx);
        sha256_update(&ctx, b, strlen(b));
        sha256_final(&ctx, buf);

        printh(buf, SHA256_BLOCK_SIZE);
        //int c = buf[SHA256_BLOCK_SIZE-2]*256+buf[SHA256_BLOCK_SIZE-1];
        int c = (buf[SHA256_BLOCK_SIZE-3]%16)*256*256+buf[SHA256_BLOCK_SIZE-2]*256+buf[SHA256_BLOCK_SIZE-1];
        printf("%d\n", c);
        unsigned char a = buf[SHA256_BLOCK_SIZE-1];
        printf("mod 2: %d\n", a%2);

    }

    return 0;
}