#ifndef _GFX_CONFIG_H_
#define _GFX_CONFIG_H_

/*
 * ----------------------------------------------------------------------------
 * This file (gfxConfig) includes header files common to most, if not all,
 * files in the Vgfx source tree.  It must be included at the top of
 * every .h and .cpp file before any other headers because it includes system
 * headers.
 * ----------------------------------------------------------------------------
 */

/* This should always be included first. */
#include <gfx_defines.h>

#ifdef _DEBUG
#   define GFX_DEBUG
#else
#   define GFX_OPT
#endif

#ifdef WIN32
/* Exclude rarely-used stuff from Windows headers */
#define WIN32_LEAN_AND_MEAN

#pragma warning(disable:4244)	/* Converting double to float */
#pragma warning(disable:4800)	/* Int forcing value to bool */
#pragma warning(disable:4101)	/* unreferenced local variable */

/* identifier truncated to 255 characters in the debug information */
#pragma warning(disable:4786)

#include <windows.h>

#ifndef HAVE_STRCASECMP
#define strcasecmp _stricmp
#endif

#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#define M_PI_4 0.78539816339744830962

/* extern HINSTANCE g_hInst = NULL; */
#endif   /* WIN32 */


/* Common C++ includes. */
/* Put here for pre-compiled headers. */
#ifdef __cplusplus
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <math.h>

#endif   /* __cplusplus */

#if 0
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

/* --- Macros ---- */

/* Define this macro to replace calls to sleep(3) if it is not avialable. */
#ifndef HAVE_SLEEP
#   define sleep(x) (Sleep(x * 1000))        /* Win32-specific */
#endif

/* Define this macro to replace calls to usleep(3) if it is not avialable. */
#ifndef HAVE_USLEEP
#   define usleep(x) (Sleep(x / 1000))       /* Win32-specific */
#endif

#ifndef HAVE_SINF
#   define sinf(x) ((float) sin(x))
#endif

#ifndef HAVE_ASINF
#   define asinf(x) ((float) asin(x))
#endif

#ifndef HAVE_ACOSF
#   define acosf(x) ((float) acos(x))
#endif

#ifndef HAVE_ATAN2F
#   define atan2f(x, y) ((float) atan2(x, y))
#endif

#ifndef HAVE_SQRTF
#   define sqrtf(x) ((float) sqrt(x))
#endif

#endif // if 0

#define GFX_EPS 1e-8
#define GFX_DEG2RAD(x) ((x)*M_PI/180.0)
#define GFX_RAD2DEG(x) ((x)*180.0/M_PI)
#define GFX_ZERO_CLAMP(x) ((fabs(x) < GFX_EPS)? 0.0f : x)
#define GFX_IS_ZERO(x) (fabs(x) < GFX_EPS)
#define GFX_CLAMP(x,y) ((x>y)? y : x)
#define GFX_MIN2(x,y) ((x>y)? y : x)
#define GFX_MIN3(x,y,z) GFX_MIN2(GFX_MIN2(x,y),z)
#define GFX_MIN4(w,x,y,z) GFX_MIN2(GFX_MIN2(w,x), GFX_MIN2(y,z))
#define GFX_MAX2(x,y) ((x>y)? x : y)
#define GFX_MAX3(x,y,z) GFX_MAX2(GFX_MAX2(x,y),z)
#define GFX_MAX4(w,x,y,z) GFX_MAX2(GFX_MAX2(w,x),GFX_MAX2(y,z))


#endif   /* _GFX_CONFIG_H_ */
