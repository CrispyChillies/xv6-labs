#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char* strcat(char* dest, const char* src){
    char* ptr = dest;

    while(*ptr != '\0'){
        ptr++;
    }

    while(*src != '\0'){
        *ptr = *src;
        ptr++;
        src++;
    }

    *ptr = '\0';

    return dest;
}

void concactenate(char* buffer, const char* start, const char* file){
    strcpy(buffer, start);
    buffer = strcat(buffer, "/");
    buffer = strcat(buffer, file);
}

void find(const char* start,const char* file){
    int fd;
    struct dirent de;
    struct stat st;
    char buffer[512];

    if((fd = open(start, 0)) < 0){
        fprintf(2, "ls: cannot open %s\n", start);
        return;
    }

    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        if(de.inum == 0)
            continue;
        if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
            continue;
        concactenate(buffer, start, de.name);
        if(stat(buffer, &st) < 0){
            printf("stat");
            continue;
        }

        if(st.type == T_DIR){
            find(buffer, file);
        }else if(st.type == T_FILE){
            if(strcmp(de.name, file) == 0){
                printf("%s/%s\n", start, de.name);
            }
        }
    }
    close(fd);

}

int main(int argc, const char* argv[]){
    if(argc < 3){
        printf("(Add the directory to find)");
    }else if(argc == 3){
        const char* start = argv[1];
        const char* file = argv[2];

        find(start, file);

    }else{
        printf("(Number arguments overloaded)");
    }

    exit(0);

}