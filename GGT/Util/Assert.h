#ifndef GGT_ASSERT_H
#define GGT_ASSERT_H

#include <gmtl/gmtlConfig.h>


// -- VERY simple assertion stuff -- //
#ifdef _DEBUG
#   include <assert.h>
#   define ggtASSERT(val) assert((val))
#else
#   define ggtASSERT(val) ((void)0)
#endif


#endif
