#include <gmtl/gmtl.h>
#include <gmtl/Matrix.h>

int main()
{
   /** Example of creating a matrix and doing stuff */
   gmtl::Matrix44f test_matrix;
   gmtl::invert(test_matrix);
   
   /** Here is an example of creating a Vector */
   gmtl::Vec3f test_vector;
   test_vector += gmtl::Vec3f(1.0, 0.0f, 1.0f);

   return 1;
}
