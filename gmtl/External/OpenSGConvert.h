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

