/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Intersection.h,v $
 * Date modified: $Date: 2003-01-10 18:42:01 $
 * Version:       $Revision: 1.8 $
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
#ifndef _GMTL_INTERSECTION_H_
#define _GMTL_INTERSECTION_H_

#include <algorithm>
#include <gmtl/AABox.h>
#include <gmtl/Point.h>
#include <gmtl/Sphere.h>
#include <gmtl/Vec.h>
#include <gmtl/Plane.h>
#include <gmtl/VecOps.h>
#include <gmtl/Math.h>
#include <gmtl/Ray.h>
#include <gmtl/LineSeg.h>
#include <gmtl/Tri.h>

namespace gmtl
{
   /**
    * Tests if the given AABoxes intersect with each other. Sharing an edge IS
    * considered intersection by this algorithm.
    *
    * @param box1    the first box to test
    * @param box2    the second box to test
    *
    * @return  true if the boxes intersect; false otherwise
    */
   template<class DATA_TYPE>
   bool intersect(const AABox<DATA_TYPE>& box1, const AABox<DATA_TYPE>& box2)
   {
      // Look for a separating axis on each box for each axis
      if (box1.getMin()[0] > box2.getMax()[0])  return false;
      if (box1.getMin()[1] > box2.getMax()[1])  return false;
      if (box1.getMin()[2] > box2.getMax()[2])  return false;

      if (box2.getMin()[0] > box1.getMax()[0])  return false;
      if (box2.getMin()[1] > box1.getMax()[1])  return false;
      if (box2.getMin()[2] > box1.getMax()[2])  return false;

      // No separating axis ... they must intersect
      return true;
   }
   
   /**
    * Tests if the given AABox and point intersect with each other. On an edge IS
    * considered intersection by this algorithm.
    *
    * @param box    the box to test
    * @param point  the point to test
    *
    * @return  true if the items intersect; false otherwise
    */
   template<class DATA_TYPE>
   bool intersect( const AABox<DATA_TYPE>& box, const Point<DATA_TYPE, 3>& point )
   {
      // Look for a separating axis on each box for each axis
      if (box.getMin()[0] > point[0])  return false;
      if (box.getMin()[1] > point[1])  return false;
      if (box.getMin()[2] > point[2])  return false;

      if (point[0] > box.getMax()[0])  return false;
      if (point[1] > box.getMax()[1])  return false;
      if (point[2] > box.getMax()[2])  return false;

      // they must intersect
      return true;
   }

   /**
    * Tests if the given AABoxes intersect if moved along the given paths. Using
    * the AABox sweep test, the normalized time of the first and last points of
    * contact are found.
    *
    * @param box1          the first box to test
    * @param path1         the path the first box should travel along
    * @param box2          the second box to test
    * @param path2         the path the second box should travel along
    * @param firstContact  set to the normalized time of the first point of contact
    * @param secondContact set to the normalized time of the second point of contact
    *
    * @return  true if the items intersect; false otherwise
    */
   template<class DATA_TYPE>
   bool intersect( const AABox<DATA_TYPE>& box1, const Vec<DATA_TYPE, 3>& path1,
                   const AABox<DATA_TYPE>& box2, const Vec<DATA_TYPE, 3>& path2,
                   DATA_TYPE& firstContact, DATA_TYPE& secondContact )
   {
      // Algorithm taken from Gamasutra's article, "Simple Intersection Test for
      // Games" - http://www.gamasutra.com/features/19991018/Gomez_3.htm
      //
      // This algorithm is solved from the frame of reference of box1

      // Get the relative path (in normalized time)
      Vec<DATA_TYPE, 3> path = path2 - path1;

      // The first time of overlap along each axis
      Vec<DATA_TYPE, 3> overlap1(DATA_TYPE(0), DATA_TYPE(0), DATA_TYPE(0));

      // The second time of overlap along each axis
      Vec<DATA_TYPE, 3> overlap2(DATA_TYPE(1), DATA_TYPE(1), DATA_TYPE(1));

      // Check if the boxes already overlap
      if (intersect(box1, box2))
      {
         firstContact = secondContact = DATA_TYPE(0);
         return true;
      }

      // Find the possible first and last times of overlap along each axis
      for (int i=0; i<3; ++i)
      {
         if ((box1.getMax()[i] < box2.getMin()[i]) && (path[i] < DATA_TYPE(0)))
         {
            overlap1[i] = (box1.getMax()[i] - box2.getMin()[i]) / path[i];
         }
         else if ((box2.getMax()[i] < box1.getMin()[i]) && (path[i] > DATA_TYPE(0)))
         {
            overlap1[i] = (box1.getMin()[i] - box2.getMax()[i]) / path[i];
         }

         if ((box2.getMax()[i] > box1.getMin()[i]) && (path[i] < DATA_TYPE(0)))
         {
            overlap2[i] = (box1.getMin()[i] - box2.getMax()[i]) / path[i];
         }
         else if ((box1.getMax()[i] > box2.getMin()[i]) && (path[i] > DATA_TYPE(0)))
         {
            overlap2[i] = (box1.getMax()[i] - box2.getMin()[i]) / path[i];
         }
      }

      // Calculate the first time of overlap
      firstContact = Math::Max(overlap1[0], overlap1[1], overlap1[2]);

      // Calculate the second time of overlap
      secondContact = Math::Min(overlap2[0], overlap2[1], overlap2[2]);

      // There could only have been a collision if the first overlap time
      // occurred before the second overlap time
      return firstContact <= secondContact;
   }

   /**
    * Tests if the given Spheres intersect if moved along the given paths. Using
    * the Sphere sweep test, the normalized time of the first and last points of
    * contact are found.
    *
    * @param sph1          the first sphere to test
    * @param path1         the path the first sphere should travel along
    * @param sph2          the second sphere to test
    * @param path2         the path the second sphere should travel along
    * @param firstContact  set to the normalized time of the first point of contact
    * @param secondContact set to the normalized time of the second point of contact
    *
    * @return  true if the items intersect; false otherwise
    */
   template<class DATA_TYPE>
   bool intersect(const Sphere<DATA_TYPE>& sph1, const Vec<DATA_TYPE, 3>& path1,
                  const Sphere<DATA_TYPE>& sph2, const Vec<DATA_TYPE, 3>& path2,
                  DATA_TYPE& firstContact, DATA_TYPE& secondContact)
   {
      // Algorithm taken from Gamasutra's article, "Simple Intersection Test for
      // Games" - http://www.gamasutra.com/features/19991018/Gomez_2.htm
      //
      // This algorithm is solved from the frame of reference of sph1

      // Get the relative path (in normalized time)
      const Vec<DATA_TYPE, 3> path = path2 - path1;

      // Get the vector from sph1's starting point to sph2's starting point
      const Vec<DATA_TYPE, 3> start_offset = sph2.getCenter() - sph1.getCenter();

      // Compute the sum of the radii
      const DATA_TYPE radius_sum = sph1.getRadius() + sph2.getRadius();

      // u*u coefficient
      const DATA_TYPE a = dot(path, path);

      // u coefficient
      const DATA_TYPE b = DATA_TYPE(2) * dot(path, start_offset);

      // constant term
      const DATA_TYPE c = dot(start_offset, start_offset) - radius_sum * radius_sum;

      // Check if they're already overlapping
      if (dot(start_offset, start_offset) <= radius_sum * radius_sum)
      {
         firstContact = secondContact = DATA_TYPE(0);
         return true;
      }

      // Find the first and last points of intersection
      if (Math::quadraticFormula(firstContact, secondContact, a, b, c))
      {
         // Swap first and second contacts if necessary
         if (firstContact > secondContact)
         {
            std::swap(firstContact, secondContact);
            return true;
         }
      }

      return false;
   }

   /**
    * Tests if the given AABox and Sphere intersect with each other. On an edge
    * IS considered intersection by this algorithm.
    *
    * @param box  the box to test
    * @param sph  the sphere to test
    *
    * @return  true if the items intersect; false otherwise
    */
   template<class DATA_TYPE>
   bool intersect(const AABox<DATA_TYPE>& box, const Sphere<DATA_TYPE>& sph)
   {
      DATA_TYPE dist_sqr = DATA_TYPE(0);

      // Compute the square of the distance from the sphere to the box
      for (int i=0; i<3; ++i)
      {
         if (sph.getCenter()[i] < box.getMin()[i])
         {
            DATA_TYPE s = sph.getCenter()[i] - box.getMin()[i];
            dist_sqr += s*s;
         }
         else if (sph.getCenter()[i] > box.getMax()[i])
         {
            DATA_TYPE s = sph.getCenter()[i] - box.getMax()[i];
            dist_sqr += s*s;
         }
      }

      return dist_sqr <= (sph.getRadius()*sph.getRadius());
   }

   /**
    * Tests if the given AABox and Sphere intersect with each other. On an edge
    * IS considered intersection by this algorithm.
    *
    * @param sph  the sphere to test
    * @param box  the box to test
    *
    * @return  true if the items intersect; false otherwise
    */
   template<class DATA_TYPE>
   bool intersect(const Sphere<DATA_TYPE>& sph, const AABox<DATA_TYPE>& box)
   {
      return intersect(box, sph);
   }

   /**
    * Tests if the given plane and ray intersect with each other.
    *
    *  @param ray - the Ray
    *  @param plane - the Plane
    *  @param t - t gives you the intersection point:
    *         isect_point = ray.origin + ray.dir * t 
    *
    *  @return true if the ray intersects the plane.
    */
   template<class DATA_TYPE>
   bool intersect( const Plane<DATA_TYPE>& plane, const Ray<DATA_TYPE>& ray, DATA_TYPE& t )
   {
      Vec<DATA_TYPE, 3> N( plane.getNormal() );
      t = dot( N, N * plane.getOffset() - ray.getOrigin() ) / dot( N, ray.getDir() );
      return (DATA_TYPE)0 <= t && t <= (DATA_TYPE)1.0; 
   }

   /**
    * Tests if the given plane and ray intersect with each other.
    *
    *  @param tri - the triangle (ccw ordering)
    *  @param ray - the ray
    *  @param u,v - tangent space u/v coordinates of the intersection
    *  @param t - t gives you the intersection point:
    *         isect = ray.dir * t + ray.origin
    *
    *  @return true if the ray intersects the triangle.
    *  @see from http://www.acm.org/jgt/papers/MollerTrumbore97/code.html
    */
   template<class DATA_TYPE>
   bool intersect( const Tri<DATA_TYPE>& tri, const Ray<DATA_TYPE>& ray, 
   						   float& u, float& v, float& t )
   {
	   const float EPSILON = (DATA_TYPE)0.00001;
	   Vec<DATA_TYPE, 3> edge1, edge2, tvec, pvec, qvec;
      float det,inv_det;

      /* find vectors for two edges sharing vert0 */
      edge1 = tri[1] - tri[0];
      edge2 = tri[2] - tri[0];

      /* begin calculating determinant - also used to calculate U parameter */
      gmtl::cross( pvec, ray.getDir(), edge2 );

      /* if determinant is near zero, ray lies in plane of triangle */
      det = gmtl::dot( edge1, pvec );

      if (det < EPSILON)
         return false;

      /* calculate distance from vert0 to ray origin */
      tvec = ray.getOrigin() - tri[0];

      /* calculate U parameter and test bounds */
      u = gmtl::dot( tvec, pvec );
      if (u < 0.0 || u > det)
         return false;

      /* prepare to test V parameter */
      gmtl::cross( qvec, tvec, edge1 );

      /* calculate V parameter and test bounds */
      v = gmtl::dot( ray.getDir(), qvec );
      if (v < 0.0 || u + v > det)
         return false;

      /* calculate t, scale parameters, ray intersects triangle */
      t = gmtl::dot( edge2, qvec );
      inv_det = ((DATA_TYPE)1.0) / det;
      t *= inv_det;
      u *= inv_det;
      v *= inv_det;
      
      // test if t is within the ray boundary (when t >= 0)
      return t >= (DATA_TYPE)0;
   }

   /**
    * Tests if the given plane and ray intersect with each other.
    *
    *  @param tri - the triangle (ccw ordering)
    *  @param ray - the ray
    *  @param u,v - tangent space u/v coordinates of the intersection
    *  @param t - t gives you the intersection point:
    *         isect = ray.dir * t + ray.origin
    *
    *  @return true if the ray intersects the triangle.
    */
   template<class DATA_TYPE>
   bool intersect( const Tri<DATA_TYPE>& tri, const LineSeg<DATA_TYPE>& lineseg, 
   						   float& u, float& v, float& t )
   {
      const DATA_TYPE eps = (DATA_TYPE)0.0001010101;
      DATA_TYPE l = length( lineseg.getDir() );
      if (eps < l)
      {
         Ray<DATA_TYPE> temp( lineseg.getOrigin(), lineseg.getDir() / l );
         bool result = intersect( tri, temp, u, v, t );
         t /= lineseg.getLength(); // need to normalize the result
         return result && t <= (DATA_TYPE)1.0;
      }
      else 
         return false;
   }
}

   

#endif
