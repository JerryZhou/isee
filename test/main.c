#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[]) {
    int n;
    for (n=0; n<argc; ++n) {
        printf("args[%d]=%s%s", n, argv[n], (n!=argc-1?", ":"\n"));
    }
    return 0;
}
