/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Xforms.h,v $
 * Date modified: $Date: 2002-03-08 17:27:04 $
 * Version:       $Revision: 1.12 $
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
    * @post Rv = q P(v) q*
    * @post vector = rotquat * pure_quat_from_vector * rotquat_conj
    * @see game programming gems #1 p199
    * @see shoemake siggraph notes
    */
   template <typename DATA_TYPE>
   inline Vec<DATA_TYPE, 3>& xform( Vec<DATA_TYPE, 3>& result_vec, const Quat<DATA_TYPE>& rot, const Vec<DATA_TYPE, 3>& vector )
   {
      // easiest to write and understand (slowest too)
      // return result_vec = makeVec( rot * makePure( vector ) * makeConj( rot ) );
      
      // longer, but maybe more optimal (faster by 8% than 1st method in gcc 2.96 debug mode.)
      //Quat<DATA_TYPE> rot_conj( rot ); conj( rot_conj );
      //Quat<DATA_TYPE> quat_vector( rot * Quat<DATA_TYPE>( vector[0], vector[1], vector[2], (DATA_TYPE)0.0 ) * rot_conj );
      //result_vec[0] = quat_vector[0];
      //result_vec[1] = quat_vector[1];
      //result_vec[2] = quat_vector[2];
      //return result_vec;
      
      // completely hand expanded 
      // (faster by 28% than 1st method in gcc 2.96 debug mode.)
      // (faster by 35% than 1st method in gcc 2.96 opt3 mode (78% for doubles))
      Quat<DATA_TYPE> rot_conj( -rot[Xelt], -rot[Yelt], -rot[Zelt], rot[Welt] ); 
      Quat<DATA_TYPE> pure( vector[0], vector[1], vector[2], (DATA_TYPE)0.0 );
      Quat<DATA_TYPE> temp( 
         pure[Welt]*rot_conj[Xelt] + pure[Xelt]*rot_conj[Welt] + pure[Yelt]*rot_conj[Zelt] - pure[Zelt]*rot_conj[Yelt],
         pure[Welt]*rot_conj[Yelt] + pure[Yelt]*rot_conj[Welt] + pure[Zelt]*rot_conj[Xelt] - pure[Xelt]*rot_conj[Zelt],
         pure[Welt]*rot_conj[Zelt] + pure[Zelt]*rot_conj[Welt] + pure[Xelt]*rot_conj[Yelt] - pure[Yelt]*rot_conj[Xelt],
         pure[Welt]*rot_conj[Welt] - pure[Xelt]*rot_conj[Xelt] - pure[Yelt]*rot_conj[Yelt] - pure[Zelt]*rot_conj[Zelt] );
      
      result_vec.set( 
         rot[Welt]*temp[Xelt] + rot[Xelt]*temp[Welt] + rot[Yelt]*temp[Zelt] - rot[Zelt]*temp[Yelt],
         rot[Welt]*temp[Yelt] + rot[Yelt]*temp[Welt] + rot[Zelt]*temp[Xelt] - rot[Xelt]*temp[Zelt],
         rot[Welt]*temp[Zelt] + rot[Zelt]*temp[Welt] + rot[Xelt]*temp[Yelt] - rot[Yelt]*temp[Xelt] );
      return result_vec;
   }

   /** transform a vector by a rotation quaternion.
    * @pre give a vector
    * @post result = quat * vector
    */
   template <typename DATA_TYPE>
   inline Vec<DATA_TYPE, 3> operator*( const Quat<DATA_TYPE>& rot, const Vec<DATA_TYPE, 3>& vector )
   {
      // easiest to write and understand (slowest too)
      // return makeVec( rot * makePure( vector ) * makeConj( rot ) );
      
      // longer, but more optimal (faster by 8% than 1st method in gcc 2.96 debug mode.)
      //Quat<DATA_TYPE> rot_conj( rot ); conj( rot_conj );
      //Quat<DATA_TYPE> quat_vector( rot * Quat<DATA_TYPE>( vector[0], vector[1], vector[2], (DATA_TYPE)0.0 ) * rot_conj );
      //return Vec<DATA_TYPE, 3>( quat_vector[0], quat_vector[1], quat_vector[2] );
      
      // completely hand expanded 
      // (faster by 24% than 1st method in gcc 2.96 debug mode.)
      // (faster by 29% than 1st method in gcc 2.96 opt3 mode (74% for doubles))
      Quat<DATA_TYPE> rot_conj( -rot[Xelt], -rot[Yelt], -rot[Zelt], rot[Welt] ); 
      Quat<DATA_TYPE> pure( vector[0], vector[1], vector[2], (DATA_TYPE)0.0 );
      Quat<DATA_TYPE> temp( 
         pure[Welt]*rot_conj[Xelt] + pure[Xelt]*rot_conj[Welt] + pure[Yelt]*rot_conj[Zelt] - pure[Zelt]*rot_conj[Yelt],
         pure[Welt]*rot_conj[Yelt] + pure[Yelt]*rot_conj[Welt] + pure[Zelt]*rot_conj[Xelt] - pure[Xelt]*rot_conj[Zelt],
         pure[Welt]*rot_conj[Zelt] + pure[Zelt]*rot_conj[Welt] + pure[Xelt]*rot_conj[Yelt] - pure[Yelt]*rot_conj[Xelt],
         pure[Welt]*rot_conj[Welt] - pure[Xelt]*rot_conj[Xelt] - pure[Yelt]*rot_conj[Yelt] - pure[Zelt]*rot_conj[Zelt] );

      return Vec<DATA_TYPE, 3>( 
         rot[Welt]*temp[Xelt] + rot[Xelt]*temp[Welt] + rot[Yelt]*temp[Zelt] - rot[Zelt]*temp[Yelt],
         rot[Welt]*temp[Yelt] + rot[Yelt]*temp[Welt] + rot[Zelt]*temp[Xelt] - rot[Xelt]*temp[Zelt],
         rot[Welt]*temp[Zelt] + rot[Zelt]*temp[Welt] + rot[Xelt]*temp[Yelt] - rot[Yelt]*temp[Xelt] );
   }

   /** matrix * vector xform.
    *  multiplication of [m x k] matrix by a [k x 1] matrix (also known as a Vector...).
    *  @post This results in a full matrix xform of the vector (assumes you know what you are doing - 
    *  i.e. that you know that the last component of a vector by definition is 0.0, and changing 
    *  this might make the xform different that what you may expect).
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   Vec<DATA_TYPE, COLS> operator*( const Matrix<DATA_TYPE, ROWS, COLS>& matrix, const Vec<DATA_TYPE, COLS>& vector )
   {
      // do a standard [m x k] by [k x n] matrix multiplication (n == 1).
      Vec<DATA_TYPE, COLS> ret_vec;
      for (int iRow = 0; iRow < ROWS; ++iRow)
      {
         for (int iCol = 0; iCol < COLS; ++iCol)
         {
            ret_vec[iCol] += matrix( iRow, iCol ) * vector[iCol];
         }
      }
      return ret_vec;
   }
   
   /** matrix * vector xform (partial).
    *  multiplication of [m x k] matrix by a [k-1 x 1] matrix (also known as a Vector [with w == 0 for vectors by definition] ).
    *  @post the [k-1 x 1] vector you pass in is treated as a [vector, 0.0]
    *  @post This ends up being a partial xform using only the rotation from the matrix (vector xformed result is untranslated).
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS, unsigned COLS_MINUS_ONE>
   Vec<DATA_TYPE, COLS_MINUS_ONE> operator*( const Matrix<DATA_TYPE, ROWS, COLS>& matrix, const Vec<DATA_TYPE, COLS_MINUS_ONE>& vector )
   {
      ggtASSERT( COLS_MINUS_ONE == COLS - 1 );
      Vec<DATA_TYPE, COLS_MINUS_ONE> ret_vec;
      for (int iRow = 0; iRow < ROWS; ++iRow)
      {
         for (int iCol = 0; iCol < COLS_MINUS_ONE; ++iCol)
         {
            ret_vec[iCol] += matrix( iRow, iCol ) * vector[iCol];
         }
         //w_coord += matrix( iRow, iCol+1 ) * 0.0f;
      }
      return ret_vec;
   }
   
   /** matrix * point xform.
    *  multiplication of [m x k] matrix by a [k x 1] matrix (also known as a Point...).
    *  @post This results in a full matrix xform of the point.
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   Point<DATA_TYPE, COLS> operator*( const Matrix<DATA_TYPE, ROWS, COLS>& matrix, const Point<DATA_TYPE, COLS>& point )
   {
      // do a standard [m x k] by [k x n] matrix multiplication (n == 1).
      Point<DATA_TYPE, COLS> result;
      for (int iRow = 0; iRow < ROWS; ++iRow)
      {
         for (int iCol = 0; iCol < COLS; ++iCol)
         {
            result[iCol] += matrix( iRow, iCol ) * point[iCol];
         }
      }
      return result;
   }

   /** matrix * point xform (partial).
    *  multiplication of [m x k] matrix by a [k-1 x 1] matrix (also known as a Point [with w == 1 for points by definition] ).
    *  @post the [k-1 x 1] vector you pass in is treated as a [point, 1.0]
    *  @post This results in a full matrix xform of the point.
    */
   template <typename DATA_TYPE, unsigned ROWS, unsigned COLS, unsigned COLS_MINUS_ONE>
   Point<DATA_TYPE, COLS_MINUS_ONE> operator*( const Matrix<DATA_TYPE, ROWS, COLS>& matrix, const Point<DATA_TYPE, COLS_MINUS_ONE>& point )
   {
      ggtASSERT( COLS_MINUS_ONE == COLS - 1 );
      
      Point<DATA_TYPE, COLS_MINUS_ONE> result;
      DATA_TYPE w_coord( (DATA_TYPE)0 );
      for (int iRow = 0; iRow < ROWS; ++iRow)
      {
         int iCol;
         for (iCol = 0; iCol < COLS_MINUS_ONE; ++iCol)
         {
            result[iCol] += matrix( iRow, iCol ) * point[iCol];
         }
         w_coord += matrix( iRow, iCol );  // vec[c] += matrix( r, c ) * 1.0
      }
      
      // distribute the w param to the result, we don't want to lose this data... 
      // (divide the other elts by it)
      DATA_TYPE w_coord_div = DATA_TYPE( 1.0 ) / w_coord;
      for (int x = 0; x < COLS_MINUS_ONE; ++x)
      {
         result[x] *= w_coord_div;
      }
            
      return result;
   }
   
   
   
   
   
   
   
   
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
