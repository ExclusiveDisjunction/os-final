#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char** argv) {
    if(argc <= 1) return 0;

    while(1){
        int i;
        for(i=1; i < argc; i++){
            printf(1, "%s ", argv[i]);
        }
        printf(1, "");
    }
}
