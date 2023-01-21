// Copyright [2022] Andrew Allman




#include <iostream>
#include <string>

#include "./CircularBuffer.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

/* Tests size after initialization, using function pointer to lambda
   Tests exception when attempting to peek, or dequeue an item from the empty buffer*/

BOOST_AUTO_TEST_CASE(testInitConditions) {
  size_t (*pEvalSize)(size_t, size_t, size_t, bool) = evalSize;
  CircularBuffer<int16_t> cBuf(10);

  // Extra credit implementation
  BOOST_REQUIRE_EQUAL(cBuf.size(pEvalSize), 0);

  BOOST_REQUIRE_THROW(cBuf.peek(), std::runtime_error);
  BOOST_REQUIRE_THROW(cBuf.dequeue(), std::runtime_error);
}

/* Tests invalid capacity value in constructor
   Test valid capacity value in constructor
   Tests size after initialization
   Tests functionality of isEmpty/isFull
   Tests size after adding elements
   Tests exception thrown trying to add item to full buffer
   Tests peek
   Tests dequeue return values while performing more queue operations
   Rechecks dequeue values after operations
   Tests no exception thrown adding item to buffer after operations
   Tests exceptions thrown peek or dequeue from empty buffer */

BOOST_AUTO_TEST_CASE(testFunctionality) {
  size_t (*pEvalSize)(size_t, size_t, size_t, bool) = evalSize;
  BOOST_REQUIRE_THROW(CircularBuffer<int16_t> cBuf(0), std::invalid_argument);
  BOOST_REQUIRE_NO_THROW(CircularBuffer<int16_t> cBuf(4));

  CircularBuffer<int16_t> cBuf(4);
  BOOST_REQUIRE_EQUAL(cBuf.size(pEvalSize), 0);
  std::cout << cBuf.size(pEvalSize) << std::endl;
  cBuf.enqueue(1);
  std::cout << cBuf.size(pEvalSize) << std::endl;
  cBuf.enqueue(2);
  std::cout << cBuf.size(pEvalSize) << std::endl;
  cBuf.enqueue(3);
  std::cout << cBuf.size(pEvalSize) << std::endl;
  cBuf.enqueue(4);
  std::cout << cBuf.size(pEvalSize) << std::endl;
  BOOST_REQUIRE_EQUAL(cBuf.isEmpty(), false);
  BOOST_REQUIRE_EQUAL(cBuf.isFull(), true);

  // Extra credit implementation
  BOOST_REQUIRE_EQUAL(cBuf.size(pEvalSize), 4);

  BOOST_REQUIRE_THROW(cBuf.enqueue(5), std::runtime_error);
  BOOST_REQUIRE_EQUAL(cBuf.peek(), 1);
  BOOST_REQUIRE_EQUAL(cBuf.dequeue(), 1);
  cBuf.enqueue(1);
  BOOST_REQUIRE_EQUAL(cBuf.dequeue(), 2);
  cBuf.enqueue(2);
  BOOST_REQUIRE_EQUAL(cBuf.dequeue(), 3);
  cBuf.enqueue(3);
  BOOST_REQUIRE_EQUAL(cBuf.dequeue(), 4);
  cBuf.enqueue(4);
  BOOST_REQUIRE_EQUAL(cBuf.dequeue(), 1);
  BOOST_REQUIRE_EQUAL(cBuf.dequeue(), 2);
  BOOST_REQUIRE_EQUAL(cBuf.dequeue(), 3);
  BOOST_REQUIRE_EQUAL(cBuf.dequeue(), 4);
  BOOST_REQUIRE_NO_THROW(cBuf.enqueue(1));
  cBuf.dequeue();
  BOOST_REQUIRE_EQUAL(cBuf.isFull(), false);
  BOOST_REQUIRE_EQUAL(cBuf.isEmpty(), true);
  BOOST_REQUIRE_THROW(cBuf.peek(), std::runtime_error);
  BOOST_REQUIRE_THROW(cBuf.dequeue(), std::runtime_error);
}
