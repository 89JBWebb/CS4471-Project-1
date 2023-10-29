#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "sha256.h"

int main(int argc, char **argv){
    
    //argument checking
    if(argc < 3){
        printf("Please input an RBF file and an IP address.\n./RBFGen IP RBF.txt\n");
        return 1;
    }
    if(argc > 3){
        printf("Please input an RBF file and an IP address.\n./RBFGen IP RBF.txt\n");
        return 1;
    }

    //open file
    int fd;
    int m;
    char fn [256];
    sprintf(fn, "Results/%s", argv[1]);
    fd = open(fn, O_RDONLY);
    m = lseek(fd, 0, SEEK_END);

    //hashing loop
    char hodl [2];
    char ip [16];
    BYTE buf[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx;
    int row, column;
    for(int i = 1; i < 9; i++){

        //hash ip with new function
        sprintf(ip, "%d%s", i, argv[2]);
        sha256_init(&ctx);
        sha256_update(&ctx, ip, 14);
        sha256_final(&ctx, buf);
        column = ((buf[SHA256_BLOCK_SIZE-3]%16)*256*256+buf[SHA256_BLOCK_SIZE-2]*256+buf[SHA256_BLOCK_SIZE-1])% m;

        //hash column of BF with secret key
        sprintf(ip, "0%d", column);
        sha256_init(&ctx);
        sha256_update(&ctx, ip, strlen(ip));
        sha256_final(&ctx, buf);
        row = buf[SHA256_BLOCK_SIZE-1]%2;

        //go to row in file
        lseek(fd, column, SEEK_SET);
        read(fd, hodl, 1);

        //check to throw pass
        if(atoi(hodl) == row){
            printf("pass\n");
            return 0;
        }
    }

    //return block
    printf("block\n");
    return 0;
}