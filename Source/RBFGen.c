#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sha256.h"

//print unsigned char chain in hexa
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

int main(int argc, char **argv){
    
    //argument checking
    if(argc < 3){
        printf("Please input an m and an n.\n./RBFGen m n\n");
        return 1;
    }
    if(argc > 3){
        printf("Please input two arguments.\n./RBFGen m n\n");
        return 1;
    }

    //instanciate bloom filter
    int m = atoi(argv[1]);
    char bloom [m];//whether or not the bucket is filled
    char choose [m]; //whether or not the top bucket is choosen
    BYTE buf[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx;
    char ip [64];
    for(int i = 0; i < m; i++){
        bloom[i] = 0;
        ip[2] = '\0';
        ip[3] = '\0';
        ip[4] = '\0';
        ip[5] = '\0';
        ip[6] = '\0';
        ip[7] = '\0';
        sprintf(ip, "0%d", i);
        sha256_init(&ctx);
        sha256_update(&ctx, ip, strlen(ip));
        sha256_final(&ctx, buf);
        choose[i] = buf[SHA256_BLOCK_SIZE-1]%2;
    }

    //add malicous IPs to filter
    int hodl;
    for(int i = 0; i < 10000; i++){
        for(int j = 1; j < 9; j++){

            //create malicous IP
            sprintf(ip, "%1d192.168.%1d.%03d", j, i/1000, i%1000);
        
            //calculate hash for each hash function
            sha256_init(&ctx);
            sha256_update(&ctx, ip, 14);
            sha256_final(&ctx, buf);

            //set that bit to true
            hodl = (buf[SHA256_BLOCK_SIZE-3]%16)*256*256+buf[SHA256_BLOCK_SIZE-2]*256+buf[SHA256_BLOCK_SIZE-1];
            bloom[hodl%m] = 1;

        }
    }

    //open or create output.txt file
    FILE * fp;
    char fn [256];
    sprintf(fn, "Results/%s", argv[2]);
    fp = fopen(fn, "w");
    for(int i = 0; i < m; i++){
        if(choose[i] == bloom[i]){
            fputc('0', fp);
        } else {
            fputc('1', fp);
        }
    }
    fclose(fp);

    return 0;
}