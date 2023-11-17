#ifndef ISA_LOGGING_H

/*
    TOOO(ingar): Make functions for the logging part and change the macros to call those.
*/

#include <stdio.h>
#include <assert.h>

#if !defined(ISA_LOGGING_CUSTOM_CONFIG)
#if !defined(NDEBUG)

#define MEM_TRACE 1
#define MEM_LOG 1
#define ISA_ASSERT_TRACE 1
#define ISA_ASSERT_ON_LOG_ERROR 1

#define ISA_DO_LOG_INFO 1
#define ISA_DO_LOG_ERROR 1
#define ISA_DO_LOG_DEBUG 1

#define ISA_ALL_INFO_TRACE 0
#define ISA_ALL_ERROR_TRACE 0
#define ISA_ALL_DEBUG_TRACE 0

#define ISA_NO_INFO_TRACE 0
#define ISA_NO_ERROR_TRACE 0
#define ISA_NO_DEBUG_TRACE 0

#else //NDEBUG

#define MEM_TRACE 0
#define MEM_LOG 0
#define ISA_ASSERT_TRACE 0
#define ISA_ASSERT_ON_LOG_ERROR 0

#define ISA_DO_LOG_INFO 0
#define ISA_DO_LOG_ERROR 0
#define ISA_DO_LOG_DEBUG 0

#define ISA_ALL_INFO_TRACE 0
#define ISA_ALL_ERROR_TRACE 0
#define ISA_ALL_DEBUG_TRACE 0

#define ISA_NO_INFO_TRACE 0
#define ISA_NO_ERROR_TRACE 0
#define ISA_NO_DEBUG_TRACE 0

#endif //NDEBUG
#endif //ISA_LOGGING_CUSTOM_CONFIG

bool
ISA__AssertTrace(bool Expression, const char *ExpressionString, int Line, const char *Function, const char *File)
{
    printf("ASSERTION: In %s on line %d in %s:\n\n" 
           "\t-> Assertion on expression \"%s\"\n", Function, Line, File, ExpressionString);
    assert(Expression);
    return true;
}

#if ISA_ASSERT_ON_LOG_ERROR
#define ISA_ErrAssert(Expression) assert(Expression)
#else
#define ISA_ErrAssert(Expression) ((void)0)
#endif

#if ISA_DO_LOG_INFO
#if ISA_ALL_INFO_TRACE
#define ISA_LOG_INFO(...) ISA_LOG_INFO_TRACE(__VA_ARGS__)
#else
#define ISA_LOG_INFO(...) \
    do { \
        printf("INFO: "); \
        printf( __VA_ARGS__); \
        printf("\n"); \
    } while (0)
#endif // ISA_ALL_INFO_TRACE

#if ISA_NO_INFO_TRACE
#define ISA_LOG_INFO_TRACE(...) ISA_LOG_INFO(__VA_ARGS__)
#else
#define ISA_LOG_INFO_TRACE(...) \
    do { \
        printf("INFO: In %s on line %d in %s:\n\n\t-> ", __func__, __LINE__, __FILE__); \
        printf(__VA_ARGS__); \
        printf("\n"); \
    } while (0)
#endif // ISA_NO_INFO_TRACE
#else
#define ISA_LOG_INFO(...) ((void)0)
#define ISA_LOG_INFO_TRACE(...) ((void)0)
#endif // ISA_DO_LOG_INFO

#if ISA_DO_LOG_ERROR
#if ISA_ALL_ERROR_TRACE
#define ISA_LOG_ERROR(...) ISA_LOG_ERROR_TRACE(__VA_ARGS__)
#else
#define ISA_LOG_ERROR(...) \
    do { \
        printf("ERROR: "); \
        fprintf(stderr, __VA_ARGS__); \
        fprintf(stderr, "\n"); \
        ISA_ErrAssert(false); \
    } while (0)
#endif // ISA_ALL_ERROR_TRACE

#if ISA_NO_ERROR_TRACE
#define ISA_LOG_ERROR_TRACE(...) ISA_LOG_ERROR(__VA_ARGS__)
#else
#define ISA_LOG_ERROR_TRACE(...) \
    do { \
        fprintf(stderr, "ERROR: In %s on line %d in %s:\n\n\t-> ", __func__, __LINE__, __FILE__); \
        fprintf(stderr, __VA_ARGS__); \
        fprintf(stderr, "\n"); \
        ISA_ErrAssert(false); \
    } while (0)
#endif // ISA_NO_ERROR_TRACE
#else
#define ISA_LOG_ERROR_TRACE(...) ((void)0)
#define ISA_LOG_ERROR(...) ((void)0)
#endif // ISA_DO_LOG_ERROR

#if ISA_DO_LOG_DEBUG
#if ISA_ALL_DEBUG_TRACE
#define ISA_LOG_DEBUG(...) ISA_LOG_DEBUG_TRACE(__VA_ARGS__)
#else
#define ISA_LOG_DEBUG(...) \
    do { \
        printf("DEBUG: "); \
        printf(__VA_ARGS__); \
        printf("\n"); \
    } while (0)
#endif

#if ISA_NO_DEBUG_TRACE
#define ISA_LOG_DEBUG_TRACE(...) ISA_LOG_DEBUG(__VA_ARGS__)
#else
#define ISA_LOG_DEBUG_TRACE(...) \
    do { \
        printf("DEBUG: In %s on line %d in %s:\n\n\t-> ", __func__, __LINE__, __FILE__); \
        printf(__VA_ARGS__); \
        printf("\n"); \
    } while (0);
#endif // ISA_NO_DEBUG_TRACE
#else
#define ISA_LOG_DEBUG_TRACE(...) ((void)0)
#define ISA_LOG_DEBUG(...) ((void)0)
#endif // ISA_DO_LOG_DEBUG

#if ISA_ASSERT_TRACE
#define assert(Expression) ISA__AssertTrace(Expression, #Expression, __LINE__, __func__, __FILE__)
#else
#define assert(Expression) assert(Expression)
#endif

#define ISA_LOGGING_H
#endif