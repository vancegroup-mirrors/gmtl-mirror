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
#  Date modified: $Date: 2005-06-03 22:52:43 $
#  Version:       $Revision: 1.5 $
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

import math
import unittest
import gmtl
import random


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

class ConvertTest(unittest.TestCase):
   def testConvertVecToPureQuat(self):
      eps = 0.0001
      vec = gmtl.Vec3f(1.0, 2.0, 3.0)
      quat = gmtl.Quatf(4.0, 5.0, 6.0, 1.0)
      expected = gmtl.Quatf(1.0, 2.0, 3.0, 0.0)

      bok = gmtl.setPure(quat, vec)
      assert gmtl.isEqual(expected, quat, eps)
      assert gmtl.isEqual(expected, bok, eps)

   def testConvertQuatMat_MatQuat(self):
      eps = 0.0001
      mat1 = gmtl.Matrix44f()

      # Identity, quat0 -> mat1 -> quat1 -> mat2
      quat0 = gmtl.Quatf()
      gmtl.set(mat1, quat0)
      quat1 = gmtl.Quatf()
      gmtl.set(quat1, mat1)
      assert gmtl.isEqual(quat0, quat1, eps)
      # Make sure we gt the same matrix as we started.
      mat2 = gmtl.Matrix44f()
      gmtl.set(mat2, quat1)     # mat2 = quat1
      assert gmtl.isEqual(mat2, mat1, eps)

      # Identity, mat1 -> quat0 -> mat2 -> quat1
      mat1 = gmtl.Matrix44f()
      gmtl.set(quat0, mat1)     # quat0 = mat1
      gmtl.set(mat2, quat0)     # mat2 = quat0
      assert gmtl.isEqual(mat1, mat2, eps)
      # Make sure that we get the same quat as we started.
      gmtl.set(quat1, mat2)     # quat1 = mat2
      assert gmtl.isEqual(quat0, quat1, eps)

      # Simple rotation around x-axis.
      mat1 = gmtl.Matrix44f()
      gmtl.set(mat1, gmtl.makeNormal(gmtl.AxisAnglef(gmtl.Math.deg2Rad(90.0),
                                                     1.0, 0.0, 0.0)))
      gmtl.set(quat0, mat1)     # quat0 = mat1
      gmtl.set(mat2, quat0)     # mat2 = quat0
      assert gmtl.isEqual(mat1, mat2, eps)
      # Make sure we get the same quaternion as we started.
      gmtl.set(quat1, mat2)     # quat1 = mat2
      assert gmtl.isEqual(quat0, quat1, eps)

      # More complex rotation mat1 -> quat0 -> mat2 -> quat1
      mat1 = gmtl.Matrix44f()
      gmtl.set(mat1, gmtl.makeNormal(gmtl.AxisAnglef(gmtl.Math.deg2Rad(123.4),
                                                     1.0, 1.0, -1.0)))
      gmtl.set(quat0, mat1)     # quat0 = mat1
      gmtl.set(mat2, quat0)     # mat2 = quat0
      assert gmtl.isEqual(mat1, mat2, eps)
      # Make sure we get the same quaternion as we started.
      gmtl.set(quat1, mat2)     # quat1 = mat2
      assert gmtl.isEqual(quat0, quat1, eps)

      # More complex rotation quat0 -> mat1 -> quat1 -> mat2
      mat1 = gmtl.Matrix44f()
      gmtl.set(mat1, gmtl.EulerAngleXYZf(45.0, -89.0, 32.45))
      gmtl.set(quat0, mat1)     # quat0 = mat1
      gmtl.set(mat2, quat0)     # mat2 = quat0
      assert gmtl.isEqual(mat1, mat2, eps)
      # Make sure we get the same quaternion as we started.
      gmtl.set(quat1, mat2)      # quat1 = mat2
      assert gmtl.isEqual(quat0, quat1, eps)

      # Really test it out.  mat1 -> quat0 -> mat2 -> quat1
      x = -math.pi
      while x < math.pi:
         y = -math.pi
         while y < math.pi:
            z = -math.pi
            while z < math.pi:
               # More complex rotation.
               mat1 = gmtl.Matrix44f()
               gmtl.set(mat1, gmtl.EulerAngleXYZf(x, y, z))
               gmtl.set(quat0, mat1)    # quat0 = mat1
               gmtl.set(mat2, quat0)    # mat2 = quat0
               assert gmtl.isEqual(mat1, mat2, eps)
               # Make sure we get the same quaternion that we started.
               gmtl.set(quat1, mat2)    # quat1 = mat2
               assert gmtl.isEquiv(quat0, quat1, eps)

               z += 0.2

            y+= 0.2

         x += 0.2

      # Really test it out.  quat0 -> mat1 -> quat1 -> mat2
      x = -math.pi
      while x < math.pi:
         y = -math.pi
         while y < math.pi:
            z = -math.pi
            while z < math.pi:
               # More complex rotation.
               quat0 = gmtl.Quatf()
               gmtl.set(quat0, gmtl.EulerAngleXYZf(x, y, z))
               gmtl.set(mat1, quat0)    # mat1 = quat0
               gmtl.set(quat1, mat1)    # quat1 = mat1
               assert gmtl.isEquiv(quat0, quat1, eps)
               # Make sure we get the same matrix that we started.
               gmtl.set(mat2, quat1)    # mat2 = quat1
               assert gmtl.isEqual(mat1, mat2, eps)

               z += 0.2

            y+= 0.2

         x += 0.2

      # Make a 4x4 matrix by hand with a postive 3x3 diagonal
      mat44a = gmtl.Matrix44f()
      mat44a.set( 0.0, 1.0, 0.0, 0.0,
                 -1.0, 0.0, 0.0, 0.0,
                  0.0, 0.0, 1.0, 0.0,
                  0.0, 0.0, 0.0, 1.0)
      mat44b = gmtl.Matrix44f()
      gmtl.set(quat0, mat44a)   # quat0 = mat44a
      gmtl.set(mat44b, quat0)   # mat44b = quat0
      assert gmtl.isEqual(mat44a, mat44b, eps)
      # Make sure we get the same quaternion that we started.
      gmtl.set(quat1, mat44b)   # quat1 = mat44b
      assert gmtl.isEqual(quat0, quat1, eps)

      # Make a 4x4 matrix by hand with a negative 3x3 diagonal
      mat44a.set( 0.0, -1.0,  0.0, 0.0,
                 -1.0,  0.0,  0.0, 0.0,
                  0.0,  0.0, -1.0, 0.0,
                  0.0,  0.0,  0.0, 1.0)
      gmtl.set(quat0, mat44a)   # quat0 = mat44a
      gmtl.set(mat44b, quat0)   # mat44b = quat0
      assert gmtl.isEqual(mat44a, mat44b, eps)
      # Make sure we get the same quaternion that we started.
      gmtl.set(quat1, mat44b)   # quat1 = mat44b
      assert gmtl.isEqual(quat0, quat1, eps)

      # Make a 3x3 matrix by hand with a positive diagonal
      mat33a = gmtl.Matrix33f()
      mat33a.set( 0.0, 1.0, 0.0,
                 -1.0, 0.0, 0.0,
                  0.0, 0.0, 1.0)
      mat33b = gmtl.Matrix33f()
      gmtl.set(quat0, mat33a)   # quat0 = mat33a
      gmtl.set(mat33b, quat0)   # mat33b = quat0
      assert gmtl.isEqual(mat33a, mat33b, eps)
      # Make sure we get the same quaternion that we started.
      gmtl.set(quat1, mat33b)   # quat1 = mat33b
      assert gmtl.isEqual(quat0, quat1, eps)

class CoordClassTest(unittest.TestCase):
   def testCoordClassTestCreation(self):
      # Test that it initializes to the multiplication identity.
      q = gmtl.Coord3fXYZ()
      assert q.pos()[0] == 0.0
      assert q.pos()[1] == 0.0
      assert q.pos()[2] == 0.0
      assert q.rot()[0] == 0.0
      assert q.rot()[1] == 0.0
      assert q.rot()[2] == 0.0

      # Try out element constructor.
      p = gmtl.Vec3f(1.0, 2.0, 3.0)
      r = gmtl.EulerAngleXYZf(4.0, 5.0, 6.0)
      q2 = gmtl.Coord3fXYZ(p, r)
      assert q2.pos()[0] == 1.0
      assert q2.pos()[1] == 2.0
      assert q2.pos()[2] == 3.0
      assert q2.rot()[0] == 4.0
      assert q2.rot()[1] == 5.0
      assert q2.rot()[2] == 6.0

      # Try out copy constructor.
      q3 = gmtl.Coord3fXYZ(q2)
      assert q3.pos()[0] == 1.0
      assert q3.pos()[1] == 2.0
      assert q3.pos()[2] == 3.0
      assert q3.rot()[0] == 4.0
      assert q3.rot()[1] == 5.0
      assert q3.rot()[2] == 6.0

      # Instantiate one copy of all types that we are supposed to support.
      CoordVec3dXYZ_test = gmtl.Coord3dXYZ()
      CoordVec3fXYZ_test = gmtl.Coord3fXYZ()
      CoordVec4dXYZ_test = gmtl.Coord4dXYZ()
      CoordVec4fXYZ_test = gmtl.Coord4fXYZ()

      CoordVec3dZYX_test = gmtl.Coord3dZYX()
      CoordVec3fZYX_test = gmtl.Coord3fZYX()
      CoordVec4dZYX_test = gmtl.Coord4dZYX()
      CoordVec4fZYX_test = gmtl.Coord4fZYX()

      CoordVec3dZXY_test = gmtl.Coord3dZXY()
      CoordVec3fZXY_test = gmtl.Coord3fZXY()
      CoordVec4dZXY_test = gmtl.Coord4dZXY()
      CoordVec4fZXY_test = gmtl.Coord4fZXY()

      CoordVec3AxisAngled_test = gmtl.Coord3dAxisAngle()
      CoordVec3AxisAnglef_test = gmtl.Coord3fAxisAngle()
      CoordVec4AxisAngled_test = gmtl.Coord4dAxisAngle()
      CoordVec4AxisAnglef_test = gmtl.Coord4fAxisAngle()

      Coord3fQuat_test = gmtl.Coord3fQuat()
      Coord3dQuat_test = gmtl.Coord3dQuat()

      Coord4fQuat_test = gmtl.Coord4fQuat()
      Coord4dQuat_test = gmtl.Coord4dQuat()

#   def testMultiArgConstructors(self):
#      coord = gmtl.Coord3fXYZ(1.0, 2.0, 3.0, 4.0, 5.0, 6.0)
#      assert coord.pos()[0] == 1.0
#      assert coord.pos()[1] == 2.0
#      assert coord.pos()[2] == 3.0
#      assert coord.rot()[0] == 4.0
#      assert coord.rot()[1] == 5.0
#      assert coord.rot()[2] == 6.0
#
#      coord = gmtl.Coord4fXYZ(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0)
#      assert coord.pos()[0] == 1.0
#      assert coord.pos()[1] == 2.0
#      assert coord.pos()[2] == 3.0
#      assert coord.pos()[3] == 4.0
#      assert coord.rot()[0] == 5.0
#      assert coord.rot()[1] == 6.0
#      assert coord.rot()[2] == 7.0
#
#      coord = gmtl.Coord4fAxisAngle(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0)
#      assert coord.pos()[0] == 1.0
#      assert coord.pos()[1] == 2.0
#      assert coord.pos()[2] == 3.0
#      assert coord.pos()[3] == 4.0
#      assert coord.rot()[0] == 5.0
#      assert coord.rot()[1] == 6.0
#      assert coord.rot()[2] == 7.0
#      assert coord.rot()[3] == 8.0

   def testCoordTimingDefaultConstructor(self):
      iters = 400000
      use_value = 1.0

      for iter in xrange(iters):
         q = gmtl.Coord3fXYZ()
         use_value += q.mPos[0]

      assert use_value != 0.0

   def testCoordTimingElementConstructor(self):
      iters = 400000
      use_value = 1.0

      p = gmtl.Vec3f(1.0, 2.0, 3.0)
      r = gmtl.EulerAngleXYZf(4.0, 5.0, 6.0)

      for iter in xrange(iters):
         q = gmtl.Coord3fXYZ(p, r)
         use_value += q.mPos[0]

      assert use_value != 0.0

   def testCoordTimingCopyConstructor(self):
      iters = 400000
      use_value = 1.0
      q = gmtl.Coord3fXYZ()

      for iter in xrange(iters):
         q3 = gmtl.Coord3fXYZ(q)
         use_value += q3.mPos[0]

      assert use_value != 0.0

   def testCoordTimingGet(self):
      iters = 400000
      use_value = 0.0
      q = gmtl.Coord3fXYZ()

      for iter in xrange(iters):
         use_value += use_value + q.pos()[0]
         use_value += use_value + q.rot()[0]
         q.rot()[0] -= use_value
         q.pos()[0] -= use_value

      assert use_value != 8324908723.0

class CoordCompareTest(unittest.TestCase):
   def __testCoordEquality(self, coordType, vecType, eulerAngleType, dataType):
      p = vecType(1.0, 2.0, 3.0)
      r = eulerAngleType(4.0, 5.0, 6.0)
      coord1 = coordType()
      coord2 = coordType(coord1)
      assert coord1 == coord2
      assert coord2 == coord1

      for j in range(3):
         coord2.pos()[j] = dataType(1221.0)
         assert coord1 != coord2
         assert not coord1 == coord2
         coord2.pos()[j] = coord1.pos()[j]      # put it back

         coord2.rot()[j] = dataType(1221.0)
         assert coord1 != coord2
         assert not coord1 == coord2
         coord2.rot()[j] = coord1.rot()[j]      # put it back

      assert gmtl.isEqual(coord1, coord2)
      assert gmtl.isEqual(coord1, coord2, dataType(0.0))
      assert gmtl.isEqual(coord2, coord1, dataType(0.0))
      assert gmtl.isEqual(coord2, coord1, dataType(100000.0))

      eps = dataType(10.0)

      for j in range(3):
         coord2.pos()[j] = coord1.pos()[j] - (eps / dataType(2.0))
         assert gmtl.isEqual(coord1, coord2, eps)
         assert not gmtl.isEqual(coord1, coord2, dataType(eps / 3.0))

         coord2.pos()[j] = coord1.pos()[j]      # put it back

         coord2.rot()[j] = coord1.rot()[j] - (eps / dataType(2.0))
         assert gmtl.isEqual(coord1, coord2, eps)
         assert not gmtl.isEqual(coord1, coord2, dataType(eps / 3.0))
         coord2.rot()[j] = coord1.rot()[j]      # put it back

   def testCoordEqualityFloatTest(self):
      for i in range(10):
         self.__testCoordEquality(gmtl.Coord3fXYZ, gmtl.Vec3f,
                                  gmtl.EulerAngleXYZf, float)

#   def testCoordEqualityDoubleTest(self):
#      for i in range(10):
#         self.__testCoordEquality(gmtl.Coord3dXYZ, gmtl.Vec3d,
#                                  gmtl.EulerAngleXYZd)

   def testCoordTimingOpEqualityTest(self):
      iters = 400000

      src_coord11  = gmtl.Coord3fXYZ()
      src_coord22  = gmtl.Coord3fXYZ()
      src_coord33  = gmtl.Coord3fXYZ()
      src_coord34  = gmtl.Coord3fXYZ()
      src_coord44  = gmtl.Coord3fXYZ()
      src_coord101 = gmtl.Coord3dXYZ()

      # Half of them will be equal.
      src_coord11.pos()[0] = 1.0
      src_coord22.pos()[1] = 1.0
      src_coord33.pos()[2] = 2.0

      test_coord11  = gmtl.Coord3fXYZ(src_coord11)
      test_coord22  = gmtl.Coord3fXYZ(src_coord22)
      test_coord33  = gmtl.Coord3fXYZ(src_coord33)
      test_coord34  = gmtl.Coord3fXYZ(src_coord34)
      test_coord44  = gmtl.Coord3fXYZ(src_coord44)
      test_coord101 = gmtl.Coord3dXYZ(src_coord101)

      # Half will be unequal.
      src_coord34.pos()[0]  = 2.0
      src_coord44.pos()[1]  = 3.0
      src_coord101.pos()[2] = 1.0

      true_count = 0

      for iter in xrange(iters):
         if src_coord11 == test_coord11:
            true_count += 1
         if src_coord22 == test_coord22:
            true_count += 1
         if src_coord33 == test_coord33:
            true_count += 1
         if src_coord34 == test_coord34:
            true_count += 1
         if src_coord44 == test_coord44:
            true_count += 1
         if src_coord101 == test_coord101:
            true_count += 1

      assert true_count > 0

   def testCoordTimingOpNotEqualityTest(self):
      iters = 400000

      src_coord11  = gmtl.Coord3fXYZ()
      src_coord22  = gmtl.Coord3fXYZ()
      src_coord33  = gmtl.Coord3fXYZ()
      src_coord34  = gmtl.Coord3fXYZ()
      src_coord44  = gmtl.Coord3fXYZ()
      src_coord101 = gmtl.Coord3dXYZ()

      # Half of them will be equal.
      src_coord11.pos()[0] = 1.0
      src_coord22.pos()[1] = 1.0
      src_coord33.pos()[2] = 2.0

      test_coord11  = gmtl.Coord3fXYZ(src_coord11)
      test_coord22  = gmtl.Coord3fXYZ(src_coord22)
      test_coord33  = gmtl.Coord3fXYZ(src_coord33)
      test_coord34  = gmtl.Coord3fXYZ(src_coord34)
      test_coord44  = gmtl.Coord3fXYZ(src_coord44)
      test_coord101 = gmtl.Coord3dXYZ(src_coord101)

      # Half will be unequal.
      src_coord34.pos()[0]  = 2.0
      src_coord44.pos()[1]  = 3.0
      src_coord101.pos()[2] = 1.0

      true_count = 0

      for iter in xrange(iters):
         if src_coord11 != test_coord11:
            true_count += 1
         if src_coord22 != test_coord22:
            true_count += 1
         if src_coord33 != test_coord33:
            true_count += 1
         if src_coord34 != test_coord34:
            true_count += 1
         if src_coord44 != test_coord44:
            true_count += 1
         if src_coord101 != test_coord101:
            true_count += 1

      assert true_count > 0

   def testCoordTimingIsEqualTest(self):
      iters = 400000

      src_coord11  = gmtl.Coord3fXYZ()
      src_coord22  = gmtl.Coord3fXYZ()
      src_coord33  = gmtl.Coord3fXYZ()
      src_coord34  = gmtl.Coord3fXYZ()
      src_coord44  = gmtl.Coord3fXYZ()
      src_coord101 = gmtl.Coord3dXYZ()

      # Half of them will be equal.
      src_coord11.pos()[0] = 1.0
      src_coord22.pos()[1] = 1.0
      src_coord33.pos()[2] = 2.0

      test_coord11  = gmtl.Coord3fXYZ(src_coord11)
      test_coord22  = gmtl.Coord3fXYZ(src_coord22)
      test_coord33  = gmtl.Coord3fXYZ(src_coord33)
      test_coord34  = gmtl.Coord3fXYZ(src_coord34)
      test_coord44  = gmtl.Coord3fXYZ(src_coord44)
      test_coord101 = gmtl.Coord3dXYZ(src_coord101)

      # Half will be unequal.
      src_coord34.pos()[0]  = 2.0
      src_coord44.pos()[1]  = 3.0
      src_coord101.pos()[2] = 1.0

      true_count = 0

      for iter in xrange(iters):
         if gmtl.isEqual(src_coord11, test_coord11):
            true_count += 1
         if gmtl.isEqual(src_coord22, test_coord22):
            true_count += 1
         if gmtl.isEqual(src_coord33, test_coord33):
            true_count += 1
         if gmtl.isEqual(src_coord34, test_coord34):
            true_count += 1
         if gmtl.isEqual(src_coord44, test_coord44):
            true_count += 1
         if gmtl.isEqual(src_coord101, test_coord101):
            true_count += 1

      assert true_count > 0

class CoordGenTest(unittest.TestCase):
   def testCoordSetMatrix(self):
      q1 = gmtl.Coord3fXYZ()
      q1.pos().set(2.0, 3.0, 4.0)
      q1.rot().set(0.2, 0.5, 0.6)

      mat1 = gmtl.Matrix44f()
      q2 = gmtl.Coord3fXYZ()
      gmtl.set(mat1, q1)        # set the matrix
      gmtl.set(q2, mat1)        # extract it

      assert gmtl.isEqual(q1, q2, 0.01)

   def testCoordMakeCoord(self):
      q1 = gmtl.Coord3fXYZ()

      # Test translation with gmtl.set()
      mat = gmtl.makeTransMatrix44(gmtl.Vec3f(1.0, 2.0, 3.0))
      gmtl.set(q1, mat)
      assert q1.getPos()[0] == 1.0
      assert q1.getPos()[1] == 2.0
      assert q1.getPos()[2] == 3.0

   def testCoordGetMatrix(self):
      trans = gmtl.Vec3f(1.0, 2.0, 3.0)
      rot   = gmtl.EulerAngleXYZf(4.0, 5.0, 6.0)
      q1    = gmtl.Coord3fXYZ(trans, rot)

      # Test translation with gmtl.set()
      mat = gmtl.Matrix44f()
      gmtl.set(mat, q1)

      v2 = gmtl.makeTransVec3(mat)
      assert v2 == trans

      eps = 0.001
      q1  = gmtl.Coord3fXYZ(trans, rot)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(0.683013, -0.183013, 0.707107,
                            0.683013, -0.183013, -0.707107,
                            0.258819, 0.965926, 0.0 )

      q1.rot()[0] = gmtl.Math.deg2Rad(90.0)
      q1.rot()[1] = gmtl.Math.deg2Rad(45.0)
      q1.rot()[2] = gmtl.Math.deg2Rad(15.0)

      mat = gmtl.Matrix33f()
      gmtl.set(mat, q1)
      assert gmtl.isEqual(expected_result33, mat, eps)

      q1 = gmtl.Coord3fZXY(trans, gmtl.EulerAngleZXYf(4.0, 5.0, 6.0))
      expected_result44 = gmtl.Matrix44f()
      expected_result44.set(-0.918494, 0.283617, -0.275553, gmtl.Math.deg2Rad(1.0),
                            -0.395247, -0.637014, 0.66181, gmtl.Math.deg2Rad(2.0),
                            0.0121696, 0.71678, 0.697193, gmtl.Math.deg2Rad(3.0),
                            0.0, 0.0, 0.0, 1.0)
      q1.pos()[0] = gmtl.Math.deg2Rad(1.0)
      q1.pos()[1] = gmtl.Math.deg2Rad(2.0)
      q1.pos()[2] = gmtl.Math.deg2Rad(3.0)
      q1.rot()[0] = gmtl.Math.deg2Rad(-156.0)
      q1.rot()[1] = gmtl.Math.deg2Rad(45.7892892)
      q1.rot()[2] = gmtl.Math.deg2Rad(-361.0)

      mat = gmtl.Matrix44f()
      gmtl.set(mat, q1)
      assert gmtl.isEqual(expected_result44, mat, eps)

   def testGenTimingMakeCoord(self):
      mat = gmtl.Matrix44f()
      iters = 25000

      for iter in xrange(iters):
         q1 = gmtl.Coord3fXYZ()
         gmtl.set(q1, mat)
         mat[3][1] != q1.getPos()[2]

      assert q1.pos()[1] != 10000.0

   def testGenTimingMakeMatrix(self):
      iters = 25000
      q1    = gmtl.Coord3fXYZ()

      for iter in xrange(iters):
         mat = gmtl.Matrix44f()
         q1.pos()[2] += mat[3][3]

      assert q1.pos()[1] != 10000.0

   def testGenTimingSetCoord(self):
      mat = gmtl.Matrix44f()
      q1  = gmtl.Coord3fXYZ()
      iters = 25000

      for iter in xrange(iters):
         gmtl.set(q1, mat)
         mat[3][3] += q1.getPos()[2]

      assert q1.pos()[1] != 10000.0

class EulerAngleClassTest(unittest.TestCase):
   def testEulerAngleClassTestCreation(self):
      # Test that it initializes to the identity.
      q = gmtl.EulerAngleXYZf()
      assert q[0] == 0.0
      assert q[1] == 0.0
      assert q[2] == 0.0

      # Try out set.
      q.set(1.0, 2.0, 3.0)
      assert q[0] == 1.0
      assert q[1] == 2.0
      assert q[2] == 3.0

      # Try out setting with brackets.
      q[0] = 5.0
      q[1] = 6.0
      q[2] = 7.0
      assert q[0] == 5.0
      assert q[1] == 6.0
      assert q[2] == 7.0

      # Try out element constructor.
      q2 = gmtl.EulerAngleZYXf(10.0, 11.0, 12.0)
      assert q2[0] == 10.0
      assert q2[1] == 11.0
      assert q2[2] == 12.0

      # Try out copy constructor.
      q3 = gmtl.EulerAngleXYZf(q)
      assert q3[0] == 5.0
      assert q3[1] == 6.0
      assert q3[2] == 7.0

   def testEulerAngleTimingDefaultConstructor(self):
      iters = 400000
      use_value = 1.0

      for iter in xrange(iters):
         q = gmtl.EulerAngleXYZf()
         use_value += q[0]

      assert use_value != 0.0

   def testEulerAngleTimingElementConstructor(self):
      iters = 400000
      use_value = 1.0

      for iter in xrange(iters):
         q2 = gmtl.EulerAngleXYZf(10.0, 11.0, 12.0)
         use_value += q2[0]

      assert use_value != 0.0

   def testEulerAngleTimingCopyConstructor(self):
      iters = 400000
      use_value = 1.0
      q = gmtl.EulerAngleXYZf(67.0, 68.0, 69.0)

      for iter in xrange(iters):
         q3 = gmtl.EulerAngleXYZf(q)
         use_value += q3[0]

      use_value != 0.0

   def testEulerAngleTimingSet(self):
      iters = 400000
      use_value = 0.0
      q = gmtl.EulerAngleXYZf()

      for iter in xrange(iters):
         q.set(1.0, 2.0, 3.0)
         use_value += q[0]

      assert use_value >= 0.0

   def testEulerAngleTimingOpBracked(self):
      iters = 400000
      use_value = 0.0
      q = gmtl.EulerAngleXYZf()
      x = 102.0
      y = 103.0
      z = 101.0

      for iter in xrange(iters):
         q[0] = x
         q[1] = y
         q[2] = z
         use_value = use_value + x + y + z

      assert use_value > 0.0

   def testEulerAngleTimingGetData(self):
      iters = 400000
      use_value = 0.0
      q = gmtl.EulerAngleXYZf(1.0, 2.0, 3.0)

      for iter in xrange(iters):
         d = q.getData()
         use_value += d[1]

      assert use_value > 0.0

class EulerAngleCompareTest(unittest.TestCase):
   def __testEulerAngleEquality(self, eulerAngleType, dataType):
      euler1 = eulerAngleType()
      euler1.set(dataType(1.0), dataType(2.0), dataType(34.0))
      euler2 = eulerAngleType(euler1)
      assert euler1 == euler2
      assert euler2 == euler1

      for j in range(3):
         euler2[j] = dataType(1221.0)
         assert euler1 != euler2
         assert not euler1 == euler2
         euler2[j] = euler1[j]  # put it back

      # Just for fun.
      assert euler1 == euler2
      assert not euler1 != euler2

      # Test for epsilon equals working.
      assert gmtl.isEqual(euler1, euler2)
      assert gmtl.isEqual(euler1, euler2, dataType(0.0))
      assert gmtl.isEqual(euler2, euler1, dataType(0.0))
      assert gmtl.isEqual(euler2, euler1, dataType(100000.0))
      eps = dataType(10.0)
      for j in range(3):
         euler2[j] = euler1[j] - (eps / dataType(2.))
         assert gmtl.isEqual(euler1, euler2, eps)
         assert not gmtl.isEqual(euler1, euler2, dataType(eps / 3.0))
         euler2[j] = euler1[j]  # put it back

   def testEulerAngleEqualityFloatTest(self):
      for i in range(10):
         self.__testEulerAngleEquality(gmtl.EulerAngleXYZf, float)

      for i in range(10):
         self.__testEulerAngleEquality(gmtl.EulerAngleZXYf, float)

      for i in range(10):
         self.__testEulerAngleEquality(gmtl.EulerAngleZYXf, float)

#   def testEulerAngleEqualityDoubleTest(self):
#      for i in range(10):
#         self.__testEulerAngleEquality(gmtl.EulerAngleXYZd, double)
#
#      for i in range(10):
#         self.__testEulerAngleEquality(gmtl.EulerAngleZXYd, double)
#
#      for i in range(10):
#         self.__testEulerAngleEquality(gmtl.EulerAngleZYXd, double)

   def testEulerAngleTimingOpEqualityTest(self):
      iters = 400000

      src_ang11  = gmtl.EulerAngleXYZf()
      src_ang22  = gmtl.EulerAngleXYZf()
      src_ang33  = gmtl.EulerAngleXYZf()
      src_ang34  = gmtl.EulerAngleXYZf()
      src_ang44  = gmtl.EulerAngleXYZf()
#      src_ang101 = gmtl.EulerAngleXYZd()

      # Half of them will be equal.
      src_ang11[0] = 1.0
      src_ang22[2] = 1.0
      src_ang33[1] = 2.0

      test_ang11  = gmtl.EulerAngleXYZf(src_ang11)
      test_ang22  = gmtl.EulerAngleXYZf(src_ang22)
      test_ang33  = gmtl.EulerAngleXYZf(src_ang33)
      test_ang34  = gmtl.EulerAngleXYZf(src_ang34)
      test_ang44  = gmtl.EulerAngleXYZf(src_ang44)
#      test_ang101 = gmtl.EulerAngleXYZd(src_ang101)

      # Half will be unequal.
      src_ang34[0]  = 2.0
      src_ang44[0]  = 3.0
#      src_ang101[0] = 1.0

      true_count = 0

      for iter in xrange(iters):
         if src_ang11 == test_ang11:
            true_count += 1
         if src_ang22 == test_ang22:
            true_count += 1
         if src_ang33 == test_ang33:
            true_count += 1
         if src_ang34 == test_ang34:
            true_count += 1
         if src_ang44 == test_ang44:
            true_count += 1
#         if src_ang101 == test_ang101:
#            true_count += 1

      assert true_count > 0

   def testEulerAngleTimingOpNotEqualityTest(self):
      iters = 400000

      src_ang11  = gmtl.EulerAngleXYZf()
      src_ang22  = gmtl.EulerAngleXYZf()
      src_ang33  = gmtl.EulerAngleXYZf()
      src_ang34  = gmtl.EulerAngleXYZf()
      src_ang44  = gmtl.EulerAngleXYZf()
#      src_ang101 = gmtl.EulerAngleXYZd()

      # Half of them will be equal.
      src_ang11[0] = 1.0
      src_ang22[2] = 1.0
      src_ang33[1] = 2.0

      test_ang11  = gmtl.EulerAngleXYZf(src_ang11)
      test_ang22  = gmtl.EulerAngleXYZf(src_ang22)
      test_ang33  = gmtl.EulerAngleXYZf(src_ang33)
      test_ang34  = gmtl.EulerAngleXYZf(src_ang34)
      test_ang44  = gmtl.EulerAngleXYZf(src_ang44)
#      test_ang101 = gmtl.EulerAngleXYZd(src_ang101)

      # Half will be unequal.
      src_ang34[0]  = 2.0
      src_ang44[0]  = 3.0
#      src_ang101[0] = 1.0

      true_count = 0

      for iter in xrange(iters):
         if src_ang11 != test_ang11:
            true_count += 1
         if src_ang22 != test_ang22:
            true_count += 1
         if src_ang33 != test_ang33:
            true_count += 1
         if src_ang34 != test_ang34:
            true_count += 1
         if src_ang44 != test_ang44:
            true_count += 1
#         if src_ang101 != test_ang101:
#            true_count += 1

      assert true_count > 0

   def testEulerAngleTimingOpIsEqualTest(self):
      iters = 400000

      src_ang11  = gmtl.EulerAngleXYZf()
      src_ang22  = gmtl.EulerAngleXYZf()
      src_ang33  = gmtl.EulerAngleXYZf()
      src_ang34  = gmtl.EulerAngleXYZf()
      src_ang44  = gmtl.EulerAngleXYZf()
#      src_ang101 = gmtl.EulerAngleXYZd()

      # Half of them will be equal.
      src_ang11[0] = 1.0
      src_ang22[2] = 1.0
      src_ang33[1] = 2.0

      test_ang11  = gmtl.EulerAngleXYZf(src_ang11)
      test_ang22  = gmtl.EulerAngleXYZf(src_ang22)
      test_ang33  = gmtl.EulerAngleXYZf(src_ang33)
      test_ang34  = gmtl.EulerAngleXYZf(src_ang34)
      test_ang44  = gmtl.EulerAngleXYZf(src_ang44)
#      test_ang101 = gmtl.EulerAngleXYZd(src_ang101)

      # Half will be unequal.
      src_ang34[0]  = 23.0
      src_ang44[0]  = 234.0
#      src_ang101[0] = 1234.0

      true_count = 0

      for iter in xrange(iters):
         if gmtl.isEqual(src_ang11, test_ang11):
            true_count += 1
         if gmtl.isEqual(src_ang22, test_ang22):
            true_count += 1
         if gmtl.isEqual(src_ang33, test_ang33):
            true_count += 1
         if gmtl.isEqual(src_ang34, test_ang34):
            true_count += 1
         if gmtl.isEqual(src_ang44, test_ang44):
            true_count += 1
#         if gmtl.isEqual(src_ang101, test_ang101, 111.1):
#            true_count += 1

      assert true_count > 0

class IntersectionTest(unittest.TestCase):
   def testIntersectAABoxAABox(self):
      # Test overlapping boxes.
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(1.0, 1.0, 1.0))
      box2 = gmtl.AABoxf(gmtl.Point3f(0.0, 0.0, 0.0),
                         gmtl.Point3f(2.0, 2.0, 2.0))
      assert gmtl.intersect(box1, box2)[0]

      # Test boxes with shared edge.
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(0.0, 0.0, 0.0))
      box2 = gmtl.AABoxf(gmtl.Point3f(0.0, 0.0, 0.0),
                         gmtl.Point3f(-1.0, -1.0, -1.0))
      assert gmtl.intersect(box1, box2)[0]

      # Test non-overlapping boxes.
      box1 = gmtl.AABoxf(gmtl.Point3f(-2.0, -2.0, -2.0),
                         gmtl.Point3f(-1.0, -1.0, -1.0))
      box2 = gmtl.AABoxf(gmtl.Point3f(1.0, 1.0, 1.0),
                         gmtl.Point3f(2.0, 2.0, 2.0))
      assert not gmtl.intersect(box1, box2)[0]

   def testIntersectAABoxPoint(self):
      # Test point in box.
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(1.0, 1.0, 1.0))
      point = gmtl.Point3f(0.0, 0.0, 0.0)
      assert gmtl.intersect(box1, point)[0]

      # Test point on edge (bottom face).
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(0.0, 0.0, 0.0))
      point = gmtl.Point3f(-0.5, -1.0, -0.5)
      assert gmtl.intersect(box1, point)[0]

      # Test point on edge (top face).
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(0.0, 0.0, 0.0))
      point = gmtl.Point3f(-0.5, 0.0, -0.5)
      assert gmtl.intersect(box1, point)[0]

      # Test point on edge (left face).
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(0.0, 0.0, 0.0))
      point = gmtl.Point3f(-1.0, -0.5, -0.5)
      assert gmtl.intersect(box1, point)[0]

      # Test point on edge (right face).
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(0.0, 0.0, 0.0))
      point = gmtl.Point3f(0.0, -0.5, -0.5)
      assert gmtl.intersect(box1, point)[0]

      # Test point on edge (near face).
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(0.0, 0.0, 0.0))
      point = gmtl.Point3f(-0.5, -0.5, 0.0)
      assert gmtl.intersect(box1, point)[0]

      # Test point on edge (far face).
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(0.0, 0.0, 0.0))
      point = gmtl.Point3f(-0.5, -0.5, -1.0)
      assert gmtl.intersect(box1, point)[0]

      # Test point outside (bottom face).
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(0.0, 0.0, 0.0))
      point = gmtl.Point3f(-0.5, -1.01, -0.5)
      assert not gmtl.intersect(box1, point)[0]

      # Test point outside (top face).
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(0.0, 0.0, 0.0))
      point = gmtl.Point3f(-0.5, 0.01, -0.5)
      assert not gmtl.intersect(box1, point)[0]

      # Test point outside (left face).
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(0.0, 0.0, 0.0))
      point = gmtl.Point3f(-1.01, -0.5, -0.5)
      assert not gmtl.intersect(box1, point)[0]

      # Test point outside (right face).
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(0.0, 0.0, 0.0))
      point = gmtl.Point3f(0.01, -0.5, -0.5)
      assert not gmtl.intersect(box1, point)[0]

      # Test point outside (right face).
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(0.0, 0.0, 0.0))
      point = gmtl.Point3f(-0.5, -0.5, 0.01)
      assert not gmtl.intersect(box1, point)[0]

      # Test point on edge (far face).
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(0.0, 0.0, 0.0))
      point = gmtl.Point3f(-0.5, -0.5, -1.01)
      assert not gmtl.intersect(box1, point)[0]

   def testIntersectLineSegPlane(self):
      plane = gmtl.Planef(gmtl.Vec3f(0.0, 1.0, 0.0), 0.0)

      eps = 0.0001

      # Behind.
      seg = gmtl.LineSegf(gmtl.Point3f(0.0, -1.0, 0.0),
                          gmtl.Vec3f(0.0, -1.0, 0.0))
      (res, d) = gmtl.intersect(plane, seg)
      assert res == False

      # Not long enough.
      seg = gmtl.LineSegf(gmtl.Point3f(0.0, 5.0, 0.0),
                          gmtl.Vec3f(0.0, -2.5, 0.0))
      (res, d) = gmtl.intersect(plane, seg)
      assert res == False
      assert d == 2.0

      # Through.
      seg = gmtl.LineSegf(gmtl.Point3f(0.0, 5.0, 0.0),
                          gmtl.Vec3f(0.0, -10.0, 0.0))
      (res, d) = gmtl.intersect(plane, seg)
      assert res == True
      assert d == 0.5

      # Parallel - Shoot seg parallel to plane.
      ray = gmtl.Rayf(gmtl.Point3f(0.0, 1.0, 0.0), gmtl.Vec3f(1.0, 0.0, 0.0))
      (res, d) = gmtl.intersect(plane, ray)
      assert res == False
      assert isEqual(d, 0.0, eps)

      # Parallel - On plane - Shoot ray parallel to the plane on the plane.
      seg = gmtl.LineSegf(gmtl.Point3f(0.0, 0.0, 0.0),
                          gmtl.Vec3f(1.0, 0.0, 0.0))
      (res, d) = gmtl.intersect(plane, seg)
      assert res == True
      assert isEqual(d, 0.0, eps)

   def testIntersectRayPlane(self):
      eps = 0.0001

      # Plane at origin

      # Derfine plane on origin pointing up.
      plane = gmtl.Planef(gmtl.Vec3f(0.0, 1.0, 0.0), 0.0)

      # Through - Shoot ray from +5y straight down at plane.
      #           Should hit with t = 5
      ray = gmtl.Rayf(gmtl.Point3f(0.0, 5.0, 0.0), gmtl.Vec3f(0.0, -1.0, 0.0))
      (res, d) = gmtl.intersect(plane, ray)
      assert res == True
      assert d == 5.0

      # Behind - Shoot ray from -1y straight down.  Should miss.
      ray = gmtl.Rayf(gmtl.Point3f(0.0, -1.0, 0.0), gmtl.Vec3f(0.0, -1.0, 0.0))
      (res, d) = gmtl.intersect(plane, ray)
      assert res == False

      # Parallel - Shoot ray parallel to plane.
      ray = gmtl.Rayf(gmtl.Point3f(0.0, 1.0, 0.0), gmtl.Vec3f(1.0, 0.0, 0.0))
      (res, d) = gmtl.intersect(plane, ray)
      assert res == False
      assert isEqual(d, 0.0, eps)

      # Parallel - On the plane; shoot ray parallel to thr plane on the plane.
      ray = gmtl.Rayf(gmtl.Point3f(0.0, 0.0, 0.0), gmtl.Vec3f(1.0, 0.0, 0.0))
      (res, d) = gmtl.intersect(plane, ray)
      assert res == True
      assert isEqual(d, 0.0, eps)

      # Plane off origin - 45 degree angle off
      plane = gmtl.Planef(gmtl.Point3f(1.0, 0.0, 0.0),
                          gmtl.Point3f(0.0, 1.0, 0.0),
                          gmtl.Point3f(0.0, 0.0, 1.0))

      # Send ray from origin orthogonal.
      ray = gmtl.Rayf(gmtl.Point3f(0.0, 0.0, 0.0), gmtl.Vec3f(1.0, 1.0, 1.0))
      (res, d) = gmtl.intersect(plane, ray)
      assert res == True
      assert isEqual(d, 0.3333, eps)

      miss_ray = gmtl.Rayf(gmtl.Point3f(0.0, 0.0, 0.0),
                           gmtl.Vec3f(-1.0, -1.0, -1.0))
      (res, d) = gmtl.intersect(plane, miss_ray)
      assert res == False

   def testIntersectAABoxSphere(self):
      # Overlapping.
      box = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                        gmtl.Point3f(0.0, 0.0, 0.0))
      sph = gmtl.Spheref(gmtl.Point3f(0.0, 0.0, 0.0), 2.0)
      assert gmtl.intersect(box, sph)[0]
      assert gmtl.intersect(sph, box)[0]

      # Shared edge.
      box = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                        gmtl.Point3f(0.0, 0.0, 0.0))
      sph = gmtl.Spheref(gmtl.Point3f(2.0, 0.0, 0.0), 2.0)
      assert gmtl.intersect(box, sph)[0]
      assert gmtl.intersect(sph, box)[0]

      # Non-overlapping.
      box = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                        gmtl.Point3f(0.0, 0.0, 0.0))
      sph = gmtl.Spheref(gmtl.Point3f(3.0, 3.0, 3.0), 2.0)
      assert not gmtl.intersect(box, sph)[0]
      assert not gmtl.intersect(sph, box)[0]

   def testIntersectAABoxSweep(self):
      box1 = gmtl.AABoxf(gmtl.Point3f(-3.0, 1.0, -3.0),
                         gmtl.Point3f(-2.0, 2.0, -2.0))
      box2 = gmtl.AABoxf(gmtl.Point3f(2.0, 1.0, -3.0),
                         gmtl.Point3f(3.0, 3.0, -2.0))
      path1 = gmtl.Vec3f(5.0, 0.0, 0.0)
      path2 = gmtl.Vec3f(-5.0, 0.0, 0.0)

      (result, first, second) = gmtl.intersect(box1, path1, box2, path2)
      assert result
      assert isEqual(first, 0.4)
      assert isEqual(second, 0.6)

   def testIntersectSphereSweep(self):
      sph1 = gmtl.Spheref(gmtl.Point3f(-3.0, 1.0, -3.0), 2.0)
      sph2 = gmtl.Spheref(gmtl.Point3f(2.0, 1.0, -3.0), 1.0)
      path1 = gmtl.Vec3f(5.0, 0.0, 0.0)
      path2 = gmtl.Vec3f(-5.0, 0.0, 0.0)

      (result, first, second) = gmtl.intersect(sph1, path1, sph2, path2)
      assert result
      assert isEqual(first, 0.2, 0.001)
      assert isEqual(second, 0.8, 0.001)

class IntersectionMetricTest(unittest.TestCase):
   def testTimingIntersectAABoxAABox(self):
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(1.0, 1.0, 1.0))
      box2 = gmtl.AABoxf(gmtl.Point3f(0.0, 0.0, 0.0),
                         gmtl.Point3f(2.0, 2.0, 2.0))
      iters = 400000
      true_count = 0

      for iter in xrange(iters):
         if gmtl.intersect(box1, box2)[0]:
            true_count += 1
         box2.mMax[0] += 0.01

      assert true_count > 0

   def testTimingIntersectAABoxPoint(self):
      box1 = gmtl.AABoxf(gmtl.Point3f(-1.0, -1.0, -1.0),
                         gmtl.Point3f(1.0, 1.0, 1.0))
      point = gmtl.Point3f(-0.5, -0.5, -1.01)
      iters = 400000
      true_count = 0

      for iter in xrange(iters):
         if gmtl.intersect(box1, point)[0]:
            true_count += 1
         point[0] += 0.01

      assert true_count == 0

   def testTimingIntersectAABoxSweep(self):
      box1 = gmtl.AABoxf(gmtl.Point3f(-3.0, 1.0, -3.0),
                         gmtl.Point3f(-2.0, 2.0, -2.0))
      box2 = gmtl.AABoxf(gmtl.Point3f(2.0, 1.0, -3.0),
                         gmtl.Point3f(3.0, 3.0, -2.0))
      path1 = gmtl.Vec3f(1.0, 0.0, 0.0)
      path2 = gmtl.Vec3f(-5.0, 0.0, 0.0)

      iters = 400000
      true_count = 0

      for iter in xrange(iters):
         if gmtl.intersect(box1, path1, box2, path2)[0]:
            true_count += 1
         path1[0] += 0.1

      assert true_count > 0

   def testTimingIntersectSphereSweep(self):
      sph1 = gmtl.Spheref(gmtl.Point3f(-3.0, 1.0, -3.0), 2.0)
      sph2 = gmtl.Spheref(gmtl.Point3f(2.0, 1.0, -3.0), 1.0)
      path1 = gmtl.Vec3f(1.0, 0.0, 0.0)
      path2 = gmtl.Vec3f(-5.0, 0.0, 0.0)

      iters = 400000
      true_count = 0

      for iter in xrange(iters):
         if gmtl.intersect(sph1, path1, sph2, path2)[0]:
            true_count += 1
         path1[0] += 0.1

      assert true_count > 0

class LineSegTest(unittest.TestCase):
   def setUp(self):
      self.origin = gmtl.Point3f(0.0, 0.0, 0.0)
      self.x1_pt  = gmtl.Point3f(1.0, 0.0, 0.0)
      self.y1_pt  = gmtl.Point3f(0.0, 1.0, 0.0)
      self.z1_pt  = gmtl.Point3f(0.0, 0.0, 1.0)
      self.x1_v   = gmtl.Vec3f(1.0, 0.0, 0.0)
      self.y1_v   = gmtl.Vec3f(0.0, 1.0, 0.0)
      self.z1_v   = gmtl.Vec3f(0.0, 0.0, 1.0)

      self.x1_lineseg = gmtl.LineSegf(self.origin, self.x1_v)
      self.y1_lineseg = gmtl.LineSegf(self.origin, self.y1_v)
      self.z1_lineseg = gmtl.LineSegf(self.origin, self.z1_v)

   def testCreation(self):
      test_lineseg = gmtl.LineSegf()
      zeroVec = gmtl.Vec3f(0.0, 0.0, 0.0)
      assert test_lineseg.mOrigin == self.origin
      assert test_lineseg.mDir == zeroVec

   def testPtVecCreation(self):
      assert self.x1_lineseg.mOrigin == self.origin
      assert self.y1_lineseg.mOrigin == self.origin
      assert self.z1_lineseg.mOrigin == self.origin
      assert self.x1_lineseg.mDir == self.x1_v
      assert self.y1_lineseg.mDir == self.y1_v
      assert self.z1_lineseg.mDir == self.z1_v

      vec = gmtl.Vec3f(1.0, 1.0, 1.0)
      test_lineseg = gmtl.LineSegf(self.x1_pt, vec)
      assert test_lineseg.mOrigin == self.x1_pt
      assert test_lineseg.mDir == vec

   def testPtPtCreation(self):
      test_lineseg = gmtl.LineSegf(self.origin, self.x1_pt)
      assert test_lineseg.mOrigin == self.origin
      assert test_lineseg.mDir == gmtl.Vec3f(self.x1_pt - self.origin)

      test_lineseg = gmtl.LineSegf(self.x1_pt, self.y1_pt)
      assert test_lineseg.mOrigin == self.x1_pt
      assert test_lineseg.mDir == gmtl.Vec3f(self.y1_pt - self.x1_pt)

   def testCopyConstruct(self):
      test_lineseg = gmtl.LineSegf(self.x1_lineseg)
      assert test_lineseg.mOrigin == self.x1_lineseg.mOrigin
      assert test_lineseg.mDir == self.x1_lineseg.mDir

   def testGetOrigin(self):
      assert self.x1_lineseg.getOrigin() == self.origin
      assert self.y1_lineseg.getOrigin() == self.origin
      assert self.z1_lineseg.getOrigin() == self.origin

      pt = gmtl.Point3f(25.0, 23.0, 0.0)
      test_lineseg = gmtl.LineSegf(pt, self.x1_pt)
      assert test_lineseg.getOrigin() == pt

   def testSetOrigin(self):
      test_lineseg = gmtl.LineSegf()
      test_lineseg.setOrigin(self.x1_pt)
      assert test_lineseg.getOrigin() == self.x1_pt

   def testGetDir(self):
      assert self.x1_lineseg.getDir() == self.x1_v
      assert self.y1_lineseg.getDir() == self.y1_v
      assert self.z1_lineseg.getDir() == self.z1_v

      dir = gmtl.Vec3f(25.0, 23.0, 0.0)
      test_lineseg = gmtl.LineSegf(self.x1_pt, dir)
      assert test_lineseg.getDir() == dir

   def testSetDir(self):
      test_lineseg = gmtl.LineSegf()
      test_lineseg.setDir(self.x1_v)
      assert test_lineseg.getDir() == self.x1_v

   def testGetLength(self):
      test_lineseg1 = gmtl.LineSegf(self.x1_pt, self.x1_v)
      assert test_lineseg1.getLength() == gmtl.length(self.x1_v)

   def testEqualityCompare(self):
      test_lineseg1 = gmtl.LineSegf(self.x1_pt, self.x1_v)
      test_lineseg2 = gmtl.LineSegf(test_lineseg1)

      assert test_lineseg1 == test_lineseg2
      assert not test_lineseg1 != test_lineseg2

      # Set equal, vary origin.
      test_lineseg2 = gmtl.LineSegf(test_lineseg1)
      test_lineseg2.mOrigin[0] += 2.0
      assert test_lineseg1 != test_lineseg2
      assert not test_lineseg1 == test_lineseg2

      # Set equal, vary dir
      test_lineseg2 = gmtl.LineSegf(test_lineseg1)
      test_lineseg2.mDir[0] += 2.0
      assert test_lineseg1 != test_lineseg2
      assert not test_lineseg1 == test_lineseg2

   def testIsEqual(self):
      test_lineseg1 = gmtl.LineSegf(self.x1_pt, self.x1_v)
      test_lineseg2 = gmtl.LineSegf(test_lineseg1)
      eps = 0.0

      while eps < 10.0:
         assert gmtl.isEqual(test_lineseg1, test_lineseg2, eps)
         eps += 0.05

      for elt in range(6):
         test_lineseg2 = gmtl.LineSegf(test_lineseg1)

         if elt < 3:
            test_lineseg2.mOrigin[elt] += 20.0
         else:
            test_lineseg2.mDir[elt - 3] += 20.0

         assert not gmtl.isEqual(test_lineseg1, test_lineseg2, 10.0)
         assert not gmtl.isEqual(test_lineseg1, test_lineseg2, 19.9)
         assert gmtl.isEqual(test_lineseg1, test_lineseg2, 20.1)
         assert gmtl.isEqual(test_lineseg1, test_lineseg2, 22.0)

   def testIntersectLineSegPlane(self):
      lineseg = gmtl.LineSegf(gmtl.Point3f(0.0, 1.0, 0.0),
                              gmtl.Point3f(0.0, -1.0, 0.0))
      plane = gmtl.Planef(gmtl.Vec3f(0.0, 1.0, 0.0), 0.0)
      (result, t) = gmtl.intersect(plane, lineseg)
      assert t == 0.5 and result == True

   def testIntersectLineSegTri(self):
       # Test t
      l = gmtl.LineSegf(gmtl.Point3f(0.0, 1.0, 0.0),
                        gmtl.Point3f(0.0, -1.0, 0.0))
      tri = gmtl.Trif(gmtl.Point3f(-1.0, 0.0, 1.0),
                      gmtl.Point3f(1.0, 0.0, 1.0),
                      gmtl.Point3f(0.0, 0.0, -1.0))
      (result, u, v, t) = gmtl.intersect(tri, l)
      assert t == 0.5 and result == True

      # Test u and v
      l = gmtl.LineSegf(gmtl.Point3f(0.25, 1.0, -0.25),
                        gmtl.Point3f(0.25, -1.0, -0.25))
      tri = gmtl.Trif(gmtl.Point3f(0.0, 0.0, 0.0),
                      gmtl.Point3f(1.0, 0.0, 0.0),
                      gmtl.Point3f(0.0, 0.0, -1.0))
      (result, u, v, t) = gmtl.intersect(tri, l)
      assert t == 0.5 and result == True
      assert u == 0.25 and v == 0.25

      # Test outside of tri.
      tri = gmtl.Trif(gmtl.Point3f(0.0, 0.0, 0.0),
                      gmtl.Point3f(1.0, 0.0, 0.0),
                      gmtl.Point3f(0.0, 0.0, -1.0))
      lineseg = gmtl.LineSegf(gmtl.Point3f(-0.25, 1.0, 0.0),
                              gmtl.Point3f(-0.25, 1.0, 0.0))
      (result, u, v, t) = gmtl.intersect(tri, lineseg)
      assert result == False
      lineseg = gmtl.LineSegf(gmtl.Point3f(0.0, 1.0, 0.25),
                              gmtl.Point3f(0.0, -1.0, 0.25))
      (result, u, v, t) = gmtl.intersect(tri, lineseg)
      assert result == False

      # Right on edge of tri should give intersection.
      lineseg = gmtl.LineSegf(gmtl.Point3f(0.0, 1.0, 0.0),
                              gmtl.Point3f(0.0, -1.0, 0.0))
      (result, u, v, t) = gmtl.intersect(tri, lineseg)
      assert t == 0.5 and result == True
      # Right off edge of tri should not.
      lineseg = gmtl.LineSegf(gmtl.Point3f(-0.000001, 1.0, 0.0),
                              gmtl.Point3f(-0.000001, -1.0, 0.0))
      (result, u, v, t) = gmtl.intersect(tri, lineseg)
      assert result == False

      # Test other places.

      # x/y plane
      tri = gmtl.Trif(gmtl.Point3f(-1.0, 0.0, 0.0),
                      gmtl.Point3f(0.0, 0.0, 0.0), gmtl.Point3f(0.0, 1.0, 0.0))
      lineseg = gmtl.LineSegf(gmtl.Point3f(0.0, 0.0, 1.0),
                              gmtl.Point3f(0.0, 0.0, 0.0))
      (result, u, v, t) = gmtl.intersect(tri, lineseg)
      assert t == 1.0 and result == True

      # Try flipped about the x/y plane.
      tri = gmtl.Trif(gmtl.Point3f(-1.0, 0.0, 0.0),
                      gmtl.Point3f(-2.0, 0.0, 0.0),
                      gmtl.Point3f(-1.0, 1.0, 0.0))
      lineseg = gmtl.LineSegf(gmtl.Point3f(-1.5, 0.0, -1.0),
                              gmtl.Point3f(-1.5, 0.0, 1.0))
      (result, u, v, t) = gmtl.intersect(tri, lineseg)
      assert t == 0.5 and result == True

      # Make sure backfacing triangles don't intersect.
      tri = gmtl.Trif(gmtl.Point3f(-1.0, 0.0, 0.0),
                      gmtl.Point3f(-2.0, 0.0, 0.0),
                      gmtl.Point3f(-1.0, 1.0, 0.0))
      lineseg = gmtl.LineSegf(gmtl.Point3f(-1.5, 0.0, 1.0),
                              gmtl.Point3f(-1.5, 0.0, -1.0))
      (result, u, v, t) = gmtl.intersect(tri, lineseg)
      assert result == False

   def testIntersectRayPlane(self):
      r = gmtl.Rayf(gmtl.Point3f(0.0, 1.0, 0.0), gmtl.Vec3f(0.0, -1.0, 0.0))
      plane = gmtl.Planef(gmtl.Vec3f(0.0, 1.0, 0.0), 0.0)
      (result, t) = gmtl.intersect(plane, r)
      assert t == 1.0 and result == True

   def testIntersectRayTri(self):
      # Test t
      r = gmtl.Rayf(gmtl.Point3f(0.0, 1.0, 0.0), gmtl.Vec3f(0.0, -1.0, 0.0))
      tri = gmtl.Trif(gmtl.Point3f(-1.0, 0.0, 1.0),
                      gmtl.Point3f(1.0, 0.0, 1.0),
                      gmtl.Point3f(0.0, 0.0, -1.0))
      (result, u, v, t) = gmtl.intersect(tri, r)
      assert t == 1.0 and result == True

      # Test u and v
      r = gmtl.Rayf(gmtl.Point3f(0.25, 1.0, -0.25), gmtl.Vec3f(0.0, -1.0, 0.0))
      tri = gmtl.Trif(gmtl.Point3f(0.0, 0.0, 0.0),
                      gmtl.Point3f(1.0, 0.0, 0.0),
                      gmtl.Point3f(0.0, 0.0, -1.0))
      (result, u, v, t) = gmtl.intersect(tri, r)
      assert t == 1.0 and result == True
      assert u == 0.25 and v == 0.25

      # Test outside of tri.
      tri = gmtl.Trif(gmtl.Point3f(0.0, 0.0, 0.0),
                      gmtl.Point3f(1.0, 0.0, 0.0),
                      gmtl.Point3f(0.0, 0.0, -1.0))
      r = gmtl.Rayf(gmtl.Point3f(-0.25, 1.0, 0.0), gmtl.Vec3f(0.0, -1.0, 0.0))
      (result, u, v, t) = gmtl.intersect(tri, r)
      assert result == False
      r = gmtl.Rayf(gmtl.Point3f(0.0, 1.0, 0.25), gmtl.Vec3f(0.0, -1.0, 0.0))
      (result, u, v, t) = gmtl.intersect(tri, r)
      assert result == False

      # Right on edge of tri should give intersection.
      r = gmtl.Rayf(gmtl.Point3f(0.0, 1.0, 0.0), gmtl.Vec3f(0.0, -1.0, 0.0))
      (result, u, v, t) = gmtl.intersect(tri, r)
      assert t == 1.0 and result == True
      # Right off edge of tri should not.
      r = gmtl.Rayf(gmtl.Point3f(-0.000001, 1.0, 0.0),
                    gmtl.Vec3f(0.0, -1.0, 0.0))
      (result, u, v, t) = gmtl.intersect(tri, r)
      assert result == False

      # Test other places.

      # x/y plane
      tri = gmtl.Trif(gmtl.Point3f(-1.0, 0.0, 0.0),
                      gmtl.Point3f(0.0, 0.0, 0.0), gmtl.Point3f(0.0, 1.0, 0.0))
      r = gmtl.Rayf(gmtl.Point3f(0.0, 0.0, 1.0), gmtl.Vec3f(0.0, 0.0, -1.0))
      (result, u, v, t) = gmtl.intersect(tri, r)
      assert t == 1.0 and result == True

      # Try flipped about the x/y plane.
      tri = gmtl.Trif(gmtl.Point3f(-1.0, 0.0, 0.0),
                      gmtl.Point3f(-2.0, 0.0, 0.0),
                      gmtl.Point3f(-1.0, 1.0, 0.0))
      r = gmtl.Rayf(gmtl.Point3f(-1.5, 0.0, -1.0), gmtl.Vec3f(0.0, 0.0, 1.0))
      (result, u, v, t) = gmtl.intersect(tri, r)
      assert t == 1.0 and result == True

      # Make sure backfacing triangles don't intersect.
      tri = gmtl.Trif(gmtl.Point3f(-1.0, 0.0, 0.0),
                      gmtl.Point3f(-2.0, 0.0, 0.0),
                      gmtl.Point3f(-1.0, 1.0, 0.0))
      r = gmtl.Rayf(gmtl.Point3f(-1.5, 0.0, 1.0), gmtl.Vec3f(0.0, 0.0, -1.0))
      (result, u, v, t) = gmtl.intersect(tri, r)
      assert result == False

class LineSegMetricTest(unittest.TestCase):
   def setUp(self):
      self.origin = gmtl.Point3f(0.0, 0.0, 0.0)
      self.x1_pt  = gmtl.Point3f(1.0, 0.0, 0.0)
      self.y1_pt  = gmtl.Point3f(0.0, 1.0, 0.0)
      self.z1_pt  = gmtl.Point3f(0.0, 0.0, 1.0)
      self.x1_v   = gmtl.Vec3f(1.0, 0.0, 0.0)
      self.y1_v   = gmtl.Vec3f(0.0, 1.0, 0.0)
      self.z1_v   = gmtl.Vec3f(0.0, 0.0, 1.0)

      self.x1_lineseg = gmtl.LineSegf(self.origin, self.x1_v)
      self.y1_lineseg = gmtl.LineSegf(self.origin, self.y1_v)
      self.z1_lineseg = gmtl.LineSegf(self.origin, self.z1_v)

   def testTimingCreation(self):
      iters = 400000
      use_value = 0.0

      for iter in xrange(iters):
         test_lineseg = gmtl.LineSegf()
         use_value += test_lineseg.mDir[0] + 1.0

      assert use_value > 0.0

   def testTimingPtVecCreation(self):
      iters = 400000
      use_value = 0.0

      for iter in xrange(iters):
         test_lineseg2 = gmtl.LineSegf(self.y1_pt, self.z1_v)
         use_value += test_lineseg2.mDir[0] + 1.0

      assert use_value > 0

   def testTimingPtPtCreation(self):
      iters = 400000
      use_value = 0.0

      for iter in xrange(iters):
         test_lineseg2 = gmtl.LineSegf(self.x1_pt, self.z1_pt)
         use_value += test_lineseg2.mDir[0]

      assert use_value != 0

   def testTimingCopyConstructor(self):
      iters = 400000
      use_value = 0.0

      for iter in xrange(iters):
         test_lineseg2 = gmtl.LineSegf(self.x1_lineseg)
         use_value += test_lineseg2.mDir[0]

      assert use_value > 0

   def testTimingGetOrigin(self):
      iters = 400000
      use_value = 0.0

      for iter in xrange(iters):
         pt = self.x1_lineseg.getOrigin()
         use_value += pt[0] + 1.0

      assert use_value > 0

   def testTimingSetOrigin(self):
      test_lineseg = gmtl.LineSegf()

      iters = 400000
      use_value = 0.0

      for iter in xrange(iters):
         test_lineseg.setOrigin(self.x1_pt)
         use_value += test_lineseg.mOrigin[0]

      assert use_value > 0

   def testTimingGetDir(self):
      iters = 400000
      use_value = 0.0

      for iter in xrange(iters):
         vec = self.x1_lineseg.getDir()
         use_value += vec[0] + 1.0

      assert use_value > 0

   def testTimingSetDir(self):
      test_lineseg = gmtl.LineSegf()

      iters = 400000
      use_value = 0.0

      for iter in xrange(iters):
         test_lineseg.setDir(self.x1_v)
         use_value += test_lineseg.mDir[0]

      assert use_value > 0

   def testTimingGetLength(self):
      lineseg = gmtl.LineSegf()
      iters = 400000
      use_value = 0.0

      for iter in xrange(iters):
         use_value += lineseg.getLength()

      assert use_value == 0

   def testTimingEqualityCompare(self):
      test_lineseg1 = gmtl.LineSegf(self.x1_pt, self.x1_v)
      test_lineseg2 = gmtl.LineSegf(test_lineseg1)

      iters = 400000
      true_count = 0

      # Equality.
      for iter in xrange(iters):
         if test_lineseg1 == test_lineseg2:
            true_count += 1
         test_lineseg1.mOrigin[0] += 1.0
         test_lineseg2.mOrigin[0] += 2.0

      # Inequality.
      test_lineseg1.mOrigin = self.x1_pt
      test_lineseg1.mDir = self.x1_v
      assert test_lineseg1.mOrigin is not self.x1_pt
      assert test_lineseg1.mDir is not self.x1_v

      test_lineseg2 = gmtl.LineSegf(test_lineseg1)

      for iter in xrange(iters):
         if test_lineseg1 == test_lineseg2:
            true_count += 1
         test_lineseg1.mOrigin[0] += 1.0
         test_lineseg2.mOrigin[0] += 2.0

      assert true_count > 0

   def testTimingIsEqual(self):
      test_lineseg1 = gmtl.LineSegf(self.x1_pt, self.x1_v)
      test_lineseg2 = gmtl.LineSegf(test_lineseg1)

      iters = 400000
      true_count = 0

      for iter in xrange(iters):
         test_lineseg1.mOrigin[0] += 1.0
         test_lineseg2.mOrigin[0] += 2.0

         if gmtl.isEqual(test_lineseg1, test_lineseg2, 1.0):
            true_count += 1
         if gmtl.isEqual(test_lineseg1, test_lineseg2, 0.1):
            true_count += 1
         if gmtl.isEqual(test_lineseg1, test_lineseg2, 100000.0):
            true_count += 1

class MathTest(unittest.TestCase):
   def testQuadraticFormula(self):
      (result, r1, r2) = gmtl.Math.quadraticFormula(1.0, 3.0, 2.0)
      assert result
      assert r1 == -1
      assert r2 == -2

      (result, r1, r2) = gmtl.Math.quadraticFormula(1.0, 5.0, 6.0)
      assert result
      assert r1 == -2
      assert r2 == -3

      # Imaginary roots.
      (result, r1, r2) = gmtl.Math.quadraticFormula(1.0, 2.0, 3.0)
      assert not result

   def testSign(self):
      def __testSign(self, dataType):
         val = dataType(2.5)
         assert gmtl.Math.sign(val) == 1

         val = dataType(-2.5)
         assert gmtl.Math.sign(val) == -1

         val = dataType(0)
         assert gmtl.Math.sign(val) == 0

      def testSigni(self):
         self.__testSign(int)

      def testSignf(self):
         self.__testSign(float)

      def testSignd(self):
         self.__testSign(double)

class MatrixClassTest(unittest.TestCase):
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

   def __testMatrix44SetPtr(self, matType, dataType):
      mat44 = [
         dataType(0.0), dataType(1.0), dataType(2.0), dataType(3.0),
         dataType(4.0), dataType(5.0), dataType(6.0), dataType(7.0),
         dataType(8.0), dataType(9.0), dataType(10.0), dataType(11.0),
         dataType(12.0), dataType(13.0), dataType(14.0), dataType(15.0)]
      test_mat = matType()
      test_mat.set(mat44)

      assert test_mat(0, 0) == 0
      assert test_mat(1, 0) == 1
      assert test_mat(2, 0) == 2
      assert test_mat(3, 0) == 3
      assert test_mat(0, 1) == 4
      assert test_mat(1, 1) == 5
      assert test_mat(2, 1) == 6
      assert test_mat(3, 1) == 7
      assert test_mat(0, 2) == 8
      assert test_mat(1, 2) == 9
      assert test_mat(2, 2) == 10
      assert test_mat(3, 2) == 11
      assert test_mat(0, 3) == 12
      assert test_mat(1, 3) == 13
      assert test_mat(2, 3) == 14
      assert test_mat(3, 3) == 15

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

   def __testMatrix33SetPtr(self, matType, dataType):
      mat33 = [
         dataType(0.0), dataType(1.0), dataType(2.0),
         dataType(3.0), dataType(4.0), dataType(5.0),
         dataType(6.0), dataType(7.0), dataType(8.0)
      ]
      test_mat = matType()
      test_mat.set(mat33)

      assert test_mat(0, 0) == 0
      assert test_mat(1, 0) == 1
      assert test_mat(2, 0) == 2
      assert test_mat(0, 1) == 3
      assert test_mat(1, 1) == 4
      assert test_mat(2, 1) == 5
      assert test_mat(0, 2) == 6
      assert test_mat(1, 2) == 7
      assert test_mat(2, 2) == 8

      assert test_mat[0][0] == 0
      assert test_mat[1][0] == 1
      assert test_mat[2][0] == 2
      assert test_mat[0][1] == 3
      assert test_mat[1][1] == 4
      assert test_mat[2][1] == 5
      assert test_mat[0][2] == 6
      assert test_mat[1][2] == 7
      assert test_mat[2][2] == 8

   def testMatrixSetPtr(self):
      self.__testMatrix44SetPtr(gmtl.Matrix44f, float)
      self.__testMatrix33SetPtr(gmtl.Matrix33f, float)

   def __testMatrix44SetTransposePtr(self, matType, dataType):
      mat44 = [
         dataType(0.0), dataType(1.0), dataType(2.0), dataType(3.0),
         dataType(4.0), dataType(5.0), dataType(6.0), dataType(7.0),
         dataType(8.0), dataType(9.0), dataType(10.0), dataType(11.0),
         dataType(12.0), dataType(13.0), dataType(14.0), dataType(15.0)
      ]
      test_mat = matType()
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

   def __testMatrix33SetTransposePtr(self, matType, dataType):
      mat33 = [
         dataType(0.0), dataType(1.0), dataType(2.0),
         dataType(3.0), dataType(4.0), dataType(5.0),
         dataType(6.0), dataType(7.0), dataType(8.0)
      ]
      test_mat = matType()
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

   def testMatrixSetTransposePtr(self):
      self.__testMatrix44SetTransposePtr(gmtl.Matrix44f, float)
      self.__testMatrix33SetTransposePtr(gmtl.Matrix33f, float)

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

class MatrixClassMetricTest(unittest.TestCase):
   def testTimingDefaultConstructor(self):
      iters = 25000
      use_value = 0.0

      for iter in xrange(iters):
         test_mat33 = gmtl.Matrix33f()
         test_mat33[1][1] = 2.0
         test_mat44 = gmtl.Matrix44f()
         test_mat44[3][3] = 3.0

         use_value = use_value + test_mat33.data[4] + test_mat44.data[15]

      assert use_value > 0.0

   def testTimingCopyConstructor(self):
      src_mat33 = gmtl.Matrix33f()
      src_mat33[1][1] = 2.0
      src_mat44 = gmtl.Matrix44f()
      src_mat44[3][3] = 3.0

      iters = 25000
      for iter in xrange(iters):
         test_mat33 = gmtl.Matrix33f(src_mat33)
         test_mat44 = gmtl.Matrix44f(src_mat44)

         test_mat33[1][1] = 2.0
         test_mat44[3][3] = 3.0

   def testTimingOpEqual(self):
      src_mat33 = gmtl.Matrix33f()
      src_mat33[1][1] = 2.0
      src_mat44 = gmtl.Matrix44f()
      src_mat44[3][3] = 3.0

      iters = 25000

      test_mat33 = gmtl.Matrix33f()
      test_mat44 = gmtl.Matrix44f()

      for iter in xrange(iters):
         test_mat33 = src_mat33
         test_mat44 = src_mat44

   def testTimingOpParen(self):
      iters = 25000

      test_mat33 = gmtl.Matrix33f()
      test_mat44 = gmtl.Matrix44f()

      for iter in xrange(iters):
         # Note: gmtl.Matrix*.__call__ returns a read-only value.
         test_mat33(1, 1)
         test_mat44(3, 3)

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

class MatrixCompareTest(unittest.TestCase):
   def __testMatEquality(self, matType, dataType):
      array = [
         dataType(0.78), dataType(1.4), dataType(2.9), dataType(3.45),
         dataType(4.21), dataType(57.9), dataType(65.9), dataType(74.6),
         dataType(89.2), dataType(99.2), dataType(10.9), dataType(11.9),
         dataType(12.5), dataType(13.9), dataType(14.78), dataType(15.6),
         dataType(4.21), dataType(57.9), dataType(65.9), dataType(74.6),
         dataType(89.2), dataType(99.2), dataType(10.9), dataType(11.9),
         dataType(89.2), dataType(99.2), dataType(10.9), dataType(11.9)
      ]
      mat1 = matType()
      mat1.set(array)
      mat2 = matType()
      mat1 = matType(mat2)
      assert mat1 == mat2
      assert mat2 == mat1
      for i in range(matType.Params.Rows):
         for j in range(matType.Params.Cols):
            mat2[i][j] = dataType(1221.0)
            assert mat1 != mat2
            assert not mat1 == mat2
            mat2[i][j] = mat1[i][j]

      # Test for epsilon equals working.
      assert gmtl.isEqual(mat1, mat2)
      assert gmtl.isEqual(mat1, mat2, dataType(0.0))
      assert gmtl.isEqual(mat2, mat1, dataType(0.0))
      assert gmtl.isEqual(mat2, mat1, dataType(100000))

      eps = dataType(10.0)
      for i in range(matType.Params.Rows):
         for j in range(matType.Params.Cols):
            mat2[i][j] = mat1[i][j] - (eps / dataType(2.0))
            assert gmtl.isEqual(mat1, mat2, eps)
            assert not gmtl.isEqual(mat1, mat2, dataType(eps / 3.0))
            mat2[i][j] = mat1[i][j]

   def testMatEqualityFloatTest(self):
      self.__testMatEquality(gmtl.Matrix44f, float)
      self.__testMatEquality(gmtl.Matrix33f, float)

#   def testMatEqualityDoubleTest(self):
#      self.__testMatEquality(gmtl.Matrix44d, double)
#      self.__testMatEquality(gmtl.Matrix33d, double)

#   def testMatEqualityIntTest(self):
#      self.__testMatEquality(gmtl.Matrix44i, int)
#      self.__testMatEquality(gmtl.Matrix33i, int)

class MatrixCompareMetricTest(unittest.TestCase):
   def testMatTimingOpEqualityTest(self):
      iters = 25000

      src_mat33 = gmtl.Matrix33f()
      src_mat44 = gmtl.Matrix44f()

      # Half will be equal.
      src_mat33[1][1] = 2.0

      test_mat33 = gmtl.Matrix33f(src_mat33)
      test_mat44 = gmtl.Matrix44f(src_mat44)

      # Half will be unequal.
      src_mat44[3][3] = 3.0

      true_count = 0

      for iter in xrange(iters):
         if src_mat33 == test_mat33:
            true_count += 1
         if src_mat44 == test_mat44:
            true_count += 1

      assert true_count > 0

   def testMatTimingOpNotEqualityTest(self):
      iters = 25000

      src_mat33 = gmtl.Matrix33f()
      src_mat44 = gmtl.Matrix44f()

      # Half will be equal.
      src_mat33[1][1] = 2.0

      test_mat33 = gmtl.Matrix33f(src_mat33)
      test_mat44 = gmtl.Matrix44f(src_mat44)

      # Half will be unequal.
      src_mat44[3][3] = 3.0

      true_count = 0

      for iter in xrange(iters):
         if src_mat33 != test_mat33:
            true_count += 1
         if src_mat44 != test_mat44:
            true_count += 1

      assert true_count > 0

   def testMatTimingIsEqualTest(self):
      iters = 25000

      src_mat33 = gmtl.Matrix33f()
      src_mat44 = gmtl.Matrix44f()

      # Half will be equal.
      src_mat33[1][1] = 2.0

      test_mat33 = gmtl.Matrix33f(src_mat33)
      test_mat44 = gmtl.Matrix44f(src_mat44)

      # Half will be unequal.
      src_mat44[3][3] = 3.0

      true_count = 0

      for iter in xrange(iters):
         if gmtl.isEqual(src_mat33, test_mat33):
            true_count += 1
         if gmtl.isEqual(src_mat44, test_mat44):
            true_count += 1

      assert true_count > 0

class MatrixGenTest(unittest.TestCase):
   def testMatrixsetViewing(self):
      mat = gmtl.Matrix44f()
      gmtl.setFrustum(mat, -1.0, 1.0, 1.0, -1.0, 0.02, 100.0)
      data = [
         0.02, 0.0, 0.0, 0.0,
         0.0, 0.02, 0.0, 0.0,
         0.0, 0.0, -1.0004, -0.040008,
         0.0, 0.0, -1.0, 0.0
      ]

      expected = gmtl.Matrix44f()
      expected.setTranspose(data)

      assert gmtl.isEqual(expected, mat, 0.001)

      mat = gmtl.Matrix44f()
      gmtl.setPerspective(mat, 89.0, 1.33, 0.001, 1000.0)

      data = [
         0.765118, 0.0, 0.0, 0.0,
         0.0, 1.01761, 0.0, 0.0,
         0.0, 0.0, -1.0, -0.002,
         0.0, 0.0, -1.0, 0.0
      ]

      expected = gmtl.Matrix44f()
      expected.setTranspose(data)

      assert gmtl.isEqual(expected, mat, 0.001)

   def testMatrixsetTrans(self):
      eps = 0.001

      # 2D rot/trans/skew.
      mat33 = gmtl.Matrix33f()
      trans_vec = gmtl.Vec2f(32.0, 33.0)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(1.0, 0.0, 32.0,
                            0.0, 1.0, 33.0,
                            0.0, 0.0, 1.0)
      gmtl.setTrans(mat33, trans_vec)
      assert gmtl.isEqual(expected_result33, mat33, eps)
      test_trans_vec = gmtl.makeTransVec2(mat33)
      assert test_trans_vec == trans_vec

      # 2D rot/trans/skew by homogeneous vector.
      mat33 = gmtl.Matrix33f()
      trans_vec = gmtl.Vec3f(32.0, 33.0, 0.5)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(1.0, 0.0, 64.0,
                            0.0, 1.0, 66.0,
                            0.0, 0.0, 1.0)
      gmtl.setTrans(mat33, trans_vec)
      assert gmtl.isEqual(expected_result33, mat33, eps)
      test_trans_vec = gmtl.makeTransVec3(mat33)
      assert test_trans_vec == gmtl.Vec3f(64.0, 66.0, 1.0)

      # 3D rot/trans/skew.
      mat44 = gmtl.Matrix44f()
      expected_result44 = gmtl.Matrix44f()
      expected_result44.set(1.0, 0.0, 0.0, 32.0,
                            0.0, 1.0, 0.0, 33.0,
                            0.0, 0.0, 1.0, 34.0,
                            0.0, 0.0, 0.0, 1.0)
      gmtl.setTrans(mat44, gmtl.Vec3f(32.0, 33.0, 34.0))
      assert gmtl.isEqual(expected_result44, mat44, eps)

      # 3D rot/trans/skew by homogeneous vector.
      mat44 = gmtl.Matrix44f()
      expected_result44 = gmtl.Matrix44f()
      expected_result44.set(1.0, 0.0, 0.0, 64.0,
                            0.0, 1.0, 0.0, 66.0,
                            0.0, 0.0, 1.0, 68.0,
                            0.0, 0.0, 0.0, 1.0)
      gmtl.setTrans(mat44, gmtl.Vec4f(32.0, 33.0, 34.0, 0.5))
      assert gmtl.isEqual(expected_result44, mat44, eps)

      # Test standalone makeTrans(trans) against setTrans(mat, trans).
      expected_mat = gmtl.Matrix44f()
      trans3 = gmtl.Vec3f(1.0, 2.0, 3.0)
      gmtl.setTrans(expected_mat, trans3)
      assert gmtl.isEqual(gmtl.makeTransMatrix44(trans3), expected_mat, eps)

   def testMatrixsetAxes(self):
      eps = 0.001
      a = 98234576.0

      mat33 = gmtl.Matrix33f()
      data = []
      for i in range(9):
         data.append(a)
      mat33.set(data)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(0.0, 1.0, 0.0,
                            1.0, 0.0, 0.0,
                            0.0, 0.0, -1.0)
      gmtl.setAxes(mat33, gmtl.Vec3f(0.0, 1.0, 0.0), gmtl.Vec3f(1.0, 0.0, 0.0),
                   gmtl.Vec3f(0.0, 0.0, -1.0))

      assert gmtl.isEqual(expected_result33, mat33, eps)
      test_mat = gmtl.makeAxesMatrix33(gmtl.Vec3f(0.0, 1.0, 0.0),
                                       gmtl.Vec3f(1.0, 0.0, 0.0),
                                       gmtl.Vec3f(0.0, 0.0, -1.0))
      assert test_mat == mat33

      mat44 = gmtl.Matrix44f()
      data = []
      for i in range(16):
         data.append(a)
      mat44.set(data)
      expected_result44 = gmtl.Matrix44f()
      expected_result44.set(0.0, 1.0, 0.0, a,
                            1.0, 0.0, 0.0, a,
                            0.0, 0.0, -1.0, a,
                            a, a, a, a)
      gmtl.setAxes(mat44, gmtl.Vec3f(0.0, 1.0, 0.0), gmtl.Vec3f(1.0, 0.0, 0.0),
                   gmtl.Vec3f(0.0, 0.0, -1.0))
      assert gmtl.isEqual(expected_result44, mat44, eps)

      # Make sure make and set are the same.
      new_mat = gmtl.Matrix44f()
      gmtl.setAxes(new_mat, gmtl.Vec3f(0.0, 1.0, 0.0),
                   gmtl.Vec3f(1.0, 0.0, 0.0), gmtl.Vec3f(0.0, 0.0, -1.0))
      test_mat = gmtl.makeAxesMatrix44(gmtl.Vec3f(0.0, 1.0, 0.0),
                                       gmtl.Vec3f(1.0, 0.0, 0.0),
                                       gmtl.Vec3f(0.0, 0.0, -1.0))
      assert test_mat == new_mat

   def testMatrixsetDirCos(self):
      eps = 0.01

      # Two points that should match in different frames.
      pt_I = gmtl.Point3f(1.0, 0.0, 0.0)        # Point in identity frame
      pt_T = gmtl.Point3f(0.0, 0.0, 1.0)        # Point in the transformed frame

      # Basis vectors of the T coordinate frame in the I coordinate frame.
      x_axis = gmtl.Vec3f(0.0, 1.0, 0.0)
      y_axis = gmtl.Vec3f(0.0, 0.0, 1.0)
      z_axis = gmtl.Vec3f(1.0, 0.0, 0.0)

      # Build the transformation matrix.
      i_M_t = gmtl.makeDirCosMatrix44(x_axis, y_axis, z_axis)

      # Test point going from T to I.
      result_pt = i_M_t * pt_T
      assert gmtl.isEqual(result_pt, pt_I, eps)

      # Test point going from I to T.
      result_pt = gmtl.makeInvert(i_M_t) * pt_I
      assert gmtl.isEqual(result_pt, pt_T, eps)

   def testMatrixsetScale(self):
      eps = 0.001
      a = 98234576.0

      # 2D rot/trans/skew.
      mat33 = gmtl.Matrix33f()
      data = []
      for i in range(9):
         data.append(a)
      mat33.set(data)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(32.0, a, a,
                            a, 33.0, a,
                            a, a, a)
      gmtl.setScale(mat33, gmtl.Vec2f(32.0, 33.0))
      assert gmtl.isEqual(expected_result33, mat33, eps)

      # Make sure set and make are the same.
      new_mat = gmtl.Matrix33f()
      gmtl.setScale(new_mat, gmtl.Vec2f(32.0, 33.0))
      assert gmtl.makeScaleMatrix33(gmtl.Vec2f(32.0, 33.0)) == new_mat

      # 3D rot/trans/skew.
      mat44 = gmtl.Matrix44f()
      data = []
      for i in range(16):
         data.append(a)
      mat44.set(data)
      expected_result44 = gmtl.Matrix44f()
      expected_result44.set(32.0, a, a, a,
                            a, 33.0, a, a,
                            a, a, 34.0, a,
                            a, a, a, a)
      gmtl.setScale(mat44, gmtl.Vec3f(32.0, 33.0, 34.0))
      assert gmtl.isEqual(expected_result44, mat44, eps)

      # Make sure set and make are the same.
      new_mat = gmtl.Matrix44f()
      gmtl.setScale(new_mat, gmtl.Vec3f(32.0, 33.0, 34.0))
      assert gmtl.makeScaleMatrix44(gmtl.Vec3f(32.0, 33.0, 34.0)) == new_mat

      # 2D rot/trans/skew.
      mat33 = gmtl.Matrix33f()
      data = []
      for i in range(9):
         data.append(a)
      mat33.set(data)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(32.0, a, a,
                            a, 32.0, a,
                            a, a, a)
      gmtl.setScale(mat33, 32.0)
      assert gmtl.isEqual(expected_result33, mat33, eps)

      # Make sure set and make are the same.
      new_mat = gmtl.Matrix33f()
      gmtl.setScale(new_mat, 32.0)
      assert gmtl.makeScaleMatrix33(32.0) == new_mat

      # 3D rot/trans/skew.
      mat44 = gmtl.Matrix44f()
      data = []
      for i in range(16):
         data.append(a)
      mat44.set(data)
      expected_result44 = gmtl.Matrix44f()
      expected_result44.set(32.0, a, a, a,
                            a, 32.0, a, a,
                            a, a, 32.0, a,
                            a, a, a, a)
      gmtl.setScale(mat44, 32.0)
      assert gmtl.isEqual(expected_result44, mat44, eps)

      # MAke sure set and make are the same.
      new_mat = gmtl.Matrix44f()
      gmtl.setScale(new_mat, 32.0)
      assert gmtl.makeScaleMatrix44(32.0) == new_mat

   def testMatrixsetRot(self):
      eps = 0.01
      a = 98234576.0

      mat = gmtl.Matrix33f()
      data = []
      for i in range(9):
         data.append(a)
      mat.set(data)

      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(1.0, 0.0, 0.0,
                            0.0, 0.0, -1.0,
                            0.0, 1.0, 0.0)
      vec = gmtl.Vec3f(1.0, 0.0, 0.0)
      gmtl.normalize(vec)
      gmtl.setRot(mat, gmtl.AxisAnglef(gmtl.Math.deg2Rad(90.0), vec))
      assert gmtl.isEqual(expected_result33, mat, eps)

      # Make sure that the other version works the same.
      mat2 = gmtl.Matrix33f()
      gmtl.setRot(mat2, gmtl.makeNormal(gmtl.AxisAnglef(gmtl.Math.deg2Rad(90.0),
                                                        1.0, 0.0, 0.0)))
      assert gmtl.isEqual(mat2, mat, eps)

      # Make sure set and make are the smae.
      mat3 = gmtl.makeRotMatrix33(gmtl.makeNormal(gmtl.AxisAnglef(gmtl.Math.deg2Rad(90.0),
                                                                  1.0, 0.0, 0.0)))
      assert mat3 == mat2

      mat = gmtl.Matrix33f()
      data = []
      for i in range(9):
         data.append(a)
      mat.set(data)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(1.0, 0.0, 0.0,
                            0.0, 1.0, 0.0,
                            0.0, 0.0, 1.0)
      vec = gmtl.Vec3f(-1.0, 1.0, -1.0)
      gmtl.normalize(vec)
      gmtl.setRot(mat, gmtl.AxisAnglef(gmtl.Math.deg2Rad(-360.0), vec))
      assert gmtl.isEqual(expected_result33, mat, eps)

      # Make sure that the other version works the same.
      mat2 = gmtl.Matrix33f()
      gmtl.setRot(mat2,
                  gmtl.makeNormal(gmtl.AxisAnglef(gmtl.Math.deg2Rad(-360.0),
                                                  -1.0, 1.0, -1.0)))
      assert gmtl.isEqual(mat2, mat, eps)

      # Make sure set and make are the smae.
      mat3 = gmtl.makeRotMatrix33(gmtl.makeNormal(gmtl.AxisAnglef(gmtl.Math.deg2Rad(-360.0),
                                                                  -1.0, 1.0, -1.0)))
      assert gmtl.isEqual(mat3, mat2, eps)
      mat3 = gmtl.makeRotMatrix33(gmtl.AxisAnglef(gmtl.Math.deg2Rad(-360.0),
                                                  vec))
      assert gmtl.isEqual(mat3, mat2, eps)

      # Test that unnormalized vedc works.
      mat = gmtl.Matrix44f()
      data = []
      for i in range(16):
         data.append(a)
      mat.set(data)
      expected_result44 = gmtl.Matrix44f()
      expected_result44.set(0.804738, -0.310617, 0.505879, a,
                            0.505879, 0.804738, -0.310617, a,
                            -0.310617, 0.505879, 0.804738, a,
                            a, a, a, a)
      vec = gmtl.Vec3f(1.7, 1.7, 1.7)
      gmtl.normalize(vec)
      gmtl.setRot(mat, gmtl.AxisAnglef(gmtl.Math.deg2Rad(45.0), vec))
      assert gmtl.isEqual(expected_result44, mat, eps)

      # Make sure that the other version works the same.
      mat2 = gmtl.Matrix44f()
      mat2.set(data)
      gmtl.setRot(mat2, gmtl.makeNormal(gmtl.AxisAnglef(gmtl.Math.deg2Rad(45.0),
                                                        1.7, 1.7, 1.7)))
      assert gmtl.isEqual(mat2, mat, eps)

      # Make sure set and make are the same.
      new_mat = gmtl.Matrix44f()
      gmtl.setRot(new_mat,
                  gmtl.makeNormal(gmtl.AxisAnglef(gmtl.Math.deg2Rad(45.0),
                                                  1.7, 1.7, 1.7)))
      assert gmtl.makeRotMatrix44(gmtl.makeNormal(gmtl.AxisAnglef(gmtl.Math.deg2Rad(45.0),
                                                                  1.7, 1.7, 1.7))) == new_mat
      gmtl.setRot(new_mat, gmtl.AxisAnglef(gmtl.Math.deg2Rad(45.0), vec))
      assert gmtl.makeRotMatrix44(gmtl.AxisAnglef(gmtl.Math.deg2Rad(45.0), vec)) == new_mat

      # Test standalone now.
      mat = gmtl.Matrix44f()
      rot_axis = gmtl.Vec3f(1.0, 2.0, 3.0)
      gmtl.normalize(rot_axis)
      axis_angle = gmtl.AxisAnglef(1.1, rot_axis)
      expected_mat = gmtl.Matrix44f()
      gmtl.setRot(expected_mat, axis_angle)
      mat = gmtl.makeRotMatrix44(axis_angle)
      assert gmtl.isEqual(mat, expected_mat, eps)
      assert gmtl.isEqual(gmtl.makeRotMatrix44(axis_angle), expected_mat, eps)

   def testMatrixgetRotEuler(self):
      eps = 0.01
      matrix = gmtl.Matrix44f()

      # XYZ
      euler = gmtl.EulerAngleXYZf()
      gmtl.set(matrix, gmtl.AxisAnglef(gmtl.Math.deg2Rad(90.0), 1.0, 0.0, 0.0))
      gmtl.set(euler, matrix)
      assert isEqual(gmtl.Math.rad2Deg(euler[0]), 90.0, eps)
      assert isEqual(gmtl.Math.rad2Deg(euler[1]), 0.0, eps)
      assert isEqual(gmtl.Math.rad2Deg(euler[2]), 0.0, eps)

      gmtl.set(matrix, gmtl.AxisAnglef(gmtl.Math.deg2Rad(-90.0), 1.0, 0.0, 0.0))
      gmtl.set(euler, matrix)
      assert isEqual(gmtl.Math.rad2Deg(euler[0]), -90.0, eps)
      assert isEqual(gmtl.Math.rad2Deg(euler[1]), 0.0, eps)
      assert isEqual(gmtl.Math.rad2Deg(euler[2]), 0.0, eps)

      gmtl.set(matrix, gmtl.AxisAnglef(gmtl.Math.deg2Rad(35.0), 0.0, 1.0, 0.0))
      gmtl.set(euler, matrix)
      assert isEqual(gmtl.Math.rad2Deg(euler[0]), 0.0, eps)
      assert isEqual(gmtl.Math.rad2Deg(euler[1]), 35.0, eps)
      assert isEqual(gmtl.Math.rad2Deg(euler[2]), 0.0, eps)

      # Test cos y = 0 singularity.
      gmtl.set(matrix, gmtl.AxisAnglef(gmtl.Math.deg2Rad(90.0), 0.0, 1.0, 0.0))
      gmtl.set(euler, matrix)
      assert isEqual(gmtl.Math.rad2Deg(euler[0]), -180.0, eps)
      assert isEqual(gmtl.Math.rad2Deg(euler[1]), 90.0, eps)
      assert isEqual(gmtl.Math.rad2Deg(euler[2]), -180.0, eps)

      # Test cos z = 0 singularity.
      gmtl.set(matrix, gmtl.AxisAnglef(gmtl.Math.deg2Rad(90.0), 0.0, 0.0, 1.0))
      gmtl.set(euler, matrix)
      assert isEqual(gmtl.Math.rad2Deg(euler[0]), 0.0, eps)
      assert isEqual(gmtl.Math.rad2Deg(euler[1]), 0.0, eps)
      assert isEqual(gmtl.Math.rad2Deg(euler[2]), 90.0, eps)

      # ZYX
      euler = gmtl.EulerAngleZYXf()
      gmtl.set(matrix, gmtl.AxisAnglef(gmtl.Math.deg2Rad(90.0), 1.0, 0.0, 0.0))
      gmtl.set(euler, matrix)
      assert isEqual(gmtl.Math.rad2Deg(euler[0]), 0.0, eps)
      assert isEqual(gmtl.Math.rad2Deg(euler[1]), 0.0, eps)
      assert isEqual(gmtl.Math.rad2Deg(euler[2]), 90.0, eps)

      gmtl.set(matrix, gmtl.AxisAnglef(gmtl.Math.deg2Rad(-90.0), 1.0, 0.0, 0.0))
      gmtl.set(euler, matrix)
      assert isEqual(gmtl.Math.rad2Deg(euler[0]), 0.0, eps)
      assert isEqual(gmtl.Math.rad2Deg(euler[1]), 0.0, eps)
      assert isEqual(gmtl.Math.rad2Deg(euler[2]), -90.0, eps)

      # Test sin x = 0 singularity.
      gmtl.set(matrix, gmtl.AxisAnglef(gmtl.Math.deg2Rad(90.0), 0.0, 0.0, 1.0))
      gmtl.set(euler, matrix)
#      assert isEqual(gmtl.Math.rad2Deg(euler[0]), 0.0, eps)
#      assert isEqual(gmtl.Math.rad2Deg(euler[1]), 35.0, eps)
#      assert isEqual(gmtl.Math.rad2Deg(euler[2]), 0.0, eps)

      # Test cos y = 0 singularity.
      gmtl.set(matrix, gmtl.AxisAnglef(gmtl.Math.deg2Rad(90.0), 0.0, 1.0, 0.0))
      gmtl.set(euler, matrix)
      assert isEqual(gmtl.Math.rad2Deg(euler[0]), 180.0, eps)
      assert isEqual(gmtl.Math.rad2Deg(euler[1]), 90.0, eps)
      assert isEqual(gmtl.Math.rad2Deg(euler[2]), 180.0, eps)

   def testMatrixsetRotEuler(self):
      eps = 0.001
      a = 98234576.0

      mat = gmtl.Matrix33f()
      data = []
      for i in range(9):
         data.append(a)
      mat.set(data)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(0.683013, -0.183013, 0.707107,
                            0.683013, -0.183013, -0.707107,
                            0.258819, 0.965926, 0.0)
      gmtl.setRot(mat, gmtl.EulerAngleXYZf(gmtl.Math.deg2Rad(90.0),
                                           gmtl.Math.deg2Rad(45.0),
                                           gmtl.Math.deg2Rad(15.0)))
      assert gmtl.isEqual(expected_result33, mat, eps)

      mat = gmtl.Matrix33f()
      data = []
      for i in range(9):
         data.append(a)
      mat.set(data)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(1.0, 0.0, 0.0,
                            0.0, 0.0, -1.0,
                            0.0, 1.0, 0.0)
      gmtl.setRot(mat, gmtl.EulerAngleXYZf(gmtl.Math.deg2Rad(90.0),
                                           gmtl.Math.deg2Rad(0.0),
                                           gmtl.Math.deg2Rad(0.0)))
      assert gmtl.isEqual(expected_result33, mat, eps)

      # Make sure set and make are the same.
      assert gmtl.makeRotMatrix33(gmtl.EulerAngleXYZf(gmtl.Math.deg2Rad(90.0),
                                                      gmtl.Math.deg2Rad(0.0),
                                                      gmtl.Math.deg2Rad(0.0))) == mat

      mat = gmtl.Matrix33f()
      data = []
      for i in range(9):
         data.append(a)
      mat.set(data)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(0.0, 0.0, 1.0,
                            0.0, 1.0, 0.0,
                            -1.0, 0.0, 0.0)
      gmtl.setRot(mat, gmtl.EulerAngleXYZf(gmtl.Math.deg2Rad(0.0),
                                           gmtl.Math.deg2Rad(90.0),
                                           gmtl.Math.deg2Rad(0.0)))
      assert gmtl.isEqual(expected_result33, mat, eps)

      # Make sure set and make are the same.
      assert gmtl.makeRotMatrix33(gmtl.EulerAngleXYZf(gmtl.Math.deg2Rad(0.0),
                                                      gmtl.Math.deg2Rad(90.0),
                                                      gmtl.Math.deg2Rad(0.0))) == mat

      mat = gmtl.Matrix33f()
      data = []
      for i in range(9):
         data.append(a)
      mat.set(data)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(0.0, -1.0, 0.0,
                            1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0)
      gmtl.setRot(mat, gmtl.EulerAngleXYZf(gmtl.Math.deg2Rad(0.0),
                                           gmtl.Math.deg2Rad(0.0),
                                           gmtl.Math.deg2Rad(90.0)))
      assert gmtl.isEqual(expected_result33, mat, eps)

      # Make sure set and make are the same.
      assert gmtl.makeRotMatrix33(gmtl.EulerAngleXYZf(gmtl.Math.deg2Rad(0.0),
                                                      gmtl.Math.deg2Rad(0.0),
                                                      gmtl.Math.deg2Rad(90.0))) == mat

      mat = gmtl.Matrix44f()
      data = []
      for i in range(16):
         data.append(a)
      mat.set(data)
      expected_result44 = gmtl.Matrix44f()
      expected_result44.set(0.697193, 0.0121696, 0.71678, a,
                            -0.275553, -0.918494, 0.283617, a,
                            0.66181, -0.395247, -0.637014, a,
                            a, a, a, a)
      gmtl.setRot(mat, gmtl.EulerAngleXYZf(gmtl.Math.deg2Rad(-156.0),
                                           gmtl.Math.deg2Rad(45.7892892),
                                           gmtl.Math.deg2Rad(-361.0)))
      assert gmtl.isEqual(expected_result44, mat, eps)

      # Make sure set and make are the same.
      new_mat = gmtl.Matrix44f()
      gmtl.setRot(new_mat, gmtl.EulerAngleXYZf(gmtl.Math.deg2Rad(-156.0),
                                               gmtl.Math.deg2Rad(45.7892892),
                                               gmtl.Math.deg2Rad(-361.0)))
      assert gmtl.makeRotMatrix44(gmtl.EulerAngleXYZf(gmtl.Math.deg2Rad(-156.0),
                                                      gmtl.Math.deg2Rad(45.7892892),
                                                      gmtl.Math.deg2Rad(-361.0))) == new_mat

      # ZYX.
      mat = gmtl.Matrix33f()
      data = []
      for i in range(9):
         data.append(a)
      mat.set(data)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(0.0, -0.965926, 0.258819,
                            0.707107, 0.183013, 0.683013,
                            -0.707107, 0.183013, 0.683013)
      gmtl.setRot(mat, gmtl.EulerAngleZYXf(gmtl.Math.deg2Rad(90.0),
                                           gmtl.Math.deg2Rad(45.0),
                                           gmtl.Math.deg2Rad(15.0)))
      assert gmtl.isEqual(expected_result33, mat, eps)

      # Make sure set and make are the same.
      assert gmtl.makeRotMatrix33(gmtl.EulerAngleZYXf(gmtl.Math.deg2Rad(90.0),
                                                      gmtl.Math.deg2Rad(45.0),
                                                      gmtl.Math.deg2Rad(15.0))) == mat

      mat = gmtl.Matrix33f()
      data = []
      for i in range(9):
         data.append(a)
      mat.set(data)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(0.0, -1.0, 0.0,
                            1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0)
      gmtl.setRot(mat, gmtl.EulerAngleZYXf(gmtl.Math.deg2Rad(90.0),
                                           gmtl.Math.deg2Rad(0.0),
                                           gmtl.Math.deg2Rad(0.0)))
      assert gmtl.isEqual(expected_result33, mat, eps)

      # Make sure set and make are the same.
      new_mat = gmtl.Matrix33f()
      gmtl.setRot(new_mat, gmtl.EulerAngleZYXf(gmtl.Math.deg2Rad(90.0),
                                               gmtl.Math.deg2Rad(0.0),
                                               gmtl.Math.deg2Rad(0.0)))
      assert gmtl.makeRotMatrix33(gmtl.EulerAngleZYXf(gmtl.Math.deg2Rad(90.0),
                                                      gmtl.Math.deg2Rad(0.0),
                                                      gmtl.Math.deg2Rad(0.0))) == new_mat

      mat = gmtl.Matrix33f()
      data = []
      for i in range(9):
         data.append(a)
      mat.set(data)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(0.0, 0.0, 1.0,
                            0.0, 1.0, 0.0,
                            -1.0, 0.0, 0.0)
      gmtl.setRot(mat, gmtl.EulerAngleZYXf(gmtl.Math.deg2Rad(0.0),
                                           gmtl.Math.deg2Rad(90.0),
                                           gmtl.Math.deg2Rad(0.0)))
      assert gmtl.isEqual(expected_result33, mat, eps)

      # Make sure set and make are the same.
      assert gmtl.makeRotMatrix33(gmtl.EulerAngleZYXf(gmtl.Math.deg2Rad(0.0),
                                                      gmtl.Math.deg2Rad(90.0),
                                                      gmtl.Math.deg2Rad(0.0))) == mat

      mat = gmtl.Matrix33f()
      data = []
      for i in range(9):
         data.append(a)
      mat.set(data)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(1.0, 0.0, 0.0,
                            0.0, 0.0, -1.0,
                            0.0, 1.0, 0.0)
      gmtl.setRot(mat, gmtl.EulerAngleZYXf(gmtl.Math.deg2Rad(0.0),
                                           gmtl.Math.deg2Rad(0.0),
                                           gmtl.Math.deg2Rad(90.0)))
      assert gmtl.isEqual(expected_result33, mat, eps)

      # Make sure set and make are the same.
      assert gmtl.makeRotMatrix33(gmtl.EulerAngleZYXf(gmtl.Math.deg2Rad(0.0),
                                                      gmtl.Math.deg2Rad(0.0),
                                                      gmtl.Math.deg2Rad(90.0))) == mat

      mat = gmtl.Matrix44f()
      data = []
      for i in range(16):
         data.append(a)
      mat.set(data)
      expected_result44 = gmtl.Matrix44f()
      expected_result44.set(-0.637014, 0.418103, -0.647613, a,
                            -0.283617, -0.908318, -0.30744, a,
                            -0.71678, -0.0121696, 0.697193, a,
                            a, a, a, a)
      gmtl.setRot(mat, gmtl.EulerAngleZYXf(gmtl.Math.deg2Rad(-156.0),
                                           gmtl.Math.deg2Rad(45.7892892),
                                           gmtl.Math.deg2Rad(-361.0)))
      assert gmtl.isEqual(expected_result44, mat, eps)

      # Make sure set and make are the same.
      new_mat = gmtl.Matrix44f()
      gmtl.setRot(new_mat, gmtl.EulerAngleZYXf(gmtl.Math.deg2Rad(-156.0),
                                               gmtl.Math.deg2Rad(45.7892892),
                                               gmtl.Math.deg2Rad(-361.0)))
      assert gmtl.makeRotMatrix44(gmtl.EulerAngleZYXf(gmtl.Math.deg2Rad(-156.0),
                                                      gmtl.Math.deg2Rad(45.7892892),
                                                      gmtl.Math.deg2Rad(-361.0))) == new_mat

      # ZXY.
      mat = gmtl.Matrix33f()
      data = []
      for i in range(9):
         data.append(a)
      mat.set(data)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(-0.183013, -0.707107, 0.683013,
                             0.965926, 0.0,       0.258819,
                            -0.183013, 0.707107,  0.683013)
      gmtl.setRot(mat, gmtl.EulerAngleZXYf(gmtl.Math.deg2Rad(90.0),
                                           gmtl.Math.deg2Rad(45.0),
                                           gmtl.Math.deg2Rad(15.0)))
      assert gmtl.isEqual(expected_result33, mat, eps)

      mat = gmtl.Matrix33f()
      data = []
      for i in range(9):
         data.append(a)
      mat.set(data)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(0.0, -1.0, 0.0,
                            1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0)
      gmtl.setRot(mat, gmtl.EulerAngleZXYf(gmtl.Math.deg2Rad(90.0),
                                           gmtl.Math.deg2Rad(0.0),
                                           gmtl.Math.deg2Rad(0.0)))
      assert gmtl.isEqual(expected_result33, mat, eps)

      mat = gmtl.Matrix33f()
      data = []
      for i in range(9):
         data.append(a)
      mat.set(data)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(1.0, 0.0, 0.0,
                            0.0, 0.0, -1.0,
                            0.0, 1.0, 0.0)
      gmtl.setRot(mat, gmtl.EulerAngleZXYf(gmtl.Math.deg2Rad(0.0),
                                           gmtl.Math.deg2Rad(90.0),
                                           gmtl.Math.deg2Rad(0.0)))
      assert gmtl.isEqual(expected_result33, mat, eps)

      mat = gmtl.Matrix33f()
      data = []
      for i in range(9):
         data.append(a)
      mat.set(data)
      expected_result33 = gmtl.Matrix33f()
      expected_result33.set(0.0, 0.0, 1.0,
                            0.0, 1.0, 0.0,
                            -1.0, 0.0, 0.0)
      gmtl.setRot(mat, gmtl.EulerAngleZXYf(gmtl.Math.deg2Rad(0.0),
                                           gmtl.Math.deg2Rad(0.0),
                                           gmtl.Math.deg2Rad(90.0)))
      assert gmtl.isEqual(expected_result33, mat, eps)

      mat = gmtl.Matrix44f()
      data = []
      for i in range(16):
         data.append(a)
      mat.set(data)
      expected_result44 = gmtl.Matrix44f()
      expected_result44.set(-0.918494, 0.283617, -0.275553, a,
                            -0.395247, -0.637014, 0.66181, a,
                            0.0121696, 0.71678, 0.697193, a,
                            a, a, a, a)
      gmtl.setRot(mat, gmtl.EulerAngleZXYf(gmtl.Math.deg2Rad(-156.0),
                                           gmtl.Math.deg2Rad(45.7892892),
                                           gmtl.Math.deg2Rad(-361.0)))
      assert gmtl.isEqual(expected_result44, mat, eps)

      # Test standalone setRot(val, val, val) against setRot(mat, val, val, val)
      expected_mat = gmtl.Matrix44f()
      gmtl.setRot(expected_mat, gmtl.EulerAngleXYZf(0.1, 2.3, -2.1))
      mat = gmtl.makeRotMatrix44(gmtl.EulerAngleXYZf(0.1, 2.3, -2.1))
      assert gmtl.isEqual(mat, expected_mat, eps)

      gmtl.setRot(expected_mat, gmtl.EulerAngleZXYf(0.1, 2.3, -2.1))
      mat = gmtl.makeRotMatrix44(gmtl.EulerAngleZXYf(0.1, 2.3, -2.1))
      assert gmtl.isEqual(mat, expected_mat, eps)

      gmtl.setRot(expected_mat, gmtl.EulerAngleZYXf(0.1, 2.3, -2.1))
      mat = gmtl.makeRotMatrix44(gmtl.EulerAngleZYXf(0.1, 2.3, -2.1))
      assert gmtl.isEqual(mat, expected_mat, eps)

      expected_mat = gmtl.Matrix33f()
      gmtl.setRot(expected_mat, gmtl.EulerAngleXYZf(0.1, 2.3, -2.1))
      mat = gmtl.makeRotMatrix33(gmtl.EulerAngleXYZf(0.1, 2.3, -2.1))
      assert gmtl.isEqual(mat, expected_mat, eps)

      gmtl.setRot(expected_mat, gmtl.EulerAngleZXYf(0.1, 2.3, -2.1))
      mat = gmtl.makeRotMatrix33(gmtl.EulerAngleZXYf(0.1, 2.3, -2.1))
      assert gmtl.isEqual(mat, expected_mat, eps)

      gmtl.setRot(expected_mat, gmtl.EulerAngleZYXf(0.1, 2.3, -2.1))
      mat = gmtl.makeRotMatrix33(gmtl.EulerAngleZYXf(0.1, 2.3, -2.1))
      assert gmtl.isEqual(mat, expected_mat, eps)

   def __matMakeInverse(self, matType):
      eps = 0.001
      mat1 = matType()
      mat1.set(0.78,  1.4,   2.9, 3.45,
               4.21, 57.9,  65.9, 74.6,
               89.2, 99.2,  10.9, 11.9,
               12.5, 13.9, 14.78, 15.6)
      expected_value = matType()
      expected_value.set( 0.3071733, -0.0239700,  0.0034853,  0.0440345,
                         -0.2891106,  0.0216826,  0.0079218, -0.0457924,
                         -3.0532152,  0.0305681, -0.0547335,  0.5708037,
                          2.9041982, -0.0290744,  0.0420053, -0.4711792)

      identity = matType()

      # Make sure our pre-computed answer is right.
      result = matType()
      gmtl.mult(result, mat1, expected_value)
      assert gmtl.isEqual(result, identity, eps)

      # Test inversion.
      result = gmtl.makeInvert(mat1)
      assert gmtl.isEqual(result, expected_value, eps)

   def testMatrixmakeInverse(self):
      self.__matMakeInverse(gmtl.Matrix44f)
#      self.__matMakeInverse(gmtl.Matrix44d)

class MatrixGenMetricTest(unittest.TestCase):
   def testTimingsetTrans(self):
      mat33 = gmtl.Matrix33f()
      mat44 = gmtl.Matrix44f()
      a = 1.0
      iters = 25000

      # 2D translation.
      for iter in xrange(iters):
         gmtl.setTrans(mat33, gmtl.Vec2f(a, 2.0))
         a += mat33.data[3]

      assert mat33.data[3] != 1234.0456 and a != 987654.321

      for iter in xrange(iters):
         gmtl.setTrans(mat33, gmtl.Vec3f(1.0, a, 1.0))   # homogeneous
         a += mat33.data[3]

      assert mat33.data[3] != 1234.0456 and a != 987654.321

      # 3D translation.
      for iter in xrange(iters):
         gmtl.setTrans(mat44, gmtl.Vec3f(30.0, a, 121.0))
         a += mat44.data[3]

      assert mat44.data[3] != 1234.0456 and a != 987654.321

      for iter in xrange(iters):
         gmtl.setTrans(mat44, gmtl.Vec4f(30.0, 32.0, a, 1.0))   # homogeneous
         a += mat44.data[3]

      assert mat44.data[3] != 1234.0456 and a != 987654.321

   def testTimingsetScale(self):
      a = 2.1
      mat33 = gmtl.Matrix33f()
      mat44 = gmtl.Matrix44f()
      iters = 25000

      for iter in xrange(iters):
         gmtl.setScale(mat33, gmtl.Vec2f(a, 2.0))
         a += mat33.data[3]

      assert mat33.data[3] != 1234.0456 and a != 987654.321

      for iter in xrange(iters):
         gmtl.setScale(mat44, gmtl.Vec3f(30.0, 32.0, a))
         a += mat44.data[3]

      assert mat44.data[3] != 1234.0456 and a != 987654.321

      for iter in xrange(iters):
         gmtl.setScale(mat33, a)
         a += mat33.data[3]

      assert mat33.data[3] != 1234.0456 and a != 987654.321

      for iter in xrange(iters):
         gmtl.setScale(mat44, a)
         a += mat44.data[3]

      assert mat44.data[3] != 1234.0456 and a != 987654.321

   def testTimingsetRot33(self):
      mat = gmtl.Matrix33f()
      a = 0.0
      iters = 25000

      for iter in xrange(iters):
         gmtl.setRot(mat, gmtl.AxisAnglef(gmtl.Math.deg2Rad(a), 1.0, 0.0, 0.0))
         a += mat.data[3]

      assert mat.data[3] != 1234.0456 and a != 987654.321

   def testTimingsetRot44(self):
      mat = gmtl.Matrix44f()
      a = 0.0
      iters = 25000

      for iter in xrange(iters):
         gmtl.setRot(mat, gmtl.AxisAnglef(gmtl.Math.deg2Rad(a), 1.0, 0.0, 0.0))
         a += mat.data[3]

      assert mat.data[3] != 1234.0456 and a != 987654.321

   def testTimingGetRot(self):
      pass

   def __testTimingsetRotEuler(self, mat):
      a = 0.0
      iters = 25000

      for iter in xrange(iters):
         gmtl.setRot(mat, gmtl.EulerAngleZXYf(a, 45.0, 35.0))
         a -= mat.data[4]

      assert mat.data[3] != 1234.0456 and a != 987654.321

      for iter in xrange(iters):
         gmtl.setRot(mat, gmtl.EulerAngleZYXf(a, 45.0, 35.0))
         a += mat.data[4]

      assert mat.data[3] != 1234.0456 and a != 987654.321

      for iter in xrange(iters):
         gmtl.setRot(mat, gmtl.EulerAngleXYZf(a, 45.0, 35.0))
         a -= mat.data[4]

      assert mat.data[3] != 1234.0456 and a != 987654.321

   def testTimingsetRotEuler33(self):
      self.__testTimingsetRotEuler(gmtl.Matrix33f())

#   def testTimingsetRotEuler34(self):
#      self.__testTimingsetRotEuler(gmtl.Matrix34f())

   def testTimingsetRotEuler44(self):
      self.__testTimingsetRotEuler(gmtl.Matrix44f())

   def __testTimingsetDirCos(self, mat):
      a = 0.0
      iters = 25000

      for iter in xrange(iters):
         gmtl.setDirCos(mat, gmtl.Vec3f(1.0, 0.0, 0.0),
                        gmtl.Vec3f(a, 1.0, 0.0), gmtl.Vec3f(0.0, 0.0, 1.0))
         a += mat.data[1]

      assert mat.data[3] != 1234.0456 and a != 987654.321

   def testTimingsetDirCos33(self):
      self.__testTimingsetDirCos(gmtl.Matrix33f())

#   def testTimingsetDirCos34(self):
#      self.__testTimingsetDirCos(gmtl.Matrix34f())

   def testTimingsetDirCos44(self):
      self.__testTimingsetDirCos(gmtl.Matrix44f())

   def __testTimingsetAxes(self, mat):
      a = 0.0
      iters = 25000

      for iter in xrange(iters):
         gmtl.setAxes(mat, gmtl.Vec3f(1.0, a, 0.0), gmtl.Vec3f(0.0, 1.0, 0.0),
                      gmtl.Vec3f(0.0, 0.0, 1.0))
         a += mat.data[1]

      assert mat.data[3] != 1234.0456 and a != 987654.321

   def testTimingsetAxes33(self):
      self.__testTimingsetAxes(gmtl.Matrix33f())

#   def testTimingsetAxes34(self):
#      self.__testTimingsetAxes(gmtl.Matrix34f())

   def testTimingsetAxes44(self):
      self.__testTimingsetAxes(gmtl.Matrix44f())

class MatrixOpsTest(unittest.TestCase):
   def testMatrixIdentity(self):
      ident_mat = gmtl.Matrix44f()
      test_mat = gmtl.Matrix44f()
      test_mat.set(0.0, 1.0, 2.0, 3.0,
                   0.0, 1.0, 2.0, 3.0,
                   0.0, 1.0, 2.0, 3.0,
                   0.0, 1.0, 2.0, 3.0)
      assert test_mat != ident_mat
      gmtl.identity(test_mat)
      assert test_mat == ident_mat

   def testMatrixSetTrans(self):
      eps = 0.01

      # 3D trans.
      mat44 = gmtl.Matrix44f()
      expected_result44 = gmtl.Matrix44f()
      gmtl.setRot(expected_result44, gmtl.EulerAngleXYZf(0.5, 1.0, -1.0))
      expected_result44[0][3] = 21
      expected_result44[1][3] = 22
      expected_result44[2][3] = 23

      gmtl.setRot(mat44, gmtl.EulerAngleXYZf(0.5, 1.0, -1.0))
      gmtl.setTrans(mat44, gmtl.Vec3f(21.0, 22.0, 23.0))
      assert gmtl.isEqual(expected_result44, mat44, eps)

      # 3D rot/trans/skew set by homogeneous vector.
      mat44 = gmtl.Matrix44f()
      expected_result44 = gmtl.Matrix44f()

      gmtl.setRot(expected_result44, gmtl.EulerAngleXYZf(0.5, 1.0, -1.0))
      expected_result44[0][3] = 42
      expected_result44[1][3] = 44
      expected_result44[2][3] = 46

      gmtl.setRot(mat44, gmtl.EulerAngleXYZf(0.5, 1.0, -1.0))
      gmtl.setTrans(mat44, gmtl.Vec4f(21.0, 22.0, 23.0, 0.5))
      assert gmtl.isEqual(expected_result44, mat44, eps)

   def __transposeTest(self, matType):
      test_mat = matType()
      res_mat  = matType()
      test_mat[test_mat.Params.Rows - 1][0] = 9
      res_mat[0][test_mat.Params.Rows - 1]  = 9

      test_mat[1][0] = 2
      res_mat[0][1]  = 2

      gmtl.transpose(res_mat)
      assert res_mat == test_mat
      gmtl.transpose(res_mat)

      # Test the other transpose op.
      gmtl.transpose(res_mat, res_mat)
      assert res_mat == test_mat

   def testMatrixTranspose(self):
      test_mat = gmtl.Matrix33f()
      res_mat  = gmtl.Matrix33f()
      test_mat.set(0.0, 1.0, 2.0,
                   4.0, 5.0, 6.0,
                   8.0, 9.0, 10.0)
      res_mat.set(0.0, 4.0, 8.0,
                  1.0, 5.0, 9.0,
                  2.0, 6.0, 10.0)
      gmtl.transpose(res_mat)
      assert res_mat == test_mat
      gmtl.transpose(res_mat)

      gmtl.transpose(res_mat, res_mat)
      assert res_mat == test_mat

      test_mat = gmtl.Matrix44f()
      res_mat  = gmtl.Matrix44f()
      test_mat.set(0.0, 1.0, 2.0, 3.0,
                   4.0, 5.0, 6.0, 7.0,
                   8.0, 9.0, 10.0, 11.0,
                   12.0, 13.0, 14.0, 15.0)
      res_mat.set(0.0, 4.0, 8.0, 12.0,
                  1.0, 5.0, 9.0, 13.0,
                  2.0, 6.0, 10.0, 14.0,
                  3.0, 7.0, 11.0, 15.0)
      gmtl.transpose(res_mat)
      assert res_mat == test_mat
      gmtl.transpose(res_mat)

      gmtl.transpose(res_mat, res_mat)
      assert res_mat == test_mat

      self.__transposeTest(gmtl.Matrix33f)
      self.__transposeTest(gmtl.Matrix44f)

   def testMatrixAddSub33(self):
      test_mat1 = gmtl.Matrix33f()
      res_mat   = gmtl.Matrix33f()
      ans_mat   = gmtl.Matrix33f()

      test_mat1.set(0.0, 1.0, 2.0,
                    4.0, 5.0, 6.0,
                    8.0, 9.0, 10.0)
      test_mat2 = gmtl.Matrix33f(test_mat1)
      ans_mat.set(0.0, 2.0, 4.0,
                  8.0, 10.0, 12.0,
                  16.0, 18.0, 20.0)
      gmtl.add(res_mat, test_mat1, test_mat2)   # rm = m1 + m2
      assert res_mat == ans_mat

      diff_mat = gmtl.Matrix33f()
      gmtl.sub(diff_mat, res_mat, test_mat1)    # rm = m1 - m2
      assert diff_mat != res_mat
      assert diff_mat == test_mat2

      test_mat1 = gmtl.Matrix44f()
      res_mat   = gmtl.Matrix44f()
      ans_mat   = gmtl.Matrix44f()

      test_mat1.set(0.0, 1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0, 7.0,
                    8.0, 9.0, 10.0, 11.0,
                    12.0, 13.0, 14.0, 15.0)
      test_mat2 = gmtl.Matrix44f(test_mat1)
      ans_mat.set(0.0, 2.0, 4.0, 6.0,
                  8.0, 10.0, 12.0, 14.0,
                  16.0, 18.0, 20.0, 22.0,
                  24.0, 26.0, 28.0, 30.0)
      gmtl.add(res_mat, test_mat1, test_mat2)   # rm = m1 + m2
      assert res_mat == ans_mat

      diff_mat = gmtl.Matrix44f()
      gmtl.sub(diff_mat, res_mat, test_mat1)    # rm = m1 - m2
      assert diff_mat != res_mat
      assert diff_mat == test_mat2

   def testMatrixMult33(self):
      mat1 = gmtl.Matrix33f()
      mat2 = gmtl.Matrix33f()
      eps = 0.001

      mat1.set(1.1000, 2.2000, 3.3000,
               5.5000, 6.6000, 7.7000,
               9.9000, 10.1000, 11.1100)
      mat2.set(43.0, -8.0, -4.0,
               23.0, 22.0, 72.0,
               -34.0, -23.0, 99.0)

      # Make sure mat3 = mat1 * mat2 yields the correct result.
      mat3 = gmtl.Matrix33f()
      gmtl.mult(mat3, mat1, mat2)
      res_mat = gmtl.Matrix33f()
      res_mat.set(-14.300, -36.300, 480.700,
                  126.500, -75.900, 1215.500,
                  280.260, -112.530, 1787.490)
      assert gmtl.isEqual(res_mat, mat3, eps)

      # Test post and pre mult operators.
      m1 = gmtl.Matrix33f(mat1)
      m2 = gmtl.Matrix33f(mat2)
      gmtl.postMult(m1, m2)
      assert gmtl.isEqual(res_mat, m1, eps)

      m1 = gmtl.Matrix33f(mat1)
      m2 = gmtl.Matrix33f(mat2)
      m1 *= m2
      assert gmtl.isEqual(res_mat, m1, eps)

      m1 = gmtl.Matrix33f(mat1)
      m2 = gmtl.Matrix33f(mat2)
      gmtl.preMult(m2, m1)
      assert gmtl.isEqual(res_mat, m2, eps)

      m1 = gmtl.Matrix33f(mat1)
      m2 = gmtl.Matrix33f(mat2)
      result = mat1 * mat2
      assert gmtl.isEqual(res_mat, result, eps)

      # Make sure mult is not commutitive.
      gmtl.mult(mat3, mat2, mat1)
      assert not gmtl.isEqual(res_mat, mat3, eps)

      # Make sure mat3 = mat2 * mat1 yields the correct result.
      res_mat.set(-36.3000,   1.4000,   35.8600,
                  859.1000, 923.0000, 1045.2200,
                  816.2000, 773.3000,  810.5900)
      assert gmtl.isEqual(res_mat, mat3, eps)

      # Test post and pre mult operators.
      m1 = gmtl.Matrix33f(mat1)
      m2 = gmtl.Matrix33f(mat2)
      gmtl.postMult(m2, m1)
      assert gmtl.isEqual(res_mat, m2, eps)

      m1 = gmtl.Matrix33f(mat1)
      m2 = gmtl.Matrix33f(mat2)
      m2 *= m1
      assert gmtl.isEqual(res_mat, m2, eps)

      m1 = gmtl.Matrix33f(mat1)
      m2 = gmtl.Matrix33f(mat2)
      gmtl.preMult(m1, m2)
      assert gmtl.isEqual(res_mat, m1, eps)

      m1 = gmtl.Matrix33f(mat1)
      m2 = gmtl.Matrix33f(mat2)
      result = mat2 * mat1
      assert gmtl.isEqual(res_mat, result, eps)

   def testMatrixMult44(self):
      mat1 = gmtl.Matrix44f()
      mat2 = gmtl.Matrix44f()
      eps = 0.001

      mat1.set( 1.1000,  2.2000,  3.3000,  4.4000,
                5.5000,  6.6000,  7.7000,  8.8000,
                9.9000, 10.1000, 11.1100, 12.1200,
               13.1300, 14.1400, 15.1500, 16.1600)
      mat2.set( 43,  -8, -4,   7,
                23,  22, 72,  69,
               -34, -23, 99, -48,
                12,  16, 21,  18)

      # Make sure mat3 = mat1 * mat2 yields the correct result.
      mat3 = gmtl.Matrix44f()
      gmtl.mult(mat3, mat1, mat2)
      res_mat = gmtl.Matrix44f()
      res_mat.set( 38.500,  34.100,  573.100,  80.300,
                  232.100,  64.900, 1400.300, 282.700,
                  425.700,  81.390, 2042.010, 451.080,
                  568.630, 116.150, 2804.770, 631.250)
      assert gmtl.isEqual(res_mat, mat3, eps)

      # Test post and pre mult operators.
      m1 = gmtl.Matrix44f(mat1)
      m2 = gmtl.Matrix44f(mat2)
      gmtl.postMult(m1, m2)
      assert gmtl.isEqual(res_mat, m1, eps)

      m1 = gmtl.Matrix44f(mat1)
      m2 = gmtl.Matrix44f(mat2)
      m1 *= m2
      assert gmtl.isEqual(res_mat, m1, eps)

      m1 = gmtl.Matrix44f(mat1)
      m2 = gmtl.Matrix44f(mat2)
      gmtl.preMult(m2, m1)
      assert gmtl.isEqual(res_mat, m2, eps)

      m1 = gmtl.Matrix44f(mat1)
      m2 = gmtl.Matrix44f(mat2)
      result = mat1 * mat2
      assert gmtl.isEqual(res_mat, result, eps)

      # Make sure mult is not commutitive.
      gmtl.mult(mat3, mat2, mat1)
      assert not gmtl.isEqual(res_mat, mat3, eps)

      # Make sure mat3 = mat2 * mat1 yields the correct result.
      res_mat.set(  55.610,  100.380,  141.910,  183.440,
                  1765.070, 1898.660, 2090.570, 2282.480,
                   185.960,   94.580,   83.390,   72.200,
                   545.440,  598.620,  668.810,  739.000)
      assert gmtl.isEqual(res_mat, mat3, eps)

      # Test post and pre mult operators.
      m1 = gmtl.Matrix44f(mat1)
      m2 = gmtl.Matrix44f(mat2)
      gmtl.postMult(m2, m1)
      assert gmtl.isEqual(res_mat, m2, eps)

      m1 = gmtl.Matrix44f(mat1)
      m2 = gmtl.Matrix44f(mat2)
      m2 *= m1
      assert gmtl.isEqual(res_mat, m2, eps)

      m1 = gmtl.Matrix44f(mat1)
      m2 = gmtl.Matrix44f(mat2)
      gmtl.preMult(m1, m2)
      assert gmtl.isEqual(res_mat, m1, eps)

      m1 = gmtl.Matrix44f(mat1)
      m2 = gmtl.Matrix44f(mat2)
      result = mat2 * mat1
      assert gmtl.isEqual(res_mat, result, eps)

   def testMatrixScalarMult44(self):
      mat1            = gmtl.Matrix44f()
      expected_result = gmtl.Matrix44f()

      eps = 0.001

      mat1.set( 1.1000,  2.2000,  3.3000,  4.4000,
                5.5000,  6.6000,  7.7000,  8.8000,
                9.9000, 10.1000, 11.1100, 12.1200,
               13.1300, 14.1400, 15.1500, 16.1600)
      expected_result.set( 3.3000,  6.6000,  9.9000, 13.2000,
                          16.5000, 19.8000, 23.1000, 26.4000,
                          29.7000, 30.3000, 33.3300, 36.3600,
                          39.3900, 42.4200, 45.4500, 48.4800)

      res_mat = gmtl.Matrix44f()

      # result = mat * scalar
      gmtl.mult(res_mat, mat1, 3)
      assert gmtl.isEqual(expected_result, res_mat, eps)

      # result *= scalar
      res_mat = gmtl.Matrix44f(mat1)
      gmtl.mult(res_mat, 3)
      assert gmtl.isEqual(expected_result, res_mat, eps)

      # result *= scalar
      res_mat = gmtl.Matrix44f(mat1)
      res_mat *= 3
      assert gmtl.isEqual(expected_result, res_mat, eps)

   def testMatInvertKnownFull44(self):
      mat1           = gmtl.Matrix44f()
      expected_value = gmtl.Matrix44f()

      mat1.set(0.78,  1.4,   2.9, 3.45,
               4.21, 57.9,  65.9, 74.6,
               89.2, 99.2,  10.9, 11.9,
               12.5, 13.9, 14.78, 15.6)
      expected_value.set( 0.3071733, -0.0239700,  0.0034853,  0.0440345,
                         -0.2891106,  0.0216826,  0.0079218, -0.0457924,
                         -3.0532152,  0.0305681, -0.0547335,  0.5708037,
                          2.9041982, -0.0290744,  0.0420053, -0.4711792)

      eps = 0.001

      result = gmtl.Matrix44f()
      identity = gmtl.Matrix44f()

      # Make sure our pre-computed answer is right.
      gmtl.mult(result, mat1, expected_value)
      assert gmtl.isEqual(result, identity, eps)

      # Test inversion.
      result = gmtl.Matrix44f()
      gmtl.invert(result, mat1)
      assert gmtl.isEqual(result, expected_value, eps)

      # Test inversion in place.
      gmtl.invert(mat1)
      assert gmtl.isEqual(mat1, expected_value, eps)

   def __testMatInvertFull(self, matType):
      iters = 100
      eps = 0.001

      mat     = matType()
      inv_mat = matType()
      expected_mat = matType()

      for iter in xrange(iters):
         for r in range(mat.Params.Rows):
            for c in range(mat.Params.Cols):
               mat[r][c] = float(random.randrange(1, 10)) / 10.0

         mat.state = matType.XformState.FULL

         gmtl.invert(inv_mat, mat)
         mult_mat = mat * inv_mat
         # This fails sometimes, but I don't know why.
         assert gmtl.isEqual(mult_mat, expected_mat, eps)

         inv_mat = matType(mat)
         gmtl.invert(inv_mat)
         assert gmtl.isEqual(mult_mat, expected_mat, eps)

   def testMatInvert(self):
      eps = 0.001

      # Test translation creation and inversion.
      trans_range = 100
      trans_inc = 10

      for x in range(-trans_range, trans_range, trans_inc):
         for y in range(-trans_range, trans_range, trans_inc):
            for z in range(-trans_range, trans_range, trans_inc):
               expected_inv = gmtl.Matrix44f()
               expected_inv.set(1.0, 0.0, 0.0, -x,
                                0.0, 1.0, 0.0, -y,
                                0.0, 0.0, 1.0, -z,
                                0.0, 0.0, 0.0, 1.0)
               src_mat = gmtl.Matrix44f()
               gmtl.setTrans(src_mat, gmtl.Vec3f(x, y, z))
               inv_mat = gmtl.Matrix44f()
               gmtl.invertFull_GJ(inv_mat, src_mat)
               assert gmtl.isEqual(inv_mat, expected_inv, eps)
               gmtl.identity(inv_mat)
               gmtl.invert(inv_mat, src_mat)
               assert gmtl.isEqual(inv_mat, expected_inv, eps)

      self.__testMatInvertFull(gmtl.Matrix33f)
      self.__testMatInvertFull(gmtl.Matrix44f)

class MatrixOpsMetricTest(unittest.TestCase):
   def testMatrixTimeIdentity44f(self):
      test_mat = gmtl.Matrix44f()
      bogus_value = 0.0
      iters = 50000

      for iter in xrange(iters):
         test_mat.set(0.0, iter + 1, iter +2, iter + 3,
                      0.0, 1.0, 2.0, 3.0,
                      0.0, 1.0, 2.0, 3.0,
                      0.0, 1.0, 2.0, 3.0)
         gmtl.identity(test_mat)
         bogus_value += test_mat(1, 1)  # Should add noe every time

      assert isEqual(bogus_value, iters, 0.5)

   def testTimingMakeTrans(self):
      mat33 = gmtl.Matrix33f()
      mat44 = gmtl.Matrix44f()

      a = 1.0
      iters = 100000

      for iter in xrange(iters):
         gmtl.setTrans(mat33, gmtl.Vec2f(a, 2.0))
         a += mat33.data[3]

      assert mat33.data[3] != 1234.0456 and a != 987654.311

      for iter in xrange(iters):
         gmtl.setTrans(mat33, gmtl.Vec3f(1.0, a, 1.0))  # homogeneous
         a += mat33.data[3]

      assert mat33.data[3] != 1234.0456 and a != 987654.311

      for iter in xrange(iters):
         gmtl.setTrans(mat44, gmtl.Vec3f(30.0, a, 121.0))
         a += mat44.data[3]

      assert mat44.data[3] != 1234.0456 and a != 987654.311

      for iter in xrange(iters):
         gmtl.setTrans(mat44, gmtl.Vec4f(30.0, 32.0, a, 1.0))   # homogeneous
         a += mat44.data[3]

      assert mat44.data[3] != 1234.0456 and a != 987654.311

   def testMatrixTimeTranspose44f(self):
      test_mat1 = gmtl.Matrix44f()
      test_mat1.set(0.0, 1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0, 7.0,
                    8.0, 9.0, 10.0, 11.0,
                    12.0, 13.0, 14.0, 15.0)

      iters = 50000
      for iter in xrange(iters):
         gmtl.transpose(test_mat1)
         test_mat1[0][2] += test_mat1.data[3]
         test_mat1[0][4] += test_mat1.data[1]

      assert test_mat1.data[2] != test_mat1.data[0]

   def testMatrixTimeMult44_mult(self):
      test_mat1 = gmtl.Matrix44f()
      test_mat1.set(0.0, 1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0, 7.0,
                    8.0, 9.0, 10.0, 11.0,
                    12.0, 13.0, 14.0, 15.0)

      test_mat2 = gmtl.Matrix44f(test_mat1)
      res_mat   = gmtl.Matrix44f(test_mat2)

      iters = 50000
      for iter in xrange(iters):
         gmtl.mult(res_mat, res_mat, test_mat1)

      assert test_mat1.data[2] != test_mat2.data[0]

   def testMatrixTimeMult44_operatorStar(self):
      test_mat1 = gmtl.Matrix44f()
      test_mat1.set(0.0, 1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0, 7.0,
                    8.0, 9.0, 10.0, 11.0,
                    12.0, 13.0, 14.0, 15.0)

      test_mat2 = gmtl.Matrix44f(test_mat1)
      res_mat   = gmtl.Matrix44f(test_mat2)

      iters = 50000

      for iter in xrange(iters):
         res_mat = test_mat1 * res_mat

      assert test_mat1.data[2] != test_mat2.data[0]

   def testMatrixTimeMult44_operatorStarStar(self):
      test_mat1 = gmtl.Matrix44f()
      test_mat1.set(0.0, 1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0, 7.0,
                    8.0, 9.0, 10.0, 11.0,
                    12.0, 13.0, 14.0, 15.0)

      test_mat2 = gmtl.Matrix44f(test_mat1)
      res_mat   = gmtl.Matrix44f(test_mat2)

      iters = 50000

      for iter in xrange(iters):
         res_mat = test_mat1 * res_mat * test_mat2

      assert test_mat1.data[2] != test_mat2.data[0]

   def testMatrixTimeMult33_operatorStarStar(self):
      test_mat1 = gmtl.Matrix33f()
      test_mat1.set(0.0, 1.0, 2.0,
                    3.0, 4.0, 5.0,
                    6.0, 7.0, 8.0)

      test_mat2 = gmtl.Matrix33f(test_mat1)
      res_mat   = gmtl.Matrix33f(test_mat2)

      iters = 50000

      for iter in xrange(iters):
         res_mat = test_mat1 * res_mat

      assert test_mat1.data[2] != test_mat2.data[0]

   def testMatrixTimeAdd44(self):
      test_mat1 = gmtl.Matrix44f()
      test_mat1.set(0.0, 1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0, 7.0,
                    8.0, 9.0, 10.0, 11.0,
                    12.0, 13.0, 14.0, 15.0)

      test_mat2 = gmtl.Matrix44f(test_mat1)
      res_mat   = gmtl.Matrix44f(test_mat2)

      iters = 50000

      for iter in xrange(iters):
         gmtl.add(res_mat, res_mat, test_mat2)

      assert test_mat1.data[2] != test_mat2.data[0]
      assert res_mat.data[2] != 1000.0

   def testMatrixTimeAdd44(self):
      test_mat1 = gmtl.Matrix44f()
      test_mat1.set(0.0, 1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0, 7.0,
                    8.0, 9.0, 10.0, 11.0,
                    12.0, 13.0, 14.0, 15.0)

      test_mat2 = gmtl.Matrix44f(test_mat1)
      res_mat   = gmtl.Matrix44f(test_mat2)

      iters = 50000

      for iter in xrange(iters):
         gmtl.sub(res_mat, res_mat, test_mat2)

      assert test_mat1.data[2] != test_mat2.data[0]
      assert res_mat.data[2] != 1000.0

class MatrixStateTrackingTest(unittest.TestCase):
   def testMatrixStateTracking(self):
      test_states = [
         gmtl.Matrix44f.XformState.IDENTITY,
         gmtl.Matrix44f.XformState.TRANS,
         gmtl.Matrix44f.XformState.ORTHOGONAL,
         gmtl.Matrix44f.XformState.AFFINE,
         gmtl.Matrix44f.XformState.NON_UNISCALE,
         gmtl.Matrix44f.XformState.AFFINE | gmtl.Matrix44f.XformState.NON_UNISCALE,
         gmtl.Matrix44f.XformState.FULL,
         gmtl.Matrix44f.XformState.XFORM_ERROR,
      ]

      # Test combine utility function.
      expected = [
            gmtl.Matrix44f.XformState.IDENTITY, # ident
            gmtl.Matrix44f.XformState.TRANS,
            gmtl.Matrix44f.XformState.ORTHOGONAL,
            gmtl.Matrix44f.XformState.AFFINE,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.AFFINE | gmtl.Matrix44f.XformState.NON_UNISCALE,
            gmtl.Matrix44f.XformState.FULL,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.TRANS,    # trans
            gmtl.Matrix44f.XformState.TRANS,
            gmtl.Matrix44f.XformState.AFFINE,
            gmtl.Matrix44f.XformState.AFFINE,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.AFFINE | gmtl.Matrix44f.XformState.NON_UNISCALE,
            gmtl.Matrix44f.XformState.FULL,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.ORTHOGONAL,    # ORTHOGONAL
            gmtl.Matrix44f.XformState.AFFINE,
            gmtl.Matrix44f.XformState.ORTHOGONAL,
            gmtl.Matrix44f.XformState.AFFINE,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.AFFINE | gmtl.Matrix44f.XformState.NON_UNISCALE,
            gmtl.Matrix44f.XformState.FULL,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.AFFINE,    # AFFINE
            gmtl.Matrix44f.XformState.AFFINE,
            gmtl.Matrix44f.XformState.AFFINE,
            gmtl.Matrix44f.XformState.AFFINE,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.AFFINE | gmtl.Matrix44f.XformState.NON_UNISCALE,
            gmtl.Matrix44f.XformState.FULL,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.XFORM_ERROR,    # NON_UNISCALE
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.AFFINE | gmtl.Matrix44f.XformState.NON_UNISCALE,    # AFFINE | NON_UNISCALE
            gmtl.Matrix44f.XformState.AFFINE | gmtl.Matrix44f.XformState.NON_UNISCALE,
            gmtl.Matrix44f.XformState.AFFINE | gmtl.Matrix44f.XformState.NON_UNISCALE,
            gmtl.Matrix44f.XformState.AFFINE | gmtl.Matrix44f.XformState.NON_UNISCALE,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.AFFINE | gmtl.Matrix44f.XformState.NON_UNISCALE,
            gmtl.Matrix44f.XformState.FULL,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.FULL,    # FULL
            gmtl.Matrix44f.XformState.FULL,
            gmtl.Matrix44f.XformState.FULL,
            gmtl.Matrix44f.XformState.FULL,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.FULL,
            gmtl.Matrix44f.XformState.FULL,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.XFORM_ERROR,    # XFORM_ERROR
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.XFORM_ERROR,
            gmtl.Matrix44f.XformState.XFORM_ERROR
      ]

      total = 0
      for x in range(len(test_states)):
         for y in range(len(test_states)):
            assert gmtl.combineMatrixStates(test_states[x], test_states[y]) == expected[total]
            total += 1

      # Test core matrix class.

      # Test default constructor.
      mat = gmtl.Matrix44f()
      assert mat.state == gmtl.Matrix44f.XformState.IDENTITY

      # Test copy constructor.
      mat1 = gmtl.Matrix44f()
      mat1.state = gmtl.Matrix44f.XformState.FULL
      mat2 = gmtl.Matrix44f(mat1)
      assert mat2.state == gmtl.Matrix44f.XformState.FULL

      # Test set.
      mat = gmtl.Matrix44f()
      mat.set(range(16))
      assert mat.state == gmtl.Matrix44f.XformState.FULL

      # Test gmtl.setTranspose()
      mat = gmtl.Matrix44f()
      gmtl.identity(mat)
      assert mat.state == gmtl.Matrix44f.XformState.IDENTITY

      # Make sure gmtl.identity() sets the flag when matrix wasn't originally
      # identity.
      mat.state = gmtl.Matrix44f.XformState.FULL
      gmtl.identity(mat)
      assert mat.state == gmtl.Matrix44f.XformState.IDENTITY

      # Test gmtl.zero().
      mat = gmtl.Matrix44f()
      gmtl.zero(mat)

      # Test composing two matrices.
      for x in range(len(test_states)):
         for y in range(len(test_states)):
            mat1 = gmtl.Matrix44f()
            mat2 = gmtl.Matrix44f()
            mat1.state = test_states[x]
            mat2.state = test_states[y]

            # Multiply two matrices using __mult__
            result = mat1 * mat2
            assert result.state == gmtl.combineMatrixStates(test_states[x],
                                                            test_states[y])
            result = mat2 * mat1
            assert result.state == gmtl.combineMatrixStates(test_states[x],
                                                            test_states[y])

            # Multiply two matrices using gmtl.mult()
            gmtl.mult(result, mat1, mat2)
            assert result.state == gmtl.combineMatrixStates(test_states[x],
                                                            test_states[y])
            gmtl.mult(result, mat2, mat1)
            assert result.state == gmtl.combineMatrixStates(test_states[x],
                                                            test_states[y])

            # Multiply two matrices using gmtl.preMult()
            result.state = test_states[y]
            gmtl.preMult(result, mat1)
            assert result.state == gmtl.combineMatrixStates(test_states[x],
                                                            test_states[y])
            gmtl.preMult(result, mat1)
            assert result.state == gmtl.combineMatrixStates(test_states[x],
                                                            test_states[y])

            # Multiply two matrices using gmtl.postMult()
            result.state = test_states[y]
            gmtl.postMult(result, mat1)
            assert result.state == gmtl.combineMatrixStates(test_states[x],
                                                            test_states[y])
            gmtl.postMult(result, mat1)
            assert result.state == gmtl.combineMatrixStates(test_states[x],
                                                            test_states[y])

            # add(res, mat, mat), sub(res, mat, mat)
            gmtl.add(result, mat1, mat2)
            assert result.state == gmtl.combineMatrixStates(test_states[x],
                                                            test_states[y])
            gmtl.add(result, mat2, mat1)
            assert result.state == gmtl.combineMatrixStates(test_states[x],
                                                            test_states[y])

            gmtl.sub(result, mat1, mat2)
            assert result.state == gmtl.combineMatrixStates(test_states[x],
                                                            test_states[y])
            gmtl.sub(result, mat2, mat1)
            assert result.state == gmtl.combineMatrixStates(test_states[x],
                                                            test_states[y])

            # mutl(res, mat, scalar)
            gmtl.mult(result, mat1, 45.0)
            assert result.state == mat1.state

            # mutl(res, scalar)
            result.state = test_states[x]
            gmtl.mult(result, 45.0)
            assert result.state == test_states[x]

            # operator*=(mat, mat)
            mat1.state   = test_states[x]
            result.state = test_states[y]
            result *= mat1
            assert result.state == gmtl.combineMatrixStates(test_states[x],
                                                            test_states[y])
            mat1.state   = test_states[x]
            result.state = test_states[y]
            mat1 *= result

      # test copying, equality, inequality, isEqual()
      mat1   = gmtl.Matrix44f()
      result = gmtl.Matrix44f()
      mat1.state = gmtl.Matrix44f.XformState.ORTHOGONAL

      result.state = gmtl.Matrix44f.XformState.FULL
      result = gmtl.Matrix44f(mat1)
      assert result.state == gmtl.Matrix44f.XformState.ORTHOGONAL

      # Make sure they are still equal (== and != should not observe the state)
      result.state = gmtl.Matrix44f.XformState.FULL
      assert not result != mat1

      result.state = gmtl.Matrix44f.XformState.ORTHOGONAL
      assert result == mat1

      result.state = gmtl.Matrix44f.XformState.FULL
      assert gmtl.isEqual(result, mat1, 0.0001)

      # Generators.

      # Test gmtl.setScale()
      mat = gmtl.Matrix44f()
      gmtl.setScale(mat, 2345.0)
      assert mat.state == gmtl.Matrix44f.XformState.AFFINE | gmtl.Matrix44f.XformState.NON_UNISCALE

      mat2 = gmtl.makeScaleMatrix44(2345.0)
      assert mat2.state == gmtl.Matrix44f.XformState.AFFINE | gmtl.Matrix44f.XformState.NON_UNISCALE

      mat = gmtl.Matrix44f()
      mat2 = gmtl.Matrix44f()
      gmtl.setScale(mat, gmtl.Vec3f(983.0, 234.0, 1.0))
      assert mat.state == gmtl.Matrix44f.XformState.AFFINE | gmtl.Matrix44f.XformState.NON_UNISCALE

      mat2 = gmtl.makeScaleMatrix44(gmtl.Vec3f(983.0, 234.0, 1.0))
      assert mat2.state == gmtl.Matrix44f.XformState.AFFINE | gmtl.Matrix44f.XformState.NON_UNISCALE

      # Test gmtl.setTrans()
      mat = gmtl.Matrix44f()

      # Set
      gmtl.setTrans(mat, gmtl.Vec3f(983.0, 234.0, 1.0))
      assert mat.state == gmtl.Matrix44f.XformState.TRANS

      mat.state = gmtl.Matrix44f.XformState.FULL
      gmtl.setTrans(mat, gmtl.Vec3f(983.0, 234.0, 1.0))
      assert mat.state == gmtl.Matrix44f.XformState.FULL

      mat.state = gmtl.Matrix44f.XformState.ORTHOGONAL
      gmtl.setTrans(mat, gmtl.Vec3f(983.0, 234.0, 1.0))
      assert mat.state == gmtl.Matrix44f.XformState.AFFINE

      mat.state = gmtl.Matrix44f.XformState.AFFINE
      gmtl.setTrans(mat, gmtl.Vec3f(983.0, 234.0, 1.0))
      assert mat.state == gmtl.Matrix44f.XformState.AFFINE

      # make
      mat2 = gmtl.makeTransMatrix44(gmtl.Vec3f(983.0, 234.0, 1.0))
      assert mat2.state == gmtl.Matrix44f.XformState.TRANS

      # Test setRot(gmtl.AxisAngle)
      self.__testStateTracking_setRot(gmtl.AxisAnglef(90.0,
                                                      gmtl.Vec3f(0.0, 1.0, 0.0)))

      # Test setRot(gmtl.EulerAngle)
      self.__testStateTracking_setRot(gmtl.EulerAngleXYZf())

      # Test gmtl.setFrustum()
      mat = gmtl.Matrix44f()
      gmtl.setFrustum(mat, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0)
      assert mat.state == gmtl.Matrix44f.XformState.FULL

      mat.state = gmtl.Matrix44f.XformState.ORTHOGONAL
      gmtl.setFrustum(mat, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0)
      assert mat.state == gmtl.Matrix44f.XformState.FULL

      # Test gmtl.setPerspective()
      mat = gmtl.Matrix44f()
      gmtl.setPerspective(mat, 60.0, 1.33, 0.0004, 100.0)
      assert mat.state == gmtl.Matrix44f.XformState.FULL

      mat.state = gmtl.Matrix44f.XformState.ORTHOGONAL
      gmtl.setPerspective(mat, 60.0, 1.33, 0.0004, 100.0)
      assert mat.state == gmtl.Matrix44f.XformState.FULL

      # Test set(gmtl.Coord3fXYZ)
      self.__testStateTracking_set(gmtl.Coord3fXYZ(),
                                   gmtl.Matrix44f.XformState.AFFINE)

      # Test set(gmtl.Coord3fQuat)
      self.__testStateTracking_set(gmtl.Coord3fQuat(),
                                   gmtl.Matrix44f.XformState.AFFINE)

      # Test set(gmtl.Coord3fAxisAngle)
      self.__testStateTracking_set(gmtl.Coord3fAxisAngle(),
                                   gmtl.Matrix44f.XformState.AFFINE)

      # Test set(gmtl.Quatf)
      self.__testStateTracking_set(gmtl.Quatf(),
                                   gmtl.Matrix44f.XformState.ORTHOGONAL)

      # Test set(gmtl.AxisAnglef)
      self.__testStateTracking_set(gmtl.AxisAnglef(),
                                   gmtl.Matrix44f.XformState.ORTHOGONAL)

      # Test gmtl.invert()
      for x in range(len(test_states)):
         # gmtl.invertFull(result, mat)
         self.__testStateTracking_invert(test_states[x], gmtl.invertFull)

         # gmtl.invertTrans(result, mat)
         self.__testStateTracking_invert(test_states[x], gmtl.invertTrans)

         # gmtl.invertOrthogonal(result, mat)
         self.__testStateTracking_invert(test_states[x], gmtl.invertOrthogonal)

         # gmtl.invertAffine(result, mat)
         self.__testStateTracking_invert(test_states[x], gmtl.invertAffine)

      mat = gmtl.Matrix44f()
      eps = 0.0001

      # gmtl.Matrix44f.XformState.IDENTITY
      mat.set( 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 )
      mat.state   = gmtl.Matrix44f.XformState.IDENTITY
      iv          = gmtl.Matrix44f(mat)
      iv_full     = gmtl.Matrix44f(mat)
      iv_nochange = gmtl.Matrix44f(mat)
      gmtl.invert(iv)
      gmtl.invertFull(iv_full, iv_full)
      assert gmtl.isEqual(iv, iv_nochange, eps) and gmtl.isEqual(iv, iv_full, eps)

      # gmtl.Matrix44f.XformState.TRANS
      mat.set(1, 0, 0, 4,
              0, 1, 0, 5,
              0, 0, 1, 6,
              0, 0, 0, 1)
      mat.state   = gmtl.Matrix44f.XformState.TRANS
      iv          = gmtl.Matrix44f(mat)
      iv_full     = gmtl.Matrix44f(mat)
      iv_trans    = gmtl.Matrix44f(mat)
      gmtl.invert(iv)
      gmtl.invertFull(iv_full, iv_full)
      gmtl.invertTrans(iv_trans, iv_trans)
      assert gmtl.isEqual(iv, iv_trans, eps) and gmtl.isEqual(iv, iv_full, eps)

      # gmtl.Matrix44f.XformState.ORTHOGONAL
      mat.set(0, 0, -1, 0,
              1, 0, 0, 0,
              0, -1, 0, 0,
              0, 0, 0, 1)
      mat.state   = gmtl.Matrix44f.XformState.ORTHOGONAL
      iv          = gmtl.Matrix44f(mat)
      iv_full     = gmtl.Matrix44f(mat)
      iv_ortho    = gmtl.Matrix44f(mat)
      gmtl.invert(iv)
      gmtl.invertFull(iv_full, iv_full)
      gmtl.invertOrthogonal(iv_ortho, iv_ortho)
      assert gmtl.isEqual(iv, iv_ortho, eps) and gmtl.isEqual(iv, iv_full, eps)

      # gmtl.Matrix44f.XformState.AFFINE
      mat.set(0, 0, -1, 10,
              1, 0, 0, 11,
              0, -1, 0, 12,
              0, 0, 0, 20057)
      mat.state   = gmtl.Matrix44f.XformState.AFFINE
      iv          = gmtl.Matrix44f(mat)
      iv_full     = gmtl.Matrix44f(mat)
      iv_affine   = gmtl.Matrix44f(mat)
      gmtl.invert(iv)
      gmtl.invertFull(iv_full, iv_full)
      gmtl.invertAffine(iv_affine, iv_affine)
      assert gmtl.isEqual(iv, iv_affine, eps) and gmtl.isEqual(iv, iv_full, eps)

      # gmtl.Matrix44f.XformState.AFFINE | gmtl.Matrix44f.XformState.NON_UNISCALE
      mat.set(0, 2, 0, 10,
              0, 0, -8, 11,
              -3, 0, 0, 12,
              0, 0, 0, 1)
      mat.state   = gmtl.Matrix44f.XformState.AFFINE | gmtl.Matrix44f.XformState.NON_UNISCALE
      iv          = gmtl.Matrix44f(mat)
      iv_full     = gmtl.Matrix44f(mat)
      iv_affine   = gmtl.Matrix44f(mat)
      gmtl.invert(iv)
      gmtl.invertFull(iv_full, iv_full)
      gmtl.invertAffine(iv_affine, iv_affine)
      assert gmtl.isEqual(iv, iv_affine, eps) and gmtl.isEqual(iv, iv_full, eps)

      mat.set(0, 2, 0, 10,
              0, 0, -8, 11,
              -3, 0, 0, 12,
              0, 0, 0, 23489)
      mat.state   = gmtl.Matrix44f.XformState.AFFINE | gmtl.Matrix44f.XformState.NON_UNISCALE
      iv          = gmtl.Matrix44f(mat)
      iv_full     = gmtl.Matrix44f(mat)
      iv_affine   = gmtl.Matrix44f(mat)
      gmtl.invert(iv)
      gmtl.invertFull(iv_full, iv_full)
      gmtl.invertAffine(iv_affine, iv_affine)
      assert gmtl.isEqual(iv, iv_affine, eps) and gmtl.isEqual(iv, iv_full, eps)

      # gmtl.Matrix44f.XformState.FULL
      mat.set(range(1, 17))
      mat.state   = gmtl.Matrix44f.XformState.FULL
      iv          = gmtl.Matrix44f(mat)
      iv_full     = gmtl.Matrix44f(mat)
      gmtl.invert(iv)
      gmtl.invertFull(iv_full, iv_full)
      assert gmtl.isEqual(iv, iv_full, eps)

   def __testStateTracking_setRot(self, rot):
      mat = gmtl.Matrix44f()

      # Set
      gmtl.setRot(mat, rot)
      assert mat.state == gmtl.Matrix44f.XformState.ORTHOGONAL

      mat.state = gmtl.Matrix44f.XformState.ORTHOGONAL
      gmtl.setRot(mat, rot)
      assert mat.state == gmtl.Matrix44f.XformState.ORTHOGONAL

      mat.state = gmtl.Matrix44f.XformState.TRANS
      gmtl.setRot(mat, rot)
      assert mat.state == gmtl.Matrix44f.XformState.AFFINE

      mat.state = gmtl.Matrix44f.XformState.AFFINE
      gmtl.setRot(mat, rot)
      assert mat.state == gmtl.Matrix44f.XformState.AFFINE

      mat.state = gmtl.Matrix44f.XformState.FULL
      gmtl.setRot(mat, rot)
      assert mat.state == gmtl.Matrix44f.XformState.FULL

      # make
      mat2 = gmtl.makeRotMatrix44(rot)
      assert mat2.state == gmtl.Matrix44f.XformState.ORTHOGONAL

   def __testStateTracking_set(self, xform, state):
      mat = gmtl.Matrix44f()

      # set
      gmtl.set(mat, xform)
      assert mat.state == state

      mat.state = gmtl.Matrix44f.XformState.ORTHOGONAL
      gmtl.set(mat, xform)
      assert mat.state == state

      mat.state = gmtl.Matrix44f.XformState.TRANS
      gmtl.set(mat, xform)
      assert mat.state == state

      mat.state = gmtl.Matrix44f.XformState.AFFINE
      gmtl.set(mat, xform)
      assert mat.state == state

      mat.state = gmtl.Matrix44f.XformState.FULL
      gmtl.set(mat, xform)
      assert mat.state == state

      # make
#      mat2 = gmtl.makeMatrix44(xform)
#      assert mat2.state == state

   def __testStateTracking_invert(self, state, inverter):
      mat = gmtl.Matrix44f()
      result = gmtl.Matrix44f()
      mat.state = state
      inverter(result, mat)
      assert result.state == mat.state

def isEqual(v0, v1, tolerance = 0.001):
   return math.fabs(v0 - v1) <= tolerance

def getTimingTests(testCase):
   return [m for m in testCase.__dict__.keys() if m.find('Timing') != -1]

def getTests(testCase):
#   timing_tests = getTimingTests(testCase)
   all_tests = [m for m in testCase.__dict__.keys() if m.startswith('test')]
#   for t in timing_tests:
#      all_tests.remove(t)

   return all_tests

random.seed()

suite = unittest.TestSuite()
#suite.addTests(map(AABoxContainTest, getTests(AABoxContainTest)))
#suite.addTests(map(AABoxOpsTest, getTests(AABoxOpsTest)))
#suite.addTests(map(AABoxTest, getTests(AABoxTest)))
#suite.addTests(map(AxisAngleClassTest, getTests(AxisAngleClassTest)))
#suite.addTests(map(AxisAngleCompareTest, getTests(AxisAngleCompareTest)))
#suite.addTests(map(ConvertTest, getTests(ConvertTest)))
#suite.addTests(map(CoordClassTest, getTests(CoordClassTest)))
#suite.addTests(map(CoordCompareTest, getTests(CoordCompareTest)))
#suite.addTests(map(CoordGenTest, getTests(CoordGenTest)))
#suite.addTests(map(EulerAngleClassTest, getTests(EulerAngleClassTest)))
#suite.addTests(map(EulerAngleCompareTest, getTests(EulerAngleCompareTest)))
#suite.addTests(map(IntersectionTest, getTests(IntersectionTest)))
#suite.addTests(map(IntersectionMetricTest, getTests(IntersectionMetricTest)))
#suite.addTests(map(LineSegTest, getTests(LineSegTest)))
#suite.addTests(map(LineSegMetricTest, getTests(LineSegMetricTest)))
#suite.addTests(map(MathTest, getTests(MathTest)))
#suite.addTests(map(MatrixClassTest, getTests(MatrixClassTest)))
#suite.addTests(map(MatrixClassMetricTest, getTests(MatrixClassMetricTest)))
#suite.addTests(map(MatrixCompareTest, getTests(MatrixCompareTest)))
#suite.addTests(map(MatrixCompareMetricTest, getTests(MatrixCompareMetricTest)))
#suite.addTests(map(MatrixGenTest, getTests(MatrixGenTest)))
#suite.addTests(map(MatrixGenMetricTest, getTests(MatrixGenMetricTest)))
#suite.addTests(map(MatrixOpsTest, getTests(MatrixOpsTest)))
#suite.addTests(map(MatrixOpsMetricTest, getTests(MatrixOpsMetricTest)))
suite.addTests(map(MatrixStateTrackingTest, getTests(MatrixStateTrackingTest)))

runner = unittest.TextTestRunner()
runner.run(suite)
