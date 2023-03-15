#define LE_CAT(A, B)   A##B
#define LE_EXPAND(...) __VA_ARGS__

// Macro overloading
#define LE_VA_ARG_SIZE(...) LE_EXPAND(LE_APPLY_ARG_N((LE_ZERO_ARGS_DETECT(__VA_ARGS__), LE_RSEQ_N)))

#define LE_ZERO_ARGS_DETECT(...)                            LE_EXPAND(LE_ZERO_ARGS_DETECT_PREFIX_##__VA_ARGS__##_ZERO_ARGS_DETECT_SUFFIX)
#define LE_ZERO_ARGS_DETECT_PREFIX__ZERO_ARGS_DETECT_SUFFIX , , , , , , , , , , , 0

#define LE_APPLY_ARG_N(ARGS)                                          LE_EXPAND(LE_ARG_N ARGS)
#define LE_ARG_N(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define LE_RSEQ_N                                                     11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define LE_OVERLOAD_SELECT(NAME, NUM) LE_CAT(NAME##_, NUM)
#define LE_MACRO_OVERLOAD(NAME, ...)  LE_OVERLOAD_SELECT(NAME, LE_VA_ARG_SIZE(__VA_ARGS__))(__VA_ARGS__)
