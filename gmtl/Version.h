/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Version.h,v $
 * Date modified: $Date: 2004-10-27 19:01:31 $
 * Version:       $Revision: 1.29 $
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
#ifndef _GMTL_VERSION_H_
#define _GMTL_VERSION_H_

/**
 * This file contains two useful items.
 *    1. The preprocessor friendly GMTL_VERSION "string". It is in the form
 *       <major><minor><patch> where each part has exactly 3 digits.
 *    2. The C++ friendly variable, version, that contains the version as a
 *       string. It is in the form of <major>.<minor>.<patch> where each part
 *       has anywhere from 1 to 3 digits.
 */

/**
 * This is the "human-readable" GMTL version _string_. It is of the form
 * <major><minor><patch>. Each part has exactly 3 digits.
 */
// The major/minor/patch version (up to 3 digits each).
#define GMTL_VERSION_MAJOR    0
#define GMTL_VERSION_MINOR    4
#define GMTL_VERSION_PATCH    2

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// To update the version number, do not modify anything below this line!!!!
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// Define the helper macros
//--------------------------------------------------------------------------

// These helper macros are used build up the GMTL_VERSION macro
#define GMTL_GLUE(a,b)        a ## b
#define GMTL_XGLUE(a,b)       GMTL_GLUE(a,b)

// These helper macros are used to stringify a given macro
#define GMTL_STR(s)           # s
#define GMTL_XSTR(s)          GMTL_STR(s)

// These helper macros are used to build up the GMTL_VERSION_STRING macro.
#define GMTL_DOT(a,b)         a ## . ## b
#define GMTL_XDOT(a,b)        GMTL_DOT(a,b)

// These helpr macros are used to facilitate a zero left fill
#define GMTL_ZEROFILL(a)      0 ## a
#define GMTL_XZEROFILL(a)     GMTL_ZEROFILL(a)

// Fix up the major version by doing a zero left fill
#if GMTL_VERSION_MAJOR < 10
#  define GMTL_VERSION_MAJOR_FILLED \
               GMTL_XZEROFILL(GMTL_XZEROFILL(GMTL_VERSION_MAJOR))
#elif GMTL_VERSION_MAJOR < 100
#  define GMTL_VERSION_MAJOR_FILLED GMTL_XZEROFILL(GMTL_VERSION_MAJOR)
#else
#  define GMTL_VERSION_MAJOR_FILLED GMTL_VERSION_MAJOR
#endif

// Fix up the minor version by doing a zero left fill
#if GMTL_VERSION_MINOR < 10
#  define GMTL_VERSION_MINOR_FILLED \
               GMTL_XZEROFILL(GMTL_XZEROFILL(GMTL_VERSION_MINOR))
#elif GMTL_VERSION_MINOR < 100
#  define GMTL_VERSION_MINOR_FILLED GMTL_XZEROFILL(GMTL_VERSION_MINOR)
#else
#  define GMTL_VERSION_MINOR_FILLED GMTL_VERSION_MINOR
#endif

// Fix up the patch version by doing a zero left fill
#if GMTL_VERSION_PATCH < 10
#  define GMTL_VERSION_PATCH_FILLED \
               GMTL_XZEROFILL(GMTL_XZEROFILL(GMTL_VERSION_PATCH))
#elif GMTL_VERSION_PATCH < 100
#  define GMTL_VERSION_PATCH_FILLED GMTL_XZEROFILL(GMTL_VERSION_PATCH)
#else
#  define GMTL_VERSION_PATCH_FILLED GMTL_VERSION_PATCH
#endif

//--------------------------------------------------------------------------
// Define the GMTL_VERSION and GMTL_VERSION_STRING macros
//--------------------------------------------------------------------------

// Build up the GMTL_VERSION macro by pasting the individual parts together
/**
 * The is the preprocessor-friendly version string. It is in the form of
 * <major><minor><patch>. Each part has exactly 3 digits.
 */
#define GMTL_VERSION \
   GMTL_XGLUE( \
      GMTL_XGLUE(GMTL_VERSION_MAJOR_FILLED, GMTL_VERSION_MINOR_FILLED), \
      GMTL_VERSION_PATCH_FILLED \
   )

// Create the GMTL_VERSION_STRING macro
#define GMTL_VERSION_STRING \
   GMTL_XDOT( \
      GMTL_XDOT(GMTL_VERSION_MAJOR, GMTL_VERSION_MINOR), \
      GMTL_VERSION_PATCH \
   )

//--------------------------------------------------------------------------
// Declare a version string constant that can be used at runtime.
//--------------------------------------------------------------------------
namespace gmtl
{
   inline const char* getVersion()
   {
      return GMTL_XSTR(GMTL_VERSION_STRING);
   }
} // end namespace gmtl

//--------------------------------------------------------------------------
// Cleanup after ourselves and undef all internal macros.
//--------------------------------------------------------------------------

// Undef the all helper macros
#undef GMTL_XGLUE
#undef GMTL_GLUE
#undef GMTL_XSTR
#undef GMTL_STR
#undef GMTL_ZEROFILL
#undef GMTL_XZEROFILL
#undef GMTL_XDOT
#undef GMTL_DOT

// Undef the GMTL_VERSION_STRING temporary macro
#undef GMTL_VERSION_STRING

// Undef the XXX_FILLED temporary macros
#undef GMTL_VERSION_MAJOR_FILLED
#undef GMTL_VERSION_MINOR_FILLED
#undef GMTL_VERSION_PATCH_FILLED

// Undef the macro for each version part
#undef GMTL_VERSION_MAJOR
#undef GMTL_VERSION_MINOR
#undef GMTL_VERSION_PATCH

#endif
