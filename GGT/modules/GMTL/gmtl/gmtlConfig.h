/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: gmtlConfig.h,v $
 * Date modified: $Date: 2002-02-22 22:28:35 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 *********************************************************** ggt-head end */
/*************************************************************** ggt-cpr beg
*
* GGT: The Generic Graphics Toolkit
* Copyright (C) 2001,2002 Allen Bierbaum
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*
 ************************************************************ ggt-cpr end */
#ifndef _GMTL_CONFIG_H
#define _GMTL_CONFIG_H

/* This should always be included first. */
//#include <gmtl/gmtlConfig.h>

#ifdef _DEBUG
#   define GMTL_DEBUG
#else
#   define GMTL_OPT
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

#define GMTL_EPS 1e-8
#define GMTL_DEG2RAD(x) ((x)*M_PI/180.0)
#define GMTL_RAD2DEG(x) ((x)*180.0/M_PI)
#define GMTL_IS_ZERO(x) (fabs(x) < GMTL_EPS)
#define GMTL_CLAMP(x,y) ((x>y)? y : x)
#define GMTL_MIN2(x,y) ((x>y)? y : x)
#define GMTL_MIN3(x,y,z) GMTL_MIN2(GMTL_MIN2(x,y),z)
#define GMTL_MIN4(w,x,y,z) GMTL_MIN2(GMTL_MIN2(w,x), GMTL_MIN2(y,z))
#define GMTL_MAX2(x,y) ((x>y)? x : y)
#define GMTL_MAX3(x,y,z) GMTL_MAX2(GMTL_MAX2(x,y),z)
#define GMTL_MAX4(w,x,y,z) GMTL_MAX2(GMTL_MAX2(w,x),GMTL_MAX2(y,z))

// -- Common GMTL classes -- //
#include <gmtl/gmtlTypes.h>
#include <gmtl/gmtlDefines.h>
#include <gmtl/Math.h>
#include <Util/Assert.h>

#endif
