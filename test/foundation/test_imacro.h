#include "foundation/core/imacro.h"

SP_SUIT(imacro);

SP_CASE(imacro, imetamacro_exprify) {
    SP_TRUE(1);
    
    ilog(imetamacro_stringify(imetamacro_exprify(1, 2, 3)));
}

SP_CASE(imacro, imetamacro_stringify) {
    imetamacro_stringify(abc);
}

SP_CASE(imacro, imetamacro_concat) {
    int ij = imetamacro_concat(-1, 23);
    SP_TRUE(ij == -123);
}

SP_CASE(imacro, imetamacro_at) {
    int i0 = imetamacro_at(0, 1, 2, 3, 4);
    int i1 = imetamacro_at(1, 1, 2, 3, 4);
    int i2 = imetamacro_at(2, 1, 2, 3, 4);
    int i3 = imetamacro_at(3, 1, 2, 3, 4);
    
    SP_TRUE(i0 == 1);
    SP_TRUE(i1 == 2);
    SP_TRUE(i2 == 3);
    SP_TRUE(i3 == 4);
}

SP_CASE(imacro, imetamacro_argcount) {
    int argn = imetamacro_argcount(1, 2, 3, 4);
    SP_TRUE(argn == 4);
}

void __ii__xx(int i, const char * v) {
    printf("args[%d]=%s", i, v);
}

SP_CASE(imacro, imetamacro_foreach) {
    imetamacro_foreach(__ii__xx, ; , "1", "2", "3", "4");
}

static int _x_m_total_n = 0;
void __ii__xx_i(int i, int ctx, int v) {
    if (_x_m_total_n == 0) {
        _x_m_total_n = ctx;
    }
    _x_m_total_n += v;
}

SP_CASE(imacro, imetamacro_foreach_cxt) {
    SP_TRUE(_x_m_total_n == 0);
    imetamacro_foreach_cxt(__ii__xx_i, ;, 5, 1, 2, 3, 4);
    SP_TRUE(_x_m_total_n == 15);
}

int __ii_sum_n(int i1, int i2, int i3) {
    return i1 + i2 + i3;
}

SP_CASE(imacro, imetamacro_foreach_concat) {
    int i1 = 1, i2 = 2, i3 = 3;
    int i = imetamacro_foreach_concat(i, -, 1, 2, 3);
    SP_TRUE(i == -4);
}

int __ii_cxt_r(int i, int cxt) {
    return i + cxt;
}

SP_CASE(imacro, imetamacro_for_cxt) {
    /* 0 + 5 */
    /* 1 + 5 */
    /* 2 + 5 */
    /* 3 + 5 */
    /* 4 + 5 */
    int total = imetamacro_for_cxt(5, __ii_cxt_r, +, 5);
    SP_TRUE(total == 35);
}

/* 0 + 10 + 100 */
/* 1 + 10 + 200 */
/* 2 + 10 + 300 */
/* 3 + 10 + 400 */
/* 4 + 10 + 500 */
int __ii_idx_i(int i, int cxt, int value) {
    return i + cxt + value;
}
SP_CASE(imacro, imetamacro_head) {
    /* 0 + 10 + 100 */
    int total = imetamacro_foreach_cxt(__ii_idx_i, +, 10, imetamacro_head(100, 200, 300, 400, 500));
    SP_TRUE(total == 110);
}

SP_CASE(imacro, imetamacro_tail) {
    /* 0 + 10 + 200 */
    /* 1 + 10 + 300 */
    /* 2 + 10 + 400 */
    /* 3 + 10 + 500 */
    int total = imetamacro_foreach_cxt(__ii_idx_i, +, 10, imetamacro_tail(100, 200, 300, 400, 500));
    SP_TRUE(total == 1446);
}

SP_CASE(imacro, imetamacro_take) {
    /* 0 + 10 + 100 */
    /* 1 + 10 + 200 */
    int total = imetamacro_foreach_cxt(__ii_idx_i, +, 10, imetamacro_take(2, 100, 200, 300, 400, 500));
    SP_TRUE(total == 321);
}

SP_CASE(imacro, imetamacro_drop) {
    /* 0 + 10 + 300 */
    /* 1 + 10 + 400 */
    /* 2 + 10 + 500 */
    int total = imetamacro_foreach_cxt(__ii_idx_i, +, 10, imetamacro_drop(2, 100, 200, 300, 400, 500));
    SP_TRUE(total == 1233);
}

SP_CASE(imacro, imetamacro_if_eq) {
    /* 0 + 10 + 100 */
    /* 1 + 10 + 200 */
    /* 2 + 10 + 300 */
    /* 3 + 10 + 400 */
    /* 4 + 10 + 500 */
    int total = imetamacro_foreach_cxt(__ii_idx_i, +, 10, imetamacro_if_eq(1, 1)(100, 200, 300, 400, 500)(1, 2, 3, 4, 5));
    SP_TRUE(total == 1560);
}

SP_CASE(imacro, imetamacro_if_eq_n) {
    /* 0 + 10 + 1 */
    /* 1 + 10 + 2 */
    /* 2 + 10 + 3 */
    /* 3 + 10 + 4 */
    /* 4 + 10 + 5 */
    int total = imetamacro_foreach_cxt(__ii_idx_i, +, 10, imetamacro_if_eq(1, 2)(100, 200, 300, 400, 500)(1, 2, 3, 4, 5));
    SP_TRUE(total == 75);
}

SP_CASE(imacro, end) {
    SP_TRUE(1);
}
