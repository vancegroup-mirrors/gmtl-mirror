#ifndef GFX_ASSERT_H
#define GFX_ASSERT_H

#include <gfxConfig.h>


// -- VERY simple assertion stuff -- //
#ifdef GFX_DEBUG
#   include <assert.h>
#   define gfxASSERT(val) assert((val))
#else
#   define gfxASSERT(val) ((void)0)
#endif


#endif
