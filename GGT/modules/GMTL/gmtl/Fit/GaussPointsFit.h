/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: GaussPointsFit.h,v $
 * Date modified: $Date: 2002-01-26 23:47:53 $
 * Version:       $Revision: 1.2 $
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
// Based on code from:
// Magic Software, Inc.
// http://www.magic-software.com
//
#ifndef _GMTL_GAUSSPOINTSFIT_H
#define _GMTL_GAUSSPOINTSFIT_H

// Fit points with a Gaussian distribution.  The center is the mean of the
// points, the axes are the eigenvectors of the covariance matrix, and the
// extents are the eigenvalues of the covariance matrix and are returned in
// increasing order.  The last two functions allow selection of valid
// vertices from a pool.  The return value is 'true' if and only if at least
// one vertex was valid.

#include <gmtl/Vec3.h>
#include <gmtl/Point3.h>

namespace gmtl
{

/*
void MgcGaussPointsFit (int iQuantity, const MgcVector2* akPoint,
    MgcVector2& rkCenter, MgcVector2 akAxis[2], MgcReal afExtent[2]);
*/

void GaussPointsFit (int iQuantity, const Point3* akPoint,
    Point3& rkCenter, Vec3 akAxis[3], float afExtent[3]);

/*
bool MgcGaussPointsFit (int iQuantity, const MgcVector2* akPoint,
    const bool* abValid, MgcVector2& rkCenter, MgcVector2 akAxis[2],
    MgcReal afExtent[2]);
*/

bool GaussPointsFit (int iQuantity, const Vec3* akPoint,
    const bool* abValid, Vec3& rkCenter, Vec3 akAxis[3],
    float afExtent[3]);
	
};

#endif
