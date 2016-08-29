#include <stdio.h>
#include <stdlib.h>

#include "simpletest.h"
#include "foundation/platform/ientry.h"

// foundation/core
#include "foundation/test_iobj.h"
#include "foundation/test_iobjcache.h"
#include "foundation/test_iref.h"
#include "foundation/test_iwref.h"
#include "foundation/test_imeta.h"

// foundation/memory
#include "foundation/test_imemorystatistic.h"
#include "foundation/test_imemory.h"

// foundation/platform
#include "foundation/test_imutex.h"
#include "foundation/test_iatomic.h"
#include "foundation/test_ientry.h"
#include "foundation/test_iplatform.h"

iimplementapplication();

int ISeeMain(const icmdarg *arg) {
    iunused(arg);
    runAllTest();
    return 0;
}
