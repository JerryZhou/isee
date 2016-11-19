#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "malloc.h"

#define __x_unused(v) (void)(v)

typedef struct Foo {
    char x;
    short y;
    int z;
} Foo;

typedef struct Bar {
    char x;
    Foo y;
    int z;
    double w;
    char s[20];
} Bar;

typedef struct Zoo {
    char x;
    Bar y;
    int z;
    double w;
} Zoo;

void line_n_o(int n, char *s, char *seq) {
    for(;n;--n) {
        printf("%s%s",s, n!=1?seq:"");
    }
    printf("\n");
}

void foo_align() {
    printf("%lu-%lu-%lu-%lu\n", sizeof(Foo), offsetof(Foo, x), offsetof(Foo, y), offsetof(Foo, z));
    Foo a;
    char b;
    Foo c;
    Foo d;
    int e;

    printf("%p-%p-%p-%p-%p\n", &a, &b, &c, &d, &e);
    printf("%lu-%lu-%lu-%lu\n", 
            (size_t)((char*)(&a)-(char*)(&b)), 
            (size_t)((char*)(&b)-(char*)(&c)),
            (size_t)((char*)(&c)-(char*)(&d)),
            (size_t)((char*)(&d)-(char*)(&e))
          );
}

void bar_align() {
    printf("%lu-%lu-%lu-%lu-%lu\n", sizeof(Bar), offsetof(Bar, x), offsetof(Bar, y), offsetof(Bar, z), offsetof(Bar, w));
    Bar a;
    char b;
    Bar c;
    Bar d;
    int e;
    printf("%p-%p-%p-%p-%p\n", &a, &b, &c, &d, &e);
    printf("%lu-%lu-%lu-%lu\n", 
            (size_t)((char*)(&a)-(char*)(&b)), 
            (size_t)((char*)(&b)-(char*)(&c)),
            (size_t)((char*)(&c)-(char*)(&d)),
            (size_t)((char*)(&d)-(char*)(&e))
          );
}

void zoo_align() {
    printf("%lu-%lu-%lu-%lu-%lu\n", sizeof(Zoo), offsetof(Zoo, x), offsetof(Zoo, y), offsetof(Zoo, z), offsetof(Zoo, w));
    Zoo a;
    char b;
    Zoo c;
    Zoo d;
    int e;
    printf("%p-%p-%p-%p-%p\n", &a, &b, &c, &d, &e);
    printf("%lu-%lu-%lu-%lu\n", 
            (size_t)((char*)(&a)-(char*)(&b)), 
            (size_t)((char*)(&b)-(char*)(&c)),
            (size_t)((char*)(&c)-(char*)(&d)),
            (size_t)((char*)(&d)-(char*)(&e))
          );
}

#define ALIGN 64

void *aligned_malloc(int size) {
    void *mem = malloc(size+ALIGN+sizeof(void*));
    void **ptr = (void**)((uintptr_t)(mem+ALIGN+sizeof(void*)) & ~(ALIGN-1));
    ptr[-1] = mem;
    return ptr;
}

void aligned_free(void *ptr) {
    free(((void**)ptr)[-1]);
}

int main(int argc, const char *argv[]) {
    __x_unused(argc);
    __x_unused(argv);

    foo_align();
    line_n_o(30, "*", "-");
    bar_align();
    line_n_o(30, "*", "-");
    zoo_align();

    return 0;
}
