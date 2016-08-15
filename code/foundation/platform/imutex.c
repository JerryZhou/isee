#include "foundation/platform/imutex.h"

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

/* create resource */
void imutexinit(imutex *mutex) {
#ifdef WIN32
    mutex->_mutex = CreateMutex(NULL, 0, NULL);
#else
    /* recursive mutex */
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex->_mutex, &attr);
#endif
}

/* release resource */
void imutexrelease(imutex *mutex) {
#ifdef WIN32
    CloseHandle(mutex->_mutex);
#else
    pthread_mutex_destroy(&mutex->_mutex);
#endif
}

/* lock mutex */
void imutexlock(imutex *mx) {
#ifdef WIN32
    WaitForSingleObject(mx->_mutex, 0);
#else
    pthread_mutex_lock(&mx->_mutex);
#endif
}

/*unlock mutex*/
void imutexunlock(imutex *mx) {
#ifdef WIN32
    ReleaseMutex(mx->_mutex);
#else
    pthread_mutex_unlock(&mx->_mutex);
#endif   
}

