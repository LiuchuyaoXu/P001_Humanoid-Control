#define DEBUG 1

#define DEBUG_PRINT(fmt, ...) \
            do { if (DEBUG) printf(fmt, __VA_ARGS__); } while (0)
        