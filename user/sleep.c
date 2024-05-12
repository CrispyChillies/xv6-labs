#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, const char* argv[]){
    if(argc < 2){
        printf("(User must enter the sleeping time)\n");
    }else{
        printf("(Nothing happens for a little while)\n");
        int time = atoi(argv[1]);
        sleep(time);
    }
    exit(0);
}
