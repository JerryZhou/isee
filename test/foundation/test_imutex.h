#include "simpletest.h"
#include "foundation/imutex.h"

// **********************************************************************************
// imutex
SP_SUIT(imutex);

SP_CASE(imutex, imutexinitANDimutexrelease) {
    imutex mutex;
    imutexinit(&mutex);
    imutexrelease(&mutex);
    
    SP_TRUE(1);
}

SP_CASE(imutex, imutexlockANDimutexunlock) {
    imutex mutex;
    imutexinit(&mutex);
    
    //RECURSIVE
    imutexlock(&mutex);
    imutexlock(&mutex);
    imutexlock(&mutex);
    
    imutexunlock(&mutex);
    
    imutexrelease(&mutex);
    
    SP_TRUE(1);
}