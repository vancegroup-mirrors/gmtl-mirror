/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Containment.h,v $
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
#ifndef _GMTL_CONTAINMENT_H_
#define _GMTL_CONTAINMENT_H_

#include <gmtl/OOBox.h>
#include <gmtl/AABox.h>
#include <gmtl/Fit/GaussPointsFit.h>
#include <gmtl/matVecFuncs.h>
#include <gmtl/Quat.h>

namespace gmtl
{

inline void computeContainment( AABox& box, const std::vector<gmtl::Point3>& points,
                         Point3& minPt, Point3& maxPt )
//void MgcContAlignedBox (int iQuantity, const MgcVector3* akPoint,
//    MgcVector3& rkMin, MgcVector3& rkMax)
{
   if (points.empty())
      return;

   minPt = points[0];
   maxPt = minPt;

   for (unsigned i = 1; i < points.size(); i++)
   {
      if ( points[i][Xelt] < minPt[Xelt] )
         minPt[Xelt] = points[i][Xelt];
      else if ( points[i][Xelt] > maxPt[Xelt] )
         maxPt[Xelt] = points[i][Xelt];

      if ( points[i][Yelt] < minPt[Yelt] )
         minPt[Yelt] = points[i][Yelt];
      else if ( points[i][Yelt] > maxPt[Yelt] )
         maxPt[Yelt] = points[i][Yelt];

      if ( points[i][Zelt] < minPt[Zelt] )
         minPt[Zelt] = points[i][Zelt];
      else if ( points[i][Zelt] > maxPt[Zelt] )
         maxPt[Zelt] = points[i][Zelt];
   }

   // Now update the box
   box.makeEmpty();
   box.mMax = maxPt;
   box.mMin = minPt;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//MgcBox3 MgcContOrientedBox (int iQuantity, const MgcVector3* akPoint)
inline void computeContainment( OOBox& box, const std::vector<gmtl::Point3>& points)
{
    //MgcGaussPointsFit(iQuantity,akPoint,kBox.Center(),kBox.Axes(),
    //    kBox.Extents());

    gmtl::GaussPointsFit(points.size(), &points[0], box.center(), box.axes(), box.halfLens());

    // Let C be the box center and let U0, U1, and U2 be the box axes.  Each
    // input point is of the form X = C + y0*U0 + y1*U1 + y2*U2.  The
    // following code computes min(y0), max(y0), min(y1), max(y1), min(y2),
    // and max(y2).  The box center is then adjusted to be
    //   C' = C + 0.5*(min(y0)+max(y0))*U0 + 0.5*(min(y1)+max(y1))*U1 +
    //        0.5*(min(y2)+max(y2))*U2
#ifdef GFX_DEBUG
   gmtl::OOBox box_test;
   box_test = box;
   gmtl::Vec3 ax0 = box_test.axis(0);
   gmtl::Vec3 ax1 = box_test.axis(1);
   gmtl::Vec3 ax2 = box_test.axis(2);
#endif

    gfxASSERT(box.axis(0).isNormalized());
    gfxASSERT(box.axis(1).isNormalized());
    gfxASSERT(box.axis(2).isNormalized());

    // XXX: Sign is sometimes wrong here
    // This is hack code to make it "work right"
    Vec3 cross;
    cross = box.axis(0).cross(box.axis(1));
    cross.normalize();
    box.axis(2) = cross;

    Vec3 kDiff = points[0] - box.center();
    float fY0Min = kDiff.dot(box.axis(0)), fY0Max = fY0Min;
    float fY1Min = kDiff.dot(box.axis(1)), fY1Max = fY1Min;
    float fY2Min = kDiff.dot(box.axis(2)), fY2Max = fY2Min;

    float fY0, fY1, fY2;

    for (unsigned i = 1; i < points.size(); i++)
    {
        kDiff = points[i] - box.center();

        fY0 = kDiff.dot(box.axis(0));
        if ( fY0 < fY0Min )
            fY0Min = fY0;
        else if ( fY0 > fY0Max )
            fY0Max = fY0;

        fY1 = kDiff.dot(box.axis(1));
        if ( fY1 < fY1Min )
            fY1Min = fY1;
        else if ( fY1 > fY1Max )
            fY1Max = fY1;

        fY2 = kDiff.dot(box.axis(2));
        if ( fY2 < fY2Min )
            fY2Min = fY2;
        else if ( fY2 > fY2Max )
            fY2Max = fY2;
    }

    box.center() += (0.5*(fY0Min+fY0Max))*box.axis(0) +
                    (0.5*(fY1Min+fY1Max))*box.axis(1) +
                    (0.5*(fY2Min+fY2Max))*box.axis(2);

    box.halfLen(0) = 0.5*(fY0Max - fY0Min);
    box.halfLen(1) = 0.5*(fY1Max - fY1Min);
    box.halfLen(2) = 0.5*(fY2Max - fY2Min);
}


inline void computeContainment (OOBox& out_box, const OOBox& box0, const OOBox& box1, bool fast=true)
{
   gmtl::OOBox ret_box;    // The resulting box

   if (fast)
   {
      ret_box.center() = 0.5*(box0.center() + box1.center());       // Center at average

      // Average the quats to get a new orientation
      Quat quat0, quat1;
      quat0.makeAxes(box0.axis(0), box0.axis(1), box0.axis(2));
      quat1.makeAxes(box1.axis(0), box1.axis(1), box1.axis(2));
      if ( quat0.dot(quat1) < 0.0 )
         quat1 = -quat1;

      Quat full_quat = quat0 + quat1;

      //float inv_len = 1.0/Math::sqrt(full_quat.norm());
      //full_quat = inv_len*full_quat;
      full_quat.normalize();
      full_quat.getAxes(ret_box.axis(0), ret_box.axis(1), ret_box.axis(2));

      // Now that we have new orientation, extend half lens to cover the volume
      //
      unsigned i, j;
      Point3 verts[8];
      Vec3 diff;
      float aDot;

      ret_box.halfLen(0) = 0.0;
      ret_box.halfLen(1) = 0.0;
      ret_box.halfLen(2) = 0.0;

      box0.getVerts(verts);
      for (i = 0; i < 8; i++)
      {
         diff = verts[i] - ret_box.center();
         for (j = 0; j < 3; j++)                       // For each axis of box0
         {
            aDot = Math::abs(diff.dot(ret_box.axis(j)));
            if ( aDot > ret_box.halfLen(j) )
               ret_box.halfLen(j) = aDot;
         }
      }

      box1.getVerts(verts);
      for (i = 0; i < 8; i++)
      {
         diff = verts[i] - ret_box.center();
         for (j = 0; j < 3; j++)
         {
            aDot = Math::abs(diff.dot(ret_box.axis(j)));
            if ( aDot > ret_box.halfLen(j) )
               ret_box.halfLen(j) = aDot;
         }
      }
   }
   else     // Tighter fit
   {
      // Hack that will do it correctly, but is slow
      Point3 verts[8];
      std::vector<gmtl::Point3> vert_points;

      box0.getVerts(verts);
      for (unsigned i=0;i<8;i++) vert_points.push_back(verts[i]);
      box1.getVerts(verts);
      for (unsigned i=0;i<8;i++) vert_points.push_back(verts[i]);

      computeContainment(ret_box, vert_points);
   }

   out_box = ret_box;
}



};

#endif
