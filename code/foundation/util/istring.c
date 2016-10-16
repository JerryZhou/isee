#include "foundation/util/istring.h"
#include "foundation/util/iarraytypes.h"

ideclarestring(kstring_empty, "");
istring *kstring_zero = NULL;

/* c-style: ending with zero */
#define __istring_cstyle(arr) \
    do { iarrayexpandcapacity(arr, iarraylen(arr)+1); \
    ((char*)iarraybuffer(arr))[iarraylen(arr)] = 0; } while(0)

/*Make a string by c-style string */
istring* istringmake(const char* s) {
    icheckret(s, kstring_zero);
    return istringmakelen(s, strlen(s));
}

/*Make a string by s and len*/
istring* istringmakelen(const char* s, size_t len) {
    islice *str;
    iarray *arr = NULL;
    
    /* kstring_zero */
    icheckret(s, kstring_zero);
    /* kstring_empty */
    if (len == 0) {
        iretain(kstring_empty);
        return kstring_empty;
    }
    
    arr = iarraymakechar(len+1);
    iarrayinsert(arr, 0, s, len);
    __istring_cstyle(arr);
    
    str = islicemake(arr, 0, len, 0);
    irelease(arr);
    return istringlaw(str);
}

/*Make a copy of s with c-style string*/
istring* istringdup(const istring *s) {
    return istringmakelen(istringbuf(s), istringlen(s));
}

/*Return the string length */
size_t istringlen(const istring *s) {
    icheckret(s, 0);
    return islicelen(s);
}

/*visit the real string buffer*/
const char* istringbuf(const istring *s) {
    return (const char*)isliceat(s, 0);
}

/*set the entry for stack string */
istring* istringlaw(istring *s) {
    /* the const string should be fill with entry */
    if (s->array && s->array->entry == NULL) {
        s->array->entry = iarrayentryget(EnumArrayEntryType_Char);
    }
    /* the flag: string */
    iflag_add(s->flag, EnumSliceFlag_String);
    return s;
}

/* Helper for irg_print() doing the actual number -> string
 * conversion. 's' must point to a string with room for at least
 * _IRB_LLSTR_SIZE bytes.
 *
 * The function returns the length of the null-terminated string
 * representation stored at 's'. */
#define _IRB_LLSTR_SIZE 256

size_t _ill2str(char *s, int64_t value) {
    char *p, aux;
    uint64_t v;
    size_t l;
    
    /* Generate the string representation, this method produces
     * an reversed string. */
    v = (value < 0) ? -value : value;
    p = s;
    do {
        *p++ = '0'+(v%10);
        v /= 10;
    } while(v);
    if (value < 0) *p++ = '-';
    
    /* Compute length and add null term. */
    l = p-s;
    *p = '\0';
    
    /* Reverse the string. */
    p--;
    while(s < p) {
        aux = *s;
        *s = *p;
        *p = aux;
        s++;
        p--;
    }
    return l;
}

/* Identical _ill2str(), but for unsigned long long type. */
size_t _iull2str(char *s, uint64_t v) {
    char *p, aux;
    size_t l;
    
    /* Generate the string representation, this method produces
     * an reversed string. */
    p = s;
    do {
        *p++ = '0'+(v%10);
        v /= 10;
    } while(v);
    
    /* Compute length and add null term. */
    l = p-s;
    *p = '\0';
    
    /* Reverse the string. */
    p--;
    while(s < p) {
        aux = *s;
        *s = *p;
        *p = aux;
        s++;
        p--;
    }
    return l;
}

size_t _idouble2str(char *s, double d) {
    size_t n = snprintf(s, 256, "%.4lf", d);
    s[n] = 0;
    return n;
}

/*format the string and return the value*/
istring* istringformat(const char* fmt, ...) {
    istring *s;
    iarray *arr = iarraymakechar(strlen(fmt)*2);
    const char *f = fmt;
    size_t i;
    double d;
    va_list ap;
    
    char next, *str;
    size_t l;
    int64_t num;
    uint64_t unum;
    
    char buf[_IRB_LLSTR_SIZE];
    
    va_start(ap,fmt);
    f = fmt;    /* Next format specifier byte to process. */
    i = 0;
    while(*f) {
        
        /* Make sure there is always space for at least 1 char. */
        switch(*f) {
            case '%':
                next = *(f+1);
                f++;
                switch(next) {
                    case 's':
                    case 'S':
                        str = va_arg(ap,char*);
                        l = strlen(str);/*(next == 's') ?  : sdslen(str);*/
                        iarrayinsert(arr, iarraylen(arr), str, l);
                        i += l;
                        break;
                    case 'v':
                    case 'V':
                        s = va_arg(ap, istring*);
                        l = istringlen(s);
                        iarrayinsert(arr, iarraylen(arr), istringbuf(s), l);
                        i += l;
                        break;
                    case 'f':
                    case 'F':
                        d = va_arg(ap, double);
                        l = _idouble2str(buf, d);
                        iarrayinsert(arr, iarraylen(arr), buf, l);
                        i += l;
                        break;
                    case 'i':
                    case 'I':
                        if (next == 'i')
                            num = va_arg(ap,int);
                        else
                            num = va_arg(ap,int64_t);
                    {
                        l = _ill2str(buf, num);
                        iarrayinsert(arr, iarraylen(arr), buf, l);
                        i += l;
                    }
                        break;
                    case 'u':
                    case 'U':
                        if (next == 'u')
                            unum = va_arg(ap,unsigned int);
                        else
                            unum = va_arg(ap,uint64_t);
                    {
                        l = _iull2str(buf, unum);
                        iarrayinsert(arr, iarraylen(arr), buf, l);
                        i += l;
                    }
                        break;
                    default: /* Handle %% and generally %<unknown>. */
                        iarrayinsert(arr, iarraylen(arr), f, 1);
                        break;
                }
                break;
            default:
                iarrayinsert(arr, iarraylen(arr), f, 1);
                break;
        }
        f++;
    }
    va_end(ap);
    
    s = islicemakearg(arr, ":");
    irelease(arr);
    return istringlaw(s);
}

/*compare the two istring*/
int istringcompare(const istring *lfs, const istring *rfs) {
    size_t lfslen = istringlen(lfs);
    size_t rfslen = istringlen(rfs);
    int n;
    /* zero string */
    if (lfs == NULL || rfs == NULL) {
        if (lfs == rfs) {
            return 0;
        } else if (lfs) {
            return 1;
        } else {
            return -1;
        }
    }
    /* not zero string */
    n = strncmp(istringbuf(lfs), istringbuf(rfs), imin(lfslen, rfslen));
    if (n) {
        return n;
    }
    return lfslen - rfslen;
}

/*find the index in istring */
/*https://en.wikipedia.org/wiki/String_searching_algorithm*/
/*[Rabin-Karp]http://mingxinglai.com/cn/2013/08/pattern-match/*/
/*[Sunday](http://blog.163.com/yangfan876@126/blog/static/80612456201342205056344)*/
/*[Boyer-Moore](http://blog.jobbole.com/52830/) */
/*[Knuth-Morris-Pratt](http://www.ruanyifeng.com/blog/2013/05/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm.html)*/

/*Boyer-Moore Algorithm*/
static void _istringfind_prebmbc(unsigned char *pattern, int m, int bmBc[]) {
    int i;
    
    for(i = 0; i < 256; i++) {
        bmBc[i] = m;
    }
    
    for(i = 0; i < m - 1; i++) {
        bmBc[(int)pattern[i]] = m - 1 - i;
    }
}

/*
 static void _istringfind_suffix_old(unsigned char *pattern, int m, int suff[]) {
 int i, j;
 suff[m - 1] = m;
 
 for(i = m - 2; i >= 0; i--){
 j = i;
 while(j >= 0 && pattern[j] == pattern[m - 1 - i + j]) j--;
 suff[i] = i - j;
 }
 }
 */

static void _istringfind_suffix(unsigned char *pattern, int m, int suff[]) {
    int f, g, i;
    
    suff[m - 1] = m;
    g = m - 1;
    for (i = m - 2; i >= 0; --i) {
        if (i > g && suff[i + m - 1 - f] < i - g)
            suff[i] = suff[i + m - 1 - f];
        else {
            if (i < g)
                g = i;
            f = i;
            while (g >= 0 && pattern[g] == pattern[g + m - 1 - f])
                --g;
            suff[i] = f - g;
        }
    }
}

static void _istringfind_prebmgs(unsigned char *pattern, int m, int bmGs[])
{
    int i, j;
    int suff[256];
    
    _istringfind_suffix(pattern, m, suff);
    
    for(i = 0; i < m; i++) {
        bmGs[i] = m;
    }
    
    j = 0;
    for(i = m - 1; i >= 0; i--) {
        if(suff[i] == i + 1) {
            for(; j < m - 1 - i; j++) {
                if(bmGs[j] == m)
                    bmGs[j] = m - 1 - i;
            }
        }
    }
    
    for(i = 0; i <= m - 2; i++) {
        bmGs[m - 1 - suff[i]] = m - 1 - i;
    }
}
iarray* _istringfind_boyermoore(unsigned char *pattern, int m, unsigned char *text, int n, int num)
{
    int i, j, bmBc[256], bmGs[256];
    iarray *indexs = iarraymakeint(num);
    
    /* Preprocessing */
    _istringfind_prebmbc(pattern, m, bmBc);
    _istringfind_prebmgs(pattern, m, bmGs);
    
    /* Searching */
    j = 0;
    while(j <= n - m && num) {
        for(i = m - 1; i >= 0 && pattern[i] == text[i + j]; i--);
        if(i < 0) {
            iarrayadd(indexs, &j);
            /*printf("Find it, the position is %d\n", j); */
            j += bmGs[0];
            --num;
        }else {
            j += imax(bmBc[text[i + j]] - m + 1 + i, bmGs[i]);
        }
    }
    
    return indexs;
}

/*find the index in istring */
int istringfind(const istring *rfs, const char *sub, int len, int index) {
    iarray *indexs;
    icheckret(index>=0 && index<istringlen(rfs), kindex_invalid);
    
    indexs = _istringfind_boyermoore((unsigned char*)sub, len,
                                     (unsigned char*) (istringbuf(rfs) + index),
                                     istringlen(rfs)-index,
                                     1);
    
    if (iarraylen(indexs)) {
        index = iarrayof(indexs, int, 0);
        irelease(indexs);
    }  else {
        index = kindex_invalid;
    }
    return index;
}

/*sub string*/
istring* istringsub(const istring *s, int begin, int end) {
    istring *sub = istringlaw(islicedby((istring*)s, begin, end));
    /* empty sub */
    if (0==istringlen(sub)) {
        iassign(sub, kstring_empty);
    }
    return sub;
}

/*return the array of istring*/
iarray* istringsplit(const istring *s, const char* split, size_t len) {
    int subindex = 0;
    int lastsubindex = 0;
    int i;
    size_t size = istringlen(s);
    istring *sub;
    iarray* arr = iarraymakeiref(8);
    
    /*find all the sub*/
    iarray* indexs = _istringfind_boyermoore((unsigned char*)split, len,
                                             (unsigned char*) (istringbuf(s)),
                                             size,
                                             size);
    if (iarraylen(indexs)) {
        /*make enough space for subs*/
        iarrayexpandcapacity(arr, iarraylen(indexs));
        /*go through the sub*/
        for (i=0; i<iarraylen(indexs); ++i) {
            subindex = iarrayof(indexs, int, i);
            sub = istringsub(s, lastsubindex, subindex);
            lastsubindex = subindex + len;
            
            iarrayadd(arr, &sub);
            irelease(sub);
        }
        
        /*the last sub*/
        subindex = iarrayof(indexs, int, 0);
        sub = istringsub(s, lastsubindex, size);
        iarrayadd(arr, &sub);
        irelease(sub);
    } else {
        /*add the original string as the first sub*/
        iarrayadd(arr, &s);
    }
    
    /*free the find indexs*/
    irelease(indexs);
    
    return arr;
}

/*return the array of sting joined by dealer */
istring* istringjoin(const iarray* ss, const char* join, size_t len) {
    iarray *joined = iarraymakechar(8);
    istring *s;
    size_t i = 0;
    size_t num = iarraylen(ss);
    /*the first one*/
    if (num) {
        s = iarrayof(ss, istring*, 0);
        iarrayinsert(joined, 0, istringbuf(s), istringlen(s));
    }
    /*the after childs*/
    for (i=1; i<num; ++i) {
        iarrayinsert(joined, iarraylen(joined), join, len);
        s = iarrayof(ss, istring*, i);
        iarrayinsert(joined, iarraylen(joined), istringbuf(s), istringlen(s));
    }
    /*set zero-ending */
    __istring_cstyle(joined);
    
    /*make slice*/
    s = islicemakearg(joined, ":");
    irelease(joined);
    return istringlaw(s);
}

/*return the new istring with new component*/
istring* istringrepleace(const istring *s, const char* olds, size_t oldslen, const char* news, size_t newlen) {
    iarray *splits = istringsplit(s, olds, oldslen);
    istring *ns = istringjoin(splits, news, newlen);
    irelease(splits);
    
    return ns;
}

/*return the new istring append with value*/
istring* istringappend(const istring *s, const char* append, size_t len) {
    istring *ns;
    iarray *arr = iarraymakechar(istringlen(s) + len +1);
    iarrayinsert(arr, 0, istringbuf(s), istringlen(s));
    iarrayinsert(arr, iarraylen(arr), append, len);
    __istring_cstyle(arr);
    
    ns = islicemakearg(arr, ":");
    irelease(arr);
    return istringlaw(ns);
}

/*baisc wrap for ::atoi */
int istringatoi(const istring *s) {
    char buf[256+1] = {0};
    size_t size = istringlen(s);
    icheckret(size, 0);
    strncpy(buf, istringbuf(s), imin(256, size));
    
    return atoi(buf);
}

/*[cocos2dx](https://github.com/cocos2d/cocos2d-x/blob/v3/cocos/base/ccUtils.h)*/
/** Same to ::atof, but strip the string, remain 7 numbers after '.' before call atof.
 * Why we need this? Because in android c++_static, atof ( and std::atof )
 * is unsupported for numbers have long decimal part and contain
 * several numbers can approximate to 1 ( like 90.099998474121094 ), it will return inf.
 * This function is used to fix this bug.
 * @param str The string be to converted to double.
 * @return Returns converted value of a string.
 */
double istringatof(const istring *s) {
    char buf[256+1] = {0};
    char* dot = NULL;
    size_t size = istringlen(s);
    
    icheckret(size, 0.0);
    strncpy(buf, istringbuf(s), imin(256, size));
    
    /* strip string, only remain 7 numbers after '.' */
    dot = strchr(buf, '.');
    if (dot != NULL && dot - buf + 8 < 256) {
        dot[8] = '\0';
    }
    
    return atof(buf);
}

/* */
size_t ill2string(char *s, int64_t value) {
    char *p, aux;
    uint64_t v;
    size_t l;
    
    /* Generate the string representation, this method produces
     * an reversed string. */
    v = (value < 0) ? -value : value;
    p = s;
    do {
        *p++ = '0'+(v%10);
        v /= 10;
    } while(v);
    if (value < 0) *p++ = '-';
    
    /* Compute length and add null term. */
    l = p-s;
    *p = '\0';
    
    /* Reverse the string. */
    p--;
    while(s < p) {
        aux = *s;
        *s = *p;
        *p = aux;
        s++;
        p--;
    }
    return l;
}

/* */
size_t iull2string(char *s, uint64_t value) {
    char *p, aux;
    size_t l;
    
    /* Generate the string representation, this method produces
     * an reversed string. */
    p = s;
    do {
        *p++ = '0'+(value%10);
        value /= 10;
    } while(value);
    
    /* Compute length and add null term. */
    l = p-s;
    *p = '\0';
    
    /* Reverse the string. */
    p--;
    while(s < p) {
        aux = *s;
        *s = *p;
        *p = aux;
        s++;
        p--;
    }
    return l;
}

/* */
size_t idouble2string(char *s, double value) {
    size_t n = snprintf(s, 256, "%.4lf", value);
    s[n] = 0;
    return n;
}
