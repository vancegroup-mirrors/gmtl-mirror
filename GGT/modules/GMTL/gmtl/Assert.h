#ifndef GMTL_ASSERT_H
#define GMTL_ASSERT_H

// -- VERY simple assertion stuff -- //
#ifdef _DEBUG
#   include <assert.h>
#   define gmtlASSERT(val) assert((val))
#else
#   define gmtlASSERT(val) ((void)0)
#endif


#endif
