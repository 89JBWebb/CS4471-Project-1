#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv){
    
    //open file
    FILE * fp;
    char fn [256];
    char buf [2];
    buf[1] = '\0';
    sprintf(fn, "Results/%s", argv[1]);
    int fd = open(fn, O_RDONLY);

    for(int i = 0; i < 10; i++){
        read(fd, buf, 1);
        lseek(fd, i, SEEK_SET);
        read(fd, buf, 1);
        printf("%s\n", buf);
    }

    return 0;
}