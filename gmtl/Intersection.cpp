/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Intersection.cpp,v $
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
#include <GMTL/gmtlDefines.h>
#include <GMTL/Vec3.h>
#include <GMTL/Point3.h>
#include <GMTL/OOBox.h>
#include <GMTL/Tri.h>

namespace gmtl
{

   bool TestIntersect(const OOBox& box0, const OOBox& box1)
   {
      // convenience variables
      const Vec3* aAxes = box0.axes();
      const Vec3* bAxes = box1.axes();
      const float* aExtents = box0.halfLens();
      const float* bExtents = box1.halfLens();

      // compute difference of box centers, D = C1-C0
      Vec3 dist = box1.center() - box0.center();

      float rMat[3][3];     // matrix rMat = A^T B, c_{ij} = Dot(A_i,B_j)
      float rMatAbs[3][3];  // |c_{ij}|
      // NOTE: Since it is not a Matrix4, I am using a different ordering here
      float aDotD[3];        // Dot(A_i,D)
      float fR0, fR1, fR;   // interval radii and distance between centers
      float fR01;           // = R0 + R1

      // axis C0+t*A0
      rMat[0][0] = aAxes[0].dot(bAxes[0]);
      rMat[0][1] = aAxes[0].dot(bAxes[1]);
      rMat[0][2] = aAxes[0].dot(bAxes[2]);
      aDotD[0] = aAxes[0].dot(dist);
      rMatAbs[0][0] = Math::abs(rMat[0][0]);
      rMatAbs[0][1] = Math::abs(rMat[0][1]);
      rMatAbs[0][2] = Math::abs(rMat[0][2]);
      fR = Math::abs(aDotD[0]);
      fR1 = bExtents[0]*rMatAbs[0][0]+bExtents[1]*rMatAbs[0][1]+bExtents[2]*rMatAbs[0][2];
      fR01 = aExtents[0] + fR1;
      if ( fR > fR01 )
         return false;

      // axis C0+t*A1
      rMat[1][0] = aAxes[1].dot(bAxes[0]);
      rMat[1][1] = aAxes[1].dot(bAxes[1]);
      rMat[1][2] = aAxes[1].dot(bAxes[2]);
      aDotD[1] = aAxes[1].dot(dist);
      rMatAbs[1][0] = Math::abs(rMat[1][0]);
      rMatAbs[1][1] = Math::abs(rMat[1][1]);
      rMatAbs[1][2] = Math::abs(rMat[1][2]);
      fR = Math::abs(aDotD[1]);
      fR1 = bExtents[0]*rMatAbs[1][0]+bExtents[1]*rMatAbs[1][1]+bExtents[2]*rMatAbs[1][2];
      fR01 = aExtents[1] + fR1;
      if ( fR > fR01 )
         return false;

      // axis C0+t*A2
      rMat[2][0] = aAxes[2].dot(bAxes[0]);
      rMat[2][1] = aAxes[2].dot(bAxes[1]);
      rMat[2][2] = aAxes[2].dot(bAxes[2]);
      aDotD[2] = aAxes[2].dot(dist);
      rMatAbs[2][0] = Math::abs(rMat[2][0]);
      rMatAbs[2][1] = Math::abs(rMat[2][1]);
      rMatAbs[2][2] = Math::abs(rMat[2][2]);
      fR = Math::abs(aDotD[2]);
      fR1 = bExtents[0]*rMatAbs[2][0]+bExtents[1]*rMatAbs[2][1]+bExtents[2]*rMatAbs[2][2];
      fR01 = aExtents[2] + fR1;
      if ( fR > fR01 )
         return false;

      // axis C0+t*B0
      fR = Math::abs(bAxes[0].dot(dist));
      fR0 = aExtents[0]*rMatAbs[0][0]+aExtents[1]*rMatAbs[1][0]+aExtents[2]*rMatAbs[2][0];
      fR01 = fR0 + bExtents[0];
      if ( fR > fR01 )
         return false;

      // axis C0+t*B1
      fR = Math::abs(bAxes[1].dot(dist));
      fR0 = aExtents[0]*rMatAbs[0][1]+aExtents[1]*rMatAbs[1][1]+aExtents[2]*rMatAbs[2][1];
      fR01 = fR0 + bExtents[1];
      if ( fR > fR01 )
         return false;

      // axis C0+t*B2
      fR = Math::abs(bAxes[2].dot(dist));
      fR0 = aExtents[0]*rMatAbs[0][2]+aExtents[1]*rMatAbs[1][2]+aExtents[2]*rMatAbs[2][2];
      fR01 = fR0 + bExtents[2];
      if ( fR > fR01 )
         return false;

      // axis C0+t*A0xB0
      fR = Math::abs(aDotD[2]*rMat[1][0]-aDotD[1]*rMat[2][0]);
      fR0 = aExtents[1]*rMatAbs[2][0] + aExtents[2]*rMatAbs[1][0];
      fR1 = bExtents[1]*rMatAbs[0][2] + bExtents[2]*rMatAbs[0][1];
      fR01 = fR0 + fR1;
      if ( fR > fR01 )
         return false;

      // axis C0+t*A0xB1
      fR = Math::abs(aDotD[2]*rMat[1][1]-aDotD[1]*rMat[2][1]);
      fR0 = aExtents[1]*rMatAbs[2][1] + aExtents[2]*rMatAbs[1][1];
      fR1 = bExtents[0]*rMatAbs[0][2] + bExtents[2]*rMatAbs[0][0];
      fR01 = fR0 + fR1;
      if ( fR > fR01 )
         return false;

      // axis C0+t*A0xB2
      fR = Math::abs(aDotD[2]*rMat[1][2]-aDotD[1]*rMat[2][2]);
      fR0 = aExtents[1]*rMatAbs[2][2] + aExtents[2]*rMatAbs[1][2];
      fR1 = bExtents[0]*rMatAbs[0][1] + bExtents[1]*rMatAbs[0][0];
      fR01 = fR0 + fR1;
      if ( fR > fR01 )
         return false;

      // axis C0+t*A1xB0
      fR = Math::abs(aDotD[0]*rMat[2][0]-aDotD[2]*rMat[0][0]);
      fR0 = aExtents[0]*rMatAbs[2][0] + aExtents[2]*rMatAbs[0][0];
      fR1 = bExtents[1]*rMatAbs[1][2] + bExtents[2]*rMatAbs[1][1];
      fR01 = fR0 + fR1;
      if ( fR > fR01 )
         return false;

      // axis C0+t*A1xB1
      fR = Math::abs(aDotD[0]*rMat[2][1]-aDotD[2]*rMat[0][1]);
      fR0 = aExtents[0]*rMatAbs[2][1] + aExtents[2]*rMatAbs[0][1];
      fR1 = bExtents[0]*rMatAbs[1][2] + bExtents[2]*rMatAbs[1][0];
      fR01 = fR0 + fR1;
      if ( fR > fR01 )
         return false;

      // axis C0+t*A1xB2
      fR = Math::abs(aDotD[0]*rMat[2][2]-aDotD[2]*rMat[0][2]);
      fR0 = aExtents[0]*rMatAbs[2][2] + aExtents[2]*rMatAbs[0][2];
      fR1 = bExtents[0]*rMatAbs[1][1] + bExtents[1]*rMatAbs[1][0];
      fR01 = fR0 + fR1;
      if ( fR > fR01 )
         return false;

      // axis C0+t*A2xB0
      fR = Math::abs(aDotD[1]*rMat[0][0]-aDotD[0]*rMat[1][0]);
      fR0 = aExtents[0]*rMatAbs[1][0] + aExtents[1]*rMatAbs[0][0];
      fR1 = bExtents[1]*rMatAbs[2][2] + bExtents[2]*rMatAbs[2][1];
      fR01 = fR0 + fR1;
      if ( fR > fR01 )
         return false;

      // axis C0+t*A2xB1
      fR = Math::abs(aDotD[1]*rMat[0][1]-aDotD[0]*rMat[1][1]);
      fR0 = aExtents[0]*rMatAbs[1][1] + aExtents[1]*rMatAbs[0][1];
      fR1 = bExtents[0]*rMatAbs[2][2] + bExtents[2]*rMatAbs[2][0];
      fR01 = fR0 + fR1;
      if ( fR > fR01 )
         return false;

      // axis C0+t*A2xB2
      fR = Math::abs(aDotD[1]*rMat[0][2]-aDotD[0]*rMat[1][2]);
      fR0 = aExtents[0]*rMatAbs[1][2] + aExtents[1]*rMatAbs[0][2];
      fR1 = bExtents[0]*rMatAbs[2][1] + bExtents[1]*rMatAbs[2][0];
      fR01 = fR0 + fR1;
      if ( fR > fR01 )
         return false;

      return true;

   }

   template<bool FIND_CONTACT>
   inline bool dynObbFind0(const float radii0, const float radiiT, const float rCenterSep,
                           const float dt, float& tMaxContact)
   {
      if(radii0 > rCenterSep)
      {
         if( radiiT > rCenterSep)
            return false;
         if(FIND_CONTACT)
         {
            float tmp(dt*((rCenterSep-radii0)/(radiiT-radii0)));
            if(tmp > tMaxContact)
            {
               tMaxContact = tmp;
            }
         }
      }
      else if( radii0 < -rCenterSep)
      {
         if( radiiT < -rCenterSep)
            return false;
         if(FIND_CONTACT)
         {
            float tmp(-dt*((rCenterSep+radii0)/(radiiT-radii0)));
            if(tmp > tMaxContact)
            {
               tMaxContact = tmp;
            }
         }
      }

      return true;
   }

   template<bool FIND_CONTACT>
   inline bool dynObbFind1(const float radii0, const float rt0, const float rt1, const float rt2, const float rt3, const float rCenterSep,
                           const float dt, float& tMaxContact)
   {
      float radiiT;

      if(radii0 > rCenterSep)
      {
         radiiT = (rt0*rt1)-(rt2*rt3);
         if( radiiT > rCenterSep)
            return false;
         if(FIND_CONTACT)
         {
            float tmp(dt*((rCenterSep-radii0)/(radiiT-radii0)));
            if(tmp > tMaxContact)
            {
               tMaxContact = tmp;
            }
         }
      }
      else if( radii0 < -rCenterSep)
      {
         radiiT = (rt0*rt1)-(rt2*rt3);
         if( radiiT < -rCenterSep)
            return false;
         if(FIND_CONTACT)
         {
            float tmp(-dt*((rCenterSep+radii0)/(radiiT-radii0)));
            if(tmp > tMaxContact)
            {
               tMaxContact = tmp;
            }
         }
      }

      return true;
   }


// boxes have constant linear velocity
   template <bool FIND_CONTACT>
   inline bool TestIntersectOBB(float time,
                         const OOBox& box0, const Vec3& vel0,
                         const OOBox& box1, const Vec3& vel1,
                         float& tFirstContact)
   {
      // convenience variables
      const Vec3* aAxes = box0.axes();
      const Vec3* bAxes = box1.axes();
      const float* aExtents = box0.halfLens();
      const float* bExtents = box1.halfLens();

      // Compute relative velocity of box1 with respect to box0 so that box0
      // may as well be stationary.
      Vec3 kW = vel1 - vel0;

      // Compute difference of box centers at time 0 and time 'fTime'.
      Vec3 dist0 = box1.center() - box0.center();
      Vec3 dist1 = dist0 + time*kW;

      float rMat[3][3];       // matrix C = A^T B, c_{ij} = dot(A_i,B_j)
      float rMatAbs[3][3];    // |c_{ij}|
      float aDotD0[3];        // dot(A_i,D0)
      float aDotD1[3];        // dot(A_i,D1)
      float bDotD0[3];        // dot(B_i,D0)
      float bDotD1[3];        // dot(B_i,D1)
      float fR0, fR1, fR;     // interval radii and distance between centers
      float fR01;             // = R0 + R1

      // Track minimum time
      if(FIND_CONTACT)
      {
         tFirstContact = 0.0f;
      }

      // axis C0+t*A0
      rMat[0][0] = aAxes[0].dot(bAxes[0]);
      rMat[0][1] = aAxes[0].dot(bAxes[1]);
      rMat[0][2] = aAxes[0].dot(bAxes[2]);
      aDotD0[0] = aAxes[0].dot(dist0);
      aDotD1[0] = aAxes[0].dot(dist1);
      rMatAbs[0][0] = Math::abs(rMat[0][0]);
      rMatAbs[0][1] = Math::abs(rMat[0][1]);
      rMatAbs[0][2] = Math::abs(rMat[0][2]);
      fR1 = bExtents[0]*rMatAbs[0][0]+bExtents[1]*rMatAbs[0][1]+bExtents[2]*rMatAbs[0][2];
      fR01 = aExtents[0] + fR1;
      //if(!FIND_CONTACT)
      //{
         if(!dynObbFind0<FIND_CONTACT>(aDotD0[0], aDotD1[0], fR01, time, tFirstContact))
            return false;
      //}
      //else
      //{

      //}
      /*
      if ( aDotD0[0] > fR01 )
      {
         if ( aDotD1[0] > fR01 )
            return false;
      }
      else if ( aDotD0[0] < -fR01 )
      {
         if ( aDotD1[0] < -fR01 )
            return false;
      }
      */

      // axis C0+t*A1
      rMat[1][0] = aAxes[1].dot(bAxes[0]);
      rMat[1][1] = aAxes[1].dot(bAxes[1]);
      rMat[1][2] = aAxes[1].dot(bAxes[2]);
      aDotD0[1] = aAxes[1].dot(dist0);
      aDotD1[1] = aAxes[1].dot(dist1);
      rMatAbs[1][0] = Math::abs(rMat[1][0]);
      rMatAbs[1][1] = Math::abs(rMat[1][1]);
      rMatAbs[1][2] = Math::abs(rMat[1][2]);
      fR1 = bExtents[0]*rMatAbs[1][0]+bExtents[1]*rMatAbs[1][1]+bExtents[2]*rMatAbs[1][2];
      fR01 = aExtents[1] + fR1;
      if(!dynObbFind0<FIND_CONTACT>(aDotD0[1], aDotD1[1], fR01, time, tFirstContact))
         return false;
      /*
      if ( aDotD0[1] > fR01 )
      {
         if ( aDotD1[1] > fR01 )
            return false;
      }
      else if ( aDotD0[1] < -fR01 )
      {
         if ( aDotD1[1] < -fR01 )
            return false;
      }
      */

      // axis C0+t*A2
      rMat[2][0] = aAxes[2].dot(bAxes[0]);
      rMat[2][1] = aAxes[2].dot(bAxes[1]);
      rMat[2][2] = aAxes[2].dot(bAxes[2]);
      aDotD0[2] = aAxes[2].dot(dist0);
      aDotD1[2] = aAxes[2].dot(dist1);
      rMatAbs[2][0] = Math::abs(rMat[2][0]);
      rMatAbs[2][1] = Math::abs(rMat[2][1]);
      rMatAbs[2][2] = Math::abs(rMat[2][2]);
      fR1 = bExtents[0]*rMatAbs[2][0]+bExtents[1]*rMatAbs[2][1]+bExtents[2]*rMatAbs[2][2];
      fR01 = aExtents[2] + fR1;
      if(!dynObbFind0<FIND_CONTACT>(aDotD0[2], aDotD1[2], fR01, time, tFirstContact))
         return false;
      /*
      if ( aDotD0[2] > fR01 )
      {
         if ( aDotD1[2] > fR01 )
            return false;
      }
      else if ( aDotD0[2] < -fR01 )
      {
         if ( aDotD1[2] < -fR01 )
            return false;
      }
      */

      // axis C0+t*B0
      bDotD0[0] = bAxes[0].dot(dist0);
      bDotD1[0] = bAxes[0].dot(dist1);
      //fR = bAxes[0].dot(dist0);
      fR0 = aExtents[0]*rMatAbs[0][0]+aExtents[1]*rMatAbs[1][0]+aExtents[2]*rMatAbs[2][0];
      fR01 = fR0 + bExtents[0];
      if(!dynObbFind0<FIND_CONTACT>(bDotD0[0], bDotD1[0], fR01, time, tFirstContact))
         return false;
      /*
      if ( fR > fR01 )
      {
         fR = bAxes[0].dot(dist1);
         if ( fR > fR01)
            return false;
      }
      else if ( fR < -fR01 )
      {
         fR = bAxes[0].dot(dist1);
         if ( fR < -fR01 )
            return false;
      }
      */

      // axis C0+t*B1
      bDotD0[1] = bAxes[1].dot(dist0);
      bDotD1[1] = bAxes[1].dot(dist1);
      //fR = bAxes[1].dot(dist0);
      fR0 = aExtents[0]*rMatAbs[0][1]+aExtents[1]*rMatAbs[1][1]+aExtents[2]*rMatAbs[2][1];
      fR01 = fR0 + bExtents[1];
      if(!dynObbFind0<FIND_CONTACT>(bDotD0[1], bDotD1[1], fR01, time, tFirstContact))
         return false;

      /*
      if ( fR > fR01 )
      {
         fR = bAxes[1].dot(dist1);
         if ( fR > fR01 )
            return false;
      }
      else if ( fR < -fR01 )
      {
         fR = bAxes[1].dot(dist1);
         if ( fR < -fR01 )
            return false;
      }
      */

      // axis C0+t*B2
      bDotD0[2] = bAxes[2].dot(dist0);
      bDotD1[2] = bAxes[2].dot(dist1);
      //fR = bAxes[2].dot(dist0);
      fR0 = aExtents[0]*rMatAbs[0][2]+aExtents[1]*rMatAbs[1][2]+aExtents[2]*rMatAbs[2][2];
      fR01 = fR0 + bExtents[2];
      if(!dynObbFind0<FIND_CONTACT>(bDotD0[2], bDotD1[2], fR01, time, tFirstContact))
         return false;

      /*
      if ( fR > fR01 )
      {
         fR = bAxes[2].dot(dist1);
         if ( fR > fR01 )
            return false;
      }
      else if ( fR < -fR01 )
      {
         fR = bAxes[2].dot(dist1);
         if ( fR < -fR01 )
            return false;
      }
      */

      // axis C0+t*A0xB0
      fR = aDotD0[2]*rMat[1][0]-aDotD0[1]*rMat[2][0];
      fR0 = aExtents[1]*rMatAbs[2][0] + aExtents[2]*rMatAbs[1][0];
      fR1 = bExtents[1]*rMatAbs[0][2] + bExtents[2]*rMatAbs[0][1];
      fR01 = fR0 + fR1;

      if(!dynObbFind1<FIND_CONTACT>(fR, aDotD1[2], rMat[1][0], aDotD1[1], rMat[2][0], fR01, time, tFirstContact))
         return false;
      /*
      if ( fR > fR01 )
      {
         fR = aDotD1[2]*rMat[1][0]-aDotD1[1]*rMat[2][0];
         if ( fR > fR01 )
            return false;
      }
      else if ( fR < -fR01 )
      {
         fR = aDotD1[2]*rMat[1][0]-aDotD1[1]*rMat[2][0];
         if ( fR < -fR01 )
            return false;
      }
      */

      // axis C0+t*A0xB1
      fR = aDotD0[2]*rMat[1][1]-aDotD0[1]*rMat[2][1];
      fR0 = aExtents[1]*rMatAbs[2][1] + aExtents[2]*rMatAbs[1][1];
      fR1 = bExtents[0]*rMatAbs[0][2] + bExtents[2]*rMatAbs[0][0];
      fR01 = fR0 + fR1;
      if(!dynObbFind1<FIND_CONTACT>(fR, aDotD1[2], rMat[1][1], aDotD1[1], rMat[2][1], fR01, time, tFirstContact))
         return false;

      /*if ( fR > fR01 )
      {
         fR = aDotD1[2]*rMat[1][1]-aDotD1[1]*rMat[2][1];
         if ( fR > fR01 )
            return false;
      }
      else if ( fR < -fR01 )
      {
         fR = aDotD1[2]*rMat[1][1]-aDotD1[1]*rMat[2][1];
         if ( fR < -fR01 )
            return false;
      }*/

      // axis C0+t*A0xB2
      fR = aDotD0[2]*rMat[1][2]-aDotD0[1]*rMat[2][2];
      fR0 = aExtents[1]*rMatAbs[2][2] + aExtents[2]*rMatAbs[1][2];
      fR1 = bExtents[0]*rMatAbs[0][1] + bExtents[1]*rMatAbs[0][0];
      fR01 = fR0 + fR1;
      if(!dynObbFind1<FIND_CONTACT>(fR,aDotD1[2],rMat[1][2],aDotD1[1],rMat[2][2],fR01, time, tFirstContact))
         return false;

      /*if ( fR > fR01 )
      {
         fR = aDotD1[2]*rMat[1][2]-aDotD1[1]*rMat[2][2];
         if ( fR > fR01 )
            return false;
      }
      else if ( fR < -fR01 )
      {
         fR = aDotD1[2]*rMat[1][2]-aDotD1[1]*rMat[2][2];
         if ( fR < -fR01 )
            return false;
      }*/

      // axis C0+t*A1xB0
      fR = aDotD0[0]*rMat[2][0]-aDotD0[2]*rMat[0][0];
      fR0 = aExtents[0]*rMatAbs[2][0] + aExtents[2]*rMatAbs[0][0];
      fR1 = bExtents[1]*rMatAbs[1][2] + bExtents[2]*rMatAbs[1][1];
      fR01 = fR0 + fR1;
      if(!dynObbFind1<FIND_CONTACT>(fR,aDotD1[0],rMat[2][0],aDotD1[2],rMat[0][0],fR01, time, tFirstContact))
         return false;
      /*if ( fR > fR01 )
      {
         fR = aDotD1[0]*rMat[2][0]-aDotD1[2]*rMat[0][0];
         if ( fR > fR01 )
            return false;
      }
      else if ( fR < -fR01 )
      {
         fR = aDotD1[0]*rMat[2][0]-aDotD1[2]*rMat[0][0];
         if ( fR < -fR01 )
            return false;
      }*/

      // axis C0+t*A1xB1
      fR = aDotD0[0]*rMat[2][1]-aDotD0[2]*rMat[0][1];
      fR0 = aExtents[0]*rMatAbs[2][1] + aExtents[2]*rMatAbs[0][1];
      fR1 = bExtents[0]*rMatAbs[1][2] + bExtents[2]*rMatAbs[1][0];
      fR01 = fR0 + fR1;
      if(!dynObbFind1<FIND_CONTACT>(fR,aDotD1[0],rMat[2][1],aDotD1[2],rMat[0][1],fR01, time, tFirstContact))
         return false;
      /*if ( fR > fR01 )
      {
         fR = aDotD1[0]*rMat[2][1]-aDotD1[2]*rMat[0][1];
         if ( fR > fR01 )
            return false;
      }
      else if ( fR < -fR01 )
      {
         fR = aDotD1[0]*rMat[2][1]-aDotD1[2]*rMat[0][1];
         if ( fR < -fR01 )
            return false;
      }*/

      // axis C0+t*A1xB2
      fR = aDotD0[0]*rMat[2][2]-aDotD0[2]*rMat[0][2];
      fR0 = aExtents[0]*rMatAbs[2][2] + aExtents[2]*rMatAbs[0][2];
      fR1 = bExtents[0]*rMatAbs[1][1] + bExtents[1]*rMatAbs[1][0];
      fR01 = fR0 + fR1;
      if(!dynObbFind1<FIND_CONTACT>(fR,aDotD1[0],rMat[2][2],aDotD1[2],rMat[0][2],fR01, time, tFirstContact))
         return false;
      /*if ( fR > fR01 )
      {
         fR = aDotD1[0]*rMat[2][2]-aDotD1[2]*rMat[0][2];
         if ( fR > fR01 )
            return false;
      }
      else if ( fR < -fR01 )
      {
         fR = aDotD1[0]*rMat[2][2]-aDotD1[2]*rMat[0][2];
         if ( fR < -fR01 )
            return false;
      }
      */

      // axis C0+t*A2xB0
      fR = aDotD0[1]*rMat[0][0]-aDotD0[0]*rMat[1][0];
      fR0 = aExtents[0]*rMatAbs[1][0] + aExtents[1]*rMatAbs[0][0];
      fR1 = bExtents[1]*rMatAbs[2][2] + bExtents[2]*rMatAbs[2][1];
      fR01 = fR0 + fR1;
      if(!dynObbFind1<FIND_CONTACT>(fR,aDotD1[1],rMat[0][0],aDotD1[0],rMat[1][0],fR01, time, tFirstContact))
         return false;
      /*if ( fR > fR01 )
      {
         fR = aDotD1[1]*rMat[0][0]-aDotD1[0]*rMat[1][0];
         if ( fR > fR01 )
            return false;
      }
      else if ( fR < -fR01 )
      {
         fR = aDotD1[1]*rMat[0][0]-aDotD1[0]*rMat[1][0];
         if ( fR < -fR01 )
            return false;
      }*/

      // axis C0+t*A2xB1
      fR = aDotD0[1]*rMat[0][1]-aDotD0[0]*rMat[1][1];
      fR0 = aExtents[0]*rMatAbs[1][1] + aExtents[1]*rMatAbs[0][1];
      fR1 = bExtents[0]*rMatAbs[2][2] + bExtents[2]*rMatAbs[2][0];
      fR01 = fR0 + fR1;
      if(!dynObbFind1<FIND_CONTACT>(fR,aDotD1[1],rMat[0][1],aDotD1[0],rMat[1][1],fR01, time, tFirstContact))
         return false;
      /*if ( fR > fR01 )
      {
         fR = aDotD1[1]*rMat[0][1]-aDotD1[0]*rMat[1][1];
         if ( fR > fR01 )
            return false;
      }
      else if ( fR < -fR01 )
      {
         fR = aDotD1[1]*rMat[0][1]-aDotD1[0]*rMat[1][1];
         if ( fR < -fR01 )
            return false;
      }*/

      // axis C0+t*A2xB2
      fR = aDotD0[1]*rMat[0][2]-aDotD0[0]*rMat[1][2];
      fR0 = aExtents[0]*rMatAbs[1][2] + aExtents[1]*rMatAbs[0][2];
      fR1 = bExtents[0]*rMatAbs[2][1] + bExtents[1]*rMatAbs[2][0];
      fR01 = fR0 + fR1;
      if(!dynObbFind1<FIND_CONTACT>(fR,aDotD1[1],rMat[0][2],aDotD1[0],rMat[1][2],fR01, time, tFirstContact))
         return false;
      /*if ( fR > fR01 )
      {
         fR = aDotD1[1]*rMat[0][2]-aDotD1[0]*rMat[1][2];
         if ( fR > fR01 )
            return false;
      }
      else if ( fR < -fR01 )
      {
         fR = aDotD1[1]*rMat[0][2]-aDotD1[0]*rMat[1][2];
         if ( fR < -fR01 )
            return false;
      }*/

      // At this point none of the 15 axes separate the boxes.  It is still
      // possible that they are separated as viewed in any plane orthogonal
      // to the relative direction of motion W.  In the worst case, the two
      // projected boxes are hexagons.  This requires three separating axis
      // tests per box.
      Vec3 kWxD0 = kW.cross(dist0);
      float wDotA[3], wDotB[3];

      // axis C0 + t*WxA0
      wDotA[1] = kW.dot(aAxes[1]);
      wDotA[2] = kW.dot(aAxes[2]);
      fR = Math::abs(aAxes[0].dot(kWxD0));
      fR0 = aExtents[1]*wDotA[2] + aExtents[2]*wDotA[1];
      fR1 =
         bExtents[0]*Math::abs(rMat[1][0]*wDotA[2] - rMat[2][0]*wDotA[1]) +
         bExtents[1]*Math::abs(rMat[1][1]*wDotA[2] - rMat[2][1]*wDotA[1]) +
         bExtents[2]*Math::abs(rMat[1][2]*wDotA[2] - rMat[2][2]*wDotA[1]);
      fR01 = fR0 + fR1;
      if ( fR > fR01 )
         return false;

      // axis C0 + t*WxA1
      wDotA[0] = kW.dot(aAxes[0]);
      fR = Math::abs(aAxes[1].dot(kWxD0));
      fR0 = aExtents[2]*wDotA[0] + aExtents[0]*wDotA[2];
      fR1 =
         bExtents[0]*Math::abs(rMat[2][0]*wDotA[0] - rMat[0][0]*wDotA[2]) +
         bExtents[1]*Math::abs(rMat[2][1]*wDotA[0] - rMat[0][1]*wDotA[2]) +
         bExtents[2]*Math::abs(rMat[2][2]*wDotA[0] - rMat[0][2]*wDotA[2]);
      fR01 = fR0 + fR1;
      if ( fR > fR01 )
         return false;

      // axis C0 + t*WxA2
      fR = Math::abs(aAxes[2].dot(kWxD0));
      fR0 = aExtents[0]*wDotA[1] + aExtents[1]*wDotA[0];
      fR1 =
         bExtents[0]*Math::abs(rMat[0][0]*wDotA[1] - rMat[1][0]*wDotA[0]) +
         bExtents[1]*Math::abs(rMat[0][1]*wDotA[1] - rMat[1][1]*wDotA[0]) +
         bExtents[2]*Math::abs(rMat[0][2]*wDotA[1] - rMat[1][2]*wDotA[0]);
      fR01 = fR0 + fR1;
      if ( fR > fR01 )
         return false;

      // axis C0 + t*WxB0
      wDotB[1] = kW.dot(bAxes[1]);
      wDotB[2] = kW.dot(bAxes[2]);
      fR = Math::abs(bAxes[0].dot(kWxD0));
      fR0 =
         aExtents[0]*Math::abs(rMat[0][1]*wDotB[2] - rMat[0][2]*wDotB[1]) +
         aExtents[1]*Math::abs(rMat[1][1]*wDotB[2] - rMat[1][2]*wDotB[1]) +
         aExtents[2]*Math::abs(rMat[2][1]*wDotB[2] - rMat[2][2]*wDotB[1]);
      fR1 = bExtents[1]*wDotB[2] + bExtents[2]*wDotB[1];
      fR01 = fR0 + fR1;
      if ( fR > fR01 )
         return false;

      // axis C0 + t*WxB1
      wDotB[0] = kW.dot(bAxes[0]);
      fR = Math::abs(bAxes[1].dot(kWxD0));
      fR0 =
         aExtents[0]*Math::abs(rMat[0][2]*wDotB[0] - rMat[0][0]*wDotB[2]) +
         aExtents[1]*Math::abs(rMat[1][2]*wDotB[0] - rMat[1][0]*wDotB[2]) +
         aExtents[2]*Math::abs(rMat[2][2]*wDotB[0] - rMat[2][0]*wDotB[2]);
      fR1 = bExtents[2]*wDotB[0] + bExtents[0]*wDotB[2];
      fR01 = fR0 + fR1;
      if ( fR > fR01 )
         return false;

      // axis C0 + t*WxB2
      fR = Math::abs(bAxes[2].dot(kWxD0));
      fR0 =
         aExtents[0]*Math::abs(rMat[0][0]*wDotB[1] - rMat[0][1]*wDotB[0]) +
         aExtents[1]*Math::abs(rMat[1][0]*wDotB[1] - rMat[1][1]*wDotB[0]) +
         aExtents[2]*Math::abs(rMat[2][0]*wDotB[1] - rMat[2][1]*wDotB[0]);
      fR1 = bExtents[0]*wDotB[1] + bExtents[1]*wDotB[0];
      fR01 = fR0 + fR1;
      if ( fR > fR01 )
         return false;

      return true;

   }

   // boxes have constant linear velocity
   bool TestIntersect(float time,
                      const OOBox& box0, const Vec3& vel0,
                      const OOBox& box1, const Vec3& vel1)
   {
      float unused;
      return TestIntersectOBB<false>(time, box0, vel0, box1, vel1, unused);
   }

   bool TestIntersect(float time,
                      const OOBox& box0, const Vec3& vel0,
                      const OOBox& box1, const Vec3& vel1,
                      float& tFirstContact)
   {
      return TestIntersectOBB<true>(time, box0, vel0, box1, vel1, tFirstContact);
   }



}
