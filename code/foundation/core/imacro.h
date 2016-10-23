#ifndef __IMACRO_H_
#define __IMACRO_H_
/* see https://github.com/jspahrsummers/libextobjc metamacroprogramming */


/**
 * Executes one or more expressions (which may have a void type, such as a call
 * to a function that returns no value) and always returns true.
 */
#define imetamacro_exprify(...) \
((__VA_ARGS__), true)

/**
 * Returns a string representation of VALUE after full macro expansion.
 */
#define imetamacro_stringify(VALUE) \
imetamacro_stringify_(VALUE)

/**
 * Returns A and B concatenated after full macro expansion.
 */
#define imetamacro_concat(A, B) \
imetamacro_concat_(A, B)

/**
 * Returns the Nth variadic argument (starting from zero). At least
 * N + 1 variadic arguments must be given. N must be between zero and twenty,
 * inclusive.
 */
#define imetamacro_at(N, ...) \
imetamacro_concat(imetamacro_at, N)(__VA_ARGS__)

/**
 * Returns the number of arguments (up to twenty) provided to the macro. At
 * least one argument must be provided.
 *
 * Inspired by P99: http://p99.gforge.inria.fr
 */
#define imetamacro_argcount(...) \
imetamacro_at(20, __VA_ARGS__, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

/**
 * Identical to #metamacro_foreach_cxt, except that no CONTEXT argument is
 * given. Only the index and current argument will thus be passed to MACRO.
 */
#define imetamacro_foreach(MACRO, SEP, ...) \
imetamacro_foreach_cxt(imetamacro_foreach_iter, SEP, MACRO, __VA_ARGS__)

/**
 * For each consecutive variadic argument (up to twenty), MACRO is passed the
 * zero-based index of the current argument, CONTEXT, and then the argument
 * itself. The results of adjoining invocations of MACRO are then separated by
 * SEP.
 *
 * Inspired by P99: http://p99.gforge.inria.fr
 */
#define imetamacro_foreach_cxt(MACRO, SEP, CONTEXT, ...) \
imetamacro_concat(imetamacro_foreach_cxt, imetamacro_argcount(__VA_ARGS__))(MACRO, SEP, CONTEXT, __VA_ARGS__)

/**
 * Identical to #metamacro_foreach_cxt. This can be used when the former would
 * fail due to recursive macro expansion.
 */
#define imetamacro_foreach_cxt_recursive(MACRO, SEP, CONTEXT, ...) \
imetamacro_concat(imetamacro_foreach_cxt_recursive, imetamacro_argcount(__VA_ARGS__))(MACRO, SEP, CONTEXT, __VA_ARGS__)

/**
 * In consecutive order, appends each variadic argument (up to twenty) onto
 * BASE. The resulting concatenations are then separated by SEP.
 *
 * This is primarily useful to manipulate a list of macro invocations into instead
 * invoking a different, possibly related macro.
 */
#define imetamacro_foreach_concat(BASE, SEP, ...) \
imetamacro_foreach_cxt(imetamacro_foreach_concat_iter, SEP, BASE, __VA_ARGS__)

/**
 * Iterates COUNT times, each time invoking MACRO with the current index
 * (starting at zero) and CONTEXT. The results of adjoining invocations of MACRO
 * are then separated by SEP.
 *
 * COUNT must be an integer between zero and twenty, inclusive.
 */
#define imetamacro_for_cxt(COUNT, MACRO, SEP, CONTEXT) \
imetamacro_concat(imetamacro_for_cxt, COUNT)(MACRO, SEP, CONTEXT)

/**
 * Returns the first argument given. At least one argument must be provided.
 *
 * This is useful when implementing a variadic macro, where you may have only
 * one variadic argument, but no way to retrieve it (for example, because \c ...
 * always needs to match at least one argument).
 *
 * @code
 #define varmacro(...) \
 metamacro_head(__VA_ARGS__)
 * @endcode
 */
#define imetamacro_head(...) \
imetamacro_head_(__VA_ARGS__, 0)

/**
 * Returns every argument except the first. At least two arguments must be
 * provided.
 */
#define imetamacro_tail(...) \
imetamacro_tail_(__VA_ARGS__)

/**
 * Returns the first N (up to twenty) variadic arguments as a new argument list.
 * At least N variadic arguments must be provided.
 */
#define imetamacro_take(N, ...) \
imetamacro_concat(imetamacro_take, N)(__VA_ARGS__)

/**
 * Removes the first N (up to twenty) variadic arguments from the given argument
 * list. At least N variadic arguments must be provided.
 */
#define imetamacro_drop(N, ...) \
imetamacro_concat(imetamacro_drop, N)(__VA_ARGS__)

/**
 * Decrements VAL, which must be a number between zero and twenty, inclusive.
 *
 * This is primarily useful when dealing with indexes and counts in
 * metaprogramming.
 */
#define imetamacro_dec(VAL) \
imetamacro_at(VAL, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19)

/**
 * Increments VAL, which must be a number between zero and twenty, inclusive.
 *
 * This is primarily useful when dealing with indexes and counts in
 * metaprogramming.
 */
#define imetamacro_inc(VAL) \
imetamacro_at(VAL, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21)

/**
 * If A is equal to B, the next argument list is expanded; otherwise, the
 * argument list after that is expanded. A and B must be numbers between zero
 * and twenty, inclusive. Additionally, B must be greater than or equal to A.
 *
 * @code
 // expands to true
 imetamacro_if_eq(0, 0)(true)(false)
 // expands to false
 imetamacro_if_eq(0, 1)(true)(false)
 * @endcode
 *
 * This is primarily useful when dealing with indexes and counts in
 * metaprogramming.
 */
#define imetamacro_if_eq(A, B) \
imetamacro_concat(imetamacro_if_eq, A)(B)

/**
 * Identical to #metamacro_if_eq. This can be used when the former would fail
 * due to recursive macro expansion.
 */
#define imetamacro_if_eq_recursive(A, B) \
imetamacro_concat(imetamacro_if_eq_recursive, A)(B)

/**
 * Returns 1 if N is an even number, or 0 otherwise. N must be between zero and
 * twenty, inclusive.
 *
 * For the purposes of this test, zero is considered even.
 */
#define imetamacro_is_even(N) \
imetamacro_at(N, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1)

/**
 * Returns the logical NOT of B, which must be the number zero or one.
 */
#define imetamacro_not(B) \
imetamacro_at(B, 1, 0)

// IMPLEMENTATION DETAILS FOLLOW!
// Do not write code that depends on anything below this line.
#define imetamacro_stringify_(VALUE) # VALUE
#define imetamacro_concat_(A, B) A ## B
#define imetamacro_foreach_iter(INDEX, MACRO, ARG) MACRO(INDEX, ARG)
#define imetamacro_head_(FIRST, ...) FIRST
#define imetamacro_tail_(FIRST, ...) __VA_ARGS__
#define imetamacro_consume_(...)
#define imetamacro_expand_(...) __VA_ARGS__

// implemented from scratch so that metamacro_concat() doesn't end up nesting
#define imetamacro_foreach_concat_iter(INDEX, BASE, ARG) imetamacro_foreach_concat_iter_(BASE, ARG)
#define imetamacro_foreach_concat_iter_(BASE, ARG) BASE ## ARG

// metamacro_at expansions
#define imetamacro_at0(...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at1(_0, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at2(_0, _1, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at3(_0, _1, _2, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at4(_0, _1, _2, _3, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at5(_0, _1, _2, _3, _4, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at6(_0, _1, _2, _3, _4, _5, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at7(_0, _1, _2, _3, _4, _5, _6, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at8(_0, _1, _2, _3, _4, _5, _6, _7, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at9(_0, _1, _2, _3, _4, _5, _6, _7, _8, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at11(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at12(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at13(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at14(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at15(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at17(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at18(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at19(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, ...) imetamacro_head(__VA_ARGS__)
#define imetamacro_at20(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, ...) imetamacro_head(__VA_ARGS__)

// metamacro_foreach_cxt expansions
#define imetamacro_foreach_cxt0(MACRO, SEP, CONTEXT)
#define imetamacro_foreach_cxt1(MACRO, SEP, CONTEXT, _0) MACRO(0, CONTEXT, _0)

#define imetamacro_foreach_cxt2(MACRO, SEP, CONTEXT, _0, _1) \
imetamacro_foreach_cxt1(MACRO, SEP, CONTEXT, _0) \
SEP \
MACRO(1, CONTEXT, _1)

#define imetamacro_foreach_cxt3(MACRO, SEP, CONTEXT, _0, _1, _2) \
imetamacro_foreach_cxt2(MACRO, SEP, CONTEXT, _0, _1) \
SEP \
MACRO(2, CONTEXT, _2)

#define imetamacro_foreach_cxt4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
imetamacro_foreach_cxt3(MACRO, SEP, CONTEXT, _0, _1, _2) \
SEP \
MACRO(3, CONTEXT, _3)

#define imetamacro_foreach_cxt5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
imetamacro_foreach_cxt4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
SEP \
MACRO(4, CONTEXT, _4)

#define imetamacro_foreach_cxt6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
imetamacro_foreach_cxt5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
SEP \
MACRO(5, CONTEXT, _5)

#define imetamacro_foreach_cxt7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
imetamacro_foreach_cxt6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
SEP \
MACRO(6, CONTEXT, _6)

#define imetamacro_foreach_cxt8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
imetamacro_foreach_cxt7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
SEP \
MACRO(7, CONTEXT, _7)

#define imetamacro_foreach_cxt9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
imetamacro_foreach_cxt8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
SEP \
MACRO(8, CONTEXT, _8)

#define imetamacro_foreach_cxt10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
imetamacro_foreach_cxt9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
SEP \
MACRO(9, CONTEXT, _9)

#define imetamacro_foreach_cxt11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
imetamacro_foreach_cxt10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
SEP \
MACRO(10, CONTEXT, _10)

#define imetamacro_foreach_cxt12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
imetamacro_foreach_cxt11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
SEP \
MACRO(11, CONTEXT, _11)

#define imetamacro_foreach_cxt13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
imetamacro_foreach_cxt12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
SEP \
MACRO(12, CONTEXT, _12)

#define imetamacro_foreach_cxt14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
imetamacro_foreach_cxt13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
SEP \
MACRO(13, CONTEXT, _13)

#define imetamacro_foreach_cxt15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
imetamacro_foreach_cxt14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
SEP \
MACRO(14, CONTEXT, _14)

#define imetamacro_foreach_cxt16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
imetamacro_foreach_cxt15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
SEP \
MACRO(15, CONTEXT, _15)

#define imetamacro_foreach_cxt17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
imetamacro_foreach_cxt16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
SEP \
MACRO(16, CONTEXT, _16)

#define imetamacro_foreach_cxt18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
imetamacro_foreach_cxt17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
SEP \
MACRO(17, CONTEXT, _17)

#define imetamacro_foreach_cxt19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
imetamacro_foreach_cxt18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
SEP \
MACRO(18, CONTEXT, _18)

#define imetamacro_foreach_cxt20(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
imetamacro_foreach_cxt19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
SEP \
MACRO(19, CONTEXT, _19)

// metamacro_foreach_cxt_recursive expansions
#define imetamacro_foreach_cxt_recursive0(MACRO, SEP, CONTEXT)
#define imetamacro_foreach_cxt_recursive1(MACRO, SEP, CONTEXT, _0) MACRO(0, CONTEXT, _0)

#define imetamacro_foreach_cxt_recursive2(MACRO, SEP, CONTEXT, _0, _1) \
imetamacro_foreach_cxt_recursive1(MACRO, SEP, CONTEXT, _0) \
SEP \
MACRO(1, CONTEXT, _1)

#define imetamacro_foreach_cxt_recursive3(MACRO, SEP, CONTEXT, _0, _1, _2) \
imetamacro_foreach_cxt_recursive2(MACRO, SEP, CONTEXT, _0, _1) \
SEP \
MACRO(2, CONTEXT, _2)

#define imetamacro_foreach_cxt_recursive4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
imetamacro_foreach_cxt_recursive3(MACRO, SEP, CONTEXT, _0, _1, _2) \
SEP \
MACRO(3, CONTEXT, _3)

#define imetamacro_foreach_cxt_recursive5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
imetamacro_foreach_cxt_recursive4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
SEP \
MACRO(4, CONTEXT, _4)

#define imetamacro_foreach_cxt_recursive6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
imetamacro_foreach_cxt_recursive5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
SEP \
MACRO(5, CONTEXT, _5)

#define imetamacro_foreach_cxt_recursive7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
imetamacro_foreach_cxt_recursive6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
SEP \
MACRO(6, CONTEXT, _6)

#define imetamacro_foreach_cxt_recursive8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
imetamacro_foreach_cxt_recursive7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
SEP \
MACRO(7, CONTEXT, _7)

#define imetamacro_foreach_cxt_recursive9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
imetamacro_foreach_cxt_recursive8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
SEP \
MACRO(8, CONTEXT, _8)

#define imetamacro_foreach_cxt_recursive10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
imetamacro_foreach_cxt_recursive9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
SEP \
MACRO(9, CONTEXT, _9)

#define imetamacro_foreach_cxt_recursive11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
imetamacro_foreach_cxt_recursive10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
SEP \
MACRO(10, CONTEXT, _10)

#define imetamacro_foreach_cxt_recursive12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
imetamacro_foreach_cxt_recursive11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
SEP \
MACRO(11, CONTEXT, _11)

#define imetamacro_foreach_cxt_recursive13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
imetamacro_foreach_cxt_recursive12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
SEP \
MACRO(12, CONTEXT, _12)

#define imetamacro_foreach_cxt_recursive14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
imetamacro_foreach_cxt_recursive13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
SEP \
MACRO(13, CONTEXT, _13)

#define imetamacro_foreach_cxt_recursive15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
imetamacro_foreach_cxt_recursive14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
SEP \
MACRO(14, CONTEXT, _14)

#define imetamacro_foreach_cxt_recursive16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
imetamacro_foreach_cxt_recursive15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
SEP \
MACRO(15, CONTEXT, _15)

#define imetamacro_foreach_cxt_recursive17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
imetamacro_foreach_cxt_recursive16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
SEP \
MACRO(16, CONTEXT, _16)

#define imetamacro_foreach_cxt_recursive18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
imetamacro_foreach_cxt_recursive17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
SEP \
MACRO(17, CONTEXT, _17)

#define imetamacro_foreach_cxt_recursive19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
imetamacro_foreach_cxt_recursive18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
SEP \
MACRO(18, CONTEXT, _18)

#define imetamacro_foreach_cxt_recursive20(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
imetamacro_foreach_cxt_recursive19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
SEP \
MACRO(19, CONTEXT, _19)

// metamacro_for_cxt expansions
#define imetamacro_for_cxt0(MACRO, SEP, CONTEXT)
#define imetamacro_for_cxt1(MACRO, SEP, CONTEXT) MACRO(0, CONTEXT)

#define imetamacro_for_cxt2(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt1(MACRO, SEP, CONTEXT) \
SEP \
MACRO(1, CONTEXT)

#define imetamacro_for_cxt3(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt2(MACRO, SEP, CONTEXT) \
SEP \
MACRO(2, CONTEXT)

#define imetamacro_for_cxt4(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt3(MACRO, SEP, CONTEXT) \
SEP \
MACRO(3, CONTEXT)

#define imetamacro_for_cxt5(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt4(MACRO, SEP, CONTEXT) \
SEP \
MACRO(4, CONTEXT)

#define imetamacro_for_cxt6(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt5(MACRO, SEP, CONTEXT) \
SEP \
MACRO(5, CONTEXT)

#define imetamacro_for_cxt7(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt6(MACRO, SEP, CONTEXT) \
SEP \
MACRO(6, CONTEXT)

#define imetamacro_for_cxt8(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt7(MACRO, SEP, CONTEXT) \
SEP \
MACRO(7, CONTEXT)

#define imetamacro_for_cxt9(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt8(MACRO, SEP, CONTEXT) \
SEP \
MACRO(8, CONTEXT)

#define imetamacro_for_cxt10(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt9(MACRO, SEP, CONTEXT) \
SEP \
MACRO(9, CONTEXT)

#define imetamacro_for_cxt11(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt10(MACRO, SEP, CONTEXT) \
SEP \
MACRO(10, CONTEXT)

#define imetamacro_for_cxt12(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt11(MACRO, SEP, CONTEXT) \
SEP \
MACRO(11, CONTEXT)

#define imetamacro_for_cxt13(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt12(MACRO, SEP, CONTEXT) \
SEP \
MACRO(12, CONTEXT)

#define imetamacro_for_cxt14(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt13(MACRO, SEP, CONTEXT) \
SEP \
MACRO(13, CONTEXT)

#define imetamacro_for_cxt15(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt14(MACRO, SEP, CONTEXT) \
SEP \
MACRO(14, CONTEXT)

#define imetamacro_for_cxt16(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt15(MACRO, SEP, CONTEXT) \
SEP \
MACRO(15, CONTEXT)

#define imetamacro_for_cxt17(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt16(MACRO, SEP, CONTEXT) \
SEP \
MACRO(16, CONTEXT)

#define imetamacro_for_cxt18(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt17(MACRO, SEP, CONTEXT) \
SEP \
MACRO(17, CONTEXT)

#define imetamacro_for_cxt19(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt18(MACRO, SEP, CONTEXT) \
SEP \
MACRO(18, CONTEXT)

#define imetamacro_for_cxt20(MACRO, SEP, CONTEXT) \
imetamacro_for_cxt19(MACRO, SEP, CONTEXT) \
SEP \
MACRO(19, CONTEXT)

// metamacro_if_eq expansions
#define imetamacro_if_eq0(VALUE) \
imetamacro_concat(imetamacro_if_eq0_, VALUE)

#define imetamacro_if_eq0_0(...) __VA_ARGS__ imetamacro_consume_
#define imetamacro_if_eq0_1(...) imetamacro_expand_
#define imetamacro_if_eq0_2(...) imetamacro_expand_
#define imetamacro_if_eq0_3(...) imetamacro_expand_
#define imetamacro_if_eq0_4(...) imetamacro_expand_
#define imetamacro_if_eq0_5(...) imetamacro_expand_
#define imetamacro_if_eq0_6(...) imetamacro_expand_
#define imetamacro_if_eq0_7(...) imetamacro_expand_
#define imetamacro_if_eq0_8(...) imetamacro_expand_
#define imetamacro_if_eq0_9(...) imetamacro_expand_
#define imetamacro_if_eq0_10(...) imetamacro_expand_
#define imetamacro_if_eq0_11(...) imetamacro_expand_
#define imetamacro_if_eq0_12(...) imetamacro_expand_
#define imetamacro_if_eq0_13(...) imetamacro_expand_
#define imetamacro_if_eq0_14(...) imetamacro_expand_
#define imetamacro_if_eq0_15(...) imetamacro_expand_
#define imetamacro_if_eq0_16(...) imetamacro_expand_
#define imetamacro_if_eq0_17(...) imetamacro_expand_
#define imetamacro_if_eq0_18(...) imetamacro_expand_
#define imetamacro_if_eq0_19(...) imetamacro_expand_
#define imetamacro_if_eq0_20(...) imetamacro_expand_

#define imetamacro_if_eq1(VALUE) imetamacro_if_eq0(imetamacro_dec(VALUE))
#define imetamacro_if_eq2(VALUE) imetamacro_if_eq1(imetamacro_dec(VALUE))
#define imetamacro_if_eq3(VALUE) imetamacro_if_eq2(imetamacro_dec(VALUE))
#define imetamacro_if_eq4(VALUE) imetamacro_if_eq3(imetamacro_dec(VALUE))
#define imetamacro_if_eq5(VALUE) imetamacro_if_eq4(imetamacro_dec(VALUE))
#define imetamacro_if_eq6(VALUE) imetamacro_if_eq5(imetamacro_dec(VALUE))
#define imetamacro_if_eq7(VALUE) imetamacro_if_eq6(imetamacro_dec(VALUE))
#define imetamacro_if_eq8(VALUE) imetamacro_if_eq7(imetamacro_dec(VALUE))
#define imetamacro_if_eq9(VALUE) imetamacro_if_eq8(imetamacro_dec(VALUE))
#define imetamacro_if_eq10(VALUE) imetamacro_if_eq9(imetamacro_dec(VALUE))
#define imetamacro_if_eq11(VALUE) imetamacro_if_eq10(imetamacro_dec(VALUE))
#define imetamacro_if_eq12(VALUE) imetamacro_if_eq11(imetamacro_dec(VALUE))
#define imetamacro_if_eq13(VALUE) imetamacro_if_eq12(imetamacro_dec(VALUE))
#define imetamacro_if_eq14(VALUE) imetamacro_if_eq13(imetamacro_dec(VALUE))
#define imetamacro_if_eq15(VALUE) imetamacro_if_eq14(imetamacro_dec(VALUE))
#define imetamacro_if_eq16(VALUE) imetamacro_if_eq15(imetamacro_dec(VALUE))
#define imetamacro_if_eq17(VALUE) imetamacro_if_eq16(imetamacro_dec(VALUE))
#define imetamacro_if_eq18(VALUE) imetamacro_if_eq17(imetamacro_dec(VALUE))
#define imetamacro_if_eq19(VALUE) imetamacro_if_eq18(imetamacro_dec(VALUE))
#define imetamacro_if_eq20(VALUE) imetamacro_if_eq19(imetamacro_dec(VALUE))

// metamacro_if_eq_recursive expansions
#define imetamacro_if_eq_recursive0(VALUE) \
imetamacro_concat(imetamacro_if_eq_recursive0_, VALUE)

#define imetamacro_if_eq_recursive0_0(...) __VA_ARGS__ imetamacro_consume_
#define imetamacro_if_eq_recursive0_1(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_2(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_3(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_4(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_5(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_6(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_7(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_8(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_9(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_10(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_11(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_12(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_13(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_14(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_15(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_16(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_17(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_18(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_19(...) imetamacro_expand_
#define imetamacro_if_eq_recursive0_20(...) imetamacro_expand_

#define imetamacro_if_eq_recursive1(VALUE) imetamacro_if_eq_recursive0(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive2(VALUE) imetamacro_if_eq_recursive1(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive3(VALUE) imetamacro_if_eq_recursive2(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive4(VALUE) imetamacro_if_eq_recursive3(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive5(VALUE) imetamacro_if_eq_recursive4(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive6(VALUE) imetamacro_if_eq_recursive5(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive7(VALUE) imetamacro_if_eq_recursive6(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive8(VALUE) imetamacro_if_eq_recursive7(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive9(VALUE) imetamacro_if_eq_recursive8(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive10(VALUE) imetamacro_if_eq_recursive9(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive11(VALUE) imetamacro_if_eq_recursive10(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive12(VALUE) imetamacro_if_eq_recursive11(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive13(VALUE) imetamacro_if_eq_recursive12(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive14(VALUE) imetamacro_if_eq_recursive13(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive15(VALUE) imetamacro_if_eq_recursive14(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive16(VALUE) imetamacro_if_eq_recursive15(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive17(VALUE) imetamacro_if_eq_recursive16(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive18(VALUE) imetamacro_if_eq_recursive17(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive19(VALUE) imetamacro_if_eq_recursive18(imetamacro_dec(VALUE))
#define imetamacro_if_eq_recursive20(VALUE) imetamacro_if_eq_recursive19(imetamacro_dec(VALUE))

// metamacro_take expansions
#define imetamacro_take0(...)
#define imetamacro_take1(...) imetamacro_head(__VA_ARGS__)
#define imetamacro_take2(...) imetamacro_head(__VA_ARGS__), imetamacro_take1(imetamacro_tail(__VA_ARGS__))
#define imetamacro_take3(...) imetamacro_head(__VA_ARGS__), imetamacro_take2(imetamacro_tail(__VA_ARGS__))
#define imetamacro_take4(...) imetamacro_head(__VA_ARGS__), imetamacro_take3(imetamacro_tail(__VA_ARGS__))
#define imetamacro_take5(...) imetamacro_head(__VA_ARGS__), imetamacro_take4(imetamacro_tail(__VA_ARGS__))
#define imetamacro_take6(...) imetamacro_head(__VA_ARGS__), imetamacro_take5(imetamacro_tail(__VA_ARGS__))
#define imetamacro_take7(...) imetamacro_head(__VA_ARGS__), imetamacro_take6(imetamacro_tail(__VA_ARGS__))
#define imetamacro_take8(...) imetamacro_head(__VA_ARGS__), imetamacro_take7(imetamacro_tail(__VA_ARGS__))
#define imetamacro_take9(...) imetamacro_head(__VA_ARGS__), imetamacro_take8(imetamacro_tail(__VA_ARGS__))
#define imetamacro_take10(...) imetamacro_head(__VA_ARGS__), imetamacro_take9(imetamacro_tail(__VA_ARGS__))
#define imetamacro_take11(...) imetamacro_head(__VA_ARGS__), imetamacro_take10(imetamacro_tail(__VA_ARGS__))
#define imetamacro_take12(...) imetamacro_head(__VA_ARGS__), imetamacro_take11(imetamacro_tail(__VA_ARGS__))
#define imetamacro_take13(...) imetamacro_head(__VA_ARGS__), imetamacro_take12(imetamacro_tail(__VA_ARGS__))
#define imetamacro_take14(...) imetamacro_head(__VA_ARGS__), imetamacro_take13(imetamacro_tail(__VA_ARGS__))
#define imetamacro_take15(...) imetamacro_head(__VA_ARGS__), imetamacro_take14(imetamacro_tail(__VA_ARGS__))
#define imetamacro_take16(...) imetamacro_head(__VA_ARGS__), imetamacro_take15(imetamacro_tail(__VA_ARGS__))
#define imetamacro_take17(...) imetamacro_head(__VA_ARGS__), imetamacro_take16(imetamacro_tail(__VA_ARGS__))
#define imetamacro_take18(...) imetamacro_head(__VA_ARGS__), imetamacro_take17(imetamacro_tail(__VA_ARGS__))
#define imetamacro_take19(...) imetamacro_head(__VA_ARGS__), imetamacro_take18(imetamacro_tail(__VA_ARGS__))
#define imetamacro_take20(...) imetamacro_head(__VA_ARGS__), imetamacro_take19(imetamacro_tail(__VA_ARGS__))

// metamacro_drop expansions
#define imetamacro_drop0(...) __VA_ARGS__
#define imetamacro_drop1(...) imetamacro_tail(__VA_ARGS__)
#define imetamacro_drop2(...) imetamacro_drop1(imetamacro_tail(__VA_ARGS__))
#define imetamacro_drop3(...) imetamacro_drop2(imetamacro_tail(__VA_ARGS__))
#define imetamacro_drop4(...) imetamacro_drop3(imetamacro_tail(__VA_ARGS__))
#define imetamacro_drop5(...) imetamacro_drop4(imetamacro_tail(__VA_ARGS__))
#define imetamacro_drop6(...) imetamacro_drop5(imetamacro_tail(__VA_ARGS__))
#define imetamacro_drop7(...) imetamacro_drop6(imetamacro_tail(__VA_ARGS__))
#define imetamacro_drop8(...) imetamacro_drop7(imetamacro_tail(__VA_ARGS__))
#define imetamacro_drop9(...) imetamacro_drop8(imetamacro_tail(__VA_ARGS__))
#define imetamacro_drop10(...) imetamacro_drop9(imetamacro_tail(__VA_ARGS__))
#define imetamacro_drop11(...) imetamacro_drop10(imetamacro_tail(__VA_ARGS__))
#define imetamacro_drop12(...) imetamacro_drop11(imetamacro_tail(__VA_ARGS__))
#define imetamacro_drop13(...) imetamacro_drop12(imetamacro_tail(__VA_ARGS__))
#define imetamacro_drop14(...) imetamacro_drop13(imetamacro_tail(__VA_ARGS__))
#define imetamacro_drop15(...) imetamacro_drop14(imetamacro_tail(__VA_ARGS__))
#define imetamacro_drop16(...) imetamacro_drop15(imetamacro_tail(__VA_ARGS__))
#define imetamacro_drop17(...) imetamacro_drop16(imetamacro_tail(__VA_ARGS__))
#define imetamacro_drop18(...) imetamacro_drop17(imetamacro_tail(__VA_ARGS__))
#define imetamacro_drop19(...) imetamacro_drop18(imetamacro_tail(__VA_ARGS__))
#define imetamacro_drop20(...) imetamacro_drop19(imetamacro_tail(__VA_ARGS__))

#endif /* __IMACRO_H_ */
