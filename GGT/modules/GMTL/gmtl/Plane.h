/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Plane.h,v $
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
#ifndef _GMTL_PLANE_H
#define _GMTL_PLANE_H

#include <gmtl/Vec3.h>
#include <gmtl/Point3.h>
#include <gmtl/matVecFuncs.h>

namespace gmtl
{

//
// Plane: Defines a geometrical plane.
//
// All points on the plane satify the equation dot(Pt,Normal) = offset
// normal is assumed to be normalized
//
// NOTE: Some plane implementation store D instead of offset.  Thus
//      those implementation have opposite sign from what we have
//
// pg. 309 Computer Graphics 2nd Edition Hearn Baker
// N dot P = -D
//  |
//  |-d-|
//__|___|-->N
//  |   |
class Plane
{
public:
   // Which side of the plane are we on
   // POS_SIDE: Side that the normal points
   // NEG_SIDE: Side away from the normal
   enum Side
   {
      ON_PLANE,
      POS_SIDE,
      NEG_SIDE
   };

public:
	// Constructors
   Plane();
	Plane(const Point3& pt1, const Point3& pt2, const Point3& pt3);
	Plane(const Vec3& norm, const Point3& _pt);
   Plane(const Vec3& norm, float dPlaneConst);

   Plane(const Plane& plane);
		
	// Helper distance functions
   float distanceToPt(const Point3& pt) const;

   Side whichSide(const Point3& pt) const;
   inline Side whichSide(const Point3& pt, const float& eps) const;

   //: Find nearest pt on the plane
	//! RETURN: distance to the point
	//+ If d is positive, pt lies on same side as normal
	//+ If d is negative, pt lies on opposite side from normal
	//+ if d is "near" zero, pt is on the plane
	float findNearestPt(const Point3& pt, Point3& nearPt) const;
	
public:
   // dot(Pt,mNorm) = mOffset
   // NOTE: mOffset = -D (neg dist from origin)
	Vec3    mNorm;       // The normal
	float   mOffset;     // offset
};


Plane::Plane()
{;}

Plane::Plane(const Vec3& norm, float dPlaneConst)
{
   mNorm = norm;
   mOffset = dPlaneConst;
}

/// Create a plane containing the given points.
 Plane::Plane(const Point3& pt1, const Point3& pt2, const Point3& pt3)
{
    Vec3 vec12(pt2-pt1);
    Vec3 vec13(pt3-pt1);

    mNorm = vec12.cross(vec13);
    mNorm.normalize();

    mOffset = pt1.dot(mNorm);	// Graphics Gems I: Page 390
}

Plane::Plane(const Vec3& norm, const Point3& _pt)
{
    mNorm = norm;
    mOffset = _pt.dot(norm);
}

Plane::Plane(const Plane& plane)
{
   mNorm = plane.mNorm;
   mOffset = plane.mOffset;
}

inline
float Plane::distanceToPt(const Point3& pt) const
{
   return mNorm.dot(pt) - mOffset;
}

inline
Plane::Side Plane::whichSide(const Point3& pt) const
{
   float dist = distanceToPt(pt);

   if(dist < 0.0f)
      return Plane::NEG_SIDE;
   else if(dist > 0.0f)
      return Plane::POS_SIDE;

   return Plane::ON_PLANE;
}

inline
Plane::Side Plane::whichSide(const Point3& pt, const float& eps) const
{
   float dist = distanceToPt(pt);

   if(dist < eps)
      return Plane::NEG_SIDE;
   else if(dist > eps)
      return Plane::POS_SIDE;

   return Plane::ON_PLANE;
}


// Finds the point on the plane nearest to pt.
// Returns the nearest point in nearPt
inline
float Plane::findNearestPt(const Point3& pt, Point3& nearPt) const
{
   // GGI: P 297
	// GGII: Pg 223
	gfxASSERT(mNorm.isNormalized());		   // Assert: Normalized
	float dist_to_plane(0.0);
	dist_to_plane = mOffset + mNorm.dot(pt);		// Distance to plane
	nearPt = pt - (mNorm*dist_to_plane);
	return dist_to_plane;
}

/*
#include <geomdist.h>


// Intersects the plane with a given segment.
// Returns TRUE if there is a hit (within the seg).
// Also returns the distance "down" the segment of the hit in t.
//
// PRE: seg.dir must be normalized
//
int sgPlane::isect(sgSeg& seg, float* t)
{
	// Graphic Gems I: Page 391
	float denom = normal.dot(seg.dir);
	if (SG_IS_ZERO(denom))		// No Hit
	{
		//: So now, it is just dist to plane tested against length
		sgVec3	hit_pt;
		float		hit_dist;		// Dist to hit
		
		hit_dist = findNearestPt(seg.pos, hit_pt);
		*t = hit_dist;			// Since dir is normalized

		if(seg.tValueOnSeg(*t))
			return 1;
		else
			return 0;
	}
	else
	{
		float numer = offset + normal.dot(seg.pos);
		(*t) = -1.0f * (numer/denom);
		
		if(seg.tValueOnSeg(*t))
			return 1;
		else
			return 0;
	}
}

///
 // Intersects the plane with the line defined
 // by the given segment
 //
 // seg - seg that represents the line to isect
 // t   - the t value of the isect
 //
int sgPlane::isectLine(const sgSeg& seg, float* t)
{
	// GGI: Pg 299
	// Lu = seg.pos;
	// Lv = seg.dir;
	// Jn = normal;
	// Jd = offset;
	
	float denom = normal.dot(seg.dir);
	if(denom == 0.0f)
      return 0;
	else
	{
      *t = - (offset+ normal.dot(seg.pos))/(denom);
      return 1;
	}
}
*/

}
#endif
