#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "sha256.h"

void printh(BYTE* word, int n){
    char outword[n*2+1];
    int i, len;

    len = strlen(word);
    if(word[len-1]=='\n')
        word[--len] = '\0';

    for(i = 0; i<len; i++){
        sprintf(outword+i*2, "%02X", word[i]);
    }
    printf("%s\n", outword);
}

int main(){
    BYTE text1[] = {"abc"};
    BYTE buf[SHA256_BLOCK_SIZE];

    SHA256_CTX ctx;
    sha256_init(&ctx);
	sha256_update(&ctx, text1, strlen(text1));
	sha256_final(&ctx, buf);

    printh(buf, SHA256_BLOCK_SIZE);

    return 0;
}