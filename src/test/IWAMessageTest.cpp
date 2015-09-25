/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libetonyek project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <boost/make_shared.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "IWAMessage.h"
#include "IWORKMemoryStream.h"

using namespace libetonyek;

using std::size_t;
using std::string;

namespace test
{

namespace
{

RVNGInputStreamPtr_t makeStream(const unsigned char *const bytes, const unsigned long length)
{
  return boost::make_shared<IWORKMemoryStream>(bytes, length);
}

}

class IWAMessageTest : public CPPUNIT_NS::TestFixture
{
public:
  virtual void setUp();
  virtual void tearDown();

private:
  CPPUNIT_TEST_SUITE(IWAMessageTest);
  CPPUNIT_TEST(testSimple);
  CPPUNIT_TEST(testNestedMessage);
  CPPUNIT_TEST(testMissingFields);
  CPPUNIT_TEST(testRepeated);
  CPPUNIT_TEST(testPacked);
  CPPUNIT_TEST(testInvalidInput);
  CPPUNIT_TEST_SUITE_END();

private:
  void testSimple();
  void testNestedMessage();
  void testMissingFields();
  void testRepeated();
  void testPacked();
  void testInvalidInput();
};

void IWAMessageTest::setUp()
{
}

void IWAMessageTest::tearDown()
{
}

#define BYTES(b) (reinterpret_cast<const unsigned char *>(b)), (sizeof(b) - 1)

void IWAMessageTest::testSimple()
{
  {
    CPPUNIT_ASSERT_NO_THROW(IWAMessage(makeStream(BYTES("\x8\x4")), 2));
    IWAMessage msg(makeStream(BYTES("\x8\x4")), 2);
    CPPUNIT_ASSERT_NO_THROW(msg.uint64(1));
    CPPUNIT_ASSERT(msg.uint64(1));
    CPPUNIT_ASSERT_EQUAL(uint64_t(4), msg.uint64(1).get());
  }

  {
    const RVNGInputStreamPtr_t input(
      makeStream(BYTES(
                   "\x8\x4" // 1: uint64 = 4
                   "\x11\x2\x0\x0\x0\x0\x0\x0\x0" // 2: fixed64 = 2
                   "\x1a\x5hello" // 3: string = "hello"
                   "\x25\x20\x0\x0\x0" // 4: fixed32 = 32
                 ))
    );
    IWAMessage msg(input, 23);
    CPPUNIT_ASSERT_NO_THROW(msg.uint64(1));
    CPPUNIT_ASSERT(msg.uint64(1));
    CPPUNIT_ASSERT_EQUAL(uint64_t(4), msg.uint64(1).get());
    CPPUNIT_ASSERT_NO_THROW(msg.fixed64(2));
    CPPUNIT_ASSERT(msg.fixed64(2));
    CPPUNIT_ASSERT_EQUAL(uint64_t(2), msg.fixed64(2).get());
    CPPUNIT_ASSERT_NO_THROW(msg.string(3));
    CPPUNIT_ASSERT(msg.string(3));
    CPPUNIT_ASSERT_EQUAL(string("hello"), msg.string(3).get());
  }
}

void IWAMessageTest::testNestedMessage()
{
  // TODO: add
}


void IWAMessageTest::testMissingFields()
{
  IWAMessage msg(makeStream(BYTES("\x8\x4")), 2);
  CPPUNIT_ASSERT_NO_THROW(msg.string(4));
  CPPUNIT_ASSERT(!msg.string(4));
  CPPUNIT_ASSERT_NO_THROW(msg.fixed64(2));
  CPPUNIT_ASSERT(!msg.fixed64(2));
  CPPUNIT_ASSERT_NO_THROW(msg.message(8));
  CPPUNIT_ASSERT(!msg.message(8));
}

void IWAMessageTest::testRepeated()
{
  IWAMessage msg(makeStream(BYTES("\x8\x4\x8\x8\x8\x10")), 6);
  CPPUNIT_ASSERT_NO_THROW(msg.uint64(1));
  CPPUNIT_ASSERT_EQUAL(size_t(3), msg.uint64(1).size());
  CPPUNIT_ASSERT_EQUAL(uint64_t(4), msg.uint64(1)[0]);
  CPPUNIT_ASSERT_EQUAL(uint64_t(8), msg.uint64(1)[1]);
  CPPUNIT_ASSERT_EQUAL(uint64_t(16), msg.uint64(1)[2]);
}

void IWAMessageTest::testPacked()
{
  IWAMessage msg(makeStream(BYTES("\xa\x3\x1\x2\x3")), 5);
  CPPUNIT_ASSERT_NO_THROW(msg.uint64(1));
  CPPUNIT_ASSERT_EQUAL(size_t(3), msg.uint64(1).size());
  CPPUNIT_ASSERT_EQUAL(uint64_t(1), msg.uint64(1)[0]);
  CPPUNIT_ASSERT_EQUAL(uint64_t(2), msg.uint64(1)[1]);
  CPPUNIT_ASSERT_EQUAL(uint64_t(3), msg.uint64(1)[2]);
}

void IWAMessageTest::testInvalidInput()
{
  // TODO: add
}

#undef BYTES

CPPUNIT_TEST_SUITE_REGISTRATION(IWAMessageTest);

}

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
