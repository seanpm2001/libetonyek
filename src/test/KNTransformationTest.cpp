/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libkeynote project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <boost/math/constants/constants.hpp>

#include "KNTransformation.h"
#include "KNTypes.h"

#include "KNTransformationTest.h"

namespace test
{

namespace m = boost::math::double_constants;

using libkeynote::KNTransformation;

namespace
{

KNTransformation wrap(const double width, const double height, const KNTransformation &tr)
{
  using namespace libkeynote::transformations;
  return decenter(width, height) * tr * center(width, height);
}

}

void KNTransformationTest::setUp()
{
}

void KNTransformationTest::tearDown()
{
}

void KNTransformationTest::testApplication()
{
  using namespace libkeynote::transformations;

  // identity - point
  {
    double x = 20;
    double y = 40;
    KNTransformation tr;
    tr(x, y);
    CPPUNIT_ASSERT_EQUAL(20.0, x);
    CPPUNIT_ASSERT_EQUAL(40.0, y);
  }

  // identity - distance
  {
    double x = 20;
    double y = 40;
    KNTransformation tr;
    tr(x, y, true);
    CPPUNIT_ASSERT_EQUAL(20.0, x);
    CPPUNIT_ASSERT_EQUAL(40.0, y);
  }

  // translation - point
  {
    double x = 20;
    double y = 40;
    KNTransformation tr = translate(10, 20);
    tr(x, y);
    CPPUNIT_ASSERT_EQUAL(30.0, x);
    CPPUNIT_ASSERT_EQUAL(60.0, y);
  }

  // translation - distance
  {
    double x = 20;
    double y = 40;
    KNTransformation tr = translate(10, 20);
    tr(x, y, true);
    CPPUNIT_ASSERT_EQUAL(20.0, x);
    CPPUNIT_ASSERT_EQUAL(40.0, y);
  }

  // non-translating transformation - point
  {
    double x = 20;
    double y = 40;
    KNTransformation tr = flip(true, false) * scale(0.25, 0.5);
    tr(x, y);
    CPPUNIT_ASSERT_EQUAL(-5.0, x);
    CPPUNIT_ASSERT_EQUAL(20.0, y);
  }

  // non-translating transformation - distance
  {
    double x = 20;
    double y = 40;
    KNTransformation tr = flip(true, false) * scale(0.25, 0.5);
    tr(x, y, true);
    CPPUNIT_ASSERT_EQUAL(-5.0, x);
    CPPUNIT_ASSERT_EQUAL(20.0, y);
  }
}

void KNTransformationTest::testConstruction()
{
  // identity
  CPPUNIT_ASSERT(KNTransformation() == KNTransformation(1, 0, 0, 1, 0, 0));

  using namespace libkeynote::transformations;

  // centering
  CPPUNIT_ASSERT(center(200, 100) == KNTransformation(1, 0, 0, 1, 100, 50));
  CPPUNIT_ASSERT(decenter(200, 100) == KNTransformation(1, 0, 0, 1, -100, -50));

  // flipping
  CPPUNIT_ASSERT(flip(true, false) == KNTransformation(-1, 0, 0, 1, 0, 0));
  CPPUNIT_ASSERT(flip(false, true) == KNTransformation(1, 0, 0, -1, 0, 0));
  CPPUNIT_ASSERT(flip(true, true) == KNTransformation(-1, 0, 0, -1, 0, 0));

  // rotating
  CPPUNIT_ASSERT(rotate(m::half_pi) == KNTransformation(0, 1, -1, 0, 0, 0));

  // scaling
  CPPUNIT_ASSERT(scale(2, 1) == KNTransformation(2, 0, 0, 1, 0, 0));
  CPPUNIT_ASSERT(scale(1, 2) == KNTransformation(1, 0, 0, 2, 0, 0));
  CPPUNIT_ASSERT(scale(3, 2) == KNTransformation(3, 0, 0, 2, 0, 0));

  // shearing
  // FIXME: find the problem and enable
  // CPPUNIT_ASSERT(shear(m::pi / 4, 0) == KNTransformation(1, 2, 0, 1, 0, 0));
  // CPPUNIT_ASSERT(shear(0, m::pi / 4) == KNTransformation(1, 0, 2, 1, 0, 0));
  // CPPUNIT_ASSERT(shear(m::pi / 4, m::pi / 4) == KNTransformation(1, 2, 2, 1, 0, 0));

  // translating
  CPPUNIT_ASSERT(translate(100, 0) == KNTransformation(1, 0, 0, 1, 100, 0));
  CPPUNIT_ASSERT(translate(0, 100) == KNTransformation(1, 0, 0, 1, 0, 100));
  CPPUNIT_ASSERT(translate(300, 100) == KNTransformation(1, 0, 0, 1, 300, 100));
}

void KNTransformationTest::testConstructionIdentity()
{
  using namespace libkeynote::transformations;

  CPPUNIT_ASSERT(center(0, 0) == KNTransformation());
  CPPUNIT_ASSERT(decenter(0, 0) == KNTransformation());
  CPPUNIT_ASSERT(flip(false, false) == KNTransformation());
  CPPUNIT_ASSERT(rotate(0) == KNTransformation());
  CPPUNIT_ASSERT(rotate(m::two_pi) == KNTransformation());
  CPPUNIT_ASSERT(scale(1, 1) == KNTransformation());
  CPPUNIT_ASSERT(shear(0, 0) == KNTransformation());
  CPPUNIT_ASSERT(translate(0, 0) == KNTransformation());
}

void KNTransformationTest::testConstructionFromGeometry()
{
  using namespace libkeynote::transformations;

  using libkeynote::KNGeometry;
  using libkeynote::KNPosition;
  using libkeynote::KNSize;

  {
    KNGeometry g;
    g.naturalSize = KNSize(100, 100);
    g.position = KNPosition(0, 0);

    const KNTransformation tr = makeTransformation(g);
    CPPUNIT_ASSERT(KNTransformation() == tr);
  }

  {
    KNGeometry g;
    g.naturalSize = KNSize(100, 100);
    g.position = KNPosition(200, 150);

    const KNTransformation tr = makeTransformation(g);
    CPPUNIT_ASSERT(translate(200, 150) == tr);
  }

  {
    KNGeometry g;
    g.naturalSize = KNSize(100, 100);
    g.position = KNPosition(0, 0);
    g.angle = m::half_pi;

    const KNTransformation tr = makeTransformation(g);
    CPPUNIT_ASSERT(wrap(100, 100, rotate(m::half_pi)) == tr);
  }

  {
    KNGeometry g;
    g.naturalSize = KNSize(100, 100);
    g.position = KNPosition(0, 0);
    g.horizontalFlip = true;

    const KNTransformation tr = makeTransformation(g);
    CPPUNIT_ASSERT(wrap(100, 100, flip(true, false)) == tr);
  }

  {
    KNGeometry g;
    g.naturalSize = KNSize(100, 100);
    g.position = KNPosition(0, 0);
    g.verticalFlip = true;

    const KNTransformation tr = makeTransformation(g);
    CPPUNIT_ASSERT(wrap(100, 100, flip(false, true)) == tr);
  }

  {
    KNGeometry g;
    g.naturalSize = KNSize(100, 100);
    g.position = KNPosition(200, 150);
    g.angle = m::half_pi;

    const KNTransformation tr = makeTransformation(g);
    CPPUNIT_ASSERT(wrap(100, 100, rotate(m::half_pi) * translate(200, 150)) == tr);
  }
}

void KNTransformationTest::testIdentities()
{
  using namespace libkeynote::transformations;

  CPPUNIT_ASSERT(center(100, 50) == translate(50, 25));
  CPPUNIT_ASSERT(decenter(100, 50) == translate(-50, -25));
  CPPUNIT_ASSERT((flip(true, false) * flip(false, true)) == flip(true, true));
  CPPUNIT_ASSERT((flip(false, true) * flip(true, false)) == flip(true, true));
  CPPUNIT_ASSERT((rotate(m::half_pi) * rotate(m::third_pi)) == (rotate(m::third_pi) * rotate(m::half_pi)));
  CPPUNIT_ASSERT(scale(-1, -1) == flip(true, true));
  CPPUNIT_ASSERT((translate(10, 20) * translate(80, 40)) == (translate(80, 40) * translate(10, 20)));
  CPPUNIT_ASSERT((translate(1, 2) * scale(2, 2)) == (scale(2, 2) * translate(2, 4)));
}

void KNTransformationTest::testInverseOperations()
{
  using namespace libkeynote::transformations;

  CPPUNIT_ASSERT(center(10, 20) * decenter(10, 20) == KNTransformation());
  CPPUNIT_ASSERT(decenter(10, 20) * center(10, 20) == KNTransformation());

  CPPUNIT_ASSERT(flip(true, false) * flip(true, false) == KNTransformation());
  CPPUNIT_ASSERT(flip(false, true) * flip(false, true) == KNTransformation());
  CPPUNIT_ASSERT(flip(true, true) * flip(true, true) == KNTransformation());

  CPPUNIT_ASSERT(rotate(m::pi) * rotate(-m::pi) == KNTransformation());

  CPPUNIT_ASSERT(scale(2, 1) * scale(0.5, 1) == KNTransformation());
  CPPUNIT_ASSERT(scale(1, 2) * scale(1, 0.5) == KNTransformation());
  CPPUNIT_ASSERT(scale(3, 2) * scale(1.0 / 3, 0.5) == KNTransformation());

  // CPPUNIT_ASSERT(shear() == KNTransformation());

  CPPUNIT_ASSERT(translate(10, 20) * translate(-10, -20) == KNTransformation());
}

void KNTransformationTest::testMultiplication()
{
  using namespace libkeynote::transformations;

  CPPUNIT_ASSERT(KNTransformation() * KNTransformation() == KNTransformation());

  CPPUNIT_ASSERT(KNTransformation() * KNTransformation(1, 2, 3, 4, 5, 6) == KNTransformation(1, 2, 3, 4, 5, 6));
  CPPUNIT_ASSERT(KNTransformation(1, 2, 3, 4, 5, 6) * KNTransformation() == KNTransformation(1, 2, 3, 4, 5, 6));
  CPPUNIT_ASSERT(KNTransformation(1, 2, 3, 4, 5, 6) * KNTransformation(6, 5, 4, 3, 2, 1) == KNTransformation(14, 11, 34, 27, 56, 44));
}

CPPUNIT_TEST_SUITE_REGISTRATION(KNTransformationTest);

}

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
