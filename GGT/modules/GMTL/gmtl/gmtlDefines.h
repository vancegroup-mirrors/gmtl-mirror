/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: gmtlDefines.h,v $
 * Date modified: $Date: 2002-01-18 20:43:12 $
 * Version:       $Revision: 1.1.1.1 $
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
#ifndef _GMTL_DEFINES_H
#define _GMTL_DEFINES_H

#include <gfxConfig.h>
#include <GMTL/gmtlTypes.h>
#include <iostream>
#include <GMTL/Math.h>

#include <Util/Assert.h>

namespace gmtl
{
   enum vecIdx { Xelt=0, Yelt=1, Zelt=2, Welt=3 };



   const float GMTL_EPSILON = 1.0e-6f;
   const float GMTL_MAT_EQUAL_EPSILON = 0.001f;      // Epsilon for matrices to be equal
   const float GMTL_VEC_EQUAL_EPSILON = 0.0001f;      // Epsilon for vectors to be equal

#define GMTL_ZERO_CLAMP(x) ((fabs(x) < GMTL_EPSILON)? 0.0f : x)
#define GMTL_NEAR(x,y,eps) (gmtl::Math::abs((x)-(y))<(eps))

};


#endif
