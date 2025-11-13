#include "types.h"
#include "user.h"

// Simple program to just hog the CPU time
int main(){
    while(1){
        printf(1, "hog\n");
        boostproc();
    }
    return 0;
}