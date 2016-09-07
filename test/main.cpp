#include <stdio.h>
#include <stdlib.h>

#include "simpletest.h"

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

// foundation/container
#include "foundation/test_iarray.h"
#include "foundation/test_idict.h" // TODO:
#include "foundation/test_iheap.h"
#include "foundation/test_ineighbor.h"
#include "foundation/test_irefcache.h"
#include "foundation/test_ireflist.h"
#include "foundation/test_islice.h"
#include "foundation/test_itree.h" // TODO:

// foundation/util
#include "foundation/test_iarraytypes.h"
#include "foundation/test_icmdarg.h"
#include "foundation/test_iradix.h" // TODO:
#include "foundation/test_istring.h"
#include "foundation/test_iringbuffer.h"    // TODO:

// foundation/math
#include "foundation/test_icircle.h"
#include "foundation/test_iline.h"
#include "foundation/test_imat.h"
#include "foundation/test_iquat.h"
#include "foundation/test_imath.h"
#include "foundation/test_iplane.h"
#include "foundation/test_ipolygon.h"
#include "foundation/test_ipos.h"
#include "foundation/test_irect.h"
#include "foundation/test_isize.h"
#include "foundation/test_ivec.h"

iimplementapplication();

int ISeeMain(const icmdarg *arg) {
    iunused(arg);
    runAllTest();
    return 0;
}
