/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Benjamin Schulz
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: FrustumOps.h,v $
 * Date modified: $Date: 2007-03-02 02:19:35 $
 * Version:       $Revision: 1.1 $
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

#ifndef _GMTL_FRUSTUM_OPS_H_
#define _GMTL_FRUSTUM_OPS_H_

#include <gmtl/Frustum.h>
#include <gmtl/PlaneOps.h>


namespace gmtl
{
	const unsigned int IN_FRONT_OFF_ALL_PLANES = 6;

	template<class DATA_TYPE>
	void normalize(Frustum<DATA_TYPE>& f)
	{
		unsigned int i = 0;
		for (; i < 6; i++)
		{
			Vec<DATA_TYPE, 3> n = f.m_planes[i].getNormal();
            DATA_TYPE o = f.m_planes[i].getOffset();
			DATA_TYPE len = Math::sqrt( n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
			n[0] /= len;
			n[1] /= len;
			n[2] /= len;
			o /= len;
            f.m_planes[i].setNormal(n);
			f.m_planes[i].setOffset(o);
		}
	}

	template<typename T>
	inline bool isInVolume(const Frustum<T> & f, const Point<T,3> & p, unsigned int & idx /*out*/)
	{
		unsigned int i = 0;
		for (; i < 6; i++)
		{
			T dist = dot(f.m_planes[i].mNorm, static_cast< Vec<T, 3> >(p)) + f.m_planes[i].mOffset;
			if (dist < T(0.0) )
			{
				idx = i;
				return false;
			}
		}
        
		idx = IN_FRONT_OFF_ALL_PLANES;
		return true;
	}

	template<typename T>
	inline bool isInVolume(const Frustum<T> & f, const Sphere<T> & s)
	{
		unsigned int i = 0;
		for (; i < 6; i++)
		{
			T dist = dot(f.m_planes[i].mNorm, static_cast< Vec<T, 3> >(s.getCenter())) + f.m_planes[i].mOffset;
			if (dist <= -T(s.getRadius()) )
				return false;
		}

		return true;
	}

	template<typename T>
	inline bool isInVolume(const Frustum<T> & f, const AABox<T> & box)
	{
		const Point3f & min = box.getMin();
		const Point3f & max = box.getMax();
		Point3f p[8];
		p[0] = min;
		p[1] = max;
		p[2] = Point3f(max[0], min[1], min[2]);
		p[3] = Point3f(min[0], max[1], min[2]);
		p[4] = Point3f(min[0], min[1], max[2]);
		p[5] = Point3f(max[0], max[1], min[2]);
		p[6] = Point3f(min[0], max[1], max[2]);
		p[7] = Point3f(max[0], min[1], max[2]);

		unsigned int idx = 6;

		if (isInVolume(f, p[0], idx))
			return true;

		//now we have the index of the seperating plane int idx, so check if all other points
		//lie on the backside of this plane too

		unsigned int i = 0;
		for (i = 1; i < 8; i++)
		{
			T dist = dot(f.m_planes[idx].mNorm, static_cast< Vec<T, 3> >(p[i])) + f.m_planes[idx].mOffset;		
			if (dist > T(0.0))
				return true;
		}
		
		return false;
	}

	template<typename T>
	inline bool isInVolume(const Frustum<T> & f, const Tri<T> & tri)
	{
		if (isInVolume(f, tri[0]) )
			return true;

		if (isInVolume(f, tri[1]) )
			return true;

		if (isInVolume(f, tri[2]) )
			return true;

		return false;
	}


}


#endif /* _GMTL_FRUSTUM_OPS_H_ */
