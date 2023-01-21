// Copyright 2022
// By Dr. Rykalova
// Editted by Dr. Daly
// test.cpp for PS1a
// updated 5/12/2022

#include <iostream>
#include <string>

#include "FibLFSR.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

//Original Step Test
BOOST_AUTO_TEST_CASE(testStepInstr1) {
  FibLFSR l("1011011000110110");
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
}
//Original Generate Test
BOOST_AUTO_TEST_CASE(testStepInstr2) {
  FibLFSR l2("1011011000110110");
  BOOST_REQUIRE_EQUAL(l2.generate(9), 51);
}
//Intensive Generate Test
BOOST_AUTO_TEST_CASE(testGenerateInstr3) {
  FibLFSR l2("1011011000110110");
  BOOST_REQUIRE_EQUAL(l2.generate(5), 3);
  BOOST_REQUIRE_EQUAL(l2.generate(5), 6);
  BOOST_REQUIRE_EQUAL(l2.generate(5), 14);
  BOOST_REQUIRE_EQUAL(l2.generate(5), 24);
  BOOST_REQUIRE_EQUAL(l2.generate(5), 1);
  BOOST_REQUIRE_EQUAL(l2.generate(5), 13);
  BOOST_REQUIRE_EQUAL(l2.generate(5), 28);
}
//Simple Size Set Test
BOOST_AUTO_TEST_CASE(testSizeInstr4) {
  FibLFSR l2("1011011000110110");
  BOOST_REQUIRE_EQUAL(l2.getSize(), 16);

}
//Simple test of limit generation, used to keep object bitstring value below threshold
BOOST_AUTO_TEST_CASE(testSizeInstr5) {
  FibLFSR l2("1011011000110110");
  BOOST_REQUIRE_EQUAL(l2.getLimit(), 65535);

}