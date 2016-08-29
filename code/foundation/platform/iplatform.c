#include "foundation/platform/iplatform.h"

#ifdef _WIN32
#include <windows.h>
#ifdef __cplusplus
extern "C" {
#endif
static int gettimeofday(struct timeval *tp, void *tzp)
{
        time_t clock;
        struct tm tm;
        SYSTEMTIME wtm;

        GetLocalTime(&wtm);
        tm.tm_year = wtm.wYear - 1900;
        tm.tm_mon = wtm.wMonth - 1;
        tm.tm_mday = wtm.wDay;
        tm.tm_hour = wtm.wHour;
        tm.tm_min = wtm.wMinute;
        tm.tm_sec = wtm.wSecond;
        tm.tm_isdst = -1;
        clock = mktime(&tm);
        tp->tv_sec = clock;
        tp->tv_usec = wtm.wMilliseconds * 1000;

        return 0;
}
#ifdef __cplusplus
}
#endif /*__cplusplus*/
#else
#include <sys/time.h>
/*http://man7.org/linux/man-pages/man2/gettimeofday.2.html*/
#endif /*WIN32*/

/* https://en.wikipedia.org/wiki/Second 
 * seconds 
 *  = 1000 milliseconds 
 *  = 1000 * 1000 microseconds 
 *  = 1000 * 1000 * 1000 nanoseconds 
 * */
int64_t igetcurmicro() {
    struct timeval tv;

	gettimeofday(&tv, NULL);
	return tv.tv_sec*1000*1000 + tv.tv_usec;
}

/* get next unique microseconds */
int64_t igetnextmicro() {
    static int64_t gseq = 0;
	int64_t curseq = igetcurmicro();
	if (curseq > gseq) {
		gseq = curseq;
	}else {
		++gseq;
	}
	return gseq;
}

/* get current milliseconds  */
int64_t igetcurtick() {
    return igetcurmicro()/1000;
}

/* sleeping the current thread */
void isleep(unsigned int milliseconds) {
#ifdef WIN32
    Sleep((DWORD)milliseconds);
#else
    /* http://man7.org/linux/man-pages/man3/usleep.3.html */
    usleep(milliseconds*1000);
#endif
}

