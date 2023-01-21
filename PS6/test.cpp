// Copyright 2022 Andrew Allman



#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main

#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include <boost/test/unit_test.hpp>

#include"./RandWriter.hpp"

using std::ifstream;
using std::stringstream;
using std::cin;


BOOST_AUTO_TEST_CASE(testInit) {
  std::ifstream fp("tomsawyer.txt");
  string inp_text;
  stringstream buffer;
  buffer << fp.rdbuf();
  BOOST_REQUIRE_NO_THROW(RandWriter(buffer.str(), 10));
  RandWriter rw(buffer.str(), 0);
  BOOST_REQUIRE_EQUAL(rw.orderK(), 0);
  BOOST_REQUIRE_GT(rw.freq("", ' '), rw.freq("", 'e'));
  BOOST_REQUIRE_GT(rw.freq(""), 380000);
  BOOST_REQUIRE_NO_THROW(rw.kRand(""));
  BOOST_REQUIRE_NO_THROW(rw.generate("", 0));
  BOOST_REQUIRE_THROW(rw.generate("I", 10), std::runtime_error);
}
