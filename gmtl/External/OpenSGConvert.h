#ifndef GMTL_OPENSG_CONVERT_H_
#define GMTL_OPENSG_CONVERT_H_

/** @file OpenSGConvert.h GMTL to OpenSG conversion functions
* 
* methods to convert between gtml and opensg matrix classes
*/

#include <gmtl/Matrix.h>
#include <gmtl/Generate.h>
#include <OpenSG/OSGMatrix.h>

namespace gmtl
{

/** Convert an opensg matrix to a gmtl::Matrix
*/
inline
Matrix44f& set( Matrix44f& mat, const osg::Matrix& osg_mat )
{
   mat.set(osg_mat.getValues());
   return mat;
}

inline
osg::Matrix& set(osg::Matrix& osg_mat, const Matrix44f& mat)
{
   osg_mat.setValue( mat.getData() );
   return osg_mat;
}

}

#endif

