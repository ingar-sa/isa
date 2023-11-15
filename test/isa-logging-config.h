
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
