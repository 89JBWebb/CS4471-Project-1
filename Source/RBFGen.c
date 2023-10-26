#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    
    //argument checking
    if(argc < 2){
        printf("Please input an m.\n./RBFGen m\n");
        return 1;
    }
    if(argc > 2){
        printf("Please input just one argument.\n./RBFGen m\n");
    }

    //instanciate bloom filter
    int m = atoi(argv[1]);
    char bloom [m];
    for(int i = 0; i < m; i++){
        bloom[i] = 0;
    }

    //open or create output.txt file
    FILE * fp;
    fp = fopen("output.txt", "w");
    for(int i = 0; i < m; i++){
        if(bloom[i]){
            fputc('1', fp);
        } else {
            fputc('0', fp);
        }
    }
    fclose(fp);

    return 0;
}