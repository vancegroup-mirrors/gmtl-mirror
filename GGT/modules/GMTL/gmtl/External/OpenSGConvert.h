#ifndef GMTL_OPENSG_CONVERT_H_
#define GMTL_OPENSG_CONVERT_H_

/** @file GMTL to OpenSG conversion functions
* 
* methods to convert between gtml and opensg matrix classes
*/

#include <gmtl/Matrix.h>
#include <gmtl/Generate.h>
#include <OpenSG/OSGMatrix.h>

namespace gmtl
{

template <typename MATRIX_TYPE>
inline MATRIX_TYPE makeMatrix( osg::Matrix osg_mat, Type2Type< MATRIX_TYPE > t = Type2Type< MATRIX_TYPE >() )
{
   MATRIX_TYPE temporary;
   return convert( temporary, osg_mat );
}

template <>
inline osg::Matrix makeMatrix<osg::Matrix>( gmtl::Matrix44f mat, Type2Type< osg::Matrix > t = Type2Type< osg::Matrix >() )
{
   osg::Matrix temp_osg_mat;
   return convert( temp_osg_mat, mat );
}


/** Convert an opensg matrix to a gmtl::Matrix
*/
Matrix44f& convert( Matrix44f& mat, const osg::Matrix& osg_mat )
{
   mat.set(osg_mat.getValues());
   return mat;
}

osg::Matrix& convert(osg::Matrix& osg_mat, const Matrix44f& mat)
{
   osg_mat.setValue( mat.getData() );
   return osg_mat;
}


}

#endif

