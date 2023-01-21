// Copyright [2022] Andrew Allman




#include <iostream>
#include <string>


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include<SFML/Audio.hpp>
#include"./KGuitarSim.hpp"

/* Tests size after initialization, using function pointer to lambda
   Tests exception when attempting to peek, or dequeue an item from the empty buffer*/

auto evalSize = [](size_t head, size_t tail, size_t capacity, bool is_full) {
    return is_full ? capacity : (head - tail) % capacity; };

BOOST_AUTO_TEST_CASE(testInitConditions) {
  CircularBuffer<int16_t> cBuf(10);

  BOOST_REQUIRE_EQUAL(cBuf.size(evalSize), 0);
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
  BOOST_REQUIRE_THROW(CircularBuffer<int16_t> cBuf(0), std::invalid_argument);
  BOOST_REQUIRE_NO_THROW(CircularBuffer<int16_t> cBuf(4));

  CircularBuffer<int16_t> cBuf(4);
  BOOST_REQUIRE_EQUAL(cBuf.size(evalSize), 0);
  cBuf.enqueue(1);
  cBuf.enqueue(2);
  cBuf.enqueue(3);
  cBuf.enqueue(4);
  BOOST_REQUIRE_EQUAL(cBuf.isEmpty(), false);
  BOOST_REQUIRE_EQUAL(cBuf.isFull(), true);

  BOOST_REQUIRE_EQUAL(cBuf.size(evalSize), 4);

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

BOOST_AUTO_TEST_CASE(testStringSound) {
  BOOST_REQUIRE_THROW(StringSound gs(0), std::invalid_argument);
  BOOST_REQUIRE_NO_THROW(StringSound gs(440));
  StringSound gs(440);
  gs.pluck();
  for (int i = 0; i < 100; i++) {
    gs.tick();
  }
  BOOST_REQUIRE_EQUAL(gs.time(), 100);
  vector<sf::Int16> sV(100, 0);
  BOOST_REQUIRE_NO_THROW(StringSound gs2(sV));
  vector<sf::Int16> sV2;
  BOOST_REQUIRE_THROW(StringSound gs2(sV2), std::invalid_argument);
  StringSound gs3(440);
  BOOST_REQUIRE_NO_THROW(gs3.pluck());
  BOOST_REQUIRE_GT(abs(gs3.sample()), 0);
  gs3.sample();
  BOOST_REQUIRE_NO_THROW(gs3.pluck());
}
