/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * PyJuggler is (C) Copyright 2002, 2003 by Patrick Hartling
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: gmtl-functions.h,v $
 * Date modified: $Date: 2003-08-17 06:32:59 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#ifndef _PYJUGGLER_GMTL_FUNCTIONS_H_
#define _PYJUGGLER_GMTL_FUNCTIONS_H_

// This file makes declarations of the templated function instantiations
// needed for Boost.Python to do its thing.

#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Quat.h>
#include <gmtl/QuatOps.h>
#include <gmtl/EulerAngle.h>
#include <gmtl/EulerAngleOps.h>
#include <gmtl/AxisAngle.h>
#include <gmtl/AxisAngleOps.h>
#include <gmtl/Sphere.h>
#include <gmtl/SphereOps.h>
#include <gmtl/AABox.h>
#include <gmtl/AABoxOps.h>
#include <gmtl/LineSeg.h>
#include <gmtl/LineSegOps.h>
#include <gmtl/Plane.h>
#include <gmtl/PlaneOps.h>
#include <gmtl/Tri.h>
#include <gmtl/TriOps.h>
#include <gmtl/Coord.h>
#include <gmtl/CoordOps.h>


namespace gmtl
{
// gmtl::Matrix<> functions ===================================================
   template bool isEqual(const gmtl::Matrix44f&, const gmtl::Matrix44f&,
                         const float&);
   template bool isEqual(const gmtl::Matrix33f&, const gmtl::Matrix33f&,
                         const float&);
// =================================================== gmtl::Matrix<> functions

// gmtl::Vec<> functions ======================================================
   typedef gmtl::VecBase<float, 3> VecBase3f;
   typedef gmtl::VecBase<double, 3> VecBase3d;
   typedef gmtl::VecBase<float, 4> VecBase4f;
   typedef gmtl::VecBase<double, 4> VecBase4d;

   template bool isEqual(const gmtl::VecBase3f&, const gmtl::VecBase3f&,
                         const float&);
   template bool isEqual(const gmtl::VecBase3d&, const gmtl::VecBase3d&,
                         const double&);
   template bool isEqual(const gmtl::VecBase4f&, const gmtl::VecBase4f&,
                         const float&);
   template bool isEqual(const gmtl::VecBase4d&, const gmtl::VecBase4d&,
                         const double&);
// ====================================================== gmtl::Vec<> functions

// gmtl::Quat<> functions =====================================================
   template bool isEqual(const gmtl::Quatf&, const gmtl::Quatf&, float);
   template bool isEqual(const gmtl::Quatd&, const gmtl::Quatd&, double);
// ===================================================== gmtl::Quat<> functions

// gmtl::EulerAngle<> functions ===============================================
   template bool isEqual(const EulerAngleXYZf&, const EulerAngleXYZf&,
                         const float&);
   template bool isEqual(const EulerAngleZXYf&, const EulerAngleZXYf&,
                         const float&);
   template bool isEqual(const EulerAngleZYXf&, const EulerAngleZYXf&,
                         const float&);
// =============================================== gmtl::EulerAngle<> functions

// gmtl::AxisAngle<> functions ================================================
   template bool isEqual(const AxisAnglef&, const AxisAnglef&, const float&);
   template bool isEqual(const AxisAngled&, const AxisAngled&, const double&);
// ================================================ gmtl::AxisAngle<> functions

// gmtl::Sphere<> functions ===================================================
   template bool isEqual(const gmtl::Spheref&, const gmtl::Spheref&,
                         const float&);
   template bool isEqual(const gmtl::Sphered&, const gmtl::Sphered&,
                         const double&);
// =================================================== gmtl::Sphere<> functions

// gmtl::AABox<> functions ====================================================
   template bool isEqual(const gmtl::AABoxf&, const gmtl::AABoxf&,
                         const float&);
   template bool isEqual(const gmtl::AABoxd&, const gmtl::AABoxd&,
                         const double&);
// ==================================================== gmtl::AABox<> functions

// gmtl::LineSeg<> functions ==================================================
   template gmtl::Point3f findNearestPt(const gmtl::LineSegf&,
                                        const gmtl::Point3f&);
   template gmtl::Point3d findNearestPt(const gmtl::LineSegd&,
                                        const gmtl::Point3d&);

   template float distance(const gmtl::LineSegf&, const gmtl::Point3f&);
   template double distance(const gmtl::LineSegd&, const gmtl::Point3d&);
// ================================================== gmtl::LineSeg<> functions

// gmtl::Plane<> functions ====================================================
   template float distance(const gmtl::Planef&, const gmtl::Point3f&);
   template double distance(const gmtl::Planed&, const gmtl::Point3d&);

   template float findNearestPt(const gmtl::Planef&, const gmtl::Point3f&,
                                gmtl::Point3f&);
   template double findNearestPt(const gmtl::Planed&, const gmtl::Point3d&,
                                 gmtl::Point3d&);

   template bool isEqual(const gmtl::Planef&, const gmtl::Planef&,
                         const float&);
   template bool isEqual(const gmtl::Planed&, const gmtl::Planed&,
                         const double&);
// ==================================================== gmtl::Plane<> functions

// gmtl::Tri<> functions ======================================================
   template bool isEqual(const gmtl::Trif&, const gmtl::Trif&, const float&);
   template bool isEqual(const gmtl::Trid&, const gmtl::Trid&, const double&);
// ====================================================== gmtl::Tri<> functions

// gmtl::Coord<> functions ====================================================
   template bool isEqual(const gmtl::Coord3fXYZ&, const gmtl::Coord3fXYZ&,
                         float);
   template bool isEqual(const gmtl::Coord3fZYX&, const gmtl::Coord3fZYX&,
                         float);
   template bool isEqual(const gmtl::Coord3fZXY&, const gmtl::Coord3fZXY&,
                         float);

   template bool isEqual(const gmtl::Coord3dXYZ&, const gmtl::Coord3dXYZ&,
                         double);
   template bool isEqual(const gmtl::Coord3dZYX&, const gmtl::Coord3dZYX&,
                         double);
   template bool isEqual(const gmtl::Coord3dZXY&, const gmtl::Coord3dZXY&,
                         double);

   template bool isEqual(const gmtl::Coord4fXYZ&, const gmtl::Coord4fXYZ&,
                         float);
   template bool isEqual(const gmtl::Coord4fZYX&, const gmtl::Coord4fZYX&,
                         float);
   template bool isEqual(const gmtl::Coord4fZXY&, const gmtl::Coord4fZXY&,
                         float);

   template bool isEqual(const gmtl::Coord4dXYZ&, const gmtl::Coord4dXYZ&,
                         double);
   template bool isEqual(const gmtl::Coord4dZYX&, const gmtl::Coord4dZYX&,
                         double);
   template bool isEqual(const gmtl::Coord4dZXY&, const gmtl::Coord4dZXY&,
                         double);

   template bool isEqual(const gmtl::Coord3fQuat&, const gmtl::Coord3fQuat&,
                         float);
   template bool isEqual(const gmtl::Coord3dQuat&, const gmtl::Coord3dQuat&,
                         double);

   template bool isEqual(const gmtl::Coord4fQuat&, const gmtl::Coord4fQuat&,
                         float);
   template bool isEqual(const gmtl::Coord4dQuat&, const gmtl::Coord4dQuat&,
                         double);

   template bool isEqual(const gmtl::Coord3fAxisAngle&,
                         const gmtl::Coord3fAxisAngle&, float);
   template bool isEqual(const gmtl::Coord3dAxisAngle&,
                         const gmtl::Coord3dAxisAngle&, double);

   template bool isEqual(const gmtl::Coord4fAxisAngle&,
                         const gmtl::Coord4fAxisAngle&, float);
   template bool isEqual(const gmtl::Coord4dAxisAngle&,
                         const gmtl::Coord4dAxisAngle&, double);
// ==================================================== gmtl::Coord<> functions
}


#endif /* _PYJUGGLER_GMTL_FUNCTIONS_H_ */
