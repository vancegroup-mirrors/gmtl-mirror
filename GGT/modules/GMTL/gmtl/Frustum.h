/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 * Benjamin Schulz
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Frustum.h,v $
 * Date modified: $Date: 2007-03-03 16:06:53 $
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

#ifndef _GMTL_FRUSTUM_H_
#define _GMTL_FRUSTUM_H_

#include <gmtl/Plane.h>


namespace gmtl
{
	/**
	* This class defines a View Frustum Volume as a set of 6 planes
	*
	* @ingroup Types
	*/
	template <class DATA_TYPE>
	class Frustum
	{
		public:
			typedef DATA_TYPE DataType;
			typedef Frustum<DATA_TYPE> FrustumType;

			/** An enum to name the plane indicies. 
			*  To have you not must remember those numbers
			*/
			enum PlaneNames
			{
				PLANE_LEFT = 0,		/**< left	clipping plane equals 0 */
				PLANE_RIGHT = 1,	/**< right	clipping plane equals 1 */
				PLANE_BOTTOM = 2,	/**< bottom	clipping plane equals 2 */
				PLANE_TOP = 3,		/**< top	clipping plane equals 3 */
				PLANE_NEAR = 4,		/**< near	clipping plane equals 4 */
				PLANE_FAR = 5		/**< far	clipping plane equals 5 */
			};

			/**
			* Constructs a new frustum with all planes in default state
			*/
			Frustum()
			{
			
			}

			/**
			* Constructs a new frustum with the given projection matrix.
			*
			* @param projMatrix the projection matrix of your camera or light etc. to construct the planes from
			*/
			Frustum(const gmtl::Matrix44f & projMatrix)
			{
				this->extractPlanes(projMatrix);
			}

			/**
			* Constructs a new frustum with given projection and modelview matricies.
			* the matricies are multiplied in this order : M = projMatrix * modelviewMatrix.
			* the planes are than extracted from M.
			*
			* @param modelviewMatrix the modelview matrix of you camera or light etc. to construct the planes from
			* @param projMatrix the projection matrix of your camera or light or what ever
			*/
			Frustum(const gmtl::Matrix44f & modelviewMatrix, const
			gmtl::Matrix44f & projMatrix)
			{
				this->extractPlanes(modelviewMatrix, projMatrix);
			}

			/**
			* extracts the planes from the given projection matrix.
			*
			* @param projMatrix the projection matrix of you camera or light or what ever
			*/
			void extractPlanes(const gmtl::Matrix44f & modelviewMatrix,
			const gmtl::Matrix44f & projMatrix)
			{
				this->extractPlanes(projMatrix * modelviewMatrix);
			}

			/**
			* extracts the planes from the given projection and modelview matricies.
			* the matricies are multiplied in this order : M = projMatrix * modelviewMatrix.
			* the planes are than extracted from M.
			*
			* @param modelviewMatrix the modelview matrix of you camera or light etc. to construct the planes from
			* @param projMatrix the projection matrix of you camera or light etc. to construct the planes from
			*/
			void extractPlanes(const gmtl::Matrix44f & projMatrix)
			{
				const gmtl::Matrix44f & m = projMatrix;

				//left
				this->m_planes[PLANE_LEFT].setNormal( gmtl::Vec3f( m[3][0] + m[0][0], m[3][1] + m[0][1], m[3][2] + m[0][2] ) );
				this->m_planes[PLANE_LEFT].setOffset(m[3][3] + m[0][3]);
				//right
				this->m_planes[PLANE_RIGHT].setNormal( gmtl::Vec3f( m[3][0] - m[0][0], m[3][1] - m[0][1], m[3][2] - m[0][2] ) );
				this->m_planes[PLANE_RIGHT].setOffset(m[3][3] - m[0][3]);
				//bottom
				this->m_planes[PLANE_BOTTOM].setNormal( gmtl::Vec3f( m[3][0] + m[1][0], m[3][1] + m[1][1], m[3][2] + m[1][2] ) );
				this->m_planes[PLANE_BOTTOM].setOffset(m[3][3] + m[1][3]);
				//top
				this->m_planes[PLANE_TOP].setNormal( gmtl::Vec3f( m[3][0] - m[1][0], m[3][1] - m[1][1], m[3][2] - m[1][2] ) );
				this->m_planes[PLANE_TOP].setOffset(m[3][3] - m[1][3]);
				//near
				this->m_planes[PLANE_NEAR].setNormal( gmtl::Vec3f( m[3][0] + m[2][0], m[3][1] + m[2][1], m[3][2] + m[2][2] ) );
				this->m_planes[PLANE_NEAR].setOffset(m[2][3] + m[3][3]);
				//far
				this->m_planes[PLANE_FAR].setNormal( gmtl::Vec3f( m[3][0] - m[2][0], m[3][1] - m[2][1], m[3][2] - m[2][2] ) );
				this->m_planes[PLANE_FAR].setOffset(m[3][3] - m[2][3]);
			}

			gmtl::Plane<DATA_TYPE> m_planes[6];
	};

	typedef Frustum<float> Frustumf;
	typedef Frustum<double> Frustumd;
}


#endif /* _GMTL_FRUSTUM_H_ */
