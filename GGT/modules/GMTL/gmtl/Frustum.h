/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Benjamin Schulz
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Frustum.h,v $
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

#ifndef _GMTL_FRUSTUM_H_
#define _GMTL_FRUSTUM_H_

#include <gmtl/Plane.h>


namespace gmtl
{
	template <class DATA_TYPE>
	class Frustum
	{
		public:
			typedef DATA_TYPE DataType;
			typedef Frustum<DATA_TYPE> FrustumType;

		public:
			Frustum()
			{
			
			}

			Frustum(const gmtl::Matrix44f & projMatrix)
			{
				this->extractPlanes(projMatrix);
			}

			Frustum(const gmtl::Matrix44f & modelviewMatrix, const gmtl::Matrix44f & projMatrix)
			{
				this->extractPlanes(modelviewMatrix, projMatrix);
			}

			void extractPlanes(const gmtl::Matrix44f & modelviewMatrix, const gmtl::Matrix44f & projMatrix)
			{
				//this->extractPlanes(M);
				gmtl::Matrix44f M;

				float clip[16];
				const float * modl = modelviewMatrix.getData();
				const float * proj = projMatrix.getData();

				clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
				clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
				clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
				clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

				clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
				clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
				clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
				clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

				clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
				clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
				clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
				clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

				clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
				clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
				clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
				clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];

				M.set(clip);
				this->extractPlanes(M);
			}

			void extractPlanes(const gmtl::Matrix44f & projMatrix)
			{
				const gmtl::Matrix44f & m = projMatrix;
				
				//left
				this->m_planes[0].setNormal( gmtl::Vec3f( m[3][0] + m[0][0], m[3][1] + m[0][1], m[3][2] + m[0][2] ) );
				this->m_planes[0].setOffset(m[3][3] + m[0][3]);
				//right
				this->m_planes[1].setNormal( gmtl::Vec3f( m[3][0] - m[0][0], m[3][1] - m[0][1], m[3][2] - m[0][2] ) );
				this->m_planes[1].setOffset(m[3][3] - m[0][3]);
				//bottom
				this->m_planes[2].setNormal( gmtl::Vec3f( m[3][0] + m[1][0], m[3][1] + m[1][1], m[3][2] + m[1][2] ) );
				this->m_planes[2].setOffset(m[3][3] + m[1][3]);
				//top
				this->m_planes[3].setNormal( gmtl::Vec3f( m[3][0] - m[1][0], m[3][1] - m[1][1], m[3][2] - m[1][2] ) );
				this->m_planes[3].setOffset(m[3][3] - m[1][3]);
				//near
				this->m_planes[4].setNormal( gmtl::Vec3f( m[3][0] + m[2][0], m[3][1] + m[2][1], m[3][2] + m[2][2] ) );
				this->m_planes[4].setOffset(m[2][3] + m[3][3]);
				//far
				this->m_planes[5].setNormal( gmtl::Vec3f( m[3][0] - m[2][0], m[3][1] - m[2][1], m[3][2] - m[2][2] ) );
				this->m_planes[5].setOffset(m[3][3] - m[2][3]);
			}

			gmtl::Plane<DATA_TYPE> m_planes[6];
	};

    typedef Frustum<float> Frustumf;
    typedef Frustum<double> Frustumd;
}


#endif /* _GMTL_FRUSTUM_H_ */
