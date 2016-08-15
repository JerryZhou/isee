#include <stdio.h>
#include <stdlib.h>

#include "simpletest.h"

#include "foundation/test_iobj.h"
#include "foundation/test_iobjcache.h"
#include "foundation/test_imemorystatistic.h"
#include "foundation/test_imemory.h"
#include "foundation/test_imeta.h"
#include "foundation/test_imutex.h"
#include "foundation/test_iatomic.h"

int main(int argc, const char* argv[]) {
    int n;
    for (n=0; n<argc; ++n) {
        printf("args[%d]=%s%s", n, argv[n], (n!=argc-1?", ":"\n"));
    }
    runAllTest();
    return 0;
}
