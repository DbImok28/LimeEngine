// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once

#define LE_CAT(A, B)   A##B
#define LE_EXPAND(...) __VA_ARGS__

#define LE_REQUIRE_SEMICOLON (void)0

// Macro if

#define LE_IF_NORM(VALUE, TRUE_EXPR, FALSE_EXPR) LE_IF(LE_IS_TRUE(VALUE), TRUE_EXPR, FALSE_EXPR)
#define LE_IF(VALUE, TRUE_EXPR, FALSE_EXPR)      LE_CAT(LE_IF_, VALUE)(TRUE_EXPR, FALSE_EXPR)
#define LE_IF_0(TRUE_EXPR, FALSE_EXPR)           FALSE_EXPR
#define LE_IF_1(TRUE_EXPR, FALSE_EXPR)           TRUE_EXPR

// True if the value is between 1 and 16, false if 0
#define LE_IS_TRUE(VALUE) LE_CAT(LE_IS_TRUE_, VALUE)()

#define LE_IS_TRUE_0()  0
#define LE_IS_TRUE_1()  1
#define LE_IS_TRUE_2()  1
#define LE_IS_TRUE_3()  1
#define LE_IS_TRUE_4()  1
#define LE_IS_TRUE_5()  1
#define LE_IS_TRUE_6()  1
#define LE_IS_TRUE_7()  1
#define LE_IS_TRUE_8()  1
#define LE_IS_TRUE_9()  1
#define LE_IS_TRUE_10() 1
#define LE_IS_TRUE_11() 1
#define LE_IS_TRUE_12() 1
#define LE_IS_TRUE_13() 1
#define LE_IS_TRUE_14() 1
#define LE_IS_TRUE_15() 1
#define LE_IS_TRUE_16() 1

// Macro arg counting

#define LE_VA_ARG_SIZE(...) LE_EXPAND(LE_APPLY_ARG_N((LE_ZERO_ARGS_DETECT(__VA_ARGS__), LE_RSEQ_N)))

#define LE_ZERO_ARGS_DETECT(...)                            LE_EXPAND(LE_ZERO_ARGS_DETECT_PREFIX_##__VA_ARGS__##_ZERO_ARGS_DETECT_SUFFIX)
#define LE_ZERO_ARGS_DETECT_PREFIX__ZERO_ARGS_DETECT_SUFFIX , , , , , , , , , , , 0

#define LE_APPLY_ARG_N(ARGS)                                          LE_EXPAND(LE_ARG_N ARGS)
#define LE_ARG_N(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define LE_RSEQ_N                                                     11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define LE_VA_ARG_IS_EMPTY(...)                  LE_IF_NORM(LE_VA_ARG_IS_NOT_EMPTY(__VA_ARGS__), 0, 1)
#define LE_VA_ARG_IS_NOT_EMPTY(...)              LE_IS_TRUE(LE_VA_ARG_SIZE(__VA_ARGS__))
#define LE_VA_ARG_SIZE_IS_MORE_THEN_ONE(_0, ...) LE_VA_ARG_IS_NOT_EMPTY(__VA_ARGS__)

// Macro overloading

#define LE_OVERLOAD_SELECT(NAME, NUM) LE_CAT(NAME##_, NUM)

#define LE_MACRO_OVERLOAD(NAME, ...)              LE_OVERLOAD_SELECT(NAME, LE_VA_ARG_SIZE(__VA_ARGS__))(__VA_ARGS__)
#define LE_MACRO_OVERLOAD_ONE_OR_MANY(NAME, ...)  LE_OVERLOAD_SELECT(NAME, LE_IF(LE_VA_ARG_SIZE_IS_MORE_THEN_ONE(__VA_ARGS__), MANY, 1))(__VA_ARGS__)
#define LE_MACRO_OVERLOAD_IF(NAME, SELECTOR, ...) LE_OVERLOAD_SELECT(NAME, SELECTOR(__VA_ARGS__))(__VA_ARGS__)
