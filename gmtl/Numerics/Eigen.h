/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Eigen.h,v $
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
//
// XXX: Based on source code from: Magic Software, Inc.
//
#ifndef _EIGEN_H
#define _EIGEN_H

#include <GMTL/gmtlDefines.h>

namespace gmtl
{

class Eigen
{
public:
    Eigen (int iSize);
    ~Eigen ();

    // set the matrix for eigensolving
    float& Matrix (int iRow, int iCol);
    void SetMatrix (float** aafMat);

    // get the results of eigensolving (eigenvectors are columns of matrix)
    float GetEigenvalue (int i) const;
    float GetEigenvector (int iRow, int iCol) const;
    float* GetEigenvalue ();
    float** GetEigenvector ();

    // solve eigensystem
    void EigenStuff2 ();
    void EigenStuff3 ();
    void EigenStuff4 ();
    void EigenStuffN ();
    void EigenStuff  ();

    // solve eigensystem, use decreasing sort on eigenvalues
    void DecrSortEigenStuff2 ();
    void DecrSortEigenStuff3 ();
    void DecrSortEigenStuff4 ();
    void DecrSortEigenStuffN ();
    void DecrSortEigenStuff  ();

    // solve eigensystem, use increasing sort on eigenvalues
    void IncrSortEigenStuff2 ();
    void IncrSortEigenStuff3 ();
    void IncrSortEigenStuff4 ();
    void IncrSortEigenStuffN ();
    void IncrSortEigenStuff  ();

protected:
    int m_iSize;
    float** m_aafMat;
    float* m_afDiag;
    float* m_afSubd;

    // Householder reduction to tridiagonal form
    static void Tridiagonal2 (float** aafMat, float* afDiag,
        float* afSubd);
    static void Tridiagonal3 (float** aafMat, float* afDiag,
        float* afSubd);
    static void Tridiagonal4 (float** aafMat, float* afDiag,
        float* afSubd);
    static void TridiagonalN (int iSize, float** aafMat, float* afDiag,
        float* afSubd);

    // QL algorithm with implicit shifting, applies to tridiagonal matrices
    static bool QLAlgorithm (int iSize, float* afDiag, float* afSubd,
        float** aafMat);

    // sort eigenvalues from largest to smallest
    static void DecreasingSort (int iSize, float* afEigval,
        float** aafEigvec);

    // sort eigenvalues from smallest to largest
    static void IncreasingSort (int iSize, float* afEigval,
        float** aafEigvec);
};

//---------------------------------------------------------------------------
inline float& Eigen::Matrix (int iRow, int iCol)
{
    return m_aafMat[iRow][iCol];
}
//---------------------------------------------------------------------------
inline float Eigen::GetEigenvalue (int i) const
{
    return m_afDiag[i];
}
//---------------------------------------------------------------------------
inline float Eigen::GetEigenvector (int iRow, int iCol) const
{
    return m_aafMat[iRow][iCol];
}
//---------------------------------------------------------------------------
inline float* Eigen::GetEigenvalue ()
{
    return m_afDiag;
}
//---------------------------------------------------------------------------
inline float** Eigen::GetEigenvector ()
{
    return m_aafMat;
}
//---------------------------------------------------------------------------

};
#endif
