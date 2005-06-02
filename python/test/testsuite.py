#!/usr/bin/env python

# ************************************************************* ggt-head beg
# 
#  GGT: Generic Graphics Toolkit
# 
#  Original Authors:
#    Allen Bierbaum
# 
#  -----------------------------------------------------------------
#  File:          $RCSfile: testsuite.py,v $
#  Date modified: $Date: 2005-06-02 05:54:47 $
#  Version:       $Revision: 1.1 $
#  -----------------------------------------------------------------
# 
# ********************************************************** ggt-head end
# ************************************************************** ggt-cpr beg
# 
# GGT: The Generic Graphics Toolkit
# Copyright (C) 2001,2002 Allen Bierbaum
# 
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
# 
# *********************************************************** ggt-cpr end

import unittest
import gmtl

class AABoxContainTest(unittest.TestCase):
   def testIsInVolumePt(self):
      # Test empty box.
      box = gmtl.AABoxf()
      origin = gmtl.Point3f()
      assert not gmtl.isInVolume(box, origin)

      # Test valid box with point outside.
      box2 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(1.0, 1.0, 1.0))
      pt1 = gmtl.Point3f(2.0, 2.0, 2.0)
      assert not gmtl.isInVolume(box2, pt1)
      assert not gmtl.isInVolumeExclusive(box2, pt1)

      # Test valid box with point inside.
      assert gmtl.isInVolume(box2, origin)
      assert gmtl.isInVolumeExclusive(box2, origin)

      # Test valid box with point on surface.
      pt_on_surf = gmtl.Point3f(1.0, 0.0, 0.0)
      assert gmtl.isInVolume(box2, pt_on_surf)

   def testTimingIsInVolumePt(self):
      box = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                        gmtl.Point3f(1.0, 1.0, 1.0))
      origin = gmtl.Point3f()

      iters = 400000
      use_value = 0.0

      for iter in xrange(iters):
         gmtl.isInVolume(box, origin)
         use_value = use_value + box.mMin[0] + 2.0

      assert use_value > 0.0

   def testIsInVolumeAABox(self):
      # Test valid box against empty box.
      empty = gmtl.AABoxf()
      box = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                        gmtl.Point3f(1.0, 1.0, 1.0))
      assert not gmtl.isInVolume(empty, box)
      assert not gmtl.isInVolume(box, empty)

      # Test non-overlapping valid boxes.
      box2 = gmtl.AABoxf(gmtl.Point3f(30.0, 30.0, 30.0),
                         gmtl.Point3f(40.0, 40.0, 40.0))
      assert not gmtl.isInVolume(box, box2)
      assert not gmtl.isInVolume(box2, box)

      # Test overlapping valid boxes.
      box3 = gmtl.AABoxf(gmtl.Point3f(35.0, 35.0, 35.0),
                         gmtl.Point3f(37.0, 37.0, 37.0))
      assert gmtl.isInVolume(box2, box3)
      assert gmtl.isInVolume(box3, box2)

      # Test valid box against itself
      assert gmtl.isInVolume(box, box)

   def testTimingIsInVolumeAABox(self):
      box = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                        gmtl.Point3f(1.0, 1.0, 1.0))
      box2 = gmtl.AABoxf(gmtl.Point3f(0.0, 0.0, 0.0),
                         gmtl.Point3f(-0.5, -0.5, -0.5))

      iters = 400000
      use_value = 0.0

      for iter in xrange(iters):
         gmtl.isInVolume(box, box2)
         use_value = use_value + box.mMin[0] + 2.0

      assert use_value > 0.0

   def testExtendVolumePt(self):
      # Test empty box and point.
      empty = gmtl.AABoxf()
      origin = gmtl.Point3f()
      result = gmtl.AABoxf(empty)
      gmtl.extendVolume(result, origin)
      assert not result.isEmpty()
      assert result.getMin() == origin
      assert result.getMax() == origin

      # Valid box against point inside.
      box2 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(1.0, 1.0, 1.0))
      result = gmtl.AABoxf(box2)
      gmtl.extendVolume(result, origin)
      assert not result.isEmpty()
      assert result.getMin() == box2.getMin()
      assert result.getMax() == box2.getMax()

      # Valid box with point outside.
      pt = gmtl.Point3f(30.0, 30.0, -30.0)
      expMin = gmtl.Point3f(-1.0, -1.0, -30.0)
      expMax = gmtl.Point3f(30.0, 30.0, 1.0)
      result = gmtl.AABoxf(box2)
      gmtl.extendVolume(result, pt)
      assert not result.isEmpty()
      assert result.getMin() == expMin
      assert result.getMax() == expMax

   def testTimingExtendVolumePt(self):
      box = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                        gmtl.Point3f(1.0, 1.0, 1.0))
      origin = gmtl.Point3f()

      iters = 400000
      use_value = 0.0

      for iter in xrange(iters):
         gmtl.extendVolume(box, origin)
         use_value = use_value + box.mMin[0] + 2.0

      assert use_value > 0.0

   def testExtendVolumeAABox(self):
      empty = gmtl.AABoxf()
      box = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                        gmtl.Point3f(1.0, 1.0, 1.0))

      # Both boxes empty.
      result = gmtl.AABoxf(empty)
      gmtl.extendVolume(result, empty)
      assert result.isEmpty()

      # Empty box with valid box.
      result = gmtl.AABoxf(empty)
      gmtl.extendVolume(result, box)
      assert not result.isEmpty()
      assert result.getMin() == box.getMin()
      assert result.getMax() == box.getMax()

      # Overlapping valid boxes.
      box2 = gmtl.AABoxf(gmtl.Point3f(0.0, 0.0, 0.0),
                         gmtl.Point3f(2.0, 2.0, 2.0))
      expMin = gmtl.Point3f(-1.0, -1.0, -1.0)
      expMax = gmtl.Point3f(2.0, 2.0, 2.0)
      result = gmtl.AABoxf(box)
      gmtl.extendVolume(result, box2)
      assert not result.isEmpty()
      assert result.getMin() == expMin
      assert result.getMax() == expMax

      # Non-overlapping valid boxes.
      box2 = gmtl.AABoxf(gmtl.Point3f(2.0, 2.0, 2.0),
                         gmtl.Point3f(4.0, 4.0, 4.0))
      expMin = gmtl.Point3f(-1.0, -1.0, -1.0)
      expMax = gmtl.Point3f(4.0, 4.0, 4.0)
      result = gmtl.AABoxf(box)
      gmtl.extendVolume(result, box2)
      assert not result.isEmpty()
      assert result.getMin() == expMin
      assert result.getMax() == expMax

   def testTimingExtendVolumeAABox(self):
      box = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                        gmtl.Point3f(1.0, 1.0, 1.0))
      box2 = gmtl.AABoxf(gmtl.Point3f(0.0, 0.0, 0.0),
                         gmtl.Point3f(2.0, 2.0, 2.0))

      iters = 400000
      use_value = 0.0

      for iter in xrange(iters):
         gmtl.extendVolume(box, box2)
         use_value = use_value + box.mMin[0] + 2.0

      assert use_value > 0.0

   def testMakeVolumeSphere(self):
      sph = gmtl.Spheref(gmtl.Point3f(1.0, 1.0, 1.0), 2.0)
      box = gmtl.AABoxf()

      expected_min = gmtl.Point3f(-1.0, -1.0, -1.0)
      expected_max = gmtl.Point3f(3.0, 3.0, 3.0)

      gmtl.makeVolume(box, sph)
      assert box.getMin() == expected_min
      assert box.getMax() == expected_max
      assert not box.isEmpty()

class AABoxOpsTest(unittest.TestCase):
   def testEqualityCompare(self):
      # Empty box against self.
      empty = gmtl.AABoxf()
      assert empty == empty
      assert not empty != empty

      # Empty boxes with different min.
      box1 = gmtl.AABoxf()
      box2 = gmtl.AABoxf()
      box1.setMin(gmtl.Point3f(-1.0, 0.0, 0.0))
      assert box1 != box2
      assert not box1 == box2

      # Empty boxes with different max
      box1 = gmtl.AABoxf(box2)
      box1.setMax(gmtl.Point3f(1.0, 0.0, 0.0))
      assert box1 != box2
      assert not box1 == box2

      # Non-empty box against self.
      box = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                        gmtl.Point3f(1.0, 1.0, 1.0))
      assert box == box
      assert not box != box

      # Non-empty boxes with different min.
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(1.0, 1.0, 1.0))
      box2 = gmtl.AABoxf(gmtl.Point3f(0.0, 0.0, 0.0),
                         gmtl.Point3f(1.0, 1.0, 1.0))
      assert box1 != box2
      assert not box1 == box2

      # Non-empty boxes with different max.
      box1 = gmtl.AABoxf(gmtl.Point3f(0.0, 0.0, 0.0),
                         gmtl.Point3f(1.0, 1.0, 1.0))
      box2 = gmtl.AABoxf(gmtl.Point3f(0.0, 0.0, 0.0),
                         gmtl.Point3f(2.0, 2.0, 2.0))
      assert box1 != box2
      assert not box1 == box2

   def testTimingEqualityCompare(self):
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(1.0, 1.0, 1.0))
      box2 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(2.0, 2.0, 2.0))

      iters = 400000
      true_count = 0

      for iter in xrange(iters):
         if box1 == box2:
            true_count += 1

      assert true_count == 0

      true_count = 0

      for iter in xrange(iters):
         if box1 != box2:
            true_count += 1

      assert true_count > 0

   def testIsEqual(self):
      box = gmtl.AABoxf(gmtl.Point3f(-1.0, -2.0, -3.0),
                        gmtl.Point3f(4.0, 5.0, 6.0))
      bok = gmtl.AABoxf(gmtl.Point3f(-1.0, -2.0, -3.0),
                        gmtl.Point3f(4.0, 5.0, 6.0))
      mok = gmtl.AABoxf(gmtl.Point3f(-1.0, -2.0, -3.0),
                        gmtl.Point3f(4.0, 5.0, 7.0))
      assert gmtl.isEqual(bok, box, 0.0001)
      assert bok == box
      assert bok != mok
      assert not gmtl.isEqual(bok, mok, 0.0001)
      assert gmtl.isEqual(bok, mok, 1.0001)

   def testTimingIsEqual(self):
      pass

class AABoxTest(unittest.TestCase):
   def testCreation(self):
      box = gmtl.AABoxf()
      zeroPoint = gmtl.Point3f()

      assert box.mMin == zeroPoint
      assert box.mMax == zeroPoint
      assert box.mEmpty

   def testTimingCreation(self):
      iters = 400000
      use_value = 0.0

      for iter in xrange(iters):
         box = gmtl.AABoxf()
         use_value = use_value + box.mMin[0] + 1.0

      assert use_value > 0.0

   def testCopyConstructor(self):
      box = gmtl.AABoxf()
      box.mMin.set(-2.0, -4.0, -8.0)
      box.mMax.set(2.0, 4.0, 8.0)
      box.mEmpty = False

      box_copy = gmtl.AABoxf(box)

      assert box_copy.mMin == gmtl.Point3f(-2.0, -4.0, -8.0)
      assert box_copy.mMax == gmtl.Point3f( 2.0,  4.0,  8.0)
      assert box_copy.mEmpty == False

   def testTimingCopyConstruct(self):
      iters = 400000
      box2 = gmtl.AABoxf()
      box2.mMin[0] = 2.0
      use_value = 0.0

      for iter in xrange(iters):
         box2_copy = gmtl.AABoxf(box2)
         use_value += box2_copy.mMin[0]

      assert use_value > 0.0

   def testConstructors(self):
      box = gmtl.AABoxf(gmtl.Point3f(1.0, 2.0, 3.0),
                        gmtl.Point3f(4.0, 5.0, 6.0))
      assert box.mMin == gmtl.Point3f(1.0, 2.0, 3.0)
      assert box.mMax == gmtl.Point3f(4.0, 5.0, 6.0)
      assert box.mEmpty == False

   def testTimingConstructors(self):
      iters = 400000
      use_value = 0.0

      for iter in xrange(iters):
         box2 = gmtl.AABoxf(gmtl.Point3f(1.0, 2.0, 3.0),
                            gmtl.Point3f(4.0, 5.0, 6.0))
         use_value += box2.mMin[0]

      assert use_value > 0.0

   def testGetMin(self):
      amin = gmtl.Point3f(-1.0, -2.0, -3.0)
      box = gmtl.AABoxf(amin, gmtl.Point3f())
      assert box.getMin() == amin

   def testTimingGetMin(self):
      amin = gmtl.Point3f(-1.0, -2.0, -3.0)
      box = gmtl.AABoxf(amin, gmtl.Point3f())

      iters = 400000
      use_value = 0.0

      for iter in xrange(iters):
         amin = box.getMin()
         use_value = use_value - amin[0]

      assert use_value > 0.0

   def testGetMax(self):
      amax = gmtl.Point3f(1.0, 2.0, 3.0)
      box = gmtl.AABoxf(gmtl.Point3f(), amax)
      assert box.getMax() == amax

   def testTimingGetMax(self):
      amax = gmtl.Point3f(1.0, 2.0, 3.0)
      box = gmtl.AABoxf(gmtl.Point3f(), amax)

      iters = 400000
      use_value = 0.0

      for iter in xrange(iters):
         amax = box.getMax()
         use_value = use_value + amax[0]

      assert use_value > 0.0

   def testIsEmpty(self):
      box = gmtl.AABoxf()
      box2 = gmtl.AABoxf(gmtl.Point3f(-1.0, -2.0, -3.0),
                         gmtl.Point3f(1.0, 2.0, 3.0))
      assert box.isEmpty() == True
      assert box2.isEmpty() == False

   def testTimingIsEmpty(self):
      box = gmtl.AABoxf()

      iters = 400000
      use_value = 0

      for iter in xrange(iters):
         if box.isEmpty():
            use_value += 1

      use_value > 0

   def testSetMin(self):
      box = gmtl.AABoxf()
      amin = gmtl.Point3f(-2.0, -4.0, -1.0)
      box.setMin(amin)
      assert box.getMin() == amin

   def testTimingSetMin(self):
      box = gmtl.AABoxf()
      amin = gmtl.Point3f()

      iters = 400000

      for iter in xrange(iters):
         amin.set(float(iter), float(iter), float(iter))
         box.setMin(amin)

   def testSetMax(self):
      box = gmtl.AABoxf()
      amax = gmtl.Point3f(2.0, 4.0, 1.0)
      box.setMax(amax)
      assert box.getMax() == amax

   def testTimingSetMax(self):
      box = gmtl.AABoxf()
      amax = gmtl.Point3f()

      iters = 400000

      for iter in xrange(iters):
         amax.set(float(iter), float(iter), float(iter))
         box.setMax(amax)

   def testSetEmpty(self):
      box = gmtl.AABoxf()
      box.setEmpty(False)
      assert box.isEmpty() == False

   def setTimingSetEmpty(self):
      box = gmtl.AABoxf()

      iters = 400000
      use_value = 0

      for iter in xrange(iters):
         box.setEmpty(True)
         if box.mEmpty:
            use_value += 1

      assert use_value > 0

class AxisAngleClassTest(unittest.TestCase):
   def testAxisAngleClassTestCreation(self):
      # Test that it initializes to the identity.
      q = gmtl.AxisAnglef()
      assert q[0] == 0.0
      assert q[1] == 1.0
      assert q[2] == 0.0
      assert q[3] == 0.0

      # Try out set...
      q.set(1.0, 2.0, 3.0, 902)
      assert q[0] == 1.0
      assert q[1] == 2.0
      assert q[2] == 3.0
      assert q[3] == 902

      # Try out setting with brackets
      q[0] = 5.0
      q[1] = 6.0
      q[2] = 7.0
      q[3] = 901
      assert q[0] == 5.0
      assert q[1] == 6.0
      assert q[2] == 7.0
      assert q[3] == 901

      # Try out element constructor.
      q2 = gmtl.AxisAnglef(10.0, 11.0, 12.0, 902)
      assert q2[0] == 10.0
      assert q2[1] == 11.0
      assert q2[2] == 12.0
      assert q2[3] == 902

      # Try out copy constructor.
      q3 = gmtl.AxisAnglef(q)
      assert q3[0] == 5.0
      assert q3[1] == 6.0
      assert q3[2] == 7.0
      assert q3[3] == 901

   def testAxisAngleTimingDefaultConstructor(self):
      iters = 400000
      use_value = 1.0

      for iter in xrange(iters):
         q = gmtl.AxisAnglef()
         use_value += q.data[0]

      assert use_value != 0.0

   def testAxisAngleTimingElementConstructor(self):
      iters = 400000
      use_value = 1.0

      for iter in xrange(iters):
         q2 = gmtl.AxisAnglef(10.0, 11.0, 12.0, 901)
         use_value += q2.data[0]

      assert use_value != 0.0

   def testAxisAngleTimingCopyConstructor(self):
      iters = 400000
      use_value = 1.0
      q = gmtl.AxisAnglef(67.0, 68.0, 69.0, 901)

      for iter in xrange(iters):
         q3 = gmtl.AxisAnglef(q)
         use_value += q3.data[0]

      assert use_value != 0.0

   def testAxisAngleTimingSet(self):
      iters = 400000
      use_value = 0.0
      q = gmtl.AxisAnglef()

      for iter in xrange(iters):
         q.set(1.0, 2.0, 3.0, 901)
         use_value += q[0]

      assert use_value >= 0.0

   def testAxisAngleTimingOpBracket(self):
      iters = 400000
      use_value = 0.0
      q = gmtl.AxisAnglef()
      x = 102.0
      y = 103.0
      z = 101.0
      w = 901

      for iter in xrange(iters):
         q[0] = x
         q[1] = y
         q[2] = z
         q[3] = w
         use_value = use_value + x + y + z + w

      assert use_value > 0.0

   def testAxisAngleTimingGetData(self):
      iters = 400000
      use_value = 0.0
      q = gmtl.AxisAnglef(1.0, 2.0, 3.0, 901)

      for iter in xrange(iters):
         d = q.getData()
         use_value += d[1]

      assert use_value > 0.0

class AxisAngleCompareTest(unittest.TestCase):
   def __testAxisAngleEqualityTest(self, type):
      quat1 = type()
      quat1.set(1.0, 2.0, 34.0, 980.0)
      quat2 = type(quat1)
      assert quat1 == quat2
      assert quat2 == quat1

      for j in range(4):
         quat2[j] = 1221.0
         assert quat1 != quat2
         assert not quat1 == quat2
         quat2[j] = quat1[j]    # put it back

      # Test for epsilon equals working.
      assert gmtl.isEqual(quat1, quat2)
      assert gmtl.isEqual(quat1, quat2, 0.0)
      assert gmtl.isEqual(quat2, quat1, 0.0)
      assert gmtl.isEqual(quat2, quat1, 100000.0)
      eps = 10.0
      for j in range(4):
         quat2[j] = quat1[j] - (eps / 2.0)
         assert gmtl.isEqual(quat1, quat2, eps)
         assert not gmtl.isEqual(quat1, quat2, eps / 3.0)
         quat2[j] = quat1[j]    # put it back

   def testAxisAngleEqualityFloatTest(self):
      for i in range(15):
         self.__testAxisAngleEqualityTest(gmtl.AxisAnglef)

   def testAxisAngleEqualityDoubleTest(self):
      for i in range(15):
         self.__testAxisAngleEqualityTest(gmtl.AxisAngled)

   def testAxisAngleTimingOpEqualityTest(self):
      # Test overhead of creation
      iters = 400000
      src_quat11 = gmtl.AxisAnglef()
      src_quat22 = gmtl.AxisAnglef()
      src_quat33 = gmtl.AxisAnglef()
      src_quat34 = gmtl.AxisAnglef()
      src_quat44 = gmtl.AxisAnglef()
      src_quat101 = gmtl.AxisAngled()

      # half of them will be equal.
      src_quat11[3] = 1.0
      src_quat22[2] = 1.0
      src_quat11[1] = 2.0

      test_quat11 = gmtl.AxisAnglef(src_quat11)
      test_quat22 = gmtl.AxisAnglef(src_quat22)
      test_quat33 = gmtl.AxisAnglef(src_quat33)
      test_quat34 = gmtl.AxisAnglef(src_quat34)
      test_quat44 = gmtl.AxisAnglef(src_quat44)
      test_quat101 = gmtl.AxisAngled(src_quat101)

      # have of them will be not equal.
      src_quat34[0] = 2.0
      src_quat44[1] = 3.0
      src_quat101[3] = 1.0

      true_count = 0

      for iter in xrange(iters):
         if src_quat11 == test_quat11:
            true_count += 1

         if src_quat22 == test_quat22:
            true_count += 1

         if src_quat33 == test_quat33:
            true_count += 1

         if src_quat34 == test_quat34:
            true_count += 1

         if src_quat44 == test_quat44:
            true_count += 1

         if src_quat101 == test_quat101:
            true_count += 1

      assert true_count > 0

   def testAxisAngleTimingOpNotEqualityTest(self):
      # Test overhead of creation
      iters = 400000
      src_quat11 = gmtl.AxisAnglef()
      src_quat22 = gmtl.AxisAnglef()
      src_quat33 = gmtl.AxisAnglef()
      src_quat34 = gmtl.AxisAnglef()
      src_quat44 = gmtl.AxisAnglef()
      src_quat101 = gmtl.AxisAngled()

      # half of them will be equal.
      src_quat11[3] = 1.0
      src_quat22[2] = 1.0
      src_quat11[1] = 2.0

      test_quat11 = gmtl.AxisAnglef(src_quat11)
      test_quat22 = gmtl.AxisAnglef(src_quat22)
      test_quat33 = gmtl.AxisAnglef(src_quat33)
      test_quat34 = gmtl.AxisAnglef(src_quat34)
      test_quat44 = gmtl.AxisAnglef(src_quat44)
      test_quat101 = gmtl.AxisAngled(src_quat101)

      # have of them will be not equal.
      src_quat34[0] = 2.0
      src_quat44[1] = 3.0
      src_quat101[3] = 1.0

      true_count = 0

      for iter in xrange(iters):
         if src_quat11 != test_quat11:
            true_count += 1

         if src_quat22 != test_quat22:
            true_count += 1

         if src_quat33 != test_quat33:
            true_count += 1

         if src_quat34 != test_quat34:
            true_count += 1

         if src_quat44 != test_quat44:
            true_count += 1

         if src_quat101 != test_quat101:
            true_count += 1

      assert true_count > 0

   def testAxisAngleTimingIsEqualTest(self):
      # Test overhead of creation
      iters = 400000
      src_quat11 = gmtl.AxisAnglef()
      src_quat22 = gmtl.AxisAnglef()
      src_quat33 = gmtl.AxisAnglef()
      src_quat34 = gmtl.AxisAnglef()
      src_quat44 = gmtl.AxisAnglef()
      src_quat101 = gmtl.AxisAngled()

      # half of them will be equal.
      src_quat11[3] = 1.0
      src_quat22[2] = 1.0
      src_quat11[1] = 2.0

      test_quat11 = gmtl.AxisAnglef(src_quat11)
      test_quat22 = gmtl.AxisAnglef(src_quat22)
      test_quat33 = gmtl.AxisAnglef(src_quat33)
      test_quat34 = gmtl.AxisAnglef(src_quat34)
      test_quat44 = gmtl.AxisAnglef(src_quat44)
      test_quat101 = gmtl.AxisAngled(src_quat101)

      # have of them will be not equal.
      src_quat34[0] = 2.0
      src_quat44[1] = 3.0
      src_quat101[3] = 1.0

      true_count = 0

      for iter in xrange(iters):
         if gmtl.isEqual(src_quat11, test_quat11, 0.0):
            true_count += 1

         if gmtl.isEqual(src_quat22, test_quat22, 0.2):
            true_count += 1

         if gmtl.isEqual(src_quat33, test_quat33, 0.3):
            true_count += 1

         if gmtl.isEqual(src_quat34, test_quat34, 0.6):
            true_count += 1

         if gmtl.isEqual(src_quat44, test_quat44, 0.8):
            true_count += 1

         if gmtl.isEqual(src_quat101, test_quat101, 111.1):
            true_count += 1

      assert true_count > 0

class MatrixClassTest(unittest.TestCase):
   def testMatrixIdentity(self):
      iters = 25000
      use_value = 0.0

      for iter in xrange(iters):
         test_mat33 = gmtl.Matrix33f()
         test_mat33.data[4] = 2.0
         test_mat44 = gmtl.Matrix44f()
         test_mat44.data[15] = 3.0

         use_value = use_value + test_mat33.data[4] + test_mat44.data[15]

      assert use_value > 0.0

   def testTimingCopyConstructor(self):
      src_mat33 = gmtl.Matrix33f()
      src_mat33.data[5] = 2.0
      src_mat44 = gmtl.Matrix44f()
      src_mat44.data[15] = 3.0

      iters = 25000
      for iter in xrange(iters):
         test_mat33 = gmtl.Matrix33f(src_mat33)
         test_mat44 = gmtl.Matrix44f(src_mat44)

         test_mat33.data[4] = 2.0
         test_mat44.data[15] = 3.0

   def testTimingOpEqual(self):
      src_mat33 = gmtl.Matrix33f()
      src_mat33.data[4] = 2.0
      src_mat44 = gmtl.Matrix44f()
      src_mat44.data[15] = 3.0

      iters = 25000

      test_mat33 = gmtl.Matrix33f()
      test_mat44 = gmtl.Matrix44f()

      for iter in xrange(iters):
         test_mat33 = src_mat33
         test_mat44 = src_mat44

   def testTimingOpBracket(self):
      iters = 25000
      test_mat33 = gmtl.Matrix33f()
      test_mat44 = gmtl.Matrix44f()

      for iter in xrange(iters):
         test_mat33[1][1] = 0.0
         test_mat44[3][3] = 0.0

   def testTimingSetPtr(self):
      iters = 25000
      test_mat33 = gmtl.Matrix33f()
      test_mat44 = gmtl.Matrix44f()

      for iter in xrange(iters):
         test_mat33.set(gmtl.Matrix33f().getData())
         test_mat44.set(gmtl.Matrix44f().getData())

   def testTimingSetTransposePtr(self):
      iters = 25000

      test_mat33 = gmtl.Matrix33f()
      test_mat44 = gmtl.Matrix44f()

      for iter in xrange(iters):
         test_mat33.setTranspose(gmtl.Matrix33f().getData())
         test_mat44.setTranspose(gmtl.Matrix44f().getData())

   def testTimingGetData(self):
      iters = 25000

      test_mat33 = gmtl.Matrix33f()
      test_mat44 = gmtl.Matrix44f()
      bok = 0.0
      bokk = 0.0

      for iter in xrange(iters):
         temp2 = test_mat33.getData()
         bok += temp2[3]
         temp4 = test_mat44.getData()
         bokk += temp4[15]

   def testTimingSet(self):
      iters = 25000

      test_mat33 = gmtl.Matrix33f()
      test_mat44 = gmtl.Matrix44f()

      for iter in xrange(iters):
         test_mat33.set(2, 3, 4, 5, 6, 7, 7, 10, 1451235)
         test_mat44.set(2, 3, 4, 5, 6, 7, 7, 10, 1451235, 1, 2, 3, 1, 2, 3, 4)

   def testMatrixIdentity(self):
      mat44 = gmtl.Matrix44f()
      assert mat44[0][0] == 1.0
      assert mat44[1][1] == 1.0
      assert mat44[2][2] == 1.0
      assert mat44[3][3] == 1.0

      assert mat44[1][0] == 0.0
      assert mat44[2][0] == 0.0
      assert mat44[3][0] == 0.0
      assert mat44[0][1] == 0.0
      assert mat44[2][1] == 0.0
      assert mat44[3][1] == 0.0
      assert mat44[0][2] == 0.0
      assert mat44[1][2] == 0.0
      assert mat44[3][2] == 0.0
      assert mat44[0][3] == 0.0
      assert mat44[1][3] == 0.0
      assert mat44[2][3] == 0.0

      mat33 = gmtl.Matrix33f()
      assert mat44[0][0] == 1.0
      assert mat44[1][1] == 1.0
      assert mat44[2][2] == 1.0

      assert mat44[1][0] == 0.0
      assert mat44[2][0] == 0.0
      assert mat44[0][1] == 0.0
      assert mat44[2][1] == 0.0
      assert mat44[0][2] == 0.0
      assert mat44[1][2] == 0.0

      # Make sure copy constructor works.
      src_mat = gmtl.Matrix44f()
      src_mat.set(1.0, 2.0, 3.0, 4.0, 
                  5.0, 6.0, 7.0, 8.0, 
                  9.0, 1.0, 2.0, 3.0, 
                  4.0, 5.0, 6.0, 7.0)
      test_mat = gmtl.Matrix44f(src_mat)
      assert src_mat == test_mat

      src_mat = gmtl.Matrix33f()
      src_mat.set(1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0)
      test_mat = gmtl.Matrix33f(src_mat)
      assert src_mat == test_mat

      # Make sure assginment works (this is rather pointless in Python).
      src_mat = gmtl.Matrix44f()
      src_mat.set(1.0, 2.0, 3.0, 4.0, 
                  5.0, 6.0, 7.0, 8.0, 
                  9.0, 1.0, 2.0, 3.0, 
                  4.0, 5.0, 6.0, 7.0)
      test_mat = src_mat
      assert test_mat == src_mat

      src_mat = gmtl.Matrix33f()
      src_mat.set(1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0)
      test_mat = src_mat
      assert src_mat == test_mat

   def testMatrixSetPtr(self):
      mat44 = [0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0,
               12.0, 13.0, 14.0, 15.0]
      test_mat = gmtl.Matrix44f()
      test_mat.set(mat44)

      assert test_mat[0][0] == 0
      assert test_mat[1][0] == 1
      assert test_mat[2][0] == 2
      assert test_mat[3][0] == 3
      assert test_mat[0][1] == 4
      assert test_mat[1][1] == 5
      assert test_mat[2][1] == 6
      assert test_mat[3][1] == 7
      assert test_mat[0][2] == 8
      assert test_mat[1][2] == 9
      assert test_mat[2][2] == 10
      assert test_mat[3][2] == 11
      assert test_mat[0][3] == 12
      assert test_mat[1][3] == 13
      assert test_mat[2][3] == 14
      assert test_mat[3][3] == 15

      mat33 = [0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0]
      test_mat = gmtl.Matrix33f()
      test_mat.set(mat33)

      assert test_mat[0][0] == 0
      assert test_mat[1][0] == 1
      assert test_mat[2][0] == 2
      assert test_mat[0][1] == 3
      assert test_mat[1][1] == 4
      assert test_mat[2][1] == 5
      assert test_mat[0][2] == 6
      assert test_mat[1][2] == 7
      assert test_mat[2][2] == 8

   def testMatrixSetTransposePtr(self):
      mat44 = [0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0,
               12.0, 13.0, 14.0, 15.0]
      test_mat = gmtl.Matrix44f()
      test_mat.setTranspose(mat44)

      assert test_mat[0][0] == 0
      assert test_mat[0][1] == 1
      assert test_mat[0][2] == 2
      assert test_mat[0][3] == 3
      assert test_mat[1][0] == 4
      assert test_mat[1][1] == 5
      assert test_mat[1][2] == 6
      assert test_mat[1][3] == 7
      assert test_mat[2][0] == 8
      assert test_mat[2][1] == 9
      assert test_mat[2][2] == 10
      assert test_mat[2][3] == 11
      assert test_mat[3][0] == 12
      assert test_mat[3][1] == 13
      assert test_mat[3][2] == 14
      assert test_mat[3][3] == 15

      mat33 = [0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0]
      test_mat = gmtl.Matrix33f()
      test_mat.setTranspose(mat33)

      assert test_mat[0][0] == 0
      assert test_mat[0][1] == 1
      assert test_mat[0][2] == 2
      assert test_mat[1][0] == 3
      assert test_mat[1][1] == 4
      assert test_mat[1][2] == 5
      assert test_mat[2][0] == 6
      assert test_mat[2][1] == 7
      assert test_mat[2][2] == 8

   def testMatrix44Creation(self):
      src_mat = gmtl.Matrix44f()
      src_mat.set(0.0,  1.0,  2.0,  3.0,
                  4.0,  5.0,  6.0,  7.0,
                  8.0,  9.0,  10.0, 11.0,
                  12.0, 13.0, 14.0, 15.0)

      assert src_mat[0][0] == 0
      assert src_mat[1][0] == 4
      assert src_mat[2][0] == 8
      assert src_mat[3][0] == 12
      assert src_mat[0][1] == 1
      assert src_mat[1][1] == 5
      assert src_mat[2][1] == 9
      assert src_mat[3][1] == 13
      assert src_mat[0][2] == 2
      assert src_mat[1][2] == 6
      assert src_mat[2][2] == 10
      assert src_mat[3][2] == 14
      assert src_mat[0][3] == 3
      assert src_mat[1][3] == 7
      assert src_mat[2][3] == 11
      assert src_mat[3][3] == 15

   def testMatrix33Creation(self):
      src_mat = gmtl.Matrix33f()
      src_mat.set(0.0, 1.0, 2.0,
                  3.0, 4.0, 5.0,
                  6.0, 7.0, 8.0)

      assert src_mat[0][0] == 0
      assert src_mat[1][0] == 3
      assert src_mat[2][0] == 6
      assert src_mat[0][1] == 1
      assert src_mat[1][1] == 4
      assert src_mat[2][1] == 7
      assert src_mat[0][2] == 2
      assert src_mat[1][2] == 5
      assert src_mat[2][2] == 8

def getTimingTests(testCase):
   return [m for m in testCase.__dict__.keys() if m.find('Timing') != -1]

def getTests(testCase):
#   timing_tests = getTimingTests(testCase)
   all_tests = [m for m in testCase.__dict__.keys() if m.startswith('test')]
#   for t in timing_tests:
#      all_tests.remove(t)

   return all_tests

suite = unittest.TestSuite()
#suite.addTests(map(AABoxContainTest, getTests(AABoxContainTest)))
#suite.addTests(map(AABoxOpsTest, getTests(AABoxOpsTest)))
#suite.addTests(map(AABoxTest, getTests(AABoxTest)))
#suite.addTests(map(AxisAngleClassTest, getTests(AxisAngleClassTest)))
suite.addTests(map(AxisAngleCompareTest, getTests(AxisAngleCompareTest)))
#suite.addTests(map(MatrixClassTest, getTests(MatrixClassTest)))

runner = unittest.TextTestRunner()
runner.run(suite)
