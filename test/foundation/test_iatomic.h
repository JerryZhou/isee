#include "simpletest.h"
#include "foundation/platform/iatomic.h"

SP_SUIT(iatomic);

SP_CASE(iatomic, iatomiccompareexchange) {
    SP_TRUE(1);
    uint32_t store = 1;
    uint32_t expected = 2;
    uint32_t desired = 3;
    
    uint32_t xv = iatomiccompareexchange(&store, expected, desired);
    SP_TRUE(xv == 1);
    SP_TRUE(store == 1);
    SP_TRUE(expected == 2);
    SP_TRUE(desired == 3);
    
    expected = 1;
    xv = iatomiccompareexchange(&store, expected, desired);
    SP_TRUE(xv == 1);
    SP_TRUE(store == 3);
    SP_TRUE(expected == 1);
    SP_TRUE(desired == 3);
}

SP_CASE(iatomic, iatomicadd) {
    SP_TRUE(1);
    
    uint32_t store = 1;
    uint32_t xv = iatomicadd(&store, 10);
    SP_TRUE(xv == 11);
    SP_TRUE(store == 11);
}

SP_CASE(iatomic, iatomicexchange) {
    SP_TRUE(1);
    uint32_t store = 1;
    uint32_t xv = iatomicexchange(&store, 10);
    SP_TRUE(xv == 1);
    SP_TRUE(store = 10);
}

SP_CASE(iatomic, iatomicincrement) {
    SP_TRUE(1);
    
    volatile uint32_t store = 1;
    uint32_t xv = iatomicincrement(&store);
    SP_TRUE(xv == 2);
    SP_TRUE(store == 2);
}

SP_CASE(iatomic, iatomicdecrement) {
    SP_TRUE(1);
    volatile uint32_t store = 1;
    uint32_t xv = iatomicdecrement(&store);
    SP_TRUE(xv == 0);
    SP_TRUE(store == 0);
}