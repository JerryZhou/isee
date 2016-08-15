#ifndef _IMUTEX_H_
#define _IMUTEX_H_
#include "foundation/itype.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* recursive mutex */
typedef struct imutex {
#ifdef WIN32
    HANDLE _mutex;
#else
    pthread_mutex_t _mutex;
#endif
}imutex;
    
/*create resource*/
void imutexinit(imutex *mutex);
/*release resource*/
void imutexrelease(imutex *mutex);

/*lock mutex*/
void imutexlock(imutex *mx);
/*unlock mutex*/
void imutexunlock(imutex *mx);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif
