/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Xforms.h,v $
 * Date modified: $Date: 2002-02-28 14:24:12 $
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
#ifndef _GMTL___XFORMS_H_
#define _GMTL___XFORMS_H_

#include <gmtl/gmtlConfig.h>
#include <gmtl/Vec.h>
#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Quat.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Convert.h>
#include <gmtl/Generate.h>

namespace gmtl
{
   /** transform a vector by a rotation quaternion.
    * @pre give a vector
    * @post result = quat * vector
    * @see game programming gems #1 p199
    * @see shoemake siggraph notes
    */
   template <typename DATA_TYPE>
   inline Vec<DATA_TYPE, 3>& xform( Vec<DATA_TYPE, 3>& result_vec, const Quat<DATA_TYPE>& rot, const Vec<DATA_TYPE, 3>& vector )
   {
      // shoemake original (left hand rule):
      // return makeVec( result_vec, makeInvert( rot ) * makePure( vector ) * rot );

      // shoemake recent version (right hand rule):
      // return result_vec = makeVec( rot * makePure( vector ) * makeInvert( rot ) );
      return result_vec = makeVec( rot * makePure( vector ) * makeConj( rot ) );
   }

   /** transform a vector by a rotation quaternion.
    * @pre give a vector
    * @post result = quat * vector
    */
   template <typename DATA_TYPE>
   inline Vec<DATA_TYPE, 3> operator*( const Quat<DATA_TYPE>& rot, const Vec<DATA_TYPE, 3>& vector )
   {
      // shoemake original (left hand rule):
      // return makeVec( result_vec, makeInvert( rot ) * makePure( vector ) * rot );

      // shoemake recent version (right hand rule):
      // return makeVec( rot * makePure( vector ) * makeInvert( rot ) );
      return makeVec( rot * makePure( vector ) * makeConj( rot ) );
   }

   /** matrix * vector xform.
    *  multiplication of [m x n] matrix by a [n x 1] matrix (aka, a Vector... :).
    *  @post This results in a full matrix xform of the vector (assumes you know what you are doing - 
    *  i.e. that you know that the last component of a vector by definition is 0.0, and changing 
    *  this might make the xform different that what you may expect).
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   Vec<DATA_TYPE, COLS> operator*( const Matrix<DATA_TYPE, ROWS, COLS>& matrix, const Vec<DATA_TYPE, COLS>& vector )
   {
      // do a standard [m x n] by [n x k] matrix multiplication (k == 1).
      Vec<DATA_TYPE, COLS> ret_vec( 0, 0, 0, 0 );
      for (int iRow = 0; iRow < ROWS; ++iRow)
      {
         for (int iCol = 0; iCol < COLS; ++iCol)
         {
            ret_vec[iCol] += vector[iCol] * matrix( iRow, iCol );
         }
      }
      return ret_vec;
   }
   
   /** matrix * vector xform (partial).
    *  multiplication of [m x n] matrix by a [n-1 x 1] matrix (aka, a Vector... :).
    *  @post the [n-1 x 1] vector you pass in is treated as a [vector, 0.0]
    *  @post This ends up being a partial xform using only the rotation from the matrix (vector xformed result is untranslated).
    */
   /*
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   Vec<DATA_TYPE, (COLS-1)> operator*( const Matrix<DATA_TYPE, ROWS, COLS>& matrix, const Vec<DATA_TYPE, (COLS-1)>& vector )
   {
      //assert( SIZE == COLS-1 );
      Vec<DATA_TYPE, (COLS-1)> ret_vec( 0, 0, 0, 0 );
      for (int iRow = 0; iRow < ROWS; ++iRow)
      {
         for (int iCol = 0; iCol < COLS - 1; ++iCol)
         {
            ret_vec[iCol] += vector[iCol] * matrix( iRow, iCol );
         }
         //ret_vec[iCol] += 0.0f * matrix( iRow, iCol+1 );
      }
      return ret_vec;
   }
   */
   
   /** matrix * point xform.
    *  multiplication of [m x n] matrix by a [n x 1] matrix (aka, a Point... :).
    *  @post This results in a full matrix xform of the point.
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   Point<DATA_TYPE, COLS> operator*( const Matrix<DATA_TYPE, ROWS, COLS>& matrix, const Point<DATA_TYPE, COLS>& point )
   {
      // do a standard [m x n] by [n x k] matrix multiplication (k == 1).
      Point<DATA_TYPE, COLS> result( 0, 0, 0, 0 );
      for (int iRow = 0; iRow < ROWS; ++iRow)
      {
         for (int iCol = 0; iCol < COLS; ++iCol)
         {
            result[iCol] += point[iCol] * matrix( iRow, iCol );
         }
      }
      return result;
   }

   /** matrix * point xform (partial).
    *  multiplication of [m x n] matrix by a [n-1 x 1] matrix (aka, a Point... :).
    *  @post the [n-1 x 1] vector you pass in is treated as a [point, 1.0]
    *  @post This results in a full matrix xform of the point.
    */
   /*
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS, unsigned SIZE>
   Point<DATA_TYPE, SIZE> operator*( const Matrix<DATA_TYPE, ROWS, COLS>& matrix, const Point<DATA_TYPE, SIZE>& point )
   {
      assert( SIZE == COLS-1 );
      Point<DATA_TYPE, SIZE> result( 0, 0, 0, 0 );
      for (int iRow = 0; iRow < ROWS; ++iRow)
      {
         int iCol;
         for (iCol = 0; iCol < COLS - 1; ++iCol)
         {
            result[iCol] += point[iCol] * matrix( iRow, iCol );
         }
         result[iCol] += matrix( iRow, iCol+1 );  // vec[c] += 1.0 * matrix( r, c )
      }
      return result;
   }
   
   */
   
   
   
   
   
   
   
   
   
   
   // old xform stuff...
/*
// XXX: Assuming that there is no projective portion to the matrix or homogeneous coord
// NOTE: It is a vec, so we don't deal with the translation
Vec3 operator*(const Matrix& mat, const Vec3& vec)
{

   Vec3 ret_vec;
   for(int iRow=0;iRow<3;iRow++)
   {
      ret_vec[iRow] = (vec[0]* (mat[0][iRow]))
                    + (vec[1]* (mat[1][iRow]))
                    + (vec[2]* (mat[2][iRow]));
   }
   return ret_vec;
}

// XXX: Assuming no projective or homogeneous coord to the mat
Point3 operator*(const Matrix& mat, const Point3& point)
{
   Point3 ret_pt;
   for(int iRow=0;iRow<3;iRow++)
   {
      ret_pt[iRow] = (point[0]* (mat[0][iRow]))
                   + (point[1]* (mat[1][iRow]))
                   + (point[2]* (mat[2][iRow]))
                   + (mat[3][iRow]);
   }
   return ret_pt;
}

// Xform an OOB by a matrix
// NOTE: This will NOT work if the matrix has shear or scale
OOBox operator*(const Matrix& mat, const OOBox& box)
{
   OOBox ret_box;

   ret_box.center() = mat * box.center();

   ret_box.axis(0) = mat * ret_box.axis(0);
   ret_box.axis(1) = mat * ret_box.axis(1);
   ret_box.axis(2) = mat * ret_box.axis(2);

   ret_box.halfLen(0) = box.halfLen(0);
   ret_box.halfLen(1) = box.halfLen(1);
   ret_box.halfLen(2) = box.halfLen(2);

   return ret_box;
}
*/

};

#endif
